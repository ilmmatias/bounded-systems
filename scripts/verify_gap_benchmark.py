#!/usr/bin/env python3
"""Fast end-to-end verification of the ordered gap-kernel benchmark."""

from __future__ import annotations

import copy
import json
import math
import os
import re
import subprocess
import statistics
import tempfile
from fractions import Fraction
from pathlib import Path
from typing import Any, NoReturn, Sequence

ROOT = Path(__file__).resolve().parents[1]
BENCHMARK = ROOT / "bin" / "gap-benchmark"
VERTICES, SAMPLES, THREADS, SEED = 48, 3, 3, 8_675_309
HORIZONS = (1, 2, 3)
CLOSURE_BINS = (2, 3)
PREDICTIVE_CLASSES = (4, 8)
TARGET_BINS = (4, 8)
REFERENCE_BINS = 32
THRESHOLDS = (0.05, 0.2)
VALIDATION_LENGTH, LEGENDRE_MODES, BULK_FRACTION = 3, 3, 0.2
FLOW_TOLERANCE, IDENTITY_TOLERANCE = 1.0e-10, 2.0e-12


class Checks:
    def __init__(self) -> None:
        self.count = 0

    def require(self, condition: bool, message: str) -> None:
        if not condition:
            raise AssertionError(message)
        self.count += 1

    def close(self, actual: Any, expected: float, message: str) -> None:
        self.require(finite(actual), f"{message}: non-finite value {actual!r}")
        self.require(
            math.isclose(float(actual), expected, rel_tol=IDENTITY_TOLERANCE, abs_tol=IDENTITY_TOLERANCE),
            f"{message}: expected {expected:.17g}, got {float(actual):.17g}",
        )


def finite(value: Any) -> bool:
    return isinstance(value, (int, float)) and not isinstance(value, bool) and math.isfinite(value)


def require_fields(value: Any, names: str, context: str, checks: Checks) -> None:
    checks.require(isinstance(value, dict), f"{context} must be an object")
    missing = set(names.split()) - set(value)
    checks.require(not missing, f"{context} is missing fields {sorted(missing)}")


def reject_nonstandard_json(token: str) -> NoReturn:
    raise ValueError(f"non-standard JSON token {token!r}")


def parse_json(text: str, context: str) -> Any:
    try:
        return json.loads(text, parse_constant=reject_nonstandard_json)
    except (json.JSONDecodeError, ValueError) as error:
        raise AssertionError(f"invalid JSON in {context}: {error}") from error


def run_checked(arguments: Sequence[str], timeout: float) -> subprocess.CompletedProcess[str]:
    try:
        result = subprocess.run(
            arguments,
            cwd=ROOT,
            check=False,
            capture_output=True,
            text=True,
            timeout=timeout,
        )
    except (OSError, subprocess.TimeoutExpired) as error:
        raise AssertionError(f"could not run {' '.join(arguments)}: {error}") from error
    if result.returncode:
        raise AssertionError(
            f"command failed ({result.returncode}): {' '.join(arguments)}\n"
            f"stdout:\n{result.stdout}\nstderr:\n{result.stderr}"
        )
    return result


def arguments(output: Path, threads: int) -> list[str]:
    return [
        str(BENCHMARK),
        "--vertices",
        str(VERTICES),
        "--horizons",
        ",".join(map(str, HORIZONS)),
        "--samples",
        str(SAMPLES),
        "--seed",
        str(SEED),
        "--threads",
        str(threads),
        "--output",
        str(output),
        "--closure-bins",
        ",".join(map(str, CLOSURE_BINS)),
        "--predictive-classes",
        ",".join(map(str, PREDICTIVE_CLASSES)),
        "--target-bins",
        ",".join(map(str, TARGET_BINS)),
        "--reference-bins",
        str(REFERENCE_BINS),
        "--lindeberg-thresholds",
        ",".join(map(str, THRESHOLDS)),
        "--validation-length",
        str(VALIDATION_LENGTH),
        "--legendre-modes",
        str(LEGENDRE_MODES),
        "--bulk-fraction",
        str(BULK_FRACTION),
    ]


def load_output(directory: Path, checks: Checks) -> dict[str, Any]:
    expected = {"run.json", "graphs.jsonl", "horizons.jsonl"}
    actual = {path.name for path in directory.iterdir() if path.is_file()}
    checks.require(actual == expected, f"{directory} files differ: {sorted(actual)}")

    def rows(name: str) -> list[Any]:
        path = directory / name
        lines = path.read_text(encoding="utf-8").splitlines()
        checks.require(
            bool(lines) and all(line.strip() for line in lines),
            f"{path} is empty or has blank rows",
        )
        return [parse_json(line, f"{path}:{number}") for number, line in enumerate(lines, 1)]

    run_path = directory / "run.json"
    return {
        "run": parse_json(run_path.read_text(encoding="utf-8"), str(run_path)),
        "graphs": rows("graphs.jsonl"),
        "horizons": rows("horizons.jsonl"),
    }


