# 1. The multiplicity branching graph

Let $\mathfrak D_n$ be the finite set of isomorphism classes of simple
directed acyclic graphs on $n$ vertices. Let $\mathfrak D_n^{\mathrm{lab}}$
be the set of labeled DAGs with vertex set $[n]=\{1,\ldots,n\}$.

For $G\in\mathfrak D_n$, write

```math
a(G)=|\operatorname{Aut}(G)|,
\qquad
\dim(G)=\frac{n!}{a(G)}.
```

For $G\in\mathfrak D_n$ and $H\in\mathfrak D_{n+1}$, retain the deletion and
extension multiplicities from the preceding construction:

```math
d(G,H)=
\left|
\left\lbrace
v\in V(H):H-v\cong G
\right\rbrace
\right|,
```

and

```math
e(G,H)=d(G,H)\frac{a(G)}{a(H)}.
```

The value $e(G,H)$ is the number of labeled realizations of $H$ on $[n+1]$
whose restriction to $[n]$ is a fixed labeled realization of $G$.

The resulting multiplicity Bratteli diagram has level $n$ equal to
$\mathfrak D_n$ and $e(G,H)$ parallel edges from $G$ to $H$. Its canonical
cotransition is

```math
D_n(H,G)=
\frac{\dim(G)e(G,H)}{\dim(H)}
=
\frac{d(G,H)}{n+1}.
```

A sequence of probability measures $(\mu_n)_{n\geq0}$, with $\mu_n$
supported on $\mathfrak D_n$, is coherent when

```math
\mu_n(G)=
\sum_{H\in\mathfrak D_{n+1}}
\mu_{n+1}(H)D_n(H,G).
```

Such coherent systems are equivalent to central measures on the path space
of the multiplicity Bratteli diagram. The use of canonical cotransitions and
coherent systems follows the theory of central measures on multiplicity
Bratteli diagrams.

# 2. Central measures and exchangeable infinite DAGs

An infinite labeled DAG $X$ on $\mathbb N$ is exchangeable when

```math
\sigma X\overset{d}=X
```

for every finite permutation $\sigma$ of $\mathbb N$. Equivalently, the law
of $X|_{[n]}$ is invariant under every permutation of $[n]$ for every $n$.

## Theorem 1. Central-exchangeable correspondence

There is an affine bijection between the following sets:

1. coherent systems $(\mu_n)_{n\geq0}$ for the cotransitions $D_n$;
2. central probability measures on the path space of the DAG multiplicity
   Bratteli diagram;
3. exchangeable probability laws on infinite labeled simple DAGs on $\mathbb N$.

Under this correspondence, a coherent system determines the finite labeled law

```math
\mathbb P_n(g)=
\frac{\mu_n([g])}{\dim([g])},
\qquad
g\in\mathfrak D_n^{\mathrm{lab}},
```

where $[g]$ denotes the unlabeled isomorphism class of $g$.

## Proof

Fix a coherent system $(\mu_n)$. The displayed formula defines a probability
law because each class $G\in\mathfrak D_n$ has exactly $\dim(G)$ labeled
realizations:

```math
\sum_{g\in\mathfrak D_n^{\mathrm{lab}}}
\mathbb P_n(g)
=
\sum_{G\in\mathfrak D_n}
\dim(G)\frac{\mu_n(G)}{\dim(G)}
=1.
```

The law $\mathbb P_n$ is invariant under relabeling because it is constant on
every isomorphism class.

Let $g$ be a fixed labeled DAG on $[n]$, and set $G=[g]$. For each
$H\in\mathfrak D_{n+1}$, exactly $e(G,H)$ labeled realizations of $H$
restrict to $g$. Therefore

```math
\begin{aligned}
\mathbb P_{n+1}
\left(
X|_{[n]}=g
\right)
&=
\sum_{H\in\mathfrak D_{n+1}}
e(G,H)
\frac{\mu_{n+1}(H)}{\dim(H)}.
\end{aligned}
```

The dimension identity gives

```math
\frac{e(G,H)}{\dim(H)}
=
\frac{D_n(H,G)}{\dim(G)}.
```

Indeed,

