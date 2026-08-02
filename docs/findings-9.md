# 1. Past rank

Acyclicity alone does not guarantee finite height. When one directional boundary
is empty, however, the corresponding reachability relation admits a canonical
ordinal rank. Write $u\prec v$ when a positive-length directed path runs from
$u$ to $v$. The past and future directions give two independent rank theories.

For the past rank, suppose there is no infinite backward chain

```math
\cdots\to v_2\to v_1\to v_0.
```

Equivalently, the predecessor relation is well-founded.

Define the past rank

```math
\rho_-(v)=
\sup{\rho_-(u)+1:u\to v}.
```

For a source, the predecessor set is empty, so

```math
\rho_-(v)=0.
```

Every edge strictly increases past rank:

```math
u\to v
\quad\Longrightarrow\quad
\rho_-(u)<\rho_-(v).
```

More strongly, a path of length $n$ from $u$ to $v$ gives

```math
\rho_-(v)\ge \rho_-(u)+n.
```

The map $\rho_-$ therefore assigns ordinals so that every channel strictly
increases rank.

## Theorem 1. Existence of past rank

In ordinary set theory the following conditions are equivalent:

1. every node has a past rank;
2. every nonempty set of nodes has a $\prec$-minimal element;
3. there is no infinite backward path.

The equivalence of the first two conditions uses no choice principle. The
implication from the third consumes the principle of dependent choices.

```math
\partial^-G=\varnothing
\iff
\rho_-\text{ is defined on all nodes}.
```

# 2. Future rank

Dually, suppose there is no infinite forward path

```math
v_0\to v_1\to v_2\to\cdots.
```

Define the future rank

```math
\rho_+(v)=
\sup{\rho_+(w)+1:v\to w}.
```

Sinks have rank zero:

```math
\rho_+(v)=0.
```

Every edge strictly decreases future rank:

```math
u\to v
\quad\Longrightarrow\quad
\rho_+(u)>\rho_+(v).
```

For a path of length $n$,

```math
\rho_+(u)\ge \rho_+(v)+n.
```

## Theorem 2. Existence of future rank

Under the same set-theoretic assumptions, the following conditions are
equivalent:

1. every node has a future rank;
2. every nonempty set of nodes has a $\prec$-maximal element;
3. there is no infinite forward path.

```math
\partial^+G=\varnothing
\iff
\rho_+\text{ is defined on all nodes}.
```

The conditions are independent: a system can have a future rank but no past
rank, or vice versa.

# 3. Transfinite rank does not mean an infinitely long path

Consider a root with one outgoing finite branch of every possible finite length:

```math
r\to \text{branch of length }1,
\qquad
r\to \text{branch of length }2,
\qquad\ldots
```

Every actual path from $r$ is finite, but

```math
\rho_+(r)=\omega.
```

The rank is a limit ordinal because the possible finite depths are unbounded:

```math
\rho_+(r)=
\sup_{n<\omega}n=
\omega.
```

Now add a node $s\to r$. Then

```math
\rho_+(s)=\omega+1.
```

Arbitrarily large transfinite ranks can occur without any infinite forward path.
For an ordinal $\alpha$, take nodes indexed by ordinals

```math
0,1,\ldots,\alpha
```

and direct a channel

```math
\gamma\to\beta
\qquad\text{whenever }\beta<\gamma.
```

Ordinals admit no infinite strictly decreasing sequence, so every forward path
is finite, while

```math
\rho_+(\gamma)=\gamma.
```

Ordinal rank therefore measures recursive branching complexity rather than the
length of a single path.

# 4. Transfinite pruning

The ranks can be constructed without initially assuming that the boundary is
empty.

## Sink pruning

Set

```math
W^+_0=V.
```

At every successor stage, remove all sinks in the currently remaining subgraph:

```math
W^+_{\alpha+1}=
\left\lbrace v\in W^+_\alpha: \exists\, w\text{ such that }v\to w\text{ with }w\in W^+_\alpha \right\rbrace.
```

