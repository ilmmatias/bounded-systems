# 1. Transition kernel for state projection

The continuum ordered-gap route has spacing law

```math
(G_0,G_1,\ldots,G_p,G_{p+1})
\sim
\operatorname{Dirichlet}(1,2,\ldots,2,1).
```

Fix $0\leq r<p$ and set

```math
X_r=\sum_{j=0}^rG_j,
\qquad
k=p-r.
```

Dirichlet aggregation gives

```math
(X_r,G_{r+1},\ldots,G_p,G_{p+1})
\sim
\operatorname{Dirichlet}(2r+1,2,\ldots,2,1).
```

Conditional on $X_r=x$, neutrality of the Dirichlet law gives

```math
\left.
\frac{(G_{r+1},\ldots,G_p,G_{p+1})}{1-X_r}
\,\right|\,
X_r=x,r,p
\sim
\operatorname{Dirichlet}(2,\ldots,2,1).
```

The first coordinate therefore satisfies

```math
Z_{r,p}
:=
\frac{G_{r+1}}{1-X_r},
\qquad
Z_{r,p}\mid X_r,r,p
\sim
\operatorname{Beta}(2,2k-1).
```

If $f_k$ and $F_k$ denote its density and distribution function, then

```math
f_k(z)
=
(2k-1)(2k)z(1-z)^{2k-2},
\qquad 0<z<1,
```

and

```math
F_k(z)
=
1-(1-z)^{2k-1}\bigl(1+(2k-1)z\bigr).
```

The conditional law depends on the past only through $X_r$ and $k$. In
particular,

```math
F_k(Z_{r,p})
\perp\!\!\!\perp
\sigma(G_0,\ldots,G_r)
\mid (X_r,k),
```

and $F_k(Z_{r,p})$ is uniform on $[0,1]$.

# 2. Exact state projections

The comparison uses the common normalized positions

```math
\mathcal S
=
\left\{
\frac18,\frac28,\ldots,\frac78
\right\},
```

and, for each scale $m\in\{1,2,4\}$, the horizon family

```math
\mathcal P_m
=
\{16m,32m,64m,128m\}.
```

Every pair $(p,s)\in\mathcal P_m\times\mathcal S$ has equal design weight, with
$r=ps$ and $k=p-r$. Write $c=(p,r)$ for one such cell. The marginal source
density is

```math
b_c(x)
=
\operatorname{BetaPDF}
\bigl(x;2r+1,2(p-r)+1\bigr).
```

The Bayes-optimal clock-free projection under this design is

```math
q_0(z\mid x)
=
\frac{
\sum_c b_c(x)f_{k_c}(z)
}{
\sum_c b_c(x)
}.
```

The normalized-clock projection is

```math
q_s(z\mid x,s)
=
\frac{
\sum_{c:s_c=s} b_c(x)f_{k_c}(z)
}{
\sum_{c:s_c=s} b_c(x)
}.
```

These are exact projected conditional laws for the stated design. The exact
augmented state uses

```math
q_k(z\mid x,k)=f_k(z),
```

which equals the conditional law from the full Dirichlet path model. This
equality is an exact finite-horizon closure statement.

The unscaled fraction $Z_{r,p}$ contracts to zero as the horizon grows. The
route-time transition scale is retained by

```math
Y_{r,p}=pZ_{r,p}.
```

For cell $c$, its exact density is

```math
g_c(y)
=
\frac1p f_{k_c}\!\left(\frac yp\right),
\qquad 0<y<p.
```

The projected densities for $Y_{r,p}$ use the same posterior cell weights as
$q_0$ and $q_s$, with $f_{k_c}$ replaced by $g_c$. The exact augmented
predictor for this target uses $(X_r,r,p)$. The smaller state $(X_r,k)$ is
sufficient for $Z_{r,p}$ itself.

# 3. Held-out scores

For every $(m,p)$, $40{,}000$ independent Dirichlet paths were generated from
independent exponential variables. Even path indices form the training sample
and odd indices form the held-out sample. All seven transitions from one path
remain on the same side of the split. Each scale therefore contains $80{,}000$
held-out paths and $560{,}000$ held-out transitions.

For predictive density $q$, the logarithmic score is

```math
S(q)=\log q(Z_{r,p}\mid\text{state}),
```

with the corresponding transformed density used for $Y_{r,p}$. Score
differences are first averaged over the seven positions of each path. The
reported uncertainty is the ordinary standard error across these paired path
means.

For each held-out state and generating cell $c$, the distributional defect is

