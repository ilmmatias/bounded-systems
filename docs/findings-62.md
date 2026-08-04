# 1. Finite endpoint bridges

The projective reconstruction of `findings-59.md` and the empirical
coherence of `findings-61.md` have a direct interpretation in the theory
of central measures. Every finite DAG is a terminal vertex of the branching
graph, and uniform measure on the finite paths leading to that vertex
defines a central bridge. The bridge marginals are exactly the
induced-subgraph frequencies of the terminal DAG.

Let $K\in\mathfrak D_N$. For $0\leq n\leq N$, define the multi-step
deletion kernel

```math
D_{n,N}(K,G)
=
\sum_{G=G_n,\ldots,G_N=K}
\prod_{j=n}^{N-1}D_j(G_{j+1},G_j).
```

The sum runs over all chains in the DAG branching graph from $G$ to $K$.

# 2. Multi-step deletion equals induced density

## Theorem 1. Endpoint cotransition identity

For every $G\in\mathfrak D_n$,

```math
D_{n,N}(K,G)=T_G(K).
```

Equivalently, sequentially deleting $N-n$ uniformly chosen vertices
from $K$ produces the same unlabeled distribution as choosing a uniform
$n$-vertex subset directly.

## Proof

At each deletion step, the cotransition $D_j(H,G)$ is the probability
that a uniformly selected vertex of $H$ can be deleted to obtain a graph
isomorphic to $G$. Sequential uniform deletion produces a uniformly
random ordered list of $N-n$ deleted vertices. Every surviving $n$-vertex
subset has exactly $(N-n)!$ deletion orders, so the surviving subset
is uniform. Its isomorphism-class distribution is therefore $T_G(K)$.

The Chapman-Kolmogorov expansion of the sequential deletion law is the
displayed sum defining $D_{n,N}$.

# 3. The uniform central bridge

Define the truncated profile

```math
\mu_n^K(G)=T_G(K),
\qquad
0\leq n\leq N.
```

Its terminal distribution is $\mu_N^K=\delta_K$.

## Theorem 2. Finite endpoint bridge

The family $(\mu_n^K)_{0\leq n\leq N}$ is the level-marginal system of
the uniform probability measure on all multiplicity paths from the root
to $K$. Its harmonic coordinates are

```math
h_n^K(G)
=
\frac{T_G(K)}{\dim(G)},
```

and its upward transitions are

```math
U_n^K(G,H)
=
D_n(H,G)
\frac{T_H(K)}{T_G(K)}
```

on states satisfying $T_G(K)>0$.

## Proof

The canonical cotransitions are the backward transitions of uniform
path measure to a fixed endpoint. Theorem 1 gives its level-$n$ marginal
as $T_G(K)$. Alternatively, exact empirical coherence from `findings-61.md`
shows that $(\mu_n^K)$ is the unique truncated coherent system with
terminal mass $\delta_K$.

The harmonic and upward formulas then follow from `findings-59.md`.
Every path ending at $G$ has bridge cylinder probability

```math
h_n^K(G)=\frac{\mu_n^K(G)}{\dim(G)}.
```

At the terminal level, every path to $K$ consequently has probability
$1/\dim(K)$, so the bridge is uniform.

# 4. Deterministic approximation of central measures

Let $(K_N)$ be any sequence of finite DAGs with $|K_N|=N$. Assume that
for every fixed finite DAG $F$,

```math
T_F(K_N)\longrightarrow p_F.
```

## Theorem 3. Bridge convergence from pattern convergence

The limits $(p_F)$ form a coherent profile $\mu$, with

```math
\mu_n(F)=p_F,
\qquad
F\in\mathfrak D_n.
```

The uniform central bridges to $K_N$ converge projectively to the central
measure determined by $\mu$: every fixed cylinder probability converges.
For a path cylinder ending at $G\in\mathfrak D_n$,

```math
\frac{T_G(K_N)}{\dim(G)}
\longrightarrow
\frac{\mu_n(G)}{\dim(G)}.
```

