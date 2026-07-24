# 1. Three different notions of infinite depth

For a node (v), let

[
\mathsf P_n(v)
]

be the set of length-(n) directed paths beginning at (v).

We must distinguish three properties.

## Global unbounded depth

For every (n), there is a length-(n) path somewhere:

[
\forall n\ge 0,\qquad
\exists v\in V:\mathsf P_n(v)\ne\varnothing.
]

Equivalently,

[
\mathcal A_n(G)\ne0
\qquad\text{for every }n.
]

## Rooted unbounded depth

There is one fixed node (v) from which paths of every finite length begin:

[
\exists v\in V;\forall n\ge0,\qquad
\mathsf P_n(v)\ne\varnothing.
]

## Actual infinite path

There is a composable sequence of channels

[
v_0\xrightarrow{e_1}v_1
\xrightarrow{e_2}v_2
\xrightarrow{e_3}\cdots.
]

These satisfy

[
\text{infinite path}
\Longrightarrow
\text{rooted unbounded depth}
\Longrightarrow
\text{global unbounded depth}.
]

Neither converse holds without additional conditions.

# 2. Two counterexamples

## Globally deep, but not rooted deeply

Take a disjoint union of finite chains:

[
C_1\sqcup C_2\sqcup C_3\sqcup\cdots,
]

where (C_n) has length (n).

There are paths of every finite length somewhere, but every individual node lies in a finite chain.

Thus:

[
\mathcal A_n\ne0\quad\forall n,
]

but no node has paths of every length, and there is no infinite path.

## Rooted deeply, but no infinite path

Take one root (v). For every positive integer (n), attach a separate branch of length (n):

[
v\to v_{n,1}\to v_{n,2}\to\cdots\to v_{n,n}.
]

Then

[
\mathsf P_k(v)\ne\varnothing
\qquad\forall k,
]

because a sufficiently long branch supplies a path of length (k).

But every chosen branch eventually terminates. There is no infinite path.

The failure is caused by infinite branching at (v): every desired length can be obtained by choosing a different first edge.

# 3. Infinite paths as an inverse limit

Every length-((n+1)) path has a length-(n) prefix. Define

[
\pi_n:
\mathsf P_{n+1}(v)\longrightarrow
\mathsf P_n(v)
]

by deleting the final edge.

The forward boundary from (v) is

[
\boxed{
\partial^+_vG
=============

\varprojlim_n
\left(
\mathsf P_n(v),\pi_n
\right).
}
]

An element of this inverse limit is a sequence

[
(p_0,p_1,p_2,\ldots)
]

such that:

* (p_n) has length (n);
* (p_n) is the prefix of (p_{n+1}).

Such a compatible sequence determines exactly one infinite path.

Therefore:

[
\boxed{
\partial^+_vG\ne\varnothing
\iff
\text{an infinite directed path starts at }v.
}
]

The total forward boundary is

[
\partial^+G
===========

\bigsqcup_{v\in V}\partial^+_vG.
]

This definition does not assume:

* countability;
* finite degree;
* a topology;
* a measure;
* or a global adjacency operator.

# 4. Why nonempty finite levels are insufficient

Rooted unbounded depth says merely

[
\mathsf P_n(v)\ne\varnothing
\qquad\forall n.
]

But the paths chosen at different levels might be incompatible.

In the finite-branch example above, a path of length (n) lies on the branch specifically selected to be sufficiently long. There need not be one sequence

[
p_1\prec p_2\prec p_3\prec\cdots
]

with every (p_n) extending the preceding one.

Thus:

[
\boxed{
\forall n,;\mathsf P_n(v)\ne\varnothing
\not\Rightarrow
\varprojlim_n\mathsf P_n(v)\ne\varnothing.
}
]

The obstruction is failure of compactness.

# 5. Finite branching restores the implication

Suppose every node has finitely many outgoing channels:

[
d^+(v)<\infty
\qquad(v\in V).
]

For a fixed root (v), every set (\mathsf P_n(v)) is then finite.

If paths of every length begin at (v), the rooted prefix tree is:

* infinite;
* finitely branching;
* nonempty at every level.

König’s infinity lemma therefore gives an infinite branch.

Hence:

[
\boxed{
\begin{aligned}
&d^+(w)<\infty\quad\forall w,\
&\mathsf P_n(v)\ne\varnothing\quad\forall n
\end{aligned}
\quad\Longrightarrow\quad
\partial^+_vG\ne\varnothing.
}
]

So under finite branching:

[
\boxed{
\text{rooted unbounded depth}
\iff
\text{an infinite path from that root}.
}
]

Uniformly bounded degree is unnecessary. Each node may have a different finite outdegree.

# 6. The compactness proof

The same result can be phrased through inverse limits.

Give each finite set (\mathsf P_n(v)) the discrete topology. Then

