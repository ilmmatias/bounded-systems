# 1. The route-duality involution

For a directed kernel $W$ on $[0,1]$, define

```math
W^\dagger(x,y)=W(1-y,1-x).
```

This operation reverses the edge direction and simultaneously reverses the latent coordinate. Every directed path is isomorphic to its edge reversal, so

```math
\rho_m(W^\dagger)=\rho_m(W)
```

for every $m\geq1$.

The gap kernel is fixed by this involution:

```math
A^\dagger=A.
```

# 2. An explicit dual-antisymmetric perturbation

Set

```math
\varphi_*(x,y)
=
x^4(1-y)^4(y-x)^4(x+y-1)
```

on $0<x<y<1$, and define

```math
H_*=\partial_x\partial_y\varphi_*.
```

The boundary factors imply exact row and column cancellation, so $H_*$ preserves both degree functions. The factor $x+y-1$ is antisymmetric under $(x,y)\mapsto(1-y,1-x)$, while the remaining factor is invariant. Consequently,

```math
H_*^\dagger=-H_*.
```

For sufficiently small $\varepsilon>0$, define

```math
B_+=A+\varepsilon H_*,
\qquad
B_-=A-\varepsilon H_*.
```

Then

```math
B_-=(B_+)^\dagger.
```

# 3. Exact equality of the complete route hierarchy

## Theorem 1. Route-dual ambiguity

The kernels $B_+$ and $B_-$ satisfy

```math
\rho_m(B_+)=\rho_m(B_-)
```

for every $m\geq1$.

They also have exactly the same incoming and outgoing degree functions as $A$.

## Proof

The route equality follows from

```math
B_-=(B_+)^\dagger
```

and invariance of every directed path density under the duality involution. Degree equality follows from the mixed-derivative boundary cancellation.

Thus the complete path-volume sequence cannot distinguish the two sectors.

# 4. Branching observables detect the lost sign

Let $D_{a,b}$ be the directed double broom consisting of:

- a root edge $u\to v$;
- $a$ incoming leaves pointing to $u$;
- $b$ outgoing leaves pointed to by $v$.

Its homomorphism density is

```math
t(D_{a,b},W)
=
\int
W(x,y)
\bigl(d_W^-(x)\bigr)^a
\bigl(d_W^+(y)\bigr)^b
\,dx\,dy.
```

Because the perturbation preserves the degrees, this density depends affinely on $\varepsilon$:

```math
t(D_{a,b},B_\pm)
=
t(D_{a,b},A)
\pm
\frac{\varepsilon}{2^{a+b}}
\int_\Delta
H_*(x,y)x^{2a}(1-y)^{2b}
\,dx\,dy.
```

For the first asymmetric pair,

```math
\frac1{2^3}
\int_\Delta
H_*(x,y)x^2(1-y)^4
\,dx\,dy
=
\frac1{4190266080},
```

while

```math
\frac1{2^3}
\int_\Delta
H_*(x,y)x^4(1-y)^2
\,dx\,dy
=
-
\frac1{4190266080}.
```

Therefore

```math
t(D_{1,2},B_+)
-
t(D_{1,2},B_-)
=
\frac{2\varepsilon}{4190266080}
\neq0.
```

The two kernels are consequently not weakly isomorphic.

# 5. Tangent interpretation

The route derivative kernels from `findings-88.md` are symmetric under

```math
(x,1-y)\longleftrightarrow(1-y,x).
```

The perturbation potential $\varphi_*$ is antisymmetric under the same exchange. Hence

```math
D\rho_m(A)[H_*]=0
```

for every $m$ simultaneously.

The exact duality statement is stronger: not only the first derivatives, but the complete route values agree between the two opposite perturbations.

The route hierarchy therefore retains only the dual-even part of this local relational information. Asymmetric branching patterns recover information that every path statistic loses.

Exact symbolic calculations confirm:

- exact dual antisymmetry of $H_*$;
- exact row and column cancellation;
- vanishing of the first route variations through the finite orders listed above;
- the two opposite double-broom coefficients;
- positivity of $\|H_*\|_2^2$.
