# 1. Robust finite selection

Exact finite forcing is useful only if small errors in the selected
relational frequencies cannot produce a macroscopically unrelated
boundary law. The compact projective structure of the central simplex
gives this robustness without requiring an explicit analytic modulus.

Let $\mathcal C$ be the space of coherent central profiles

```math
\mu=(\mu_n)_{n\geq0}.
```

Equip it with the projective metric

```math
d_{\mathrm{proj}}(\mu,\nu)
=
\sum_{n\geq0}2^{-n-1}
\|\mu_n-\nu_n\|_{\mathrm{TV}}.
```

Each level simplex is finite-dimensional and compact, and coherence is a
closed condition. Hence $\mathcal C$ is compact.

Let $f_1,\ldots,f_m$ be finite linear combinations of pattern
coordinates, and let $\mu^\star$ be their unique common target:

```math
f_j(\mu)=f_j(\mu^\star)
\quad(1\leq j\leq m)
\quad\Longrightarrow\quad
\mu=\mu^\star.
```

Define the forcing energy

```math
\mathcal E(\mu)
=
\sum_{j=1}^m
\left(
 f_j(\mu)-f_j(\mu^\star)
\right)^2.
```

# 2. Compactness gap

## Theorem 1. Robust projective forcing

For every $\varepsilon>0$, there exists $\delta(\varepsilon)>0$ such that

```math
\mathcal E(\mu)<\delta(\varepsilon)
```

implies

```math
d_{\mathrm{proj}}(\mu,\mu^\star)<\varepsilon.
```

## Proof

The closed set

```math
K_\varepsilon
=
\{\mu\in\mathcal C:
 d_{\mathrm{proj}}(\mu,\mu^\star)\geq\varepsilon\}
```

is compact. The continuous function $\mathcal E$ is strictly positive on
this set because $\mu^\star$ is its unique zero. Its minimum on
$K_\varepsilon$ is therefore positive.

The argument is a compactness argument and produces no bound on
$\delta(\varepsilon)$. A quantitative modulus requires an explicit
positive lower bound for $\mathcal E$ on $K_\varepsilon$.

# 3. Finite endpoint stability

For a finite DAG $K$ on $N$ vertices, evaluate every forcing coordinate
through its empirical induced-subgraph profile and write the result as
$f_j(K)$. Set

```math
\mathcal E_N(K)
=
\sum_{j=1}^m
\left(
 f_j(K)-f_j(\mu^\star)
\right)^2.
```

## Theorem 2. Finite profile stability

For every fixed level $L$ and every $\varepsilon>0$, there are $\delta>0$
and $N_0$ such that, whenever $N\geq N_0$,

```math
\mathcal E_N(K)<\delta
```

implies

```math
\left\|
(T_G(K))_{G\in\mathfrak D_L}
-
\mu_L^\star
\right\|_{\mathrm{TV}}
<\varepsilon.
```

## Proof

If the statement failed, there would be finite DAGs $K_r$ with orders
tending to infinity, forcing energies tending to zero, and level-$L$
profiles bounded away from $\mu_L^\star$. A diagonal subsequence of their
finite pattern profiles converges at every fixed level. Exact empirical
coherence from `findings-61.md` passes to the limit and produces a central
profile $\mu$. Continuity gives $\mathcal E(\mu)=0$, so finite forcing
gives $\mu=\mu^\star$, contradicting the level-$L$ separation.

# 4. Stability of reconstructed growth laws

Let $G\in\mathfrak D_n$ satisfy $\mu_n^\star(G)>0$. The empirical bridge
transition reconstructed from a finite endpoint is

```math
U_n^K(G,H)
=
D_n(H,G)
\frac{T_H(K)}{T_G(K)}.
```

## Corollary 3. Robust predictive closure

If $\mathcal E_N(K_N)\to0$, then for every fixed positive-mass state $G$,

```math
U_n^{K_N}(G,\cdot)
\longrightarrow
U_n^{\mu^\star}(G,\cdot)
```

in total variation.

## Proof

Theorem 2 gives convergence of the level-$n$ and level-$n+1$ empirical
profiles. The ratio formula and the positive limiting denominator give
transition convergence. The quantitative estimate of `findings-61.md`
gives the corresponding local modulus away from zero-mass states.

# 5. Application to ordered layers

For the deterministic ordered-layer sector of `findings-66.md`, take as
forcing coordinates the two forbidden three-vertex densities together
with the finitely many bi-star moments occurring in $Q_p$. Then small
forcing energy implies closeness of every fixed finite induced-DAG
distribution and every fixed reconstructed up transition.

Thus absolute finite selection controls the finite relational predictions
used by the growth process.

# 6. Graph-intrinsic testing with approximate data

The result also supplies a graph-intrinsic test of a proposed selected
sector. A large endpoint need not be assigned latent layers before
testing. One computes only the finite forcing coordinates. If their
energy is small, every bounded observation horizon has a profile and
growth kernel close to the target sector.

The test distinguishes two failures. A nonzero forbidden-pattern
contribution rejects the strict weak-order structure itself. A nonzero
degree-polynomial contribution retains ordered layers while rejecting the
prescribed layer masses.

Enumeration of ordered rational compositions gives finite forcing gaps
consistent with Theorems 1 and 2. These values are finite-level
diagnostics; compactness, rather than enumeration, proves the general
statements.
