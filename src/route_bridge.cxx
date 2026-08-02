#include "route_bridge.hxx"

#include <algorithm>
#include <boost/multiprecision/cpp_int.hpp>
#include <chrono>
#include <cmath>
#include <functional>
#include <limits>
#include <map>
#include <numeric>
#include <stdexcept>
#include <tuple>
#include <utility>

namespace {

using boost::multiprecision::cpp_int;
using Clock = std::chrono::steady_clock;

constexpr double kMinimumClosureMass = 1.0e-8;

size_t covarianceIndex(size_t first, size_t second) {
    if (first > second) {
        std::swap(first, second);
    }

    size_t index = 0;
    for (size_t left = 0; left < kGapCoordinateCount; ++left) {
        for (size_t right = left; right < kGapCoordinateCount; ++right) {
            if (left == first && right == second) {
                return index;
            }
            ++index;
        }
    }
    throw std::logic_error("invalid covariance index");
}

double covarianceFrobenius(const GapCovariance& covariance) {
    long double squared = 0.0L;
    size_t index = 0;
    for (size_t first = 0; first < kGapCoordinateCount; ++first) {
        for (size_t second = first; second < kGapCoordinateCount; ++second) {
            const int multiplicity = first == second ? 1 : 2;
            squared += multiplicity *
                       static_cast<long double>(covariance[index]) *
                       covariance[index];
            ++index;
        }
    }
    return std::sqrt(static_cast<double>(squared));
}

double thirdMomentFrobenius(const GapThirdMoment& moment) {
    long double squared = 0.0L;
    size_t index = 0;
    for (size_t first = 0; first < kGapCoordinateCount; ++first) {
        for (size_t second = first; second < kGapCoordinateCount; ++second) {
            for (size_t third = second; third < kGapCoordinateCount; ++third) {
                int multiplicity = 6;
                if (first == third) {
                    multiplicity = 1;
                } else if (first == second || second == third) {
                    multiplicity = 3;
                }
                squared += multiplicity *
                           static_cast<long double>(moment[index]) *
                           moment[index];
                ++index;
            }
        }
    }
    return std::sqrt(static_cast<double>(squared));
}

double coordinateNorm(const GapCoordinate& coordinate) {
    long double squared = 0.0L;
    for (double value : coordinate) {
        squared += static_cast<long double>(value) * value;
    }
    return std::sqrt(static_cast<double>(squared));
}

long double logDoubleFactorial(int value) {
    if (value <= 0) {
        return 0.0L;
    }

    const int half = value / 2;
    if (value % 2 == 0) {
        return half * std::log(2.0L) +
               std::lgamma(static_cast<long double>(half + 1));
    }
    return std::lgamma(static_cast<long double>(value + 1)) -
           half * std::log(2.0L) -
           std::lgamma(static_cast<long double>(half + 1));
}

long double legendrePolynomial(int degree, long double value) {
    if (degree == 0) {
        return 1.0L;
    }
    if (degree == 1) {
        return value;
    }

    long double previous = 1.0L;
    long double current = value;
    for (int order = 1; order < degree; ++order) {
        const long double next =
            ((2 * order + 1) * value * current - order * previous) /
            (order + 1);
        previous = current;
        current = next;
    }
    return current;
}

struct TransitionSnapshot {
    std::vector<double> kernel;
    std::vector<double> sourceMass;
};

struct ClosureAccumulator {
    const ProfilePartition* partition = nullptr;
    std::vector<long double> sourceMass;
    std::vector<long double> squaredSourceMass;
    std::vector<long double> weightedConditionalNorm;
    std::vector<long double> classFlow;
    std::vector<long double> targetScratch;
    std::vector<uint32_t> touchedTargets;

    explicit ClosureAccumulator(const ProfilePartition& input)
        : partition(&input), sourceMass(input.classSizes.size(), 0.0L),
          squaredSourceMass(input.classSizes.size(), 0.0L),
          weightedConditionalNorm(input.classSizes.size(), 0.0L),
          classFlow(input.classSizes.size() * input.classSizes.size(), 0.0L),
          targetScratch(input.classSizes.size(), 0.0L) {}

