# 1. Exact truncations and approximate closure

The universal compression obstruction rules out one fixed finite-dimensional state for the entire central boundary. It does not rule out a convergent hierarchy of finite states. The projective structure supplies such a hierarchy canonically.

For a coherent profile $\mu=(\mu_n)_{n\geq0}$, define the level-$N$ truncation

```math
\Pi_N(\mu)
=
(\mu_0,\ldots,\mu_N).
```

By `findings-59.md`, this finite vector determines every upward transition through level $N-1$ exactly. The estimates below add quantitative stability and show that the truncated transition laws can be recovered graph-intrinsically from one large sample in an extremal sector.

# 2. A metric on projective profiles

Enumerate the finite unlabeled DAGs as

```math
F_1,F_2,\ldots,
```

with nondecreasing vertex number, and write

```math
p_j(\mu)=\mu_{|F_j|}(F_j).
```

Define

```math
d_{\mathrm{prof}}(\mu,\nu)
=
\sum_{j=1}^{\infty}
2^{-j}
|p_j(\mu)-p_j(\nu)|.
```

This metric generates the coordinatewise induced-pattern topology on the compact central simplex.

## Proposition 1. Uniform truncation error

If two coherent profiles agree in their first $M$ enumerated pattern coordinates, then

```math
d_{\mathrm{prof}}(\mu,\nu)
\leq
2^{-M}.
```

More generally, if the first $M$ coordinates are known with errors $\delta_1,\ldots,\delta_M$, then

```math
d_{\mathrm{prof}}(\mu,\nu)
\leq
\sum_{j=1}^M2^{-j}\delta_j
+
2^{-M}.
```

## Proof

Every coordinate lies in $[0,1]$. The unobserved tail is bounded by

```math
\sum_{j>M}2^{-j}=2^{-M}.
```

The displayed estimates follow by splitting the defining series at $M$.

Thus every sector is approximately specified, to any prescribed profile resolution, by finitely many pattern coordinates even though no fixed finite list identifies all sectors exactly.

# 3. Stability of the reconstructed growth kernel

For coherent profiles $\mu$ and $\nu$, let

```math
\delta_n(\mu,\nu)
=
\frac12
\sum_{G\in\mathfrak D_n}
|\mu_n(G)-\nu_n(G)|
```

be the total-variation distance between their level-$n$ distributions.

## Theorem 2. Predictive stability away from zero-mass states

Fix $G\in\mathfrak D_n$. Suppose

```math
\mu_n(G)\geq\eta,
\qquad
\nu_n(G)\geq\eta
```

for some $\eta>0$. Then

```math
\left\|
U_n^{\mu}(G,\cdot)
-
U_n^{\nu}(G,\cdot)
\right\|_{\mathrm{TV}}
\leq
\frac{
\delta_n(\mu,\nu)
+
\delta_{n+1}(\mu,\nu)
}{\eta}.
```

## Proof

Use the reconstruction formula

```math
U_n^{\mu}(G,H)
=
D_n(H,G)
\frac{\mu_{n+1}(H)}{\mu_n(G)}.
```

Writing $a=\mu_n(G)$ and $b=\nu_n(G)$, the triangle inequality gives

```math
\begin{aligned}
2\left\|U_n^{\mu}(G,\cdot)-U_n^{\nu}(G,\cdot)\right\|_{\mathrm{TV}}
&\leq
\frac1a
\sum_H D_n(H,G)
|\mu_{n+1}(H)-\nu_{n+1}(H)|\\
&\quad+
\left|\frac1a-\frac1b\right|
\sum_H D_n(H,G)\nu_{n+1}(H).
\end{aligned}
```

Coherence gives

```math
\sum_H D_n(H,G)\nu_{n+1}(H)=\nu_n(G)=b.
```

Since $0\leq D_n(H,G)\leq1$, the first sum is at most $2\delta_{n+1}$, while the second term becomes $|a-b|/a\leq2\delta_n/\eta$. Using $a\geq\eta$ yields the result.

The denominator is essential. Transition probabilities can be unstable near a state whose sector probability tends to zero. This is a genuine boundary singularity rather than a defect of the estimate.

# 4. Finite graphs already define coherent profiles

Let $K$ be any fixed finite DAG on $N$ vertices. For $F\in\mathfrak D_n$, define

```math
\widehat\mu_{K,n}(F)=T_F(K).
```

These are the isomorphism-class probabilities obtained by choosing a uniformly random $n$-vertex subset of $K$.

## Theorem 3. Exact empirical coherence

For every $n<N$,

```math
\widehat\mu_{K,n}(G)
=
\sum_{H\in\mathfrak D_{n+1}}
\widehat\mu_{K,n+1}(H)D_n(H,G).
```

Thus every finite DAG produces an exact truncated coherent profile through its own level. Whenever $T_G(K)>0$, the empirical transition

```math
\widehat U_{K,n}(G,H)
=
D_n(H,G)
\frac{T_H(K)}{T_G(K)}
```

