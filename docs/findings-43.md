# 1. Three separate refinement variables

Three indices must remain distinct: $n$ is the system size, $r$ is the
observation or 2-WL refinement depth, and $p$ is the resolved path horizon.

They play different roles:

* $n\to\infty$ constructs the continuum profile space;
* $r\to\infty$ removes the profile collapse observed in the enumeration of
  Section 1;
* $p\to\infty$ constructs the operational dynamics and asymptotic harmonic
  profile.

Exhaustive data show why $r$ matters: the second-order pair profile classifies
every non-isomorphic simple DAG through seven nodes; at eight nodes, one 2-WL
round leaves only $509$ collision classes containing $1020$ graphs, whereas
stabilized 2-WL separates all $20{,}286{,}025$ configurations.

Numerically,

```math
c_{8,1}=
20{,}286{,}025-(1020-509)=
20{,}285{,}514,
```

so one refinement round is missing only

```math
511
```

distinctions.

The enumeration establishes injectivity of the stabilized second-order profile
at eight nodes. Separation by two-dimensional refinement at every finite size
remains open.

The fraction of graphs involved in collisions is

```math
\frac{1020}{20{,}286{,}025}
\approx
5.03\times10^{-5},
```

or about $0.00503\%$.

At $n=8$, the pair profile is nearly injective, while stabilized refinement
is fully separating.

# 2. A normalized 2-WL profile space valid for every $n$

Because raw WL color integers are incomparable across graph sizes, use a
recursively normalized object.

Let

```math
\mathcal Z_0=
\{
=,\to,\leftarrow,\parallel
\}
```

be the four primitive ordered-pair relations.

For a DAG $G$ on $n$ nodes, define

```math
z_0^G(u,v)
\in\mathcal Z_0
```

from equality and immediate channel direction.

Now define recursively

```math
m_r^G(u,v)=
\frac1n
\sum_{w\in V(G)}
\delta_{
\left(
z_r^G(u,w),
z_r^G(w,v)
\right)
}.
```

The normalized empirical distribution records how a third node $w$ relates
to the ordered pair $(u,v)$.

Set $z_{r+1}^G(u,v)$ by

```math
z_{r+1}^G(u,v)=
\left(
z_r^G(u,v),
m_r^G(u,v)
\right).
```

The profile spaces satisfy

```math
\mathcal Z_{r+1}=
\mathcal Z_r
\times
\mathcal P(\mathcal Z_r^2).
```

At fixed $n$, multiplying $m_r$ by $n$ recovers the ordinary integer multiset
used by exact 2-WL. Across different $n$, the normalized measure remains
comparable.

The graph-level profile is

```math
\mu_{G,r}=
\frac1{n^2}
\sum_{u,v\in V(G)}
\delta_{z_r^G(u,v)}.
```

The normalized profile has the following properties:

* invariant under node relabeling;
* fixed ambient space for every $n$;
* equivalent to exact $r$-round 2-WL when $n$ is retained;
* naturally measure-valued;
* directly computable with sparse canonical hashes.

The explicit second-order communication profile used in the exhaustive
computations is precisely a finite-coordinate realization of the first
refinement, counting degrees, length-two routes, common targets, and common
sources.

# 3. Compactness of the finite-observation profile spaces

Give $\mathcal Z_0$ its bounded discrete metric.

Recursively equip

```math
\mathcal Z_{r+1}=
\mathcal Z_r
\times\mathcal P(\mathcal Z_r^2)
```

with a product metric involving the Wasserstein metric on the
probability-measure factor.

Because $\mathcal Z_0$ is finite and compact, induction gives

```math
\mathcal Z_r
\text{ is compact for every finite }r.
```

The space

```math
\mathcal X_r=
\mathcal P(\mathcal Z_r)
```

is also compact.

Every finite DAG is now represented by a point

```math
\mu_{G,r}\in\mathcal X_r.
```

The space

```math
\mathcal M_r=
\overline{
\bigcup_{n\ge1}
{
\mu_{G,r}:|V(G)|=n
}
}
```

is a canonical compact finite-observation continuum profile space.

The candidate continuum state space satisfies the following compactness
statement:

> For every fixed observation depth $r$, every sequence of finite DAG profiles
> has a convergent subsequence.

Convergence of the operational path process additionally requires control of
its transition laws.

# 4. Stability under one-node refinement

Suppose $H$ has $n+1$ nodes and $G=H-a$ is obtained by deleting one node.

For surviving ordered pairs $u,v\neq a$,

```math
z_0^H(u,v)=z_0^G(u,v).
```

At the next refinement round, removing one atom and renormalizing changes the
empirical measure over intermediate nodes. Inductively,

