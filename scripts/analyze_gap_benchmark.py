#!/usr/bin/env python3
"""Summarize ordered gap-kernel benchmark runs."""

from __future__ import annotations

import argparse
import copy
import json
import math
import statistics
import sys
from collections import defaultdict
from pathlib import Path
from typing import Any, Iterable, Sequence

RUN_SCHEMA = "bounded-systems.gap-run.v1"
GRAPH_SCHEMA = "bounded-systems.gap-graph.v1"
HORIZON_SCHEMA = "bounded-systems.gap-horizon.v1"
ANALYSIS_SCHEMA = "bounded-systems.gap-analysis.v1"
COORDINATES = ["d_out", "d_in", "q_pp", "q_mm", "q_pm", "q_mp"]

class InputError(ValueError):
    pass

def load_json(path: Path) -> Any:
    try:
        with path.open(encoding="utf-8") as stream:
            return json.load(stream)
    except (OSError, json.JSONDecodeError) as error:
        raise InputError(f"{path}: {error}") from error

def load_jsonl(path: Path) -> list[dict[str, Any]]:
    rows = []
    try:
        with path.open(encoding="utf-8") as stream:
            for line_number, line in enumerate(stream, 1):
                if not line.strip():
                    raise InputError(f"{path}:{line_number}: blank JSONL row")
                try:
                    row = json.loads(line)
                except json.JSONDecodeError as error:
                    raise InputError(f"{path}:{line_number}: {error}") from error
                if not isinstance(row, dict):
                    raise InputError(f"{path}:{line_number}: expected an object")
                rows.append(row)
    except OSError as error:
        raise InputError(f"{path}: {error}") from error
    return rows

def require_schema(row: Any, expected: str, context: str) -> dict[str, Any]:
    accepted = {expected}
    if expected.endswith(".v1"):
        accepted.add(expected.removesuffix(".v1") + ".v2")

    if not isinstance(row, dict) or row.get("schema") not in accepted:
        found = row.get("schema") if isinstance(row, dict) else type(row).__name__
        raise InputError(
            f"{context}: expected one of {sorted(accepted)!r}, found {found!r}"
        )
    return row


def normalize_horizon(row: dict[str, Any]) -> dict[str, Any]:
    """Map additive v2 diagnostics onto the historical v1 summary fields."""

    if row["schema"] == HORIZON_SCHEMA:
        return row

    normalized = dict(row)
    decomposition = row["covariance_decomposition"]
    normalized["time_scale"] = decomposition["mixed_trace"]
    normalized["maximal_jump"] = row["maximal_six_coordinate_jump"]
    normalized["scaled_maximal_jump"] = None
    normalized["scaled_raw_third_moment"] = None
    normalized["scaled_centered_third_moment"] = None
    normalized["lindeberg"] = [
        {
            "threshold": tail["threshold"],
            "second_moment_tail": tail["second_moment_tail"],
            "scaled_tail": None,
        }
        for tail in row["raw_jump_tails"]
    ]

    normalized["closure"] = []
    for closure in row["legacy_uniform_partition_closure"]:
        item = dict(closure)
        item["max_corrected_rms_defect"] = closure[
            "max_exact_route_weighted_rms_l2_defect"
        ]
        item["max_corrected_class_defect"] = closure[
            "max_exact_class_l2_defect"
        ]
        item["min_assessable_route_mass"] = closure[
            "minimum_total_route_mass"
        ]
        item["positions"] = []
        for position in closure["positions"]:
            position_item = dict(position)
            position_item["assessable_route_mass"] = position[
                "total_route_mass"
            ]
            position_item["corrected_rms_defect"] = position[
                "exact_route_weighted_rms_l2_defect"
            ]
            position_item["corrected_max_defect"] = position[
                "exact_max_class_l2_defect"
            ]
            item["positions"].append(position_item)
        normalized["closure"].append(item)

    normalized["bulk"] = {
        "first_position": row["bulk"]["first_position"],
        "last_position": row["bulk"]["last_position"],
        "drift_plateau_defect": row["bulk"]["max_p_drift_curve_deviation"],
        "covariance_plateau_defect": row["bulk"][
            "max_p2_covariance_curve_deviation"
        ],
        "coefficient_plateau_defect": row["bulk"][
            "scaled_coefficient_curve_deviation"
        ],
    }
    return normalized

def finite(value: Any) -> float | None:
    if value is None or isinstance(value, bool):
        return None
    try:
        number = float(value)
    except (TypeError, ValueError):
        return None
    return number if math.isfinite(number) else None

def same_number(left: Any, right: float) -> bool:
    number = finite(left)
    return number is not None and math.isclose(number, right, rel_tol=2e-13, abs_tol=2e-15)

def check(condition: bool, context: str, message: str) -> None:
    if not condition:
        raise InputError(f"{context}: {message}")

def validate_run(run: dict[str, Any], context: str) -> None:
    config = run["configuration"]
    horizons = config["horizons"]
    check(config["vertices"] >= 2 and config["samples"] >= 1, context,
          "invalid vertex or sample count")
    check(bool(horizons) and all(p >= 1 for p in horizons)
          and len(horizons) == len(set(horizons)), context,
          "horizons must be distinct positive integers")
    check(run["array_order"]["coordinates"] == COORDINATES, context,
          "unsupported coordinate order")
    check(run["array_order"]["covariance_upper"] == "lexicographic i<=j", context,
          "unsupported covariance packing")
    check(run["generator"]["kernel"] == "(y-x)_+", context, "unsupported generator kernel")

