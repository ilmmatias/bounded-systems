#!/usr/bin/env python3
"""Aggregate matched finite-DAG route-closure runs."""

from __future__ import annotations

import argparse
import json
import math
import statistics
from collections import defaultdict
from pathlib import Path
from typing import Any, Iterable, Sequence

RUN_SCHEMA = "bounded-systems.gap-finite-closure-run.v1"
GRAPH_SCHEMA = "bounded-systems.gap-finite-closure-graph.v1"
METRIC_SCHEMA = "bounded-systems.gap-finite-closure-metric.v1"
ANALYSIS_SCHEMA = "bounded-systems.gap-finite-closure-analysis.v1"

METRIC_FIELDS = (
    "log_score",
    "wasserstein",
    "pit_mean",
    "pit_variance",
    "pit_kolmogorov",
    "mean_residual",
    "second_residual",
    "pit_x_correlation",
    "pit_age_correlation",
    "pit_history_correlation",
    "max_conditional_mean_error",
    "max_conditional_variance_error",
)

COMPARISONS = {
    "finite_beta_deviation": ("latent", "continuum_oracle"),
    "normalized_clock_gain": ("latent_age", "latent"),
    "latent_history_gain": ("latent_history", "latent_age"),
    "mark_reconstruction_loss": ("latent", "intrinsic_mark"),
    "intrinsic_clock_gain": ("intrinsic_age", "intrinsic_mark"),
    "intrinsic_history_gain": ("intrinsic_history", "intrinsic_age"),
    "transverse_state_gain": ("full_state", "intrinsic_mark"),
    "full_clock_gain": ("full_age", "full_state"),
    "full_history_gain": ("full_history", "full_age"),
}


def reject_constant(value: str) -> None:
    raise ValueError(f"nonstandard JSON constant: {value}")


def read_json(path: Path) -> dict[str, Any]:
    with path.open(encoding="utf-8") as stream:
        value = json.load(stream, parse_constant=reject_constant)
    if not isinstance(value, dict):
        raise ValueError(f"{path} does not contain a JSON object")
    return value


def read_jsonl(path: Path) -> list[dict[str, Any]]:
    records = []
    with path.open(encoding="utf-8") as stream:
        for line_number, line in enumerate(stream, 1):
            if not line.strip():
                continue
            value = json.loads(line, parse_constant=reject_constant)
            if not isinstance(value, dict):
                raise ValueError(f"{path}:{line_number} is not a JSON object")
            records.append(value)
    return records


def check_schema(records: Iterable[dict[str, Any]], schema: str, path: Path) -> None:
    for index, record in enumerate(records, 1):
        if record.get("schema") != schema:
            raise ValueError(f"{path}:{index} has an unexpected schema")


def summarize(values: Sequence[float]) -> dict[str, float | int]:
    if not values:
        raise ValueError("cannot summarize an empty sample")
    if not all(math.isfinite(value) for value in values):
        raise ValueError("cannot summarize nonfinite values")
    standard_error = 0.0
    if len(values) > 1:
        standard_error = statistics.stdev(values) / math.sqrt(len(values))
    return {
        "mean": statistics.fmean(values),
        "standard_error": standard_error,
        "count": len(values),
    }


def atomic_write(path: Path, text: str) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    temporary = path.with_name(f".{path.name}.tmp")
    temporary.write_text(text, encoding="utf-8", newline="\n")
    temporary.replace(path)


def load_runs(directories: Sequence[Path]) -> tuple[
    list[dict[str, Any]], list[dict[str, Any]], list[dict[str, Any]]
]:
    runs = []
    graphs = []
    metrics = []
    seen_vertices: set[int] = set()
    for directory in directories:
        run_path = directory / "run.json"
        graph_path = directory / "graphs.jsonl"
        metric_path = directory / "metrics.jsonl"
        run = read_json(run_path)
        graph_records = read_jsonl(graph_path)
        metric_records = read_jsonl(metric_path)
        if run.get("schema") != RUN_SCHEMA:
            raise ValueError(f"{run_path} has an unexpected schema")
        check_schema(graph_records, GRAPH_SCHEMA, graph_path)
        check_schema(metric_records, METRIC_SCHEMA, metric_path)

        vertices = int(run["configuration"]["vertices"])
        if vertices in seen_vertices:
            raise ValueError(f"duplicate vertex count: {vertices}")
        seen_vertices.add(vertices)
        if any(int(record["vertices"]) != vertices for record in graph_records):
            raise ValueError(f"{graph_path} has an inconsistent vertex count")
        if any(int(record["vertices"]) != vertices for record in metric_records):
            raise ValueError(f"{metric_path} has an inconsistent vertex count")
        if len(graph_records) != int(run["configuration"]["samples"]):
            raise ValueError(f"{graph_path} has an unexpected record count")

        runs.append(run)
        graphs.extend(graph_records)
        metrics.extend(metric_records)
    return runs, graphs, metrics


