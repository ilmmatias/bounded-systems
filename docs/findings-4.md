# 1. The graded path algebra

Let

```math
G=(V,E,s,r)
```

be a set-sized directed multigraph. A representative of a bounded system is
acyclic, although the constructions below do not require acyclicity unless
stated explicitly. Parallel channels are allowed because the pair of maps
$s,r:E\to V$ need not be jointly injective.

Over a field $\mathbb K$, usually $\mathbb C$, define the algebraic path algebra

```math
\mathcal A(G)=\mathbb K G=
\bigoplus_{n\ge 0}\mathcal A_n(G),
```

where $\mathcal A_n(G)$ has as a basis all directed paths of length $n$.

The degree-zero component is

```math
\mathcal D(G)=\mathcal A_0(G)=
\bigoplus_{v\in V}\mathbb K e_v,
```

with

```math
e_v^2=e_v,
\qquad
e_ue_v=0\quad(u\ne v).
```

For a channel $a:u\to v$,

```math
e_v a e_u=a.
```

The grading satisfies

```math
\mathcal A_m\mathcal A_n
\subseteq
\mathcal A_{m+n}.
```

These definitions do not require $V$ or $E$ to be finite or countable.

# 2. Reconstruction from the marked grading

## Theorem 1. Weak reconstruction

Let $G$ and $H$ be two set-sized directed multigraphs. Suppose there is an
algebra isomorphism

```math
\Phi:\mathcal A(G)\longrightarrow\mathcal A(H)
```

such that

```math
\Phi(\mathcal D(G))=\mathcal D(H)
```

and

```math
\Phi(\mathcal A_n(G))=\mathcal A_n(H)
\qquad(n\ge0).
```

Then $G$ and $H$ are isomorphic as directed multigraphs.

The statement allows arbitrary node and edge cardinalities, including parallel
channels, and applies to both finite and infinite multigraphs. Acyclicity is
not required for the reconstruction argument.

## Proof

The two hypotheses on $\Phi$ are used separately: preservation of the marked
diagonal recovers the node set, and preservation of degree one recovers the
channel multiplicities.

### Recovery of the nodes

An idempotent of $\mathcal D(G)$ has the form

```math
p=\sum_{v\in F}\lambda_v e_v
```

for some finite $F\subseteq V$.

The condition $p^2=p$ forces

```math
\lambda_v\in\{0,1\}.
```

The nonzero primitive idempotents of $\mathcal D(G)$ are exactly

```math
\{e_v:v\in V\}.
```

Because $\Phi$ restricts to an isomorphism of the diagonal algebras, it
permutes their primitive idempotents and induces a bijection

```math
\phi:V(G)\longrightarrow V(H)
```

such that

```math
\Phi(e_v)=e_{\phi(v)}.
```

The node set is therefore recovered up to relabeling.

### Recovery of primitive-channel multiplicities

For $u,v\in V(G)$, the corner

```math
e_v\mathcal A_1(G)e_u
```

has as a basis the channels from $u$ to $v$. Hence

```math
\dim_{\mathbb K}
e_v\mathcal A_1(G)e_u=
|E_G(u,v)|.
```

Because $\Phi$ preserves degree one and the node idempotents,

```math
\Phi\!\left(
e_v\mathcal A_1(G)e_u
\right)=
e_{\phi(v)}
\mathcal A_1(H)
e_{\phi(u)}.
```

Taking dimensions gives

```math
|E_G(u,v)|=
|E_H(\phi(u),\phi(v))|
```

as cardinals.

For each ordered pair $(u,v)$, choose a bijection between the corresponding
channel sets. Together with $\phi$, these bijections define a directed
multigraph isomorphism

```math
G\cong H.
```

Conversely, every directed multigraph isomorphism induces a diagonal- and
grading-preserving path-algebra isomorphism. Thus

```math
G\cong H
\iff
\bigl(\mathcal A(G),\mathcal D(G),\text{grading}\bigr)
\cong
\bigl(\mathcal A(H),\mathcal D(H),\text{grading}\bigr).
```

The marked graded algebra is therefore a complete invariant of the directed
multigraph.

# 3. Linear mixing of parallel channels

The theorem recovers the underlying system up to isomorphism, but it does not
imply that every algebra isomorphism is induced by a permutation of individual
channels.

Consider two nodes $u,v$ and two parallel channels

```math
a,b:u\to v.
```

The transformation

```math
a\mapsto a+b,
\qquad
b\mapsto b
```

extends to a graded diagonal-preserving algebra automorphism. Its inverse is

