# 1. Finite ambiguity and asymptotic observability

The preceding stochastic ordered-layer constructions were described as
latent-state models because missing edges can make the layer assignment
ambiguous in a finite graph. That statement is correct at fixed size, but it
does not imply a persistent closure obstruction.

In every finite ordered-layer sector with positive adjacent-layer edge
probabilities, the graph eventually identifies every latent layer exactly. The
two- and three-layer degree signatures give the simplest cases, while
iterative source deletion gives the general result. The ambiguity is almost
surely temporary.

The following results establish eventual graph-intrinsic recovery, construct
consistent parameter estimators, and express the ordered-layer stable
coefficients in observable coordinates.

# 2. Three-layer degree signatures

Consider the stochastic three-layer sector with

```math
p_i>0,
\qquad
p_1+p_2+p_3=1,
```

and

```math
a=w_{12}>0,
\qquad
b=w_{23}>0,
\qquad
0\leq c=w_{13}\leq1.
```

For a vertex $v\in G_n$, let

```math
d_n^-(v)
```

and

```math
d_n^+(v)
```

be its indegree and outdegree. The latent layers have deterministic
zero-degree constraints:

```math
A_v=1
\Longrightarrow
d_n^-(v)=0,
```

whereas a middle-layer vertex satisfies

```math
A_v=2
\Longrightarrow
d_n^-(v),d_n^+(v)
\text{ may both be positive},
```

and

```math
A_v=3
\Longrightarrow
d_n^+(v)=0.
```

The only obstruction to exact recovery is a vertex that has not yet acquired
an allowed incident edge.

## Theorem 1. Eventual exact recovery of the latent partition

Almost surely, there is a finite random level $N$ such that for every
$n\geq N$,

```math
V_1(n)
=
\left\{
v\in[n]:
d_n^-(v)=0,
\ d_n^+(v)>0
\right\},
```

the middle layer is recovered as

```math
V_2(n)
=
\left\{
v\in[n]:
d_n^-(v)>0,
\ d_n^+(v)>0
\right\},
```

and

```math
V_3(n)
=
\left\{
v\in[n]:
d_n^-(v)>0,
\ d_n^+(v)=0
\right\}.
```

In particular, there are no isolated vertices after level $N$, and the
unlabeled DAG endpoint determines its latent ordered partition.

## Proof

A layer-1 vertex fails to have an outgoing edge at level $n$ only if it
misses every potential layer-2 edge. Conditional on that vertex having mark
$1$, each of the other $n-1$ vertices independently fails to provide such an
edge with probability $1-p_2a$. Hence

```math
\mathbb P
\left(
A_v=1,
\ d_n^+(v)=0
\right)
\leq
p_1(1-p_2a)^{n-1}.
```

A union bound over $v\in[n]$ gives

```math
\mathbb P
\left(
\text{some layer-1 vertex has zero outdegree at level }n
\right)
\leq
np_1(1-p_2a)^{n-1}.
```

The series over $n$ converges.

The same argument gives

```math
\mathbb P
\left(
\text{some layer-2 vertex has zero indegree}
\right)
\leq
np_2(1-p_1a)^{n-1},
```

and the corresponding outdegree bound is

```math
\mathbb P
\left(
\text{some layer-2 vertex has zero outdegree}
\right)
\leq
np_2(1-p_3b)^{n-1},
```

and

```math
\mathbb P
\left(
\text{some layer-3 vertex has zero indegree}
\right)
\leq
np_3(1-p_2b)^{n-1}.
```

All four bounds are summable. The Borel-Cantelli lemma shows that only
finitely many levels contain any of these exceptional vertices. Beyond their
last occurrence, the zero-degree signatures give the exact partition.

The direct layer-1 to layer-3 probability $c$ is irrelevant to this
conclusion. Positive adjacent probabilities $a$ and $b$ are sufficient.

## Corollary 2. Two-layer recovery

In the stochastic two-layer sector with $0<\theta<1$ and $r>0$, the latent
bipartition is also recovered exactly after a finite random level:

```math
V_1(n)=\{v:d_n^-(v)=0<d_n^+(v)\},
```

and

```math
V_2(n)=\{v:d_n^+(v)=0<d_n^-(v)\}.
```

Thus the finite ambiguity noted previously is not an asymptotic obstruction
in that sector either.

## Theorem 3. Recovery of finitely many ordered layers

Consider the stochastic ordered block sector with any fixed number $q$ of
layers. Assume

```math
p_i>0
```

for every $i$, and assume positive adjacent connectivity,

```math
w_{i,i+1}>0,
\qquad
1\leq i<q.
```

Almost surely, there is a finite random level after which the complete
ordered layer partition is determined by iterative source deletion. More
precisely, define

```math
S_1(G_n)=\{v:d^-_{G_n}(v)=0\},
```

and, after removing $S_1,\ldots,S_{r-1}$, let $S_r(G_n)$ be the sources of
the remaining induced graph. Then eventually

```math
S_r(G_n)=V_r(n),
\qquad
1\leq r\leq q.
```

The analogous iterative sink deletion recovers the layers in reverse order.

### Proof

For a layer-$i$ vertex with $i>1$, the probability that it has no incoming
edge from the adjacent layer $i-1$ at level $n$ is at most

```math
(1-p_{i-1}w_{i-1,i})^{n-1}.
```

For a layer-$i$ vertex with $i<q$, the probability that it has no outgoing
edge to layer $i+1$ is at most

```math
(1-p_{i+1}w_{i,i+1})^{n-1}.
```

After a union bound over the vertices and the finitely many adjacent layer
pairs, the resulting level-$n$ error probability is bounded by a finite sum
of terms of the form

```math
n(1-\varepsilon)^{n-1},
```

which is summable. The Borel-Cantelli lemma therefore gives a finite random
level after which every nonminimal-layer vertex has an incoming witness from
its immediate predecessor and every nonmaximal-layer vertex has an outgoing
witness to its immediate successor.

At such a level, the sources of the full graph are exactly the layer-1
vertices. After removing them, the sources of the remaining graph are exactly
the layer-2 vertices: true layer-2 vertices have no remaining incoming edges,
while every higher-layer vertex retains an incoming witness from its
immediate predecessor. Induction gives $S_r(G_n)=V_r(n)$ for every $r$.

This theorem shows that positive adjacent connectivity is sufficient for
eventual graph-intrinsic observability throughout the finite ordered block
family. Direct long-range probabilities $w_{ij}$ with $j>i+1$ may vanish
without affecting recovery. If some adjacent probabilities vanish, the ordered
block representation may become reducible or observationally merge
neighboring layers. In that regime, degree information alone need not identify
the latent decomposition, and higher rooted pattern distributions or a minimal
quotient of the block representation are required.

# 3. Observable layer proportions

After the recovery time of Theorem 3, the graph endpoint gives the exact counts

```math
C_{n,i}=|V_i(n)|
```

and proportions

```math
\widehat p_{n,i}=\frac{C_{n,i}}n.
```

The strong law gives

```math
\widehat p_n\longrightarrow p
```

almost surely. Their exact one-node coefficient fields remain

```math
b(z)=p-z,
\qquad
a(z)=\Sigma_p.
```

After a finite random level, the state variable $Z_n$ is a graph-intrinsic
observable.

The logarithmic-size fluctuation process

```math
Y_N(s)=
\sqrt{m_N(s)}
\left(
\widehat p_{m_N(s)}-p
\right)
```

therefore has the same graph-intrinsic Ornstein-Uhlenbeck limit

```math
dY_s=-\frac12Y_s\,ds+
\Sigma_p^{1/2}\,dW_s.
```

# 4. Observable edge parameters

Let $E_{ij,n}$ be the number of edges from recovered layer $i$ to recovered
layer $j$, for any $1\leq i<j\leq q$. Define

```math
\widehat w_{ij,n}
=
\frac{E_{ij,n}}{C_{n,i}C_{n,j}},
\qquad
i<j,
```

