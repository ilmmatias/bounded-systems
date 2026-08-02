# 1. The chaotic nerve of a route set

For a set $S$, define a simplicial set $E(S)$ by

```math
E(S)_n=S^{n+1}.
```

In low degrees this gives

```math
E(S)_0=S,
\qquad
E(S)_1=S\times S,
\qquad
E(S)_2=S\times S\times S.
```

The face map $d_i$ deletes the $i$-th entry:

```math
d_i(s_0,\ldots,s_n)=
(s_0,\ldots,\widehat{s_i},\ldots,s_n),
```

while the degeneracy $s_i$ repeats the $i$-th entry.

Equivalently, $E(S)$ is the nerve of the indiscrete groupoid on $S$, with
exactly one isomorphism between each ordered pair of objects.

If $S\ne\varnothing$, choosing any element gives this groupoid an initial and
terminal object, so its nerve is contractible.

But it remains marked:

* its vertices are the individual elements of $S$;
* an edge $(s_0,s_1)$ witnesses the formal identification of $s_0$ and $s_1$;
* a triangle $(s_0,s_1,s_2)$ witnesses compatibility among the three pairwise
  identifications;
* higher simplices provide all higher coherences.

# 2. Apply this to every route set

Let $\mathscr P_G(u,v)$ be the set of finite paths from $u$ to $v$, including
the identity path when $u=v$.

Define a simplicial category $\mathfrak R_G$ with object set

```math
\mathrm{Ob}(\mathfrak R_G)=V
```

and mapping simplicial sets

```math
\mathrm{Map}_{\mathfrak R_G}(u,v)=
E\bigl(\mathscr P_G(u,v)\bigr).
```

Its $n$-simplices are therefore

```math
\mathrm{Map}_{\mathfrak R_G}(u,v)_n=
\mathscr P_G(u,v)^{n+1}.
```

An $n$-simplex is an ordered collection

```math
(p_0,\ldots,p_n)
```

of $n+1$ routes with the same source and target.

## Composition

Given

```math
(p_0,\ldots,p_n)\in
\mathrm{Map}_{\mathfrak R_G}(u,v)_n
```

and

```math
(q_0,\ldots,q_n)\in
\mathrm{Map}_{\mathfrak R_G}(v,w)_n,
```

define composition coordinatewise:

```math
(q_0,\ldots,q_n)\circ(p_0,\ldots,p_n)=
(q_0p_0,\ldots,q_np_n).
```

Faces and degeneracies act coordinatewise, so they commute with composition.

The identity at $u$ in degree $n$ is

```math
(1_u,\ldots,1_u).
```

Path concatenation is associative, so this simplicial composition is strictly
associative.

Thus $\mathfrak R_G$ is a genuine simplicially enriched category: its morphism
objects are simplicial sets, and composition is simplicial. Its
homotopy-coherent nerve is a model of higher categorical structure.

# 3. The two visible truncations

The simplicial category $\mathfrak R_G$ contains both the path and reachability
categories.

## Its zero-simplices recover the path category

Since $E(S)_0=S$,

```math
\mathrm{Map}_{\mathfrak R_G}(u,v)_0=
\mathscr P_G(u,v).
```

Composition of zero-simplices is ordinary path concatenation, and hence

```math
\mathrm{sk}_0\mathfrak R_G=
\mathsf P(G).
```

## Its connected components recover reachability

If $\mathscr P_G(u,v)\ne\varnothing$, then

```math
E(\mathscr P_G(u,v))
```

is connected and contractible.

If there is no path, it is empty. Hence

```math
\pi_0
\mathrm{Map}_{\mathfrak R_G}(u,v)=
\begin{cases}
\{\ast\},&u\le v,\\
\varnothing,&u\nleq v.
\end{cases}
```

This gives

```math
\pi_0\mathfrak R_G=
\mathsf R(G).
```

The construction gives the interpolation

```math
\mathsf P(G)=
\mathrm{sk}_0\mathfrak R_G
\quad\longrightarrow\quad
\mathfrak R_G
\quad\longrightarrow\quad
\pi_0\mathfrak R_G=
\mathsf R(G).
```

The middle object retains actual paths while coherently realizing their
collapse to reachability.

# 4. The canonical map to the thin category

Regard $\mathsf R(G)$ as a simplicial category with discrete mapping spaces.

There is a canonical enriched functor

```math
\epsilon:
\mathfrak R_G\longrightarrow\mathsf R(G)
```

which fixes nodes and sends every tuple

```math
(p_0,\ldots,p_n)
```

to the unique reachability arrow having those endpoints.

For every comparable pair $u\le v$, its mapping-space component is

```math
E(\mathscr P_G(u,v))
\longrightarrow
\{\ast\}.
```

