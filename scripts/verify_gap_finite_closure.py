#!/usr/bin/env python3
"""Verify finite-DAG route sampling, cross-fitting, and output determinism."""

from __future__ import annotations

import copy
import json
import math
import subprocess
import sys
import tempfile
from pathlib import Path
from typing import Any

RUN_SCHEMA = "bounded-systems.gap-finite-closure-run.v1"
GRAPH_SCHEMA = "bounded-systems.gap-finite-closure-graph.v1"
METRIC_SCHEMA = "bounded-systems.gap-finite-closure-metric.v1"
ANALYSIS_SCHEMA = "bounded-systems.gap-finite-closure-analysis.v1"


def reject_constant(value: str) -> None:
    raise ValueError(f"nonstandard JSON constant: {value}")


def load_json(path: Path) -> dict[str, Any]:
    with path.open(encoding="utf-8") as stream:
        value = json.load(stream, parse_constant=reject_constant)
    assert isinstance(value, dict)
    return value


def load_jsonl(path: Path) -> list[dict[str, Any]]:
    records = []
    with path.open(encoding="utf-8") as stream:
        for line in stream:
            if line.strip():
                value = json.loads(line, parse_constant=reject_constant)
                assert isinstance(value, dict)
                records.append(value)
    return records


def scientific_run(run: dict[str, Any]) -> dict[str, Any]:
    result = copy.deepcopy(run)
    result.pop("runtime")
    configuration = result["configuration"]
    configuration.pop("requested_threads")
    configuration.pop("effective_threads")
    configuration.pop("output_directory")
    return result


def scientific_graphs(records: list[dict[str, Any]]) -> list[dict[str, Any]]:
    result = copy.deepcopy(records)
    for record in result:
        record.pop("seconds")
    return result


def run_study(program: Path, output: Path, threads: int) -> None:
    subprocess.run(
        [
            str(program),
            "--vertices",
            "96",
            "--horizons",
            "4,8",
            "--samples",
            "4",
            "--paths",
            "300",
            "--seed",
            "20260817",
            "--threads",
            str(threads),
            "--output",
            str(output),
            "--base-bins",
            "4,8",
            "--aux-leaves",
            "2,2",
            "--target-bins",
            "16,32",
            "--reference-bins",
            "64",
            "--pseudocount",
            "0.5",
        ],
        check=True,
        capture_output=True,
        text=True,
    )


def main() -> int:
    root = Path(__file__).resolve().parent.parent
    program = root / "bin" / "gap-finite-closure"
    analyzer = root / "scripts" / "analyze_gap_finite_closure.py"
    self_test = subprocess.run(
        [str(program), "--self-test"],
        check=True,
        capture_output=True,
        text=True,
    )
    assert "self-tests passed" in self_test.stderr
    checks = 1

    with tempfile.TemporaryDirectory(prefix="gap-finite-closure-") as temporary:
        directory = Path(temporary)
        serial = directory / "serial"
        threaded = directory / "threaded"
        run_study(program, serial, 1)
        run_study(program, threaded, 4)

        serial_run = load_json(serial / "run.json")
        threaded_run = load_json(threaded / "run.json")
        serial_graphs = load_jsonl(serial / "graphs.jsonl")
        threaded_graphs = load_jsonl(threaded / "graphs.jsonl")
        serial_metrics = load_jsonl(serial / "metrics.jsonl")
        threaded_metrics = load_jsonl(threaded / "metrics.jsonl")
        assert serial_run["schema"] == RUN_SCHEMA
        assert all(record["schema"] == GRAPH_SCHEMA for record in serial_graphs)
        assert all(record["schema"] == METRIC_SCHEMA for record in serial_metrics)
        checks += 3

        assert scientific_run(serial_run) == scientific_run(threaded_run)
        assert scientific_graphs(serial_graphs) == scientific_graphs(threaded_graphs)
        assert serial_metrics == threaded_metrics
        checks += 3

        assert len(serial_graphs) == 4
        assert len(serial_metrics) == 4 * 2 * 2 * 20
        checks += 2
        for graph in serial_graphs:
            assert graph["node_mark_rmse"] > 0.0
            assert graph["node_mark_max_error"] >= graph["node_mark_rmse"]
            assert all(horizon["has_routes"] for horizon in graph["horizons"])
            assert all(horizon["route_mark_rmse"] > 0.0 for horizon in graph["horizons"])
            checks += 4

        for metric in serial_metrics:
            expected = 300 * (int(metric["horizon"]) - 1)
            assert int(metric["record_count"]) == expected
            assert math.isfinite(float(metric["log_score"]))
            assert math.isfinite(float(metric["wasserstein"]))
            assert 0.0 <= float(metric["pit_mean"]) <= 1.0
            assert float(metric["wasserstein"]) >= 0.0
            if metric["model"] != "continuum_oracle":
                assert int(metric["minimum_training_class"]) > 0
                assert int(metric["realized_classes"]) > 0
            checks += 7

        summary_path = directory / "summary.json"
        markdown_path = directory / "summary.md"
        subprocess.run(
            [
                sys.executable,
                str(analyzer),
                str(serial),
                "--json",
                str(summary_path),
                "--markdown",
                str(markdown_path),
            ],
            check=True,
        )
        analysis = load_json(summary_path)
        assert analysis["schema"] == ANALYSIS_SCHEMA
        assert len(analysis["comparisons"]) == 2 * 2 * 9
        assert markdown_path.read_text(encoding="utf-8").startswith(
            "# Finite-DAG route-closure analysis\n"
        )
        checks += 3

        oracle_excess = analysis["oracle_sampling_excess"]
        assert len(oracle_excess) == 2
        checks += 1
        for entry in oracle_excess:
            assert int(entry["graphs"]) == 4
            for diagnostic in ("wasserstein", "pit_kolmogorov"):
                value = entry["finite_minus_beta_control"][diagnostic]
                assert int(value["count"]) == 4
                assert math.isfinite(float(value["mean"]))
                assert math.isfinite(float(value["standard_error"]))
                checks += 4

        controls = [
            entry
            for entry in analysis["metric_aggregates"]
            if entry["model"] == "continuum_oracle"
            and entry["data"] == "beta_control"
            and entry["resolution_index"] == 0
        ]
        assert len(controls) == 2
        for control in controls:
            assert abs(float(control["pit_mean"]["mean"]) - 0.5) < 0.025
            assert abs(float(control["pit_variance"]["mean"]) - 1.0 / 12.0) < 0.01
            assert float(control["pit_kolmogorov"]["mean"]) < 0.05
            assert float(control["wasserstein"]["mean"]) < 0.06
            checks += 4

        for comparison in analysis["comparisons"]:
            for diagnostic in ("log_gain", "wasserstein_reduction"):
                value = comparison[diagnostic]["control_corrected"]
                assert int(value["count"]) == 4
                assert math.isfinite(float(value["mean"]))
                assert math.isfinite(float(value["standard_error"]))
                checks += 3

    print(f"verified {checks} exact and sampled finite-closure checks")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
