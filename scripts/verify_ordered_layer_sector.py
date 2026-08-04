#!/usr/bin/env python3
"""Exact audits for findings-48 ordered-layer sectors.

The script uses only the Python standard library. It verifies:
1. the exact finite induced-pattern formula by exhaustive subset counting;
2. the exact layer-proportion drift and covariance for rational parameters;
3. the two-layer edge-density identity and its symmetric second-order form.
"""

from __future__ import annotations

from fractions import Fraction
from itertools import combinations
from math import comb
from typing import Dict, Iterator, List, Sequence, Tuple

Composition = Tuple[int, ...]


def weak_compositions(total: int, parts: int) -> Iterator[Tuple[int, ...]]:
    if parts == 1:
        yield (total,)
        return
    for first in range(total + 1):
        for tail in weak_compositions(total - first, parts - 1):
            yield (first,) + tail


def subset_pattern(marks: Sequence[int], subset: Sequence[int]) -> Composition:
    counts: Dict[int, int] = {}
    for vertex in subset:
        mark = marks[vertex]
        counts[mark] = counts.get(mark, 0) + 1
    return tuple(counts[key] for key in sorted(counts))


def brute_pattern_count(marks: Sequence[int], k: int) -> Dict[Composition, int]:
    counts: Dict[Composition, int] = {}
    for subset in combinations(range(len(marks)), k):
        pattern = subset_pattern(marks, subset)
        counts[pattern] = counts.get(pattern, 0) + 1
    return counts


def exact_formula_count(counts: Sequence[int], pattern: Composition) -> int:
    r = len(pattern)
    total = 0
    for layers in combinations(range(len(counts)), r):
        term = 1
        for layer, size in zip(layers, pattern):
            term *= comb(counts[layer], size)
        total += term
    return total


def audit_pattern_formula(q: int = 3, max_n: int = 8) -> int:
    checks = 0
    for n in range(1, max_n + 1):
        for counts in weak_compositions(n, q):
            marks: List[int] = []
            for layer, count in enumerate(counts, start=1):
                marks.extend([layer] * count)
            for k in range(1, n + 1):
                brute = brute_pattern_count(marks, k)
                patterns = set(brute)
                # Every composition of k with at most q parts is a possible query.
                for r in range(1, min(q, k) + 1):
                    for cuts in combinations(range(1, k), r - 1):
                        endpoints = (0,) + cuts + (k,)
                        patterns.add(
                            tuple(
                                endpoints[j + 1] - endpoints[j]
                                for j in range(r)
                            )
                        )
                for pattern in patterns:
                    expected = exact_formula_count(counts, pattern)
                    actual = brute.get(pattern, 0)
                    if actual != expected:
                        raise AssertionError(
                            f"pattern mismatch counts={counts} k={k} "
                            f"pattern={pattern}: {actual} != {expected}"
                        )
                    checks += 1
    return checks


def outer(vector: Sequence[Fraction]) -> List[List[Fraction]]:
    return [[x * y for y in vector] for x in vector]


def audit_count_coefficients() -> int:
    p = (Fraction(1, 6), Fraction(1, 3), Fraction(1, 2))
    counts = (3, 4, 5)
    n = sum(counts)
    z = tuple(Fraction(c, n) for c in counts)

    increments = []
    for i in range(len(p)):
        e = tuple(Fraction(int(j == i), 1) for j in range(len(p)))
        increments.append(tuple(e[j] - z[j] for j in range(len(p))))

    mean = [sum(p[i] * increments[i][j] for i in range(len(p))) for j in range(len(p))]
    expected_mean = [p[j] - z[j] for j in range(len(p))]
    if mean != expected_mean:
        raise AssertionError(f"drift mismatch: {mean} != {expected_mean}")

    covariance = [[Fraction(0, 1) for _ in p] for _ in p]
    for i in range(len(p)):
        centered = tuple(increments[i][j] - mean[j] for j in range(len(p)))
        term = outer(centered)
        for r in range(len(p)):
            for c in range(len(p)):
                covariance[r][c] += p[i] * term[r][c]

    expected_covariance = [
        [
            (p[r] if r == c else Fraction(0, 1)) - p[r] * p[c]
            for c in range(len(p))
        ]
        for r in range(len(p))
    ]
    if covariance != expected_covariance:
        raise AssertionError(
            f"covariance mismatch: {covariance} != {expected_covariance}"
        )
    return 2


def audit_two_layer_edge_identity(max_n: int = 40) -> int:
    checks = 0
    for n in range(2, max_n + 1):
        for c1 in range(n + 1):
            c2 = n - c1
            x = Fraction(c1, n)
            exact = Fraction(c1 * c2, comb(n, 2))
            profile = Fraction(2 * n, n - 1) * x * (1 - x)
            if exact != profile:
                raise AssertionError(
                    f"edge identity mismatch n={n} c1={c1}: {exact} != {profile}"
                )

            centered = Fraction(n, 1) * (exact - Fraction(1, 2))
            y_squared = Fraction((2 * c1 - n) ** 2, 4 * n)
            second_order = Fraction(n, 2 * (n - 1)) - Fraction(2 * n, n - 1) * y_squared
            if centered != second_order:
                raise AssertionError(
                    f"second-order mismatch n={n} c1={c1}: "
                    f"{centered} != {second_order}"
                )
            checks += 2
    return checks


def main() -> None:
    total = 0
    total += audit_pattern_formula()
    total += audit_count_coefficients()
    total += audit_two_layer_edge_identity()
    print(f"ordered-layer audits passed: {total} exact checks")


if __name__ == "__main__":
    raise SystemExit(main())
