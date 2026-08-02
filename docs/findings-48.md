# 1. Finite ordered-layer sectors

The general central boundary from the preceding construction is large. A
first process-level continuum theorem should therefore be proved on a
nontrivial family for which the central law, macroscopic state, coefficient
fields, and fluctuation scaling are all explicit.

Fix an integer $q\geq2$ and a probability vector

```math
p=(p_1,\ldots,p_q),
\qquad
p_i>0,
\qquad
\sum_{i=1}^q p_i=1.
```

Let $(A_j)_{j\geq1}$ be independent random variables with

```math
\mathbb P(A_j=i)=p_i.
```

Define a directed graph $X_p$ on $\mathbb N$ by placing the edge

```math
u\longrightarrow v
```

exactly when

```math
A_u<A_v.
```

Vertices with the same mark form an antichain. Every vertex in layer $i$
points to every vertex in layer $j$ when $i<j$. The graph is therefore
acyclic and transitive. Its restriction to $[n]$ will be denoted by

```math
G_n=X_p|_{[n]}.
```

The layer counts and proportions are

```math
C_{n,i}=\sum_{j=1}^n\mathbf 1\{A_j=i\},
\qquad
Z_{n,i}=\frac{C_{n,i}}n.
```

We write

```math
C_n=(C_{n,1},\ldots,C_{n,q}),
\qquad
Z_n=(Z_{n,1},\ldots,Z_{n,q}).
```

# 2. Centrality and graph observability

## Proposition 1. Ordered-layer extremal sectors

The law of $X_p$ is exchangeable, dissociated, and supported on infinite
DAGs. It therefore determines an extremal central measure on the DAG
multiplicity branching graph.

Moreover, with probability one there is a finite random level $\tau$ such
that $C_n$, and hence $Z_n$, is determined by the unlabeled graph $G_n$ for
every $n\geq\tau$.

## Proof

Exchangeability follows because a finite permutation of the vertices only
permutes the independent marks. Restrictions to disjoint vertex sets are
functions of disjoint collections of marks and are therefore independent. The
law is dissociated and hence extremal under the central-exchangeable
correspondence.

Two vertices of $G_n$ are nonadjacent exactly when they have the same mark.
Thus nonadjacency partitions the graph into its nonempty layers, and the
directions of the edges totally order those layers. Since every $p_i$ is
positive, every mark appears after a finite random time almost surely. After
that time, the ordered nonadjacency classes recover the complete vector
$C_n$.

The finite exceptional interval before all layers appear does not affect any
asymptotic statement below.

# 3. Deterministic continuum kernel

Partition $[0,1]$ into consecutive intervals $I_1,\ldots,I_q$ with Lebesgue
measures

```math
\lambda(I_i)=p_i.
```

Define the ordered step kernel

```math
W_p(x,y)=
\mathbf 1
\left\{
 x\in I_i,
 y\in I_j,
 i<j
\right\}.
```

Sampling independent uniform points $U_j\in[0,1]$ and assigning mark $i$ when
$U_j\in I_i$ reproduces $X_p$. Thus $W_p$ is a deterministic continuum
representative of the extremal sector.

A finite DAG belongs to the support of this sector precisely when it is a
complete ordered multipartite DAG. Such a graph is determined by a
composition

```math
m=(m_1,\ldots,m_r),
\qquad
m_j\geq1,
\qquad
m_1+\cdots+m_r=k.
```

Write $F_m$ for the $k$-vertex DAG whose vertices are partitioned into
ordered antichains of sizes $m_1,\ldots,m_r$, with every edge directed from
an earlier block to a later block.

## Proposition 2. Exact finite pattern formula

For every $F_m$ as above,

```math
T_{F_m}(G_n)=
\frac{k!}{(n)_k\prod_{a=1}^r m_a!}
\sum_{1\leq i_1<\cdots<i_r\leq q}
\prod_{a=1}^r(C_{n,i_a})_{m_a},
```

where

```math
(x)_j=x(x-1)\cdots(x-j+1).
```

Consequently,

```math
T_{F_m}(G_n)
\longrightarrow
P_m(p)
```