[
\prod_{n=0}^{\infty}\mathsf P_n(v)
]

is compact.

The compatibility conditions

[
\pi_n(p_{n+1})=p_n
]

define closed subsets.

Every finite collection of compatibility conditions is satisfiable: choose a sufficiently long finite path and take all its prefixes.

Compactness implies that all compatibility conditions can be satisfied simultaneously.

Thus the inverse limit is nonempty.

This identifies exactly what the infinitely branching counterexample lacks: its prefix levels are infinite discrete spaces and therefore are not compact.

# 7. The completed prefix space

To understand the boundary topologically, include both finite and infinite paths:

[
\Omega_G
========

\mathsf P(G)\sqcup\partial^+G.
]

For a finite path (p), define its cylinder

[
Z(p)
====

{
x\in\Omega_G:
p\text{ is an initial segment of }x
}.
]

Here (x) may itself be the finite path (p), a longer finite path, or an infinite path.

The cylinder sets form the basic observable neighborhoods.

Two cylinders satisfy:

[
Z(p)\cap Z(q)
=============

\begin{cases}
Z(q),&p\text{ is a prefix of }q,\
Z(p),&q\text{ is a prefix of }p,\
\varnothing,&p,q\text{ are incompatible}.
\end{cases}
]

This is a purely combinatorial topology derived from path composition.

# 8. Prefix projections and the boundary spectrum

For each finite path (p), introduce a projection (\Pi_p) satisfying

[
\Pi_p\Pi_q
==========

\begin{cases}
\Pi_q,&p\preceq q,\
\Pi_p,&q\preceq p,\
0,&p,q\text{ incompatible}.
\end{cases}
]

Concretely, on the finite-path Hilbert space,

[
\Pi_p\xi_q
==========

\begin{cases}
\xi_q,&p\text{ is a prefix of }q,\
0,&\text{otherwise}.
\end{cases}
]

The commuting family

[
{\Pi_p:p\in\mathsf P(G)}
]

forms a semilattice of projections.

A character of this semilattice is a map

[
\chi:{\Pi_p}\to{0,1}
]

that preserves multiplication and is not identically zero.

For every finite or infinite path (x), define

[
\chi_x(\Pi_p)
=============

\begin{cases}
1,&p\preceq x,\
0,&p\npreceq x.
\end{cases}
]

Conversely, a character selects a chain of mutually compatible prefixes.

There are exactly two possibilities:

1. the selected prefixes have a longest member, producing a finite path;
2. their lengths are unbounded, producing an infinite path.

Therefore:

[
\boxed{
\operatorname{Spec}({\Pi_p})
\cong
\mathsf P(G)\sqcup\partial^+G.
}
]

The infinite boundary is precisely the set of **non-principal prefix characters**—those whose selected prefix chain has no maximal finite element.

This is an important operator-algebraic result:

[
\boxed{
\text{Infinite paths appear in the spectrum of the prefix diagonal,}
}
]

not necessarily as vectors in the finite-path Fock space.

# 9. Why infinite paths are not Fock basis vectors

The Fock Hilbert space is

[
\ell^2(\mathsf P(G)),
]

whose basis consists only of finite paths.

Let

[
x=e_1e_2e_3\cdots
]

be an infinite path, and let (p_n) be its length-(n) prefix.

Then the prefix projections form a decreasing chain:

[
\Pi_{p_1}
\ge
\Pi_{p_2}
\ge
\Pi_{p_3}
\ge\cdots.
]

On the finite-path Fock space,

[
\Pi_{p_n}\longrightarrow0
]

strongly.

Indeed, any fixed finite path eventually becomes too short to extend (p_n).

Yet the boundary character satisfies

[
\chi_x(\Pi_{p_n})=1
\qquad\forall n.
]

So the infinite path is not represented by a nonzero vector lying in

[
\bigcap_n\operatorname{Ran}\Pi_{p_n}.
]

That intersection is zero.

Instead, the infinite path is an asymptotic character of the commutative prefix algebra.

This cleanly separates:

[
\boxed{
\text{finite path states}
\quad\text{from}\quad
\text{boundary paths at infinity}.
}
]

# 10. Finite paths at finite and infinite emitters

The topology distinguishes finite branching from infinite branching.

Let (p) end at node (v).

If (v) emits finitely many edges (e_1,\ldots,e_k), then

[
{p}
===

Z(p)
\setminus
\bigcup_{i=1}^k Z(pe_i).
]

Thus (p) is isolated in the prefix space.

If (v) emits infinitely many edges, no finite list of exclusions removes every proper extension of (p). The point (p) need not be isolated.

This explains the rooted counterexample topologically.

For the infinitely branching root (v), longer and longer finite branches can converge back to the finite path (1_v), rather than converging to an infinite branch.

