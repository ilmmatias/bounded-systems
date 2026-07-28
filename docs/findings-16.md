# 1. The factorization complex of an endpoint pair

Let

```math
P=P_G=(V,\le)
```

be the reachability poset.

For $u<v$, define the open interval

```math
(u,v)=\{w\in V:u<w<v\}.
```

Its order complex

```math
\Delta(u,v)
```

is the simplicial complex whose:

* vertices are intermediate nodes $w\in(u,v)$;
* $r$-simplices are strict chains
  ```math
  u<w_0<w_1<\cdots<w_r<v.
  ```

An $r$-simplex represents a factorization of the single reachability arrow

```math
\varepsilon_{v,u}
```

into $r+2$ nonidentity reachability morphisms:

```math
u\to w_0\to w_1\to\cdots\to w_r\to v.
```

Deleting one intermediate node composes the two neighboring factors. Thus the simplicial boundary is exactly the “merge adjacent factors” operation that appeared in the bar complexes.

For

```math
\sigma=[w_0<\cdots<w_r],
```

the boundary is

```math
\partial\sigma=
\sum_{i=0}^{r}
(-1)^i
[w_0<\cdots<\widehat{w_i}<\cdots<w_r].
```

This construction is defined for any set-sized interval, finite or infinite. Every simplex and every boundary contain only finitely many terms.

# 2. Canonical coherence groups

Define

```math
\mathcal K_n(v,u;\mathbb Z)=
\widetilde H_{n-2}\bigl(\Delta(u,v);\mathbb Z\bigr)
```

for $n\ge1$, with the convention

```math
\widetilde H_{-1}(\varnothing;\mathbb Z)=\mathbb Z.
```

The shift by two is meaningful.

## $n=1$: primitive cover generators

If $u\lessdot v$, then

```math
(u,v)=\varnothing,
```

so

```math
\mathcal K_1(v,u)\cong\mathbb Z.
```

This represents one primitive cover arrow in the Hasse presentation of the reachability order.

If an intermediate node exists, then

```math
\mathcal K_1(v,u)=0.
```

## $n=2$: independent route-identification relations

Here

```math
\mathcal K_2(v,u)=
\widetilde H_0(\Delta(u,v)).
```

Reduced $H_0$ measures how many connected components the factorization space has, minus one.

A nonzero class means that distinct families of factorizations from $u$ to $v$ cannot be connected through elementary refinements and coarsenings without imposing an independent relation.

## $n=3$: relations among relations

Now

```math
\mathcal K_3(v,u)=
\widetilde H_1(\Delta(u,v)).
```

These are loops in the factorization complex: coherent cycles of relations that require a third-level filling.

## Higher $n$

```math
\mathcal K_n(v,u)=
\widetilde H_{n-2}(\Delta(u,v))
```

measures higher-dimensional holes among factorizations and their coherences.

Thus the hierarchy is:

```math
\begin{array}{c|l}
\mathcal K_1&\text{cover generators}\\
\mathcal K_2&\text{independent path-identification relations}\\
\mathcal K_3&\text{relations among those relations}\\
\mathcal K_4&\text{relations among third-level coherences}\\
\vdots&\vdots
\end{array}
```

# 3. Why this is the correct canonical replacement

The original path algebra

```math
A(G)
```

is free on the primitive channels. Distinct paths are not equal there, so it contains no intrinsic equations among routes.

The thin reachability algebra

```math
B(P)
```

imposes the rule that every two paths with the same endpoints become equal. It can be obtained from a path algebra by the parallel-path ideal, and this presentation of incidence algebras is standard.

Different choices of relation generators—diamonds, shortcuts, arbitrary path pairs—can produce different-looking resolutions. But

```math
\Delta(u,v)
```

depends only on the reachability order. It is therefore independent of:

* preferred paths;
* a Gröbner ordering;
* chosen diamond generators;
* a minimal basis;
* the original node labels.

The full complex is canonical even when a minimal cellular presentation is not.

# 4. Relation to Ext groups

For a finite poset $P$, let $B=B(P)$ be its incidence algebra over a field $k$, and let $S_u,S_v$ be the simple modules at $u,v$.

The normalized relative bar resolution yields

```math
\mathrm{Ext}^n_B(S_u,S_v)
\cong
\widetilde H^{\,n-2}\bigl(\Delta(u,v);k\bigr)
```

for $u<v$ and $n\ge1$, with the corresponding empty-complex convention.

The reason for the shift is that an $(n-2)$-simplex

```math
u<w_0<\cdots<w_{n-2}<v
```

contains $n$ strict reachability factors.

