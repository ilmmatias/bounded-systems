# 1. One-node deletion multiplicity

For

```math
G\in\mathfrak D_n,
\qquad
H\in\mathfrak D_{n+1},
```

define

```math
d(G,H)=
\left|\left\lbrace v\in V(H):H-v\cong G \right\rbrace\right|.
```

$d(G,H)$ counts how many vertices of $H$ can be deleted to obtain the
isomorphism class $G$.

It satisfies

```math
0\le d(G,H)\le n+1,
```

and

```math
\sum_{G\in\mathfrak D_n}d(G,H)=n+1.
```

The deletion multiplicities are obtained by the following procedure:

* take a canonical representative of $H$;
* delete each vertex $v$;
* canonically label $H-v$;
* look up its level-$n$ class ID;
* increment the corresponding deletion count.

The operator is sparse: every $H$ has at most $n+1$ predecessor classes.

# 2. Extension multiplicity

Deletion multiplicity is not yet the multiplicity of labeled one-node
extensions.

Let $a(G)=|\mathrm{Aut}(G)|$ be the automorphism-group size.

Fix a labeled representative of $G$ on $[n]$. Define $e(G,H)$ to be the
number of labeled DAGs on $[n+1]$ that:

* restrict exactly to the fixed labeled $G$ on $[n]$;
* belong to the unlabeled class $H$.

A double count gives

```math
e(G,H)=
d(G,H),
\frac{|\mathrm{Aut}(G)|}
{|\mathrm{Aut}(H)|}.
```

Although written as a ratio, this is always a nonnegative integer.

## Check for the empty DAG

For the empty DAGs $E_n,E_{n+1}$,

```math
d(E_n,E_{n+1})=n+1,
```

The automorphism groups have orders

```math
|\mathrm{Aut}(E_n)|=n!,
\qquad
|\mathrm{Aut}(E_{n+1})|=(n+1)!.
```

Equivalently,

```math
e(E_n,E_{n+1})=
(n+1)\frac{n!}{(n+1)!}
=1.
```

There is exactly one way to add an isolated labeled vertex.

The extension incidence matrix is therefore

```math
B_n(G,H)=e(G,H).
```

# 3. Exact labeled-history dimension

Define the dimension of an unlabeled DAG class by

```math
\dim(G)=
\frac{n!}{|\mathrm{Aut}(G)|}.
```

The value is the number of labeled realizations of $G$ on $[n]$.

The incidence matrices satisfy

```math
\dim(H)=
\sum_{G\in\mathfrak D_n}
\dim(G)e(G,H).
```

Indeed,

```math
\begin{aligned}
\sum_G\dim(G)e(G,H)
&=
\sum_G
\frac{n!}{a(G)}
d(G,H)\frac{a(G)}{a(H)}\\
&=
\frac{n!}{a(H)}
\sum_Gd(G,H)\\
&=
\frac{n!(n+1)}{a(H)}\\
&=
\frac{(n+1)!}{a(H)}.
\end{aligned}
```

The weighted number of paths from the empty graph to $H$ is precisely

```math
\left|\{\text{labeled realizations of }H\}\right|=
\dim(H).
```

The identity is a consistency check for the extension matrix.

# 4. Canonical down transition

Suppose a labeled realization of $H$ is given and one of its $n+1$ vertices
is deleted uniformly.

The probability that the resulting unlabeled graph is $G$ is

```math
D_n(H,G)=
\frac{d(G,H)}{n+1}.
```

Using the dimension and extension multiplicity,

```math
D_n(H,G)=
\frac{\dim(G)e(G,H)}{\dim(H)}.
```

The down transition is completely canonical:

```math
D_n(H,G)=
\frac{\dim(G)B_n(G,H)}{\dim(H)}=
\frac{d(G,H)}{n+1}.
```

It requires no ensemble choice and no positive eigenfunction.

A growth law coherent with respect to uniform one-node deletion therefore has
cotransition probabilities $D_n$.

# 5. Finite-horizon route counts on the configuration graph

