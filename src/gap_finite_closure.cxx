#include "reference_dag.hxx"
#include "route_bridge.hxx"

#include <algorithm>
#include <array>
#include <atomic>
#include <boost/math/special_functions/beta.hpp>
#include <charconv>
#include <chrono>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <exception>
#include <filesystem>
#include <fstream>
#include <iterator>
#include <limits>
#include <mutex>
#include <numeric>
#include <ostream>
#include <print>
#include <span>
#include <stdexcept>
#include <string>
#include <string_view>
#include <system_error>
#include <thread>
#include <tuple>
#include <utility>
#include <vector>

namespace {

using Clock = std::chrono::steady_clock;
constexpr size_t kConditionalBins = 16;
constexpr uint64_t kRouteDomain = 0x7e0f8b18a61c27d3ULL;
constexpr uint64_t kControlDomain = 0xb564e548f2d9a30fULL;

struct Resolution {
    int baseBins = 0;
    int auxLeaves = 0;
    int targetBins = 0;
};

struct Options {
    size_t vertexCount = 0;
    std::vector<int> horizons;
    size_t sampleCount = 0;
    size_t pathsPerHorizon = 0;
    uint64_t seed = 0;
    size_t threads = 1;
    std::filesystem::path outputDirectory;
    std::vector<Resolution> resolutions;
    int referenceBins = 256;
    double pseudocount = 0.5;
    bool overwrite = false;
    bool selfTest = false;
    bool help = false;
};

struct TransitionRecord {
    uint32_t graphIndex = 0;
    uint32_t pathIndex = 0;
    uint16_t horizon = 0;
    uint16_t position = 0;
    double x = 0.0;
    double intrinsicX = 0.0;
    double routeAge = 0.0;
    double previousX = 0.0;
    double previousIntrinsicX = 0.0;
    double latentLastFraction = 0.0;
    double latentQuadratic = 0.0;
    double intrinsicLast = 0.0;
    double intrinsicQuadratic = 0.0;
    std::array<double, kGapCoordinateCount> transverse{};
    std::array<double, kGapCoordinateCount> previousTransverse{};
    double z = 0.0;
    double controlZ = 0.0;
};

struct HorizonGraphRecord {
    int horizon = 0;
    bool hasRoutes = false;
    size_t paths = 0;
    long double logRouteCount = -std::numeric_limits<long double>::infinity();
    double routeMarkRmse = 0.0;
};

struct GraphRecords {
    size_t index = 0;
    uint64_t sampleSeed = 0;
    size_t edgeCount = 0;
    size_t estimatedBytes = 0;
    double nodeMarkRmse = 0.0;
    double nodeMarkMaxError = 0.0;
    double seconds = 0.0;
    std::vector<HorizonGraphRecord> horizons;
    std::vector<TransitionRecord> transitions;
};

struct Metric {
    size_t graphIndex = 0;
    int horizon = 0;
    size_t resolutionIndex = 0;
    int baseBins = 0;
    int auxLeaves = 0;
    int targetBins = 0;
    std::string model;
    std::string data;
    size_t recordCount = 0;
    size_t trainingRecords = 0;
    size_t realizedClasses = 0;
    size_t minimumTrainingClass = 0;
    double logScore = 0.0;
    double wasserstein = 0.0;
    double pitMean = 0.0;
    double pitVariance = 0.0;
    double pitKolmogorov = 0.0;
    double meanResidual = 0.0;
    double secondResidual = 0.0;
    double pitXCorrelation = 0.0;
    double pitAgeCorrelation = 0.0;
    double pitHistoryCorrelation = 0.0;
    double maxConditionalMeanError = 0.0;
    double maxConditionalVarianceError = 0.0;
};

uint64_t mix64(uint64_t value) {
    value += 0x9e3779b97f4a7c15ULL;
    value = (value ^ (value >> 30U)) * 0xbf58476d1ce4e5b9ULL;
    value = (value ^ (value >> 27U)) * 0x94d049bb133111ebULL;
    return value ^ (value >> 31U);
}

class Rng {
  public:
    explicit Rng(uint64_t seed) : m_state(seed) {}

    uint64_t next() {
        m_state += 0x9e3779b97f4a7c15ULL;
        return mix64(m_state);
    }

    double uniformOpen() {
        constexpr double scale = 0x1.0p-53;
        return (static_cast<double>(next() >> 11U) + 0.5) * scale;
    }