```math
W_1(q,c)
=
\int
\left|Q(t\mid\text{state})-F_c(t)\right|\,dt.
```

The integral is evaluated directly from the exact beta distribution functions.
The dependence of the projected mixture weights on $x$ is evaluated with $64$,
$128$, and $256$ uniform $x$-bins. The target integral uses steps
$2\times10^{-5}$, $10^{-4}$, and $10^{-3}$ on the successive fraction
intervals $[0,0.02]$, $[0.02,0.1]$, and $[0.1,1]$. The route-time integral uses
successively coarser steps after $2$, $10$, and $50$. The reported values use
$256$ source bins.

# 4. Conditional-law audit

The oracle probability transform has exact mean $1/2$ and variance $1/12$.
Direct samples give:

| $m$ | horizons | PIT mean | PIT variance | Kolmogorov distance | maximal conditional-mean error | $\operatorname{corr}(U,G_r/X_r)$ | $\operatorname{corr}(U,\sum_{j\leq r}(G_j/X_r)^2)$ |
| ---: | :--- | ---: | ---: | ---: | ---: | ---: | ---: |
| 1 | 16, 32, 64, 128 | $0.499721$ | $0.0832018$ | $0.0010370$ | $0.0011701$ | $-0.0000661$ | $-0.0005084$ |
| 2 | 32, 64, 128, 256 | $0.499010$ | $0.0833617$ | $0.0017520$ | $0.0013229$ | $-0.0001652$ | $0.0001501$ |
| 4 | 64, 128, 256, 512 | $0.500091$ | $0.0833580$ | $0.0009043$ | $0.0012871$ | $-0.0002209$ | $-0.0000605$ |

Here the maximal conditional-mean error is the maximum over the $28$ cells of

```math
\left|
\widehat{\mathbb E}Z_{r,p}
-
\frac{2}{2(p-r)+1}
\right|.
```

An independent exact audit checks the Dirichlet concentration algebra for
every $1\leq p\leq64$, the beta moments, and the probability transform from
$30{,}000$ independent beta samples.

# 5. Clock-free, normalized-clock, and exact augmented states

Let

```math
D_0=S(q_*)-S(q_0),
\qquad
D_s=S(q_*)-S(q_s),
```

where $q_*$ is the oracle. Positive values are losses relative to the full
conditional law. For the exact transition fraction:

| $m$ | $D_0$ | $D_s$ | $S(q_s)-S(q_0)$ | exact augmented loss |
| ---: | ---: | ---: | ---: | ---: |
| 1 | $0.369608\pm0.000984$ | $0.321329\pm0.000982$ | $0.048279\pm0.000506$ | $0$ |
| 2 | $0.339183\pm0.000975$ | $0.315397\pm0.000971$ | $0.023786\pm0.000354$ | $0$ |
| 4 | $0.320177\pm0.000960$ | $0.314198\pm0.000961$ | $0.005979\pm0.000172$ | $0$ |

Adding $s$ resolves part of the finite-horizon clock-free loss. At fixed $s$,
the concentration $2p(1-s)+1$ still varies with $p$, leaving a scale mixture.
The normalized-clock log loss consequently remains near $0.314$ under the
multiplicatively rescaled horizon families.

The corresponding Wasserstein defects are:

| $m$ | $W_1(q_0,q_*)$ for $Z$ | $W_1(q_s,q_*)$ for $Z$ | $W_1(q_0,q_*)$ for $Y$ | $W_1(q_s,q_*)$ for $Y$ |
| ---: | ---: | ---: | ---: | ---: |
| 1 | $0.048709\pm0.000081$ | $0.042632\pm0.000070$ | $0.278093\pm0.000738$ | $0.093716\pm0.000184$ |
| 2 | $0.024643\pm0.000041$ | $0.022863\pm0.000038$ | $0.151324\pm0.000573$ | $0.050836\pm0.000104$ |
| 4 | $0.012184\pm0.000020$ | $0.011865\pm0.000020$ | $0.064495\pm0.000359$ | $0.026599\pm0.000055$ |

The raw-$Z$ Wasserstein defects decrease because every compared law contracts
toward a point mass at zero. The log loss detects the unresolved scale mixture,
while the route-time target removes this contraction.

For $Y$, the $64$, $128$, and $256$ source-bin values for the clock-free state
are respectively

```math
(0.279607,0.278464,0.278093),
```

```math
(0.153114,0.151665,0.151324),
```

and

```math
(0.065941,0.064786,0.064495),
```