def aggregate_metrics(metrics: Sequence[dict[str, Any]]) -> list[dict[str, Any]]:
    groups: dict[tuple[Any, ...], list[dict[str, Any]]] = defaultdict(list)
    for record in metrics:
        key = (
            int(record["vertices"]),
            int(record["horizon"]),
            int(record["resolution_index"]),
            str(record["model"]),
            str(record["data"]),
        )
        groups[key].append(record)

    result = []
    for key, records in sorted(groups.items()):
        vertices, horizon, resolution, model, data = key
        entry = {
            "vertices": vertices,
            "horizon": horizon,
            "resolution_index": resolution,
            "model": model,
            "data": data,
            "graphs": len(records),
            "base_bins": int(records[0]["base_bins"]),
            "aux_leaves": int(records[0]["aux_leaves"]),
            "target_bins": int(records[0]["target_bins"]),
            "record_count": sum(int(record["record_count"]) for record in records),
            "realized_classes": summarize(
                [float(record["realized_classes"]) for record in records]
            ),
            "minimum_training_class": min(
                int(record["minimum_training_class"]) for record in records
            ),
        }
        for field in METRIC_FIELDS:
            entry[field] = summarize([float(record[field]) for record in records])
        result.append(entry)
    return result


def paired_comparisons(metrics: Sequence[dict[str, Any]]) -> list[dict[str, Any]]:
    indexed = {
        (
            int(record["vertices"]),
            int(record["graph_index"]),
            int(record["horizon"]),
            int(record["resolution_index"]),
            str(record["model"]),
            str(record["data"]),
        ): record
        for record in metrics
    }
    settings = sorted(
        {
            (
                int(record["vertices"]),
                int(record["horizon"]),
                int(record["resolution_index"]),
                int(record["base_bins"]),
                int(record["aux_leaves"]),
                int(record["target_bins"]),
            )
            for record in metrics
        }
    )
    result = []
    for vertices, horizon, resolution, base_bins, aux_leaves, target_bins in settings:
        graph_indices = sorted(
            {
                int(record["graph_index"])
                for record in metrics
                if int(record["vertices"]) == vertices
                and int(record["horizon"]) == horizon
                and int(record["resolution_index"]) == resolution
            }
        )
        for name, (augmented, baseline) in COMPARISONS.items():
            finite_log = []
            control_log = []
            corrected_log = []
            finite_wasserstein = []
            control_wasserstein = []
            corrected_wasserstein = []
            for graph in graph_indices:
                keys = {
                    (model, data): indexed.get(
                        (vertices, graph, horizon, resolution, model, data)
                    )
                    for model in (augmented, baseline)
                    for data in ("finite_dag", "beta_control")
                }
                if any(record is None for record in keys.values()):
                    continue
                finite_gain = (
                    float(keys[(augmented, "finite_dag")]["log_score"])
                    - float(keys[(baseline, "finite_dag")]["log_score"])
                )
                control_gain = (
                    float(keys[(augmented, "beta_control")]["log_score"])
                    - float(keys[(baseline, "beta_control")]["log_score"])
                )
                finite_reduction = (
                    float(keys[(baseline, "finite_dag")]["wasserstein"])
                    - float(keys[(augmented, "finite_dag")]["wasserstein"])
                )
                control_reduction = (
                    float(keys[(baseline, "beta_control")]["wasserstein"])
                    - float(keys[(augmented, "beta_control")]["wasserstein"])
                )
                finite_log.append(finite_gain)
                control_log.append(control_gain)
                corrected_log.append(finite_gain - control_gain)
                finite_wasserstein.append(finite_reduction)
                control_wasserstein.append(control_reduction)
                corrected_wasserstein.append(finite_reduction - control_reduction)
            if not corrected_log:
                continue
            result.append(
                {
                    "vertices": vertices,
                    "horizon": horizon,
                    "resolution_index": resolution,
                    "base_bins": base_bins,
                    "aux_leaves": aux_leaves,
                    "target_bins": target_bins,
                    "comparison": name,
                    "augmented": augmented,
                    "baseline": baseline,
                    "graphs": len(corrected_log),
                    "log_gain": {
                        "finite_dag": summarize(finite_log),
                        "beta_control": summarize(control_log),
                        "control_corrected": summarize(corrected_log),
                    },
                    "wasserstein_reduction": {
                        "finite_dag": summarize(finite_wasserstein),
                        "beta_control": summarize(control_wasserstein),
                        "control_corrected": summarize(corrected_wasserstein),
                    },
                }
            )
    return result