  private:
    uint64_t m_state;
};

double sampleBetaInteger(int firstShape, int secondShape, Rng& rng) {
    double first = 0.0;
    double second = 0.0;
    for (int index = 0; index < firstShape; ++index) {
        first -= std::log(rng.uniformOpen());
    }
    for (int index = 0; index < secondShape; ++index) {
        second -= std::log(rng.uniformOpen());
    }
    return first / (first + second);
}

template <typename Integer>
Integer parseInteger(std::string_view text, std::string_view option) {
    Integer value{};
    const auto [end, error] =
        std::from_chars(text.data(), text.data() + text.size(), value);
    if (error != std::errc{} || end != text.data() + text.size()) {
        throw std::invalid_argument(std::string(option) +
                                    " requires an integer");
    }
    return value;
}

double parseDouble(std::string_view text, std::string_view option) {
    std::string copy(text);
    size_t used = 0;
    const double value = std::stod(copy, &used);
    if (used != copy.size() || !std::isfinite(value)) {
        throw std::invalid_argument(std::string(option) +
                                    " requires a finite number");
    }
    return value;
}

std::string_view requireValue(std::span<char*> arguments, size_t& index,
                              std::string_view option) {
    if (index + 1 >= arguments.size()) {
        throw std::invalid_argument(std::string(option) + " requires a value");
    }
    return arguments[++index];
}

std::vector<int> parseList(std::string_view text, std::string_view option) {
    std::vector<int> values;
    size_t begin = 0;
    while (begin <= text.size()) {
        const size_t comma = text.find(',', begin);
        const size_t end =
            comma == std::string_view::npos ? text.size() : comma;
        if (end == begin) {
            throw std::invalid_argument(std::string(option) +
                                        " contains an empty item");
        }
        values.push_back(
            parseInteger<int>(text.substr(begin, end - begin), option));
        if (comma == std::string_view::npos) {
            break;
        }
        begin = comma + 1;
    }
    return values;
}

void printUsage(std::string_view program) {
    std::println(stderr,
                 "usage: {} --vertices N --horizons p[,p...] --samples S "
                 "--paths R --seed U --threads T --output DIR [options]",
                 program);
    std::println(stderr, "options:");
    std::println(stderr,
                 "  --base-bins b[,b...]      zipped state-bin refinements "
                 "(8,16,32)");
    std::println(stderr, "  --aux-leaves l[,l...]     zipped within-bin leaves "
                         "(2,2,2)");
    std::println(stderr,
                 "  --target-bins b[,b...]    zipped conditional-law bins "
                 "(32,64,128)");
    std::println(stderr,
                 "  --reference-bins B        held-out Wasserstein grid (256)");
    std::println(stderr,
                 "  --pseudocount a           histogram pseudocount (0.5)");
    std::println(stderr, "  --overwrite               replace an existing run");
    std::println(stderr,
                 "  --self-test               run internal checks only");
}

Options parseOptions(std::span<char*> arguments) {
    Options options;
    std::vector<int> baseBins{8, 16, 32};
    std::vector<int> auxLeaves{2, 2, 2};
    std::vector<int> targetBins{32, 64, 128};

    for (size_t index = 1; index < arguments.size(); ++index) {
        const std::string_view option = arguments[index];
        if (option == "--vertices") {
            options.vertexCount = parseInteger<size_t>(
                requireValue(arguments, index, option), option);
        } else if (option == "--horizons") {
            options.horizons =
                parseList(requireValue(arguments, index, option), option);
        } else if (option == "--samples") {
            options.sampleCount = parseInteger<size_t>(
                requireValue(arguments, index, option), option);
        } else if (option == "--paths") {
            options.pathsPerHorizon = parseInteger<size_t>(
                requireValue(arguments, index, option), option);
        } else if (option == "--seed") {
            options.seed = parseInteger<uint64_t>(
                requireValue(arguments, index, option), option);
        } else if (option == "--threads") {
            options.threads = parseInteger<size_t>(
                requireValue(arguments, index, option), option);
        } else if (option == "--output") {
            options.outputDirectory = requireValue(arguments, index, option);
        } else if (option == "--base-bins") {
            baseBins =
                parseList(requireValue(arguments, index, option), option);
        } else if (option == "--aux-leaves") {
            auxLeaves =
                parseList(requireValue(arguments, index, option), option);
        } else if (option == "--target-bins") {
            targetBins =
                parseList(requireValue(arguments, index, option), option);
        } else if (option == "--reference-bins") {
            options.referenceBins = parseInteger<int>(
                requireValue(arguments, index, option), option);
        } else if (option == "--pseudocount") {
            options.pseudocount =
                parseDouble(requireValue(arguments, index, option), option);
        } else if (option == "--overwrite") {
            options.overwrite = true;
        } else if (option == "--self-test") {
            options.selfTest = true;
        } else if (option == "--help") {
            options.help = true;
            return options;
        } else {
            throw std::invalid_argument("unknown option: " +
                                        std::string(option));
        }
    }

    if (options.selfTest || options.help) {
        return options;
    }
    if (options.vertexCount < 2) {
        throw std::invalid_argument("--vertices must be at least two");
    }
    if (options.horizons.empty()) {
        throw std::invalid_argument("--horizons is required");
    }
    std::ranges::sort(options.horizons);
    if (std::ranges::adjacent_find(options.horizons) !=
            options.horizons.end() ||
        options.horizons.front() < 2 || options.horizons.back() > 65535) {
        throw std::invalid_argument(
            "--horizons must contain distinct integers in 2..65535");
    }
    if (options.sampleCount < 4) {
        throw std::invalid_argument("--samples must be at least four");
    }
    if (options.pathsPerHorizon == 0) {
        throw std::invalid_argument("--paths must be positive");
    }
    if (options.threads == 0) {
        throw std::invalid_argument("--threads must be positive");
    }
    if (options.outputDirectory.empty()) {
        throw std::invalid_argument("--output is required");
    }
    if (baseBins.size() != auxLeaves.size() ||
        baseBins.size() != targetBins.size() || baseBins.empty()) {
        throw std::invalid_argument("--base-bins, --aux-leaves, and "
                                    "--target-bins must have equal lengths");
    }
    if (options.referenceBins < 64 || options.referenceBins > 4096) {
        throw std::invalid_argument("--reference-bins must be in 64..4096");
    }
    if (!(options.pseudocount > 0.0)) {
        throw std::invalid_argument("--pseudocount must be positive");
    }

    for (size_t index = 0; index < baseBins.size(); ++index) {
        if (baseBins[index] < 2 || baseBins[index] > 256 ||
            auxLeaves[index] < 1 || auxLeaves[index] > 16 ||
            targetBins[index] < 8 || targetBins[index] > 1024) {
            throw std::invalid_argument(
                "resolution entries exceed their permitted ranges");
        }
        options.resolutions.push_back(
            {baseBins[index], auxLeaves[index], targetBins[index]});
    }
    return options;
}

size_t drawWeighted(std::span<const long double> weights, Rng& rng) {
    const long double total =
        std::accumulate(weights.begin(), weights.end(), 0.0L);
    if (!(total > 0.0L)) {
        throw std::runtime_error("route sampler encountered zero weight");
    }

    const long double target =
        static_cast<long double>(rng.uniformOpen()) * total;
    long double cumulative = 0.0L;
    for (size_t index = 0; index < weights.size(); ++index) {
        cumulative += weights[index];
        if (target < cumulative) {
            return index;
        }
    }
    return weights.size() - 1;
}

std::vector<uint32_t> sampleRoute(const ReferenceDag& graph,
                                  const StableRouteCounts& routes, int horizon,
                                  Rng& rng) {
    const auto& forward = routes.forward[static_cast<size_t>(horizon)];
    const size_t source = drawWeighted(forward, rng);
    std::vector<uint32_t> path;
    path.reserve(static_cast<size_t>(horizon) + 1);
    path.push_back(static_cast<uint32_t>(source));

    const auto offsets = graph.outgoingOffsets();
    const auto targets = graph.outgoingTargets();
    for (int position = 0; position < horizon; ++position) {
        const uint32_t vertex = path.back();
        const size_t begin = offsets[vertex];
        const size_t end = offsets[static_cast<size_t>(vertex) + 1];
        const auto& continuations =
            routes.forward[static_cast<size_t>(horizon - position - 1)];

        long double total = 0.0L;
        for (size_t edge = begin; edge < end; ++edge) {
            total += continuations[targets[edge]];
        }
        if (!(total > 0.0L)) {
            throw std::runtime_error("route sampler reached a dead end");
        }

        const long double selected =
            static_cast<long double>(rng.uniformOpen()) * total;
        long double cumulative = 0.0L;
        uint32_t next = std::numeric_limits<uint32_t>::max();
        for (size_t edge = begin; edge < end; ++edge) {
            const uint32_t candidate = targets[edge];
            const long double weight = continuations[candidate];
            if (weight <= 0.0L) {
                continue;
            }
            next = candidate;
            cumulative += weight;
            if (selected < cumulative) {
                break;
            }
        }
        path.push_back(next);
    }
    return path;
}

std::array<double, kGapCoordinateCount>
scaledTransverse(const GapCoordinate& coordinate, double intrinsicX,
                 double rootVertexCount) {
    const GapCoordinate reference = gapContinuumCoordinate(intrinsicX);
    std::array<double, kGapCoordinateCount> result{};
    for (size_t index = 0; index < result.size(); ++index) {
        result[index] =
            rootVertexCount * (coordinate[index] - reference[index]);
    }
    return result;
}

double intrinsicMark(const GapNodeState& state, uint32_t vertex) {
    const GapCoordinate& coordinate = state.coordinates[vertex];
    return 0.5 + coordinate[1] - coordinate[0];
}

void appendTransitions(GraphRecords& sample, const ReferenceDag& graph,
                       const GapNodeState& state,
                       const StableRouteCounts& routes, int horizon,
                       size_t pathCount, uint64_t sampleSeed) {
    const auto marks = graph.latentMarks();
    const double rootVertexCount =
        std::sqrt(static_cast<double>(graph.vertexCount()));

    for (size_t pathIndex = 0; pathIndex < pathCount; ++pathIndex) {
        const uint64_t routeSeed =
            mix64(sampleSeed ^ kRouteDomain ^
                  (static_cast<uint64_t>(horizon) << 40U) ^ pathIndex);
        Rng routeRng(routeSeed);
        Rng controlRng(mix64(routeSeed ^ kControlDomain));
        const std::vector<uint32_t> path =
            sampleRoute(graph, routes, horizon, routeRng);

        double latentSquareSum = 0.0;
        double intrinsicSquareSum = 0.0;

        for (int position = 1; position < horizon; ++position) {
            const uint32_t vertex = path[static_cast<size_t>(position)];
            const uint32_t previous = path[static_cast<size_t>(position - 1)];
            const uint32_t next = path[static_cast<size_t>(position) + 1];
            const double x = marks[vertex];
            const double previousX = marks[previous];
            const double intrinsicX = intrinsicMark(state, vertex);
            const double previousIntrinsicX = intrinsicMark(state, previous);
            const double latentGap = x - previousX;
            const double intrinsicGap = intrinsicX - previousIntrinsicX;
            latentSquareSum += latentGap * latentGap;
            intrinsicSquareSum += intrinsicGap * intrinsicGap;
            const int remaining = horizon - position;

            TransitionRecord record;
            record.graphIndex = static_cast<uint32_t>(sample.index);
            record.pathIndex = static_cast<uint32_t>(pathIndex);
            record.horizon = static_cast<uint16_t>(horizon);
            record.position = static_cast<uint16_t>(position);
            record.x = x;
            record.intrinsicX = intrinsicX;
            record.routeAge =
                static_cast<double>(position) / static_cast<double>(horizon);
            record.previousX = previousX;
            record.previousIntrinsicX = previousIntrinsicX;
            record.latentLastFraction = x > 0.0 ? latentGap / x : 0.0;
            record.latentQuadratic = x > 0.0 ? latentSquareSum / (x * x) : 0.0;
            record.intrinsicLast = intrinsicGap;
            const double intrinsicScale =
                intrinsicX * intrinsicX +
                1.0 / static_cast<double>(graph.vertexCount());
            record.intrinsicQuadratic = intrinsicSquareSum / intrinsicScale;
            record.transverse = scaledTransverse(state.coordinates[vertex],
                                                 intrinsicX, rootVertexCount);
            record.previousTransverse =
                scaledTransverse(state.coordinates[previous],
                                 previousIntrinsicX, rootVertexCount);
            record.z = (marks[next] - x) / (1.0 - x);
            record.controlZ =
                sampleBetaInteger(2, 2 * remaining - 1, controlRng);
            sample.transitions.push_back(record);
        }
    }
}

GraphRecords sampleGraph(const Options& options, size_t index) {
    const auto started = Clock::now();
    GraphRecords sample;
    sample.index = index;
    sample.sampleSeed = deriveGapSampleSeed(options.seed, index);

    ReferenceDag graph =
        ReferenceDag::generate(options.vertexCount, sample.sampleSeed);
    const GapNodeState state = computeGapNodeState(graph);
    const LatentStateValidation validation = validateGapNodeState(graph, state);
    sample.nodeMarkRmse = validation.reconstructedMarkRmse;
    sample.nodeMarkMaxError = validation.reconstructedMarkMaxError;
    const StableRouteCounts routes =
        computeRouteCounts(graph, static_cast<size_t>(options.horizons.back()));
    sample.edgeCount = graph.edgeCount();
    sample.estimatedBytes = graph.estimatedBytes() + state.estimatedBytes() +
                            routes.estimatedBytes();

    for (int horizon : options.horizons) {
        HorizonGraphRecord horizonRecord;
        horizonRecord.horizon = horizon;
        horizonRecord.hasRoutes =
            routes.hasRoutes(static_cast<size_t>(horizon));
        horizonRecord.logRouteCount =
            horizonRecord.hasRoutes
                ? routes.forwardLogs[static_cast<size_t>(horizon)]
                : -std::numeric_limits<long double>::infinity();
        horizonRecord.paths =
            horizonRecord.hasRoutes ? options.pathsPerHorizon : 0;
        if (horizonRecord.hasRoutes) {
            const size_t first = sample.transitions.size();
            appendTransitions(sample, graph, state, routes, horizon,
                              options.pathsPerHorizon, sample.sampleSeed);
            double squareError = 0.0;
            for (size_t transition = first;
                 transition < sample.transitions.size(); ++transition) {
                const double error = sample.transitions[transition].intrinsicX -
                                     sample.transitions[transition].x;
                squareError += error * error;
            }
            horizonRecord.routeMarkRmse =
                std::sqrt(squareError / static_cast<double>(
                                            sample.transitions.size() - first));
        }
        sample.horizons.push_back(horizonRecord);
    }

    sample.estimatedBytes +=
        sample.transitions.capacity() * sizeof(TransitionRecord);
    sample.seconds =
        std::chrono::duration<double>(Clock::now() - started).count();
    return sample;
}

std::vector<GraphRecords> sampleGraphs(const Options& options,
                                       size_t threadCount) {
    std::vector<GraphRecords> graphs(options.sampleCount);
    std::atomic<size_t> next{0};
    std::exception_ptr failure;
    std::mutex failureMutex;

    auto worker = [&] {
        try {
            while (true) {
                const size_t index =
                    next.fetch_add(1, std::memory_order_relaxed);
                if (index >= options.sampleCount) {
                    return;
                }
                graphs[index] = sampleGraph(options, index);
            }
        } catch (...) {
            std::scoped_lock lock(failureMutex);
            if (!failure) {
                failure = std::current_exception();
            }
            next.store(options.sampleCount, std::memory_order_relaxed);
        }
    };

    std::vector<std::thread> workers;
    workers.reserve(threadCount);
    for (size_t index = 0; index < threadCount; ++index) {
        workers.emplace_back(worker);
    }
    for (std::thread& thread : workers) {
        thread.join();
    }
    if (failure) {
        std::rethrow_exception(failure);
    }
    return graphs;
}

enum class ModelKind {
    latent,
    latentAge,
    latentHistory,
    intrinsic,
    intrinsicAge,
    intrinsicHistory,
    fullState,
    fullAge,
    fullHistory,
};

struct ModelSpec {
    ModelKind kind;
    std::string_view name;
};

constexpr std::array<ModelSpec, 9> kModels{{
    {ModelKind::latent, "latent"},
    {ModelKind::latentAge, "latent_age"},
    {ModelKind::latentHistory, "latent_history"},
    {ModelKind::intrinsic, "intrinsic_mark"},
    {ModelKind::intrinsicAge, "intrinsic_age"},
    {ModelKind::intrinsicHistory, "intrinsic_history"},
    {ModelKind::fullState, "full_state"},
    {ModelKind::fullAge, "full_age"},
    {ModelKind::fullHistory, "full_history"},
}};

double primaryFeature(const ModelSpec& model, const TransitionRecord& record) {
    switch (model.kind) {
    case ModelKind::latent:
    case ModelKind::latentAge:
    case ModelKind::latentHistory:
        return record.x;
    case ModelKind::intrinsic:
    case ModelKind::intrinsicAge:
    case ModelKind::intrinsicHistory:
    case ModelKind::fullState:
    case ModelKind::fullAge:
    case ModelKind::fullHistory:
        return record.intrinsicX;
    }
    throw std::logic_error("unreachable model kind");
}

size_t auxiliaryFeatureCount(const ModelSpec& model) {
    switch (model.kind) {
    case ModelKind::latent:
    case ModelKind::intrinsic:
        return 0;
    case ModelKind::latentAge:
    case ModelKind::intrinsicAge:
        return 1;
    case ModelKind::latentHistory:
    case ModelKind::intrinsicHistory:
        return 4;
    case ModelKind::fullState:
        return kGapCoordinateCount;
    case ModelKind::fullAge:
        return kGapCoordinateCount + 1;
    case ModelKind::fullHistory:
        return 2 * kGapCoordinateCount + 4;
    }
    throw std::logic_error("unreachable model kind");
}

double auxiliaryFeature(const ModelSpec& model, const TransitionRecord& record,
                        size_t index) {
    switch (model.kind) {
    case ModelKind::latent:
    case ModelKind::intrinsic:
        break;
    case ModelKind::latentAge:
    case ModelKind::intrinsicAge:
        if (index == 0) {
            return record.routeAge;
        }
        break;
    case ModelKind::latentHistory:
        if (index == 0) {
            return record.routeAge;
        }
        if (index == 1) {
            return record.previousX;
        }
        if (index == 2) {
            return record.latentLastFraction;
        }
        if (index == 3) {
            return record.latentQuadratic;
        }
        break;
    case ModelKind::intrinsicHistory:
        if (index == 0) {
            return record.routeAge;
        }
        if (index == 1) {
            return record.previousIntrinsicX;
        }
        if (index == 2) {
            return record.intrinsicLast;
        }
        if (index == 3) {
            return record.intrinsicQuadratic;
        }
        break;
    case ModelKind::fullState:
        if (index < kGapCoordinateCount) {
            return record.transverse[index];
        }
        break;
    case ModelKind::fullAge:
        if (index < kGapCoordinateCount) {
            return record.transverse[index];
        }
        if (index == kGapCoordinateCount) {
            return record.routeAge;
        }
        break;
    case ModelKind::fullHistory:
        if (index < kGapCoordinateCount) {
            return record.transverse[index];
        }
        if (index == kGapCoordinateCount) {
            return record.routeAge;
        }
        if (index == kGapCoordinateCount + 1) {
            return record.previousIntrinsicX;
        }
        if (index == kGapCoordinateCount + 2) {
            return record.intrinsicLast;
        }
        if (index == kGapCoordinateCount + 3) {
            return record.intrinsicQuadratic;
        }
        if (index >= kGapCoordinateCount + 4 &&
            index < 2 * kGapCoordinateCount + 4) {
            return record.previousTransverse[index - kGapCoordinateCount - 4];
        }
        break;
    }
    throw std::out_of_range("auxiliary feature index out of range");
}

struct TreeNode {
    int feature = -1;
    double threshold = 0.0;
    int left = -1;
    int right = -1;
    size_t leaf = 0;
};

struct FeatureTree {
    std::vector<TreeNode> nodes;
    size_t leafCount = 1;

