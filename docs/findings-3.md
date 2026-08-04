# 1. Infinite-system structure

Let

```math
G=(V,E,s,r)
```

be a representative quiver of a bounded system. Here $V$ and $E$ are sets, and

```math
s,r:E\to V
```

are the source and range maps. Describing the system as a quiver, rather than
as a subset of $V\times V$, retains the parallel channels allowed by the
definition.

## Unrestricted cardinality

Strict endogeneity imposes no finiteness condition. The definition therefore
permits

```math
|V|=n,\qquad |V|=\aleph_0,
\qquad\text{or an uncountable cardinal.}
```

The constructions apply at each of these cardinalities.

## Reachability as a strict partial order

Define

```math
u\prec v
```

when a positive-length finite directed path runs from $u$ to $v$. Acyclicity
makes this relation irreflexive, and path concatenation makes it transitive. The
direct edge relation may fail to be transitive because a shortcut edge can
coexist with a longer path having the same endpoints.

## Information lost under passage to reachability

Several distinct paths may connect the same ordered pair,

```math
u\longrightarrow v.
```

Replacing all such paths by the single relation $u\prec v$ discards
primitive-edge and route multiplicities, path lengths, intermediate-node data,
and the distinction between parallel channels. The reachability poset is
therefore a quotient of the communication structure rather than a complete
representation of it.

## Infinite chains and local finiteness

Acyclicity permits an infinite chain while forbidding directed cycles,

```math
v_0\to v_1\to v_2\to\cdots.
```

An acyclic quiver can therefore have infinite height, lack both sources and
sinks, and fail to be well founded, bounded degree, or locally finite.

## Path length as compositional depth

For a path $p$, the length

```math
|p|=k
```

records the number of primitive channels in the composition. It measures
compositional depth independently of any external time parameter. The
definition also permits mutually noncommunicating components, so a strictly
endogenous system may be disconnected.

# 2. The path category

Let

```math
\mathsf P(G)
```

denote the free path category of $G$. Its objects are the nodes $v\in V$, its
generating morphisms are the edges $e\in E$, and its morphisms are finite
directed paths. The identity at $v$ is the length-zero path $1_v$, and
composition is path concatenation.

Acyclicity implies

```math
\mathrm{End}_{\mathsf P(G)}(v)=\{1_v\}.
```

There are no nonidentity endomorphisms because any positive-length path from
$v$ back to $v$ would be a directed cycle.

Distinct edge sequences remain distinct morphisms in the free path category. Any
additional identification of paths would introduce structure not contained in
the definition of a bounded system.

# 3. The algebraic path algebra

Over the scalar field $\mathbb C$, define

```math
\mathbb C[G]=
\mathbb C^{(\mathsf P(G))},
```

the vector space of finite formal linear combinations of finite paths.

For basis paths $p,q$, define

```math
[q][p]=
\begin{cases}
[q\circ p],&p\text{ and }q\text{ are composable},\\
0,&\text{otherwise}.
\end{cases}
```

Finite linear combinations of paths with this product form an associative,
generally noncommutative path algebra.

Let

```math
e_v=[1_v].
```

Then

```math
e_v^2=e_v,
\qquad
e_ue_v=0\quad(u\ne v).
```

These relations encode the orthogonality of distinct nodes.

For an edge $a:u\to v$,

```math
e_v a e_u=a.
```

By contrast,

```math
e_u a=0,
\qquad
a e_v=0,
```

because $u\ne v$ in an acyclic system.

Consequently, every channel $a:u\to v$ satisfies

```math
[e_v,a]=a,
\qquad
[e_u,a]=-a.
```

Thus any graph with a nonzero channel has a noncommutative path algebra.

# 4. The marked node diagonal

Define

```math
\mathcal D_0=
\bigoplus_{v\in V}\mathbb C e_v.
```

This degree-zero subalgebra is the distinguished node diagonal. It must remain
marked as part of the algebraic object:

```math
\bigl(\mathbb C[G],\mathcal D_0\bigr).
```

Without the marked diagonal, an abstract algebra can have additional
idempotents that are not nodes. Arbitrary orthogonal or unitary changes of
basis may preserve operator information while destroying the distinguished node
decomposition.

Marking the diagonal removes the orthogonal-similarity ambiguity encountered in
the finite matrix analysis. An equivalence must preserve the diagonal as a
subalgebra, although it may permute its primitive idempotents because the node
labels are not intrinsic.

When $V$ is infinite, $\mathbb C[G]$ generally has no algebraic identity, since
the formal sum

```math
\sum_{v\in V}e_v
```

is not finitely supported. It does have local units. Every finite collection of
algebra elements is supported on finitely many nodes, so some finite sum

```math
e_F=\sum_{v\in F}e_v
```

