#!/usr/bin/env python3
"""Verify projective harmonic reconstruction and predictive stability.

The script enumerates unlabeled simple DAGs through four vertices, builds exact
coherent profiles from positive terminal harmonic data, and checks the formulas
in findings-59.md and findings-61.md with fractions.
"""

from fractions import Fraction
from itertools import permutations


def is_acyclic(n, edges):
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


def graph_code(n, edges):
    edge_set = set(edges)
    return "".join(
        "1" if (source, target) in edge_set else "0"
        for source in range(n)
        for target in range(n)
        if source != target
    )


def relabel(edges, permutation):
    return {
        (permutation[source], permutation[target])
        for source, target in edges
    }


def canonical_code(n, edges):
    return min(
        graph_code(n, relabel(edges, permutation))
        for permutation in permutations(range(n))
    )


def automorphism_size(n, edges):
    original = graph_code(n, edges)
    return sum(
        graph_code(n, relabel(edges, permutation)) == original
        for permutation in permutations(range(n))
    )


def delete_vertex(n, edges, vertex):
    remaining = [item for item in range(n) if item != vertex]
    relabeling = {old: new for new, old in enumerate(remaining)}
    return {
        (relabeling[source], relabeling[target])
        for source, target in edges
        if source != vertex and target != vertex
    }


def unlabeled_classes(n):
    possible_edges = [
        (source, target)
        for source in range(n)
        for target in range(n)
        if source != target
    ]
    representatives = {}
    for mask in range(1 << len(possible_edges)):
        edges = {
            possible_edges[index]
            for index in range(len(possible_edges))
            if (mask >> index) & 1
        }
        if is_acyclic(n, edges):
            representatives.setdefault(canonical_code(n, edges), edges)
    return representatives


def build_branching(max_n):
    levels = [unlabeled_classes(n) for n in range(max_n + 1)]
    dimensions = []
    for n, level in enumerate(levels):
        dimensions.append(
            {
                code: Fraction(1 if n == 0 else 1)
                * Fraction(_factorial(n), automorphism_size(n, graph))
                for code, graph in level.items()
            }
        )

    extensions = []
    deletions = []
    for n in range(max_n):
        e_level = {}
        d_level = {}
        for g_code, graph in levels[n].items():
            aut_g = automorphism_size(n, graph)
            for h_code, successor in levels[n + 1].items():
                aut_h = automorphism_size(n + 1, successor)
                d = sum(
                    canonical_code(
                        n,
                        delete_vertex(n + 1, successor, vertex),
                    )
                    == g_code
                    for vertex in range(n + 1)
                )
                e = Fraction(d * aut_g, aut_h)
                assert e.denominator == 1
                e_level[(g_code, h_code)] = e
                d_level[(h_code, g_code)] = Fraction(d, n + 1)
        extensions.append(e_level)
        deletions.append(d_level)
    return levels, dimensions, extensions, deletions


def _factorial(n):
    value = 1
    for item in range(2, n + 1):
        value *= item
    return value


def coherent_profile(levels, dimensions, extensions, terminal_seed):
    max_n = len(levels) - 1
    h = [{} for _ in levels]
    for index, code in enumerate(sorted(levels[max_n])):
        h[max_n][code] = Fraction(terminal_seed + index + 1, 1)

    for n in range(max_n - 1, -1, -1):
        for g_code in levels[n]:
            h[n][g_code] = sum(
                extensions[n][(g_code, h_code)] * h[n + 1][h_code]
                for h_code in levels[n + 1]
            )

    root_code = next(iter(levels[0]))
    scale = h[0][root_code]
    for level in h:
        for code in level:
            level[code] /= scale

    mu = []
    for n, level in enumerate(levels):
        mu.append(
            {
                code: dimensions[n][code] * h[n][code]
                for code in level
            }
        )
    return h, mu


def total_variation(left, right):
    return Fraction(1, 2) * sum(
        abs(left[key] - right[key]) for key in left
    )


def induced_profile(top_n, top_graph, levels):
    profile = []
    for n in range(top_n + 1):
        counts = {code: 0 for code in levels[n]}
        subsets = list(_combinations(range(top_n), n))
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


