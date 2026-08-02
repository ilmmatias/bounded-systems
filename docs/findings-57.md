# 1. Central mixtures and the boundary variable

The extremal theory treats a coherent measure that is equivalently a
dissociated exchangeable infinite DAG law. A general coherent measure need
not be extremal. It decomposes into extremal sectors, and that
decomposition introduces a qualitatively different continuum mode.

Let $\mathcal E$ denote the extreme boundary of the central simplex, and
let $\Theta$ be the random extremal sector in the ergodic decomposition of
a coherent measure $\mathbb P$. Conditional on $\Theta=\vartheta$, the
infinite DAG law is dissociated and has deterministic finite-pattern
coordinates

```math
p_F(\vartheta)
=
\mathbb P
\left(
G_\infty|_{[k]}\cong F
\mid
\Theta=\vartheta
\right).
```

The variable $\Theta$ is invariant under finite relabelings. It is the
global variable that disappears in an extremal Aldous-Hoover
representation and remains in a nonextremal one.

# 2. Random continuum profile

For a finite DAG $F$, retain the induced density $T_n(F)$.

## Theorem 1. Sector-valued continuum limit

For every finite DAG pattern $F$,

```math
T_n(F)
\longrightarrow
p_F(\Theta)
```

almost surely and in $L^2$. The complete induced-density profile converges
coordinatewise to the random boundary point

```math
\Phi_\infty(\Theta)
=
\left(p_F(\Theta)\right)_{F\in\mathcal D_{\mathrm{fin}}}.
```

The limit is deterministic exactly when the coherent measure is supported
on extremal sectors having the same finite-pattern profile; in particular,
it is deterministic for every extremal coherent measure.

## Proof

Conditional on $\Theta$, the law is extremal. The almost-sure convergence
theorem of `findings-47.md` therefore gives

```math
T_n(F)\longrightarrow p_F(\Theta)
```

with conditional probability one. Integrating the conditional null set
proves unconditional almost-sure convergence. Since $0\leq T_n(F)\leq1$,
bounded convergence gives $L^2$ convergence.

The joint coordinate statement follows because the set of finite DAG
isomorphism classes is countable.

For a general central law the continuum object is therefore the random
extremal boundary point $\Phi_\infty(\Theta)$ rather than a single
deterministic kernel.

# 3. Exact degree-zero covariance decomposition

Conditional on $\Theta=\vartheta$, `findings-56.md` supplies intrinsic
coefficients

```math
C_r^{\vartheta}(F,K),
\qquad r\geq1.
```

The conditional expectation of every induced density is independent of the
level:

```math
\mathbb E[T_n(F)\mid\Theta]
=
p_F(\Theta).
```

Define the sector-mixture coefficient

```math
C_0(F,K)
=
\operatorname{Cov}
\left(
 p_F(\Theta),p_K(\Theta)
\right)
```

and, for $r\geq1$,

```math
\overline C_r(F,K)
=
\mathbb E
\left[
 C_r^{\Theta}(F,K)
\right].
```

## Theorem 2. Central covariance spectrum including order zero

For $n\leq m$,

```math
\operatorname{Cov}
\left(
T_n(F),T_m(K)
\right)
=
C_0(F,K)
+
\sum_{r=1}^{\min(k,\ell)}
\frac{\overline C_r(F,K)}{(m)_r}.
```

## Proof

The law of total covariance gives

```math
\operatorname{Cov}(T_n(F),T_m(K))
=
\operatorname{Cov}
\left(
\mathbb E[T_n(F)\mid\Theta],
\mathbb E[T_m(K)\mid\Theta]
\right)
+
\mathbb E
\left[
\operatorname{Cov}
\left(
T_n(F),T_m(K)
\mid
\Theta
\right)
\right].
```

The first term is $C_0(F,K)$. Conditional on $\Theta$, the exact extremal
covariance expansion of `findings-56.md` applies. Taking expectations
gives the result.

The coefficient $C_0$ has no decaying denominator. It survives at infinite
size:

```math
\lim_{n,m\to\infty}
\operatorname{Cov}
\left(
T_n(F),T_m(K)
\right)
=
C_0(F,K).
```

This is the covariance of uncertainty about which extremal sector was
selected.

# 4. Frozen mode and positive relaxation spectrum

The decomposition

```math
T_n(F)-\mathbb E[T_n(F)]
=
\left[
 p_F(\Theta)-\mathbb E p_F(\Theta)
\right]
+
\left[
 T_n(F)-p_F(\Theta)
\right]
```

separates two kinds of variation.

The first term is constant in the growth level. Under logarithmic size it
has relaxation rate zero. The second term is the within-sector
fluctuation and decomposes into positive support orders with rates

```math
\frac12,1,\frac32,\ldots .
```

The full central spectrum therefore begins at degree zero:

```math
0,\frac12,1,\frac32,\ldots .
```

The zero mode is the invariant information carried by the
ergodic-component variable, not a finite-pattern overlap effect.

If an uncentered statistic does not concentrate, the obstruction may be a
sector mixture rather than a failure of stable coefficients. Centering by
the random boundary profile $p_F(\Theta)$ removes the degree-zero term and
exposes the positive relaxation hierarchy.

