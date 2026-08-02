# 1. Finite-DAG conditional transition

For each $N$, let $x_1,\ldots,x_N$ be independent uniform marks on $[0,1]$.
When $x_i<x_j$, the edge $i\to j$ is included independently with probability
$x_j-x_i$. Edges are always directed from the smaller mark to the larger
mark. A $p$-edge route is a sequence $(v_0,\ldots,v_p)$ satisfying
$v_r\to v_{r+1}$ for $0\leq r<p$.

For a sampled reference DAG $G_N$, let $F_m(v)$ count the $m$-edge routes
beginning at $v$. The forward recurrence and total route count are

```math
F_0(v)=1,
\qquad
F_m(v)=\sum_{v\to w}F_{m-1}(w),
\qquad
T_p(G_N)=\sum_v F_p(v).
```

Conditional on $G_N$ and $T_p(G_N)>0$, the sampled route is uniform among the
$p$-edge routes. The implementation draws its initial vertex according to

```math
\Pr(V_0=v\mid G_N,p)=\frac{F_p(v)}{T_p(G_N)},
```

and, at position $r$, draws an outgoing edge $v\to w$ according to

```math
\Pr(V_{r+1}=w\mid V_r=v,G_N,p)
=
\frac{F_{p-r-1}(w)}{F_{p-r}(v)}.
```

At each remaining horizon, the stable dynamic program normalizes the forward
vector and accumulates its logarithmic scale. The normalized vectors determine
the route probabilities used below.

Write $x_r$ for the latent mark of $V_r$, set $m=p-r$, and retain the interior
positions $1\leq r<p$. The predicted quantity is

```math
Z_{r,p}
:=
\frac{x_{r+1}-x_r}{1-x_r}.
```

The continuum reference law is

```math
Z_{r,p}\mid x_r,r,p
\sim
\operatorname{Beta}(2,2m-1),
```

whose distribution function will be denoted by

```math
C_m(z)
:=
1-(1-z)^{2m-1}\bigl(1+(2m-1)z\bigr).
```

Thus $(x_r,m)$ is the exact continuum closing state. The finite-DAG
experiment estimates the departure from this law and tests whether the
departure is reduced by current transverse coordinates or route history. Its
probability space contains the reference-DAG law and the uniform fixed-length
route law conditional on $G_N$.

# 2. Intrinsic state and history variables

For a vertex $v$, let $d^+(v)$ and $d^-(v)$ be its outgoing and incoming
degrees. The second-order coordinates are

```math
\begin{aligned}
q^{++}(v)&=\sum_{v\to w}d^+(w),
& q^{+-}(v)&=\sum_{v\to w}d^-(w),\\
q^{--}(v)&=\sum_{w\to v}d^-(w),
& q^{-+}(v)&=\sum_{w\to v}d^+(w).
\end{aligned}
```

The six-coordinate state is

```math
X_N(v)
:=
\left(
\frac{d^+(v)}N,
\frac{d^-(v)}N,
\frac{q^{++}(v)}{N^2},
\frac{q^{--}(v)}{N^2},
\frac{q^{+-}(v)}{N^2},
\frac{q^{-+}(v)}{N^2}
\right).
```

The intrinsic mark reconstruction and its continuum profile are

```math
\widehat x(v)
:=
\frac12+\frac{d^-(v)-d^+(v)}N,
```

and

```math
\chi(x)
:=
\left(
\frac{(1-x)^2}{2},
\frac{x^2}{2},
\frac{(1-x)^4}{24},
\frac{x^4}{24},
\frac18-\frac{x}{6}+\frac{x^4}{24},
\frac18-\frac{1-x}{6}+\frac{(1-x)^4}{24}
\right).
```

The fitted full current state is represented by

```math
\bigl(\widehat x_r,R_r\bigr),
\qquad
R_r
:=
\sqrt N\bigl(X_N(V_r)-\chi(\widehat x_r)\bigr).
```

The first two residual coordinates satisfy
$R_r^{(2)}-R_r^{(1)}=0$, since
$\widehat x_r-\frac12=X_N^{(2)}(V_r)-X_N^{(1)}(V_r)$ and
$\chi^{(2)}(\widehat x_r)-\chi^{(1)}(\widehat x_r)
=\widehat x_r-\frac12$. Comparing the full state with $\widehat x_r$
therefore tests the remaining five effective coordinates.