def paired_oracle_excess(metrics: Sequence[dict[str, Any]]) -> list[dict[str, Any]]:
    indexed = {
        (
            int(record["vertices"]),
            int(record["graph_index"]),
            int(record["horizon"]),
            str(record["data"]),
        ): record
        for record in metrics
        if record["model"] == "continuum_oracle"
        and int(record["resolution_index"]) == 0
    }
    settings = sorted({(key[0], key[2]) for key in indexed})
    result = []
    for vertices, horizon in settings:
        graph_indices = sorted(
            {
                key[1]
                for key in indexed
                if key[0] == vertices
                and key[2] == horizon
                and key[3] == "finite_dag"
                and (vertices, key[1], horizon, "beta_control") in indexed
            }
        )
        result.append(
            {
                "vertices": vertices,
                "horizon": horizon,
                "graphs": len(graph_indices),
                "finite_minus_beta_control": {
                    field: summarize(
                        [
                            float(
                                indexed[(vertices, graph, horizon, "finite_dag")][
                                    field
                                ]
                            )
                            - float(
                                indexed[
                                    (vertices, graph, horizon, "beta_control")
                                ][field]
                            )
                            for graph in graph_indices
                        ]
                    )
                    for field in ("wasserstein", "pit_kolmogorov")
                },
            }
        )
    return result


def aggregate_graphs(graphs: Sequence[dict[str, Any]]) -> list[dict[str, Any]]:
    groups: dict[int, list[dict[str, Any]]] = defaultdict(list)
    for graph in graphs:
        groups[int(graph["vertices"])].append(graph)
    result = []
    for vertices, records in sorted(groups.items()):
        horizons: dict[int, list[dict[str, Any]]] = defaultdict(list)
        for record in records:
            for horizon in record["horizons"]:
                horizons[int(horizon["horizon"])].append(horizon)
        result.append(
            {
                "vertices": vertices,
                "graphs": len(records),
                "edge_count": summarize([float(record["edges"]) for record in records]),
                "node_mark_rmse": summarize(
                    [float(record["node_mark_rmse"]) for record in records]
                ),
                "node_mark_max_error": summarize(
                    [float(record["node_mark_max_error"]) for record in records]
                ),
                "horizons": [
                    {
                        "horizon": horizon,
                        "supported_graphs": sum(
                            bool(record["has_routes"]) for record in values
                        ),
                        "route_mark_rmse": summarize(
                            [
                                float(record["route_mark_rmse"])
                                for record in values
                                if record["has_routes"]
                            ]
                        )
                        if any(record["has_routes"] for record in values)
                        else None,
                        "log_route_count": summarize(
                            [
                                float(record["log_route_count"])
                                for record in values
                                if record["has_routes"]
                            ]
                        )
                        if any(record["has_routes"] for record in values)
                        else None,
                    }
                    for horizon, values in sorted(horizons.items())
                ],
            }
        )
    return result


def number(summary: dict[str, Any], digits: int = 4) -> str:
    mean = float(summary["mean"])
    error = float(summary["standard_error"])
    return f"{mean:.{digits}g} ± {error:.2g}"