def validate_graph(row: dict[str, Any], run: dict[str, Any], context: str) -> None:
    config = run["configuration"]
    check(row["vertices"] == config["vertices"], context, "vertex count differs from run.json")
    check(0 <= row["sample_index"] < config["samples"], context,
          "sample index outside run configuration")
    check(len(row["even_legendre_modes"]) == config["legendre_modes"], context,
          "Legendre mode count differs from run.json")
    check(len(row["latent_validation"]["coordinate_rmse"]) == 6, context,
          "coordinate array must have length 6")
    check(same_number(row["directed_edge_target"], 1 / 6), context,
          "directed-edge target is not 1/6")
    calibration = row["route_calibration"]
    check(len(calibration) == config["validation_length"], context,
          "calibration length differs from run.json")
    for length, item in enumerate(calibration, 1):
        p_target = 1 / math.factorial(2 * length + 1)
        check(item["length"] == length, context, "nonconsecutive calibration lengths")
        check(same_number(item["path_homomorphism_target"], p_target)
              and same_number(item["subset_route_target"],
                              math.factorial(length + 1) * p_target),
              context, f"incorrect analytic calibration target at l={length}")

def validate_horizon(row: dict[str, Any], run: dict[str, Any], context: str) -> None:
    config = run["configuration"]
    check(row["vertices"] == config["vertices"] and row["horizon"] in config["horizons"],
          context, "row differs from run configuration")
    check(0 <= row["sample_index"] < config["samples"], context,
          "sample index outside run configuration")
    lengths = {"mean_increment": 6, "raw_second_upper": 21, "covariance_upper": 21,
               "raw_third_symmetric": 56, "centered_third_symmetric": 56}
    check(all(len(row[name]) == length for name, length in lengths.items()), context,
          "packed moment array has the wrong length")
    expected = 1 if row["has_routes"] else 0
    check(len(row["lindeberg"]) == expected * len(config["lindeberg_thresholds"])
          and len(row["closure"]) == expected * len(config["closure_bins"]), context,
          "diagnostic arrays differ from run.json")
    check(all(same_number(item["threshold"], threshold)
              for item, threshold in zip(row["lindeberg"], config["lindeberg_thresholds"]))
          and all(item["bins_per_coordinate"] == bins
                  for item, bins in zip(row["closure"], config["closure_bins"])),
          context, "diagnostic configuration differs from run.json")
    if row["has_routes"]:
        n, p = row["vertices"], row["horizon"]
        target = max(n - p - 1, 0) / ((2 * p + 2) * (2 * p + 3))
        check(same_number(row["expected_count_ratio"], target), context,
              "incorrect finite count-ratio target")

def load_directory(directory: Path) -> dict[str, Any]:
    run_path = directory / "run.json"
    graph_path = directory / "graphs.jsonl"
    horizon_path = directory / "horizons.jsonl"
    if not directory.is_dir():
        raise InputError(f"{directory}: not a directory")
    try:
        run = require_schema(load_json(run_path), RUN_SCHEMA, str(run_path))
        validate_run(run, str(run_path))
        graphs = load_jsonl(graph_path)
        horizons = load_jsonl(horizon_path)
        for index, row in enumerate(graphs, 1):
            require_schema(row, GRAPH_SCHEMA, f"{graph_path}:{index}")
            validate_graph(row, run, f"{graph_path}:{index}")
        for index, row in enumerate(horizons, 1):
            require_schema(row, HORIZON_SCHEMA, f"{horizon_path}:{index}")
        horizons = [normalize_horizon(row) for row in horizons]
        for index, row in enumerate(horizons, 1):
            validate_horizon(row, run, f"{horizon_path}:{index}")
    except (KeyError, TypeError) as error:
        raise InputError(f"{directory}: schema mismatch at {error}") from error

    config = run["configuration"]
    if len(graphs) != config["samples"]:
        raise InputError(f"{graph_path}: expected {config['samples']} rows, found {len(graphs)}")
    expected = config["samples"] * len(config["horizons"])
    if len(horizons) != expected:
        raise InputError(f"{horizon_path}: expected {expected} rows, found {len(horizons)}")
    graph_keys = {(row["sample_index"], row["sample_seed"]): row for row in graphs}
    if len(graph_keys) != len(graphs):
        raise InputError(f"{graph_path}: duplicate sample identity")
    seen = set()
    for row in horizons:
        sample_key = (row["sample_index"], row["sample_seed"])
        key = (*sample_key, row["horizon"])
        if sample_key not in graph_keys or row["edges"] != graph_keys[sample_key]["edges"]:
            raise InputError(f"{horizon_path}: row has no consistent graph sample")
        if key in seen:
            raise InputError(f"{horizon_path}: duplicate sample/horizon row")
        seen.add(key)
    return {"directory": directory.as_posix(), "run": run, "graphs": graphs, "horizons": horizons}

