#!/usr/bin/env python3
"""Exhaustive checks for the joint vertex-edge support decomposition.

The local kernel uses three vertex variables and three pair variables, all
independent symmetric Bernoulli bits.  Symmetric kernels are assigned random
integer values on permutation orbits.  The script verifies:

1. the primitive-coordinate ANOVA decomposition pointwise;
2. canonicality of every projection;
3. grouping by looped support-graph isomorphism classes;
4. the automorphism/orbit counting identity;
5. the exact finite-n variance formula; and
6. the exact nested-level covariance formula.
"""

from __future__ import annotations

from fractions import Fraction
from itertools import combinations, permutations, product
import math
import random

K = 3
VERTEX_COORDS = tuple(("v", i) for i in range(K))
EDGE_COORDS = tuple(("e", i, j) for i in range(K) for j in range(i + 1, K))
COORDS = VERTEX_COORDS + EDGE_COORDS
C = len(COORDS)
PERMS = tuple(permutations(range(K)))


def popcount(mask: int) -> int:
    return mask.bit_count()


def permute_coord(coord: tuple, perm: tuple[int, ...]) -> tuple:
    if coord[0] == "v":
        return ("v", perm[coord[1]])
    a, b = sorted((perm[coord[1]], perm[coord[2]]))
    return ("e", a, b)


COORD_INDEX = {coord: idx for idx, coord in enumerate(COORDS)}


def permute_mask(mask: int, perm: tuple[int, ...]) -> int:
    out = 0
    for idx, coord in enumerate(COORDS):
        if (mask >> idx) & 1:
            out |= 1 << COORD_INDEX[permute_coord(coord, perm)]
    return out


def permute_assignment(bits: tuple[int, ...], perm: tuple[int, ...]) -> tuple[int, ...]:
    out = [0] * C
    for idx, coord in enumerate(COORDS):
        new_coord = permute_coord(coord, perm)
        out[COORD_INDEX[new_coord]] = bits[idx]
    return tuple(out)


def assignment_orbit_key(bits: tuple[int, ...]) -> tuple[int, ...]:
    return min(permute_assignment(bits, perm) for perm in PERMS)


def mask_orbit(mask: int) -> tuple[int, ...]:
    return tuple(sorted({permute_mask(mask, perm) for perm in PERMS}))


def support(mask: int) -> tuple[int, ...]:
    vertices: set[int] = set()
    for idx, coord in enumerate(COORDS):
        if not ((mask >> idx) & 1):
            continue
        if coord[0] == "v":
            vertices.add(coord[1])
        else:
            vertices.add(coord[1])
            vertices.add(coord[2])
    return tuple(sorted(vertices))


def automorphism_count(mask: int) -> int:
    supp = support(mask)
    r = len(supp)
    relabel = {old: i for i, old in enumerate(supp)}
    local_coords = []
    for idx, coord in enumerate(COORDS):
        if not ((mask >> idx) & 1):
            continue
        if coord[0] == "v":
            local_coords.append(("v", relabel[coord[1]]))
        else:
            a, b = sorted((relabel[coord[1]], relabel[coord[2]]))
            local_coords.append(("e", a, b))
    local_set = frozenset(local_coords)
    count = 0
    for perm in permutations(range(r)):
        moved = set()
        for coord in local_set:
            if coord[0] == "v":
                moved.add(("v", perm[coord[1]]))
            else:
                a, b = sorted((perm[coord[1]], perm[coord[2]]))
                moved.add(("e", a, b))
        if frozenset(moved) == local_set:
            count += 1
    return count


ALL_LOCAL = tuple(product((0, 1), repeat=C))


def random_symmetric_kernel(seed: int) -> dict[tuple[int, ...], Fraction]:
    rng = random.Random(seed)
    orbit_values: dict[tuple[int, ...], Fraction] = {}
    kernel: dict[tuple[int, ...], Fraction] = {}
    for bits in ALL_LOCAL:
        key = assignment_orbit_key(bits)
        if key not in orbit_values:
            orbit_values[key] = Fraction(rng.randint(-7, 9), 1)
        kernel[bits] = orbit_values[key]
    return kernel


