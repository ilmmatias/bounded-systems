#!/usr/bin/env python3
"""Aggregate continuum-scaling diagnostics from gap benchmark v2 runs."""

from __future__ import annotations

import argparse
import json
import math
import statistics
import sys
from collections import defaultdict
from pathlib import Path
from typing import Any, Callable, Iterable, Sequence

RUN_SCHEMA = "bounded-systems.gap-run.v2"
GRAPH_SCHEMA = "bounded-systems.gap-graph.v2"
HORIZON_SCHEMA = "bounded-systems.gap-horizon.v2"
ANALYSIS_SCHEMA = "bounded-systems.gap-scaling-analysis.v1"
WITHIN_TRACE_LIMIT = 179.0 / 504.0
BETWEEN_TRACE_LIMIT = 59.0 / 336.0
CONDITIONAL_THIRD_NORM_LIMIT = math.sqrt(68_989_499.0 / 1_371_686_400.0)


class InputError(ValueError):
    pass


def load_json(path: Path) -> Any:
    try:
        return json.loads(path.read_text(encoding="utf-8"))
    except (OSError, json.JSONDecodeError) as error:
        raise InputError(f"{path}: {error}") from error


def load_jsonl(path: Path) -> list[dict[str, Any]]:
    try:
        lines = path.read_text(encoding="utf-8").splitlines()
    except OSError as error:
        raise InputError(f"{path}: {error}") from error

    rows: list[dict[str, Any]] = []
    for line_number, line in enumerate(lines, 1):
        if not line.strip():
            raise InputError(f"{path}:{line_number}: blank JSONL row")
        try:
            row = json.loads(line)
        except json.JSONDecodeError as error:
            raise InputError(f"{path}:{line_number}: {error}") from error
        if not isinstance(row, dict):
            raise InputError(f"{path}:{line_number}: expected an object")
        rows.append(row)

    return rows


def require_schema(row: Any, schema: str, context: str) -> dict[str, Any]:
    if not isinstance(row, dict) or row.get("schema") != schema:
        found = row.get("schema") if isinstance(row, dict) else type(row).__name__
        raise InputError(f"{context}: expected {schema!r}, found {found!r}")
    return row


def load_directory(directory: Path) -> dict[str, Any]:
    run = require_schema(
        load_json(directory / "run.json"),
        RUN_SCHEMA,
        str(directory / "run.json"),
    )
    graphs = load_jsonl(directory / "graphs.jsonl")
    horizons = load_jsonl(directory / "horizons.jsonl")

    for index, graph in enumerate(graphs, 1):
        require_schema(graph, GRAPH_SCHEMA, f"{directory}/graphs.jsonl:{index}")
    for index, horizon in enumerate(horizons, 1):
        require_schema(
            horizon,
            HORIZON_SCHEMA,
            f"{directory}/horizons.jsonl:{index}",
        )

    configuration = run["configuration"]
    expected_horizons = configuration["samples"] * len(configuration["horizons"])
    if len(graphs) != configuration["samples"] or len(horizons) != expected_horizons:
        raise InputError(f"{directory}: row counts disagree with run.json")

    return {
        "directory": directory.as_posix(),
        "run": run,
        "graphs": graphs,
        "horizons": horizons,
    }


# Sample-level reductions


def finite_values(values: Iterable[Any]) -> list[float]:
    result: list[float] = []
    for value in values:
        if value is None or isinstance(value, bool):
            continue
        number = float(value)
        if math.isfinite(number):
            result.append(number)
    return result


def stat(values: Iterable[Any]) -> dict[str, Any]:
    samples = finite_values(values)
    if not samples:
        return {"mean": None, "standard_error": None, "sample_count": 0}

    standard_error = (
        statistics.stdev(samples) / math.sqrt(len(samples))
        if len(samples) > 1
        else None
    )
    return {
        "mean": statistics.fmean(samples),
        "standard_error": standard_error,
        "sample_count": len(samples),
    }


def vector_norm(values: Sequence[float]) -> float:
    return math.sqrt(sum(value * value for value in values))