At a limit ordinal $\lambda$, define

```math
W^+_\lambda=
\bigcap_{\beta<\lambda}W^+_\beta.
```

A node removed at stage $\alpha+1$,

```math
v\in W^+_\alpha\setminus W^+_{\alpha+1},
```

has

```math
\rho_+(v)=\alpha.
```

The forward core is

```math
K^+=
\bigcap_\alpha W^+_\alpha.
```

## Source pruning

Similarly, source pruning begins with $W^-_0=V$ and proceeds at successor
stages by

```math
W^-_{\alpha+1}=
\left\lbrace v\in W^-_\alpha: \exists\, u\text{ such that }u\to v\text{ with }u\in W^-_\alpha \right\rbrace.
```

At limit ordinals,

```math
W^-_\lambda=
\bigcap_{\beta<\lambda}W^-_\beta.
```

A node removed at stage $\alpha+1$ has past rank $\alpha$.

The backward core is

```math
K^-=\bigcap_\alpha W^-_\alpha.
```

# 5. The boundary-core theorem

The transfinite pruning process exactly detects genuine infinite paths.

## Theorem 3. Boundary-core characterization

For every node $v$,

```math
v\in K^+
\iff
\text{an infinite forward path begins at }v.
```

Likewise,

```math
v\in K^-
\iff
\text{an infinite backward path ends at }v.
```

## Proof

If an infinite path begins at $v$, none of its nodes is ever removed as a sink.
Transfinite induction shows that every path node remains in every
$W^+_\alpha$, so $v\in K^+$.

Conversely, suppose $v\in K^+$.

Assume every successor $w$ of $v$ is eventually removed. Let $\alpha_w$ be a
stage after which $w$ is absent. Since the successor set is a set, the ordinal

```math
\beta=\sup_{v\to w}(\alpha_w+1)
```

exists.

At stage $\beta$, none of $v$'s successors remains. Therefore $v$ becomes a
sink and is removed at stage $\beta+1$, contradicting $v\in K^+$.

Thus $v$ has a successor in $K^+$. Repeating this choice gives an infinite path.

Transfinite pruning therefore corrects the weakness of finite-depth tests. The
root of the infinitely branching finite tree survives every finite pruning stage
but is removed at stage $\omega+1$, whereas the root of an actual infinite path
survives every ordinal stage. Thus finite-stage survival is insufficient for
boundary membership; membership in $K^+$ is equivalent to survival through every
ordinal stage.

# 6. Rank layers

Define the cumulative past-rank sets

```math
V^-_{<\alpha}=
\{v:\rho_-(v)<\alpha\},
```

and layers

```math
L^-_\alpha=
\{v:\rho_-(v)=\alpha\}.
```

Similarly, define

```math
V^+_{<\alpha}=
\{v:\rho_+(v)<\alpha\},
\qquad
L^+_\alpha=
\{v:\rho_+(v)=\alpha\}.
```

Every layer is an antichain.

Indeed, if $u\prec v$, then

```math
\rho_-(u)<\rho_-(v)
```

and, when future ranks exist,

```math
\rho_+(u)>\rho_+(v).
```

Two comparable nodes cannot have the same rank.

Edges may skip ordinal layers. Nothing requires

```math
\rho_-(v)=\rho_-(u)+1
```

for an edge $u\to v$. The edge only guarantees

```math
\rho_-(v)\ge \rho_-(u)+1.
```

# 7. Global ordinal height

When every node has a past rank, define

```math
\mathrm{ht}_-(G)=
\sup_{v\in V}\bigl(\rho_-(v)+1\bigr).
```

When every node has a future rank, define

```math
\mathrm{ht}_+(G)=
\sup_{v\in V}\bigl(\rho_+(v)+1\bigr).
```

These are ordinal heights, not node counts and not maximum finite path lengths.

For a system with $|V|=\kappa$,

```math
\mathrm{ht}_\pm(G)<\kappa^+.
```