The map is a weak homotopy equivalence because its source is contractible.

The functor $\epsilon$ is the identity on objects, induces weak equivalences on
all nonempty mapping spaces, and induces an isomorphism on $\pi_0$.

In simplicial-category language, it is therefore a Dwyer-Kan-type equivalence;
mapping-space equivalences are central to comparing simplicial categories and
their corresponding higher categories.

However, this must be interpreted carefully:

```math
\text{the weak-equivalence type of }\mathfrak R_G
\text{ remembers only reachability}.
```

The original route structure is retained by its marked zero-skeleton.

The complete object should therefore be regarded as

```math
\left(
\mathfrak R_G,\;
\mathsf P(G)=\mathrm{sk}_0\mathfrak R_G
\right),
```

not merely as the unmarked homotopy type of $\mathfrak R_G$.

# 5. Acyclicity inside the simplicial category

By acyclicity,

```math
\mathscr P_G(v,v)=\{1_v\}.
```

Consequently,

```math
\mathrm{Map}_{\mathfrak R_G}(v,v)=
E(\{1_v\})
\cong\Delta^0.
```

There is exactly one endomorphism vertex and no nontrivial route loop.

Thus acyclicity becomes:

```math
\mathrm{Map}_{\mathfrak R_G}(v,v)
\text{ has exactly the identity as its marked vertex}.
```

If directed cycles were allowed, this mapping space would have additional
marked vertices corresponding to nonempty closed paths, even though its
unmarked homotopy type would still be contractible.

# 6. Linearization: the canonical route-resolution complex

Choose a commutative coefficient ring $k$.

For each endpoint pair, define the free $k$-module on $(n+1)$-tuples of routes
by

```math
C_n^{\mathrm{route}}(v,u)=
k^{(\mathscr P_G(u,v)^{n+1})}.
```

The simplicial differential is

```math
d_n(p_0,\ldots,p_n)=
\sum_{i=0}^{n}
(-1)^i
(p_0,\ldots,\widehat{p_i},\ldots,p_n).
```

In degrees one and two, this gives

```math
\begin{aligned}
d_1(p_0,p_1)&=p_1-p_0,\\
d_2(p_0,p_1,p_2)&=(p_1,p_2)-(p_0,p_2)+(p_0,p_1).
\end{aligned}
```

There is an augmentation

```math
\varepsilon:
C_0^{\mathrm{route}}(v,u)
\longrightarrow
k\varepsilon_{v,u}
```

sending every route $p:u\to v$ to the unique thin reachability arrow:

```math
\varepsilon(p)=\varepsilon_{v,u}.
```

Because $E(\mathscr P_G(u,v))$ is contractible whenever it is nonempty, this
augmented chain complex is exact:

```math
\cdots
\to
C_2^{\mathrm{route}}(v,u)
\to
C_1^{\mathrm{route}}(v,u)
\to
C_0^{\mathrm{route}}(v,u)
\to
k\varepsilon_{v,u}
\to0.
```

# 7. The route ideal is exactly the first boundary

Recall that

```math
A_{v,u}=
e_vA(G)e_u=
k^{(\mathscr P_G(u,v))}=
C_0^{\mathrm{route}}(v,u).
```

The route-collapse kernel is

```math
I_{v,u}=
\left\lbrace \sum_pc_pp: \sum_pc_p=0 \right\rbrace.
```

Here,

```math
\mathrm{im}d_1=
\mathrm{span}\{p_1-p_0\}.
```

Therefore

```math
I_{v,u}=
\mathrm{im}
\left(
d_1:
C_1^{\mathrm{route}}(v,u)
\to
C_0^{\mathrm{route}}(v,u)
\right).
```

Globally,

```math
I=\mathrm{im}d_1.
```

The familiar exact sequence

```math
0\to I\to A(G)\to B(P_G)\to0
```

is merely the degree-zero end of the full route-resolution complex:

```math
\cdots
\to C_2^{\mathrm{route}}
\to C_1^{\mathrm{route}}
\to A(G)
\to B(P_G)
\to0.
```

The resulting complex is the canonical resolution by all route relations.

# 8. Higher simplices are relations among route identifications

A one-simplex

```math
(p,q)
```

has boundary

```math
q-p.
```

It witnesses the identification of two routes.

A two-simplex

```math
(p,q,r)
```

has boundary

```math
(q,r)-(p,r)+(p,q).
```

This gives

```math
[p,r]=[p,q]+[q,r]
```

at the level of route-identification chains.

It says that the direct identification $p\sim r$ agrees coherently with
identifying

```math
p\sim q\sim r.
```

A three-simplex gives the tetrahedral coherence among these triangular
identifications.

Higher simplices continue indefinitely.