def verify_count(value: Any, context: str, checks: Checks) -> float:
    require_fields(value, "log mantissa base10_exponent", context, checks)
    logarithm, mantissa, exponent = value["log"], value["mantissa"], value["base10_exponent"]
    checks.require(finite(logarithm) and finite(mantissa), f"{context} is not finite")
    checks.require(isinstance(exponent, int) and 1.0 <= mantissa < 10.0, f"{context} notation is invalid")
    checks.close(math.log(mantissa) + exponent * math.log(10.0), logarithm, f"{context} notation")
    return float(logarithm)


def double_factorial(number: int) -> int:
    return math.prod(range(number, 0, -2)) if number > 0 else 1


def upper_frobenius(values: Sequence[float]) -> float:
    squared = 0.0
    index = 0
    for row in range(6):
        for column in range(row, 6):
            multiplicity = 1 if row == column else 2
            squared += multiplicity * values[index] ** 2
            index += 1
    return math.sqrt(squared)


def legendre_coefficient(length: int, mode: int) -> float:
    amplitude = Fraction(math.factorial(length), 2 * math.factorial(2 * length))
    coefficient = Fraction(
        (4 * mode + 1) * math.factorial(2 * length),
        double_factorial(2 * length - 2 * mode) * double_factorial(2 * length + 2 * mode + 1),
    )
    return float((length + 1) * amplitude * coefficient) / math.sqrt(4 * mode + 1)


def verify_calibration(graph: dict[str, Any], horizons: dict[int, dict[str, Any]], checks: Checks) -> None:
    sample, modes, rows = graph["sample_index"], graph["even_legendre_modes"], graph["route_calibration"]
    checks.require(
        len(modes) == LEGENDRE_MODES and all(finite(value) for value in modes),
        f"sample {sample} modes differ",
    )
    checks.require(len(rows) == VALIDATION_LENGTH, f"sample {sample} calibration row count differs")
    fields = (
        "length route_count path_homomorphism_density path_homomorphism_target "
        "path_homomorphism_error subset_route_mean subset_route_target subset_route_error "
        "scaled_route_fluctuation leading_mode_prediction leading_mode_residual"
    )
    for length, row in enumerate(rows, 1):
        context = f"sample {sample} calibration {length}"
        require_fields(row, fields, context, checks)
        checks.require(row["length"] == length, f"{context} length differs")
        verify_count(row["route_count"], f"{context}.route_count", checks)
        checks.require(row["route_count"] == horizons[length]["route_count"], f"{context} count differs")
        p_l = Fraction(1, math.factorial(2 * length + 1))
        theta_l = Fraction(math.factorial(length + 1), math.factorial(2 * length + 1))
        path_density, route_mean = row["path_homomorphism_density"], row["subset_route_mean"]
        checks.close(row["path_homomorphism_target"], float(p_l), f"{context} p_l")
        checks.close(row["subset_route_target"], float(theta_l), f"{context} theta_l")
        checks.close(route_mean, math.factorial(length + 1) * path_density, f"{context} normalization")
        checks.close(row["path_homomorphism_error"], path_density - float(p_l), f"{context} path error")
        checks.close(row["subset_route_error"], route_mean - float(theta_l), f"{context} subset error")
        checks.require(
            abs(route_mean - float(theta_l)) <= max(0.03, 0.60 * float(theta_l)),
            f"{context} stochastic estimate is implausibly far from theta_l",
        )
        scaled = math.sqrt(VERTICES) * (route_mean - float(theta_l))
        checks.close(row["scaled_route_fluctuation"], scaled, f"{context} scaling")
        prediction = sum(
            legendre_coefficient(length, mode) * modes[mode - 1]
            for mode in range(1, min(length, LEGENDRE_MODES) + 1)
        )
        checks.close(row["leading_mode_prediction"], prediction, f"{context} Legendre prediction")
        checks.close(row["leading_mode_residual"], scaled - prediction, f"{context} Legendre residual")
        checks.require(abs(row["leading_mode_residual"]) <= 1.0, f"{context} residual is implausibly large")
        first_projection = legendre_coefficient(length, 1)
        checks.require(first_projection > 0.0, f"{context} first projection vanished")
        support_order = 1 if first_projection != 0.0 else length
        checks.require(Fraction(support_order, 2) == Fraction(1, 2), f"{context} OU rate is not 1/2")