almost surely, where

```math
P_m(z)=
\frac{k!}{\prod_{a=1}^r m_a!}
\sum_{1\leq i_1<\cdots<i_r\leq q}
\prod_{a=1}^r z_{i_a}^{m_a}.
```

Every finite DAG that is not complete ordered multipartite has density zero
at every level.

## Proof

A $k$-element subset induces $F_m$ exactly when it meets some strictly
increasing sequence of layers $i_1<\cdots<i_r$ in the respective sizes
$m_1,\ldots,m_r$. The number of such subsets is

```math
\sum_{i_1<\cdots<i_r}
\prod_{a=1}^r
\binom{C_{n,i_a}}{m_a}.
```

Division by $\binom nk$ gives the displayed falling-factorial formula. The
strong law gives $Z_n\to p$, and division of numerator and denominator by
$n^k$ gives the polynomial limit.

The complete collection $(P_m(p))_m$ is the induced-density continuum point
of this sector.

# 4. Exact coefficient fields for layer proportions

Let $\mathbf e_i$ denote the $i$-th standard basis vector in $\mathbb R^q$,
and let

```math
\Sigma_p=
\operatorname{diag}(p)-pp^\mathsf T.
```

The matrix is positive semidefinite, has null vector $\mathbf 1$, and acts on
the tangent hyperplane

```math
H_q=
\left\{
 y\in\mathbb R^q:
 \sum_{i=1}^q y_i=0
\right\}.
```

## Theorem 3. Exact stable drift and covariance

The layer proportions satisfy the exact recursion

```math
Z_{n+1}=Z_n+
\frac{\mathbf e_{A_{n+1}}-Z_n}{n+1}.
```

With respect to the mark filtration $\mathcal F_n=\sigma(A_1,\ldots,A_n)$,
their scaled one-step coefficients are

```math
(n+1)
\mathbb E
\left[
Z_{n+1}-Z_n
\mid\mathcal F_n
\right]
=p-Z_n,
```

and

```math
\operatorname{Cov}
\left(
(n+1)(Z_{n+1}-Z_n)
\mid\mathcal F_n
\right)
=\Sigma_p.
```

All conditional moments of the scaled increment are uniformly bounded. The
coefficient fields are therefore already independent of $n$:

```math
b(z)=p-z,
\qquad
a(z)=\Sigma_p.
```

## Proof

The count recursion is

```math
C_{n+1}=C_n+\mathbf e_{A_{n+1}}.
```

Dividing by $n+1$ gives the first identity. Since $A_{n+1}$ is independent of
$\mathcal F_n$, its indicator vector has mean $p$ and covariance $\Sigma_p$.
Subtracting the fixed conditional vector $Z_n$ does not change the
covariance.

This sector therefore satisfies the stable-coefficient requirement exactly
rather than asymptotically. After the almost-sure finite occupancy time from
Proposition 1, the same coefficient identities hold with the graph
filtration because the layer counts are then determined by the DAG endpoint.

# 5. Logarithmic-size hydrodynamics

The one-step increment is of order $1/n$, so the macroscopic size variable is

```math
s=\log n.
```

To expose nontrivial relaxation rather than the already equilibrated
trajectory of the stationary sector, consider a triangular family restarted
at level $N$. Assume that

```math
Z_N^{(N)}\longrightarrow z_0
```

in probability, and let all marks added after level $N$ be independent with
law $p$. For $s\geq0$, set

```math
m_N(s)=\left\lfloor Ne^s\right\rfloor.
```

## Theorem 4. Hydrodynamic limit

For every finite $S>0$,

```math
\sup_{0\leq s\leq S}
\left\|
Z_{m_N(s)}^{(N)}-z(s)
\right\|
\longrightarrow0
```

in probability, where $z$ is the solution of

```math
\frac{dz}{ds}=p-z,
\qquad
z(0)=z_0.
```

Explicitly,

```math
z(s)=p+e^{-s}(z_0-p).
```

For the original extremal sector, $Z_N\to p$ almost surely, so the
hydrodynamic trajectory is the fixed point $z(s)=p$.

## Proof

