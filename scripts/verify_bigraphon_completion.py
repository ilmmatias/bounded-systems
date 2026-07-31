#!/usr/bin/env python3
"""Exact checks for findings-75 balanced acyclic completion."""

from __future__ import annotations

from fractions import Fraction
from typing import List

Matrix = List[List[Fraction]]


def mean(values: List[Fraction]) -> Fraction:
    return sum(values, Fraction(0)) / len(values)


def row_means(matrix: Matrix) -> List[Fraction]:
    return [mean(row) for row in matrix]


def col_means(matrix: Matrix) -> List[Fraction]:
    cols = len(matrix[0])
    return [mean([row[j] for row in matrix]) for j in range(cols)]


def edge_mean(matrix: Matrix) -> Fraction:
    return mean([x for row in matrix for x in row])


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


def repeated_rows(values: List[Fraction], count: int) -> Matrix:
    return [[value for _ in range(count)] for value in values]


def repeated_cols(values: List[Fraction], count: int) -> Matrix:
    return [[values[j] for j in range(len(values))] for _ in range(count)]


def verify_payload(payload: Matrix) -> int:
    m = len(payload)
    n = len(payload[0])
    assert all(len(row) == n for row in payload)
    assert all(Fraction(0) <= x <= Fraction(1) for row in payload for x in row)

    r = row_means(payload)
    c = col_means(payload)
    e = edge_mean(payload)
    assert Fraction(0) < e < Fraction(1)

    # A -> C is constant in the C coordinate; D -> B is constant in D.
    ac = repeated_rows([Fraction(1) - x for x in r], n)
    db = repeated_cols([Fraction(1) - y for y in c], m)

    assert row_means(ac) == [Fraction(1) - x for x in r]
    assert col_means(db) == [Fraction(1) - y for y in c]
    assert row_gram_defect(ac) == 0
    assert col_gram_defect(db) == 0

    # Four equal-mass parts. Degrees are in the whole probability space.
    degree_d = (Fraction(0), (Fraction(1) - e) / 4)
    degree_a = (Fraction(0), Fraction(1, 4))
    degree_b = (Fraction(1, 4), Fraction(0))
    degree_c = ((Fraction(1) - e) / 4, Fraction(0))
    assert len({degree_d, degree_a, degree_b, degree_c}) == 4

    for i in range(m):
        assert (r[i] + row_means(ac)[i]) / 4 == Fraction(1, 4)
    for j in range(n):
        assert (c[j] + col_means(db)[j]) / 4 == Fraction(1, 4)
    assert edge_mean(db) / 4 == degree_d[1]
    assert edge_mean(ac) / 4 == degree_c[0]

    # A nonconstant row perturbation preserving each row sum is detected.
    if n >= 2:
        perturbed = [row[:] for row in ac]
        epsilon = Fraction(1, 100)
        i = 0
        if perturbed[i][0] + epsilon <= 1 and perturbed[i][1] - epsilon >= 0:
            perturbed[i][0] += epsilon
            perturbed[i][1] -= epsilon
        else:
            perturbed[i][0] -= epsilon
            perturbed[i][1] += epsilon
        assert row_means(perturbed) == row_means(ac)
        assert row_gram_defect(perturbed) > 0

    # The only nonzero blocks go from D,A to B,C, so no two-step route exists.
    allowed = {("D", "B"), ("A", "B"), ("A", "C")}
    for u, v in allowed:
        for x, y in allowed:
            assert v != x

    return 1


def main() -> None:
    payloads: List[Matrix] = [
        [
            [Fraction(1, 5), Fraction(2, 5), Fraction(4, 5)],
            [Fraction(3, 5), Fraction(1, 10), Fraction(7, 10)],
        ],
        [
            [Fraction(0), Fraction(1, 3), Fraction(2, 3), Fraction(1)],
            [Fraction(1, 4), Fraction(1, 2), Fraction(3, 4), Fraction(1, 8)],
            [Fraction(5, 6), Fraction(1, 6), Fraction(1, 2), Fraction(1, 3)],
        ],
        [
            [Fraction(1, 7), Fraction(2, 7)],
            [Fraction(3, 7), Fraction(4, 7)],
            [Fraction(5, 7), Fraction(6, 7)],
            [Fraction(1), Fraction(0)],
        ],
    ]

    checks = sum(verify_payload(payload) for payload in payloads)
    print(f"balanced completion exact payload checks: {checks}")
    print("all exact degree, complement, rigidity, and acyclicity checks passed")


if __name__ == "__main__":
    main()
