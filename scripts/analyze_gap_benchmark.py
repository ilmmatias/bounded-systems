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
from collections.abc import Iterable, Sequence
from pathlib import Path
from typing import Any

RUN_SCHEMA = "bounded-systems.gap-run.v1"
GRAPH_SCHEMA = "bounded-systems.gap-graph.v1"
HORIZON_SCHEMA = "bounded-systems.gap-horizon.v1"
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
    rows: list[dict[str, Any]] = []

    try:
        with path.open(encoding="utf-8") as stream:
            for line_no, line in enumerate(stream, 1):
                if not line.strip():
                    raise InputError(f"{path}:{line_no}: blank JSONL row")

                try:
                    row = json.loads(line)
                except json.JSONDecodeError as error:
                    raise InputError(f"{path}:{line_no}: {error}") from error

                if not isinstance(row, dict):
                    raise InputError(f"{path}:{line_no}: expected an object")

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

    out = dict(row)
    decomposition = row["covariance_decomposition"]
    out["time_scale"] = decomposition["mixed_trace"]
    out["maximal_jump"] = row["maximal_six_coordinate_jump"]
    out["scaled_maximal_jump"] = None
    out["scaled_raw_third_moment"] = None
    out["scaled_centered_third_moment"] = None
    out["lindeberg"] = [
        {
            "threshold": tail["threshold"],
            "second_moment_tail": tail["second_moment_tail"],
            "scaled_tail": None,
        }
        for tail in row["raw_jump_tails"]
    ]

    out["closure"] = []

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
            pos = dict(position)
            pos["assessable_route_mass"] = position["total_route_mass"]
            pos["corrected_rms_defect"] = position[
                "exact_route_weighted_rms_l2_defect"
            ]
            pos["corrected_max_defect"] = position[
                "exact_max_class_l2_defect"
            ]
            item["positions"].append(pos)

        out["closure"].append(item)

    out["bulk"] = {
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
    return out


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
    return number is not None and math.isclose(
        number, right, rel_tol=2e-13, abs_tol=2e-15
    )


def check(condition: bool, context: str, message: str) -> None:
    if not condition:
        raise InputError(f"{context}: {message}")


def validate_run(run: dict[str, Any], context: str) -> None:
    config = run["configuration"]
    horizons = config["horizons"]

    check(
        config["vertices"] >= 2 and config["samples"] >= 1,
        context,
        "invalid vertex or sample count",
    )

    check(
        bool(horizons)
        and all(p >= 1 for p in horizons)
        and len(horizons) == len(set(horizons)),
        context,
        "horizons must be distinct positive integers",
    )

    check(
        run["array_order"]["coordinates"] == COORDINATES,
        context,
        "unsupported coordinate order",
    )

    check(
        run["array_order"]["covariance_upper"] == "lexicographic i<=j",
        context,
        "unsupported covariance packing",
    )

    check(
        run["generator"]["kernel"] == "(y-x)_+",
        context,
        "unsupported generator kernel",
    )


def validate_graph(
    row: dict[str, Any], run: dict[str, Any], context: str
) -> None:
    config = run["configuration"]

    check(
        row["vertices"] == config["vertices"],
        context,
        "vertex count differs from run.json",
    )

    check(
        0 <= row["sample_index"] < config["samples"],
        context,
        "sample index outside run configuration",
    )

    check(
        len(row["even_legendre_modes"]) == config["legendre_modes"],
        context,
        "Legendre mode count differs from run.json",
    )

    check(
        len(row["latent_validation"]["coordinate_rmse"]) == 6,
        context,
        "coordinate array must have length 6",
    )

    check(
        same_number(row["directed_edge_target"], 1 / 6),
        context,
        "directed-edge target is not 1/6",
    )

    calibration = row["route_calibration"]

    check(
        len(calibration) == config["validation_length"],
        context,
        "calibration length differs from run.json",
    )

    for length, item in enumerate(calibration, 1):
        p_target = 1 / math.factorial(2 * length + 1)

        check(
            item["length"] == length,
            context,
            "nonconsecutive calibration lengths",
        )

        check(
            same_number(item["path_homomorphism_target"], p_target)
            and same_number(
                item["subset_route_target"],
                math.factorial(length + 1) * p_target,
            ),
            context,
            f"incorrect analytic calibration target at l={length}",
        )


def validate_horizon(
    row: dict[str, Any], run: dict[str, Any], context: str
) -> None:
    config = run["configuration"]

    check(
        row["vertices"] == config["vertices"]
        and row["horizon"] in config["horizons"],
        context,
        "row differs from run configuration",
    )

    check(
        0 <= row["sample_index"] < config["samples"],
        context,
        "sample index outside run configuration",
    )

    lengths = {
        "mean_increment": 6,
        "raw_second_upper": 21,
        "covariance_upper": 21,
        "raw_third_symmetric": 56,
        "centered_third_symmetric": 56,
    }

    check(
        all(len(row[name]) == length for name, length in lengths.items()),
        context,
        "packed moment array has the wrong length",
    )

    expected = 1 if row["has_routes"] else 0

    check(
        len(row["lindeberg"])
        == expected * len(config["lindeberg_thresholds"])
        and len(row["closure"]) == expected * len(config["closure_bins"]),
        context,
        "diagnostic arrays differ from run.json",
    )

    thresholds_match = all(
        same_number(item["threshold"], threshold)
        for item, threshold in zip(
            row["lindeberg"], config["lindeberg_thresholds"], strict=True
        )
    )
    bins_match = all(
        item["bins_per_coordinate"] == bins
        for item, bins in zip(
            row["closure"], config["closure_bins"], strict=True
        )
    )

    check(
        thresholds_match and bins_match,
        context,
        "diagnostic configuration differs from run.json",
    )

    if row["has_routes"]:
        n, p = row["vertices"], row["horizon"]
        target = max(n - p - 1, 0) / ((2 * p + 2) * (2 * p + 3))

        check(
            same_number(row["expected_count_ratio"], target),
            context,
            "incorrect finite count-ratio target",
        )


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

        for i, row in enumerate(graphs, 1):
            context = f"{graph_path}:{i}"
            require_schema(row, GRAPH_SCHEMA, context)
            validate_graph(row, run, context)

        for i, row in enumerate(horizons, 1):
            require_schema(row, HORIZON_SCHEMA, f"{horizon_path}:{i}")

        horizons = [normalize_horizon(row) for row in horizons]

        for i, row in enumerate(horizons, 1):
            validate_horizon(row, run, f"{horizon_path}:{i}")
    except (KeyError, TypeError) as error:
        raise InputError(f"{directory}: schema mismatch at {error}") from error

    config = run["configuration"]

    if len(graphs) != config["samples"]:
        raise InputError(
            f"{graph_path}: expected {config['samples']} rows, "
            f"found {len(graphs)}"
        )

    expected = config["samples"] * len(config["horizons"])

    if len(horizons) != expected:
        raise InputError(
            f"{horizon_path}: expected {expected} rows, found {len(horizons)}"
        )

    graph_keys = {
        (row["vertices"], row["sample_seed"]): row for row in graphs
    }

    for row in horizons:
        sample_key = (row["vertices"], row["sample_seed"])

        if (
            sample_key not in graph_keys
            or row["edges"] != graph_keys[sample_key]["edges"]
        ):
            raise InputError(
                f"{horizon_path}: horizon row does not match its graph row"
            )

    return {
        "directory": directory.as_posix(),
        "run": run,
        "graphs": graphs,
        "horizons": horizons,
    }


def without_runtime(row: dict[str, Any], names: Sequence[str]) -> dict[str, Any]:
    out = copy.deepcopy(row)

    for name in names:
        out.pop(name, None)

    return out


def without_horizon_runtime(row: dict[str, Any]) -> dict[str, Any]:
    out = without_runtime(
        row,
        ("analysis_seconds", "estimated_peak_bytes"),
    )
    scaling = out.get("continuum_scaling")

    if isinstance(scaling, dict):
        scaling.pop("analysis_seconds", None)
        scaling.pop("estimated_peak_bytes", None)

    return out


def unique_rows(
    bundles: Sequence[dict[str, Any]],
) -> tuple[list[dict[str, Any]], list[dict[str, Any]], int, int]:
    graphs: dict[tuple[int, str], dict[str, Any]] = {}
    horizons: dict[tuple[int, int, str], dict[str, Any]] = {}
    graph_duplicates = 0
    horizon_duplicates = 0

    for bundle in bundles:
        for row in bundle["graphs"]:
            key = row["vertices"], row["sample_seed"]

            if key not in graphs:
                graphs[key] = row
                continue

            graph_duplicates += 1
            current = without_runtime(
                row,
                ("timing_seconds", "estimated_bytes"),
            )
            previous = without_runtime(
                graphs[key],
                ("timing_seconds", "estimated_bytes"),
            )

            if current != previous:
                raise InputError(
                    f"duplicate graph sample {key} has inconsistent values"
                )

        for row in bundle["horizons"]:
            key = row["vertices"], row["horizon"], row["sample_seed"]

            if key not in horizons:
                horizons[key] = row
                continue

            horizon_duplicates += 1
            current = without_horizon_runtime(row)
            previous = without_horizon_runtime(horizons[key])

            if current != previous:
                raise InputError(
                    f"duplicate horizon sample {key} has inconsistent values"
                )

    graph_rows = [graphs[key] for key in sorted(graphs)]
    horizon_rows = [horizons[key] for key in sorted(horizons)]
    return graph_rows, horizon_rows, graph_duplicates, horizon_duplicates


def stat(values: Iterable[Any], total: int | None = None) -> dict[str, Any]:
    seen = [finite(value) for value in values]
    valid = [value for value in seen if value is not None]
    count = len(seen) if total is None else total
    error = None

    if len(valid) > 1:
        error = statistics.stdev(valid) / math.sqrt(len(valid))

    return {
        "sample_count": len(valid),
        "null_count": count - len(valid),
        "mean": statistics.fmean(valid) if valid else None,
        "standard_error": error,
    }


def target_stat(
    values: Iterable[Any],
    target: float,
    relative: bool = False,
) -> dict[str, Any]:
    observed = [finite(value) for value in values]
    out = {
        "target": target,
        "observed": stat(observed),
        "signed_error": stat(
            None if value is None else value - target for value in observed
        ),
        "absolute_error": stat(
            None if value is None else abs(value - target) for value in observed
        ),
    }

    if relative:
        out["relative_error"] = stat(
            None if value is None or target == 0 else value / target - 1
            for value in observed
        )

    return out


def symmetric_matrix(entries: Sequence[Any]) -> list[list[Any]]:
    out = [[None] * 6 for _ in range(6)]
    pos = 0

    for row in range(6):
        for col in range(row, 6):
            out[row][col] = entries[pos]
            out[col][row] = entries[pos]
            pos += 1

    return out


def covariance_jackknife(rows: Sequence[dict[str, Any]]) -> dict[str, Any]:
    samples = [
        [finite(value) for value in row["covariance_upper"]]
        for row in rows
    ]
    samples = [
        sample
        for sample in samples
        if all(value is not None for value in sample)
    ]
    n = len(samples)

    estimates = [None] * 21
    if n:
        estimates = [
            statistics.fmean(sample[j] for sample in samples)
            for j in range(21)
        ]

    errors: list[float | None] = []
    for j in range(21):
        if n < 2:
            errors.append(None)
            continue

        leave = [
            statistics.fmean(
                samples[k][j] for k in range(n) if k != omitted
            )
            for omitted in range(n)
        ]
        center = statistics.fmean(leave)
        error = math.sqrt(
            (n - 1) / n * sum((value - center) ** 2 for value in leave)
        )
        errors.append(error)

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


def leading_route_covariance(
    rows: Sequence[dict[str, Any]],
) -> dict[str, Any]:
    lengths = sorted(
        {
            item["length"]
            for row in rows
            for item in row["route_calibration"]
        }
    )
    vectors: list[list[float]] = []

    for row in rows:
        calibration = {
            item["length"]: finite(item["scaled_route_fluctuation"])
            for item in row["route_calibration"]
        }
        vector = [calibration.get(length) for length in lengths]

        if all(value is not None for value in vector):
            vectors.append([float(value) for value in vector])

    dim = len(lengths)
    n = len(vectors)

    def covariance(
        samples: Sequence[Sequence[float]],
    ) -> list[list[float]] | None:
        if len(samples) < 2:
            return None

        means = [
            statistics.fmean(sample[j] for sample in samples)
            for j in range(dim)
        ]
        return [
            [
                sum(
                    (sample[i] - means[i]) * (sample[j] - means[j])
                    for sample in samples
                )
                / (len(samples) - 1)
                for j in range(dim)
            ]
            for i in range(dim)
        ]

    sample_cov = covariance(vectors)
    target = []

    for length in lengths:
        a_length = math.exp(
            math.lgamma(length + 1)
            - math.log(2)
            - math.lgamma(2 * length + 1)
        )
        row = []

        for other in lengths:
            a_other = math.exp(
                math.lgamma(other + 1)
                - math.log(2)
                - math.lgamma(2 * other + 1)
            )
            value = (
                (length + 1)
                * (other + 1)
                * a_length
                * a_other
                * (
                    1 / (2 * length + 2 * other + 1)
                    - 1 / ((2 * length + 1) * (2 * other + 1))
                )
            )
            row.append(value)

        target.append(row)

    jackknife = None
    standard_error = None

    if n >= 3 and sample_cov is not None:
        leave = [
            covariance(vectors[:omitted] + vectors[omitted + 1 :])
            for omitted in range(n)
        ]
        centers = [
            [
                statistics.fmean(
                    matrix[i][j] for matrix in leave if matrix is not None
                )
                for j in range(dim)
            ]
            for i in range(dim)
        ]
        jackknife = [
            [
                n * sample_cov[i][j] - (n - 1) * centers[i][j]
                for j in range(dim)
            ]
            for i in range(dim)
        ]
        standard_error = [
            [
                math.sqrt(
                    (n - 1)
                    / n
                    * sum(
                        (matrix[i][j] - centers[i][j]) ** 2
                        for matrix in leave
                        if matrix is not None
                    )
                )
                for j in range(dim)
            ]
            for i in range(dim)
        ]

    def errors(
        estimate: list[list[float]] | None,
        relative: bool,
    ) -> list[list[float | None]] | None:
        if estimate is None:
            return None

        out: list[list[float | None]] = []
        for i in range(dim):
            row = []

            for j in range(dim):
                if relative:
                    value = (
                        estimate[i][j] / target[i][j] - 1
                        if target[i][j] != 0
                        else None
                    )
                else:
                    value = estimate[i][j] - target[i][j]

                row.append(value)

            out.append(row)

        return out

    return {
        "length_order": lengths,
        "complete_sample_count": n,
        "excluded_sample_count": len(rows) - n,
        "sample_covariance": sample_cov,
        "sample_covariance_signed_error": errors(sample_cov, False),
        "sample_covariance_relative_error": errors(sample_cov, True),
        "jackknife_method": (
            "delete-1 jackknife over complete independent graph samples"
        ),
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
    latent_names = (
        "total_coordinate_rmse",
        "reconstructed_mark_rmse",
        "reconstructed_mark_max_error",
    )

    out = {
        "vertices": n,
        "sample_count": len(rows),
        "scalars": {
            name: stat(row[name] for row in rows) for name in scalar_names
        },
        "timing_seconds": {
            name: stat(row["timing_seconds"][name] for row in rows)
            for name in timing_names
        },
        "estimated_bytes": {
            name: stat(row["estimated_bytes"][name] for row in rows)
            for name in byte_names
        },
        "directed_edge_density": target_stat(
            (row["directed_edge_density"] for row in rows),
            1 / 6,
        ),
        "latent_validation": {
            name: stat(row["latent_validation"][name] for row in rows)
            for name in latent_names
        },
        "even_legendre_modes": {
            f"mode_{j + 1}": stat(
                row["even_legendre_modes"][j] for row in rows
            )
            for j in range(
                max(len(row["even_legendre_modes"]) for row in rows)
            )
        },
    }
    out["latent_validation"]["coordinate_rmse"] = {
        name: stat(
            row["latent_validation"]["coordinate_rmse"][j] for row in rows
        )
        for j, name in enumerate(COORDINATES)
    }

    signatures = [row["exact_signature"] for row in rows]
    signature_names = (
        "class_count",
        "singleton_class_count",
        "singleton_node_count",
        "largest_class_size",
    )
    out["exact_signature"] = {
        name: stat(item[name] for item in signatures)
        for name in signature_names
    }
    out["exact_signature"].update(
        {
            "closure_degenerate": stat(
                float(item["closure_degenerate"]) for item in signatures
            ),
            "degenerate_count": sum(
                bool(item["closure_degenerate"]) for item in signatures
            ),
            "singleton_node_occupancy": stat(
                item["singleton_node_count"] / n for item in signatures
            ),
            "singleton_class_fraction": stat(
                item["singleton_class_count"] / item["class_count"]
                if item["class_count"]
                else None
                for item in signatures
            ),
        }
    )

    calibration: dict[int, list[dict[str, Any]]] = defaultdict(list)
    for row in rows:
        for item in row["route_calibration"]:
            calibration[item["length"]].append(item)

    out["route_calibration"] = []
    for length in sorted(calibration):
        items = calibration[length]
        p_target = 1 / math.factorial(2 * length + 1)
        theta_target = math.factorial(length + 1) * p_target
        out["route_calibration"].append(
            {
                "length": length,
                "sample_count": len(items),
                "route_count_log": stat(
                    item["route_count"]["log"] for item in items
                ),
                "path_homomorphism_density": target_stat(
                    (item["path_homomorphism_density"] for item in items),
                    p_target,
                ),
                "subset_route_mean": target_stat(
                    (item["subset_route_mean"] for item in items),
                    theta_target,
                ),
                "scaled_route_fluctuation": stat(
                    item["scaled_route_fluctuation"] for item in items
                ),
                "leading_mode_prediction": stat(
                    item["leading_mode_prediction"] for item in items
                ),
                "leading_mode_residual": stat(
                    item["leading_mode_residual"] for item in items
                ),
            }
        )

    out["leading_route_covariance"] = leading_route_covariance(rows)
    return out


def closure_summary(rows: Sequence[dict[str, Any]]) -> list[dict[str, Any]]:
    groups: dict[int, list[dict[str, Any]]] = defaultdict(list)

    for row in rows:
        for item in row["closure"]:
            groups[item["bins_per_coordinate"]].append(item)

    out = []
    scalar_names = (
        "class_count",
        "singleton_class_count",
        "largest_class_size",
        "max_corrected_rms_defect",
        "max_corrected_class_defect",
        "min_assessable_route_mass",
        "transition_plateau_defect",
    )
    position_names = (
        "singleton_route_mass",
        "assessable_route_mass",
        "route_weighted_effective_size",
        "corrected_rms_defect",
        "corrected_max_defect",
    )

    for bins in sorted(groups):
        items = groups[bins]
        positions: dict[
            int,
            list[tuple[dict[str, Any], dict[str, Any]]],
        ] = defaultdict(list)

        for item in items:
            for pos in item["positions"]:
                positions[pos["position"]].append((item, pos))

        position_rows = []
        for pos, values in sorted(positions.items()):
            position_rows.append(
                {
                    "position": pos,
                    "sample_count": len(values),
                    "occupied_class_count": stat(
                        value[1]["occupied_class_count"] for value in values
                    ),
                    "occupied_class_fraction": stat(
                        value[1]["occupied_class_count"]
                        / value[0]["class_count"]
                        if value[0]["class_count"]
                        else None
                        for value in values
                    ),
                    **{
                        name: stat(value[1][name] for value in values)
                        for name in position_names
                    },
                }
            )

        out.append(
            {
                "bins_per_coordinate": bins,
                "sample_count": len(items),
                **{
                    name: stat(item[name] for item in items)
                    for name in scalar_names
                },
                "singleton_class_fraction": stat(
                    item["singleton_class_count"] / item["class_count"]
                    if item["class_count"]
                    else None
                    for item in items
                ),
                "positions": position_rows,
            }
        )

    return out


def horizon_summary(
    n: int,
    p: int,
    rows: Sequence[dict[str, Any]],
) -> dict[str, Any]:
    valid = [row for row in rows if row["has_routes"]]
    missing = len(rows) - len(valid)

    def with_missing(getter: Any) -> list[Any]:
        return [getter(row) for row in valid] + [None] * missing

    target = max(n - p - 1, 0) / ((2 * p + 2) * (2 * p + 3))
    scalar_names = (
        "time_scale",
        "maximal_jump",
        "scaled_maximal_jump",
        "scaled_raw_third_moment",
        "scaled_centered_third_moment",
    )
    scalars = {
        name: stat(with_missing(lambda row, field=name: row[field]))
        for name in scalar_names
    }
    scalars.update(
        {
            "route_count_log": stat(
                with_missing(lambda row: row["route_count"]["log"])
            ),
            "next_route_count_log": stat(
                with_missing(lambda row: row["next_route_count"]["log"])
            ),
            "route_growth_ratio": target_stat(
                with_missing(lambda row: row["route_growth_ratio"]),
                target,
                True,
            ),
            "log_route_growth_ratio": stat(
                with_missing(lambda row: row["log_route_growth_ratio"])
            ),
            "analysis_seconds": stat(
                row["analysis_seconds"] for row in rows
            ),
            "estimated_peak_bytes": stat(
                row["estimated_peak_bytes"] for row in rows
            ),
        }
    )

    audit_names = (
        "max_flow_relative_error",
        "mean_flow_relative_error",
        "max_conditional_row_error",
        "max_forward_backward_log_error",
    )
    audits = {
        name: stat(with_missing(lambda row, field=name: row["audits"][field]))
        for name in audit_names
    }

    bulk_names = (
        "first_position",
        "last_position",
        "drift_plateau_defect",
        "covariance_plateau_defect",
        "coefficient_plateau_defect",
    )
    bulk = {
        name: stat(with_missing(lambda row, field=name: row["bulk"][field]))
        for name in bulk_names
    }

    thresholds = sorted(
        {
            float(item["threshold"])
            for row in valid
            for item in row["lindeberg"]
        }
    )
    lindeberg = []

    for threshold in thresholds:
        matching = [
            next(
                item
                for item in row["lindeberg"]
                if same_number(item["threshold"], threshold)
            )
            for row in valid
        ]
        lindeberg.append(
            {
                "threshold": threshold,
                "second_moment_tail": stat(
                    [item["second_moment_tail"] for item in matching]
                    + [None] * missing
                ),
                "scaled_tail": stat(
                    [item["scaled_tail"] for item in matching]
                    + [None] * missing
                ),
            }
        )

    return {
        "vertices": n,
        "horizon": p,
        "sample_count": len(rows),
        "has_routes_count": len(valid),
        "has_routes": stat(float(row["has_routes"]) for row in rows),
        "finite_count_ratio_target": target,
        "scalars": scalars,
        "flow_audits": audits,
        "bulk_plateau": bulk,
        "mean_increment": {
            name: stat(
                with_missing(lambda row, j=j: row["mean_increment"][j])
            )
            for j, name in enumerate(COORDINATES)
        },
        "leading_covariance_6x6": covariance_jackknife(valid),
        "lindeberg": lindeberg,
        "closure": closure_summary(valid),
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


def ou_stat(
    pairs: Sequence[tuple[float, float]],
    delta: float,
) -> dict[str, Any]:
    def estimate(
        data: Sequence[tuple[float, float]],
    ) -> tuple[float | None, float | None]:
        rho = correlation(data)
        rate = -math.log(rho) / delta if rho is not None and rho > 0 else None
        return rho, rate

    rho, rate = estimate(pairs)
    out = {
        "paired_sample_count": len(pairs),
        "full_sample_correlation": rho,
        "full_sample_rate": rate,
        "jackknife_correlation": None,
        "jackknife_correlation_standard_error": None,
        "jackknife_rate": None,
        "jackknife_rate_standard_error": None,
        "rate_target": 0.5,
        "jackknife_rate_error": None,
        "status": "insufficient paired variation",
    }

    if len(pairs) < 4 or rho is None or rate is None:
        return out

    leave = [estimate(pairs[:j] + pairs[j + 1 :]) for j in range(len(pairs))]

    if any(item[0] is None or item[1] is None for item in leave):
        out["status"] = (
            "a delete-1 replicate has nonpositive or degenerate correlation"
        )
        return out

    n = len(pairs)

    def jackknife(full: float, samples: Sequence[float]) -> tuple[float, float]:
        center = statistics.fmean(samples)
        estimate = n * full - (n - 1) * center
        error = math.sqrt(
            (n - 1) / n * sum((value - center) ** 2 for value in samples)
        )
        return estimate, error

    jk_rho, se_rho = jackknife(
        rho,
        [item[0] for item in leave if item[0] is not None],
    )
    jk_rate, se_rate = jackknife(
        rate,
        [item[1] for item in leave if item[1] is not None],
    )
    out.update(
        {
            "jackknife_correlation": jk_rho,
            "jackknife_correlation_standard_error": se_rho,
            "jackknife_rate": jk_rate,
            "jackknife_rate_standard_error": se_rate,
            "jackknife_rate_error": jk_rate - 0.5,
            "status": "estimated",
        }
    )
    return out


def ou_comparisons(rows: Sequence[dict[str, Any]]) -> list[dict[str, Any]]:
    groups: dict[int, dict[str, dict[str, Any]]] = defaultdict(dict)

    for row in rows:
        groups[row["vertices"]][row["sample_seed"]] = row

    out = []
    sizes = sorted(groups)

    for i, small in enumerate(sizes):
        for large in sizes[i + 1 :]:
            seeds = sorted(set(groups[small]) & set(groups[large]))

            if not seeds:
                continue

            delta = math.log(large / small)
            observables = []
            mode_count = min(
                len(groups[size][seed]["even_legendre_modes"])
                for size in (small, large)
                for seed in seeds
            )

            for mode in range(mode_count):
                pairs = [
                    (
                        groups[small][seed]["even_legendre_modes"][mode],
                        groups[large][seed]["even_legendre_modes"][mode],
                    )
                    for seed in seeds
                ]
                valid = [
                    (float(x), float(y))
                    for x, y in pairs
                    if finite(x) is not None and finite(y) is not None
                ]
                item = {"observable": f"even_legendre_mode_{mode + 1}"}
                item.update(ou_stat(valid, delta))
                observables.append(item)

            calibrations = {
                (size, seed): {
                    item["length"]: item
                    for item in groups[size][seed]["route_calibration"]
                }
                for size in (small, large)
                for seed in seeds
            }
            lengths = set(calibrations[(small, seeds[0])]) & set(
                calibrations[(large, seeds[0])]
            )

            for seed in seeds[1:]:
                lengths &= set(calibrations[(small, seed)])
                lengths &= set(calibrations[(large, seed)])

            for length in sorted(lengths):
                pairs = [
                    (
                        calibrations[(small, seed)][length][
                            "scaled_route_fluctuation"
                        ],
                        calibrations[(large, seed)][length][
                            "scaled_route_fluctuation"
                        ],
                    )
                    for seed in seeds
                ]
                valid = [
                    (float(x), float(y))
                    for x, y in pairs
                    if finite(x) is not None and finite(y) is not None
                ]
                item = {
                    "observable": f"scaled_route_fluctuation_length_{length}"
                }
                item.update(ou_stat(valid, delta))
                observables.append(item)

            out.append(
                {
                    "smaller_vertices": small,
                    "larger_vertices": large,
                    "log_vertex_separation": delta,
                    "theoretical_correlation_at_rate_one_half": math.sqrt(
                        small / large
                    ),
                    "matched_sample_seed_count": len(seeds),
                    "observables": observables,
                }
            )

    return out


def run_summary(bundle: dict[str, Any]) -> dict[str, Any]:
    config = bundle["run"]["configuration"]
    runtime = bundle["run"]["runtime"]
    wall = finite(runtime["wall_seconds"])

    return {
        "input_directory": bundle["directory"],
        "vertices": config["vertices"],
        "horizons": config["horizons"],
        "declared_samples": config["samples"],
        "master_seed": config["master_seed"],
        "requested_threads": config["requested_threads"],
        "effective_threads": config["effective_threads"],
        "wall_seconds": wall,
        "summed_sample_seconds": finite(runtime["summed_sample_seconds"]),
        "edge_total": runtime["edge_total"],
        "edges_per_wall_second": (
            runtime["edge_total"] / wall if wall and wall > 0 else None
        ),
        "peak_rss_kib": runtime["peak_rss_kib"],
        "max_sample_estimated_peak_bytes": runtime[
            "max_sample_estimated_peak_bytes"
        ],
    }


def runtime_comparisons(
    bundles: Sequence[dict[str, Any]],
) -> list[dict[str, Any]]:
    groups: dict[str, list[dict[str, Any]]] = defaultdict(list)

    for bundle in bundles:
        config = {
            key: value
            for key, value in bundle["run"]["configuration"].items()
            if key
            not in {
                "requested_threads",
                "effective_threads",
                "output_directory",
            }
        }
        signature = json.dumps(config, sort_keys=True)
        groups[signature].append(run_summary(bundle))

    out = []
    for signature, rows in sorted(groups.items()):
        rows.sort(
            key=lambda row: (
                row["effective_threads"],
                row["input_directory"],
            )
        )

        if len(rows) < 2 or rows[0]["wall_seconds"] is None:
            continue

        baseline = rows[0]
        comparisons = []

        for row in rows:
            speedup = (
                baseline["wall_seconds"] / row["wall_seconds"]
                if row["wall_seconds"]
                else None
            )
            efficiency = (
                speedup
                * baseline["effective_threads"]
                / row["effective_threads"]
                if speedup is not None
                else None
            )
            comparisons.append(
                {
                    "input_directory": row["input_directory"],
                    "effective_threads": row["effective_threads"],
                    "wall_seconds": row["wall_seconds"],
                    "speedup_against_baseline": speedup,
                    "parallel_efficiency_against_baseline": efficiency,
                }
            )

        out.append(
            {
                "configuration": json.loads(signature),
                "baseline_input_directory": baseline["input_directory"],
                "runs": comparisons,
            }
        )

    return out


def build_summary(bundles: Sequence[dict[str, Any]]) -> dict[str, Any]:
    graphs, horizons, graph_duplicates, horizon_duplicates = unique_rows(
        bundles
    )
    graph_groups: dict[int, list[dict[str, Any]]] = defaultdict(list)
    horizon_groups: dict[tuple[int, int], list[dict[str, Any]]] = defaultdict(
        list
    )

    for row in graphs:
        graph_groups[row["vertices"]].append(row)

    for row in horizons:
        key = row["vertices"], row["horizon"]
        horizon_groups[key].append(row)

    return {
        "inputs": [bundle["directory"] for bundle in bundles],
        "sample_accounting": {
            "run_directory_count": len(bundles),
            "graph_records_read": sum(
                len(bundle["graphs"]) for bundle in bundles
            ),
            "unique_graph_samples": len(graphs),
            "duplicate_graph_records": graph_duplicates,
            "horizon_records_read": sum(
                len(bundle["horizons"]) for bundle in bundles
            ),
            "unique_horizon_samples": len(horizons),
            "duplicate_horizon_records": horizon_duplicates,
        },
        "runs": [run_summary(bundle) for bundle in bundles],
        "runtime_comparisons": runtime_comparisons(bundles),
        "by_vertices": [
            graph_summary(n, graph_groups[n]) for n in sorted(graph_groups)
        ],
        "by_vertex_and_horizon": [
            horizon_summary(n, p, horizon_groups[(n, p)])
            for n, p in sorted(horizon_groups)
        ],
        "ou_relaxation_comparisons": ou_comparisons(graphs),
    }


def write_output(path: Path, text: str) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    temp = path.with_name(f".{path.name}.tmp")
    temp.write_text(text, encoding="utf-8", newline="\n")
    temp.replace(path)


def parse_args(args: Sequence[str] | None = None) -> argparse.Namespace:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("directories", nargs="+", type=Path, metavar="DIR")
    parser.add_argument("--output", required=True, type=Path)
    opt = parser.parse_args(args)

    unique = {path.as_posix(): path for path in opt.directories}
    opt.directories = [unique[key] for key in sorted(unique)]
    return opt


def main(args: Sequence[str] | None = None) -> int:
    opt = parse_args(args)

    try:
        bundles = [load_directory(path) for path in opt.directories]
        summary = build_summary(bundles)
        payload = json.dumps(
            summary,
            indent=2,
            sort_keys=True,
            allow_nan=False,
        )
    except InputError as error:
        print(f"analyze_gap_benchmark.py: {error}", file=sys.stderr)
        return 2

    try:
        write_output(opt.output, payload + "\n")
    except OSError as error:
        print(f"analyze_gap_benchmark.py: {error}", file=sys.stderr)
        return 1

    return 0


if __name__ == "__main__":
    raise SystemExit(main())