For $m\geq N$, the count decomposition gives

```math
Z_m=
\frac Nm Z_N+
\frac1m
\sum_{j=N+1}^m\mathbf e_{A_j}.
```

After adding and subtracting $p$, this becomes

```math
Z_m-p=
\frac Nm(Z_N-p)+
\frac1m
\sum_{j=N+1}^m
(\mathbf e_{A_j}-p).
```

Uniformly for $N\leq m\leq Ne^S$, the second term converges to zero in
probability by the maximal inequality for bounded independent centered
increments. Since $N/m_N(s)\to e^{-s}$ uniformly on compact $s$-intervals,
the first term converges to $e^{-s}(z_0-p)$.

# 6. Functional fluctuation limit

The exact coefficient fields allow the fluctuation process to be identified
without a separate tightness argument for the graph coordinates.

Define

```math
Y_N(s)=
\sqrt{m_N(s)}
\left(
Z_{m_N(s)}-p
\right),
\qquad
0\leq s\leq S.
```

## Theorem 5. Stationary Ornstein-Uhlenbeck limit

For every finite $S>0$, the process $Y_N$ converges in distribution in
$D([0,S],H_q)$ to

```math
Y(s)=e^{-s/2}B_{\Sigma_p}(e^s),
```

where $B_{\Sigma_p}$ is a Brownian motion with covariance

```math
\mathbb E
\left[
B_{\Sigma_p}(t)B_{\Sigma_p}(u)^\mathsf T
\right]
=\min(t,u)\Sigma_p.
```

The limiting covariance is

```math
\mathbb E
\left[
Y(s)Y(t)^\mathsf T
\right]
=e^{-|s-t|/2}\Sigma_p.
```

Equivalently, $Y$ is the stationary solution on $H_q$ of

```math
dY_s=-\frac12Y_s\,ds+
\Sigma_p^{1/2}\,dW_s.
```

## Proof

Write

```math
S_n=\sum_{j=1}^n
(\mathbf e_{A_j}-p).
```

The multivariate invariance principle gives

```math
N^{-1/2}S_{\lfloor Nt\rfloor}
\Longrightarrow
B_{\Sigma_p}(t)
```

on every compact interval of positive $t$. Applying the continuous time
change $t=e^s$ and multiplying by $e^{-s/2}$ gives the displayed limit.

The covariance follows directly from the Brownian covariance. Ito's formula
applied to $e^{-s/2}B_{\Sigma_p}(e^s)$ gives the Ornstein-Uhlenbeck
equation.

The hydrodynamic Jacobian is

```math
J=Db=-I
```

on $H_q$. The fluctuation drift predicted in the preceding construction is
therefore

```math
J+\frac12I=-\frac12I,
```

which agrees exactly with the limit above. The positive relaxation operator
is

```math
B=\frac12I
```

on the tangent sector. Its stationary covariance solves

```math
BC+CB^\mathsf T=\Sigma_p
```

with solution

```math
C=\Sigma_p.
```

# 7. Stable coefficients for finite pattern coordinates

For every supported pattern $F_m$, retain the continuum polynomial $P_m$ from
Proposition 2. For an unsupported finite DAG $F$, set

```math
P_F=0.
```

Let

```math
\Delta_{n,F}=
(n+1)
\left(
T_F(G_{n+1})-T_F(G_n)
\right).
```

## Theorem 6. Cylinder coefficient convergence

For every fixed pair of finite DAGs $F$ and $K$, uniformly over all possible
count vectors at level $n$,

```math
\mathbb E
\left[
\Delta_{n,F}
\mid\mathcal F_n
\right]
=
B_F(Z_n)+O_{F,q}(n^{-1}),
```

and

```math
\operatorname{Cov}
\left(
\Delta_{n,F},
\Delta_{n,K}
\mid\mathcal F_n
\right)
=
A_{F,K}(Z_n)+O_{F,K,q}(n^{-1}),
```

where

```math
B_F(z)=
\nabla P_F(z)^\mathsf T(p-z),
```

and

```math
A_{F,K}(z)=
\nabla P_F(z)^\mathsf T
\Sigma_p
\nabla P_K(z).
```

