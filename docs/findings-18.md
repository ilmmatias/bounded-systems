# 1. The chaotic nerve of a route set

For a set $S$, define a simplicial set $E(S)$ by

$$
E(S)_n=S^{n+1}.
$$

Thus:

$$
E(S)_0=S,
$$

$$
E(S)_1=S\times S,
$$

$$
E(S)_2=S\times S\times S,
$$

and so on.

The face map $d_i$ deletes the $i$-th entry:

$$
d_i(s_0,\ldots,s_n)=
(s_0,\ldots,\widehat{s_i},\ldots,s_n),
$$

while the degeneracy $s_i$ repeats the $i$-th entry.

Equivalently, $E(S)$ is the nerve of the indiscrete groupoid whose objects are the elements of $S$ and which has exactly one isomorphism between every ordered pair of objects.

If $S\ne\varnothing$, this groupoid has an initial and terminal object after choosing any element, so its nerve is contractible. Nerves of categories and their contractibility in the presence of initial or terminal objects are standard categorical constructions.

But it remains richly marked:

* its vertices are the individual elements of $S$;
* an edge $(s_0,s_1)$ witnesses the formal identification of $s_0$ and $s_1$;
* a triangle $(s_0,s_1,s_2)$ witnesses compatibility among the three pairwise identifications;
* higher simplices provide all higher coherences.

# 2. Apply this to every route set

Let

$$
\mathscr P_G(u,v)
$$

be the set of finite paths from $u$ to $v$, including the identity path when $u=v$.

Define a simplicial category

$$
\mathfrak R_G
$$

with:

$$
\mathrm{Ob}(\mathfrak R_G)=V
$$

and mapping simplicial sets

$$
\mathrm{Map}_{\mathfrak R_G}(u,v)=
E\bigl(\mathscr P_G(u,v)\bigr).
$$

Consequently,

$$
\mathrm{Map}_{\mathfrak R_G}(u,v)_n=
\mathscr P_G(u,v)^{n+1}.
$$

An $n$-simplex is an ordered collection

$$
(p_0,\ldots,p_n)
$$

of $n+1$ routes with the same source and target.

## Composition

Given

$$
(p_0,\ldots,p_n)\in
\mathrm{Map}_{\mathfrak R_G}(u,v)_n
$$

and

$$
(q_0,\ldots,q_n)\in
\mathrm{Map}_{\mathfrak R_G}(v,w)_n,
$$

define composition coordinatewise:

$$
(q_0,\ldots,q_n)\circ(p_0,\ldots,p_n)=
(q_0p_0,\ldots,q_np_n).
$$

Faces and degeneracies act coordinatewise, so they commute with composition.

The identity at $u$ in degree $n$ is

$$
(1_u,\ldots,1_u).
$$

Path concatenation is associative, so this simplicial composition is strictly associative.

Thus $\mathfrak R_G$ is a genuine simplicially enriched category. Simplicial categories are categories whose morphism objects are simplicial sets, with composition defined simplicially; their homotopy-coherent nerves are standard models of higher categorical structure.

# 3. The two visible truncations

This single object contains both categories we previously kept separate.

## Its zero-simplices recover the path category

Since

$$
E(S)_0=S,
$$

we have

$$
\mathrm{Map}_{\mathfrak R_G}(u,v)_0=
\mathscr P_G(u,v).
$$

Composition of zero-simplices is ordinary path concatenation.

Therefore:

$$
\mathrm{sk}_0\mathfrak R_G=
\mathsf P(G).
$$

## Its connected components recover reachability

If $\mathscr P_G(u,v)\ne\varnothing$, then

$$
E(\mathscr P_G(u,v))
$$

is connected and contractible.

If there is no path, it is empty.

Therefore:

$$
\pi_0
\mathrm{Map}_{\mathfrak R_G}(u,v)=
\begin{cases}
{\ast},&u\le v,\\
\varnothing,&u\nleq v.
\end{cases}
$$

Hence:

$$
\pi_0\mathfrak R_G=
\mathsf R(G).
$$

We have therefore obtained the exact interpolation

$$
\mathsf P(G)=
\mathrm{sk}_0\mathfrak R_G
\quad\longrightarrow\quad
\mathfrak R_G
\quad\longrightarrow\quad
\pi_0\mathfrak R_G=
\mathsf R(G).
$$