If $\mu_n(G)>0$, then for every $H\in\mathfrak D_{n+1}$,

```math
U_n^{K_N}(G,H)
\longrightarrow
U_n^{\mu}(G,H).
```

## Proof

Each finite endpoint profile is exactly coherent:

```math
T_G(K_N)
=
\sum_H T_H(K_N)D_n(H,G).
```

Passing to the coordinatewise limit gives coherence of $p_F$. The
coordinates at every fixed level sum to one, so they define a coherent
probability profile.

A cylinder determined by a finite path ending at $G$ has bridge probability
$T_G(K_N)/\dim(G)$. These cylinder probabilities converge to those of
the central measure defined by $\mu$. Since cylinder probabilities
determine a path measure, this is projective convergence to that central
measure. The transition convergence is the ratio formula of Theorem 2
together with the positive limiting denominator.

# 5. Approximation along an extremal sample

Let $X$ be an extremal exchangeable infinite DAG with coherent profile
$\mu$, and set

```math
K_N=X|_{[N]}.
```

## Corollary 4. Almost-sure endpoint approximation

With probability one, the uniform central bridges to the random endpoints
$K_N$ converge in the cylinder or projective sense to the original
extremal central measure. Equivalently, for every fixed finite DAG $F$,

```math
D_{|F|,N}(K_N,F)
=
T_F(K_N)
\longrightarrow
\mu_{|F|}(F).
```

The bridge harmonic functions and upward transitions converge on every
fixed positive-mass state.

## Proof

The almost-sure induced-density theorem of `findings-47.md` gives
coordinatewise convergence of $T_F(K_N)$ to $\mu_{|F|}(F)$. Theorem 3
applies simultaneously to the countable family of finite DAGs.

## Corollary 5. Nonextremal endpoint approximation

For a general central law with boundary variable $\Theta$, the random
endpoint bridges converge almost surely to the selected extremal central
measure $\mu^{\Theta}$, not to the prior mixture. The remote endpoint
asymptotically reveals the degree-zero boundary variable of `findings-57.md`.

# 6. Relation to the ergodic method

The preceding result is the DAG form of the ergodic method for central
measures on graded graphs. A remote vertex $K_N$ defines a uniform
measure on its finite predecessor paths. An extremal central measure is
recovered as the limit of such uniform endpoint measures along almost
every path in the sector.

In the DAG branching graph, the uniform predecessor bridge to $K_N$ is
exactly its uniform induced-subgraph profile.

The bridge marginals are ordinary induced-DAG densities, so computing
them requires no separate path enumeration.

This also supplies a deterministic existence statement. Every extremal
coherent profile admits at least one sequence of finite DAG endpoints
whose uniform bridges converge to it: choose any infinite sample in the
probability-one set of Corollary 4 and retain its finite restrictions.

# 7. Central bridges and finite observations

The exact finite and infinite objects fit into one sequence:

```math
K_N
\longmapsto
(T_F(K_N))_F
\longmapsto
h^{K_N}
\longmapsto
U^{K_N}
\longrightarrow
\mu
\longmapsto
h^{\mu}
\longmapsto
U^{\mu}.
```

Thus the continuum growth law can be approached entirely through finite
DAGs, uniform deletion, and induced-subgraph counting.

Exhaustive calculation for every terminal DAG through four vertices
confirms Theorems 1 and 2: uniform induced-subgraph distributions
coincide with the composed deletion cotransitions, satisfy exact coherence,
and reconstruct normalized bridge up kernels.

# 8. Literature relation

Vershik describes central measures as a projective limit of finite
simplices and emphasizes approximation by uniform conditional measures
associated with remote vertices. The result above makes that method
explicit for the DAG branching graph by identifying the remote-vertex
cotransition coordinates with induced-subgraph densities.

Reference:

- A. M. Vershik, *The problem of describing central measures on the path
  spaces of graded graphs*, Functional Analysis and Its Applications 48
  (2014), 256-271, arXiv:1408.3291.
