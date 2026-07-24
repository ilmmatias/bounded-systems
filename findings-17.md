# 1. Gluing intervals through a node

For

[
u<v<w,
]

a strict chain from (u) to (w) that passes through (v) decomposes uniquely into:

[
u<\cdots<v
\qquad\text{and}\qquad
v<\cdots<w.
]

At the simplicial level, this gives a canonical concatenation pattern

[
\Delta(u,v)
\quad+\quad
v
\quad+\quad
\Delta(v,w)
\longrightarrow
\Delta(u,w).
]

For a longer sequence

[
u=v_0<v_1<\cdots<v_r=w,
]

the same construction concatenates factorization chains from every interval

[
(v_{i-1},v_i).
]

These concatenations are strictly compatible with regrouping. Whether we first combine the intervals around (v_1) or those around (v_2), the resulting full chain is the same.

Thus the primary thin-coherence object is not merely

[
{\Delta(u,v)}_{u<v},
]

but

[
\boxed{
\left(
{\Delta(u,v)}_{u<v},
{\text{all interval-concatenation maps}}
\right).
}
]

This type of cochain, operadic, and brace-compatible structure on posets and their incidence algebras is part of the broader cohomology-comparison framework.

# 2. The derived reachability category

Fix a coefficient field (k). Define a graded category

[
\mathscr E_G
]

whose objects are the nodes of (G).

For (u<v), set

[
\boxed{
\mathscr E_G^n(v,u)
===================

\widetilde C^{,n-2}
\bigl(\Delta(u,v);k\bigr),
}
]

where (\widetilde C^\bullet) is the augmented reduced simplicial cochain complex.

Also define

[
\mathscr E_G^0(u,u)=k,1_u,
]

and

[
\mathscr E_G^\bullet(v,u)=0
]

when (u) and (v) are incomparable or (v<u).

The shift by two gives the expected degrees:

* a cover (u\lessdot v) has empty open interval, whose reduced cochains occur in degree (-1), so it becomes a degree-one morphism;
* a diamond relation occurs in degree two;
* the Boolean (B_3) hexagon occurs in degree three.

The differential is the shifted simplicial coboundary:

[
d:
\mathscr E_G^n(v,u)
\longrightarrow
\mathscr E_G^{n+1}(v,u).
]

This construction uses finite chains only, so it is defined for arbitrary set-sized posets, with no local-finiteness or countability assumption.

# 3. Cochain-level composition

Take

[
f\in
\mathscr E_G^q(v,u)
===================

\widetilde C^{q-2}(\Delta(u,v);k),
]

and

[
g\in
\mathscr E_G^p(w,v)
===================

\widetilde C^{p-2}(\Delta(v,w);k).
]

Their composite

[
g\star_v f
\in
\mathscr E_G^{p+q}(w,u)
]

is supported on chains whose distinguished (q)-th intermediate node is (v).

Explicitly, for

[
u<x_1<\cdots<x_{p+q-1}<w,
]

define, up to the standard suspension sign,

[
(g\star_v f)
(x_1<\cdots<x_{p+q-1})
======================

\begin{cases}
\pm,
g(x_{q+1}<\cdots<x_{p+q-1}),
f(x_1<\cdots<x_{q-1}),
&x_q=v,[2mm]
0,&x_q\ne v.
\end{cases}
]

When (q=1), the list supplied to (f) is empty; that is exactly the augmented degree-(-1) cover class.

The degrees work because:

[
(q-2)+(p-2)+2=p+q-2.
]

The extra two positions arise from joining the lower factorization, the intermediate node (v), and the upper factorization.

With the standard signs,

[
d(g\star f)
===========

dg\star f
+
(-1)^p g\star df,
]

and composition is associative:

[
h\star(g\star f)
================

(h\star g)\star f.
]

Therefore:

[
\boxed{
\mathscr E_G
\text{ is a differential graded category.}
}
]

Its noncommutativity is directional. A product exists only when endpoints match in the correct order; reversing it is generally impossible or zero.

# 4. Cohomology and the Yoneda category

Taking cohomology gives

[
H^n\mathscr E_G(v,u)
====================

\widetilde H^{,n-2}
\bigl(\Delta(u,v);k\bigr).
]

For finite posets, these groups identify with extension groups between the corresponding simple modules of the incidence algebra:

[
\boxed{
H^n\mathscr E_G(v,u)
\cong
\operatorname{Ext}_{B(P_G)}^n(S_u,S_v),
}
]

subject to the usual left/right module convention.

The induced product

