# 1. Fock representation at arbitrary cardinality

Let $\mathsf P(G)$ be the set of finite paths in $G$, including the length-zero paths $1_v$, and define

```math
\mathcal H_G=\ell^2(\mathsf P(G)).
```

The definition remains valid when $\mathsf P(G)$ is uncountable because every vector in $\ell^2(\mathsf P(G))$ has at most countable support.

Write

```math
\{\xi_p:p\in\mathsf P(G)\}
```

for the canonical orthonormal basis.

For every node $v$, define

```math
P_v\xi_p=
\begin{cases}
\xi_p,&r(p)=v,\\
0,&r(p)\ne v.
\end{cases}
```

Thus $P_v$ projects onto the subspace spanned by paths with terminal node $v$.

For every primitive channel $e:u\to v$, define

```math
L_e\xi_p=
\begin{cases}
\xi_{ep},&r(p)=u,\\
0,&r(p)\ne u.
\end{cases}
```

The notation $ep$ means that $p$ is traversed first and $e$ second. For countable graphs, the operators $P_v$ and $L_e$ are the standard left-regular, or Fock, representation used in free semigroupoid algebra theory.

## Operator relations

A direct calculation gives

```math
P_uP_v=\delta_{uv}P_v,
\qquad
L_e^\ast L_e=P_{s(e)},
\qquad
L_eL_e^\ast\le P_{r(e)},
\qquad
P_{r(e)}L_eP_{s(e)}=L_e.
```

For distinct primitive channels,

```math
L_e^\ast L_f=0
\qquad(e\ne f).
```

Parallel channels share source and target but still produce orthogonal path vectors.

The projections satisfy

```math
\sum_{v\in V}P_v=I
```

in the strong-operator sense, meaning that the net of finite partial sums

```math
\sum_{v\in F}P_v
```

converges strongly to $I$ as $F$ ranges over finite subsets of $V$.

The full node decomposition therefore converges to the identity in the strong topology, even when no algebraic sum over all nodes exists.

# 2. Faithfulness of the Fock representation

For a finite path $p=e_n\cdots e_1$, define

```math
L_p=L_{e_n}\cdots L_{e_1},
```

and set

```math
L_{1_v}=P_v.
```

These operators define a representation

```math
\lambda_G:\mathbb C[G]\to B(\mathcal H_G).
```

## Theorem 1. Fock faithfulness

For every set-sized quiver $G$, the representation $\lambda_G$ is injective.

To prove this, take

```math
x=\sum_{p\in F}c_p p,
```

where $F$ is finite. For a node $v$,

```math
\lambda_G(x)\xi_{1_v}=
\sum_{\substack{p\in F\\s(p)=v}}
c_p\xi_p.
```

The vectors $\xi_p$ are orthonormal. If $\lambda_G(x)=0$, this expression vanishes for every $v$, so every coefficient $c_p$ is zero.

Hence the Fock representation preserves all algebraic path information.

# 3. Natural operator-algebra completions

The Fock representation gives several natural operator-algebra completions.

## Algebraic image

The algebraic image is

```math
\mathcal A_{\mathrm{alg}}(G)=
\lambda_G(\mathbb C[G]).
```

This algebra consists of finite linear combinations of path operators and is the direct image of the primitive node-channel structure.

## Norm closure

Define

```math
\mathcal T_+(G)=
\overline{\mathcal A_{\mathrm{alg}}(G)}^{\lVert\cdot\rVert}.
```

The norm closure contains precisely the operator-norm limits of algebraic path polynomials.

For countable graphs, this is the graph tensor algebra, or norm-closed quiver algebra, an instance of a tensor algebra of a $C^\ast$-correspondence.

## Weak-operator closure

Define

```math
\mathcal L(G)=
\overline{\mathcal A_{\mathrm{alg}}(G)}^{\mathrm{WOT}}.
```

The weak-operator closure contains bounded global operators obtained as weak limits, including strong limits of uniformly bounded finite sums.

In the standard countable setting, this is called the free semigroupoid algebra.

## Self-adjoint Fock algebra

Define

```math
\mathcal T_{\mathrm{Fock}}(G)=
C^\ast(P_v,L_e:v\in V,e\in E).
```

This self-adjoint algebra includes the adjoints $L_e^\ast$, which test and remove path prefixes in the Fock representation. They do not represent reverse communication channels.

These algebras satisfy

```math
\mathcal A_{\mathrm{alg}}(G)
\subseteq
\mathcal T_+(G)
\subseteq
\mathcal L(G)
\subseteq
B(\mathcal H_G),
```

while the self-adjoint Fock algebra is generated from the same representation by adjoining the $L_e^\ast$.