Set $s=r/p$, $\Delta x_j=x_j-x_{j-1}$, and
$\Delta\widehat x_j=\widehat x_j-\widehat x_{j-1}$. Every fitted model is
conditioned exactly on $m$. Its additional inputs are:

| model | inputs in addition to $m$ |
| :--- | :--- |
| `latent` | $x_r$ |
| `latent_age` | $x_r,s$, where $s=r/p$ |
| `latent_history` | $x_r,s,x_{r-1},(x_r-x_{r-1})/x_r,\sum_{j=1}^r(\Delta x_j/x_r)^2$ |
| `intrinsic_mark` | $\widehat x_r$ |
| `intrinsic_age` | $\widehat x_r,s$ |
| `intrinsic_history` | $\widehat x_r,s,\widehat x_{r-1},\Delta\widehat x_r,\sum_{j=1}^r(\Delta\widehat x_j)^2/(\widehat x_r^2+N^{-1})$ |
| `full_state` | $\widehat x_r,R_r$ |
| `full_age` | $\widehat x_r,R_r,s$ |
| `full_history` | the `full_age` inputs, $\widehat x_{r-1}$, $\Delta\widehat x_r$, the intrinsic quadratic history, and $R_{r-1}$ |

The first three validation models and the response $Z_{r,p}$ use latent marks.
Every graph-intrinsic model uses variables constructed from $X_N$ together
with the route-position quantities $m$ and $s$. The common Wasserstein audit
uses latent-$x_r$ strata solely to compare predicted laws on the same
ground-truth subsets.

# 3. Cross-fitted estimators and controls

Graphs with even and odd sample indices form the two held-out folds. All routes
from one graph remain in the same fold. Within every remaining horizon $m$, a
model first partitions its primary coordinate, $x_r$ or $\widehat x_r$, by
training quantiles. A greedy tree then partitions the auxiliary coordinates by
training multinomial likelihood. The target law within each resulting class is
a uniform-bin histogram with Dirichlet pseudocount $1/2$ per bin.

The four resolution triples

```math
(B,L,J)
\in
\{(8,2,32),(16,2,64),(16,4,64),(32,2,128)\}
```

specify primary bins, maximal auxiliary leaves per primary bin, and target
bins. Models without auxiliary coordinates use one leaf. The fitted trees,
bin boundaries, and probabilities use training graphs only.

For a held-out set $\mathcal D$ of response-feature pairs $(z,u)$, where $u$
contains the model inputs other than $m$, let
$\widehat f_M(\mathord\cdot\mid u,m)$ be the fitted histogram density. Its
logarithmic score is

```math
\mathcal S(M;\mathcal D)
:=
\frac1{|\mathcal D|}
\sum_{(z,u)\in\mathcal D}
\log \widehat f_M(z\mid u,m).
```

Let $M_1$ be an augmented model and $M_0$ its baseline. If
$\mathcal D_{\mathrm F}$ contains the finite-DAG responses, their held-out
score contrast is

```math
G^{\mathrm F}_{M_1:M_0}
:=
\mathcal S(M_1;\mathcal D_{\mathrm F})
-
\mathcal S(M_0;\mathcal D_{\mathrm F}).
```

Every finite transition record also carries an independent
$Z^{\mathrm C}\sim\operatorname{Beta}(2,2m-1)$. The same fitting procedure is
applied independently to these control responses, giving
$G^{\mathrm C}_{M_1:M_0}$. The control-corrected score contrast is

```math
\widetilde G_{M_1:M_0}
:=
G^{\mathrm F}_{M_1:M_0}-G^{\mathrm C}_{M_1:M_0}.
```

The control measures the held-out cost of estimating additional classes when
the response has no feature signal. Differences between the finite and
control histogram-approximation errors generally bias $\widetilde G$ as an
estimator of conditional mutual information. The raw held-out gain and the
corrected contrast are therefore reported separately.

