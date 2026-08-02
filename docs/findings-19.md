# 1. Route-factorization double object

Fix comparable nodes

```math
u<v.
```

For $r,q\ge 0$, define

```math
\mathbb X_{r,q}(v,u)
```

as follows.

Choose a strict factorization chain

```math
u=v_0<v_1<\cdots<v_r<v_{r+1}=v.
```

It contains $r$ intermediate nodes and $r+1$ reachability factors.

For each $j=0,\ldots,q$, choose actual paths

```math
p_i^{(j)}:v_{i-1}\to v_i
\qquad(1\le i\le r+1).
```

An element is

```math
x=
\left(
\mathbf p^{(0)},\ldots,\mathbf p^{(q)}
\right),
```

where

```math
\mathbf p^{(j)}=
\left(
p_1^{(j)},\ldots,p_{r+1}^{(j)}
\right).
```

Each $\mathbf p^{(j)}$ realizes the same thin factorization chain by actual
routes.

## Vertical faces

Delete one complete route realization:

```math
d_j^{\mathrm{rt}}
\left(
\mathbf p^{(0)},\ldots,\mathbf p^{(q)}
\right)=
\left(
\mathbf p^{(0)},\ldots,
\widehat{\mathbf p^{(j)}},
\ldots,\mathbf p^{(q)}
\right).
```

These are the route-collapse directions.

## Horizontal faces

Delete an intermediate node $v_i$ and concatenate the adjacent paths:

```math
p_{i+1}^{(j)},p_i^{(j)}
\longmapsto
p_{i+1}^{(j)}p_i^{(j)}
```

for every $j$.

These are the factorization directions.

Deleting one route realization commutes with merging two factors.

Taking free modules and normalized chains gives a double complex

```math
C_{r,q}^{\mathrm{RF}}(v,u).
```

Here $q$ measures coherent route identification and $r$ measures
intermediate-node factorization.

As before, the horizontal degree has the conventional two-step shift: $r=0$,
with no intermediate nodes, represents the open interval's empty simplex.

# 2. Intrinsic path-length filtration

For

```math
x=
(\mathbf p^{(0)},\ldots,\mathbf p^{(q)}),
```

define

```math
\Lambda(x)=
\max_{0\le j\le q}
\sum_{i=1}^{r+1}|p_i^{(j)}|.
```

For each $j$, the sum is the length of the full actual path

```math
p_{r+1}^{(j)}\cdots p_1^{(j)}:u\to v.
```

$\Lambda(x)$ is the largest length among the $q+1$ route realizations
represented by $x$.

The length statistic has the required functoriality:

* deleting a route realization cannot increase $\Lambda$;
* deleting a factorization node merely concatenates two path pieces, so it
  leaves every complete-route length unchanged.

```math
F_N^{\mathrm{len}}C_{r,q}^{\mathrm{RF}}=
\mathrm{span}
\{x:\Lambda(x)\le N\}
```

is a sub-double-complex.

The filtration counts primitive channels only; it introduces neither a time
scale nor a damping parameter.

# 3. Intrinsic ordinal-rank filtration

The transfinite past-rank decomposition also records where a route lies.

For every node $w$, define its extended past stage

```math
\tau^-(w)=
\begin{cases}
\rho_-(w)+1,&w\text{ lies in the past-well-founded part},\\
\infty,&w\in K^-.
\end{cases}
```

For a generator $x$, let $\mathrm{Int}(x)$ be all nodes other than $u,v$
appearing:

* as factorization nodes $v_1,\ldots,v_r$;
* or internally inside any path $p_i^{(j)}$.

The maximal past-stage index of $x$ is

```math
\Theta^-(x)=
\sup{\tau^-(w):w\in\mathrm{Int}(x)},
```

with the supremum of the empty set taken to be $0$.

Both families of faces act on $\mathrm{Int}(x)$ as follows:

* vertical faces can only remove nodes;
* horizontal faces regroup the same complete paths and introduce no new nodes.

