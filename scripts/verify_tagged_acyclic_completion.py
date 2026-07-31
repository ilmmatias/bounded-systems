#!/usr/bin/env python3
"""Exact checks for findings-84 tagged-compensated acyclic completion."""

from __future__ import annotations

from fractions import Fraction
from typing import Dict, List, Tuple

Matrix = List[List[Fraction]]


def mean(values: List[Fraction]) -> Fraction:
    return sum(values, Fraction(0)) / len(values)


def row_means(matrix: Matrix) -> List[Fraction]:
    return [mean(row) for row in matrix]


def col_means(matrix: Matrix) -> List[Fraction]:
    cols = len(matrix[0])
    return [mean([row[j] for row in matrix]) for j in range(cols)]


def row_gram_defect(matrix: Matrix) -> Fraction:
    rows = len(matrix)
    cols = len(matrix[0])
    r = row_means(matrix)
    total = Fraction(0)
    for i in range(rows):
        for j in range(rows):
            inner = sum((matrix[i][k] * matrix[j][k] for k in range(cols)), Fraction(0)) / cols
            total += (inner - r[i] * r[j]) ** 2
    return total / (rows * rows)


def col_gram_defect(matrix: Matrix) -> Fraction:
    transposed = [[matrix[i][j] for i in range(len(matrix))] for j in range(len(matrix[0]))]
    return row_gram_defect(transposed)


def verify_completion() -> int:
    alpha = [Fraction(1, 5), Fraction(3, 10), Fraction(1, 2)]
    atom_counts = [2, 3, 2]

    blocks: Dict[Tuple[int, int], Matrix] = {
        (0, 1): [
            [Fraction(1, 5), Fraction(2, 5), Fraction(4, 5)],
            [Fraction(3, 5), Fraction(1, 10), Fraction(7, 10)],
        ],
        (0, 2): [
            [Fraction(1, 3), Fraction(5, 6)],
            [Fraction(2, 3), Fraction(1, 6)],
        ],
        (1, 2): [
            [Fraction(1, 4), Fraction(3, 4)],
            [Fraction(2, 5), Fraction(4, 5)],
            [Fraction(1, 2), Fraction(1, 5)],
        ],
    }

    outgoing: List[List[Fraction]] = [
        [Fraction(0) for _ in range(atom_counts[i])] for i in range(3)
    ]
    incoming: List[List[Fraction]] = [
        [Fraction(0) for _ in range(atom_counts[i])] for i in range(3)
    ]

    for (i, j), block in blocks.items():
        rm = row_means(block)
        cm = col_means(block)
        for a, value in enumerate(rm):
            outgoing[i][a] += alpha[j] * value
        for b, value in enumerate(cm):
            incoming[j][b] += alpha[i] * value

    edge_density = sum(
        alpha[i] * mean(outgoing[i]) for i in range(3)
    )
    assert edge_density == sum(
        alpha[i] * mean(incoming[i]) for i in range(3)
    )

    beta = Fraction(1, 20)
    source_masses = [Fraction(1, 100), Fraction(1, 50), Fraction(3, 100)]
    sink_masses = [Fraction(1, 50), Fraction(3, 100), Fraction(1, 25)]
    d_mass = Fraction(7, 20)
    c_mass = Fraction(9, 20)
    assert beta + sum(source_masses) + sum(sink_masses) + d_mass + c_mass == 1
    assert d_mass >= 2 * beta and c_mass >= 2 * beta

    d_to_l: List[Matrix] = []
    l_to_c: List[Matrix] = []
    d_atoms = 3
    c_atoms = 4

    for i in range(3):
        col_values = [
            Fraction(1, 2) + beta * (1 - value) / d_mass
            for value in incoming[i]
        ]
        row_values = [
            Fraction(1, 2) + beta * (1 - value) / c_mass
            for value in outgoing[i]
        ]
        assert all(Fraction(0) <= value <= 1 for value in col_values + row_values)
        d_to_l.append([col_values[:] for _ in range(d_atoms)])
        l_to_c.append([[value for _ in range(c_atoms)] for value in row_values])

    # Pointwise degree flattening on every payload atom.
    for i in range(3):
        target_in = source_masses[i] + beta + d_mass / 2
        target_out = sink_masses[i] + beta + c_mass / 2
        d_cols = col_means(d_to_l[i])
        c_rows = row_means(l_to_c[i])
        for a in range(atom_counts[i]):
            actual_in = source_masses[i] + beta * incoming[i][a] + d_mass * d_cols[a]
            actual_out = sink_masses[i] + beta * outgoing[i][a] + c_mass * c_rows[a]
            assert actual_in == target_in
            assert actual_out == target_out

    # The one-sided rigidity defects vanish at the completion.
    for i in range(3):
        assert col_gram_defect(d_to_l[i]) == 0
        assert row_gram_defect(l_to_c[i]) == 0

    # Perturbations preserving the relevant marginal are detected.
    perturbed_d = [row[:] for row in d_to_l[0]]
    epsilon = Fraction(1, 1000)
    perturbed_d[0][0] += epsilon
    perturbed_d[1][0] -= epsilon
    assert col_means(perturbed_d) == col_means(d_to_l[0])
    assert col_gram_defect(perturbed_d) > 0

    perturbed_c = [row[:] for row in l_to_c[0]]
    perturbed_c[0][0] += epsilon
    perturbed_c[0][1] -= epsilon
    assert row_means(perturbed_c) == row_means(l_to_c[0])
    assert row_gram_defect(perturbed_c) > 0

    degree_pairs = []
    d_out = beta / 2 + beta * beta * (1 - edge_density) / d_mass
    c_in = beta / 2 + beta * beta * (1 - edge_density) / c_mass
    degree_pairs.append(("D", Fraction(0), d_out))
    degree_pairs.append(("C", c_in, Fraction(0)))

    for i in range(3):
        degree_pairs.append((f"S{i}", Fraction(0), beta * alpha[i] + sink_masses[i]))
        degree_pairs.append((f"T{i}", source_masses[i] + beta * alpha[i], Fraction(0)))
        degree_pairs.append(
            (
                f"L{i}",
                source_masses[i] + beta + d_mass / 2,
                sink_masses[i] + beta + c_mass / 2,
            )
        )

    assert len({(x, y) for _, x, y in degree_pairs}) == len(degree_pairs)

    # Every allowed block points forward in the displayed topological order.
    order = {"D": 0, "S0": 1, "S1": 2, "S2": 3, "L0": 4, "L1": 5, "L2": 6,
             "T0": 7, "T1": 8, "T2": 9, "C": 10}
    allowed = {
        ("D", "L0"), ("D", "L1"), ("D", "L2"),
        ("S0", "L0"), ("S1", "L1"), ("S2", "L2"),
        ("S0", "T0"), ("S1", "T1"), ("S2", "T2"),
        ("L0", "T0"), ("L1", "T1"), ("L2", "T2"),
        ("L0", "C"), ("L1", "C"), ("L2", "C"),
        ("L0", "L1"), ("L0", "L2"), ("L1", "L2"),
    }
    assert all(order[u] < order[v] for u, v in allowed)

    return len(degree_pairs) + sum(atom_counts) * 2 + 9


def main() -> None:
    checks = verify_completion()
    print(f"tagged-compensated exact checks: {checks}")
    print("all degree flattening, separation, rigidity, and acyclicity checks passed")


if __name__ == "__main__":
    main()