For the distributional score, records are grouped by $m$ and by $16$ common
latent-$x_r$ bins. The predicted and empirical conditional distribution
functions are compared on a $256$-point target grid, and the groupwise
Wasserstein-$1$ values are averaged by held-out occupancy. A reduction is
baseline minus augmented, with the same finite-minus-control correction as for
the log score. Oracle PIT mean, variance, Kolmogorov distance, correlations,
and conditional moment errors are computed directly from $C_m(Z_{r,p})$.

The uncertainty unit is one graph. Every displayed uncertainty below is an
ordinary standard error across the $32$ independent graph samples. Route draws
from the same graph remain within that unit.

# 4. Parameter families

The principal sweep uses seed $20260817$, $32$ graph samples at each size, and
the same graphs in the fixed and joint families. The fixed family uses
$p\in\{8,16\}$. The joint family uses a half-horizon control and a primary
horizon with $p/\sqrt N\in[0.35,0.375]$:

```math
(N,p)
=
(512,8),(1024,12),(2048,16),(4096,24),(8192,32),
(16384,46),(32768,64).
```

The route counts per horizon are $3000$ for $N\leq2048$, $2500$ at $N=4096$,
and $2000$ thereafter. A separate seed $20260819$ supplies the focused
fixed-$p$ audit at

```math
N\in\{4096,8192,16384,32768\},
\qquad p=16,
```

with $10{,}000$ routes per graph.

# 5. Route support and intrinsic-mark recovery

All $32$ graphs at every reported $(N,p)$ contain routes at the requested
horizons. The focused-family reconstruction errors and route counts are:

| $N$ | node $\widehat x$ RMSE | route-weighted $\widehat x$ RMSE | $\log T_{16}$ |
| ---: | ---: | ---: | ---: |
| $4096$ | $0.007730\pm0.000299$ | $0.007720\pm0.000298$ | $56.3175\pm0.0133$ |
| $8192$ | $0.005310\pm0.000226$ | $0.005306\pm0.000226$ | $68.1261\pm0.0061$ |
| $16384$ | $0.0035134\pm0.0000683$ | $0.0035136\pm0.0000679$ | $79.9064\pm0.0030$ |
| $32768$ | $0.0026021\pm0.0000806$ | $0.0026036\pm0.0000808$ | $91.6926\pm0.0024$ |

An ordinary least-squares fit of log RMSE on log $N$ gives slope $-0.531$.
Its statistical scope is the four simulated sizes. The slope differs from
$-1/2$ by $0.031$, and the route-weighted and node RMSE means differ by at
most $1.0\times10^{-5}$.

# 6. Fixed-horizon continuum-law audit

The fixed-horizon audit compares the finite-DAG oracle score with its
independent Beta control on each graph. Empirical Wasserstein distance has a
positive sampling floor, so the paired finite-minus-control contrast is
reported:

| $N$ | routes per graph | $W_1^{\mathrm F}-W_1^{\mathrm C}$ | $D_{\mathrm{KS}}^{\mathrm F}-D_{\mathrm{KS}}^{\mathrm C}$ |
| ---: | ---: | ---: | ---: |
| $512$ | $3000$ | $0.0262114\pm0.0010725$ | $0.0432258\pm0.0034153$ |
| $1024$ | $3000$ | $0.0104736\pm0.0003926$ | $0.0154627\pm0.0009536$ |
| $2048$ | $3000$ | $0.0040902\pm0.0001826$ | $0.0055538\pm0.0006390$ |
| $4096$ | $2500$ | $0.0016008\pm0.0001186$ | $0.0032055\pm0.0005946$ |
| $8192$ | $2000$ | $0.0006336\pm0.0000798$ | $0.0007187\pm0.0004590$ |
| $16384$ | $2000$ | $0.0001819\pm0.0000696$ | $0.0005739\pm0.0003903$ |
| $32768$ | $2000$ | $0.0000700\pm0.0000841$ | $0.0002894\pm0.0005449$ |

The number of routes changes across these rows and gives each row a different
sampling floor. The focused family fixes the count at $10{,}000$ routes per
graph:

| $N$ | finite $W_1$ | control $W_1$ | paired excess $W_1$ | paired excess PIT KS |
| ---: | ---: | ---: | ---: | ---: |
| $4096$ | $0.0053840\pm0.0001169$ | $0.0028258\pm0.0000291$ | $0.0025582\pm0.0001177$ | $0.0050690\pm0.0006518$ |
| $8192$ | $0.0040739\pm0.0000782$ | $0.0027954\pm0.0000279$ | $0.0012785\pm0.0000856$ | $0.0026777\pm0.0004429$ |
| $16384$ | $0.0034949\pm0.0000496$ | $0.0028146\pm0.0000293$ | $0.0006803\pm0.0000574$ | $0.0015378\pm0.0002768$ |
| $32768$ | $0.0032048\pm0.0000339$ | $0.0028164\pm0.0000257$ | $0.0003885\pm0.0000423$ | $0.0009375\pm0.0002121$ |

At $N=32768$, the paired Wasserstein excess is positive by approximately
$9.2$ standard errors and resolves a finite-DAG departure from the continuum
Beta law. A descriptive log-log fit gives exponent $-0.907$ for this excess
and $-0.810$ for the corresponding PIT-KS excess. These exponents describe the
four simulated sizes. Resolving the leading finite-DAG correction requires an
analytic expansion or a conditional-law estimator with approximation error
below the observed $3.885\times10^{-4}$ Wasserstein excess.

At $N=32768$, the finite-DAG oracle PIT has mean
$0.499814\pm0.000236$ and variance
$0.0832435\pm0.0000450$, compared with $1/2$ and $1/12$. Its correlations with
$x_r$, $r/p$, and the latent quadratic history are respectively

```math
-0.00129\pm0.00101,
\qquad
-0.00109\pm0.00101,
\qquad
0.000297\pm0.000828.
```

The three correlations are within $1.3$ standard errors of zero. The maximal
conditional-mean and conditional-variance errors over the populated
$(m,x)$ audit strata are $0.04009\pm0.00299$ and
$0.01033\pm0.00081$. Taking a maximum over multiple strata contributes a
positive sampling bias. The maxima do not decrease monotonically at the last
two sizes.

# 7. Joint-growth audit

The joint family keeps $p/\sqrt N$ bounded away from zero while $p/N\to0$.
For the primary horizon at each size, the continuum-oracle comparison is:

| $N$ | $p$ | $p/\sqrt N$ | supported graphs | $\log T_p$ | paired excess $W_1$ | paired excess PIT KS |
| ---: | ---: | ---: | ---: | ---: | ---: | ---: |
| $512$ | $8$ | $0.3536$ | $32$ | $22.4821\pm0.0281$ | $0.0140500\pm0.0006609$ | $0.0175283\pm0.0018299$ |
| $1024$ | $12$ | $0.3750$ | $32$ | $31.9440\pm0.0276$ | $0.0084315\pm0.0002949$ | $0.0117817\pm0.0009434$ |
| $2048$ | $16$ | $0.3536$ | $32$ | $44.4761\pm0.0242$ | $0.0040902\pm0.0001826$ | $0.0055538\pm0.0006390$ |
| $4096$ | $24$ | $0.3750$ | $32$ | $63.3010\pm0.0183$ | $0.0023895\pm0.0001066$ | $0.0048534\pm0.0005663$ |
| $8192$ | $32$ | $0.3536$ | $32$ | $87.9267\pm0.0293$ | $0.0010144\pm0.0000731$ | $0.0019605\pm0.0004700$ |
| $16384$ | $46$ | $0.3594$ | $32$ | $124.2278\pm0.0276$ | $0.0004925\pm0.0000406$ | $0.0021721\pm0.0003571$ |
| $32768$ | $64$ | $0.3536$ | $32$ | $174.4177\pm0.0275$ | $0.0002611\pm0.0000288$ | $0.0015273\pm0.0002586$ |

Over all seven rows, the paired Wasserstein excess has descriptive exponent
$-0.981$. Both $N$ and $p$ vary along this sequence, and the target remains the
unscaled fraction $Z_{r,p}$, so the exponent describes this parameter path
rather than a general convergence rate. The decrease observed at fixed $p$
also occurs when $p$ grows proportionally to $\sqrt N$.