whenever the denominator is nonzero. After the recovery time, these are
ordinary empirical Bernoulli means over the cross-layer pairs.

## Theorem 4. Strong parameter recovery

For every $i<j$, almost surely,

```math
\widehat w_{ij,n}\longrightarrow w_{ij}.
```

Consequently, the complete finite ordered-block parameter pair

```math
(p,W)
```

is identifiable and consistently recoverable from the unlabeled graph
sequence whenever the adjacent probabilities are positive.

## Proof

Theorem 3 identifies the true layer partition after a finite random level.
Conditional on the marks, the edges in block $ij$ are independent Bernoulli
variables with parameter $w_{ij}$, and

```math
C_{n,i}C_{n,j}
\sim
p_ip_jn^2
```

almost surely. The strong law for the block-edge averages gives the result.

# 5. Parameter fluctuation processes

Set

```math
N_{ij,n}
=
E_{ij,n}-w_{ij}C_{n,i}C_{n,j}.
```

The block residuals are the pair-noise martingales of the ordered-block
analysis. Since

```math
\widehat w_{ij,n}-w_{ij}
=
\frac{N_{ij,n}}{C_{n,i}C_{n,j}},
```

the natural normalization is $n$, not $\sqrt n$.

## Theorem 5. Graph-intrinsic edge-parameter limit

For $i<j$, define

```math
\Xi_{ij,N}(s)
=
m_N(s)
\left(
\widehat w_{ij,m_N(s)}-w_{ij}
\right).
```

For every finite collection of block pairs, the joint process consisting of
$Y_N$ and the corresponding $\Xi_{ij,N}$ converges to independent components.
The empirical-proportion component is the rate-$1/2$ process above, and

```math
d\Xi_{ij,s}
=-\Xi_{ij,s}\,ds+
\sqrt{
\frac{2w_{ij}(1-w_{ij})}{p_ip_j}
}
\,dB_s^{(ij)}.
```

Its stationary variance is

```math
\operatorname{Var}(\Xi_{ij})
=
\frac{w_{ij}(1-w_{ij})}{p_ip_j}.
```

## Proof

The pair-noise functional limit gives

```math
\frac{N_{ij,\lfloor Nt\rfloor}}N
\Longrightarrow
\sqrt{p_ip_jw_{ij}(1-w_{ij})}
B_{ij}(t^2).
```

Moreover,

```math
\frac{C_{n,i}C_{n,j}}{n^2}
\longrightarrow
p_ip_j
```

uniformly on compact logarithmic-size intervals. Therefore

```math
n
\left(
\widehat w_{ij,n}-w_{ij}
\right)
=
\frac{N_{ij,n}/n}{(C_{n,i}C_{n,j})/n^2}
```

has the asserted time-changed Brownian limit. The Lamperti transformation
gives the rate-one Ornstein-Uhlenbeck equation. Orthogonality of the centered
edge residuals across blocks and against the mark increments gives
independence.

The two fluctuation scales are now both graph-intrinsic:

```math
\sqrt n
\quad\text{for layer proportions},
```

and

```math
n
\quad\text{for cross-layer edge probabilities}.
```

# 6. Degree-profile identification without exact zeros

The exact zero-degree argument is special to the extreme source and sink
layers. A more robust asymptotic signature is obtained from normalized
indegree and outdegree.

For a layer-$i$ vertex, define its limiting degree point

```math
x_i=
\left(
\sum_{h<i}p_hw_{hi},
\sum_{j>i}p_jw_{ij}
\right).
```

In the three-layer sector these points are

```math
x_1=
\left(
0,
 ap_2+cp_3
\right),
```

the middle-layer degree point is

```math
x_2=
\left(
 ap_1,
 bp_3
\right),
```

and

```math
x_3=
\left(
 cp_1+bp_2,
0
\right).
```

The empirical normalized-degree measure is

```math
\nu_n
=
\frac1n
\sum_{v=1}^n
\delta_{(
 d_n^-(v)/(n-1),
 d_n^+(v)/(n-1)
 )}.
```

## Proposition 6. Degree-measure limit

