# 1. Fock representation for arbitrary cardinality

Let

$$
\mathsf P(G)
$$

be the set of all finite paths, including the length-zero paths $1_v$.

Define

$$
\mathcal H_G=\ell^2(\mathsf P(G)).
$$

This remains well-defined when $\mathsf P(G)$ is uncountable because every vector in $\ell^2(\mathsf P(G))$ has at most countable support.

Let

$$
{\xi_p:p\in\mathsf P(G)}
$$

be the canonical orthonormal basis.

For every node $v$, define

$$
P_v\xi_p=
\begin{cases}
\xi_p,&r(p)=v,\\
0,&r(p)\ne v.
\end{cases}
$$

Thus $P_v$ projects onto paths whose current terminal node is $v$.

For every primitive channel $e:u\to v$, define

$$
L_e\xi_p=
\begin{cases}
\xi_{ep},&r(p)=u,\\
0,&r(p)\ne u.
\end{cases}
$$

Here $ep$ means: first traverse $p$, then traverse $e$.

These are the standard left-regular or Fock operators associated with a directed graph; the countable case is the starting point of free semigroupoid algebra theory.

## Forced relations

Direct calculation gives

$$
P_uP_v=\delta_{uv}P_v,
$$

$$
L_e^\ast L_e=P_{s(e)},
$$

$$
L_eL_e^\ast\le P_{r(e)},
$$

and

$$
P_{r(e)}L_eP_{s(e)}=L_e.
$$

For distinct primitive channels,

$$
L_e^\ast L_f=0
\qquad(e\ne f).
$$

This remains true for parallel channels. Although they share source and target, they produce orthogonal path vectors.

The projections satisfy

$$
\sum_{v\in V}P_v=I
$$

in the strong-operator sense, meaning that the net of finite partial sums

$$
\sum_{v\in F}P_v
$$

converges strongly to $I$ as $F$ ranges over finite subsets of $V$.

Thus the complete boundary of A1 appears as the strong identity even when there is no algebraic finite sum of all nodes.

# 2. Faithfulness

For a finite path $p=e_n\cdots e_1$, define

$$
L_p=L_{e_n}\cdots L_{e_1},
$$

and set

$$
L_{1_v}=P_v.
$$

This defines a representation

$$
\lambda_G:\mathbb C[G]\to B(\mathcal H_G).
$$

## Theorem: Fock faithfulness

$$
\lambda_G\text{ is injective for every set-sized quiver }G.
$$

Take

$$
x=\sum_{p\in F}c_p p,
$$

where $F$ is finite. For a node $v$,

$$
\lambda_G(x)\xi_{1_v}=
\sum_{\substack{p\in F\\s(p)=v}}
c_p\xi_p.
$$

The vectors $\xi_p$ are orthonormal. If $\lambda_G(x)=0$, this expression vanishes for every $v$, so every coefficient $c_p$ is zero.

Therefore the Fock realization loses none of the algebraic path information.

# 3. The completion tower

There is not one operator algebra but a natural tower.

## Algebraic level

$$
\mathcal A_{\mathrm{alg}}(G)=
\lambda_G(\mathbb C[G]).
$$

Only finite linear combinations of paths occur here.

This level is forced most directly by A1–A5.

## Norm-closed level

Define

$$
\mathcal T_+(G)=
\overline{\mathcal A_{\mathrm{alg}}(G)}^{|\cdot|}.
$$

This permits precisely those infinite approximations that converge in operator norm.

For countable graphs this is the graph tensor algebra or norm-closed quiver algebra. Such tensor algebras are instances of tensor algebras of $C^\ast$-correspondences.

## Weak-operator level

Define

$$
\mathcal L(G)=
\overline{\mathcal A_{\mathrm{alg}}(G)}^{\mathrm{WOT}}.
$$

This admits bounded global operators obtained as weak or strong limits of uniformly bounded finite sums.

In the standard countable setting, this is called the free semigroupoid algebra.

## Self-adjoint Fock envelope

Define

$$
\mathcal T_{\mathrm{Fock}}(G)=
C^\ast(P_v,L_e:v\in V,e\in E).
$$

This includes the adjoints $L_e^\ast$, but those adjoints are not reverse communication channels. They are operator-theoretic devices that test and remove path prefixes.

The hierarchy is therefore

$$
\mathcal A_{\mathrm{alg}}(G)
\subseteq
\mathcal T_+(G)
\subseteq
\mathcal L(G)
\subseteq
B(\mathcal H_G),
$$

with the self-adjoint Fock algebra generated alongside them.

## Cardinality limitation