The pruning sequence must stabilize before $\kappa^+$ because each nonstationary
successor stage removes at least one remaining node.

In a finite DAG, these ranks reduce to familiar longest-path depths.

In an infinite system, they can be arbitrary set-sized ordinals.

# 8. Algebraic extraction from primitive channels

Recall

```math
J=[\mathcal A,\mathcal A]
```

and define the primitive-channel bimodule

```math
\mathcal M=J/J^2.
```

For nodes $u,v$,

```math
e_v\mathcal M e_u
```

is the vector space of primitive channels from $u$ to $v$.

Pass to the completed diagonal

```math
\widehat{\mathcal D}=
\prod_{v\in V}\mathbb C e_v,
```

where arbitrary sums of node projections exist.

## Past-rank projections

Let

```math
F^-_0=0.
```

Recursively define

```math
F^-_{\alpha+1}=
\bigvee
\left\lbrace e_v: e_v\mathcal M(1-F^-_\alpha)=0 \right\rbrace.
```

At a limit ordinal,

```math
F^-_\lambda=
\bigvee_{\beta<\lambda}F^-_\beta.
```

The condition

```math
e_v\mathcal M(1-F^-_\alpha)=0
```

says that every immediate predecessor of $v$ has already entered the lower-rank
part. The recursion therefore yields

```math
F^-_\alpha=
\sum_{\rho_-(v)<\alpha}e_v.
```

The layer projection is

```math
\Delta^-_\alpha=
F^-_{\alpha+1}-F^-_\alpha=
\sum_{\rho_-(v)=\alpha}e_v.
```

## Future-rank projections

Similarly, set $F^+_0=0$ and define successor stages by

```math
F^+_{\alpha+1}=
\bigvee
\left\lbrace e_v: (1-F^+_\alpha)\mathcal M e_v=0 \right\rbrace.
```

At limit ordinals,

```math
F^+_\lambda=
\bigvee_{\beta<\lambda}F^+_\beta.
```

The condition

```math
(1-F^+_\alpha)\mathcal M e_v=0
```

says that every immediate successor of $v$ has already entered the lower
future-rank part. Consequently,

```math
F^+_\alpha=
\sum_{\rho_+(v)<\alpha}e_v.
```

Hence the transfinite ranks are intrinsic to $(\mathcal A,\mathcal D)$ and
require neither node labels nor an externally supplied ordering.

# 9. Triangular operator structure

The past-rank initial segment

```math
V^-_{<\alpha}
```

is predecessor-closed. No path can begin outside it and terminate inside it.

```math
F^-_\alpha\mathcal A(1-F^-_\alpha)=0.
```

Relative to

```math
\mathcal H=
F^-_\alpha\mathcal H
\oplus
(1-F^-_\alpha)\mathcal H,
```

every path operator has block form

```math
\begin{pmatrix}
\ast&0\\
\ast&\ast
\end{pmatrix}.
```

The high-rank complement is invariant, while the low-rank part is coinvariant.

Dually, future-rank initial segments are successor-closed:

```math
(1-F^+_\alpha)\mathcal A F^+_\alpha=0.
```

Their block form is

```math
\begin{pmatrix}
\ast&\ast\\
0&\ast
\end{pmatrix}.
```

The ordinal ranks thus determine canonical past- and future-rank projection
nests. Their opposite triangular forms encode the direction of communication.

# 10. Canonical rank truncations

For past rank, define

```math
I^-_\alpha=
\mathrm{span}
\left\lbrace p: r(p)\notin V^-_{<\alpha} \right\rbrace.
```

These are paths whose terminal node has past rank at least $\alpha$, or belongs
to the backward core.

Because high past-rank nodes are forward-closed,

```math
I^-_\alpha
```

is a two-sided ideal.

The quotient is

```math
\mathcal A/I^-_\alpha
\cong
\mathcal A\!\left(G[V^-_{<\alpha}]\right).
```

Equivalently, compression gives