```math
\begin{aligned}
C_0 &: \text{actual routes},\\
C_1 &: \text{pairwise route identifications},\\
C_2 &: \text{coherences among identifications},\\
C_3 &: \text{coherences among those coherences},\\
&\ \vdots
\end{aligned}
```

Because every mapping simplicial set is contractible, this full hierarchy has
no residual positive-degree homology. Every coherence cycle is filled at a
higher level.

Thus the collapse to one reachability arrow is completely coherent.

# 9. Finite and infinite route sets

Set $S$ by

```math
S=\mathscr P_G(u,v).
```

## Finite $S$

If $|S|=m<\infty$, then

```math
C_0^{\mathrm{route}}(v,u)\cong k^m.
```

The augmentation kernel has rank

```math
m-1.
```

In the Fock Hilbert realization, this is the codimension-one route-defect
subspace orthogonal to the equal-route vector.

## Infinite $S$

The algebraic resolution remains well defined: every chain contains finitely
many tuples, every boundary is a finite alternating sum, and no summation over
all routes is required.

But the augmentation

```math
\sum_pc_pp\longmapsto\sum_pc_p
```

does not extend boundedly to

```math
\ell^2(S).
```

Correspondingly, its kernel is norm dense in the entire Fock route corner.

The simplicial resolution explains the earlier analytic singularity: route
collapse is exact algebraically, but it need not be a bounded Hilbert-space
quotient.

Orthogonality and coherent route identification coexist, but they belong to
different categorical levels.

# 10. Two distinct coherence directions

Higher coherence has two previously conflated forms.

## Vertical coherence: identifying routes

At fixed endpoints $u,v$, the simplicial set

```math
E(\mathscr P_G(u,v))
```

records how all actual routes collapse to one thin arrow.

It is contractible.

Its first boundary produces the route ideal $I_{v,u}$.

## Horizontal coherence: factoring a reachability arrow

The order complex

```math
\Delta(u,v)
```

records the possible factorizations

```math
u<w_1<\cdots<w_r<v
```

of the thin arrow $u\le v$ through intermediate nodes.

It need not be contractible.

Its reduced homology gives the interval-coherence groups

```math
\widetilde H_*(\Delta(u,v)).
```

In matrix form,

```math
\begin{array}{c|c}
\text{Route direction}&
\text{Factorization direction}\\
\hline
\text{different actual paths}&
\text{different intermediate-node chains}\\
\text{fixed endpoints}&
\text{factorizations through endpoints}\\
\text{contractible resolution}&
\text{possibly nontrivial topology}\\
I=\mathrm{im}d_1&
\widetilde H_*(\Delta(u,v))
\end{array}
```

The two coherence directions are distinct.

# 11. The combined route-factorization bicomplex

Let $\mathcal C^{\mathrm{route}}(b,a)$ denote the augmented route-resolution
chain complex for paths $a\to b$.

For $u<v$, form

```math
\mathbb B_r(v,u)=
\bigoplus_{
u=v_0<v_1<\cdots<v_{r+1}=v
}
\mathcal C^{\mathrm{route}}(v_{r+1},v_r)
\otimes_k\cdots\otimes_k
\mathcal C^{\mathrm{route}}(v_1,v_0).
```

There are now two differentials.

## Vertical differential

The vertical differential applies the route-resolution differential inside one
tensor factor:

```math
d_{\mathrm{route}}.
```

It changes route-coherence degree but leaves the intermediate-node chain fixed.

## Horizontal differential

The horizontal differential removes an intermediate node by composing the
adjacent route-resolution factors:

```math
d_{\mathrm{fact}}.
```

It changes factorization degree but preserves total route-resolution degree.

With the usual total-complex signs,

```math
d_{\mathrm{tot}}=
d_{\mathrm{route}}
+
(-1)^{\deg_{\mathrm{route}}}d_{\mathrm{fact}},
```

and

```math
d_{\mathrm{tot}}^2=0.
```

The primary combined object is the filtered bicomplex

```math
\mathbb B_{\bullet,\bullet}^{\mathrm{RF}}(v,u),
```

where “RF” means route-factorization.

# 12. Recovering interval topology from the bicomplex

Take vertical homology first.

For every comparable pair $a<b$,

```math
H_j\mathcal C^{\mathrm{route}}(b,a)=
\begin{cases}
k,&j=0,\\
0,&j>0.
\end{cases}
```

Each tensor product in vertical homology becomes one copy of $k$ for every
strict node chain

```math
u=v_0<v_1<\cdots<v_{r+1}=v.
```

The remaining horizontal differential deletes intermediate nodes with
alternating signs.

The remaining horizontal complex is the augmented simplicial chain complex of
the open interval:

```math
\Delta(u,v).
```

After the conventional index shift,

