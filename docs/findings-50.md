# 1. Stochastic ordered block sectors

The stochastic two-layer construction extends to finitely many ordered latent layers without sacrificing exchangeability or exact acyclicity. Fix an integer $q\geq2$, a probability vector

```math
p=(p_1,\ldots,p_q),
\qquad
p_i>0,
\qquad
\sum_{i=1}^q p_i=1,
```

and cross-layer edge parameters

```math
W=(w_{ij})_{1\leq i<j\leq q},
\qquad
0\leq w_{ij}\leq1.
```

Let $(A_v)_{v\geq1}$ be independent layer marks with law $p$. Conditional on the marks, place each possible edge between distinct layers independently: if $A_u=i<A_v=j$, place $u\to v$ with probability $w_{ij}$, and if $A_v=i<A_u=j$, place $v\to u$ with the same probability. No edge is placed within a layer.

Every edge points from a lower layer to a higher layer, so the resulting infinite directed graph $X_{p,W}$ is acyclic. Write

```math
G_n=X_{p,W}|_{[n]}.
```

## Proposition 1. Extremal centrality

The law of $X_{p,W}$ is exchangeable and dissociated. It therefore determines an extremal central measure on the DAG branching graph.

## Proof

A finite permutation of the vertices permutes the independent mark variables and pair variables without changing their joint law. Restrictions to disjoint vertex sets depend on disjoint collections of those variables and are therefore independent. The central-exchangeable correspondence for extremal sectors gives the result.

The sector is represented by a finite ordered directed kernel. Partition $[0,1]$ into intervals of lengths $p_1,\ldots,p_q$; for points in blocks $i<j$, place the directed edge from block $i$ to block $j$ with probability $w_{ij}$.

# 2. Exact latent coefficients

Let

```math
C_{n,i}=\sum_{v=1}^n\mathbf 1\{A_v=i\},
\qquad
Z_{n,i}=\frac{C_{n,i}}n,
```

and set $Z_n=(Z_{n,1},\ldots,Z_{n,q})$. If $I_{n+1}=\mathbf e_{A_{n+1}}$, then

```math
(n+1)(Z_{n+1}-Z_n)=I_{n+1}-Z_n.
```

Consequently, with

```math
\Sigma_p=\operatorname{diag}(p)-pp^{\mathsf T},
```

the exact scaled drift and covariance are

```math
b(z)=p-z,
\qquad
a(z)=\Sigma_p.
```

The logarithmic-size hydrodynamic equation is therefore

```math
\frac{dz}{ds}=p-z,
```

and the stationary fluctuation process on

```math
H_q=\left\{x\in\mathbb R^q:\sum_i x_i=0\right\}
```

is

```math
dY_s=-\frac12Y_s\,ds+\Sigma_p^{1/2}\,dW_s.
```

As in the deterministic ordered-layer sector, the coefficient fields are exact and independent of $n$. The new issue is that the finite graph generally does not reveal $Z_n$.

# 3. First projections of finite DAG observables

Let $F$ be a finite DAG on $k$ vertices. Conditional on a mark vector $a=(a_1,\ldots,a_k)\in[q]^k$, define

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

The kernel $\psi_F$ is symmetric in its arguments because the event is unlabeled. Its continuum density is

```math
P_F(p,W)=
\mathbb E
\left[
\psi_F(A_1,\ldots,A_k)
\right].
```

For a distinguished vertex of layer $i$, set

```math
q_F(i)=
\mathbb E
\left[
\psi_F(i,A_2,\ldots,A_k)
\right].
```

Then

```math
P_F(p,W)=\sum_{i=1}^q p_iq_F(i).
```

The quantity $q_F(i)-P_F$ is the first Hoeffding projection of the pattern event. It measures the predictive effect of knowing the layer of one observed vertex.

## Theorem 2. Generic cylinder fluctuation mode

For every finite collection $F_1,\ldots,F_d$, define

```math
V_{N,r}(s)=
\sqrt{m_N(s)}
\left(
T_{F_r}(G_{m_N(s)})-P_{F_r}(p,W)
\right),
\qquad
m_N(s)=\lfloor Ne^s\rfloor.
```

