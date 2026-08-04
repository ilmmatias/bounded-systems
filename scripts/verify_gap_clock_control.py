#!/usr/bin/env python3
"""Exact and sampled checks for findings-104.md."""

from __future__ import annotations

import copy
import json
import math
import random
import subprocess
import tempfile
from fractions import Fraction
from pathlib import Path
from typing import Any

ROOT = Path(__file__).resolve().parents[1]
PROGRAM = ROOT / "bin" / "gap-clock-control"
SCHEMA = "bounded-systems.gap-clock-control.v1"
SEED = 0x104D1A1C


class Checks:
    def __init__(self) -> None:
        self.count = 0

    def require(self, condition: bool, message: str) -> None:
        if not condition:
            raise AssertionError(message)
        self.count += 1

    def close(self, actual: float, expected: float, error: float, message: str) -> None:
        self.require(abs(actual - expected) <= error, f"{message}: {actual}")


def route_parameters(p: int) -> tuple[int, ...]:
    return (1, *(2 for _ in range(p)), 1)


def beta_mean(alpha: int, beta: int) -> Fraction:
    return Fraction(alpha, alpha + beta)


def beta_variance(alpha: int, beta: int) -> Fraction:
    total = alpha + beta
    return Fraction(alpha * beta, total * total * (total + 1))


def beta_cdf(z: float, k: int) -> float:
    b = 2 * k - 1
    return 1.0 - (1.0 - z) ** b * (1.0 + b * z)


def kolmogorov_uniform(values: list[float]) -> float:
    values.sort()
    count = len(values)
    return max(
        max(abs(value - i / count), abs(value - (i + 1) / count))
        for i, value in enumerate(values)
    )


def verify_conditional_factorization(checks: Checks) -> None:
    for p in range(1, 65):
        params = route_parameters(p)

        for r in range(p):
            left = sum(params[: r + 1])
            next_gap = params[r + 1]
            remaining = sum(params[r + 2 :])

            checks.require(left == 2 * r + 1, f"p={p}, r={r}: left concentration")
            checks.require(next_gap == 2, f"p={p}, r={r}: next-gap concentration")
            checks.require(
                remaining == 2 * (p - r) - 1,
                f"p={p}, r={r}: remaining concentration",
            )
            checks.require(
                beta_mean(next_gap, remaining) == Fraction(2, 2 * (p - r) + 1),
                f"p={p}, r={r}: conditional mean",
            )

    for k in range(1, 65):
        checks.require(
            beta_variance(2, 2 * k - 1)
            == Fraction(2 * (2 * k - 1), (2 * k + 1) ** 2 * (2 * k + 2)),
            f"k={k}: conditional variance",
        )


def verify_probability_transform(checks: Checks) -> None:
    rng = random.Random(SEED)
    values: list[float] = []

    for _ in range(30_000):
        k = rng.choice((2, 4, 8, 16, 32, 64, 128))
        z = rng.betavariate(2, 2 * k - 1)
        values.append(beta_cdf(z, k))

    mean = sum(values) / len(values)
    variance = sum((value - mean) ** 2 for value in values) / len(values)

    checks.close(mean, 0.5, 0.006, "oracle PIT mean")
    checks.close(variance, 1.0 / 12.0, 0.003, "oracle PIT variance")
    checks.require(
        kolmogorov_uniform(values) < 0.012,
        "oracle PIT is not uniform",
    )


def load(path: Path) -> dict[str, Any]:
    with path.open(encoding="utf-8") as stream:
        return json.load(stream)


def run_control(path: Path, threads: int) -> dict[str, Any]:
    command = [
        str(PROGRAM),
        "--horizons",
        "8,16",
        "--scales",
        "1,2",
        "--paths",
        "400",
        "--seed",
        str(SEED),
        "--threads",
        str(threads),
        "--output",
        str(path),
        "--overwrite",
    ]
    proc = subprocess.run(command, cwd=ROOT, capture_output=True, text=True)

    if proc.returncode != 0:
        raise AssertionError(proc.stderr)

    return load(path)


def scientific_projection(value: dict[str, Any]) -> dict[str, Any]:
    projected = copy.deepcopy(value)
    del projected["runtime"]
    del projected["configuration"]["requested_threads"]
    return projected


def verify_split(config: dict[str, Any], checks: Checks) -> None:
    count = config["paths_per_horizon"]
    training = set(range(0, count, 2))
    held_out = set(range(1, count, 2))

    checks.require(not training & held_out, "training and holdout path indices overlap")
    checks.require(
        training | held_out == set(range(count)),
        "path split does not cover every index",
    )
    checks.require(config["train_rule"] == "even path index", "training rule differs")
    checks.require(config["holdout_rule"] == "odd path index", "holdout rule differs")


