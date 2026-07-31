#!/usr/bin/env python3
"""Exact checks for findings-63.md."""

from fractions import Fraction
from itertools import product, permutations


def canonical_digraph(edges, n):
    """Canonical directed adjacency bit tuple under vertex permutations."""
    reps = []
    for perm in permutations(range(n)):
        bits = []
        for i in range(n):
            for j in range(n):
                if i != j:
                    bits.append(1 if (perm[i], perm[j]) in edges else 0)
        reps.append(tuple(bits))
    return min(reps)


def profile_three(theta, r):
    probs = {}
    n = 3
    for marks in product((1, 2), repeat=n):
        mark_prob = Fraction(1)
        for mark in marks:
            mark_prob *= theta if mark == 1 else 1 - theta
        possible = []
        for i in range(n):
            for j in range(i + 1, n):
                if marks[i] == marks[j]:
                    continue
                if marks[i] == 1:
                    possible.append((i, j))
                else:
                    possible.append((j, i))
        for outcomes in product((0, 1), repeat=len(possible)):
            edges = set()
            edge_prob = Fraction(1)
            for edge, present in zip(possible, outcomes):
                edge_prob *= r if present else 1 - r
                if present:
                    edges.add(edge)
            key = canonical_digraph(edges, n)
            probs[key] = probs.get(key, Fraction(0)) + mark_prob * edge_prob
    return probs


def main():
    checked = 0
    for theta in (Fraction(1, 5), Fraction(1, 3), Fraction(2, 5), Fraction(3, 5), Fraction(4, 5)):
        for r in (Fraction(1, 7), Fraction(2, 5), Fraction(3, 4)):
            edge = 2 * theta * (1 - theta) * r
            out_star = 3 * theta * (1 - theta) ** 2 * r ** 2
            in_star = 3 * theta ** 2 * (1 - theta) * r ** 2
            recovered_theta = in_star / (in_star + out_star)
            recovered_r = edge / (2 * recovered_theta * (1 - recovered_theta))
            assert recovered_theta == theta
            assert recovered_r == r

            probs = profile_three(theta, r)
            assert sum(probs.values(), Fraction(0)) == 1

            out_edges = {(0, 1), (0, 2)}
            in_edges = {(1, 0), (2, 0)}
            assert probs[canonical_digraph(out_edges, 3)] == out_star
            assert probs[canonical_digraph(in_edges, 3)] == in_star
            checked += 1

    print(f"verified {checked} exact two-layer finite-selection parameter pairs")


if __name__ == "__main__":
    main()