    size_t classify(const ModelSpec& model,
                    const TransitionRecord& record) const {
        size_t nodeIndex = 0;
        while (nodes[nodeIndex].feature >= 0) {
            const TreeNode& node = nodes[nodeIndex];
            nodeIndex = auxiliaryFeature(model, record,
                                         static_cast<size_t>(node.feature)) <=
                                node.threshold
                            ? static_cast<size_t>(node.left)
                            : static_cast<size_t>(node.right);
        }
        return nodes[nodeIndex].leaf;
    }
};

struct LeafWork {
    size_t node = 0;
    std::vector<size_t> rows;
};

struct CandidateSplit {
    bool valid = false;
    size_t leaf = 0;
    size_t feature = 0;
    double threshold = 0.0;
    double gain = 0.0;
    std::vector<size_t> left;
    std::vector<size_t> right;
};

double multinomialLogLikelihood(std::span<const size_t> counts) {
    const size_t total =
        std::accumulate(counts.begin(), counts.end(), size_t{0});
    if (total == 0) {
        return 0.0;
    }
    double result = 0.0;
    for (size_t count : counts) {
        if (count > 0) {
            result += static_cast<double>(count) *
                      std::log(static_cast<double>(count) /
                               static_cast<double>(total));
        }
    }
    return result;
}

size_t targetBin(double value, int bins) {
    return std::min(static_cast<size_t>(value * static_cast<double>(bins)),
                    static_cast<size_t>(bins - 1));
}

CandidateSplit bestLeafSplit(const ModelSpec& model,
                             std::span<const TransitionRecord* const> records,
                             std::span<const double> outcomes,
                             const LeafWork& leaf, size_t leafIndex,
                             int targetBins, size_t minimumChild) {
    CandidateSplit best;
    best.leaf = leafIndex;
    if (leaf.rows.size() < 2 * minimumChild) {
        return best;
    }

    std::vector<size_t> parentCounts(static_cast<size_t>(targetBins), 0);
    for (size_t row : leaf.rows) {
        ++parentCounts[targetBin(outcomes[row], targetBins)];
    }
    const double parentLikelihood = multinomialLogLikelihood(parentCounts);
    const size_t featureCount = auxiliaryFeatureCount(model);

    for (size_t feature = 0; feature < featureCount; ++feature) {
        std::vector<size_t> sorted = leaf.rows;
        std::ranges::sort(sorted, [&](size_t left, size_t right) {
            const double a = auxiliaryFeature(model, *records[left], feature);
            const double b = auxiliaryFeature(model, *records[right], feature);
            return a < b || (a == b && left < right);
        });

        std::vector<size_t> boundaries;
        for (size_t split = minimumChild; split + minimumChild <= sorted.size();
             ++split) {
            const double lower =
                auxiliaryFeature(model, *records[sorted[split - 1]], feature);
            const double upper =
                auxiliaryFeature(model, *records[sorted[split]], feature);
            if (lower < upper) {
                boundaries.push_back(split);
            }
        }
        std::vector<size_t> candidates;
        if (boundaries.size() <= 16) {
            candidates = boundaries;
        } else {
            for (size_t numerator : {size_t{1}, size_t{2}, size_t{3}}) {
                const size_t target = numerator * sorted.size() / 4;
                const auto upper = std::lower_bound(boundaries.begin(),
                                                    boundaries.end(), target);
                if (upper != boundaries.end()) {
                    candidates.push_back(*upper);
                }
                if (upper != boundaries.begin()) {
                    candidates.push_back(*std::prev(upper));
                }
            }
            std::ranges::sort(candidates);
            candidates.erase(std::unique(candidates.begin(), candidates.end()),
                             candidates.end());
        }

        for (size_t split : candidates) {
            const double lower =
                auxiliaryFeature(model, *records[sorted[split - 1]], feature);
            const double upper =
                auxiliaryFeature(model, *records[sorted[split]], feature);
            if (!(lower < upper)) {
                throw std::logic_error("candidate is not a feature boundary");
            }

            std::vector<size_t> leftCounts(static_cast<size_t>(targetBins), 0);
            std::vector<size_t> rightCounts(static_cast<size_t>(targetBins), 0);
            for (size_t index = 0; index < split; ++index) {
                ++leftCounts[targetBin(outcomes[sorted[index]], targetBins)];
            }
            for (size_t index = split; index < sorted.size(); ++index) {
                ++rightCounts[targetBin(outcomes[sorted[index]], targetBins)];
            }
            const double gain = multinomialLogLikelihood(leftCounts) +
                                multinomialLogLikelihood(rightCounts) -
                                parentLikelihood;
            if (!best.valid || gain > best.gain + 1.0e-12) {
                best.valid = true;
                best.feature = feature;
                best.threshold = std::midpoint(lower, upper);
                best.gain = gain;
                best.left.assign(sorted.begin(),
                                 sorted.begin() +
                                     static_cast<std::ptrdiff_t>(split));
                best.right.assign(sorted.begin() +
                                      static_cast<std::ptrdiff_t>(split),
                                  sorted.end());
            }
        }
    }
    return best;
}

FeatureTree buildFeatureTree(const ModelSpec& model,
                             std::span<const TransitionRecord* const> records,
                             std::span<const double> outcomes,
                             std::vector<size_t> rows, int requestedLeaves,
                             int targetBins) {
    FeatureTree tree;
    tree.nodes.push_back({});
    std::vector<LeafWork> leaves{{0, std::move(rows)}};
    const size_t minimumChild =
        std::max<size_t>(16, static_cast<size_t>(targetBins / 2));

    while (leaves.size() < static_cast<size_t>(requestedLeaves)) {
        CandidateSplit best;
        for (size_t leaf = 0; leaf < leaves.size(); ++leaf) {
            CandidateSplit candidate =
                bestLeafSplit(model, records, outcomes, leaves[leaf], leaf,
                              targetBins, minimumChild);
            if (candidate.valid &&
                (!best.valid || candidate.gain > best.gain + 1.0e-12)) {
                best = std::move(candidate);
            }
        }
        if (!best.valid) {
            break;
        }

        const size_t node = leaves[best.leaf].node;
        const int leftNode = static_cast<int>(tree.nodes.size());
        tree.nodes.push_back({});
        const int rightNode = static_cast<int>(tree.nodes.size());
        tree.nodes.push_back({});
        tree.nodes[node].feature = static_cast<int>(best.feature);
        tree.nodes[node].threshold = best.threshold;
        tree.nodes[node].left = leftNode;
        tree.nodes[node].right = rightNode;
        leaves[best.leaf] = {static_cast<size_t>(leftNode),
                             std::move(best.left)};
        leaves.push_back(
            {static_cast<size_t>(rightNode), std::move(best.right)});
    }

    for (size_t leaf = 0; leaf < leaves.size(); ++leaf) {
        tree.nodes[leaves[leaf].node].leaf = leaf;
    }
    tree.leafCount = leaves.size();
    return tree;
}

struct ClockFit {
    bool valid = false;
    int targetBins = 0;
    std::vector<double> primaryCuts;
    std::vector<FeatureTree> trees;
    std::vector<size_t> offsets;
    std::vector<double> probabilities;
    std::vector<double> cumulative;
    std::vector<double> means;
    std::vector<double> variances;
    std::vector<size_t> counts;
    size_t trainingRecords = 0;