```math
a\mapsto F^-_\alpha aF^-_\alpha.
```

The triangular relation ensures this compression is an algebra homomorphism.

For future rank, define

```math
I^+_\alpha=
\mathrm{span}
\left\lbrace p: s(p)\notin V^+_{<\alpha} \right\rbrace.
```

Then

```math
\mathcal A/I^+_\alpha
\cong
\mathcal A\!\left(G[V^+_{<\alpha}]\right).
```

These ordinal quotients provide canonical finite or transfinite approximations
to the full system. Unlike truncation by node count, rank truncation respects
the direction of communication and the associated ancestry relation.

# 11. When both ranks exist

If both boundaries are empty, every node receives a pair

```math
\bigl(\rho_-(v),\rho_+(v)\bigr).
```

For an edge $u\to v$,

```math
\rho_-(u)<\rho_-(v),
```

while

```math
\rho_+(u)>\rho_+(v).
```

Communication moves upward in past rank and downward in future rank.

For a path of length $n$, the two ranks satisfy

```math
\rho_-(v)\ge\rho_-(u)+n,
\qquad
\rho_+(u)\ge\rho_+(v)+n.
```

The intersections

```math
C_{\alpha,\beta}=
\{v:\rho_-(v)=\alpha,\ \rho_+(v)=\beta\}
```

are antichains.

The pair of ranks gives a canonical two-dimensional ordinal coordinate system
without labeling individual nodes.

The coordinate need not distinguish nodes: those in the same cell remain
intrinsically indistinguishable unless their channel relations differ.

# 12. Ordinal ranks and numeric operators

A numerical rank operator would be defined by

```math
R=\sum_v\rho(v)P_v.
```

Ordinal values are not ordinary real or complex scalars; arbitrary ordinals have
no canonical order-preserving embedding into $\mathbb R$.

Turning transfinite ranks into real numbers would therefore require an
arbitrary coding.

The canonical analytic object is therefore the ordinal-indexed projection family

```math
{F_\alpha}_{\alpha},
```

or equivalently the family of layer projections

```math
{\Delta_\alpha}_{\alpha},
```

rather than a single self-adjoint rank operator.

These projection nests retain the complete ordinal ordering without numerical
distortion.

# 13. Combined finite and infinite decomposition

Every node belongs either to a well-founded past layer $L^-_\alpha$ or to the
backward boundary core $K^-$. Independently, it belongs either to a
well-founded future layer $L^+_\beta$ or to the forward boundary core $K^+$.

Thus the node set decomposes into four broad sectors:

```math
V=
(V_{\mathrm{wf}}^-\cap V_{\mathrm{wf}}^+)
\sqcup
(V_{\mathrm{wf}}^-\cap K^+)
\sqcup
(K^-\cap V_{\mathrm{wf}}^+)
\sqcup
(K^-\cap K^+).
```

The four summands represent, respectively, nodes that are well-founded in both
directions, well-founded only toward the past, well-founded only toward the
future, and contained in both infinite cores.

The last sector contains all nodes on bi-infinite chains but can also contain
nodes connected to separate backward and forward infinite branches that do not
form a unique bi-infinite route.

# 14. Literature relation

The source-pruning stages of section 4, restricted to a finite system, and the
finite reduction of the ranks noted in section 7 correspond to the procedure of
A. B. Kahn, *Topological sorting of large networks*, Communications of the ACM 5
(1962), 558-562, which orders a finite network consistently with its edges by
repeatedly removing nodes that have no remaining predecessor. Kahn supplies an
algorithm for the finite case rather than an existence statement about ordinal
ranks: the loop halts because each round deletes at least one node, and the
output is a linear order on the nodes. Sections 4 and 5 keep the successor
stages of that removal but add limit stages
$W^+_\lambda=\bigcap_{\beta<\lambda}W^+_\beta$ and the fixed point $K^+$, which
have no counterpart in a finite run; the infinitely branching tree of section 3
survives every finite stage and is removed only at stage $\omega+1$.
