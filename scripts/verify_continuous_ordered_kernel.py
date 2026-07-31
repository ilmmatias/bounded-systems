#!/usr/bin/env python3
"""Exact checks for findings-58.md using rational polynomial arithmetic."""

from __future__ import annotations

from fractions import Fraction
from typing import Iterable

Poly = tuple[Fraction, ...]  # ascending powers


def poly(*coeffs: int | Fraction) -> Poly:
    return tuple(Fraction(c) for c in coeffs)


def add(a: Poly, b: Poly) -> Poly:
    n = max(len(a), len(b))
    return tuple(
        (a[i] if i < len(a) else Fraction(0))
        + (b[i] if i < len(b) else Fraction(0))
        for i in range(n)
    )


def sub(a: Poly, b: Poly) -> Poly:
    return add(a, tuple(-c for c in b))


def mul(a: Poly, b: Poly) -> Poly:
    out = [Fraction(0)] * (len(a) + len(b) - 1)
    for i, ai in enumerate(a):
        for j, bj in enumerate(b):
            out[i + j] += ai * bj
    return tuple(out)


def scale(a: Poly, c: int | Fraction) -> Poly:
    c = Fraction(c)
    return tuple(c * ai for ai in a)


def integrate_01(a: Poly) -> Fraction:
    return sum((c / Fraction(i + 1) for i, c in enumerate(a)), Fraction(0))


def assert_equal(actual: Fraction | Poly, expected: Fraction | Poly, label: str) -> None:
    if actual != expected:
        raise AssertionError(f"{label}: expected {expected}, got {actual}")


def main() -> None:
    # q_E(x) = x^2 - x + 1/2; theta_E = 1/3.
    q_edge = poly(Fraction(1, 2), -1, 1)
    theta_edge = integrate_01(q_edge)
    assert_equal(theta_edge, Fraction(1, 3), "edge mean")

    h_edge = sub(q_edge, poly(theta_edge))
    sigma_edge_1 = integrate_01(mul(h_edge, h_edge))
    assert_equal(sigma_edge_1, Fraction(1, 180), "edge first projection norm")

    c_edge_1 = 4 * sigma_edge_1
    assert_equal(c_edge_1, Fraction(1, 45), "edge C1")

    var_edge_indicator = theta_edge * (1 - theta_edge)
    sigma_edge_2 = var_edge_indicator - 2 * sigma_edge_1
    assert_equal(sigma_edge_2, Fraction(19, 90), "edge second projection norm")
    assert_equal(2 * sigma_edge_2, Fraction(19, 45), "edge C2")

    # Conditional route contributions.
    q_min = poly(
        Fraction(1, 12),
        Fraction(-1, 3),
        Fraction(1, 2),
        Fraction(-1, 3),
        Fraction(1, 12),
    )
    q_mid = poly(0, 0, Fraction(1, 2), -1, Fraction(1, 2))
    q_max = poly(0, 0, 0, 0, Fraction(1, 12))
    q_route = add(add(q_min, q_mid), q_max)
    expected_q_route = poly(
        Fraction(1, 12),
        Fraction(-1, 3),
        1,
        Fraction(-4, 3),
        Fraction(2, 3),
    )
    assert_equal(q_route, expected_q_route, "route conditional polynomial")

    theta_route = integrate_01(q_route)
    assert_equal(theta_route, Fraction(1, 20), "route mean")

    h_route = sub(q_route, poly(theta_route))
    sigma_route_1 = integrate_01(mul(h_route, h_route))
    assert_equal(sigma_route_1, Fraction(1, 8100), "route first projection norm")
    assert_equal(9 * sigma_route_1, Fraction(1, 900), "route C1")

    cross_projection = integrate_01(mul(h_edge, h_route))
    assert_equal(cross_projection, Fraction(1, 1260), "edge-route projection inner product")
    cross_c1 = 6 * cross_projection
    assert_equal(cross_c1, Fraction(1, 210), "edge-route C1")

    determinant = Fraction(1, 45) * Fraction(1, 900) - Fraction(1, 210) ** 2
    assert_equal(determinant, Fraction(1, 496125), "joint covariance determinant")
    if determinant <= 0:
        raise AssertionError("joint covariance matrix is not positive definite")

    checks: Iterable[tuple[str, Fraction]] = (
        ("edge mean", theta_edge),
        ("edge C1", c_edge_1),
        ("edge C2", 2 * sigma_edge_2),
        ("route mean", theta_route),
        ("route C1", 9 * sigma_route_1),
        ("edge-route C1", cross_c1),
        ("covariance determinant", determinant),
    )
    print("continuous ordered-kernel exact checks passed")
    for name, value in checks:
        print(f"  {name}: {value}")


if __name__ == "__main__":
    main()
