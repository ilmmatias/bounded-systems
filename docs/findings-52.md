# 1. Canonical projections of finite relational statistics

The explicit ordered-layer sectors exhibit logarithmic relaxation rates $1/2$
and $1$. These rates are not isolated features of the chosen edge and route
coordinates; they are the first two levels of the Hoeffding decomposition of a
finite relational statistic.

Let $(A_v)_{v\geq1}$ be independent variables taking values in a finite set
$\mathcal A$ with law $p$. Let

```math
h:\mathcal A^k\longrightarrow\mathbb R
```

be a bounded symmetric kernel, and define

```math
\theta=\mathbb E[h(A_1,\ldots,A_k)].
```

For a subset $S\subseteq[j]$, write

```math
h_S(x_S)
=
\mathbb E
\left[
h(A_1,\ldots,A_k)
\mid
A_i=x_i,
\ i\in S
\right].
```

The order-$j$ canonical projection is

```math
\pi_jh(x_1,\ldots,x_j)
=
\sum_{S\subseteq[j]}
(-1)^{j-|S|}h_S(x_S).
```

The empty-set term is $h_\varnothing=\theta$.

## Proposition 1. Canonical degeneracy

For every $j\geq1$, every coordinate $r\leq j$, and every fixed choice of the
other arguments,

```math
\mathbb E
\left[
\pi_jh(x_1,\ldots,x_{r-1},A_r,x_{r+1},\ldots,x_j)
\right]
=0.
```

The projections give the pointwise decomposition

```math
h(x_1,\ldots,x_k)-\theta
=
\sum_{j=1}^k
\sum_{\substack{S\subseteq[k]\\|S|=j}}
\pi_jh(x_S).
```

## Proof

Averaging the inclusion-exclusion formula over one coordinate pairs every
subset containing that coordinate with the corresponding subset omitting it.
The two conditional expectations agree after the averaging and enter with
opposite signs. This proves degeneracy.

The pointwise identity is the Möbius inversion formula on the Boolean lattice
of coordinate subsets.

# 2. Exact Hoeffding decomposition

Define the order-$k$ $U$-statistic

```math
U_n(h)
=
\frac1{\binom nk}
\sum_{\substack{S\subseteq[n]\\|S|=k}}
h(A_S).
```

For a symmetric $j$-variable kernel $g$, write

```math
U_{n,j}(g)
=
\frac1{\binom nj}
\sum_{\substack{S\subseteq[n]\\|S|=j}}
g(A_S).
```

## Theorem 2. Exact support-order decomposition

For every $n\geq k$,

```math
U_n(h)-\theta
=
\sum_{j=1}^k
\binom kj
U_{n,j}(\pi_jh).
```

The summands are pairwise orthogonal in $L^2$. If

```math
\sigma_j^2
=
\mathbb E
\left[
\pi_jh(A_1,\ldots,A_j)^2
\right],
```

then

```math
\operatorname{Var}
\left(
U_{n,j}(\pi_jh)
\right)
=
\frac{\sigma_j^2}{\binom nj}.
```

More generally, for $n\leq m$,

```math
\operatorname{Cov}
\left(
U_{n,j}(\pi_jh),
U_{m,j}(\pi_jh)
\right)
=
\frac{\sigma_j^2}{\binom mj}.
```

## Proof

Average the pointwise decomposition of Proposition 1 over all $k$-subsets of
$[n]$. A fixed $j$-subset is contained in exactly

```math
\binom{n-j}{k-j}
```

of those $k$-subsets. Dividing by $\binom nk$ gives the coefficient

```math
\frac{\binom{n-j}{k-j}}{\binom nk}
=
\frac{\binom kj}{\binom nj},
```

which proves the decomposition.

For two canonical kernel evaluations on vertex sets $S$ and $T$, the
covariance vanishes unless $S=T$. If $S\neq T$, one of the sets contains a
vertex absent from the other; averaging over that variable annihilates the
corresponding canonical kernel. The same argument shows orthogonality between
different projection orders.

The variance therefore receives one contribution from each of the $\binom nj$
diagonal pairs. For $n\leq m$, exactly the $\binom nj$ common $j$-subsets
contribute to the cross covariance, giving the displayed formula.

This exact covariance identity already contains the logarithmic relaxation
spectrum.

# 3. Sequential chaos limits

Let

```math
m_N(s)=\lfloor Ne^s\rfloor,
\qquad
0\leq s\leq S.
```

For each projection order $j$, define

```math
X_{j,N}(s)
=
\binom kj
m_N(s)^{j/2}
U_{m_N(s),j}(\pi_jh).
```