```math
d_r\left(
z_r^H(u,v),
z_r^G(u,v)
\right)
\le
\frac{r}{n+1}
```

up to an inessential metric-normalization constant.

At graph level, the pairs involving $a$ occupy the fraction

```math
\frac{2n+1}{(n+1)^2}
\le
\frac2{n+1}.
```

A direct coupling therefore gives

```math
W_1\left(
\mu_{H,r},
\mu_{G,r}
\right)
\le
\frac{r+2}{n+1}.
```

The estimate controls the refinement mesh.

For fixed $r$,

```math
W_1(\mu_{H,r},\mu_{G,r})=
O(n^{-1}).
```

For a diagonal limit $r=r_n$, vanishing profile jumps are guaranteed when

```math
r_n=o(n).
```

A diagonal limit that uses stabilized 2-WL therefore requires the chosen
sequence to satisfy

```math
r_{\mathrm{stab}}(n)=o(n).
```

This is a hypothesis on the sequence $G_n$ rather than a property of the
refinement. The eight-node result proves finite injectivity. Estimating the
growth of $r_{\mathrm{stab}}(n)$ requires the first-separation round for each
collision class.

# 5. Node profiles for operational dynamics

The graph-level measure $\mu_{G,r}$ describes the whole system. The
operational path process needs a profile attached to each current node.

Define the normalized node profile

```math
x_{G,r}(u)=
\frac1n
\sum_{v\in V(G)}
\delta_{
\left(
z_r^G(u,v),
z_r^G(v,u)
\right)
}.
```

Equivalently,

```math
x_{G,r}(u)
\in
\mathcal Y_r
:=
\mathcal P(\mathcal Z_r^2).
```

Two nodes are close when their complete normalized relational views of the
graph are close.

For an edge

```math
e:u\to w,
```

the operational profile jump is

```math
\Delta_{G,r}(e)=
x_{G,r}(w)-x_{G,r}(u).
```

Unlike the graph-level deletion increment, this edge increment is not
automatically small as $n\to\infty$.

The relevant test for a local differential limit is

```math
|\Delta_{G_n,r}(e)|\to0
```

If a nonzero fraction of channel jumps remains macroscopic, the continuum
limit is a jump or Lévy operator.

The limiting jump data determine whether the regime is Gaussian or anomalous.

# 6. Canonical finite-horizon route dynamics

Because finite DAGs have no positive adjacency eigenvalue, define the
finite-horizon route-count functions

```math
R_0(v)=1,
```

with the recursion

```math
R_{k+1}(v)=
\sum_{e:s(e)=v}R_k(r(e)).
```

Thus $R_k(v)$ is the number of resolved length-$k$ paths starting at $v$.

For a simple DAG,

```math
R_k=A^k\mathbf1.
```

For parallel channels, the adjacency entries contain their multiplicities.

On the active set $R_k(v)>0$, define

```math
P_k(e\mid v)=
\frac{
R_{k-1}(r(e))
}{
R_k(v)
}.
```

It follows that

```math
\sum_{e:s(e)=v}P_k(e\mid v)=1.
```

The kernel has the interpretation:

```math
P_k(e\mid v)=
\Pr(
\text{first edge is }e
\mid
\text{uniform resolved length-}k\text{ route from }v
).
```

After traversing one edge, the remaining horizon changes from $k$ to $k-1$.
Therefore

```math
(v,k)\longmapsto(r(e),k-1)
```

is a genuine Markov process on the augmented finite-horizon state space.

No eigenvector, asymptotic limit, or external probability law is required;
the kernel is normalized route counting.

# 7. Canonical route ensemble over the whole graph

Define the total number of length-$p$ routes:

```math
T_p(G)=
\sum_vR_p(v)=
\sum_{u,v}(A^p)_{uv}.
```

Let

```math
L_j(v)=
\sum_u(A^j)_{uv}
```

be the number of length-$j$ paths ending at $v$.

Under the uniform counting measure on resolved length-$p$ paths, the
probability of being at $v$ after $j$ steps is

```math
\rho_{p,j}(v)=
\frac{
L_j(v)R_{p-j}(v)
}{
T_p(G)
}.
```

The probability that the path uses a particular edge $e:v\to w$ at step $j$ is

```math
\Pr_p(e\text{ at }j)=
\frac{
L_j(v)R_{p-j-1}(w)
}{
T_p(G)
}.
```

For $A_{vw}$ parallel channels, summing over them introduces the factor
$A_{vw}$.

The kernel gives finite formulas for every continuum coefficient.

# 8. Exact finite coefficient tensors

Choose finitely many cylindrical observables

```math
F_1,\ldots,F_d
```