def without_runtime(row: dict[str, Any], names: Sequence[str]) -> dict[str, Any]:
    result = copy.deepcopy(row)
    for name in names:
        result.pop(name, None)
    return result

def unique_rows(bundles: Sequence[dict[str, Any]]) -> tuple[list[dict[str, Any]], list[dict[str, Any]], int, int]:
    graphs: dict[tuple[int, str], dict[str, Any]] = {}
    horizons: dict[tuple[int, int, str], dict[str, Any]] = {}
    duplicates = [0, 0]
    for bundle in bundles:
        for row in bundle["graphs"]:
            key = row["vertices"], row["sample_seed"]
            if key in graphs:
                duplicates[0] += 1
                if without_runtime(row, ("timing_seconds", "estimated_bytes")) != without_runtime(
                    graphs[key], ("timing_seconds", "estimated_bytes")
                ):
                    raise InputError(f"duplicate graph sample {key} has inconsistent values")
            else:
                graphs[key] = row
        for row in bundle["horizons"]:
            key = row["vertices"], row["horizon"], row["sample_seed"]
            if key in horizons:
                duplicates[1] += 1
                if without_runtime(row, ("analysis_seconds", "estimated_peak_bytes")) != without_runtime(
                    horizons[key], ("analysis_seconds", "estimated_peak_bytes")
                ):
                    raise InputError(f"duplicate horizon sample {key} has inconsistent values")
            else:
                horizons[key] = row
    return ([graphs[key] for key in sorted(graphs)],
            [horizons[key] for key in sorted(horizons)], *duplicates)

def stat(values: Iterable[Any], total: int | None = None) -> dict[str, Any]:
    materialized = [finite(value) for value in values]
    good = [value for value in materialized if value is not None]
    denominator = len(materialized) if total is None else total
    return {
        "sample_count": len(good),
        "null_count": denominator - len(good),
        "mean": statistics.fmean(good) if good else None,
        "standard_error": statistics.stdev(good) / math.sqrt(len(good)) if len(good) > 1 else None,
    }

def target_stat(values: Iterable[Any], target: float, relative: bool = False) -> dict[str, Any]:
    observed = [finite(value) for value in values]
    result = {
        "target": target,
        "observed": stat(observed),
        "signed_error": stat(None if value is None else value - target for value in observed),
        "absolute_error": stat(None if value is None else abs(value - target) for value in observed),
    }
    if relative:
        result["relative_error"] = stat(
            None if value is None or target == 0 else value / target - 1 for value in observed
        )
    return result

def symmetric_matrix(entries: Sequence[Any]) -> list[list[Any]]:
    matrix = [[None] * 6 for _ in range(6)]
    index = 0
    for row in range(6):
        for column in range(row, 6):
            matrix[row][column] = entries[index]
            matrix[column][row] = entries[index]
            index += 1
    return matrix

def covariance_jackknife(rows: Sequence[dict[str, Any]]) -> dict[str, Any]:
    samples = [[finite(value) for value in row["covariance_upper"]] for row in rows]
    samples = [sample for sample in samples if all(value is not None for value in sample)]
    n = len(samples)
    estimates = [statistics.fmean(sample[j] for sample in samples) for j in range(21)] if n else [None] * 21
    errors: list[float | None] = []
    for j in range(21):
        if n < 2:
            errors.append(None)
            continue
        leave = [statistics.fmean(samples[k][j] for k in range(n) if k != omitted) for omitted in range(n)]
        center = statistics.fmean(leave)
        errors.append(math.sqrt((n - 1) / n * sum((value - center) ** 2 for value in leave)))
    return {
        "method": "delete-1 jackknife over complete independent graph samples",
        "source_field": "covariance_upper",
        "coordinate_order": COORDINATES,
        "complete_sample_count": n,
        "excluded_sample_count": len(rows) - n,
        "full_sample_estimate": symmetric_matrix(estimates),
        "jackknife_estimate": symmetric_matrix(estimates),
        "standard_error": symmetric_matrix(errors),
    }

