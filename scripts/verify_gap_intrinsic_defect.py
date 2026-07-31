#!/usr/bin/env python3
"""Exact checks for findings-94.md and the target identities in findings-96.md."""

from __future__ import annotations

import sympy as sp


def main() -> None:
    x, y, z, xp = sp.symbols("x y z xp", real=True)
    checks = 0

    # Target degree and signed-coordinate formulas.
    d_in = sp.integrate(y - x, (x, 0, y))
    d_out = sp.integrate(y - x, (y, x, 1))
    assert sp.simplify(d_in - y**2 / 2) == 0
    assert sp.simplify(d_out - (1 - x) ** 2 / 2) == 0
    checks += 2

    s_x = x - sp.Rational(1, 2)
    s_y = y - sp.Rational(1, 2)
    forward = y - x
    assert sp.expand(forward - (s_y - s_x)) == 0
    checks += 1

    # Rooted two-step incoming and outgoing identities.
    p2_in = sp.integrate((y - x) * x**2 / 2, (x, 0, y))
    p2_out = sp.integrate((y - x) * (1 - y) ** 2 / 2, (y, x, 1))
    assert sp.simplify(p2_in - y**4 / 24) == 0
    assert sp.simplify(6 * p2_in - d_in**2) == 0
    assert sp.simplify(p2_out - (1 - x) ** 4 / 24) == 0
    assert sp.simplify(6 * p2_out - d_out**2) == 0
    checks += 4

    edge_density = sp.integrate(sp.integrate(y - x, (y, x, 1)), (x, 0, 1))
    assert edge_density == sp.Rational(1, 6)
    checks += 1

    # An explicit nonzero degree-preserving perturbation has a positive Gram detector.
    psi = x**3 * (1 - y) ** 3 * (y - x) ** 3
    hxy = sp.diff(psi, x, y)
    assert sp.simplify(sp.integrate(hxy, (y, x, 1))) == 0
    assert sp.simplify(sp.integrate(hxy, (x, 0, y))) == 0
    checks += 2

    hxz = hxy.subs({x: x, y: z}, simultaneous=True)
    hxpz = hxy.subs({x: xp, y: z}, simultaneous=True)
    lower = sp.Max(x, xp)
    # Split the square into x < xp and double by symmetry.
    gram = sp.integrate(sp.expand(hxz * hxpz), (z, xp, 1))
    gram_norm = 2 * sp.integrate(
        sp.integrate(sp.expand(gram**2), (x, 0, xp)), (xp, 0, 1)
    )
    assert gram_norm > 0
    checks += 1

    print(f"verified {checks} intrinsic gap-defect identities")
    print(f"explicit perturbation Gram norm: {gram_norm}")


if __name__ == "__main__":
    main()