    size_t classCount() const { return counts.size(); }

    size_t classify(const ModelSpec& model,
                    const TransitionRecord& record) const {
        const size_t base = static_cast<size_t>(
            std::upper_bound(primaryCuts.begin(), primaryCuts.end(),
                             primaryFeature(model, record)) -
            primaryCuts.begin());
        return offsets[base] + trees[base].classify(model, record);
    }
};

struct FittedModel {
    ModelSpec model{};
    Resolution resolution{};
    bool control = false;
    std::vector<ClockFit> clocks;
};

std::vector<double> quantileCuts(std::vector<double> values, int bins) {
    std::ranges::sort(values);
    std::vector<double> cuts;
    cuts.reserve(static_cast<size_t>(bins - 1));
    for (int bin = 1; bin < bins; ++bin) {
        const size_t index = static_cast<size_t>(bin) * values.size() /
                             static_cast<size_t>(bins);
        if (index == 0 || index >= values.size()) {
            continue;
        }
        const double cut = std::midpoint(values[index - 1], values[index]);
        if (cuts.empty() || cut > cuts.back()) {
            cuts.push_back(cut);
        }
    }
    return cuts;
}

FittedModel
fitModel(const ModelSpec& model, const Resolution& resolution, bool control,
         const std::vector<std::vector<const TransitionRecord*>>& training,
         int maxRemaining, double pseudocount) {
    FittedModel fit;
    fit.model = model;
    fit.resolution = resolution;
    fit.control = control;
    fit.clocks.resize(static_cast<size_t>(maxRemaining) + 1);

    for (int remaining = 1; remaining <= maxRemaining; ++remaining) {
        const std::vector<const TransitionRecord*>& records =
            training[static_cast<size_t>(remaining)];
        if (records.empty()) {
            continue;
        }

        ClockFit& clock = fit.clocks[static_cast<size_t>(remaining)];
        clock.valid = true;
        clock.targetBins = resolution.targetBins;
        clock.trainingRecords = records.size();
        std::vector<double> primary;
        std::vector<double> outcomes;
        primary.reserve(records.size());
        outcomes.reserve(records.size());
        for (const TransitionRecord* record : records) {
            primary.push_back(primaryFeature(model, *record));
            outcomes.push_back(control ? record->controlZ : record->z);
        }
        clock.primaryCuts =
            quantileCuts(std::move(primary), resolution.baseBins);
        const size_t baseCount = clock.primaryCuts.size() + 1;
        std::vector<std::vector<size_t>> baseRows(baseCount);
        for (size_t row = 0; row < records.size(); ++row) {
            const size_t base = static_cast<size_t>(
                std::upper_bound(clock.primaryCuts.begin(),
                                 clock.primaryCuts.end(),
                                 primaryFeature(model, *records[row])) -
                clock.primaryCuts.begin());
            baseRows[base].push_back(row);
        }

        clock.trees.reserve(baseCount);
        clock.offsets.resize(baseCount);
        size_t classCount = 0;
        for (size_t base = 0; base < baseCount; ++base) {
            clock.offsets[base] = classCount;
            FeatureTree tree = buildFeatureTree(
                model, records, outcomes, std::move(baseRows[base]),
                auxiliaryFeatureCount(model) == 0 ? 1 : resolution.auxLeaves,
                resolution.targetBins);
            classCount += tree.leafCount;
            clock.trees.push_back(std::move(tree));
        }

        clock.counts.assign(classCount, 0);
        clock.probabilities.assign(
            classCount * static_cast<size_t>(resolution.targetBins), 0.0);
        for (size_t row = 0; row < records.size(); ++row) {
            const size_t classIndex = clock.classify(model, *records[row]);
            ++clock.counts[classIndex];
            ++clock.probabilities[classIndex * static_cast<size_t>(
                                                   resolution.targetBins) +
                                  targetBin(outcomes[row],
                                            resolution.targetBins)];
        }
        for (size_t classIndex = 0; classIndex < classCount; ++classIndex) {
            const double denominator =
                static_cast<double>(clock.counts[classIndex]) +
                pseudocount * static_cast<double>(resolution.targetBins);
            for (int bin = 0; bin < resolution.targetBins; ++bin) {
                double& probability =
                    clock
                        .probabilities[classIndex * static_cast<size_t>(
                                                        resolution.targetBins) +
                                       static_cast<size_t>(bin)];
                probability = (probability + pseudocount) / denominator;
            }
        }
        const size_t bins = static_cast<size_t>(resolution.targetBins);
        clock.cumulative.assign(classCount * (bins + 1), 0.0);
        clock.means.assign(classCount, 0.0);
        clock.variances.assign(classCount, 0.0);
        for (size_t classIndex = 0; classIndex < classCount; ++classIndex) {
            const size_t probabilityOffset = classIndex * bins;
            const size_t cumulativeOffset = classIndex * (bins + 1);
            double second = 0.0;
            for (size_t bin = 0; bin < bins; ++bin) {
                const double probability =
                    clock.probabilities[probabilityOffset + bin];
                const double lower =
                    static_cast<double>(bin) / static_cast<double>(bins);
                const double upper =
                    static_cast<double>(bin + 1) / static_cast<double>(bins);
                clock.cumulative[cumulativeOffset + bin + 1] =
                    clock.cumulative[cumulativeOffset + bin] + probability;
                clock.means[classIndex] +=
                    probability * std::midpoint(lower, upper);
                second += probability *
                          (lower * lower + lower * upper + upper * upper) / 3.0;
            }
            clock.variances[classIndex] =
                second - clock.means[classIndex] * clock.means[classIndex];
        }
    }
    return fit;
}

struct ModelFits {
    std::vector<FittedModel> finite;
    std::vector<FittedModel> control;
};

ModelFits
fitModels(const Resolution& resolution,
          const std::vector<std::vector<const TransitionRecord*>>& clocks,
          int maxRemaining, double pseudocount, size_t threadCount) {
    ModelFits fits{std::vector<FittedModel>(kModels.size()),
                   std::vector<FittedModel>(kModels.size())};
    const size_t taskCount = 2 * kModels.size();
    std::atomic<size_t> next{0};
    std::exception_ptr failure;
    std::mutex failureMutex;

    auto worker = [&] {
        try {
            while (true) {
                const size_t task =
                    next.fetch_add(1, std::memory_order_relaxed);
                if (task >= taskCount) {
                    return;
                }
                const bool control = task >= kModels.size();
                const size_t model = task % kModels.size();
                FittedModel fit = fitModel(kModels[model], resolution, control,
                                           clocks, maxRemaining, pseudocount);
                if (control) {
                    fits.control[model] = std::move(fit);
                } else {
                    fits.finite[model] = std::move(fit);
                }
            }
        } catch (...) {
            std::scoped_lock lock(failureMutex);
            if (!failure) {
                failure = std::current_exception();
            }
            next.store(taskCount, std::memory_order_relaxed);
        }
    };

    const size_t workers = std::min(threadCount, taskCount);
    std::vector<std::thread> threads;
    threads.reserve(workers);
    for (size_t index = 0; index < workers; ++index) {
        threads.emplace_back(worker);
    }
    for (std::thread& thread : threads) {
        thread.join();
    }
    if (failure) {
        std::rethrow_exception(failure);
    }
    return fits;
}

struct Prediction {
    double logDensity = 0.0;
    double cdf = 0.0;
    double mean = 0.0;
    double variance = 0.0;
};

Prediction histogramPrediction(const ClockFit& clock, size_t classIndex,
                               double value) {
    const size_t bins = static_cast<size_t>(clock.targetBins);
    const size_t probabilityOffset = classIndex * bins;
    const size_t cumulativeOffset = classIndex * (bins + 1);
    const size_t bin = targetBin(value, clock.targetBins);
    const double local =
        value * static_cast<double>(bins) - static_cast<double>(bin);
    Prediction result;
    result.logDensity = std::log(clock.probabilities[probabilityOffset + bin] *
                                 static_cast<double>(bins));
    result.cdf = clock.cumulative[cumulativeOffset + bin] +
                 local * clock.probabilities[probabilityOffset + bin];
    result.mean = clock.means[classIndex];
    result.variance = clock.variances[classIndex];
    return result;
}

double histogramCdf(const ClockFit& clock, size_t classIndex, double value) {
    if (value <= 0.0) {
        return 0.0;
    }
    if (value >= 1.0) {
        return 1.0;
    }
    const size_t bins = static_cast<size_t>(clock.targetBins);
    const size_t probabilityOffset = classIndex * bins;
    const size_t cumulativeOffset = classIndex * (bins + 1);
    const size_t bin = targetBin(value, clock.targetBins);
    const double local =
        value * static_cast<double>(bins) - static_cast<double>(bin);
    return clock.cumulative[cumulativeOffset + bin] +
           local * clock.probabilities[probabilityOffset + bin];
}

double betaCdf(int remaining, double value) {
    if (value <= 0.0) {
        return 0.0;
    }
    if (value >= 1.0) {
        return 1.0;
    }
    const double second = static_cast<double>(2 * remaining - 1);
    const double logSurvival =
        second * std::log1p(-value) + std::log1p(second * value);
    return -std::expm1(logSurvival);
}

Prediction betaPrediction(int remaining, double value) {
    const double first = 2.0;
    const double second = static_cast<double>(2 * remaining - 1);
    Prediction result;
    result.logDensity = std::log(second * (second + 1.0)) + std::log(value) +
                        (second - 1.0) * std::log1p(-value);
    result.cdf = betaCdf(remaining, value);
    result.mean = first / (first + second);
    result.variance =
        first * second /
        ((first + second) * (first + second) * (first + second + 1.0));
    return result;
}

struct PairMoments {
    double sumX = 0.0;
    double sumY = 0.0;
    double sumXX = 0.0;
    double sumYY = 0.0;
    double sumXY = 0.0;
    size_t count = 0;

