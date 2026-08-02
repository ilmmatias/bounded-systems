# 1. Routes of arbitrary length

The continuous ordered sector of `findings-58.md` assigns independent marks

```math
U_i\sim\operatorname{Uniform}[0,1]
```

and places the edge from the smaller mark to the larger mark with probability
equal to their separation. For an integer $\ell\geq1$, consider a subset of
$\ell+1$ sampled vertices, order its marks as

```math
U_{(0)}<U_{(1)}<\cdots<U_{(\ell)},
```

and let $H_S^{(\ell)}$ be the indicator that every adjacent edge

```math
U_{(j-1)}\longrightarrow U_{(j)}
\qquad(1\leq j\leq\ell)
```

is present. Edges between nonadjacent ordered vertices are not constrained.
Define

```math
R_n^{(\ell)}
=
\frac1{\binom n{\ell+1}}
\sum_{|S|=\ell+1}H_S^{(\ell)}.
```

This extends the edge statistic $R_n^{(1)}$ and the two-step route statistic
$R_n^{(2)}$ studied previously.

# 2. Route means

The $\ell+2$ spacings determined by $\ell+1$ uniform order statistics have
the Dirichlet distribution with every parameter equal to one. The route
probability is the product of the $\ell$ internal spacings. The Dirichlet
moment formula therefore gives

```math
\theta_\ell
=
\mathbb E[H_S^{(\ell)}]
=
\frac{(\ell+1)!}{(2\ell+1)!}.
```

Equivalently, the labeled directed-path homomorphism density is

```math
p_\ell
=
\frac1{(2\ell+1)!},
```

and $\theta_\ell=(\ell+1)!p_\ell$.

# 3. Conditional one-vertex profile

Fix one distinguished mark at $x$. Suppose it has rank $r$ among the
$\ell+1$ ordered marks, so that $r$ other marks lie to its left and $\ell-r$
lie to its right.

The ordered left integral is

```math
\int_{0<y_1<\cdots<y_r<x}
(y_2-y_1)\cdots(y_r-y_{r-1})(x-y_r)
\,dy
=
\frac{x^{2r}}{(2r)!},
```

with the value one when $r=0$. The right integral is

```math
\frac{(1-x)^{2(\ell-r)}}{(2\ell-2r)!}.
```

After assigning the $\ell$ remaining labels, the rank-$r$ contribution is

```math
\ell!
\frac{x^{2r}(1-x)^{2(\ell-r)}}
{(2r)!(2\ell-2r)!}.
```

Summing over ranks and using the even-binomial identity gives the closed form

```math
q_\ell(x)
=
\ell!
\sum_{r=0}^{\ell}
\frac{x^{2r}(1-x)^{2(\ell-r)}}
{(2r)!(2\ell-2r)!}
=
\frac{\ell!}{2(2\ell)!}
\left[1+(1-2x)^{2\ell}\right].
```

Set

```math
A_\ell=\frac{\ell!}{2(2\ell)!}.
```

The first canonical projection is then

```math
h_\ell(x)
=
q_\ell(x)-\theta_\ell
=
A_\ell
\left[
(1-2x)^{2\ell}-\frac1{2\ell+1}
\right].
```

For $\ell=1$ and $\ell=2$, these formulas reproduce the edge and two-step
route projections of `findings-58.md`.

# 4. Exact leading coefficients

The change of variable $t=1-2x$ gives

```math
\sigma_{\ell,1}^2
=
\int_0^1h_\ell(x)^2\,dx
=
A_\ell^2
\left[
\frac1{4\ell+1}
-
\frac1{(2\ell+1)^2}
\right].
```

Since the route kernel has $\ell+1$ vertex positions, its intrinsic order-one
coefficient is

```math
C_1(\ell,\ell)
=
(\ell+1)^2A_\ell^2
\left[
\frac1{4\ell+1}
-
\frac1{(2\ell+1)^2}
\right].
```

For two route lengths $\ell,m\geq1$, the exact leading cross coefficient is

```math
\begin{aligned}
C_1(\ell,m)
={}&
(\ell+1)(m+1)A_\ell A_m\\
&\times
\left[
\frac1{2\ell+2m+1}
-
\frac1{(2\ell+1)(2m+1)}
\right].
\end{aligned}
```

At $(\ell,m)=(1,2)$, this gives $1/210$, agreeing with the independent
calculation in `findings-58.md`.

# 5. Joint logarithmic process limit

For every fixed finite set of lengths $\ell_1,\ldots,\ell_r$, the vector

```math
\sqrt{m_N(s)}
\left(
R_{m_N(s)}^{(\ell_a)}-\theta_{\ell_a}
\right)_{a=1}^r
```

converges to a stationary Gaussian Ornstein-Uhlenbeck process with common
drift rate $1/2$ and stationary covariance matrix

```math
\left(C_1(\ell_a,\ell_b)\right)_{a,b=1}^r.
```

The common rate follows because every route length has a nonzero one-vertex
projection. The route length changes the projection polynomial and covariance
amplitude, but not the support order.

# 6. Infinite-rank route state

The functions

```math
(1-2x)^{2\ell}-\frac1{2\ell+1},
\qquad \ell\geq1,
```

are linearly independent. Indeed, each has a different highest polynomial
degree. Hence the covariance matrices of the first $L$ route observables have
rank $L$.

The complete route hierarchy therefore does not collapse to a fixed
finite-dimensional Gaussian state. Every finite family has a closed
Ornstein-Uhlenbeck limit, but increasing the maximum route length reveals new
independent directions in the latent empirical field.

This is an explicit distinction between finite-observable closure and
universal finite-dimensional closure.

Exact rational calculations confirm:

- the ordered-simplex and compact-binomial forms of $q_\ell$;
- the mean $\theta_\ell$;
- the projection norm and cross-coefficient formulas;
- agreement with the edge and two-step route results;
- full rank of the finite route covariance matrices.
