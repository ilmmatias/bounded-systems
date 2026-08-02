# 1. The intrinsic signed degree coordinate

Let $W$ be an acyclic directed kernel on a probability space $(\Omega,\mu)$.
Define its incoming and outgoing degree functions by

```math
d_W^-(x)=\int W(y,x)\,d\mu(y),
\qquad
d_W^+(x)=\int W(x,y)\,d\mu(y),
```

and set

```math
s_W(x)=d_W^-(x)-d_W^+(x).
```

For the standalone gap kernel

```math
A(x,y)=(y-x)_+
```

on $[0,1]$, these functions are

```math
d_A^-(x)=\frac{x^2}{2},
\qquad
d_A^+(x)=\frac{(1-x)^2}{2},
\qquad
s_A(x)=x-\frac12.
```

The latent coordinate is therefore already encoded by the difference of two
rooted graph observables.

# 2. The antisymmetric gap defect

Define the signed two-point defect

```math
R_W(x,y)
=
W(x,y)-W(y,x)-s_W(y)+s_W(x).
```

For $A$, the identity

```math
(y-x)_+-(x-y)_+=y-x
```

implies $R_A=0$.

## Theorem 1. Intrinsic gap reconstruction

Suppose $W$ is acyclic in the pointwise sense

```math
W(x,y)W(y,x)=0
```

for almost every pair $(x,y)$. Then

```math
R_W=0
```

if and only if

```math
W(x,y)=\bigl(s_W(y)-s_W(x)\bigr)_+
```

almost everywhere.

## Proof

Fix a pair $(x,y)$ and write

```math
a=W(x,y),
\qquad
b=W(y,x),
\qquad
\delta=s_W(y)-s_W(x).
```

The equation $R_W=0$ gives $a-b=\delta$. Acyclicity gives $a,b\geq0$ and
$ab=0$. If $\delta\geq0$, the only possibility is $a=\delta$ and $b=0$. If
$\delta<0$, the only possibility is $a=0$ and $b=-\delta$.

Thus the edge law is reconstructed from the intrinsic scalar coordinate $s_W$
without introducing an external order parameter.

# 3. A simple-DAG Gram constraint

The direct square $\int R_W^2$ contains repeated edge factors. As in
`findings-93.md`, use the one-sided Gram defect

```math
G_W(x,x')
=
\int R_W(x,z)R_W(x',z)\,d\mu(z)
```

and

```math
\mathcal G_{\mathrm{gap}}(W)
=
\int G_W(x,x')^2\,d\mu(x)d\mu(x').
```

Then

```math
\mathcal G_{\mathrm{gap}}(W)
=
\|R_WR_W^*\|_{\mathrm{HS}}^2
\geq0,
```

with equality if and only if $R_W=0$ as an $L^2$ kernel.

Every occurrence of $W$ in the expansion belongs to a distinct sampled vertex
pair. The degree functions are rooted one-edge densities, and products of them
are represented by independently sampled leaves. Consequently,
$\mathcal G_{\mathrm{gap}}$ is a finite linear combination of ordinary
simple-DAG homomorphism densities.

# 4. Relation to the earlier ambiguity mechanisms

The defect removes each explicit ambiguity constructed in `findings-87.md`
through `findings-91.md`.

For a nonzero degree-preserving perturbation $B=A+H$ supported on $x<y$,

```math
R_B(x,y)=H(x,y)-H(y,x).
```

Since $H$ vanishes on the reverse triangle, $R_B$ is nonzero whenever $H$ is
nonzero. Hence

```math
\mathcal G_{\mathrm{gap}}(B)>0.
```

For a signed two-sheet lift, the degree coordinate is unchanged while the
sheet-dependent pair mode remains in $W-W^{\mathsf T}$. The same Gram defect
therefore detects every nonzero lift of that form.

A specific finite cyclic contraction removes the route, forest, and
hidden-sheet ambiguities already exhibited.

# 5. Residual ambiguity after the Gram constraint

After imposing $\mathcal G_{\mathrm{gap}}=0$, the problem reduces from a
two-variable kernel to the distribution of one intrinsic scalar coordinate:

```math
W(x,y)=\bigl(s(y)-s(x)\bigr)_+.
```

The remaining question is whether finitely many rooted compositional identities
can force the distribution of $s$ to be uniform on an interval.

Exact symbolic calculations reproduce the target degree formulas, the
antisymmetric identity, the rooted two-step formulas, and strict positivity of
the Gram detector on explicit nonzero perturbations.