    size_t estimatedBytes() const {
        return sourceMass.capacity() * sizeof(long double) +
               squaredSourceMass.capacity() * sizeof(long double) +
               weightedConditionalNorm.capacity() * sizeof(long double) +
               classFlow.capacity() * sizeof(long double) +
               targetScratch.capacity() * sizeof(long double) +
               touchedTargets.capacity() * sizeof(uint32_t);
    }
};

struct ClosureWork {
    ClosureResult result;
    std::vector<TransitionSnapshot> transitions;
};

ClosurePosition finishClosurePosition(int position,
                                      ClosureAccumulator& accumulator,
                                      TransitionSnapshot& snapshot) {
    const size_t classCount = accumulator.partition->classSizes.size();
    ClosurePosition result;
    result.position = position;

    long double totalMass = 0.0L;
    long double weightedEffectiveSize = 0.0L;
    long double weightedDefect = 0.0L;
    long double singletonMass = 0.0L;
    long double maximalDefect = 0.0L;

    snapshot.kernel.assign(classCount * classCount, 0.0);
    snapshot.sourceMass.assign(classCount, 0.0);

    for (size_t sourceClass = 0; sourceClass < classCount; ++sourceClass) {
        const long double mass = accumulator.sourceMass[sourceClass];
        if (!(mass > 0.0L)) {
            continue;
        }

        ++result.occupiedClasses;
        totalMass += mass;
        snapshot.sourceMass[sourceClass] = static_cast<double>(mass);
        if (accumulator.partition->classSizes[sourceClass] == 1) {
            singletonMass += mass;
        }

        const long double effectiveSize =
            mass * mass / accumulator.squaredSourceMass[sourceClass];
        weightedEffectiveSize += mass * effectiveSize;

        long double meanNorm = 0.0L;
        const size_t rowOffset = sourceClass * classCount;
        for (size_t targetClass = 0; targetClass < classCount; ++targetClass) {
            const long double probability =
                accumulator.classFlow[rowOffset + targetClass] / mass;
            snapshot.kernel[rowOffset + targetClass] =
                static_cast<double>(probability);
            meanNorm += probability * probability;
        }

        long double rawDefect =
            accumulator.weightedConditionalNorm[sourceClass] / mass - meanNorm;
        rawDefect = std::max(0.0L, rawDefect);

        weightedDefect += mass * rawDefect;
        maximalDefect = std::max(maximalDefect, rawDefect);
    }

    result.singletonMass = static_cast<double>(singletonMass);
    result.assessableMass = static_cast<double>(totalMass);
    result.meanEffectiveSize =
        totalMass > 0.0L
            ? static_cast<double>(weightedEffectiveSize / totalMass)
            : std::numeric_limits<double>::quiet_NaN();
    result.rmsDefect =
        totalMass > 0.0L
            ? std::sqrt(static_cast<double>(weightedDefect / totalMass))
            : std::numeric_limits<double>::quiet_NaN();
    result.maxDefect = totalMass > 0.0L
                           ? std::sqrt(static_cast<double>(maximalDefect))
                           : std::numeric_limits<double>::quiet_NaN();
    return result;
}

void finishTransitionPlateau(ClosureWork& work) {
    const size_t classCount = work.result.classCount;
    if (work.transitions.empty() || classCount == 0) {
        work.result.plateauDefect = std::numeric_limits<double>::quiet_NaN();
        return;
    }

    std::vector<long double> meanKernel(classCount * classCount, 0.0L);
    std::vector<size_t> occupiedPositionCount(classCount, 0);
    for (const TransitionSnapshot& snapshot : work.transitions) {
        for (size_t sourceClass = 0; sourceClass < classCount; ++sourceClass) {
            if (snapshot.sourceMass[sourceClass] < kMinimumClosureMass) {
                continue;
            }
            ++occupiedPositionCount[sourceClass];
            const size_t rowOffset = sourceClass * classCount;
            for (size_t targetClass = 0; targetClass < classCount;
                 ++targetClass) {
                meanKernel[rowOffset + targetClass] +=
                    snapshot.kernel[rowOffset + targetClass];
            }
        }
    }

    for (size_t sourceClass = 0; sourceClass < classCount; ++sourceClass) {
        if (occupiedPositionCount[sourceClass] == 0) {
            continue;
        }
        const size_t rowOffset = sourceClass * classCount;
        for (size_t targetClass = 0; targetClass < classCount; ++targetClass) {
            meanKernel[rowOffset + targetClass] /=
                occupiedPositionCount[sourceClass];
        }
    }

    long double maximalDefect = 0.0L;
    for (const TransitionSnapshot& snapshot : work.transitions) {
        long double squaredDefect = 0.0L;
        for (size_t sourceClass = 0; sourceClass < classCount; ++sourceClass) {
            const long double mass = snapshot.sourceMass[sourceClass];
            if (!(mass > 0.0L)) {
                continue;
            }
            const size_t rowOffset = sourceClass * classCount;
            long double rowSquared = 0.0L;
            for (size_t targetClass = 0; targetClass < classCount;
                 ++targetClass) {
                const long double difference =
                    snapshot.kernel[rowOffset + targetClass] -
                    meanKernel[rowOffset + targetClass];
                rowSquared += difference * difference;
            }
            squaredDefect += mass * rowSquared;
        }
        maximalDefect = std::max(maximalDefect, squaredDefect);
    }

    work.result.plateauDefect = std::sqrt(static_cast<double>(maximalDefect));
}

std::pair<int, int> bulkRange(int horizon, double fraction) {
    int first = static_cast<int>(std::ceil(fraction * horizon));
    int last = static_cast<int>(std::floor((1.0 - fraction) * horizon));
    first = std::clamp(first, 0, horizon - 1);
    last = std::clamp(last, 0, horizon - 1);
    if (first > last) {
        first = horizon / 2;
        last = first;
    }
    return {first, last};
}

std::vector<std::vector<cpp_int>> computeExactForward(const ReferenceDag& graph,
                                                      size_t maximumHorizon) {
    const size_t vertexCount = graph.vertexCount();
    const auto offsets = graph.outgoingOffsets();
    const auto targets = graph.outgoingTargets();
    std::vector<std::vector<cpp_int>> forward(
        maximumHorizon + 1, std::vector<cpp_int>(vertexCount, 1));

    for (size_t horizon = 1; horizon <= maximumHorizon; ++horizon) {
        std::ranges::fill(forward[horizon], 0);
        for (size_t source = 0; source < vertexCount; ++source) {
            for (size_t edge = offsets[source]; edge < offsets[source + 1];
                 ++edge) {
                forward[horizon][source] += forward[horizon - 1][targets[edge]];
            }
        }
    }
    return forward;
}

std::vector<std::vector<cpp_int>>
computeExactBackward(const ReferenceDag& graph, size_t maximumHorizon) {
    const size_t vertexCount = graph.vertexCount();
    const auto offsets = graph.outgoingOffsets();
    const auto targets = graph.outgoingTargets();
    std::vector<std::vector<cpp_int>> backward(
        maximumHorizon + 1, std::vector<cpp_int>(vertexCount, 1));

    for (size_t horizon = 1; horizon <= maximumHorizon; ++horizon) {
        std::ranges::fill(backward[horizon], 0);
        for (size_t source = 0; source < vertexCount; ++source) {
            for (size_t edge = offsets[source]; edge < offsets[source + 1];
                 ++edge) {
                backward[horizon][targets[edge]] +=
                    backward[horizon - 1][source];
            }
        }
    }
    return backward;
}

struct EnumeratedRoutes {
    cpp_int routeCount = 0;
    std::vector<cpp_int> edgePositionCounts;
    GapCoordinate mean{};
    GapCovariance rawSecond{};
    GapThirdMoment rawThird{};
};

EnumeratedRoutes enumerateRoutes(const ReferenceDag& graph,
                                 const GapNodeState& state, int horizon) {
    const auto offsets = graph.outgoingOffsets();
    const auto targets = graph.outgoingTargets();
    EnumeratedRoutes result;
    result.edgePositionCounts.assign(
        static_cast<size_t>(horizon) * graph.edgeCount(), 0);
    std::vector<size_t> routeEdges(static_cast<size_t>(horizon));

    std::function<void(uint32_t, int)> visit = [&](uint32_t vertex, int depth) {
        if (depth == horizon) {
            ++result.routeCount;
            for (int position = 0; position < horizon; ++position) {
                ++result.edgePositionCounts[static_cast<size_t>(position) *
                                                graph.edgeCount() +
                                            routeEdges[position]];
            }
            return;
        }

        for (size_t edge = offsets[vertex]; edge < offsets[vertex + 1];
             ++edge) {
            routeEdges[depth] = edge;
            visit(targets[edge], depth + 1);
        }
    };

    for (uint32_t start = 0; start < graph.vertexCount(); ++start) {
        visit(start, 0);
    }

    if (result.routeCount == 0) {
        return result;
    }

    const long double denominator =
        result.routeCount.convert_to<long double>() * horizon;
    for (int position = 0; position < horizon; ++position) {
        for (size_t source = 0; source < graph.vertexCount(); ++source) {
            for (size_t edge = offsets[source]; edge < offsets[source + 1];
                 ++edge) {
                const cpp_int count =
                    result.edgePositionCounts[static_cast<size_t>(position) *
                                                  graph.edgeCount() +
                                              edge];
                if (count == 0) {
                    continue;
                }
                const long double weight =
                    count.convert_to<long double>() / denominator;
                const size_t target = targets[edge];
                GapCoordinate difference{};
                for (size_t coordinate = 0; coordinate < kGapCoordinateCount;
                     ++coordinate) {
                    difference[coordinate] =
                        state.coordinates[target][coordinate] -
                        state.coordinates[source][coordinate];
                    result.mean[coordinate] +=
                        static_cast<double>(weight * difference[coordinate]);
                }

                size_t secondIndex = 0;
                for (size_t first = 0; first < kGapCoordinateCount; ++first) {
                    for (size_t second = first; second < kGapCoordinateCount;
                         ++second) {
                        result.rawSecond[secondIndex++] += static_cast<double>(
                            weight * difference[first] * difference[second]);
                    }
                }

                size_t thirdIndex = 0;
                for (size_t first = 0; first < kGapCoordinateCount; ++first) {
                    for (size_t second = first; second < kGapCoordinateCount;
                         ++second) {
                        for (size_t third = second; third < kGapCoordinateCount;
                             ++third) {
                            result.rawThird[thirdIndex++] +=
                                static_cast<double>(weight * difference[first] *
                                                    difference[second] *
                                                    difference[third]);
                        }
                    }
                }
            }
        }
    }
    return result;
}

void requireClose(double actual, double expected, double tolerance,
                  const char* label) {
    if (std::abs(actual - expected) > tolerance) {
        throw std::runtime_error(std::string("route self-test failed: ") +
                                 label);
    }
}

} // namespace

