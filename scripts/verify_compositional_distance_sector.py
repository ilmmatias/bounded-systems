#!/usr/bin/env python3
"""Exact checks for findings-83.md."""

from __future__ import annotations

import sympy as sp


def main() -> None:
    x, y, z = sp.symbols("x y z", real=True)
    checks = 0

    # Normalized degrees of the adjacent half-kernels.
    c01 = y
    r12 = 1 - y
    assert sp.simplify(c01 + r12 - 1) == 0
    checks += 1

    # A nontrivial reparameterization fails the alignment identity.
    phi = y**2
    misalignment = sp.integrate((y + (1 - phi) - 1) ** 2, (y, 0, 1))
    assert misalignment == sp.Rational(1, 30)
    checks += 1

    # Exact path volume for rational ordered and reversed endpoints.
    rational_points = [sp.Rational(i, 7) for i in range(8)]
    for xv in rational_points:
        for zv in rational_points:
            path_length = max(sp.Rational(0), zv - xv)
            ambient_path = path_length / 3
            shortcut = max(sp.Rational(0), zv - xv)
            assert sp.simplify(shortcut - 3 * ambient_path) == 0
            checks += 1

    # Integrated shortcut defect: zero at the target and positive at wrong blocks.
    target_defect = sp.integrate(
        sp.integrate(((z - x) - (z - x)) ** 2, (z, x, 1)), (x, 0, 1)
    )
    assert target_defect == 0
    checks += 1

    zero_shortcut_defect = sp.integrate(
        sp.integrate((z - x) ** 2, (z, x, 1)), (x, 0, 1)
    )
    assert zero_shortcut_defect == sp.Rational(1, 12)
    checks += 1

    half_shortcut_defect = sp.integrate(
        sp.integrate(((z - x) / 2) ** 2, (z, x, 1)), (x, 0, 1)
    )
    assert half_shortcut_defect == sp.Rational(1, 48)
    checks += 1

    print(f"verified {checks} exact compositional-distance checks")


if __name__ == "__main__":
    main()