```math
\begin{aligned}
\frac{e(G,H)}{\dim(H)}
&=
\frac{d(G,H)a(G)/a(H)}{(n+1)!/a(H)}\\
&=
\frac{d(G,H)}{n+1}
\frac{a(G)}{n!}\\
&=
\frac{D_n(H,G)}{\dim(G)}.
\end{aligned}
```

Coherence now yields

```math
\begin{aligned}
\mathbb P_{n+1}
\left(
X|_{[n]}=g
\right)
&=
\frac1{\dim(G)}
\sum_H\mu_{n+1}(H)D_n(H,G)\\
&=
\frac{\mu_n(G)}{\dim(G)}\\
&=
\mathbb P_n(g).
\end{aligned}
```

The labeled laws are therefore projectively consistent. The Kolmogorov
extension theorem produces an infinite random directed graph $X$ on
$\mathbb N$. Every finite restriction is a DAG, so $X$ contains no finite
directed cycle and is itself acyclic. The invariance of every $\mathbb P_n$
makes $X$ exchangeable.

Conversely, let $X$ be an exchangeable infinite DAG. For $G\in\mathfrak D_n$,
define

```math
\mu_n(G)=
\mathbb P
\left(
X|_{[n]}\cong G
\right).
```

Exchangeability makes the labeled restrictions uniform within each
isomorphism class, so every labeled realization $g$ of $G$ has probability
$\mu_n(G)/\dim(G)$. Applying the preceding restriction count in reverse
gives

```math
\mu_n(G)=
\sum_H\mu_{n+1}(H)D_n(H,G).
```

Thus $(\mu_n)$ is coherent. The two constructions are inverse and preserve
convex combinations.

Finally, a coherent system uniquely determines a central path measure: every
finite path ending at $G\in\mathfrak D_n$ is assigned cylinder probability

```math
\frac{\mu_n(G)}{\dim(G)}.
```

The consistency of these cylinder probabilities is precisely the coherence
relation. Conversely, the level distributions of a central path measure form
a coherent system. This proves all three equivalences.

# 3. Extremal sectors

## Corollary 2. Extremality and dissociation

Under Theorem 1, extremal central measures correspond exactly to extreme
exchangeable DAG laws. Such laws are ergodic under finite permutations and
are dissociated: restrictions to disjoint finite vertex sets are independent.

The central boundary can therefore be identified with the space of ergodic
exchangeable infinite DAG laws.

A general coherent growth law is a mixture of extremal sectors, while an
extremal sector is not further decomposable by exchangeable mixing.

# 4. Induced-density coordinates

For $F\in\mathfrak D_k$ and a finite labeled or unlabeled DAG $G$ with
$|G|=n\geq k$, define the induced density

```math
T_F(G)=
\frac1{\binom nk}
\sum_{\substack{S\subseteq V(G)\\|S|=k}}
\mathbf 1
\left\lbrace
G[S]\cong F
\right\rbrace.
```

The full induced-density profile is

```math
\Phi(G)=
\left(
T_F(G)
\right)_{F\in\bigcup_{k\geq1}\mathfrak D_k}.
```

It takes values in a countable product of compact intervals. The coordinates
satisfy normalization and deletion consistency relations, so their closure is
a compact projective space of relational limit data.

# 5. Almost-sure continuum limit

## Theorem 3. Induced-density limit in an extremal sector

Let $X$ be the exchangeable infinite DAG corresponding to an extremal
central measure, and let

```math
G_n=X|_{[n]}.
```

For every $F\in\mathfrak D_k$, define

```math
p_F=
\mathbb P
\left(
X|_{[k]}\cong F
\right).
```

Then

```math
T_F(G_n)\longrightarrow p_F
```

almost surely and in $L^2$. Since there are only countably many finite DAG
classes, the whole profile converges coordinatewise almost surely:

```math
\Phi(G_n)\longrightarrow
p=
\left(
p_F
\right)_F.
```

The limit is deterministic within an extremal sector. Moreover, its
level-$k$ coordinates are exactly the coherent measure:

```math
p_F=\mu_k(F).
```

## Proof

Fix $F\in\mathfrak D_k$. For each $k$-element set $S\subseteq[n]$, let