Choose a terminal level $N$ and a nonnegative terminal weight

```math
w_N:\mathfrak D_N\to[0,\infty).
```

Define backward route counts by

```math
R_{N,N}(H)=w_N(H),
```

and recursively

```math
R_{n,N}(G)=
\sum_{H\in\mathfrak D_{n+1}}
e(G,H)R_{n+1,N}(H).
```

$R_{n,N}(G)$ is the weighted number of labeled one-node extension histories
from $G$ to level $N$.

The exact finite-horizon up transition is

```math
U_n^{N,w}(G,H)=
\frac{
e(G,H)R_{n+1,N}(H)
}{
R_{n,N}(G)
}.
```

Normalization follows:

```math
\sum_HU_n^{N,w}(G,H)=1.
```

The kernel is the whole-configuration analogue of the finite route kernel
inside a DAG.

# 6. Two canonical finite endpoint ensembles

The endpoint probability at level $N$ is proportional to

```math
\dim(H)w_N(H).
```

The two endpoint measures are:

## Uniform labeled DAG

Set $w_N(H)=1$.

It follows that

```math
\Pr(H)
\propto
\dim(H)=
\frac{N!}{|\mathrm{Aut}(H)|},
```

which is the distribution induced by uniform counting of labeled DAGs.

## Uniform unlabeled DAG class

Set $w_N(H)=\frac1{\dim(H)}$.

It follows that

```math
\Pr(H)\propto1,
```

so every isomorphism class at level $N$ is equally weighted.

These are distinct measures, both computable by the finite-horizon machinery.

More general $w_N$ can select a profile region, height window, edge-density
window, or candidate Martin-boundary sector.

# 7. Coherent level measures

Define $Z_{N,w}$ by

```math
Z_{N,w}=R_{0,N}(\varnothing).
```

The probability of occupying class $G\in\mathfrak D_n$ is

```math
\mu_n^{N,w}(G)=
\frac{
\dim(G)R_{n,N}(G)
}{
Z_{N,w}
}.
```

It follows that

```math
\mu_n^{N,w}(G)U_n^{N,w}(G,H)=
\mu_{n+1}^{N,w}(H)D_n(H,G).
```

Indeed, both sides equal

```math
\frac{
\dim(G)e(G,H)R_{n+1,N}(H)
}{
Z_{N,w}
}.
```

The identity gives exact forward and backward consistency, an implementation
audit, and a finite approximation to the central measures on the infinite
Bratteli boundary.

If, as $N\to\infty$,

```math
R_{n,N}(G)
```

converges after normalization to $h_n(G)$, then

```math
h_n(G)=
\sum_He(G,H)h_{n+1}(H)
```

and

```math
U_n^h(G,H)=
\frac{e(G,H)h_{n+1}(H)}{h_n(G)}.
```

The graph-profile process is a positive harmonic transform unavailable from
any single finite nilpotent adjacency matrix.

# 8. The canonical graph-profile process

Let $x_{n,r}(G)=\mu_{G,r}$ be the normalized graph-level refinement profile
at observation depth $r$.

Under the up transition $U_n^h$, define

```math
X_n=x_{n,r}(G_n).
```

For an extension $G\to H$, let

```math
\Delta_{n,r}(G,H)=
x_{n+1,r}(H)-x_{n,r}(G).
```

From the one-node stability estimate,

```math
|\Delta_{n,r}(G,H)|
\le
\frac{C_r}{n+1},
```

with $C_r$ growing at most linearly in $r$ under the recursive profile metric.

Thus the whole-graph profile process has automatically vanishing jumps at
every fixed observation depth.

By contrast, edge jumps in the internal node-profile process need not shrink.

# 9. Scaled increment

The scaled one-step increment is

```math
F_{n,r}(G,H)=
(n+1)\Delta_{n,r}(G,H).
```

The $F_{n,r}$ remain uniformly bounded at fixed $r$.

The conditional mean scaled increment is

```math
b_{n,r}^h(G)=
\sum_H
U_n^h(G,H)
F_{n,r}(G,H).
```