def verify_classes(value: dict[str, Any], vertices: int, context: str, checks: Checks) -> None:
    sizes = value["class_sizes"]
    checks.require(
        isinstance(sizes, list)
        and sizes
        and all(isinstance(size, int) and size > 0 for size in sizes),
        f"{context} sizes are invalid",
    )
    checks.require(
        len(sizes) == value["class_count"] and sum(sizes) == vertices,
        f"{context} class total differs",
    )
    checks.require(
        sum(size == 1 for size in sizes) == value["singleton_class_count"],
        f"{context} singleton count differs",
    )
    checks.require(max(sizes) == value["largest_class_size"], f"{context} largest class differs")


def verify_closure(
    value: dict[str, Any],
    vertices: int,
    bulk: list[int],
    context: str,
    checks: Checks,
) -> None:
    fields = (
        "bins_per_coordinate class_count singleton_class_count largest_class_size "
        "class_sizes max_exact_route_weighted_rms_l2_defect "
        "max_exact_class_l2_defect minimum_total_route_mass "
        "transition_plateau_defect positions"
    )
    require_fields(value, fields, context, checks)
    verify_classes(value, vertices, context, checks)

    rows = value["positions"]
    checks.require(
        [row["position"] for row in rows] == bulk,
        f"{context} positions differ",
    )

    masses: list[float] = []
    rms_values: list[float] = []
    maximum_values: list[float] = []
    row_fields = (
        "occupied_class_count singleton_route_mass total_route_mass "
        "route_weighted_effective_size exact_route_weighted_rms_l2_defect "
        "exact_max_class_l2_defect"
    )

    for row in rows:
        row_context = f"{context} position {row['position']}"
        require_fields(row, row_fields, row_context, checks)
        checks.require(
            1 <= row["occupied_class_count"] <= value["class_count"],
            f"{row_context} occupancy is invalid",
        )
        checks.require(
            finite(row["singleton_route_mass"])
            and 0.0 <= row["singleton_route_mass"] <= 1.0 + 1.0e-12,
            f"{row_context} singleton mass is invalid",
        )
        checks.close(row["total_route_mass"], 1.0, f"{row_context} total mass")
        checks.require(
            finite(row["route_weighted_effective_size"])
            and row["route_weighted_effective_size"] >= 1.0 - 1.0e-12,
            f"{row_context} ESS is invalid",
        )

        masses.append(float(row["total_route_mass"]))
        rms_values.append(float(row["exact_route_weighted_rms_l2_defect"]))
        maximum_values.append(float(row["exact_max_class_l2_defect"]))

    checks.close(
        value["minimum_total_route_mass"],
        min(masses),
        f"{context} minimum mass",
    )
    checks.close(
        value["max_exact_route_weighted_rms_l2_defect"],
        max(rms_values),
        f"{context} maximum RMS defect",
    )
    checks.close(
        value["max_exact_class_l2_defect"],
        max(maximum_values),
        f"{context} maximum class defect",
    )
    checks.require(
        finite(value["transition_plateau_defect"])
        and value["transition_plateau_defect"] >= 0.0,
        f"{context} plateau is invalid",
    )


def verify_predictive_closure(
    value: dict[str, Any],
    bulk: list[int],
    context: str,
    checks: Checks,
) -> None:
    fields = (
        "state feature_count requested_classes realized_classes "
        "singleton_classes largest_class_size class_sizes positions"
    )
    require_fields(value, fields, context, checks)

    sizes = value["class_sizes"]
    checks.require(
        len(sizes) == value["realized_classes"]
        and sum(sizes) == VERTICES
        and value["realized_classes"] == value["requested_classes"],
        f"{context} class partition differs",
    )
    checks.require(
        sum(size == 1 for size in sizes) == value["singleton_classes"]
        and max(sizes) == value["largest_class_size"],
        f"{context} class occupancy metadata differs",
    )

    rows = value["positions"]
    checks.require(
        [position["position"] for position in rows] == bulk,
        f"{context} positions differ",
    )

    for position in rows:
        row_context = f"{context} position {position['position']}"
        row_fields = (
            "normalized_position occupied_classes training_occupied_classes "
            "singleton_route_mass training_route_mass held_out_route_mass "
            "held_out_covered_mass exact_moment_rmse held_out_moment_rmse "
            "exact_moment_r2 held_out_moment_r2 target_partitions"
        )
        require_fields(position, row_fields, row_context, checks)

        checks.close(
            position["training_route_mass"] + position["held_out_route_mass"],
            1.0,
            f"{row_context} train/test mass",
        )
        checks.require(
            0.0 <= position["held_out_covered_mass"]
            <= position["held_out_route_mass"] + 1.0e-12,
            f"{row_context} held-out coverage is invalid",
        )
        checks.require(
            len(position["exact_moment_rmse"]) == 7
            and all(finite(item) and item >= 0.0 for item in position["exact_moment_rmse"]),
            f"{row_context} exact moment errors are invalid",
        )
        checks.require(
            len(position["held_out_moment_rmse"]) == 7
            and all(finite(item) and item >= 0.0 for item in position["held_out_moment_rmse"]),
            f"{row_context} held-out moment errors are invalid",
        )
        checks.require(
            finite(position["exact_moment_r2"])
            and finite(position["held_out_moment_r2"]),
            f"{row_context} predictive R2 is invalid",
        )

        target_rows = position["target_partitions"]
        checks.require(
            [target["bins"] for target in target_rows] == list(TARGET_BINS),
            f"{row_context} target partitions differ",
        )
        for target in target_rows:
            metrics = (
                target["exact_total_variation"],
                target["exact_wasserstein_1"],
                target["held_out_total_variation"],
                target["held_out_wasserstein_1"],
            )
            checks.require(
                all(finite(item) and -1.0e-12 <= item <= 1.0 + 1.0e-12 for item in metrics),
                f"{row_context} distribution error is invalid",
            )


