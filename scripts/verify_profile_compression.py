#!/usr/bin/env python3
"""Verify an explicit finite-profile collision in ordered block DAG sectors."""

from __future__ import annotations

from collections.abc import Mapping, Sequence
from fractions import Fraction
from itertools import product

Edge = tuple[int, int]
EdgeWeights = Mapping[Edge, Fraction]


def edge_density(p: Sequence[Fraction], w: EdgeWeights) -> Fraction:
    return 2 * sum(
        p[i] * p[j] * w[(i, j)]
        for i in range(len(p))
        for j in range(i + 1, len(p))
    )


def route_density_three_layers(
    p: Sequence[Fraction], w: EdgeWeights
) -> Fraction:
    return 6 * p[0] * p[1] * p[2] * w[(0, 1)] * w[(1, 2)]


def induced_code(
    layers: Sequence[int], edge_bits: Sequence[int]
) -> str:
    n = len(layers)
    code: list[str] = []
    bit = 0

    for source in range(n):
        for target in range(n):
            if source == target:
                continue

            if layers[source] < layers[target]:
                code.append(str(edge_bits[bit]))
                bit += 1
            else:
                code.append("0")

    return "".join(code)


def three_vertex_distribution(
    p: Sequence[Fraction], w: EdgeWeights
) -> dict[str, Fraction]:
    distribution: dict[str, Fraction] = {}

    for layers in product(range(len(p)), repeat=3):
        layer_weight = p[layers[0]] * p[layers[1]] * p[layers[2]]
        possible = [
            (source, target)
            for source in range(3)
            for target in range(3)
            if source != target and layers[source] < layers[target]
        ]

        for bits in product((0, 1), repeat=len(possible)):
            probability = layer_weight

            for present, edge in zip(bits, possible, strict=True):
                value = w[(layers[edge[0]], layers[edge[1]])]
                probability *= value if present else 1 - value

            code = induced_code(layers, bits)
            distribution[code] = (
                distribution.get(code, Fraction(0)) + probability
            )

    return distribution


def main() -> None:
    p = [Fraction(1, 3)] * 3
    w_a = {
        (0, 1): Fraction(1, 2),
        (0, 2): Fraction(1, 2),
        (1, 2): Fraction(1, 2),
    }
    w_b = {
        (0, 1): Fraction(1, 4),
        (0, 2): Fraction(3, 4),
        (1, 2): Fraction(1, 2),
    }

    assert edge_density(p, w_a) == Fraction(1, 3)
    assert edge_density(p, w_b) == Fraction(1, 3)
    assert route_density_three_layers(p, w_a) == Fraction(1, 18)
    assert route_density_three_layers(p, w_b) == Fraction(1, 36)

    dist_a = three_vertex_distribution(p, w_a)
    dist_b = three_vertex_distribution(p, w_b)

    assert sum(dist_a.values()) == 1
    assert sum(dist_b.values()) == 1
    assert dist_a != dist_b

    print("edge density collision:", edge_density(p, w_a))
    print(
        "route densities:",
        route_density_three_layers(p, w_a),
        route_density_three_layers(p, w_b),
    )
    print(
        "three-vertex labeled outcomes checked:",
        len(set(dist_a) | set(dist_b)),
    )


if __name__ == "__main__":
    raise SystemExit(main())
