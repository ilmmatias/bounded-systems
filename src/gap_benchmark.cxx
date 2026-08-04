#include "gap_benchmark.hxx"
#include "gap_output.hxx"
#include "reference_dag.hxx"
#include "route_bridge.hxx"
#include "route_scaling.hxx"

#include <algorithm>
#include <atomic>
#include <charconv>
#include <chrono>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <exception>
#include <filesystem>
#include <format>
#include <mutex>
#include <print>
#include <span>
#include <stdexcept>
#include <string_view>
#include <system_error>
#include <thread>
#include <utility>
#include <vector>

namespace {

using Clock = std::chrono::steady_clock;

bool hasOption(std::span<char*> args, std::string_view opt) {
    return std::ranges::any_of(
        args, [opt](const char* arg) { return std::string_view(arg) == opt; });
}

std::string_view requireValue(std::span<char*> args, size_t& i,
                              std::string_view opt) {
    if (i + 1 >= args.size()) {
        throw std::invalid_argument(std::format("{} requires a value", opt));
    }

    return args[++i];
}

template <typename Integer>
Integer parseInt(std::string_view text, std::string_view opt) {
    Integer value{};
    const auto [end, error] =
        std::from_chars(text.data(), text.data() + text.size(), value);

    if (error != std::errc{} || end != text.data() + text.size()) {
        throw std::invalid_argument(std::format("{} requires an integer", opt));
    }

    return value;
}

double parseReal(std::string_view text, std::string_view opt) {
    double value = 0.0;
    const auto [end, error] =
        std::from_chars(text.data(), text.data() + text.size(), value,
                        std::chars_format::general);

    if (error != std::errc{} || end != text.data() + text.size() ||
        !std::isfinite(value)) {
        throw std::invalid_argument(
            std::format("{} requires a finite number", opt));
    }

    return value;
}

template <typename Value, typename Parser>
std::vector<Value> parseList(std::string_view text, std::string_view opt,
                             Parser parse) {
    std::vector<Value> values;
    size_t first = 0;

    while (first <= text.size()) {
        const size_t comma = text.find(',', first);
        const size_t last =
            comma == std::string_view::npos ? text.size() : comma;

        if (last == first) {
            throw std::invalid_argument(
                std::format("{} contains an empty item", opt));
        }

        values.push_back(parse(text.substr(first, last - first), opt));

        if (comma == std::string_view::npos) {
            break;
        }

        first = comma + 1;
    }

    return values;
}

template <typename Value> void sortUnique(std::vector<Value>& values) {
    std::ranges::sort(values);
    values.erase(std::unique(values.begin(), values.end()), values.end());
}

GapOptions parseOptions(std::span<char*> args) {
    GapOptions opt;
    opt.threadCount = std::max(1U, std::thread::hardware_concurrency());

    for (size_t i = 1; i < args.size(); ++i) {
        const std::string_view name = args[i];

        if (name == "--vertices") {
            opt.vertexCount =
                parseInt<size_t>(requireValue(args, i, name), name);
        } else if (name == "--horizons") {
            opt.horizons = parseList<int>(requireValue(args, i, name), name,
                                          parseInt<int>);
        } else if (name == "--samples") {
            opt.sampleCount =
                parseInt<size_t>(requireValue(args, i, name), name);
        } else if (name == "--seed") {
            opt.seed = parseInt<uint64_t>(requireValue(args, i, name), name);
        } else if (name == "--threads") {
            opt.threadCount =
                parseInt<size_t>(requireValue(args, i, name), name);
        } else if (name == "--output") {
            opt.outputDirectory = requireValue(args, i, name);
        } else if (name == "--closure-bins") {
            opt.bins = parseList<int>(requireValue(args, i, name), name,
                                      parseInt<int>);
        } else if (name == "--predictive-classes") {
            opt.predictiveClasses = parseList<int>(requireValue(args, i, name),
                                                   name, parseInt<int>);
        } else if (name == "--target-bins") {
            opt.targetBins = parseList<int>(requireValue(args, i, name), name,
                                            parseInt<int>);
        } else if (name == "--reference-bins") {
            opt.referenceBins =
                parseInt<int>(requireValue(args, i, name), name);
        } else if (name == "--lindeberg-thresholds") {
            opt.thresholds =
                parseList<double>(requireValue(args, i, name), name, parseReal);
        } else if (name == "--validation-length") {
            opt.validationLength =
                parseInt<int>(requireValue(args, i, name), name);
        } else if (name == "--legendre-modes") {
            opt.modeCount = parseInt<int>(requireValue(args, i, name), name);
        } else if (name == "--bulk-fraction") {
            opt.bulkFraction = parseReal(requireValue(args, i, name), name);
        } else if (name == "--overwrite") {
            opt.overwrite = true;
        } else {
            throw std::invalid_argument(
                std::format("unknown option: {}", name));
        }
    }

    sortUnique(opt.horizons);
    sortUnique(opt.bins);
    sortUnique(opt.predictiveClasses);
    sortUnique(opt.targetBins);
    sortUnique(opt.thresholds);

    if (opt.vertexCount < 2) {
        throw std::invalid_argument("--vertices must be at least 2");
    }

    if (opt.horizons.empty()) {
        throw std::invalid_argument("--horizons must not be empty");
    }

    for (const int horizon : opt.horizons) {
        if (horizon < 1 || std::cmp_greater_equal(horizon, opt.vertexCount)) {
            throw std::invalid_argument(
                "--horizons values must lie in 1..vertices-1");
        }
    }

    if (opt.sampleCount == 0) {
        throw std::invalid_argument("--samples must be positive");
    }

    if (opt.threadCount == 0) {
        throw std::invalid_argument("--threads must be positive");
    }

    if (opt.outputDirectory.empty()) {
        throw std::invalid_argument("--output is required");
    }

    for (const int bins : opt.bins) {
        if (bins < 2) {
            throw std::invalid_argument(
                "--closure-bins values must be at least 2");
        }
    }

    for (const int classes : opt.predictiveClasses) {
        if (classes < 2 || std::cmp_greater(classes, opt.vertexCount)) {
            throw std::invalid_argument(
                "--predictive-classes values must lie in 2..vertices");
        }
    }

    if (opt.targetBins.empty()) {
        throw std::invalid_argument("--target-bins must not be empty");
    }

    const int maxBins = opt.targetBins.back();

    for (const int bins : opt.targetBins) {
        if (bins < 2 || maxBins % bins != 0) {
            throw std::invalid_argument(
                "--target-bins must be nested divisors of the maximum");
        }
    }

    if (opt.referenceBins < 16) {
        throw std::invalid_argument("--reference-bins must be at least 16");
    }

    for (const double threshold : opt.thresholds) {
        if (!(threshold > 0.0)) {
            throw std::invalid_argument(
                "--lindeberg-thresholds values must be positive");
        }
    }

    if (opt.validationLength < 1 ||
        std::cmp_greater_equal(opt.validationLength, opt.vertexCount)) {
        throw std::invalid_argument(
            "--validation-length must lie in 1..vertices-1");
    }

    if (opt.modeCount < 1) {
        throw std::invalid_argument("--legendre-modes must be positive");
    }

    if (!(opt.bulkFraction > 0.0 && opt.bulkFraction < 0.5)) {
        throw std::invalid_argument(
            "--bulk-fraction must lie strictly between 0 and 0.5");
    }

    return opt;
}

void printUsage(std::string_view program) {
    std::println(
        stderr,
        "usage: {} --vertices N --horizons p[,p...] --samples S --output DIR "
        "[options]",
        program);
    std::println(stderr, "       {} --self-test", program);
    std::println(stderr, "");
    std::println(stderr, "required benchmark options:");
    std::println(stderr, "  --vertices N             number of vertices");
    std::println(stderr, "  --horizons p[,p...]      route lengths");
    std::println(stderr,
                 "  --samples S              independent graph samples");
    std::println(stderr, "  --output DIR             JSON output directory");
    std::println(stderr, "");
    std::println(stderr, "reproducibility and parallelism:");
    std::println(stderr, "  --seed Z                 master seed (default: 0)");
    std::println(
        stderr,
        "  --threads T              sample workers (default: hardware)");
    std::println(stderr,
                 "  --overwrite              replace existing output files");
    std::println(stderr, "");
    std::println(stderr, "diagnostic options:");
    std::println(stderr,
                 "  --closure-bins b[,b...]  bins per coordinate (8,16,32)");
    std::println(
        stderr,
        "  --predictive-classes k[,k...]  balanced class counts (8,16,32)");
    std::println(stderr,
                 "  --target-bins b[,b...]  nested mark targets (16,32,64)");
    std::println(
        stderr, "  --reference-bins B      spacing audit histogram bins (256)");
    std::println(stderr, "  --lindeberg-thresholds x[,x...]  jump thresholds");
    std::println(stderr,
                 "  --validation-length L    analytic route lengths (4)");
    std::println(stderr,
                 "  --legendre-modes M       even latent validation modes (4)");
    std::println(
        stderr,
        "  --bulk-fraction f        excluded fraction per boundary (0.2)");
}

size_t graphHeight(const ReferenceDag& graph) {
    std::vector<size_t> height(graph.vertexCount(), 1);
    const auto offsets = graph.outgoingOffsets();
    const auto targets = graph.outgoingTargets();
    size_t maxHeight = 1;

    for (size_t src = 0; src < graph.vertexCount(); ++src) {
        for (size_t edge = offsets[src]; edge < offsets[src + 1]; ++edge) {
            const uint32_t dst = targets[edge];
            height[dst] = std::max(height[dst], height[src] + 1);
            maxHeight = std::max(maxHeight, height[dst]);
        }
    }

    return maxHeight;
}

GapSample runSample(const GapOptions& opt, size_t sampleIndex) {
    const auto started = Clock::now();

    GapSample sample;
    sample.index = sampleIndex;
    sample.seed = deriveGapSampleSeed(opt.seed, sampleIndex);
    sample.vertexCount = opt.vertexCount;

    const auto generationStarted = Clock::now();
    const ReferenceDag graph =
        ReferenceDag::generate(opt.vertexCount, sample.seed);
    sample.generationSeconds =
        std::chrono::duration<double>(Clock::now() - generationStarted).count();
    sample.edgeCount = graph.edgeCount();
    sample.height = graphHeight(graph);
    sample.edgeDensity =
        static_cast<double>(sample.edgeCount) /
        static_cast<double>(sample.vertexCount * (sample.vertexCount - 1));
    sample.pairDensity = 2.0 * sample.edgeDensity;
    sample.graphBytes = graph.estimatedBytes();

    const auto stateStarted = Clock::now();
    const GapNodeState state = computeGapNodeState(graph);
    sample.stateSeconds =
        std::chrono::duration<double>(Clock::now() - stateStarted).count();
    sample.stateBytes = state.estimatedBytes();
    sample.latentCheck = validateGapNodeState(graph, state);
    sample.intrinsicScaling = summarizeIntrinsicState(state);
    sample.signatures = summarizeSignatures(state);

    const int maxHorizon = *std::ranges::max_element(opt.horizons);
    const int maxLength = std::max(maxHorizon + 1, opt.validationLength);

    const auto routeStarted = Clock::now();
    const StableRouteCounts routes =
        computeRouteCounts(graph, static_cast<size_t>(maxLength));
    sample.routeSeconds =
        std::chrono::duration<double>(Clock::now() - routeStarted).count();
    sample.routeBytes = routes.estimatedBytes();
    sample.maxLogError = routes.maxLogError;

    const std::vector<ProfilePartition> partitions =
        buildPartitions(state, opt.bins);
    const std::vector<PredictivePartition> predPartitions =
        buildPredictivePartitions(graph, state, opt.predictiveClasses);
    sample.modes = computeLegendreModes(graph, opt.modeCount);
    sample.calibration =
        computeCalibration(graph, routes, sample.modes, opt.validationLength);

    sample.horizons.reserve(opt.horizons.size());
    sample.scaling.reserve(opt.horizons.size());
    size_t peakBytes =
        sample.graphBytes + sample.stateBytes + sample.routeBytes;

    for (const int horizon : opt.horizons) {
        HorizonResult bridge =
            analyzeHorizon(graph, state, routes, horizon, partitions,
                           opt.bulkFraction, opt.thresholds);
        RouteScalingResult scaling = analyzeRouteScaling(
            graph, state, routes, bridge, predPartitions, opt.targetBins,
            opt.thresholds, opt.bulkFraction, opt.referenceBins);

        peakBytes = std::max(peakBytes, bridge.peakBytes);
        peakBytes =
            std::max(peakBytes, sample.graphBytes + sample.stateBytes +
                                    sample.routeBytes + scaling.peakBytes);
        sample.horizons.push_back(std::move(bridge));
        sample.scaling.push_back(std::move(scaling));
    }

    sample.peakBytes = peakBytes;
    sample.totalSeconds =
        std::chrono::duration<double>(Clock::now() - started).count();
    return sample;
}

std::vector<GapSample> runSamples(const GapOptions& opt, size_t threadCount) {
    std::vector<GapSample> samples(opt.sampleCount);
    std::atomic<size_t> next{0};
    std::atomic<bool> failed{false};
    std::mutex errorMutex;
    std::exception_ptr error;
    std::vector<std::jthread> workers;
    workers.reserve(threadCount);

    for (size_t thread = 0; thread < threadCount; ++thread) {
        workers.emplace_back([&samples, &next, &failed, &errorMutex, &error,
                              &opt] {
            while (!failed.load(std::memory_order_relaxed)) {
                const size_t i = next.fetch_add(1, std::memory_order_relaxed);

                if (i >= opt.sampleCount) {
                    return;
                }

                try {
                    samples[i] = runSample(opt, i);
                } catch (...) {
                    const std::scoped_lock lock(errorMutex);

                    if (!error) {
                        error = std::current_exception();
                    }

                    failed.store(true, std::memory_order_relaxed);
                    return;
                }
            }
        });
    }

    workers.clear();

    if (error) {
        std::rethrow_exception(error);
    }

    return samples;
}

} // namespace

