#!/usr/bin/env python3
"""Complete symbolic chain for the regular standalone gap forcing theorem."""

from __future__ import annotations

import sympy as sp


def main() -> None:
    u, v, L, c = sp.symbols("u v L c", real=True, positive=True)
    checks = 0

    q_u = L * (u - sp.Rational(1, 2))
    q_v = L * (v - sp.Rational(1, 2))
    w = L * (v - u)

    d_in = sp.integrate(w, (v, 0, u))
    # The preceding integral uses v as the lower coordinate; rewrite directly.
    x = sp.symbols("x", real=True)
    d_in = sp.integrate(L * (u - x), (x, 0, u))
    d_out = sp.integrate(L * (v - u), (v, u, 1))
    s = sp.simplify(d_in - d_out)
    assert sp.simplify(s - q_u) == 0
    checks += 1

    p2 = sp.integrate(L * (u - x) * (L * x**2 / 2), (x, 0, u))
    assert sp.simplify(6 * p2 - d_in**2) == 0
    checks += 1

    edge = sp.integrate(sp.integrate(L * (v - u), (v, u, 1)), (u, 0, 1))
    assert sp.simplify(edge - L / 6) == 0
    assert sp.solve(sp.Eq(edge, sp.Rational(1, 6)), L) == [1]
    checks += 2

    # A non-affine quantile violates the rooted composition equation.
    q_u = u**2 - sp.Rational(1, 3)
    q_v = v**2 - sp.Rational(1, 3)
    f = sp.integrate(q_u - q_v, (v, 0, u))
    fv = f.subs(u, v)
    g = sp.integrate((q_u - q_v) * fv, (v, 0, u))
    assert sp.factor(6 * g - f**2) != 0
    checks += 1

    print(f"verified {checks} regular standalone forcing identities")


if __name__ == "__main__":
    main()
