#!/usr/bin/env python3
"""Verify the Dirichlet route law and its Beta consequences independently."""

from __future__ import annotations

import math
import random
import statistics
from fractions import Fraction
from typing import Iterable

SEED = 0x103D1A1C
SAMPLES = 30_000
HORIZONS = (1, 3, 8, 32)


class Checks:
    def __init__(self) -> None:
        self.count = 0

    def require(self, condition: bool, message: str) -> None:
        if not condition:
            raise AssertionError(message)
        self.count += 1

    def close(self, actual: Fraction, expected: Fraction, message: str) -> None:
        self.require(actual == expected, f"{message}: {actual} != {expected}")


# Exact Dirichlet identities


def route_parameters(horizon: int) -> tuple[int, ...]:
    """Parameters of (g_0,...,g_{p+1}) for a route with p edges."""

    return (1, *(2 for _ in range(horizon)), 1)


def dirichlet_simplex_integral(parameters: Iterable[int]) -> Fraction:
    values = tuple(parameters)
    numerator = math.prod(math.factorial(value - 1) for value in values)
    denominator = math.factorial(sum(values) - 1)
    return Fraction(numerator, denominator)


def beta_mean(alpha: int, beta: int) -> Fraction:
    return Fraction(alpha, alpha + beta)


def beta_variance(alpha: int, beta: int) -> Fraction:
    total = alpha + beta
    return Fraction(alpha * beta, total * total * (total + 1))


def beta_third_central(alpha: int, beta: int) -> Fraction:
    total = alpha + beta
    return Fraction(
        2 * (beta - alpha) * alpha * beta,
        total**3 * (total + 1) * (total + 2),
    )


def beta_raw_moment(alpha: int, beta: int, power: int) -> Fraction:
    moment = Fraction(1)
    for offset in range(power):
        moment *= Fraction(alpha + offset, alpha + beta + offset)
    return moment


def continuum_coordinate_expectation(
    alpha: int, beta: int
) -> tuple[Fraction, ...]:
    x1 = beta_raw_moment(alpha, beta, 1)
    x2 = beta_raw_moment(alpha, beta, 2)
    x4 = beta_raw_moment(alpha, beta, 4)
    one_minus_x2 = beta_raw_moment(beta, alpha, 2)
    one_minus_x4 = beta_raw_moment(beta, alpha, 4)
    return (
        one_minus_x2 / 2,
        x2 / 2,
        one_minus_x4 / 24,
        x4 / 24,
        Fraction(1, 8) - x1 / 6 + x4 / 24,
        Fraction(1, 8) - (1 - x1) / 6 + one_minus_x4 / 24,
    )


def decay_power(points: Iterable[tuple[int, float]]) -> float:
    values = tuple(points)
    log_x = [math.log(x) for x, _ in values]
    log_y = [math.log(y) for _, y in values]
    mean_x = statistics.fmean(log_x)
    mean_y = statistics.fmean(log_y)
    return -sum(
        (x - mean_x) * (y - mean_y)
        for x, y in zip(log_x, log_y, strict=True)
    ) / sum((x - mean_x) ** 2 for x in log_x)


def polynomial_product(
    left: tuple[Fraction, ...], right: tuple[Fraction, ...]
) -> tuple[Fraction, ...]:
    out = [Fraction(0) for _ in range(len(left) + len(right) - 1)]
    for first, left_value in enumerate(left):
        for second, right_value in enumerate(right):
            out[first + second] += left_value * right_value
    return tuple(out)


def polynomial_integral(polynomial: tuple[Fraction, ...]) -> Fraction:
    return sum(
        (coefficient / (degree + 1) for degree, coefficient in enumerate(polynomial)),
        start=Fraction(0),
    )


# Independent Monte Carlo sampler and integer-parameter Beta CDF


def sample_dirichlet(parameters: tuple[int, ...], rng: random.Random) -> list[float]:
    gamma = [rng.gammavariate(parameter, 1.0) for parameter in parameters]
    total = sum(gamma)
    return [value / total for value in gamma]


def beta_cdf_integer(value: float, alpha: int, beta: int) -> float:
    if value <= 0.0:
        return 0.0
    if value >= 1.0:
        return 1.0

    degree = alpha + beta - 1
    return sum(
        math.comb(degree, i)
        * value**i
        * (1.0 - value) ** (degree - i)
        for i in range(alpha, degree + 1)
    )


def kolmogorov(values: list[float], alpha: int, beta: int) -> float:
    ordered = sorted(values)
    count = len(ordered)
    maxError = 0.0

    for i, value in enumerate(ordered, 1):
        target = beta_cdf_integer(value, alpha, beta)
        maxError = max(
            maxError,
            abs((i - 1) / count - target),
            abs(i / count - target),
        )

    return maxError


def correlation(left: list[float], right: list[float]) -> float:
    left_mean = statistics.fmean(left)
    right_mean = statistics.fmean(right)
    covariance = statistics.fmean(
        (x - left_mean) * (y - right_mean)
        for x, y in zip(left, right, strict=True)
    )
    left_variance = statistics.fmean((x - left_mean) ** 2 for x in left)
    right_variance = statistics.fmean((y - right_mean) ** 2 for y in right)
    return covariance / math.sqrt(left_variance * right_variance)


def check_sample_mean(
    values: list[float], alpha: int, beta: int, context: str, checks: Checks
) -> None:
    target_mean = float(beta_mean(alpha, beta))
    target_variance = float(beta_variance(alpha, beta))
    standard_error = math.sqrt(target_variance / len(values))

    checks.require(
        abs(statistics.fmean(values) - target_mean) <= 6.0 * standard_error,
        f"{context}: sample mean misses the exact target",
    )
    checks.require(
        kolmogorov(values, alpha, beta) <= 0.02,
        f"{context}: empirical CDF misses the exact Beta law",
    )


