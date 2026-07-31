# 1. Stochastic two-layer DAG sectors

The ordered-layer construction gives exact closure because the edge relation determines the latent layers after finite occupancy. The first extension beyond that regime is obtained by retaining the ordered latent partition while allowing independent edge noise between its layers.

Fix parameters

```math
0<\theta<1,
\qquad
0<r<1.
```

Let $(A_j)_{j\geq1}$ be independent marks with

```math
\mathbb P(A_j=1)=\theta,
\qquad
\mathbb P(A_j=2)=1-\theta.
```

For each unordered pair $\{i,j\}$, let $B_{ij}=B_{ji}$ be an independent Bernoulli variable with parameter $r$, independent of all marks. If $A_i=1$ and $A_j=2$, place the edge $i\to j$ when $B_{ij}=1$. If $A_i=2$ and $A_j=1$, place the edge $j\to i$ when $B_{ij}=1$. No edge is placed between vertices in the same layer.

The resulting infinite graph $X_{\theta,r}$ is a DAG because every edge is directed from layer $1$ to layer $2$. Its restriction to $[n]$ is denoted by $G_n$.

## Proposition 1. Extremal centrality

The law of $X_{\theta,r}$ is exchangeable and dissociated. It therefore determines an extremal central measure on the DAG branching graph.

## Proof

A finite permutation simultaneously permutes the independent vertex marks and pair variables, leaving their joint law invariant. Restrictions to disjoint vertex sets depend on disjoint families of marks and pair variables, so they are independent. The central-exchangeable correspondence then gives an extremal central sector.

Unlike the deterministic ordered-layer sector, the unlabeled graph does not generally recover the latent marks. Missing edges create finite observational ambiguity. The latent count process nevertheless remains exactly closed and provides a controlled setting in which graph observables can be analyzed beyond perfect observability.

# 2. Continuum kernel and edge density

The sector is represented by a two-block ordered directed kernel. Partition $[0,1]$ into intervals of lengths $\theta$ and $1-\theta$. For points in the first and second intervals, include the edge from the first block to the second with probability $r$; include no other edges.

Let

```math
C_{n,1}=\sum_{j=1}^n\mathbf 1\{A_j=1\},
\qquad
C_{n,2}=n-C_{n,1},
```

and define

```math
X_n=\frac{C_{n,1}}n.
```

Let $M_n$ be the number of edges in $G_n$, and let

```math
Q_n=\frac{M_n}{\binom n2}
```

be the induced density of the two-vertex one-edge pattern.

Conditional on the marks, the number of possible cross-layer edges is

```math
R_n=C_{n,1}C_{n,2},
```

and

```math
M_n\mid(A_1,\ldots,A_n)
\sim
\operatorname{Binomial}(R_n,r).
```

Consequently,

```math
Q_n=
rH_n+U_n,
```

where

```math
H_n=
\frac{C_{n,1}C_{n,2}}{\binom n2}
=
\frac{2n}{n-1}X_n(1-X_n),
```

and

```math
U_n=
\frac{N_n}{\binom n2},
\qquad
N_n=M_n-rR_n.
```

The strong law gives

```math
Q_n\longrightarrow
q_*=2r\theta(1-\theta)
```

almost surely.

# 3. The vertex-proportion mode

The latent proportion process is unchanged from the deterministic sector. If

```math
I_j=\mathbf 1\{A_j=1\},
```

then

```math
(n+1)(X_{n+1}-X_n)=I_{n+1}-X_n.
```

Its exact stable coefficients are

```math
b(x)=\theta-x,
\qquad
a(x)=\theta(1-\theta).
```

For

```math
m_N(s)=\lfloor Ne^s\rfloor,
```

define

```math
Y_N(s)=
\sqrt{m_N(s)}
\left(
X_{m_N(s)}-\theta
\right).
```

The preceding result gives

```math
Y_N\Longrightarrow Y,
```

where $Y$ is the stationary Ornstein-Uhlenbeck process

```math
dY_s=-\frac12Y_s\,ds+
\sqrt{\theta(1-\theta)}\,dW_s^{(1)}.
```

Its covariance is

```math
\mathbb E[Y(s)Y(t)]
=
\theta(1-\theta)e^{-|s-t|/2}.
```

# 4. The centered edge-noise martingale

For $i<j$, define

```math
\eta_{ij}=
\mathbf 1\{A_i\neq A_j\}
(B_{ij}-r).
```

Then

```math
N_n=\sum_{1\leq i<j\leq n}\eta_{ij}.
```

Reveal the process one vertex at a time and set

```math
D_j=\sum_{i<j}\eta_{ij}.
```

With respect to the natural filtration containing all marks and pair variables revealed through level $j$, the sequence $(D_j)_{j\geq2}$ is a martingale-difference sequence and

```math
N_n=\sum_{j=2}^nD_j.
```

## Proposition 2. Predictable pair-noise variance

The conditional variance of the new-vertex edge-noise increment is

```math
\mathbb E
\left[
D_j^2
\mid\mathcal F_{j-1}
\right]
=
r(1-r)
\left[
(1-\theta)C_{j-1,1}
+
\theta C_{j-1,2}
\right].
```