acts as an identity on that collection. The absence of a global algebraic unit
is therefore unrelated to the requirement of strict endogeneity.

# 5. The positive-path ideal and local nilpotence

Let

```math
J=\mathrm{span}\{p:|p|\ge1\}.
```

Then

```math
\mathbb C[G]=
\mathcal D_0\oplus J
```

as vector spaces.

More generally, the algebra is graded by path length:

```math
\mathbb C[G]=
\bigoplus_{n=0}^{\infty}\mathcal A_n,
```

where

```math
\mathcal A_n=
\mathrm{span}\{p:|p|=n\}.
```

Multiplication respects the grading:

```math
\mathcal A_m\mathcal A_n
\subseteq
\mathcal A_{m+n}.
```

Moreover,

```math
J^n=
\mathrm{span}\{p:|p|\ge n\}.
```

## Local nilpotence

If $G$ is acyclic, then $J$ is locally nilpotent. Indeed, finitely many elements
of $J$ involve only finitely many paths and hence only finitely many vertices. A
sufficiently long nonzero product would contain a path that repeats a vertex,
producing a directed cycle. All sufficiently long products therefore vanish. In
particular, every algebraic element $x\in J$ is nilpotent.

However, $J$ need not be globally nilpotent.

More precisely,

```math
J^{h+1}=0
\iff
\text{there is no directed path longer than }h.
```

Finite-height systems therefore have a nilpotent positive-path ideal. If paths
of arbitrarily large finite length occur, then $J^n\ne0$ for every $n$,
although each finitely supported positive-path process remains nilpotent. None
of these statements depends on the cardinality of the node set.

# 6. Recovery from the marked graded algebra

The marked grading and node diagonal retain the primitive graph structure. For
nodes $u,v$, the corner

```math
e_v\mathcal A_n e_u
```

is the vector space spanned by length-$n$ paths from $u$ to $v$. In particular,
reachability is recovered from

```math
u\prec v
\iff
e_vJe_u\ne0,
```

and the number of length-$n$ paths is given by

```math
\dim\left(e_v\mathcal A_n e_u\right)=
\left|\{\text{length-}n\text{ paths } u \to v\}\right|.
```

The dimension may be any cardinal. Composite paths lie in $J^2$, so the quotient
$J/J^2$ is precisely the primitive-edge space. For each pair $u,v$,

```math
\dim\left(
e_v(J/J^2)e_u
\right)=
\left|\{\text{primitive edges }u\to v\}\right|.
```

The quotient therefore preserves parallel channels. Hence the marked graded
algebra

```math
\left(\mathbb C[G],\mathcal D_0,\{\mathcal A_n\}_{n\ge0}\right)
```

recovers the nodes, primitive channels, parallel-channel multiplicities, all
finite paths and their lengths, the reachability relation, and acyclicity. This
recovery does not require the cardinality of $V$ to be fixed in advance.

# 7. The Fock-space representation

Let

```math
\mathcal H_G=
\ell^2(\mathsf P(G)),
```

with orthonormal basis

```math
\{\xi_p:p\in\mathsf P(G)\}.
```

This Hilbert space is well defined even when the path set is uncountable, since
every vector in an $\ell^2$ space has countable support.

For each node $v$, let $P_v$ project onto paths whose terminal node is $v$.

For each edge $e$, define left path creation:

```math
L_e\xi_p=
\begin{cases}
\xi_{ep},&s(e)=r(p),\\
0,&\text{otherwise}.
\end{cases}
```

The resulting operators satisfy

```math
P_uP_v=0\quad(u\ne v),
\qquad
L_e^\ast L_e=P_{s(e)},
\qquad
L_eL_e^\ast\le P_{r(e)},
```

and, for distinct primitive channels,

```math
L_e^\ast L_f=0
\quad(e\ne f).
```

Parallel channels remain orthogonal because they create different path basis
vectors.

Also,

```math
P_{r(e)}L_eP_{s(e)}=L_e.
```

For a path $p=e_n\cdots e_1$,

```math
L_p=L_{e_n}\cdots L_{e_1}.
```

For countable graphs, the Fock-space construction leads to free semigroupoid
algebras, for which the directed graph is a complete unitary invariant. The
formulas above apply to arbitrary cardinality, but the extension of the
countable classification theory to nonseparable Fock spaces is a separate
question.

# 8. One-sided composition in acyclic systems

If nonempty paths $p$ and $q$ satisfy

```math
L_qL_p\ne0,
```

then $p$ can be followed by $q$.

In an acyclic graph, the reverse composition cannot also exist:

```math
L_qL_p\ne0
\implies
L_pL_q=0.
```

If both products were nonzero, their source-target conditions would form a
directed closed path.

Thus an allowed composition in one order excludes the reversed composition. This
one-sided multiplication is a direct operator-algebraic consequence of
orientation and acyclicity.