Finite incidence algebras admit projective resolutions of their simple modules and Ext calculations entirely from the underlying poset; incidence-algebra cohomology is likewise computed by simplicial chain complexes of poset chains.

Over a field and for finite intervals,

```math
\dim_k\mathrm{Ext}^n_B(S_u,S_v)=
\dim_k\widetilde H_{n-2}(\Delta(u,v);k).
```

So the canonical invariant can be viewed either as:

```math
\text{interval topology}
```

or as

```math
\text{the Ext hierarchy of the thin reachability algebra}.
```

# 5. Basic examples

## A cover

If

```math
u\lessdot v,
```

then the open interval is empty:

```math
\Delta(u,v)=\varnothing.
```

Hence

```math
\mathcal K_1(v,u)\cong\mathbb Z,
```

and all higher groups vanish.

This is one primitive Hasse arrow with no relation.

## A three-node chain

Suppose

```math
u<w<v.
```

The open interval contains one point. Its order complex is contractible:

```math
\Delta(u,v)\simeq\{\text{point}\}.
```

Therefore

```math
\mathcal K_n(v,u)=0
\qquad\forall n.
```

There is a unique factorization through $w$, so no relation is needed between alternative routes.

## A diamond

Suppose

```math
u<a<v,
\qquad
u<b<v,
```

with $a$ and $b$ incomparable.

Then

```math
\Delta(u,v)
```

is two isolated points. Hence

```math
\widetilde H_0(\Delta(u,v))
\cong\mathbb Z.
```

Therefore

```math
\mathcal K_2(v,u)\cong\mathbb Z.
```

This relation identifies

```math
u\to a\to v
```

with

```math
u\to b\to v.
```

## The Boolean interval $B_3$

Between

```math
\varnothing
\quad\text{and}\quad
{1,2,3},
```

the open interval consists of:

* three singleton subsets;
* three two-element subsets.

Its order complex is the six-cycle

```math
S^1.
```

Thus

```math
\widetilde H_1(\Delta)\cong\mathbb Z,
```

giving

```math
\mathcal K_3({1,2,3},\varnothing)
\cong\mathbb Z.
```

This is the canonical home of the hexagonal relation among the six diamond relations.

The earlier $I$-adic complex missed it because it searched for products of ambiguity ideals. The interval complex instead records relations among contextualized local relations.

# 6. Boolean intervals of arbitrary rank

For the Boolean lattice $B_d$, the open interval between bottom and top consists of all nonempty proper subsets of a $d$-element set.

Its order complex is the barycentric subdivision of the boundary of a $(d-1)$-simplex. Therefore

```math
\Delta(\varnothing,[d])
\simeq
S^{d-2}.
```

Consequently,

```math
\mathcal K_d([d],\varnothing)
\cong\mathbb Z,
```

and

```math
\mathcal K_n([d],\varnothing)=0
\qquad(n\ne d).
```

This produces the exact hierarchy:

```math
\begin{array}{c|c}
d&\text{highest coherence}\\
\hline
1&\text{cover generator}\\
2&\text{diamond relation}\\
3&\text{hexagonal relation among diamonds}\\
4&\text{relation among three-dimensional coherences}\\
\vdots&\vdots
\end{array}
```

The complete interval may contain $d!$ saturated routes, but their minimal higher coherence between bottom and top is concentrated in degree $d$.

# 7. The full homotopy type is primary

Homology is already more informative than the Möbius number, but it is still a compression.

Two interval complexes can have identical homology while having different:

* fundamental groups;
* higher homotopy groups;
* simple-homotopy types;
* cup products;
* torsion operations.

Therefore the most complete canonical coherence datum is

```math
\mathfrak F_G(v,u)=
\text{homotopy type of }\Delta(u,v).
```

The groups

```math
\mathcal K_n(v,u)
```

are linearized shadows of this homotopy type.

This gives the hierarchy

```math
\Delta(u,v)
\longrightarrow
\widetilde H_*(\Delta(u,v))
\longrightarrow
{\beta_n(u,v)}
\longrightarrow
\mu(u,v).
```

Each arrow loses information.

# 8. Möbius inversion as Euler-characteristic compression

When the reachability interval is finite, its Möbius function satisfies

```math
\mu(u,v)=
\widetilde\chi\bigl(\Delta(u,v)\bigr).
```

This follows directly from the alternating-chain expression for $\mu$: an $r$-simplex of $\Delta(u,v)$ is a strict chain with $r+1$ intermediate nodes.

Over a field $k$,