[
\operatorname{Ext}^p(S_v,S_w)
\otimes
\operatorname{Ext}^q(S_u,S_v)
\longrightarrow
\operatorname{Ext}^{p+q}(S_u,S_w)
]

is the Yoneda product. Incidence algebras can be presented as path algebras modulo the parallel-path ideal, while their projective resolutions and Ext groups are governed by the combinatorics of the poset intervals.

Thus the isolated groups from the previous step assemble into a graded category:

[
\boxed{
\mathcal Y_G
============

H^\bullet(\mathscr E_G).
}
]

# 5. A three-node chain

Consider

[
u<v<w.
]

Both covers give degree-one classes:

[
\eta_{v,u}\in H^1\mathscr E_G(v,u),
]

[
\eta_{w,v}\in H^1\mathscr E_G(w,v).
]

Their cochain composite is supported on the single intermediate node (v).

But

[
\Delta(u,w)={v}
]

is contractible, so

[
\widetilde H^0(\Delta(u,w))=0.
]

Therefore

[
\boxed{
\eta_{w,v}\eta_{v,u}=0.
}
]

This is not saying that the reachability arrows fail to compose. They certainly compose:

[
u\le v\le w
\implies
u\le w.
]

It says that the unique two-step factorization creates no independent degree-two coherence class.

So:

[
\boxed{
\text{reachability composition}
\neq
\text{Yoneda-coherence composition}.
}
]

# 6. A diamond

Let

[
0<a<1,
\qquad
0<b<1,
]

with (a) and (b) incomparable.

There are four cover classes:

[
\eta_{a,0},\quad
\eta_{1,a},\quad
\eta_{b,0},\quad
\eta_{1,b}.
]

The open interval

[
(0,1)={a,b}
]

consists of two isolated points, so

[
H^2\mathscr E_G(1,0)
====================

\widetilde H^0({a,b};k)
\cong k.
]

The two cover products are the cochains supported at (a) and (b). Reduced cohomology identifies their sum with zero. With consistent orientation,

[
\boxed{
\eta_{1,a}\eta_{a,0}
====================

-\eta_{1,b}\eta_{b,0}
\ne0.
}
]

This is dual to the incidence-algebra relation identifying the two parallel paths:

[
(0\to a\to1)
============

(0\to b\to1).
]

The original relation uses equality; its dual Yoneda relation appears with an alternating sign.

# 7. Boolean intervals

For the Boolean lattice (B_d),

[
\Delta(\varnothing,[d])
\simeq S^{d-2},
]

so

[
H^d\mathscr E_G([d],\varnothing)\cong k.
]

Every saturated chain corresponds to a permutation

[
\pi\in S_d.
]

Composing the (d) cover classes along that chain gives the top degree class. Exchanging two adjacent steps reverses its orientation, so after a consistent choice of generator (\omega),

[
\boxed{
\eta_{\pi(d)}\cdots\eta_{\pi(1)}
================================

\operatorname{sgn}(\pi),\omega.
}
]

The diamond relations account for adjacent exchanges, while the higher interval topology ensures that all sequences of such exchanges are coherently compatible.

This exterior-like behavior is consistent with the fact that graded incidence algebras are Koszul exactly under the relevant Cohen–Macaulay interval conditions; Boolean intervals satisfy those conditions.

# 8. The Yoneda product is not always enough

The graded category

[
H^\bullet(\mathscr E_G)
]

retains the cohomology groups and their binary product. But it forgets the actual cochain complexes and the specific null-homotopies inside them.

For example, a product may vanish in cohomology because it is a coboundary:

[
g\star f=dh.
]

The cohomology category remembers only that the product is zero. It forgets the cochain (h) witnessing why it is zero.

When several such null-homotopies interact, that forgotten information produces higher operations.

# 9. The minimal (A_\infty) category

Transfer the dg category (\mathscr E_G) to its cohomology. The result is a minimal (A_\infty) category with operations

[
m_r:
H^\bullet\mathscr E_G(v_r,v_{r-1})
\otimes\cdots\otimes
H^\bullet\mathscr E_G(v_1,v_0)
\longrightarrow
H^\bullet\mathscr E_G(v_r,v_0)
]

of degree

[
2-r.
]

Here:

[
m_1=0,
]

[
m_2=\text{Yoneda product},
]

while

[
m_3,m_4,\ldots
]

record higher dependencies among products and null-homotopies.

For example,

[
m_3(c,b,a)
]

may be nonzero when

[
m_2(b,a)=0
\qquad\text{and}\qquad
m_2(c,b)=0,
]

but the chosen reasons for those two vanishings fail to fit together trivially. This is closely related to a triple Massey product.