# 8. Intrinsic-mark substitution and transverse coordinates

The focused family supplies $4.8\times10^6$ held-out transitions at each size.
At the finest resolution $(32,2,128)$, positive log gain favors the first
state named in each comparison, as does positive Wasserstein reduction. The
`mark reconstruction` row compares latent $x_r$ against intrinsic
$\widehat x_r$. The `transverse state` row compares
$(\widehat x_r,R_r)$ against $\widehat x_r$.

| $N$ | comparison | raw finite log gain | Beta-control log gain | corrected log gain | corrected $W_1$ reduction |
| ---: | :--- | ---: | ---: | ---: | ---: |
| $4096$ | mark reconstruction | $-0.000696\pm0.000282$ | $-0.000034\pm0.000058$ | $-0.000661\pm0.000291$ | $-0.000001\pm0.000011$ |
| $4096$ | transverse state | $-0.020878\pm0.000248$ | $-0.013664\pm0.000091$ | $-0.007214\pm0.000271$ | $0.000064\pm0.000073$ |
| $8192$ | mark reconstruction | $-0.000300\pm0.000076$ | $-0.000070\pm0.000052$ | $-0.000230\pm0.000107$ | $-0.000007\pm0.000006$ |
| $8192$ | transverse state | $-0.014281\pm0.000126$ | $-0.013361\pm0.000126$ | $-0.000920\pm0.000092$ | $0.000071\pm0.000050$ |
| $16384$ | mark reconstruction | $-0.000009\pm0.000051$ | $-0.000153\pm0.000051$ | $0.000144\pm0.000071$ | $-0.000001\pm0.000004$ |
| $16384$ | transverse state | $-0.013243\pm0.000099$ | $-0.013544\pm0.000080$ | $0.000300\pm0.000073$ | $0.000072\pm0.000030$ |
| $32768$ | mark reconstruction | $-0.000138\pm0.000053$ | $0.000093\pm0.000051$ | $-0.000231\pm0.000073$ | $0.000004\pm0.000002$ |
| $32768$ | transverse state | $-0.013376\pm0.000134$ | $-0.013282\pm0.000080$ | $-0.000094\pm0.000099$ | $0.000014\pm0.000033$ |

The mark-substitution contrasts change sign. Their Wasserstein magnitude is
below $7.2\times10^{-6}$ at every displayed size, placing the predictive
difference between $x_r$ and $\widehat x_r$ below the resolution of these
comparisons.

At $N=32768$, the transverse-state corrected log gains from coarse to fine are

```math
0.0002455\pm0.0000367,
\quad
0.0001294\pm0.0000501,
\quad
0.0001813\pm0.0001105,
\quad
-0.0000940\pm0.0000993,
```

while the corrected Wasserstein reductions are

```math
-0.0001089\pm0.0000327,
\quad
-0.0000750\pm0.0000282,
\quad
-0.0000551\pm0.0000391,
\quad
0.0000140\pm0.0000331.
```

The signs reverse as the primary and target resolutions increase. The raw
held-out log gain is negative at every resolution because the additional
classes cost more than the available signal. The four tested resolutions
provide no common positive contrast for the five effective transverse
coordinates beyond $\widehat x_r$.

# 9. Route-history contrasts

At the finest focused resolution, the history comparisons are:

| $N$ | augmented history | raw finite log gain | corrected log gain | corrected $W_1$ reduction |
| ---: | :--- | ---: | ---: | ---: |
| $4096$ | latent | $-0.013251\pm0.000066$ | $-0.000158\pm0.000087$ | $0.000322\pm0.000039$ |
| $4096$ | intrinsic | $-0.013322\pm0.000060$ | $-0.000172\pm0.000079$ | $0.000339\pm0.000039$ |
| $4096$ | full state | $-0.000028\pm0.000035$ | $0.000643\pm0.000090$ | $0.000054\pm0.000017$ |
| $8192$ | latent | $-0.013224\pm0.000063$ | $-0.000156\pm0.000085$ | $0.000168\pm0.000040$ |
| $8192$ | intrinsic | $-0.013195\pm0.000056$ | $-0.000100\pm0.000096$ | $0.000171\pm0.000041$ |
| $8192$ | full state | $-0.000285\pm0.000052$ | $0.000440\pm0.000084$ | $0.000013\pm0.000009$ |
| $16384$ | latent | $-0.012926\pm0.000055$ | $0.000106\pm0.000067$ | $0.000104\pm0.000025$ |
| $16384$ | intrinsic | $-0.013119\pm0.000055$ | $-0.000135\pm0.000081$ | $0.000101\pm0.000024$ |
| $16384$ | full state | $-0.000484\pm0.000069$ | $0.000065\pm0.000087$ | $-0.000001\pm0.000007$ |
| $32768$ | latent | $-0.012936\pm0.000057$ | $0.000049\pm0.000074$ | $0.000077\pm0.000024$ |
| $32768$ | intrinsic | $-0.012984\pm0.000066$ | $0.000032\pm0.000067$ | $0.000068\pm0.000025$ |
| $32768$ | full state | $-0.000541\pm0.000075$ | $0.000243\pm0.000096$ | $0.000026\pm0.000015$ |

The raw logarithmic gains for the simple latent and intrinsic histories are
negative. Their fine-resolution corrected Wasserstein reductions decrease
with $N$, while their corrected log gains remain statistically consistent
with zero. The full-history correction has a positive log contrast at some
sizes, but its raw log gain is nonpositive throughout the grid and its
Wasserstein contrast changes with size and resolution. At $N=32768$, the
full-history corrected log gain is consistent with zero at the first three
resolutions and positive at the finest resolution.

At the largest joint case, $(N,p)=(32768,64)$, the coarsest corrected log
gains for latent, intrinsic, and full history are respectively

```math
-0.000040\pm0.000030,
\qquad
-0.000029\pm0.000040,
\qquad
-0.000049\pm0.000043.
```

The finest full-history corrected gain is
$0.000091\pm0.000106$. Its raw gain is
$-0.001145\pm0.000104$, and its corrected Wasserstein reduction is
$0.000016\pm0.000035$. The disagreement among resolutions and scores leaves
the Markov comparison unresolved.

These comparisons test coarsened predictive closure. Exact six-integer
signatures are singleton-degenerate over the sampled graphs. An asymptotic
closure claim requires a specified joint regime for $(N,p)$ and stability
under joint refinement of the source partition and target resolution.
Distinguishing a finite-memory contribution from histogram-control mismatch
also requires an ablation that adds only $X_N(V_{r-1})$ to the current-state
model, followed by matched target-resolution extrapolation.

# 10. Occupancy and nondegeneracy

The focused family contains $4.8\times10^6$ held-out transitions at each size.
Each cross-fit model is trained on $16$ graphs, or $2.4\times10^6$ transitions.
For `full_history`, the total number of classes over the $15$ remaining-horizon
fits and the smallest training class are:

| resolution $(B,L,J)$ | total classes | minimum at $N=4096$ | minimum at $N=8192$ | minimum at $N=16384$ | minimum at $N=32768$ |
| :--- | ---: | ---: | ---: | ---: | ---: |
| $(8,2,32)$ | $240$ | $4914$ | $4928$ | $4977$ | $4991$ |
| $(16,2,64)$ | $480$ | $2423$ | $2448$ | $2473$ | $2491$ |
| $(16,4,64)$ | $960$ | $145$ | $148$ | $155$ | $154$ |
| $(32,2,128)$ | $960$ | $1168$ | $1215$ | $1172$ | $1237$ |

The fitted predictors use the controlled classes in the table. The four-leaf
resolution has the smallest training classes, with minimum occupancy $145$.
Every sign change in Sections 8 and 9 therefore occurs on source classes with
at least $145$ training records.

# 11. Exact implementation audits

The executable self-test reports $84{,}843$ checks, including exact Beta
formula checks, sampled Beta moments, a three-route uniform sampler check, and
cross-fit invariants. The independent verifier reports $2509$ schema,
determinism, PIT-control, occupancy, paired-comparison, and oracle-excess
checks. The route sampler uses disjoint deterministic streams indexed by
master seed, sample, horizon, and route. Sample records are reduced in sample
order.