The definitions above extend directly to arbitrary cardinality. Many published structure and classification theorems, however, are stated for finite or countable graphs and need not extend to a nonseparable $\mathcal H_G$. The arbitrary-cardinality results here are those proved directly from the definitions.

# 4. Norm and weak closure retain different infinities

If $V$ is infinite, the finite node sums satisfy

$$
\left|
I-\sum_{v\in F}P_v
\right|=1
$$

for every finite $F\subset V$.

Therefore

$$
I\notin\mathcal T_+(G)
$$

in general.

But

$$
\sum_{v\in F}P_v\longrightarrow I
$$

strongly, so

$$
I\in\mathcal L(G).
$$

The diagonal at the norm-closed level is

$$
\mathcal D_{|\cdot|}
\cong c_0(V),
$$

whereas the weakly closed diagonal is

$$
\mathcal D_{\mathrm{WOT}}
\cong\ell^\infty(V).
$$

This is a concrete example of infinite information appearing only after a topology is selected: the choice specifies which limits of finite path expressions are retained.

# 5. Compositional depth and the gauge action

Decompose the Fock space by path length:

$$
\mathcal H_G=
\bigoplus_{n=0}^\infty\mathcal H_n,
$$

where

$$
\mathcal H_n=
\overline\{\mathrm{span}\}
{\xi_p:|p|=n}.
$$

Define the unbounded number operator

$$
N\xi_p=|p|\xi_p
$$

on the natural domain

$$
\mathrm{Dom}(N)=
\left\{
\sum_pa_p\xi_p:
\sum_p |p|^2|a_p|^2<\infty
\right\}.
$$

The operator measures primitive-channel composition depth.

For every channel,

$$
[N,L_e]=L_e,
$$

and for every finite path,

$$
[N,L_p]=|p|L_p.
$$

Exponentiating $N$ gives a circle action:

$$
U_z\xi_p=z^{|p|}\xi_p,
\qquad z\in\mathbb T.
$$

Then

$$
\gamma_z(X)=U_zXU_z^\ast
$$

satisfies

$$
\gamma_z(P_v)=P_v,
\qquad
\gamma_z(L_e)=zL_e,
\qquad
\gamma_z(L_p)=z^{|p|}L_p.
$$

The variable $z$ is dual to path length, not physical time.

# 6. Canonical Fourier decomposition

For $X\in\mathcal T_+(G)$, define

$$
\Phi_n(X)=
\int_{\mathbb T}
\overline z^{,n}\gamma_z(X),dm(z),
$$

where $m$ is normalized Haar measure on the circle.

Then:

* $\Phi_0(X)$ is the node-diagonal part;
* $\Phi_1(X)$ is the primitive-channel part;
* $\Phi_n(X)$ is the length-$n$ path part.

For an algebraic polynomial,

$$
X=\sum_pc_pL_p,
$$

we obtain

$$
\Phi_n(X)=
\sum_{|p|=n}c_pL_p.
$$

The Fejér sums

$$
\Sigma_N(X)=
\sum_{n=0}^N
\left(1-\frac{n}{N+1}\right)\Phi_n(X)
$$

converge to $X$ in norm for $X\in\mathcal T_+(G)$.

Thus the norm-closed operator algebra can still be reconstructed from its finite compositional-depth components.

The grading has not disappeared after completion.

# 7. Oriented noncommutativity

Let $p$ and $q$ be nonempty paths.

Suppose

$$
L_qL_p\ne0.
$$

This means the terminal node of $p$ is the initial node of $q$.

If also

$$
L_pL_q\ne0,
$$

then $p$ and $q$ concatenate in both cyclic orders, producing a directed closed path.

Therefore A5 implies

$$
L_qL_p\ne0
\quad\Longrightarrow\quad
L_pL_q=0.
$$

This identifies the noncommuting terms explicitly.

It says that permitted composition in one direction actively excludes the reverse composition.

# 8. A canonical global channel operator

The individual $L_e$ always exist and have norm one.

A global unweighted sum

$$
S=\sum_{e\in E}L_e
$$

does not always define a bounded operator.

Let

$$
d^+(v)=|{e:s(e)=v}|
$$

be the outgoing channel multiplicity.

## Theorem: bounded global creator

The unweighted operator $S$ is bounded precisely when

$$
D^+=
\sup_{v\in V}d^+(v)<\infty.
$$

In that case,

$$
S^\ast S=
\sum_{v\in V}d^+(v)P_v
$$

strongly, and

$$
|S|=\sqrt{D^+}.
$$

Indeed, distinct edge creators have orthogonal ranges, so

$$
\left|
\sum_ec_eL_e
\right|^2=
\sup_v
\sum_{s(e)=v}|c_e|^2
$$

