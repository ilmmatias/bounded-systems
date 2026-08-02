#include "gap_output.hxx"

#include <algorithm>
#include <array>
#include <cmath>
#include <filesystem>
#include <format>
#include <fstream>
#include <ostream>
#include <print>
#include <stdexcept>
#include <string>
#include <string_view>
#include <sys/resource.h>
#include <thread>

namespace {

void printText(std::ostream& out, std::string_view text) {
    std::print(out, "{}", text);
}

void printString(std::ostream& out, std::string_view text) {
    printText(out, "\"");

    for (const unsigned char byte : text) {
        switch (byte) {
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
            if (byte < 0x20) {
                std::print(out, "\\u{:04x}", byte);
            } else {
                std::print(out, "{}", static_cast<char>(byte));
            }
        }
    }

    printText(out, "\"");
}

void printNumber(std::ostream& out, double value) {
    if (std::isfinite(value)) {
        std::print(out, "{:.17g}", value);
    } else {
        printText(out, "null");
    }
}

void printNumber(std::ostream& out, long double value) {
    if (std::isfinite(value)) {
        std::print(out, "{:.21g}", value);
    } else {
        printText(out, "null");
    }
}

template <typename Range>
void printNumbers(std::ostream& out, const Range& values) {
    printText(out, "[");

    for (size_t index = 0; index < values.size(); ++index) {
        if (index != 0) {
            printText(out, ",");
        }
        printNumber(out, static_cast<double>(values[index]));
    }

    printText(out, "]");
}

template <typename Range>
void printScaledNumbers(std::ostream& out, const Range& values, double scale) {
    printText(out, "[");

    for (size_t index = 0; index < values.size(); ++index) {
        if (index != 0) {
            printText(out, ",");
        }
        printNumber(out, scale * static_cast<double>(values[index]));
    }

    printText(out, "]");
}

template <typename Range>
void printIntegers(std::ostream& out, const Range& values) {
    printText(out, "[");

    for (size_t index = 0; index < values.size(); ++index) {
        if (index != 0) {
            printText(out, ",");
        }
        std::print(out, "{}", values[index]);
    }

    printText(out, "]");
}

void printCount(std::ostream& out, long double logCount) {
    printText(out, R"({"log":)");
    printNumber(out, logCount);

    if (std::isfinite(logCount)) {
        constexpr long double logTen = 2.3025850929940456840179914546843642L;
        const long double exponentValue = std::floor(logCount / logTen);
        const auto exponent = static_cast<long long>(exponentValue);
        const long double mantissa =
            std::exp(logCount - exponentValue * logTen);

        printText(out, R"(,"mantissa":)");
        printNumber(out, mantissa);
        std::print(out, R"(,"base10_exponent":{})", exponent);
    } else {
        printText(out, R"(,"mantissa":null,"base10_exponent":null)");
    }

    printText(out, "}");
}

void printGraph(std::ostream& out, const GapSample& sample) {
    printText(out, R"({"schema":"bounded-systems.gap-graph.v2")");
    std::print(out, R"(,"sample_index":{})", sample.index);
    std::print(out, R"(,"sample_seed":"{}")", sample.seed);
    std::print(out, R"(,"vertices":{})", sample.vertexCount);
    std::print(out, R"(,"edges":{})", sample.edgeCount);
    std::print(out, R"(,"height":{})", sample.height);

    printText(out, R"(,"directed_edge_density":)");
    printNumber(out, sample.edgeDensity);
    printText(out, R"(,"directed_edge_target":)");
    printNumber(out, 1.0 / 6.0);
    printText(out, R"(,"directed_edge_error":)");
    printNumber(out, sample.edgeDensity - 1.0 / 6.0);
    printText(out, R"(,"unoriented_edge_density":)");
    printNumber(out, sample.pairDensity);
    printText(out, R"(,"unoriented_edge_target":)");
    printNumber(out, 1.0 / 3.0);

    printText(out, R"(,"timing_seconds":{"generation":)");
    printNumber(out, sample.generationSeconds);
    printText(out, R"(,"node_state":)");
    printNumber(out, sample.stateSeconds);
    printText(out, R"(,"route_counts":)");
    printNumber(out, sample.routeSeconds);
    printText(out, R"(,"total":)");
    printNumber(out, sample.totalSeconds);
    printText(out, "}");

    std::print(out,
               R"(,"estimated_bytes":{{"graph":{},"node_state":{},)"
               R"("route_workspace":{},"peak":{}}})",
               sample.graphBytes, sample.stateBytes, sample.routeBytes,
               sample.peakBytes);

    printText(out, R"(,"latent_validation":{"coordinate_rmse":)");
    printNumbers(out, sample.latentCheck.coordinateRmse);
    printText(out, R"(,"total_coordinate_rmse":)");
    printNumber(out, sample.latentCheck.totalCoordinateRmse);
    printText(out, R"(,"reconstructed_mark_rmse":)");
    printNumber(out, sample.latentCheck.reconstructedMarkRmse);
    printText(out, R"(,"reconstructed_mark_max_error":)");
    printNumber(out, sample.latentCheck.reconstructedMarkMaxError);
    printText(out, "}");

    printText(out, R"(,"intrinsic_scaling":{"mark_minimum":)");
    printNumber(out, sample.intrinsicScaling.intrinsicMarkMinimum);
    printText(out, R"(,"mark_maximum":)");
    printNumber(out, sample.intrinsicScaling.intrinsicMarkMaximum);
    printText(out, R"(,"transverse_residual_rms":)");
    printNumber(out, sample.intrinsicScaling.transverseResidualRms);
    printText(out, R"(,"sqrt_N_transverse_residual_rms":)");
    printNumber(out, sample.intrinsicScaling.scaledTransverseResidualRms);
    printText(out, R"(,"coordinate_residual_rms":)");
    printNumbers(out, sample.intrinsicScaling.coordinateResidualRms);
    printText(out, R"(,"sqrt_N_coordinate_residual_rms":)");
    printNumbers(out, sample.intrinsicScaling.scaledCoordinateResidualRms);
    printText(out, "}");

    std::print(out,
               R"(,"exact_signature":{{"class_count":{},)"
               R"("singleton_class_count":{},"singleton_node_count":{},)"
               R"("largest_class_size":{},"closure_degenerate":{})",
               sample.signatures.classCount, sample.signatures.singletonClasses,
               sample.signatures.singletonNodes, sample.signatures.largestClass,
               sample.signatures.degenerate);
    printText(out, R"(,"class_sizes":)");
    printIntegers(out, sample.signatures.classSizes);
    printText(out, "}");

    printText(out, R"(,"even_legendre_modes":)");
    printNumbers(out, sample.modes);
    printText(out, R"(,"route_calibration":[)");

    for (size_t index = 0; index < sample.calibration.size(); ++index) {
        if (index != 0) {
            printText(out, ",");
        }

        const RouteCalibration& check = sample.calibration[index];
        std::print(out, R"({{"length":{},"route_count":)", check.length);
        printCount(out, check.logCount);
        printText(out, R"(,"path_homomorphism_density":)");
        printNumber(out, check.pathDensity);
        printText(out, R"(,"path_homomorphism_target":)");
        printNumber(out, check.pathTarget);
        printText(out, R"(,"path_homomorphism_error":)");
        printNumber(out, check.pathDensity - check.pathTarget);
        printText(out, R"(,"subset_route_mean":)");
        printNumber(out, check.routeMean);
        printText(out, R"(,"subset_route_target":)");
        printNumber(out, check.routeTarget);
        printText(out, R"(,"subset_route_error":)");
        printNumber(out, check.routeMean - check.routeTarget);
        printText(out, R"(,"scaled_route_fluctuation":)");
        printNumber(out, check.scaledFluctuation);
        printText(out, R"(,"leading_mode_prediction":)");
        printNumber(out, check.modePrediction);
        printText(out, R"(,"leading_mode_residual":)");
        printNumber(out, check.modeResidual);
        printText(out, "}");
    }

    std::println(out, "]}}");
}

void printClosure(std::ostream& out, const ClosureResult& closure) {
    std::print(out,
               R"({{"bins_per_coordinate":{},"class_count":{},)"
               R"("singleton_class_count":{},"largest_class_size":{})",
               closure.bins, closure.classCount, closure.singletonClasses,
               closure.largestClass);

    printText(out, R"(,"class_sizes":)");
    printIntegers(out, closure.classSizes);
    printText(out, R"(,"max_exact_route_weighted_rms_l2_defect":)");
    printNumber(out, closure.rmsDefect);
    printText(out, R"(,"max_exact_class_l2_defect":)");
    printNumber(out, closure.maxDefect);
    printText(out, R"(,"minimum_total_route_mass":)");
    printNumber(out, closure.minMass);
    printText(out, R"(,"transition_plateau_defect":)");
    printNumber(out, closure.plateauDefect);
    printText(out, R"(,"positions":[)");

    for (size_t index = 0; index < closure.positions.size(); ++index) {
        if (index != 0) {
            printText(out, ",");
        }

        const ClosurePosition& position = closure.positions[index];
        std::print(out, R"({{"position":{},"occupied_class_count":{})",
                   position.position, position.occupiedClasses);
        printText(out, R"(,"singleton_route_mass":)");
        printNumber(out, position.singletonMass);
        printText(out, R"(,"total_route_mass":)");
        printNumber(out, position.assessableMass);
        printText(out, R"(,"route_weighted_effective_size":)");
        printNumber(out, position.meanEffectiveSize);
        printText(out, R"(,"exact_route_weighted_rms_l2_defect":)");
        printNumber(out, position.rmsDefect);
        printText(out, R"(,"exact_max_class_l2_defect":)");
        printNumber(out, position.maxDefect);
        printText(out, "}");
    }

    printText(out, "]}");
}

void printPredictiveClosure(std::ostream& out,
                            const PredictiveClosureResult& closure) {
    printText(out, R"({"state":)");
    printString(out, closure.state);
    std::print(out,
               R"(,"feature_count":{},"requested_classes":{},)"
               R"("realized_classes":{},"singleton_classes":{},)"
               R"("largest_class_size":{})",
               closure.featureCount, closure.requestedClasses,
               closure.realizedClasses, closure.singletonClasses,
               closure.largestClass);
    printText(out, R"(,"class_sizes":)");
    printIntegers(out, closure.classSizes);
    printText(out, R"(,"positions":[)");

    for (size_t index = 0; index < closure.positions.size(); ++index) {
        if (index != 0) {
            printText(out, ",");
        }

        const PredictivePosition& position = closure.positions[index];
        std::print(out,
                   R"({{"position":{},"normalized_position":)"
                   R"({},"occupied_classes":{},)"
                   R"("training_occupied_classes":{})",
                   position.position, position.scaledPosition,
                   position.occupiedClasses, position.trainingOccupiedClasses);
        printText(out, R"(,"singleton_route_mass":)");
        printNumber(out, position.singletonRouteMass);
        printText(out, R"(,"training_route_mass":)");
        printNumber(out, position.trainingRouteMass);
        printText(out, R"(,"held_out_route_mass":)");
        printNumber(out, position.heldOutRouteMass);
        printText(out, R"(,"held_out_covered_mass":)");
        printNumber(out, position.heldOutCoveredMass);
        printText(out, R"(,"exact_moment_rmse":)");
        printNumbers(out, position.exactMomentRmse);
        printText(out, R"(,"held_out_moment_rmse":)");
        printNumbers(out, position.heldOutMomentRmse);
        printText(out, R"(,"exact_moment_r2":)");
        printNumber(out, position.exactMomentR2);
        printText(out, R"(,"held_out_moment_r2":)");
        printNumber(out, position.heldOutMomentR2);
        printText(out, R"(,"target_partitions":[)");

        for (size_t target = 0; target < position.distributions.size();
             ++target) {
            if (target != 0) {
                printText(out, ",");
            }

            const PredictionDistributionMetric& metric =
                position.distributions[target];
            std::print(out, R"({{"bins":{},"exact_total_variation":)",
                       metric.targetBins);
            printNumber(out, metric.exactTotalVariation);
            printText(out, R"(,"exact_wasserstein_1":)");
            printNumber(out, metric.exactWasserstein1);
            printText(out, R"(,"held_out_total_variation":)");
            printNumber(out, metric.heldOutTotalVariation);
            printText(out, R"(,"held_out_wasserstein_1":)");
            printNumber(out, metric.heldOutWasserstein1);
            printText(out, "}");
        }

        printText(out, "]}");
    }

    printText(out, "]}");
}

void printScaling(std::ostream& out, const RouteScalingResult& scaling) {
    printText(out, R"(,"continuum_scaling":{"route_profile":[)");

    for (size_t index = 0; index < scaling.routeProfile.size(); ++index) {
        if (index != 0) {
            printText(out, ",");
        }

        const RouteProfilePosition& profile = scaling.routeProfile[index];
        std::print(out, R"({{"position":{},"normalized_position":)",
                   profile.position);
        printNumber(out, profile.scaledPosition);
        printText(out, R"(,"beta_mean":)");
        printNumber(out, profile.betaMean);
        printText(out, R"(,"beta_variance":)");
        printNumber(out, profile.betaVariance);
        printText(out, R"(,"latent_mean":)");
        printNumber(out, profile.latentMean);
        printText(out, R"(,"latent_variance":)");
        printNumber(out, profile.latentVariance);
        printText(out, R"(,"latent_kolmogorov":)");
        printNumber(out, profile.latentKolmogorov);
        printText(out, R"(,"intrinsic_mean":)");
        printNumber(out, profile.intrinsicMean);
        printText(out, R"(,"intrinsic_variance":)");
        printNumber(out, profile.intrinsicVariance);
        printText(out, R"(,"intrinsic_kolmogorov":)");
        printNumber(out, profile.intrinsicKolmogorov);
        printText(out, R"(,"intrinsic_outside_mass":)");
        printNumber(out, profile.intrinsicOutsideMass);
        printText(out, R"(,"intrinsic_oracle_rmse":)");
        printNumber(out, profile.intrinsicOracleRmse);
        printText(out, R"(,"sqrt_2p_intrinsic_mean_error":)");
        printNumber(out, profile.scaledIntrinsicMeanError);
        printText(out, R"(,"two_p_intrinsic_variance":)");
        printNumber(out, profile.scaledIntrinsicVariance);
        printText(out, R"(,"two_p_latent_variance":)");
        printNumber(out, profile.scaledLatentVariance);
        printText(out, "}");
    }

    printText(out, R"(],"spacing":[)");
    for (size_t index = 0; index < scaling.spacing.size(); ++index) {
        if (index != 0) {
            printText(out, ",");
        }

        const RouteSpacingPosition& spacing = scaling.spacing[index];
        std::print(out,
                   R"({{"position":{},"remaining_edges":{},)"
                   R"("gap_mean":)",
                   spacing.position, spacing.remainingEdges);
        printNumber(out, spacing.gapMean);
        printText(out, R"(,"gap_target_mean":)");
        printNumber(out, spacing.gapTargetMean);
        printText(out, R"(,"gap_variance":)");
        printNumber(out, spacing.gapVariance);
        printText(out, R"(,"gap_target_variance":)");
        printNumber(out, spacing.gapTargetVariance);
        printText(out, R"(,"gap_kolmogorov_bound":)");
        printNumber(out, spacing.gapKolmogorovBound);
        printText(out, R"(,"conditional_fraction_mean":)");
        printNumber(out, spacing.conditionalFractionMean);
        printText(out, R"(,"conditional_fraction_target_mean":)");
        printNumber(out, spacing.conditionalFractionTargetMean);
        printText(out, R"(,"conditional_fraction_variance":)");
        printNumber(out, spacing.conditionalFractionVariance);
        printText(out, R"(,"conditional_fraction_target_variance":)");
        printNumber(out, spacing.conditionalFractionTargetVariance);
        printText(out, R"(,"conditional_fraction_kolmogorov_bound":)");
        printNumber(out, spacing.conditionalFractionKolmogorovBound);
        printText(out, R"(,"source_fraction_covariance":)");
        printNumber(out, spacing.sourceFractionCovariance);
        printText(out, R"(,"source_fraction_correlation":)");
        printNumber(out, spacing.sourceFractionCorrelation);
        printText(out, "}");
    }

    printText(out, R"(],"jumps":{"p_intrinsic_mark_maximum":)");
    printNumber(out, scaling.macroscopicMaximalJump);
    printText(out, R"(,"sqrt_2p_centered_intrinsic_maximum":)");
    printNumber(out, scaling.intrinsicFluctuationMaximalJump);
    printText(out, R"(,"lindeberg_sums":[)");
    for (size_t index = 0; index < scaling.intrinsicLindeberg.size(); ++index) {
        if (index != 0) {
            printText(out, ",");
        }
        printText(out, R"({"threshold":)");
        printNumber(out, scaling.intrinsicLindeberg[index].threshold);
        printText(out, R"(,"sum":)");
        printNumber(out, scaling.intrinsicLindeberg[index].sum);
        printText(out, "}");
    }
    printText(out, "]}");

    printText(out, R"(,"predictive_closure":[)");
    for (size_t index = 0; index < scaling.predictiveClosure.size(); ++index) {
        if (index != 0) {
            printText(out, ",");
        }
        printPredictiveClosure(out, scaling.predictiveClosure[index]);
    }

    printText(out, R"(],"analysis_seconds":)");
    printNumber(out, scaling.seconds);
    std::print(out, R"(,"estimated_peak_bytes":{}}})", scaling.peakBytes);
}

void printHorizon(std::ostream& out, const GapSample& sample,
                  const HorizonResult& result,
                  const RouteScalingResult& scaling) {
    printText(out, R"({"schema":"bounded-systems.gap-horizon.v2")");
    std::print(out, R"(,"sample_index":{})", sample.index);
    std::print(out, R"(,"sample_seed":"{}")", sample.seed);
    std::print(out, R"(,"vertices":{})", sample.vertexCount);
    std::print(out, R"(,"edges":{})", sample.edgeCount);
    std::print(out, R"(,"horizon":{})", result.p);
    std::print(out, R"(,"has_routes":{})", result.valid);

    printText(out, R"(,"route_count":)");
    printCount(out, result.logCount);
    printText(out, R"(,"next_route_count":)");
    printCount(out, result.logNextCount);
    printText(out, R"(,"route_growth_ratio":)");
    printNumber(out, result.growth);
    printText(out, R"(,"log_route_growth_ratio":)");
    printNumber(out, result.logGrowth);
    printText(out, R"(,"expected_count_ratio":)");
    printNumber(out, result.expectedGrowth);
    printText(out, R"(,"count_ratio_relative_error":)");
    if (result.expectedGrowth > 0.0) {
        printNumber(out, result.growth / result.expectedGrowth - 1.0);
    } else {
        printText(out, "null");
    }

    printText(out, R"(,"audits":{"max_flow_relative_error":)");
    printNumber(out, result.maxFlowError);
    printText(out, R"(,"mean_flow_relative_error":)");
    printNumber(out, result.meanFlowError);
    printText(out, R"(,"max_conditional_row_error":)");
    printNumber(out, result.maxRowError);
    printText(out, R"(,"max_forward_backward_log_error":)");
    printNumber(out, sample.maxLogError);
    printText(out, "}");

    printText(out, R"(,"mean_increment":)");
    printNumbers(out, result.mean);
    printText(out, R"(,"raw_second_upper":)");
    printNumbers(out, result.rawSecond);
    printText(out, R"(,"covariance_upper":)");
    printNumbers(out, result.covariance);
    printText(out, R"(,"covariance_decomposition":{"within_position_upper":)");
    printNumbers(out, result.withinPositionCovariance);
    printText(out, R"(,"between_position_upper":)");
    printNumbers(out, result.betweenPositionCovariance);
    printText(out, R"(,"within_position_trace":)");
    printNumber(out, result.withinCovarianceTrace);
    printText(out, R"(,"between_position_trace":)");
    printNumber(out, result.betweenCovarianceTrace);
    printText(out, R"(,"mixed_trace":)");
    printNumber(out, result.timeScale);
    printText(out, R"(,"max_reconstruction_error":)");
    printNumber(out, result.covarianceDecompositionError);
    printText(out, "}");
    printText(out, R"(,"raw_third_symmetric":)");
    printNumbers(out, result.rawThird);
    printText(out, R"(,"centered_third_symmetric":)");
    printNumbers(out, result.centeredThird);
    printText(out, R"(,"within_position_centered_third_symmetric":)");
    printNumbers(out, result.withinPositionCenteredThird);
    printText(out, R"(,"within_position_centered_third_norm":)");
    printNumber(out, result.withinPositionThirdNorm);
    printText(out, R"(,"maximal_six_coordinate_jump":)");
    printNumber(out, result.maxJump);

    printText(out, R"(,"raw_jump_tails":[)");
    for (size_t index = 0; index < result.tails.size(); ++index) {
        if (index != 0) {
            printText(out, ",");
        }

        const TailResult& tail = result.tails[index];
        printText(out, R"({"threshold":)");
        printNumber(out, tail.threshold);
        printText(out, R"(,"second_moment_tail":)");
        printNumber(out, tail.tail);
        printText(out, "}");
    }
    printText(out, "]");

    std::print(out, R"(,"bulk":{{"first_position":{},"last_position":{})",
               result.bulkFirst, result.bulkLast);
    printText(out, R"(,"max_p_drift_curve_deviation":)");
    printNumber(out, result.driftPlateau);
    printText(out, R"(,"max_p2_covariance_curve_deviation":)");
    printNumber(out, result.covariancePlateau);
    printText(out, R"(,"scaled_coefficient_curve_deviation":)");
    printNumber(out, result.plateauDefect);
    printText(out, "}");

    printText(out, R"(,"positions":[)");
    for (size_t index = 0; index < result.positions.size(); ++index) {
        if (index != 0) {
            printText(out, ",");
        }

        const PositionResult& position = result.positions[index];
        std::print(out, R"({{"position":{},"normalized_position":)",
                   position.position);
        printNumber(out, position.scaledPosition);
        printText(out, R"(,"mean_increment":)");
        printNumbers(out, position.mean);
        printText(out, R"(,"p_mean_increment":)");
        printScaledNumbers(out, position.mean, static_cast<double>(result.p));
        printText(out, R"(,"covariance_upper":)");
        printNumbers(out, position.covariance);
        printText(out, R"(,"p2_covariance_upper":)");
        printScaledNumbers(out, position.covariance,
                           static_cast<double>(result.p) * result.p);
        printText(out, R"(,"covariance_trace":)");
        printNumber(out, position.variance);
        printText(out, R"(,"flow_relative_error":)");
        printNumber(out, position.flowError);
        printText(out, R"(,"conditional_row_error":)");
        printNumber(out, position.rowError);
        printText(out, "}");
    }
    printText(out, "]");

    printText(out, R"(,"legacy_uniform_partition_closure":[)");
    for (size_t index = 0; index < result.closure.size(); ++index) {
        if (index != 0) {
            printText(out, ",");
        }
        printClosure(out, result.closure[index]);
    }
    printText(out, "]");

    printScaling(out, scaling);

    printText(out, R"(,"analysis_seconds":)");
    printNumber(out, result.seconds);
    std::print(out, R"(,"estimated_peak_bytes":{})", result.peakBytes);
    std::println(out, "{}", "}");
}

void prepareDirectory(const GapOptions& options) {
    std::filesystem::create_directories(options.outputDirectory);

    constexpr std::array<std::string_view, 3> names{"run.json", "graphs.jsonl",
                                                    "horizons.jsonl"};
    for (const std::string_view name : names) {
        const std::filesystem::path path = options.outputDirectory / name;
        if (std::filesystem::exists(path) && !options.overwrite) {
            throw std::runtime_error("output file exists; pass --overwrite: " +
                                     path.string());
        }
    }
}

void printRun(std::ostream& out, const GapOptions& options,
              std::span<const GapSample> samples, size_t threads,
              double wallSeconds) {
    size_t edgeCount = 0;
    double sampleSeconds = 0.0;
    size_t peakBytes = 0;

    for (const GapSample& sample : samples) {
        edgeCount += sample.edgeCount;
        sampleSeconds += sample.totalSeconds;
        peakBytes = std::max(peakBytes, sample.peakBytes);
    }

    std::println(out, "{}", "{");
    printText(out, R"(  "schema": "bounded-systems.gap-run.v2",)"
                   "\n");
    std::print(out, R"(  "configuration": {{"vertices":{},"horizons":)",
               options.vertexCount);
    printIntegers(out, options.horizons);
    std::print(out, R"(,"samples":{},"master_seed":"{}")", options.sampleCount,
               options.seed);
    std::print(out, R"(,"requested_threads":{},"effective_threads":{})",
               options.threadCount, threads);
    printText(out, R"(,"output_directory":)");
    printString(out, options.outputDirectory.string());
    printText(out, R"(,"closure_bins":)");
    printIntegers(out, options.bins);
    printText(out, R"(,"predictive_classes":)");
    printIntegers(out, options.predictiveClasses);
    printText(out, R"(,"target_bins":)");
    printIntegers(out, options.targetBins);
    std::print(out, R"(,"reference_bins":{})", options.referenceBins);
    printText(out, R"(,"lindeberg_thresholds":)");
    printNumbers(out, options.thresholds);
    std::print(out, R"(,"validation_length":{},"legendre_modes":{})",
               options.validationLength, options.modeCount);
    printText(out, R"(,"bulk_fraction":)");
    printNumber(out, options.bulkFraction);
    std::println(out, "{}", "},");

    printText(out, R"(  "generator": {"kernel":"(y-x)_+",)"
                   R"("marks":"counter-splitmix64-uniform53-v1",)"
                   R"("edge_stream":"counter-splitmix64-pair-v1",)"
                   R"("nested_across_vertex_counts":true},)"
                   "\n");
    printText(
        out,
        R"(  "normalization": {)"
        R"("route_vectors":"unit-sum with accumulated natural-log",)"
        R"("flow":"normalized occupancy and remaining-horizon transition",)"
        R"("degree_scale":"N","second_order_scale":"N^2"},)"
        "\n");
    printText(
        out,
        R"(  "array_order": {)"
        R"("coordinates":["d_out","d_in","q_pp","q_mm","q_pm","q_mp"],)"
        R"("predictive_moments":["intrinsic_mark","sqrt_N_residual_d_out",)"
        R"("sqrt_N_residual_d_in","sqrt_N_residual_q_pp",)"
        R"("sqrt_N_residual_q_mm","sqrt_N_residual_q_pm",)"
        R"("sqrt_N_residual_q_mp"],)"
        R"("covariance_upper":"lexicographic i<=j",)"
        R"("third_symmetric":"lexicographic i<=j<=k"},)"
        "\n");
    printText(
        out,
        R"(  "finite_sample_closure": {)"
        R"("legacy_classes":"fixed uniform bins on normalized coordinates",)"
        R"("legacy_defect":"exact route-weighted L2 conditional-law variance; no finite-sample correction",)"
        R"("predictive_classes":"nested balanced median partitions of standardized intrinsic features",)"
        R"("predictive_target":"seven canonical conditional moments and nested intrinsic-mark histograms",)"
        R"("holdout":"source vertices selected by deterministic identifier hash"},)"
        "\n");
    printText(out, "  \"continuum_scaling\": {"
                   "\"route_time\":\"s=r/p with delta_s=1/p\","
                   "\"route_law\":\"Dirichlet(1,2,...,2,1)\","
                   "\"intrinsic_mark\":\"1/2+(d_in-d_out)\","
                   "\"transverse_residual_scale\":\"sqrt(N)\","
                   "\"intrinsic_fluctuation_scale\":\"sqrt(2p)\"},\n");

    printText(out, R"(  "build": {"cxx_standard":"C++23","compiler":)");
    printString(out, __VERSION__);
    std::println(out, R"(,"hardware_concurrency":{}}},)",
                 std::thread::hardware_concurrency());

    printText(out, R"(  "runtime": {"wall_seconds":)");
    printNumber(out, wallSeconds);
    printText(out, R"(,"summed_sample_seconds":)");
    printNumber(out, sampleSeconds);
    std::println(out,
                 R"(,"edge_total":{},"peak_rss_kib":{},)"
                 R"("max_sample_estimated_peak_bytes":{}}})",
                 edgeCount, peakRssKib(), peakBytes);
    std::println(out, "{}", "}");
}

std::ofstream openFile(const std::filesystem::path& path) {
    std::filesystem::path temporary = path;
    temporary += ".tmp";
    std::ofstream out(temporary);

    if (!out) {
        throw std::runtime_error(
            std::format("cannot create artifact: {}", temporary.string()));
    }

    return out;
}

void closeFile(std::ofstream& out, const std::filesystem::path& path) {
    out.close();

    if (!out) {
        throw std::runtime_error(
            std::format("failed while writing artifact: {}", path.string()));
    }

    std::filesystem::path temporary = path;
    temporary += ".tmp";
    std::filesystem::rename(temporary, path);
}

} // namespace