def conditional_expectation(
    kernel: dict[tuple[int, ...], Fraction],
    fixed_mask: int,
    bits: tuple[int, ...],
) -> Fraction:
    total = Fraction(0)
    count = 0
    for candidate in ALL_LOCAL:
        if all(
            not ((fixed_mask >> idx) & 1) or candidate[idx] == bits[idx]
            for idx in range(C)
        ):
            total += kernel[candidate]
            count += 1
    return total / count


def projections(
    kernel: dict[tuple[int, ...], Fraction],
) -> dict[int, dict[tuple[int, ...], Fraction]]:
    cond: dict[tuple[int, tuple[int, ...]], Fraction] = {}
    for mask in range(1 << C):
        for bits in ALL_LOCAL:
            cond[(mask, bits)] = conditional_expectation(kernel, mask, bits)

    out: dict[int, dict[tuple[int, ...], Fraction]] = {}
    for mask in range(1 << C):
        vals: dict[tuple[int, ...], Fraction] = {}
        sub = mask
        subsets = []
        while True:
            subsets.append(sub)
            if sub == 0:
                break
            sub = (sub - 1) & mask
        for bits in ALL_LOCAL:
            value = Fraction(0)
            for submask in subsets:
                sign = -1 if (popcount(mask) - popcount(submask)) % 2 else 1
                value += sign * cond[(submask, bits)]
            vals[bits] = value
        out[mask] = vals
    return out


def local_bits_from_global(
    global_bits: tuple[int, ...],
    n: int,
    vertices: tuple[int, ...],
) -> tuple[int, ...]:
    vertex_offset = 0
    edge_pairs = tuple(combinations(range(n), 2))
    edge_index = {pair: n + idx for idx, pair in enumerate(edge_pairs)}
    vals = []
    for coord in COORDS:
        if coord[0] == "v":
            vals.append(global_bits[vertex_offset + vertices[coord[1]]])
        else:
            a, b = sorted((vertices[coord[1]], vertices[coord[2]]))
            vals.append(global_bits[edge_index[(a, b)]])
    return tuple(vals)


def projected_value_on_embedding(
    proj: dict[int, dict[tuple[int, ...], Fraction]],
    rep_mask: int,
    global_bits: tuple[int, ...],
    n: int,
    embedding: tuple[int, ...],
) -> Fraction:
    supp = support(rep_mask)
    local_vertex_map = {supp[pos]: embedding[pos] for pos in range(len(supp))}
    edge_pairs = tuple(combinations(range(n), 2))
    edge_index = {pair: n + idx for idx, pair in enumerate(edge_pairs)}
    local_assignment = [0] * C
    for idx, coord in enumerate(COORDS):
        if coord[0] == "v":
            if coord[1] in local_vertex_map:
                local_assignment[idx] = global_bits[local_vertex_map[coord[1]]]
        else:
            if coord[1] in local_vertex_map and coord[2] in local_vertex_map:
                a, b = sorted((local_vertex_map[coord[1]], local_vertex_map[coord[2]]))
                local_assignment[idx] = global_bits[edge_index[(a, b)]]
    return proj[rep_mask][tuple(local_assignment)]


def falling(n: int, r: int) -> int:
    return math.prod(range(n - r + 1, n + 1)) if r else 1


def statistic(
    kernel: dict[tuple[int, ...], Fraction],
    global_bits: tuple[int, ...],
    n: int,
) -> Fraction:
    total = Fraction(0)
    count = 0
    for subset in combinations(range(n), K):
        total += kernel[local_bits_from_global(global_bits, n, subset)]
        count += 1
    return total / count


def grouped_rhs(
    proj: dict[int, dict[tuple[int, ...], Fraction]],
    global_bits: tuple[int, ...],
    n: int,
    reps: tuple[int, ...],
) -> Fraction:
    theta = proj[0][ALL_LOCAL[0]]
    value = theta
    for rep in reps:
        r = len(support(rep))
        aut = automorphism_count(rep)
        coefficient = falling(K, r) // aut
        total = Fraction(0)
        for embedding in permutations(range(n), r):
            total += projected_value_on_embedding(proj, rep, global_bits, n, embedding)
        value += coefficient * total / falling(n, r)
    return value


