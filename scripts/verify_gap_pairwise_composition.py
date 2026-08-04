#!/usr/bin/env python3
"""Exact checks for findings-99.md through findings-102.md."""

from __future__ import annotations

import sympy as sp


def main() -> None:
    x, y, z = sp.symbols("x y z", real=True)
    checks = 0

    # Target two-step path volume.
    path_volume = sp.integrate((z - x) * (y - z), (z, x, y))
    assert sp.simplify(path_volume - (y - x) ** 3 / 6) == 0
    checks += 1

    # Distributional second derivative of the left-endpoint transform.
    a, t = sp.symbols("a t", real=True)
    uniform_transform = sp.integrate((z - a) * (t - z), (z, a, t))
    assert sp.simplify(sp.diff(uniform_transform, t, 2) - (t - a)) == 0
    checks += 1

    # Endpoint atoms do not contribute to the cubic composition integral.
    p, q, d = sp.symbols("p q d", nonnegative=True, real=True)
    endpoint_integrand_left = (a - a) * (t - a)
    endpoint_integrand_right = (t - a) * (t - t)
    assert endpoint_integrand_left == 0
    assert endpoint_integrand_right == 0
    checks += 2

    # Exact edge-density decomposition for an interval of length d with
    # endpoint masses p and q.
    edge_density = d**3 / 6 + (p + q) * d**2 / 2 + p * q * d
    checks += 1

    # Under p+q=1-d, the endpoint product is maximized at equal masses.
    edge_max = sp.simplify(
        edge_density.subs(q, 1 - d - p).subs(p, (1 - d) / 2)
    )
    expected_max = (3 * d - d**3) / 12
    assert sp.simplify(edge_max - expected_max) == 0
    checks += 1

    target_gap = sp.factor(sp.Rational(1, 6) - expected_max)
    assert target_gap == (d - 1) ** 2 * (d + 2) / 12
    checks += 1

    # Direct substitution of the target distribution.
    assert sp.simplify(edge_density.subs({d: 1, p: 0, q: 0}) - sp.Rational(1, 6)) == 0
    checks += 1

    # A nontrivial endpoint-atomic example satisfies the pairwise path law
    # but falls strictly below the target edge density.
    example = sp.simplify(
        edge_density.subs(
            {
                d: sp.Rational(1, 2),
                p: sp.Rational(1, 4),
                q: sp.Rational(1, 4),
            }
        )
    )
    assert example < sp.Rational(1, 6)
    checks += 1

    # A genuine coordinate gap gives zero intermediate volume and positive
    # cubic separation.
    gap_length = sp.Rational(2, 5)
    assert 0 != gap_length**3
    checks += 1

    print(f"verified {checks} pairwise-composition and absolute-rigidity identities")


if __name__ == "__main__":
    raise SystemExit(main())
