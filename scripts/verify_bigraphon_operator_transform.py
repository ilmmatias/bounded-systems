#!/usr/bin/env python3
"""Finite-rank diagnostics for findings-78 rectangular cubic transform."""

from __future__ import annotations

import numpy as np


def inverse_scalar(values: np.ndarray) -> np.ndarray:
    """Solve z^3+z=s for nonnegative s by Newton iteration."""
    z = values.copy()
    for _ in range(80):
        update = (z**3 + z - values) / (3 * z**2 + 1)
        z -= update
        if np.max(np.abs(update)) < 1e-14:
            break
    return z


def inverse_transform(operator: np.ndarray) -> np.ndarray:
    left, singular, right_t = np.linalg.svd(operator, full_matrices=False)
    recovered = inverse_scalar(singular)
    return (left * recovered) @ right_t


def transform(operator: np.ndarray) -> np.ndarray:
    return operator @ operator.T @ operator + operator


def threshold_kernel(n: int) -> np.ndarray:
    points = (np.arange(n) + 0.5) / n
    return (points[:, None] + points[None, :] <= 1.0).astype(float)


def kernel_mean(kernel: np.ndarray) -> float:
    return float(np.mean(kernel))


def verify_threshold(n: int) -> tuple[float, int]:
    h_kernel = threshold_kernel(n)
    h_operator = h_kernel / n
    w_operator = inverse_transform(h_operator)
    residual = np.max(np.abs(transform(w_operator) - h_operator))
    assert residual < 2e-12

    w_kernel = n * w_operator
    cubic_kernel = n * (w_operator @ w_operator.T @ w_operator)
    density_residual = abs(
        kernel_mean(h_kernel)
        - (kernel_mean(w_kernel) + kernel_mean(cubic_kernel))
    )
    assert density_residual < 2e-12

    rounded_distinct = len(np.unique(np.round(w_kernel, 10)))
    return residual, rounded_distinct


def verify_random_rectangular(rows: int, cols: int, seed: int) -> float:
    rng = np.random.default_rng(seed)
    operator = rng.normal(size=(rows, cols)) / max(rows, cols)
    image = transform(operator)
    recovered = inverse_transform(image)
    residual = np.max(np.abs(recovered - operator))
    # The image has the same polar part, so the SVD signs recover the operator.
    assert residual < 2e-11
    return residual


def main() -> None:
    threshold_results = [verify_threshold(n) for n in (8, 12, 20, 32)]
    random_results = [
        verify_random_rectangular(5, 3, 1101),
        verify_random_rectangular(4, 7, 1102),
        verify_random_rectangular(8, 6, 1103),
    ]

    distinct = [count for _, count in threshold_results]
    assert distinct == sorted(distinct)
    assert distinct[-1] > distinct[0]

    print(
        "threshold transform max residuals:",
        [f"{r:.3e}" for r, _ in threshold_results],
    )
    print("threshold payload distinct-value counts:", distinct)
    print(
        "random rectangular recovery residuals:",
        [f"{r:.3e}" for r in random_results],
    )
    print("all rectangular cubic-transform diagnostics passed")


if __name__ == "__main__":
    raise SystemExit(main())
