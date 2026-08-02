# 1. The factorization complex of an endpoint pair

Let $P=P_G=(V,\le)$ be the reachability poset.

For $u<v$, define the open interval

```math
(u,v)=\{w\in V:u<w<v\}.
```

Its order complex

```math
\Delta(u,v)
```

is the simplicial complex whose vertices are the intermediate nodes
$w\in(u,v)$ and whose $r$-simplices are the strict chains
$u<w_0<w_1<\cdots<w_r<v$.

An $r$-simplex represents a factorization of the single reachability arrow

```math
\varepsilon_{v,u}
```

into $r+2$ nonidentity reachability morphisms:

```math
u\to w_0\to w_1\to\cdots\to w_r\to v.
```

Deleting an intermediate node composes its neighboring factors, so the
simplicial boundary is exactly the “merge adjacent factors” operation from the
bar complexes.

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

The construction applies to any set-sized interval, finite or infinite; every
simplex and boundary has finitely many terms.

# 2. Canonical coherence groups

Define the canonical coherence group

```math
\mathcal K_n(v,u;\mathbb Z)=
\widetilde H_{n-2}\bigl(\Delta(u,v);\mathbb Z\bigr)
```

for $n\ge1$, with the convention

```math
\widetilde H_{-1}(\varnothing;\mathbb Z)=\mathbb Z.
```

## $n=1$: primitive cover generators

If $u\lessdot v$, then

```math
(u,v)=\varnothing,
```

so

```math
\mathcal K_1(v,u)\cong\mathbb Z.
```

The class represents one primitive cover arrow in the Hasse presentation.

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

Reduced $H_0$ measures how many connected components the factorization space
has, minus one.

A nonzero class means distinct families of factorizations from $u$ to $v$
cannot be connected by elementary refinements and coarsenings without an
independent relation.

## $n=3$: relations among relations

Now

```math
\mathcal K_3(v,u)=
\widetilde H_1(\Delta(u,v)).
```

These are loops in the factorization complex: coherent cycles of relations
that require a third-level filling.

## Higher $n$

For higher degrees, the coherence group

```math
\mathcal K_n(v,u)=
\widetilde H_{n-2}(\Delta(u,v))
```

measures higher-dimensional holes among factorizations and their coherences.

Thus these constructions are related as follows:

```math
\begin{array}{c|l}
\mathcal K_1&\text{cover generators}\\
\mathcal K_2&\text{independent path-identification relations}\\
\mathcal K_3&\text{relations among those relations}\\
\mathcal K_4&\text{relations among third-level coherences}\\
\vdots&\vdots
\end{array}
```

# 3. Canonical replacement

The original path algebra

```math
A(G)
```

is free on the primitive channels. Distinct paths are not equal there, so it
contains no intrinsic equations among routes.

The thin reachability algebra

```math
B(P)
```

imposes equality of every two paths with the same endpoints; it is the
quotient of a path algebra by the parallel-path ideal, a presentation of
incidence algebras.

Different choices of relation generators, such as diamonds, shortcuts,
arbitrary path pairs, can produce different-looking resolutions. But

```math
\Delta(u,v)
```

depends only on the reachability order. It is therefore independent of
preferred paths, a Gröbner ordering, chosen diamond generators, a minimal
basis, and the original node labels.

The full complex is canonical even when a minimal cellular presentation is not.

# 4. Relation to Ext groups

For a finite poset $P$, let $B=B(P)$ be its incidence algebra over a field
$k$, with simple modules $S_u,S_v$ at $u,v$.

The normalized relative bar resolution yields

```math
\mathrm{Ext}^n_B(S_u,S_v)
\cong
\widetilde H^{\,n-2}\bigl(\Delta(u,v);k\bigr)
```

for $u<v$ and $n\ge1$, subject to the usual left/right module convention, which
fixes which of $u,v$ occupies the first argument. The published form of the
isomorphism assumes the open interval nonempty; the cover case, where
$\Delta(u,v)$ is empty, is covered here by the convention that the reduced
cohomology of the empty complex is concentrated in degree $-1$.

The reason for the shift is that an $(n-2)$-simplex

```math
u<w_0<\cdots<w_{n-2}<v
```

contains $n$ strict reachability factors.

For a finite incidence algebra, projective resolutions of the simple modules,
and hence the Ext groups between them, are determined by the underlying poset.
The Hochschild cohomology of that algebra is separately identified with the
simplicial cohomology of the complex of poset chains.

Over a field and for finite intervals,

```math
\dim_k\mathrm{Ext}^n_B(S_u,S_v)=
\dim_k\widetilde H_{n-2}(\Delta(u,v);k).
```

