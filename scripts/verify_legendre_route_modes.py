#!/usr/bin/env python3
"""Exact checks for findings-81.md."""

from __future__ import annotations

import sympy as sp


def legendre_coefficient(ell: int, j: int) -> sp.Expr:
    return sp.simplify(
        (4 * j + 1)
        * sp.factorial(2 * ell)
        / (
            sp.factorial2(2 * ell - 2 * j)
            * sp.factorial2(2 * ell + 2 * j + 1)
        )
    )


def main() -> None:
    t, x = sp.symbols("t x", real=True)
    checks = 0

    for ell in range(1, 9):
        expansion = sum(
            legendre_coefficient(ell, j) * sp.legendre(2 * j, t)
            for j in range(1, ell + 1)
        )
        target = t ** (2 * ell) - sp.Rational(1, 2 * ell + 1)
        assert sp.simplify(sp.expand(expansion - target)) == 0
        checks += 1
        assert legendre_coefficient(ell, ell) != 0
        checks += 1

    for j in range(1, 7):
        ej = sp.sqrt(4 * j + 1) * sp.legendre(2 * j, 1 - 2 * x)
        for k in range(1, 7):
            ek = sp.sqrt(4 * k + 1) * sp.legendre(2 * k, 1 - 2 * x)
            value = sp.simplify(sp.integrate(ej * ek, (x, 0, 1)))
            assert value == (1 if j == k else 0)
            checks += 1

    # Check route covariance from the orthogonal expansion.
    for ell in range(1, 6):
        for m in range(1, 6):
            a_ell = sp.factorial(ell) / (2 * sp.factorial(2 * ell))
            a_m = sp.factorial(m) / (2 * sp.factorial(2 * m))
            mode_cov = sp.simplify(
                (ell + 1)
                * (m + 1)
                * a_ell
                * a_m
                * sum(
                    legendre_coefficient(ell, j)
                    * legendre_coefficient(m, j)
                    / (4 * j + 1)
                    for j in range(1, min(ell, m) + 1)
                )
            )
            closed = sp.simplify(
                (ell + 1)
                * (m + 1)
                * a_ell
                * a_m
                * (
                    sp.Rational(1, 2 * ell + 2 * m + 1)
                    - sp.Rational(1, (2 * ell + 1) * (2 * m + 1))
                )
            )
            assert sp.simplify(mode_cov - closed) == 0
            checks += 1

    # Incoming/outgoing stars span every polynomial degree through 2L.
    for length in range(1, 7):
        polys = [sp.Integer(1)]
        for r in range(1, length + 1):
            incoming = (x**2 / 2) ** r
            outgoing = ((1 - x) ** 2 / 2) ** r
            polys.extend([sp.expand(incoming + outgoing), sp.expand(incoming - outgoing)])
        coeff_matrix = sp.zeros(2 * length + 1, 2 * length + 1)
        for col, poly in enumerate(polys):
            p = sp.Poly(poly, x)
            for degree in range(2 * length + 1):
                coeff_matrix[degree, col] = p.coeff_monomial(x**degree)
        assert coeff_matrix.det() != 0
        checks += 1

    d_in = x**2 / 2
    d_out = (1 - x) ** 2 / 2
    coordinate = sp.simplify(sp.Rational(1, 2) + d_in - d_out)
    assert coordinate == x
    checks += 1

    y = sp.symbols("y", real=True)
    s_x = d_in - d_out
    s_y = y**2 / 2 - (1 - y) ** 2 / 2
    assert sp.simplify((s_y - s_x) - (y - x)) == 0
    checks += 1

    print(f"verified {checks} exact Legendre and rooted-star checks")


if __name__ == "__main__":
    main()
