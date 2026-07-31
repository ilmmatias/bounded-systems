# 1. A stochastic absolutely forced sector

The deterministic ordered-layer theorem of `findings-66.md` uses strict weak-order identities. Missing cross-layer edges destroy those identities, so stochastic ordered sectors require a different selector. In the two-layer case, rooted degrees and one quasirandomness equality suffice.

Fix

```math
0<\theta<1,
\qquad
0<r\leq1.
```

The target sector $\mu^{\theta,r}$ has a source layer of mass $\theta$, a sink layer of mass $1-\theta$, and independent source-to-sink edges with probability $r$.

# 2. Height-one structure

Let $P_2$ be the directed path with two consecutive edges. Its homomorphism density is

```math
t(P_2)
=
\mathbb E[D^-D^+].
```

## Proposition 1. Source-sink decomposition

If a central DAG law satisfies

```math
t(P_2)=0,
```

then almost every vertex has either zero limiting indegree or zero limiting outdegree. Every edge runs from a source vertex to a sink vertex, up to null sets.

## Proof

The product $D^-D^+$ is nonnegative, so zero expectation makes it vanish almost surely. A positive-density set of edges entering and leaving the same vertex would give positive path density. Vertices with positive outdegree are therefore sources, vertices with positive indegree are sinks, and all remaining vertices are isolated.

# 3. Degree-pair forcing

Define the target degree points

```math
z_S=(0,r(1-\theta)),
\qquad
z_T=(r\theta,0),
```

and the nonnegative polynomial

```math
Q_{\theta,r}(x,y)
=
\left(x^2+(y-r(1-\theta))^2\right)
\left((x-r\theta)^2+y^2\right).
```

Assume

the degree-polynomial constraint satisfies

```math
\mathbb E[Q_{\theta,r}(D^-,D^+)]=0.
```

Then the root degree pair belongs almost surely to $\{z_S,z_T\}$. Since both points have a positive nonzero coordinate, there is no isolated mass.

Let $s$ be the source mass. Counting the same edge density from its two endpoints gives

```math
s\,r(1-\theta)
=
(1-s)r\theta.
```

Hence

```math
s=\theta.
```

Thus the degree polynomial fixes both layer masses and the normalized row and column degrees of the cross-layer kernel.

# 4. Directed four-cycle equality

Let $B_{2,2}$ be the four-vertex DAG with two source vertices, two sink vertices, and all four directed source-to-sink edges.

On the recovered source and sink spaces, use normalized probability measures and let

```math
W:S\times T\to[0,1]
```

be the cross-layer edge kernel. The degree constraints give

```math
\int_T W(x,y)\,dy=r
```

for almost every source $x$, and

```math
\int_S W(x,y)\,dx=r
```

for almost every sink $y$.

## Proposition 2. Bipartite quasirandomness inequality

The directed four-edge density satisfies

```math
t(B_{2,2})
\geq
\theta^2(1-\theta)^2r^4.
```

Equality holds if and only if

```math
W(x,y)=r
```

almost everywhere.

## Proof

Regard $W$ as a Hilbert-Schmidt operator from $L^2(T)$ to $L^2(S)$ with normalized measures. The constant row and column degrees make the constant functions a singular pair with singular value $r$. If $\sigma_1,\sigma_2,\ldots$ are the remaining singular values, the normalized $K_{2,2}$ density is

```math
r^4+\sum_{j\geq1}\sigma_j^4.
```

Restoring the source and sink masses gives the stated factor $\theta^2(1-\theta)^2$. Equality holds exactly when every nonconstant singular value vanishes, which is equivalent to $W=r$ almost everywhere.

# 5. Absolute forcing theorem

## Theorem 3. Absolute forcing of the stochastic two-layer sector

Let $\mu$ be any central measure on the DAG branching graph. If

```math
t(P_2)=0,
```

the degree-polynomial constraint satisfies

```math
\mathbb E[Q_{\theta,r}(D^-,D^+)]=0,
```

and

```math
t(B_{2,2})
=
\theta^2(1-\theta)^2r^4,
```

then

```math
\mu=\mu^{\theta,r}.
```

The sector is therefore absolutely finitely forcible in the full central DAG boundary.

## Proof

Apply the extremal decomposition of $\mu$. The first two nonnegative constraints hold in almost every component and force the same source mass $\theta$, sink mass $1-\theta$, and normalized row and column degree $r$. Proposition 2 gives the same lower bound for the $B_{2,2}$ density in every component. Since their mixture attains the lower bound, almost every component attains equality and therefore has constant cross kernel $r$. All components equal $\mu^{\theta,r}$, so the mixture is trivial.

# 6. Finite pattern order

The path and $B_{2,2}$ constraints use at most four vertices. The polynomial $Q_{\theta,r}$ has degree four, so its mixed moments are directed bi-star densities with at most four leaves. After conversion to induced densities, the entire forcing family uses DAG patterns on at most five vertices.

The case $r=1$ recovers the deterministic two-layer sector through a different selector. For $0<r<1$, the theorem gives an absolutely selected noisy sector.

# 7. Terminal selection

The forcing coordinates can be inserted into the terminal energy of `findings-68.md`. With inverse temperature satisfying $\beta_N/N^2\to\infty$, the weighted finite-horizon route process selects the stochastic two-layer boundary profile and its harmonic up transition.

Thus edge randomness does not obstruct absolute finite selection. What is essential is a finite equality that removes nonconstant cross-layer modes.

Exact degree-pair calculations and rational biregular block examples show that the directed $K_{2,2}$ excess is the sum of fourth powers of the nonconstant singular values. It therefore vanishes exactly for the constant cross kernel.

The four-edge equality is the bipartite form of the quasirandomness mechanism used in graphon forcing: edge regularity identifies the constant singular mode, and the four-cycle density detects every remaining singular component. The result is formulated here directly for the central DAG boundary and combined with graph-intrinsic source-sink and degree selectors.
