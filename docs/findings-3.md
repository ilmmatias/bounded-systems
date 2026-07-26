# 1. Infinite-system consequences of A1–A5

Let the system be a directed quiver

$$
G=(V,E,s,r),
$$

where $V$ and $E$ are sets and

$$
s,r:E\to V
$$

give the source and target of each channel.

Using a quiver rather than merely $E\subseteq V\times V$ keeps parallel channels possible, since the axioms do not rule them out.

## $C_{\infty 1}$: Cardinality is unrestricted

A1’s boundary is an isolation condition, not a finiteness condition. Therefore the axioms allow:

$$
|V|=n,\qquad |V|=\aleph_0,
\qquad\text{or an uncountable cardinal.}
$$

Nothing below needs the exact cardinality.

## $C_{\infty 2}$: Reachability is a strict partial order

Define

$$
u\prec v
$$

when there exists a positive-length finite directed path from $u$ to $v$.

A5 gives:

* irreflexivity:
$$
  u\nprec u;
$$
* transitivity:
$$
  u\prec v,;v\prec w\implies u\prec w.
$$

The direct edge relation need not itself be transitive. Shortcut edges may coexist with longer paths.

## $C_{\infty 3}$: The system is richer than its reachability poset

Several different paths may connect the same ordered pair:

$$
u\longrightarrow v.
$$

Collapsing all of them to the statement $u\prec v$ loses:

* primitive-edge multiplicity;
* route multiplicity;
* path length;
* intermediate-node structure;
* parallel channels.

So the reachability poset is a quotient of the full communication structure, not the full object.

## $C_{\infty 4}$: Infinite chains are allowed

A5 forbids finite directed cycles, but it does not forbid

$$
v_0\to v_1\to v_2\to\cdots.
$$

It consequently does not imply:

* finite height;
* a source;
* a sink;
* well-foundedness;
* bounded degree;
* local finiteness.

## $C_{\infty 5}$: Path length is not time

The number of edges in a path is its **compositional depth**:

$$
|p|=k.
$$

This records how many primitive channels were composed.

## $C_{\infty 6}$: Connectivity is not forced

A1 can contain several mutually noncommunicating components. “One outermost system” does not mean every node must be connected to every other node.

# 2. The universal object is the path category

Let

$$
\mathsf P(G)
$$

be the category whose:

* objects are nodes $v\in V$;
* generating morphisms are edges $e\in E$;
* morphisms are finite directed paths;
* identity at $v$ is the zero-length path $1_v$;
* composition is path concatenation.

Acyclicity gives:

$$
\mathrm{End}_{\mathsf P(G)}(v)=\{1_v\}.
$$

There are no nonidentity endomorphisms because any positive-length path from $v$ back to $v$ would be a directed cycle.

This is the **free** path category: it introduces no equations identifying two different edge sequences. If two paths were declared equal for some further reason, that equality would be extra structure not contained in A1–A5.

# 3. Algebraic path representation

Choose a scalar field, normally $\mathbb C$, and form

$$
\mathbb C[G]=
\mathbb C^{(\mathsf P(G))},
$$

the vector space of finite formal linear combinations of finite paths.

For basis paths $p,q$, define

$$
[q][p]=
\begin{cases}
[q\circ p],&p\text{ and }q\text{ are composable},\\
0,&\text{otherwise}.
\end{cases}
$$

This gives an associative, generally noncommutative path algebra. Standard path algebras are defined exactly from finite linear combinations of paths and concatenation.

Let

$$
e_v=[1_v].
$$

Then

$$
e_v^2=e_v,
\qquad
e_ue_v=0\quad(u\ne v).
$$

These are the algebraic form of node orthogonality.

For an edge $a:u\to v$,

$$
e_v a e_u=a.
$$

But

$$
e_u a=0,
\qquad
a e_v=0,
$$

because $u\ne v$ in an acyclic system.

Therefore every actual channel forces noncommutativity:

$$
[e_v,a]=a,
\qquad
[e_u,a]=-a.
$$

So noncommutativity is not merely something that occasionally appears in complicated examples:

$$
\text{Any non-null edge structure is intrinsically noncommutative.}
$$

# 4. The distinguished node diagonal

Define

$$
\mathcal D_0=
\bigoplus_{v\in V}\mathbb C e_v.
$$

This is the canonical node algebra.

It must remain marked as part of the object:

$$
\bigl(\mathbb C[G],\mathcal D_0\bigr).
$$

Without the marked diagonal, an abstract algebra can have additional idempotents that are not nodes. Arbitrary orthogonal or unitary changes of basis may preserve operator information while destroying the distinguished node decomposition.

This formalizes the lesson from the earlier orthogonal-similarity collisions:

$$
\text{System equivalence must preserve the node diagonal,}
$$

although it may permute its primitive node idempotents because node labels are not intrinsic.

For infinite $V$, $\mathbb C[G]$ generally has no algebraic global identity: the formal sum

$$
\sum_{v\in V}e_v
$$

is not finitely supported. It does have **local units**. Every finite collection of algebra elements is supported on finitely many nodes, so some finite sum

$$
e_F=\sum_{v\in F}e_v
$$

acts as an identity on that collection.

Algebraic unitality and system closure are distinct notions, so the construction is compatible with A1.

# 5. The positive-path ideal

Let

$$
J=\mathrm{span}\{p:|p|\ge1\}.
$$

Then

$$
\mathbb C[G]=
\mathcal D_0\oplus J
$$

as vector spaces.

More generally, the algebra is graded by path length:

$$
\mathbb C[G]=
\bigoplus_{n=0}^{\infty}\mathcal A_n,
$$

where

$$
\mathcal A_n=
\mathrm{span}\{p:|p|=n\}.
$$

Multiplication respects the grading:

$$
\mathcal A_m\mathcal A_n
\subseteq
\mathcal A_{m+n}.
$$

And

$$
J^n=
\mathrm{span}\{p:|p|\ge n\}.
$$

## A general infinite theorem

For every acyclic $G$:

$$
J\text{ is locally nilpotent}.
$$

To see this, take finitely many elements of $J$. Their path supports involve only finitely many vertices. A sufficiently long nonzero product would give a directed path that repeats a vertex, producing a cycle. Therefore sufficiently long products vanish.

In particular, every individual algebraic element

$$
x\in J
$$

is nilpotent.

However, $J$ need not be globally nilpotent.

In fact:

$$
J^{h+1}=0
\iff
\text{there is no directed path longer than }h.
$$

Thus:

* finite-height systems correspond to a nilpotent positive-path ideal;
* systems with paths of arbitrary finite length have
$$
  J^n\ne0
  \quad\text{for every }n;
$$
* nevertheless, every finitely supported positive process remains nilpotent.

This is a genuinely infinite result and does not depend on node count.

# 6. Recovering the system from the algebra

The marked graded algebra retains the primitive structure exactly.

For nodes $u,v$,

$$
e_v\mathcal A_n e_u
$$

is the vector space spanned by length-$n$ paths from $u$ to $v$.

Therefore:

### Reachability

$$
u\prec v
\iff
e_vJe_u\ne0.
$$

### Number of length-$n$ paths

$$
\dim\left(e_v\mathcal A_n e_u\right)=
\left|\{\text{length-}n\text{ paths } u \to v\}\right|
$$

The dimension may be any cardinal.

### Primitive channels

Composite paths lie in $J^2$. Consequently,

$$
J/J^2
$$

is precisely the primitive-edge space.

For each pair $u,v$,

$$
\dim\left(
e_v(J/J^2)e_u
\right)=
\left|\{\text{primitive edges }u\to v\}\right|.
$$

This preserves parallel channels.

Hence the triple

$$
\left(\mathbb C[G],\mathcal D_0,{\mathcal A_n}_{n\ge0}\right)
$$

recovers:

* nodes;
* primitive channels;
* parallel-edge multiplicities;
* all finite paths;
* path lengths;
* reachability;
* acyclicity.

It does so without knowing or fixing $|V|$.

# 7. Canonical Hilbert-space realization

Let

$$
\mathcal H_G=
\ell^2(\mathsf P(G)),
$$

with orthonormal basis

$$
{\xi_p:p\in\mathsf P(G)}.
$$

This Hilbert space is defined for an arbitrary set of paths, including an uncountable one.

For each node $v$, let $P_v$ project onto paths whose terminal node is $v$.

For each edge $e$, define left path creation:

$$
L_e\xi_p=
\begin{cases}
\xi_{ep},&s(e)=r(p),\\
0,&\text{otherwise}.
\end{cases}
$$

Then:

$$
P_uP_v=0\quad(u\ne v),
$$

$$
L_e^\ast L_e=P_{s(e)},
$$