def verify_exact_identities(checks: Checks) -> None:
    for horizon in range(1, 13):
        parameters = route_parameters(horizon)
        checks.close(
            dirichlet_simplex_integral(parameters),
            Fraction(1, math.factorial(2 * horizon + 1)),
            f"p={horizon} route normalization",
        )

        for position in range(horizon + 1):
            left = sum(parameters[: position + 1])
            right = sum(parameters[position + 1 :])
            checks.require(
                (left, right)
                == (2 * position + 1, 2 * (horizon - position) + 1),
                f"p={horizon}, r={position} marginal parameters differ",
            )

        for position in range(horizon):
            remaining = horizon - position
            tail = sum(parameters[position + 1 :])
            checks.require(
                (parameters[position + 1], tail - parameters[position + 1])
                == (2, 2 * remaining - 1),
                f"p={horizon}, r={position} conditional parameters differ",
            )

    for horizon in range(1, 65):
        checks.close(
            beta_mean(2, 2 * horizon),
            Fraction(1, horizon + 1),
            f"p={horizon} internal-spacing mean",
        )
        checks.close(
            beta_variance(2, 2 * horizon),
            Fraction(horizon, (horizon + 1) ** 2 * (2 * horizon + 3)),
            f"p={horizon} internal-spacing variance",
        )
        checks.close(
            beta_third_central(2, 2 * horizon),
            Fraction(
                horizon * (horizon - 1),
                (horizon + 1) ** 3
                * (horizon + 2)
                * (2 * horizon + 3),
            ),
            f"p={horizon} internal-spacing third moment",
        )

    mean_norms: list[tuple[int, float]] = []
    for horizon in (4, 8, 16, 32):
        first = continuum_coordinate_expectation(1, 2 * horizon + 1)
        last = continuum_coordinate_expectation(2 * horizon + 1, 1)
        squared_norm = sum(
            ((right - left) / horizon) ** 2
            for left, right in zip(first, last, strict=True)
        )
        mean_norms.append((horizon, math.sqrt(float(squared_norm))))
    checks.require(
        abs(decay_power(mean_norms) - 0.909_222_464_588_296_3) < 1.0e-14,
        "finite-grid continuum-coordinate mean decay power differs",
    )

    gradient = (
        (Fraction(-1), Fraction(1)),
        (Fraction(0), Fraction(1)),
        (
            Fraction(-1, 6),
            Fraction(1, 2),
            Fraction(-1, 2),
            Fraction(1, 6),
        ),
        (Fraction(0), Fraction(0), Fraction(0), Fraction(1, 6)),
        (Fraction(-1, 6), Fraction(0), Fraction(0), Fraction(1, 6)),
        (
            Fraction(0),
            Fraction(1, 2),
            Fraction(-1, 2),
            Fraction(1, 6),
        ),
    )
    gradient_norm = sum(
        (
            polynomial_integral(polynomial_product(component, component))
            for component in gradient
        ),
        start=Fraction(0),
    )
    endpoint_displacement_norm = sum(
        (polynomial_integral(component) ** 2 for component in gradient),
        start=Fraction(0),
    )
    checks.close(
        gradient_norm,
        Fraction(179, 252),
        "continuum-coordinate gradient norm",
    )
    checks.close(
        gradient_norm / 2,
        Fraction(179, 504),
        "leading within-position covariance trace",
    )
    checks.close(
        endpoint_displacement_norm,
        Fraction(77, 144),
        "continuum-coordinate endpoint displacement norm",
    )
    checks.close(
        gradient_norm - endpoint_displacement_norm,
        Fraction(59, 336),
        "leading between-position covariance trace",
    )
    third_squared = sum(
        (
            (
                polynomial_integral(
                    polynomial_product(
                        polynomial_product(first, second),
                        third,
                    )
                )
                / 2
            )
            ** 2
            for first in gradient
            for second in gradient
            for third in gradient
        ),
        start=Fraction(0),
    )
    checks.close(
        third_squared,
        Fraction(68_989_499, 1_371_686_400),
        "leading conditional third-tensor norm squared",
    )


def verify_monte_carlo(checks: Checks) -> None:
    rng = random.Random(SEED)

    for horizon in HORIZONS:
        parameters = route_parameters(horizon)
        routes = [sample_dirichlet(parameters, rng) for _ in range(SAMPLES)]

        positions = sorted({0, horizon // 2, horizon})
        for position in positions:
            values = [sum(route[: position + 1]) for route in routes]
            check_sample_mean(
                values,
                2 * position + 1,
                2 * (horizon - position) + 1,
                f"p={horizon}, r={position} marginal",
                checks,
            )

        transitions = sorted({0, horizon // 2, horizon - 1})
        for position in transitions:
            remaining = horizon - position
            sources = [sum(route[: position + 1]) for route in routes]
            fractions = [
                route[position + 1] / (1.0 - source)
                for route, source in zip(routes, sources, strict=True)
            ]

            check_sample_mean(
                fractions,
                2,
                2 * remaining - 1,
                f"p={horizon}, r={position} conditional fraction",
                checks,
            )
            checks.require(
                abs(correlation(sources, fractions)) <= 0.03,
                f"p={horizon}, r={position}: neutrality check failed",
            )


def main() -> None:
    checks = Checks()
    verify_exact_identities(checks)
    verify_monte_carlo(checks)
    print(f"verified {checks.count} exact and sampled route-scaling checks")


if __name__ == "__main__":
    raise SystemExit(main())
