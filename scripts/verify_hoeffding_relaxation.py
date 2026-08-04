#!/usr/bin/env python3
"""Exact checks for findings-52.

The script builds random symmetric finite-state kernels with rational values,
computes their canonical Hoeffding projections, and verifies:
1. coordinatewise degeneracy;
2. pointwise Boolean-lattice reconstruction;
3. the exact U-statistic decomposition on finite samples;
4. exact variance and cross-level covariance formulas for canonical kernels;
5. the symmetric three-layer route projection norm.
"""

from __future__ import annotations

from collections.abc import Callable, Iterator
from fractions import Fraction
from itertools import combinations, product
from math import comb
import random

Kernel = Callable[[tuple[int, ...]], Fraction]


def subsets(items: tuple[int, ...]) -> Iterator[tuple[int, ...]]:
    for r in range(len(items) + 1):
        yield from combinations(items, r)


def random_symmetric_kernel(q: int, k: int, rng: random.Random) -> Kernel:
    values: dict[tuple[int, ...], Fraction] = {}
    for xs in product(range(q), repeat=k):
        key = tuple(sorted(xs))
        if key not in values:
            values[key] = Fraction(rng.randint(-5, 5), rng.randint(1, 5))

    def h(xs: tuple[int, ...]) -> Fraction:
        return values[tuple(sorted(xs))]

    return h


def conditional(
    h: Kernel,
    p: tuple[Fraction, ...],
    k: int,
    fixed: dict[int, int],
) -> Fraction:
    total = Fraction(0)
    free = [i for i in range(k) if i not in fixed]
    for vals in product(range(len(p)), repeat=len(free)):
        xs = [0] * k
        for i, value in fixed.items():
            xs[i] = value
        weight = Fraction(1)
        for i, value in zip(free, vals):
            xs[i] = value
            weight *= p[value]
        total += weight * h(tuple(xs))
    return total


def projection(
    h: Kernel,
    p: tuple[Fraction, ...],
    k: int,
    xs: tuple[int, ...],
) -> Fraction:
    j = len(xs)
    out = Fraction(0)
    indices = tuple(range(j))
    for s in subsets(indices):
        fixed = {i: xs[i] for i in s}
        out += (-1) ** (j - len(s)) * conditional(h, p, k, fixed)
    return out


def check_random_kernels(trials: int = 40) -> int:
    rng = random.Random(5202026)
    checks = 0
    for _ in range(trials):
        q = rng.randint(2, 4)
        k = rng.randint(1, 4)
        raw = [rng.randint(1, 7) for _ in range(q)]
        p = tuple(Fraction(x, sum(raw)) for x in raw)
        h = random_symmetric_kernel(q, k, rng)
        cond_cache: dict[tuple[tuple[int, int], ...], Fraction] = {}
        proj_cache: dict[tuple[int, ...], Fraction] = {}

        def cond(fixed: dict[int, int]) -> Fraction:
            key = tuple(sorted(fixed.items()))
            if key not in cond_cache:
                cond_cache[key] = conditional(h, p, k, fixed)
            return cond_cache[key]

        def proj(xs: tuple[int, ...]) -> Fraction:
            if xs not in proj_cache:
                j = len(xs)
                value = Fraction(0)
                indices = tuple(range(j))
                for subset in subsets(indices):
                    fixed = {i: xs[i] for i in subset}
                    value += (-1) ** (j - len(subset)) * cond(fixed)
                proj_cache[xs] = value
            return proj_cache[xs]

        theta = cond({})

        # Canonical degeneracy in each argument.
        for j in range(1, k + 1):
            for xs in product(range(q), repeat=j):
                for r in range(j):
                    averaged = Fraction(0)
                    for value in range(q):
                        ys = list(xs)
                        ys[r] = value
                        averaged += p[value] * proj(tuple(ys))
                    assert averaged == 0
                    checks += 1

        # Pointwise ANOVA/Hoeffding reconstruction.
        for xs in product(range(q), repeat=k):
            rhs = theta
            for j in range(1, k + 1):
                for s in combinations(range(k), j):
                    rhs += proj(tuple(xs[i] for i in s))
            assert rhs == h(xs)
            checks += 1

        # Exact sample U-statistic decomposition.
        n = k + 2
        sample = tuple(rng.randrange(q) for _ in range(n))
        lhs = sum(
            h(tuple(sample[i] for i in s))
            for s in combinations(range(n), k)
        ) / comb(n, k) - theta
        rhs = Fraction(0)
        for j in range(1, k + 1):
            uj = sum(
                proj(tuple(sample[i] for i in s))
                for s in combinations(range(n), j)
            ) / comb(n, j)
            rhs += comb(k, j) * uj
        assert lhs == rhs
        checks += 1
    return checks


def canonical_covariance_checks() -> int:
    # A fixed order-two canonical kernel on a two-state alphabet.
    p = (Fraction(2, 5), Fraction(3, 5))
    centered = (Fraction(3, 5), Fraction(-2, 5))

    def g(xs: tuple[int, int]) -> Fraction:
        return centered[xs[0]] * centered[xs[1]]

    sigma2 = sum(
        p[i] * p[j] * g((i, j)) ** 2
        for i, j in product(range(2), repeat=2)
    )
    checks = 0

    # Exhaustively compute U_n covariance for n <= m by summing over samples.
    for n in range(2, 6):
        for m in range(n, 7):
            eu_nu_m = Fraction(0)
            eu_n = Fraction(0)
            eu_m = Fraction(0)
            for sample in product(range(2), repeat=m):
                weight = Fraction(1)
                for value in sample:
                    weight *= p[value]
                un = sum(
                    g(tuple(sample[i] for i in s))
                    for s in combinations(range(n), 2)
                ) / comb(n, 2)
                um = sum(
                    g(tuple(sample[i] for i in s))
                    for s in combinations(range(m), 2)
                ) / comb(m, 2)
                eu_n += weight * un
                eu_m += weight * um
                eu_nu_m += weight * un * um
            covariance = eu_nu_m - eu_n * eu_m
            assert covariance == sigma2 / comb(m, 2)
            checks += 1
    return checks


def route_projection_check() -> int:
    p = (Fraction(1, 3),) * 3
    a = Fraction(2, 5)
    b = Fraction(3, 7)
    k = 3

    def h(xs: tuple[int, ...]) -> Fraction:
        return a * b if set(xs) == {0, 1, 2} else Fraction(0)

    pi1 = [projection(h, p, k, (i,)) for i in range(3)]
    assert pi1 == [0, 0, 0]
    sigma2 = sum(
        p[i] * p[j] * projection(h, p, k, (i, j)) ** 2
        for i, j in product(range(3), repeat=2)
    )
    assert sigma2 == 2 * a * a * b * b / 81
    assert comb(3, 2) ** 2 * 2 * sigma2 == 4 * a * a * b * b / 9
    return 5


def main() -> None:
    checks = check_random_kernels()
    checks += canonical_covariance_checks()
    checks += route_projection_check()
    print(f"verified {checks:,} Hoeffding-relaxation identities")


if __name__ == "__main__":
    raise SystemExit(main())
