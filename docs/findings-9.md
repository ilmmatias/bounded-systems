# Transfinite rank and height

Acyclicity alone does not guarantee finite height. But when one directional boundary is empty, the corresponding reachability relation admits a canonical ordinal rank.

Let

```math
u\prec v
```

mean that a positive-length directed path runs from $u$ to $v$.

There are two independent rank theories.

# 1. Past rank

Suppose there is no infinite backward chain

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

Thus $\rho_-$ is a canonical transfinite topological ordering.

## Existence theorem

Under ordinary set theory with dependent choice, the following are equivalent:

1. every node has a past rank;
2. every nonempty set of nodes has a $\prec$-minimal element;
3. there is no infinite backward path.

Hence:

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

The equivalent conditions are:

1. every node has a future rank;
2. every nonempty set of nodes has a $\prec$-maximal element;
3. there is no infinite forward path.

Therefore:

```math
\partial^+G=\varnothing
\iff
\rho_+\text{ is defined on all nodes}.
```

The conditions are independent: a system can have a future rank but no past rank, or vice versa.

# 3. Transfinite rank does not mean an infinitely long path

Consider a root with one outgoing finite branch of every possible finite length:

```math
r\to \text{branch of length }1,
```

```math
r\to \text{branch of length }2,
```

and so forth.

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

Arbitrarily large transfinite ranks can occur without any infinite forward path. For an ordinal $\alpha$, take nodes indexed by ordinals

```math
0,1,\ldots,\alpha
```

and direct a channel

```math
\gamma\to\beta
\qquad\text{whenever }\beta<\gamma.
```

Ordinals admit no infinite strictly decreasing sequence, so every forward path is finite, while

```math
\rho_+(\gamma)=\gamma.
```

Thus:

```math
\text{ordinal rank measures recursive branching complexity, not one path's length}.
```

# 4. Transfinite pruning

The ranks can be constructed without initially assuming that the boundary is empty.

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

Similarly,

```math
W^-_0=V,
```

```math
W^-_{\alpha+1}=
\left\lbrace v\in W^-_\alpha: \exists\, u\text{ such that }u\to v\text{ with }u\in W^-_\alpha \right\rbrace,
```

and at limits,

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

## Theorem

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

## Proof in the forward direction

If an infinite path begins at $v$, none of its nodes is ever removed as a sink. Transfinite induction shows that every path node remains in every $W^+_\alpha$, so $v\in K^+$.

Conversely, suppose $v\in K^+$.

Assume every successor $w$ of $v$ is eventually removed. Let $\alpha_w$ be a stage after which $w$ is absent. Since the successor set is a set, the ordinal

```math
\beta=\sup_{v\to w}(\alpha_w+1)
```

exists.

At stage $\beta$, none of $v$'s successors remains. Therefore $v$ becomes a sink and is removed at stage $\beta+1$, contradicting $v\in K^+$.

Thus $v$ has a successor in $K^+$. Repeating this choice gives an infinite path.

So transfinite pruning fixes precisely the weakness of finite-depth tests:

* the infinitely branching finite-tree root survives every finite pruning stage;
* but it is removed at stage $\omega+1$;
* an actual infinite-path root survives every ordinal stage.

Therefore:

```math
\text{finite-stage survival}
\neq
\text{boundary membership},
```

but

```math
\text{survival through all ordinal stages}=
\text{boundary membership}.
```

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

Similarly,

```math
V^+_{<\alpha}=
\{v:\rho_+(v)<\alpha\},
```

```math
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

So two comparable nodes cannot have the same rank.

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

The pruning sequence must stabilize before $\kappa^+$ because each nonstationary successor stage removes at least one remaining node.

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

says that every immediate predecessor of $v$ has already entered the lower-rank part.

Therefore:

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

Similarly,

```math
F^+_0=0,
```

```math
F^+_{\alpha+1}=
\bigvee
\left\lbrace e_v: (1-F^+_\alpha)\mathcal M e_v=0 \right\rbrace,
```

and

```math
F^+_\lambda=
\bigvee_{\beta<\lambda}F^+_\beta.
```

Here

```math
(1-F^+_\alpha)\mathcal M e_v=0
```

says every immediate successor of $v$ has already entered the lower future-rank part.

Thus

```math
F^+_\alpha=
\sum_{\rho_+(v)<\alpha}e_v.
```

Consequently,

```math
\text{transfinite ranks are intrinsic to }(\mathcal A,\mathcal D).
```

They require neither labels nor an externally supplied ordering.

# 9. Triangular operator structure

The past-rank initial segment

```math
V^-_{<\alpha}
```

is predecessor-closed. No path can begin outside it and terminate inside it.

Therefore:

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

Thus the ordinal ranks yield two canonical projection nests:

* a past-rank nest;
* a future-rank nest.

They encode direction through opposite triangularities.

# 10. Canonical rank truncations

For past rank, define

```math
I^-_\alpha=
\mathrm{span}
\left\lbrace p: r(p)\notin V^-_{<\alpha} \right\rbrace.
```

These are paths whose terminal node has past rank at least $\alpha$, or belongs to the backward core.

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

These ordinal quotients provide canonical finite-or-transfinite approximations to the full system.

They differ fundamentally from approximating by node count:

```math
\text{rank truncation respects communication direction and causal ancestry}.
```

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

So communication moves:

* upward in past rank;
* downward in future rank.

For a path of length $n$,

```math
\rho_-(v)\ge\rho_-(u)+n,
```

```math
\rho_+(u)\ge\rho_+(v)+n.
```

The intersections

```math
C_{\alpha,\beta}=
\{v:\rho_-(v)=\alpha,\ \rho_+(v)=\beta\}
```

are antichains.

This gives a canonical two-dimensional ordinal coordinate system without assigning labels to individual nodes.

The coordinate need not distinguish nodes: those in the same cell remain intrinsically indistinguishable unless their channel relations differ.

# 12. Why there is no canonical numeric rank operator

It may be tempting to define

```math
R=\sum_v\rho(v)P_v.
```

Ordinal values are not ordinary real or complex scalars; arbitrary ordinals have no canonical order-preserving embedding into $\mathbb R$.

Turning transfinite ranks into real numbers would therefore require an arbitrary coding.

The canonical analytic object is an ordinal-indexed projection family, not one self-adjoint rank operator.

```math
{F_\alpha}_{\alpha}
```

or equivalently the layer projections

```math
{\Delta_\alpha}_{\alpha}.
```

These projection nests retain the complete ordinal ordering without numerical distortion.

# 13. Combined finite and infinite decomposition

Every node belongs to exactly one of the following:

1. a well-founded past layer $L^-_\alpha$;
2. the backward boundary core $K^-$;

and independently:

1. a well-founded future layer $L^+_\beta$;
2. the forward boundary core $K^+$.

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

They represent:

* finite in both directional senses;
* finite past but infinite future;
* infinite past but finite future;
* infinite in both directions.

The last sector contains all nodes on bi-infinite chains but can also contain nodes connected to separate backward and forward infinite branches that do not form a unique bi-infinite route.