The definitions extend directly to arbitrary cardinality. Many structure and classification theorems in the literature, however, are stated only for finite or countable graphs and do not automatically extend to a nonseparable $\mathcal H_G$. The arbitrary-cardinality statements used here are therefore established directly from the definitions.

# 4. Norm and weak closures

If $V$ is infinite, the finite node sums satisfy

```math
\left\lVert
I-\sum_{v\in F}P_v
\right\rVert=1
```

for every finite $F\subset V$. Hence, in general,

```math
I\notin\mathcal T_+(G).
```

However,

```math
\sum_{v\in F}P_v\longrightarrow I
```

strongly, so

```math
I\in\mathcal L(G).
```

The diagonal at the norm-closed level is

```math
\mathcal D_{\lVert\cdot\rVert}
\cong c_0(V),
```

whereas the weakly closed diagonal is

```math
\mathcal D_{\mathrm{WOT}}
\cong\ell^\infty(V).
```

The choice of topology therefore determines which limits of finite path expressions belong to the completed algebra.

# 5. Compositional depth and the gauge action

Decompose the Fock space by path length:

```math
\mathcal H_G=
\bigoplus_{n=0}^\infty\mathcal H_n,
```

where

```math
\mathcal H_n=
\overline{\operatorname{span}\{\xi_p:|p|=n\}}.
```

Define the unbounded number operator

```math
N\xi_p=|p|\xi_p
```

on the natural domain

```math
\mathrm{Dom}(N)=
\left\lbrace \sum_pa_p\xi_p: \sum_p |p|^2|a_p|^2<\infty \right\rbrace.
```

The number operator measures primitive-channel composition depth.

For every channel,

```math
[N,L_e]=L_e,
```

and for every finite path,

```math
[N,L_p]=|p|L_p.
```

Exponentiating $N$ gives a circle action:

```math
U_z\xi_p=z^{|p|}\xi_p,
\qquad z\in\mathbb T.
```

Then

```math
\gamma_z(X)=U_zXU_z^\ast
```

satisfies

```math
\gamma_z(P_v)=P_v,
\qquad
\gamma_z(L_e)=zL_e,
\qquad
\gamma_z(L_p)=z^{|p|}L_p.
```

The circle parameter $z$ is dual to path length and has no assumed interpretation as physical time.

# 6. Fourier decomposition under the gauge action

For $X\in\mathcal T_+(G)$, define

```math
\Phi_n(X)=
\int_{\mathbb T}
\overline{z}^{\,n}\gamma_z(X)\,dm(z),
```

where $m$ is normalized Haar measure on the circle.

The coefficient $\Phi_0(X)$ is the node-diagonal component, $\Phi_1(X)$ is the primitive-channel component, and $\Phi_n(X)$ is the length-$n$ path component.

For an algebraic polynomial

```math
X=\sum_pc_pL_p,
```

the degree-$n$ Fourier coefficient is

```math
\Phi_n(X)=
\sum_{|p|=n}c_pL_p.
```

The Fejér sums

```math
\Sigma_N(X)=
\sum_{n=0}^N
\left(1-\frac{n}{N+1}\right)\Phi_n(X)
```

converge to $X$ in norm for $X\in\mathcal T_+(G)$.

The norm-closed algebra is therefore recovered as the norm limit of finite compositional-depth components; the grading persists after completion.

# 7. One-sided composition and noncommutativity

Let $p$ and $q$ be nonempty paths.

Suppose

```math
L_qL_p\ne0.
```

The terminal node of $p$ is therefore the initial node of $q$.

If also

```math
L_pL_q\ne0,
```

then $p$ and $q$ concatenate in both cyclic orders, producing a directed closed path.

Therefore acyclicity implies

```math
L_qL_p\ne0
\quad\Longrightarrow\quad
L_pL_q=0.
```

Thus a permitted composition in one order excludes the reversed composition. The noncommutativity is fixed by the orientation of the underlying paths.

# 8. The global channel creator

The individual $L_e$ always exist and have norm one.

The global unweighted sum

```math
S=\sum_{e\in E}L_e
```

does not always define a bounded operator.

Let

```math
d^+(v)=\lvert\{e:s(e)=v\}\rvert
```

denote the outgoing channel multiplicity at $v$.

## Theorem 2. Boundedness of the global creator

The unweighted operator $S$ is bounded precisely when

```math
D^+=
\sup_{v\in V}d^+(v)<\infty.
```

In that case the strong-operator identity

```math
S^\ast S=
\sum_{v\in V}d^+(v)P_v
```

holds, and

```math
\lVert S\rVert=\sqrt{D^+}.
```

