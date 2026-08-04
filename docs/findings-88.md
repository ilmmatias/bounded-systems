# 1. Route functionals of the gap kernel

Let

```math
A(x,y)=(y-x)_+
```

on $[0,1]^2$. For an integer $m\geq1$, define the directed $m$-edge route
density

```math
\rho_m(W)
=
\int_{[0,1]^{m+1}}
\prod_{j=0}^{m-1}W(x_j,x_{j+1})
\,dx_0\cdots dx_m.
```

For the gap kernel,

```math
\rho_m(A)=\frac1{(2m+1)!}.
```

The question addressed here is whether finitely many of these route
densities, even together with the complete incoming and outgoing degree
functions, can determine $A$.

# 2. Degree-preserving perturbation space

Let

```math
\Delta=\{(x,y):0<x<y<1\}.
```

For $\varphi\in C_c^\infty(\Delta)$, set

```math
H_\varphi=\partial_x\partial_y\varphi
```

on $\Delta$ and extend it by zero outside $\Delta$. Integration by parts
gives

```math
\int_x^1H_\varphi(x,y)\,dy=0,
\qquad
\int_0^yH_\varphi(x,y)\,dx=0.
```

Hence every sufficiently small perturbation

```math
A_c=A+\sum_{j=0}^r c_jH_{\varphi_j}
```

has exactly the same incoming and outgoing degree functions as $A$:

```math
d^-_{A_c}(x)=\frac{x^2}{2},
\qquad
d^+_{A_c}(x)=\frac{(1-x)^2}{2}.
```

Because the perturbations are compactly supported in the open triangle,
sufficiently small coefficients also preserve the bounds $0\leq A_c\leq1$ and
the strict-order support $x<y$. Thus $A_c$ remains an acyclic directed
kernel.

# 3. Linearization of every route density

Separating the perturbations of the previous section requires the first
variation of each $\rho_m$ at $A$.

## Proposition 1. Route derivative formula

For every $m\geq1$,

```math
D\rho_m(A)[H]
=
\int_\Delta H(x,y)Q_m(x,y)\,dx\,dy,
```

where

```math
Q_m(x,y)
=
\sum_{a=0}^{m-1}
\frac{x^{2a}}{(2a)!}
\frac{(1-y)^{2(m-1-a)}}{(2(m-1-a))!}.
```

If $H=H_\varphi$, then

```math
D\rho_m(A)[H_\varphi]
=
\int_\Delta \varphi(x,y)R_m(x,y)\,dx\,dy,
```

with

```math
R_m=\partial_x\partial_yQ_m.
```

For $m=1,2$,

```math
R_m=0.
```

For $m\geq3$,

```math
R_m(x,y)
=
-
\sum_{a=1}^{m-2}
\frac{x^{2a-1}}{(2a-1)!}
\frac{(1-y)^{2(m-1-a)-1}}
{(2(m-1-a)-1)!}.
```

## Proof

Differentiate the operator expression

```math
\rho_m(W)=\langle1,T_W^m1\rangle.
```

The $a$-th summand is

```math
\left\langle
(T_A^*)^a1,
T_HA^{m-1-a}1
\right\rangle.
```

The Volterra formulas from `findings-82.md` give

```math
(T_A^*)^a1(x)=\frac{x^{2a}}{(2a)!},
\qquad
T_A^b1(y)=\frac{(1-y)^{2b}}{(2b)!}.
```

Summing over $a$ yields $Q_m$. The formula for $R_m$ follows by two
integrations by parts.

# 4. Independence of the route derivatives

For $m\geq3$, the polynomial $R_m$ is nonzero and has total degree $2m-4$ in
the variables $x$ and $1-y$. Therefore the family

```math
R_{m_1},\ldots,R_{m_r}
```

is linearly independent whenever the integers $m_1,\ldots,m_r\geq3$ are
distinct.

Consequently, for every finite set

```math
M=\{m_1,\ldots,m_r\}\subseteq\{3,4,\ldots\},
```

there exist test functions $\varphi_1,\ldots,\varphi_r\in C_c^\infty(\Delta)$
for which the matrix

```math
\left(
\int_\Delta
\varphi_jR_{m_i}
\right)_{i,j=1}^r
```

is invertible.

# 5. Exact finite-route matching

The linear independence of the $R_{m_i}$ allows the route constraints to be
solved exactly, which gives the following matching statement.

## Theorem 2. Local route-matching manifolds

Let $M\subseteq\{1,2,3,\ldots\}$ be finite. There are nonzero smooth
perturbations $B$ arbitrarily close to $A$ such that:

1. $B$ is an acyclic $[0,1]$-valued directed kernel;
2. $B$ has exactly the same incoming and outgoing degree functions as $A$;
3. $\rho_m(B)=\rho_m(A)$ for every $m\in M$;
4. $B$ is not weakly isomorphic to $A$.

## Proof

The cases $m=1,2$ are automatic on the degree-preserving perturbation space.
Write the remaining elements of $M$ as $m_1,\ldots,m_r\geq3$.

Choose $r+1$ perturbation directions $H_0,H_1,\ldots,H_r$ so that the
Jacobian of

```math
F(c_0,\ldots,c_r)
=
\left(
\rho_{m_i}
\left(
A+\sum_{j=0}^rc_jH_j
\right)
-
\rho_{m_i}(A)
\right)_{i=1}^r
```

has rank $r$ at the origin. The finite-dimensional implicit-function theorem
implies that $F^{-1}(0)$ is locally a smooth one-dimensional manifold through
the origin. It therefore contains nonzero points arbitrarily close to zero.

For sufficiently small coefficients, the corresponding kernel $B$ remains in
$[0,1]$ and supported in $x<y$.

Finally, compact support and integration by parts give

```math
\langle A,H_j\rangle_{L^2}=0.
```

Hence every nonzero perturbation satisfies

```math
\|B\|_2^2
=
\|A\|_2^2+\|B-A\|_2^2
>
\|A\|_2^2.
```

The $L^2$ norm is invariant under weak isomorphism, so $B$ cannot be weakly
isomorphic to $A$.

# 6. Local fibers of finite route data

No finite collection of directed route densities can force the standalone gap
kernel, even after the complete incoming and outgoing degree functions have
been fixed exactly and even within the smooth ordered-support class.

This is stronger than the first-order obstruction in `findings-87.md`. Each
finite route family has an exact positive-dimensional local fiber of
non-isomorphic acyclic kernels.

The argument uses only directed route densities, so patterns with branching
or undirected cycle structure remain available for a forcing family.

Exact symbolic calculations confirm:

- the formulas for $Q_m$ and $R_m$;
- the automatic vanishing at $m=1,2$;
- the generating-function identity for the $R_m$;
- exact full-rank derivative matrices for the first six finite route families;
- the orthogonality $\langle A,H_\varphi\rangle=0$ for the specified
  polynomial test family.
