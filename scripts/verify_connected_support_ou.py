#!/usr/bin/env python3
"""Numerical diagnostics for connected-support logarithmic OU limits.

The connected test pattern is a two-edge path supported on three vertices with
independent Rademacher pair variables.  Its normalized support statistic should
have stationary variance 2 and logarithmic covariance 2 exp(-3 Delta/2).
A disconnected two-loop statistic is included to confirm the contrasting
non-Gaussian limit at the same normalization order.
"""

from __future__ import annotations

import math
import numpy as np


def path_statistic(edge_matrix: np.ndarray, n: int) -> float:
    block = edge_matrix[:n, :n]
    degrees = block.sum(axis=1)
    # Ordered embeddings of the path 1-2-3.
    raw = np.sum(degrees * degrees - (n - 1))
    return (n ** 1.5) * raw / (n * (n - 1) * (n - 2))


def disconnected_loop_statistic(marks: np.ndarray, n: int) -> float:
    total = marks[:n].sum()
    raw = total * total - n
    return n * raw / (n * (n - 1))


def standardized_moments(values: np.ndarray) -> tuple[float, float]:
    centered = values - values.mean()
    variance = np.mean(centered**2)
    skew = np.mean(centered**3) / variance**1.5
    kurtosis = np.mean(centered**4) / variance**2
    return float(skew), float(kurtosis)


def main() -> None:
    rng = np.random.default_rng(20260730)
    reps = 3500
    n = 80
    m = 160

    x_n = np.empty(reps)
    x_m = np.empty(reps)
    disconnected = np.empty(reps)

    for rep in range(reps):
        upper = rng.choice((-1.0, 1.0), size=(m, m))
        upper = np.triu(upper, 1)
        edges = upper + upper.T
        x_n[rep] = path_statistic(edges, n)
        x_m[rep] = path_statistic(edges, m)

        marks = rng.choice((-1.0, 1.0), size=m)
        disconnected[rep] = disconnected_loop_statistic(marks, m)

    var_n = float(np.var(x_n))
    var_m = float(np.var(x_m))
    cov_nm = float(np.mean((x_n - x_n.mean()) * (x_m - x_m.mean())))
    predicted_cov = 2.0 * (n / m) ** 1.5
    skew_path, kurt_path = standardized_moments(x_m)
    skew_disc, kurt_disc = standardized_moments(disconnected)

    assert abs(x_n.mean()) < 0.12
    assert abs(x_m.mean()) < 0.12
    assert abs(var_n - 2.0) < 0.22
    assert abs(var_m - 2.0) < 0.22
    assert abs(cov_nm - predicted_cov) < 0.16
    assert abs(skew_path) < 0.22
    assert abs(kurt_path - 3.0) < 0.45

    # The disconnected statistic converges to Z^2-1, whose skewness is sqrt(8)
    # and whose kurtosis is 15.  Finite-size estimates should be visibly
    # separated from Gaussian values.
    assert skew_disc > 2.0
    assert kurt_disc > 9.0

    print("connected path diagnostics")
    print(f"  variance at n={n}: {var_n:.4f} (target 2)")
    print(f"  variance at n={m}: {var_m:.4f} (target 2)")
    print(f"  nested covariance: {cov_nm:.4f} (target {predicted_cov:.4f})")
    print(f"  skew/kurtosis: {skew_path:.4f}, {kurt_path:.4f} (Gaussian 0, 3)")
    print("disconnected two-loop diagnostics")
    print(f"  skew/kurtosis: {skew_disc:.4f}, {kurt_disc:.4f} (limit sqrt(8), 15)")


if __name__ == "__main__":
    main()