whenever the right side is finite.

This result is entirely structural. It says:

$$
\text{A uniformly weighted bounded aggregate exists exactly under uniform finite branching.}
$$

If one node has infinitely many outgoing channels, an equal nonzero Hilbert coefficient on all of them cannot be square-summable.

The individual channel family remains valid; only its unweighted aggregate fails to be bounded.

# 9. Powers count all paths without a node-count assumption

Assume $S$ is bounded.

For $n\ge1$,

$$
S^n=
\sum_{|p|=n}L_p
$$

in the strong-operator sense.

Let

$$
N_n(v)=
\#\{p:|p|=n,\ s(p)=v\}.
$$

This is the number of length-$n$ communication paths beginning at $v$.

Distinct paths of the same length have orthogonal Fock ranges, so

$$
(S^n)^\ast S^n=
\sum_{v\in V}N_n(v)P_v.
$$

Consequently,

$$
|S^n|=
\sqrt{\sup_{v\in V}N_n(v)}.
$$

The spectral-radius formula gives

$$
r(S)=
\lim_{n\to\infty}|S^n|^{1/n},
$$

hence

$$
r(S)=
\lim_{n\to\infty}
\left(
\sup_{v\in V}N_n(v)
\right)^{1/(2n)}.
$$

This is a genuine cardinality-independent spectral theorem:

$$
\text{the spectral radius of the global path creator measures exponential path branching.}
$$

No chosen time evolution appears.

# 10. Examples

## Finite-height system

If every path has length at most $h$, then

$$
S^{h+1}=0.
$$

Therefore

$$
\sigma(S)=\{0\}.
$$

## One-way infinite chain

For

$$
v_0\to v_1\to v_2\to\cdots,
$$

there is exactly one length-$n$ path from each node:

$$
N_n(v)=1.
$$

Thus

$$
|S^n|=1,
\qquad
r(S)=1.
$$

The Fock operator is a pure isometry, so

$$
\sigma(S)=\{z:|z|\le1\}.
$$

## Regular (d)-branching tree

If every node has exactly $d$ outgoing channels, then

$$
N_n(v)=d^n.
$$

Therefore

$$
|S^n|=d^{n/2},
\qquad
r(S)=\sqrt d.
$$

After normalization,

$$
\frac1{\sqrt d}S
$$

is an isometry.

## Arbitrarily long finite chains

Take a disjoint union of finite chains whose lengths are unbounded.

There is no infinite directed path, but for every $n$ some component contains a path of length $n$. Hence

$$
\sup_vN_n(v)=1
$$

for all $n$, and again

$$
r(S)=1.
$$

Indeed, the direct sum of increasingly large nilpotent shifts has spectrum equal to the closed unit disk.

Consequently,

$$
\sigma(S)\text{ cannot distinguish an actual infinite chain from unbounded finite depth.}
$$

So the spectrum is meaningful but not complete. The full marked path algebra remains primary.

# 11. Why the node diagonal remains essential

Suppose we retain only $S$.

An arbitrary unitary conjugation

$$
S\mapsto USU^\ast
$$

preserves its spectrum, norms of powers, singular values, and many other operator invariants.

But it need not preserve the node sectors.

The correct object is therefore at least

$$
\bigl(
\mathcal T_+(G),
\mathcal D(G),
\gamma,
{L_e}_{e\in E}
\bigr).
$$

Here:

* $\mathcal D(G)$ records orthogonal nodes;
* ${L_e}$ records primitive channels;
* multiplication records path composition;
* $\gamma$ records compositional depth;
* the completion records infinite limits.

This directly incorporates the two earlier general lessons:

$$
\text{orthogonality must remain marked}
$$

and

$$
\text{channel composition is intrinsically noncommutative}.
$$

# 12. Why the (C^\ast)-envelope should not be primary

Tensor-algebra theory shows that the $C^\ast$-envelope of a $C^\ast$-correspondence tensor algebra is its Cuntz–Pimsner algebra.

That invariant should not replace the Fock algebra as the primary construction.

Passing from the Toeplitz/Fock algebra to a Cuntz–Pimsner or Cuntz–Krieger quotient can remove defect projections and impose coisometric boundary relations. Those relations are not stated in A1–A5.

So our hierarchy should be:

$$
\text{path algebra}
\to
\text{Fock tensor algebra}
\to
\text{Fock Toeplitz }C^\ast\text{-algebra}
$$

with the $C^\ast$-envelope retained as a derived quotient invariant, not interpreted automatically as the system itself.

This caution matches known reconstruction results: even in finite graph Toeplitz theory, the gauge action alone may not recover the graph; the canonical vertex diagonal is also needed.