Indeed, distinct edge creators have orthogonal ranges, so

```math
\left\lVert
\sum_ec_eL_e
\right\rVert^2=
\sup_v
\sum_{s(e)=v}|c_e|^2
```

whenever the right-hand side is finite. The unweighted aggregate is therefore bounded exactly under uniform finite branching.

If a node has infinitely many outgoing channels, equal nonzero Hilbert coefficients on all of them cannot be square-summable.

The individual channel operators remain well defined even when their unweighted aggregate is unbounded.

# 9. Path counting by powers of the global creator

Assume $S$ is bounded.

For $n\ge1$,

```math
S^n=
\sum_{|p|=n}L_p
```

in the strong-operator sense.

Let

```math
N_n(v)=
\left|\{p:|p|=n,\ s(p)=v\}\right|.
```

This cardinal counts the length-$n$ paths beginning at $v$.

Distinct paths of the same length have orthogonal Fock ranges, so

```math
(S^n)^\ast S^n=
\sum_{v\in V}N_n(v)P_v.
```

It follows that

```math
\lVert S^n\rVert=
\sqrt{\sup_{v\in V}N_n(v)}.
```

The spectral-radius formula gives

```math
r(S)=
\lim_{n\to\infty}\lVert S^n\rVert^{1/n},
```

hence

```math
r(S)=
\lim_{n\to\infty}
\left(
\sup_{v\in V}N_n(v)
\right)^{1/(2n)}.
```

This formula is independent of cardinality. The spectral radius of the global creator measures the exponential growth rate of path branching and does not require a chosen time evolution.

# 10. Examples

## Finite-height system

If every path has length at most $h$, then

```math
S^{h+1}=0,
\qquad
\sigma(S)=\{0\}.
```

## One-way infinite chain

For

```math
v_0\to v_1\to v_2\to\cdots,
```

there is exactly one length-$n$ path from each node:

```math
N_n(v)=1.
```

Consequently,

```math
\lVert S^n\rVert=1,
\qquad
r(S)=1.
```

The Fock operator is a pure isometry, so

```math
\sigma(S)=\{z:|z|\le1\}.
```

## Regular $d$-branching tree

If every node has exactly $d$ outgoing channels, then

```math
N_n(v)=d^n.
```

Therefore,

```math
\lVert S^n\rVert=d^{n/2},
\qquad
r(S)=\sqrt d.
```

After normalization,

```math
\frac1{\sqrt d}S
```

is an isometry.

## Arbitrarily long finite chains

Take a disjoint union of finite chains whose lengths are unbounded.

No infinite directed path exists, but for every $n$ some component contains a path of length $n$. Hence

```math
\sup_vN_n(v)=1
```

for all $n$, and again

```math
r(S)=1.
```

The direct sum of increasingly large nilpotent shifts has the closed unit disk as its spectrum. Consequently, $\sigma(S)$ does not distinguish an infinite chain from a family of finite chains with unbounded depth. The spectrum is informative but incomplete, so the full marked path algebra remains the primary invariant.

# 11. The role of the node diagonal

If only the operator $S$ is retained, an arbitrary unitary conjugation

```math
S\mapsto USU^\ast
```

preserves its spectrum, norms of powers, singular values, and many other operator invariants, but it need not preserve the node sectors. A graph-sensitive invariant must therefore retain at least

```math
\bigl(
\mathcal T_+(G),
\mathcal D(G),
\gamma,
\{L_e\}_{e\in E}
\bigr).
```

Here $\mathcal D(G)$ records the orthogonal node sectors, the family $\{L_e\}_{e\in E}$ records the primitive channels, multiplication records path composition, $\gamma$ records compositional depth, and the completion retains infinite limits. The marked object therefore preserves both node orthogonality and the intrinsically noncommutative composition of channels.

# 12. The status of the $C^\ast$-envelope

Tensor-algebra theory shows that the $C^\ast$-envelope of a $C^\ast$-correspondence tensor algebra is its Cuntz-Pimsner algebra.

This derived invariant should not replace the Fock algebra as the primary construction.

A Cuntz-Pimsner or Cuntz-Krieger quotient of the Toeplitz/Fock algebra can remove defect projections and impose coisometric boundary relations not imposed by the bounded system definition.

The path algebra embeds in the Fock tensor algebra, which in turn embeds in the Fock Toeplitz $C^\ast$-algebra. The $C^\ast$-envelope is retained as a derived quotient invariant and is not interpreted automatically as the system itself.

This distinction is consistent with reconstruction results for finite graph Toeplitz algebras, where the gauge action alone need not recover the graph and the distinguished vertex diagonal must also be retained.