def average(values: Iterable[float]) -> float:
    materialized = list(values)
    return statistics.fmean(materialized)


def profile_scalars(row: dict[str, Any]) -> dict[str, float]:
    profiles = row["continuum_scaling"]["route_profile"]
    midpoint = min(profiles, key=lambda item: abs(item["normalized_position"] - 0.5))

    return {
        "latent_mean_max_error": max(
            abs(item["latent_mean"] - item["beta_mean"]) for item in profiles
        ),
        "intrinsic_mean_max_error": max(
            abs(item["intrinsic_mean"] - item["beta_mean"])
            for item in profiles
        ),
        "latent_variance_max_error": max(
            abs(item["latent_variance"] - item["beta_variance"])
            for item in profiles
        ),
        "intrinsic_variance_max_error": max(
            abs(item["intrinsic_variance"] - item["beta_variance"])
            for item in profiles
        ),
        "latent_kolmogorov_max": max(
            item["latent_kolmogorov"] for item in profiles
        ),
        "intrinsic_kolmogorov_max": max(
            item["intrinsic_kolmogorov"] for item in profiles
        ),
        "intrinsic_oracle_rmse_mean": average(
            item["intrinsic_oracle_rmse"] for item in profiles
        ),
        "intrinsic_outside_mass_max": max(
            item["intrinsic_outside_mass"] for item in profiles
        ),
        "midpoint_intrinsic_variance": midpoint["intrinsic_variance"],
        "midpoint_two_p_intrinsic_variance": midpoint[
            "two_p_intrinsic_variance"
        ],
        "midpoint_two_p_latent_variance": midpoint["two_p_latent_variance"],
        "midpoint_limit_variance": (
            midpoint["normalized_position"]
            * (1.0 - midpoint["normalized_position"])
        ),
    }


def spacing_scalars(row: dict[str, Any]) -> dict[str, float]:
    spacing = row["continuum_scaling"]["spacing"]
    return {
        "gap_mean_max_error": max(
            abs(item["gap_mean"] - item["gap_target_mean"]) for item in spacing
        ),
        "gap_variance_max_error": max(
            abs(item["gap_variance"] - item["gap_target_variance"])
            for item in spacing
        ),
        "fraction_mean_max_error": max(
            abs(
                item["conditional_fraction_mean"]
                - item["conditional_fraction_target_mean"]
            )
            for item in spacing
        ),
        "fraction_variance_max_error": max(
            abs(
                item["conditional_fraction_variance"]
                - item["conditional_fraction_target_variance"]
            )
            for item in spacing
        ),
        "gap_kolmogorov_bound_max": max(
            item["gap_kolmogorov_bound"] for item in spacing
        ),
        "fraction_kolmogorov_bound_max": max(
            item["conditional_fraction_kolmogorov_bound"] for item in spacing
        ),
        "source_fraction_correlation_max": max(
            abs(item["source_fraction_correlation"]) for item in spacing
        ),
    }