    void add(double x, double y) {
        sumX += x;
        sumY += y;
        sumXX += x * x;
        sumYY += y * y;
        sumXY += x * y;
        ++count;
    }

    double correlation() const {
        if (count < 2) {
            return 0.0;
        }
        const double n = static_cast<double>(count);
        const double covariance = sumXY - sumX * sumY / n;
        const double varianceX = sumXX - sumX * sumX / n;
        const double varianceY = sumYY - sumY * sumY / n;
        if (!(varianceX > 0.0) || !(varianceY > 0.0)) {
            return 0.0;
        }
        return covariance / std::sqrt(varianceX * varianceY);
    }
};

struct EmpiricalGroup {
    size_t remaining = 0;
    size_t count = 0;
    double sum = 0.0;
    double sumSquare = 0.0;
    std::vector<size_t> bins;
    std::vector<size_t> classCounts;
};

Metric evaluateModel(const FittedModel* fit, bool oracle,
                     std::span<const TransitionRecord* const> records,
                     size_t graphIndex, int horizon, size_t resolutionIndex,
                     const Resolution& resolution, bool control,
                     int referenceBins) {
    Metric metric;
    metric.graphIndex = graphIndex;
    metric.horizon = horizon;
    metric.resolutionIndex = resolutionIndex;
    metric.baseBins = resolution.baseBins;
    metric.auxLeaves = resolution.auxLeaves;
    metric.targetBins = resolution.targetBins;
    metric.model = oracle ? "continuum_oracle" : std::string(fit->model.name);
    metric.data = control ? "beta_control" : "finite_dag";

    std::vector<double> pits;
    pits.reserve(records.size());
    std::vector<EmpiricalGroup> groups(static_cast<size_t>(horizon) *
                                       kConditionalBins);
    for (size_t remaining = 1; remaining < static_cast<size_t>(horizon);
         ++remaining) {
        for (size_t xBin = 0; xBin < kConditionalBins; ++xBin) {
            groups[remaining * kConditionalBins + xBin].remaining = remaining;
        }
    }
    PairMoments pitX;
    PairMoments pitAge;
    PairMoments pitHistory;
    double sumPit = 0.0;
    double sumPitSquare = 0.0;
    double sumLogScore = 0.0;
    double sumMeanResidual = 0.0;
    double sumSecondResidual = 0.0;

    for (const TransitionRecord* record : records) {
        if (record->horizon != horizon) {
            continue;
        }
        const size_t remaining =
            static_cast<size_t>(record->horizon - record->position);
        const double value = control ? record->controlZ : record->z;
        Prediction prediction;
        size_t classIndex = 0;
        if (oracle) {
            prediction = betaPrediction(static_cast<int>(remaining), value);
        } else {
            const ClockFit& clock = fit->clocks[remaining];
            if (!clock.valid) {
                continue;
            }
            classIndex = clock.classify(fit->model, *record);
            prediction = histogramPrediction(clock, classIndex, value);
        }
        prediction.cdf = std::clamp(prediction.cdf, 0.0, 1.0);

        ++metric.recordCount;
        sumLogScore += prediction.logDensity;
        sumPit += prediction.cdf;
        sumPitSquare += prediction.cdf * prediction.cdf;
        pits.push_back(prediction.cdf);
        sumMeanResidual += value - prediction.mean;
        sumSecondResidual +=
            (value - prediction.mean) * (value - prediction.mean) -
            prediction.variance;
        pitX.add(prediction.cdf, record->x);
        pitAge.add(prediction.cdf, record->routeAge);
        pitHistory.add(prediction.cdf, record->latentQuadratic);

        const size_t xBin =
            std::min(static_cast<size_t>(record->x * kConditionalBins),
                     kConditionalBins - 1);
        EmpiricalGroup& group = groups[remaining * kConditionalBins + xBin];
        if (group.bins.empty()) {
            group.bins.assign(static_cast<size_t>(referenceBins), 0);
            if (!oracle) {
                group.classCounts.assign(fit->clocks[remaining].classCount(),
                                         0);
            }
        }
        ++group.count;
        group.sum += value;
        group.sumSquare += value * value;
        ++group.bins[targetBin(value, referenceBins)];
        if (!oracle) {
            ++group.classCounts[classIndex];
        }
    }

    if (metric.recordCount == 0) {
        return metric;
    }
    const double count = static_cast<double>(metric.recordCount);
    metric.logScore = sumLogScore / count;
    metric.pitMean = sumPit / count;
    metric.pitVariance = sumPitSquare / count - metric.pitMean * metric.pitMean;
    metric.meanResidual = sumMeanResidual / count;
    metric.secondResidual = sumSecondResidual / count;
    metric.pitXCorrelation = pitX.correlation();
    metric.pitAgeCorrelation = pitAge.correlation();
    metric.pitHistoryCorrelation = pitHistory.correlation();

    std::ranges::sort(pits);
    for (size_t index = 0; index < pits.size(); ++index) {
        const double lower = static_cast<double>(index) / count;
        const double upper = static_cast<double>(index + 1) / count;
        metric.pitKolmogorov = std::max(
            {metric.pitKolmogorov, upper - pits[index], pits[index] - lower});
    }

    double weightedWasserstein = 0.0;
    for (const EmpiricalGroup& group : groups) {
        if (group.count == 0) {
            continue;
        }
        size_t cumulative = 0;
        double distance = 0.0;
        for (int bin = 0; bin < referenceBins; ++bin) {
            cumulative += group.bins[static_cast<size_t>(bin)];
            const double empirical = static_cast<double>(cumulative) /
                                     static_cast<double>(group.count);
            const double boundary = static_cast<double>(bin + 1) /
                                    static_cast<double>(referenceBins);
            double predicted = 0.0;
            if (oracle) {
                predicted =
                    betaCdf(static_cast<int>(group.remaining), boundary);
            } else {
                const ClockFit& clock = fit->clocks[group.remaining];
                for (size_t classIndex = 0;
                     classIndex < group.classCounts.size(); ++classIndex) {
                    predicted +=
                        static_cast<double>(group.classCounts[classIndex]) *
                        histogramCdf(clock, classIndex, boundary);
                }
                predicted /= static_cast<double>(group.count);
            }
            distance += std::abs(empirical - predicted) /
                        static_cast<double>(referenceBins);
        }
        weightedWasserstein += distance * static_cast<double>(group.count);
    }
    metric.wasserstein = weightedWasserstein / count;

    for (size_t remaining = 1; remaining < static_cast<size_t>(horizon);
         ++remaining) {
        const Prediction beta =
            betaPrediction(static_cast<int>(remaining), 0.5);
        for (size_t xBin = 0; xBin < kConditionalBins; ++xBin) {
            const EmpiricalGroup& moment =
                groups[remaining * kConditionalBins + xBin];
            if (moment.count < 32) {
                continue;
            }
            const double n = static_cast<double>(moment.count);
            const double mean = moment.sum / n;
            const double variance = moment.sumSquare / n - mean * mean;
            metric.maxConditionalMeanError = std::max(
                metric.maxConditionalMeanError, std::abs(mean - beta.mean));
            metric.maxConditionalVarianceError =
                std::max(metric.maxConditionalVarianceError,
                         std::abs(variance - beta.variance));
        }
    }

    if (!oracle) {
        for (const ClockFit& clock : fit->clocks) {
            if (!clock.valid) {
                continue;
            }
            metric.trainingRecords += clock.trainingRecords;
            metric.realizedClasses += clock.classCount();
            for (size_t classCount : clock.counts) {
                if (classCount > 0 &&
                    (metric.minimumTrainingClass == 0 ||
                     classCount < metric.minimumTrainingClass)) {
                    metric.minimumTrainingClass = classCount;
                }
            }
        }
    }
    return metric;
}

std::vector<const TransitionRecord*>
trainingRecords(const std::vector<GraphRecords>& graphs, size_t heldOutFold) {
    std::vector<const TransitionRecord*> records;
    size_t count = 0;
    for (const GraphRecords& graph : graphs) {
        if (graph.index % 2 != heldOutFold) {
            count += graph.transitions.size();
        }
    }
    records.reserve(count);
    for (const GraphRecords& graph : graphs) {
        if (graph.index % 2 != heldOutFold) {
            for (const TransitionRecord& record : graph.transitions) {
                records.push_back(&record);
            }
        }
    }
    return records;
}

std::vector<std::vector<const TransitionRecord*>>
groupByClock(std::span<const TransitionRecord* const> records,
             int maxRemaining) {
    std::vector<std::vector<const TransitionRecord*>> clocks(
        static_cast<size_t>(maxRemaining) + 1);
    for (const TransitionRecord* record : records) {
        const size_t remaining =
            static_cast<size_t>(record->horizon - record->position);
        clocks[remaining].push_back(record);
    }
    return clocks;
}

std::vector<const TransitionRecord*> graphRecords(const GraphRecords& graph) {
    std::vector<const TransitionRecord*> records;
    records.reserve(graph.transitions.size());
    for (const TransitionRecord& record : graph.transitions) {
        records.push_back(&record);
    }
    return records;
}

std::vector<Metric> fitAndScore(const Options& options,
                                const std::vector<GraphRecords>& graphs,
                                size_t threadCount) {
    std::vector<Metric> metrics;
    const int maxRemaining = options.horizons.back() - 1;

    for (size_t resolutionIndex = 0;
         resolutionIndex < options.resolutions.size(); ++resolutionIndex) {
        const Resolution resolution = options.resolutions[resolutionIndex];
        for (size_t heldOutFold = 0; heldOutFold < 2; ++heldOutFold) {
            const std::vector<const TransitionRecord*> training =
                trainingRecords(graphs, heldOutFold);
            if (training.empty()) {
                throw std::runtime_error(
                    "cross-fit training fold has no transitions");
            }
            const std::vector<std::vector<const TransitionRecord*>> clocks =
                groupByClock(training, maxRemaining);
            const ModelFits fits = fitModels(resolution, clocks, maxRemaining,
                                             options.pseudocount, threadCount);

            std::vector<size_t> heldOut;
            for (size_t index = 0; index < graphs.size(); ++index) {
                if (graphs[index].index % 2 == heldOutFold) {
                    heldOut.push_back(index);
                }
            }
            std::vector<std::vector<Metric>> scored(graphs.size());
            std::atomic<size_t> next{0};
            std::exception_ptr failure;
            std::mutex failureMutex;
            auto worker = [&] {
                try {
                    while (true) {
                        const size_t task =
                            next.fetch_add(1, std::memory_order_relaxed);
                        if (task >= heldOut.size()) {
                            return;
                        }
                        const size_t graphIndex = heldOut[task];
                        const GraphRecords& graph = graphs[graphIndex];
                        const std::vector<const TransitionRecord*> records =
                            graphRecords(graph);
                        std::vector<Metric>& local = scored[graphIndex];
                        local.reserve(options.horizons.size() * 2 *
                                      (kModels.size() + 1));
                        for (int horizon : options.horizons) {
                            local.push_back(evaluateModel(
                                nullptr, true, records, graph.index, horizon,
                                resolutionIndex, resolution, false,
                                options.referenceBins));
                            local.push_back(evaluateModel(
                                nullptr, true, records, graph.index, horizon,
                                resolutionIndex, resolution, true,
                                options.referenceBins));
                            for (size_t model = 0; model < kModels.size();
                                 ++model) {
                                local.push_back(evaluateModel(
                                    &fits.finite[model], false, records,
                                    graph.index, horizon, resolutionIndex,
                                    resolution, false, options.referenceBins));
                                local.push_back(evaluateModel(
                                    &fits.control[model], false, records,
                                    graph.index, horizon, resolutionIndex,
                                    resolution, true, options.referenceBins));
                            }
                        }
                    }
                } catch (...) {
                    std::scoped_lock lock(failureMutex);
                    if (!failure) {
                        failure = std::current_exception();
                    }
                    next.store(heldOut.size(), std::memory_order_relaxed);
                }
            };

            const size_t workers = std::min(threadCount, heldOut.size());
            std::vector<std::thread> threads;
            threads.reserve(workers);
            for (size_t index = 0; index < workers; ++index) {
                threads.emplace_back(worker);
            }
            for (std::thread& thread : threads) {
                thread.join();
            }
            if (failure) {
                std::rethrow_exception(failure);
            }
            for (size_t graphIndex : heldOut) {
                metrics.insert(
                    metrics.end(),
                    std::make_move_iterator(scored[graphIndex].begin()),
                    std::make_move_iterator(scored[graphIndex].end()));
            }
        }
    }

    std::ranges::sort(metrics, [](const Metric& left, const Metric& right) {
        return std::tie(left.graphIndex, left.horizon, left.resolutionIndex,
                        left.model, left.data) <
               std::tie(right.graphIndex, right.horizon, right.resolutionIndex,
                        right.model, right.data);
    });
    return metrics;
}

void writeJsonString(std::ostream& out, std::string_view value) {
    out.put('"');
    for (char character : value) {
        switch (character) {
        case '"':
            out << "\\\"";
            break;
        case '\\':
            out << "\\\\";
            break;
        case '\n':
            out << "\\n";
            break;
        case '\r':
            out << "\\r";
            break;
        case '\t':
            out << "\\t";
            break;
        default:
            out.put(character);
            break;
        }
    }
    out.put('"');
}

void writeIntList(std::ostream& out, std::span<const int> values) {
    out.put('[');
    for (size_t index = 0; index < values.size(); ++index) {
        if (index > 0) {
            out.put(',');
        }
        out << values[index];
    }
    out.put(']');
}

std::ofstream openTemporary(const std::filesystem::path& path) {
    std::ofstream out(path.string() + ".tmp");
    if (!out) {
        throw std::runtime_error("cannot create output file: " + path.string());
    }
    out.precision(17);
    return out;
}

void commitTemporary(std::ofstream& out, const std::filesystem::path& path) {
    out.close();
    if (!out) {
        throw std::runtime_error("failed while writing output file: " +
                                 path.string());
    }
    std::filesystem::rename(path.string() + ".tmp", path);
}

void prepareOutput(const Options& options) {
    const std::array<std::string_view, 3> names{"run.json", "graphs.jsonl",
                                                "metrics.jsonl"};
    std::filesystem::create_directories(options.outputDirectory);
    for (std::string_view name : names) {
        const std::filesystem::path path = options.outputDirectory / name;
        if (std::filesystem::exists(path) && !options.overwrite) {
            throw std::runtime_error(
                "pass --overwrite to replace existing output: " +
                path.string());
        }
        std::filesystem::remove(path.string() + ".tmp");
    }
}

void writeRun(const Options& options, size_t effectiveThreads,
              double wallSeconds, size_t peakBytes) {
    const std::filesystem::path path = options.outputDirectory / "run.json";
    std::ofstream out = openTemporary(path);
    out << "{\n  \"schema\":\"bounded-systems.gap-finite-closure-run.v1\",\n";
    out << "  \"configuration\":{\"vertices\":" << options.vertexCount
        << ",\"horizons\":";
    writeIntList(out, options.horizons);
    out << ",\"samples\":" << options.sampleCount
        << ",\"paths_per_horizon\":" << options.pathsPerHorizon
        << ",\"master_seed\":\"" << options.seed << "\""
        << ",\"requested_threads\":" << options.threads
        << ",\"effective_threads\":" << effectiveThreads
        << ",\"reference_bins\":" << options.referenceBins
        << ",\"pseudocount\":" << options.pseudocount
        << ",\"output_directory\":";
    writeJsonString(
        out, std::filesystem::absolute(options.outputDirectory).string());
    out << "},\n  \"resolutions\":[";
    for (size_t index = 0; index < options.resolutions.size(); ++index) {
        if (index > 0) {
            out.put(',');
        }
        const Resolution& resolution = options.resolutions[index];
        out << "{\"base_bins\":" << resolution.baseBins
            << ",\"aux_leaves\":" << resolution.auxLeaves
            << ",\"target_bins\":" << resolution.targetBins << '}';
    }
    out << "],\n";
    out << "  \"generator\":{\"kernel\":\"(y-x)_+\","
           "\"marks\":\"counter-splitmix64-uniform53-v1\","
           "\"edge_stream\":\"counter-splitmix64-pair-v1\"},\n";
    out << "  \"route_sampling\":{\"law\":\"uniform fixed-length route\","
           "\"transition\":\"F_(m-1)(w)/F_m(v) on outgoing edges\","
           "\"path_stream\":\"splitmix64-sample-horizon-path-v1\"},\n";
    out << "  \"cross_fit\":{\"held_out_fold\":\"graph_index modulo 2\","
           "\"clock\":\"remaining edge count m\","
           "\"primary_bins\":\"training quantiles\","
           "\"auxiliary_partition\":\"greedy conditional-likelihood tree\","
           "\"uncertainty_unit\":\"held-out graph\"},\n";
    out << "  \"estimands\":{\"continuum_oracle\":\"Beta(2,2m-1)\","
           "\"intrinsic_mark\":\"1/2+(d_in-d_out)/N\","
           "\"transverse\":\"sqrt(N)(X_N-chi(intrinsic_mark))\","
           "\"target\":\"z=(x_(r+1)-x_r)/(1-x_r)\"},\n";
    out << "  \"model_features\":{"
           "\"latent\":[\"x\"],"
           "\"latent_age\":[\"x\",\"r/p\"],"
           "\"latent_history\":[\"x\",\"r/p\",\"x_(r-1)\","
           "\"(x_r-x_(r-1))/x_r\",\"sum_(j<=r)(Delta x_j/x_r)^2\"],"
           "\"intrinsic_mark\":[\"xhat\"],"
           "\"intrinsic_age\":[\"xhat\",\"r/p\"],"
           "\"intrinsic_history\":[\"xhat\",\"r/p\",\"xhat_(r-1)\","
           "\"Delta xhat_r\",\"sum_(j<=r)(Delta xhat_j)^2/(xhat_r^2+1/N)\"],"
           "\"full_state\":[\"xhat\",\"sqrt(N)(X_N(V_r)-chi(xhat_r))\"],"
           "\"full_age\":[\"xhat\",\"sqrt(N)(X_N(V_r)-chi(xhat_r))\",\"r/p\"],"
           "\"full_history\":[\"xhat\",\"sqrt(N)(X_N(V_r)-chi(xhat_r))\","
           "\"r/p\",\"xhat_(r-1)\",\"Delta xhat_r\","
           "\"sum_(j<=r)(Delta xhat_j)^2/(xhat_r^2+1/N)\","
           "\"sqrt(N)(X_N(V_(r-1))-chi(xhat_(r-1)))\"]},\n";
    out << "  \"metrics\":{\"log_score\":\"mean log predictive density\","
           "\"wasserstein\":\"held-out W1 on common (m,16-bin latent-x) "
           "audit strata and reference grid\","
           "\"pit_kolmogorov\":\"exact empirical CDF defect\"},\n";
    out << "  \"runtime\":{\"wall_seconds\":" << wallSeconds
        << ",\"max_sample_estimated_bytes\":" << peakBytes << "}\n}\n";
    commitTemporary(out, path);
}

void writeGraphs(const Options& options,
                 const std::vector<GraphRecords>& graphs) {
    const std::filesystem::path path = options.outputDirectory / "graphs.jsonl";
    std::ofstream out = openTemporary(path);
    for (const GraphRecords& graph : graphs) {
        out << "{\"schema\":\"bounded-systems.gap-finite-closure-graph.v1\","
            << "\"graph_index\":" << graph.index << ",\"sample_seed\":\""
            << graph.sampleSeed << "\",\"vertices\":" << options.vertexCount
            << ",\"edges\":" << graph.edgeCount
            << ",\"node_mark_rmse\":" << graph.nodeMarkRmse
            << ",\"node_mark_max_error\":" << graph.nodeMarkMaxError
            << ",\"estimated_bytes\":" << graph.estimatedBytes
            << ",\"seconds\":" << graph.seconds << ",\"horizons\":[";
        for (size_t index = 0; index < graph.horizons.size(); ++index) {
            if (index > 0) {
                out.put(',');
            }
            const HorizonGraphRecord& horizon = graph.horizons[index];
            out << "{\"horizon\":" << horizon.horizon
                << ",\"has_routes\":" << (horizon.hasRoutes ? "true" : "false")
                << ",\"paths\":" << horizon.paths << ",\"route_mark_rmse\":";
            if (horizon.hasRoutes) {
                out << horizon.routeMarkRmse;
            } else {
                out << "null";
            }
            out << ",\"log_route_count\":";
            if (horizon.hasRoutes) {
                out << static_cast<double>(horizon.logRouteCount);
            } else {
                out << "null";
            }
            out << '}';
        }
        out << "]}\n";
    }
    commitTemporary(out, path);
}

void writeMetrics(const Options& options, std::span<const Metric> metrics) {
    const std::filesystem::path path =
        options.outputDirectory / "metrics.jsonl";
    std::ofstream out = openTemporary(path);
    for (const Metric& metric : metrics) {
        out << "{\"schema\":\"bounded-systems.gap-finite-closure-metric.v1\","
            << "\"vertices\":" << options.vertexCount
            << ",\"graph_index\":" << metric.graphIndex
            << ",\"horizon\":" << metric.horizon
            << ",\"resolution_index\":" << metric.resolutionIndex
            << ",\"base_bins\":" << metric.baseBins
            << ",\"aux_leaves\":" << metric.auxLeaves
            << ",\"target_bins\":" << metric.targetBins << ",\"model\":";
        writeJsonString(out, metric.model);
        out << ",\"data\":";
        writeJsonString(out, metric.data);
        out << ",\"record_count\":" << metric.recordCount
            << ",\"training_records\":" << metric.trainingRecords
            << ",\"realized_classes\":" << metric.realizedClasses
            << ",\"minimum_training_class\":" << metric.minimumTrainingClass
            << ",\"log_score\":" << metric.logScore
            << ",\"wasserstein\":" << metric.wasserstein
            << ",\"pit_mean\":" << metric.pitMean
            << ",\"pit_variance\":" << metric.pitVariance
            << ",\"pit_kolmogorov\":" << metric.pitKolmogorov
            << ",\"mean_residual\":" << metric.meanResidual
            << ",\"second_residual\":" << metric.secondResidual
            << ",\"pit_x_correlation\":" << metric.pitXCorrelation
            << ",\"pit_age_correlation\":" << metric.pitAgeCorrelation
            << ",\"pit_history_correlation\":" << metric.pitHistoryCorrelation
            << ",\"max_conditional_mean_error\":"
            << metric.maxConditionalMeanError
            << ",\"max_conditional_variance_error\":"
            << metric.maxConditionalVarianceError << "}\n";
    }
    commitTemporary(out, path);
}

void requireCheck(bool condition, std::string_view message, size_t& checks) {
    ++checks;
    if (!condition) {
        throw std::runtime_error("self-test failed: " + std::string(message));
    }
}

size_t runSelfTests() {
    size_t checks = 0;
    for (int remaining = 1; remaining <= 8; ++remaining) {
        const Prediction prediction = betaPrediction(remaining, 0.37);
        const double mean = 2.0 / static_cast<double>(2 * remaining + 1);
        const double variance =
            2.0 * static_cast<double>(2 * remaining - 1) /
            (static_cast<double>((2 * remaining + 1) * (2 * remaining + 1) *
                                 (2 * remaining + 2)));
        requireCheck(std::abs(prediction.mean - mean) < 1.0e-15, "Beta mean",
                     checks);
        requireCheck(std::abs(prediction.variance - variance) < 1.0e-15,
                     "Beta variance", checks);
        requireCheck(prediction.cdf > 0.0 && prediction.cdf < 1.0,
                     "Beta CDF range", checks);
        requireCheck(std::abs(prediction.cdf -
                              boost::math::ibeta(
                                  2.0, static_cast<double>(2 * remaining - 1),
                                  0.37)) < 1.0e-14,
                     "Beta CDF formula", checks);
    }

    Rng rng(0x13bc729d05e641a7ULL);
    for (int remaining : {1, 2, 4, 8}) {
        constexpr size_t count = 100000;
        double sum = 0.0;
        double sumSquare = 0.0;
        for (size_t index = 0; index < count; ++index) {
            const double value = sampleBetaInteger(2, 2 * remaining - 1, rng);
            sum += value;
            sumSquare += value * value;
        }
        const double empiricalMean = sum / static_cast<double>(count);
        const Prediction exact = betaPrediction(remaining, 0.5);
        const double error =
            6.0 * std::sqrt(exact.variance / static_cast<double>(count));
        requireCheck(std::abs(empiricalMean - exact.mean) < error,
                     "Beta sampler mean", checks);
        requireCheck(sumSquare > 0.0, "Beta sampler second moment", checks);
    }

    const std::array<std::pair<uint32_t, uint32_t>, 5> edges{{
        {0, 1},
        {0, 2},
        {1, 3},
        {2, 3},
        {2, 4},
    }};
    const ReferenceDag tiny = ReferenceDag::fromTopologicalEdges(5, edges);
    const StableRouteCounts tinyRoutes = computeRouteCounts(tiny, 2);
    requireCheck(std::abs(tinyRoutes.forwardLogs[2] - std::log(3.0L)) <
                     1.0e-15L,
                 "tiny route count", checks);
    std::array<size_t, 3> routeCounts{};
    Rng routeRng(0x284d3971e6bc5a0fULL);
    constexpr size_t routeSamples = 60000;
    for (size_t index = 0; index < routeSamples; ++index) {
        const std::vector<uint32_t> path =
            sampleRoute(tiny, tinyRoutes, 2, routeRng);
        requireCheck(path.size() == 3, "tiny route length", checks);
        size_t category = 0;
        if (path[1] == 2 && path[2] == 3) {
            category = 1;
        } else if (path[1] == 2 && path[2] == 4) {
            category = 2;
        } else {
            requireCheck(path[1] == 1 && path[2] == 3, "tiny route support",
                         checks);
        }
        ++routeCounts[category];
    }
    for (size_t count : routeCounts) {
        const double frequency =
            static_cast<double>(count) / static_cast<double>(routeSamples);
        requireCheck(std::abs(frequency - 1.0 / 3.0) < 0.01,
                     "uniform tiny route frequency", checks);
    }

    Options options;
    options.vertexCount = 64;
    options.horizons = {4};
    options.sampleCount = 4;
    options.pathsPerHorizon = 200;
    options.seed = 20260817;
    options.threads = 1;
    options.resolutions = {{4, 2, 16}};
    options.referenceBins = 64;
    options.pseudocount = 0.5;
    std::vector<GraphRecords> graphs = sampleGraphs(options, 1);
    size_t transitionCount = 0;
    for (const GraphRecords& graph : graphs) {
        requireCheck(graph.horizons.front().hasRoutes,
                     "generated graph has four-edge routes", checks);
        transitionCount += graph.transitions.size();
        for (const TransitionRecord& record : graph.transitions) {
            requireCheck(record.z > 0.0 && record.z < 1.0,
                         "finite transition target range", checks);
            requireCheck(record.controlZ > 0.0 && record.controlZ < 1.0,
                         "control transition target range", checks);
        }
    }
    requireCheck(transitionCount ==
                     options.sampleCount * options.pathsPerHorizon * 3,
                 "route transition count", checks);
    const std::vector<Metric> metrics = fitAndScore(options, graphs, 1);
    requireCheck(metrics.size() == options.sampleCount * 20,
                 "cross-fit metric count", checks);
    for (const Metric& metric : metrics) {
        requireCheck(metric.recordCount == options.pathsPerHorizon * 3,
                     "held-out metric record count", checks);
        requireCheck(std::isfinite(metric.logScore) &&
                         std::isfinite(metric.wasserstein),
                     "finite held-out score", checks);
    }
    return checks;
}

} // namespace