is a probability distribution in $H$ and satisfies the exact forward-backward identity

```math
T_G(K)\widehat U_{K,n}(G,H)
=
T_H(K)D_n(H,G).
```

## Proof

Choose a uniformly random $n+1$-vertex subset of $K$, and then delete one of its vertices uniformly. The remaining $n$-vertex subset is uniform among all $n$-vertex subsets: every such subset has exactly $N-n$ possible added vertices. Conditional on the $n+1$-vertex isomorphism class being $H$, the probability that deletion produces $G$ is $D_n(H,G)$. The law of total probability gives empirical coherence. The transition statements then follow exactly as in `findings-59.md`.

# 5. Empirical recovery from one large graph

Let $X$ be an extremal exchangeable infinite DAG with coherent profile $\mu$, and let

```math
G_N=X|_{[N]}.
```

For a fixed finite DAG $F$, its induced density $T_F(G_N)$ converges almost surely to $\mu_{|F|}(F)$. Theorem 3 shows that the random vectors

```math
\widehat\mu_{N,n}(F)=T_F(G_N)
```

form exact finite coherent profiles before the limit is taken.

## Theorem 4. Consistent graph-intrinsic transition estimator

Fix $n$, $G\in\mathfrak D_n$, and $H\in\mathfrak D_{n+1}$, with $\mu_n(G)>0$. Then

```math
\widehat U_{N,n}(G,H)
=
D_n(H,G)
\frac{T_H(G_N)}{T_G(G_N)}
```

is eventually defined and satisfies

```math
\widehat U_{N,n}(G,H)
\longrightarrow
U_n^{\mu}(G,H)
```

almost surely. Because $\mathfrak D_n$ and $\mathfrak D_{n+1}$ are finite, the convergence holds jointly for every transition from every fixed positive-mass level-$n$ state.

## Proof

The extremal induced-density theorem gives

```math
T_G(G_N)\longrightarrow\mu_n(G),
\qquad
T_H(G_N)\longrightarrow\mu_{n+1}(H)
```

almost surely. The limiting denominator is positive, so the ratio converges. Multiplication by the fixed cotransition $D_n(H,G)$ gives the reconstructed up kernel of `findings-59.md`.

## Corollary 5. Quenched recovery in a central mixture

For a nonextremal central law with boundary variable $\Theta$, the same estimator converges almost surely to

```math
U_n^{\mu^{\Theta}}(G,H)
```

on every state having positive mass in the selected sector. A single large realization therefore estimates its own quenched extremal growth law rather than the prior mixture average.

# 6. Finite-horizon predictive closure

The empirical estimator gives a precise sense in which the infinite boundary profile is operationally accessible. For every fixed horizon $N_0$, one sufficiently large graph supplies consistent estimates of all coordinates

```math
\mu_n(G),
\qquad
n\leq N_0,
```

and therefore of all transitions

```math
U_n^{\mu}(G,H),
\qquad
n<N_0.
```

The required number of coordinates grows with the requested horizon. A fixed horizon therefore has a finite exact state, whereas simultaneous closure over all horizons and sectors requires the infinite projective state.

There is no contradiction between exact finite-horizon closure and the absence of a universal fixed finite-dimensional closure.

# 7. Continuous observables of the boundary

Let $\mathcal C$ be the compact central simplex in the profile topology. The algebra generated by the finite coordinate maps

```math
\mu\longmapsto p_F(\mu)
```

contains the constants and separates points of $\mathcal C$. The Stone-Weierstrass theorem therefore gives the following result.

## Proposition 6. Uniform finite-coordinate approximation

For every continuous functional

```math
A:\mathcal C\longrightarrow\mathbb R
```

and every $\epsilon>0$, there exist finite patterns $F_1,\ldots,F_M$ and a polynomial $Q$ such that

```math
\sup_{\mu\in\mathcal C}
\left|
A(\mu)
-
Q\left(
 p_{F_1}(\mu),\ldots,p_{F_M}(\mu)
\right)
\right|
<\epsilon.
```

Thus cylinder functions are uniformly dense in the continuous observables of the compact profile space.

Finite profiles are therefore universally sufficient for approximate evaluation of continuous macroscopic observables, even though they are not universally sufficient for exact sector identification.

# 8. Projective-state consequences

The closure problem now has a three-level answer.

First, the complete projective profile is an exact boundary state and determines the central growth law. Second, every fixed finite horizon has an exact finite-dimensional truncation. Third, no fixed finite dimension identifies every sector at every horizon, but finite truncations approximate the profile and all continuous boundary observables uniformly.

The remaining question is whether a physically or structurally selected subclass of sectors admits a lower-dimensional invariant manifold inside the projective profile space, and whether the reconstructed up kernels preserve that manifold.

Exact rational calculations on independently generated coherent profiles through four vertices satisfy the stated stability estimate. With exact level frequencies, the empirical reconstruction formula also agrees algebraically with the harmonic up kernel.
