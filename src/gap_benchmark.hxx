#pragma once

#include "reference_dag.hxx"
#include "route_bridge.hxx"
#include "route_scaling.hxx"

#include <cstddef>
#include <cstdint>
#include <filesystem>
#include <vector>

struct GapOptions {
    size_t vertexCount = 0;
    std::vector<int> horizons;
    size_t sampleCount = 0;
    uint64_t seed = 0;
    size_t threadCount = 0;
    std::filesystem::path outputDirectory;
    std::vector<int> bins{8, 16, 32};
    std::vector<double> thresholds{0.01, 0.025, 0.05, 0.1, 0.2};
    std::vector<int> predictiveClasses{8, 16, 32};
    std::vector<int> targetBins{16, 32, 64};
    int referenceBins = 256;
    int validationLength = 4;
    int modeCount = 4;
    double bulkFraction = 0.2;
    bool overwrite = false;
};

struct GapSample {
    size_t index = 0;
    uint64_t seed = 0;
    size_t vertexCount = 0;
    size_t edgeCount = 0;
    size_t height = 0;
    double edgeDensity = 0.0;
    double pairDensity = 0.0;
    double generationSeconds = 0.0;
    double stateSeconds = 0.0;
    double routeSeconds = 0.0;
    double totalSeconds = 0.0;
    size_t graphBytes = 0;
    size_t stateBytes = 0;
    size_t routeBytes = 0;
    size_t peakBytes = 0;
    LatentStateValidation latentCheck;
    IntrinsicStateScaling intrinsicScaling;
    SignatureSummary signatures;
    std::vector<double> modes;
    std::vector<RouteCalibration> calibration;
    std::vector<HorizonResult> horizons;
    std::vector<RouteScalingResult> scaling;
    long double maxLogError = 0.0L;
};
