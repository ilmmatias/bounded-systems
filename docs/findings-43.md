# 1. Three separate refinement variables

We need to keep three indices distinct:

$$
n=\text{system size},
$$

$$
r=\text{observation/2-WL refinement depth},
$$

$$
p=\text{resolved path horizon}.
$$

They play different roles:

* $n\to\infty$ constructs the continuum profile space;
* $r\to\infty$ removes observational/profile collapse;
* $p\to\infty$ constructs the operational dynamics and asymptotic harmonic profile.

The existing exhaustive data already demonstrates why $r$ matters. The second-order pair profile classifies every non-isomorphic simple DAG through seven nodes. At eight nodes, one 2-WL round leaves only $509$ collision classes containing $1020$ graphs, while stabilized 2-WL separates all $20{,}286{,}025$ configurations.

Numerically,

$$
c_{8,1}=
20{,}286{,}025-(1020-509)=
20{,}285{,}514,
$$

so one refinement round is missing only

$$
511
$$

distinctions.

The fraction of graphs involved in collisions is

$$
\frac{1020}{20{,}286{,}025}
\approx
5.03\times10^{-5},
$$

or about $0.00503%$.

Thus the pair profile is already extremely close to injective at $n=8$, but stabilized refinement is the exact finite coordinate.

# 2. A normalized 2-WL profile space valid for every (n)

Raw WL color integers cannot be compared across different graph sizes. We need a recursively defined, normalized object.

Let

$$
\mathcal Z_0=
\{
=,\to,\leftarrow,\parallel
\}
$$

be the four primitive ordered-pair relations.

For a DAG $G$ on $n$ nodes, define

$$
z_0^G(u,v)
\in\mathcal Z_0
$$

from equality and immediate channel direction.

Now define recursively

$$
m_r^G(u,v)=
\frac1n
\sum_{w\in V(G)}
\delta_{
\left(
z_r^G(u,w),
z_r^G(w,v)
\right)
}.
$$

This is the normalized empirical distribution of all ways a third node $w$ relates the ordered pair $(u,v)$.

Set

$$
z_{r+1}^G(u,v)=
\left(
z_r^G(u,v),
m_r^G(u,v)
\right).
$$

The profile spaces satisfy

$$
\mathcal Z_{r+1}=
\mathcal Z_r
\times
\mathcal P(\mathcal Z_r^2).
$$

At fixed $n$, multiplying $m_r$ by $n$ recovers the ordinary integer multiset used by exact 2-WL. Across different $n$, the normalized measure remains comparable.

The graph-level profile is

$$
\mu_{G,r}=
\frac1{n^2}
\sum_{u,v\in V(G)}
\delta_{z_r^G(u,v)}.
$$

This has the properties we need:

* invariant under node relabeling;
* fixed ambient space for every $n$;
* equivalent to exact $r$-round 2-WL when $n$ is retained;
* naturally measure-valued;
* directly computable with sparse canonical hashes.

The explicit second-order communication profile already used in the exhaustive computations is precisely a finite-coordinate realization of the first refinement: its entries count degrees, length-two routes, common targets and common sources. 

# 3. Compactness of the finite-observation profile spaces

Give $\mathcal Z_0$ its bounded discrete metric.

Recursively equip

$$
\mathcal Z_{r+1}=
\mathcal Z_r
\times\mathcal P(\mathcal Z_r^2)
$$

with a product metric involving the Wasserstein metric on the probability-measure factor.

Because $\mathcal Z_0$ is finite and compact, induction gives

$$
\mathcal Z_r
\text{ is compact for every finite }r.
$$

Therefore

$$
\mathcal X_r=
\mathcal P(\mathcal Z_r)
$$

is also compact.

Every finite DAG is now represented by a point

$$
\mu_{G,r}\in\mathcal X_r.
$$

Consequently,

$$
\mathcal M_r=
\overline{
\bigcup_{n\ge1}
{
\mu_{G,r}:|V(G)|=n
}
}
$$

is a canonical compact finite-observation continuum profile space.

This already proves one part of continuum existence:

> For every fixed observation depth $r$, every sequence of finite DAG profiles has a convergent subsequence.

It does not yet prove convergence of the operational path process, but it proves that its candidate state space is compact.

# 4. Stability under one-node refinement

Suppose $H$ has $n+1$ nodes and $G=H-a$ is obtained by deleting one node.