size_t StableRouteCounts::maxHorizon() const {
    return forward.empty() ? 0 : forward.size() - 1;
}

bool StableRouteCounts::hasRoutes(size_t horizon) const {
    return horizon < forwardLogs.size() && std::isfinite(forwardLogs[horizon]);
}

size_t StableRouteCounts::estimatedBytes() const {
    size_t bytes = sizeof(*this);
    for (const auto& level : forward) {
        bytes += level.capacity() * sizeof(long double);
    }
    for (const auto& level : backward) {
        bytes += level.capacity() * sizeof(long double);
    }
    bytes += forward.capacity() * sizeof(std::vector<long double>);
    bytes += backward.capacity() * sizeof(std::vector<long double>);
    bytes += forwardLogs.capacity() * sizeof(long double);
    bytes += backwardLogs.capacity() * sizeof(long double);
    bytes += forwardScales.capacity() * sizeof(long double);
    return bytes;
}

StableRouteCounts computeRouteCounts(const ReferenceDag& graph,
                                     size_t maxHorizon) {
    const size_t vertexCount = graph.vertexCount();
    const auto offsets = graph.outgoingOffsets();
    const auto targets = graph.outgoingTargets();
    const long double negativeInfinity =
        -std::numeric_limits<long double>::infinity();

    StableRouteCounts result;
    result.forward.assign(maxHorizon + 1,
                          std::vector<long double>(vertexCount, 0.0L));
    result.backward.assign(maxHorizon + 1,
                           std::vector<long double>(vertexCount, 0.0L));
    result.forwardLogs.assign(maxHorizon + 1, negativeInfinity);
    result.backwardLogs.assign(maxHorizon + 1, negativeInfinity);
    result.forwardScales.assign(maxHorizon + 1, 0.0L);

    const long double initial = 1.0L / vertexCount;
    std::ranges::fill(result.forward[0], initial);
    std::ranges::fill(result.backward[0], initial);
    result.forwardLogs[0] = std::log(static_cast<long double>(vertexCount));
    result.backwardLogs[0] = result.forwardLogs[0];
    result.forwardScales[0] = 1.0L;

    for (size_t horizon = 1; horizon <= maxHorizon; ++horizon) {
        auto& next = result.forward[horizon];
        const auto& previous = result.forward[horizon - 1];
        for (size_t source = 0; source < vertexCount; ++source) {
            long double count = 0.0L;
            for (size_t edge = offsets[source]; edge < offsets[source + 1];
                 ++edge) {
                count += previous[targets[edge]];
            }
            next[source] = count;
        }

        const long double scale =
            std::accumulate(next.begin(), next.end(), 0.0L);
        result.forwardScales[horizon] = scale;
        if (scale > 0.0L && std::isfinite(result.forwardLogs[horizon - 1])) {
            for (long double& value : next) {
                value /= scale;
            }
            result.forwardLogs[horizon] =
                result.forwardLogs[horizon - 1] + std::log(scale);
        }
    }

    for (size_t horizon = 1; horizon <= maxHorizon; ++horizon) {
        auto& next = result.backward[horizon];
        const auto& previous = result.backward[horizon - 1];
        for (size_t source = 0; source < vertexCount; ++source) {
            const long double sourceValue = previous[source];
            for (size_t edge = offsets[source]; edge < offsets[source + 1];
                 ++edge) {
                next[targets[edge]] += sourceValue;
            }
        }

        const long double scale =
            std::accumulate(next.begin(), next.end(), 0.0L);
        if (scale > 0.0L && std::isfinite(result.backwardLogs[horizon - 1])) {
            for (long double& value : next) {
                value /= scale;
            }
            result.backwardLogs[horizon] =
                result.backwardLogs[horizon - 1] + std::log(scale);
        }
    }

    for (size_t horizon = 0; horizon <= maxHorizon; ++horizon) {
        if (std::isfinite(result.forwardLogs[horizon]) &&
            std::isfinite(result.backwardLogs[horizon])) {
            result.maxLogError = std::max(
                result.maxLogError, std::abs(result.forwardLogs[horizon] -
                                             result.backwardLogs[horizon]));
        }
    }

    return result;
}

SignatureSummary summarizeSignatures(const GapNodeState& state) {
    std::map<GapSignature, uint32_t> classes;
    for (const GapSignature& signature : state.signatures) {
        ++classes[signature];
    }

    SignatureSummary result;
    result.classCount = classes.size();
    result.classSizes.reserve(classes.size());
    for (const auto& [signature, size] : classes) {
        static_cast<void>(signature);
        result.classSizes.push_back(size);
        result.largestClass =
            std::max(result.largestClass, static_cast<size_t>(size));
        if (size == 1) {
            ++result.singletonClasses;
            ++result.singletonNodes;
        }
    }
    result.degenerate =
        result.singletonNodes * 20 >= state.signatures.size() * 19;
    return result;
}

