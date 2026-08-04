#!/usr/bin/env python3
"""Exact diagnostics for findings-70 and findings-71."""

from __future__ import annotations

from collections.abc import Sequence
from fractions import Fraction
from typing import NamedTuple

Signature = tuple[Fraction, ...]
Matrix = list[list[Fraction]]


class ForcingTerms(NamedTuple):
    signature: Fraction
    mass: Fraction
    wrong_direction: Fraction
    row: Fraction
    column: Fraction
    c4: Fraction


def distance_squared(
    left: Sequence[Fraction], right: Sequence[Fraction]
) -> Fraction:
    return sum((x - y) ** 2 for x, y in zip(left, right))


def target_signatures(
    p: Sequence[Fraction], w: Sequence[Sequence[Fraction]]
) -> list[Signature]:
    q = len(p)
    incoming = [[Fraction(1)] + [Fraction(0)] * (q - 1) for _ in range(q)]
    outgoing = [[Fraction(1)] + [Fraction(0)] * (q - 1) for _ in range(q)]
    for length in range(1, q):
        for i in range(q):
            incoming[i][length] = sum(
                p[j] * w[j][i] * incoming[j][length - 1]
                for j in range(i)
            )

        for i in range(q - 1, -1, -1):
            outgoing[i][length] = sum(
                p[j] * w[i][j] * outgoing[j][length - 1]
                for j in range(i + 1, q)
            )
    return [
        tuple(incoming[i][1:] + outgoing[i][1:])
        for i in range(q)
    ]


def micro_signatures(
    masses: Sequence[Fraction],
    kernel: Sequence[Sequence[Fraction]],
    max_length: int,
) -> list[Signature]:
    count = len(masses)
    incoming = [[Fraction(1)] + [Fraction(0)] * max_length for _ in range(count)]
    outgoing = [[Fraction(1)] + [Fraction(0)] * max_length for _ in range(count)]
    for length in range(1, max_length + 1):
        for i in range(count):
            incoming[i][length] = sum(
                masses[j] * kernel[j][i] * incoming[j][length - 1]
                for j in range(count)
            )

        for i in range(count):
            outgoing[i][length] = sum(
                masses[j] * kernel[i][j] * outgoing[j][length - 1]
                for j in range(count)
            )
    return [
        tuple(incoming[i][1:] + outgoing[i][1:])
        for i in range(count)
    ]


def q_polynomial(
    signature: Signature, targets: Sequence[Signature]
) -> Fraction:
    value = Fraction(1)
    for target in targets:
        value *= distance_squared(signature, target)
    return value


def lagrange_value(
    signature: Signature, targets: Sequence[Signature], i: int
) -> Fraction:
    numerator = Fraction(1)
    denominator = Fraction(1)
    for j, target in enumerate(targets):
        if j == i:
            continue
        numerator *= distance_squared(signature, target)
        denominator *= distance_squared(targets[i], target)
    return numerator / denominator


def refined_target(
    p: Sequence[Fraction], w: Sequence[Sequence[Fraction]]
) -> tuple[list[Fraction], list[int], Matrix]:
    masses = []
    layers = []
    for layer, mass in enumerate(p):
        masses.extend((mass / 2, mass / 2))
        layers.extend((layer, layer))
    count = len(masses)
    kernel = [[Fraction(0) for _ in range(count)] for _ in range(count)]
    for source in range(count):
        for target in range(count):
            i = layers[source]
            j = layers[target]
            if i < j:
                kernel[source][target] = w[i][j]
    return masses, layers, kernel


def block_c4(
    masses: Sequence[Fraction],
    kernel: Sequence[Sequence[Fraction]],
    indicators: Sequence[Sequence[Fraction]],
    i: int,
    j: int,
) -> Fraction:
    count = len(masses)
    total = Fraction(0)
    for x1 in range(count):
        for x2 in range(count):
            for y1 in range(count):
                for y2 in range(count):
                    total += (
                        masses[x1]
                        * masses[x2]
                        * masses[y1]
                        * masses[y2]
                        * indicators[x1][i]
                        * indicators[x2][i]
                        * indicators[y1][j]
                        * indicators[y2][j]
                        * kernel[x1][y1]
                        * kernel[x1][y2]
                        * kernel[x2][y1]
                        * kernel[x2][y2]
                    )
    return total


