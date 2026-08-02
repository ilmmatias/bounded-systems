# 1. A continuous ordered-kernel sector

The universal theorem of `findings-56.md` applies to arbitrary extremal
exchangeable DAG kernels. The continuous ordered sector below supplies an
explicit non-block example with exactly computable finite-pattern
coefficients.

Let

```math
(U_i)_{i\geq1},
\qquad
(V_{ij})_{1\leq i<j<\infty}
```

be independent uniform random variables on $[0,1]$. For each pair $i<j$,
place one directed edge from the vertex with smaller $U$-mark to the vertex
with larger $U$-mark when

```math
V_{ij}\leq|U_i-U_j|.
```

No edge is placed otherwise. Every edge follows the strict latent order, so
the resulting directed graph is acyclic almost surely. The law is
exchangeable and dissociated, hence it determines an extremal central
sector.

The conditional edge probability is the continuous kernel

```math
w(x,y)
=
|x-y|.
```

This sector is not equivalent to a finite ordered-block model. Its
conditional expected incident-edge density

```math
q_E(x)
=
\int_0^1|x-y|\,dy
```

has a continuous distribution under $x\sim\operatorname{Uniform}[0,1]$,
whereas a finite block kernel has only finitely many such conditional
values. For a continuous kernel of this kind, exact finite-time recovery of
latent coordinates is generally unavailable.

# 2. Edge-density coefficient

Let $B_{ij}$ be the indicator that the unordered pair $\{i,j\}$ carries an
edge, and define

```math
E_n
=
\frac1{\binom n2}
\sum_{1\leq i<j\leq n}
B_{ij}.
```

The continuum edge density is

```math
\theta_E
=
\mathbb E|U_1-U_2|
=
\frac13.
```

Conditioning on one vertex mark gives

```math
q_E(x)
=
\int_0^1|x-y|\,dy
=
\frac{x^2}{2}
+
\frac{(1-x)^2}{2}
=
x^2-x+\frac12.
```

The first canonical projection is therefore

```math
h_E(x)
=
q_E(x)-\theta_E
=
x^2-x+\frac16.
```

Its squared norm is

```math
\sigma_{E,1}^2
=
\int_0^1h_E(x)^2\,dx
=
\frac1{180}.
```

Because the edge kernel has two vertex positions, its intrinsic order-one
coefficient is

```math
C_1(E,E)
=
4\sigma_{E,1}^2
=
\frac1{45}.
```

## Theorem 1. Edge-density Ornstein-Uhlenbeck limit

With $m_N(s)=\lfloor Ne^s\rfloor$,

```math
\sqrt{m_N(s)}
\left(
E_{m_N(s)}-\frac13
\right)
\Longrightarrow
X_E(s),
```

where $X_E$ is the stationary Ornstein-Uhlenbeck process

```math
dX_E(s)
=
-\frac12X_E(s)\,ds
+
\frac1{\sqrt{45}}\,dW_E(s).
```

Its covariance is

```math
\mathbb E[X_E(s)X_E(t)]
=
\frac1{45}e^{-|s-t|/2}.
```

## Proof

The principal projection is the nonzero one-vertex kernel $h_E$, so the
principal degree is one. The universal process theorem of
`findings-56.md` gives a rate-$1/2$ Gaussian limit with stationary
variance $C_1(E,E)=1/45$. The displayed diffusion coefficient is the one
satisfying the stationary Lyapunov identity for drift $1/2$.

# 3. Exact second-order edge coefficient

The marginal edge indicator is Bernoulli with mean $1/3$, and therefore

```math
\operatorname{Var}(B_{12})
=
\frac29.
```

The two one-vertex projections contribute $2\sigma_{E,1}^2=1/90$. Hence
the total canonical order-two kernel has squared norm

```math
\sigma_{E,2}^2
=
\frac29-\frac1{90}
=
\frac{19}{90}.
```

The exact variance and nested covariance are consequently

```math
\operatorname{Var}(E_n)
=
\frac1{45n}
+
\frac{19}{45n(n-1)},
```

and, for $n\leq m$,

```math
\operatorname{Cov}(E_n,E_m)
=
\frac1{45m}
+
\frac{19}{45m(m-1)}.
```

Thus

```math
C_2(E,E)
=
\frac{19}{45}.
```