Under finite branching, every finite path is isolated. Therefore an accumulation point of paths whose lengths tend to infinity must be an actual infinite path.

That is the topological form of König’s lemma.

# 11. Formal resolvent and the inverse system

Recall the universal channel element

[
\mathbf E=\sum_{e\in E}e
]

in the formal path completion, and

[
R_G(z)
======

# (1-z\mathbf E)^{-1}

\sum_{n=0}^{\infty}z^n\mathbf E^n.
]

Its degree-(n) support is exactly the set of length-(n) paths:

[
\operatorname{supp}(\mathbf E^n)
================================

\mathsf P_n(G).
]

Path factorization supplies the truncation maps

[
\pi_n:
\operatorname{supp}(\mathbf E^{n+1})
\to
\operatorname{supp}(\mathbf E^n).
]

Therefore:

[
\boxed{
\partial^+_vG
=============

\varprojlim_n
\operatorname{supp}
\left(
e_{\bullet}\mathbf E^ne_v
\right),
}
]

with the source corner fixed at (v).

So the full marked formal resolvent does determine the infinite boundary. It does not do so through any single coefficient or spectral value, but through the inverse system formed by all degrees simultaneously.

The correct hierarchy is:

[
\boxed{
R_G(z)
\longrightarrow
{\text{finite path levels}}
\longrightarrow
{\text{prefix maps}}
\longrightarrow
\partial^+G.
}
]

# 12. The tail map

For a nonempty finite or infinite path

[
x=e_1e_2e_3\cdots,
]

define

[
\sigma(x)=e_2e_3\cdots.
]

This deletes the first primitive channel.

It is not a time-evolution law. It is a syntactic operation on channel factorizations.

For finite paths, it reduces compositional length by one. For infinite paths, it produces the remaining infinite tail.

## Acyclicity theorem

A system is acyclic if and only if the infinite-path tail map has no periodic point of positive period.

If

[
\sigma^k(x)=x
]

for some (k>0), then the first (k) channels repeat indefinitely. They form a directed cycle.

Conversely, a directed cycle can be repeated forever to produce a periodic infinite path.

Therefore:

[
\boxed{
\text{A5}
\iff
\sigma\text{ has no positive-period infinite boundary points}.
}
]

This is a boundary-space version of acyclicity.

Again, it introduces no physical clock. Periodicity here means repetition of a path word under prefix deletion.

# 13. Tail equivalence

Two infinite paths are tail equivalent when

[
\sigma^m(x)=\sigma^n(y)
]

for some (m,n\ge0).

This means the paths may begin differently but eventually merge into the same infinite communication route.

Tail equivalence records confluence:

[
\begin{matrix}
&\text{route }x&\searrow\
&&\text{shared infinite tail}\
&\text{route }y&\nearrow
\end{matrix}
]

It is invisible to simple path counts and often invisible to aggregate spectra, but it is intrinsic to the full path structure.

# 14. Forward and backward boundaries

Direction gives two distinct boundary notions.

## Forward boundary

[
\partial^+G
]

contains paths

[
v_0\to v_1\to v_2\to\cdots.
]

## Backward boundary

[
\partial^-G
]

contains chains

[
\cdots\to v_{-2}\to v_{-1}\to v_0.
]

## Bi-infinite boundary

[
\partial^{\mathbb Z}G
]

contains chains indexed by all integers:

[
\cdots\to v_{-1}\to v_0\to v_1\to\cdots.
]

A5 permits all three kinds because none requires a directed cycle.

A system may have:

* a nonempty forward boundary but empty backward boundary;
* a nonempty backward boundary but empty forward boundary;
* both;
* neither.

For example:

[
0\to1\to2\to\cdots
]

has a forward boundary but no backward boundary from node (0).

The integer chain

[
\cdots\to-1\to0\to1\to\cdots
]

has both and contains a bi-infinite path.

# 15. Exact classification of depth phenomena

We can now classify the main possibilities.

| Property                                               | Algebraic/formal signature            | Boundary signature                    |
| ------------------------------------------------------ | ------------------------------------- | ------------------------------------- |
| Finite height (h)                                      | (J^{h+1}=0); (R_G(z)) polynomial      | (\partial^+G=\varnothing)             |
| Unbounded finite paths, no rooted unboundedness        | (J^n\ne0) for all (n)                 | all (\partial^+_vG) empty             |
| Rooted unbounded depth, infinite branching obstruction | all (\mathsf P_n(v)\ne\varnothing)    | (\partial^+_vG=\varnothing)           |
| Actual infinite path                                   | compatible prefixes at all depths     | (\partial^+_vG\ne\varnothing)         |
| Bi-infinite chain                                      | compatible forward and backward tails | (\partial^{\mathbb Z}G\ne\varnothing) |

This is the first layer of the theory that distinguishes genuine infinite structure from mere absence of a finite height bound.
