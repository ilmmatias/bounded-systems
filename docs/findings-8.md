# 1. Three different notions of infinite depth

For a node $v$, let

```math
\mathsf P_n(v)
```

be the set of length-$n$ directed paths beginning at $v$.

The following three notions of depth are distinct.

## Global unbounded depth

For every $n$, there is a length-$n$ path somewhere:

```math
\forall n\ge 0,\qquad
\exists v\in V:\mathsf P_n(v)\ne\varnothing.
```

Equivalently,

```math
\mathcal A_n(G)\ne0
\qquad\text{for every }n.
```

## Rooted unbounded depth

There is one fixed node $v$ from which paths of every finite length begin:

```math
\exists v\in V;\forall n\ge0,\qquad
\mathsf P_n(v)\ne\varnothing.
```

## Actual infinite path

There is a composable sequence of channels

```math
v_0\xrightarrow{e_1}v_1
\xrightarrow{e_2}v_2
\xrightarrow{e_3}\cdots.
```

These satisfy

```math
\text{infinite path}
\Longrightarrow
\text{rooted unbounded depth}
\Longrightarrow
\text{global unbounded depth}.
```

Neither converse holds without additional conditions.

# 2. Two counterexamples

## Global depth without rooted depth

Take a disjoint union of finite chains:

```math
C_1\sqcup C_2\sqcup C_3\sqcup\cdots,
```

where $C_n$ has length $n$.

There are paths of every finite length somewhere, but every individual node
lies in a finite chain.

```math
\mathcal A_n\ne0\quad\forall n,
```

but no node has paths of every length, and there is no infinite path.

## Rooted depth without an infinite path

Take one root $v$. For every positive integer $n$, attach a separate branch of
length $n$:

```math
v\to v_{n,1}\to v_{n,2}\to\cdots\to v_{n,n}.
```

Then

```math
\mathsf P_k(v)\ne\varnothing
\qquad\forall k,
```

because a sufficiently long branch supplies a path of length $k$.

But every chosen branch eventually terminates. There is no infinite path.

Infinite branching at $v$ causes the failure: choosing a different first edge
realizes every desired length.

# 3. Infinite paths as an inverse limit

Every length-$(n+1)$ path has a length-$n$ prefix. Define

```math
\pi_n:
\mathsf P_{n+1}(v)\longrightarrow
\mathsf P_n(v)
```

by deleting the final edge.

The forward boundary from $v$ is

```math
\partial^+_vG=
\varprojlim_n
\left(
\mathsf P_n(v),\pi_n
\right).
```

An element of this inverse limit is a sequence

```math
(p_0,p_1,p_2,\ldots)
```

in which $p_n$ has length $n$ and is the prefix of $p_{n+1}$. Such a compatible
sequence determines exactly one infinite path.

```math
\partial^+_vG\ne\varnothing
\iff
\text{an infinite directed path starts at }v.
```

The total forward boundary is

```math
\partial^+G=
\bigsqcup_{v\in V}\partial^+_vG.
```

This definition requires neither countability nor finite degree and introduces
no topology, measure, or global adjacency operator.

# 4. Nonempty finite levels and compatibility

Rooted unbounded depth says merely

```math
\mathsf P_n(v)\ne\varnothing
\qquad\forall n.
```

But the paths chosen at different levels might be incompatible.

In the finite-branch example of Section 2, a path of length $n$ lies on the
branch specifically selected to be sufficiently long. There need not be one
sequence

```math
p_1\prec p_2\prec p_3\prec\cdots
```

with every $p_n$ extending the preceding one.

```math
\forall n,\;\mathsf P_n(v)\ne\varnothing
\not\Rightarrow
\varprojlim_n\mathsf P_n(v)\ne\varnothing.
```

The obstruction is failure of compactness.

# 5. Finite branching restores the implication

Suppose every node has finitely many outgoing channels:

```math
d^+(v)<\infty
\qquad(v\in V).
```

For a fixed root $v$, every set $\mathsf P_n(v)$ is then finite.