Consequently,

```math
\frac1{N^2}
\sum_{j=2}^{\lfloor Nt\rfloor}
\mathbb E
\left[
D_j^2
\mid\mathcal F_{j-1}
\right]
\longrightarrow
c_{\theta,r}t^2
```

almost surely, where

```math
c_{\theta,r}=
\theta(1-\theta)r(1-r).
```

## Proof

Conditional on $A_j$ and the preceding marks, the summands in $D_j$ are independent centered Bernoulli residuals. Cross terms therefore vanish. Averaging over the new mark gives

```math
r(1-r)
\sum_{i<j}
\mathbb P(A_j\neq A_i\mid\mathcal F_{j-1}),
```

which is the displayed formula. The strong law gives

```math
C_{j-1,1}=\theta j+o(j),
\qquad
C_{j-1,2}=(1-\theta)j+o(j).
```

The conditional variance is therefore

```math
2c_{\theta,r}j+o(j).
```

Summation through $Nt$ and division by $N^2$ gives $c_{\theta,r}t^2$.

# 5. Functional limit of the pair-noise mode

Define the pair-noise process in ordinary size time by

```math
\mathcal M_N(t)=
\frac1N
N_{\lfloor Nt\rfloor},
\qquad
t\geq0.
```

## Theorem 3. Pair-noise martingale limit

For every finite $T>0$,

```math
\mathcal M_N
\Longrightarrow
\sqrt{c_{\theta,r}}B_2(t^2)
```

in $D([0,T])$, where $B_2$ is a standard Brownian motion.

Moreover, this limit is independent of the Brownian motion driving the vertex-proportion limit.

## Proof

Proposition 2 gives convergence of the predictable quadratic variation. The conditional fourth moment of $D_j$ is $O(j^2)$, uniformly in the preceding marks, because $D_j$ is a sum of at most $j-1$ bounded conditionally independent centered variables. Hence, for every $\varepsilon>0$,

```math
\frac1{N^2}
\sum_{j\leq NT}
\mathbb E
\left[
D_j^2
\mathbf 1\{|D_j|>\varepsilon N\}
\mid\mathcal F_{j-1}
\right]
\longrightarrow0
```

in probability. The martingale functional central limit theorem gives the stated time-changed Brownian motion.

The mark increment $I_j-\theta$ and the pair-noise increment $D_j$ have zero conditional cross moment, because every term of $D_j$ contains the independent centered factor $B_{ij}-r$. The limiting continuous Gaussian martingales are therefore orthogonal and hence independent.

# 6. Logarithmic-size pair-noise dynamics

The graph-observable pair-noise contribution appears at scale $n$, since

```math
nU_n=
\frac{n}{\binom n2}N_n
=
\frac{2}{n-1}N_n.
```

Define

```math
Z_N(s)=
m_N(s)U_{m_N(s)}.
```

## Corollary 4. Pair-noise Ornstein-Uhlenbeck limit

The process $Z_N$ converges in distribution to

```math
Z(s)=
2\sqrt{c_{\theta,r}}
 e^{-s}B_2(e^{2s}).
```

Its covariance is

```math
\mathbb E[Z(s)Z(t)]
=
4c_{\theta,r}e^{-|s-t|}.
```

Equivalently, $Z$ is the stationary Ornstein-Uhlenbeck process

```math
dZ_s=-Z_s\,ds+
\sqrt{8c_{\theta,r}}\,dW_s^{(2)}.
```

The Brownian motion $W^{(2)}$ is independent of the Brownian motion $W^{(1)}$ in the vertex-proportion mode.

## Proof

Apply Theorem 3 at $t=e^s$ and multiply by the asymptotic factor $2e^{-s}$. The covariance follows from

```math
\mathbb E
\left[
B_2(e^{2s})B_2(e^{2t})
\right]
=e^{2\min(s,t)}.
```

Ito's formula gives the stochastic differential equation.

The relaxation rate is now $1$, rather than $1/2$. The difference reflects the combinatorial order of the fluctuation: the vertex mode is a first-order empirical fluctuation, whereas the centered edge noise is a second-order pair fluctuation.

# 7. Generic edge-density fluctuations

The decomposition

```math
Q_n=rH_n+U_n
```

separates the vertex-proportion and pair-noise modes. Since

```math
H_n=
\frac{2n}{n-1}X_n(1-X_n),
```

the first-order derivative at the limiting proportion is

```math
\frac{d}{dx}
\left[
2rx(1-x)
\right]_{x=\theta}
=
2r(1-2\theta).
```

## Theorem 5. Generic $\sqrt n$ edge-density limit

If $\theta\neq1/2$, then

```math
\sqrt{m_N(s)}
\left(
Q_{m_N(s)}-2r\theta(1-\theta)
\right)
\Longrightarrow
2r(1-2\theta)Y(s)
```

in $D([0,S])$ for every finite $S$.

The pair-noise contribution vanishes on this scale.

## Proof

The delta method applied to $rH_n$ gives the displayed limit. The pair-noise term satisfies

```math
\sqrt n U_n
=
\frac{nU_n}{\sqrt n}
\longrightarrow0
```