for $m=1,2,4$. The normalized-clock triples are

```math
(0.093965,0.093767,0.093716),
```

```math
(0.051055,0.050889,0.050836),
```

and

```math
(0.026897,0.026628,0.026599).
```

The largest change from $128$ to $256$ bins is $3.71\times10^{-4}$ for $Y$ and
$2.25\times10^{-5}$ for $Z$.

# 6. Route-time limit

Fix $s\in(0,1)$ and take $r=ps$. Since $k=p(1-s)$, the density of $Y_{r,p}$ is

```math
g_{p,s}(y)
=
\frac{(2k-1)(2k)}{p^2}
\,y
\left(1-\frac yp\right)^{2k-2}.
```

For fixed $y>0$,

```math
g_{p,s}(y)
\longrightarrow
4(1-s)^2y\exp\bigl(-2(1-s)y\bigr),
```

which is the density of a gamma law with shape $2$ and rate $2(1-s)$. Thus
$(X_r,s)$ is asymptotically sufficient for the route-time-scaled transition
under the stated interior-position limit. At finite horizon, the pooled law
retains the additional parameter $p$.

The sampled route-time log losses are:

| $m$ | clock-free loss | normalized-clock loss | normalized-clock gain |
| ---: | ---: | ---: | ---: |
| 1 | $0.023076\pm0.000255$ | $0.004260\pm0.000093$ | $0.018816\pm0.000234$ |
| 2 | $0.009078\pm0.000170$ | $0.001054\pm0.000050$ | $0.008024\pm0.000162$ |
| 4 | $0.002817\pm0.000098$ | $0.000164\pm0.000026$ | $0.002654\pm0.000095$ |

The clock-free loss also decreases. Indeed,

```math
X_r
\sim
\operatorname{Beta}(2r+1,2(p-r)+1),
```

with

```math
\mathbb E X_r\longrightarrow s,
\qquad
\operatorname{Var}(X_r)
=
\frac{s(1-s)}{2p}+O(p^{-2}).
```

On the fixed interior grid, $X_r$ itself recovers the normalized clock with
error of order $p^{-1/2}$. Hence the finite-horizon clock-free loss is
compatible with asymptotic clock recovery by $X_r$.

# 7. Route-history positive control

Two past-dependent summaries were retained:

```math
H_1=\frac{G_r}{X_r},
\qquad
H_2=\sum_{j=0}^r\left(\frac{G_j}{X_r}\right)^2.
```

For the exact augmented state, set

```math
U=F_k(Z_{r,p}).
```

The oracle density of $U$ is one. Training paths partition $H_1$, $H_2$, or
$(H_1,H_2)$ by empirical quantiles. Within each history class, a $16$-,
$32$-, or $64$-bin density for $U$ is fitted with pseudocount $1/2$. The
held-out history gain is

```math
\Delta_H
=
\log \widehat q(U\mid H).
```

Under the exact conditional law,

```math
\mathbb E\Delta_H
=
\int_0^1\log \widehat q(u\mid H)\,du
\leq 0
```

for every fitted density independent of the held-out path. A persistent
positive value would diagnose estimator error, implementation error, or
leakage.

All $27$ combinations of history state, history refinement, and target
refinement have nonpositive point estimates. The largest estimate and the
finest joint estimate are:

| $m$ | largest held-out $\Delta_H$ | associated PIT $W_1$ | joint $8\times8$, 64-bin $\Delta_H$ | associated PIT $W_1$ |
| ---: | ---: | ---: | ---: | ---: |
| 1 | $-0.0000118\pm0.0000072$ | $0.0002283$ | $-0.003184\pm0.000108$ | $0.002753$ |
| 2 | $-0.0000127\pm0.0000068$ | $0.0004205$ | $-0.003288\pm0.000108$ | $0.002553$ |
| 4 | $-0.0000252\pm0.0000090$ | $0.0007862$ | $-0.003437\pm0.000110$ | $0.003134$ |

The negative values at finer resolution are the held-out cost of estimating
more histogram probabilities. The exact augmented law closes on $(X_r,p-r)$,
and the direct Dirichlet paths have no residual memory conditional on that
state.

# 8. Exact and sampled verification

The C++ self-test reports $331$ checks of the Dirichlet sampler, conditional
moments, projected densities, and deterministic sample splitting. An
independent verifier reports $9602$ exact and sampled checks, including the
concentration algebra, beta formulas, numerical normalizations, probability
transforms, and held-out score identities.