std::vector<ProfilePartition> buildPartitions(const GapNodeState& state,
                                              std::span<const int> bins) {
    std::vector<ProfilePartition> result;
    result.reserve(bins.size());

    for (const int binCount : bins) {
        if (binCount < 2) {
            throw std::invalid_argument(
                "closure bins per coordinate must be at least two");
        }

        using Key = std::array<uint32_t, kGapCoordinateCount>;
        std::map<Key, uint32_t> classIds;
        ProfilePartition partition;
        partition.bins = binCount;
        partition.classIds.resize(state.coordinates.size());

        for (size_t vertex = 0; vertex < state.coordinates.size(); ++vertex) {
            Key key{};
            for (size_t coordinate = 0; coordinate < kGapCoordinateCount;
                 ++coordinate) {
                const double value =
                    std::clamp(state.coordinates[vertex][coordinate], 0.0,
                               std::nextafter(1.0, 0.0));
                key[coordinate] = static_cast<uint32_t>(
                    std::min(binCount - 1,
                             static_cast<int>(std::floor(value * binCount))));
            }

            const auto [iterator, inserted] = classIds.try_emplace(
                key, static_cast<uint32_t>(classIds.size()));
            if (inserted) {
                partition.classSizes.push_back(0);
            }
            const uint32_t classId = iterator->second;
            partition.classIds[vertex] = classId;
            ++partition.classSizes[classId];
        }
        result.push_back(std::move(partition));
    }

    return result;
}

std::vector<double> computeLegendreModes(const ReferenceDag& graph,
                                         int modeCount) {
    if (!graph.hasLatentMarks()) {
        throw std::invalid_argument(
            "Legendre validation requires latent reference marks");
    }
    if (modeCount < 0) {
        throw std::invalid_argument("Legendre mode count cannot be negative");
    }

    std::vector<long double> sums(static_cast<size_t>(modeCount), 0.0L);
    for (double mark : graph.latentMarks()) {
        const long double centered = 1.0L - 2.0L * mark;
        for (int mode = 1; mode <= modeCount; ++mode) {
            sums[static_cast<size_t>(mode - 1)] +=
                std::sqrt(static_cast<long double>(4 * mode + 1)) *
                legendrePolynomial(2 * mode, centered);
        }
    }

    const long double normalization =
        std::sqrt(static_cast<long double>(graph.vertexCount()));
    std::vector<double> result(static_cast<size_t>(modeCount));
    for (int mode = 0; mode < modeCount; ++mode) {
        result[static_cast<size_t>(mode)] = static_cast<double>(
            sums[static_cast<size_t>(mode)] / normalization);
    }
    return result;
}

std::vector<RouteCalibration>
computeCalibration(const ReferenceDag& graph, const StableRouteCounts& routes,
                   std::span<const double> modes, int maxLength) {
    if (maxLength < 1 || static_cast<size_t>(maxLength) > routes.maxHorizon()) {
        throw std::invalid_argument(
            "route calibration length exceeds the route workspace");
    }

    std::vector<RouteCalibration> result;
    result.reserve(static_cast<size_t>(maxLength));
    const long double vertexCount = graph.vertexCount();

    for (int length = 1; length <= maxLength; ++length) {
        RouteCalibration calibration;
        calibration.length = length;
        calibration.logCount = routes.forwardLogs[length];

        const long double pathTarget =
            std::exp(-std::lgamma(static_cast<long double>(2 * length + 2)));
        const long double subsetTarget =
            std::exp(std::lgamma(static_cast<long double>(length + 2)) -
                     std::lgamma(static_cast<long double>(2 * length + 2)));
        calibration.pathTarget = static_cast<double>(pathTarget);
        calibration.routeTarget = static_cast<double>(subsetTarget);

        if (routes.hasRoutes(static_cast<size_t>(length)) &&
            graph.vertexCount() > static_cast<size_t>(length)) {
            const long double logFallingFactorial =
                std::lgamma(vertexCount + 1.0L) -
                std::lgamma(vertexCount - length);
            const long double pathDensity =
                std::exp(calibration.logCount - logFallingFactorial);
            const long double subsetMean =
                pathDensity *
                std::exp(std::lgamma(static_cast<long double>(length + 2)));
            calibration.pathDensity = static_cast<double>(pathDensity);
            calibration.routeMean = static_cast<double>(subsetMean);
        }

        calibration.scaledFluctuation =
            std::sqrt(static_cast<double>(vertexCount)) *
            (calibration.routeMean - calibration.routeTarget);

        long double prediction = 0.0L;
        for (int mode = 1;
             mode <= length && static_cast<size_t>(mode) <= modes.size();
             ++mode) {
            const long double logProjection =
                std::lgamma(static_cast<long double>(length + 2)) -
                std::log(2.0L) +
                0.5L * std::log(static_cast<long double>(4 * mode + 1)) -
                logDoubleFactorial(2 * length - 2 * mode) -
                logDoubleFactorial(2 * length + 2 * mode + 1);
            prediction +=
                std::exp(logProjection) * modes[static_cast<size_t>(mode - 1)];
        }
        calibration.modePrediction = static_cast<double>(prediction);
        calibration.modeResidual =
            calibration.scaledFluctuation - calibration.modePrediction;
        result.push_back(calibration);
    }
    return result;
}

