#!/usr/bin/env python3
"""Exact diagnostics for findings-66 and findings-67."""

from __future__ import annotations

from fractions import Fraction
from itertools import combinations, product
from typing import Iterable

import sympy as sp


def compositions(total: int) -> Iterable[tuple[int, ...]]:
    """Yield all positive ordered compositions of total."""
    if total == 0:
        yield ()
        return
    for mask in range(1 << (total - 1)):
        parts: list[int] = []
        start = 0
        for i in range(total - 1):
            if mask & (1 << i):
                parts.append(i + 1 - start)
                start = i + 1
        parts.append(total - start)
        yield tuple(parts)


def degree_points(parts: tuple[Fraction, ...]) -> list[tuple[Fraction, Fraction]]:
    points = []
    before = Fraction(0)
    for p in parts:
        after = Fraction(1) - before - p
        points.append((before, after))
        before += p
    return points


def q_value(
    x: Fraction,
    y: Fraction,
    target_points: list[tuple[Fraction, Fraction]],
) -> Fraction:
    value = Fraction(1)
    for a, b in target_points:
        value *= (x - a) ** 2 + (y - b) ** 2
    return value


def forcing_energy(
    candidate: tuple[Fraction, ...],
    target_points: list[tuple[Fraction, Fraction]],
) -> Fraction:
    return sum(
        mass * q_value(x, y, target_points)
        for mass, (x, y) in zip(candidate, degree_points(candidate), strict=True)
    )


def classify_three_layers(labels: tuple[int, int, int]) -> tuple[int, int]:
    """Return (edge_count, open_path_count) for a deterministic ordered-layer triple."""
    edges: set[tuple[int, int]] = set()
    for u, v in combinations(range(3), 2):
        if labels[u] < labels[v]:
            edges.add((u, v))
        elif labels[v] < labels[u]:
            edges.add((v, u))
    open_paths = 0
    for x, y, z in permutations3():
        if (x, y) in edges and (y, z) in edges and (x, z) not in edges:
            open_paths += 1
    return len(edges), open_paths


def permutations3() -> tuple[tuple[int, int, int], ...]:
    return (
        (0, 1, 2),
        (0, 2, 1),
        (1, 0, 2),
        (1, 2, 0),
        (2, 0, 1),
        (2, 1, 0),
    )


def check_target(numerators: tuple[int, ...]) -> int:
    denominator = sum(numerators)
    target = tuple(Fraction(n, denominator) for n in numerators)
    points = degree_points(target)
    checks = 0

    # The target is exactly a zero of the forcing polynomial.
    assert forcing_energy(target, points) == 0
    checks += 1

    # Every rational strict weak-order competitor on the same denominator
    # has positive energy unless its ordered class masses are the target.
    zero_candidates = []
    min_positive: Fraction | None = None
    for comp in compositions(denominator):
        candidate = tuple(Fraction(n, denominator) for n in comp)
        energy = forcing_energy(candidate, points)
        checks += 1
        if energy == 0:
            zero_candidates.append(comp)
        elif min_positive is None or energy < min_positive:
            min_positive = energy
    assert zero_candidates == [numerators]
    assert min_positive is not None and min_positive > 0
    checks += 2

    # Symbolic expansion agrees with the mixed-moment evaluation.
    x, y = sp.symbols("x y")
    q_poly = sp.Integer(1)
    for a, b in points:
        q_poly *= (x - sp.Rational(a.numerator, a.denominator)) ** 2 + (
            y - sp.Rational(b.numerator, b.denominator)
        ) ** 2
    q_poly = sp.Poly(sp.expand(q_poly), x, y)
    moment_sum = sp.Integer(0)
    for (a_exp, b_exp), coeff in q_poly.terms():
        moment = sum(
            sp.Rational(mass.numerator, mass.denominator)
            * sp.Rational(px.numerator, px.denominator) ** a_exp
            * sp.Rational(py.numerator, py.denominator) ** b_exp
            for mass, (px, py) in zip(target, points, strict=True)
        )
        moment_sum += coeff * moment
        checks += 1
    assert sp.simplify(moment_sum) == 0
    assert q_poly.total_degree() == 2 * len(target)
    checks += 2

    # Deterministic ordered layers contain neither forbidden three-vertex pattern.
    q = len(target)
    for labels in product(range(q), repeat=3):
        edge_count, open_paths = classify_three_layers(labels)
        assert edge_count != 1
        assert open_paths == 0
        checks += 2

    print(
        f"target={numerators}/{denominator}: "
        f"competitors={2 ** (denominator - 1)}, "
        f"minimum_positive_gap={min_positive}, "
        f"polynomial_terms={len(q_poly.terms())}"
    )
    return checks


def main() -> None:
    targets = (
        (1, 1),
        (1, 2),
        (1, 1, 2),
        (1, 2, 1),
        (1, 1, 1, 1),
        (1, 2, 2, 1),
    )
    checks = sum(check_target(target) for target in targets)
    print(f"verified {checks} exact absolute-forcing identities")


if __name__ == "__main__":
    main()