The vector process $V_N$ converges to

```math
V_r(s)=k_r q_{F_r}^{\mathsf T}Y(s),
```

where $k_r=|F_r|$. Its covariance is

```math
\mathbb E[V_r(s)V_t(u)]
=
 e^{-|s-u|/2}
 k_rk_t
\left[
\sum_{i=1}^q p_iq_{F_r}(i)q_{F_t}(i)
-
P_{F_r}P_{F_t}
\right].
```

Equivalently, every nondegenerate first-order cylinder mode has logarithmic relaxation rate $1/2$.

## Proof

Condition on all layer marks. The conditional expectation of $T_F(G_n)$ is the bounded $U$-statistic with kernel $\psi_F$. Its first Hoeffding projection is

```math
\frac{k}{n}
\sum_{v=1}^n
\left(
q_F(A_v)-P_F
\right).
```

The remaining mark kernel is degenerate of order at least two and has variance $O(n^{-2})$.

The difference between the graph statistic and its conditional expectation also has variance $O(n^{-2})$. Indeed, two induced-pattern indicators use disjoint edge variables whenever their vertex sets intersect in at most one vertex. Conditional covariances can therefore occur only for pairs of $k$-sets with overlap at least two, whose proportion is $O(n^{-2})$.

It follows that

```math
\sqrt n
\left(
T_F(G_n)-P_F
\right)
-
\frac{k}{\sqrt n}
\sum_{v=1}^n
\left(
q_F(A_v)-P_F
\right)
\longrightarrow0
```

in $L^2$. The sequential Hoeffding decomposition gives the same approximation uniformly on compact size intervals. Applying the invariance principle to the empirical mark process and then the logarithmic time change gives

```math
V_F(s)=kq_F^{\mathsf T}Y(s).
```

Since $Y$ has covariance $e^{-|s-u|/2}\Sigma_p$, the displayed covariance follows from

```math
q_F^{\mathsf T}\Sigma_pq_K
=
\sum_i p_iq_F(i)q_K(i)-P_FP_K.
```

This result isolates the graph-observable first-order coefficient without assuming that the latent layers are recoverable from the finite graph.

# 4. Route-density hierarchy

For $r\geq1$, let $\mathcal R_{r,n}$ be the fraction of $(r+1)$-element vertex subsets whose induced graph contains a directed route visiting all selected vertices. In an ordered block sector, such a route exists only when the selected marks are strictly increasing, and then its required consecutive edges are unique.

The continuum route density is therefore

```math
\tau_r(p,W)
=
(r+1)!
\sum_{1\leq i_0<\cdots<i_r\leq q}
\left(
\prod_{a=0}^r p_{i_a}
\right)
\left(
\prod_{a=1}^r w_{i_{a-1},i_a}
\right).
```

This formula gives a path-sensitive continuum coordinate rather than an endpoint or edge-density coordinate. It detects products of edge probabilities along composable layer chains.

The first nontrivial case is the two-step route density

```math
R_n=\mathcal R_{2,n}.
```

Its continuum value is

```math
\tau(p,W)
=
6
\sum_{i<j<k}
p_ip_jp_k w_{ij}w_{jk}.
```

For a distinguished layer $a$, the conditional route probability is

```math
\begin{aligned}
q_R(a)=2\Bigg[&
\sum_{a<j<k}
p_jp_k w_{aj}w_{jk}
+
\sum_{i<a<k}
p_ip_k w_{ia}w_{ak}\\
&+
\sum_{i<j<a}
p_ip_j w_{ij}w_{ja}
\Bigg].
\end{aligned}
```

The three sums correspond respectively to the distinguished vertex acting as the lower endpoint, middle vertex, or upper endpoint of the route.

## Corollary 3. Generic route Ornstein-Uhlenbeck limit

If $q_R$ is not constant on the support of $p$, then