on the node-profile space $\mathcal Y_r$.

Define the coordinate vector

```math
X_{G,r}(u)=
\left(
F_1(x_{G,r}(u)),
\ldots,
F_d(x_{G,r}(u))
\right).
```

For an edge $v\to w$,

```math
\Delta_{vw}=
X_{G,r}(w)-X_{G,r}(v).
```

The exact $q$-th route-increment moment, averaged over all steps of all
length-$p$ routes, is

```math
M_{n,p,r}^{(q)}=
\frac1{pT_p(G)}
\sum_{j=0}^{p-1}
\sum_{v,w}
L_j(v)
A_{vw}
R_{p-j-1}(w)
,
\Delta_{vw}^{\otimes q}.
```

In particular,

```math
m_{n,p,r}=
M_{n,p,r}^{(1)}
```

is the mean profile displacement per primitive channel, and

```math
Q_{n,p,r}=
M_{n,p,r}^{(2)}
```

is the raw quadratic-variation tensor.

The centered covariance is

```math
C_{n,p,r}=
Q_{n,p,r}-
m_{n,p,r}\otimes m_{n,p,r}.
```

These are exact finite sums. They can be computed without Monte Carlo sampling.

# 9. The scaling is now data-determined

Define the root-mean-square edge-profile scale

```math
\delta_{n,p,r}^2=
\mathrm{tr}C_{n,p,r}.
```

The regime is determined by comparing the mean with this scale.

## Ballistic scaling

If

```math
|m_{n,p,r}|
\asymp
\delta_{n,p,r},
```

then the natural time unit is

```math
a_{n,p,r}\asymp\delta_{n,p,r},
```

and the quadratic variation disappears in the limit.

## Diffusive scaling

If

```math
|m_{n,p,r}|=
O(\delta_{n,p,r}^2),
```

it follows that

```math
a_{n,p,r}=
\delta_{n,p,r}^2
```

produces finite drift and quadratic variation.

The coefficients are

```math
b
=
\lim
\frac{m_{n,p,r}}{\delta_{n,p,r}^2},
```

and

```math
a
=
\lim
\frac{C_{n,p,r}}{\delta_{n,p,r}^2}.
```

## Jump scaling

If

```math
\delta_{n,p,r}\not\to0
```

or the scaled Lindeberg quantity does not vanish,

```math
\frac{
\mathbb E[
|\Delta|^2
\mathbf1_{\{|\Delta|>\varepsilon\}}
]
}{
\delta_{n,p,r}^2
}
\not\to0,
```

then the limiting object is nonlocal.

The jump measure is obtained directly from the empirical edge-jump law.

# 10. Emergence of $h$ and $\lambda$

The correct positive harmonic profile arises from finite route counts.

Suppose for a graph sequence and horizons $p_n\to\infty$, there are positive
normalizations $c_{n,k}$ such that

```math
\frac{R_k^{(n)}}{c_{n,k}}
\longrightarrow
h
```

on finite profile coordinates, and

```math
\frac{c_{n,k+1}}{c_{n,k}}
\longrightarrow
\lambda.
```

Because

```math
R_{k+1}^{(n)}=
A_nR_k^{(n)},
```

passing to the limit gives

```math
Ah=\lambda h.
```

The asymptotic ratio limit of finite route-count vectors yields the
infinite-volume positive eigenprofile.

A rootless global growth estimator is

```math
\lambda_{n,p}=
\frac{T_{p+1}(G_n)}{T_p(G_n)}.
```

A local estimator is

```math
\lambda_{n,p}(v)=
\frac{R_{p+1}(v)}{R_p(v)}.
```

The required bulk condition is that these ratios stabilize away from the
path-horizon boundaries.

# 11. Finite-horizon boundary effects

The finite kernel

```math
P_k(e\mid v)
```

depends on the remaining horizon $k$. Therefore the first candidate continuum
generator may be nonautonomous.

Define the rescaled time coordinate $s$ by

```math
s=\frac{j}{p}
\in[0,1].
```

If the coefficient tensors converge to

```math
b(s,x),\qquad a(s,x),
```

the limit equation is

```math
\partial_\tau f=
b(\tau,x)\cdot\nabla f
+
\frac12a(\tau,x):\nabla^2f.
```

The autonomous master equation previously derived requires a stronger bulk
plateau condition:

```math
P_k(e\mid v)
\longrightarrow
P_h(e\mid v)
```

uniformly when both $k\to\infty$ and the distance from the terminal horizon
diverges.

Equivalently, the coefficients measured in the middle portion

```math
\varepsilon p\le j\le(1-\varepsilon)p
```

must become independent of $j/p$.

# 12. A continuum theorem