$$
L_eL_e^\ast\le P_{r(e)},
$$

and for distinct primitive channels,

$$
L_e^\ast L_f=0
\quad(e\ne f).
$$

Parallel channels remain orthogonal because they create different path basis vectors.

Also,

$$
P_{r(e)}L_eP_{s(e)}=L_e.
$$

For a path $p=e_n\cdots e_1$,

$$
L_p=L_{e_n}\cdots L_{e_1}.
$$

The standard countable-graph version of this Fock-space construction leads to free semigroupoid algebras. Kribs and Power showed that, in that setting, the directed graph is a complete unitary invariant of the resulting algebra.

The formula itself makes sense for arbitrary cardinality; what remains to be established is which countable classification theorems extend unchanged to the nonseparable case.

# 8. Acyclicity becomes one-sided operator multiplication

If nonempty paths $p$ and $q$ satisfy

$$
L_qL_p\ne0,
$$

then $p$ can be followed by $q$.

In an acyclic graph, the reverse composition cannot also exist:

$$
L_qL_p\ne0
\implies
L_pL_q=0.
$$

If both products were nonzero, their source-target conditions would form a directed closed path.

This composes **oriented noncommutativity**:

$$
\text{one ordering may exist while its reversal is forbidden.}
$$

And that relation comes directly from A4 and A5.

# 9. Canonical aggregate operators

We do not assume one global adjacency operator exists.

Instead, individual channel operators $L_e$ always exist. For coefficients $c_e$, consider formally

$$
T_c=\sum_{e\in E}c_eL_e.
$$

Because distinct $L_e$ have orthogonal ranges,

$$
T_c^\ast T_c=
\sum_{v\in V}
\left(
\sum_{s(e)=v}|c_e|^2
\right)P_v.
$$

Therefore $T_c$ defines a bounded operator precisely when

$$
\sup_{v\in V}
\sum_{s(e)=v}|c_e|^2
<\infty.
$$

Then

$$
|T_c|=
\sup_{v\in V}
\left(
\sum_{s(e)=v}|c_e|^2
\right)^{1/2}.
$$

For the unweighted choice $c_e=1$, this becomes

$$
|T|=\sqrt{\sup_v\deg^+(v)}.
$$

Thus an unweighted global creator is bounded exactly when outgoing degree is uniformly bounded.

A corresponding right-creation aggregate is bounded exactly when incoming degree is uniformly bounded.

# 10. Spectral structure unique to infinity

Every finite-support element of $J$ is nilpotent, hence has spectrum

$$
{0}.
$$

But an operator completion may contain limits with nonzero spectral radius.

Consider the infinite chain

$$
0\to1\to2\to3\to\cdots.
$$

The global operator

$$
T=\sum_{n\ge0}L_{e_n}
$$

is bounded with $|T|=1$. On each fixed-start path sector, it acts as a unilateral shift, so

$$
\sigma(T)=\{z\in\mathbb C:|z|\le1\}.
$$

Every finite partial sum is nilpotent and has spectrum ${0}$, yet the infinite strong limit has the entire closed unit disk as spectrum.

Therefore:

$$
\text{Infinite spectral structure can appear only after completion,}
$$

even though every algebraic finite process is nilpotent.

The infinite object is not determined by the spectra of its finite truncations.

# 11. The primary invariant

The primary candidate is the marked nonselfadjoint operator algebra

$$
\mathbf B(G)=
\left(
\mathcal A_G,
\mathcal D_G,
\gamma
\right),
$$

where:

* $\mathcal A_G$ is generated by the $P_v$ and $L_e$;
* $\mathcal D_G$ is the distinguished node diagonal;
* $\gamma$ is the path-length grading or gauge action:
    $$
    \gamma_z(L_p)=z^{|p|}L_p,
    \qquad
    \gamma_z(P_v)=P_v.
    $$

This records:

* orthogonality;
* source and target corners;
* noncommutative composition;
* primitive versus composite channels;
* all finite paths;
* operator norms;
* spectra of canonical elements;
* infinite completion effects.

The norm-closed version is closely related to the directed graph tensor algebra; in the countable case, its $C^\ast$-envelope is the graph’s universal Cuntz–Krieger algebra.

But the nonselfadjoint algebra should remain primary here. Adjoint operators such as $L_e^\ast$ are mathematical Hilbert-space adjoints, **not reverse communication channels**.
