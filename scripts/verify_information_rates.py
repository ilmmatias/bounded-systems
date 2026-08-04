#!/usr/bin/env python3
"""Exact moment and contraction checks for findings-65.md."""

from __future__ import annotations

from collections.abc import Sequence
from fractions import Fraction


def dirichlet_cov(
    alpha: Sequence[int],
) -> tuple[list[Fraction], list[list[Fraction]]]:
    total = sum(alpha)
    mean = [Fraction(a, total) for a in alpha]
    cov: list[list[Fraction]] = []

    for i in range(len(alpha)):
        row: list[Fraction] = []

        for j in range(len(alpha)):
            if i == j:
                direct = Fraction(
                    alpha[i] * (total - alpha[i]),
                    total * total * (total + 1),
                )
            else:
                direct = Fraction(
                    -alpha[i] * alpha[j], total * total * (total + 1)
                )

            formula = (
                (mean[i] if i == j else 0) - mean[i] * mean[j]
            ) / (total + 1)

            assert direct == formula
            row.append(formula)

        cov.append(row)

    return mean, cov


def beta_variance(a: int, b: int) -> tuple[Fraction, Fraction]:
    total = a + b
    mean = Fraction(a, total)
    direct = Fraction(a * b, total * total * (total + 1))
    formula = mean * (1 - mean) / (total + 1)

    assert direct == formula

    second = Fraction(a * (a + 1), total * (total + 1))

    assert second - mean * mean == direct
    return mean, direct


def main() -> None:
    checks = 0

    for alpha in ([2, 3], [1, 4, 5], [3, 5, 7, 11]):
        dirichlet_cov(alpha)
        checks += 1

    for a, b in ((2, 3), (5, 7), (11, 4)):
        mean, var = beta_variance(a, b)
        # Two future Bernoulli observations have covariance Var(theta).
        exy = Fraction(a * (a + 1), (a + b) * (a + b + 1))

        assert exy - mean * mean == var
        checks += 1

    # One-vertex rate for p=(2/5, 3/5) along n divisible by five.
    p = [Fraction(2, 5), Fraction(3, 5)]
    alpha = [2, 3]
    errors: list[Fraction] = []

    for n in (50, 100, 200, 400):
        post = [alpha[i] + int(p[i] * n) for i in range(2)]
        _, cov = dirichlet_cov(post)
        target = p[0] * (1 - p[0])
        errors.append(abs(n * cov[0][0] - target))

    assert all(errors[i + 1] < errors[i] for i in range(len(errors) - 1))
    checks += len(errors)

    # Pair rate for block opportunity c n^2 with c=6/25 and w=1/3.
    c = Fraction(6, 25)
    w = Fraction(1, 3)
    a, b = 2, 3
    errors = []

    for n in (50, 100, 200, 400):
        m = int(c * n * n)
        assert Fraction(m, 1) == c * n * n

        e = int(w * m)
        assert Fraction(e, 1) == w * m

        _, var = beta_variance(a + e, b + m - e)
        target = w * (1 - w) / c
        errors.append(abs(n * n * var - target))

    assert all(errors[i + 1] < errors[i] for i in range(len(errors) - 1))
    checks += len(errors)

    # General r-support beta contraction on exact opportunity sequences.
    lam = Fraction(2, 5)

    for r in (1, 2, 3, 4):
        c_r = Fraction(1, 5)
        n = 500
        m = int(c_r * n**r)
        assert Fraction(m, 1) == c_r * n**r

        e = int(lam * m)
        assert Fraction(e, 1) == lam * m

        _, var = beta_variance(3 + e, 4 + m - e)
        scaled = n**r * var
        target = lam * (1 - lam) / c_r

        assert abs(scaled - target) < Fraction(1, 10)
        checks += 1

    print(
        f"verified {checks} exact information-rate identities and "
        "convergence checks"
    )


if __name__ == "__main__":
    raise SystemExit(main())