For a finite poset over a field, the canonical invariant therefore admits two
interpretations: interval topology and the Ext hierarchy of the thin
reachability algebra.

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

Consequently,

```math
\mathcal K_1(v,u)\cong\mathbb Z,
```

and all higher groups vanish.

A cover contributes one primitive Hasse arrow and no relation.

## A three-node chain

Suppose $u<w<v$.

The open interval contains one point. Its order complex is contractible:

```math
\Delta(u,v)\simeq\{\text{point}\}.
```

Equivalently,

```math
\mathcal K_n(v,u)=0
\qquad\forall n.
```

There is a unique factorization through $w$, so no relation is needed between
alternative routes.

## A diamond

Suppose that

```math
u<a<v,
\qquad
u<b<v,
```

with $a$ and $b$ incomparable.

It follows that

```math
\Delta(u,v)
```

is two isolated points. Hence

```math
\widetilde H_0(\Delta(u,v))
\cong\mathbb Z.
```

Equivalently,

```math
\mathcal K_2(v,u)\cong\mathbb Z.
```

The relation identifies

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
\{1,2,3\},
```

the open interval consists of three singleton subsets and three two-element
subsets.

Its order complex is the six-cycle

```math
S^1.
```

Consequently,

```math
\widetilde H_1(\Delta)\cong\mathbb Z,
```

giving

```math
\mathcal K_3(\{1,2,3\},\varnothing)
\cong\mathbb Z.
```

The open-interval complex is the natural home of the hexagonal relation among
the six diamond relations.

The earlier $I$-adic complex missed it by searching for products of ambiguity
ideals; the interval complex records relations among contextualized local
relations.

# 6. Boolean intervals of arbitrary rank

For the Boolean lattice $B_d$, the open bottom-to-top interval comprises all
nonempty proper subsets of a $d$-element set.

Its order complex is the barycentric subdivision of the boundary of a
$(d-1)$-simplex. Therefore

```math
\Delta(\varnothing,[d])
\simeq
S^{d-2}.
```

The resulting isomorphism is

```math
\mathcal K_d([d],\varnothing)
\cong\mathbb Z,
```

and

```math
\mathcal K_n([d],\varnothing)=0
\qquad(n\ne d).
```

These constructions are related as follows:

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

The complete interval may have $d!$ saturated routes, but their minimal higher
bottom-to-top coherence is concentrated in degree $d$.

# 7. The full homotopy type is primary

Homology is more informative than the Möbius number but remains a compression:
the homotopy type of an interval complex carries a fundamental group, higher
homotopy groups, a simple-homotopy type, cup products, and torsion operations
that its homology does not determine in general. No interval-complex pair
separating these invariants at equal homology is exhibited here.

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

The homotopy type determines the hierarchy

```math
\Delta(u,v)
\longrightarrow
\widetilde H_*(\Delta(u,v))
\longrightarrow
\{\beta_n(u,v)\}
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

The identity follows from the alternating-chain expression for $\mu$: an
$r$-simplex of $\Delta(u,v)$ is a strict chain with $r+1$ intermediate nodes.

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

Möbius inversion retains only the alternating total of all higher coherence
dimensions.

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

containing $n$ strict reachability steps. Hence

```math
\rho_-(u)+n\le\rho_-(v).
```

This gives

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

The higher coherence groups inherit the same transfinite triangularity as
paths and resolvents.

Define the past-rank block

```math
\mathcal K_n^-(\beta,\alpha)=
\bigoplus_{\substack{
\rho_-(u)=\alpha\\
\rho_-(v)=\beta
}}
\mathcal K_n(v,u).
```

It follows that

```math
\mathcal K_n^-(\beta,\alpha)=0
\qquad\text{unless}\qquad
\alpha+n\le\beta.
```

Higher syzygies require correspondingly larger ordinal separation.

# 10. Finite global dimension

For a finite reachability poset, its incidence algebra has global dimension
equal to the largest $n$ with a nonzero simple-module Ext group:

```math
\mathrm{gldim}B=
\max
\left\lbrace n: \widetilde H^{n-2} \bigl(\Delta(u,v);k\bigr)\ne0 \text{ for some }u<v \right\rbrace.
```

The basic finite examples are

```math
\begin{array}{c|c}
P&\mathrm{gldim}B(P)\\
\hline
\text{total order, at least two elements}&1\\
\text{diamond }B_2&2\\
B_3&3\\
B_d&d
\end{array}
```

A long chain alone does not increase global dimension because its intervals
are contractible simplices.