def horizon_scalars(row: dict[str, Any]) -> dict[str, float]:
    horizon = row["horizon"]
    decomposition = row["covariance_decomposition"]
    scaling = row["continuum_scaling"]

    values = {
        "mean_increment_norm": vector_norm(row["mean_increment"]),
        "within_covariance_trace": decomposition["within_position_trace"],
        "between_covariance_trace": decomposition["between_position_trace"],
        "p2_within_covariance_trace": (
            horizon * horizon * decomposition["within_position_trace"]
        ),
        "p2_between_covariance_trace": (
            horizon * horizon * decomposition["between_position_trace"]
        ),
        "within_centered_third_norm": row[
            "within_position_centered_third_norm"
        ],
        "p3_within_centered_third_norm": (
            horizon**3 * row["within_position_centered_third_norm"]
        ),
        "p2_within_covariance_trace_error": (
            horizon**2 * decomposition["within_position_trace"]
            - WITHIN_TRACE_LIMIT
        ),
        "p2_between_covariance_trace_error": (
            horizon**2 * decomposition["between_position_trace"]
            - BETWEEN_TRACE_LIMIT
        ),
        "p3_within_centered_third_norm_error": (
            horizon**3 * row["within_position_centered_third_norm"]
            - CONDITIONAL_THIRD_NORM_LIMIT
        ),
        "maximal_six_coordinate_jump": row["maximal_six_coordinate_jump"],
        "p_intrinsic_mark_maximum": scaling["jumps"][
            "p_intrinsic_mark_maximum"
        ],
        "sqrt_2p_centered_intrinsic_maximum": scaling["jumps"][
            "sqrt_2p_centered_intrinsic_maximum"
        ],
        "drift_curve_deviation": row["bulk"][
            "max_p_drift_curve_deviation"
        ],
        "covariance_curve_deviation": row["bulk"][
            "max_p2_covariance_curve_deviation"
        ],
    }
    values.update(profile_scalars(row))
    values.update(spacing_scalars(row))

    for tail in scaling["jumps"]["lindeberg_sums"]:
        values[f"lindeberg_{tail['threshold']:.12g}"] = tail["sum"]

    return values


def predictive_sample_rows(row: dict[str, Any]) -> list[dict[str, Any]]:
    output: list[dict[str, Any]] = []

    for closure in row["continuum_scaling"]["predictive_closure"]:
        positions = closure["positions"]
        for target_bins in positions[0]["target_partitions"]:
            bins = target_bins["bins"]
            target_rows = [
                next(
                    item
                    for item in position["target_partitions"]
                    if item["bins"] == bins
                )
                for position in positions
            ]

            held_out_mass = sum(position["held_out_route_mass"] for position in positions)
            covered_mass = sum(position["held_out_covered_mass"] for position in positions)
            output.append(
                {
                    "vertices": row["vertices"],
                    "horizon": row["horizon"],
                    "state": closure["state"],
                    "classes": closure["requested_classes"],
                    "target_bins": bins,
                    "exact_mark_rmse": average(
                        position["exact_moment_rmse"][0] for position in positions
                    ),
                    "held_out_mark_rmse": average(
                        position["held_out_moment_rmse"][0]
                        for position in positions
                    ),
                    "exact_transverse_rmse": average(
                        math.sqrt(
                            statistics.fmean(
                                value * value
                                for value in position["exact_moment_rmse"][1:]
                            )
                        )
                        for position in positions
                    ),
                    "held_out_transverse_rmse": average(
                        math.sqrt(
                            statistics.fmean(
                                value * value
                                for value in position["held_out_moment_rmse"][1:]
                            )
                        )
                        for position in positions
                    ),
                    "exact_moment_r2": average(
                        position["exact_moment_r2"] for position in positions
                    ),
                    "held_out_moment_r2": average(
                        position["held_out_moment_r2"] for position in positions
                    ),
                    "held_out_coverage": (
                        covered_mass / held_out_mass if held_out_mass > 0.0 else None
                    ),
                    "exact_total_variation": average(
                        item["exact_total_variation"] for item in target_rows
                    ),
                    "held_out_total_variation": average(
                        item["held_out_total_variation"] for item in target_rows
                    ),
                    "exact_wasserstein_1": average(
                        item["exact_wasserstein_1"] for item in target_rows
                    ),
                    "held_out_wasserstein_1": average(
                        item["held_out_wasserstein_1"] for item in target_rows
                    ),
                }
            )

    return output


# Aggregation across independent graph samples


def aggregate_records(
    records: Sequence[dict[str, Any]], key_names: Sequence[str]
) -> list[dict[str, Any]]:
    groups: dict[tuple[Any, ...], list[dict[str, Any]]] = defaultdict(list)
    for record in records:
        groups[tuple(record[name] for name in key_names)].append(record)

    output: list[dict[str, Any]] = []
    for key in sorted(groups):
        rows = groups[key]
        item = {name: value for name, value in zip(key_names, key, strict=True)}
        item["sample_count"] = len(rows)

        value_names = sorted(set(rows[0]) - set(key_names))
        for name in value_names:
            if name != "sample_count":
                item[name] = stat(row.get(name) for row in rows)
        output.append(item)

    return output