```math
\sqrt{m_N(s)}
\left(
R_{m_N(s)}-\tau(p,W)
\right)
\Longrightarrow
3q_R^{\mathsf T}Y(s).
```

The stationary variance is

```math
9
\left[
\sum_a p_aq_R(a)^2-\tau(p,W)^2
\right],
```

and the logarithmic relaxation rate is $1/2$.

# 5. Three layers and first-order degeneracy

Now take $q=3$ and write

```math
a=w_{12},
\qquad
b=w_{23}.
```

The parameter $w_{13}$ does not affect the number of two-step routes. The continuum route density is

```math
\tau=6abp_1p_2p_3,
```

and the conditional probabilities are

```math
q_R(1)=2abp_2p_3,
\qquad
q_R(2)=2abp_1p_3,
\qquad
q_R(3)=2abp_1p_2.
```

## Proposition 4. Unique interior degeneracy

Assume $a,b>0$ and $p_i>0$. The first route projection vanishes if and only if

```math
p_1=p_2=p_3=\frac13.
```

## Proof

The first projection vanishes precisely when $q_R(1)=q_R(2)=q_R(3)$. Since $2abp_1p_2p_3>0$, these equalities reduce to

```math
p_1=p_2=p_3.
```

Normalization gives the stated value.

Thus the equal-layer sector is not merely a convenient symmetric example. It is the unique interior point at which the two-step route loses its $\sqrt n$ fluctuation mode.

# 6. Exact decomposition of the route count

Let $V_i(n)$ be the layer-$i$ vertices among $[n]$, and write $C_{n,i}=|V_i(n)|$. Let

```math
E_{12,n}
=
\sum_{u\in V_1(n)}
\sum_{v\in V_2(n)}
B^{12}_{uv},
```

and define $E_{23,n}$ analogously. Their centered residuals are

```math
N_{12,n}=E_{12,n}-aC_{n,1}C_{n,2},
```

and

```math
N_{23,n}=E_{23,n}-bC_{n,2}C_{n,3}.
```

For $v\in V_2(n)$, set

```math
X_v=
\sum_{u\in V_1(n)}
\left(B^{12}_{uv}-a\right),
\qquad
Y_v=
\sum_{w\in V_3(n)}
\left(B^{23}_{vw}-b\right).
```

The number $L_n$ of directed two-step routes is

```math
L_n=
\sum_{v\in V_2(n)}
\left(aC_{n,1}+X_v\right)
\left(bC_{n,3}+Y_v\right).
```

Hence the exact decomposition is

```math
\begin{aligned}
L_n={}&
abC_{n,1}C_{n,2}C_{n,3}
+bC_{n,3}N_{12,n}\\
&+aC_{n,1}N_{23,n}
+Q_n,
\end{aligned}
```

where

```math
Q_n=\sum_{v\in V_2(n)}X_vY_v.
```

The route density is

```math
R_n=\frac{L_n}{\binom n3}.
```

## Proposition 5. Negligibility of the bilinear residual

With respect to the natural vertex-exposure filtration, $(Q_n)$ is a martingale and

```math
\mathbb E[Q_n^2\mid A_1,\ldots,A_n]
=
a(1-a)b(1-b)
C_{n,1}C_{n,2}C_{n,3}.
```

Consequently, for every finite $S>0$,

```math
\sup_{0\leq s\leq S}
\frac{|Q_{m_N(s)}|}{m_N(s)^2}
\longrightarrow0
```

in probability.

## Proof

When a new vertex is exposed, every new contribution to $Q_n-Q_{n-1}$ contains at least one newly revealed centered edge residual. Its conditional expectation is therefore zero, so $Q_n$ is a martingale.

Conditional on the marks, the pairs $(X_v,Y_v)$ are independent across $v\in V_2(n)$, and $X_v$ is independent of $Y_v$. Therefore

```math
\operatorname{Var}(X_v\mid A)=
a(1-a)C_{n,1},
```

and

```math
\operatorname{Var}(Y_v\mid A)=
b(1-b)C_{n,3}.
```

