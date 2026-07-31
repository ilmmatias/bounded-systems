# 1. The universal finite-compression question

Although the complete projective pattern profile is an exact predictive state, it might still admit a continuous encoding by a fixed finite-dimensional vector. The result below rules out such a universal compression.

The obstruction already appears inside the finite ordered-layer sectors. Their parameter dimension grows without bound, while each sector is still extremal, acyclic, graph-intrinsically identifiable, and covered by the finite-pattern continuum theorems above.

# 2. Ordered block sectors of arbitrary dimension

Fix $q\geq2$, positive layer probabilities

```math
p_1,\ldots,p_q>0,
\qquad
\sum_{i=1}^q p_i=1,
```

and a number $\varepsilon\in(0,1/2)$. Let

```math
D_q=\frac{q(q-1)}2.
```

For every matrix

```math
W=(w_{ij})_{1\leq i<j\leq q}
\in
K_q=[\varepsilon,1-\varepsilon]^{D_q},
```

sample independent layer marks with distribution $p$. Conditional on the marks, include each edge from layer $i$ to layer $j$, where $i<j$, independently with probability $w_{ij}$. There are no edges inside a layer or from a higher layer to a lower layer.

Every sampled graph is a DAG, and the resulting infinite law is exchangeable and dissociated. Denote its extremal coherent profile by $\mu^W$.

# 3. The parameter cube embeds in the central boundary

## Theorem 1. Ordered block parameter embedding

The map

```math
\iota_q:K_q\longrightarrow\mathcal E,
\qquad
W\longmapsto\mu^W,
```

from the parameter cube to the extremal central boundary $\mathcal E$ is continuous and injective in the induced-pattern topology. Since $K_q$ is compact and the profile space is Hausdorff, it is a homeomorphism onto its image.

## Proof

For every finite DAG $F$, the probability $p_F(W)$ is obtained by summing over the finitely many assignments of the vertices of $F$ to the $q$ layers. Each assignment contributes a monomial in the variables

```math
p_i,
\qquad
w_{ij},
\qquad
1-w_{ij}.
```

Thus every induced-pattern coordinate is a polynomial in $W$, and $\iota_q$ is continuous.

Injectivity follows from graph-intrinsic recovery. Because every adjacent probability satisfies

```math
w_{i,i+1}\geq\varepsilon>0,
```

iterative source deletion recovers the latent ordered layers almost surely after a finite random level, by `findings-51.md`. Once the layers have been recovered, the empirical edge frequency between recovered layers $i$ and $j$ converges almost surely to $w_{ij}$. Hence $W$ is an almost-sure measurable invariant of the infinite graph law. Two distinct matrices cannot induce the same exchangeable DAG law or the same coherent profile.

# 4. No fixed continuous finite-dimensional state

## Theorem 2. Universal finite-dimensional compression is impossible

For every finite $M$, there is no continuous injective map

```math
\Psi:\mathcal E\longrightarrow\mathbb R^M
```

from the full extremal central boundary, equipped with the induced-pattern topology, into $M$-dimensional Euclidean space.

The same conclusion holds if $\mathcal E$ is replaced by the union of the positive ordered-block sectors.

## Proof

Choose $q$ so that

```math
D_q\geq M+1.
```

The interior of $K_q$ contains an embedded sphere $S^M$. If a continuous injective map $\Psi$ existed, then

```math
S^M
\longrightarrow
K_q
\overset{\iota_q}{\longrightarrow}
\mathcal E
\overset{\Psi}{\longrightarrow}
\mathbb R^M
```

would be continuous and injective. The Borsuk-Ulam theorem states that every continuous map from $S^M$ to $\mathbb R^M$ takes the same value at some antipodal pair. The composite therefore cannot be injective, giving a contradiction.

## Corollary 3. Dimension required by ordered layers

Any continuous Euclidean coordinate system that separates every sector in a fixed $q$-layer parameter cube must have dimension at least

```math
D_q=\frac{q(q-1)}2.
```

Since $D_q$ is unbounded, there is no fixed number of continuous macroscopic coordinates that identifies all dense extremal central DAG sectors.

# 5. Consequence for finite pattern lists

Every finite induced-pattern list defines a continuous map

```math
\mu
\longmapsto
\left(
 p_{F_1}(\mu),\ldots,p_{F_M}(\mu)
\right)
\in\mathbb R^M.
```

## Corollary 4. No universal finite list of pattern densities

For every finite collection of DAG patterns $F_1,\ldots,F_M$, there exist distinct extremal ordered-block sectors $\mu\neq\nu$ such that

```math
p_{F_a}(\mu)=p_{F_a}(\nu),
\qquad
1\leq a\leq M.
```

The two sectors disagree on at least one other finite pattern coordinate because the complete profile is injective by `findings-59.md`.

This is a global statement. It does not say that no individual sector can be determined by finitely many constraints. A sector is finitely forcible when one particular finite collection has that sector as its unique fiber. Finitely forcible graphons are known to exist, including examples with complicated or infinite-dimensional internal structure. The theorem says only that no single fixed finite coordinate system works for the entire boundary.

# 6. An explicit one-coordinate collision

The general theorem is topological, but the simplest collision is elementary. Take three equally likely layers and compare

```math
W^{(A)}:
\quad
w_{12}=w_{23}=w_{13}=\frac12,
```

with

```math
W^{(B)}:
\quad
w_{12}=\frac14,
\qquad
w_{23}=\frac12,
\qquad
w_{13}=\frac34.
```

Both have edge density

```math
2\sum_{i<j}p_ip_jw_{ij}
=
\frac13.
```

Their directed two-step route densities differ. A three-vertex route through the ordered layers requires the $1\to2$ and $2\to3$ edges, so

```math
\tau(W)
=
6p_1p_2p_3w_{12}w_{23}.
```

Therefore

```math
\tau(W^{(A)})=\frac1{18},
\qquad
\tau(W^{(B)})=\frac1{36}.
```

Edge density alone is not a closed sector coordinate, even inside a three-layer family.

# 7. Interpretation

The projective profile is infinite-dimensional for a structural reason rather than a poor choice of coordinates. The central boundary contains continuously embedded parameter spaces of arbitrarily high finite dimension. Any exact universal compression that respects convergence must therefore remain infinite-dimensional.

This does not prevent restricted closure. A fixed $q$-layer class has a finite parameter state $(p,W)$, and selected finitely forcible sectors may be isolated by finitely many pattern constraints. What fails is a single finite-dimensional state covering every extremal sector without loss.

Exact rational calculations give the following finite-compression identities and separations:

- equality of the edge densities in the explicit three-layer collision;
- inequality of the two-step route densities;
- polynomial evaluation of the complete three-vertex labeled adjacency distribution in a finite ordered-block sector;
- normalization of those probabilities.

# 8. Literature relation

Graph-limit theory distinguishes full identification by all finite pattern densities from finite forcibility by a selected finite list. Lovász and Szegedy introduced finitely forcible graphons and showed both positive examples and obstructions. Later work established that finite forcibility does not imply a simple finite-dimensional latent structure. The present theorem concerns a different issue: the impossibility of one universal finite-dimensional continuous coordinate system on the complete DAG central boundary.

References:

- L. Lovász and B. Szegedy, *Finitely forcible graphons*, Journal of Combinatorial Theory, Series B 101 (2011), 269-301, arXiv:0901.0929.
- J. W. Cooper, D. Král', and T. L. Martins, *Finitely forcible graph limits are universal*, Advances in Mathematics 340 (2018), 819-854, arXiv:1701.03846.
