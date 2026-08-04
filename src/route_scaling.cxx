#include "route_scaling.hxx"

#include <algorithm>
#include <boost/math/special_functions/beta.hpp>
#include <chrono>
#include <cmath>
#include <cstddef>
#include <limits>
#include <numeric>
#include <stdexcept>
#include <string_view>
#include <utility>

namespace {

using Clock = std::chrono::steady_clock;

constexpr uint64_t kHoldoutDomain = 0x6a09e667f3bcc909ULL;

uint64_t splitMix64(uint64_t value) {
    value += 0x9e3779b97f4a7c15ULL;
    value = (value ^ (value >> 30)) * 0xbf58476d1ce4e5b9ULL;
    value = (value ^ (value >> 27)) * 0x94d049bb133111ebULL;
    return value ^ (value >> 31);
}

double intrinsicMark(const GapCoordinate& coordinate) {
    return 0.5 + coordinate[1] - coordinate[0];
}

PredictiveMoment predictiveTarget(const GapCoordinate& coordinate,
                                  double rootVertexCount) {
    PredictiveMoment out{};
    const double mark = intrinsicMark(coordinate);
    const GapCoordinate reference = gapContinuumCoordinate(mark);

    out[0] = mark;
    for (size_t i = 0; i < kGapCoordinateCount; ++i) {
        out[i + 1] = rootVertexCount * (coordinate[i] - reference[i]);
    }

    return out;
}

// Reference Beta laws

double betaCdf(double value, double alpha, double beta) {
    if (value <= 0.0) {
        return 0.0;
    }
    if (value >= 1.0) {
        return 1.0;
    }
    return boost::math::ibeta(alpha, beta, value);
}

double weightedKolmogorov(std::vector<std::pair<double, long double>>& values,
                          double alpha, double beta) {
    std::ranges::sort(values, {}, &std::pair<double, long double>::first);

    const long double total = std::accumulate(
        values.begin(), values.end(), 0.0L,
        [](long double sum, const auto& item) { return sum + item.second; });
    if (!(total > 0.0L)) {
        return std::numeric_limits<double>::quiet_NaN();
    }

    long double cumulative = 0.0L;
    double maxError = 0.0;
    size_t first = 0;

    while (first < values.size()) {
        size_t last = first + 1;
        long double weight = values[first].second;

        while (last < values.size() &&
               values[last].first == values[first].first) {
            weight += values[last].second;
            ++last;
        }

        const double target = betaCdf(values[first].first, alpha, beta);
        const double leftError =
            std::abs(static_cast<double>(cumulative / total) - target);
        maxError = std::max(maxError, leftError);

        cumulative += weight;
        const double rightError =
            std::abs(static_cast<double>(cumulative / total) - target);
        maxError = std::max(maxError, rightError);

        first = last;
    }

    return maxError;
}

size_t histogramBin(double value, size_t bins) {
    if (value <= 0.0) {
        return 0;
    }
    if (value >= 1.0) {
        return bins - 1;
    }

    return std::min(bins - 1,
                    static_cast<size_t>(value * static_cast<double>(bins)));
}

double histogramKolmogorovBound(std::span<const long double> histogram,
                                double alpha, double beta) {
    const long double total =
        std::accumulate(histogram.begin(), histogram.end(), 0.0L);
    if (!(total > 0.0L)) {
        return std::numeric_limits<double>::quiet_NaN();
    }

    long double cumulative = 0.0L;
    double endpointMaximum = 0.0;
    double maximalEmpiricalBin = 0.0;
    double maximalTargetBin = 0.0;
    double previousTarget = 0.0;

    for (size_t i = 0; i < histogram.size(); ++i) {
        cumulative += histogram[i];

        const double boundary =
            static_cast<double>(i + 1) / static_cast<double>(histogram.size());
        const double target = betaCdf(boundary, alpha, beta);

        endpointMaximum = std::max(
            endpointMaximum,
            std::abs(static_cast<double>(cumulative / total) - target));
        maximalEmpiricalBin = std::max(
            maximalEmpiricalBin, static_cast<double>(histogram[i] / total));
        maximalTargetBin = std::max(maximalTargetBin, target - previousTarget);
        previousTarget = target;
    }

    // Both CDFs are monotone within a bin. The larger bin mass therefore
    // bounds the unresolved difference between adjacent checked endpoints.
    return std::min(1.0, endpointMaximum +
                             std::max(maximalEmpiricalBin, maximalTargetBin));
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

// Balanced nested predictive partitions

std::vector<double> makeFeatures(const GapNodeState& state,
                                 std::string_view name, size_t& dimension) {
    const size_t vertexCount = state.coordinates.size();
    const double rootVertexCount = std::sqrt(static_cast<double>(vertexCount));

    if (name == "intrinsic_mark") {
        dimension = 1;
    } else if (name == "intrinsic_mark_transverse") {
        dimension = kPredictiveMomentCount;
    } else if (name == "full_six_coordinate") {
        dimension = kGapCoordinateCount;
    } else {
        throw std::logic_error("unknown predictive state");
    }

    std::vector<double> features(vertexCount * dimension, 0.0);
    for (size_t vertex = 0; vertex < vertexCount; ++vertex) {
        if (name == "intrinsic_mark") {
            features[vertex] = intrinsicMark(state.coordinates[vertex]);
            continue;
        }

        if (name == "intrinsic_mark_transverse") {
            const PredictiveMoment target =
                predictiveTarget(state.coordinates[vertex], rootVertexCount);
            std::ranges::copy(target, features.data() + vertex * dimension);
            continue;
        }

        std::ranges::copy(state.coordinates[vertex],
                          features.data() + vertex * dimension);
    }

    // Standardization prevents the arbitrary units of the six coordinates
    // from deciding every median split.
    for (size_t coordinate = 0; coordinate < dimension; ++coordinate) {
        long double mean = 0.0L;
        for (size_t vertex = 0; vertex < vertexCount; ++vertex) {
            mean += features[vertex * dimension + coordinate];
        }
        mean /= vertexCount;

        long double variance = 0.0L;
        for (size_t vertex = 0; vertex < vertexCount; ++vertex) {
            const long double difference =
                features[vertex * dimension + coordinate] - mean;
            variance += difference * difference;
        }
        const double scale =
            std::sqrt(static_cast<double>(variance / vertexCount));

        for (size_t vertex = 0; vertex < vertexCount; ++vertex) {
            double& value = features[vertex * dimension + coordinate];
            value =
                scale > 0.0 ? static_cast<double>((value - mean) / scale) : 0.0;
        }
    }

    return features;
}

std::vector<PredictivePartition>
buildCandidatePartitions(const ReferenceDag& graph, const GapNodeState& state,
                         std::span<const int> requested,
                         std::string_view stateName) {
    size_t dimension = 0;
    const std::vector<double> features =
        makeFeatures(state, stateName, dimension);
    const size_t vertexCount = state.coordinates.size();
    const size_t maxClasses = static_cast<size_t>(requested.back());

    std::vector<std::vector<uint32_t>> leaves(1);
    leaves.front().resize(vertexCount);
    std::iota(leaves.front().begin(), leaves.front().end(), uint32_t{0});

    std::vector<PredictivePartition> out;
    size_t requestedPos = 0;

    while (leaves.size() <= maxClasses) {
        if (leaves.size() == static_cast<size_t>(requested[requestedPos])) {
            PredictivePartition partition;
            partition.state = stateName;
            partition.featureCount = dimension;
            partition.requestedClasses = leaves.size();
            partition.classIds.resize(vertexCount);
            partition.training.resize(vertexCount);
            partition.classSizes.reserve(leaves.size());

            for (size_t classIndex = 0; classIndex < leaves.size();
                 ++classIndex) {
                partition.classSizes.push_back(
                    static_cast<uint32_t>(leaves[classIndex].size()));

                for (uint32_t vertex : leaves[classIndex]) {
                    partition.classIds[vertex] =
                        static_cast<uint32_t>(classIndex);
                }
            }

            // The split depends only on a permanent vertex identifier, not on
            // the route outcomes used below for prediction.
            const auto originalIds = graph.originalVertexIds();
            for (size_t vertex = 0; vertex < vertexCount; ++vertex) {
                const uint64_t id =
                    originalIds.empty() ? vertex : originalIds[vertex];
                partition.training[vertex] = static_cast<uint8_t>(
                    (splitMix64(id ^ kHoldoutDomain) & 1U) == 0U);
            }

            out.push_back(std::move(partition));
            ++requestedPos;
            if (requestedPos == requested.size()) {
                break;
            }
        }

        size_t selected = leaves.size();
        for (size_t i = 0; i < leaves.size(); ++i) {
            if (leaves[i].size() > 1 &&
                (selected == leaves.size() ||
                 leaves[i].size() > leaves[selected].size())) {
                selected = i;
            }
        }
        if (selected == leaves.size()) {
            break;
        }

        size_t splitCoordinate = 0;
        long double maxVariance = -1.0L;
        for (size_t coordinate = 0; coordinate < dimension; ++coordinate) {
            long double mean = 0.0L;
            for (uint32_t vertex : leaves[selected]) {
                mean += features[vertex * dimension + coordinate];
            }
            mean /= leaves[selected].size();

            long double variance = 0.0L;
            for (uint32_t vertex : leaves[selected]) {
                const long double difference =
                    features[vertex * dimension + coordinate] - mean;
                variance += difference * difference;
            }

            if (variance > maxVariance) {
                maxVariance = variance;
                splitCoordinate = coordinate;
            }
        }

        std::ranges::sort(leaves[selected],
                          [&features, dimension,
                           splitCoordinate](uint32_t left, uint32_t right) {
                              const double leftValue =
                                  features[left * dimension + splitCoordinate];
                              const double rightValue =
                                  features[right * dimension + splitCoordinate];
                              return leftValue < rightValue ||
                                     (leftValue == rightValue && left < right);
                          });

        const size_t midpoint = leaves[selected].size() / 2;
        std::vector<uint32_t> rightLeaf(leaves[selected].data() + midpoint,
                                        leaves[selected].data() +
                                            leaves[selected].size());
        leaves[selected].resize(midpoint);
        leaves.insert(leaves.begin() + static_cast<ptrdiff_t>(selected + 1),
                      std::move(rightLeaf));
    }

    if (out.size() != requested.size()) {
        throw std::runtime_error(
            "could not realize requested predictive class counts");
    }

    return out;
}

// Conditional-law aggregation and held-out scoring

struct SourceLaw {
    PredictiveMoment mean{};
};

struct ClassPrediction {
    size_t classCount = 0;
    std::vector<long double> allMass;
    std::vector<long double> trainingMass;
    std::vector<long double> allMean;
    std::vector<long double> trainingMean;
    std::vector<long double> allHistogram;
    std::vector<long double> trainingHistogram;
    PredictiveMoment globalAll{};
    PredictiveMoment globalTraining{};
    long double totalMass = 0.0L;
    long double totalTrainingMass = 0.0L;
};

ClassPrediction aggregateClasses(const PredictivePartition& partition,
                                 std::span<const long double> occupancy,
                                 std::span<const SourceLaw> laws,
                                 std::span<const long double> histograms,
                                 size_t maxBins) {
    ClassPrediction out;
    out.classCount = partition.classSizes.size();
    out.allMass.assign(out.classCount, 0.0L);
    out.trainingMass.assign(out.classCount, 0.0L);
    out.allMean.assign(out.classCount * kPredictiveMomentCount, 0.0L);
    out.trainingMean.assign(out.classCount * kPredictiveMomentCount, 0.0L);
    out.allHistogram.assign(out.classCount * maxBins, 0.0L);
    out.trainingHistogram.assign(out.classCount * maxBins, 0.0L);

    for (size_t source = 0; source < occupancy.size(); ++source) {
        const long double mass = occupancy[source];
        if (!(mass > 0.0L)) {
            continue;
        }

        const size_t sourceClass = partition.classIds[source];
        out.allMass[sourceClass] += mass;
        out.totalMass += mass;

        for (size_t coordinate = 0; coordinate < kPredictiveMomentCount;
             ++coordinate) {
            const long double value = laws[source].mean[coordinate];
            out.allMean[sourceClass * kPredictiveMomentCount + coordinate] +=
                mass * value;
            out.globalAll[coordinate] += static_cast<double>(mass * value);
        }
        for (size_t bin = 0; bin < maxBins; ++bin) {
            out.allHistogram[sourceClass * maxBins + bin] +=
                mass * histograms[source * maxBins + bin];
        }

        if (partition.training[source] == 0) {
            continue;
        }

        out.trainingMass[sourceClass] += mass;
        out.totalTrainingMass += mass;
        for (size_t coordinate = 0; coordinate < kPredictiveMomentCount;
             ++coordinate) {
            const long double value = laws[source].mean[coordinate];
            out.trainingMean[sourceClass * kPredictiveMomentCount +
                             coordinate] += mass * value;
            out.globalTraining[coordinate] += static_cast<double>(mass * value);
        }
        for (size_t bin = 0; bin < maxBins; ++bin) {
            out.trainingHistogram[sourceClass * maxBins + bin] +=
                mass * histograms[source * maxBins + bin];
        }
    }

    for (size_t coordinate = 0; coordinate < kPredictiveMomentCount;
         ++coordinate) {
        out.globalAll[coordinate] /= static_cast<double>(out.totalMass);
        out.globalTraining[coordinate] =
            out.totalTrainingMass > 0.0L
                ? out.globalTraining[coordinate] /
                      static_cast<double>(out.totalTrainingMass)
                : std::numeric_limits<double>::quiet_NaN();
    }

    return out;
}

PredictivePosition scorePrediction(int position, int horizon,
                                   const PredictivePartition& partition,
                                   std::span<const long double> occupancy,
                                   std::span<const SourceLaw> laws,
                                   std::span<const long double> histograms,
                                   size_t maxBins,
                                   std::span<const int> targetBins) {
    const ClassPrediction classes =
        aggregateClasses(partition, occupancy, laws, histograms, maxBins);

    PredictivePosition out;
    out.position = position;
    out.scaledPosition = static_cast<double>(position) / horizon;
    out.trainingRouteMass = static_cast<double>(classes.totalTrainingMass);
    out.heldOutRouteMass =
        static_cast<double>(classes.totalMass - classes.totalTrainingMass);

    for (size_t sourceClass = 0; sourceClass < classes.classCount;
         ++sourceClass) {
        out.occupiedClasses += classes.allMass[sourceClass] > 0.0L ? 1 : 0;
        out.trainingOccupiedClasses +=
            classes.trainingMass[sourceClass] > 0.0L ? 1 : 0;
    }

    std::array<long double, kPredictiveMomentCount> exactSquared{};
    std::array<long double, kPredictiveMomentCount> heldOutSquared{};
    long double exactBaseline = 0.0L;
    long double heldOutBaseline = 0.0L;
    long double heldOutCoveredMass = 0.0L;

    std::vector<long double> exactTv(targetBins.size(), 0.0L);
    std::vector<long double> exactWasserstein(targetBins.size(), 0.0L);
    std::vector<long double> heldOutTv(targetBins.size(), 0.0L);
    std::vector<long double> heldOutWasserstein(targetBins.size(), 0.0L);

    for (size_t source = 0; source < occupancy.size(); ++source) {
        const long double mass = occupancy[source];
        if (!(mass > 0.0L)) {
            continue;
        }

        const size_t sourceClass = partition.classIds[source];
        if (partition.classSizes[sourceClass] == 1) {
            out.singletonRouteMass += static_cast<double>(mass);
        }

        // Exact finite-partition conditional-moment error.
        for (size_t coordinate = 0; coordinate < kPredictiveMomentCount;
             ++coordinate) {
            const long double observed = laws[source].mean[coordinate];
            const long double prediction =
                classes.allMean[sourceClass * kPredictiveMomentCount +
                                coordinate] /
                classes.allMass[sourceClass];
            const long double difference = observed - prediction;
            exactSquared[coordinate] += mass * difference * difference;

            const long double baselineDifference =
                observed - classes.globalAll[coordinate];
            exactBaseline += mass * baselineDifference * baselineDifference;
        }

        // The target partitions are nested. TV is reported at every
        // resolution; W1 retains the units of the intrinsic mark.
        for (size_t resolution = 0; resolution < targetBins.size();
             ++resolution) {
            const size_t bins = static_cast<size_t>(targetBins[resolution]);
            const size_t block = maxBins / bins;
            long double cdfDifference = 0.0L;

            for (size_t bin = 0; bin < bins; ++bin) {
                long double observed = 0.0L;
                long double prediction = 0.0L;

                for (size_t fine = bin * block; fine < (bin + 1) * block;
                     ++fine) {
                    observed += histograms[source * maxBins + fine];
                    prediction +=
                        classes.allHistogram[sourceClass * maxBins + fine] /
                        classes.allMass[sourceClass];
                }

                exactTv[resolution] +=
                    mass * std::abs(observed - prediction) / 2.0L;
                cdfDifference += observed - prediction;
                if (bin + 1 < bins) {
                    exactWasserstein[resolution] +=
                        mass * std::abs(cdfDifference) / bins;
                }
            }
        }

        // Fit on hash-selected source vertices and score only held-out ones.
        if (partition.training[source] != 0 ||
            !(classes.trainingMass[sourceClass] > 0.0L)) {
            continue;
        }

        heldOutCoveredMass += mass;
        for (size_t coordinate = 0; coordinate < kPredictiveMomentCount;
             ++coordinate) {
            const long double observed = laws[source].mean[coordinate];
            const long double prediction =
                classes.trainingMean[sourceClass * kPredictiveMomentCount +
                                     coordinate] /
                classes.trainingMass[sourceClass];
            const long double difference = observed - prediction;
            heldOutSquared[coordinate] += mass * difference * difference;

            const long double baselineDifference =
                observed - classes.globalTraining[coordinate];
            heldOutBaseline += mass * baselineDifference * baselineDifference;
        }

        for (size_t resolution = 0; resolution < targetBins.size();
             ++resolution) {
            const size_t bins = static_cast<size_t>(targetBins[resolution]);
            const size_t block = maxBins / bins;
            long double cdfDifference = 0.0L;

            for (size_t bin = 0; bin < bins; ++bin) {
                long double observed = 0.0L;
                long double prediction = 0.0L;

                for (size_t fine = bin * block; fine < (bin + 1) * block;
                     ++fine) {
                    observed += histograms[source * maxBins + fine];
                    prediction +=
                        classes
                            .trainingHistogram[sourceClass * maxBins + fine] /
                        classes.trainingMass[sourceClass];
                }

                heldOutTv[resolution] +=
                    mass * std::abs(observed - prediction) / 2.0L;
                cdfDifference += observed - prediction;
                if (bin + 1 < bins) {
                    heldOutWasserstein[resolution] +=
                        mass * std::abs(cdfDifference) / bins;
                }
            }
        }
    }

    out.heldOutCoveredMass = static_cast<double>(heldOutCoveredMass);
    for (size_t coordinate = 0; coordinate < kPredictiveMomentCount;
         ++coordinate) {
        out.exactMomentRmse[coordinate] = std::sqrt(
            static_cast<double>(exactSquared[coordinate] / classes.totalMass));
        out.heldOutMomentRmse[coordinate] =
            heldOutCoveredMass > 0.0L
                ? std::sqrt(static_cast<double>(heldOutSquared[coordinate] /
                                                heldOutCoveredMass))
                : std::numeric_limits<double>::quiet_NaN();
    }

    const long double exactSquaredTotal =
        std::accumulate(exactSquared.begin(), exactSquared.end(), 0.0L);
    const long double heldOutSquaredTotal =
        std::accumulate(heldOutSquared.begin(), heldOutSquared.end(), 0.0L);

    out.exactMomentR2 =
        exactBaseline > 0.0L
            ? 1.0 - static_cast<double>(exactSquaredTotal / exactBaseline)
            : std::numeric_limits<double>::quiet_NaN();
    out.heldOutMomentR2 =
        heldOutBaseline > 0.0L
            ? 1.0 - static_cast<double>(heldOutSquaredTotal / heldOutBaseline)
            : std::numeric_limits<double>::quiet_NaN();

    out.distributions.reserve(targetBins.size());
    for (size_t i = 0; i < targetBins.size(); ++i) {
        out.distributions.push_back({
            .targetBins = targetBins[i],
            .exactTotalVariation =
                static_cast<double>(exactTv[i] / classes.totalMass),
            .exactWasserstein1 =
                static_cast<double>(exactWasserstein[i] / classes.totalMass),
            .heldOutTotalVariation =
                heldOutCoveredMass > 0.0L
                    ? static_cast<double>(heldOutTv[i] / heldOutCoveredMass)
                    : std::numeric_limits<double>::quiet_NaN(),
            .heldOutWasserstein1 =
                heldOutCoveredMass > 0.0L
                    ? static_cast<double>(heldOutWasserstein[i] /
                                          heldOutCoveredMass)
                    : std::numeric_limits<double>::quiet_NaN(),
        });
    }

    return out;
}

} // namespace

IntrinsicStateScaling summarizeIntrinsicState(const GapNodeState& state) {
    if (state.coordinates.empty()) {
        throw std::invalid_argument("node state must not be empty");
    }

    IntrinsicStateScaling out;
    out.intrinsicMarkMinimum = std::numeric_limits<double>::infinity();
    out.intrinsicMarkMaximum = -std::numeric_limits<double>::infinity();

    std::array<long double, kGapCoordinateCount> squared{};
    long double totalSquared = 0.0L;

    for (const GapCoordinate& coordinate : state.coordinates) {
        const double mark = intrinsicMark(coordinate);
        out.intrinsicMarkMinimum = std::min(out.intrinsicMarkMinimum, mark);
        out.intrinsicMarkMaximum = std::max(out.intrinsicMarkMaximum, mark);

        const GapCoordinate reference = gapContinuumCoordinate(mark);
        for (size_t i = 0; i < kGapCoordinateCount; ++i) {
            const long double residual = coordinate[i] - reference[i];
            squared[i] += residual * residual;
            totalSquared += residual * residual;
        }
    }

    const long double count = state.coordinates.size();
    const double rootVertexCount = std::sqrt(static_cast<double>(count));
    out.transverseResidualRms = std::sqrt(
        static_cast<double>(totalSquared / (count * kGapCoordinateCount)));
    out.scaledTransverseResidualRms =
        rootVertexCount * out.transverseResidualRms;

    for (size_t i = 0; i < kGapCoordinateCount; ++i) {
        out.coordinateResidualRms[i] =
            std::sqrt(static_cast<double>(squared[i] / count));
        out.scaledCoordinateResidualRms[i] =
            rootVertexCount * out.coordinateResidualRms[i];
    }

    return out;
}

std::vector<PredictivePartition>
buildPredictivePartitions(const ReferenceDag& graph, const GapNodeState& state,
                          std::span<const int> requestedClasses) {
    if (state.coordinates.size() != graph.vertexCount()) {
        throw std::invalid_argument(
            "predictive state size does not match graph");
    }
    if (requestedClasses.empty()) {
        throw std::invalid_argument(
            "predictive class counts must not be empty");
    }

    int previous = 0;
    for (int count : requestedClasses) {
        if (count < 2 || count <= previous ||
            static_cast<size_t>(count) > graph.vertexCount()) {
            throw std::invalid_argument(
                "predictive class counts must be increasing in 2..N");
        }
        previous = count;
    }

    constexpr std::array<std::string_view, 3> names{
        "intrinsic_mark", "intrinsic_mark_transverse", "full_six_coordinate"};

    std::vector<PredictivePartition> out;
    out.reserve(names.size() * requestedClasses.size());

    for (std::string_view name : names) {
        std::vector<PredictivePartition> candidate =
            buildCandidatePartitions(graph, state, requestedClasses, name);
        out.insert(out.end(), std::make_move_iterator(candidate.begin()),
                   std::make_move_iterator(candidate.end()));
    }

    return out;
}

RouteScalingResult analyzeRouteScaling(
    const ReferenceDag& graph, const GapNodeState& state,
    const StableRouteCounts& routes, const HorizonResult& bridge,
    std::span<const PredictivePartition> partitions,
    std::span<const int> targetBins, std::span<const double> thresholds,
    double bulkFraction, int referenceBins) {
    const auto started = Clock::now();

    RouteScalingResult out;
    out.horizon = bridge.p;
    out.hasRoutes = bridge.hasRoutes;
    if (!out.hasRoutes) {
        return out;
    }

    if (bridge.positions.size() != static_cast<size_t>(bridge.p)) {
        throw std::invalid_argument("bridge position count is inconsistent");
    }
    if (targetBins.empty() || referenceBins < 16) {
        throw std::invalid_argument(
            "target bins must be nonempty and reference bins at least 16");
    }

    const size_t maxBins = static_cast<size_t>(targetBins.back());
    for (int bins : targetBins) {
        if (bins < 2 || maxBins % static_cast<size_t>(bins) != 0) {
            throw std::invalid_argument(
                "target bins must be nested divisors of the maximum");
        }
    }

    const size_t vertexCount = graph.vertexCount();
    const int horizon = bridge.p;
    const double rootVertexCount = std::sqrt(static_cast<double>(vertexCount));
    const double rootTwoHorizon = std::sqrt(2.0 * horizon);
    const bool hasMarks = graph.hasLatentMarks();

    const auto offsets = graph.outgoingOffsets();
    const auto targets = graph.outgoingTargets();
    const auto marks = graph.latentMarks();
    const auto [bulkFirst, bulkLast] = bulkRange(horizon, bulkFraction);

    // Graph-intrinsic target variables shared across route positions.
    std::vector<PredictiveMoment> canonical(vertexCount);
    std::vector<double> intrinsicMarks(vertexCount);
    for (size_t vertex = 0; vertex < vertexCount; ++vertex) {
        canonical[vertex] =
            predictiveTarget(state.coordinates[vertex], rootVertexCount);
        intrinsicMarks[vertex] = canonical[vertex][0];
    }

    // Route-position marginals test the exact Beta law implied by the
    // Dirichlet spacing representation.
    std::vector<long double> occupancy(vertexCount, 0.0L);
    std::vector<std::pair<double, long double>> empirical(vertexCount);
    const size_t routeLength = static_cast<size_t>(horizon);
    out.routeProfile.reserve(routeLength + 1);

    for (int position = 0; position <= horizon; ++position) {
        const size_t pos = static_cast<size_t>(position);
        const size_t remaining = static_cast<size_t>(horizon - position);
        const auto& left = routes.backward[pos];
        const auto& right = routes.forward[remaining];

        long double normalizer = 0.0L;
        for (size_t vertex = 0; vertex < vertexCount; ++vertex) {
            occupancy[vertex] = left[vertex] * right[vertex];
            normalizer += occupancy[vertex];
        }
        for (long double& mass : occupancy) {
            mass /= normalizer;
        }

        RouteProfilePosition profile;
        profile.position = position;
        profile.scaledPosition = static_cast<double>(position) / horizon;

        const double alpha = 2.0 * position + 1.0;
        const double beta = 2.0 * (horizon - position) + 1.0;
        const double total = alpha + beta;
        profile.betaMean = alpha / total;
        profile.betaVariance = alpha * beta / (total * total * (total + 1.0));

        long double intrinsicSecond = 0.0L;
        long double latentSecond = 0.0L;
        long double oracleSquared = 0.0L;

        for (size_t vertex = 0; vertex < vertexCount; ++vertex) {
            const long double mass = occupancy[vertex];
            const double intrinsic = intrinsicMarks[vertex];

            profile.intrinsicMean += static_cast<double>(mass * intrinsic);
            intrinsicSecond += mass * intrinsic * intrinsic;
            if (intrinsic < 0.0 || intrinsic > 1.0) {
                profile.intrinsicOutsideMass += static_cast<double>(mass);
            }
            empirical[vertex] = {intrinsic, mass};

            if (hasMarks) {
                profile.latentMean += static_cast<double>(mass * marks[vertex]);
                latentSecond += mass * marks[vertex] * marks[vertex];
                const long double error = intrinsic - marks[vertex];
                oracleSquared += mass * error * error;
            }
        }

        profile.intrinsicVariance =
            static_cast<double>(intrinsicSecond) -
            profile.intrinsicMean * profile.intrinsicMean;
        profile.intrinsicKolmogorov =
            weightedKolmogorov(empirical, alpha, beta);

        if (hasMarks) {
            for (size_t vertex = 0; vertex < vertexCount; ++vertex) {
                empirical[vertex] = {marks[vertex], occupancy[vertex]};
            }

            profile.latentVariance = static_cast<double>(latentSecond) -
                                     profile.latentMean * profile.latentMean;
            profile.latentKolmogorov =
                weightedKolmogorov(empirical, alpha, beta);
            profile.intrinsicOracleRmse =
                std::sqrt(static_cast<double>(oracleSquared));
        } else {
            const double nan = std::numeric_limits<double>::quiet_NaN();
            profile.latentMean = nan;
            profile.latentVariance = nan;
            profile.latentKolmogorov = nan;
            profile.intrinsicOracleRmse = nan;
        }

        profile.scaledIntrinsicMeanError =
            rootTwoHorizon * (profile.intrinsicMean - profile.betaMean);
        profile.scaledIntrinsicVariance =
            2.0 * horizon * profile.intrinsicVariance;
        profile.scaledLatentVariance =
            hasMarks ? 2.0 * horizon * profile.latentVariance
                     : std::numeric_limits<double>::quiet_NaN();

        out.routeProfile.push_back(profile);
    }

    // Diagnostics retained across transition positions.
    for (double threshold : thresholds) {
        out.intrinsicLindeberg.push_back({.threshold = threshold, .sum = 0.0});
    }
    for (const PredictivePartition& partition : partitions) {
        PredictiveClosureResult closure;
        closure.state = partition.state;
        closure.featureCount = partition.featureCount;
        closure.requestedClasses = partition.requestedClasses;
        closure.realizedClasses = partition.classSizes.size();
        closure.classSizes = partition.classSizes;

        for (uint32_t size : partition.classSizes) {
            closure.singletonClasses += size == 1 ? 1 : 0;
            closure.largestClass =
                std::max(closure.largestClass, static_cast<size_t>(size));
        }

        out.predictiveClosure.push_back(std::move(closure));
    }

    std::vector<SourceLaw> sourceLaws(vertexCount);
    std::vector<long double> sourceHistograms;
    std::vector<long double> gapHistogram(static_cast<size_t>(referenceBins));
    std::vector<long double> fractionHistogram(
        static_cast<size_t>(referenceBins));

    const size_t baseBytes = occupancy.capacity() * sizeof(long double) +
                             empirical.capacity() * sizeof(empirical.front()) +
                             canonical.capacity() * sizeof(canonical.front()) +
                             intrinsicMarks.capacity() * sizeof(double) +
                             sourceLaws.capacity() * sizeof(SourceLaw);
    out.peakBytes = baseBytes;
    out.spacing.reserve(routeLength);

    // One shared traversal supplies spacing, jump, and predictive diagnostics.
    for (int position = 0; position < horizon; ++position) {
        const int remaining = horizon - position;
        const size_t pos = static_cast<size_t>(position);
        const size_t remainingIndex = static_cast<size_t>(remaining);
        const auto& left = routes.backward[pos];
        const auto& right = routes.forward[remainingIndex];
        const auto& rightPrevious = routes.forward[remainingIndex - 1];

        long double occupancyNormalizer = 0.0L;
        for (size_t vertex = 0; vertex < vertexCount; ++vertex) {
            occupancy[vertex] = left[vertex] * right[vertex];
            occupancyNormalizer += occupancy[vertex];
        }
        for (long double& mass : occupancy) {
            mass /= occupancyNormalizer;
        }

        const bool inBulk = position >= bulkFirst && position <= bulkLast;
        if (inBulk) {
            sourceHistograms.assign(vertexCount * maxBins, 0.0L);
            std::ranges::fill(sourceLaws, SourceLaw{});
            out.peakBytes = std::max(out.peakBytes,
                                     baseBytes + sourceHistograms.capacity() *
                                                     sizeof(long double));
        }

        std::ranges::fill(gapHistogram, 0.0L);
        std::ranges::fill(fractionHistogram, 0.0L);

        long double flowTotal = 0.0L;
        long double gapMean = 0.0L;
        long double gapSecond = 0.0L;
        long double fractionMean = 0.0L;
        long double fractionSecond = 0.0L;
        long double sourceMean = 0.0L;
        long double sourceSecond = 0.0L;
        long double sourceFraction = 0.0L;

        for (size_t source = 0; source < vertexCount; ++source) {
            const long double sourceMass = occupancy[source];
            if (!(sourceMass > 0.0L)) {
                continue;
            }

            const long double denominator =
                routes.forwardScales[remainingIndex] * right[source];
            for (size_t edge = offsets[source]; edge < offsets[source + 1];
                 ++edge) {
                const size_t target = targets[edge];
                const long double probability =
                    rightPrevious[target] / denominator;
                if (!(probability > 0.0L)) {
                    continue;
                }

                const long double flow = sourceMass * probability;
                flowTotal += flow;

                const double markDifference =
                    intrinsicMarks[target] - intrinsicMarks[source];
                const double meanMarkDifference =
                    bridge.positions[pos].mean[1] -
                    bridge.positions[pos].mean[0];
                const double scaledCentered =
                    rootTwoHorizon * (markDifference - meanMarkDifference);

                out.macroscopicMaximalJump =
                    std::max(out.macroscopicMaximalJump,
                             horizon * std::abs(markDifference));
                out.intrinsicFluctuationMaximalJump =
                    std::max(out.intrinsicFluctuationMaximalJump,
                             std::abs(scaledCentered));

                for (ScaledLindebergTail& tail : out.intrinsicLindeberg) {
                    if (std::abs(scaledCentered) > tail.threshold) {
                        tail.sum += static_cast<double>(flow * scaledCentered *
                                                        scaledCentered);
                    }
                }

                // Latent marks are used only for the independent reference-law
                // audit, never in a predictor or predictive partition.
                if (hasMarks) {
                    const double sourceMark = marks[source];
                    const double gap = marks[target] - sourceMark;
                    const double fraction = gap / (1.0 - sourceMark);

                    gapMean += flow * gap;
                    gapSecond += flow * gap * gap;
                    fractionMean += flow * fraction;
                    fractionSecond += flow * fraction * fraction;
                    sourceMean += flow * sourceMark;
                    sourceSecond += flow * sourceMark * sourceMark;
                    sourceFraction += flow * sourceMark * fraction;

                    gapHistogram[histogramBin(
                        gap, static_cast<size_t>(referenceBins))] += flow;
                    fractionHistogram[histogramBin(
                        fraction, static_cast<size_t>(referenceBins))] += flow;
                }

                if (inBulk) {
                    for (size_t coordinate = 0;
                         coordinate < kPredictiveMomentCount; ++coordinate) {
                        sourceLaws[source].mean[coordinate] +=
                            static_cast<double>(probability) *
                            canonical[target][coordinate];
                    }
                    sourceHistograms[source * maxBins +
                                     histogramBin(intrinsicMarks[target],
                                                  maxBins)] += probability;
                }
            }
        }

        RouteSpacingPosition spacing;
        spacing.position = position;
        spacing.remainingEdges = remaining;

        if (hasMarks) {
            gapMean /= flowTotal;
            gapSecond /= flowTotal;
            fractionMean /= flowTotal;
            fractionSecond /= flowTotal;
            sourceMean /= flowTotal;
            sourceSecond /= flowTotal;
            sourceFraction /= flowTotal;

            spacing.gapMean = static_cast<double>(gapMean);
            spacing.gapTargetMean = 1.0 / (horizon + 1.0);
            spacing.gapVariance =
                static_cast<double>(gapSecond - gapMean * gapMean);
            spacing.gapTargetVariance =
                4.0 * horizon /
                (std::pow(2.0 * horizon + 2.0, 2) * (2.0 * horizon + 3.0));
            spacing.gapKolmogorovBound =
                histogramKolmogorovBound(gapHistogram, 2.0, 2.0 * horizon);

            spacing.conditionalFractionMean = static_cast<double>(fractionMean);
            spacing.conditionalFractionTargetMean =
                2.0 / (2.0 * remaining + 1.0);
            spacing.conditionalFractionVariance = static_cast<double>(
                fractionSecond - fractionMean * fractionMean);
            spacing.conditionalFractionTargetVariance =
                2.0 * (2.0 * remaining - 1.0) /
                (std::pow(2.0 * remaining + 1.0, 2) * (2.0 * remaining + 2.0));
            spacing.conditionalFractionKolmogorovBound =
                histogramKolmogorovBound(fractionHistogram, 2.0,
                                         2.0 * remaining - 1.0);

            spacing.sourceFractionCovariance =
                static_cast<double>(sourceFraction - sourceMean * fractionMean);
            const long double sourceVariance =
                sourceSecond - sourceMean * sourceMean;
            const long double fractionVariance =
                fractionSecond - fractionMean * fractionMean;
            spacing.sourceFractionCorrelation =
                sourceVariance > 0.0L && fractionVariance > 0.0L
                    ? static_cast<double>(
                          spacing.sourceFractionCovariance /
                          std::sqrt(sourceVariance * fractionVariance))
                    : std::numeric_limits<double>::quiet_NaN();
        } else {
            const double nan = std::numeric_limits<double>::quiet_NaN();
            spacing.gapMean = nan;
            spacing.gapTargetMean = nan;
            spacing.gapVariance = nan;
            spacing.gapTargetVariance = nan;
            spacing.gapKolmogorovBound = nan;
            spacing.conditionalFractionMean = nan;
            spacing.conditionalFractionTargetMean = nan;
            spacing.conditionalFractionVariance = nan;
            spacing.conditionalFractionTargetVariance = nan;
            spacing.conditionalFractionKolmogorovBound = nan;
            spacing.sourceFractionCovariance = nan;
            spacing.sourceFractionCorrelation = nan;
        }

        out.spacing.push_back(spacing);

        if (inBulk) {
            for (size_t i = 0; i < partitions.size(); ++i) {
                out.predictiveClosure[i].positions.push_back(scorePrediction(
                    position, horizon, partitions[i], occupancy, sourceLaws,
                    sourceHistograms, maxBins, targetBins));
            }
        }
    }

    out.seconds = std::chrono::duration<double>(Clock::now() - started).count();
    return out;
}

size_t runRouteScalingSelfTests() {
    size_t checks = 0;

    const ReferenceDag graph = ReferenceDag::generate(32, 918273645ULL);
    const GapNodeState state = computeGapNodeState(graph);
    const IntrinsicStateScaling summary = summarizeIntrinsicState(state);
    if (!std::isfinite(summary.scaledTransverseResidualRms)) {
        throw std::runtime_error("route scaling self-test: residual summary");
    }
    ++checks;

    constexpr std::array<int, 2> classes{2, 4};
    const std::vector<PredictivePartition> partitions =
        buildPredictivePartitions(graph, state, classes);
    if (partitions.size() != 6) {
        throw std::runtime_error("route scaling self-test: partitions");
    }
    ++checks;

    for (const PredictivePartition& partition : partitions) {
        const size_t covered =
            std::accumulate(partition.classSizes.begin(),
                            partition.classSizes.end(), size_t{0});
        if (covered != graph.vertexCount()) {
            throw std::runtime_error(
                "route scaling self-test: partition coverage");
        }
        ++checks;
    }

    const StableRouteCounts routes = computeRouteCounts(graph, 4);
    const HorizonResult bridge =
        analyzeHorizon(graph, state, routes, 3, {}, 0.2, {});
    constexpr std::array<int, 2> targetBins{4, 8};
    constexpr std::array<double, 2> thresholds{0.5, 1.0};
    const RouteScalingResult scaling =
        analyzeRouteScaling(graph, state, routes, bridge, partitions,
                            targetBins, thresholds, 0.2, 32);

    if (!scaling.hasRoutes || scaling.routeProfile.size() != 4 ||
        scaling.spacing.size() != 3 ||
        scaling.predictiveClosure.size() != partitions.size()) {
        throw std::runtime_error("route scaling self-test: analysis shape");
    }
    checks += 4;

    return checks;
}