def verify_graph(graph: dict[str, Any], checks: Checks) -> None:
    fields = (
        "schema sample_index sample_seed vertices edges directed_edge_density "
        "directed_edge_target directed_edge_error unoriented_edge_density "
        "unoriented_edge_target timing_seconds estimated_bytes latent_validation "
        "intrinsic_scaling exact_signature even_legendre_modes route_calibration"
    )
    require_fields(graph, fields, "graph row", checks)

    context = f"sample {graph['sample_index']} graph"
    checks.require(
        graph["schema"] == "bounded-systems.gap-graph.v2",
        f"{context} schema differs",
    )
    checks.require(
        graph["vertices"] == VERTICES and graph["edges"] > 0,
        f"{context} size is invalid",
    )

    density = graph["directed_edge_density"]
    checks.close(graph["directed_edge_target"], 1.0 / 6.0, f"{context} target 1/6")
    checks.close(
        density,
        graph["edges"] / (VERTICES * (VERTICES - 1)),
        f"{context} density",
    )
    checks.close(
        graph["unoriented_edge_density"],
        2.0 * density,
        f"{context} pair density",
    )
    checks.close(
        graph["unoriented_edge_target"],
        1.0 / 3.0,
        f"{context} pair target",
    )
    checks.close(
        graph["directed_edge_error"],
        density - 1.0 / 6.0,
        f"{context} edge error",
    )
    checks.require(
        abs(density - 1.0 / 6.0) <= 0.15,
        f"{context} stochastic density is implausible",
    )

    timing = graph["timing_seconds"]
    require_fields(
        timing,
        "generation node_state route_counts total",
        f"{context} timing",
        checks,
    )
    checks.require(
        all(finite(value) and value >= 0.0 for value in timing.values()),
        f"{context} timing is invalid",
    )

    byte_data = graph["estimated_bytes"]
    require_fields(
        byte_data,
        "graph node_state route_workspace peak",
        f"{context} bytes",
        checks,
    )
    checks.require(
        all(isinstance(value, int) and value > 0 for value in byte_data.values()),
        f"{context} bytes are invalid",
    )

    scaling = graph["intrinsic_scaling"]
    require_fields(
        scaling,
        "mark_minimum mark_maximum transverse_residual_rms "
        "sqrt_N_transverse_residual_rms coordinate_residual_rms "
        "sqrt_N_coordinate_residual_rms",
        f"{context} intrinsic scaling",
        checks,
    )
    checks.require(
        len(scaling["coordinate_residual_rms"]) == 6
        and len(scaling["sqrt_N_coordinate_residual_rms"]) == 6,
        f"{context} residual coordinate arrays differ",
    )
    checks.close(
        scaling["sqrt_N_transverse_residual_rms"],
        math.sqrt(VERTICES) * scaling["transverse_residual_rms"],
        f"{context} transverse residual scaling",
    )
    for index, residual in enumerate(scaling["coordinate_residual_rms"]):
        checks.close(
            scaling["sqrt_N_coordinate_residual_rms"][index],
            math.sqrt(VERTICES) * residual,
            f"{context} coordinate residual {index}",
        )

    signature = graph["exact_signature"]
    require_fields(
        signature,
        "class_count singleton_class_count singleton_node_count "
        "largest_class_size closure_degenerate class_sizes",
        f"{context} signature",
        checks,
    )
    verify_classes(signature, VERTICES, f"{context} signature", checks)
    checks.require(
        signature["singleton_node_count"] == signature["singleton_class_count"],
        f"{context} singleton nodes differ",
    )
    expected = signature["singleton_node_count"] * 20 >= VERTICES * 19
    checks.require(
        signature["closure_degenerate"] is expected,
        f"{context} degeneracy flag differs",
    )


