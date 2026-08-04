# 1. Rooted finite-pattern observables

The absolute forcing argument for stochastic ordered sectors requires
finite constraints that refer to graph-intrinsic classes without
introducing latent labels. Rooted homomorphism densities provide the
required calculus.

Let $F^\bullet$ be a finite rooted DAG. For an extremal central DAG sector
represented by a dissociated acyclic digraphon $\Gamma$, write

```math
t_x(F^\bullet,\Gamma)
```

for the homomorphism density obtained by sending the root to $x$ and
integrating all other vertices independently. The function is defined
almost everywhere and is invariant under changes of representation up to
the usual measure-preserving equivalence.

If $F^\bullet$ and $G^\bullet$ have the same root label, their rooted
product is formed by taking disjoint copies of their unlabelled vertices
and identifying the roots. Independence of the integration variables
gives

```math
t_x(F^\bullet,\Gamma)
 t_x(G^\bullet,\Gamma)
=
t_x(F^\bullet G^\bullet,\Gamma).
```

The same construction applies to several labelled roots. Ordinary edges
may be inserted between labelled roots before the labels are integrated
out.

# 2. Quantum-DAG realization lemma

## Proposition 1. Polynomial realization

Let $z_1(x),\ldots,z_m(x)$ be rooted homomorphism-density functions of
finite rooted DAGs. Every expression obtained by the following finite
operations is a finite linear combination of ordinary finite-DAG
homomorphism densities:

1. polynomial combinations of the functions $z_j$;
2. multiplication by finitely many edge kernels between labelled roots;
3. integration over all labelled roots.

After the standard homomorphism-to-induced change of basis, the expression
is a finite linear combination of ordinary induced-DAG densities.

## Proof

Products of rooted densities are represented by root-gluing. Multiplication
by an edge kernel inserts that edge between the corresponding labelled
vertices. Integrating a label forgets the label. Repeating these
operations produces a finite quantum DAG. Each homomorphism density on a
fixed number of vertices is a finite sum of induced densities over its
possible completions, and Mobius inversion gives the converse change of
basis.

The proposition means that rooted and decorated notation can be used in
proofs without enlarging the observable language. Every constraint in the
construction expands into finitely many ordinary finite-DAG frequencies.

# 3. Polynomial lifting through the central boundary

Let $\mu$ be an arbitrary central measure and let $\nu_\mu$ be its
ergodic decomposition over extremal central sectors. If $a(\xi)=t(F,\xi)$
and $b(\xi)=t(G,\xi)$, dissociation inside each extremal component gives

```math
\int a(\xi)b(\xi)\,d\nu_\mu(\xi)
=
t(F\sqcup G,\mu).
```

Here $F\sqcup G$ is the disjoint union in the homomorphism-density
algebra; no conditions are imposed on cross pairs. More generally, every
polynomial in finitely many extremal pattern coordinates has an ergodic
average that is a finite quantum-DAG density of $\mu$.

## Proposition 2. Boundary polynomial lift

If $P$ is a polynomial in finitely many finite-pattern coordinates of an
extremal sector, then

```math
\mu\longmapsto
\int P(\xi)\,d\nu_\mu(\xi)
```

is a finite linear combination of ordinary induced-DAG coordinates of $\mu$.

This permits a nonnegative sector-level forcing energy to be imposed on
every extremal component simultaneously by one finite central constraint.

# 4. Ordered stochastic sectors

Fix an integer $q\geq2$, positive layer masses

```math
p_i>0,
\qquad
\sum_{i=1}^q p_i=1,
```

and edge probabilities

```math
0\leq w_{ij}\leq1
\qquad(i<j).
```

The target sector has independent layer marks with law $p$. Conditional
on the marks, an edge from layer $i$ to layer $j$ is present independently
with probability $w_{ij}$ when $i<j$, and no other edge is permitted.

Assume throughout that

```math
w_{i,i+1}>0
\qquad(1\leq i<q).
```

This condition makes every layer visible through finite rooted path data.

# 5. Rooted path signatures

For a general extremal sector, let $I_k(x)$ be the rooted density of a
directed path of length $k$ ending at $x$, and let $O_k(x)$ be the rooted
density of a directed path of length $k$ starting at $x$. Define

```math
S(x)
=
(I_1(x),\ldots,I_{q-1}(x),
 O_1(x),\ldots,O_{q-1}(x)).
```

In the target sector, a vertex in layer $i$ has a deterministic signature
$s_i$. Its coordinates can be computed recursively from

```math
\alpha_{i,0}=1,
\qquad
\alpha_{i,k}
=
\sum_{j<i}p_j w_{ji}\alpha_{j,k-1},
```

and

```math
\beta_{i,0}=1,
\qquad
\beta_{i,k}
=
\sum_{j>i}p_j w_{ij}\beta_{j,k-1},
```

by setting

```math
s_i
=
(\alpha_{i,1},\ldots,\alpha_{i,q-1},
 \beta_{i,1},\ldots,\beta_{i,q-1}).
```

## Proposition 3. Signature separation

The signatures $s_1,\ldots,s_q$ are pairwise distinct. More precisely,

```math
\alpha_{i,k}>0
\quad\Longleftrightarrow\quad
k\leq i-1,
```

and

```math
\beta_{i,k}>0
\quad\Longleftrightarrow\quad
k\leq q-i.
```

## Proof

No increasing layer sequence of length $k$ can end in layer $i$ when
$k\geq i$, so the corresponding incoming path density is zero. When
$k\leq i-1$, the adjacent chain

```math
i-k\longrightarrow i-k+1\longrightarrow\cdots\longrightarrow i
```

has positive mass because every layer mass and every adjacent probability
is positive. The outgoing statement is symmetric. The locations of the
final positive incoming and outgoing coordinates determine $i$.

# 6. Polynomial layer indicators

Define

```math
Q_{p,W}(z)
=
\prod_{i=1}^q
\|z-s_i\|^2.
```

The nonnegative rooted constraint

```math
\int Q_{p,W}(S(x))\,dx=0
```

forces $S(x)\in\{s_1,\ldots,s_q\}$ almost everywhere.

For each layer set

```math
L_i(z)
=
\prod_{j\neq i}
\frac{\|z-s_j\|^2}{\|s_i-s_j\|^2}.
```

On the zero set of $Q_{p,W}$, these polynomials satisfy

```math
L_i(s_j)=\delta_{ij}.
```

Thus $L_i(S(x))$ is the indicator of the graph-intrinsic class having the
target signature $s_i$. No latent layer labels occur in the final
constraints.

# 7. Finite forcing through rooted observables

The path-signature constraint, the polynomial indicators, block edge
densities, rooted block-degree defects, and block four-cycle densities are
all finite quantum-DAG observables by Proposition 1. Their sector-level
squares and products have finite central lifts by Proposition 2.

This supplies the finite observable calculus required to force an
arbitrary finite stochastic ordered sector in the full central boundary.
The forcing theorem is stated in `findings-71.md`.

For rational three- and four-layer sectors, exact calculations separate
the path signatures, satisfy the interpolation identities, and reproduce
the stated forcing defects on refined step kernels.

Rooted products and label-forgetting are the directed-DAG form of the
quantum-graph and flag-algebra calculus. The present use is specialized
to the central DAG boundary: rooted path coordinates construct the
partition internally, while the boundary polynomial lift makes
componentwise nonnegative energies observable in a nonextremal central
law.
