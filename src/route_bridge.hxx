#pragma once

#include "reference_dag.hxx"

#include <array>
#include <cstddef>
#include <cstdint>
#include <span>
#include <vector>

constexpr size_t kGapCovarianceCount = 21;
constexpr size_t kGapThirdMomentCount = 56;

using GapCovariance = std::array<double, kGapCovarianceCount>;
using GapThirdMoment = std::array<double, kGapThirdMomentCount>;

struct StableRouteCounts {
    std::vector<std::vector<long double>> forward;
    std::vector<std::vector<long double>> backward;
    std::vector<long double> forwardLogs;
    std::vector<long double> backwardLogs;
    std::vector<long double> forwardScales;
    long double maxLogError = 0.0L;

    size_t maxHorizon() const;
    bool hasRoutes(size_t horizon) const;
    size_t estimatedBytes() const;
};

struct SignatureSummary {
    size_t classCount = 0;
    size_t singletonClasses = 0;
    size_t singletonNodes = 0;
    size_t largestClass = 0;
    bool degenerate = false;
    std::vector<uint32_t> classSizes;
};

struct ProfilePartition {
    int bins = 0;
    std::vector<uint32_t> classIds;
    std::vector<uint32_t> classSizes;
};

struct RouteCalibration {
    int length = 0;
    long double logCount = 0.0L;
    double pathDensity = 0.0;
    double pathTarget = 0.0;
    double routeMean = 0.0;
    double routeTarget = 0.0;
    double scaledFluctuation = 0.0;
    double modePrediction = 0.0;
    double modeResidual = 0.0;
};

struct PositionResult {
    int position = 0;
    double scaledPosition = 0.0;
    GapCoordinate mean{};
    GapCovariance covariance{};
    double variance = 0.0;
    double flowError = 0.0;
    double rowError = 0.0;
};

struct TailResult {
    double threshold = 0.0;
    double tail = 0.0;
    double scaled = 0.0;
};

struct ClosurePosition {
    int position = 0;
    size_t occupiedClasses = 0;
    double singletonMass = 0.0;
    double assessableMass = 0.0;
    double meanEffectiveSize = 0.0;
    double rmsDefect = 0.0;
    double maxDefect = 0.0;
};

struct ClosureResult {
    int bins = 0;
    size_t classCount = 0;
    size_t singletonClasses = 0;
    size_t largestClass = 0;
    std::vector<uint32_t> classSizes;
    std::vector<ClosurePosition> positions;
    double rmsDefect = 0.0;
    double maxDefect = 0.0;
    double minMass = 0.0;
    double plateauDefect = 0.0;
};

struct HorizonResult {
    int p = 0;
    bool hasRoutes = false;
    long double logCount = 0.0L;
    long double logNextCount = 0.0L;
    double growth = 0.0;
    double logGrowth = 0.0;
    double expectedGrowth = 0.0;
    double maxFlowError = 0.0;
    double meanFlowError = 0.0;
    double maxRowError = 0.0;
    GapCoordinate mean{};
    GapCovariance rawSecond{};
    GapCovariance covariance{};
    GapCovariance withinPositionCovariance{};
    GapCovariance betweenPositionCovariance{};
    GapThirdMoment rawThird{};
    GapThirdMoment centeredThird{};
    GapThirdMoment withinPositionCenteredThird{};
    double timeScale = 0.0;
    double withinCovarianceTrace = 0.0;
    double betweenCovarianceTrace = 0.0;
    double covarianceDecompositionError = 0.0;
    double withinPositionThirdNorm = 0.0;
    double maxJump = 0.0;
    double scaledJump = 0.0;
    double scaledRawThird = 0.0;
    double scaledCenteredThird = 0.0;
    std::vector<TailResult> tails;
    std::vector<PositionResult> positions;
    int bulkFirst = 0;
    int bulkLast = 0;
    double driftPlateau = 0.0;
    double covariancePlateau = 0.0;
    double plateauDefect = 0.0;
    std::vector<ClosureResult> closure;
    double seconds = 0.0;
    size_t peakBytes = 0;
};

StableRouteCounts computeRouteCounts(const ReferenceDag& graph,
                                     size_t maxHorizon);
SignatureSummary summarizeSignatures(const GapNodeState& state);
std::vector<ProfilePartition> buildPartitions(const GapNodeState& state,
                                              std::span<const int> bins);
std::vector<double> computeLegendreModes(const ReferenceDag& graph,
                                         int modeCount);
std::vector<RouteCalibration>
computeCalibration(const ReferenceDag& graph, const StableRouteCounts& routes,
                   std::span<const double> modes, int maxLength);
HorizonResult analyzeHorizon(const ReferenceDag& graph,
                             const GapNodeState& state,
                             const StableRouteCounts& routes, int p,
                             std::span<const ProfilePartition> partitions,
                             double bulk, std::span<const double> thresholds);

size_t runRouteSelfTests();