Let $\mathcal W$ be a Gaussian random measure on

```math
[0,\infty)\times\mathcal A
```

with control measure $dt\otimes p$. For a canonical kernel $g$ of order $j$,
let

```math
I_j(t;g)
```

denote the order-$j$ multiple Wiener-Itô integral of

```math
\mathbf 1_{[0,t]}^{\otimes j}g
```

with respect to $\mathcal W$.

## Theorem 3. Hoeffding-Lamperti limit

For every finite collection of projection orders, the processes $X_{j,N}$
converge jointly in the Skorohod topology to

```math
X_j(s)
=
\binom kj
 e^{-js/2}
 I_j(e^s;\pi_jh).
```

The process $X_j$ is stationary, belongs to the $j$-th Wiener chaos, and has
covariance

```math
\mathbb E[X_j(s)X_j(t)]
=
\binom kj^2
j!\sigma_j^2
 e^{-j|s-t|/2}.
```

Processes of different orders are orthogonal in $L^2$, although they need not
be probabilistically independent because they are built from the same
Gaussian random measure.

## Proof

The functional limit theorem for canonical $U$-statistics gives

```math
N^{-j/2}
\sum_{1\leq i_1<\cdots<i_j\leq\lfloor Nt\rfloor}
\pi_jh(A_{i_1},\ldots,A_{i_j})
\Longrightarrow
\frac1{j!}I_j(t;\pi_jh).
```

Since

```math
\binom{\lfloor Nt\rfloor}{j}
\sim
\frac{N^jt^j}{j!},
```

multiplication by $\lfloor Nt\rfloor^{j/2}$ converts the limit to

```math
t^{-j/2}I_j(t;\pi_jh).
```

Setting $t=e^s$ gives the displayed Lamperti form.

The Wiener-Itô isometry gives, for $s\leq t$,

```math
\mathbb E
\left[
I_j(e^s;\pi_jh)
I_j(e^t;\pi_jh)
\right]
=
j!e^{js}\sigma_j^2.
```

Multiplication by $e^{-j(s+t)/2}$ yields the covariance. Stationarity follows
because all finite joint moments of multiple Gaussian integrals depend only on
logarithmic time differences after this normalization.

The exact finite covariance from Theorem 2 gives the same limit directly:

```math
\begin{aligned}
&\operatorname{Cov}
\left(
 n^{j/2}U_{n,j},
 m^{j/2}U_{m,j}
\right)\\
&\qquad=
\frac{n^{j/2}m^{j/2}}{\binom mj}
\sigma_j^2
\longrightarrow
j!\sigma_j^2
\left(\frac nm\right)^{j/2}.
\end{aligned}
```

For $n/m\to e^{-(t-s)}$, this is exactly the rate $j/2$.

# 4. First nonvanishing projection

Define the Hoeffding rank of $h$ at $p$ by

```math
r(h)
=
\min
\left\{
j\geq1:\sigma_j^2>0
\right\}.
```

If every projection vanishes, the kernel is constant almost surely.

## Corollary 4. Scale and relaxation selected by Hoeffding rank

If $r=r(h)$, then

```math
m_N(s)^{r/2}
\left(
U_{m_N(s)}(h)-\theta
\right)
\Longrightarrow
X_r(s).
```

All higher projection orders vanish under this normalization. The limiting
process lies in the $r$-th Wiener chaos and has covariance proportional to

```math
 e^{-r|s-t|/2}.
```

Thus

```math
\boxed{
\text{first nonvanishing support order }r
\Longrightarrow
n^{r/2}\text{ normalization}
\Longrightarrow
\text{logarithmic relaxation rate }\frac r2
}
```

for every bounded finite-state $U$-statistic.

The limit is Gaussian only for $r=1$. For $r\geq2$, it is generally a
non-Gaussian Gaussian-chaos process.

# 5. Application to ordered-layer pattern densities

In a stochastic ordered block sector, let $F$ be a $k$-vertex DAG pattern and
retain the conditional mark kernel

```math
\psi_F(a_1,\ldots,a_k)
=
\mathbb P
\left(
X_{p,W}|_{[k]}\cong F
\mid
A_1=a_1,\ldots,A_k=a_k
\right).
```

The conditional expectation of the observed pattern density is the $U$-statistic

```math
\mathbb E
\left[
T_F(G_n)
\mid
A_1,\ldots,A_n
\right]
=
U_n(\psi_F).
```

Theorem 3 therefore gives a complete orthogonal relaxation spectrum for its
latent empirical component:

```math
\frac12,
1,
\frac32,
\ldots,
\frac k2.
```

The first projection is exactly the predictive layer coefficient from the
ordered-layer analysis:

```math
\pi_1\psi_F(i)
=
q_F(i)-P_F.
```

If this projection is nonzero, the generic $\sqrt n$ Gaussian mode dominates.
If it vanishes, the next nonzero projection determines both the normalization
and the logarithmic decay.

The actual graph statistic also contains edge-variable fluctuations around its
conditional expectation. Those components begin at support order two because
an edge is attached to two vertices. The stochastic edge and route
calculations already prove that their order-two modes have rate $1$. A full
generalized Hoeffding decomposition for all vertex and edge variables would
extend Theorem 3 from the conditional mark statistic to the complete graph
statistic at every support order. In that extension the index is the number of
vertices supporting a canonical component rather than the number of primitive
random variables: a centered edge variable has support order two, a triangle
of centered edges has support order three, and a general connected edge-noise
monomial is indexed by the size of its incident vertex set. The natural
extension assigns logarithmic rate $j/2$ to every canonical component
supported on $j$ vertices.

# 6. Two-step route projection

Consider the three-layer two-step route kernel. Conditional on three marks,
the route probability is

```math
h_R(a_1,a_2,a_3)
=
\begin{cases}
ab,
&\{a_1,a_2,a_3\}=\{1,2,3\},\\
0,
&\text{otherwise}.
\end{cases}
```

At equal layer weights,

```math
p_1=p_2=p_3=\frac13,
```

the first projection vanishes:

```math
\pi_1h_R=0.
```

The second projection is nonzero, and its squared norm is

```math
\sigma_2^2
=
\frac{2a^2b^2}{81}.
```

Since $\binom32=3$, Theorem 3 gives stationary variance

```math
\binom32^2 2!\sigma_2^2
=
\frac{4a^2b^2}{9}.
```

This is exactly the variance of the quadratic mark component

```math
\frac{2ab}{3}-ab\|Y\|^2
```

in the path-sensitive limit derived previously. Its covariance decays as

```math
 e^{-|s-t|},
```

confirming that the quadratic term is the canonical order-two route projection
rather than an accidental Taylor correction.

The remaining order-two variance in the full route statistic comes from the
centered $12$ and $23$ edge variables. The complete second-order coefficient
is therefore the orthogonal sum of the canonical mark projection and the
pair-noise projections.

# 7. Spectral interpretation

The empirical mark process has the rate-$1/2$ Ornstein-Uhlenbeck generator.
Its $j$-th Wiener chaos is an eigenspace of the second-quantized generator
with eigenvalue

```math
\frac j2.
```

The support-order decomposition is therefore simultaneously:

- the Hoeffding decomposition of a finite relational statistic;
- the overlap decomposition of its covariance;
- the normalization hierarchy $n^{j/2}$;
- the Wiener-chaos decomposition of its continuum limit;
- the logarithmic relaxation spectrum $j/2$.

They are equivalent descriptions of the same orthogonal structure in the
finite ordered-layer sectors.

# 8. Stable coefficients by support order

The stable-coefficient problem now has an exact hierarchy. For a finite
pattern kernel $h$, define

```math
C_j(h)
=
\binom kj^2j!\sigma_j^2.
```

The coefficient $C_j(h)$ is the stationary variance of the order-$j$
continuum component. It is finite, nonnegative, and computable directly from
the finite conditional kernel.

For two kernels $h$ and $g$, the cross coefficient is

```math
C_j(h,g)
=
\binom kj
\binom \ell j
j!
\mathbb E
\left[
\pi_jh(A_1,\ldots,A_j)
\pi_jg(A_1,\ldots,A_j)
\right].
```

The corresponding logarithmic cross covariance is

```math
C_j(h,g)e^{-j|s-t|/2}.
```

Thus the full finite-pattern coefficient problem in a recovered ordered block
sector reduces to finite sums over the layer alphabet. No phenomenological
fitting or continuum approximation is required.

# 9. Literature relation

The orthogonal decomposition is the classical Hoeffding decomposition of
$U$-statistics. Sequential weak convergence of $U$-statistics was developed by
Miller and Sen, and the general multiple-Wiener-integral limits of symmetric
statistics were developed by Dynkin and Mandelbaum. The logarithmic stationary
form used here is the Lamperti transform of those self-similar sequential
limits.

The contribution of the present construction is the identification of
Hoeffding order with overlap order and logarithmic relaxation in the
relational growth setting, together with explicit graph and route sectors in
which both the mark and edge-supported coefficients can be computed exactly.