HorizonResult analyzeHorizon(const ReferenceDag& graph,
                             const GapNodeState& state,
                             const StableRouteCounts& routes, int horizon,
                             std::span<const ProfilePartition> partitions,
                             double bulkFraction,
                             std::span<const double> lindebergThresholds) {
    const auto started = Clock::now();
    if (horizon < 1 || static_cast<size_t>(horizon + 1) > routes.maxHorizon()) {
        throw std::invalid_argument(
            "horizon analysis requires route counts through p + 1");
    }
    if (!(bulkFraction > 0.0 && bulkFraction < 0.5)) {
        throw std::invalid_argument("bulk fraction must lie in (0, 1/2)");
    }

    HorizonResult result;
    result.p = horizon;
    result.valid = routes.hasRoutes(static_cast<size_t>(horizon));
    result.logCount = routes.forwardLogs[horizon];
    result.logNextCount = routes.forwardLogs[horizon + 1];
    result.peakBytes = routes.estimatedBytes() + graph.estimatedBytes() +
                       state.estimatedBytes();
    if (!result.valid) {
        result.seconds =
            std::chrono::duration<double>(Clock::now() - started).count();
        return result;
    }

    if (routes.hasRoutes(static_cast<size_t>(horizon + 1))) {
        const long double logRatio = result.logNextCount - result.logCount;
        result.logGrowth = static_cast<double>(logRatio);
        result.growth = static_cast<double>(std::exp(logRatio));
    } else {
        result.logGrowth = -std::numeric_limits<double>::infinity();
        result.growth = 0.0;
    }

    const long double numerator =
        static_cast<long double>(graph.vertexCount()) - horizon - 1;
    const long double denominator =
        static_cast<long double>(2 * horizon + 2) * (2 * horizon + 3);
    result.expectedGrowth =
        numerator > 0.0L ? static_cast<double>(numerator / denominator) : 0.0;

    const auto [bulkFirst, bulkLast] = bulkRange(horizon, bulkFraction);
    result.bulkFirst = bulkFirst;
    result.bulkLast = bulkLast;

    std::vector<ClosureWork> closureWork;
    closureWork.reserve(partitions.size());
    for (const ProfilePartition& partition : partitions) {
        ClosureWork work;
        work.result.bins = partition.bins;
        work.result.classCount = partition.classSizes.size();
        work.result.classSizes = partition.classSizes;
        work.result.minMass = 1.0;
        work.result.rmsDefect = std::numeric_limits<double>::quiet_NaN();
        work.result.maxDefect = std::numeric_limits<double>::quiet_NaN();
        for (uint32_t size : partition.classSizes) {
            if (size == 1) {
                ++work.result.singletonClasses;
            }
            work.result.largestClass =
                std::max(work.result.largestClass, static_cast<size_t>(size));
        }
        closureWork.push_back(std::move(work));
    }

    const auto offsets = graph.outgoingOffsets();
    const auto targets = graph.outgoingTargets();
    const size_t vertexCount = graph.vertexCount();
    std::vector<long double> occupancy(vertexCount, 0.0L);
    std::array<long double, kGapCoordinateCount> globalMean{};
    std::array<long double, kGapCovarianceCount> globalSecond{};
    std::array<long double, kGapThirdMomentCount> globalThird{};
    std::array<long double, kGapCovarianceCount> globalWithinCovariance{};
    std::array<long double, kGapThirdMomentCount> globalWithinThird{};
    std::vector<long double> globalTails(lindebergThresholds.size(), 0.0L);
    long double meanFlowError = 0.0L;
    const size_t occupancyBytes = occupancy.capacity() * sizeof(long double);
    size_t retainedTransitionBytes = 0;
    size_t temporaryPeakBytes = occupancyBytes;

    result.positions.reserve(static_cast<size_t>(horizon));
    for (int position = 0; position < horizon; ++position) {
        const int remaining = horizon - position;
        const auto& left = routes.backward[position];
        const auto& right = routes.forward[remaining];
        const auto& rightPrevious = routes.forward[remaining - 1];

        long double occupancyNormalizer = 0.0L;
        for (size_t vertex = 0; vertex < vertexCount; ++vertex) {
            occupancy[vertex] = left[vertex] * right[vertex];
            occupancyNormalizer += occupancy[vertex];
        }
        if (!(occupancyNormalizer > 0.0L)) {
            throw std::runtime_error("route occupancy normalization vanished");
        }
        for (long double& value : occupancy) {
            value /= occupancyNormalizer;
        }

        const long double flowLogError =
            std::log(occupancyNormalizer) + routes.backwardLogs[position] +
            routes.forwardLogs[remaining] - result.logCount;
        const double flowRelativeError =
            static_cast<double>(std::abs(std::expm1(flowLogError)));
        result.maxFlowError = std::max(result.maxFlowError, flowRelativeError);
        meanFlowError += flowRelativeError;

        const bool inBulk = position >= bulkFirst && position <= bulkLast;
        std::vector<ClosureAccumulator> accumulators;
        size_t accumulatorBytes = 0;
        if (inBulk) {
            accumulators.reserve(partitions.size());
            for (const ProfilePartition& partition : partitions) {
                accumulators.emplace_back(partition);
                accumulatorBytes += accumulators.back().estimatedBytes();
            }
            temporaryPeakBytes = std::max(
                temporaryPeakBytes,
                occupancyBytes + retainedTransitionBytes + accumulatorBytes);
        }

        std::array<long double, kGapCoordinateCount> positionMean{};
        std::array<long double, kGapCovarianceCount> positionSecond{};
        std::array<long double, kGapThirdMomentCount> positionThird{};
        std::vector<long double> positionTails(lindebergThresholds.size(),
                                               0.0L);
        long double positionFlow = 0.0L;
        long double maximalRowError = 0.0L;

        for (size_t source = 0; source < vertexCount; ++source) {
            const long double sourceMass = occupancy[source];
            if (!(sourceMass > 0.0L)) {
                continue;
            }

            const long double transitionDenominator =
                routes.forwardScales[remaining] * right[source];
            if (!(transitionDenominator > 0.0L)) {
                throw std::runtime_error(
                    "positive route occupancy has no outgoing continuation");
            }

            long double rowProbability = 0.0L;
            for (size_t edge = offsets[source]; edge < offsets[source + 1];
                 ++edge) {
                const size_t target = targets[edge];
                const long double probability =
                    rightPrevious[target] / transitionDenominator;
                if (!(probability > 0.0L)) {
                    continue;
                }
                rowProbability += probability;
                const long double flow = sourceMass * probability;
                positionFlow += flow;

                GapCoordinate difference{};
                long double jumpSquared = 0.0L;
                for (size_t coordinate = 0; coordinate < kGapCoordinateCount;
                     ++coordinate) {
                    difference[coordinate] =
                        state.coordinates[target][coordinate] -
                        state.coordinates[source][coordinate];
                    jumpSquared +=
                        static_cast<long double>(difference[coordinate]) *
                        difference[coordinate];
                    positionMean[coordinate] += flow * difference[coordinate];
                }

                size_t secondIndex = 0;
                for (size_t first = 0; first < kGapCoordinateCount; ++first) {
                    for (size_t second = first; second < kGapCoordinateCount;
                         ++second) {
                        positionSecond[secondIndex++] +=
                            flow * difference[first] * difference[second];
                    }
                }

                size_t thirdIndex = 0;
                for (size_t first = 0; first < kGapCoordinateCount; ++first) {
                    for (size_t second = first; second < kGapCoordinateCount;
                         ++second) {
                        for (size_t third = second; third < kGapCoordinateCount;
                             ++third) {
                            positionThird[thirdIndex++] +=
                                flow * difference[first] * difference[second] *
                                difference[third];
                        }
                    }
                }

                const double jump = std::sqrt(static_cast<double>(jumpSquared));
                result.maxJump = std::max(result.maxJump, jump);
                for (size_t tail = 0; tail < lindebergThresholds.size();
                     ++tail) {
                    if (jump > lindebergThresholds[tail]) {
                        positionTails[tail] += flow * jumpSquared;
                    }
                }

                for (ClosureAccumulator& accumulator : accumulators) {
                    const uint32_t targetClass =
                        accumulator.partition->classIds[target];
                    if (accumulator.targetScratch[targetClass] == 0.0L) {
                        accumulator.touchedTargets.push_back(targetClass);
                    }
                    accumulator.targetScratch[targetClass] += probability;
                }
            }

            maximalRowError =
                std::max(maximalRowError, std::abs(rowProbability - 1.0L));
            for (ClosureAccumulator& accumulator : accumulators) {
                const uint32_t sourceClass =
                    accumulator.partition->classIds[source];
                accumulator.sourceMass[sourceClass] += sourceMass;
                accumulator.squaredSourceMass[sourceClass] +=
                    sourceMass * sourceMass;

                long double conditionalNorm = 0.0L;
                const size_t rowOffset =
                    static_cast<size_t>(sourceClass) *
                    accumulator.partition->classSizes.size();
                for (uint32_t targetClass : accumulator.touchedTargets) {
                    const long double probability =
                        accumulator.targetScratch[targetClass];
                    conditionalNorm += probability * probability;
                    accumulator.classFlow[rowOffset + targetClass] +=
                        sourceMass * probability;
                    accumulator.targetScratch[targetClass] = 0.0L;
                }
                accumulator.touchedTargets.clear();
                accumulator.weightedConditionalNorm[sourceClass] +=
                    sourceMass * conditionalNorm;
            }
        }

        if (!(positionFlow > 0.0L)) {
            throw std::runtime_error("route-position flow vanished");
        }
        const long double inverseFlow = 1.0L / positionFlow;
        PositionResult positionResult;
        positionResult.position = position;
        positionResult.scaledPosition = static_cast<double>(position) / horizon;
        positionResult.flowError =
            std::max(flowRelativeError,
                     static_cast<double>(std::abs(positionFlow - 1.0L)));
        positionResult.rowError = static_cast<double>(maximalRowError);
        result.maxFlowError =
            std::max(result.maxFlowError, positionResult.flowError);
        result.maxRowError =
            std::max(result.maxRowError, positionResult.rowError);

        for (size_t coordinate = 0; coordinate < kGapCoordinateCount;
             ++coordinate) {
            positionMean[coordinate] *= inverseFlow;
            positionResult.mean[coordinate] =
                static_cast<double>(positionMean[coordinate]);
            globalMean[coordinate] += positionMean[coordinate] / horizon;
        }
        for (size_t index = 0; index < kGapCovarianceCount; ++index) {
            positionSecond[index] *= inverseFlow;
            globalSecond[index] += positionSecond[index] / horizon;
        }
        for (size_t index = 0; index < kGapThirdMomentCount; ++index) {
            positionThird[index] *= inverseFlow;
            globalThird[index] += positionThird[index] / horizon;
        }
        for (size_t tail = 0; tail < lindebergThresholds.size(); ++tail) {
            positionTails[tail] *= inverseFlow;
            globalTails[tail] += positionTails[tail] / horizon;
        }

        size_t covarianceIndexValue = 0;
        for (size_t first = 0; first < kGapCoordinateCount; ++first) {
            for (size_t second = first; second < kGapCoordinateCount;
                 ++second) {
                const long double covariance =
                    positionSecond[covarianceIndexValue] -
                    positionMean[first] * positionMean[second];
                positionResult.covariance[covarianceIndexValue] =
                    static_cast<double>(covariance);
                globalWithinCovariance[covarianceIndexValue] +=
                    covariance / horizon;
                if (first == second) {
                    positionResult.variance += static_cast<double>(covariance);
                }
                ++covarianceIndexValue;
            }
        }

        size_t centeredThirdIndex = 0;
        for (size_t first = 0; first < kGapCoordinateCount; ++first) {
            for (size_t second = first; second < kGapCoordinateCount;
                 ++second) {
                for (size_t third = second; third < kGapCoordinateCount;
                     ++third) {
                    const long double centered =
                        positionThird[centeredThirdIndex] -
                        positionMean[first] *
                            positionSecond[covarianceIndex(second, third)] -
                        positionMean[second] *
                            positionSecond[covarianceIndex(first, third)] -
                        positionMean[third] *
                            positionSecond[covarianceIndex(first, second)] +
                        2.0L * positionMean[first] * positionMean[second] *
                            positionMean[third];
                    globalWithinThird[centeredThirdIndex] += centered / horizon;
                    ++centeredThirdIndex;
                }
            }
        }
        result.positions.push_back(positionResult);

        if (inBulk) {
            for (size_t index = 0; index < accumulators.size(); ++index) {
                TransitionSnapshot snapshot;
                ClosurePosition diagnostic = finishClosurePosition(
                    position, accumulators[index], snapshot);
                ClosureWork& work = closureWork[index];
                work.result.positions.push_back(diagnostic);
                if (std::isfinite(diagnostic.rmsDefect)) {
                    work.result.rmsDefect =
                        std::isfinite(work.result.rmsDefect)
                            ? std::max(work.result.rmsDefect,
                                       diagnostic.rmsDefect)
                            : diagnostic.rmsDefect;
                }
                if (std::isfinite(diagnostic.maxDefect)) {
                    work.result.maxDefect =
                        std::isfinite(work.result.maxDefect)
                            ? std::max(work.result.maxDefect,
                                       diagnostic.maxDefect)
                            : diagnostic.maxDefect;
                }
                work.result.minMass =
                    std::min(work.result.minMass, diagnostic.assessableMass);
                retainedTransitionBytes +=
                    snapshot.kernel.capacity() * sizeof(double) +
                    snapshot.sourceMass.capacity() * sizeof(double);
                temporaryPeakBytes =
                    std::max(temporaryPeakBytes, occupancyBytes +
                                                     retainedTransitionBytes +
                                                     accumulatorBytes);
                work.transitions.push_back(std::move(snapshot));
            }
        }
    }

    result.meanFlowError = static_cast<double>(meanFlowError / horizon);
    for (size_t coordinate = 0; coordinate < kGapCoordinateCount;
         ++coordinate) {
        result.mean[coordinate] = static_cast<double>(globalMean[coordinate]);
    }

    size_t secondIndex = 0;
    for (size_t first = 0; first < kGapCoordinateCount; ++first) {
        for (size_t second = first; second < kGapCoordinateCount; ++second) {
            result.rawSecond[secondIndex] =
                static_cast<double>(globalSecond[secondIndex]);
            const long double covariance =
                globalSecond[secondIndex] -
                globalMean[first] * globalMean[second];
            result.covariance[secondIndex] = static_cast<double>(covariance);
            result.withinPositionCovariance[secondIndex] =
                static_cast<double>(globalWithinCovariance[secondIndex]);
            result.betweenPositionCovariance[secondIndex] = static_cast<double>(
                covariance - globalWithinCovariance[secondIndex]);
            result.covarianceDecompositionError = std::max(
                result.covarianceDecompositionError,
                std::abs(result.covariance[secondIndex] -
                         result.withinPositionCovariance[secondIndex] -
                         result.betweenPositionCovariance[secondIndex]));
            if (first == second) {
                result.timeScale += static_cast<double>(covariance);
                result.withinCovarianceTrace +=
                    result.withinPositionCovariance[secondIndex];
                result.betweenCovarianceTrace +=
                    result.betweenPositionCovariance[secondIndex];
            }
            ++secondIndex;
        }
    }
    result.timeScale = std::max(0.0, result.timeScale);

    size_t thirdIndex = 0;
    for (size_t first = 0; first < kGapCoordinateCount; ++first) {
        for (size_t second = first; second < kGapCoordinateCount; ++second) {
            for (size_t third = second; third < kGapCoordinateCount; ++third) {
                result.rawThird[thirdIndex] =
                    static_cast<double>(globalThird[thirdIndex]);
                const long double centered =
                    globalThird[thirdIndex] -
                    globalMean[first] *
                        globalSecond[covarianceIndex(second, third)] -
                    globalMean[second] *
                        globalSecond[covarianceIndex(first, third)] -
                    globalMean[third] *
                        globalSecond[covarianceIndex(first, second)] +
                    2.0L * globalMean[first] * globalMean[second] *
                        globalMean[third];
                result.centeredThird[thirdIndex] =
                    static_cast<double>(centered);
                result.withinPositionCenteredThird[thirdIndex] =
                    static_cast<double>(globalWithinThird[thirdIndex]);
                ++thirdIndex;
            }
        }
    }
    result.withinPositionThirdNorm =
        thirdMomentFrobenius(result.withinPositionCenteredThird);

    if (result.timeScale > 0.0) {
        result.scaledJump = result.maxJump / std::sqrt(result.timeScale);
        result.scaledRawThird =
            thirdMomentFrobenius(result.rawThird) / result.timeScale;
        result.scaledCenteredThird =
            thirdMomentFrobenius(result.centeredThird) / result.timeScale;
    } else {
        result.scaledJump = std::numeric_limits<double>::quiet_NaN();
        result.scaledRawThird = std::numeric_limits<double>::quiet_NaN();
        result.scaledCenteredThird = std::numeric_limits<double>::quiet_NaN();
    }

    result.tails.reserve(lindebergThresholds.size());
    for (size_t index = 0; index < lindebergThresholds.size(); ++index) {
        result.tails.push_back({
            .threshold = lindebergThresholds[index],
            .tail = static_cast<double>(globalTails[index]),
            .scaled =
                result.timeScale > 0.0
                    ? static_cast<double>(globalTails[index]) / result.timeScale
                    : std::numeric_limits<double>::quiet_NaN(),
        });
    }

    GapCoordinate bulkMean{};
    GapCovariance bulkCovariance{};
    size_t bulkCount = 0;
    for (const PositionResult& position : result.positions) {
        if (position.position < bulkFirst || position.position > bulkLast) {
            continue;
        }
        ++bulkCount;
        for (size_t coordinate = 0; coordinate < kGapCoordinateCount;
             ++coordinate) {
            bulkMean[coordinate] += position.mean[coordinate];
        }
        for (size_t index = 0; index < kGapCovarianceCount; ++index) {
            bulkCovariance[index] += position.covariance[index];
        }
    }
    for (double& value : bulkMean) {
        value /= static_cast<double>(bulkCount);
    }
    for (double& value : bulkCovariance) {
        value /= static_cast<double>(bulkCount);
    }

    for (const PositionResult& position : result.positions) {
        if (position.position < bulkFirst || position.position > bulkLast) {
            continue;
        }
        GapCoordinate meanDifference{};
        GapCovariance covarianceDifference{};
        for (size_t coordinate = 0; coordinate < kGapCoordinateCount;
             ++coordinate) {
            meanDifference[coordinate] =
                position.mean[coordinate] - bulkMean[coordinate];
        }
        for (size_t index = 0; index < kGapCovarianceCount; ++index) {
            covarianceDifference[index] =
                position.covariance[index] - bulkCovariance[index];
        }
        GapCoordinate scaledMeanDifference{};
        GapCovariance scaledCovarianceDifference{};
        for (size_t coordinate = 0; coordinate < kGapCoordinateCount;
             ++coordinate) {
            scaledMeanDifference[coordinate] =
                horizon * meanDifference[coordinate];
        }
        for (size_t index = 0; index < kGapCovarianceCount; ++index) {
            scaledCovarianceDifference[index] = static_cast<double>(horizon) *
                                                horizon *
                                                covarianceDifference[index];
        }
        result.driftPlateau =
            std::max(result.driftPlateau, coordinateNorm(scaledMeanDifference));
        result.covariancePlateau =
            std::max(result.covariancePlateau,
                     covarianceFrobenius(scaledCovarianceDifference));
    }
    result.plateauDefect =
        std::max(result.driftPlateau, result.covariancePlateau);

    for (ClosureWork& work : closureWork) {
        const size_t meanKernelBytes = work.result.classCount *
                                       work.result.classCount *
                                       sizeof(long double);
        temporaryPeakBytes = std::max(temporaryPeakBytes,
                                      occupancyBytes + retainedTransitionBytes +
                                          meanKernelBytes);
        finishTransitionPlateau(work);
        result.closure.push_back(std::move(work.result));
    }

    result.peakBytes = routes.estimatedBytes() + graph.estimatedBytes() +
                       state.estimatedBytes() + temporaryPeakBytes;
    result.seconds =
        std::chrono::duration<double>(Clock::now() - started).count();
    return result;
}

