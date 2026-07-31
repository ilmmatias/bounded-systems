#!/usr/bin/env python3
"""Exact diagnostics for findings-72 through findings-74."""

from __future__ import annotations

from fractions import Fraction
from itertools import product

import sympy as sp


def hom_density(pattern_vertices, pattern_edges, target_vertices, target_edges):
    edge_set = set(target_edges)
    good = 0
    total = target_vertices ** pattern_vertices
    for mapping in product(range(target_vertices), repeat=pattern_vertices):
        if all((mapping[source], mapping[target]) in edge_set for source, target in pattern_edges):
            good += 1
    return Fraction(good, total)


def disjoint_union(left_vertices, left_edges, right_vertices, right_edges):
    shifted = [(source + left_vertices, target + left_vertices) for source, target in right_edges]
    return left_vertices + right_vertices, tuple(left_edges) + tuple(shifted)


def verify_endpoint_multiplicativity():
    target_edges = ((0, 1), (0, 2), (1, 2))
    edge = (2, ((0, 1),))
    path = (3, ((0, 1), (1, 2)))
    union = disjoint_union(*edge, *path)
    edge_density = hom_density(*edge, 3, target_edges)
    path_density = hom_density(*path, 3, target_edges)
    union_density = hom_density(*union, 3, target_edges)
    assert union_density == edge_density * path_density
    return 1


def verify_finite_phase_weights():
    theta = Fraction(1, 2)
    r1 = Fraction(1, 3)
    r2 = Fraction(2, 3)
    lam = Fraction(2, 5)

    edge1 = 2 * theta * (1 - theta) * r1
    edge2 = 2 * theta * (1 - theta) * r2
    mean_edge = lam * edge1 + (1 - lam) * edge2
    recovered = (edge2 - mean_edge) / (edge2 - edge1)
    assert recovered == lam

    second = lam * edge1**2 + (1 - lam) * edge2**2
    assert second - mean_edge**2 == lam * (1 - lam) * (edge1 - edge2) ** 2
    assert second > mean_edge**2

    # A support polynomial vanishes exactly on the two phase values.
    for value in (r1, r2):
        assert (value - r1) ** 2 * (value - r2) ** 2 == 0
    assert (Fraction(1, 2) - r1) ** 2 * (Fraction(1, 2) - r2) ** 2 > 0
    return 5


def verify_richter_quadrature_example():
    # The uniform law on [0,1] and its two-node Gauss rule have identical
    # moments through degree three, while one is diffuse and one is atomic.
    x = sp.symbols("x")
    nodes = (sp.Rational(1, 2) - sp.sqrt(3) / 6, sp.Rational(1, 2) + sp.sqrt(3) / 6)
    for degree in range(4):
        uniform = sp.integrate(x**degree, (x, 0, 1))
        atomic = sum(node**degree for node in nodes) / 2
        assert sp.simplify(uniform - atomic) == 0
    fourth_uniform = sp.integrate(x**4, (x, 0, 1))
    fourth_atomic = sum(node**4 for node in nodes) / 2
    assert sp.simplify(fourth_uniform - fourth_atomic) != 0
    return 5


def verify_adaptive_transition():
    lam = (Fraction(2, 5), Fraction(3, 5))
    mu_n = (Fraction(1, 3), Fraction(2, 3))
    successors = (
        (Fraction(1, 9), Fraction(2, 9)),
        (Fraction(1, 2), Fraction(1, 6)),
    )
    phase_up = tuple(
        tuple(value / mu_n[a] for value in successors[a])
        for a in range(2)
    )
    mixture_mass = sum(lam[a] * mu_n[a] for a in range(2))
    posterior = tuple(lam[a] * mu_n[a] / mixture_mass for a in range(2))
    mixture_successors = tuple(
        sum(lam[a] * successors[a][h] for a in range(2))
        for h in range(2)
    )
    reconstructed = tuple(value / mixture_mass for value in mixture_successors)
    adaptive = tuple(
        sum(posterior[a] * phase_up[a][h] for a in range(2))
        for h in range(2)
    )
    assert posterior == (Fraction(1, 4), Fraction(3, 4))
    assert adaptive == reconstructed
    assert sum(adaptive) == 1
    return 3


def verify_calibrated_multiwell():
    dimensions = (Fraction(1), Fraction(3), Fraction(2))
    raw_phase = (
        (Fraction(1, 2), Fraction(1, 4), Fraction(1, 8)),
        (Fraction(1, 5), Fraction(2, 5), Fraction(1, 10)),
    )
    lam = (Fraction(2, 7), Fraction(5, 7))
    partition = tuple(
        sum(dimensions[k] * raw_phase[a][k] for k in range(3))
        for a in range(2)
    )
    phase_laws = tuple(
        tuple(dimensions[k] * raw_phase[a][k] / partition[a] for k in range(3))
        for a in range(2)
    )
    mixed_weight = tuple(
        sum(lam[a] * raw_phase[a][k] / partition[a] for a in range(2))
        for k in range(3)
    )
    endpoint_law = tuple(dimensions[k] * mixed_weight[k] for k in range(3))
    expected = tuple(
        sum(lam[a] * phase_laws[a][k] for a in range(2))
        for k in range(3)
    )
    assert sum(endpoint_law) == 1
    assert endpoint_law == expected

    lower_statistic = (Fraction(0), Fraction(1, 2), Fraction(1))
    mixed_lower = sum(endpoint_law[k] * lower_statistic[k] for k in range(3))
    phase_lower = tuple(
        sum(phase_laws[a][k] * lower_statistic[k] for k in range(3))
        for a in range(2)
    )
    assert mixed_lower == sum(lam[a] * phase_lower[a] for a in range(2))
    return 3


def main():
    checks = 0
    checks += verify_endpoint_multiplicativity()
    checks += verify_finite_phase_weights()
    checks += verify_richter_quadrature_example()
    checks += verify_adaptive_transition()
    checks += verify_calibrated_multiwell()
    print(f"verified {checks} exact finite-phase and endpoint-selection checks")


if __name__ == "__main__":
    main()