def forcing_terms(
    p: Sequence[Fraction],
    w: Sequence[Sequence[Fraction]],
    masses: Sequence[Fraction],
    kernel: Sequence[Sequence[Fraction]],
) -> tuple[ForcingTerms, list[Signature], list[Signature], list[list[Fraction]]]:
    q = len(p)
    targets = target_signatures(p, w)
    signatures = micro_signatures(masses, kernel, q - 1)
    indicators = [
        [lagrange_value(signature, targets, i) for i in range(q)]
        for signature in signatures
    ]

    signature_defect = sum(
        mass * q_polynomial(signature, targets)
        for mass, signature in zip(masses, signatures, strict=True)
    )

    recovered_masses = [
        sum(masses[a] * indicators[a][i] for a in range(len(masses)))
        for i in range(q)
    ]
    mass_defect = sum(
        (recovered_masses[i] - p[i]) ** 2 for i in range(q)
    )

    wrong = Fraction(0)
    for i in range(q):
        for j in range(i + 1):
            edge_density = sum(
                masses[a]
                * masses[b]
                * indicators[a][i]
                * indicators[b][j]
                * kernel[a][b]
                for a in range(len(masses))
                for b in range(len(masses))
            )
            wrong += edge_density**2

    row_defect = Fraction(0)
    column_defect = Fraction(0)
    c4_defect = Fraction(0)
    for i in range(q):
        for j in range(i + 1, q):
            target_row = p[j] * w[i][j]
            target_column = p[i] * w[i][j]
            for a in range(len(masses)):
                row = sum(
                    masses[b] * indicators[b][j] * kernel[a][b]
                    for b in range(len(masses))
                )
                row_defect += masses[a] * indicators[a][i] * (row - target_row) ** 2
            for b in range(len(masses)):
                column = sum(
                    masses[a] * indicators[a][i] * kernel[a][b]
                    for a in range(len(masses))
                )
                column_defect += (
                    masses[b]
                    * indicators[b][j]
                    * (column - target_column) ** 2
                )
            c4 = block_c4(masses, kernel, indicators, i, j)
            target_c4 = p[i] ** 2 * p[j] ** 2 * w[i][j] ** 4
            c4_defect += (c4 - target_c4) ** 2

    terms = ForcingTerms(
        signature=signature_defect,
        mass=mass_defect,
        wrong_direction=wrong,
        row=row_defect,
        column=column_defect,
        c4=c4_defect,
    )
    return terms, targets, signatures, indicators


def make_target(q_case: int) -> tuple[tuple[Fraction, ...], Matrix]:
    if q_case == 3:
        p = (Fraction(1, 5), Fraction(3, 10), Fraction(1, 2))
        w = [[Fraction(0) for _ in range(3)] for _ in range(3)]
        w[0][1] = Fraction(1, 2)
        w[0][2] = Fraction(2, 3)
        w[1][2] = Fraction(3, 4)
        return p, w

    if q_case == 4:
        p = (Fraction(1, 10), Fraction(1, 5), Fraction(3, 10), Fraction(2, 5))
        w = [[Fraction(0) for _ in range(4)] for _ in range(4)]
        values = {
            (0, 1): Fraction(1, 3),
            (0, 2): Fraction(1, 2),
            (0, 3): Fraction(2, 3),
            (1, 2): Fraction(2, 5),
            (1, 3): Fraction(3, 5),
            (2, 3): Fraction(3, 4),
        }
        for (i, j), value in values.items():
            w[i][j] = value
        return p, w

    raise ValueError(q_case)


def verify_case(q_case: int) -> int:
    p, w = make_target(q_case)
    q = len(p)
    targets = target_signatures(p, w)
    checks = 0

    assert len(set(targets)) == q
    checks += 1
    for i, signature in enumerate(targets):
        assert q_polynomial(signature, targets) == 0
        for j in range(q):
            assert lagrange_value(signature, targets, j) == int(i == j)
            checks += 1

    masses, layers, kernel = refined_target(p, w)
    terms, _, signatures, indicators = forcing_terms(p, w, masses, kernel)
    assert all(value == 0 for value in terms)
    checks += len(terms)
    for micro, layer in enumerate(layers):
        assert signatures[micro] == targets[layer]
        assert indicators[micro][layer] == 1
        checks += 2

    # A nonconstant biregular perturbation preserves all rooted signatures and
    # block row/column degrees, but creates a positive K_2,2 excess.
    perturbed = [row[:] for row in kernel]
    source_layer = 0
    target_layer = 1
    source_micro = [i for i, layer in enumerate(layers) if layer == source_layer]
    target_micro = [i for i, layer in enumerate(layers) if layer == target_layer]
    delta = Fraction(1, 12)
    base = w[source_layer][target_layer]
    for a_index, a in enumerate(source_micro):
        for b_index, b in enumerate(target_micro):
            perturbed[a][b] = base + (delta if a_index == b_index else -delta)

    perturbed_terms, _, perturbed_signatures, _ = forcing_terms(p, w, masses, perturbed)
    assert perturbed_terms.signature == 0
    assert perturbed_terms.mass == 0
    assert perturbed_terms.wrong_direction == 0
    assert perturbed_terms.row == 0
    assert perturbed_terms.column == 0
    assert perturbed_terms.c4 > 0
    assert perturbed_signatures == signatures
    checks += 7

    # A backward edge is detected by at least one nonnegative defect.
    backward = [row[:] for row in kernel]
    backward[target_micro[0]][source_micro[0]] = Fraction(1, 7)
    backward_terms, _, _, _ = forcing_terms(p, w, masses, backward)
    assert sum(backward_terms) > 0
    assert backward_terms.wrong_direction > 0
    checks += 2

    return checks


def main() -> None:
    checks = verify_case(3) + verify_case(4)
    print(f"verified {checks} exact general stochastic ordered-forcing checks")


if __name__ == "__main__":
    raise SystemExit(main())