All conditional third moments of $\Delta_{n,F}$ are uniformly bounded. Thus
every finite cylinder family has explicit stable drift and covariance fields.

## Proof

The falling-factorial expression in Proposition 2 has a uniform expansion

```math
T_F(G_n)=
P_F(Z_n)+
\frac1nQ_F(Z_n)+O_{F,q}(n^{-2})
```

for a polynomial $Q_F$. This follows by expanding each fixed falling
factorial and the denominator $(n)_k$ in powers of $n$.

The exact proportion increment is

```math
Z_{n+1}-Z_n=
\frac{\mathbf e_{A_{n+1}}-Z_n}{n+1}.
```

Taylor expansion of $P_F$ gives

```math
\Delta_{n,F}=
\nabla P_F(Z_n)^\mathsf T
(\mathbf e_{A_{n+1}}-Z_n)
+O_{F,q}(n^{-1}).
```

The contribution of the $Q_F/n$ term to the scaled increment is also
$O(n^{-1})$. Conditional expectation now gives $B_F$. Conditional covariance
gives $A_{F,K}$, because the covariance of $\mathbf e_{A_{n+1}}$ is
$\Sigma_p$. Uniform boundedness follows from the fixed degree of the pattern
polynomials and compactness of the simplex.

# 8. Process limit for cylinder coordinates

Fix finite DAGs $F_1,\ldots,F_d$, and define the gradient matrix

```math
L_p=
\begin{bmatrix}
\nabla P_{F_1}(p)^\mathsf T\\
\vdots\\
\nabla P_{F_d}(p)^\mathsf T
\end{bmatrix}.
```

Let

```math
V_N(s)=
\sqrt{m_N(s)}
\left(
\begin{bmatrix}
T_{F_1}(G_{m_N(s)})\\
\vdots\\
T_{F_d}(G_{m_N(s)})
\end{bmatrix}
-
\begin{bmatrix}
P_{F_1}(p)\\
\vdots\\
P_{F_d}(p)
\end{bmatrix}
\right).
```

## Corollary 7. Cylinder Ornstein-Uhlenbeck limit

The process $V_N$ converges in distribution to

```math
V(s)=L_pY(s).
```

It is a stationary Gaussian process with covariance

```math
\mathbb E
\left[
V(s)V(t)^\mathsf T
\right]
=
e^{-|s-t|/2}
L_p\Sigma_pL_p^\mathsf T.
```

It satisfies

```math
dV_s=-\frac12V_s\,ds+
L_p\Sigma_p^{1/2}\,dW_s.
```

## Proof

The finite-pattern expansion gives

```math
T_F(G_n)-P_F(p)=
\nabla P_F(p)^\mathsf T(Z_n-p)
+O(\|Z_n-p\|^2)
+O(n^{-1}).
```

Since $Z_n-p=O_{\mathbb P}(n^{-1/2})$, multiplication by $\sqrt n$ makes the
two remainder terms vanish in probability. The functional result follows from
Theorem 5 and the continuous mapping theorem.

This proves a process-level continuum limit with stable coefficients for
every finite collection of cylinder observables in the ordered-layer sector.

# 9. Agreement with the overlap-one coefficient

The stable static covariance from the general overlap-one formula can be
recovered directly from the coefficient matrix above.

For a $k$-vertex pattern $F$, define

```math
q_F(i)=
\mathbb P
\left(
X_p|_{[k]}\cong F
\mid A_1=i
\right).
```

Symmetry of the pattern event among its $k$ vertices gives

```math
\frac{\partial P_F}{\partial p_i}(p)=kq_F(i).
```

If $F$ and $K$ are observed on sets sharing one vertex, their remaining
marks are conditionally independent given the mark of the shared vertex. Hence

```math
\gamma_{F,K}=
\sum_{i=1}^q
p_iq_F(i)q_K(i).
```

It follows that

```math
\nabla P_F(p)^\mathsf T
\Sigma_p
\nabla P_K(p)
=
k\ell
\left(
\gamma_{F,K}-p_Fp_K
\right).
```