For a sequence $G_n$, choose $r_n=o(n)$ and $p_n\to\infty$. Suppose:

```math
\delta_n^2=
\mathrm{tr}C_{n,p_n,r_n}
\to0,
```

the normalized mean displacement satisfies

```math
\frac{M^{(1)}_{n,p_n,r_n}}{\delta_n^2}
\to b,
```

the normalized covariance satisfies

```math
\frac{C_{n,p_n,r_n}}{\delta_n^2}
\to a,
```

the Lindeberg quantity vanishes, the coefficient fields are tight on compact
profile spaces, and the finite-horizon bulk plateau exists.

Then the route-weighted node-profile process, rescaled by

```math
\tau=j\delta_n^2,
```

converges, subject to uniqueness of the limiting martingale problem, to

```math
dX_\tau=
b(X_\tau)\,d\tau
+
\sigma(X_\tau)\,dW_\tau,
\qquad
\sigma\sigma^\mathsf T=a.
```

If Lindeberg fails but the scaled edge-jump measures converge, the same
construction yields the corresponding Lévy-type operator.

The computable bridge is:

```math
\text{finite DAG}
\to
\text{normalized pair profiles}
\to
\text{uniform resolved-route kernel}
\to
\text{exact increment tensors}
\to
\text{continuum coefficients}.
```

Dynamic programming and sparse profile hashing compute every quantity in that
chain, without diagonalizing the nilpotent adjacency matrix or assuming the
continuum regime in advance.

# 13. Gauge coefficient from route growth

The per-edge route-growth parameter is

```math
\beta_{n,p}=
\log\frac{T_{p+1}}{T_p}.
```

If one primitive edge represents $a_{n,p,r}$ continuum-time units, then the
continuum gauge rate is

```math
\Omega_{n,p,r}=
\frac{
\beta_{n,p}-\beta_0
}{
a_{n,p,r}
},
```

where $\beta_0$ is any nonvanishing bulk carrier removed in the interaction
picture. Explicitly,

```math
\Omega=
\lim
\frac{
\log(T_{p+1}/T_p)-\beta_0
}{
a_{n,p,r}
}.
```

The coefficient enters

```math
Z_q=qI+i\Omega N.
```

# 14. Literature relation

Sections 1 and 4 hold the refinement dimension fixed at two and let the round
depth $r$ grow. J.-Y. Cai, M. Fürer, and N. Immerman, *An optimal lower bound on
the number of variables for graph identification*, Combinatorica 12 (1992),
389-410, prove that $\Omega(n)$ variables are needed for graph identification,
and that the $k$-variable counting logic has exactly the distinguishing power of
$(k-1)$-dimensional Weisfeiler-Leman refinement. Taken together these give an
obstruction to the limit taken here: at fixed refinement dimension, increasing
the number of rounds does not separate all non-isomorphic graphs, since
separation across all sizes requires the dimension itself to grow with $n$.

The exhaustive computation reported in Section 1 concerns the single size
eight and is consistent with that lower bound. The lower bound leaves open the
narrower question recorded there: whether two-dimensional refinement separates
every finite size.

The growth of the stabilization depth is also constrained. M. Fürer,
*Weisfeiler-Lehman refinement requires at least a linear number of iterations*,
in Automata, Languages and Programming, Lecture Notes in Computer Science 2076,
Springer, 2001, 322-333, exhibits, for each fixed dimension, pairs requiring a
linear number of iterations, and the best available general upper bound for
two-dimensional refinement is the superlinear $O(n\log n)$ of M. Lichter,
I. Ponomarenko, and P. Schweitzer, *Walk refinement, walk logic, and the
iteration number of the Weisfeiler-Leman algorithm*, in 2019 34th Annual
ACM/IEEE Symposium on Logic in Computer Science, IEEE, 2019, 1-13,
arXiv:1905.03008. No sublinear stabilization bound is therefore available, and
the condition $r_{\mathrm{stab}}(n)=o(n)$ required in section 4 for a diagonal
limit is not supplied by either result.

All three results concern undirected graphs. Their realization inside the class
of acyclic digraphs used here, together with an $O(n\log n)$ upper bound on
that class, remains open.

The count $20{,}286{,}025$ used in section 1 is the number of acyclic digraphs
on eight unlabeled nodes, recorded as Sequence A003087, On-Line Encyclopedia of
Integer Sequences; the counting theory for unlabeled graphs and digraphs is
developed in F. Harary and E. M. Palmer, *Graphical Enumeration*, Academic
Press, 1973. That count fixes the number of isomorphism classes at eight nodes
and carries no refinement information; the collision figures $509$ and $1020$
come from the computation reported in section 1.
