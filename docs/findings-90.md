# 1. Signed two-sheet lifts

Let $(\Omega,\mu)$ be a standard probability space. Suppose $W$ is a directed kernel and $h$ is a bounded measurable function such that, for sufficiently small $|\varepsilon|$,

```math
0\leq W(x,y)\pm\varepsilon h(x,y)\leq1.
```

Pass to the two-sheet space

```math
\widetilde\Omega
=
\Omega\times\{-1,+1\}
```

with the product probability measure. Define

```math
\widetilde W_\varepsilon
\bigl((x,\sigma),(y,\tau)\bigr)
=
W(x,y)+\varepsilon h(x,y)\sigma\tau.
```

If both $W$ and $h$ vanish outside a common measurable strict order, then $\widetilde W_\varepsilon$ is also acyclic.

# 2. Eulerian-subgraph expansion

For a finite directed graph $F$, expand its homomorphism density in powers of $\varepsilon$. For an edge subset $S\subseteq E(F)$, let $\deg_S(v)$ denote the degree of $v$ in the underlying undirected graph formed by $S$.

Averaging the sheet signs gives

```math
\mathbb E
\left[
\prod_{uv\in S}\sigma_u\sigma_v
\right]
=
\prod_{v\in V(F)}
\mathbb E
\left[
\sigma_v^{\deg_S(v)}
\right].
```

This is one if every $\deg_S(v)$ is even and zero otherwise. Therefore

```math
t(F,\widetilde W_\varepsilon)
=
\sum_{\substack{S\subseteq E(F)\\
\deg_S(v)\text{ even for every }v}}
\varepsilon^{|S|}
I_S(F;W,h),
```

where $I_S(F;W,h)$ is obtained by placing $h$ on the edges of $S$ and $W$ on the remaining edges.

Only Eulerian edge subsets survive.

# 3. Complete forest invariance

## Theorem 1. Forest-blind pair modes

If the underlying undirected graph of $F$ is a forest, then

```math
t(F,\widetilde W_\varepsilon)=t(F,W)
```

for every sufficiently small $\varepsilon$.

## Proof

Every nonempty subgraph of a forest has a vertex of odd degree. Hence the empty edge set is the only Eulerian subset of $E(F)$, and the expansion contains only its zeroth-order term.

The conclusion applies simultaneously to:

- every directed path;
- every incoming or outgoing star;
- every directed double broom;
- every finite branching tree;
- every directed forest.

# 4. Application to the gap sector

Take

```math
W=A,
```

and

```math
h(x,y)
=
\mathbf1_{\{x<y\}}
 x^2(1-y)^2(y-x)^2.
```

For sufficiently small nonzero $\varepsilon$, the lift

```math
\widetilde A_\varepsilon
\bigl((x,\sigma),(y,\tau)\bigr)
=
(y-x)_+
+
\varepsilon h(x,y)\sigma\tau
```

is an acyclic $[0,1]$-valued kernel.

Its directed degree functions are independent of the sheet sign:

```math
d^-_{\widetilde A_\varepsilon}(x,\sigma)
=
\frac{x^2}{2},
\qquad
d^+_{\widetilde A_\varepsilon}(x,\sigma)
=
\frac{(1-x)^2}{2}.
```

The sign term averages to zero when the opposite endpoint sheet is integrated out.

Thus $A$ and $\widetilde A_\varepsilon$ have identical degree functions and identical homomorphism densities for every directed forest.

# 5. Relation to fractional information

In undirected graphon theory, equality of all tree homomorphism densities is closely related to fractional isomorphism and branching-process equivalence. The signed lift supplies a direct directed acyclic mechanism behind the same loss of information: tree observables repeatedly integrate out leaf variables, and every hidden pair-sign contribution is killed at a leaf.

The result is stronger than finite nonuniqueness. Even the complete infinite forest hierarchy does not determine the full acyclic kernel.

It concerns homomorphism densities. Induced pattern probabilities also contain nonedge factors and are not claimed to remain unchanged.

Finite combinatorial expansion gives:

- the even-degree selection rule for edge subsets;
- exhaustive forest cancellation through the finite graph sizes considered;
- exact preservation of directed degrees;
- the exact cycle coefficients used in `findings-91.md`.