Summing the product variances over the $C_{n,2}$ middle vertices gives the displayed identity. In particular, $\mathbb E[Q_n^2]=O(n^3)$. Doob's maximal inequality then gives

```math
\mathbb E
\left[
\sup_{m\leq Ne^S}
|Q_m|^2
\right]
=O(N^3),
```

which becomes $O(N^{-1})$ after division by $N^4$.

# 7. Pair-noise processes

For $ij\in\{12,23\}$, define the all-pair normalized residual

```math
U_{ij,n}=\frac{N_{ij,n}}{\binom n2},
```

and its logarithmic-size process

```math
Z_{ij,N}(s)=m_N(s)U_{ij,m_N(s)}.
```

## Theorem 6. Joint latent and pair-noise limit

The vector

```math
\left(
Y_N,Z_{12,N},Z_{23,N}
\right)
```

converges jointly to independent processes $(Y,Z_{12},Z_{23})$, where

```math
dY_s=-\frac12Y_s\,ds+
\Sigma_p^{1/2}\,dW_s^{(0)},
```

and

```math
dZ_{12,s}=-Z_{12,s}\,ds+
\sqrt{8p_1p_2a(1-a)}\,dW_s^{(12)},
```

and the second edge-noise coordinate satisfies

```math
dZ_{23,s}=-Z_{23,s}\,ds+
\sqrt{8p_2p_3b(1-b)}\,dW_s^{(23)}.
```

The Brownian drivers are mutually independent.

## Proof

The centered block-edge counts are martingales under vertex exposure. Their predictable quadratic variations satisfy

```math
\frac1{N^2}
\left\langle
N_{ij}
\right\rangle_{\lfloor Nt\rfloor}
\longrightarrow
p_ip_jw_{ij}(1-w_{ij})t^2.
```

The bounded increments satisfy the martingale Lindeberg condition. Distinct block residuals have zero predictable cross variation because every cross product contains independent centered edge variables. Their predictable cross variations with the empirical mark martingale also vanish. The multivariate martingale functional central limit theorem therefore gives independent time-changed Brownian limits in ordinary size time. Multiplication by $2e^{-s}$ after the change $t=e^s$ yields the displayed Ornstein-Uhlenbeck equations.

# 8. Symmetric two-step route limit

Assume from now on that

```math
p_1=p_2=p_3=\frac13.
```

Let

```math
Y_N(s)=
\sqrt{m_N(s)}
\left(
Z_{m_N(s)}-\frac13\mathbf 1
\right).
```

The conditional-mean part of the route density satisfies

```math
\frac{abC_{n,1}C_{n,2}C_{n,3}}{\binom n3}
\longrightarrow
\frac{2ab}{9}.
```

Because the coordinates of $Y_N$ sum to zero, the first-order term cancels exactly. Expanding the product gives

```math
n
\left[
\frac{abC_{n,1}C_{n,2}C_{n,3}}{\binom n3}
-
\frac{2ab}{9}
\right]
\Longrightarrow
\frac{2ab}{3}-ab\|Y(s)\|^2.
```

The two linear edge-noise terms in the exact decomposition satisfy

```math
n
\frac{bC_{n,3}N_{12,n}}{\binom n3}
\Longrightarrow
bZ_{12}(s),
```

and

```math
n
\frac{aC_{n,1}N_{23,n}}{\binom n3}
\Longrightarrow
aZ_{23}(s).
```

Proposition 5 removes the bilinear residual.

## Theorem 7. Path-sensitive second-order continuum limit

For every finite $S>0$,

```math
m_N(s)
\left(
R_{m_N(s)}-\frac{2ab}{9}
\right)
\Longrightarrow
V(s)
```

in $D([0,S])$, where

```math
V(s)=
\frac{2ab}{3}
-ab\|Y(s)\|^2
+bZ_{12}(s)
+aZ_{23}(s).
```

Here $Y$ is the stationary two-dimensional Ornstein-Uhlenbeck process on $H_3$ with covariance matrix

```math
\Sigma_{1/3}
=
\frac13I-\frac19\mathbf 1\mathbf 1^{\mathsf T},
```