# 9. Aggregate creation operators

The construction does not assume that a global adjacency operator is bounded.
The individual channel operators $L_e$ are always defined, and for coefficients
$c_e$ one may consider the formal sum

```math
T_c=\sum_{e\in E}c_eL_e.
```

Because distinct $L_e$ have orthogonal ranges,

```math
T_c^\ast T_c=
\sum_{v\in V}
\left(
\sum_{s(e)=v}|c_e|^2
\right)P_v.
```

The sum defines a bounded operator precisely when

```math
\sup_{v\in V}
\sum_{s(e)=v}|c_e|^2
<\infty.
```

In that case,

```math
\lVert T_c\rVert=
\sup_{v\in V}
\left(
\sum_{s(e)=v}|c_e|^2
\right)^{1/2}.
```

For the unweighted choice $c_e=1$, this becomes

```math
\lVert T\rVert=\sqrt{\sup_v\deg^+(v)}.
```

An unweighted global creator is bounded exactly when outgoing degree is
uniformly bounded.

A corresponding right-creation aggregate is bounded exactly when incoming degree
is uniformly bounded.

# 10. Spectral effects of completion

Every finitely supported element of $J$ is nilpotent and therefore has spectrum
$\{0\}$. An operator completion, however, may contain limits with nonzero
spectral radius.

Consider the infinite chain

```math
0\to1\to2\to3\to\cdots.
```

The global operator

```math
T=\sum_{n\ge0}L_{e_n}
```

is bounded with $\lVert T\rVert=1$. On each fixed-start path sector it acts as
a unilateral shift, and hence

```math
\sigma(T)=\{z\in\mathbb C:|z|\le1\}.
```

Every finite partial sum is nilpotent with spectrum $\{0\}$, whereas the strong
limit has the closed unit disk as its spectrum. Nonzero spectral structure may
therefore arise after operator-topology completion even though every algebraic
finite process is nilpotent. In particular, the spectra of finite truncations do
not determine the completed infinite operator.

# 11. A marked nonselfadjoint invariant

A natural primary invariant is the marked nonselfadjoint operator algebra

```math
\mathbf B(G)=
\left(
\mathcal A_G,
\mathcal D_G,
\gamma
\right).
```

In this triple, $\mathcal A_G$ is generated by the vertex projections $P_v$ and
edge creators $L_e$, $\mathcal D_G$ is the distinguished node diagonal, and
$\gamma$ is the path-length grading, equivalently the gauge action,

```math
\gamma_z(L_p)=z^{|p|}L_p,
\qquad
\gamma_z(P_v)=P_v.
```

This marked algebra records node orthogonality, source and target corners,
noncommutative composition, the distinction between primitive and composite
channels, all finite paths, operator norms, spectra of canonical elements, and
effects introduced by completion.

The norm-closed version is closely related to the directed graph tensor algebra;
in the countable case, its $C^\ast$-envelope is the graph's universal
Cuntz-Krieger algebra.

The nonselfadjoint algebra remains primary because the adjoints $L_e^\ast$ are
Hilbert-space operators used to remove path prefixes; they do not represent
reverse communication channels.

# 12. Literature relation

The Fock representation of section 7, and the statement quoted there that the
directed graph is a complete unitary invariant of the algebra it generates, are
the subject of D. W. Kribs and S. C. Power, *Free semigroupoid algebras*,
Journal of the Ramanujan Mathematical Society 19 (2004), 117-159,
arXiv:math/0309394, where the graph is assumed countable and the Fock space is
consequently separable. The relations among the operators $P_v$ and $L_e$ used
in sections 7 to 9 are verified directly from the definitions and hold at
arbitrary cardinality, whereas the unitary-invariant statement is quoted only in
the countable case; a nonseparable $\mathcal H_G$ falls outside the hypothesis
of that paper.

The norm-closed algebra named in section 11 is the tensor algebra of the
$C^\ast$-correspondence attached to the graph, in the sense of P. S. Muhly and
B. Solel, *Tensor algebras over $C^\ast$-correspondences: representations,
dilations, and $C^\ast$-envelopes*, Journal of Functional Analysis 158 (1998),
389-457, where the tensor algebra of a correspondence over a $C^\ast$-algebra is
characterized as universal for completely contractive covariant representations
of that correspondence. Their hypotheses concern the correspondence and its
coefficient algebra and mention no graph. The identification of the
$C^\ast$-envelope with the universal Cuntz-Krieger algebra of the graph, quoted
at the end of section 11, is proved in E. G. Katsoulis and D. W. Kribs, *The
$C^\ast$-envelope of the tensor algebra of a directed graph*, Integral Equations
and Operator Theory 56 (2006), 401-414, arXiv:math/0411417, for an arbitrary
countable graph, and the restriction to the countable case in section 11 is
exactly that hypothesis.