def logarithmic_slope(points: Sequence[tuple[float, float]]) -> float | None:
    usable = [(x, y) for x, y in points if x > 0.0 and y > 0.0]
    if len(usable) < 3:
        return None

    log_x = [math.log(x) for x, _ in usable]
    log_y = [math.log(y) for _, y in usable]
    mean_x = statistics.fmean(log_x)
    mean_y = statistics.fmean(log_y)
    denominator = sum((value - mean_x) ** 2 for value in log_x)
    if denominator == 0.0:
        return None

    return sum(
        (x - mean_x) * (y - mean_y)
        for x, y in zip(log_x, log_y, strict=True)
    ) / denominator


def stabilization_exponents(horizons: Sequence[dict[str, Any]]) -> list[dict[str, Any]]:
    by_sample: dict[tuple[int, str], list[dict[str, Any]]] = defaultdict(list)
    for row in horizons:
        by_sample[(row["vertices"], row["sample_seed"])].append(row)

    metric_names = (
        "mean_increment_norm",
        "within_covariance_trace",
        "between_covariance_trace",
        "within_centered_third_norm",
        "midpoint_intrinsic_variance",
        "maximal_six_coordinate_jump",
    )
    slopes: dict[tuple[int, str], list[float]] = defaultdict(list)

    for (vertices, _), rows in by_sample.items():
        scalar_rows = [(row["horizon"], horizon_scalars(row)) for row in rows]
        for metric in metric_names:
            slope = logarithmic_slope(
                [(horizon, values[metric]) for horizon, values in scalar_rows]
            )
            if slope is not None:
                slopes[(vertices, metric)].append(-slope)

    return [
        {
            "vertices": vertices,
            "observable": metric,
            "decay_power": stat(values),
        }
        for (vertices, metric), values in sorted(slopes.items())
    ]


def position_curves(horizons: Sequence[dict[str, Any]]) -> list[dict[str, Any]]:
    groups: dict[tuple[int, int, int], list[dict[str, Any]]] = defaultdict(list)
    for row in horizons:
        profiles = {
            item["position"]: item
            for item in row["continuum_scaling"]["route_profile"]
        }
        for position in row["positions"]:
            groups[(row["vertices"], row["horizon"], position["position"])].append(
                {"coefficient": position, "profile": profiles[position["position"]]}
            )

    output: list[dict[str, Any]] = []
    for (vertices, horizon, position), rows in sorted(groups.items()):
        output.append(
            {
                "vertices": vertices,
                "horizon": horizon,
                "position": position,
                "normalized_position": position / horizon,
                "sample_count": len(rows),
                "p_mean_increment": [
                    stat(row["coefficient"]["p_mean_increment"][index] for row in rows)
                    for index in range(6)
                ],
                "p2_covariance_upper": [
                    stat(row["coefficient"]["p2_covariance_upper"][index] for row in rows)
                    for index in range(21)
                ],
                "latent_mean": stat(row["profile"]["latent_mean"] for row in rows),
                "intrinsic_mean": stat(
                    row["profile"]["intrinsic_mean"] for row in rows
                ),
                "beta_mean": rows[0]["profile"]["beta_mean"],
                "two_p_latent_variance": stat(
                    row["profile"]["two_p_latent_variance"] for row in rows
                ),
                "two_p_intrinsic_variance": stat(
                    row["profile"]["two_p_intrinsic_variance"] for row in rows
                ),
            }
        )

    return output