long peakRssKib() {
    rusage usage{};
    if (getrusage(RUSAGE_SELF, &usage) != 0) {
        return -1;
    }
    return usage.ru_maxrss;
}

void writeGapOutput(const GapOptions& options,
                    std::span<const GapSample> samples, size_t threads,
                    double wallSeconds) {
    prepareDirectory(options);

    const std::filesystem::path graphsPath =
        options.outputDirectory / "graphs.jsonl";
    const std::filesystem::path horizonsPath =
        options.outputDirectory / "horizons.jsonl";
    std::ofstream graphs = openFile(graphsPath);
    std::ofstream horizons = openFile(horizonsPath);

    for (const GapSample& sample : samples) {
        if (sample.horizons.size() != sample.scaling.size()) {
            throw std::logic_error(
                "horizon and scaling result counts do not match");
        }

        printGraph(graphs, sample);
        for (size_t index = 0; index < sample.horizons.size(); ++index) {
            printHorizon(horizons, sample, sample.horizons[index],
                         sample.scaling[index]);
        }
    }

    closeFile(graphs, graphsPath);
    closeFile(horizons, horizonsPath);

    const std::filesystem::path runPath = options.outputDirectory / "run.json";
    std::ofstream run = openFile(runPath);
    printRun(run, options, samples, threads, wallSeconds);
    closeFile(run, runPath);
}