def finite_summary(value: dict[str, Any], context: str, checks: Checks) -> None:
    checks.require(value["path_count"] > 0, f"{context}: empty summary")
    checks.require(math.isfinite(value["mean"]), f"{context}: nonfinite mean")
    checks.require(
        math.isfinite(value["standard_error"]) and value["standard_error"] >= 0.0,
        f"{context}: invalid standard error",
    )


def verify_output(output: dict[str, Any], checks: Checks) -> None:
    checks.require(output["schema"] == SCHEMA, "clock-control schema differs")
    config = output["configuration"]
    checks.require(config["base_horizons"] == [8, 16], "base horizons differ")
    checks.require(config["scales"] == [1, 2], "scale factors differ")
    checks.require(config["positions"] == list(range(1, 8)), "positions differ")
    checks.require(config["position_denominator"] == 8, "position denominator differs")
    verify_split(config, checks)

    for group in output["scale_groups"]:
        expected_paths = len(config["base_horizons"]) * config["paths_per_horizon"] // 2
        expected_steps = expected_paths * len(config["positions"])
        checks.require(
            group["training_paths"] == expected_paths,
            "training path count differs",
        )
        checks.require(
            group["held_out_paths"] == expected_paths,
            "holdout path count differs",
        )
        checks.require(
            group["held_out_transitions"] == expected_steps,
            "holdout transition count differs",
        )

        audit = group["conditional_audit"]
        error = 6.0 / math.sqrt(12.0 * expected_steps)
        checks.close(audit["pit_mean"], 0.5, error, "sampled conditional PIT mean")
        checks.close(
            audit["pit_variance"],
            1.0 / 12.0,
            0.006,
            "sampled conditional PIT variance",
        )
        checks.require(audit["pit_kolmogorov"] < 0.04, "sampled PIT CDF differs")

        for target in ("remaining_fraction", "route_time_scaled"):
            scores = group["log_score"][target]

            for state in (
                "oracle",
                "clock_free_local",
                "normalized_clock",
                "exact_augmented",
            ):
                finite_summary(scores[state], f"{target} {state}", checks)

            exact = scores["paired_differences"]["exact_augmented_minus_oracle"]
            checks.require(exact["mean"] == 0.0, f"{target}: exact state misses oracle")
            checks.require(
                exact["standard_error"] == 0.0,
                f"{target}: exact score varies",
            )

            w1 = group["wasserstein"][target]
            checks.require(
                [row["x_bins"] for row in w1] == [64, 128, 256],
                "W1 refinements differ",
            )

            for row in w1:
                finite_summary(
                    row["clock_free_to_oracle"],
                    f"{target} local W1",
                    checks,
                )
                finite_summary(
                    row["normalized_clock_to_oracle"],
                    f"{target} clock W1",
                    checks,
                )
                checks.require(
                    row["exact_augmented_to_oracle"]["mean"] == 0.0,
                    f"{target}: exact W1 is nonzero",
                )

            local = [row["clock_free_to_oracle"]["mean"] for row in w1]
            clock = [row["normalized_clock_to_oracle"]["mean"] for row in w1]
            checks.require(
                max(local) - min(local) < 0.01,
                f"{target}: local W1 is not stable",
            )
            checks.require(
                max(clock) - min(clock) < 0.01,
                f"{target}: clock W1 is not stable",
            )

        history = group["history_positive_control"]
        checks.require(len(history) == 27, "history refinement grid differs")

        for row in history:
            finite_summary(row["held_out_log_gain"], "history log gain", checks)
            finite_summary(row["pit_wasserstein_to_oracle"], "history PIT W1", checks)
            checks.require(
                row["training_transitions"] == expected_steps,
                "history training transition count differs",
            )
            checks.require(
                row["held_out_transitions"] == expected_steps,
                "history holdout transition count differs",
            )


def main() -> None:
    checks = Checks()
    verify_conditional_factorization(checks)
    verify_probability_transform(checks)

    with tempfile.TemporaryDirectory(prefix="gap-clock-control-") as directory:
        root = Path(directory)
        serial = run_control(root / "serial.json", 1)
        parallel = run_control(root / "parallel.json", 4)

    verify_output(serial, checks)
    verify_output(parallel, checks)
    checks.require(
        scientific_projection(serial) == scientific_projection(parallel),
        "serial and threaded scientific outputs differ",
    )

    print(f"verified {checks.count} exact and sampled clock-control checks")


if __name__ == "__main__":
    raise SystemExit(main())