If paths of every length begin at $v$, the rooted prefix tree is infinite,
finitely branching, and nonempty at every level. König's infinity lemma
therefore yields an infinite branch.

```math
\begin{aligned}
&d^+(w)<\infty\quad\forall w,\\
&\mathsf P_n(v)\ne\varnothing\quad\forall n
\end{aligned}
\quad\Longrightarrow\quad
\partial^+_vG\ne\varnothing.
```

Under finite branching, rooted unbounded depth at a node is equivalent to the
existence of an infinite path from that node. Uniformly bounded degree is
unnecessary. Each node may have a different finite outdegree.

# 6. The compactness proof

The same result can be phrased through inverse limits.

Give each finite set $\mathsf P_n(v)$ the discrete topology. Then

```math
\prod_{n=0}^{\infty}\mathsf P_n(v)
```

is compact.

The compatibility conditions

```math
\pi_n(p_{n+1})=p_n
```

define closed subsets.

Every finite set of compatibility conditions is satisfiable by taking all
prefixes of a sufficiently long finite path.

Compactness implies that all compatibility conditions can be satisfied
simultaneously.

Thus the inverse limit is nonempty.

The infinitely branching counterexample fails exactly because its prefix levels
are infinite discrete spaces and therefore are not compact.

# 7. The completed prefix space

To understand the boundary topologically, include both finite and infinite
paths:

```math
\Omega_G=
\mathsf P(G)\sqcup\partial^+G.
```

For a finite path $p$, define its cylinder

```math
Z(p)=
\{
x\in\Omega_G:
p\text{ is an initial segment of }x
\}.
```

Here $x$ may itself be the finite path $p$, a longer finite path, or an infinite
path.

The cylinder sets form the basic observable neighborhoods.

Two cylinders satisfy:

```math
Z(p)\cap Z(q)=
\begin{cases}
Z(q),&p\text{ is a prefix of }q,\\
Z(p),&q\text{ is a prefix of }p,\\
\varnothing,&p,q\text{ are incompatible}.
\end{cases}
```

The topology is purely combinatorial and comes from path composition.

# 8. Prefix projections and the boundary spectrum

For each finite path $p$, introduce a projection $\Pi_p$ satisfying

```math
\Pi_p\Pi_q=
\begin{cases}
\Pi_q,&p\preceq q,\\
\Pi_p,&q\preceq p,\\
0,&p,q\text{ incompatible}.
\end{cases}
```

Concretely, on the finite-path Hilbert space,

```math
\Pi_p\xi_q=
\begin{cases}
\xi_q,&p\text{ is a prefix of }q,\\
0,&\text{otherwise}.
\end{cases}
```

The commuting family

```math
\{\Pi_p:p\in\mathsf P(G)\}
```

forms a semilattice of projections.

A character of this semilattice is a map

```math
\chi:\{\Pi_p\}\to\{0,1\}
```

that preserves multiplication and is not identically zero.

For every finite or infinite path $x$, define

```math
\chi_x(\Pi_p)=
\begin{cases}
1,&p\preceq x,\\
0,&p\npreceq x.
\end{cases}
```

Conversely, a character selects a chain of mutually compatible prefixes.

If the selected prefixes have a longest member, the character is determined by a
finite path. If their lengths are unbounded, compatibility determines an
infinite path. Therefore,

```math
\mathrm{Spec}(\{\Pi_p\})
\cong
\mathsf P(G)\sqcup\partial^+G.
```

The infinite boundary is precisely the set of non-principal prefix characters,
those whose selected prefix chain has no maximal finite element.

Infinite paths thus occur as characters in the spectrum of the prefix diagonal,
rather than necessarily as vectors in the finite-path Fock space.

# 9. Infinite paths and Fock basis vectors

The Fock Hilbert space is

```math
\ell^2(\mathsf P(G)),
```

whose basis consists only of finite paths.

Let

```math
x=e_1e_2e_3\cdots
```

be an infinite path, and let $p_n$ be its length-$n$ prefix.

Then the prefix projections form a decreasing chain:

```math
\Pi_{p_1}
\ge
\Pi_{p_2}
\ge
\Pi_{p_3}
\ge\cdots.
```

On the finite-path Fock space,

```math
\Pi_{p_n}\longrightarrow0
```

strongly.

Indeed, any fixed finite path eventually becomes too short to extend $p_n$.

Yet the boundary character satisfies

```math
\chi_x(\Pi_{p_n})=1
\qquad\forall n.
```

The infinite path is not represented by a nonzero vector lying in

```math
\bigcap_n\mathrm{Ran}\Pi_{p_n}.
```

That intersection is zero.

Instead, the infinite path is an asymptotic character of the commutative prefix
algebra.

The finite-path vector states must therefore be distinguished from boundary
characters determined by paths at infinity.

# 10. Finite paths at finite and infinite emitters

The topology distinguishes finite branching from infinite branching.

Let $p$ end at node $v$.

If $v$ emits finitely many edges $e_1,\ldots,e_k$, then

```math
\{p\}=
Z(p)
\setminus
\bigcup_{i=1}^k Z(pe_i).
```

$p$ is isolated in the prefix space.

If $v$ emits infinitely many edges, no finite exclusion list removes every
proper extension of $p$, so $p$ need not be isolated.

The topology explains the rooted counterexample.

For the infinitely branching root $v$, increasingly long finite branches can
converge to the finite path $1_v$ rather than an infinite branch.

Under finite branching, every finite path is isolated; hence any accumulation
point of arbitrarily long paths must be an actual infinite path.

The implication is the topological form of König's lemma.

# 11. Formal resolvent and the inverse system

Recall the universal channel element

```math
\mathbf E=\sum_{e\in E}e
```

in the formal path completion, and

```math
R_G(z)=
(1-z\mathbf E)^{-1}=
\sum_{n=0}^{\infty}z^n\mathbf E^n.
```

Its degree-$n$ support is exactly the set of length-$n$ paths:

```math
\mathrm{supp}(\mathbf E^n)=
\mathsf P_n(G).
```

Path factorization supplies the truncation maps

```math
\pi_n:
\mathrm{supp}(\mathbf E^{n+1})
\to
\mathrm{supp}(\mathbf E^n).
```

Consequently, the forward boundary from $v$ is recovered as

```math
\partial^+_vG=
\varprojlim_n
\mathrm{supp}
\left(
e_{\bullet}\mathbf E^ne_v
\right),
```

with the source corner fixed at $v$. The full marked formal resolvent therefore
determines the finite path levels, their prefix maps, and hence the infinite
boundary through the inverse system of all degrees. No single coefficient or
spectral value carries this information.

# 12. The tail map

For a nonempty finite or infinite path

```math
x=e_1e_2e_3\cdots,
```

define

```math
\sigma(x)=e_2e_3\cdots.
```

Prefix deletion removes the first primitive channel from a channel
factorization.

It reduces finite-path length by one and produces the remaining infinite tail of
an infinite path.

## Theorem 1. Acyclicity and the tail map

A system is acyclic if and only if the infinite-path tail map has no periodic
point of positive period.

If

```math
\sigma^k(x)=x
```

for some $k>0$, then the first $k$ channels repeat indefinitely. They form a
directed cycle.

Conversely, a directed cycle can be repeated forever to produce a periodic
infinite path.

```math
\text{acyclicity}
\iff
\sigma\text{ has no positive-period infinite boundary points}.
```

The absence of periodic points is the boundary-space form of acyclicity.

Periodicity here means repetition of a path word under prefix deletion.

# 13. Tail equivalence

Two infinite paths are tail equivalent when

```math
\sigma^m(x)=\sigma^n(y)
```

for some $m,n\ge0$.

The paths may begin differently but eventually merge into the same infinite
communication route. Tail equivalence therefore records confluence:

```math
\begin{matrix}
&\text{route }x&\searrow\\
&&\text{shared infinite tail}\\
&\text{route }y&\nearrow
\end{matrix}
```

Although invisible to simple path counts and often to aggregate spectra, it is
intrinsic to the full path structure.

