#!/usr/bin/env python3
"""Symbolic and exact finite-type checks for findings-95.md through findings-97.md."""

from __future__ import annotations

from fractions import Fraction
from itertools import combinations

import sympy as sp


def atomic_degrees(values: tuple[Fraction, ...], masses: tuple[Fraction, ...]):
    d_in = []
    p2_in = []
    d_out = []
    p2_out = []
    for i, qi in enumerate(values):
        incoming = sum(masses[j] * (qi - values[j]) for j in range(i))
        outgoing = sum(masses[j] * (values[j] - qi) for j in range(i + 1, len(values)))
        two_in = sum(
            masses[j] * (qi - values[j])
            * sum(masses[k] * (values[j] - values[k]) for k in range(j))
            for j in range(i)
        )
        two_out = sum(
            masses[j] * (values[j] - qi)
            * sum(
                masses[k] * (values[k] - values[j])
                for k in range(j + 1, len(values))
            )
            for j in range(i + 1, len(values))
        )
        d_in.append(incoming)
        d_out.append(outgoing)
        p2_in.append(two_in)
        p2_out.append(two_out)
    return d_in, p2_in, d_out, p2_out


def main() -> None:
    u, v, L, c = sp.symbols("u v L c", positive=True, real=True)
    checks = 0

    q_u = L * u + c
    q_v = L * v + c
    f = sp.integrate(q_u - q_v, (v, 0, u))
    fv = f.subs(u, v)
    g = sp.integrate((q_u - q_v) * fv, (v, 0, u))
    assert sp.simplify(f - L * u**2 / 2) == 0
    assert sp.simplify(g - L**2 * u**4 / 24) == 0
    assert sp.simplify(6 * g - f**2) == 0
    checks += 3

    b = sp.integrate((L * v + c) - q_u, (v, u, 1))
    bv = b.subs(u, v)
    h = sp.integrate(((L * v + c) - q_u) * bv, (v, u, 1))
    assert sp.simplify(b - L * (1 - u) ** 2 / 2) == 0
    assert sp.simplify(h - L**2 * (1 - u) ** 4 / 24) == 0
    assert sp.simplify(6 * h - b**2) == 0
    checks += 3

    edge = sp.integrate(sp.integrate(L * (v - u), (v, u, 1)), (u, 0, 1))
    assert sp.simplify(edge - L / 6) == 0
    checks += 1

    # Exact finite atomic obstruction for many rational sectors.
    atomic_checks = 0
    for size in range(2, 7):
        for selected in combinations(range(0, 9), size):
            values = tuple(Fraction(a, 8) for a in selected)
            raw = tuple(Fraction(i + 1, 1) for i in range(size))
            total = sum(raw)
            masses = tuple(p / total for p in raw)
            d_in, p2_in, d_out, p2_out = atomic_degrees(values, masses)
            assert d_in[1] > 0
            assert p2_in[1] == 0
            assert 6 * p2_in[1] - d_in[1] ** 2 < 0
            atomic_checks += 1
    checks += atomic_checks

    # Non-affine monotone polynomial diagnostics.
    for power in range(2, 7):
        q_u = u**power
        q_v = v**power
        f = sp.integrate(q_u - q_v, (v, 0, u))
        fv = f.subs(u, v)
        g = sp.integrate((q_u - q_v) * fv, (v, 0, u))
        residual = sp.factor(6 * g - f**2)
        assert residual != 0
        checks += 1

    print(f"verified {checks} quantile-rigidity and finite-atomic checks")
    print(f"finite atomic sectors excluded: {atomic_checks}")


if __name__ == "__main__":
    main()