For surviving ordered pairs $u,v\neq a$,

$$
z_0^H(u,v)=z_0^G(u,v).
$$

At the next refinement round, the empirical measure over intermediate nodes changes by removing one atom and renormalizing. Inductively,

$$
d_r\left(
z_r^H(u,v),
z_r^G(u,v)
\right)
\le
\frac{r}{n+1}
$$

up to an inessential metric-normalization constant.

At graph level, the pairs involving $a$ occupy the fraction

$$
\frac{2n+1}{(n+1)^2}
\le
\frac2{n+1}.
$$

A direct coupling therefore gives

$$
W_1\left(
\mu_{H,r},
\mu_{G,r}
\right)
\le
\frac{r+2}{n+1}.
$$

This is our first rigorous mesh estimate.

For fixed $r$,

$$
W_1(\mu_{H,r},\mu_{G,r})=
O(n^{-1}).
$$

For a diagonal limit $r=r_n$, vanishing profile jumps are guaranteed when

$$
r_n=o(n).
$$

Therefore stabilized 2-WL may be used in a continuum limit only after checking that its required stabilization depth grows sublinearly:

$$
r_{\mathrm{stab}}(n)=o(n).
$$

The eight-node result proves finite injectivity, but the per-class first-separation rounds must now be exported to estimate the growth of $r_{\mathrm{stab}}(n)$.

# 5. Node profiles for operational dynamics

The graph-level measure $\mu_{G,r}$ describes the whole system. The operational path process needs a profile attached to each current node.

Define the normalized node profile

$$
x_{G,r}(u)=
\frac1n
\sum_{v\in V(G)}
\delta_{
\left(
z_r^G(u,v),
z_r^G(v,u)
\right)
}.
$$

Thus

$$
x_{G,r}(u)
\in
\mathcal Y_r
:=
\mathcal P(\mathcal Z_r^2).
$$

Two nodes are close when their complete normalized relational views of the graph are close.

For an edge

$$
e:u\to w,
$$

the operational profile jump is

$$
\Delta_{G,r}(e)=
x_{G,r}(w)-x_{G,r}(u).
$$

Unlike the graph-level deletion increment, this edge increment is **not automatically small** as $n\to\infty$.

That gives a decisive test:

$$
|\Delta_{G_n,r}(e)|\to0
$$

is the condition for a local differential limit.

If a nonzero fraction of channel jumps remains macroscopic, the continuum limit is a jump or Lévy operator instead.

The limiting jump data determine whether the regime is Gaussian or anomalous.

# 6. Canonical finite-horizon route dynamics

Because finite DAGs have no positive adjacency eigenvalue, define the finite-horizon route-count functions

$$
R_0(v)=1,
$$

$$
R_{k+1}(v)=
\sum_{e:s(e)=v}R_k(r(e)).
$$

Thus

$$
R_k(v)=
\#\{
\text{resolved length-}k\text{ paths starting at }v
\}.
$$

For a simple DAG,

$$
R_k=A^k\mathbf1.
$$

For parallel channels, the adjacency entries contain their multiplicities.

On the active set $R_k(v)>0$, define

$$
P_k(e\mid v)=
\frac{
R_{k-1}(r(e))
}{
R_k(v)
}.
$$

Then

$$
\sum_{e:s(e)=v}P_k(e\mid v)=1.
$$

This kernel has an exact interpretation:

$$
P_k(e\mid v)=
\Pr(
\text{first edge is }e
\mid
\text{uniform resolved length-}k\text{ route from }v
).
$$

After traversing one edge, the remaining horizon changes from $k$ to $k-1$. Therefore

$$
(v,k)\longmapsto(r(e),k-1)
$$

is a genuine Markov process on the augmented finite-horizon state space.

No eigenvector, asymptotic limit or external probability law is required. It is simply normalized route counting.

# 7. Canonical route ensemble over the whole graph

Define the total number of length-$p$ routes:

$$
T_p(G)=
\sum_vR_p(v)=
\sum_{u,v}(A^p)_{uv}.
$$

Let

$$
L_j(v)=
\sum_u(A^j)_{uv}
$$

be the number of length-$j$ paths ending at $v$.

Under the uniform counting measure on all resolved length-$p$ paths, the probability that the path is at $v$ after $j$ steps is

$$
\rho_{p,j}(v)=
\frac{
L_j(v)R_{p-j}(v)
}{
T_p(G)
}.
$$