Almost surely,

```math
\nu_n
\Longrightarrow
p_1\delta_{x_1}
+p_2\delta_{x_2}
+p_3\delta_{x_3}.
```

When $a,b>0$, the three atoms are distinct: $x_1$ lies on the outgoing axis,
$x_3$ lies on the incoming axis, and $x_2$ lies in the interior of the
positive quadrant.

## Proof

Conditional on a vertex having layer $i$, its normalized in- and outdegrees
are averages of independent bounded edge indicators over the other vertices.
Hoeffding concentration and a union bound over all $n$ vertices show that the
maximum distance between a vertex degree pair and its layer point tends to
zero almost surely. The empirical layer proportions converge to $p$, giving
the weak convergence of $\nu_n$.

The atom masses recover $p_1,p_2,p_3$. The interior atom then gives

```math
a=\frac{x_2^-}{p_1},
\qquad
b=\frac{x_2^+}{p_3}.
```

The remaining parameter is recovered consistently from either axis atom:

```math
c=
\frac{x_1^+-ap_2}{p_3}
=
\frac{x_3^--bp_2}{p_1}.
```

Thus even the limiting one-root degree distribution already identifies the
full three-layer parameter vector.

# 7. Observable predictive coefficients

For every finite DAG pattern $F$, the quantities

```math
P_F(p,W)
```

and

```math
q_F(i;p,W)
```

are finite polynomials in the layer probabilities and cross-layer edge
probabilities. Define their plug-in versions by

```math
\widehat P_{F,n}
=
P_F(\widehat p_n,\widehat W_n),
```

and

```math
\widehat q_{F,n}(i)
=
q_F(i;\widehat p_n,\widehat W_n).
```

## Corollary 7. Graph-intrinsic coefficient closure

Almost surely,

```math
\widehat P_{F,n}\longrightarrow P_F(p,W),
```

and

```math
\widehat q_{F,n}(i)
\longrightarrow q_F(i;p,W).
```

For any finite collection $F_1,\ldots,F_d$, the estimated first-order
covariance matrix

```math
\widehat A_{rs,n}
=
k_rk_s
\left[
\sum_i
\widehat p_{n,i}
\widehat q_{F_r,n}(i)
\widehat q_{F_s,n}(i)
-
\widehat P_{F_r,n}
\widehat P_{F_s,n}
\right]
```

converges almost surely to the stable cylinder covariance matrix.

For the two-step route, the observable estimates are

```math
\widehat\tau_n
=
6\widehat a_n\widehat b_n
\widehat p_{n,1}\widehat p_{n,2}\widehat p_{n,3},
```

and

```math
\widehat q_R(1)
=
2\widehat a_n\widehat b_n
\widehat p_{n,2}\widehat p_{n,3},
```

with the analogous cyclic formulas for layers $2$ and $3$.

The coefficients derived for the ordered-block sectors are therefore
consistently measurable from the graph endpoint itself.

# 8. Eventual Markov closure on graph states

Assume the sector parameters $(p,W)$ are fixed. Once the layer partition is
recovered, the conditional extension law is determined by the current DAG
endpoint:

1. the new vertex chooses layer $i$ with probability $p_i$;
2. conditional on that layer, it connects independently to each current
   vertex using the corresponding block probability $w_{hi}$ or $w_{ij}$;
3. its incident directions are fixed by the recovered layer order.

## Theorem 8. Eventual graph-intrinsic transition law

Almost surely, there is a finite random level after which the conditional law
of the next one-node extension is a function of the current unlabeled DAG
endpoint and the fixed sector parameters. No unobserved historical state is
then required.

## Proof

Theorem 3 makes the ordered layer partition an isomorphism-invariant function
of the current DAG. Given that partition, the future extension rule depends
only on the current vertices' layer classes and on the fixed parameters.
Earlier growth history contributes no additional information.

This result resolves the closure issue throughout the finite ordered-layer
family with positive adjacent connectivity. At finite levels the endpoint may
not identify the latent state, but almost surely the obstruction disappears
after finite growth.
