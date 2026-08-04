#!/usr/bin/env python3
"""Combinatorial and exact integral checks for findings-90.md and findings-91.md."""

from __future__ import annotations

from itertools import combinations

import sympy as sp


def is_forest(vertex_count: int, edges: tuple[tuple[int, int], ...]) -> bool:
    parent = list(range(vertex_count))

    def find(a: int) -> int:
        while parent[a] != a:
            parent[a] = parent[parent[a]]
            a = parent[a]
        return a

    for u, v in edges:
        ru, rv = find(u), find(v)
        if ru == rv:
            return False
        parent[ru] = rv
    return True


def is_even_subset(
    vertex_count: int,
    edges: tuple[tuple[int, int], ...],
    mask: int,
) -> bool:
    degree = [0] * vertex_count
    for i, (u, v) in enumerate(edges):
        if mask & (1 << i):
            degree[u] += 1
            degree[v] += 1
    return all(value % 2 == 0 for value in degree)


def main() -> None:
    checks = 0
    forest_count = 0

    for vertex_count in range(1, 7):
        possible = tuple(combinations(range(vertex_count), 2))
        for graph_mask in range(1 << len(possible)):
            edges = tuple(
                edge
                for i, edge in enumerate(possible)
                if graph_mask & (1 << i)
            )
            if not is_forest(vertex_count, edges):
                continue
            forest_count += 1
            for subset_mask in range(1, 1 << len(edges)):
                assert not is_even_subset(vertex_count, edges, subset_mask)
                checks += 1

    triangle = ((0, 1), (0, 2), (1, 2))
    even_triangle = [
        mask for mask in range(1 << 3) if is_even_subset(3, triangle, mask)
    ]
    assert even_triangle == [0, 7]
    checks += 1

    four_cycle = ((0, 2), (0, 3), (1, 2), (1, 3))
    even_four_cycle = [
        mask
        for mask in range(1 << 4)
        if is_even_subset(4, four_cycle, mask)
    ]
    assert even_four_cycle == [0, 15]
    checks += 1

    x, y, z = sp.symbols("x y z", nonnegative=True)

    def h(a: sp.Expr, b: sp.Expr) -> sp.Expr:
        return a**2 * (1 - b) ** 2 * (b - a) ** 2

    base_triangle = sp.integrate(
        sp.integrate(
            sp.integrate((y - x) * (z - x) * (z - y), (x, 0, y)),
            (y, 0, z),
        ),
        (z, 0, 1),
    )
    assert sp.simplify(base_triangle) == sp.Rational(1, 180)
    checks += 1

    i3 = sp.integrate(
        sp.integrate(
            sp.integrate(sp.expand(h(x, y) * h(x, z) * h(y, z)), (x, 0, y)),
            (y, 0, z),
        ),
        (z, 0, 1),
    )
    assert sp.simplify(i3) == sp.Rational(311, 20_532_303_792_000)
    checks += 1

    x1, x2, yy = sp.symbols("x1 x2 yy", nonnegative=True)
    gram_a = sp.integrate((yy - x1) * (yy - x2), (yy, x2, 1))
    base_four = 2 * sp.integrate(
        sp.integrate(sp.expand(gram_a**2), (x1, 0, x2)),
        (x2, 0, 1),
    )
    assert sp.simplify(base_four) == sp.Rational(11, 1680)
    checks += 1

    gram_h = sp.integrate(sp.expand(h(x1, yy) * h(x2, yy)), (yy, x2, 1))
    i4 = 2 * sp.integrate(
        sp.integrate(sp.expand(gram_h**2), (x1, 0, x2)),
        (x2, 0, 1),
    )
    assert sp.simplify(i4) == sp.Rational(13, 624_153_318_768_000)
    checks += 1

    print(
        f"verified {checks} signed-lift checks across {forest_count} undirected forests"
    )


if __name__ == "__main__":
    raise SystemExit(main())
