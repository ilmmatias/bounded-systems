# 1. Gluing intervals through a node

For

```math
u<v<w,
```

a strict chain from $u$ to $w$ that passes through $v$ decomposes uniquely
into:

```math
u<\cdots<v
\qquad\text{and}\qquad
v<\cdots<w.
```

At the simplicial level, this gives a canonical concatenation pattern

```math
\Delta(u,v)
\quad+\quad
v
\quad+\quad
\Delta(v,w)
\longrightarrow
\Delta(u,w).
```

For a longer sequence

```math
u=v_0<v_1<\cdots<v_r=w,
```

the same construction concatenates factorization chains from every interval

```math
(v_{i-1},v_i).
```

These concatenations are strictly compatible with regrouping: first combining
the intervals around $v_1$ or those around $v_2$ yields the same full chain.

Thus the primary thin-coherence object is not merely

```math
\{\Delta(u,v)\}_{u<v},
```

but

```math
\left(
\{\Delta(u,v)\}_{u<v},
\{\text{all interval-concatenation maps}\}
\right).
```

# 2. The derived reachability category

Fix a coefficient field $k$. Define a graded category

```math
\mathscr E_G
```

whose objects are the nodes of $G$.

For $u<v$, set

```math
\mathscr E_G^n(v,u)=
\widetilde C^{\,n-2}
\bigl(\Delta(u,v);k\bigr),
```

where $\widetilde C^\bullet$ is the augmented reduced simplicial cochain
complex.

Also define

```math
\mathscr E_G^0(u,u)=k\,1_u,
```

and

```math
\mathscr E_G^\bullet(v,u)=0
```

when $u$ and $v$ are incomparable or $v<u$.

The shift by two gives the expected degrees:

* a cover $u\lessdot v$ has empty open interval, whose reduced cochains occur
  in degree $-1$, so it becomes a degree-one morphism;
* a diamond relation occurs in degree two;
* the Boolean $B_3$ hexagon occurs in degree three.

The differential is the shifted simplicial coboundary:

```math
d:
\mathscr E_G^n(v,u)
\longrightarrow
\mathscr E_G^{n+1}(v,u).
```

Only finite chains are used, so the construction is defined for arbitrary
set-sized posets without local-finiteness or countability assumptions: every
simplex is a finite chain, every coboundary evaluation involves finitely many
faces, every cochain composition examines one finite chain, and no sum over an
entire interval is needed.

# 3. Cochain-level composition

Take

```math
f\in
\mathscr E_G^q(v,u)=
\widetilde C^{q-2}(\Delta(u,v);k),
```

and

```math
g\in
\mathscr E_G^p(w,v)=
\widetilde C^{p-2}(\Delta(v,w);k).
```

Their composite

```math
g\star_v f
\in
\mathscr E_G^{p+q}(w,u)
```

is supported on chains whose distinguished $q$-th intermediate node is $v$.

Explicitly, for

```math
u<x_1<\cdots<x_{p+q-1}<w,
```

define, up to the standard suspension sign,

```math
(g\star_v f)
(x_1<\cdots<x_{p+q-1})=
\begin{cases}
\pm\,g(x_{q+1}<\cdots<x_{p+q-1})
\,f(x_1<\cdots<x_{q-1}),
&x_q=v,\\[2mm]
0,&x_q\ne v.
\end{cases}
```

When $q=1$, the list supplied to $f$ is empty; that is exactly the augmented
degree-$-1$ cover class.

The degrees match because

```math
(q-2)+(p-2)+2=p+q-2.
```

The extra two positions join the lower factorization, the intermediate node
$v$, and the upper factorization.

With the standard signs,

```math
d(g\star f)=
dg\star f
+
(-1)^p g\star df,
```

and composition is associative:

```math
h\star(g\star f)=
(h\star g)\star f.
```

Thus $\mathscr E_G$ is a differential graded category. Its noncommutativity is
directional. A product exists only when endpoints match in the correct order;
reversing it is generally impossible or zero.

# 4. Cohomology and the Yoneda category

Taking cohomology gives

```math
H^n\mathscr E_G(v,u)=
\widetilde H^{\,n-2}
\bigl(\Delta(u,v);k\bigr).
```

For finite posets, these groups identify with extension groups between the
corresponding simple modules of the incidence algebra:

```math
H^n\mathscr E_G(v,u)
\cong
\operatorname{Ext}_{B(P_G)}^n(S_u,S_v),
```

subject to the usual left/right module convention. For infinite posets, this
identification with Ext over a particular completed incidence algebra may
require additional finiteness or module-theoretic hypotheses, while
$\mathscr E_G$ itself is unconditional.

The induced product

```math
\operatorname{Ext}^p(S_v,S_w)
\otimes
\operatorname{Ext}^q(S_u,S_v)
\longrightarrow
\operatorname{Ext}^{p+q}(S_u,S_w)
```

is the Yoneda product. Incidence algebras are path algebras modulo the
parallel-path ideal, and poset-interval combinatorics governs their projective
resolutions and Ext groups.

Thus the individual cohomology groups assemble into a graded category:

```math
\mathcal Y_G=
H^\bullet(\mathscr E_G).
```

# 5. A three-node chain

Consider $u<v<w$.

Both covers give degree-one classes,

```math
\eta_{v,u}\in H^1\mathscr E_G(v,u),
\qquad
\eta_{w,v}\in H^1\mathscr E_G(w,v).
```

Their cochain composite is supported on the single intermediate node $v$.

However,

```math
\Delta(u,w)=\{v\}
```

is contractible, so

```math
\widetilde H^0(\Delta(u,w))=0.
```

Consequently,

```math
\eta_{w,v}\eta_{v,u}=0.
```

The reachability arrows still compose:

```math
u\le v\le w
\implies
u\le w.
```

The unique two-step factorization creates no independent degree-two coherence
class.

```math
\text{reachability composition}
\neq
\text{Yoneda-coherence composition}.
```

# 6. A diamond

Let $a$ and $b$ be incomparable elements satisfying $0<a<1$ and $0<b<1$.

There are four cover classes:

```math
\eta_{a,0},\quad
\eta_{1,a},\quad
\eta_{b,0},\quad
\eta_{1,b}.
```

The open interval

```math
(0,1)=\{a,b\}
```

consists of two isolated points, so

```math
H^2\mathscr E_G(1,0)=
\widetilde H^0(\{a,b\};k)
\cong k.
```

The two cover products are the cochains supported at $a$ and $b$. Reduced
cohomology identifies their sum with zero. With consistent orientation,

```math
\eta_{1,a}\eta_{a,0}=
-\eta_{1,b}\eta_{b,0}
\ne0.
```

The class is dual to the incidence-algebra relation identifying the two
parallel paths:

```math
(0\to a\to1)=
(0\to b\to1).
```

The original relation uses equality; its dual Yoneda relation appears with an
alternating sign.

# 7. Boolean intervals

For the Boolean lattice $B_d$,

```math
\Delta(\varnothing,[d])
\simeq S^{d-2},
```

so

```math
H^d\mathscr E_G([d],\varnothing)\cong k.
```

Every saturated chain corresponds to a permutation

```math
\pi\in S_d.
```

Composing the $d$ cover classes along that chain gives the top degree class.
Exchanging two adjacent steps reverses its orientation, so after a consistent
choice of generator $\omega$,

```math
\eta_{\pi(d)}\cdots\eta_{\pi(1)}=
\operatorname{sgn}(\pi)\,\omega.
```

The diamond relations account for adjacent exchanges, and higher interval
topology makes all sequences of such exchanges coherently compatible.

The exterior-like behavior is consistent with the Koszul property of graded
incidence algebras under the relevant Cohen-Macaulay interval conditions, which
Boolean intervals satisfy.

# 8. The Yoneda product is not always enough

The graded category

```math
H^\bullet(\mathscr E_G)
```

retains the cohomology groups and binary product but forgets the cochain
complexes and their specific null-homotopies.

For example, a product may vanish in cohomology because it is a coboundary:

```math
g\star f=dh.
```

The cohomology category remembers only that the product is zero. It forgets
the cochain $h$ witnessing why it is zero.

When several such null-homotopies interact, that forgotten information
produces higher operations.

# 9. The minimal $A_\infty$ category

Transfer the dg category $\mathscr E_G$ to its cohomology. The result is a
minimal $A_\infty$ category with operations

