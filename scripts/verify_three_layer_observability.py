#!/usr/bin/env python3
"""Checks for findings-51.

The script verifies the degree-atom inversion formulas exactly over random
rational parameters and simulates eventual zero-degree recovery and parameter
estimation in the stochastic three-layer sector.
"""

from __future__ import annotations

from fractions import Fraction
import math
import random


def exact_inversion_checks(trials: int = 5000) -> int:
    rng = random.Random(5102026)
    checks = 0
    for _ in range(trials):
        raw = [rng.randint(1, 20) for _ in range(3)]
        total = sum(raw)
        p1, p2, p3 = [Fraction(x, total) for x in raw]
        a = Fraction(rng.randint(1, 19), 20)
        b = Fraction(rng.randint(1, 19), 20)
        c = Fraction(rng.randint(0, 20), 20)

        x1_out = a * p2 + c * p3
        x2_in = a * p1
        x2_out = b * p3
        x3_in = c * p1 + b * p2

        recovered_a = x2_in / p1
        recovered_b = x2_out / p3
        recovered_c_1 = (x1_out - recovered_a * p2) / p3
        recovered_c_2 = (x3_in - recovered_b * p2) / p1

        assert recovered_a == a
        assert recovered_b == b
        assert recovered_c_1 == c
        assert recovered_c_2 == c
        assert x2_in > 0 and x2_out > 0
        assert x1_out > 0 and x3_in > 0
        checks += 8
    return checks


def generate_graph(
    n: int,
    p: tuple[float, float, float],
    w: tuple[float, float, float],
    rng: random.Random,
):
    marks = rng.choices((0, 1, 2), weights=p, k=n)
    indeg = [0] * n
    outdeg = [0] * n
    edge_counts = {(0, 1): 0, (0, 2): 0, (1, 2): 0}
    a, b, c = w
    probs = {(0, 1): a, (1, 2): b, (0, 2): c}
    for u in range(n):
        for v in range(u + 1, n):
            i, j = marks[u], marks[v]
            if i == j:
                continue
            low, high = (i, j) if i < j else (j, i)
            if rng.random() >= probs[(low, high)]:
                continue
            source, target = (u, v) if i < j else (v, u)
            outdeg[source] += 1
            indeg[target] += 1
            edge_counts[(low, high)] += 1
    return marks, indeg, outdeg, edge_counts


def classify(indeg: list[int], outdeg: list[int]) -> list[int | None]:
    result: list[int | None] = []
    for din, dout in zip(indeg, outdeg):
        if din == 0 and dout > 0:
            result.append(0)
        elif din > 0 and dout > 0:
            result.append(1)
        elif din > 0 and dout == 0:
            result.append(2)
        else:
            result.append(None)
    return result


def simulation_checks() -> int:
    rng = random.Random(5112026)
    p = (0.27, 0.41, 0.32)
    w = (0.37, 0.61, 0.22)  # a, b, c
    checks = 0
    for n in (200, 400, 800, 1600):
        marks, indeg, outdeg, edge_counts = generate_graph(n, p, w, rng)
        recovered = classify(indeg, outdeg)
        errors = sum(r != m for r, m in zip(recovered, marks))
        # The probability of an error is exponentially small at these sizes.
        assert errors == 0
        checks += n

        counts = [marks.count(i) for i in range(3)]
        phat = [count / n for count in counts]
        ahat = edge_counts[(0, 1)] / (counts[0] * counts[1])
        bhat = edge_counts[(1, 2)] / (counts[1] * counts[2])
        chat = edge_counts[(0, 2)] / (counts[0] * counts[2])
        assert max(abs(phat[i] - p[i]) for i in range(3)) < 0.08
        assert abs(ahat - w[0]) < 0.08
        assert abs(bhat - w[1]) < 0.08
        assert abs(chat - w[2]) < 0.08
        checks += 6
    return checks



def peel_sources(
    n: int,
    edges: set[tuple[int, int]],
) -> list[int]:
    remaining = set(range(n))
    recovered = [-1] * n
    layer = 0
    while remaining:
        indeg = {v: 0 for v in remaining}
        for u, v in edges:
            if u in remaining and v in remaining:
                indeg[v] += 1
        sources = {v for v in remaining if indeg[v] == 0}
        assert sources
        for v in sources:
            recovered[v] = layer
        remaining -= sources
        layer += 1
    return recovered


def general_q_peeling_checks(trials: int = 500) -> int:
    rng = random.Random(5122026)
    checks = 0
    for _ in range(trials):
        q = rng.randint(2, 7)
        counts = [rng.randint(1, 6) for _ in range(q)]
        marks: list[int] = []
        for i, count in enumerate(counts):
            marks.extend([i] * count)
        rng.shuffle(marks)
        n = len(marks)
        edges: set[tuple[int, int]] = set()

        # Force one adjacent predecessor/successor witness for every vertex.
        by_layer = {i: [v for v, mark in enumerate(marks) if mark == i] for i in range(q)}
        for i in range(q - 1):
            left = by_layer[i]
            right = by_layer[i + 1]
            for u in left:
                v = rng.choice(right)
                edges.add((u, v))
            for v in right:
                u = rng.choice(left)
                edges.add((u, v))

        # Add arbitrary additional order-respecting edges.
        for u in range(n):
            for v in range(n):
                if marks[u] < marks[v] and rng.random() < 0.2:
                    edges.add((u, v))

        recovered = peel_sources(n, edges)
        assert recovered == marks
        checks += n
    return checks

def summability_check() -> int:
    p1, p2, p3 = 0.27, 0.41, 0.32
    a, b = 0.37, 0.61
    bases = (
        1 - p2 * a,
        1 - p1 * a,
        1 - p3 * b,
        1 - p2 * b,
    )
    total = 0.0
    for base in bases:
        assert 0 < base < 1
        # sum_{n>=1} n base^{n-1} = 1/(1-base)^2
        closed = 1.0 / (1.0 - base) ** 2
        partial = sum(n * base ** (n - 1) for n in range(1, 10000))
        assert math.isclose(partial, closed, rel_tol=1e-12, abs_tol=1e-12)
        total += closed
    assert math.isfinite(total)
    return 9


def main() -> None:
    checks = exact_inversion_checks()
    checks += simulation_checks()
    checks += general_q_peeling_checks()
    checks += summability_check()
    print(f"verified {checks:,} three-layer observability checks")


if __name__ == "__main__":
    main()