```math
\mu(u,v)=
\sum_{j\ge-1}
(-1)^j
\dim_k\widetilde H_j(\Delta(u,v);k).
```

Using the coherence index $n=j+2$,

```math
\mu(u,v)=
\sum_{n\ge1}
(-1)^n
\dim_k\mathrm{Ext}^n_B(S_u,S_v).
```

So Möbius inversion retains only the alternating total of all higher coherence dimensions.

For a diamond:

```math
\mu(u,v)=1
```

comes from one degree-two relation.

For $B_3$:

```math
\mu(\varnothing,[3])=-1
```

comes from one degree-three coherence.

The Möbius value alone cannot tell which degree produced it.

# 9. Ordinal-rank support

Suppose past ranks exist.

If an $(n-2)$-simplex occurs in $\Delta(u,v)$, then there is a strict chain

```math
u<w_0<\cdots<w_{n-2}<v
```

containing $n$ strict reachability steps.

Therefore

```math
\rho_-(u)+n\le\rho_-(v).
```

Consequently,

```math
\mathcal K_n(v,u)=0
\quad\text{unless}\quad
\rho_-(u)+n\le\rho_-(v).
```

Dually,

```math
\mathcal K_n(v,u)=0
\quad\text{unless}\quad
\rho_+(v)+n\le\rho_+(u).
```

Thus the higher coherence groups inherit the same transfinite triangularity as paths and resolvents.

Define the past-rank block

```math
\mathcal K_n^-(\beta,\alpha)=
\bigoplus_{\substack{
\rho_-(u)=\alpha\\
\rho_-(v)=\beta
}}
\mathcal K_n(v,u).
```

Then

```math
\mathcal K_n^-(\beta,\alpha)=0
\qquad\text{unless}\qquad
\alpha+n\le\beta.
```

Higher syzygies require correspondingly larger ordinal separation.

# 10. Finite global dimension

For a finite reachability poset, the global dimension of its incidence algebra is the largest $n$ for which some simple-module Ext group is nonzero:

```math
\mathrm{gldim}B=
\max
\left\lbrace n: \widetilde H^{n-2} \bigl(\Delta(u,v);k\bigr)\ne0 \text{ for some }u<v \right\rbrace.
```

Examples:

```math
\begin{array}{c|c}
P&\mathrm{gldim}B(P)\\
\hline
\text{total order}&1\\
\text{diamond }B_2&2\\
B_3&3\\
B_d&d
\end{array}
```

A long chain does not itself increase global dimension: its intervals are simplices and therefore contractible.

What increases homological dimension is not mere path length but topologically nontrivial multiplicity of factorizations.

The distinction is:

```math
\text{compositional depth}
\neq
\text{coherence depth}.
```

# 11. What this does not recover

The interval complex depends only on the reachability poset.

It does not know:

* how many parallel primitive channels existed;
* which original edges were shortcuts;
* how many distinct original paths represented one saturated order chain;
* whether an original cover relation was realized by one channel or many;
* path lengths in the original graph when shortcut edges exist.

For example, these systems have the same reachability interval topology:

```math
u\to w\to v
```

and

```math
u\to w\to v,
\qquad
u\to v.
```

The shortcut is invisible after thin collapse.

Therefore the full theory needs two separate invariants.

## Presentation defect

```math
I_G=
\ker\!\left(A(G)\to B(P_G)\right)
```

records the route information lost from the original system.

## Intrinsic thin coherence

```math
{\Delta(u,v)}_{u<v}
```

records the higher coherence intrinsic to the reachability order after all routes are identified.

Neither replaces the other.

# 12. Infinite systems

For an arbitrary set-sized system, the order complex

```math
\Delta(u,v)
```

still exists, even when $(u,v)$ is infinite or not locally finite.

Its simplicial chain group is the free abelian group on finite chains:

```math
C_r(\Delta(u,v))=
\mathbb Z^{({
u<w_0<\cdots<w_r<v
})}.
```

The boundary is always a finite alternating sum.

Thus

```math
\mathcal K_n(v,u;\mathbb Z)
```

is defined independently of:

* interval finiteness;
* incidence convolution;
* summability;
* Hilbert completion;
* countability;
* bounded degree.

What requires more care in the infinite case is identifying these groups with Ext groups of a particular completed incidence algebra. The combinatorial homology itself has no such problem.

So for the unrestricted theory, the safest primary definition is:

```math
\mathcal K_n(v,u)=
\widetilde H_{n-2}(\Delta(u,v);\mathbb Z).
```

The incidence-algebra Ext interpretation is then a conditional algebraic realization in settings where the relevant module theory is well behaved.
