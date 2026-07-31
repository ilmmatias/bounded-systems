#!/usr/bin/env python3
"""Exact checks for findings-88.md."""

from __future__ import annotations

import sympy as sp

x, y = sp.symbols("x y")


def triangle_integral(expr: sp.Expr) -> sp.Expr:
    return sp.simplify(sp.integrate(sp.integrate(sp.expand(expr), (x, 0, y)), (y, 0, 1)))


def q_route(m: int) -> sp.Expr:
    return sp.expand(
        sum(
            x ** (2 * a)
            / sp.factorial(2 * a)
            * (1 - y) ** (2 * (m - 1 - a))
            / sp.factorial(2 * (m - 1 - a))
            for a in range(m)
        )
    )


def r_route(m: int) -> sp.Expr:
    return sp.expand(sp.diff(q_route(m), x, y))


def r_formula(m: int) -> sp.Expr:
    if m < 3:
        return sp.Integer(0)
    return sp.expand(
        -sum(
            x ** (2 * a - 1)
            / sp.factorial(2 * a - 1)
            * (1 - y) ** (2 * (m - 1 - a) - 1)
            / sp.factorial(2 * (m - 1 - a) - 1)
            for a in range(1, m - 1)
        )
    )


def main() -> None:
    checks = 0

    for m in range(1, 11):
        assert sp.expand(r_route(m) - r_formula(m)) == 0
        checks += 1

    assert r_route(1) == 0
    assert r_route(2) == 0
    checks += 2

    for m in range(3, 10):
        poly = sp.Poly(r_route(m), x, y)
        assert poly.total_degree() == 2 * m - 4
        assert poly != 0
        checks += 2

    base = x**4 * (1 - y) ** 4 * (y - x) ** 4
    for size in range(1, 7):
        matrix = sp.Matrix(
            [
                [triangle_integral(base * x**j * r_route(m)) for j in range(size)]
                for m in range(3, size + 3)
            ]
        )
        assert matrix.rank() == size
        checks += 1

    for j in range(7):
        phi = sp.expand(base * x**j)
        h = sp.diff(phi, x, y)
        inner = triangle_integral((y - x) * h)
        assert inner == 0
        checks += 1

    # The compact generating function for the route derivative kernels.
    z = sp.symbols("z")
    truncated = sum(r_route(m) * z ** (m - 1) for m in range(3, 9))
    target = -z * sp.sinh(x * sp.sqrt(z)) * sp.sinh((1 - y) * sp.sqrt(z))
    target_series = sp.series(target, z, 0, 9).removeO()
    for power in range(2, 8):
        assert sp.expand(truncated - target_series).coeff(z, power) == 0
        checks += 1

    print(f"verified {checks} exact gap-route matching identities")


if __name__ == "__main__":
    main()
