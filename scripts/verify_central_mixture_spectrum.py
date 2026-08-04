#!/usr/bin/env python3
"""Exact degree-zero/degree-two covariance checks for findings-57.md."""

from __future__ import annotations

from fractions import Fraction


def falling_two(n: int) -> int:
    if n < 2:
        raise ValueError("n must be at least 2")
    return n * (n - 1)


def mixture_covariance(
    alpha: Fraction,
    a: Fraction,
    b: Fraction,
    m: int,
) -> Fraction:
    mean_r = alpha * a + (1 - alpha) * b
    mean_r2 = alpha * a * a + (1 - alpha) * b * b
    frozen = mean_r2 - mean_r * mean_r
    within = 2 * (
        alpha * a * (1 - a)
        + (1 - alpha) * b * (1 - b)
    ) / falling_two(m)
    return frozen + within


def direct_pair_calculation(
    alpha: Fraction,
    a: Fraction,
    b: Fraction,
    n: int,
    m: int,
) -> Fraction:
    if not (2 <= n <= m):
        raise ValueError("require 2 <= n <= m")

    # Conditional means are a and b. Conditional nested covariance of two
    # edge-density averages is p(1-p)/C(m,2).
    frozen = alpha * (1 - alpha) * (a - b) ** 2
    conditional = alpha * a * (1 - a) / Fraction(m * (m - 1), 2)
    conditional += (1 - alpha) * b * (1 - b) / Fraction(m * (m - 1), 2)
    return frozen + conditional


def main() -> None:
    alpha = Fraction(2, 5)
    a = Fraction(1, 4)
    b = Fraction(3, 4)

    frozen = alpha * (1 - alpha) * (a - b) ** 2
    expected_frozen = Fraction(3, 50)
    if frozen != expected_frozen:
        raise AssertionError(f"frozen coefficient: {frozen} != {expected_frozen}")

    c2 = 2 * (
        alpha * a * (1 - a)
        + (1 - alpha) * b * (1 - b)
    )
    expected_c2 = Fraction(3, 8)
    if c2 != expected_c2:
        raise AssertionError(f"order-two coefficient: {c2} != {expected_c2}")

    checks = 0
    for n in range(2, 15):
        for m in range(n, 20):
            lhs = mixture_covariance(alpha, a, b, m)
            rhs = direct_pair_calculation(alpha, a, b, n, m)
            if lhs != rhs:
                raise AssertionError(
                    f"covariance mismatch at n={n}, m={m}: {lhs} != {rhs}"
                )
            checks += 1

    print(f"central mixture spectrum checks passed: {checks}")
    print(f"  C0: {frozen}")
    print(f"  C2: {c2}")


if __name__ == "__main__":
    raise SystemExit(main())
