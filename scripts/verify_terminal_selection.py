#!/usr/bin/env python3
"""Finite Gibbs endpoint diagnostics for findings-68."""

from __future__ import annotations

from collections import defaultdict
from collections.abc import Iterator, Sequence
from itertools import combinations, permutations, product
from math import exp

Adjacency = tuple[tuple[int, ...], ...]
GraphCode = tuple[int, ...]


def is_acyclic(adj: Adjacency) -> bool:
    n = len(adj)
    indegree = [0] * n

    for u in range(n):
        for v in range(n):
            indegree[v] += adj[u][v]

    stack = [i for i, degree in enumerate(indegree) if degree == 0]
    seen = 0

    while stack:
        u = stack.pop()
        seen += 1

        for v in range(n):
            if not adj[u][v]:
                continue

            indegree[v] -= 1

            if indegree[v] == 0:
                stack.append(v)

    return seen == n


def enumerate_labeled_dags(n: int) -> Iterator[Adjacency]:
    pairs = list(combinations(range(n), 2))

    for states in product((0, 1, 2), repeat=len(pairs)):
        adj = [[0] * n for _ in range(n)]

        for (u, v), state in zip(pairs, states, strict=True):
            if state == 1:
                adj[u][v] = 1
            elif state == 2:
                adj[v][u] = 1

        frozen = tuple(tuple(row) for row in adj)

        if is_acyclic(frozen):
            yield frozen


def induced_subgraph(adj: Adjacency, vertices: Sequence[int]) -> Adjacency:
    return tuple(tuple(adj[u][v] for v in vertices) for u in vertices)


def canonical_key(adj: Adjacency) -> GraphCode:
    n = len(adj)
    best: GraphCode | None = None

    for perm in permutations(range(n)):
        bits = tuple(
            adj[perm[i]][perm[j]] for i in range(n) for j in range(n)
        )

        if best is None or bits < best:
            best = bits

    assert best is not None
    return best


def forbidden_densities(adj: Adjacency) -> tuple[float, float]:
    n = len(adj)

    if n < 3:
        return 0.0, 0.0

    one_edge = 0
    open_path = 0
    total = 0

    for vertices in combinations(range(n), 3):
        sub = induced_subgraph(adj, vertices)
        edges = [(i, j) for i in range(3) for j in range(3) if sub[i][j]]
        total += 1

        if len(edges) == 1:
            one_edge += 1

        if len(edges) == 2:
            indegree = [sum(sub[i][j] for i in range(3)) for j in range(3)]
            outdegree = [sum(sub[i][j] for j in range(3)) for i in range(3)]

            if sorted(indegree) == [0, 1, 1] and sorted(outdegree) == [0, 1, 1]:
                open_path += 1

    return one_edge / total, open_path / total


def degree_polynomial_energy(adj: Adjacency) -> float:
    n = len(adj)

    if n <= 1:
        return 0.0

    total = 0.0

    for v in range(n):
        incoming = sum(adj[u][v] for u in range(n)) / (n - 1)
        outgoing = sum(adj[v][u] for u in range(n)) / (n - 1)
        q = (incoming**2 + (outgoing - 0.5) ** 2) * (
            (incoming - 0.5) ** 2 + outgoing**2
        )
        total += q

    return total / n


def energy(adj: Adjacency) -> float:
    one_edge, open_path = forbidden_densities(adj)
    return one_edge**2 + open_path**2 + degree_polynomial_energy(adj) ** 2


def edge_density(adj: Adjacency) -> float:
    n = len(adj)
    return sum(sum(row) for row in adj) / (n * (n - 1) / 2)


def level_profile(adj: Adjacency, level: int) -> dict[GraphCode, float]:
    counts: defaultdict[GraphCode, int] = defaultdict(int)
    total = 0

    for vertices in combinations(range(len(adj)), level):
        counts[canonical_key(induced_subgraph(adj, vertices))] += 1
        total += 1

    return {key: value / total for key, value in counts.items()}


def main() -> None:
    n = 5
    dags = list(enumerate_labeled_dags(n))
    energies = [energy(adj) for adj in dags]
    min_energy = min(energies)
    minimizers = [
        i for i, value in enumerate(energies) if abs(value - min_energy) < 1e-15
    ]

    print(
        f"n={n}: labeled DAGs={len(dags)}, minimum_energy={min_energy:.12g}, "
        f"minimizers={len(minimizers)}"
    )

    prev_mass = -1.0

    for beta in (0.0, 10.0, 100.0, 1000.0, 10000.0):
        weights = [exp(-beta * (value - min_energy)) for value in energies]
        z = sum(weights)
        min_mass = sum(weights[i] for i in minimizers) / z
        mean_edge = sum(
            weight * edge_density(adj)
            for weight, adj in zip(weights, dags, strict=True)
        ) / z

        assert min_mass + 1e-14 >= prev_mass
        prev_mass = min_mass

        print(
            f"beta={beta:7.1f}: minimizer_mass={min_mass:.12f}, "
            f"mean_edge_density={mean_edge:.9f}"
        )

    assert prev_mass > 0.999

    # Endpoint mixtures of induced profiles are normalized coherent marginals.
    beta = 10000.0
    weights = [exp(-beta * (value - min_energy)) for value in energies]
    z = sum(weights)

    for level in (1, 2, 3):
        mixture: defaultdict[GraphCode, float] = defaultdict(float)

        for weight, adj in zip(weights, dags, strict=True):
            for key, probability in level_profile(adj, level).items():
                mixture[key] += weight * probability / z

        mass = sum(mixture.values())

        assert abs(mass - 1.0) < 1e-12
        print(
            f"level={level}: endpoint-bridge classes={len(mixture)}, "
            f"mass={mass:.12f}"
        )

    print("verified finite Gibbs concentration and bridge normalization")


if __name__ == "__main__":
    raise SystemExit(main())
