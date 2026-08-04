#!/usr/bin/env python3
"""Symbolic checks for findings-98.md."""

from __future__ import annotations

import sympy as sp


def main() -> None:
    u, c = sp.symbols("u c", positive=True, real=True)
    delta = sp.symbols("delta", real=True)
    checks = 0

    q = c * (2 * u - 1)
    assert sp.simplify((2 * u - 1) * sp.diff(q, u) - 2 * q) == 0
    checks += 1

    # The affine active component has the expected incoming and outgoing degrees.
    v = sp.symbols("v", real=True)
    qv = c * (2 * v - 1)
    f = sp.integrate(q - qv, (v, 0, u))
    b = sp.integrate(qv - q, (v, u, 1))
    assert sp.simplify(f - c * u**2) == 0
    assert sp.simplify(b - c * (1 - u) ** 2) == 0
    checks += 2

    j = sp.integrate(c * v**2, (v, 0, u))
    k = sp.integrate(c * (1 - v) ** 2, (v, u, 1))
    assert sp.simplify(j - u * f / 3) == 0
    assert sp.simplify(k - (1 - u) * b / 3) == 0
    checks += 2

    # Jump increments in the integrated degree functions.
    f_minus, b_plus = sp.symbols("f_minus b_plus", real=True)
    f_plus = f_minus + u * delta
    b_minus = b_plus + (1 - u) * delta
    incoming_jump = sp.simplify((f_plus**2 - f_minus**2) / 6)
    outgoing_jump = sp.simplify((b_minus**2 - b_plus**2) / 6)
    expected_in = u * f_minus * delta / 3 + u**2 * delta**2 / 6
    assert sp.simplify(incoming_jump - expected_in) == 0
    expected_out = (
        (1 - u) * b_plus * delta / 3
        + (1 - u) ** 2 * delta**2 / 6
    )
    assert sp.simplify(outgoing_jump - expected_out) == 0
    checks += 2

    # An active component immediately on the left has zero incoming D-defect,
    # so the jump equation requires delta = 0.
    assert sp.solve(sp.Eq(0, u**2 * delta / 6), delta) == [0]
    assert sp.solve(sp.Eq(0, (1 - u) ** 2 * delta / 6), delta) == [0]
    checks += 2

    print(f"verified {checks} active-component and jump-structure identities")


if __name__ == "__main__":
    raise SystemExit(main())