After the order-one empirical projection is removed, the remaining edge
statistic has normalization $n$, logarithmic rate one, and stationary
variance $19/45$. Its process law is generally a sum of connected Gaussian
and disconnected Wick components rather than a single Gaussian coordinate.

# 4. Two-step route density

The model also yields an explicit compositional observable. For a
three-element vertex set $S$, write

```math
U_{(1)}<U_{(2)}<U_{(3)}
```

for its ordered marks, and let $H_S$ be the indicator that both adjacent
edges

```math
U_{(1)}\longrightarrow U_{(2)},
\qquad
U_{(2)}\longrightarrow U_{(3)}
```

are present. The possible shortcut from $U_{(1)}$ to $U_{(3)}$ is not
constrained. Define

```math
R_n
=
\frac1{\binom n3}
\sum_{|S|=3}H_S.
```

Conditional on the three marks, the route probability is the product of the
two adjacent gaps. The vector of four spacings determined by three uniform
order statistics has the Dirichlet distribution with all parameters equal
to one. Hence

```math
\theta_R
=
\mathbb E
\left[
(U_{(2)}-U_{(1)})(U_{(3)}-U_{(2)})
\right]
=
\frac1{20}.
```

# 5. One-vertex route projection

Condition on one sampled mark being equal to $x$. The distinguished point
can be the minimum, middle, or maximum of the triple. Direct integration
over the other two points gives the three contributions

```math
q_{R,\min}(x)
=
\frac{x^4}{12}
-
\frac{x^3}{3}
+
\frac{x^2}{2}
-
\frac{x}{3}
+
\frac1{12},
```

the middle-point contribution is

```math
q_{R,\mathrm{mid}}(x)
=
\frac{x^2(1-x)^2}{2},
```

and

```math
q_{R,\max}(x)
=
\frac{x^4}{12}.
```

Their sum is

```math
q_R(x)
=
\frac23x^4
-
\frac43x^3
+x^2
-
\frac13x
+
\frac1{12}.
```

The first route projection is

```math
h_R(x)
=
q_R(x)-\frac1{20},
```

and its squared norm is

```math
\sigma_{R,1}^2
=
\int_0^1h_R(x)^2\,dx
=
\frac1{8100}.
```

Since the route kernel has three vertex positions,

```math
C_1(R,R)
=
9\sigma_{R,1}^2
=
\frac1{900}.
```

## Theorem 2. Path-density Ornstein-Uhlenbeck limit

The route density satisfies

```math
\sqrt{m_N(s)}
\left(
R_{m_N(s)}-\frac1{20}
\right)
\Longrightarrow
X_R(s),
```

where

```math
dX_R(s)
=
-\frac12X_R(s)\,ds
+
\frac1{30}\,dW_R(s),
```

and

```math
\mathbb E[X_R(s)X_R(t)]
=
\frac1{900}e^{-|s-t|/2}.
```

This is an explicit path-sensitive continuum law in a continuous extremal
sector.

# 6. Joint edge-route process

The leading edge and route modes are driven by the same empirical vertex
field, since both respond to the location of one distinguished vertex in
the latent order. Their one-vertex inner product is

```math
\int_0^1h_E(x)h_R(x)\,dx
=
\frac1{1260}.
```

The orbit coefficients are two and three, so

```math
C_1(E,R)
=
6\int_0^1h_E(x)h_R(x)\,dx
=
\frac1{210}.
```

Therefore the vector

```math
\sqrt{m_N(s)}
\begin{pmatrix}
E_{m_N(s)}-1/3\\
R_{m_N(s)}-1/20
\end{pmatrix}
```

converges to the stationary two-dimensional Ornstein-Uhlenbeck process

```math
dX(s)
=
-\frac12X(s)\,ds
+
C^{1/2}dW(s),
```

with stationary covariance matrix

```math
C
=
\begin{pmatrix}
1/45 & 1/210\\
1/210 & 1/900
\end{pmatrix}.
```

The determinant is

```math
\det C
=
\frac1{496125}>0,
```

so the two continuum observables are correlated but not linearly redundant.

The kernel sector is infinite-dimensional, while any finite family of
relational observables has an exact finite covariance matrix and a joint
continuum process.

# 7. Exact rational verification

Exact rational calculations confirm:

- the edge mean and one-vertex projection;
- the edge order-one and order-two coefficients;
- the three conditional route integrals;
- the route mean and projection norm;
- the edge-route cross coefficient;
- positivity of the joint covariance matrix.
