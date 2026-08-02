#include "gap_benchmark.hxx"
#include "gap_output.hxx"

#include <algorithm>
#include <atomic>
#include <charconv>
#include <chrono>
#include <cmath>
#include <exception>
#include <filesystem>
#include <mutex>
#include <print>
#include <span>
#include <stdexcept>
#include <string>
#include <string_view>
#include <thread>
#include <vector>

namespace {

using Clock = std::chrono::steady_clock;

bool hasOption(std::span<char*> arguments, std::string_view option) {
    return std::ranges::any_of(arguments, [option](const char* argument) {
        return std::string_view(argument) == option;
    });
}

std::string_view requireValue(std::span<char*> arguments, size_t& index,
                              std::string_view option) {
    if (index + 1 >= arguments.size()) {
        throw std::invalid_argument(std::string(option) + " requires a value");
    }
    return arguments[++index];
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

double parseReal(std::string_view text, std::string_view option) {
    double value = 0.0;
    const auto [end, error] =
        std::from_chars(text.data(), text.data() + text.size(), value,
                        std::chars_format::general);
    if (error != std::errc{} || end != text.data() + text.size() ||
        !std::isfinite(value)) {
        throw std::invalid_argument(std::string(option) +
                                    " requires a finite number");
    }
    return value;
}

template <typename Value, typename Parser>
std::vector<Value> parseList(std::string_view text, std::string_view option,
                             Parser parser) {
    std::vector<Value> values;
    size_t first = 0;

    while (first <= text.size()) {
        const size_t comma = text.find(',', first);
        const size_t last =
            comma == std::string_view::npos ? text.size() : comma;
        if (last == first) {
            throw std::invalid_argument(std::string(option) +
                                        " contains an empty item");
        }

        values.push_back(parser(text.substr(first, last - first), option));
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

GapOptions parseOptions(std::span<char*> arguments) {
    GapOptions options;
    options.threadCount = std::max(1U, std::thread::hardware_concurrency());

    for (size_t index = 1; index < arguments.size(); ++index) {
        const std::string_view option = arguments[index];

        if (option == "--vertices") {
            options.vertexCount = parseInteger<size_t>(
                requireValue(arguments, index, option), option);
        } else if (option == "--horizons") {
            options.horizons =
                parseList<int>(requireValue(arguments, index, option), option,
                               parseInteger<int>);
        } else if (option == "--samples") {
            options.sampleCount = parseInteger<size_t>(
                requireValue(arguments, index, option), option);
        } else if (option == "--seed") {
            options.seed = parseInteger<uint64_t>(
                requireValue(arguments, index, option), option);
        } else if (option == "--threads") {
            options.threadCount = parseInteger<size_t>(
                requireValue(arguments, index, option), option);
        } else if (option == "--output") {
            options.outputDirectory = requireValue(arguments, index, option);
        } else if (option == "--closure-bins") {
            options.bins =
                parseList<int>(requireValue(arguments, index, option), option,
                               parseInteger<int>);
        } else if (option == "--predictive-classes") {
            options.predictiveClasses =
                parseList<int>(requireValue(arguments, index, option), option,
                               parseInteger<int>);
        } else if (option == "--target-bins") {
            options.targetBins =
                parseList<int>(requireValue(arguments, index, option), option,
                               parseInteger<int>);
        } else if (option == "--reference-bins") {
            options.referenceBins = parseInteger<int>(
                requireValue(arguments, index, option), option);
        } else if (option == "--lindeberg-thresholds") {
            options.thresholds = parseList<double>(
                requireValue(arguments, index, option), option, parseReal);
        } else if (option == "--validation-length") {
            options.validationLength = parseInteger<int>(
                requireValue(arguments, index, option), option);
        } else if (option == "--legendre-modes") {
            options.modeCount = parseInteger<int>(
                requireValue(arguments, index, option), option);
        } else if (option == "--bulk-fraction") {
            options.bulkFraction =
                parseReal(requireValue(arguments, index, option), option);
        } else if (option == "--overwrite") {
            options.overwrite = true;
        } else {
            throw std::invalid_argument("unknown option: " +
                                        std::string(option));
        }
    }

    sortUnique(options.horizons);
    sortUnique(options.bins);
    sortUnique(options.predictiveClasses);
    sortUnique(options.targetBins);
    sortUnique(options.thresholds);

    if (options.vertexCount < 2) {
        throw std::invalid_argument("--vertices must be at least 2");
    }
    if (options.horizons.empty()) {
        throw std::invalid_argument("--horizons must not be empty");
    }
    for (const int horizon : options.horizons) {
        if (horizon < 1 || horizon >= static_cast<int>(options.vertexCount)) {
            throw std::invalid_argument(
                "each route horizon must lie in 1..vertices-1");
        }
    }
    if (options.sampleCount == 0) {
        throw std::invalid_argument("--samples must be positive");
    }
    if (options.threadCount == 0) {
        throw std::invalid_argument("--threads must be positive");
    }
    if (options.outputDirectory.empty()) {
        throw std::invalid_argument("--output is required");
    }
    for (const int bins : options.bins) {
        if (bins < 2) {
            throw std::invalid_argument(
                "--closure-bins values must be at least 2");
        }
    }
    for (const int classes : options.predictiveClasses) {
        if (classes < 2 || static_cast<size_t>(classes) > options.vertexCount) {
            throw std::invalid_argument(
                "--predictive-classes values must lie in 2..vertices");
        }
    }
    if (options.targetBins.empty()) {
        throw std::invalid_argument("--target-bins must not be empty");
    }
    const int maximumTargetBins = options.targetBins.back();
    for (const int bins : options.targetBins) {
        if (bins < 2 || maximumTargetBins % bins != 0) {
            throw std::invalid_argument(
                "--target-bins must be nested divisors of the maximum");
        }
    }
    if (options.referenceBins < 16) {
        throw std::invalid_argument("--reference-bins must be at least 16");
    }
    for (const double threshold : options.thresholds) {
        if (!(threshold > 0.0)) {
            throw std::invalid_argument(
                "--lindeberg-thresholds values must be positive");
        }
    }
    if (options.validationLength < 1 ||
        options.validationLength >= static_cast<int>(options.vertexCount)) {
        throw std::invalid_argument(
            "--validation-length must lie in 1..vertices-1");
    }
    if (options.modeCount < 1) {
        throw std::invalid_argument("--legendre-modes must be positive");
    }
    if (!(options.bulkFraction > 0.0 && options.bulkFraction < 0.5)) {
        throw std::invalid_argument(
            "--bulk-fraction must lie strictly between 0 and 0.5");
    }

    return options;
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
    std::vector<size_t> heights(graph.vertexCount(), 1);
    const auto offsets = graph.outgoingOffsets();
    const auto targets = graph.outgoingTargets();
    size_t maximum = 1;

    for (size_t source = 0; source < graph.vertexCount(); ++source) {
        for (size_t edge = offsets[source]; edge < offsets[source + 1];
             ++edge) {
            const uint32_t target = targets[edge];
            heights[target] = std::max(heights[target], heights[source] + 1);
            maximum = std::max(maximum, heights[target]);
        }
    }

    return maximum;
}

GapSample runSample(const GapOptions& options, size_t index) {
    const auto started = Clock::now();

    GapSample sample;
    sample.index = index;
    sample.seed = deriveGapSampleSeed(options.seed, index);
    sample.vertexCount = options.vertexCount;

    const auto generationStarted = Clock::now();
    const ReferenceDag graph =
        ReferenceDag::generate(options.vertexCount, sample.seed);
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

    const int requestedHorizon = *std::ranges::max_element(options.horizons);
    const int maximumLength =
        std::max(requestedHorizon + 1, options.validationLength);

    const auto routeStarted = Clock::now();
    const StableRouteCounts routes =
        computeRouteCounts(graph, static_cast<size_t>(maximumLength));
    sample.routeSeconds =
        std::chrono::duration<double>(Clock::now() - routeStarted).count();
    sample.routeBytes = routes.estimatedBytes();
    sample.maxLogError = routes.maxLogError;

    const std::vector<ProfilePartition> partitions =
        buildPartitions(state, options.bins);
    const std::vector<PredictivePartition> predictivePartitions =
        buildPredictivePartitions(graph, state, options.predictiveClasses);
    sample.modes = computeLegendreModes(graph, options.modeCount);
    sample.calibration = computeCalibration(graph, routes, sample.modes,
                                            options.validationLength);

    sample.horizons.reserve(options.horizons.size());
    sample.scaling.reserve(options.horizons.size());
    size_t maximumAnalysisBytes =
        sample.graphBytes + sample.stateBytes + sample.routeBytes;
    for (const int horizon : options.horizons) {
        HorizonResult bridge =
            analyzeHorizon(graph, state, routes, horizon, partitions,
                           options.bulkFraction, options.thresholds);
        RouteScalingResult scaling = analyzeRouteScaling(
            graph, state, routes, bridge, predictivePartitions,
            options.targetBins, options.thresholds, options.bulkFraction,
            options.referenceBins);

        maximumAnalysisBytes = std::max(maximumAnalysisBytes, bridge.peakBytes);
        maximumAnalysisBytes = std::max(
            maximumAnalysisBytes, sample.graphBytes + sample.stateBytes +
                                      sample.routeBytes + scaling.peakBytes);
        sample.horizons.push_back(std::move(bridge));
        sample.scaling.push_back(std::move(scaling));
    }

    sample.peakBytes = maximumAnalysisBytes;
    sample.totalSeconds =
        std::chrono::duration<double>(Clock::now() - started).count();
    return sample;
}

std::vector<GapSample> runSamples(const GapOptions& options,
                                  size_t threadCount) {
    std::vector<GapSample> samples(options.sampleCount);
    std::atomic<size_t> next{0};
    std::atomic<bool> failed{false};
    std::mutex errorMutex;
    std::exception_ptr error;
    std::vector<std::jthread> workers;
    workers.reserve(threadCount);

    for (size_t thread = 0; thread < threadCount; ++thread) {
        workers.emplace_back([&] {
            while (!failed.load(std::memory_order_relaxed)) {
                const size_t index =
                    next.fetch_add(1, std::memory_order_relaxed);
                if (index >= options.sampleCount) {
                    return;
                }

                try {
                    samples[index] = runSample(options, index);
                } catch (...) {
                    std::scoped_lock lock(errorMutex);
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

int main(int argumentCount, char** argumentValues) {
    const std::span<char*> arguments(argumentValues,
                                     static_cast<size_t>(argumentCount));

    try {
        if (hasOption(arguments, "--help")) {
            printUsage(arguments.front());
            return 0;
        }
        if (hasOption(arguments, "--self-test")) {
            if (arguments.size() != 2) {
                throw std::invalid_argument(
                    "--self-test cannot be combined with other options");
            }
            const size_t routeChecks = runRouteSelfTests();
            const size_t scalingChecks = runRouteScalingSelfTests();
            std::println("gap route-bridge self-tests passed: {} checks",
                         routeChecks + scalingChecks);
            return 0;
        }

        const GapOptions options = parseOptions(arguments);
        const size_t threadCount =
            std::min(options.threadCount, options.sampleCount);
        const auto started = Clock::now();
        const std::vector<GapSample> samples = runSamples(options, threadCount);
        const double wallSeconds =
            std::chrono::duration<double>(Clock::now() - started).count();

        writeGapOutput(options, samples, threadCount, wallSeconds);
        std::println(stderr,
                     "completed samples={} vertices={} threads={} "
                     "wall_seconds={:.6f} peak_rss_kib={}",
                     options.sampleCount, options.vertexCount, threadCount,
                     wallSeconds, peakRssKib());
        return 0;
    } catch (const std::exception& error) {
        std::println(stderr, "fatal: {}", error.what());
        printUsage(arguments.empty() ? "gap-benchmark" : arguments.front());
        return 2;
    }
}