A natural (A_\infty) structure exists on Ext, and its higher products encode defining relations; in suitable graded settings, the coefficients of (m_r) on degree-one classes recover length-(r) relations. The Yoneda algebra of simples is generated in degrees zero and one when regarded as a minimal (A_\infty) algebra.

# 10. These are not additional laws

This point matters for the project.

The operations

[
m_3,m_4,\ldots
]

are not new interaction rules placed on the bounded system.

They arise through the sequence

[
\boxed{
\text{reachability order}
\longrightarrow
\text{interval cochain dg category}
\longrightarrow
\text{cohomology compression}
\longrightarrow
A_\infty\text{ correction data}.
}
]

The full dg category is already strictly associative.

Higher (A_\infty) operations appear only because we replace that full chain-level object by its smaller cohomology groups. They restore information lost under this compression.

So the correct interpretation is:

[
\boxed{
A_\infty\text{ operations measure compression loss, not added dynamics}.
}
]

# 11. What is canonical

A transferred minimal (A_\infty) structure requires choices such as representatives and contracting homotopies. Therefore the individual formulas for

[
m_3,m_4,\ldots
]

are not absolutely canonical.

But the resulting (A_\infty) quasi-isomorphism type is canonical.

The more directly canonical object is the dg category itself:

[
\boxed{
\mathscr E_G.
}
]

The hierarchy is:

[
\mathscr E_G
\longrightarrow
H^\bullet(\mathscr E_G)
\longrightarrow
\bigl(H^\bullet(\mathscr E_G),m_2,m_3,\ldots\bigr).
]

The first object is large and strict.

The second is small but loses information.

The third is small while retaining the lost information up to higher coherent operations.

# 12. Koszul versus non-Koszul reachability

Suppose the reachability poset is finite, graded, and its intervals satisfy the Cohen–Macaulay conditions that make the incidence algebra Koszul. Then the Ext groups are concentrated on the expected diagonal.

That degree concentration forces

[
m_r=0
\qquad(r\ge3)
]

in the grading-compatible minimal model.

Thus the ordinary Yoneda algebra with its binary product is sufficient:

[
\boxed{
\text{Koszul case}
\implies
\text{no essential higher }A_\infty\text{ products}.
}
]

For a non-Koszul or nongraded incidence structure, the binary product may not retain all relation data. Nonzero higher operations can then be essential.

The Cohen–Macaulay characterization of Koszul incidence algebras gives the topological criterion separating these regimes.

# 13. A correction to the previous hierarchy

Previously, we treated the individual interval homotopy types

[
{\Delta(u,v)}
]

as the primary thin-coherence invariant.

That was incomplete.

Two systems could have intervals with matching homotopy types while differing in how the intervals sit inside larger intervals and how their classes compose.

The correct object is the **compositional interval system**:

[
\boxed{
\mathbf{Int}(G)
===============

\left(
{\Delta(u,v)}*{u<v},
{\text{concatenation-at-}v}*{u<v<w}
\right),
}
]

or equivalently its cochain realization

[
\boxed{
\mathscr E_G.
}
]

The separate homotopy groups and Ext groups are shadows of this richer object.

# 14. Relationship to the original channel structure

The derived reachability category depends only on the thin reachability poset.

It still does not remember:

* parallel primitive channels;
* shortcut edges;
* multiple original paths realizing one order chain;
* original path lengths when shortcuts exist.

Therefore the complete framework now has two distinct layers.

## Resolved communication layer

[
\boxed{
\bigl(A(G),D(G),{e\in E}\bigr)
}
]

retains nodes, primitive channels, and all actual routes.

## Derived thin layer

[
\boxed{
\mathscr E_G
}
]

retains the factorization topology and higher coherence of the reachability order.

They are linked by the route-collapse map

[
Q:A(G)\to B(P_G).
]

Thus the combined object is

[
\boxed{
\mathbf B_{\mathrm{der}}(G)
===========================

\left(
A(G),
D(G),
Q,
\mathscr E_G
\right).
}
]

The first component is already sufficient to reconstruct (G). The additional components expose systematic derived invariants that spectra and path counts do not reveal.

# 15. Cardinality-independent status

The combinatorial dg category remains valid for arbitrary cardinality because:

* every simplex is a finite chain;
* every coboundary evaluation involves finitely many faces;
* every cochain composition examines one finite chain;
* no sum over an entire interval is needed.

For infinite posets, the identification with Ext over a particular completed incidence algebra may require additional finiteness or module-theoretic hypotheses.

But the primary construction

[
\mathscr E_G
]

itself is unconditional.
