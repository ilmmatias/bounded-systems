#!/usr/bin/env python3
"""Verify projective harmonic reconstruction and predictive stability.

The script enumerates unlabeled simple DAGs through four vertices, builds exact
coherent profiles from positive terminal harmonic data, and checks the formulas
in findings-59.md and findings-61.md with fractions.
"""

from __future__ import annotations

from collections.abc import Iterator, Mapping, Sequence
from fractions import Fraction
from itertools import permutations
from typing import NamedTuple

Edge = tuple[int, int]
EdgeSet = set[Edge]
Level = dict[str, EdgeSet]
Weights = dict[str, Fraction]
Transitions = dict[tuple[str, str], Fraction]


class Branching(NamedTuple):
    levels: list[Level]
    dimensions: list[Weights]
    extensions: list[Transitions]
    deletions: list[Transitions]


class CoherentProfile(NamedTuple):
    harmonic: list[Weights]
    laws: list[Weights]


def is_acyclic(n: int, edges: EdgeSet) -> bool:
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


def graph_code(n: int, edges: EdgeSet) -> str:
    return "".join(
        "1" if (source, target) in edges else "0"
        for source in range(n)
        for target in range(n)
        if source != target
    )


def relabel(edges: EdgeSet, permutation: tuple[int, ...]) -> EdgeSet:
    return {
        (permutation[source], permutation[target])
        for source, target in edges
    }


def canonical_code(n: int, edges: EdgeSet) -> str:
    return min(
        graph_code(n, relabel(edges, permutation))
        for permutation in permutations(range(n))
    )


def automorphism_size(n: int, edges: EdgeSet) -> int:
    original = graph_code(n, edges)
    return sum(
        graph_code(n, relabel(edges, permutation)) == original
        for permutation in permutations(range(n))
    )


def delete_vertex(n: int, edges: EdgeSet, vertex: int) -> EdgeSet:
    remaining = [item for item in range(n) if item != vertex]
    relabeling = {old: new for new, old in enumerate(remaining)}
    return {
        (relabeling[source], relabeling[target])
        for source, target in edges
        if source != vertex and target != vertex
    }


def unlabeled_classes(n: int) -> Level:
    possible_edges = [
        (source, target)
        for source in range(n)
        for target in range(n)
        if source != target
    ]
    representatives: Level = {}

    for mask in range(1 << len(possible_edges)):
        edges = {
            possible_edges[i]
            for i in range(len(possible_edges))
            if (mask >> i) & 1
        }

        if is_acyclic(n, edges):
            representatives.setdefault(canonical_code(n, edges), edges)

    return representatives


def factorial(n: int) -> int:
    value = 1

    for item in range(2, n + 1):
        value *= item

    return value


def build_branching(max_n: int) -> Branching:
    levels = [unlabeled_classes(n) for n in range(max_n + 1)]
    dimensions: list[Weights] = []

    for n, level in enumerate(levels):
        dimensions.append(
            {
                code: Fraction(factorial(n), automorphism_size(n, graph))
                for code, graph in level.items()
            }
        )

    extensions: list[Transitions] = []
    deletions: list[Transitions] = []

    for n in range(max_n):
        extension: Transitions = {}
        deletion: Transitions = {}

        for g_code, graph in levels[n].items():
            aut_g = automorphism_size(n, graph)

            for h_code, successor in levels[n + 1].items():
                aut_h = automorphism_size(n + 1, successor)
                deleted = sum(
                    canonical_code(
                        n, delete_vertex(n + 1, successor, vertex)
                    )
                    == g_code
                    for vertex in range(n + 1)
                )
                extended = Fraction(deleted * aut_g, aut_h)

                assert extended.denominator == 1

                extension[(g_code, h_code)] = extended
                deletion[(h_code, g_code)] = Fraction(deleted, n + 1)

        extensions.append(extension)
        deletions.append(deletion)

    return Branching(levels, dimensions, extensions, deletions)


def coherent_profile(branching: Branching, terminal_seed: int) -> CoherentProfile:
    levels = branching.levels
    max_n = len(levels) - 1
    harmonic: list[Weights] = [{} for _ in levels]

    for i, code in enumerate(sorted(levels[max_n])):
        harmonic[max_n][code] = Fraction(terminal_seed + i + 1, 1)

    for n in range(max_n - 1, -1, -1):
        for g_code in levels[n]:
            harmonic[n][g_code] = sum(
                branching.extensions[n][(g_code, h_code)]
                * harmonic[n + 1][h_code]
                for h_code in levels[n + 1]
            )

    root_code = next(iter(levels[0]))
    scale = harmonic[0][root_code]

    for level in harmonic:
        for code in level:
            level[code] /= scale

    laws = [
        {
            code: branching.dimensions[n][code] * harmonic[n][code]
            for code in level
        }
        for n, level in enumerate(levels)
    ]

    return CoherentProfile(harmonic, laws)


def total_variation(
    left: Mapping[str, Fraction], right: Mapping[str, Fraction]
) -> Fraction:
    return Fraction(1, 2) * sum(abs(left[key] - right[key]) for key in left)


def combinations(items: Sequence[int], size: int) -> Iterator[tuple[int, ...]]:
    if size == 0:
        yield ()
        return

    if size > len(items):
        return

    first, rest = items[0], items[1:]

    for tail in combinations(rest, size - 1):
        yield (first,) + tail

    yield from combinations(rest, size)