```math
a\mapsto a-b,
\qquad
b\mapsto b.
```

The transformation mixes the two-dimensional channel basis rather than
permuting the discrete channels.

More generally, if there are $\kappa$ parallel channels from $u$ to $v$, the
algebra admits invertible linear transformations of the corner

```math
e_v\mathcal A_1e_u.
```

Thus the marked graded algebra determines the system's isomorphism class. The
stronger assertion that every algebra isomorphism extends a channel permutation
is generally false.

## Channel-resolved marking

To recover individual channels rather than only their multiplicities, retain
the distinguished subset

```math
\mathcal E(G)\subseteq\mathcal A_1(G)
```

and require

```math
\Phi(\mathcal E(G))=\mathcal E(H).
```

The isomorphism then maps channels to channels. Since the node idempotents and
primitive channels generate the path algebra, such a $\Phi$ is precisely the
extension of a directed multigraph isomorphism.

This gives two natural levels of marking. The multiplicity-level object is

```math
\mathbf A_{\mathrm{multiplicity}}(G)=
(\mathcal A,\mathcal D,\text{grading}),
```

which remembers the cardinality of each parallel-channel space. The
channel-resolved object is

```math
\mathbf A_{\mathrm{resolved}}(G)=
(\mathcal A,\mathcal D,\text{grading},\mathcal E),
```

which also remembers the distinguished discrete set of channels. Since the
definition assigns no additional primitive attributes to parallel channels, the
resolved marking is the more conservative universal object; it may be forgotten
when only channel multiplicities are relevant.

# 4. Generation by the degree-one bimodule

Let

```math
\mathcal M(G)=\mathcal A_1(G).
```

It is naturally a bimodule over the node diagonal:

```math
\mathcal D\mathcal M\mathcal D\subseteq\mathcal M.
```

The corner

```math
e_v\mathcal M e_u
```

is the channel space from $u$ to $v$.

Form the tensor powers over $\mathcal D$,

```math
\mathcal M^{\otimes_{\mathcal D}n}.
```

A pure tensor

```math
a_n\otimes\cdots\otimes a_1
```

survives precisely when the channels are composable and then corresponds to
the path

```math
a_n\cdots a_1.
```

Multiplication therefore induces the graded isomorphism

```math
\mathcal A_n(G)
\cong
\mathcal M(G)^{\otimes_{\mathcal D}n}.
```

Consequently, the full path algebra is the tensor algebra

```math
\mathcal A(G)
\cong
T_{\mathcal D}(\mathcal M)=
\mathcal D
\oplus\mathcal M
\oplus
\mathcal M^{\otimes_{\mathcal D}2}
\oplus
\mathcal M^{\otimes_{\mathcal D}3}
\oplus\cdots.
```

Thus $\mathcal D$ encodes the mutually orthogonal nodes, while $\mathcal M$
encodes the primitive directed channels. Tensor multiplication produces
indirect communication, the order of multiplication records direction, and
noncomposable tensors vanish. The complete finite-path structure is freely
generated by the pair

```math
(\mathcal D,\mathcal M).
```

# 5. Algebraic characterization of acyclicity

Define the positive-path ideal

```math
J(G)=
\bigoplus_{n\ge1}\mathcal A_n(G).
```

## Theorem 2. Acyclicity and local nilpotence

The following are equivalent:

1. $G$ contains no directed cycle.
2. For every $v\in V$ and $n\ge1$, $e_v\mathcal A_n(G)e_v=0$.
3. Every element of $J(G)$ is nilpotent.
4. $J(G)$ is locally nilpotent: every finitely generated subalgebra of $J(G)$
   is nilpotent.

## Proof

The path basis identifies the first two conditions. If $G$ has a directed cycle
$p$, then

```math
p^m\ne0
\qquad(m\ge1).
```

Thus $p\in J$ is not nilpotent, so neither condition 3 nor condition 4 can
hold.

Conversely, take finitely many elements

```math
x_1,\ldots,x_k\in J.
```

Each is a finite linear combination of finite paths. Their combined supports
involve only finitely many vertices; call this finite set $F$.

Any sufficiently long nonzero product of the $x_i$ would contain a composable
path through more than $|F|$ vertices, forcing a repeated vertex and hence a
directed cycle.

Acyclicity therefore forces all sufficiently long products to vanish, and the
subalgebra generated by the $x_i$ is nilpotent. Hence

```math
\text{acyclicity}
\iff
J(G)\text{ is locally nilpotent}.
```

The argument is independent of the cardinality of the node set.

