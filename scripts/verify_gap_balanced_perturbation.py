#!/usr/bin/env python3
"""Exact symbolic checks for findings-87 balanced gap-kernel perturbation."""

from __future__ import annotations

import sympy as sp


def main() -> None:
    x, y, z, w = sp.symbols("x y z w", real=True)
    psi = x**4 * (1 - y) ** 4 * (y - x) ** 4
    h = sp.diff(psi, x, y)

    assert sp.simplify(sp.integrate(h, (y, x, 1))) == 0
    assert sp.simplify(sp.integrate(h, (x, 0, y))) == 0

    a = y - x
    inner = sp.integrate(sp.integrate(a * h, (y, x, 1)), (x, 0, 1))
    assert sp.simplify(inner) == 0

    norm = sp.integrate(sp.integrate(h**2, (y, x, 1)), (x, 0, 1))
    assert norm == sp.Rational(1, 1867190325)

    in_degree = sp.integrate(y - x, (x, 0, y))
    out_degree = sp.integrate(y - x, (y, x, 1))
    assert sp.simplify(in_degree - y**2 / 2) == 0
    assert sp.simplify(out_degree - (1 - x) ** 2 / 2) == 0

    two_edge = sp.integrate((x**2 / 2) * ((1 - x) ** 2 / 2), (x, 0, 1))
    assert two_edge == sp.Rational(1, 120)

    # First variation of the three-edge route. The outer-edge terms vanish;
    # only the perturbation on the middle edge survives.
    hyz = h.subs({x: y, y: z}, simultaneous=True)
    middle = sp.integrate(
        sp.integrate(
            sp.integrate(
                sp.integrate((y - x) * hyz * (w - z), (w, z, 1)),
                (z, y, 1),
            ),
            (y, x, 1),
        ),
        (x, 0, 1),
    )
    assert middle == -sp.Rational(1, 60540480)

    base_three_edge = sp.integrate(
        sp.integrate(
            sp.integrate(
                sp.integrate((y - x) * (z - y) * (w - z), (w, z, 1)),
                (z, y, 1),
            ),
            (y, x, 1),
        ),
        (x, 0, 1),
    )
    assert base_three_edge == sp.Rational(1, 5040)

    print("balanced gap perturbation exact checks: 10")
    print("all marginal cancellations, norm, and route-variation checks passed")


if __name__ == "__main__":
    raise SystemExit(main())
