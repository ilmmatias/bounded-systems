#!/usr/bin/env python3
"""Diagnostics for a disconnected loop-plus-edge Wick-product limit.

The support pattern has one loop component and one ordinary-edge component on
three vertices.  With independent Rademacher vertex marks S_i and pair noises
E_ij, the canonical kernel is S_i E_jk on distinct vertices.  Its logarithmic
limit is the product of an independent rate-1/2 OU field and rate-1 OU field,
so the total relaxation rate is 3/2, stationary variance is 2, and the
standardized kurtosis is 9.
"""

from __future__ import annotations

import numpy as np


def loop_edge_statistic(marks: np.ndarray, edges: np.ndarray, n: int) -> float:
    s = marks[:n]
    e = edges[:n, :n]
    mark_sum = s.sum()
    edge_sum_unordered = np.triu(e, 1).sum()
    incident_weight = np.sum(s * e.sum(axis=1))

    # Ordered embeddings of the representative with loop at vertex 1 and
    # ordinary edge 2-3.  The edge endpoints are ordered, hence the factor 2.
    raw = 2.0 * (mark_sum * edge_sum_unordered - incident_weight)
    return (n ** 1.5) * raw / (n * (n - 1) * (n - 2))


def standardized_moments(values: np.ndarray) -> tuple[float, float]:
    centered = values - values.mean()
    variance = np.mean(centered**2)
    skew = np.mean(centered**3) / variance**1.5
    kurtosis = np.mean(centered**4) / variance**2
    return float(skew), float(kurtosis)


def main() -> None:
    rng = np.random.default_rng(20260731)
    reps = 4500
    n = 90
    m = 180

    x_n = np.empty(reps)
    x_m = np.empty(reps)

    for rep in range(reps):
        marks = rng.choice((-1.0, 1.0), size=m)
        upper = rng.choice((-1.0, 1.0), size=(m, m))
        upper = np.triu(upper, 1)
        edges = upper + upper.T
        x_n[rep] = loop_edge_statistic(marks, edges, n)
        x_m[rep] = loop_edge_statistic(marks, edges, m)

    var_n = float(np.var(x_n))
    var_m = float(np.var(x_m))
    cov_nm = float(np.mean((x_n - x_n.mean()) * (x_m - x_m.mean())))
    predicted_cov = 2.0 * (n / m) ** 1.5
    skew, kurtosis = standardized_moments(x_m)

    assert abs(x_n.mean()) < 0.15
    assert abs(x_m.mean()) < 0.15
    assert abs(var_n - 2.0) < 0.25
    assert abs(var_m - 2.0) < 0.25
    assert abs(cov_nm - predicted_cov) < 0.18
    assert abs(skew) < 0.25
    assert abs(kurtosis - 9.0) < 1.5

    print("disconnected loop-plus-edge diagnostics")
    print(f"  variance at n={n}: {var_n:.4f} (target 2)")
    print(f"  variance at n={m}: {var_m:.4f} (target 2)")
    print(f"  nested covariance: {cov_nm:.4f} (target {predicted_cov:.4f})")
    print(f"  skew/kurtosis: {skew:.4f}, {kurtosis:.4f} (product-normal 0, 9)")


if __name__ == "__main__":
    raise SystemExit(main())