def mean(values: list[Fraction]) -> Fraction:
    return sum(values, Fraction(0)) / len(values)


def covariance(xs: list[Fraction], ys: list[Fraction]) -> Fraction:
    mx = mean(xs)
    my = mean(ys)
    return sum((x - mx) * (y - my) for x, y in zip(xs, ys)) / len(xs)


def run_kernel(seed: int) -> int:
    checks = 0
    kernel = random_symmetric_kernel(seed)
    proj = projections(kernel)

    # Pointwise ANOVA decomposition.
    for bits in ALL_LOCAL:
        total = sum(
            (proj[mask][bits] for mask in range(1 << C)),
            Fraction(0),
        )
        assert total == kernel[bits]
        checks += 1

    # Canonicality in each selected primitive coordinate.
    for mask in range(1, 1 << C):
        for idx in range(C):
            if not ((mask >> idx) & 1):
                continue
            for fixed in product((0, 1), repeat=C - 1):
                vals = []
                for bit in (0, 1):
                    assignment = [0] * C
                    pos = 0
                    for j in range(C):
                        if j == idx:
                            assignment[j] = bit
                        else:
                            assignment[j] = fixed[pos]
                            pos += 1
                    vals.append(proj[mask][tuple(assignment)])
                assert vals[0] + vals[1] == 0
                checks += 1

    # Orbit representatives and counting identity.
    seen: set[int] = set()
    reps = []
    for mask in range(1, 1 << C):
        if mask in seen:
            continue
        orbit = mask_orbit(mask)
        seen.update(orbit)
        rep = min(orbit)
        reps.append(rep)
        r = len(support(rep))
        aut = automorphism_count(rep)
        assert len(orbit) == falling(K, r) // aut
        checks += 1
    reps = tuple(sorted(reps))

    # Exhaustive grouped decomposition at n=4.
    n = 4
    total_coords = n + n * (n - 1) // 2
    values_n: list[Fraction] = []
    for global_bits in product((0, 1), repeat=total_coords):
        lhs = statistic(kernel, global_bits, n)
        rhs = grouped_rhs(proj, global_bits, n, reps)
        assert lhs == rhs
        values_n.append(lhs)
        checks += 1

    # Exact finite-n variance formula.
    actual_var = covariance(values_n, values_n)
    predicted_var = Fraction(0)
    for rep in reps:
        r = len(support(rep))
        aut = automorphism_count(rep)
        coefficient = Fraction(falling(K, r), aut)
        sigma2 = mean([value * value for value in proj[rep].values()])
        predicted_var += coefficient * coefficient * aut * sigma2 / falling(n, r)
    assert actual_var == predicted_var
    checks += 1

    # Exact covariance between levels 3 and 4, evaluated on the same size-4 space.
    values_3: list[Fraction] = []
    values_4: list[Fraction] = []
    for global_bits in product((0, 1), repeat=total_coords):
        # Restrict the size-4 assignment to the first three vertices.
        edges4 = tuple(combinations(range(4), 2))
        edge_index4 = {pair: 4 + idx for idx, pair in enumerate(edges4)}
        restricted = tuple(global_bits[i] for i in range(3)) + tuple(
            global_bits[edge_index4[pair]] for pair in combinations(range(3), 2)
        )
        values_3.append(statistic(kernel, restricted, 3))
        values_4.append(statistic(kernel, global_bits, 4))
    actual_cov = covariance(values_3, values_4)
    predicted_cov = Fraction(0)
    for rep in reps:
        r = len(support(rep))
        aut = automorphism_count(rep)
        coefficient = Fraction(falling(K, r), aut)
        sigma2 = mean([value * value for value in proj[rep].values()])
        predicted_cov += coefficient * coefficient * aut * sigma2 / falling(4, r)
    assert actual_cov == predicted_cov
    checks += 1

    return checks


def main() -> None:
    total = 0
    for seed in range(6):
        total += run_kernel(seed)
    print(f"verified {total:,} joint vertex-edge support identities")


if __name__ == "__main__":
    raise SystemExit(main())