def leading_route_covariance(rows: Sequence[dict[str, Any]]) -> dict[str, Any]:
    lengths = sorted({item["length"] for row in rows for item in row["route_calibration"]})
    vectors = []
    for row in rows:
        calibration = {item["length"]: finite(item["scaled_route_fluctuation"])
                       for item in row["route_calibration"]}
        vector = [calibration.get(length) for length in lengths]
        if all(value is not None for value in vector):
            vectors.append([float(value) for value in vector])
    dimension, n = len(lengths), len(vectors)

    def covariance(samples: Sequence[Sequence[float]]) -> list[list[float]] | None:
        if len(samples) < 2:
            return None
        means = [statistics.fmean(sample[j] for sample in samples)
                 for j in range(dimension)]
        return [[sum((sample[i] - means[i]) * (sample[j] - means[j])
                     for sample in samples) / (len(samples) - 1)
                 for j in range(dimension)] for i in range(dimension)]

    sample_covariance = covariance(vectors)
    target = []
    for length in lengths:
        a_length = math.exp(
            math.lgamma(length + 1) - math.log(2) - math.lgamma(2 * length + 1)
        )
        row = []
        for other in lengths:
            a_other = math.exp(
                math.lgamma(other + 1) - math.log(2)
                - math.lgamma(2 * other + 1)
            )
            row.append(
                (length + 1) * (other + 1) * a_length * a_other
                * (
                    1 / (2 * length + 2 * other + 1)
                    - 1 / ((2 * length + 1) * (2 * other + 1))
                )
            )
        target.append(row)
    jackknife = standard_error = None
    if n >= 3 and sample_covariance is not None:
        leave = [covariance(vectors[:omitted] + vectors[omitted + 1:])
                 for omitted in range(n)]
        centers = [[statistics.fmean(matrix[i][j] for matrix in leave if matrix is not None)
                    for j in range(dimension)] for i in range(dimension)]
        jackknife = [[n * sample_covariance[i][j] - (n - 1) * centers[i][j]
                      for j in range(dimension)] for i in range(dimension)]
        standard_error = [[math.sqrt((n - 1) / n * sum(
            (matrix[i][j] - centers[i][j]) ** 2 for matrix in leave if matrix is not None))
            for j in range(dimension)] for i in range(dimension)]

    def errors(estimate: list[list[float]] | None, relative: bool) -> list[list[float]] | None:
        if estimate is None:
            return None
        return [
            [
                (
                    estimate[i][j] / target[i][j] - 1
                    if relative and target[i][j] != 0
                    else estimate[i][j] - target[i][j]
                    if not relative
                    else None
                )
                for j in range(dimension)
            ]
            for i in range(dimension)
        ]

    return {
        "length_order": lengths,
        "complete_sample_count": n,
        "excluded_sample_count": len(rows) - n,
        "sample_covariance": sample_covariance,
        "sample_covariance_signed_error": errors(sample_covariance, False),
        "sample_covariance_relative_error": errors(sample_covariance, True),
        "jackknife_method": "delete-1 jackknife over complete independent graph samples",
        "jackknife_estimate": jackknife,
        "jackknife_standard_error": standard_error,
        "jackknife_signed_error": errors(jackknife, False),
        "jackknife_relative_error": errors(jackknife, True),
        "exact_target_C1": target,
    }

def graph_summary(n: int, rows: Sequence[dict[str, Any]]) -> dict[str, Any]:
    timing_names = ("generation", "node_state", "route_counts", "total")
    byte_names = ("graph", "node_state", "route_workspace", "peak")
    scalar_names = ("edges", "height", "unoriented_edge_density")
    result = {
        "vertices": n,
        "sample_count": len(rows),
        "scalars": {name: stat(row[name] for row in rows) for name in scalar_names},
        "timing_seconds": {name: stat(row["timing_seconds"][name] for row in rows) for name in timing_names},
        "estimated_bytes": {name: stat(row["estimated_bytes"][name] for row in rows) for name in byte_names},
        "directed_edge_density": target_stat((row["directed_edge_density"] for row in rows), 1 / 6),
        "latent_validation": {
            name: stat(row["latent_validation"][name] for row in rows)
            for name in ("total_coordinate_rmse", "reconstructed_mark_rmse", "reconstructed_mark_max_error")
        },
        "even_legendre_modes": {
            f"mode_{j + 1}": stat(row["even_legendre_modes"][j] for row in rows)
            for j in range(max(len(row["even_legendre_modes"]) for row in rows))
        },
    }
    result["latent_validation"]["coordinate_rmse"] = {
        name: stat(row["latent_validation"]["coordinate_rmse"][j] for row in rows)
        for j, name in enumerate(COORDINATES)
    }
    signatures = [row["exact_signature"] for row in rows]
    result["exact_signature"] = {
        name: stat(item[name] for item in signatures)
        for name in ("class_count", "singleton_class_count", "singleton_node_count", "largest_class_size")
    }
    result["exact_signature"].update({
        "closure_degenerate": stat(float(item["closure_degenerate"]) for item in signatures),
        "degenerate_count": sum(bool(item["closure_degenerate"]) for item in signatures),
        "singleton_node_occupancy": stat(item["singleton_node_count"] / n for item in signatures),
        "singleton_class_fraction": stat(
            item["singleton_class_count"] / item["class_count"] if item["class_count"] else None
            for item in signatures
        ),
    })
    calibration: dict[int, list[dict[str, Any]]] = defaultdict(list)
    for row in rows:
        for item in row["route_calibration"]:
            calibration[item["length"]].append(item)
    result["route_calibration"] = []
    for length in sorted(calibration):
        items = calibration[length]
        p_target = 1 / math.factorial(2 * length + 1)
        theta_target = math.factorial(length + 1) * p_target
        result["route_calibration"].append({
            "length": length,
            "sample_count": len(items),
            "route_count_log": stat(item["route_count"]["log"] for item in items),
            "path_homomorphism_density": target_stat(
                (item["path_homomorphism_density"] for item in items), p_target
            ),
            "subset_route_mean": target_stat((item["subset_route_mean"] for item in items), theta_target),
            "scaled_route_fluctuation": stat(item["scaled_route_fluctuation"] for item in items),
            "leading_mode_prediction": stat(item["leading_mode_prediction"] for item in items),
            "leading_mode_residual": stat(item["leading_mode_residual"] for item in items),
        })
    result["leading_route_covariance"] = leading_route_covariance(rows)
    return result