size_t runRouteSelfTests() {
    const std::array<std::vector<std::pair<uint32_t, uint32_t>>, 3> edgeSets{
        std::vector<std::pair<uint32_t, uint32_t>>{
            {0, 1}, {0, 2}, {1, 3}, {1, 4}, {2, 3}, {3, 4}},
        std::vector<std::pair<uint32_t, uint32_t>>{
            {0, 1}, {0, 2}, {0, 3}, {1, 2}, {1, 3}, {2, 3}},
        std::vector<std::pair<uint32_t, uint32_t>>{
            {0, 2}, {0, 4}, {1, 3}, {1, 4}, {2, 5}, {3, 5}, {4, 5}},
    };
    const std::array<size_t, 3> vertexCounts{5, 4, 6};
    size_t checks = 0;

    for (size_t graphIndex = 0; graphIndex < edgeSets.size(); ++graphIndex) {
        const ReferenceDag graph = ReferenceDag::fromTopologicalEdges(
            vertexCounts[graphIndex], edgeSets[graphIndex]);
        const GapNodeState state = computeGapNodeState(graph);
        if (graphIndex == 0) {
            const std::array<GapSignature, 5> expectedSignatures{{
                {2, 0, 3, 0, 2, 0},
                {2, 1, 1, 0, 4, 2},
                {1, 1, 1, 0, 2, 2},
                {1, 2, 0, 2, 2, 3},
                {0, 2, 0, 3, 0, 3},
            }};
            if (!std::ranges::equal(state.signatures, expectedSignatures)) {
                throw std::runtime_error(
                    "route self-test failed: six-coordinate signatures");
            }
            checks += expectedSignatures.size();
        }
        constexpr size_t maximumHorizon = 4;
        const StableRouteCounts stable =
            computeRouteCounts(graph, maximumHorizon + 1);
        const auto exactForward =
            computeExactForward(graph, maximumHorizon + 1);
        const auto exactBackward =
            computeExactBackward(graph, maximumHorizon + 1);

        for (size_t horizon = 0; horizon <= maximumHorizon; ++horizon) {
            const cpp_int exactTotal =
                std::accumulate(exactForward[horizon].begin(),
                                exactForward[horizon].end(), cpp_int{0});
            if ((exactTotal != 0) != stable.hasRoutes(horizon)) {
                throw std::runtime_error(
                    "route self-test failed: zero-count status");
            }
            ++checks;
            if (exactTotal != 0) {
                const long double stableTotal =
                    std::exp(stable.forwardLogs[horizon]);
                requireClose(static_cast<double>(stableTotal),
                             exactTotal.convert_to<double>(), 1.0e-10,
                             "stable total");
                ++checks;
            }

            const cpp_int backwardTotal =
                std::accumulate(exactBackward[horizon].begin(),
                                exactBackward[horizon].end(), cpp_int{0});
            if (backwardTotal != exactTotal) {
                throw std::runtime_error(
                    "route self-test failed: forward/backward total");
            }
            ++checks;

            if (exactTotal != 0) {
                const long double total = exactTotal.convert_to<long double>();
                for (size_t vertex = 0; vertex < graph.vertexCount();
                     ++vertex) {
                    requireClose(
                        static_cast<double>(stable.forward[horizon][vertex]),
                        static_cast<double>(exactForward[horizon][vertex]
                                                .convert_to<long double>() /
                                            total),
                        1.0e-12, "normalized forward count");
                    requireClose(
                        static_cast<double>(stable.backward[horizon][vertex]),
                        static_cast<double>(exactBackward[horizon][vertex]
                                                .convert_to<long double>() /
                                            total),
                        1.0e-12, "normalized backward count");
                    checks += 2;
                }
            }
        }

        for (int horizon = 1; horizon <= static_cast<int>(maximumHorizon);
             ++horizon) {
            const EnumeratedRoutes enumerated =
                enumerateRoutes(graph, state, horizon);
            if (enumerated.routeCount == 0) {
                continue;
            }

            cpp_int occurrenceTotal = 0;
            for (const cpp_int& count : enumerated.edgePositionCounts) {
                occurrenceTotal += count;
            }
            if (occurrenceTotal != enumerated.routeCount * horizon) {
                throw std::runtime_error(
                    "route self-test failed: enumerated flow identity");
            }
            ++checks;

            const auto offsets = graph.outgoingOffsets();
            const auto targets = graph.outgoingTargets();
            for (int position = 0; position < horizon; ++position) {
                for (size_t source = 0; source < graph.vertexCount();
                     ++source) {
                    for (size_t edge = offsets[source];
                         edge < offsets[source + 1]; ++edge) {
                        const cpp_int formula =
                            exactBackward[position][source] *
                            exactForward[horizon - position - 1][targets[edge]];
                        const cpp_int enumeratedCount =
                            enumerated
                                .edgePositionCounts[static_cast<size_t>(
                                                        position) *
                                                        graph.edgeCount() +
                                                    edge];
                        if (formula != enumeratedCount) {
                            throw std::runtime_error(
                                "route self-test failed: edge-position flow");
                        }
                        ++checks;
                    }
                }
            }

            const std::array<int, 1> bins{4};
            const auto partitions = buildPartitions(state, bins);
            const std::array<double, 2> thresholds{0.05, 0.2};
            const HorizonResult optimized = analyzeHorizon(
                graph, state, stable, horizon, partitions, 0.2, thresholds);
            for (size_t coordinate = 0; coordinate < kGapCoordinateCount;
                 ++coordinate) {
                requireClose(optimized.mean[coordinate],
                             enumerated.mean[coordinate], 1.0e-11,
                             "enumerated mean");
                ++checks;
            }
            for (size_t index = 0; index < kGapCovarianceCount; ++index) {
                requireClose(optimized.rawSecond[index],
                             enumerated.rawSecond[index], 1.0e-11,
                             "enumerated second moment");
                ++checks;
            }
            for (size_t index = 0; index < kGapThirdMomentCount; ++index) {
                requireClose(optimized.rawThird[index],
                             enumerated.rawThird[index], 1.0e-11,
                             "enumerated third moment");
                ++checks;
            }
            if (optimized.maxFlowError > 1.0e-12 ||
                optimized.maxRowError > 1.0e-12) {
                throw std::runtime_error(
                    "route self-test failed: normalized-flow audit");
            }
            checks += 2;
        }
    }
    const std::array<std::pair<uint32_t, uint32_t>, 1> singleEdge{{
        {0, 1},
    }};
    const ReferenceDag shortGraph =
        ReferenceDag::fromTopologicalEdges(2, singleEdge);
    const GapNodeState shortState = computeGapNodeState(shortGraph);
    constexpr size_t longCalibration = 2'000;
    const StableRouteCounts longRoutes =
        computeRouteCounts(shortGraph, longCalibration);
    const std::array<double, 1> modes{0.25};
    const auto calibration = computeCalibration(
        shortGraph, longRoutes, modes, static_cast<int>(longCalibration));
    for (const RouteCalibration& value : calibration) {
        if (!std::isfinite(value.modePrediction) ||
            !std::isfinite(value.modeResidual)) {
            throw std::runtime_error(
                "route self-test failed: stable Legendre coefficient");
        }
        checks += 2;
    }

    const HorizonResult routeFree = analyzeHorizon(
        shortGraph, shortState, longRoutes, 2,
        std::span<const ProfilePartition>{}, 0.2, std::span<const double>{});
    if (routeFree.valid || routeFree.peakBytes == 0) {
        throw std::runtime_error(
            "route self-test failed: route-free workspace accounting");
    }
    checks += 2;

    return checks;
}