def render_markdown(analysis: dict[str, Any]) -> str:
    lines = [
        "# Finite-DAG route-closure analysis",
        "",
        "## Runs",
        "",
        "| $N$ | graphs | horizons | paths per horizon | wall time (s) | node $\\widehat x$ RMSE |",
        "|---:|---:|:---|---:|---:|---:|",
    ]
    graph_by_vertices = {
        entry["vertices"]: entry for entry in analysis["graph_diagnostics"]
    }
    for run in analysis["runs"]:
        configuration = run["configuration"]
        vertices = int(configuration["vertices"])
        lines.append(
            f"| {vertices} | {configuration['samples']} | "
            f"{','.join(str(value) for value in configuration['horizons'])} | "
            f"{configuration['paths_per_horizon']} | "
            f"{run['runtime']['wall_seconds']:.4g} | "
            f"{number(graph_by_vertices[vertices]['node_mark_rmse'])} |"
        )

    lines.extend(
        [
            "",
            "## Continuum-oracle audit",
            "",
            "The continuum oracle is independent of the fitted partition,",
            "so the table uses the first resolution.",
            "",
            "| $N$ | $p$ | data | log score | $W_1$ | PIT mean | PIT variance | PIT KS | PIT-$x$ corr. |",
            "|---:|---:|:---|---:|---:|---:|---:|---:|---:|",
        ]
    )
    for entry in analysis["metric_aggregates"]:
        if entry["model"] != "continuum_oracle" or entry["resolution_index"] != 0:
            continue
        lines.append(
            f"| {entry['vertices']} | {entry['horizon']} | {entry['data']} | "
            f"{number(entry['log_score'])} | {number(entry['wasserstein'])} | "
            f"{number(entry['pit_mean'])} | {number(entry['pit_variance'])} | "
            f"{number(entry['pit_kolmogorov'])} | "
            f"{number(entry['pit_x_correlation'])} |"
        )

    lines.extend(
        [
            "",
            "## Oracle audit above the sampling control",
            "",
            "| $N$ | $p$ | finite minus control $W_1$ | finite minus control PIT KS |",
            "|---:|---:|---:|---:|",
        ]
    )
    for entry in analysis["oracle_sampling_excess"]:
        values = entry["finite_minus_beta_control"]
        lines.append(
            f"| {entry['vertices']} | {entry['horizon']} | "
            f"{number(values['wasserstein'])} | "
            f"{number(values['pit_kolmogorov'])} |"
        )

    maximum_resolution: dict[tuple[int, int], int] = {}
    for entry in analysis["comparisons"]:
        key = (entry["vertices"], entry["horizon"])
        maximum_resolution[key] = max(
            maximum_resolution.get(key, -1), entry["resolution_index"]
        )
    lines.extend(
        [
            "",
            "## Paired predictive comparisons",
            "",
            "Positive log gain and positive Wasserstein reduction favor the",
            "augmented state. The displayed values subtract the matched",
            "Beta-control difference.",
            "",
            "| $N$ | $p$ | comparison | bins/leaves/target | corrected log gain | corrected $W_1$ reduction |",
            "|---:|---:|:---|:---|---:|---:|",
        ]
    )
    for entry in analysis["comparisons"]:
        key = (entry["vertices"], entry["horizon"])
        if entry["resolution_index"] != maximum_resolution[key]:
            continue
        lines.append(
            f"| {entry['vertices']} | {entry['horizon']} | "
            f"{entry['comparison']} | {entry['base_bins']}/{entry['aux_leaves']}/{entry['target_bins']} | "
            f"{number(entry['log_gain']['control_corrected'])} | "
            f"{number(entry['wasserstein_reduction']['control_corrected'])} |"
        )

    largest = max(entry["vertices"] for entry in analysis["comparisons"])
    lines.extend(
        [
            "",
            "## Largest-size refinement",
            "",
            "| $p$ | resolution | comparison | corrected log gain | corrected $W_1$ reduction |",
            "|---:|:---|:---|---:|---:|",
        ]
    )
    for entry in analysis["comparisons"]:
        if entry["vertices"] != largest:
            continue
        lines.append(
            f"| {entry['horizon']} | {entry['base_bins']}/{entry['aux_leaves']}/{entry['target_bins']} | "
            f"{entry['comparison']} | "
            f"{number(entry['log_gain']['control_corrected'])} | "
            f"{number(entry['wasserstein_reduction']['control_corrected'])} |"
        )
    lines.append("")
    return "\n".join(lines)


def parse_args(arguments: Sequence[str] | None = None) -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Aggregate finite-DAG route-closure artifacts."
    )
    parser.add_argument("directories", nargs="+", type=Path)
    parser.add_argument("--json", type=Path)
    parser.add_argument("--markdown", type=Path)
    return parser.parse_args(arguments)


def main(arguments: Sequence[str] | None = None) -> int:
    options = parse_args(arguments)
    runs, graphs, metrics = load_runs(options.directories)
    analysis = {
        "schema": ANALYSIS_SCHEMA,
        "runs": sorted(
            runs, key=lambda run: int(run["configuration"]["vertices"])
        ),
        "graph_diagnostics": aggregate_graphs(graphs),
        "metric_aggregates": aggregate_metrics(metrics),
        "comparisons": paired_comparisons(metrics),
        "oracle_sampling_excess": paired_oracle_excess(metrics),
        "comparison_convention": {
            "log_gain": (
                "augmented minus baseline. Positive favors augmented"
            ),
            "wasserstein_reduction": (
                "baseline minus augmented. Positive favors augmented"
            ),
            "control_corrected": (
                "finite-DAG difference minus matched Beta-control difference"
            ),
        },
    }
    json_text = json.dumps(analysis, indent=2, sort_keys=True) + "\n"
    markdown_text = render_markdown(analysis)
    if options.json:
        atomic_write(options.json, json_text)
    if options.markdown:
        atomic_write(options.markdown, markdown_text)
    if not options.json and not options.markdown:
        print(json_text, end="")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
