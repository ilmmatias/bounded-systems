#pragma once

#include "route_bridge.hxx"

#include <array>
#include <cstddef>
#include <cstdint>
#include <span>
#include <string>
#include <vector>

constexpr size_t kPredictiveMomentCount = kGapCoordinateCount + 1;
using PredictiveMoment = std::array<double, kPredictiveMomentCount>;

struct IntrinsicStateScaling {
    double intrinsicMarkMinimum = 0.0;
    double intrinsicMarkMaximum = 0.0;
    double transverseResidualRms = 0.0;
    double scaledTransverseResidualRms = 0.0;
    GapCoordinate coordinateResidualRms{};
    GapCoordinate scaledCoordinateResidualRms{};
};

struct PredictivePartition {
    std::string state;
    size_t featureCount = 0;
    size_t requestedClasses = 0;
    std::vector<uint32_t> classIds;
    std::vector<uint32_t> classSizes;
    std::vector<uint8_t> training;
};

struct RouteProfilePosition {
    int position = 0;
    double scaledPosition = 0.0;
    double betaMean = 0.0;
    double betaVariance = 0.0;
    double latentMean = 0.0;
    double latentVariance = 0.0;
    double latentKolmogorov = 0.0;
    double intrinsicMean = 0.0;
    double intrinsicVariance = 0.0;
    double intrinsicKolmogorov = 0.0;
    double intrinsicOutsideMass = 0.0;
    double intrinsicOracleRmse = 0.0;
    double scaledIntrinsicMeanError = 0.0;
    double scaledIntrinsicVariance = 0.0;
    double scaledLatentVariance = 0.0;
};

struct RouteSpacingPosition {
    int position = 0;
    int remainingEdges = 0;
    double gapMean = 0.0;
    double gapTargetMean = 0.0;
    double gapVariance = 0.0;
    double gapTargetVariance = 0.0;
    double gapKolmogorovBound = 0.0;
    double conditionalFractionMean = 0.0;
    double conditionalFractionTargetMean = 0.0;
    double conditionalFractionVariance = 0.0;
    double conditionalFractionTargetVariance = 0.0;
    double conditionalFractionKolmogorovBound = 0.0;
    double sourceFractionCovariance = 0.0;
    double sourceFractionCorrelation = 0.0;
};

struct ScaledLindebergTail {
    double threshold = 0.0;
    double sum = 0.0;
};

struct PredictionDistributionMetric {
    int targetBins = 0;
    double exactTotalVariation = 0.0;
    double exactWasserstein1 = 0.0;
    double heldOutTotalVariation = 0.0;
    double heldOutWasserstein1 = 0.0;
};

struct PredictivePosition {
    int position = 0;
    double scaledPosition = 0.0;
    size_t occupiedClasses = 0;
    size_t trainingOccupiedClasses = 0;
    double singletonRouteMass = 0.0;
    double trainingRouteMass = 0.0;
    double heldOutRouteMass = 0.0;
    double heldOutCoveredMass = 0.0;
    PredictiveMoment exactMomentRmse{};
    PredictiveMoment heldOutMomentRmse{};
    double exactMomentR2 = 0.0;
    double heldOutMomentR2 = 0.0;
    std::vector<PredictionDistributionMetric> distributions;
};

struct PredictiveClosureResult {
    std::string state;
    size_t featureCount = 0;
    size_t requestedClasses = 0;
    size_t realizedClasses = 0;
    size_t singletonClasses = 0;
    size_t largestClass = 0;
    std::vector<uint32_t> classSizes;
    std::vector<PredictivePosition> positions;
};

struct RouteScalingResult {
    int horizon = 0;
    bool hasRoutes = false;
    std::vector<RouteProfilePosition> routeProfile;
    std::vector<RouteSpacingPosition> spacing;
    double macroscopicMaximalJump = 0.0;
    double intrinsicFluctuationMaximalJump = 0.0;
    std::vector<ScaledLindebergTail> intrinsicLindeberg;
    std::vector<PredictiveClosureResult> predictiveClosure;
    double seconds = 0.0;
    size_t peakBytes = 0;
};

IntrinsicStateScaling summarizeIntrinsicState(const GapNodeState& state);
std::vector<PredictivePartition>
buildPredictivePartitions(const ReferenceDag& graph, const GapNodeState& state,
                          std::span<const int> requestedClasses);
RouteScalingResult analyzeRouteScaling(
    const ReferenceDag& graph, const GapNodeState& state,
    const StableRouteCounts& routes, const HorizonResult& bridge,
    std::span<const PredictivePartition> partitions,
    std::span<const int> targetBins, std::span<const double> thresholds,
    double bulkFraction, int referenceBins);

size_t runRouteScalingSelfTests();