Thus the diffusion covariance obtained from the exact one-node coefficients
is identical to the stable overlap-one covariance derived for general central
sectors.

# 10. Two-layer sector and first-order degeneracy

The case $q=2$ makes the coefficient and degeneracy structure explicit. Write

```math
p=(\theta,1-\theta),
\qquad
X_n=Z_{n,1}.
```

Then

```math
(n+1)(X_{n+1}-X_n)
=I_{n+1}-X_n,
```

where $I_{n+1}$ is Bernoulli with parameter $\theta$. The stable
coefficients are

```math
b(x)=\theta-x,
\qquad
a(x)=\theta(1-\theta).
```

The logarithmic-size hydrodynamic equation and fluctuation equation are

```math
\frac{dx}{ds}=\theta-x,
```

and

```math
dY_s=-\frac12Y_s\,ds+
\sqrt{\theta(1-\theta)}\,dW_s.
```

Let $E$ be the two-vertex one-edge pattern. Its exact density is

```math
T_E(G_n)=
\frac{C_{n,1}C_{n,2}}{\binom n2}
=
\frac{2n}{n-1}X_n(1-X_n).
```

The continuum polynomial is

```math
P_E(x)=2x(1-x).
```

When $\theta\neq1/2$, the first derivative is nonzero and

```math
\sqrt{m_N(s)}
\left(
T_E(G_{m_N(s)})-2\theta(1-\theta)
\right)
\Longrightarrow
2(1-2\theta)Y(s).
```

At the symmetric point $\theta=1/2$, the first derivative vanishes. The
overlap-one covariance is zero, and the $\sqrt n$ limit degenerates. The
exact density formula instead gives

```math
m_N(s)
\left(
T_E(G_{m_N(s)})-\frac12
\right)
\Longrightarrow
\frac12-2Y(s)^2,
```

where $Y$ is the stationary Ornstein-Uhlenbeck process with variance $1/4$.

The limiting process is non-Gaussian. This realizes the degeneracy mechanism
identified by the overlap expansion: a nonzero first projection gives a
Gaussian limit on the $\sqrt n$ scale, whereas a vanishing first projection
moves the leading term to the second-order $n$ scale.

The scale is therefore determined by the first nonvanishing overlap order
rather than imposed independently.

# 11. Relation to Pascal-type branching

The marked count process $C_n$ moves on the $q$-dimensional Pascal graph:

```math
c\longrightarrow c+\mathbf e_i.
```

The Bernoulli product law with parameter $p$ is an extremal central measure
on that graph. Mapping a count vector to the complete ordered-layer DAG with
those layer sizes pushes the Pascal process into the DAG branching graph.
Once all coordinates are positive, the map is injective and the DAG endpoint
recovers the Pascal state.

This explains why the sector is exactly solvable. It is an embedded
Pascal-type subfamily of the much larger DAG central boundary. The continuum
parameter $p$, hydrodynamic simplex, multinomial covariance, and
Ornstein-Uhlenbeck fluctuation operator all descend from that subfamily.

Continuum existence and coefficient stability hold for the whole
finite-dimensional family of extremal sectors indexed by $p$. The
construction contains no selection principle for a particular $p$.

# 12. Literature relation

Central measures and canonical cotransitions on multiplicity graded graphs
are treated in A. M. Vershik, *The problem of describing central measures on
the path spaces of graded graphs*, Functional Analysis and Its Applications
48 (2014), arXiv:1408.3291.

The relation between extreme exchangeable laws and deterministic dense limit
objects is developed for graphs in P. Diaconis and S. Janson, *Graph limits
and exchangeable random graphs*, Rendiconti di Matematica 28 (2008),
arXiv:0712.2749, and for posets in S. Janson, *Poset limits and exchangeable
random posets*, Combinatorica 31 (2011), arXiv:0902.0306.

Directed exchangeable kernel models, including acyclic and ordered block
constructions, are described in D. Cai, N. Ackerman, and C. Freer, *Priors on
exchangeable directed graphs*, arXiv:1510.08440. The present ordered-layer
construction is elementary and all coefficient and limit formulas above are
derived directly.