def closure_summary(rows: Sequence[dict[str, Any]]) -> list[dict[str, Any]]:
    groups: dict[int, list[dict[str, Any]]] = defaultdict(list)
    for row in rows:
        for item in row["closure"]:
            groups[item["bins_per_coordinate"]].append(item)
    output = []
    for bins in sorted(groups):
        items = groups[bins]
        positions: dict[int, list[tuple[dict[str, Any], dict[str, Any]]]] = defaultdict(list)
        for item in items:
            for position in item["positions"]:
                positions[position["position"]].append((item, position))
        output.append({
            "bins_per_coordinate": bins,
            "sample_count": len(items),
            **{name: stat(item[name] for item in items) for name in (
                "class_count", "singleton_class_count", "largest_class_size",
                "max_corrected_rms_defect", "max_corrected_class_defect",
                "min_assessable_route_mass", "transition_plateau_defect")},
            "singleton_class_fraction": stat(
                item["singleton_class_count"] / item["class_count"] if item["class_count"] else None
                for item in items
            ),
            "positions": [{
                "position": position,
                "sample_count": len(values),
                "occupied_class_count": stat(value[1]["occupied_class_count"] for value in values),
                "occupied_class_fraction": stat(
                    value[1]["occupied_class_count"] / value[0]["class_count"]
                    if value[0]["class_count"] else None for value in values
                ),
                **{name: stat(value[1][name] for value in values) for name in (
                    "singleton_route_mass", "assessable_route_mass", "route_weighted_effective_size",
                    "corrected_rms_defect", "corrected_max_defect")},
            } for position, values in sorted(positions.items())],
        })
    return output



def horizon_summary(n: int, p: int, rows: Sequence[dict[str, Any]]) -> dict[str, Any]:
    valid = [row for row in rows if row["has_routes"]]
    missing = len(rows) - len(valid)
    values = lambda getter: [getter(row) for row in valid] + [None] * missing
    target = max(n - p - 1, 0) / ((2 * p + 2) * (2 * p + 3))
    scalar_names = ("time_scale", "maximal_jump", "scaled_maximal_jump",
                    "scaled_raw_third_moment", "scaled_centered_third_moment")
    scalars = {name: stat(values(lambda row, field=name: row[field])) for name in scalar_names}
    scalars.update({
        "route_count_log": stat(values(lambda row: row["route_count"]["log"])),
        "next_route_count_log": stat(values(lambda row: row["next_route_count"]["log"])),
        "route_growth_ratio": target_stat(values(lambda row: row["route_growth_ratio"]), target, True),
        "log_route_growth_ratio": stat(values(lambda row: row["log_route_growth_ratio"])),
        "analysis_seconds": stat(row["analysis_seconds"] for row in rows),
        "estimated_peak_bytes": stat(row["estimated_peak_bytes"] for row in rows),
    })
    audits = {name: stat(values(lambda row, field=name: row["audits"][field])) for name in (
        "max_flow_relative_error", "mean_flow_relative_error", "max_conditional_row_error",
        "max_forward_backward_log_error")}
    bulk = {name: stat(values(lambda row, field=name: row["bulk"][field])) for name in (
        "first_position", "last_position", "drift_plateau_defect", "covariance_plateau_defect",
        "coefficient_plateau_defect")}
    thresholds = sorted({float(item["threshold"]) for row in valid for item in row["lindeberg"]})
    lindeberg = []
    for threshold in thresholds:
        matching = [next(item for item in row["lindeberg"] if same_number(item["threshold"], threshold))
                    for row in valid]
        lindeberg.append({"threshold": threshold,
                          "second_moment_tail": stat(
                              [item["second_moment_tail"] for item in matching] + [None] * missing),
                          "scaled_tail": stat([item["scaled_tail"] for item in matching] + [None] * missing)})
    return {
        "vertices": n, "horizon": p, "sample_count": len(rows),
        "has_routes_count": len(valid), "has_routes": stat(float(row["has_routes"]) for row in rows),
        "finite_count_ratio_target": target, "scalars": scalars, "flow_audits": audits,
        "bulk_plateau": bulk,
        "mean_increment": {name: stat(values(lambda row, j=j: row["mean_increment"][j]))
                           for j, name in enumerate(COORDINATES)},
        "leading_covariance_6x6": covariance_jackknife(valid),
        "lindeberg": lindeberg, "closure": closure_summary(valid),
    }

def correlation(pairs: Sequence[tuple[float, float]]) -> float | None:
    if len(pairs) < 2:
        return None
    x_mean = statistics.fmean(x for x, _ in pairs)
    y_mean = statistics.fmean(y for _, y in pairs)
    x2 = sum((x - x_mean) ** 2 for x, _ in pairs)
    y2 = sum((y - y_mean) ** 2 for _, y in pairs)
    if x2 <= 0 or y2 <= 0:
        return None
    cross = sum((x - x_mean) * (y - y_mean) for x, y in pairs)
    return max(-1.0, min(1.0, cross / math.sqrt(x2 * y2)))