The conditional covariance is

```math
a_{n,r}^h(G)=
\sum_H
U_n^h(G,H)
\left(
F_{n,r}(G,H)-b_{n,r}^h(G)
\right)^{\otimes2}.
```

Likewise, the conditional third cumulant is

```math
c_{n,r}^{(3),h}(G)=
\sum_HU_n^h(G,H)
\left(
F_{n,r}(G,H)-b_{n,r}^h(G)
\right)^{\otimes3}.
```

Every term is computable from the sparse extension incidence, the
finite-horizon route counts, and the normalized graph profiles.

# 10. The size continuum is generically hydrodynamic

The actual profile recursion has the form

```math
X_{n+1}=
X_n
+
\frac1{n+1}
F_{n,r}(G_n,G_{n+1}).
```

Therefore the conditional increment is

```math
\mathbb E[
X_{n+1}-X_n\mid G_n
]
=
\frac1{n+1}b_{n,r}^h(G_n),
```

while

```math
\mathrm{Cov}(
X_{n+1}-X_n\mid G_n
)
=
\frac1{(n+1)^2}a_{n,r}^h(G_n).
```

The scaling consequence is obtained by defining logarithmic size time as

```math
s_n=
\sum_{k=n_0}^{n-1}\frac1{k+1}=
\log\frac n{n_0}+o(1),
```

then over one unit of $s$:

* the drift accumulates at order one;
* the raw noise accumulates only at order $1/n$.

Hence the unscaled graph profile generically converges to a deterministic
hydrodynamic flow, not to a diffusion:

```math
\frac{dx}{ds}=b_r^h(x).
```

The stochastic diffusion appears in the fluctuations around this
hydrodynamic law.

# 11. Failure of direct graph-profile diffusion

A one-node extension produces a jump of order

```math
\frac1n.
```

Its variance is therefore order

```math
\frac1{n^2}.
```

If $a_n=1/n^2$ were used directly as the continuum-time increment, the
total future time would be:

```math
\sum_{n=n_0}^\infty\frac1{n^2}<\infty.
```

One-node graph growth cannot produce an indefinitely evolving raw diffusion
at the graph-profile level under that clock.

The correct hierarchy is instead

```math
\text{law of large numbers}
\to
\text{deterministic profile flow},
```

followed by

```math
\text{central-limit scaling}
\to
\text{Gaussian fluctuation diffusion}.
```

The fluctuation scaling separates:

* continuum evolution of the macroscopic profile;
* stochastic evolution of finite-size fluctuations.

# 12. Hydrodynamic limit theorem

Fix $r$. Assume that whenever

```math
x_{n,r}(G_n)\to x,
```

one has

```math
b_{n,r}^h(G_n)\to b_r^h(x)
```

uniformly on relevant profile regions.

Assume in addition that $b_r^h$ is bounded and Lipschitz on those regions and
that the increment noise is a martingale difference with uniformly bounded
second moments.

Then the interpolation of $X_n$ in logarithmic size time converges to

```math
\dot x(s)=b_r^h(x(s)).
```

A fixed point satisfies

```math
b_r^h(x_\ast)=0.
```

Such a point is a scale-invariant limiting graph profile under the chosen
harmonic boundary sector.

The Jacobian

```math
J_r=
Db_r^h(x_\ast)
```

is the first concrete spectral object in the continuum construction.

Its eigenvalues determine which profile perturbations:

* decay under size refinement;
* persist as neutral moduli;
* grow and destabilize the candidate fixed profile.

# 13. Gaussian fluctuation limit

Let $x(s)$ solve the hydrodynamic equation.

Define the rescaled fluctuation process

```math
Y_n=
\sqrt n,
\left(
X_n-x(s_n)
\right).
```

The factor $\sqrt n$ is forced by the one-step variance $O(n^{-2})$.

Suppose that the covariance coefficients satisfy

```math
a_{n,r}^h(G_n)\to a_r^h(x),
```