def build_summary(bundles: Sequence[dict[str, Any]]) -> dict[str, Any]:
    graphs = [graph for bundle in bundles for graph in bundle["graphs"]]
    all_horizons = [row for bundle in bundles for row in bundle["horizons"]]
    horizons = [row for row in all_horizons if row["has_routes"]]

    support_groups: dict[tuple[int, int], list[bool]] = defaultdict(list)
    for row in all_horizons:
        support_groups[(row["vertices"], row["horizon"])].append(
            row["has_routes"]
        )
    route_support = [
        {
            "vertices": vertices,
            "horizon": horizon,
            "sample_count": len(values),
            "route_sample_count": sum(values),
            "route_sample_fraction": sum(values) / len(values),
        }
        for (vertices, horizon), values in sorted(support_groups.items())
    ]
    graph_records = []
    for graph in graphs:
        scaling = graph["intrinsic_scaling"]
        graph_records.append(
            {
                "vertices": graph["vertices"],
                "directed_edge_density": graph["directed_edge_density"],
                "transverse_residual_rms": scaling["transverse_residual_rms"],
                "sqrt_N_transverse_residual_rms": scaling[
                    "sqrt_N_transverse_residual_rms"
                ],
                "intrinsic_mark_oracle_rmse": graph["latent_validation"][
                    "reconstructed_mark_rmse"
                ],
                "total_seconds": graph["timing_seconds"]["total"],
                "estimated_peak_bytes": graph["estimated_bytes"]["peak"],
            }
        )

    horizon_records = []
    for row in horizons:
        record = {
            "vertices": row["vertices"],
            "horizon": row["horizon"],
        }
        record.update(horizon_scalars(row))
        horizon_records.append(record)

    predictive_records = [
        record
        for row in horizons
        for record in predictive_sample_rows(row)
    ]

    return {
        "schema": ANALYSIS_SCHEMA,
        "inputs": [bundle["directory"] for bundle in bundles],
        "uncertainty": (
            "Each entry is an independent-graph sample mean with ordinary "
            "standard error. Route positions are reduced within a graph before "
            "uncertainty is computed."
        ),
        "runs": [bundle["run"] for bundle in bundles],
        "route_support": route_support,
        "analytic_limits": {
            "p2_within_covariance_trace": WITHIN_TRACE_LIMIT,
            "p2_between_covariance_trace": BETWEEN_TRACE_LIMIT,
            "p3_within_centered_third_norm": CONDITIONAL_THIRD_NORM_LIMIT,
        },
        "by_vertices": aggregate_records(graph_records, ("vertices",)),
        "by_vertex_and_horizon": aggregate_records(
            horizon_records,
            ("vertices", "horizon"),
        ),
        "position_curves": position_curves(horizons),
        "predictive_closure": aggregate_records(
            predictive_records,
            ("vertices", "horizon", "state", "classes", "target_bins"),
        ),
        "stabilization_exponents": stabilization_exponents(horizons),
    }


# Human-readable report


def format_stat(value: dict[str, Any]) -> str:
    mean = value.get("mean")
    error = value.get("standard_error")
    if mean is None:
        return "null"
    if error is None:
        return f"{mean:.6g}"
    return f"{mean:.6g} ± {error:.2g}"


