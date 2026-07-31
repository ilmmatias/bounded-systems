#!/usr/bin/env python3
"""Exact checks for findings-80.md."""

from __future__ import annotations

import math

import sympy as sp


def route_profile_sum(ell: int, x: sp.Symbol) -> sp.Expr:
    return sp.factorial(ell) * sum(
        x ** (2 * r)
        * (1 - x) ** (2 * (ell - r))
        / (sp.factorial(2 * r) * sp.factorial(2 * ell - 2 * r))
        for r in range(ell + 1)
    )


def route_profile_closed(ell: int, x: sp.Symbol) -> sp.Expr:
    return (
        sp.factorial(ell)
        / (2 * sp.factorial(2 * ell))
        * (1 + (1 - 2 * x) ** (2 * ell))
    )


def theta(ell: int) -> sp.Rational:
    return sp.factorial(ell + 1) / sp.factorial(2 * ell + 1)


def sigma(ell: int) -> sp.Expr:
    a = sp.factorial(ell) / (2 * sp.factorial(2 * ell))
    return sp.simplify(
        a**2
        * (
            sp.Rational(1, 4 * ell + 1)
            - sp.Rational(1, (2 * ell + 1) ** 2)
        )
    )


def cross(ell: int, m: int) -> sp.Expr:
    a = sp.factorial(ell) / (2 * sp.factorial(2 * ell))
    b = sp.factorial(m) / (2 * sp.factorial(2 * m))
    return sp.simplify(
        (ell + 1)
        * (m + 1)
        * a
        * b
        * (
            sp.Rational(1, 2 * ell + 2 * m + 1)
            - sp.Rational(1, (2 * ell + 1) * (2 * m + 1))
        )
    )


def main() -> None:
    x = sp.symbols("x", real=True)
    checks = 0

    projections: list[sp.Expr] = []
    for ell in range(1, 9):
        q_sum = sp.expand(route_profile_sum(ell, x))
        q_closed = sp.expand(route_profile_closed(ell, x))
        assert sp.simplify(q_sum - q_closed) == 0
        checks += 1

        mean = sp.integrate(q_closed, (x, 0, 1))
        assert sp.simplify(mean - theta(ell)) == 0
        checks += 1

        h = sp.expand(q_closed - theta(ell))
        projections.append(h)
        norm = sp.integrate(h**2, (x, 0, 1))
        assert sp.simplify(norm - sigma(ell)) == 0
        checks += 1

        c_diag = (ell + 1) ** 2 * norm
        assert sp.simplify(c_diag - cross(ell, ell)) == 0
        checks += 1

    for ell in range(1, 7):
        for m in range(1, 7):
            direct = sp.simplify(
                (ell + 1)
                * (m + 1)
                * sp.integrate(projections[ell - 1] * projections[m - 1], (x, 0, 1))
            )
            assert sp.simplify(direct - cross(ell, m)) == 0
            checks += 1

    assert cross(1, 2) == sp.Rational(1, 210)
    checks += 1

    for length in range(1, 8):
        gram = sp.Matrix(
            [[cross(i, j) for j in range(1, length + 1)] for i in range(1, length + 1)]
        )
        assert gram.det() != 0
        assert gram.is_positive_definite
        checks += 2

    print(f"verified {checks} exact distance-route hierarchy checks")


if __name__ == "__main__":
    main()
