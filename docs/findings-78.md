# 1. Rectangular kernel transforms

The explicit completion of `findings-76.md` obtains continuum edge probabilities from one-variable compensator blocks. A second construction produces a finitely forcible payload whose own two-variable range is a continuum.

Let $K:X\times Y\to\mathbb R$ be a square-integrable bigraphon, viewed as a Hilbert-Schmidt operator

```math
T_K:L^2(Y)\longrightarrow L^2(X).
```

Define the rectangular cubic transform

```math
\Phi(T_K)
=
T_KT_K^*T_K+T_K.
```

At the kernel level, the cubic term is the alternating three-edge composition

```math
(KK^*K)(x,y)
=
\int_{Y\times X}
K(x,y_1)K(x_1,y_1)K(x_1,y)
\,d\nu(y_1)d\mu(x_1).
```

# 2. Injectivity

Write the polar decomposition as

```math
T_K=V|T_K|.
```

Then

```math
\Phi(T_K)
=
V\left(|T_K|+|T_K|^3\right).
```

The scalar map

```math
s\longmapsto s+s^3
```

is strictly increasing on $[0,\infty)$. The polar part and every singular value of $T_K$ are therefore determined by $\Phi(T_K)$.

## Proposition 1. Injectivity of the rectangular cubic transform

The map

```math
T\longmapsto TT^*T+T
```

is injective on real Hilbert-Schmidt operators.

# 3. Density adjoint

For a finite bipartite graph $F$, substitute

```math
\Phi(K)=K+KK^*K
```

on each edge. Expanding the product replaces every edge independently by either:

- one direct edge; or
- one alternating path of length three.

Every resulting object is again a finite bipartite graph. Hence there is a finite quantum-bigraph $\Phi^*(F)$ satisfying

```math
t(F,\Phi(K))
=
t(\Phi^*(F),K).
```

## Theorem 2. Forcing through the cubic transform

If $U$ is a finitely forcible real bigraphon and

```math
\Phi(K)=U,
```

then $K$ is finitely forcible.

## Proof

Pull a finite forcing family for $U$ back through $\Phi^*$. The resulting constraints force $\Phi(K)=U$. Proposition 1 makes the preimage unique.

An invertible affine transformation

```math
K\longmapsto\lambda K+\eta
```

also preserves finite forcibility. Thus a bounded real solution can be rescaled into $[0,1]$ without losing finite forcing.

# 4. A continuum-range payload

Take the half-bigraphon $H$ of `findings-76.md` and let $K$ be the unique solution of

```math
KK^*K+K=H.
```

Because $H$ is symmetric, this is the same kernel constructed from the half-graphon by Lovasz and Szegedy. Their spectral argument shows that $K$ has continuum essential range: it differs from the zero-one threshold kernel by a nonconstant continuous function, and its range contains two nontrivial intervals.

After an affine normalization, obtain

```math
\widetilde K:X\times Y\longrightarrow[0,1].
```

Theorem 2 makes $\widetilde K$ a finitely forcible bigraphon. The balanced-completion theorem then gives an absolutely finitely forcible central DAG sector whose payload block itself has continuum range.

## Corollary 3. Continuum-range payload selection

There exists an absolutely finitely forcible extremal central DAG sector whose graph-intrinsic payload block is non-step and has continuum essential range.

# 5. Consequences for the selection program

The finite relational selector need not arise from a finite block model. It can select a kernel defined through an infinite singular-value spectrum and a nonlinear operator equation.

For the selected sector, the finite terminal Gibbs construction of `findings-68.md` applies. A finite endpoint potential built from the forcing coordinates therefore selects, in the large-horizon limit, the harmonic growth law associated with this continuum-range payload.

The result does not establish finite forcibility of the specific distance kernel $|x-y|$ from `findings-58.md`. It instead supplies an explicit analytic class showing that continuum-range payloads are compatible with absolute finite selection. Determining whether $|x-y|$ itself is finitely forcible remains open.

Finite-rank calculations apply the singular-value inverse of $s\mapsto s+s^3$ to threshold matrices and recover the input rectangular operators from the equation $TT^*T+T=H$ to numerical precision. The single-edge density agrees with the adjoint substitution by a direct edge plus an alternating three-edge path, and the number of distinct payload values increases under refinement. These results verify the finite-rank algebra used by the proof. The continuum-range statement is the analytic result of the cited spectral construction.

# 6. Literature relation

Lovasz and Szegedy prove the symmetric version of the transform principle using adjoints of graphon operations and spectral injectivity. The rectangular proof above replaces eigenvalue decomposition by polar and singular-value decomposition; the density substitution remains bipartite because every cubic replacement is an alternating path.

Reference:

- L. Lovasz and B. Szegedy, *Finitely forcible graphons*, Journal of Combinatorial Theory, Series B 101 (2011), 269-301, arXiv:0901.0929, Section 3 and Proposition 5.4.
