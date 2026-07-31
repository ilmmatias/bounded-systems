#!/usr/bin/env python3
"""Exact and exhaustive checks for findings-50.

The script verifies:
1. the general q-layer two-step route density and first-projection formulas;
2. uniqueness of the interior first-order degeneracy for q=3;
3. the exact three-layer route-count decomposition for every mark/edge
   realization through n=6;
4. exact finite-n means and the approach of n^2 Var(R_n) to the predicted
   symmetric second-order coefficient for a=b=1/2.
"""

from __future__ import annotations

from fractions import Fraction
from itertools import combinations, product
from math import comb
import random


def route_kernel(marks: tuple[int, int, int], w: list[list[Fraction]]) -> Fraction:
    ordered = sorted(marks)
    if len(set(ordered)) < 3:
        return Fraction(0)
    i, j, k = ordered
    return w[i][j] * w[j][k]


def check_general_projection(trials: int = 200) -> int:
    rng = random.Random(20260729)
    checks = 0
    for _ in range(trials):
        q = rng.randint(3, 6)
        raw = [rng.randint(1, 7) for _ in range(q)]
        total = sum(raw)
        p = [Fraction(x, total) for x in raw]
        w = [[Fraction(0) for _ in range(q)] for _ in range(q)]
        for i in range(q):
            for j in range(i + 1, q):
                w[i][j] = Fraction(rng.randint(0, 5), 5)

        direct = Fraction(0)
        for marks in product(range(q), repeat=3):
            prob = p[marks[0]] * p[marks[1]] * p[marks[2]]
            direct += prob * route_kernel(marks, w)

        formula = Fraction(0)
        for i in range(q):
            for j in range(i + 1, q):
                for k in range(j + 1, q):
                    formula += 6 * p[i] * p[j] * p[k] * w[i][j] * w[j][k]
        assert direct == formula
        checks += 1

        qvals: list[Fraction] = []
        for a in range(q):
            conditional = Fraction(0)
            for b, c in product(range(q), repeat=2):
                conditional += p[b] * p[c] * route_kernel((a, b, c), w)
            qvals.append(conditional)

            closed = Fraction(0)
            for j in range(a + 1, q):
                for k in range(j + 1, q):
                    closed += 2 * p[j] * p[k] * w[a][j] * w[j][k]
            for i in range(a):
                for k in range(a + 1, q):
                    closed += 2 * p[i] * p[k] * w[i][a] * w[a][k]
            for i in range(a):
                for j in range(i + 1, a):
                    closed += 2 * p[i] * p[j] * w[i][j] * w[j][a]
            assert conditional == closed
            checks += 1

        assert sum(p[i] * qvals[i] for i in range(q)) == formula
        checks += 1
    return checks


def check_unique_degeneracy() -> int:
    checks = 0
    for x1 in range(1, 12):
        for x2 in range(1, 12):
            for x3 in range(1, 12):
                total = x1 + x2 + x3
                p1, p2, p3 = (Fraction(x, total) for x in (x1, x2, x3))
                q1 = p2 * p3
                q2 = p1 * p3
                q3 = p1 * p2
                degenerate = q1 == q2 == q3
                assert degenerate == (x1 == x2 == x3)
                checks += 1
    return checks


def route_count_and_decomposition(
    marks: tuple[int, ...],
    bits12: tuple[int, ...],
    bits23: tuple[int, ...],
    a: Fraction,
    b: Fraction,
) -> tuple[Fraction, Fraction]:
    v1 = [u for u, mark in enumerate(marks) if mark == 0]
    v2 = [u for u, mark in enumerate(marks) if mark == 1]
    v3 = [u for u, mark in enumerate(marks) if mark == 2]
    pairs12 = [(u, v) for u in v1 for v in v2]
    pairs23 = [(v, w) for v in v2 for w in v3]
    edge12 = dict(zip(pairs12, bits12))
    edge23 = dict(zip(pairs23, bits23))

    route_count = 0
    for u in v1:
        for v in v2:
            for w in v3:
                route_count += edge12[(u, v)] * edge23[(v, w)]

    n12 = sum(Fraction(edge12[e]) - a for e in pairs12)
    n23 = sum(Fraction(edge23[e]) - b for e in pairs23)
    qterm = Fraction(0)
    for v in v2:
        xv = sum(Fraction(edge12[(u, v)]) - a for u in v1)
        yv = sum(Fraction(edge23[(v, w)]) - b for w in v3)
        qterm += xv * yv

    decomposition = (
        a * b * len(v1) * len(v2) * len(v3)
        + b * len(v3) * n12
        + a * len(v1) * n23
        + qterm
    )
    return Fraction(route_count), decomposition


def exhaustive_decomposition(max_n: int = 6) -> int:
    a = Fraction(1, 2)
    b = Fraction(1, 2)
    checks = 0
    for n in range(3, max_n + 1):
        for marks in product(range(3), repeat=n):
            c1 = marks.count(0)
            c2 = marks.count(1)
            c3 = marks.count(2)
            m12 = c1 * c2
            m23 = c2 * c3
            for bits in product((0, 1), repeat=m12 + m23):
                lhs, rhs = route_count_and_decomposition(
                    marks,
                    bits[:m12],
                    bits[m12:],
                    a,
                    b,
                )
                assert lhs == rhs
                checks += 1
    return checks


def exact_mean_variance(n: int) -> tuple[Fraction, Fraction]:
    """Exhaustive law for p=(1/3,1/3,1/3), a=b=1/2."""
    p_mark = Fraction(1, 3) ** n
    mean = Fraction(0)
    second = Fraction(0)
    denominator = comb(n, 3)
    for marks in product(range(3), repeat=n):
        c1 = marks.count(0)
        c2 = marks.count(1)
        c3 = marks.count(2)
        m12 = c1 * c2
        m23 = c2 * c3
        edge_weight = Fraction(1, 2) ** (m12 + m23)
        for bits in product((0, 1), repeat=m12 + m23):
            count, _ = route_count_and_decomposition(
                marks,
                bits[:m12],
                bits[m12:],
                Fraction(1, 2),
                Fraction(1, 2),
            )
            density = count / denominator
            weight = p_mark * edge_weight
            mean += weight * density
            second += weight * density * density
    return mean, second - mean * mean


def check_exact_moments(max_n: int = 6) -> int:
    target_mean = Fraction(1, 18)  # 2ab/9 with a=b=1/2
    target_scaled_variance = Fraction(1, 12)  # 4ab(a+b-ab)/9
    checks = 0
    previous_error = None
    for n in range(3, max_n + 1):
        mean, variance = exact_mean_variance(n)
        assert mean == target_mean
        scaled = n * n * variance
        error = abs(scaled - target_scaled_variance)
        if previous_error is not None and n >= 5:
            assert error < previous_error
        previous_error = error
        print(
            f"n={n}: mean={mean}, n^2 Var={scaled} "
            f"(target {target_scaled_variance})"
        )
        checks += 2
    return checks


def main() -> None:
    checks = 0
    checks += check_general_projection()
    checks += check_unique_degeneracy()
    checks += exhaustive_decomposition()
    checks += check_exact_moments()
    print(f"verified {checks:,} stochastic three-layer route identities")


if __name__ == "__main__":
    main()