What increases homological dimension is not mere path length but topologically
nontrivial multiplicity of factorizations.

The distinction is:

```math
\text{compositional depth}
\neq
\text{coherence depth}.
```

# 11. Information not recovered

The interval complex depends only on the reachability poset.

It does not record how many parallel primitive channels existed, which
original edges were shortcuts, how many distinct original paths represented one
saturated order chain, whether an original cover relation was realized by one
channel or many, or the original path lengths when shortcuts exist.

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

Therefore the full theory needs two separate invariants. The presentation
defect

```math
I_G=
\ker\!\left(A(G)\to B(P_G)\right)
```

records the route information lost from the original system. By contrast, the
family of interval complexes $\{\Delta(u,v)\}_{u<v}$ records the higher
coherence intrinsic to the reachability order after all routes have been
identified. Neither invariant replaces the other.

# 12. Infinite systems

For an arbitrary set-sized system, the order complex

```math
\Delta(u,v)
```

still exists, even when $(u,v)$ is infinite or not locally finite.

Its simplicial chain group is the free abelian group on finite chains:

```math
C_r(\Delta(u,v))=
\mathbb Z^{(\{
u<w_0<\cdots<w_r<v
\})}.
```

The boundary is always a finite alternating sum.

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

In the infinite case, identifying these groups with Ext groups of a particular
completed incidence algebra requires more care; the combinatorial homology has
no such problem.

For the unrestricted theory, the primary definition is therefore

```math
\mathcal K_n(v,u)=
\widetilde H_{n-2}(\Delta(u,v);\mathbb Z).
```

The incidence-algebra Ext interpretation is then a conditional algebraic
realization in settings where the relevant module theory is well behaved.

# 13. Literature relation

The isomorphism of section 4 between the Ext groups of the simple modules of a
finite incidence algebra over a field and the reduced cohomology of the open
interval, shifted by two, is the theorem of K. Igusa and D. Zacharia, *On the
cohomology of incidence algebras of partially ordered sets*, Communications in
Algebra 18 (1990), 873-887. Their statement assumes a finite poset and a
nonempty open interval, which is the restriction section 4 records, and their
indexing places the larger element in the first argument, which fixes the
left/right convention there. The presentation of $B(P)$ used in section 3 is
that of C. Cibils, *Cohomology of incidence algebras and simplicial complexes*,
Journal of Pure and Applied Algebra 56 (1989), 221-232, again for a finite
poset. The separate Hochschild statement in section 4 is M. Gerstenhaber and
S. D. Schack, *Simplicial cohomology is Hochschild cohomology*, Journal of Pure
and Applied Algebra 30 (1983), 143-156, which identifies the Hochschild
cohomology of the incidence algebra with the simplicial cohomology of the
complex of poset chains, a different object from the Ext groups between simple
modules. Algorithms for the projective resolutions mentioned in the same section
are given in V. Bekkert, J. W. MacQuarrie, and J. Marques, *Projective
resolutions of simple modules and Hochschild cohomology for incidence algebras*,
Linear Algebra and its Applications 740 (2026), 139-150, arXiv:2411.07910, for a
finite-dimensional incidence algebra over a field. The choice dependence
recorded in section 3 is explicit in S. Chouhy and A. Solotar, *Projective
resolutions of associative algebras and ambiguities*, Journal of Algebra 432
(2015), 22-61, arXiv:1406.2300, where the resolution is produced from a
reduction system chosen as data over a quiver with finitely many vertices; the
complex $\Delta(u,v)$ requires no such choice.

The identity of section 8 between $\mu(u,v)$ and $\widetilde\chi(\Delta(u,v))$,
together with the alternating-chain expression it uses, appears as Propositions
3.8.5 and 3.8.6 of R. P. Stanley, *Enumerative Combinatorics, Volume 1*, second
edition, Cambridge Studies in Advanced Mathematics 49, Cambridge University
Press, 2012. The alternating chain count originates in P. Hall, *The Eulerian
functions of a group*, Quarterly Journal of Mathematics os-7 (1936), 134-151,
and the Möbius function in G.-C. Rota, *On the foundations of combinatorial
theory I. Theory of Möbius functions*, Zeitschrift für
Wahrscheinlichkeitstheorie und Verwandte Gebiete 2 (1964), 340-368. The
barycentric subdivision used in section 6 is Example 3.8.7 of the same volume.
These sources work with finite posets, and with a field wherever an algebra is
involved, while the groups $\mathcal K_n(v,u;\mathbb Z)$ of sections 1, 2, and
12 are defined over $\mathbb Z$ from finite chains alone, without convolution
and without interval finiteness.
