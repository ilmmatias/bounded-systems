#!/usr/bin/env python3
"""Exact audits for findings-49 stochastic two-layer sectors.

The script uses rational arithmetic to verify:
1. the conditional variance formula for the new-vertex pair-noise increment;
2. the exact edge-density decomposition;
3. the symmetric second-order algebraic identity.
"""

from __future__ import annotations

from fractions import Fraction
from itertools import product
from math import comb
from typing import Iterable, Sequence, Tuple


def bernoulli_outcomes(probability: Fraction) -> Iterable[Tuple[int, Fraction]]:
    yield 0, 1 - probability
    yield 1, probability


def conditional_pair_increment_moments(
    past_marks: Sequence[int], theta: Fraction, r: Fraction
) -> Tuple[Fraction, Fraction]:
    mean = Fraction(0, 1)
    second = Fraction(0, 1)
    for new_mark, mark_probability in ((1, theta), (2, 1 - theta)):
        for edge_bits in product((0, 1), repeat=len(past_marks)):
            probability = mark_probability
            value = Fraction(0, 1)
            for old_mark, bit in zip(past_marks, edge_bits):
                probability *= r if bit else 1 - r
                if old_mark != new_mark:
                    value += Fraction(bit, 1) - r
            mean += probability * value
            second += probability * value * value
    return mean, second


def audit_conditional_variance() -> int:
    theta = Fraction(2, 5)
    r = Fraction(3, 7)
    checks = 0
    for past_marks in (
        (1,),
        (2,),
        (1, 1),
        (1, 2),
        (2, 2),
        (1, 1, 2),
        (1, 2, 2),
        (1, 1, 2, 2),
    ):
        mean, second = conditional_pair_increment_moments(past_marks, theta, r)
        if mean != 0:
            raise AssertionError(f"nonzero conditional mean for {past_marks}: {mean}")
        c1 = sum(mark == 1 for mark in past_marks)
        c2 = len(past_marks) - c1
        expected = r * (1 - r) * ((1 - theta) * c1 + theta * c2)
        if second != expected:
            raise AssertionError(
                f"variance mismatch for {past_marks}: {second} != {expected}"
            )
        checks += 2
    return checks


def audit_edge_decomposition(max_n: int = 30) -> int:
    r = Fraction(3, 8)
    checks = 0
    for n in range(2, max_n + 1):
        denominator = comb(n, 2)
        for c1 in range(n + 1):
            c2 = n - c1
            cross = c1 * c2
            # Check every possible edge count in the conditional support.
            for edges in range(cross + 1):
                q = Fraction(edges, denominator)
                h = Fraction(cross, denominator)
                noise = Fraction(edges, 1) - r * cross
                u = noise / denominator
                if q != r * h + u:
                    raise AssertionError(
                        f"decomposition mismatch n={n} c1={c1} edges={edges}"
                    )
                checks += 1
    return checks


def audit_symmetric_identity(max_n: int = 80) -> int:
    checks = 0
    for n in range(2, max_n + 1):
        for c1 in range(n + 1):
            c2 = n - c1
            h = Fraction(c1 * c2, comb(n, 2))
            y_squared = Fraction((2 * c1 - n) ** 2, 4 * n)
            left = n * (h - Fraction(1, 2))
            right = Fraction(n, 2 * (n - 1)) - Fraction(2 * n, n - 1) * y_squared
            if left != right:
                raise AssertionError(
                    f"symmetric identity mismatch n={n} c1={c1}: {left} != {right}"
                )
            checks += 1
    return checks


def main() -> None:
    total = 0
    total += audit_conditional_variance()
    total += audit_edge_decomposition()
    total += audit_symmetric_identity()
    print(f"stochastic two-layer audits passed: {total} exact checks")


if __name__ == "__main__":
    main()