that the conditional Lindeberg condition holds, and that the drift admits a
differentiable limit.

Then the candidate fluctuation SDE is

```math
dY_s=
\left[
Db_r^h(x(s))
+\frac12I
\right]Y_s\,ds
+
\sigma_r^h(x(s))\,dW_s,
```

where

```math
\sigma_r^h(\sigma_r^h)^\mathsf T=
a_r^h.
```

The additional

```math
\frac12I
```

comes from differentiating the changing normalization $\sqrt n$.

At a fixed profile $x_\ast$,

```math
dY_s=
\left(
J_r+\frac12I
\right)Y_s\,ds
+
\sigma_\ast\,dW_s.
```

Define the positive relaxation operator, when stable, by

```math
B_r=
-\left(
J_r+\frac12I
\right).
```

The covariance equation identifies the one-particle operator $B_h$:

```math
B_h=
\lim_{r\to\infty}B_r
```

on compatible cylinder sectors, provided that projective limit exists.

The spectral problem is now concrete:

```math
\text{estimate }Db_r^h(x_\ast)
\text{ from finite extension data}.
```

# 14. Stationary fluctuation covariance

If $B_r$ is stable, with spectrum in the open right half-plane, the OU
covariance $C_r$ satisfies the Lyapunov equation

```math
B_rC_r+C_rB_r^\mathsf T=
a_r^h(x_\ast).
```

Equivalently,

```math
C_r=
\int_0^\infty
e^{-sB_r}
a_r^h(x_\ast)
e^{-sB_r^\mathsf T}\,ds.
```

The matrix gives direct numerical access to the fluctuation metric, the
dominant covariance directions, the spectral gap, and neutral or nearly
neutral modes.

The second-quantized generator from the candidate stage is then

```math
d\Gamma(B_r).
```

No phenomenological fitting is needed once $J_r$ and $a_r^h$ are extracted.

# 15. Exact streaming construction of the incidence operator

The incidence pass can be implemented level by level.

```text
for each H in DAG_classes[n + 1]:
    counts = empty map G_id -> deletion_count

    for each vertex v of H:
        G_deleted = delete_vertex(H, v)
        G_id = canonical_id_at_level_n(G_deleted)
        counts[G_id] += 1

    for each (G_id, d) in counts:
        aut_G = automorphism_size[G_id]
        aut_H = automorphism_size[H.id]

        numerator = d * aut_G
        assert(numerator % aut_H == 0)

        e = numerator / aut_H

        emit_incidence(
            level=n,
            predecessor=G_id,
            successor=H.id,
            deletion_multiplicity=d,
            extension_multiplicity=e
        )
```

Required audits are

```math
\sum_Gd(G,H)=n+1
```

for every $H$, and

```math
\sum_G\dim(G)e(G,H)=\dim(H)
```

for every $H$.

The second follows from the first but is useful for detecting automorphism
or integer-overflow errors.

# 16. Backward finite-horizon dynamic program

The route counts are computed backward from the sparse incidence files.

```text
for H in level[N]:
    R[N][H] = terminal_weight(H)

for n = N - 1 down to 0:
    initialize R[n][G] = 0 for all G in level[n]

    stream incidence edges (G -> H, multiplicity e):
        R[n][G] += e * R[n + 1][H]
```

Then stream the same incidence file to compute

```math
U_n^{N,w}(G,H)=
\frac{eR_{n+1,N}(H)}{R_{n,N}(G)}.
```

The counts quickly require arbitrary-precision arithmetic. Normalized log
weights suffice when the required outputs are probabilities and coefficient
moments.

# 17. Streaming coefficient accumulation

For each incidence edge $G\to H$, compute the scaled profile increment

```math
F=(n+1)(x_{n+1,r}(H)-x_{n,r}(G)).
```

Its conditional transition weight is

```math
u=
\frac{eR_{n+1,N}(H)}{R_{n,N}(G)}.
```

Accumulate per predecessor $G$:

```text
mean[G] += u * F
raw_second[G] += u * outer(F, F)
raw_third[G] += u * tensor3(F)
```