in probability because $nU_n$ is tight by Corollary 4.

Thus the generic graph-observable edge-density fluctuation is inherited entirely from the first-order vertex mode.

# 8. Symmetric degeneracy and mixed fluctuation orders

At

```math
\theta=\frac12,
```

the first derivative of the continuum edge density vanishes. The $\sqrt n$ limit is therefore zero, and the next scale retains both the quadratic vertex fluctuation and the centered pair-noise fluctuation.

## Theorem 6. Symmetric $n$-scale edge-density limit

Assume $\theta=1/2$. Then

```math
m_N(s)
\left(
Q_{m_N(s)}-\frac r2
\right)
\Longrightarrow
r
\left(
\frac12-2Y(s)^2
\right)
+Z(s),
```

where

```math
dY_s=-\frac12Y_s\,ds+
\frac12\,dW_s^{(1)},
```

and

```math
dZ_s=-Z_s\,ds+
\sqrt{2r(1-r)}\,dW_s^{(2)}.
```

The processes $Y$ and $Z$ are independent. The stationary variances are

```math
\operatorname{Var}(Y)=\frac14,
\qquad
\operatorname{Var}(Z)=r(1-r).
```

## Proof

The exact identity from the deterministic two-layer sector gives

```math
n
\left(
H_n-\frac12
\right)
=
\frac{n}{2(n-1)}
-
\frac{2n}{n-1}
\left[
\sqrt n
\left(
X_n-\frac12
\right)
\right]^2.
```

The functional convergence of $Y_N$ and the continuous mapping theorem give

```math
n
\left(
H_n-\frac12
\right)
\Longrightarrow
\frac12-2Y^2.
```

The centered edge-noise term converges to $Z$ by Corollary 4. Joint convergence and independence follow from Theorem 3.

The limit is not Gaussian because of the quadratic Ornstein-Uhlenbeck term. It contains two distinct relaxation rates generated by two overlap orders.

# 9. Coefficient interpretation

The stochastic two-layer sector separates three statements that were previously combined.

The latent proportion state has exact finite-dimensional closure:

```math
b(x)=\theta-x,
\qquad
a(x)=\theta(1-\theta).
```

The graph-observable edge density has a deterministic continuum limit:

```math
q_*=2r\theta(1-\theta).
```

Its fluctuation coefficient depends on the first nonvanishing projection. Away from symmetry, the first-order coefficient is

```math
4r^2(1-2\theta)^2\theta(1-\theta),
```

and the relaxation rate is $1/2$. At symmetry this coefficient vanishes, and the second-order pair coefficient

```math
4c_{1/2,r}=r(1-r)
```

survives with relaxation rate $1$, together with the quadratic first-mode contribution.

Thus coefficient stability does not require a single universal scaling. Stable coefficients appear in an overlap hierarchy, and each nonvanishing order carries its own normalization and logarithmic relaxation rate.

# 10. Overlap order and relaxation spectrum

The two explicit modes suggest the general relation

```math
\text{overlap order }j
\quad\longleftrightarrow\quad
\text{relaxation rate }\frac j2.
```

For $j=1$, empirical vertex fluctuations have covariance

```math
e^{-|s-t|/2}.
```

For $j=2$, degenerate pair fluctuations have covariance

```math
e^{-|s-t|}.
```

This relation is consistent with the Hoeffding decomposition of finite-pattern statistics: a pattern observable decomposes into projections indexed by the number of shared vertices. If the first $j-1$ projections vanish, the $j$-th projection determines the normalization and the logarithmic decay rate.

The general statement remains to be proved for arbitrary finite DAG patterns. The present sector establishes it exactly for the first two orders and provides the coefficient values without phenomenological fitting.

# 11. Continuum consequences

The stochastic two-layer sector connects an extremal central DAG law to a deterministic directed kernel, a graph-observable density limit, and multiple stable fluctuation modes.

It also identifies the first genuine closure obstruction. The latent mark proportion is exactly Markov, but it is not generally recoverable from the finite graph. A graph-intrinsic state must therefore encode enough rooted or predictive information to reconstruct its posterior effect on future extensions.

The next step should be the $q$-layer stochastic ordered block sector with probabilities

```math
w_{ij},
\qquad
i<j.
```

That model remains acyclic, permits routes of length greater than one, and has a finite latent simplex with explicit multinomial hydrodynamics. Its finite-pattern observables should admit a Hoeffding hierarchy whose first projections are functions of rooted layer patterns and whose second projections contain independent edge noise. Proving graph-intrinsic predictive closure there would connect the current exact examples to the general rooted-density program.

# 12. Literature relation

The directed-kernel representation of exchangeable DAGs is discussed in D. Cai, N. Ackerman, and C. Freer, *Priors on exchangeable directed graphs*, arXiv:1510.08440. The process above is a finite ordered block specialization of that representation.

The functional limits used here are direct applications of the invariance principle for bounded independent increments and the martingale functional central limit theorem. The logarithmic-size Ornstein-Uhlenbeck forms follow by the Lamperti time change applied to the corresponding Brownian and time-changed Brownian limits.