int main(int argc, char** argv) {
    const std::span<char*> args(argv, static_cast<size_t>(argc));

    try {
        if (hasOption(args, "--help")) {
            printUsage(args.front());
            return 0;
        }

        if (hasOption(args, "--self-test")) {
            if (args.size() != 2) {
                throw std::invalid_argument(
                    "--self-test cannot be combined with other options");
            }

            const size_t routeChecks = runRouteSelfTests();
            const size_t scalingChecks = runRouteScalingSelfTests();
            std::println("gap route-bridge self-tests passed: {} checks",
                         routeChecks + scalingChecks);
            return 0;
        }

        const GapOptions opt = parseOptions(args);
        const size_t threadCount = std::min(opt.threadCount, opt.sampleCount);
        const auto started = Clock::now();
        const std::vector<GapSample> samples = runSamples(opt, threadCount);
        const double wallSeconds =
            std::chrono::duration<double>(Clock::now() - started).count();

        writeGapOutput(opt, samples, threadCount, wallSeconds);
        std::println(stderr,
                     "completed samples={} vertices={} threads={} "
                     "wall_seconds={:.6f} peak_rss_kib={}",
                     opt.sampleCount, opt.vertexCount, threadCount, wallSeconds,
                     peakRssKib());
        return 0;
    } catch (const std::exception& error) {
        std::println(stderr, "fatal: {}", error.what());
        printUsage(args.empty() ? "gap-benchmark" : args.front());
        return 2;
    }
}
