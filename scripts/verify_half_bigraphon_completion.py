#!/usr/bin/env python3
"""Symbolic and finite-grid checks for findings-76 and findings-77."""

from __future__ import annotations

from fractions import Fraction
from math import factorial

import sympy as sp


def half_moment(a: int, b: int) -> sp.Rational:
    x, y = sp.symbols("x y", nonnegative=True)
    integral = a * b * sp.integrate(
        sp.integrate(x ** (a - 1) * y ** (b - 1), (y, 0, 1 - x)),
        (x, 0, 1),
    )
    return sp.simplify(integral)


def threshold_matrix(n: int) -> list[list[int]]:
    # Midpoint discretization: x_i=(i+1/2)/n.
    return [[1 if i + j + 1 <= n else 0 for j in range(n)] for i in range(n)]


def matrix_rank(matrix: list[list[int]]) -> int:
    return int(sp.Matrix(matrix).rank())


def row_l1_completion(matrix: list[list[int]], i: int, j: int) -> Fraction:
    n = len(matrix)
    # B-block threshold contribution, weighted by 1/4.
    threshold = sum(abs(matrix[i][k] - matrix[j][k]) for k in range(n))
    threshold_term = Fraction(threshold, 4 * n)
    # C-block values x_i and x_j, weighted by 1/4.
    x_i = Fraction(2 * i + 1, 2 * n)
    x_j = Fraction(2 * j + 1, 2 * n)
    compensator_term = abs(x_i - x_j) / 4
    return threshold_term + compensator_term


def main() -> None:
    moment_checks = 0
    for a in range(1, 6):
        for b in range(1, 6):
            expected = sp.Rational(factorial(a) * factorial(b), factorial(a + b))
            assert half_moment(a, b) == expected
            moment_checks += 1

    x, y = sp.symbols("x y", real=True)
    assert sp.integrate(1 - x, (x, 0, 1)) == sp.Rational(1, 2)
    assert sp.integrate(x, (x, 0, 1)) == sp.Rational(1, 2)
    assert sp.integrate(y, (y, 0, 1)) == sp.Rational(1, 2)

    degree_d = (sp.Rational(0), sp.Rational(1, 8))
    degree_a = (sp.Rational(0), sp.Rational(1, 4))
    degree_b = (sp.Rational(1, 4), sp.Rational(0))
    degree_c = (sp.Rational(1, 8), sp.Rational(0))
    assert len({degree_d, degree_a, degree_b, degree_c}) == 4
    assert 3 * sp.Rational(1, 16) * sp.Rational(1, 2) == sp.Rational(3, 32)

    grid_checks = 0
    for n in range(2, 13):
        matrix = threshold_matrix(n)
        # Nested supports.
        for i in range(n - 1):
            assert all(matrix[i][j] >= matrix[i + 1][j] for j in range(n))
        # The anti-triangular threshold matrix is full rank.
        assert matrix_rank(matrix) == n
        # Rooted completion distance is exactly half the coordinate distance.
        for i in range(n):
            for j in range(n):
                x_i = Fraction(2 * i + 1, 2 * n)
                x_j = Fraction(2 * j + 1, 2 * n)
                assert row_l1_completion(matrix, i, j) == abs(x_i - x_j) / 2
                grid_checks += 1

    allowed = {("D", "B"), ("A", "B"), ("A", "C")}
    assert all(v != x_part for _, v in allowed for x_part, _ in allowed)

    print(f"half-bigraphon symbolic moment checks: {moment_checks}")
    print(f"half-completion rooted-profile grid checks: {grid_checks}")
    print("all moment, degree, rank, profile-distance, and acyclicity checks passed")


if __name__ == "__main__":
    main()