while $Z_{12}$ and $Z_{23}$ are independent rate-one Ornstein-Uhlenbeck processes with stationary variances

```math
\operatorname{Var}(Z_{12})=
\frac{4a(1-a)}9,
```

and

```math
\operatorname{Var}(Z_{23})=
\frac{4b(1-b)}9.
```

The process $V$ is non-Gaussian whenever $ab>0$. Its covariance is

```math
\mathbb E[V(s)V(t)]
=
\frac49ab(a+b-ab)e^{-|s-t|}.
```

## Proof

The exact route decomposition and the preceding convergence statements give the process limit. The quadratic mark term is centered because

```math
\mathbb E\|Y(s)\|^2
=\operatorname{tr}(\Sigma_{1/3})
=\frac23.
```

For a centered Gaussian vector process with

```math
\mathbb E[Y(s)Y(t)^{\mathsf T}]
=e^{-|s-t|/2}\Sigma_{1/3},
```

Wick's formula gives

```math
\operatorname{Cov}
\left(
\|Y(s)\|^2,
\|Y(t)\|^2
\right)
=
2e^{-|s-t|}
\operatorname{tr}(\Sigma_{1/3}^2)
=
\frac49e^{-|s-t|}.
```

The pair-noise processes are independent of $Y$ and of one another. Adding their covariance contributions gives

```math
\frac49
\left[
a^2b^2
+ab^2(1-a)
+a^2b(1-b)
\right]
e^{-|s-t|},
```

which simplifies to the displayed coefficient.

# 9. Overlap order and path observables

The two-step route now exhibits both established fluctuation orders in a genuinely compositional observable.

Away from equal layer weights, its first projection is nonzero and the route density has a $\sqrt n$ Gaussian mode with logarithmic relaxation rate $1/2$. At equal layer weights, that projection vanishes, and the $n$-scale limit combines a quadratic empirical-mark term with two centered edge-noise modes. Every surviving covariance decays at rate $1$.

Thus, for a path-sensitive DAG coordinate, a first nonvanishing overlap of order $j$ produces logarithmic relaxation rate $j/2$ at the established orders $j=1$ and $j=2$.

The result also separates two distinct sources of second-order behavior. The term

```math
\frac{2ab}{3}-ab\|Y\|^2
```

comes from a degenerate projection of the latent empirical measure, whereas

```math
bZ_{12}+aZ_{23}
```

comes from irreducible edge randomness. They share the same relaxation rate because both belong to overlap order two, but one is Gaussian chaos and the other is Gaussian pair noise.

# 10. Path-observable consequences

The stochastic ordered block sectors now connect extremal central DAG laws and ordered directed kernels to stable route densities, first-projection coefficients, and path-sensitive functional limits.

The remaining closure problem has become more precise. The latent simplex is finite-dimensional and exactly Markov, while graph observables inherit stable coefficients through their predictive projections. A graph-intrinsic closure theorem would have to show that a finite or projective family of observed rooted densities consistently reconstructs the relevant quantities

```math
p_i,
\qquad
w_{ij},
\qquad
q_F(i),
```

up to the natural block symmetries. That is an identifiability and posterior-concentration problem rather than a continuum-existence problem.

The next useful target is therefore the graph-intrinsic recovery of the three-layer parameters from finite induced densities and rooted extension statistics. Once this is proved, the stable coefficient fields above can be expressed in observable coordinates rather than latent ones.

# 11. Literature relation

The first-projection argument is the classical Hoeffding decomposition for bounded $U$-statistics. The sequential form used for the process limit is the corresponding functional invariance principle. Degenerate higher-order terms are naturally described by the theory of Gaussian chaoses and degenerate $U$-statistics.

The present calculation differs from an ordinary vertex-sampled $U$-statistic because the graph also contains independent pair variables. The overlap decomposition shows exactly how this additional randomness enters: one-vertex overlaps carry the latent empirical mode, while shared edges first appear at two-vertex overlap. This produces the separate rate-$1/2$ and rate-$1$ logarithmic modes derived above.