def ou_stat(pairs: Sequence[tuple[float, float]], delta: float) -> dict[str, Any]:
    def estimate(data: Sequence[tuple[float, float]]) -> tuple[float | None, float | None]:
        rho = correlation(data)
        rate = -math.log(rho) / delta if rho is not None and rho > 0 else None
        return rho, rate

    rho, rate = estimate(pairs)
    result = {"paired_sample_count": len(pairs), "full_sample_correlation": rho,
              "full_sample_rate": rate, "jackknife_correlation": None,
              "jackknife_correlation_standard_error": None, "jackknife_rate": None,
              "jackknife_rate_standard_error": None, "rate_target": 0.5,
              "jackknife_rate_error": None, "status": "insufficient paired variation"}
    if len(pairs) < 4 or rho is None or rate is None:
        return result
    leave = [estimate(pairs[:j] + pairs[j + 1:]) for j in range(len(pairs))]
    if any(item[0] is None or item[1] is None for item in leave):
        result["status"] = "a delete-1 replicate has nonpositive or degenerate correlation"
        return result
    n = len(pairs)
    def jackknife(full: float, samples: Sequence[float]) -> tuple[float, float]:
        center = statistics.fmean(samples)
        return (n * full - (n - 1) * center,
                math.sqrt((n - 1) / n * sum((value - center) ** 2 for value in samples)))
    jk_rho, se_rho = jackknife(rho, [item[0] for item in leave if item[0] is not None])
    jk_rate, se_rate = jackknife(rate, [item[1] for item in leave if item[1] is not None])
    result.update({"jackknife_correlation": jk_rho, "jackknife_correlation_standard_error": se_rho,
                   "jackknife_rate": jk_rate, "jackknife_rate_standard_error": se_rate,
                   "jackknife_rate_error": jk_rate - 0.5, "status": "estimated"})
    return result

def ou_comparisons(rows: Sequence[dict[str, Any]]) -> list[dict[str, Any]]:
    groups: dict[int, dict[str, dict[str, Any]]] = defaultdict(dict)
    for row in rows:
        groups[row["vertices"]][row["sample_seed"]] = row
    output = []
    sizes = sorted(groups)
    for index, small in enumerate(sizes):
        for large in sizes[index + 1:]:
            seeds = sorted(set(groups[small]) & set(groups[large]))
            if not seeds:
                continue
            delta = math.log(large / small)
            observables = []
            mode_count = min(len(groups[size][seed]["even_legendre_modes"])
                             for size in (small, large) for seed in seeds)
            for mode in range(mode_count):
                pairs = [(groups[small][seed]["even_legendre_modes"][mode],
                          groups[large][seed]["even_legendre_modes"][mode]) for seed in seeds]
                item = {"observable": f"even_legendre_mode_{mode + 1}"}
                item.update(ou_stat([(float(x), float(y)) for x, y in pairs
                                     if finite(x) is not None and finite(y) is not None], delta))
                observables.append(item)
            calibrations = {
                (size, seed): {item["length"]: item for item in groups[size][seed]["route_calibration"]}
                for size in (small, large) for seed in seeds
            }
            lengths = set(calibrations[(small, seeds[0])]) & set(calibrations[(large, seeds[0])])
            for seed in seeds[1:]:
                lengths &= set(calibrations[(small, seed)]) & set(calibrations[(large, seed)])
            for length in sorted(lengths):
                pairs = [(calibrations[(small, seed)][length]["scaled_route_fluctuation"],
                          calibrations[(large, seed)][length]["scaled_route_fluctuation"])
                         for seed in seeds]
                item = {"observable": f"scaled_route_fluctuation_length_{length}"}
                item.update(ou_stat([(float(x), float(y)) for x, y in pairs
                                     if finite(x) is not None and finite(y) is not None], delta))
                observables.append(item)
            output.append({"smaller_vertices": small, "larger_vertices": large,
                           "log_vertex_separation": delta,
                           "theoretical_correlation_at_rate_one_half": math.sqrt(small / large),
                           "matched_sample_seed_count": len(seeds), "observables": observables})
    return output

def run_summary(bundle: dict[str, Any]) -> dict[str, Any]:
    config, runtime = bundle["run"]["configuration"], bundle["run"]["runtime"]
    wall = finite(runtime["wall_seconds"])
    return {"input_directory": bundle["directory"], "vertices": config["vertices"],
            "horizons": config["horizons"], "declared_samples": config["samples"],
            "master_seed": config["master_seed"], "requested_threads": config["requested_threads"],
            "effective_threads": config["effective_threads"], "wall_seconds": wall,
            "summed_sample_seconds": finite(runtime["summed_sample_seconds"]),
            "edge_total": runtime["edge_total"],
            "edges_per_wall_second": runtime["edge_total"] / wall if wall and wall > 0 else None,
            "peak_rss_kib": runtime["peak_rss_kib"],
            "max_sample_estimated_peak_bytes": runtime["max_sample_estimated_peak_bytes"]}