# 14. Forward and backward boundaries

Direction gives distinct forward, backward, and bi-infinite boundary notions.
The forward boundary $\partial^+G$ contains paths of the form

```math
v_0\to v_1\to v_2\to\cdots,
```

whereas the backward boundary $\partial^-G$ contains chains of the form

```math
\cdots\to v_{-2}\to v_{-1}\to v_0.
```

The bi-infinite boundary $\partial^{\mathbb Z}G$ consists of chains indexed by
all integers:

```math
\cdots\to v_{-1}\to v_0\to v_1\to\cdots.
```

Acyclicity permits all three because none requires a directed cycle. The forward
and backward boundaries are independent: either may be nonempty while the other
is empty, and both may be simultaneously empty or nonempty. For example, the
one-way chain

```math
0\to1\to2\to\cdots
```

has a forward boundary but no backward boundary from node $0$, whereas the
integer chain

```math
\cdots\to-1\to0\to1\to\cdots
```

has both and contains a bi-infinite path.

# 15. Depth phenomena

| Property                                               | Algebraic/formal signature            | Boundary signature                    |
| ------------------------------------------------------ | ------------------------------------- | ------------------------------------- |
| Finite height $h$                                      | $J^{h+1}=0$; $R_G(z)$ polynomial      | $\partial^+G=\varnothing$             |
| Unbounded finite paths, no rooted unboundedness        | $J^n\ne0$ for all $n$                 | all $\partial^+_vG$ empty             |
| Rooted unbounded depth, infinite branching obstruction | all $\mathsf P_n(v)\ne\varnothing$    | $\partial^+_vG=\varnothing$           |
| Actual infinite path                                   | compatible prefixes at all depths     | $\partial^+_vG\ne\varnothing$         |
| Bi-infinite chain                                      | compatible forward and backward tails | $\partial^{\mathbb Z}G\ne\varnothing$ |

The boundary layer distinguishes actual infinite paths from unbounded finite
depth.

# 16. Literature relation

Sections 5 and 10 invoke König's infinity lemma, proved in D. König, *Über
eine Schlußweise aus dem Endlichen ins Unendliche*, Acta Litterarum ac
Scientiarum Regiae Universitatis Hungaricae Francisco-Josephinae, Sectio
Scientiarum Mathematicarum 3 (1927), 121-130. The form matching section 5 takes
disjoint nonempty finite sets $V_0,V_1,\ldots$ in which every vertex of $V_n$
with $n\ge1$ has a neighbour in $V_{n-1}$ and produces an infinite ray; the
reference below states it in that form. Here $V_n=\mathsf P_n(v)$ and the
neighbour of a path is its length-$(n-1)$ prefix, so finiteness of each $V_n$ is
the finite-outdegree hypothesis of section 5, and the infinitely branching
example of section 2 violates it by having an infinite level.

The prefix topology of section 7 and the character space computed in section 8
admit a comparison with S. B. G. Webster, *The path space of a directed graph*,
Proceedings of the American Mathematical Society 142 (2014), 213-225,
arXiv:1102.1225, who equips the boundary-path space of an arbitrary directed
graph with a locally compact Hausdorff topology having a basis of compact open
cylinder sets and identifies that space with the Gelfand spectrum of the
diagonal subalgebra. His boundary-path space consists of the infinite paths
together with the finite paths whose terminal vertex is singular. The
semilattice $\{\Pi_p:p\in\mathsf P(G)\}$ of section 8 is indexed by every finite
path, and every prefix chain with a maximal element yields a character, so the
spectrum computed there is $\mathsf P(G)\sqcup\partial^+G$ and retains all
finite paths. Webster's theorem is therefore a comparison for that computation
and not its source; the two spaces contain the same infinite paths, and they
differ on the finite paths, among which section 10 isolates those whose terminal
node emits finitely many edges.

Reference:

- R. Diestel, *Graph Theory*, sixth edition, Graduate Texts in Mathematics 173,
  Springer, 2025, Lemma 8.1.2.