```math
H_*\bigl(
\mathrm{Tot}
\mathbb B^{\mathrm{RF}}(v,u)
\bigr)
\cong
\widetilde H_*(\Delta(u,v);k).
```

Interval topology is obtained by:

```math
\text{resolve every thin factor by its actual routes}
\quad\longrightarrow\quad
\text{compose those resolved factors}
\quad\longrightarrow\quad
\text{take total homology}.
```

The bicomplex unifies the resolved and thin layers.

# 13. Limitations of total homology as a complete invariant

Taking total homology discards most route information.

The vertical route complexes are contractible, so their individual route
vertices disappear after homology.

Therefore the primary object cannot be merely

```math
H_*\mathrm{Tot}\mathbb B^{\mathrm{RF}}.
```

At least the filtered bicomplex itself must be retained:

```math
\left(
\mathbb B^{\mathrm{RF}},
F_{\mathrm{route}},
F_{\mathrm{fact}}
\right).
```

Its pages have different meanings:

* the initial page sees actual paths and their orthogonal route bases;
* the route differential sees the collapse ideal;
* later pages see factorization topology;
* the terminal homology sees only the surviving thin coherence.

The spectral sequence's intermediate pages identify the structural information
lost at each compression stage and determine the limiting group.

# 14. Diamond example

Consider the diamond

```math
u\to a\to v,
\qquad
u\to b\to v.
```

There are two complete routes:

```math
p_a,\quad p_b:u\to v.
```

## Vertical route resolution

The one-simplex

```math
(p_a,p_b)
```

has boundary

```math
p_b-p_a.
```

The boundary is the route-collapse relation.

## Horizontal interval topology

The open interval is

```math
(u,v)=\{a,b\}.
```

Its order complex consists of two isolated points, so

```math
\widetilde H_0(\Delta(u,v))\cong k.
```

The reduced homology class is the independent degree-two factorization relation.

These are related but not identical:

* vertically, $p_a-p_b$ is a boundary implementing the collapse;
* horizontally, the two disconnected factorization components create a
  nontrivial interval-coherence class.

# 15. Boolean $B_3$ example

From bottom to top, there are six saturated routes.

## Vertical direction

The route mapping space is

```math
E(\{p_1,\ldots,p_6\}),
```

which is contractible.

It contains six route vertices, an edge between every pair, a triangle filling
every route triple, and all higher coherent fillings.

Thus all six routes collapse completely coherently to one reachability arrow.

## Horizontal direction

The open interval order complex is a six-cycle:

```math
\Delta(\varnothing,[3])\simeq S^1.
```

The resulting isomorphism is

```math
\widetilde H_1\cong k.
```

The resulting class is the third-level coherence among the six diamond
relations.

Route-collapse coherence is contractible, while factorization coherence can be
topologically nontrivial.

# 16. Literature relation

Section 1 uses the contractibility of the nerve of the indiscrete groupoid on a
nonempty set. G. Segal, *Classifying spaces and spectral sequences*,
Publications Mathématiques de l'IHÉS 34 (1968), 105-112, states this for the
indiscrete groupoid on a topological group and supplies the homotopy invariance
of nerves in Proposition 2.1. The version used here is the set-level one, where
$\mathscr P_G(u,v)$ carries no group structure and no topology, and section 1
obtains it from the presence of an initial object.

The homotopy-coherent nerve named in section 2 is that of J.-M. Cordier and
T. Porter, *Vogt's theorem on categories of homotopy coherent diagrams*,
Mathematical Proceedings of the Cambridge Philosophical Society 100 (1986),
65-90, whose results assume the simplicially enriched category to be locally
Kan. That hypothesis holds for $\mathfrak R_G$: a horn in $E(S)$ determines its
vertices, and every tuple of elements of $S$ is a simplex of $E(S)$, so the
tuple of vertices fills the horn, while the mapping spaces at incomparable pairs
are empty.

The equivalence notion used in section 4 for the functor $\epsilon$ is the one
for simplicially enriched categories going back to W. G. Dwyer and D. M. Kan,
*Simplicial localizations of categories*, Journal of Pure and Applied Algebra 17
(1980), 267-284, and characterized in J. E. Bergner, *A model category structure
on the category of simplicial categories*, Transactions of the American
Mathematical Society 359 (2007), 2043-2058, arXiv:math/0406507, as an
equivalence on $\pi_0$ together with weak equivalences of mapping spaces.
Bergner's model structure is imposed on small simplicial categories, a
hypothesis satisfied by $\mathfrak R_G$ because $V$ and each route set
$\mathscr P_G(u,v)$ are sets; the criterion therefore applies to $\epsilon$,
whose mapping-space equivalences and $\pi_0$ isomorphism are established in
section 4.