# 6. Finite height and unbounded finite depth

The ideal powers satisfy

```math
J^n=
\bigoplus_{m\ge n}\mathcal A_m.
```

It follows that

```math
J^{h+1}=0
```

if and only if no path has length greater than $h$. Equivalently,

```math
\text{finite path height}
\iff
J\text{ is globally nilpotent}.
```

An acyclic infinite multigraph with paths of arbitrary finite length instead
satisfies

```math
J^n\ne0
\qquad\text{for every }n,
```

while $J$ remains locally nilpotent.

The three cases may be summarized as follows:

```math
\begin{array}{c|c}
\text{System type}&\text{Positive-path ideal}\\
\hline
\text{finite height}&\text{nilpotent}\\
\text{unbounded finite path lengths}&
\text{locally nilpotent but not nilpotent}\\
\text{contains a directed cycle}&
\text{not locally nilpotent}
\end{array}
```

Both an infinite chain and a disjoint union of finite chains with unbounded
lengths lie in the middle row. Their distinction requires finer
order-theoretic information than the non-nilpotence of $J$ alone.

# 7. Recovery of finite communication data

The marked graded algebra gives exact recovery formulas. Direct-channel
multiplicities are

```math
\left|\{e:u\to v\}\right|=
\dim e_v\mathcal A_1e_u.
```

Since $\mathcal A_1\cong J/J^2$, the same multiplicity is recovered
intrinsically from

```math
\left|\{e:u\to v\}\right|=
\dim e_v(J/J^2)e_u.
```

More generally, the number of length-$n$ paths is

```math
\left|\{\text{paths of length }n:u\to v\}\right|=
\dim e_v\mathcal A_ne_u,
```

which may be a finite or infinite cardinal. Reachability and acyclicity are
characterized by

```math
u\prec v
\iff
e_vJe_u\ne0
```

and

```math
u\nprec u
\iff
e_uJe_u=0,
```

respectively. Finally, the least $n$ for which

```math
e_v\mathcal A_ne_u\ne0
```

is the shortest channel-composition length from $u$ to $v$. The supremum of
such integers measures finite compositional depth; it is not an external time
duration.

# 8. Spectral consequences of local nilpotence

For an acyclic system, every finitely supported element $x\in J$ is nilpotent.
Hence in every bounded representation,

```math
\sigma(x)=\{0\}.
```

A finitely supported positive-path expression therefore has no nonzero
spectrum. Nonzero spectral data may enter through diagonal components, through
expressions involving adjoints in a Hilbert-space representation, or through
norm and operator-topology completions. Within the positive-path sector, the
first such behavior arises from infinite limits.

For example, finite partial sums along an infinite chain are nilpotent:

```math
T_N=L_{e_0}+\cdots+L_{e_N},
\qquad
\sigma(T_N)=\{0\}.
```

But a bounded infinite sum can converge to a shift-like operator $T$ with

```math
\sigma(T)=\{z:|z|\le1\}.
```

Thus the algebraic positive-path structure may be locally nilpotent while its
operator completion has nontrivial spectrum. The example isolates the role of
infinite limits in producing this spectral behavior.

# 9. Literature relation

Theorem 1 recovers a directed multigraph from its path algebra together with the
marked diagonal and the grading. Reconstruction theorems for the operator
algebras attached to a directed graph are proved in E. G. Katsoulis and D. W.
Kribs, *Isomorphisms of algebras associated with directed graphs*, Mathematische
Annalen 330 (2004), 709-728, arXiv:math/0309363, and in B. Solel, *You can see
the arrows in a quiver operator algebra*, Journal of the Australian Mathematical
Society 77 (2004), 111-122, arXiv:math/0309420. Katsoulis and Kribs work with
countable graphs and recover the graph from a Banach-algebra isomorphism of the
associated algebras, and from an algebraic isomorphism when the graph has no
sinks; Solel shows that an isometric isomorphism of quiver operator algebras
forces an isomorphism of the underlying quivers.

Theorem 1 assumes an algebra isomorphism that carries the diagonal onto the
diagonal and each grading component onto the corresponding component, and it
imposes no norm, no topology, no restriction on the cardinality of the node or
edge set, and no condition on sinks. Neither statement implies the other. The
hypotheses of Theorem 1 include the diagonal and the grading, which the cited
theorems do not assume, and exclude the analytic and countability hypotheses on
which their proofs rest; conversely those theorems apply to isomorphisms of
completed algebras that are not given as graded maps, about which Theorem 1
says nothing.
