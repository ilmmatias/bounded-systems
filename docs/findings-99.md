# 1. The intrinsic two-step kernel

Let $W$ be an acyclic directed kernel on a probability space $(\Omega,\mu)$, and let

```math
s_W=d_W^--d_W^+
```

be its intrinsic signed degree coordinate. Retain the gap reconstruction defect from `findings-94.md`, so that vanishing of the corresponding Gram functional implies

```math
W(x,y)=\bigl(s_W(y)-s_W(x)\bigr)_+.
```

Define the rooted two-step kernel

```math
P_W(x,y)
=
\int_\Omega W(x,z)W(z,y)\,d\mu(z).
```

For the standalone gap kernel

```math
A(x,y)=(y-x)_+,
```

one has, whenever $x<y$,

```math
P_A(x,y)
=
\int_x^y(z-x)(y-z)\,dz
=
\frac{(y-x)^3}{6}.
```

Since $s_A(y)-s_A(x)=y-x$, the target satisfies the pointwise identity

```math
6P_A(x,y)
=
A(x,y)\bigl(s_A(y)-s_A(x)\bigr)^2.
```

This is a two-root compositional law. The left side measures the weighted volume of admissible intermediate states, while the right side is the cube of the intrinsic directed separation.

# 2. The cubic composition defect

Define

```math
C_W(x,y)
=
6P_W(x,y)
-
W(x,y)\bigl(s_W(y)-s_W(x)\bigr)^2.
```

The direct square $\int C_W^2$ contains repeated copies of the same formal edge through the term $W(x,y)^2$. As in `findings-93.md` and `findings-94.md`, use a one-sided Gram contraction instead. Set

```math
K_C(x,x')
=
\int_\Omega C_W(x,y)C_W(x',y)\,d\mu(y)
```

and

```math
\mathcal G_{\mathrm{comp}}(W)
=
\int_{\Omega^2}K_C(x,x')^2\,d\mu(x)d\mu(x').
```

Then

```math
\mathcal G_{\mathrm{comp}}(W)
=
\|C_WC_W^*\|_{\mathrm{HS}}^2
\geq0,
```

with equality if and only if $C_W=0$ in $L^2(\Omega^2)$.

## Proposition 1. Realization by simple DAG densities

The functional $\mathcal G_{\mathrm{comp}}$ is a finite linear combination of ordinary simple-DAG homomorphism densities.

## Proof

Each occurrence of $P_W(x,y)$ uses a fresh intermediate vertex and two distinct formal edges. Each occurrence of $s_W$ is a difference of one-edge rooted degree functions and can be expanded using fresh incoming and outgoing leaves. In the Gram contraction, the four appearances of $C_W$ occur at the formal pairs

```math
(x,y),\qquad(x',y),\qquad(x,y'),\qquad(x',y').
```

No formal directed edge is repeated. Expanding the products therefore produces finitely many simple directed patterns, even though their homomorphisms may identify vertices in an atomic representation.

Thus the cubic composition law is an admissible finite relational constraint in the ordinary central-DAG pattern algebra.

# 3. Reduction to a measure identity

Assume

```math
\mathcal G_{\mathrm{gap}}(W)=0
```

and

```math
\mathcal G_{\mathrm{comp}}(W)=0.
```

Let $\nu=(s_W)_*\mu$ be the probability distribution of the intrinsic signed degree coordinate. Since $s_W$ is bounded, $\nu$ has compact support. The two constraints imply

```math
W(x,y)=\bigl(s_W(y)-s_W(x)\bigr)_+
```

and, for $\nu\otimes\nu$-almost every $(a,b)$,

```math
6\int_{\mathbb R}
(t-a)_+(b-t)_+\,d\nu(t)
=
(b-a)_+^3.
```

The two sides are continuous functions of $(a,b)$. Therefore the identity holds for every pair in

```math
\operatorname{supp}(\nu)\times\operatorname{supp}(\nu).
```

The remaining forcing problem is now a one-dimensional measure-rigidity problem.

# 4. Relation to the rooted composition identities

The rooted identities of `findings-95.md` compare a one-root two-step volume with the square of a rooted degree. The present identity retains both endpoints and is strictly more sensitive to missing coordinate values. In particular, a gap in the coordinate support removes all admissible intermediate states between its endpoints while leaving a positive intrinsic separation.

This observation will eliminate the buffered-jump ambiguity without requiring a direct solution of the Stieltjes jump equations in `findings-98.md`.

Exact symbolic calculations reproduce the path-volume integral, the cubic defect, the endpoint-mixture formulas, and the edge-density extremality calculation.