def _combinations(items, size):
    if size == 0:
        yield ()
        return
    if size > len(items):
        return
    first, rest = items[0], items[1:]
    for tail in _combinations(rest, size - 1):
        yield (first,) + tail
    yield from _combinations(rest, size)


def verify_empirical_coherence(levels, deletions):
    checks = 0
    top_n = len(levels) - 1
    for top_code, top_graph in levels[top_n].items():
        profile = induced_profile(top_n, top_graph, levels)
        backward = [dict() for _ in levels]
        backward[top_n] = {
            code: Fraction(int(code == top_code), 1)
            for code in levels[top_n]
        }
        for n in range(top_n - 1, -1, -1):
            backward[n] = {
                g_code: sum(
                    backward[n + 1][h_code]
                    * deletions[n][(h_code, g_code)]
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
                    * deletions[n][(h_code, g_code)]
                    for h_code in levels[n + 1]
                )
                assert predicted == profile[n][g_code]
                if profile[n][g_code] > 0:
                    row_sum = sum(
                        deletions[n][(h_code, g_code)]
                        * profile[n + 1][h_code]
                        / profile[n][g_code]
                        for h_code in levels[n + 1]
                    )
                    assert row_sum == 1
                checks += 1
    return checks


def verify_profile(levels, dimensions, extensions, deletions, h, mu):
    for n, level in enumerate(levels):
        assert sum(mu[n].values()) == 1
        for code in level:
            assert mu[n][code] == dimensions[n][code] * h[n][code]

    for n in range(len(levels) - 1):
        for g_code in levels[n]:
            harmonic = sum(
                extensions[n][(g_code, h_code)] * h[n + 1][h_code]
                for h_code in levels[n + 1]
            )
            assert harmonic == h[n][g_code]

            coherent = sum(
                mu[n + 1][h_code] * deletions[n][(h_code, g_code)]
                for h_code in levels[n + 1]
            )
            assert coherent == mu[n][g_code]

            row = {}
            for h_code in levels[n + 1]:
                via_h = (
                    extensions[n][(g_code, h_code)]
                    * h[n + 1][h_code]
                    / h[n][g_code]
                )
                via_mu = (
                    deletions[n][(h_code, g_code)]
                    * mu[n + 1][h_code]
                    / mu[n][g_code]
                )
                assert via_h == via_mu
                row[h_code] = via_h
                assert (
                    mu[n][g_code] * via_h
                    == mu[n + 1][h_code]
                    * deletions[n][(h_code, g_code)]
                )
            assert sum(row.values()) == 1


def verify_stability(levels, deletions, mu, nu):
    checks = 0
    for n in range(len(levels) - 1):
        delta_n = total_variation(mu[n], nu[n])
        delta_next = total_variation(mu[n + 1], nu[n + 1])
        for g_code in levels[n]:
            eta = min(mu[n][g_code], nu[n][g_code])
            left_row = {}
            right_row = {}
            for h_code in levels[n + 1]:
                d = deletions[n][(h_code, g_code)]
                left_row[h_code] = d * mu[n + 1][h_code] / mu[n][g_code]
                right_row[h_code] = d * nu[n + 1][h_code] / nu[n][g_code]
            observed = total_variation(left_row, right_row)
            bound = (delta_n + delta_next) / eta
            assert observed <= bound
            checks += 1
    return checks


def main():
    levels, dimensions, extensions, deletions = build_branching(4)
    print("unlabeled class counts:", [len(level) for level in levels])

    h_a, mu_a = coherent_profile(
        levels,
        dimensions,
        extensions,
        terminal_seed=2,
    )
    h_b, mu_b = coherent_profile(
        levels,
        dimensions,
        extensions,
        terminal_seed=11,
    )

    verify_profile(levels, dimensions, extensions, deletions, h_a, mu_a)
    verify_profile(levels, dimensions, extensions, deletions, h_b, mu_b)
    checks = verify_stability(levels, deletions, mu_a, mu_b)
    empirical_checks = verify_empirical_coherence(levels, deletions)

    print("harmonic and predictive identities verified")
    print("predictive stability checks:", checks)
    print("empirical coherence checks:", empirical_checks)


if __name__ == "__main__":
    main()