```math
m_r:
H^\bullet\mathscr E_G(v_r,v_{r-1})
\otimes\cdots\otimes
H^\bullet\mathscr E_G(v_1,v_0)
\longrightarrow
H^\bullet\mathscr E_G(v_r,v_0)
```

of degree

```math
2-r.
```

Here $m_1=0$, $m_2$ is the Yoneda product, and the higher operations
$m_3,m_4,\ldots$ record dependencies among products and null-homotopies. The
transfer requires a choice of representatives and contracting homotopies, so
the individual operations are not canonical; Section 11 records what survives
that choice.

For example,

```math
m_3(c,b,a)
```

may be nonzero when

```math
m_2(b,a)=0
\qquad\text{and}\qquad
m_2(c,b)=0,
```

but the chosen null-homotopies need not be compatible. The obstruction is
closely related to a triple Massey product.

For a finite quiver with an admissible relation ideal over a field, the higher
operations of the corresponding minimal $A_\infty$ structure on the Ext algebra
of the simples are known to encode the defining relations: the coefficients of
$m_r$ on degree-one classes recover the length-$r$ relations, and that algebra
is generated in degrees zero and one. The reachability-poset argument here is
independent of both statements and allows infinite posets.

# 10. Origin of the higher operations

The operations

```math
m_3,m_4,\ldots
```

are not new interaction rules placed on the system.

They arise through the sequence

```math
\text{reachability order}
\longrightarrow
\text{interval cochain dg category}
\longrightarrow
\text{cohomology compression}
\longrightarrow
A_\infty\text{ correction data}.
```

The full dg category is already strictly associative.

Higher $A_\infty$ operations appear only after replacing the full chain-level
object by its smaller cohomology groups. They restore information lost under
this compression.

The correct interpretation is therefore

```math
A_\infty\text{ operations measure compression loss, not added dynamics}.
```

# 11. Canonical structure

A transferred minimal $A_\infty$ structure requires choices such as
representatives and contracting homotopies. Therefore the individual formulas
for

```math
m_3,m_4,\ldots
```

are not absolutely canonical.

But the resulting $A_\infty$ quasi-isomorphism type is canonical.

The more directly canonical object is the dg category itself:

```math
\mathscr E_G.
```

The comparison is

```math
\mathscr E_G
\longrightarrow
H^\bullet(\mathscr E_G)
\longrightarrow
\bigl(H^\bullet(\mathscr E_G),m_2,m_3,\ldots\bigr).
```

The first object is large and strict.

The second is small but loses information.

The third is small while retaining the lost information up to higher coherent
operations.

# 12. Koszul versus non-Koszul reachability

Suppose the reachability poset is finite, graded, and its intervals satisfy the
Cohen-Macaulay conditions that make the incidence algebra Koszul. Then the Ext
groups are concentrated on the expected diagonal.

That degree concentration forces

```math
m_r=0
\qquad(r\ge3)
```

in the grading-compatible minimal model: such an $m_r$ has cohomological degree
$2-r$ and preserves internal degree, so on classes of cohomological degrees
$n_1,\ldots,n_r$ its value has cohomological degree $\sum_in_i+2-r$ and internal
degree $\sum_in_i$, and diagonal concentration of the target requires $r=2$.

Thus the ordinary Yoneda algebra with its binary product is sufficient:

```math
\text{Koszul case}
\implies
\text{no essential higher }A_\infty\text{ products}.
```

For a non-Koszul or nongraded incidence structure, the binary product may not
retain all relation data, making nonzero higher operations essential.

The Cohen-Macaulay condition on intervals is therefore a topological criterion
for the Koszul side of this division.

# 13. A correction to the previous hierarchy

The previous hierarchy treated the individual interval homotopy types

```math
\{\Delta(u,v)\}
```

as the primary thin-coherence invariant.

That was incomplete.

Two systems could have intervals with matching homotopy types while differing
in how the intervals sit inside larger intervals and how their classes compose.

The correct object is the compositional interval system:

```math
\mathbf{Int}(G)=
\left(
\{\Delta(u,v)\}_{u<v},
\{\text{concatenation-at-}v\}_{u<v<w}
\right),
```

or equivalently its cochain realization

```math
\mathscr E_G.
```

The separate homotopy groups and Ext groups are shadows of this richer object.