Hence $\Theta^-$ cannot increase under either differential.

For an ordinal stage $\alpha$, define

```math
F_\alpha^{\mathrm{rk}}C_{r,q}^{\mathrm{RF}}=
\mathrm{span}
\{x:\Theta^-(x)\le\alpha\}.
```

The stage $\alpha=\infty$ includes paths that pass through the
backward-infinite core.

There is a dual construction using future ranks.

# 4. The canonical bifiltration

Combine the two:

```math
F_{N,\alpha}C_{r,q}^{\mathrm{RF}}=
F_N^{\mathrm{len}}
\cap
F_\alpha^{\mathrm{rk}}.
```

If

```math
N\le M,
\qquad
\alpha\le\beta,
```

it follows that

```math
F_{N,\alpha}C^{\mathrm{RF}}
\subseteq
F_{M,\beta}C^{\mathrm{RF}}.
```

This defines a functor from the product order

```math
\mathbb N\times
\bigl(\mathrm{RankStages}(G)\cup\{\infty\}\bigr)
```

to double complexes.

The bifiltered complex is canonical; no chosen one-dimensional traversal is.

# 5. Route-restricted distance

Fix a rank stage $\alpha$. Define

```math
d_\alpha(a,b)
```

to be the minimum length of a path $p:a\to b$ whose internal nodes all satisfy

```math
\tau^-(w)\le\alpha.
```

If no such path exists, set

```math
d_\alpha(a,b)=\infty.
```

At the final stage,

```math
d_\infty(a,b)
```

is the ordinary shortest directed-path length.

Whenever the intermediate node $b$ is itself admitted at stage $\alpha$,

```math
d_\alpha(a,c)
\le
d_\alpha(a,b)+d_\alpha(b,c).
```

The inequality follows by concatenating shortest admissible paths through $b$.

# 6. The filtered interval complex

For fixed $N,\alpha$, define

```math
\Delta^{N,\alpha}(u,v)
```

as the augmented simplicial complex whose simplices are strict chains

```math
u=v_0<v_1<\cdots<v_r<v_{r+1}=v
```

satisfying:

```math
\tau^-(v_i)\le\alpha
\qquad(1\le i\le r),
```

and

```math
\sum_{i=1}^{r+1}
d_\alpha(v_{i-1},v_i)
\le N.
```

For $r=0$, this is the empty simplex for the unfactored arrow $u<v$, admitted
precisely when

```math
d_\alpha(u,v)\le N.
```

Deleting an intermediate node preserves the condition because two adjacent
distance terms are replaced by one no larger term.

Therefore $\Delta^{N,\alpha}(u,v)$ is a subcomplex of the augmented order
complex.

# 7. Route-first collapse theorem

Now fix one factorization chain

```math
\mathbf v:
u=v_0<\cdots<v_{r+1}=v.
```

Let $S_{N,\alpha}(\mathbf v)$ be the set of actual route realizations

```math
(p_1,\ldots,p_{r+1})
```

such that:

```math
\sum_i|p_i|\le N
```

and every internal node used has past stage at most $\alpha$.

For this fixed node chain, the vertical simplicial set is exactly

```math
E\bigl(S_{N,\alpha}(\mathbf v)\bigr).
```

Its $q$-simplices are

```math
S_{N,\alpha}(\mathbf v)^{q+1}.
```

Its vertical homology is

```math
H_q^{\mathrm{rt}}=
\begin{cases}
k,&q=0\text{ and }S_{N,\alpha}(\mathbf v)\ne\varnothing,\\
0,&\text{otherwise}.
\end{cases}
```

Moreover,

```math
S_{N,\alpha}(\mathbf v)\ne\varnothing
```

exactly when

```math
\sum_i d_\alpha(v_{i-1},v_i)\le N
```

and all intermediate factorization nodes are admitted.

After vertical homology, the horizontal complex is precisely the augmented
simplicial chain complex of

```math
\Delta^{N,\alpha}(u,v).
```