def verify_horizon(row: dict[str, Any], checks: Checks) -> None:
    fields = (
        "schema sample_index sample_seed vertices edges horizon has_routes "
        "route_count next_route_count route_growth_ratio log_route_growth_ratio "
        "expected_count_ratio count_ratio_relative_error audits mean_increment "
        "raw_second_upper covariance_upper covariance_decomposition "
        "raw_third_symmetric centered_third_symmetric "
        "within_position_centered_third_symmetric "
        "within_position_centered_third_norm maximal_six_coordinate_jump "
        "raw_jump_tails bulk positions legacy_uniform_partition_closure "
        "continuum_scaling analysis_seconds estimated_peak_bytes"
    )
    require_fields(row, fields, "horizon row", checks)

    context = f"sample {row['sample_index']} horizon {row['horizon']}"
    checks.require(
        row["schema"] == "bounded-systems.gap-horizon.v2",
        f"{context} schema differs",
    )
    checks.require(
        row["vertices"] == VERTICES and row["has_routes"] is True,
        f"{context} has no route",
    )

    # Route-count and finite-flow identities.
    route_log = verify_count(row["route_count"], f"{context}.route_count", checks)
    next_log = verify_count(
        row["next_route_count"], f"{context}.next_route_count", checks
    )
    growth = row["route_growth_ratio"]
    checks.close(
        row["log_route_growth_ratio"],
        next_log - route_log,
        f"{context} log ratio",
    )
    checks.close(
        growth,
        math.exp(row["log_route_growth_ratio"]),
        f"{context} count ratio",
    )

    horizon = row["horizon"]
    expected = (VERTICES - horizon - 1) / (
        (2 * horizon + 2) * (2 * horizon + 3)
    )
    checks.close(row["expected_count_ratio"], expected, f"{context} expected ratio")
    checks.close(
        row["count_ratio_relative_error"],
        growth / expected - 1.0,
        f"{context} ratio error",
    )

    audits = row["audits"]
    audit_names = (
        "max_flow_relative_error mean_flow_relative_error "
        "max_conditional_row_error max_forward_backward_log_error"
    )
    require_fields(audits, audit_names, f"{context} audits", checks)
    checks.require(
        all(
            finite(audits[name])
            and 0.0 <= audits[name] <= FLOW_TOLERANCE
            for name in audit_names.split()
        ),
        f"{context} flow/row audit exceeds {FLOW_TOLERANCE:.1e}: {audits}",
    )

    # The global covariance is the sum of within-position and
    # between-position covariance, not a universal time normalization.
    array_lengths = {
        "mean_increment": 6,
        "raw_second_upper": 21,
        "covariance_upper": 21,
        "raw_third_symmetric": 56,
        "centered_third_symmetric": 56,
        "within_position_centered_third_symmetric": 56,
    }
    checks.require(
        all(
            len(row[name]) == length
            and all(finite(value) for value in row[name])
            for name, length in array_lengths.items()
        ),
        f"{context} moment arrays are invalid",
    )

    decomposition = row["covariance_decomposition"]
    require_fields(
        decomposition,
        "within_position_upper between_position_upper within_position_trace "
        "between_position_trace mixed_trace max_reconstruction_error",
        f"{context} covariance decomposition",
        checks,
    )
    within = decomposition["within_position_upper"]
    between = decomposition["between_position_upper"]
    checks.require(
        len(within) == 21 and len(between) == 21,
        f"{context} covariance decomposition arrays differ",
    )
    for index, covariance in enumerate(row["covariance_upper"]):
        checks.close(
            within[index] + between[index],
            covariance,
            f"{context} covariance decomposition {index}",
        )

    diagonal = (0, 6, 11, 15, 18, 20)
    checks.close(
        decomposition["within_position_trace"],
        sum(within[index] for index in diagonal),
        f"{context} within trace",
    )
    checks.close(
        decomposition["between_position_trace"],
        sum(between[index] for index in diagonal),
        f"{context} between trace",
    )
    checks.close(
        decomposition["mixed_trace"],
        sum(row["covariance_upper"][index] for index in diagonal),
        f"{context} mixed trace",
    )
    checks.require(
        0.0 <= decomposition["max_reconstruction_error"] <= IDENTITY_TOLERANCE,
        f"{context} covariance reconstruction failed",
    )

    checks.require(
        finite(row["analysis_seconds"])
        and row["analysis_seconds"] >= 0.0
        and isinstance(row["estimated_peak_bytes"], int)
        and row["estimated_peak_bytes"] > 0,
        f"{context} runtime/bytes are invalid",
    )
    checks.require(
        finite(row["within_position_centered_third_norm"])
        and row["within_position_centered_third_norm"] >= 0.0
        and finite(row["maximal_six_coordinate_jump"])
        and row["maximal_six_coordinate_jump"] >= 0.0,
        f"{context} third-moment or jump norm is invalid",
    )

    tails = row["raw_jump_tails"]
    checks.require(
        len(tails) == len(THRESHOLDS)
        and [tail["threshold"] for tail in tails] == list(THRESHOLDS)
        and all(finite(tail["second_moment_tail"]) for tail in tails),
        f"{context} raw jump tails differ",
    )

    # Position-dependent macroscopic coefficients.
    positions = row["positions"]
    checks.require(
        len(positions) == horizon
        and [position["position"] for position in positions]
        == list(range(horizon)),
        f"{context} positions differ",
    )

    for position in positions:
        checks.require(
            0.0 <= position["flow_relative_error"] <= FLOW_TOLERANCE
            and 0.0 <= position["conditional_row_error"] <= FLOW_TOLERANCE,
            f"{context} position flow/row identity failed",
        )
        for coordinate in range(6):
            checks.close(
                position["p_mean_increment"][coordinate],
                horizon * position["mean_increment"][coordinate],
                f"{context} scaled drift",
            )
        for index in range(21):
            checks.close(
                position["p2_covariance_upper"][index],
                horizon * horizon * position["covariance_upper"][index],
                f"{context} scaled covariance",
            )

    checks.close(
        audits["max_flow_relative_error"],
        max(position["flow_relative_error"] for position in positions),
        f"{context} max flow",
    )
    checks.close(
        audits["max_conditional_row_error"],
        max(position["conditional_row_error"] for position in positions),
        f"{context} max row",
    )

    bulk = row["bulk"]
    first, last = bulk["first_position"], bulk["last_position"]
    checks.require(0 <= first <= last < horizon, f"{context} bulk range is invalid")
    checks.close(
        bulk["scaled_coefficient_curve_deviation"],
        max(
            bulk["max_p_drift_curve_deviation"],
            bulk["max_p2_covariance_curve_deviation"],
        ),
        f"{context} plateau",
    )

    bulk_positions = positions[first : last + 1]
    bulk_mean = [
        statistics.fmean(
            position["p_mean_increment"][coordinate]
            for position in bulk_positions
        )
        for coordinate in range(6)
    ]
    bulk_covariance = [
        statistics.fmean(
            position["p2_covariance_upper"][entry]
            for position in bulk_positions
        )
        for entry in range(21)
    ]
    drift_defect = max(
        math.sqrt(
            sum(
                (
                    position["p_mean_increment"][coordinate]
                    - bulk_mean[coordinate]
                )
                ** 2
                for coordinate in range(6)
            )
        )
        for position in bulk_positions
    )
    covariance_defect = max(
        upper_frobenius(
            [
                position["p2_covariance_upper"][entry]
                - bulk_covariance[entry]
                for entry in range(21)
            ]
        )
        for position in bulk_positions
    )
    checks.close(
        bulk["max_p_drift_curve_deviation"],
        drift_defect,
        f"{context} drift plateau",
    )
    checks.close(
        bulk["max_p2_covariance_curve_deviation"],
        covariance_defect,
        f"{context} covariance plateau",
    )

    legacy = row["legacy_uniform_partition_closure"]
    checks.require(
        [closure["bins_per_coordinate"] for closure in legacy]
        == list(CLOSURE_BINS),
        f"{context} closure bins differ",
    )
    for closure in legacy:
        verify_closure(
            closure,
            VERTICES,
            list(range(first, last + 1)),
            f"{context} closure {closure['bins_per_coordinate']}",
            checks,
        )

    # Exact reference-route and graph-intrinsic fluctuation diagnostics.
    scaling = row["continuum_scaling"]
    require_fields(
        scaling,
        "route_profile spacing jumps predictive_closure analysis_seconds "
        "estimated_peak_bytes",
        f"{context} continuum scaling",
        checks,
    )
    checks.require(
        finite(scaling["analysis_seconds"])
        and scaling["analysis_seconds"] >= 0.0
        and scaling["estimated_peak_bytes"] > 0,
        f"{context} scaling runtime is invalid",
    )

    profiles = scaling["route_profile"]
    checks.require(
        [profile["position"] for profile in profiles]
        == list(range(horizon + 1)),
        f"{context} route profile positions differ",
    )
    for profile in profiles:
        position = profile["position"]
        alpha = 2 * position + 1
        beta = 2 * (horizon - position) + 1
        total = alpha + beta
        target_mean = alpha / total
        target_variance = alpha * beta / (total * total * (total + 1))

        checks.close(profile["beta_mean"], target_mean, f"{context} Beta mean")
        checks.close(
            profile["beta_variance"],
            target_variance,
            f"{context} Beta variance",
        )
        checks.close(
            profile["sqrt_2p_intrinsic_mean_error"],
            math.sqrt(2 * horizon)
            * (profile["intrinsic_mean"] - profile["beta_mean"]),
            f"{context} intrinsic mean scaling",
        )
        checks.close(
            profile["two_p_intrinsic_variance"],
            2 * horizon * profile["intrinsic_variance"],
            f"{context} intrinsic variance scaling",
        )
        checks.close(
            profile["two_p_latent_variance"],
            2 * horizon * profile["latent_variance"],
            f"{context} latent variance scaling",
        )
        checks.require(
            0.0 <= profile["latent_kolmogorov"] <= 1.0
            and 0.0 <= profile["intrinsic_kolmogorov"] <= 1.0
            and 0.0 <= profile["intrinsic_outside_mass"] <= 1.0,
            f"{context} route-profile diagnostic is invalid",
        )

    spacing_rows = scaling["spacing"]
    checks.require(
        [spacing["position"] for spacing in spacing_rows]
        == list(range(horizon)),
        f"{context} spacing positions differ",
    )
    for spacing in spacing_rows:
        remaining = horizon - spacing["position"]
        checks.close(
            spacing["gap_target_mean"],
            1.0 / (horizon + 1),
            f"{context} gap mean target",
        )
        checks.close(
            spacing["gap_target_variance"],
            4.0
            * horizon
            / ((2 * horizon + 2) ** 2 * (2 * horizon + 3)),
            f"{context} gap variance target",
        )
        checks.close(
            spacing["conditional_fraction_target_mean"],
            2.0 / (2 * remaining + 1),
            f"{context} conditional fraction mean target",
        )
        checks.close(
            spacing["conditional_fraction_target_variance"],
            2.0
            * (2 * remaining - 1)
            / ((2 * remaining + 1) ** 2 * (2 * remaining + 2)),
            f"{context} conditional fraction variance target",
        )
        checks.require(
            0.0 <= spacing["gap_kolmogorov_bound"] <= 1.0
            and 0.0
            <= spacing["conditional_fraction_kolmogorov_bound"]
            <= 1.0
            and -1.0 <= spacing["source_fraction_correlation"] <= 1.0,
            f"{context} spacing diagnostic is invalid",
        )

    jumps = scaling["jumps"]
    checks.require(
        finite(jumps["p_intrinsic_mark_maximum"])
        and jumps["p_intrinsic_mark_maximum"] >= 0.0
        and finite(jumps["sqrt_2p_centered_intrinsic_maximum"])
        and jumps["sqrt_2p_centered_intrinsic_maximum"] >= 0.0,
        f"{context} scaled jump is invalid",
    )
    lindeberg = jumps["lindeberg_sums"]
    checks.require(
        [tail["threshold"] for tail in lindeberg] == list(THRESHOLDS)
        and all(finite(tail["sum"]) and tail["sum"] >= 0.0 for tail in lindeberg),
        f"{context} intrinsic Lindeberg rows differ",
    )
    checks.require(
        all(
            lindeberg[index]["sum"] + IDENTITY_TOLERANCE
            >= lindeberg[index + 1]["sum"]
            for index in range(len(lindeberg) - 1)
        ),
        f"{context} Lindeberg sums are not monotone",
    )

    predictive = scaling["predictive_closure"]
    expected_partitions = [
        (state_name, classes)
        for state_name in (
            "intrinsic_mark",
            "intrinsic_mark_transverse",
            "full_six_coordinate",
        )
        for classes in PREDICTIVE_CLASSES
    ]
    checks.require(
        [
            (closure["state"], closure["requested_classes"])
            for closure in predictive
        ]
        == expected_partitions,
        f"{context} predictive partitions differ",
    )
    for closure in predictive:
        verify_predictive_closure(
            closure,
            list(range(first, last + 1)),
            f"{context} predictive {closure['state']} "
            f"{closure['requested_classes']}",
            checks,
        )


