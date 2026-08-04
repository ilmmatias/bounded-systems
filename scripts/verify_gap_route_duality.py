#!/usr/bin/env python3
"""Exact checks for findings-89.md."""

from __future__ import annotations

import sympy as sp

x, y = sp.symbols("x y")


def triangle_integral(expr: sp.Expr) -> sp.Expr:
    inner = sp.integrate(sp.expand(expr), (x, 0, y))
    return sp.simplify(sp.integrate(inner, (y, 0, 1)))


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


def main() -> None:
    checks = 0
    phi = x**4 * (1 - y) ** 4 * (y - x) ** 4 * (x + y - 1)
    h = sp.expand(sp.diff(phi, x, y))

    dual = sp.expand(h.subs({x: 1 - y, y: 1 - x}, simultaneous=True))
    assert sp.expand(dual + h) == 0
    checks += 1

    row = sp.simplify(sp.integrate(h, (y, x, 1)))
    col = sp.simplify(sp.integrate(h, (x, 0, y)))
    assert row == 0
    assert col == 0
    checks += 2

    for m in range(1, 11):
        derivative = triangle_integral(h * q_route(m))
        assert derivative == 0
        checks += 1

    def broom_coefficient(a: int, b: int) -> sp.Expr:
        return sp.simplify(
            triangle_integral(h * x ** (2 * a) * (1 - y) ** (2 * b))
            / 2 ** (a + b)
        )

    c12 = broom_coefficient(1, 2)
    c21 = broom_coefficient(2, 1)
    assert c12 == sp.Rational(1, 4_190_266_080)
    assert c21 == -c12
    checks += 2

    assert broom_coefficient(1, 1) == 0
    checks += 1

    norm = triangle_integral(h**2)
    assert norm == sp.Rational(1, 57_260_503_300)
    checks += 1

    print(f"verified {checks} exact gap-route duality identities")


if __name__ == "__main__":
    raise SystemExit(main())
