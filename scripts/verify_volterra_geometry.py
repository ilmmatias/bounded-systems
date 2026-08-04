#!/usr/bin/env python3
"""Exact checks for findings-82.md."""

from __future__ import annotations

import sympy as sp


def power_kernel(m: int, x: sp.Symbol, y: sp.Symbol) -> sp.Expr:
    return (y - x) ** (m - 1) / sp.factorial(m - 1)


def main() -> None:
    x, y, z, t = sp.symbols("x y z t", real=True)
    checks = 0

    for m in range(1, 8):
        convolution = sp.integrate(power_kernel(m, x, z), (z, x, y))
        assert sp.simplify(convolution - power_kernel(m + 1, x, y)) == 0
        checks += 1

    for m in range(1, 6):
        for n in range(1, 6):
            convolution = sp.integrate(
                power_kernel(m, x, z) * power_kernel(n, z, y), (z, x, y)
            )
            assert sp.simplify(convolution - power_kernel(m + n, x, y)) == 0
            checks += 1

    for ell in range(1, 8):
        path_kernel = power_kernel(2 * ell, x, y)
        density = sp.integrate(sp.integrate(path_kernel, (y, x, 1)), (x, 0, 1))
        assert sp.simplify(density - sp.Rational(1, sp.factorial(2 * ell + 1))) == 0
        checks += 1

    for m in range(1, 8):
        hs_sq = sp.integrate(
            sp.integrate(power_kernel(m, x, y) ** 2, (y, x, 1)), (x, 0, 1)
        )
        expected = sp.Rational(
            1, sp.factorial(m - 1) ** 2 * (2 * m - 1) * (2 * m)
        )
        assert sp.simplify(hs_sq - expected) == 0
        checks += 1

    # Generating-kernel coefficient checks.
    for m in range(1, 9):
        coeff = (
            sp.series(t * sp.exp(t * (y - x)), t, 0, m + 1)
            .removeO()
            .expand()
            .coeff(t, m)
        )
        assert sp.simplify(coeff - power_kernel(m, x, y)) == 0
        checks += 1

    q = sp.symbols("q")
    series = sp.sqrt(q) * sp.sinh(sp.sqrt(q) * (y - x))
    for ell in range(1, 8):
        coeff = sp.series(series, q, 0, ell + 1).removeO().expand().coeff(q, ell)
        assert sp.simplify(coeff - power_kernel(2 * ell, x, y)) == 0
        checks += 1

    scalar = sp.sinh(sp.sqrt(q)) / sp.sqrt(q)
    for ell in range(0, 8):
        coeff = sp.series(scalar, q, 0, ell + 1).removeO().expand().coeff(q, ell)
        assert coeff == sp.Rational(1, sp.factorial(2 * ell + 1))
        checks += 1

    d_in = x**2 / 2
    d_out = (1 - x) ** 2 / 2
    assert sp.simplify(sp.Rational(1, 2) + d_in - d_out - x) == 0
    assert sp.simplify((z - x) - ((y - x) + (z - y))) == 0
    checks += 2

    print(f"verified {checks} exact Volterra path-geometry checks")


if __name__ == "__main__":
    raise SystemExit(main())