int main(int argc, char** argv) {
    try {
        const std::span<char*> arguments(argv, static_cast<size_t>(argc));
        const Options options = parseOptions(arguments);
        if (options.help) {
            printUsage(arguments.front());
            return 0;
        }
        if (options.selfTest) {
            const size_t checks = runSelfTests();
            std::println(stderr,
                         "gap-finite-closure self-tests passed: {} checks",
                         checks);
            return 0;
        }

        prepareOutput(options);
        const size_t effectiveThreads =
            std::min(options.threads, options.sampleCount);
        const auto started = Clock::now();
        std::vector<GraphRecords> graphs =
            sampleGraphs(options, effectiveThreads);
        std::vector<Metric> metrics =
            fitAndScore(options, graphs, effectiveThreads);
        const double wallSeconds =
            std::chrono::duration<double>(Clock::now() - started).count();
        size_t peakBytes = 0;
        for (const GraphRecords& graph : graphs) {
            peakBytes = std::max(peakBytes, graph.estimatedBytes);
        }

        writeRun(options, effectiveThreads, wallSeconds, peakBytes);
        writeGraphs(options, graphs);
        writeMetrics(options, metrics);
        std::println(stderr,
                     "completed samples={} vertices={} paths={} threads={} "
                     "metrics={} wall_seconds={:.6f}",
                     options.sampleCount, options.vertexCount,
                     options.pathsPerHorizon, effectiveThreads, metrics.size(),
                     wallSeconds);
        return 0;
    } catch (const std::exception& error) {
        std::println(stderr, "fatal: {}", error.what());
        printUsage(argc > 0 ? argv[0] : "gap-finite-closure");
        return 2;
    }
}