def verify_run(
    output: dict[str, Any],
    directory: Path,
    threads: int,
    checks: Checks,
) -> None:
    run, graphs = output["run"], output["graphs"]
    checks.require(
        run["schema"] == "bounded-systems.gap-run.v2",
        "run schema differs",
    )

    expected = {
        "vertices": VERTICES,
        "horizons": list(HORIZONS),
        "samples": SAMPLES,
        "master_seed": str(SEED),
        "requested_threads": threads,
        "effective_threads": min(threads, SAMPLES),
        "output_directory": str(directory),
        "closure_bins": list(CLOSURE_BINS),
        "predictive_classes": list(PREDICTIVE_CLASSES),
        "target_bins": list(TARGET_BINS),
        "reference_bins": REFERENCE_BINS,
        "lindeberg_thresholds": list(THRESHOLDS),
        "validation_length": VALIDATION_LENGTH,
        "legendre_modes": LEGENDRE_MODES,
        "bulk_fraction": BULK_FRACTION,
    }
    checks.require(run["configuration"] == expected, "run configuration differs")
    checks.require(
        run["generator"]["kernel"] == "(y-x)_+",
        "generator metadata differs",
    )
    checks.require(
        run["finite_sample_closure"]["holdout"]
        == "source vertices selected by deterministic identifier hash",
        "holdout metadata differs",
    )
    checks.require(
        run["continuum_scaling"]["route_time"]
        == "s=r/p with delta_s=1/p",
        "route-time metadata differs",
    )

    runtime = run["runtime"]
    require_fields(
        runtime,
        "wall_seconds summed_sample_seconds edge_total peak_rss_kib "
        "max_sample_estimated_peak_bytes",
        "run runtime",
        checks,
    )
    checks.require(
        finite(runtime["wall_seconds"])
        and runtime["wall_seconds"] >= 0.0
        and finite(runtime["summed_sample_seconds"])
        and runtime["summed_sample_seconds"] >= 0.0,
        "runtime is invalid",
    )
    checks.require(
        isinstance(runtime["peak_rss_kib"], int)
        and runtime["peak_rss_kib"] >= -1,
        "peak RSS metadata is invalid",
    )
    checks.require(
        runtime["edge_total"] == sum(graph["edges"] for graph in graphs),
        "runtime edge total differs",
    )
    checks.close(
        runtime["summed_sample_seconds"],
        sum(graph["timing_seconds"]["total"] for graph in graphs),
        "summed runtime",
    )
    checks.require(
        runtime["max_sample_estimated_peak_bytes"]
        == max(graph["estimated_bytes"]["peak"] for graph in graphs),
        "maximum sample bytes differ",
    )


