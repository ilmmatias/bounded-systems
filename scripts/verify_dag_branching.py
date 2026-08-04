#!/usr/bin/env python3
"""Exhaustively verify the DAG branching identities through four vertices.

The script uses only the Python standard library.  It enumerates all simple
labeled digraphs, filters for acyclicity, quotients by permutation isomorphism,
and checks

    e(G,H) = d(G,H) |Aut(G)| / |Aut(H)|

against direct labeled-extension counting.
"""

from __future__ import annotations

from itertools import permutations


def is_acyclic(n: int, edges: set[tuple[int, int]]) -> bool:
    adjacency = [[] for _ in range(n)]
    indegree = [0] * n
    for source, target in edges:
        adjacency[source].append(target)
        indegree[target] += 1

    stack = [vertex for vertex, degree in enumerate(indegree) if degree == 0]
    visited = 0
    while stack:
        source = stack.pop()
        visited += 1
        for target in adjacency[source]:
            indegree[target] -= 1
            if indegree[target] == 0:
                stack.append(target)
    return visited == n


def graph_code(n: int, edges: set[tuple[int, int]]) -> str:
    edge_set = set(edges)
    return "".join(
        "1" if (source, target) in edge_set else "0"
        for source in range(n)
        for target in range(n)
        if source != target
    )


def relabel(
    edges: set[tuple[int, int]], permutation: tuple[int, ...]
) -> set[tuple[int, int]]:
    return {
        (permutation[source], permutation[target])
        for source, target in edges
    }


def canonical_code(n: int, edges: set[tuple[int, int]]) -> str:
    return min(
        graph_code(n, relabel(edges, permutation))
        for permutation in permutations(range(n))
    )


def automorphism_size(n: int, edges: set[tuple[int, int]]) -> int:
    original = graph_code(n, edges)
    return sum(
        graph_code(n, relabel(edges, permutation)) == original
        for permutation in permutations(range(n))
    )


def delete_vertex(
    n: int, edges: set[tuple[int, int]], vertex: int
) -> set[tuple[int, int]]:
    remaining = [item for item in range(n) if item != vertex]
    relabeling = {old: new for new, old in enumerate(remaining)}
    return {
        (relabeling[source], relabeling[target])
        for source, target in edges
        if source != vertex and target != vertex
    }


def unlabeled_classes(n: int) -> dict[str, set[tuple[int, int]]]:
    possible_edges = [
        (source, target)
        for source in range(n)
        for target in range(n)
        if source != target
    ]
    representatives = {}
    for mask in range(1 << len(possible_edges)):
        edges = {
            possible_edges[i]
            for i in range(len(possible_edges))
            if (mask >> i) & 1
        }
        if not is_acyclic(n, edges):
            continue
        representatives.setdefault(canonical_code(n, edges), edges)
    return representatives


def main() -> None:
    levels = [unlabeled_classes(n) for n in range(5)]
    print("unlabeled class counts:", [len(level) for level in levels])

    for n in range(4):
        for graph_code_n, graph in levels[n].items():
            aut_graph = automorphism_size(n, graph)
            direct_counts = {code: 0 for code in levels[n + 1]}
            incident_edges = [
                (n, vertex) for vertex in range(n)
            ] + [
                (vertex, n) for vertex in range(n)
            ]

            for mask in range(1 << (2 * n)):
                extension = set(graph)
                for i, edge in enumerate(incident_edges):
                    if (mask >> i) & 1:
                        extension.add(edge)
                if is_acyclic(n + 1, extension):
                    direct_counts[canonical_code(n + 1, extension)] += 1

            for successor_code, successor in levels[n + 1].items():
                aut_successor = automorphism_size(n + 1, successor)
                deletion_count = sum(
                    canonical_code(
                        n,
                        delete_vertex(n + 1, successor, vertex),
                    ) == graph_code_n
                    for vertex in range(n + 1)
                )
                numerator = deletion_count * aut_graph
                assert numerator % aut_successor == 0
                predicted = numerator // aut_successor
                observed = direct_counts[successor_code]
                assert observed == predicted, (
                    n,
                    graph_code_n,
                    successor_code,
                    observed,
                    predicted,
                )

    print("all branching identities verified through n = 4")


if __name__ == "__main__":
    raise SystemExit(main())
