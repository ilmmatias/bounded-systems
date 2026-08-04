#!/usr/bin/env python3
"""Exact checks for findings-79 balanced-completion edge spectrum."""

from __future__ import annotations

from fractions import Fraction
from typing import List

Matrix = List[List[Fraction]]


def mean(values: list[Fraction]) -> Fraction:
    return sum(values, Fraction(0)) / len(values)


def edge_mean(payload: Matrix) -> Fraction:
    return mean([x for row in payload for x in row])


def k22_density(payload: Matrix) -> Fraction:
    rows = len(payload)
    cols = len(payload[0])
    total = Fraction(0)
    for i1 in range(rows):
        for i2 in range(rows):
            for j1 in range(cols):
                for j2 in range(cols):
                    total += (
                        payload[i1][j1]
                        * payload[i1][j2]
                        * payload[i2][j1]
                        * payload[i2][j2]
                    )
    return total / (rows * rows * cols * cols)


def coefficients(e: Fraction) -> tuple[Fraction, Fraction, Fraction]:
    theta = (Fraction(2) - e) / 8
    c1 = e * e / 16
    c2 = 2 * theta * (1 - theta) - e * e / 16
    return theta, c1, c2


def direct_overlap_coefficients(e: Fraction) -> tuple[Fraction, Fraction, Fraction]:
    theta = (Fraction(2) - e) / 8
    q_low = (Fraction(1) - e) / 4
    q_high = Fraction(1, 4)
    sigma1 = (
        Fraction(1, 2) * (q_low - theta) ** 2
        + Fraction(1, 2) * (q_high - theta) ** 2
    )
    c1 = 4 * sigma1
    sigma2 = theta * (1 - theta) - 2 * sigma1
    c2 = 2 * sigma2
    return theta, c1, c2


def main() -> None:
    constant: Matrix = [
        [Fraction(1, 2), Fraction(1, 2)],
        [Fraction(1, 2), Fraction(1, 2)],
    ]
    checker: Matrix = [
        [Fraction(1), Fraction(0)],
        [Fraction(0), Fraction(1)],
    ]

    assert edge_mean(constant) == edge_mean(checker) == Fraction(1, 2)
    assert k22_density(constant) != k22_density(checker)

    checks = 0
    for e in [Fraction(1, 5), Fraction(1, 2), Fraction(3, 4), Fraction(9, 10)]:
        assert coefficients(e) == direct_overlap_coefficients(e)
        theta, c1, c2 = coefficients(e)
        # At n=2, the U-statistic is one Bernoulli pair.
        assert c1 / 2 + c2 / 2 == theta * (1 - theta)
        checks += 1

    theta, c1, c2 = coefficients(Fraction(1, 2))
    assert theta == Fraction(3, 16)
    assert c1 == Fraction(1, 64)
    assert c2 == Fraction(37, 128)

    print(f"balanced edge-spectrum exact coefficient checks: {checks}")
    print("constant payload K2,2 density:", k22_density(constant))
    print("checker payload K2,2 density:", k22_density(checker))
    print("all universal-edge and higher-pattern separation checks passed")


if __name__ == "__main__":
    raise SystemExit(main())