## Corollary 3. Extremality removes the frozen mode

The following conditions are equivalent:

1. $C_0(F,F)=0$ for every finite DAG $F$;
2. $p_F(\Theta)$ is almost surely constant for every $F$;
3. $\Phi_\infty(\Theta)$ is almost surely deterministic.

If finite-pattern profiles separate the extreme boundary, these are
further equivalent to extremality of the coherent measure.

## Proof

The first two conditions are equivalent because $C_0(F,F)$ is the variance
of $p_F(\Theta)$. Countability of the finite pattern family gives the
equivalence with a deterministic profile. Separation of the extreme
boundary then identifies a unique sector.

# 5. Conditional functional limits

A single unconditional normalization need not exist when different
extremal sectors have different principal degrees. For a pattern $F$, let

```math
d_F(\vartheta)
=
\min
\left\{
 r\geq1:
 C_r^{\vartheta}(F,F)>0
\right\}.
```

The boundary decomposes into strata on which $d_F$ is constant.

## Theorem 4. Sectorwise process limit

Conditional on $\Theta=\vartheta$,

```math
m_N(s)^{d_F(\vartheta)/2}
\left[
T_{m_N(s)}(F)-p_F(\vartheta)
\right]
```

converges to the stationary Wick process of `findings-56.md` with
conditional covariance

```math
C_{d_F(\vartheta)}^{\vartheta}(F,F)
 e^{-d_F(\vartheta)|s-t|/2}.
```

If $d_F(\Theta)=d$ almost surely and the conditional principal fields form
a measurable family, then the unconditional centered process converges to
the corresponding mixture of stationary order-$d$ Wick processes.

## Proof

The first statement is the extremal process theorem applied conditionally.
For the second, conditional bounded convergence of finite-dimensional
characteristic functions and conditional tightness yield the mixture
limit.

The unconditional limit need not be Gaussian or Markov even when every
conditional limit is a Gaussian Ornstein-Uhlenbeck process. Random
sector-dependent variances, kernels, or covariance matrices produce a
mixture of Gaussian processes. The boundary variable must be adjoined to
recover a Markov description of the full quenched system.

# 6. Selection as removal of persistent uncertainty

Every extremal sector has a deterministic continuum pattern profile and a
positive-order fluctuation spectrum. A nonextremal central law has, in
addition, a degree-zero mode recording uncertainty about the extremal
sector. Selecting an extremal law removes this frozen uncertainty but does
not create the within-sector dynamics; those positive-order processes
already exist conditionally.

A central coherent law first selects a random extreme boundary point
$\Theta$. Conditional on $\Theta$, the continuum profile is deterministic
and the remaining finite-size behavior consists of positive-order
fluctuations.

A foundational selection principle would therefore constrain or determine
the distribution of $\Theta$. There are three mathematically distinct
outcomes:

1. a unique extremal sector is forced;
2. a family of extremal sectors remains, with no canonical mixture;
3. a nontrivial central mixture is itself selected, leaving a persistent
   degree-zero variable.

In the third possibility the degree-zero uncertainty persists at every
level rather than decaying with the positive support orders.

# 7. A two-sector exact example

Consider a latent total-order DAG in which each permitted edge is present
independently with probability $R$, where

```math
R=
\begin{cases}
 a,&\text{with probability }\alpha,\\
 b,&\text{with probability }1-\alpha.
\end{cases}
```

Conditional on $R$, orient every present edge from the smaller latent mark
to the larger one. Let $E_n$ be the edge density. Then

```math
\mathbb E[E_n\mid R]=R
```

and, for $n\leq m$,

```math
\operatorname{Cov}(E_n,E_m\mid R)
=
\frac{2R(1-R)}{(m)_2}.
```

The unconditional covariance is therefore

```math
\operatorname{Cov}(E_n,E_m)
=
\alpha(1-\alpha)(a-b)^2
+
\frac{2\mathbb E[R(1-R)]}{(m)_2}.
```

The first term is the frozen order-zero mode. The second is the rate-one
pair-noise mode. No $\sqrt n$ vertex mode occurs because, conditional on
$R$, edge presence is independent of the latent order marks.

This example separates sector uncertainty from within-sector
stochasticity in an exact finite-level identity.

# 8. Literature relation

The decomposition into a random extreme point and a conditionally
dissociated law is the ergodic or Choquet decomposition of an exchangeable
array, for which see D. J. Aldous, *Exchangeability and related topics*,
École d'Été de Probabilités de Saint-Flour XIII, Lecture Notes in
Mathematics 1117, Springer, 1985. In the graph-limit formulation of
P. Diaconis and S. Janson, *Graph limits and exchangeable random graphs*,
Rendiconti di Matematica 28 (2008), 33-61, arXiv:0712.2749, random graph
limits correspond to general exchangeable laws, while deterministic graph
limits correspond to extreme laws. The global Aldous-Hoover variable
records the same mixture.

The present addition is the exact spectral interpretation in logarithmic
growth: the ergodic-component variable is a support-degree-zero mode,
while all finite relational fluctuations inside a sector occupy positive
half-integer rates.
