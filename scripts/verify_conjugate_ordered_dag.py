#!/usr/bin/env python3
"""Exact conjugate-predictive checks for findings-64.md."""

from fractions import Fraction
from itertools import product


def rising(a, n):
    out = 1
    for t in range(n):
        out *= a + t
    return out


def beta_ratio(a, b, successes, failures):
    return Fraction(rising(a, successes) * rising(b, failures), rising(a + b, successes + failures))


def sufficient(marks, edges, q):
    counts = [marks.count(i) for i in range(q)]
    ecounts = {(i, j): 0 for i in range(q) for j in range(i + 1, q)}
    for u in range(len(marks)):
        for v in range(u + 1, len(marks)):
            i, j = marks[u], marks[v]
            if i == j:
                assert (u, v) not in edges and (v, u) not in edges
                continue
            lo, hi = sorted((i, j))
            directed = (u, v) if i < j else (v, u)
            if directed in edges:
                ecounts[(lo, hi)] += 1
    return counts, ecounts


def marginal_probability(marks, edges, alpha, aprior, bprior):
    q = len(alpha)
    counts, ecounts = sufficient(marks, edges, q)
    prob = Fraction(1)
    for i, c in enumerate(counts):
        prob *= rising(alpha[i], c)
    prob /= rising(sum(alpha), len(marks))
    for i in range(q):
        for j in range(i + 1, q):
            m = counts[i] * counts[j]
            e = ecounts[(i, j)]
            prob *= beta_ratio(aprior[(i, j)], bprior[(i, j)], e, m - e)
    return prob


def extensions(marks, edges, alpha, aprior, bprior):
    q = len(alpha)
    n = len(marks)
    counts, ecounts = sufficient(marks, edges, q)
    alpha0 = sum(alpha)
    for k in range(q):
        old_vertices = [u for u, mark in enumerate(marks) if mark != k]
        for bits in product((0, 1), repeat=len(old_vertices)):
            new_edges = set(edges)
            successes = {(min(k, i), max(k, i)): 0 for i in range(q) if i != k}
            totals = {(min(k, i), max(k, i)): 0 for i in range(q) if i != k}
            for u, present in zip(old_vertices, bits):
                i = marks[u]
                block = (min(i, k), max(i, k))
                totals[block] += 1
                if present:
                    successes[block] += 1
                    if i < k:
                        new_edges.add((u, n))
                    else:
                        new_edges.add((n, u))
            pred = Fraction(alpha[k] + counts[k], alpha0 + n)
            for block, m in totals.items():
                i, j = block
                old_m = counts[i] * counts[j]
                old_e = ecounts[block]
                A = aprior[block] + old_e
                B = bprior[block] + old_m - old_e
                s = successes[block]
                pred *= beta_ratio(A, B, s, m - s)
            yield k, bits, new_edges, pred


def all_marked_states(q, n):
    for marks in product(range(q), repeat=n):
        possible = []
        for u in range(n):
            for v in range(u + 1, n):
                if marks[u] == marks[v]:
                    continue
                possible.append((u, v) if marks[u] < marks[v] else (v, u))
        for bits in product((0, 1), repeat=len(possible)):
            edges = {edge for edge, present in zip(possible, bits) if present}
            yield list(marks), edges


def run_case(q, n):
    alpha = [2 + i for i in range(q)]
    aprior = {(i, j): 2 + i + j for i in range(q) for j in range(i + 1, q)}
    bprior = {(i, j): 3 + 2 * i + j for i in range(q) for j in range(i + 1, q)}
    checked = 0
    for marks, edges in all_marked_states(q, n):
        current = marginal_probability(marks, edges, alpha, aprior, bprior)
        total = Fraction(0)
        for k, bits, new_edges, pred in extensions(marks, edges, alpha, aprior, bprior):
            total += pred
            extended_marks = marks + [k]
            extended = marginal_probability(extended_marks, new_edges, alpha, aprior, bprior)
            assert current * pred == extended
            checked += 1
        assert total == 1
    return checked


def main():
    checked = 0
    checked += run_case(2, 3)
    checked += run_case(3, 2)
    print(f"verified {checked} exact conjugate one-node extensions")


if __name__ == "__main__":
    main()
