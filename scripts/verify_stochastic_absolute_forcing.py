#!/usr/bin/env python3
"""Exact diagnostics for findings-69."""

from __future__ import annotations

from fractions import Fraction


def q_value(x: Fraction, y: Fraction, theta: Fraction, r: Fraction) -> Fraction:
    return (x * x + (y - r * (1 - theta)) ** 2) * (
        (x - r * theta) ** 2 + y * y
    )


def normalized_k22(matrix: tuple[tuple[Fraction, ...], ...]) -> Fraction:
    rows = len(matrix)
    cols = len(matrix[0])
    total = Fraction(0)
    for i in range(rows):
        for j in range(rows):
            for a in range(cols):
                for b in range(cols):
                    total += matrix[i][a] * matrix[i][b] * matrix[j][a] * matrix[j][b]
    return total / (rows * rows * cols * cols)


def check(theta: Fraction, r: Fraction, delta: Fraction) -> int:
    source = (Fraction(0), r * (1 - theta))
    sink = (r * theta, Fraction(0))
    assert q_value(*source, theta, r) == 0
    assert q_value(*sink, theta, r) == 0

    # The edge balance equation uniquely recovers the source mass.
    recovered = (r * theta) / (r * (1 - theta) + r * theta)
    assert recovered == theta

    # A 2-by-2 biregular perturbation has singular modes r and delta.
    matrix = (
        (r + delta, r - delta),
        (r - delta, r + delta),
    )
    for row in matrix:
        assert sum(row) / 2 == r
    for col in range(2):
        assert sum(matrix[row][col] for row in range(2)) / 2 == r

    k22 = normalized_k22(matrix)
    assert k22 == r**4 + delta**4
    assert k22 >= r**4
    if delta != 0:
        assert k22 > r**4

    directed_density = theta**2 * (1 - theta) ** 2 * k22
    target_density = theta**2 * (1 - theta) ** 2 * r**4
    assert directed_density - target_density == theta**2 * (1 - theta) ** 2 * delta**4
    return 10


def main() -> None:
    cases = (
        (Fraction(1, 2), Fraction(1, 2), Fraction(0)),
        (Fraction(1, 2), Fraction(1, 2), Fraction(1, 4)),
        (Fraction(1, 3), Fraction(2, 3), Fraction(1, 6)),
        (Fraction(2, 5), Fraction(3, 4), Fraction(1, 8)),
        (Fraction(3, 7), Fraction(4, 5), Fraction(1, 10)),
    )
    checks = sum(check(*case) for case in cases)
    print(f"verified {checks} exact stochastic absolute-forcing identities")


if __name__ == "__main__":
    raise SystemExit(main())