The probability that the path uses a particular edge $e:v\to w$ at step $j$ is

$$
\Pr_p(e\text{ at }j)=
\frac{
L_j(v)R_{p-j-1}(w)
}{
T_p(G)
}.
$$

For $A_{vw}$ parallel channels, summing over them introduces the factor $A_{vw}$.

This gives us exact finite formulas for every continuum coefficient.

# 8. Exact finite coefficient tensors

Choose finitely many cylindrical observables

$$
F_1,\ldots,F_d
$$

on the node-profile space $\mathcal Y_r$.

Define the coordinate vector

$$
X_{G,r}(u)=
\left(
F_1(x_{G,r}(u)),
\ldots,
F_d(x_{G,r}(u))
\right).
$$

For an edge $v\to w$,

$$
\Delta_{vw}=
X_{G,r}(w)-X_{G,r}(v).
$$

The exact $q$-th route-increment moment, averaged over all steps of all length-$p$ routes, is

$$
M_{n,p,r}^{(q)}=
\frac1{pT_p(G)}
\sum_{j=0}^{p-1}
\sum_{v,w}
L_j(v)
A_{vw}
R_{p-j-1}(w)
,
\Delta_{vw}^{\otimes q}.
$$

In particular,

$$
m_{n,p,r}=
M_{n,p,r}^{(1)}
$$

is the mean profile displacement per primitive channel, and

$$
Q_{n,p,r}=
M_{n,p,r}^{(2)}
$$

is the raw quadratic-variation tensor.

The centered covariance is

$$
C_{n,p,r}=
Q_{n,p,r}-
m_{n,p,r}\otimes m_{n,p,r}.
$$

These are exact finite sums. They can be computed without Monte Carlo sampling.

# 9. The scaling is now data-determined

Define the root-mean-square edge-profile scale

$$
\delta_{n,p,r}^2=
\operatorname{tr}C_{n,p,r}.
$$

The regime is determined by comparing the mean with this scale.

## Ballistic scaling

If

$$
|m_{n,p,r}|
\asymp
\delta_{n,p,r},
$$

then the natural time unit is

$$
a_{n,p,r}\asymp\delta_{n,p,r},
$$

and the quadratic variation disappears in the limit.

## Diffusive scaling

If

$$
|m_{n,p,r}|=
O(\delta_{n,p,r}^2),
$$

then

$$
a_{n,p,r}=
\delta_{n,p,r}^2
$$

produces finite drift and quadratic variation.

The coefficients are

$$
b
=
\lim
\frac{m_{n,p,r}}{\delta_{n,p,r}^2},
$$

$$
a
=
\lim
\frac{C_{n,p,r}}{\delta_{n,p,r}^2}.
$$

## Jump scaling

If

$$
\delta_{n,p,r}\not\to0
$$

or the scaled Lindeberg quantity does not vanish,

$$
\frac{
\mathbb E[
|\Delta|^2
\mathbf1_{\{|\Delta|>\varepsilon\}}
]
}{
\delta_{n,p,r}^2
}
\not\to0,
$$

then the limiting object is nonlocal.

The jump measure is obtained directly from the empirical edge-jump law.

# 10. Emergence of (h) and (\lambda)

The correct positive harmonic profile arises from finite route counts.

Suppose for a graph sequence and horizons $p_n\to\infty$, there are positive normalizations $c_{n,k}$ such that

$$
\frac{R_k^{(n)}}{c_{n,k}}
\longrightarrow
h
$$

on finite profile coordinates, and

$$
\frac{c_{n,k+1}}{c_{n,k}}
\longrightarrow
\lambda.
$$

Because

$$
R_{k+1}^{(n)}=
A_nR_k^{(n)},
$$

passing to the limit gives

$$
Ah=\lambda h.
$$

The asymptotic ratio limit of finite route-count vectors yields the infinite-volume positive eigenprofile.

A rootless global growth estimator is

$$
\lambda_{n,p}=
\frac{T_{p+1}(G_n)}{T_p(G_n)}.
$$

A local estimator is

$$
\lambda_{n,p}(v)=
\frac{R_{p+1}(v)}{R_p(v)}.
$$

The required bulk condition is that these ratios stabilize away from the path-horizon boundaries.

# 11. Finite-horizon boundary effects

The finite kernel

$$
P_k(e\mid v)
$$

depends on the remaining horizon $k$. Therefore the first candidate continuum generator may be nonautonomous.