After completing the row:

```math
b_{n,r}(G)=\text{mean}[G],
```

The conditional covariance is

```math
a_{n,r}(G)=
\text{raw\_second}[G]-
b_{n,r}(G)b_{n,r}(G)^\mathsf T.
```

The global level averages are

```math
\overline b_{n,r}=
\sum_G\mu_n(G)b_{n,r}(G),
```

Averaging over the ensemble gives

```math
\overline a_{n,r}=
\sum_G\mu_n(G)a_{n,r}(G).
```

But the state-dependent values must also be retained to reconstruct
$b_r(x)$ and $a_r(x)$.

# 18. Estimating the Jacobian from finite data

Near a candidate fixed profile $x_\ast$, the conditional scaled increments
are regressed against profile displacement.

For classes $G$ near $x_\ast$,

```math
b_{n,r}(G)
\approx
b_r(x_\ast)
+
J_r\left(
x_{n,r}(G)-x_\ast
\right).
```

At a fixed point,

```math
b_r(x_\ast)=0,
```

so a weighted least-squares estimator of $J_r$ is

```math
\widehat J_r=
\left[
\sum_G\mu_n(G)b_{n,r}(G)
\delta x_G^\mathsf T
\right]
\left[
\sum_G\mu_n(G)
\delta x_G\delta x_G^\mathsf T
\right]^+,
```

where

```math
\delta x_G=x_{n,r}(G)-x_\ast
```

and $+$ denotes the Moore-Penrose pseudoinverse.

The fluctuation relaxation matrix is then

```math
\widehat B_r=
-\left(
\widehat J_r+\frac12I
\right).
```

The matrix is a directly computable spectral object for the continuum theory.

# 19. Literature relation

The configuration graph of sections 4 to 7, graded by node count with finite
levels $\mathfrak D_n$, the down transitions $D_n$, the coherence identity
between $\mu_n^{N,w}U_n^{N,w}$ and $\mu_{n+1}^{N,w}D_n$, and the central
measures on the infinite boundary named in section 8, are the objects studied in
A. M. Vershik, *Equipped graded graphs, projective limits of simplices, and
their boundaries*, Journal of Mathematical Sciences 209 (2015), 860-873,
arXiv:1503.04447, with the diagrams of O. Bratteli, *Inductive limits of finite
dimensional $C^\ast$-algebras*, Transactions of the American Mathematical
Society 171 (1972), 195-234. In that setting the cotransition probabilities are
part of the given data, tail equivalence and the Martin compactification are
taken with respect to them, and the boundary is obtained as a projective limit
of simplices. Here $D_n$ is not given but computed in section 4 from uniform
one-node deletion, through $\dim$ and the extension multiplicity, and the
constructions of sections 5 to 7 are carried out at a finite terminal level $N$
with weight $w_N$, so they approximate rather than realize that projective
limit.

The recursion $X_{n+1}=X_n+F_{n,r}/(n+1)$ of section 10 is a Robbins-Monro
recursion with step $1/(n+1)$, and the logarithmic size time $s_n$ used there
and in section 12 is its associated time change $\sum\gamma_k$, as treated in
M. Benaïm, *Dynamics of stochastic approximation algorithms*, in Séminaire de
Probabilités XXXIII, Lecture Notes in Mathematics 1709, Springer, 1999, 1-68.
What that source supplies is the law of large numbers, the convergence of the
interpolated recursion to the flow of $b_r^h$ asserted in section 12; it does
not supply the fluctuation limit.

The fluctuation statement of section 13 is of the type established in
V. Fabian, *On asymptotic normality in stochastic approximation*, Annals of
Mathematical Statistics 39 (1968), 1327-1332, for the normalization $\sqrt n$.
The shift of the drift by $\frac12I$ is obtained in section 13 by
differentiating that normalization along the logarithmic time change, and is not
read off from that source; the Lindeberg and covariance-convergence hypotheses
listed in section 13 remain assumptions on the extension data.
