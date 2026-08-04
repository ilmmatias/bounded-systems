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
#include <format>
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
    size_t sampleIndex = 0;
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
    for (int i = 0; i < firstShape; ++i) {
        first -= std::log(rng.uniformOpen());
    }
    for (int i = 0; i < secondShape; ++i) {
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
    const std::string copy(text);
    size_t used = 0;
    const double value = std::stod(copy, &used);
    if (used != copy.size() || !std::isfinite(value)) {
        throw std::invalid_argument(std::string(option) +
                                    " requires a finite number");
    }
    return value;
}

std::string_view requireValue(std::span<char*> args, size_t& i,
                              std::string_view option) {
    if (i + 1 >= args.size()) {
        throw std::invalid_argument(std::string(option) + " requires a value");
    }
    return args[++i];
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

Options parseOptions(std::span<char*> args) {
    Options opt;
    std::vector<int> baseBins{8, 16, 32};
    std::vector<int> auxLeaves{2, 2, 2};
    std::vector<int> targetBins{32, 64, 128};

    for (size_t i = 1; i < args.size(); ++i) {
        const std::string_view name = args[i];

        if (name == "--vertices") {
            opt.vertexCount =
                parseInteger<size_t>(requireValue(args, i, name), name);
            continue;
        }

        if (name == "--horizons") {
            opt.horizons = parseList(requireValue(args, i, name), name);
            continue;
        }

        if (name == "--samples") {
            opt.sampleCount =
                parseInteger<size_t>(requireValue(args, i, name), name);
            continue;
        }

        if (name == "--paths") {
            opt.pathsPerHorizon =
                parseInteger<size_t>(requireValue(args, i, name), name);
            continue;
        }

        if (name == "--seed") {
            opt.seed =
                parseInteger<uint64_t>(requireValue(args, i, name), name);
            continue;
        }

        if (name == "--threads") {
            opt.threads =
                parseInteger<size_t>(requireValue(args, i, name), name);
            continue;
        }

        if (name == "--output") {
            opt.outputDirectory = requireValue(args, i, name);
            continue;
        }

        if (name == "--base-bins") {
            baseBins = parseList(requireValue(args, i, name), name);
            continue;
        }

        if (name == "--aux-leaves") {
            auxLeaves = parseList(requireValue(args, i, name), name);
            continue;
        }

        if (name == "--target-bins") {
            targetBins = parseList(requireValue(args, i, name), name);
            continue;
        }

        if (name == "--reference-bins") {
            opt.referenceBins =
                parseInteger<int>(requireValue(args, i, name), name);
            continue;
        }

        if (name == "--pseudocount") {
            opt.pseudocount = parseDouble(requireValue(args, i, name), name);
            continue;
        }

        if (name == "--overwrite") {
            opt.overwrite = true;
            continue;
        }

        if (name == "--self-test") {
            opt.selfTest = true;
            continue;
        }

        if (name == "--help") {
            opt.help = true;
            return opt;
        }

        throw std::invalid_argument("unknown option: " + std::string(name));
    }

    if (opt.selfTest || opt.help) {
        return opt;
    }

    if (opt.vertexCount < 2) {
        throw std::invalid_argument("--vertices must be at least two");
    }

    if (opt.horizons.empty()) {
        throw std::invalid_argument("--horizons is required");
    }

    std::ranges::sort(opt.horizons);

    if (std::ranges::adjacent_find(opt.horizons) != opt.horizons.end() ||
        opt.horizons.front() < 2 || opt.horizons.back() > 65535) {
        throw std::invalid_argument(
            "--horizons must contain distinct integers in 2..65535");
    }

    if (opt.sampleCount < 4) {
        throw std::invalid_argument("--samples must be at least four");
    }

    if (opt.pathsPerHorizon == 0) {
        throw std::invalid_argument("--paths must be positive");
    }

    if (opt.threads == 0) {
        throw std::invalid_argument("--threads must be positive");
    }

    if (opt.outputDirectory.empty()) {
        throw std::invalid_argument("--output is required");
    }

    if (baseBins.empty() || baseBins.size() != auxLeaves.size() ||
        baseBins.size() != targetBins.size()) {
        throw std::invalid_argument(
            "--base-bins, --aux-leaves, and --target-bins must have equal "
            "lengths");
    }

    if (opt.referenceBins < 64 || opt.referenceBins > 4096) {
        throw std::invalid_argument("--reference-bins must be in 64..4096");
    }

    if (!(opt.pseudocount > 0.0)) {
        throw std::invalid_argument("--pseudocount must be positive");
    }

    for (size_t i = 0; i < baseBins.size(); ++i) {
        if (baseBins[i] < 2 || baseBins[i] > 256 || auxLeaves[i] < 1 ||
            auxLeaves[i] > 16 || targetBins[i] < 8 || targetBins[i] > 1024) {
            throw std::invalid_argument(
                "resolution entries exceed their permitted ranges");
        }

        opt.resolutions.push_back({baseBins[i], auxLeaves[i], targetBins[i]});
    }

    return opt;
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
    for (size_t i = 0; i < weights.size(); ++i) {
        cumulative += weights[i];
        if (target < cumulative) {
            return i;
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
    std::array<double, kGapCoordinateCount> out{};
    for (size_t i = 0; i < out.size(); ++i) {
        out[i] = rootVertexCount * (coordinate[i] - reference[i]);
    }
    return out;
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
            record.graphIndex = static_cast<uint32_t>(sample.sampleIndex);
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

GraphRecords sampleGraph(const Options& opt, size_t sampleIndex) {
    const auto started = Clock::now();
    GraphRecords sample;
    sample.sampleIndex = sampleIndex;
    sample.sampleSeed = deriveGapSampleSeed(opt.seed, sampleIndex);

    const ReferenceDag graph =
        ReferenceDag::generate(opt.vertexCount, sample.sampleSeed);
    const GapNodeState state = computeGapNodeState(graph);
    const LatentStateValidation validation = validateGapNodeState(graph, state);
    sample.nodeMarkRmse = validation.reconstructedMarkRmse;
    sample.nodeMarkMaxError = validation.reconstructedMarkMaxError;
    const StableRouteCounts routes =
        computeRouteCounts(graph, static_cast<size_t>(opt.horizons.back()));
    sample.edgeCount = graph.edgeCount();
    sample.estimatedBytes = graph.estimatedBytes() + state.estimatedBytes() +
                            routes.estimatedBytes();

    for (const int horizon : opt.horizons) {
        HorizonGraphRecord horizonRecord;
        horizonRecord.horizon = horizon;
        horizonRecord.hasRoutes =
            routes.hasRoutes(static_cast<size_t>(horizon));
        horizonRecord.logRouteCount =
            horizonRecord.hasRoutes
                ? routes.forwardLogs[static_cast<size_t>(horizon)]
                : -std::numeric_limits<long double>::infinity();
        horizonRecord.paths = horizonRecord.hasRoutes ? opt.pathsPerHorizon : 0;
        if (horizonRecord.hasRoutes) {
            const size_t first = sample.transitions.size();
            appendTransitions(sample, graph, state, routes, horizon,
                              opt.pathsPerHorizon, sample.sampleSeed);
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

std::vector<GraphRecords> sampleGraphs(const Options& opt, size_t threadCount) {
    std::vector<GraphRecords> graphs(opt.sampleCount);
    std::atomic<size_t> next{0};
    std::exception_ptr failure;
    std::mutex failureMutex;

    auto worker = [&failure, &failureMutex, &graphs, &next, &opt] {
        try {
            while (true) {
                const size_t i = next.fetch_add(1, std::memory_order_relaxed);
                if (i >= opt.sampleCount) {
                    return;
                }

                graphs[i] = sampleGraph(opt, i);
            }
        } catch (...) {
            const std::scoped_lock lock(failureMutex);
            if (!failure) {
                failure = std::current_exception();
            }
            next.store(opt.sampleCount, std::memory_order_relaxed);
        }
    };

    std::vector<std::thread> workers;
    workers.reserve(threadCount);

    for (size_t i = 0; i < threadCount; ++i) {
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
                        size_t feature) {
    switch (model.kind) {
    case ModelKind::latent:
    case ModelKind::intrinsic:
        break;
    case ModelKind::latentAge:
    case ModelKind::intrinsicAge:
        if (feature == 0) {
            return record.routeAge;
        }
        break;
    case ModelKind::latentHistory:
        if (feature == 0) {
            return record.routeAge;
        }
        if (feature == 1) {
            return record.previousX;
        }
        if (feature == 2) {
            return record.latentLastFraction;
        }
        if (feature == 3) {
            return record.latentQuadratic;
        }
        break;
    case ModelKind::intrinsicHistory:
        if (feature == 0) {
            return record.routeAge;
        }
        if (feature == 1) {
            return record.previousIntrinsicX;
        }
        if (feature == 2) {
            return record.intrinsicLast;
        }
        if (feature == 3) {
            return record.intrinsicQuadratic;
        }
        break;
    case ModelKind::fullState:
        if (feature < kGapCoordinateCount) {
            return record.transverse[feature];
        }
        break;
    case ModelKind::fullAge:
        if (feature < kGapCoordinateCount) {
            return record.transverse[feature];
        }
        if (feature == kGapCoordinateCount) {
            return record.routeAge;
        }
        break;
    case ModelKind::fullHistory:
        if (feature < kGapCoordinateCount) {
            return record.transverse[feature];
        }
        if (feature == kGapCoordinateCount) {
            return record.routeAge;
        }
        if (feature == kGapCoordinateCount + 1) {
            return record.previousIntrinsicX;
        }
        if (feature == kGapCoordinateCount + 2) {
            return record.intrinsicLast;
        }
        if (feature == kGapCoordinateCount + 3) {
            return record.intrinsicQuadratic;
        }
        if (feature >= kGapCoordinateCount + 4 &&
            feature < 2 * kGapCoordinateCount + 4) {
            return record.previousTransverse[feature - kGapCoordinateCount - 4];
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
    bool found = false;
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
    double score = 0.0;
    for (const size_t count : counts) {
        if (count > 0) {
            score += static_cast<double>(count) *
                     std::log(static_cast<double>(count) /
                              static_cast<double>(total));
        }
    }
    return score;
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
    for (const size_t row : leaf.rows) {
        ++parentCounts[targetBin(outcomes[row], targetBins)];
    }
    const double parentLikelihood = multinomialLogLikelihood(parentCounts);
    const size_t featureCount = auxiliaryFeatureCount(model);

    for (size_t feature = 0; feature < featureCount; ++feature) {
        std::vector<size_t> sorted = leaf.rows;
        std::ranges::sort(sorted, [&model, &records, feature](size_t left,
                                                              size_t right) {
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
            for (const size_t numerator : {size_t{1}, size_t{2}, size_t{3}}) {
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

        for (const size_t split : candidates) {
            const double lower =
                auxiliaryFeature(model, *records[sorted[split - 1]], feature);
            const double upper =
                auxiliaryFeature(model, *records[sorted[split]], feature);
            if (!(lower < upper)) {
                throw std::logic_error("candidate is not a feature boundary");
            }

            std::vector<size_t> leftCounts(static_cast<size_t>(targetBins), 0);
            std::vector<size_t> rightCounts(static_cast<size_t>(targetBins), 0);
            for (size_t i = 0; i < split; ++i) {
                ++leftCounts[targetBin(outcomes[sorted[i]], targetBins)];
            }

            for (size_t i = split; i < sorted.size(); ++i) {
                ++rightCounts[targetBin(outcomes[sorted[i]], targetBins)];
            }
            const double gain = multinomialLogLikelihood(leftCounts) +
                                multinomialLogLikelihood(rightCounts) -
                                parentLikelihood;
            if (!best.found || gain > best.gain + 1.0e-12) {
                best.found = true;
                best.feature = feature;
                best.threshold = std::midpoint(lower, upper);
                best.gain = gain;
                best.left.assign(sorted.begin(),
                                 sorted.begin() +
                                     static_cast<ptrdiff_t>(split));
                best.right.assign(sorted.begin() +
                                      static_cast<ptrdiff_t>(split),
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
            if (candidate.found &&
                (!best.found || candidate.gain > best.gain + 1.0e-12)) {
                best = std::move(candidate);
            }
        }
        if (!best.found) {
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
    bool hasData = false;
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
        const size_t pos = static_cast<size_t>(bin) * values.size() /
                           static_cast<size_t>(bins);
        if (pos == 0 || pos >= values.size()) {
            continue;
        }

        const double cut = std::midpoint(values[pos - 1], values[pos]);
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
        clock.hasData = true;
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

    auto worker = [&clocks, &failure, &failureMutex, &fits, &next, &resolution,
                   maxRemaining, pseudocount] {
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
            const std::scoped_lock lock(failureMutex);
            if (!failure) {
                failure = std::current_exception();
            }
            next.store(taskCount, std::memory_order_relaxed);
        }
    };

    const size_t workers = std::min(threadCount, taskCount);
    std::vector<std::thread> threads;
    threads.reserve(workers);

    for (size_t i = 0; i < workers; ++i) {
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
    Prediction out;
    out.logDensity = std::log(clock.probabilities[probabilityOffset + bin] *
                              static_cast<double>(bins));
    out.cdf = clock.cumulative[cumulativeOffset + bin] +
              local * clock.probabilities[probabilityOffset + bin];
    out.mean = clock.means[classIndex];
    out.variance = clock.variances[classIndex];
    return out;
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
    Prediction out;
    out.logDensity = std::log(second * (second + 1.0)) + std::log(value) +
                     (second - 1.0) * std::log1p(-value);
    out.cdf = betaCdf(remaining, value);
    out.mean = first / (first + second);
    out.variance =
        first * second /
        ((first + second) * (first + second) * (first + second + 1.0));
    return out;
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
            if (!clock.hasData) {
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
    for (size_t i = 0; i < pits.size(); ++i) {
        const double lower = static_cast<double>(i) / count;
        const double upper = static_cast<double>(i + 1) / count;
        metric.pitKolmogorov =
            std::max({metric.pitKolmogorov, upper - pits[i], pits[i] - lower});
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
            if (!clock.hasData) {
                continue;
            }
            metric.trainingRecords += clock.trainingRecords;
            metric.realizedClasses += clock.classCount();
            for (const size_t classCount : clock.counts) {
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
        if (graph.sampleIndex % 2 != heldOutFold) {
            count += graph.transitions.size();
        }
    }
    records.reserve(count);
    for (const GraphRecords& graph : graphs) {
        if (graph.sampleIndex % 2 != heldOutFold) {
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

std::vector<Metric> fitAndScore(const Options& opt,
                                const std::vector<GraphRecords>& graphs,
                                size_t threadCount) {
    std::vector<Metric> metrics;
    const int maxRemaining = opt.horizons.back() - 1;

    for (size_t resolutionIndex = 0; resolutionIndex < opt.resolutions.size();
         ++resolutionIndex) {
        const Resolution resolution = opt.resolutions[resolutionIndex];
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
                                             opt.pseudocount, threadCount);

            std::vector<size_t> heldOut;
            for (size_t i = 0; i < graphs.size(); ++i) {
                if (graphs[i].sampleIndex % 2 == heldOutFold) {
                    heldOut.push_back(i);
                }
            }
            std::vector<std::vector<Metric>> scored(graphs.size());
            std::atomic<size_t> next{0};
            std::exception_ptr failure;
            std::mutex failureMutex;
            auto worker = [&failure, &failureMutex, &fits, &graphs, &heldOut,
                           &next, &opt, &resolution, &scored, resolutionIndex] {
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
                        local.reserve(opt.horizons.size() * 2 *
                                      (kModels.size() + 1));

                        for (const int horizon : opt.horizons) {
                            local.push_back(evaluateModel(
                                nullptr, true, records, graph.sampleIndex,
                                horizon, resolutionIndex, resolution, false,
                                opt.referenceBins));
                            local.push_back(evaluateModel(
                                nullptr, true, records, graph.sampleIndex,
                                horizon, resolutionIndex, resolution, true,
                                opt.referenceBins));
                            for (size_t model = 0; model < kModels.size();
                                 ++model) {
                                local.push_back(evaluateModel(
                                    &fits.finite[model], false, records,
                                    graph.sampleIndex, horizon, resolutionIndex,
                                    resolution, false, opt.referenceBins));
                                local.push_back(evaluateModel(
                                    &fits.control[model], false, records,
                                    graph.sampleIndex, horizon, resolutionIndex,
                                    resolution, true, opt.referenceBins));
                            }
                        }
                    }
                } catch (...) {
                    const std::scoped_lock lock(failureMutex);
                    if (!failure) {
                        failure = std::current_exception();
                    }
                    next.store(heldOut.size(), std::memory_order_relaxed);
                }
            };

            const size_t workers = std::min(threadCount, heldOut.size());
            std::vector<std::thread> threads;
            threads.reserve(workers);

            for (size_t i = 0; i < workers; ++i) {
                threads.emplace_back(worker);
            }

            for (std::thread& thread : threads) {
                thread.join();
            }

            if (failure) {
                std::rethrow_exception(failure);
            }

            for (const size_t graphIndex : heldOut) {
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

void printText(std::ostream& out, std::string_view text) {
    std::print(out, "{}", text);
}

void printNumber(std::ostream& out, double value) {
    std::print(out, "{:.17g}", value);
}

void writeJsonString(std::ostream& out, std::string_view value) {
    printText(out, "\"");

    for (char character : value) {
        switch (character) {
        case '"':
            printText(out, "\\\"");
            break;
        case '\\':
            printText(out, "\\\\");
            break;
        case '\n':
            printText(out, "\\n");
            break;
        case '\r':
            printText(out, "\\r");
            break;
        case '\t':
            printText(out, "\\t");
            break;
        default:
            std::print(out, "{}", character);
            break;
        }
    }

    printText(out, "\"");
}

void writeIntList(std::ostream& out, std::span<const int> values) {
    printText(out, "[");

    for (size_t i = 0; i < values.size(); ++i) {
        if (i != 0) {
            printText(out, ",");
        }

        std::print(out, "{}", values[i]);
    }

    printText(out, "]");
}

std::filesystem::path tempPath(const std::filesystem::path& path) {
    std::filesystem::path temp = path;
    temp += ".tmp";
    return temp;
}

std::ofstream openTemporary(const std::filesystem::path& path) {
    const std::filesystem::path temp = tempPath(path);
    std::ofstream out(temp);

    if (!out) {
        throw std::runtime_error(
            std::format("cannot create artifact: {}", temp.string()));
    }

    return out;
}

void commitTemporary(std::ofstream& out, const std::filesystem::path& path) {
    out.close();

    if (!out) {
        throw std::runtime_error(
            std::format("failed while writing artifact: {}", path.string()));
    }

    std::filesystem::rename(tempPath(path), path);
}

void prepareOutput(const Options& opt) {
    constexpr std::array<std::string_view, 3> names{
        "run.json",
        "graphs.jsonl",
        "metrics.jsonl",
    };

    std::filesystem::create_directories(opt.outputDirectory);

    for (const std::string_view name : names) {
        const std::filesystem::path path = opt.outputDirectory / name;
        if (std::filesystem::exists(path) && !opt.overwrite) {
            throw std::runtime_error(
                std::format("pass --overwrite to replace existing output: {}",
                            path.string()));
        }

        std::filesystem::remove(tempPath(path));
    }
}

void writeRun(const Options& opt, size_t effectiveThreads, double wallSeconds,
              size_t peakBytes) {
    const std::filesystem::path path = opt.outputDirectory / "run.json";
    std::ofstream out = openTemporary(path);

    std::print(out,
               "{{\n"
               "  \"schema\":\"bounded-systems.gap-finite-closure-run.v1\",\n"
               "  \"configuration\":{{\"vertices\":{},\"horizons\":",
               opt.vertexCount);
    writeIntList(out, opt.horizons);
    std::print(out,
               ",\"samples\":{},\"paths_per_horizon\":{},"
               "\"master_seed\":\"{}\",\"requested_threads\":{},"
               "\"effective_threads\":{},\"reference_bins\":{},"
               "\"pseudocount\":{:.17g},\"output_directory\":",
               opt.sampleCount, opt.pathsPerHorizon, opt.seed, opt.threads,
               effectiveThreads, opt.referenceBins, opt.pseudocount);
    writeJsonString(out,
                    std::filesystem::absolute(opt.outputDirectory).string());
    printText(out, "},\n  \"resolutions\":[");

    for (size_t i = 0; i < opt.resolutions.size(); ++i) {
        if (i != 0) {
            printText(out, ",");
        }

        const Resolution& resolution = opt.resolutions[i];
        std::print(out,
                   "{{\"base_bins\":{},\"aux_leaves\":{},"
                   "\"target_bins\":{}}}",
                   resolution.baseBins, resolution.auxLeaves,
                   resolution.targetBins);
    }

    printText(out, "],\n");
    printText(out, "  \"generator\":{\"kernel\":\"(y-x)_+\","
                   "\"marks\":\"counter-splitmix64-uniform53-v1\","
                   "\"edge_stream\":\"counter-splitmix64-pair-v1\"},\n");
    printText(out, "  \"route_sampling\":{"
                   "\"law\":\"uniform fixed-length route\","
                   "\"transition\":\"F_(m-1)(w)/F_m(v) on outgoing edges\","
                   "\"path_stream\":\"splitmix64-sample-horizon-path-v1\"},\n");
    printText(out, "  \"cross_fit\":{\"held_out_fold\":"
                   "\"graph_index modulo 2\","
                   "\"clock\":\"remaining edge count m\","
                   "\"primary_bins\":\"training quantiles\","
                   "\"auxiliary_partition\":"
                   "\"greedy conditional-likelihood tree\","
                   "\"uncertainty_unit\":\"held-out graph\"},\n");
    printText(out, "  \"estimands\":{\"continuum_oracle\":"
                   "\"Beta(2,2m-1)\","
                   "\"intrinsic_mark\":\"1/2+(d_in-d_out)/N\","
                   "\"transverse\":"
                   "\"sqrt(N)(X_N-chi(intrinsic_mark))\","
                   "\"target\":\"z=(x_(r+1)-x_r)/(1-x_r)\"},\n");
    printText(out, "  \"model_features\":{"
                   "\"latent\":[\"x\"],"
                   "\"latent_age\":[\"x\",\"r/p\"],"
                   "\"latent_history\":[\"x\",\"r/p\",\"x_(r-1)\","
                   "\"(x_r-x_(r-1))/x_r\","
                   "\"sum_(j<=r)(Delta x_j/x_r)^2\"],"
                   "\"intrinsic_mark\":[\"xhat\"],"
                   "\"intrinsic_age\":[\"xhat\",\"r/p\"],"
                   "\"intrinsic_history\":[\"xhat\",\"r/p\","
                   "\"xhat_(r-1)\",\"Delta xhat_r\","
                   "\"sum_(j<=r)(Delta xhat_j)^2/(xhat_r^2+1/N)\"],"
                   "\"full_state\":[\"xhat\","
                   "\"sqrt(N)(X_N(V_r)-chi(xhat_r))\"],"
                   "\"full_age\":[\"xhat\","
                   "\"sqrt(N)(X_N(V_r)-chi(xhat_r))\",\"r/p\"],"
                   "\"full_history\":[\"xhat\","
                   "\"sqrt(N)(X_N(V_r)-chi(xhat_r))\",\"r/p\","
                   "\"xhat_(r-1)\",\"Delta xhat_r\","
                   "\"sum_(j<=r)(Delta xhat_j)^2/(xhat_r^2+1/N)\","
                   "\"sqrt(N)(X_N(V_(r-1))-chi(xhat_(r-1)))\"]},\n");
    printText(out, "  \"metrics\":{\"log_score\":"
                   "\"mean log predictive density\","
                   "\"wasserstein\":"
                   "\"held-out W1 on common (m,16-bin latent-x) audit strata "
                   "and reference grid\","
                   "\"pit_kolmogorov\":\"exact empirical CDF defect\"},\n");
    std::print(out,
               "  \"runtime\":{{\"wall_seconds\":{:.17g},"
               "\"max_sample_estimated_bytes\":{}}}\n"
               "}}\n",
               wallSeconds, peakBytes);

    commitTemporary(out, path);
}

void writeGraphs(const Options& opt, const std::vector<GraphRecords>& graphs) {
    const std::filesystem::path path = opt.outputDirectory / "graphs.jsonl";
    std::ofstream out = openTemporary(path);

    for (const GraphRecords& graph : graphs) {
        std::print(out,
                   "{{\"schema\":"
                   "\"bounded-systems.gap-finite-closure-graph.v1\","
                   "\"graph_index\":{},\"sample_seed\":\"{}\","
                   "\"vertices\":{},\"edges\":{},"
                   "\"node_mark_rmse\":{:.17g},"
                   "\"node_mark_max_error\":{:.17g},"
                   "\"estimated_bytes\":{},\"seconds\":{:.17g},"
                   "\"horizons\":[",
                   graph.sampleIndex, graph.sampleSeed, opt.vertexCount,
                   graph.edgeCount, graph.nodeMarkRmse, graph.nodeMarkMaxError,
                   graph.estimatedBytes, graph.seconds);

        for (size_t i = 0; i < graph.horizons.size(); ++i) {
            if (i != 0) {
                printText(out, ",");
            }

            const HorizonGraphRecord& horizon = graph.horizons[i];
            std::print(out,
                       "{{\"horizon\":{},\"has_routes\":{},"
                       "\"paths\":{},\"route_mark_rmse\":",
                       horizon.horizon, horizon.hasRoutes, horizon.paths);

            if (horizon.hasRoutes) {
                printNumber(out, horizon.routeMarkRmse);
            } else {
                printText(out, "null");
            }

            printText(out, ",\"log_route_count\":");
            if (horizon.hasRoutes) {
                printNumber(out, static_cast<double>(horizon.logRouteCount));
            } else {
                printText(out, "null");
            }

            printText(out, "}");
        }

        printText(out, "]}\n");
    }

    commitTemporary(out, path);
}

void writeMetrics(const Options& opt, std::span<const Metric> metrics) {
    const std::filesystem::path path = opt.outputDirectory / "metrics.jsonl";
    std::ofstream out = openTemporary(path);

    for (const Metric& metric : metrics) {
        std::print(out,
                   "{{\"schema\":"
                   "\"bounded-systems.gap-finite-closure-metric.v1\","
                   "\"vertices\":{},\"graph_index\":{},"
                   "\"horizon\":{},\"resolution_index\":{},"
                   "\"base_bins\":{},\"aux_leaves\":{},"
                   "\"target_bins\":{},\"model\":",
                   opt.vertexCount, metric.graphIndex, metric.horizon,
                   metric.resolutionIndex, metric.baseBins, metric.auxLeaves,
                   metric.targetBins);
        writeJsonString(out, metric.model);
        printText(out, ",\"data\":");
        writeJsonString(out, metric.data);
        std::print(
            out,
            ",\"record_count\":{},\"training_records\":{},"
            "\"realized_classes\":{},"
            "\"minimum_training_class\":{},"
            "\"log_score\":{:.17g},\"wasserstein\":{:.17g},"
            "\"pit_mean\":{:.17g},\"pit_variance\":{:.17g},"
            "\"pit_kolmogorov\":{:.17g},"
            "\"mean_residual\":{:.17g},"
            "\"second_residual\":{:.17g},"
            "\"pit_x_correlation\":{:.17g},"
            "\"pit_age_correlation\":{:.17g},"
            "\"pit_history_correlation\":{:.17g},"
            "\"max_conditional_mean_error\":{:.17g},"
            "\"max_conditional_variance_error\":{:.17g}}}\n",
            metric.recordCount, metric.trainingRecords, metric.realizedClasses,
            metric.minimumTrainingClass, metric.logScore, metric.wasserstein,
            metric.pitMean, metric.pitVariance, metric.pitKolmogorov,
            metric.meanResidual, metric.secondResidual, metric.pitXCorrelation,
            metric.pitAgeCorrelation, metric.pitHistoryCorrelation,
            metric.maxConditionalMeanError, metric.maxConditionalVarianceError);
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
    for (const int remaining : {1, 2, 4, 8}) {
        constexpr size_t count = 100000;
        double sum = 0.0;
        double sumSquare = 0.0;
        for (size_t i = 0; i < count; ++i) {
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
    for (size_t i = 0; i < routeSamples; ++i) {
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
    for (const size_t count : routeCounts) {
        const double frequency =
            static_cast<double>(count) / static_cast<double>(routeSamples);
        requireCheck(std::abs(frequency - 1.0 / 3.0) < 0.01,
                     "uniform tiny route frequency", checks);
    }

    Options opt;
    opt.vertexCount = 64;
    opt.horizons = {4};
    opt.sampleCount = 4;
    opt.pathsPerHorizon = 200;
    opt.seed = 20260817;
    opt.threads = 1;
    opt.resolutions = {{4, 2, 16}};
    opt.referenceBins = 64;
    opt.pseudocount = 0.5;
    const std::vector<GraphRecords> graphs = sampleGraphs(opt, 1);
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
    requireCheck(transitionCount == opt.sampleCount * opt.pathsPerHorizon * 3,
                 "route transition count", checks);
    const std::vector<Metric> metrics = fitAndScore(opt, graphs, 1);
    requireCheck(metrics.size() == opt.sampleCount * 20,
                 "cross-fit metric count", checks);
    for (const Metric& metric : metrics) {
        requireCheck(metric.recordCount == opt.pathsPerHorizon * 3,
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
        const std::span<char*> args(argv, static_cast<size_t>(argc));
        const Options opt = parseOptions(args);
        if (opt.help) {
            printUsage(args.front());
            return 0;
        }
        if (opt.selfTest) {
            const size_t checks = runSelfTests();
            std::println(stderr,
                         "gap-finite-closure self-tests passed: {} checks",
                         checks);
            return 0;
        }

        prepareOutput(opt);
        const size_t effectiveThreads = std::min(opt.threads, opt.sampleCount);
        const auto started = Clock::now();
        std::vector<GraphRecords> graphs = sampleGraphs(opt, effectiveThreads);
        std::vector<Metric> metrics =
            fitAndScore(opt, graphs, effectiveThreads);
        const double wallSeconds =
            std::chrono::duration<double>(Clock::now() - started).count();
        size_t peakBytes = 0;
        for (const GraphRecords& graph : graphs) {
            peakBytes = std::max(peakBytes, graph.estimatedBytes);
        }

        writeRun(opt, effectiveThreads, wallSeconds, peakBytes);
        writeGraphs(opt, graphs);
        writeMetrics(opt, metrics);
        std::println(stderr,
                     "completed samples={} vertices={} paths={} threads={} "
                     "metrics={} wall_seconds={:.6f}",
                     opt.sampleCount, opt.vertexCount, opt.pathsPerHorizon,
                     effectiveThreads, metrics.size(), wallSeconds);
        return 0;
    } catch (const std::exception& error) {
        std::println(stderr, "fatal: {}", error.what());
        printUsage(argc > 0 ? argv[0] : "gap-finite-closure");
        return 2;
    }
}