def runtime_comparisons(bundles: Sequence[dict[str, Any]]) -> list[dict[str, Any]]:
    groups: dict[str, list[dict[str, Any]]] = defaultdict(list)
    for bundle in bundles:
        config = {key: value for key, value in bundle["run"]["configuration"].items()
                  if key not in {"requested_threads", "effective_threads", "output_directory"}}
        groups[json.dumps(config, sort_keys=True)].append(run_summary(bundle))
    output = []
    for signature, rows in sorted(groups.items()):
        rows.sort(key=lambda row: (row["effective_threads"], row["input_directory"]))
        if len(rows) < 2 or rows[0]["wall_seconds"] is None:
            continue
        baseline = rows[0]
        comparisons = []
        for row in rows:
            speedup = baseline["wall_seconds"] / row["wall_seconds"] if row["wall_seconds"] else None
            comparisons.append({"input_directory": row["input_directory"],
                                "effective_threads": row["effective_threads"],
                                "wall_seconds": row["wall_seconds"],
                                "speedup_against_baseline": speedup,
                                "parallel_efficiency_against_baseline":
                                    speedup * baseline["effective_threads"] / row["effective_threads"]
                                    if speedup is not None else None})
        output.append({"configuration": json.loads(signature),
                       "baseline_input_directory": baseline["input_directory"], "runs": comparisons})
    return output

def build_summary(bundles: Sequence[dict[str, Any]]) -> dict[str, Any]:
    graphs, horizons, graph_duplicates, horizon_duplicates = unique_rows(bundles)
    graph_groups: dict[int, list[dict[str, Any]]] = defaultdict(list)
    horizon_groups: dict[tuple[int, int], list[dict[str, Any]]] = defaultdict(list)
    for row in graphs:
        graph_groups[row["vertices"]].append(row)
    for row in horizons:
        horizon_groups[(row["vertices"], row["horizon"])].append(row)
    return {
        "schema": ANALYSIS_SCHEMA,
        "analysis_contract": {
            "ordinary_uncertainty": "sample mean and sample standard deviation divided by sqrt(n)",
            "jackknife_uncertainty": "delete-1 jackknife; null when undefined",
            "independence_unit": "unique (vertices, sample_seed) graph sample",
            "duplicate_policy": "scientifically identical repeated samples are counted once",
            "edge_target_t_edge": 1 / 6, "path_target_p_l": "1/(2*l+1)!",
            "subset_route_target_theta_l": "(l+1)!/(2*l+1)!",
            "leading_route_covariance_target": (
                "C1(l,m)=(l+1)(m+1)A_l*A_m*(1/(2l+2m+1)-"
                "1/((2l+1)(2m+1))), A_l=l!/(2(2l)!)"
            ),
            "finite_count_ratio_target": "max(N-p-1,0)/((2*p+2)*(2*p+3))",
            "ou_rate_target": 0.5,
            "ou_estimator": "-log(seed-matched Pearson correlation)/log(N_large/N_small)",
            "coordinate_order": COORDINATES},
        "inputs": [bundle["directory"] for bundle in bundles],
        "sample_accounting": {"run_directory_count": len(bundles),
            "graph_records_read": sum(len(bundle["graphs"]) for bundle in bundles),
            "unique_graph_samples": len(graphs), "duplicate_graph_records": graph_duplicates,
            "horizon_records_read": sum(len(bundle["horizons"]) for bundle in bundles),
            "unique_horizon_samples": len(horizons), "duplicate_horizon_records": horizon_duplicates},
        "runs": [run_summary(bundle) for bundle in bundles],
        "runtime_comparisons": runtime_comparisons(bundles),
        "by_vertices": [graph_summary(n, graph_groups[n]) for n in sorted(graph_groups)],
        "by_vertex_and_horizon": [horizon_summary(n, p, horizon_groups[(n, p)])
                                  for n, p in sorted(horizon_groups)],
        "ou_relaxation_comparisons": ou_comparisons(graphs),
    }

def fmt(value: Any) -> str:
    number = finite(value)
    return "null" if number is None else ("0" if number == 0 else f"{number:.6g}")

def mean_se(value: dict[str, Any]) -> str:
    return fmt(value["mean"]) if value["standard_error"] is None else \
        f"{fmt(value['mean'])} ± {fmt(value['standard_error'])}"