```math
Y_S=
\mathbf 1
\left\lbrace
X[S]\cong F
\right\rbrace.
```

Exchangeability gives

```math
\mathbb E[Y_S]=p_F.
```

Because the law is extremal, it is dissociated. Hence $Y_S$ and $Y_T$ are
independent whenever $S\cap T=\varnothing$. Consequently,

```math
\operatorname{Var}
\left(
T_F(G_n)
\right)
=
O_F\left(\frac1n\right),
```

since only pairs of $k$-sets with nonempty intersection contribute to the
covariance sum. This proves $L^2$ convergence.

For almost-sure convergence, first take the square subsequence $n=m^2$.
Chebyshev's inequality gives

```math
\sum_{m=1}^{\infty}
\mathbb P
\left(
\left|
T_F(G_{m^2})-p_F
\right|>\varepsilon
\right)
<\infty.
```

The Borel-Cantelli lemma therefore gives

```math
T_F(G_{m^2})\longrightarrow p_F
```

almost surely.

Adding one vertex changes an induced density by at most $k/(n+1)$. To see
this, write the level-$n+1$ density as the convex combination of the density
on old $k$-sets and the density on $k$-sets containing the new vertex. Thus

```math
\left|
T_F(G_{n+1})-T_F(G_n)
\right|
\leq
\frac{k}{n+1}.
```

For $m^2\leq n\leq(m+1)^2$, it follows that

```math
\left|
T_F(G_n)-T_F(G_{m^2})
\right|
\leq
k
\sum_{j=m^2}^{(m+1)^2-1}
\frac1{j+1}
\longrightarrow0.
```

The square-subsequence convergence therefore extends to the full sequence.
Intersecting the resulting probability-one events over the countable set of
finite DAG classes proves simultaneous coordinatewise convergence.

# 6. The central boundary as a continuum compactification

Theorem 3 gives a direct continuum realization of every extremal central
sector. The limiting point is the almost-sure limit of finite
induced-pattern frequencies along a central growth path.

The central boundary therefore embeds into the compact induced-density space by

```math
\mu\longmapsto
\left(
\mu_k(F)
\right)_{k,F}.
```

The map is injective because all finite-dimensional distributions determine
the exchangeable law. Its image consists of the projectively consistent
induced-density profiles that arise from ergodic exchangeable DAG laws.

For a nonextremal central measure, the same argument applied to the ergodic
decomposition yields a random limiting profile. Conditional on the selected
extremal component, the limit is deterministic.

The exchangeable and induced-density interpretation is the
directed-relational analogue of the correspondence between graph limits and
extreme exchangeable random graph laws. The transitive-closure quotient can
be compared separately with the established correspondence between poset
limits and exchangeable random posets.

# 7. Density dichotomy

## Corollary 4. Nontrivial central sectors are dense

Let $E\in\mathfrak D_2$ be the class containing one directed edge. In an
extremal central sector, set

```math
\rho=p_E.
```

Then

```math
\frac{|E(G_n)|}{\binom n2}
\longrightarrow
\rho
```

almost surely.

If $\rho=0$, the infinite DAG is empty almost surely. If the sector is
nonempty, then $\rho>0$, and the number of edges is of order $n^2$.

## Proof

The convergence is Theorem 3 applied to the two-vertex edge class. If
$\rho=0$, exchangeability gives probability zero for an edge on every fixed
unordered pair. A countable union shows that no pair carries an edge almost
surely. Otherwise $\rho>0$, and the limiting edge density is positive.

This corollary fixes the natural regime of the classical central boundary:
every nontrivial exchangeable sector is dense. Sparse nonempty growth cannot
be represented by an ordinary exchangeable law under vertex restriction and
therefore requires a different limit structure or a weakened symmetry
principle.

# 8. Exact one-node increment for cylinder coordinates

Let $g$ be a labeled DAG on $[n]$, and let $h$ be a labeled one-node
extension on $[n+1]$ with $h|_{[n]}=g$. For $F\in\mathfrak D_k$, define the
new-root density