def induced_profile(
    top_n: int, top_graph: EdgeSet, levels: Sequence[Level]
) -> list[Weights]:
    profile: list[Weights] = []

    for n in range(top_n + 1):
        counts = {code: 0 for code in levels[n]}
        subsets = list(combinations(tuple(range(top_n)), n))

        for subset in subsets:
            relabeling = {old: new for new, old in enumerate(subset)}
            edges = {
                (relabeling[source], relabeling[target])
                for source, target in top_graph
                if source in relabeling and target in relabeling
            }
            counts[canonical_code(n, edges)] += 1

        total = len(subsets)
        profile.append(
            {code: Fraction(count, total) for code, count in counts.items()}
        )

    return profile


def verify_empirical_coherence(branching: Branching) -> int:
    levels = branching.levels
    checks = 0
    top_n = len(levels) - 1

    for top_code, top_graph in levels[top_n].items():
        profile = induced_profile(top_n, top_graph, levels)
        backward: list[Weights] = [dict() for _ in levels]
        backward[top_n] = {
            code: Fraction(int(code == top_code), 1) for code in levels[top_n]
        }

        for n in range(top_n - 1, -1, -1):
            backward[n] = {
                g_code: sum(
                    backward[n + 1][h_code]
                    * branching.deletions[n][(h_code, g_code)]
                    for h_code in levels[n + 1]
                )
                for g_code in levels[n]
            }

        for n in range(top_n + 1):
            assert backward[n] == profile[n]

        for n in range(top_n):
            for g_code in levels[n]:
                predicted = sum(
                    profile[n + 1][h_code]
                    * branching.deletions[n][(h_code, g_code)]
                    for h_code in levels[n + 1]
                )

                assert predicted == profile[n][g_code]

                if profile[n][g_code] > 0:
                    row_sum = sum(
                        branching.deletions[n][(h_code, g_code)]
                        * profile[n + 1][h_code]
                        / profile[n][g_code]
                        for h_code in levels[n + 1]
                    )
                    assert row_sum == 1

                checks += 1

    return checks


def verify_profile(branching: Branching, profile: CoherentProfile) -> None:
    levels = branching.levels
    harmonic = profile.harmonic
    laws = profile.laws

    for n, level in enumerate(levels):
        assert sum(laws[n].values()) == 1

        for code in level:
            assert laws[n][code] == branching.dimensions[n][code] * harmonic[n][code]

    for n in range(len(levels) - 1):
        for g_code in levels[n]:
            harmonic_sum = sum(
                branching.extensions[n][(g_code, h_code)]
                * harmonic[n + 1][h_code]
                for h_code in levels[n + 1]
            )

            assert harmonic_sum == harmonic[n][g_code]

            coherent = sum(
                laws[n + 1][h_code]
                * branching.deletions[n][(h_code, g_code)]
                for h_code in levels[n + 1]
            )

            assert coherent == laws[n][g_code]

            row: Weights = {}

            for h_code in levels[n + 1]:
                via_h = (
                    branching.extensions[n][(g_code, h_code)]
                    * harmonic[n + 1][h_code]
                    / harmonic[n][g_code]
                )
                via_mu = (
                    branching.deletions[n][(h_code, g_code)]
                    * laws[n + 1][h_code]
                    / laws[n][g_code]
                )

                assert via_h == via_mu

                row[h_code] = via_h

                assert laws[n][g_code] * via_h == (
                    laws[n + 1][h_code]
                    * branching.deletions[n][(h_code, g_code)]
                )

            assert sum(row.values()) == 1


def verify_stability(
    branching: Branching, left: Sequence[Weights], right: Sequence[Weights]
) -> int:
    levels = branching.levels
    checks = 0

    for n in range(len(levels) - 1):
        delta_n = total_variation(left[n], right[n])
        delta_next = total_variation(left[n + 1], right[n + 1])

        for g_code in levels[n]:
            eta = min(left[n][g_code], right[n][g_code])
            left_row: Weights = {}
            right_row: Weights = {}

            for h_code in levels[n + 1]:
                deletion = branching.deletions[n][(h_code, g_code)]
                left_row[h_code] = (
                    deletion * left[n + 1][h_code] / left[n][g_code]
                )
                right_row[h_code] = (
                    deletion * right[n + 1][h_code] / right[n][g_code]
                )

            observed = total_variation(left_row, right_row)
            bound = (delta_n + delta_next) / eta

            assert observed <= bound
            checks += 1

    return checks


def main() -> None:
    branching = build_branching(4)
    print(
        "unlabeled class counts:",
        [len(level) for level in branching.levels],
    )

    profile_a = coherent_profile(branching, terminal_seed=2)
    profile_b = coherent_profile(branching, terminal_seed=11)

    verify_profile(branching, profile_a)
    verify_profile(branching, profile_b)
    stability_checks = verify_stability(
        branching, profile_a.laws, profile_b.laws
    )
    empirical_checks = verify_empirical_coherence(branching)

    print("harmonic and predictive identities verified")
    print("predictive stability checks:", stability_checks)
    print("empirical coherence checks:", empirical_checks)


if __name__ == "__main__":
    raise SystemExit(main())