The middle object retains actual paths while coherently realizing their collapse to reachability.

# 4. The canonical map to the thin category

Regard $\mathsf R(G)$ as a simplicial category with discrete mapping spaces.

There is a canonical enriched functor

$$
\epsilon:
\mathfrak R_G\longrightarrow\mathsf R(G)
$$

which fixes nodes and sends every tuple

$$
(p_0,\ldots,p_n)
$$

to the unique reachability arrow having those endpoints.

For every comparable pair $u\le v$, its mapping-space component is

$$
E(\mathscr P_G(u,v))
\longrightarrow
{\ast}.
$$

This is a weak homotopy equivalence because its source is contractible.

Thus $\epsilon$:

* is the identity on objects;
* induces weak equivalences on all nonempty mapping spaces;
* induces an isomorphism on $\pi_0$.

In the language of simplicial categories, it is therefore a Dwyer–Kan-type equivalence. Mapping-space equivalences are the central notion used to compare simplicial categories and their corresponding higher categories.

However, this must be interpreted carefully:

$$
\text{the weak-equivalence type of }\mathfrak R_G
\text{ remembers only reachability}.
$$

The original route structure is retained by its **marked zero-skeleton**.

So the complete object should be regarded as

$$
\left(
\mathfrak R_G,;
\mathsf P(G)=\mathrm{sk}_0\mathfrak R_G
\right),
$$

not merely as the unmarked homotopy type of $\mathfrak R_G$.

# 5. Acyclicity inside the simplicial category

Under A5,

$$
\mathscr P_G(v,v)=\{1_v\}.
$$

Therefore

$$
\mathrm{Map}_{\mathfrak R_G}(v,v)=
E({1_v})
\cong\Delta^0.
$$

There is exactly one endomorphism vertex and no nontrivial route loop.

Thus acyclicity becomes:

$$
\mathrm{Map}_{\mathfrak R_G}(v,v)
\text{ has exactly the identity as its marked vertex}.
$$

If directed cycles were allowed, this mapping space would have additional marked vertices corresponding to nonempty closed paths, even though its unmarked homotopy type would still be contractible.

Again, the marking is essential.

# 6. Linearization: the canonical route-resolution complex

Choose a commutative coefficient ring $k$.

For each endpoint pair define

$$
C_n^{\mathrm{route}}(v,u)=
k^{(\mathscr P_G(u,v)^{n+1})},
$$

the free $k$-module on $(n+1)$-tuples of routes.

The simplicial differential is

$$
d_n(p_0,\ldots,p_n)=
\sum_{i=0}^{n}
(-1)^i
(p_0,\ldots,\widehat{p_i},\ldots,p_n).
$$

At low degree:

$$
d_1(p_0,p_1)=p_1-p_0,
$$

and

$$
d_2(p_0,p_1,p_2)=
(p_1,p_2)-
(p_0,p_2)
+
(p_0,p_1).
$$

There is an augmentation

$$
\varepsilon:
C_0^{\mathrm{route}}(v,u)
\longrightarrow
k,\varepsilon_{v,u}
$$

sending every route $p:u\to v$ to the unique thin reachability arrow:

$$
\varepsilon(p)=\varepsilon_{v,u}.
$$

Because $E(\mathscr P_G(u,v))$ is contractible whenever it is nonempty, this augmented chain complex is exact:

$$
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
$$

Normalized chains on simplicial sets and dg categories are standard linearizations of simplicial higher structures.

# 7. The route ideal is exactly the first boundary

Recall that

$$
A_{v,u}=
e_vA(G)e_u=
k^{(\mathscr P_G(u,v))}=
C_0^{\mathrm{route}}(v,u).
$$

The route-collapse kernel is

$$
I_{v,u}=
\left\lbrace \sum_pc_pp: \sum_pc_p=0 \right\rbrace.
$$

But

$$
\mathrm{im}d_1=
\mathrm{span}\{p_1-p_0\}.
$$

Therefore:

$$
I_{v,u}=
\mathrm{im}
\left(
d_1:
C_1^{\mathrm{route}}(v,u)
\to
C_0^{\mathrm{route}}(v,u)
\right).
$$

Globally,