Let

$$
s=\frac{j}{p}
\in[0,1].
$$

If the coefficient tensors converge to

$$
b(s,x),\qquad a(s,x),
$$

the limit equation is

$$
\partial_\tau f=
b(\tau,x)\cdot\nabla f
+
\frac12a(\tau,x):\nabla^2f.
$$

The autonomous master equation previously derived requires a stronger **bulk plateau condition**:

$$
P_k(e\mid v)
\longrightarrow
P_h(e\mid v)
$$

uniformly when both $k\to\infty$ and the distance from the terminal horizon diverges.

Equivalently, the coefficients measured in the middle portion

$$
\varepsilon p\le j\le(1-\varepsilon)p
$$

must become independent of $j/p$.

That is now a directly testable numerical condition.

# 12. Gauge coefficient from route growth

The per-edge route-growth parameter is

$$
\beta_{n,p}=
\log\frac{T_{p+1}}{T_p}.
$$

If one primitive edge represents $a_{n,p,r}$ continuum-time units, then the continuum gauge rate is

$$
\Omega_{n,p,r}=
\frac{
\beta_{n,p}-\beta_0
}{
a_{n,p,r}
},
$$

where $\beta_0$ is any nonvanishing bulk carrier removed in the interaction picture.

Thus

$$
\Omega=
\lim
\frac{
\log(T_{p+1}/T_p)-\beta_0
}{
a_{n,p,r}
}.
$$

This is the coefficient that enters

$$
Z_q=qI+i\Omega N.
$$

# 13. What the computation should output now

For every processed graph and every selected $p,r$, the next data pass should emit:

$$
\begin{aligned}
&n,\quad |E|,\quad \text{height},\quad |\operatorname{Aut}(G)|,\\
&r_{\mathrm{stab}}(G),\\
&\text{canonical hashes of }\mu_{G,r},\\
&T_p,\quad T_{p+1}/T_p,\\
&M^{(1)}_{n,p,r},\quad
M^{(2)}_{n,p,r},\quad
M^{(3)}_{n,p,r},\\
&\text{large-jump tail histogram},\\
&\text{coefficient profile versus }j/p.
\end{aligned}
$$

The first new global tables should be:

$$
c_{n,r}=
\#\{\text{distinct }r\text{-round profiles}\},
$$

$$
s_n(k)=
\#\{
G:r_{\mathrm{stab}}(G)=k
\},
$$

$$
\delta_{n,p,r}^2=
\operatorname{tr}C_{n,p,r},
$$

$$
\beta_{n,p}=
\log(T_{p+1}/T_p),
$$

and the scaled ratios

$$
\frac{|M^{(1)}|}{\delta},
\qquad
\frac{|M^{(1)}|}{\delta^2},
\qquad
\frac{|M^{(3)}|}{\delta^2}.
$$

Those three ratios immediately distinguish ballistic, Gaussian and non-Gaussian scaling.

# 14. The first concrete continuum theorem

For a sequence $G_n$, choose $r_n=o(n)$ and $p_n\to\infty$. Suppose:

$$
\delta_n^2=
\operatorname{tr}C_{n,p_n,r_n}
\to0,
$$

$$
\frac{M^{(1)}_{n,p_n,r_n}}{\delta_n^2}
\to b,
$$

$$
\frac{C_{n,p_n,r_n}}{\delta_n^2}
\to a,
$$

the Lindeberg quantity vanishes, the coefficient fields are tight on the compact profile spaces, and the finite-horizon bulk plateau exists.

Then the route-weighted node-profile process, rescaled by

$$
\tau=j\delta_n^2,
$$

converges—subject to uniqueness of the limiting martingale problem—to

$$
dX_\tau=
b(X_\tau),d\tau
+
\sigma(X_\tau),dW_\tau,
\qquad
\sigma\sigma^\mathsf T=a.
$$

If Lindeberg fails but the scaled edge-jump measures converge, the same construction yields the corresponding Lévy-type operator.

This gives the computable bridge:

$$
\text{finite DAG}
\to
\text{normalized pair profiles}
\to
\text{uniform resolved-route kernel}
\to
\text{exact increment tensors}
\to
\text{continuum coefficients}.
$$

Every quantity in that chain can be computed by dynamic programming and sparse profile hashing, without diagonalizing the nilpotent adjacency matrix or assuming the continuum regime in advance.
