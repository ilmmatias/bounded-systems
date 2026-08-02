# 1. Balanced perturbations of the standalone gap kernel

The completed sector of `findings-85.md` is absolutely selectable, while the
standalone finite-forcing status of

```math
A(x,y)=(y-x)_+
```

remains unresolved. The first obstruction can be made exact: the complete
directed degree profile does not determine $A$.

On the open triangle $0<x<y<1$, define

```math
\psi(x,y)
=
x^4(1-y)^4(y-x)^4
```

and

```math
H(x,y)
=
\partial_x\partial_y\psi(x,y).
```

Set $H(x,y)=0$ when $x\geq y$. The polynomial factorization on the open
triangle is

```math
\begin{aligned}
H(x,y)
={}&
4x^3(x-y)^2(y-1)^3\\
&\times
\left(
8x^2-19xy+7x+8y^2-4y
\right).
\end{aligned}
```

For sufficiently small $|\varepsilon|$, the perturbed kernel

```math
A_\varepsilon(x,y)
=
A(x,y)+\varepsilon H(x,y)
```

still takes values in $[0,1]$ and vanishes when $x\geq y$. It therefore
remains an acyclic directed kernel.

# 2. Exact degree preservation

The boundary factors in $\psi$ give

```math
\int_x^1H(x,y)\,dy=0
```

for every $x$, and

```math
\int_0^yH(x,y)\,dx=0
```

for every $y$. Hence $A_\varepsilon$ has exactly the same incoming and
outgoing degree functions as $A$:

```math
d^-_\varepsilon(x)=\frac{x^2}{2},
\qquad
d^+_\varepsilon(x)=\frac{(1-x)^2}{2}.
```

Every rooted incoming star, rooted outgoing star, and mixed bi-star density
is therefore unchanged for all sufficiently small $\varepsilon$.

The two-edge route density is also unchanged, because it is

```math
\int_0^1d^-(x)d^+(x)\,dx.
```

Thus the full degree hierarchy and the first compositional route statistic do
not force the standalone gap kernel.

# 3. The perturbation is not an isomorphism

Integration by parts gives

```math
\langle A,H\rangle_{L^2}=0.
```

The exact squared norm of the perturbation is

```math
\|H\|_2^2
=
\frac1{1867190325}.
```

Therefore

```math
\|A_\varepsilon\|_2^2
=
\|A\|_2^2
+
\frac{\varepsilon^2}{1867190325}.
```

For every nonzero sufficiently small $\varepsilon$, the kernels
$A_\varepsilon$ and $A$ are not weakly isomorphic.

The first route statistic detecting this particular perturbation is the
three-edge route. Its first variation is

```math
\left.
\frac{d}{d\varepsilon}
\right|_{\varepsilon=0}
 t(P_3,A_\varepsilon)
=
-\frac1{60540480},
```

where $P_3$ denotes the directed path with three edges. Hence

```math
t(P_3,A_\varepsilon)
=
\frac1{7!}
-
\frac{\varepsilon}{60540480}
+
O(\varepsilon^2).
```

# 4. Infinite-dimensional balanced directions

The example belongs to an infinite-dimensional perturbation space. For every
smooth function $\varphi$ compactly supported inside the open triangle, the
mixed derivative

```math
H_\varphi
=
\partial_x\partial_y\varphi
```

has zero row and column integrals. These directions preserve the complete
directed degree functions to all orders in the perturbation parameter.

For a finite list of pattern densities $t(F_1,\cdot),\ldots,t(F_m,\cdot)$,
their Gateaux derivatives at $A$ are continuous linear functionals on this
infinite-dimensional space. Their common kernel is therefore
infinite-dimensional. There exists a nonzero balanced direction $H$
satisfying

```math
D t(F_j,A)[H]=0
\qquad
(1\leq j\leq m).
```

Thus no finite pattern family separates all nearby balanced perturbations at
first order.

A finite forcing family can be nonlinearly rigid even when its first
derivatives vanish along nonzero directions, so the first-order statement
leaves the finite forcibility of $A$ undecided.

A standalone forcing theorem for $A$ must therefore use nonlinear
higher-pattern rigidity. The compositional completion avoids this obstruction
by forcing the primitive order scaffold first and deriving the gap block from
an exact square defect.

Exact symbolic integration gives the row and column cancellations, invariant
degree functions, the vanishing inner product $\langle A,H\rangle$, the stated
$L^2$ norm, the unchanged two-edge route density, and the nonzero first
variation of the three-edge route.