The route-first spectral sequence has only one nonzero row after vertical
homology and collapses immediately:

```math
E^1
\cong
\widetilde C_*
\bigl(\Delta^{N,\alpha}(u,v);k\bigr),
```

Consequently,

```math
E^2
\cong
\widetilde H_*
\bigl(\Delta^{N,\alpha}(u,v);k\bigr)=
E^\infty.
```

The collapse occurs because each nonempty route fiber is contractible, not
because the original system lacks route complexity.

# 8. Filtered coherence groups

Using the same coherence-degree convention, define

```math
\mathcal K_m^{N,\alpha}(v,u;k)=
\widetilde H_{m-2}
\bigl(
\Delta^{N,\alpha}(u,v);k
\bigr).
```

Thus the first three coherence degrees are

```math
\mathcal K_1^{N,\alpha}=\widetilde H_{-1},
\qquad
\mathcal K_2^{N,\alpha}=\widetilde H_0,
\qquad
\mathcal K_3^{N,\alpha}=\widetilde H_1,
```

and similarly in higher degrees.

For

```math
N\le M,\qquad \alpha\le\beta,
```

the inclusions of filtered interval complexes induce maps

```math
\mathcal K_m^{N,\alpha}(v,u)
\longrightarrow
\mathcal K_m^{M,\beta}(v,u).
```

Each endpoint pair and coherence degree determines a two-parameter persistence
module:

```math
(N,\alpha)
\longmapsto
\mathcal K_m^{N,\alpha}(v,u).
```

No general complete barcode classification exists for persistence with two or
more independent parameters; the persistence module itself, or derived rank and
restriction invariants, must remain primary.

# 9. Recovery of the unfiltered coherence

At the final rank stage and with no finite length bound,

```math
\bigcup_{N,\alpha}
\Delta^{N,\alpha}(u,v)=
\Delta(u,v).
```

Every finite simplex uses:

* finitely many intermediate nodes;
* finitely many finite paths;
* a finite total route length.

Therefore it appears at some finite $N$ and some rank stage $\alpha$, unless it
passes through the infinite core, in which case it appears at $\alpha=\infty$.

Thus the filtered construction recovers the earlier interval coherence:

```math
\varinjlim_{N,\alpha}
\mathcal K_m^{N,\alpha}(v,u;k)
\cong
\mathcal K_m(v,u;k).
```

But the filtered module contains considerably more information than its limit.

# 10. Where route information disappears

The construction gives the following compression hierarchy.

## Initial route page

The $q=0$ groups contain all actual factorized routes.

For $r=0$,

```math
F_{N,\alpha}C_{0,0}^{\mathrm{RF}}(v,u)
```

has a basis consisting of every path $p:u\to v$ with:

```math
|p|\le N,
\qquad
\Theta^-(p)\le\alpha.
```

The initial page retains parallel channels, exact path multiplicities, every
path length, and every internal rank profile.

## Vertical differential and homology

The first route differential is

```math
d_1(p,q)=q-p.
```

It records the route-collapse ideal. After vertical homology, every nonempty
route set becomes one-dimensional. The resolved-path data then retain only the
existence of an admissible realization and the minimum admissible length
$d_\alpha$; parallel-route multiplicity, non-shortest alternatives, same-length
route distinctions, route orthogonality, and shortcut multiplicity beyond its
shortest effect are discarded.

## Horizontal homology

The next step retains only topological coherence among the resulting weighted
thin factorizations.

```math
\begin{aligned}
E^0&:\text{all resolved paths},\\
E^1&:\text{rank-restricted shortest-path geometry},\\
E^2=E^\infty&:\text{filtered interval coherence}.
\end{aligned}
```

Each information loss occurs at a specified page.

# 11. Example: one shortcut

Suppose that the system contains both $u\to w\to v$ and the shortcut

```math
u\to v.
```

There are paths of lengths one and two from $u$ to $v$.

## Route-resolved page

Both paths are visible:

```math
p_{\mathrm{direct}},
\qquad
p_{\mathrm{via};w}.
```

Their difference lies in the route-collapse ideal.

## At length budget $N=1$

The unfactored arrow is admitted because

```math
d(u,v)=1.
```

But the intermediate node $w$ is not yet admitted as a factorization, because

```math
d(u,w)+d(w,v)=2.
```

Equivalently,

```math
\Delta^{1,\infty}(u,v)=\varnothing
```

as an open interval complex, while its augmented empty simplex is present.

```math
\mathcal K_1^{1,\infty}(v,u)\cong k.
```

At this resolution, $u<v$ looks primitive.

## At $N=2$

The vertex $w$ appears. The interval complex becomes one point and is
contractible:

```math
\mathcal K_1^{2,\infty}(v,u)=0.
```

The apparent cover class is born at length one and dies at length two.

A shortcut becomes a temporary low-budget primitive class.

The final reachability poset forgets the shortcut, but the filtered coherence
module remembers exactly when it became redundant.

# 12. Example: parallel primitive channels

Suppose there are $m$ parallel channels

```math
e_1,\ldots,e_m:u\to v
```

and no intermediate node between $u$ and $v$.

At $N=1$, the route-resolved page has an $m$-dimensional path corner.

The vertical route differential contains the $(m-1)$-dimensional defect space

```math
\left\lbrace \sum_i c_ie_i: \sum_i c_i=0 \right\rbrace.
```

But after vertical homology, all $m$ channels become the same one-dimensional
reachability arrow.

```math
\mathcal K_1^{1,\alpha}(v,u)\cong k
```

regardless of $m$. Thus parallel multiplicity lives vertically and never
reaches interval homology.

# 13. Example: an asymmetric diamond

Suppose there are two factorization branches:

```math
u\to a\to v
```

of total shortest length two, and

```math
u\rightsquigarrow b\rightsquigarrow v
```

of total shortest length three.

At $N=2$, only $a$ appears in the filtered interval. A one-point complex is
contractible:

```math
\mathcal K_2^{2,\infty}(v,u)=0.
```

At $N=3$, $b$ appears as a second disconnected vertex:

```math
\Delta^{3,\infty}(u,v)=\{a,b\}.
```

Equivalently,

```math
\mathcal K_2^{3,\infty}(v,u)\cong k.
```

The diamond relation is born only when both competing factorizations are
accessible.

# 14. Example: Boolean $B_3$

For the bottom and top of $B_3$, every saturated factorization has total length
three.

At $N=3$, the entire six-cycle interval complex appears:

```math
\Delta^{3,\infty}(\varnothing,[3])
\simeq S^1.
```

Consequently,

```math
\mathcal K_3^{3,\infty}([3],\varnothing)\cong k.
```

The hexagonal third-level coherence is born at exact compositional budget three.

# 15. Rank persistence has the same interpretation

Return to the shortcut example.

A direct channel

```math
u\to v
```

has no internal node, so it is available at the earliest rank stage.

The composite route

```math
u\to w\to v
```

becomes available only once the cutoff includes

```math
\tau^-(w).
```

The temporary cover-like class dies exactly when the intermediate rank layer
containing $w$ enters.

In a diamond with intermediate nodes $a,b$, degree-two coherence appears only
after both rank layers enter.

Thus the ordinal filtration records the transfinite construction stage at which
a route or coherence becomes visible.

# 16. Relation to the formal resolvent

The length filtration comes directly from the formal resolvent

```math
R_G(z)=
\sum_{n\ge0}z^n\mathbf E^n.
```

Its truncation

```math
R_G^{\le N}(z)=
\sum_{n=0}^{N}z^n\mathbf E^n
```

contains exactly the paths visible under the length budget $N$.

The rank filtration comes from the transfinite projections

```math
F^-_\alpha.
```

The route-factorization filtration can be summarized as:

```math
\text{paths supported by }R_G^{\le N}
\quad\text{and admitted by the rank stage }F^-_\alpha.
```