def render_markdown(summary: dict[str, Any]) -> str:
    lines = [
        "# Gap continuum-scaling summary",
        "",
        summary["uncertainty"],
        "",
        "## Intrinsic transverse scaling",
        "",
        "| N | samples | residual RMS | sqrt(N) residual RMS | mark oracle RMS |",
        "|---:|---:|---:|---:|---:|",
    ]

    for row in summary["by_vertices"]:
        lines.append(
            f"| {row['vertices']} | {row['sample_count']} | "
            f"{format_stat(row['transverse_residual_rms'])} | "
            f"{format_stat(row['sqrt_N_transverse_residual_rms'])} | "
            f"{format_stat(row['intrinsic_mark_oracle_rmse'])} |"
        )

    lines.extend(
        [
            "",
            "## Finite route support",
            "",
            "| N | p | graph samples | samples with routes | fraction |",
            "|---:|---:|---:|---:|---:|",
        ]
    )
    for row in summary["route_support"]:
        lines.append(
            f"| {row['vertices']} | {row['horizon']} | {row['sample_count']} | "
            f"{row['route_sample_count']} | {row['route_sample_fraction']:.6g} |"
        )

    lines.extend(
        [
            "",
            "## Route law and coefficient scaling",
            "",
            "| N | p | samples | latent mean max error | intrinsic mean max error | "
            "p² within trace | p² between trace | p³ conditional third norm | "
            "2p midpoint intrinsic variance |",
            "|---:|---:|---:|---:|---:|---:|---:|---:|---:|",
        ]
    )
    for row in summary["by_vertex_and_horizon"]:
        lines.append(
            f"| {row['vertices']} | {row['horizon']} | {row['sample_count']} | "
            f"{format_stat(row['latent_mean_max_error'])} | "
            f"{format_stat(row['intrinsic_mean_max_error'])} | "
            f"{format_stat(row['p2_within_covariance_trace'])} | "
            f"{format_stat(row['p2_between_covariance_trace'])} | "
            f"{format_stat(row['p3_within_centered_third_norm'])} | "
            f"{format_stat(row['midpoint_two_p_intrinsic_variance'])} |"
        )

    lines.extend(
        [
            "",
            "## Empirical powers in p",
            "",
            "The reported power a is fitted from observable proportional to p^(-a) "
            "within each matched graph sample.",
            "",
            "| N | observable | decay power |",
            "|---:|:---|---:|",
        ]
    )
    for row in summary["stabilization_exponents"]:
        lines.append(
            f"| {row['vertices']} | {row['observable']} | "
            f"{format_stat(row['decay_power'])} |"
        )

    lines.extend(
        [
            "",
            "## Held-out predictive closure",
            "",
            "| N | p | state | classes | target bins | held-out mark RMS | "
            "held-out transverse RMS | held-out TV | held-out W1 | held-out R² | coverage |",
            "|---:|---:|:---|---:|---:|---:|---:|---:|---:|---:|---:|",
        ]
    )
    for row in summary["predictive_closure"]:
        lines.append(
            f"| {row['vertices']} | {row['horizon']} | {row['state']} | "
            f"{row['classes']} | {row['target_bins']} | "
            f"{format_stat(row['held_out_mark_rmse'])} | "
            f"{format_stat(row['held_out_transverse_rmse'])} | "
            f"{format_stat(row['held_out_total_variation'])} | "
            f"{format_stat(row['held_out_wasserstein_1'])} | "
            f"{format_stat(row['held_out_moment_r2'])} | "
            f"{format_stat(row['held_out_coverage'])} |"
        )

    return "\n".join(lines) + "\n"


def clean_json(value: Any) -> Any:
    if isinstance(value, float) and not math.isfinite(value):
        return None
    if isinstance(value, list):
        return [clean_json(item) for item in value]
    if isinstance(value, dict):
        return {key: clean_json(item) for key, item in value.items()}
    return value


def write_output(path: Path, text: str) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    temporary = path.with_name(f".{path.name}.tmp")
    temporary.write_text(text, encoding="utf-8", newline="\n")
    temporary.replace(path)


def parse_args(arguments: Sequence[str]) -> argparse.Namespace:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("inputs", nargs="+", type=Path, help="benchmark directories")
    parser.add_argument("--json", type=Path, help="write aggregate JSON")
    parser.add_argument("--markdown", type=Path, help="write Markdown summary")
    return parser.parse_args(arguments)


def main(arguments: Sequence[str] | None = None) -> int:
    options = parse_args(sys.argv[1:] if arguments is None else arguments)

    try:
        bundles = [load_directory(path) for path in options.inputs]
        summary = clean_json(build_summary(bundles))
    except (InputError, KeyError, TypeError, ValueError) as error:
        print(f"analyze_gap_scaling.py: {error}", file=sys.stderr)
        return 1

    json_text = json.dumps(summary, indent=2, sort_keys=True) + "\n"
    markdown_text = render_markdown(summary)

    if options.json:
        write_output(options.json, json_text)
    if options.markdown:
        write_output(options.markdown, markdown_text)
    if not options.json and not options.markdown:
        print(markdown_text, end="")

    return 0


if __name__ == "__main__":
    raise SystemExit(main())