def render_markdown(summary: dict[str, Any]) -> str:
    lines = [
        "# Gap benchmark summary",
        "",
        "Entries are sample mean ± ordinary standard error; `null` means unavailable.",
        "",
        "## Calibration",
        "",
        "| N | samples | edge density | edge error | l | path error | route error |",
        "|---:|---:|---:|---:|---:|---:|---:|",
    ]
    for group in summary["by_vertices"]:
        edge = group["directed_edge_density"]
        for index, item in enumerate(group["route_calibration"]):
            lines.append(
                f"| {group['vertices'] if index == 0 else ''} | "
                f"{group['sample_count'] if index == 0 else ''} | "
                f"{mean_se(edge['observed']) if index == 0 else ''} | "
                f"{mean_se(edge['signed_error']) if index == 0 else ''} | "
                f"{item['length']} | "
                f"{mean_se(item['path_homomorphism_density']['signed_error'])} | "
                f"{mean_se(item['subset_route_mean']['signed_error'])} |"
            )

    lines.extend([
        "",
        "## Horizon diagnostics",
        "",
        "| N | p | routes | ratio rel. error | time scale | scaled jump | "
        "centered third | coefficient plateau | max flow | seconds |",
        "|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|",
    ])
    for group in summary["by_vertex_and_horizon"]:
        scalar = group["scalars"]
        lines.append(
            f"| {group['vertices']} | {group['horizon']} | "
            f"{group['has_routes_count']}/{group['sample_count']} | "
            f"{mean_se(scalar['route_growth_ratio']['relative_error'])} | "
            f"{mean_se(scalar['time_scale'])} | "
            f"{mean_se(scalar['scaled_maximal_jump'])} | "
            f"{mean_se(scalar['scaled_centered_third_moment'])} | "
            f"{mean_se(group['bulk_plateau']['coefficient_plateau_defect'])} | "
            f"{mean_se(group['flow_audits']['max_flow_relative_error'])} | "
            f"{mean_se(scalar['analysis_seconds'])} |"
        )

    lines.extend([
        "",
        "## Closure diagnostics",
        "",
        "| N | p | bins | classes | singleton fraction | assessable mass | "
        "RMS defect | transition plateau |",
        "|---:|---:|---:|---:|---:|---:|---:|---:|",
    ])
    for group in summary["by_vertex_and_horizon"]:
        for closure in group["closure"]:
            lines.append(
                f"| {group['vertices']} | {group['horizon']} | "
                f"{closure['bins_per_coordinate']} | "
                f"{mean_se(closure['class_count'])} | "
                f"{mean_se(closure['singleton_class_fraction'])} | "
                f"{mean_se(closure['min_assessable_route_mass'])} | "
                f"{mean_se(closure['max_corrected_rms_defect'])} | "
                f"{mean_se(closure['transition_plateau_defect'])} |"
            )

    lines.extend([
        "",
        "## OU rate estimates",
        "",
        "| smaller N | larger N | observable | pairs | rate | status |",
        "|---:|---:|---|---:|---:|---|",
    ])
    for comparison in summary["ou_relaxation_comparisons"]:
        for observable in comparison["observables"]:
            rate = observable["jackknife_rate"]
            error = observable["jackknife_rate_standard_error"]
            estimate = fmt(rate) if error is None else f"{fmt(rate)} ± {fmt(error)}"
            lines.append(
                f"| {comparison['smaller_vertices']} | "
                f"{comparison['larger_vertices']} | {observable['observable']} | "
                f"{observable['paired_sample_count']} | {estimate} | "
                f"{observable['status']} |"
            )

    lines.extend([
        "",
        "## Runtime",
        "",
        "| input | N | samples | threads | wall s | edges/s | peak RSS KiB |",
        "|---|---:|---:|---:|---:|---:|---:|",
    ])
    for run in summary["runs"]:
        lines.append(
            f"| {run['input_directory']} | {run['vertices']} | "
            f"{run['declared_samples']} | {run['effective_threads']} | "
            f"{fmt(run['wall_seconds'])} | {fmt(run['edges_per_wall_second'])} | "
            f"{run['peak_rss_kib']} |"
        )

    lines.extend([
        "",
        "## Parallel comparisons",
        "",
        "| input | threads | wall s | speedup | efficiency |",
        "|---|---:|---:|---:|---:|",
    ])
    for comparison in summary["runtime_comparisons"]:
        for run in comparison["runs"]:
            lines.append(
                f"| {run['input_directory']} | {run['effective_threads']} | "
                f"{fmt(run['wall_seconds'])} | "
                f"{fmt(run['speedup_against_baseline'])} | "
                f"{fmt(run['parallel_efficiency_against_baseline'])} |"
            )
    return "\n".join(lines) + "\n"

def write_output(path: Path, text: str) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    temporary = path.with_name(f".{path.name}.tmp")
    temporary.write_text(text, encoding="utf-8", newline="\n")
    temporary.replace(path)

def parse_args(arguments: Sequence[str]) -> argparse.Namespace:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("directories", nargs="*", metavar="DIR")
    parser.add_argument("--inputs", nargs="+", default=[], metavar="DIR")
    parser.add_argument("--output", required=True, type=Path)
    parser.add_argument("--markdown", type=Path)
    options = parser.parse_args(arguments)
    inputs = [Path(value) for value in options.directories + options.inputs]
    if not inputs:
        parser.error("at least one run directory is required")
    options.inputs = [dict((path.as_posix(), path) for path in inputs)[key]
                      for key in sorted({path.as_posix() for path in inputs})]
    return options

def main(arguments: Sequence[str] | None = None) -> int:
    options = parse_args(sys.argv[1:] if arguments is None else arguments)
    try:
        bundles = [load_directory(path) for path in options.inputs]
        summary = build_summary(bundles)
        markdown = render_markdown(summary)
        write_output(options.output, json.dumps(summary, indent=2, sort_keys=True, allow_nan=False) + "\n")
        if options.markdown:
            write_output(options.markdown, markdown)
        sys.stdout.write(markdown)
    except InputError as error:
        print(f"analyze_gap_benchmark.py: {error}", file=sys.stderr)
        return 2
    except OSError as error:
        print(f"analyze_gap_benchmark.py: {error}", file=sys.stderr)
        return 1
    return 0

if __name__ == "__main__":
    raise SystemExit(main())