$$
I=\mathrm{im}d_1.
$$

So the familiar exact sequence

$$
0\to I\to A(G)\to B(P_G)\to0
$$

is merely the degree-zero end of the full route-resolution complex:

$$
\cdots
\to C_2^{\mathrm{route}}
\to C_1^{\mathrm{route}}
\to A(G)
\to B(P_G)
\to0.
$$

This is the canonical “all route relations” resolution that we were approaching earlier.

# 8. Higher simplices are relations among route identifications

A one-simplex

$$
(p,q)
$$

has boundary

$$
q-p.
$$

It witnesses the identification of two routes.

A two-simplex

$$
(p,q,r)
$$

has boundary

$$
(q,r)-(p,r)+(p,q).
$$

Thus:

$$
[p,r]=[p,q]+[q,r]
$$

at the level of route-identification chains.

It says that the direct identification $p\sim r$ agrees coherently with identifying

$$
p\sim q\sim r.
$$

A three-simplex gives the tetrahedral coherence among these triangular identifications.

Higher simplices continue indefinitely.

Therefore:

$$
\begin{aligned}
C_0 &: \text{actual routes},\\
C_1 &: \text{pairwise route identifications},\\
C_2 &: \text{coherences among identifications},\\
C_3 &: \text{coherences among those coherences},\\
&\ \vdots
\end{aligned}
$$

Because every mapping simplicial set is contractible, this full hierarchy has no residual positive-degree homology. Every coherence cycle is filled at a higher level.

Thus the collapse to one reachability arrow is completely coherent.

# 9. Finite and infinite route sets

Let

$$
S=\mathscr P_G(u,v).
$$

## Finite (S)

If $|S|=m<\infty$, then

$$
C_0^{\mathrm{route}}(v,u)\cong k^m.
$$

The augmentation kernel has rank

$$
m-1.
$$

In the Fock Hilbert realization, this is the codimension-one route-defect subspace orthogonal to the equal-route vector.

## Infinite (S)

The algebraic resolution remains perfectly defined:

* every chain contains finitely many tuples;
* every boundary is a finite alternating sum;
* no summation over all routes is required.

But the augmentation

$$
\sum_pc_pp\longmapsto\sum_pc_p
$$

does not extend boundedly to

$$
\ell^2(S).
$$

Correspondingly, its kernel is norm dense in the entire Fock route corner.

The simplicial resolution explains the earlier analytic singularity:

$$
\text{route collapse is exact algebraically,}
$$

but

$$
\text{it need not be a bounded Hilbert-space quotient}.
$$

Orthogonality and coherent route identification coexist, but they belong to different categorical levels.

# 10. Two distinct coherence directions

We can now distinguish two kinds of higher coherence that had previously been mixed together.

## Vertical coherence: identifying routes

At fixed endpoints $u,v$, the simplicial set

$$
E(\mathscr P_G(u,v))
$$

records how all actual routes collapse to one thin arrow.

It is contractible.

Its first boundary produces the route ideal $I_{v,u}$.

## Horizontal coherence: factoring a reachability arrow

The order complex

$$
\Delta(u,v)
$$

records the possible factorizations

$$
u<w_1<\cdots<w_r<v
$$

of the thin arrow $u\le v$ through intermediate nodes.

It need not be contractible.

Its reduced homology gives the interval-coherence groups

$$
\widetilde H_*(\Delta(u,v)).
$$

Thus:

$$
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
$$

This is the conceptual separation we needed.

# 11. The combined route-factorization bicomplex

Let

$$
\mathcal C^{\mathrm{route}}(b,a)
$$

denote the augmented route-resolution chain complex for paths $a\to b$.

For $u<v$, form

$$
\mathbb B_r(v,u)=
\bigoplus_{
u=v_0<v_1<\cdots<v_{r+1}=v
}
\mathcal C^{\mathrm{route}}(v_{r+1},v_r)
\otimes_k\cdots\otimes_k
\mathcal C^{\mathrm{route}}(v_1,v_0).
$$

There are now two differentials.

## Vertical differential

This applies the route-resolution differential inside one tensor factor:

$$
d_{\mathrm{route}}.
$$

It changes route-coherence degree but leaves the intermediate-node chain fixed.

## Horizontal differential

This removes an intermediate node by composing the two adjacent route-resolution factors:

$$
d_{\mathrm{fact}}.
$$

It changes factorization degree but preserves total route-resolution degree.

The standard bar construction organizes precisely such iterated compositions, while homotopy limits and colimits are commonly expressed through bar and cobar totalizations.

With the usual total-complex signs,

$$
d_{\mathrm{tot}}=
d_{\mathrm{route}}
+
(-1)^{\deg_{\mathrm{route}}}d_{\mathrm{fact}},
$$

and

$$
d_{\mathrm{tot}}^2=0.
$$

The primary combined object is the filtered bicomplex

$$
\mathbb B_{\bullet,\bullet}^{\mathrm{RF}}(v,u),
$$

where “RF” means route–factorization.

# 12. Recovering interval topology from it

Take vertical homology first.

For every comparable pair $a<b$,

$$
H_j\mathcal C^{\mathrm{route}}(b,a)=
\begin{cases}
k,&j=0,\\
0,&j>0.
\end{cases}
$$

Therefore each tensor product in vertical homology becomes one copy of $k$ for every strict node chain

$$
u=v_0<v_1<\cdots<v_{r+1}=v.
$$

The remaining horizontal differential deletes intermediate nodes with alternating signs.

This gives the augmented simplicial chain complex of the open interval:

$$
\Delta(u,v).
$$

Consequently, after the conventional index shift,

$$
H_*\bigl(
\mathrm{Tot}
\mathbb B^{\mathrm{RF}}(v,u)
\bigr)
\cong
\widetilde H_*(\Delta(u,v);k).
$$

So interval topology is obtained by:

$$
\text{resolve every thin factor by its actual routes}
\quad\longrightarrow\quad
\text{compose those resolved factors}
\quad\longrightarrow\quad
\text{take total homology}.
$$

This unifies the resolved and thin layers.

# 13. Why the total homology is still not the full invariant

Taking total homology discards most route information.

The vertical route complexes are contractible, so their individual route vertices disappear after homology.

Therefore the primary object cannot be merely

$$
H_*\mathrm{Tot}\mathbb B^{\mathrm{RF}}.
$$

We must retain at least the filtered bicomplex itself:

$$
\left(
\mathbb B^{\mathrm{RF}},
F_{\mathrm{route}},
F_{\mathrm{fact}}
\right).
$$

Its pages have different meanings:

* the initial page sees actual paths and their orthogonal route bases;
* the route differential sees the collapse ideal;
* later pages see factorization topology;
* the terminal homology sees only the surviving thin coherence.

The intermediate pages of the spectral sequence identify which structural information is lost at each compression stage, in addition to determining the limiting group.

# 14. Diamond example

Let

$$
u\to a\to v,
\qquad
u\to b\to v.
$$

There are two complete routes:

$$
p_a,\quad p_b:u\to v.
$$

## Vertical route resolution

The one-simplex

$$
(p_a,p_b)
$$

has boundary

$$
p_b-p_a.
$$

This is the route-collapse relation.

## Horizontal interval topology

The open interval is

$$
(u,v)=\{a,b\}.
$$

Its order complex consists of two isolated points, so

$$
\widetilde H_0(\Delta(u,v))\cong k.
$$

This is the independent degree-two factorization relation.

These are related but not identical:

* vertically, $p_a-p_b$ is a boundary implementing the collapse;
* horizontally, the two disconnected factorization components create a nontrivial interval-coherence class.

# 15. Boolean (B_3) example

From bottom to top, there are six saturated routes.

## Vertical direction

The route mapping space is

$$
E({p_1,\ldots,p_6}),
$$

which is contractible.

It contains:

* six route vertices;
* an edge between every pair;
* a triangle filling every route triple;
* and all higher coherent fillings.

Thus all six routes collapse completely coherently to one reachability arrow.

## Horizontal direction

The open interval order complex is a six-cycle:

$$
\Delta(\varnothing,[3])\simeq S^1.
$$

Therefore:

$$
\widetilde H_1\cong k.
$$

This is the nontrivial third-level coherence among the six diamond relations.

So:

$$
\text{route-collapse coherence is contractible,}
$$

while

$$
\text{factorization coherence can be topologically nontrivial.}
$$

This resolves the apparent tension in the previous constructions.