def verify_output(output: dict[str, Any], directory: Path, threads: int, checks: Checks) -> None:
    graphs, horizons = output["graphs"], output["horizons"]
    checks.require(len(graphs) == SAMPLES, f"{directory} graph row count differs")
    checks.require(len(horizons) == SAMPLES * len(HORIZONS), f"{directory} horizon row count differs")
    checks.require(
        [row["sample_index"] for row in graphs] == list(range(SAMPLES)),
        f"{directory} graph order differs",
    )
    expected = [(sample, horizon) for sample in range(SAMPLES) for horizon in HORIZONS]
    checks.require(
        [(row["sample_index"], row["horizon"]) for row in horizons] == expected,
        f"{directory} horizon order differs",
    )
    for graph in graphs:
        verify_graph(graph, checks)
    for row in horizons:
        verify_horizon(row, checks)
    for graph in graphs:
        sample = graph["sample_index"]
        rows = {row["horizon"]: row for row in horizons if row["sample_index"] == sample}
        checks.require(
            all(
                row["sample_seed"] == graph["sample_seed"]
                and row["edges"] == graph["edges"]
                for row in rows.values()
            ),
            f"sample {sample} graph/horizon metadata differs",
        )
        verify_calibration(graph, rows, checks)
    verify_run(output, directory, threads, checks)


