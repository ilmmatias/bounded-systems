#include <algorithm>
#include <array>
#include <charconv>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <filesystem>
#include <format>
#include <fstream>
#include <limits>
#include <numeric>
#include <ostream>
#include <print>
#include <span>
#include <stdexcept>
#include <string>
#include <string_view>
#include <thread>
#include <utility>
#include <vector>

namespace {

constexpr std::array<int, 7> kPositions{1, 2, 3, 4, 5, 6, 7};
constexpr int kPositionDenominator = 8;
constexpr std::array<int, 3> kXBins{64, 128, 256};
constexpr std::array<int, 3> kHistoryBins{2, 4, 8};
constexpr std::array<int, 3> kPitBins{16, 32, 64};
constexpr double kPrior = 0.5;

struct Options {
    std::vector<int> horizons{16, 32, 64, 128};
    std::vector<int> scales{1, 2, 4};
    size_t paths = 40'000;
    uint64_t seed = 0x104D1A1CULL;
    size_t threads = std::max(1U, std::thread::hardware_concurrency());
    std::filesystem::path output;
    bool overwrite = false;
    bool selfTest = false;
};

struct RouteStep {
    double x = 0.0;
    double z = 0.0;
    double y = 0.0;
    double last = 0.0;
    double quad = 0.0;
    size_t cell = 0;
};

struct RoutePath {
    std::array<RouteStep, kPositions.size()> steps;
    bool training = false;
};

struct Cell {
    int p = 0;
    int r = 0;
    int k = 0;
    int pos = 0;
    double logXNorm = 0.0;
};

struct Summary {
    double mean = 0.0;
    double standardError = 0.0;
    size_t count = 0;
};

struct Scores {
    std::vector<double> oracle;
    std::vector<double> local;
    std::vector<double> clock;
    std::vector<double> augmented;
};

struct W1Result {
    int xBins = 0;
    Summary local;
    Summary clock;
    Summary localMinusClock;
};

struct HistoryResult {
    std::string state;
    int historyBins = 0;
    int pitBins = 0;
    Summary logGain;
    Summary pitWasserstein;
    size_t occupiedClasses = 0;
    size_t trainingTransitions = 0;
    size_t heldOutTransitions = 0;
};

struct Audit {
    double pitMean = 0.0;
    double pitVariance = 0.0;
    double pitKolmogorov = 0.0;
    double maxConditionalMeanError = 0.0;
    double pitLastCorrelation = 0.0;
    double pitQuadCorrelation = 0.0;
};

struct ScaleResult {
    int scale = 0;
    std::vector<int> horizons;
    size_t trainingPaths = 0;
    size_t heldOutPaths = 0;
    size_t heldOutTransitions = 0;
    Audit audit;
    Scores fractionScores;
    Scores routeTimeScores;
    std::vector<W1Result> fractionW1;
    std::vector<W1Result> routeTimeW1;
    std::vector<HistoryResult> history;
};

int parseInt(std::string_view text, std::string_view opt) {
    int value = 0;
    const auto [end, error] =
        std::from_chars(text.data(), text.data() + text.size(), value);

    if (error != std::errc{} || end != text.data() + text.size()) {
        throw std::invalid_argument(std::format("{} requires an integer", opt));
    }

    return value;
}

size_t parseSize(std::string_view text, std::string_view opt) {
    uint64_t value = 0;
    const auto [end, error] =
        std::from_chars(text.data(), text.data() + text.size(), value);

    if (error != std::errc{} || end != text.data() + text.size()) {
        throw std::invalid_argument(
            std::format("{} requires a nonnegative integer", opt));
    }

    if (value > std::numeric_limits<size_t>::max()) {
        throw std::invalid_argument(std::format("{} is too large", opt));
    }

    return static_cast<size_t>(value);
}

uint64_t parseSeed(std::string_view text, std::string_view opt) {
    uint64_t value = 0;
    const auto [end, error] =
        std::from_chars(text.data(), text.data() + text.size(), value);

    if (error != std::errc{} || end != text.data() + text.size()) {
        throw std::invalid_argument(
            std::format("{} requires an unsigned integer", opt));
    }

    return value;
}

std::vector<int> parseList(std::string_view text, std::string_view opt) {
    std::vector<int> values;
    size_t start = 0;

    while (start <= text.size()) {
        const size_t end = text.find(',', start);
        const size_t length =
            end == std::string_view::npos ? text.size() - start : end - start;

        if (length == 0) {
            throw std::invalid_argument(
                std::format("{} contains an empty value", opt));
        }

        values.push_back(parseInt(text.substr(start, length), opt));

        if (end == std::string_view::npos) {
            break;
        }

        start = end + 1;
    }

    return values;
}

void sortUnique(std::vector<int>& values) {
    std::ranges::sort(values);
    values.erase(std::unique(values.begin(), values.end()), values.end());
}

Options parseOptions(std::span<char*> args) {
    Options opt;

    for (size_t i = 0; i < args.size(); ++i) {
        const std::string_view arg = args[i];

        if (arg == "--self-test") {
            opt.selfTest = true;
            continue;
        }

        if (arg == "--overwrite") {
            opt.overwrite = true;
            continue;
        }

        if (++i == args.size()) {
            throw std::invalid_argument(
                std::format("{} requires a value", arg));
        }

        const std::string_view value = args[i];

        if (arg == "--horizons") {
            opt.horizons = parseList(value, arg);
            continue;
        }

        if (arg == "--scales") {
            opt.scales = parseList(value, arg);
            continue;
        }

        if (arg == "--paths") {
            opt.paths = parseSize(value, arg);
            continue;
        }

        if (arg == "--seed") {
            opt.seed = parseSeed(value, arg);
            continue;
        }

        if (arg == "--threads") {
            opt.threads = parseSize(value, arg);
            continue;
        }

        if (arg == "--output") {
            opt.output = value;
            continue;
        }

        throw std::invalid_argument(std::format("unknown option: {}", arg));
    }

    sortUnique(opt.horizons);
    sortUnique(opt.scales);

    if (opt.selfTest) {
        return opt;
    }

    if (opt.horizons.size() < 2) {
        throw std::invalid_argument("--horizons requires at least two values");
    }

    for (int p : opt.horizons) {
        if (p < kPositionDenominator || p % kPositionDenominator != 0) {
            throw std::invalid_argument(
                "--horizons values must be positive multiples of 8");
        }
    }

    if (opt.scales.empty()) {
        throw std::invalid_argument("--scales must not be empty");
    }

    for (int scale : opt.scales) {
        if (scale < 1) {
            throw std::invalid_argument("--scales values must be positive");
        }
    }

    if (opt.paths < 100 || opt.paths % 2 != 0) {
        throw std::invalid_argument(
            "--paths must be an even integer of at least 100");
    }

    if (opt.threads == 0) {
        throw std::invalid_argument("--threads must be positive");
    }

    if (opt.output.empty()) {
        throw std::invalid_argument("missing --output");
    }

    return opt;
}

void printUsage(std::string_view program) {
    std::print(stderr,
               "usage: {} --output FILE [options]\n"
               "       {} --self-test\n\n"
               "options:\n"
               "  --horizons p[,p...]  base horizons (16,32,64,128)\n"
               "  --scales m[,m...]    horizon multipliers (1,2,4)\n"
               "  --paths M            paths per horizon (40000)\n"
               "  --seed Z             master seed (273488412)\n"
               "  --threads T          path workers (hardware concurrency)\n"
               "  --output FILE        output JSON artifact\n"
               "  --overwrite          replace an existing artifact\n",
               program, program);
}

uint64_t splitMix64(uint64_t value) {
    value += 0x9e3779b97f4a7c15ULL;
    value = (value ^ (value >> 30)) * 0xbf58476d1ce4e5b9ULL;
    value = (value ^ (value >> 27)) * 0x94d049bb133111ebULL;
    return value ^ (value >> 31);
}

double uniform(uint64_t& state) {
    state = splitMix64(state);
    return static_cast<double>(state >> 11) * 0x1.0p-53;
}

double exponential(uint64_t& state) { return -std::log1p(-uniform(state)); }

uint64_t pathSeed(uint64_t seed, int scale, int p, size_t path) {
    uint64_t value = seed;
    value ^= splitMix64(static_cast<uint64_t>(scale));
    value ^= splitMix64(static_cast<uint64_t>(p) << 16);
    value ^= splitMix64(path);
    return splitMix64(value);
}

std::vector<Cell> makeCells(std::span<const int> horizons) {
    std::vector<Cell> cells;
    cells.reserve(horizons.size() * kPositions.size());

    for (int p : horizons) {
        for (size_t pos = 0; pos < kPositions.size(); ++pos) {
            const int r = p * kPositions[pos] / kPositionDenominator;
            const int k = p - r;
            const int a = 2 * r + 1;
            const int b = 2 * k + 1;

            cells.push_back({
                .p = p,
                .r = r,
                .k = k,
                .pos = static_cast<int>(pos),
                .logXNorm =
                    std::lgamma(a + b) - std::lgamma(a) - std::lgamma(b),
            });
        }
    }

    return cells;
}

void samplePath(RoutePath& path, int p, size_t pIndex, uint64_t seed) {
    const size_t n = static_cast<size_t>(p);
    std::vector<double> gaps(n + 2);
    double total = 0.0;

    for (size_t j = 0; j <= n + 1; ++j) {
        double gap = exponential(seed);

        if (j > 0 && j <= n) {
            gap += exponential(seed);
        }

        gaps[j] = gap;
        total += gap;
    }

    double prefix = gaps.front();
    double square = prefix * prefix;
    size_t pos = 0;

    for (size_t r = 0; r < n && pos < kPositions.size(); ++r) {
        if (r ==
            n * static_cast<size_t>(kPositions[pos]) / kPositionDenominator) {
            const double remaining = total - prefix;
            const double z = gaps[r + 1] / remaining;

            path.steps[pos] = {
                .x = prefix / total,
                .z = z,
                .y = static_cast<double>(p) * z,
                .last = gaps[r] / prefix,
                .quad = square / (prefix * prefix),
                .cell = pIndex * kPositions.size() + pos,
            };
            ++pos;
        }

        prefix += gaps[r + 1];
        square += gaps[r + 1] * gaps[r + 1];
    }

    if (pos != kPositions.size()) {
        throw std::runtime_error("route position generation failed");
    }
}

std::vector<RoutePath> samplePaths(std::span<const int> horizons, size_t count,
                                   uint64_t seed, int scale, size_t threads) {
    const size_t size = horizons.size() * count;
    std::vector<RoutePath> paths(size);
    const size_t workers = std::min(threads, size);
    std::vector<std::jthread> pool;
    pool.reserve(workers);

    for (size_t worker = 0; worker < workers; ++worker) {
        const size_t begin = size * worker / workers;
        const size_t end = size * (worker + 1) / workers;

        pool.emplace_back([&, begin, end] {
            for (size_t i = begin; i < end; ++i) {
                const size_t pIndex = i / count;
                const size_t sample = i % count;
                RoutePath& path = paths[i];

                path.training = sample % 2 == 0;
                samplePath(path, horizons[pIndex], pIndex,
                           pathSeed(seed, scale, horizons[pIndex], sample));
            }
        });
    }

    return paths;
}

double logXDensity(const Cell& cell, double x) {
    const double a = 2.0 * cell.r + 1.0;
    const double b = 2.0 * cell.k + 1.0;
    return cell.logXNorm + (a - 1.0) * std::log(x) + (b - 1.0) * std::log1p(-x);
}

double logZDensity(int k, double z) {
    if (!(z > 0.0 && z < 1.0)) {
        return -std::numeric_limits<double>::infinity();
    }

    const double b = 2.0 * k - 1.0;
    return std::log(b) + std::log(b + 1.0) + std::log(z) +
           (b - 1.0) * std::log1p(-z);
}

double betaCdf(int k, double z) {
    if (z <= 0.0) {
        return 0.0;
    }

    if (z >= 1.0) {
        return 1.0;
    }

    const double b = 2.0 * k - 1.0;
    const double logSurvival = b * std::log1p(-z) + std::log1p(b * z);
    return std::clamp(-std::expm1(logSurvival), 0.0, 1.0);
}

double logTargetDensity(const Cell& cell, double value, bool routeTime) {
    if (!routeTime) {
        return logZDensity(cell.k, value);
    }

    return logZDensity(cell.k, value / cell.p) - std::log(cell.p);
}

double targetCdf(const Cell& cell, double value, bool routeTime) {
    return betaCdf(cell.k, routeTime ? value / cell.p : value);
}

double logSumExp(std::span<const double> values) {
    const double maximum = *std::ranges::max_element(values);
    double total = 0.0;

    for (double value : values) {
        total += std::exp(value - maximum);
    }

    return maximum + std::log(total);
}

std::array<double, 4> stepScores(const RouteStep& step,
                                 std::span<const Cell> cells, bool routeTime) {
    const Cell& truth = cells[step.cell];
    const double target = routeTime ? step.y : step.z;
    std::vector<double> weights(cells.size());
    std::vector<double> joint(cells.size());
    std::vector<double> clockWeights;
    std::vector<double> clockJoint;

    for (size_t i = 0; i < cells.size(); ++i) {
        weights[i] = logXDensity(cells[i], step.x);
        joint[i] = weights[i] + logTargetDensity(cells[i], target, routeTime);

        if (cells[i].pos == truth.pos) {
            clockWeights.push_back(weights[i]);
            clockJoint.push_back(joint[i]);
        }
    }

    const double local = logSumExp(joint) - logSumExp(weights);
    const double clock = logSumExp(clockJoint) - logSumExp(clockWeights);
    const double oracle = logTargetDensity(truth, target, routeTime);

    return {oracle, local, clock, oracle};
}

Scores scorePaths(std::span<const RoutePath> paths, std::span<const Cell> cells,
                  bool routeTime) {
    Scores scores;

    for (const RoutePath& path : paths) {
        if (path.training) {
            continue;
        }

        std::array<double, 4> sum{};

        for (const RouteStep& step : path.steps) {
            const auto score = stepScores(step, cells, routeTime);

            for (size_t i = 0; i < sum.size(); ++i) {
                sum[i] += score[i];
            }
        }

        const double inv = 1.0 / path.steps.size();
        scores.oracle.push_back(sum[0] * inv);
        scores.local.push_back(sum[1] * inv);
        scores.clock.push_back(sum[2] * inv);
        scores.augmented.push_back(sum[3] * inv);
    }

    return scores;
}

Summary summarize(std::span<const double> values) {
    if (values.empty()) {
        throw std::runtime_error("cannot summarize an empty sample");
    }

    const double count = static_cast<double>(values.size());
    const double mean =
        std::accumulate(values.begin(), values.end(), 0.0) / count;
    double sum = 0.0;

    for (double value : values) {
        const double delta = value - mean;
        sum += delta * delta;
    }

    const double error =
        values.size() > 1 ? std::sqrt(sum / (count * (count - 1.0))) : 0.0;
    return {.mean = mean, .standardError = error, .count = values.size()};
}

Summary pairedDifference(std::span<const double> left,
                         std::span<const double> right) {
    if (left.size() != right.size()) {
        throw std::runtime_error("paired score sizes differ");
    }

    std::vector<double> values(left.size());

    for (size_t i = 0; i < values.size(); ++i) {
        values[i] = left[i] - right[i];
    }

    return summarize(values);
}

std::vector<double> makeGrid(bool routeTime, int maxP) {
    std::vector<double> grid{0.0};

    const auto append = [&](double end, double step) {
        double value = grid.back() + step;

        while (value < end) {
            grid.push_back(value);
            value += step;
        }

        if (grid.back() < end) {
            grid.push_back(end);
        }
    };

    if (!routeTime) {
        append(0.02, 0.00002);
        append(0.1, 0.0001);
        append(1.0, 0.001);
        return grid;
    }

    append(2.0, 0.002);
    append(10.0, 0.01);
    append(50.0, 0.05);
    append(static_cast<double>(maxP), 0.5);
    return grid;
}

std::vector<double> posterior(double x, std::span<const Cell> cells, int pos) {
    std::vector<double> logs(cells.size(),
                             -std::numeric_limits<double>::infinity());
    double maximum = -std::numeric_limits<double>::infinity();

    for (size_t i = 0; i < cells.size(); ++i) {
        if (pos >= 0 && cells[i].pos != pos) {
            continue;
        }

        logs[i] = logXDensity(cells[i], x);
        maximum = std::max(maximum, logs[i]);
    }

    double total = 0.0;

    for (double value : logs) {
        if (std::isfinite(value)) {
            total += std::exp(value - maximum);
        }
    }

    for (double& value : logs) {
        value = std::isfinite(value) ? std::exp(value - maximum) / total : 0.0;
    }

    return logs;
}

double integrateDifference(std::span<const double> grid,
                           std::span<const double> left,
                           std::span<const double> right) {
    double integral = 0.0;

    for (size_t i = 1; i < grid.size(); ++i) {
        const double first = std::abs(left[i - 1] - right[i - 1]);
        const double second = std::abs(left[i] - right[i]);
        integral += 0.5 * (first + second) * (grid[i] - grid[i - 1]);
    }

    return integral;
}

W1Result wasserstein(std::span<const RoutePath> paths,
                     std::span<const Cell> cells, bool routeTime, int xBins) {
    const int maxP = std::ranges::max(cells, {}, &Cell::p).p;
    const std::vector<double> grid = makeGrid(routeTime, maxP);
    std::vector<std::vector<double>> component(
        cells.size(), std::vector<double>(grid.size()));

    for (size_t c = 0; c < cells.size(); ++c) {
        for (size_t j = 0; j < grid.size(); ++j) {
            component[c][j] = targetCdf(cells[c], grid[j], routeTime);
        }
    }

    std::vector<double> localCache(static_cast<size_t>(xBins) * cells.size());
    std::vector<double> clockCache(static_cast<size_t>(xBins) * cells.size());
    std::vector<double> mix(grid.size());

    for (int bin = 0; bin < xBins; ++bin) {
        const double x = (bin + 0.5) / xBins;
        const std::vector<double> localWeights = posterior(x, cells, -1);

        std::ranges::fill(mix, 0.0);

        for (size_t c = 0; c < cells.size(); ++c) {
            for (size_t j = 0; j < grid.size(); ++j) {
                mix[j] += localWeights[c] * component[c][j];
            }
        }

        for (size_t truth = 0; truth < cells.size(); ++truth) {
            localCache[static_cast<size_t>(bin) * cells.size() + truth] =
                integrateDifference(grid, mix, component[truth]);
        }

        for (size_t pos = 0; pos < kPositions.size(); ++pos) {
            const std::vector<double> weights =
                posterior(x, cells, static_cast<int>(pos));

            std::ranges::fill(mix, 0.0);

            for (size_t c = 0; c < cells.size(); ++c) {
                for (size_t j = 0; j < grid.size(); ++j) {
                    mix[j] += weights[c] * component[c][j];
                }
            }

            for (size_t truth = 0; truth < cells.size(); ++truth) {
                if (cells[truth].pos != static_cast<int>(pos)) {
                    continue;
                }

                clockCache[static_cast<size_t>(bin) * cells.size() + truth] =
                    integrateDifference(grid, mix, component[truth]);
            }
        }
    }

    std::vector<double> local;
    std::vector<double> clock;
    std::vector<double> difference;

    for (const RoutePath& path : paths) {
        if (path.training) {
            continue;
        }

        double pathLocal = 0.0;
        double pathClock = 0.0;

        for (const RouteStep& step : path.steps) {
            const int bin =
                std::min(static_cast<int>(step.x * xBins), xBins - 1);
            const size_t offset = static_cast<size_t>(bin) * cells.size() +
                                  static_cast<size_t>(step.cell);
            pathLocal += localCache[offset];
            pathClock += clockCache[offset];
        }

        const double inv = 1.0 / path.steps.size();
        pathLocal *= inv;
        pathClock *= inv;
        local.push_back(pathLocal);
        clock.push_back(pathClock);
        difference.push_back(pathLocal - pathClock);
    }

    return {
        .xBins = xBins,
        .local = summarize(local),
        .clock = summarize(clock),
        .localMinusClock = summarize(difference),
    };
}

std::vector<double> quantileCuts(std::vector<double> values, int bins) {
    std::ranges::sort(values);
    std::vector<double> cuts;
    cuts.reserve(static_cast<size_t>(bins - 1));

    for (int bin = 1; bin < bins; ++bin) {
        const size_t i = values.size() * static_cast<size_t>(bin) /
                         static_cast<size_t>(bins);
        cuts.push_back(values[std::min(i, values.size() - 1)]);
    }

    return cuts;
}

int quantileBin(double value, std::span<const double> cuts) {
    return static_cast<int>(std::upper_bound(cuts.begin(), cuts.end(), value) -
                            cuts.begin());
}

double histogramWasserstein(std::span<const uint64_t> counts) {
    const int bins = static_cast<int>(counts.size());
    const double total =
        std::accumulate(counts.begin(), counts.end(), 0.0) + kPrior * bins;
    const double width = 1.0 / bins;
    double cumulative = 0.0;
    double result = 0.0;

    for (int bin = 0; bin < bins; ++bin) {
        const double probability =
            (static_cast<double>(counts[static_cast<size_t>(bin)]) + kPrior) /
            total;
        const double left = cumulative - bin * width;
        const double right = cumulative + probability - (bin + 1) * width;

        if (left * right >= 0.0) {
            result += 0.5 * width * (std::abs(left) + std::abs(right));
        } else {
            result += width * (left * left + right * right) /
                      (2.0 * (std::abs(left) + std::abs(right)));
        }

        cumulative += probability;
    }

    return result;
}

HistoryResult scoreHistory(std::span<const RoutePath> paths,
                           std::span<const Cell> cells, std::string_view state,
                           int histBins, int pitBins) {
    std::vector<double> first;
    std::vector<double> second;

    for (const RoutePath& path : paths) {
        if (!path.training) {
            continue;
        }

        for (const RouteStep& step : path.steps) {
            if (state == "last_fraction" || state == "joint") {
                first.push_back(step.last);
            }

            if (state == "quadratic_concentration" || state == "joint") {
                second.push_back(step.quad);
            }
        }
    }

    const std::vector<double> firstCuts =
        first.empty() ? std::vector<double>{}
                      : quantileCuts(std::move(first), histBins);
    const std::vector<double> secondCuts =
        second.empty() ? std::vector<double>{}
                       : quantileCuts(std::move(second), histBins);
    const int classes = state == "joint" ? histBins * histBins : histBins;
    std::vector<uint64_t> counts(static_cast<size_t>(classes * pitBins));
    std::vector<uint64_t> classCounts(static_cast<size_t>(classes));
    size_t training = 0;

    const auto classOf = [&](const RouteStep& step) {
        if (state == "last_fraction") {
            return quantileBin(step.last, firstCuts);
        }

        if (state == "quadratic_concentration") {
            return quantileBin(step.quad, secondCuts);
        }

        const int row = quantileBin(step.last, firstCuts);
        const int col = quantileBin(step.quad, secondCuts);
        return row * histBins + col;
    };

    for (const RoutePath& path : paths) {
        if (!path.training) {
            continue;
        }

        for (const RouteStep& step : path.steps) {
            const int cls = classOf(step);
            const double u = betaCdf(cells[step.cell].k, step.z);
            const int bin =
                std::min(static_cast<int>(u * pitBins), pitBins - 1);
            const size_t offset =
                static_cast<size_t>(cls) * pitBins + static_cast<size_t>(bin);
            ++counts[offset];
            ++classCounts[static_cast<size_t>(cls)];
            ++training;
        }
    }

    std::vector<double> classW1(static_cast<size_t>(classes));
    size_t occupied = 0;

    for (int cls = 0; cls < classes; ++cls) {
        const size_t offset =
            static_cast<size_t>(cls) * static_cast<size_t>(pitBins);
        const auto row =
            std::span(counts).subspan(offset, static_cast<size_t>(pitBins));
        classW1[static_cast<size_t>(cls)] = histogramWasserstein(row);
        occupied += classCounts[static_cast<size_t>(cls)] > 0;
    }

    std::vector<double> gains;
    std::vector<double> distances;
    size_t heldOut = 0;

    for (const RoutePath& path : paths) {
        if (path.training) {
            continue;
        }

        double gain = 0.0;
        double distance = 0.0;

        for (const RouteStep& step : path.steps) {
            const int cls = classOf(step);
            const double u = betaCdf(cells[step.cell].k, step.z);
            const int bin =
                std::min(static_cast<int>(u * pitBins), pitBins - 1);
            const double total =
                static_cast<double>(classCounts[static_cast<size_t>(cls)]) +
                kPrior * pitBins;
            const size_t offset =
                static_cast<size_t>(cls) * pitBins + static_cast<size_t>(bin);
            const double probability =
                (static_cast<double>(counts[offset]) + kPrior) / total;

            gain += std::log(pitBins * probability);
            distance += classW1[static_cast<size_t>(cls)];
            ++heldOut;
        }

        const double inv = 1.0 / path.steps.size();
        gains.push_back(gain * inv);
        distances.push_back(distance * inv);
    }

    return {
        .state = std::string(state),
        .historyBins = histBins,
        .pitBins = pitBins,
        .logGain = summarize(gains),
        .pitWasserstein = summarize(distances),
        .occupiedClasses = occupied,
        .trainingTransitions = training,
        .heldOutTransitions = heldOut,
    };
}

double correlation(std::span<const double> left,
                   std::span<const double> right) {
    if (left.size() != right.size() || left.empty()) {
        throw std::runtime_error("correlation sample sizes differ");
    }

    const double count = static_cast<double>(left.size());
    const double leftMean =
        std::accumulate(left.begin(), left.end(), 0.0) / count;
    const double rightMean =
        std::accumulate(right.begin(), right.end(), 0.0) / count;
    double cov = 0.0;
    double leftVar = 0.0;
    double rightVar = 0.0;

    for (size_t i = 0; i < left.size(); ++i) {
        const double x = left[i] - leftMean;
        const double y = right[i] - rightMean;
        cov += x * y;
        leftVar += x * x;
        rightVar += y * y;
    }

    return cov / std::sqrt(leftVar * rightVar);
}

Audit auditConditionalLaw(std::span<const RoutePath> paths,
                          std::span<const Cell> cells) {
    std::vector<double> pit;
    std::vector<double> last;
    std::vector<double> quad;
    std::vector<double> sums(cells.size());
    std::vector<size_t> counts(cells.size());

    for (const RoutePath& path : paths) {
        if (path.training) {
            continue;
        }

        for (const RouteStep& step : path.steps) {
            const Cell& cell = cells[step.cell];
            pit.push_back(betaCdf(cell.k, step.z));
            last.push_back(step.last);
            quad.push_back(step.quad);
            sums[step.cell] += step.z;
            ++counts[step.cell];
        }
    }

    const double count = static_cast<double>(pit.size());
    const double mean = std::accumulate(pit.begin(), pit.end(), 0.0) / count;
    double variance = 0.0;

    for (double value : pit) {
        const double delta = value - mean;
        variance += delta * delta;
    }

    variance /= count;
    std::vector<double> sorted = pit;
    std::ranges::sort(sorted);
    double ks = 0.0;

    for (size_t i = 0; i < sorted.size(); ++i) {
        const double lower = static_cast<double>(i) / count;
        const double upper = static_cast<double>(i + 1) / count;
        ks = std::max(
            {ks, std::abs(sorted[i] - lower), std::abs(sorted[i] - upper)});
    }

    double maxError = 0.0;

    for (size_t i = 0; i < cells.size(); ++i) {
        const double empirical = sums[i] / static_cast<double>(counts[i]);
        const double exact = 2.0 / (2.0 * cells[i].k + 1.0);
        maxError = std::max(maxError, std::abs(empirical - exact));
    }

    return {
        .pitMean = mean,
        .pitVariance = variance,
        .pitKolmogorov = ks,
        .maxConditionalMeanError = maxError,
        .pitLastCorrelation = correlation(pit, last),
        .pitQuadCorrelation = correlation(pit, quad),
    };
}

ScaleResult analyzeScale(const Options& opt, int scale) {
    std::vector<int> horizons;
    horizons.reserve(opt.horizons.size());

    for (int p : opt.horizons) {
        horizons.push_back(scale * p);
    }

    const std::vector<Cell> cells = makeCells(horizons);
    const std::vector<RoutePath> paths =
        samplePaths(horizons, opt.paths, opt.seed, scale, opt.threads);
    ScaleResult result;
    result.scale = scale;
    result.horizons = horizons;
    result.trainingPaths = horizons.size() * (opt.paths / 2);
    result.heldOutPaths = result.trainingPaths;
    result.heldOutTransitions = result.heldOutPaths * kPositions.size();
    result.audit = auditConditionalLaw(paths, cells);
    result.fractionScores = scorePaths(paths, cells, false);
    result.routeTimeScores = scorePaths(paths, cells, true);

    for (int bins : kXBins) {
        result.fractionW1.push_back(wasserstein(paths, cells, false, bins));
        result.routeTimeW1.push_back(wasserstein(paths, cells, true, bins));
    }

    constexpr std::array<std::string_view, 3> states{
        "last_fraction", "quadratic_concentration", "joint"};

    for (std::string_view state : states) {
        for (int histBins : kHistoryBins) {
            for (int pitBins : kPitBins) {
                result.history.push_back(
                    scoreHistory(paths, cells, state, histBins, pitBins));
            }
        }
    }

    return result;
}

void printInts(std::ostream& out, std::span<const int> values) {
    std::print(out, "[");

    for (size_t i = 0; i < values.size(); ++i) {
        std::print(out, "{}{}", i == 0 ? "" : ",", values[i]);
    }

    std::print(out, "]");
}

void printSummary(std::ostream& out, const Summary& value) {
    std::print(out,
               "{{\"mean\":{:.17g},\"standard_error\":{:.17g},"
               "\"path_count\":{}}}",
               value.mean, value.standardError, value.count);
}

void printScores(std::ostream& out, const Scores& scores) {
    std::print(out, "{{\n      \"oracle\":");
    printSummary(out, summarize(scores.oracle));
    std::print(out, ",\n      \"clock_free_local\":");
    printSummary(out, summarize(scores.local));
    std::print(out, ",\n      \"normalized_clock\":");
    printSummary(out, summarize(scores.clock));
    std::print(out, ",\n      \"exact_augmented\":");
    printSummary(out, summarize(scores.augmented));
    std::print(out, ",\n      \"paired_differences\":{{\n");
    std::print(out, "        \"normalized_clock_minus_clock_free\":");
    printSummary(out, pairedDifference(scores.clock, scores.local));
    std::print(out, ",\n        \"clock_free_minus_oracle\":");
    printSummary(out, pairedDifference(scores.local, scores.oracle));
    std::print(out, ",\n        \"normalized_clock_minus_oracle\":");
    printSummary(out, pairedDifference(scores.clock, scores.oracle));
    std::print(out, ",\n        \"exact_augmented_minus_oracle\":");
    printSummary(out, pairedDifference(scores.augmented, scores.oracle));
    std::print(out, "\n      }}\n    }}");
}

void printW1(std::ostream& out, std::span<const W1Result> values) {
    std::print(out, "[");

    for (size_t i = 0; i < values.size(); ++i) {
        if (i > 0) {
            std::print(out, ",");
        }

        std::print(out, "\n      {{\"x_bins\":{},\"clock_free_to_oracle\":",
                   values[i].xBins);
        printSummary(out, values[i].local);
        std::print(out, ",\"normalized_clock_to_oracle\":");
        printSummary(out, values[i].clock);
        std::print(out, ",\"clock_free_minus_normalized_clock\":");
        printSummary(out, values[i].localMinusClock);
        std::print(out,
                   ",\"exact_augmented_to_oracle\":{{\"mean\":0,"
                   "\"standard_error\":0,\"path_count\":{}}}}}",
                   values[i].local.count);
    }

    std::print(out, "\n    ]");
}

void printHistory(std::ostream& out, std::span<const HistoryResult> values) {
    std::print(out, "[");

    for (size_t i = 0; i < values.size(); ++i) {
        if (i > 0) {
            std::print(out, ",");
        }

        const HistoryResult& value = values[i];
        std::print(out,
                   "\n      {{\"state\":\"{}\",\"history_bins\":{},"
                   "\"pit_bins\":{},\"occupied_classes\":{},"
                   "\"training_transitions\":{},"
                   "\"held_out_transitions\":{},\"held_out_log_gain\":",
                   value.state, value.historyBins, value.pitBins,
                   value.occupiedClasses, value.trainingTransitions,
                   value.heldOutTransitions);
        printSummary(out, value.logGain);
        std::print(out, ",\"pit_wasserstein_to_oracle\":");
        printSummary(out, value.pitWasserstein);
        std::print(out, "}}");
    }

    std::print(out, "\n    ]");
}

void writeOutput(const Options& opt, std::span<const ScaleResult> results,
                 double seconds) {
    const std::filesystem::path parent = opt.output.parent_path();

    if (!parent.empty()) {
        std::filesystem::create_directories(parent);
    }

    if (std::filesystem::exists(opt.output) && !opt.overwrite) {
        throw std::runtime_error(
            std::format("output exists: {}", opt.output.string()));
    }

    std::filesystem::path temporary = opt.output;
    temporary += ".tmp";
    std::ofstream out(temporary);

    if (!out) {
        throw std::runtime_error(
            std::format("cannot create artifact: {}", temporary.string()));
    }

    std::print(out, "{{\n"
                    "  \"schema\":\"bounded-systems.gap-clock-control.v1\",\n"
                    "  \"configuration\":{{\"base_horizons\":");
    printInts(out, opt.horizons);
    std::print(out, ",\"scales\":");
    printInts(out, opt.scales);
    std::print(out,
               ",\"positions\":[1,2,3,4,5,6,7],"
               "\"position_denominator\":8,\"paths_per_horizon\":{},"
               "\"master_seed\":\"{}\",\"requested_threads\":{},"
               "\"history_bins\":[2,4,8],\"pit_bins\":[16,32,64],"
               "\"x_projection_bins\":[64,128,256],"
               "\"train_rule\":\"even path index\","
               "\"holdout_rule\":\"odd path index\"}},\n",
               opt.paths, opt.seed, opt.threads);
    std::print(
        out,
        "  \"transition_law\":{{"
        "\"fraction\":\"G_(r+1)/(1-X_r)\","
        "\"conditional\":\"Beta(2,2(p-r)-1)\","
        "\"route_time_target\":\"p G_(r+1)/(1-X_r)\","
        "\"history\":[\"G_r/X_r\","
        "\"sum_(j<=r)(G_j/X_r)^2\"],"
        "\"history_density_prior\":0.5}},\n"
        "  \"predictors\":{{"
        "\"clock_free_local\":\"exact design mixture given X_r\","
        "\"normalized_clock\":\"exact design mixture given (X_r,r/p)\","
        "\"exact_augmented\":\"Beta component given (X_r,r,p)\","
        "\"oracle\":\"full Dirichlet conditional component\"}},\n"
        "  \"metrics\":{{"
        "\"log_score\":\"held-out natural log density\","
        "\"wasserstein\":\"conditional one-dimensional W1 to oracle\","
        "\"uncertainty\":\"ordinary standard error of paired path means\"}},\n"
        "  \"scale_groups\":[");

    for (size_t i = 0; i < results.size(); ++i) {
        if (i > 0) {
            std::print(out, ",");
        }

        const ScaleResult& result = results[i];
        std::print(out, "\n    {{\"scale\":{},\"horizons\":", result.scale);
        printInts(out, result.horizons);
        std::print(out,
                   ",\"training_paths\":{},\"held_out_paths\":{},"
                   "\"held_out_transitions\":{},\n"
                   "     \"conditional_audit\":{{"
                   "\"pit_mean\":{:.17g},\"pit_variance\":{:.17g},"
                   "\"pit_kolmogorov\":{:.17g},"
                   "\"max_conditional_mean_error\":{:.17g},"
                   "\"pit_last_fraction_correlation\":{:.17g},"
                   "\"pit_quadratic_concentration_correlation\":{:.17g}}},\n"
                   "     \"log_score\":{{\n"
                   "      \"remaining_fraction\":",
                   result.trainingPaths, result.heldOutPaths,
                   result.heldOutTransitions, result.audit.pitMean,
                   result.audit.pitVariance, result.audit.pitKolmogorov,
                   result.audit.maxConditionalMeanError,
                   result.audit.pitLastCorrelation,
                   result.audit.pitQuadCorrelation);
        printScores(out, result.fractionScores);
        std::print(out, ",\n      \"route_time_scaled\":");
        printScores(out, result.routeTimeScores);
        std::print(out, "\n     }},\n     \"wasserstein\":{{\n");
        std::print(out, "      \"remaining_fraction\":");
        printW1(out, result.fractionW1);
        std::print(out, ",\n      \"route_time_scaled\":");
        printW1(out, result.routeTimeW1);
        std::print(out, "\n     }},\n     \"history_positive_control\":");
        printHistory(out, result.history);
        std::print(out, "\n    }}");
    }

    std::print(out,
               "\n  ],\n"
               "  \"runtime\":{{\"wall_seconds\":{:.9f},"
               "\"compiler\":\"{}\"}}\n"
               "}}\n",
               seconds, __VERSION__);
    out.close();

    if (!out) {
        throw std::runtime_error(std::format(
            "failed while writing artifact: {}", temporary.string()));
    }

    std::filesystem::rename(temporary, opt.output);
}

size_t runSelfTests() {
    size_t checks = 0;

    for (int k = 1; k <= 64; ++k) {
        const double mean = 2.0 / (2.0 * k + 1.0);
        const double step = 1.0e-6;
        double integral = 0.0;

        for (int i = 0; i < 1'000; ++i) {
            const double z = (i + 0.5) / 1'000.0;
            integral += std::exp(logZDensity(k, z)) / 1'000.0;
        }

        const double derivative =
            (betaCdf(k, mean + step) - betaCdf(k, mean - step)) / (2.0 * step);

        if (std::abs(integral - 1.0) > 2.0e-3 ||
            std::abs(derivative - std::exp(logZDensity(k, mean))) > 1.0e-6) {
            throw std::runtime_error("Beta density self-test failed");
        }

        checks += 2;
    }

    const std::vector<double> grid = makeGrid(false, 64);
    std::vector<double> first(grid.size());
    std::vector<double> second(grid.size());

    for (size_t i = 0; i < grid.size(); ++i) {
        first[i] = betaCdf(2, grid[i]);
        second[i] = betaCdf(64, grid[i]);
    }

    const double numerical = integrateDifference(grid, first, second);
    const double exact = 2.0 / 5.0 - 2.0 / 129.0;

    if (std::abs(numerical - exact) > 2.0e-6) {
        throw std::runtime_error("Wasserstein quadrature self-test failed");
    }

    ++checks;

    const std::vector<int> horizons{8, 16};
    const std::vector<Cell> cells = makeCells(horizons);
    const std::vector<RoutePath> paths = samplePaths(horizons, 200, 17, 1, 1);
    const Scores scores = scorePaths(paths, cells, false);

    for (size_t i = 0; i < scores.oracle.size(); ++i) {
        if (scores.oracle[i] != scores.augmented[i]) {
            throw std::runtime_error("augmented score self-test failed");
        }

        ++checks;
    }

    const Audit audit = auditConditionalLaw(paths, cells);

    if (std::abs(audit.pitMean - 0.5) > 0.04 ||
        std::abs(audit.pitVariance - 1.0 / 12.0) > 0.015) {
        throw std::runtime_error("conditional PIT self-test failed");
    }

    checks += 2;
    return checks;
}

} // namespace

int main(int argc, char** argv) {
    try {
        const std::span args(argv + 1, static_cast<size_t>(argc - 1));
        const Options opt = parseOptions(args);

        if (opt.selfTest) {
            const size_t checks = runSelfTests();
            std::println("gap clock-control self-tests passed: {} checks",
                         checks);
            return 0;
        }

        const auto start = std::chrono::steady_clock::now();
        std::vector<ScaleResult> results;
        results.reserve(opt.scales.size());

        for (int scale : opt.scales) {
            results.push_back(analyzeScale(opt, scale));
        }

        const double seconds = std::chrono::duration<double>(
                                   std::chrono::steady_clock::now() - start)
                                   .count();
        writeOutput(opt, results, seconds);
        std::println(stderr, "wrote {} in {:.3f} seconds", opt.output.string(),
                     seconds);
        return 0;
    } catch (const std::exception& error) {
        std::println(stderr, "fatal: {}", error.what());
        printUsage(argc > 0 ? argv[0] : "gap-clock-control");
        return 2;
    }
}