```math
R_F(h;n+1)=
\frac1{\binom n{k-1}}
\sum_{\substack{S\subseteq[n]\\|S|=k-1}}
\mathbf 1
\left\lbrace
h[S\cup\{n+1\}]\cong F
\right\rbrace.
```

The induced density satisfies the exact recursion

```math
T_F(h)=
\frac{n+1-k}{n+1}T_F(g)
+
\frac{k}{n+1}R_F(h;n+1).
```

Equivalently,

```math
(n+1)
\left(
T_F(h)-T_F(g)
\right)
=
k
\left(
R_F(h;n+1)-T_F(g)
\right).
```

The scaled increment is therefore uniformly bounded by $k$. Its closure
variable is explicit: the drift of an unrooted $k$-vertex density is
controlled by a one-root $k$-vertex density.

For an edge-level up law on labeled extensions, the exact conditional
coefficient formulas are

```math
b_{n,F}(g)=
k
\left(
\mathbb E
\left[
R_F(G_{n+1};n+1)
\mid G_n=g
\right]
-
T_F(g)
\right),
```

and

```math
a_{n,F,K}(g)=
k\ell
\operatorname{Cov}
\left(
R_F(G_{n+1};n+1),
R_K(G_{n+1};n+1)
\mid G_n=g
\right),
```

where $|F|=k$ and $|K|=\ell$.

The rooted-density hierarchy is therefore the exact coefficient hierarchy
forced by one-node extension. Whether a finite or projective rooted profile
closes this hierarchy is unresolved.

# 9. Stable overlap-one covariance

Let $F\in\mathfrak D_k$ and $K\in\mathfrak D_\ell$. In an extremal sector,
define the overlap-one probability

```math
\gamma_{F,K}=
\mathbb P
\left(
X|_{[k]}\cong F,
\quad
X|_{\{1,k+1,\ldots,k+\ell-1\}}\cong K
\right).
```

The two observed vertex sets share exactly one vertex. The value
$\gamma_{F,K}$ is determined by the coherent distribution on level
$k+\ell-1$, because it is a finite sum of level-$k+\ell-1$ class
probabilities with combinatorial restriction coefficients.

## Theorem 5. Stable covariance coefficient

For the induced-density coordinates,

```math
\lim_{n\to\infty}
n\,
\operatorname{Cov}
\left(
T_F(G_n),T_K(G_n)
\right)
=
k\ell
\left(
\gamma_{F,K}-p_Fp_K
\right).
```

## Proof

Expand the covariance as an average over ordered pairs $(S,T)$, where
$|S|=k$ and $|T|=\ell$. If $S\cap T=\varnothing$, dissociation makes the
covariance zero.

The proportion of ordered pairs with $|S\cap T|=j$ is

```math
w_{n,j}=
\frac{
\binom kj
\binom{n-k}{\ell-j}
}{
\binom n\ell
}.
```

For one-point overlap,

```math
n w_{n,1}\longrightarrow k\ell.
```

For every $j\geq2$,

```math
n w_{n,j}\longrightarrow0.
```

All covariance terms are bounded. Exchangeability makes the covariance for
an overlap-one pair equal to $\gamma_{F,K}-p_Fp_K$. Only the one-point
overlaps therefore survive after multiplication by $n$, proving the formula.

# 10. Fluctuation scaling in extremal and mixed sectors

Theorem 5 proves the existence of a stable second-order coefficient directly
from the central sector. It also sharpens the proposed $\sqrt n$ fluctuation
claim.

If the overlap-one matrix

```math
C_{F,K}=
k\ell
\left(
\gamma_{F,K}-p_Fp_K
\right)
```

is nonzero on the chosen cylinder sector, then $\sqrt n$ is the natural
fluctuation scale.

If this matrix vanishes, the coordinate family is first-order degenerate.
The leading variance then comes from overlaps of two or more vertices, and a
faster normalization may be required. The $\sqrt n$ scale is therefore
generic but not universal.

This degeneracy occurs in homogeneous sectors and must be determined sector
by sector rather than assumed.

Theorem 5 gives the limiting static covariance. Convergence of the
state-dependent rooted coefficient fields $b_{n,F}$ and $a_{n,F,K}$ is
unproved.