def scientific_projection(output: dict[str, Any]) -> dict[str, Any]:
    projected = copy.deepcopy(output)
    for name in ("requested_threads", "effective_threads", "output_directory"):
        del projected["run"]["configuration"][name]
    for name in ("wall_seconds", "summed_sample_seconds", "peak_rss_kib"):
        del projected["run"]["runtime"][name]
    for graph in projected["graphs"]:
        del graph["timing_seconds"]
    for horizon in projected["horizons"]:
        del horizon["analysis_seconds"]
        del horizon["continuum_scaling"]["analysis_seconds"]
    return projected


def main() -> None:
    checks = Checks()
    checks.require(BENCHMARK.is_file(), f"benchmark binary is missing: {BENCHMARK}")
    checks.require(os.access(BENCHMARK, os.X_OK), f"benchmark is not executable: {BENCHMARK}")
    self_test = run_checked((str(BENCHMARK), "--self-test"), timeout=15.0)
    match = re.fullmatch(r"gap route-bridge self-tests passed: ([1-9][0-9]*) checks\n?", self_test.stdout)
    checks.require(match is not None, f"unexpected --self-test output: {self_test.stdout!r}")
    checks.require(not self_test.stderr, f"--self-test wrote stderr: {self_test.stderr!r}")
    with tempfile.TemporaryDirectory(prefix="verify-gap-benchmark-") as temporary:
        serial_directory = Path(temporary) / "serial"
        threaded_directory = Path(temporary) / "threaded"
        serial_result = run_checked(arguments(serial_directory, 1), timeout=30.0)
        threaded_result = run_checked(arguments(threaded_directory, THREADS), timeout=30.0)
        checks.require(not serial_result.stdout and not threaded_result.stdout, "sample run wrote stdout")
        serial = load_output(serial_directory, checks)
        threaded = load_output(threaded_directory, checks)
        verify_output(serial, serial_directory, 1, checks)
        verify_output(threaded, threaded_directory, THREADS, checks)
        checks.require(
            scientific_projection(serial) == scientific_projection(threaded),
            "serial and threaded scientific outputs differ",
        )
    print(f"verified {checks.count} gap benchmark checks")


if __name__ == "__main__":
    main()