# 14. Relationship to the original channel structure

The derived reachability category depends only on the thin reachability poset.

It still does not remember parallel primitive channels, shortcut edges,
multiple original paths realizing one order chain, or original path lengths
when shortcuts exist.

Therefore the complete framework has two distinct layers. The resolved
communication layer, represented by $\bigl(A(G),D(G),\{e\in E\}\bigr)$, retains
the nodes, primitive channels, and all actual routes. The derived thin layer
$\mathscr E_G$ retains the factorization topology and higher coherence of the
reachability order.

They are linked by the route-collapse map

```math
Q:A(G)\to B(P_G).
```

The combined object is

```math
\mathbf B_{\mathrm{der}}(G)=
\left(
A(G),
D(G),
Q,
\mathscr E_G
\right).
```

The first component is already sufficient to reconstruct $G$. The additional
components expose systematic derived invariants that spectra and path counts do
not reveal.

# 15. Literature relation

The identification in section 4 of $H^n\mathscr E_G(v,u)$ with an Ext group
between simple modules of a finite incidence algebra is the theorem of K. Igusa
and D. Zacharia, *On the cohomology of incidence algebras of partially ordered
sets*, Communications in Algebra 18 (1990), 873-887, stated there for a finite
poset over a field and for a nonempty open interval, with the larger element in
the first argument. The presentation of an incidence algebra as a path algebra
modulo the parallel-path ideal, also used in section 4, is that of C. Cibils,
*Cohomology of incidence algebras and simplicial complexes*, Journal of Pure and
Applied Algebra 56 (1989), 221-232, for a finite poset. The Hochschild
cohomology of such an algebra is identified with the simplicial cohomology of
the complex of poset chains in M. Gerstenhaber and S. D. Schack, *Simplicial
cohomology is Hochschild cohomology*, Journal of Pure and Applied Algebra 30
(1983), 143-156; that statement concerns Hochschild cohomology and not the Ext
groups between simple modules used here.

The transfer performed in section 9 rests on the existence of a minimal model,
proved in T. V. Kadeishvili, *Algebraic structure in the homology of an
$A(\infty)$-algebra*, Soobshcheniya Akademii Nauk Gruzinskoi SSR 108 (1982),
249-252, where the model is unique up to a non-unique isomorphism; that
non-uniqueness is the choice dependence recorded in sections 9 and 11. The
finite-quiver statements quoted in section 9 are those of B. Keller,
*A-infinity algebras in representation theory*, in Representations of Algebras,
Volume I, Beijing Normal University Press, 2002, 74-86, for a field and a finite
quiver with admissible ideal: the coefficients of $m_r$ on degree-one classes
give the relations, the Ext algebra of the simples is generated in degrees zero
and one, and that algebra is formal exactly when the quiver algebra is Koszul.
Section 12 does not use the last equivalence; it derives $m_r=0$ for $r\ge3$ in
the grading-compatible minimal model from a degree count. The relation of the
higher operations to Massey products, invoked in section 9, is developed for
connected graded algebras in D.-M. Lu, J. H. Palmieri, Q.-S. Wu, and
J. J. Zhang, *A-infinity structure on Ext-algebras*, Journal of Pure and Applied
Algebra 213 (2009), 2017-2037, arXiv:math/0606144, where $m_n$ on
$\operatorname{Ext}^1$ produces the relation coefficients; $\mathscr E_G$ is not
a connected graded algebra and carries no such internal grading in general.

The Koszul criterion invoked in sections 7 and 12 is the biconditional between
the Koszul property of the incidence algebra and the Cohen-Macaulay property of
the open intervals, proved in P. Polo, *On Cohen-Macaulay posets, Koszul
algebras and certain modules associated to Schubert varieties*, Bulletin of the
London Mathematical Society 27 (1995), 425-434, for a finite poset, and in
D. Woodcock, *Cohen-Macaulay complexes and Koszul rings*, Journal of the London
Mathematical Society 57 (1998), 398-410, for a finite graded poset, which is the
hypothesis-matching form for the finite graded situation assumed in section 12.
Each source cited in this section assumes a finite poset, or a finite quiver
over a field, whereas $\mathscr E_G$ is defined for arbitrary set-sized
reachability posets and its composition is strictly associative at cochain level
by section 3.
