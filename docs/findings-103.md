# 1. Reference-sector samples and intrinsic coordinates

For each sample, independent marks $x_i$ are uniform on $[0,1]$. After sorting
the vertices by mark, the edge $i\to j$ with $x_i<x_j$ is included
independently with probability $x_j-x_i$. The resulting graph is acyclic by
construction.

Independent deterministic streams determine the marks and pair decisions. For
the calibration across vertex counts, samples with the same index are nested:
increasing $N$ retains all earlier marks and pair decisions.

For a vertex $u$, let $d^+(u)$ and $d^-(u)$ be its outgoing and incoming
degrees, and set

```math
\begin{aligned}
q^{++}(u)&=\sum_{u\to v}d^+(v),
& q^{+-}(u)&=\sum_{u\to v}d^-(v),\\
q^{--}(u)&=\sum_{v\to u}d^-(v),
& q^{-+}(u)&=\sum_{v\to u}d^+(v).
\end{aligned}
```

The state supplied to every closure and coefficient estimator is

```math
X_N(u)=
\left(
\frac{d^+(u)}N,
\frac{d^-(u)}N,
\frac{q^{++}(u)}{N^2},
\frac{q^{--}(u)}{N^2},
\frac{q^{+-}(u)}{N^2},
\frac{q^{-+}(u)}{N^2}
\right).
```

The latent marks do not enter $X_N$, its partitions, the finite route bridge,
or any closure defect. They are retained only for separate reference-sector
checks. The continuum coordinate used in that audit is

```math
\chi(x)=
\left(
\frac{(1-x)^2}{2},
\frac{x^2}{2},
\frac{(1-x)^4}{24},
\frac{x^4}{24},
\frac18-\frac{x}{6}+\frac{x^4}{24},
\frac18-\frac{1-x}{6}+\frac{(1-x)^4}{24}
\right).
```

The total coordinate RMSE against $\chi$ decreases from
$0.0222953\pm0.0003422$ at $N=512$ to $0.00555059\pm0.0000810$ at $N=8192$.
The mark reconstructed from the graph is

```math
\widehat x(u)=\frac12+\frac{d^-(u)-d^+(u)}N,
```

with RMSE $0.0219804\pm0.0004290$ and $0.00544334\pm0.0001034$ at those two
sizes. These are ground-truth validation statistics rather than inputs to the
numerical state.

# 2. Stable route bridge

Let $F_k(v)$ be the number of directed routes of $k$ edges beginning at $v$,
and let $B_k(v)$ be the corresponding number ending at $v$. The dynamic
programs are

```math
F_0(v)=B_0(v)=1,
```

```math
F_{k+1}(v)=\sum_{v\to w}F_k(w),
\qquad
B_{k+1}(w)=\sum_{v\to w}B_k(v).
```

Their common total is

```math
T_k=\sum_v F_k(v)=\sum_v B_k(v).
```

Every level is divided by its sum, and the logarithm of that scale is
accumulated. The numerical representation therefore consists of unit-sum
vectors and $\log T_k$. Each reported count is represented by its natural
logarithm and by a base-$10$ mantissa and exponent.

For a uniformly selected route of $p$ edges and route position $0\leq r<p$,
the node occupancy, conditional transition, and edge flow are

```math
\mu_{p,r}(v)=\frac{B_r(v)F_{p-r}(v)}{T_p},
```

```math
P_{p,r}(v,w)
=
\mathbf 1_{\{v\to w\}}
\frac{F_{p-r-1}(w)}{F_{p-r}(v)},
```

and

```math
f_{p,r}(v,w)=\mu_{p,r}(v)P_{p,r}(v,w).
```

The formulas are evaluated from the normalized vectors with their accumulated
scales. They satisfy

```math
\sum_v\mu_{p,r}(v)=1,
\qquad
\sum_wP_{p,r}(v,w)=1
```

on the route-relevant support. If

```math
W_e=T_p\sum_{r=0}^{p-1}f_{p,r}(e),
```

then the exact route-flow identity is

```math
\sum_eW_e=pT_p.
```

The numerical audit checks the equivalent unit-flow identity at every
position, together with forward-backward count agreement and every conditional
row sum.

# 3. Coefficient, jump, plateau, and closure estimators

Write $\Delta X=X_N(w)-X_N(v)$ on a route transition. The global expectation
first samples $r$ uniformly from $\{0,\ldots,p-1\}$ and then samples the
transition from $f_{p,r}$. The reported quantities are the mean, raw second
moment, covariance, and raw and centered symmetric third moments:

```math
b_{N,p}=\mathbb E_{N,p}[\Delta X],
```

```math
M_{N,p}^{(2)}=\mathbb E_{N,p}[\Delta X\Delta X^{\mathsf T}],
\qquad
A_{N,p}=M_{N,p}^{(2)}-b_{N,p}b_{N,p}^{\mathsf T},
```

and

```math
M_{N,p}^{(3)}=\mathbb E_{N,p}[\Delta X^{\otimes3}],
\qquad
K_{N,p}^{(3)}=\mathbb E_{N,p}[(\Delta X-b_{N,p})^{\otimes3}].
```

The same mean and covariance are evaluated separately at every route position.
The scalar normalization is

```math
\alpha_{N,p}=\operatorname{tr}A_{N,p}.
```

For the Euclidean jump $J=\lVert\Delta X\rVert_2$, the diagnostics are

```math
\frac{\max J}{\sqrt{\alpha_{N,p}}},
\qquad
L_{N,p}(\varepsilon)
=
\frac{\mathbb E_{N,p}[J^2\mathbf 1_{\{J>\varepsilon\}}]}
{\alpha_{N,p}},
```

and

```math
\frac{\lVert M_{N,p}^{(3)}\rVert_F}{\alpha_{N,p}},
\qquad
\frac{\lVert K_{N,p}^{(3)}\rVert_F}{\alpha_{N,p}}.
```

Tensor norms include the multiplicities represented by the stored
lexicographic symmetric entries.

For a bulk fraction $\eta$, the bulk positions are

```math
\mathcal B_{p,\eta}
=
\{\lceil\eta p\rceil,\ldots,\lfloor(1-\eta)p\rfloor\}.
```

Let $b_{p,r}$ and $A_{p,r}$ denote the position-resolved mean and covariance,
and let bars denote their averages over $\mathcal B_{p,\eta}$. The two
coefficient-plateau defects are

```math
D_b=\max_{r\in\mathcal B_{p,\eta}}
\frac{\lVert b_{p,r}-\overline b\rVert_2}{\alpha_{N,p}},
```

```math
D_A=\max_{r\in\mathcal B_{p,\eta}}
\frac{\lVert A_{p,r}-\overline A\rVert_F}{\alpha_{N,p}}.
```

The reported coefficient defect is $\max(D_b,D_A)$. It tests constancy after
the common time normalization while retaining the route-position dependence.

Exact six-integer signatures are too sparse to test closure. In every one of
the $648$ distinct graph samples, all $N$ signatures were singletons. The exact
partition is therefore degenerate.

For a controlled finite-sample replacement, each of the six normalized
coordinates is placed in one of $q\in\{8,16,32\}$ fixed uniform bins. Let
$C_q(v)$ be the resulting class. At position $r$, the exact
vertex-conditioned law on target classes is

```math
p_{v,r}(c)=\sum_{w:C_q(w)=c}P_{p,r}(v,w).
```

Within a source class $a$, its route-mass-weighted mean is
$\overline p_{a,r}$. The raw within-class defect is the weighted mean of
$\lVert p_{v,r}-\overline p_{a,r}\rVert_2^2$. If the route weights in the
class have effective size

```math
n_{\mathrm{eff}}=
\frac{(\sum_v\mu_{p,r}(v))^2}{\sum_v\mu_{p,r}(v)^2},
```

the defect is multiplied by $n_{\mathrm{eff}}/(n_{\mathrm{eff}}-1)$. Classes
are assessable when their vertex count and effective size are at least two and
their route mass is at least $10^{-8}$. The reported RMS defect is the square
root of the assessable-mass-weighted corrected variance, maximized over bulk
positions. The calculation also records the maximal corrected class defect,
assessable and singleton route mass, occupied classes, class sizes, and
route-weighted effective sizes.

A separate transition-plateau defect compares each binned class-transition
matrix with its bulk-position mean, using the source route mass and the
Euclidean row norm. It distinguishes approximate lumpability at each position
from autonomy in route position.

# 4. Parameter families and uncertainty convention

Unless a delete-one jackknife is stated explicitly, an entry $a\pm b$ is a
sample mean and its ordinary standard error across independent graph samples.

The main grid used master seed `20260801`, bulk fraction $\eta=0.2$, and
Lindeberg thresholds $0.01,0.025,0.05,0.1,0.2$. Its parameter family was:

| $N$ | route horizons $p$ | graph samples |
| ---: | --- | ---: |
| 512 | 4, 8, 12, 16 | 32 |
| 1024 | 4, 8, 16, 24 | 16 |
| 2048 | 4, 8, 16, 24, 32 | 8 |
| 4096 | 4, 8, 16, 32, 48 | 8 |
| 8192 | 4, 8, 16, 32 | 4 |

A matched calibration grid used $128$ nested samples at each displayed $N$ and
horizon one. Eight independent $N=1024$ samples increased that size's unpaired
scalar and route-covariance count to $136$. The corresponding $p=16$ summaries
contain $24$ samples rather than the $16$ main-grid samples. The OU comparisons
use the $128$ matched sample indices.

# 5. Exact and numerical audits

The C++ self-test explicitly enumerates every route through horizons one to
four in three nontrivial DAGs of four to six vertices. It compares
arbitrary-precision forward and backward counts, normalized dynamic-program
vectors, every edge-position flow, the six mean increments, all $21$ raw
second moments, and all $56$ raw symmetric third moments. It also checks the
six-coordinate integer signatures, the identity $\sum_eW_e=pT_p$, a route-free
horizon, and finite Legendre coefficients through length $2000$. The
route-scaling extension gives $4949$ checks.

Every main-grid sample had at least one route at every requested horizon. At
the largest measured point, $(N,p)=(8192,32)$, the maximal route-flow relative
error was

```math
(1.348\pm0.108)\times10^{-15},
```

the maximal conditional-row error was

```math
(2.662\pm0.060)\times10^{-17},
```

and the maximal forward-backward log-count error was

```math
(1.561\pm0.173)\times10^{-17}.
```

An end-to-end verifier rejects nonstandard JSON numbers, checks all output
fields and tensor sizes, recomputes the finite count targets and coefficient
normalizations, and compares independently scheduled scientific records
exactly.

# 6. Calibration against the analytic route sector

For a route of $\ell$ edges, the exact homomorphism density and mean route count
per unordered $(\ell+1)$-set are

```math
p_\ell=\frac1{(2\ell+1)!},
\qquad
\theta_\ell=(\ell+1)!p_\ell.
```

The first case also gives $t(\mathord\to)=1/6$. At $N=8192$, using $128$
samples, the direct estimates were:

| $\ell$ | $p_\ell$ estimate | exact $p_\ell$ | signed error | $\theta_\ell$ estimate | exact $\theta_\ell$ | signed error |
| ---: | ---: | ---: | ---: | ---: | ---: | ---: |
| 1 | $0.1666214\pm0.0000767$ | $0.1666667$ | $(-4.525\pm7.667)10^{-5}$ | $0.3332428\pm0.0001533$ | $0.3333333$ | $(-9.050\pm15.334)10^{-5}$ |
| 2 | $0.008330818\pm0.000005499$ | $0.008333333$ | $(-2.515\pm5.499)10^{-6}$ | $0.04998491\pm0.00003299$ | $0.05$ | $(-1.509\pm3.299)10^{-5}$ |
| 3 | $(1.983507\pm0.001607)10^{-4}$ | $1.98412710^{-4}$ | $(-0.620\pm1.607)10^{-7}$ | $0.004760416\pm0.000003857$ | $0.004761905$ | $(-1.489\pm3.857)10^{-6}$ |
| 4 | $(2.754769\pm0.002618)10^{-6}$ | $2.75573210^{-6}$ | $(-0.963\pm2.618)10^{-9}$ | $(3.305722\pm0.003141)10^{-4}$ | $3.30687810^{-4}$ | $(-1.156\pm3.141)10^{-7}$ |

The leading covariance of

```math
\sqrt N\left(R_N^{(\ell)}-\theta_\ell\right)
```

has exact coefficient $C_1(\ell,m)$. The following $N=8192$ entries are
delete-one jackknife estimates over $128$ complete graph samples:

| $(\ell,m)$ | estimate | standard error | exact $C_1(\ell,m)$ | signed error |
| ---: | ---: | ---: | ---: | ---: |
| (1,1) | $2.46559\,10^{-2}$ | $3.63579\,10^{-3}$ | $2.22222\,10^{-2}$ | $2.43365\,10^{-3}$ |
| (1,2) | $5.08289\,10^{-3}$ | $7.38938\,10^{-4}$ | $4.76190\,10^{-3}$ | $3.20984\,10^{-4}$ |
| (1,3) | $5.49768\,10^{-4}$ | $8.12202\,10^{-5}$ | $5.29101\,10^{-4}$ | $2.06672\,10^{-5}$ |
| (1,4) | $4.10044\,10^{-5}$ | $6.31171\,10^{-6}$ | $4.00834\,10^{-5}$ | $9.21034\,10^{-7}$ |
| (2,2) | $1.14147\,10^{-3}$ | $1.57898\,10^{-4}$ | $1.11111\,10^{-3}$ | $3.03540\,10^{-5}$ |
| (2,3) | $1.30631\,10^{-4}$ | $1.79934\,10^{-5}$ | $1.29870\,10^{-4}$ | $7.60802\,10^{-7}$ |
| (2,4) | $1.01400\,10^{-5}$ | $1.42833\,10^{-6}$ | $1.01750\,10^{-5}$ | $-3.50126\,10^{-8}$ |
| (3,3) | $1.56007\,10^{-5}$ | $2.10859\,10^{-6}$ | $1.56986\,10^{-5}$ | $-9.79165\,10^{-8}$ |
| (3,4) | $1.25240\,10^{-6}$ | $1.70395\,10^{-7}$ | $1.25976\,10^{-6}$ | $-7.36706\,10^{-9}$ |
| (4,4) | $1.03458\,10^{-7}$ | $1.39480\,10^{-8}$ | $1.02922\,10^{-7}$ | $5.35948\,10^{-10}$ |

Every displayed target lies within $0.67$ estimated standard errors of its
estimate. At $N=512$, the $(4,4)$ entry has finite-size error
$(8.434\pm2.317)10^{-8}$. Its reduction to
$(0.0536\pm1.3948)10^{-8}$ at $N=8192$ supplies a convergence check beyond
same-size agreement.

For the even Legendre coordinates

```math
Z_{j,N}=\frac1{\sqrt N}\sum_{i=1}^N
\sqrt{4j+1}\,P_{2j}(1-2x_i),
```

the route fluctuation is compared with its exact triangular projection. At
$N=8192$, the mean residuals for route lengths one through four were
respectively

```math
(8.96\pm6.19)10^{-4},\quad
(5.55\pm2.76)10^{-4},\quad
(0.897\pm0.542)10^{-4},\quad
(0.796\pm0.639)10^{-5}.
```

The common Ornstein-Uhlenbeck rate is tested from nested samples. For $M>N$,
the exact mode correlation is $\sqrt{N/M}$, and the numerical rate is

```math
\widehat\lambda_j(N,M)
=-\frac{\log\widehat\rho_j(N,M)}{\log(M/N)}.
```

The table gives delete-one jackknife rates and standard errors for adjacent
doublings. The target is $1/2$ in every entry.

| $(N,M)$ | $j=1$ | $j=2$ | $j=3$ | $j=4$ |
| ---: | ---: | ---: | ---: | ---: |
| (512,1024) | $0.4800\pm0.1008$ | $0.5958\pm0.0863$ | $0.5078\pm0.1022$ | $0.4184\pm0.0780$ |
| (1024,2048) | $0.5471\pm0.1055$ | $0.5707\pm0.1088$ | $0.4853\pm0.0704$ | $0.4212\pm0.0756$ |
| (2048,4096) | $0.4116\pm0.0757$ | $0.4892\pm0.0926$ | $0.4474\pm0.0774$ | $0.4343\pm0.0707$ |
| (4096,8192) | $0.4029\pm0.0881$ | $0.4602\pm0.0817$ | $0.5038\pm0.0897$ | $0.4744\pm0.0684$ |

All sixteen estimates are within $1.17$ estimated standard errors of $1/2$.
The direct route-fluctuation rates include finite-$N$ projection residuals. At
the last doubling they range from $0.4087\pm0.0902$ to
$0.5809\pm0.1160$. These path-density, covariance, triangular-mode, and
paired-rate checks recover the analytic route sector to the resolution of the
stated samples.

# 7. Finite route coefficients

The selected longest-horizon route-count results use the finite reference
ratio

```math
\frac{N-p-1}{(2p+2)(2p+3)}.
```

This is the ratio of the analytic expected counts. The final column is the
observed ratio's relative error against this reference.

| $N$ | $p$ | samples | $\log T_p$ | $T_{p+1}/T_p$ | $\log(T_{p+1}/T_p)$ | reference ratio | relative error |
| ---: | ---: | ---: | ---: | ---: | ---: | ---: | ---: |
| 512 | 16 | 32 | $20.5661\pm0.1185$ | $0.3867\pm0.0089$ | $-0.9585\pm0.0237$ | 0.4160 | $-0.0703\pm0.0214$ |
| 1024 | 24 | 16 | $28.1751\pm0.2344$ | $0.3630\pm0.0116$ | $-1.0211\pm0.0319$ | 0.3918 | $-0.0735\pm0.0296$ |
| 2048 | 32 | 8 | $41.8909\pm0.1927$ | $0.4446\pm0.0085$ | $-0.8119\pm0.0194$ | 0.4557 | $-0.0243\pm0.0187$ |
| 4096 | 48 | 8 | $57.1592\pm0.3255$ | $0.4038\pm0.0085$ | $-0.9084\pm0.0210$ | 0.4171 | $-0.0319\pm0.0204$ |
| 8192 | 32 | 4 | $87.9203\pm0.0382$ | $1.8366\pm0.0068$ | $0.6079\pm0.0037$ | 1.8451 | $-0.00463\pm0.00369$ |

The $N=8192$, $p=32$ mean increment, in the declared coordinate order, is

```math
\begin{aligned}
b_{8192,32}={}&(
-0.0151312\pm0.0000616,
\phantom{-}0.0151732\pm0.0000540,\\
&-0.00122556\pm0.00000696,
\phantom{-}0.00123118\pm0.00000567,\\
&-0.00382605\pm0.00001383,
\phantom{-}0.00382939\pm0.00000954).
\end{aligned}
```

At the same point, the following covariance estimate uses parenthesized
standard errors.

```math
\begin{pmatrix}
 2.318(0.030)10^{-4}&-6.746(0.176)10^{-6}& 2.499(0.034)10^{-5}& 6.801(0.083)10^{-6}& 4.859(0.053)10^{-5}&-1.286(0.020)10^{-5}\\
-6.746(0.176)10^{-6}& 2.319(0.018)10^{-4}& 6.741(0.063)10^{-6}& 2.500(0.022)10^{-5}&-1.279(0.013)10^{-5}& 4.859(0.031)10^{-5}\\
 2.499(0.034)10^{-5}& 6.741(0.063)10^{-6}& 3.528(0.050)10^{-6}& 1.221(0.012)10^{-6}& 4.207(0.063)10^{-6}& 4.847(0.233)10^{-7}\\
 6.801(0.083)10^{-6}& 2.500(0.022)10^{-5}& 1.221(0.012)10^{-6}& 3.538(0.040)10^{-6}& 5.033(0.296)10^{-7}& 4.196(0.041)10^{-6}\\
 4.859(0.053)10^{-5}&-1.279(0.013)10^{-5}& 4.207(0.063)10^{-6}& 5.033(0.296)10^{-7}& 1.165(0.008)10^{-5}&-5.317(0.019)10^{-6}\\
-1.286(0.020)10^{-5}& 4.859(0.031)10^{-5}& 4.847(0.233)10^{-7}& 4.196(0.041)10^{-6}&-5.317(0.019)10^{-6}& 1.165(0.005)10^{-5}
\end{pmatrix}.
```

All $56$ entries of both symmetric third-moment tensors are stored in each
horizon record. Their six diagonal entries at $N=8192$, $p=32$ are:

| coordinate | raw third moment | centered third moment |
| --- | ---: | ---: |
| $d^+$ | $(-1.9946\pm0.0349)10^{-5}$ | $(-5.9587\pm0.1333)10^{-6}$ |
| $d^-$ | $(1.9988\pm0.0226)10^{-5}$ | $(5.9383\pm0.0706)10^{-6}$ |
| $q^{++}$ | $(-3.1412\pm0.0737)10^{-8}$ | $(-1.6597\pm0.0450)10^{-8}$ |
| $q^{--}$ | $(3.1588\pm0.0543)10^{-8}$ | $(1.6651\pm0.0314)10^{-8}$ |
| $q^{+-}$ | $(-2.4000\pm0.0244)10^{-7}$ | $(-5.0288\pm0.0769)10^{-8}$ |
| $q^{-+}$ | $(2.3989\pm0.0172)10^{-7}$ | $(4.9851\pm0.0505)10^{-8}$ |

The sign-paired increments and tensor entries are consistent with reflection
of the ordered interval. Their pairwise differences are statistically
unresolved at this sample count, giving a finite-sample symmetry audit.

# 8. Route-position dependence and graph-intrinsic closure

The local coefficients depend on route position. For $N=8192$ and $p=32$,
three bulk positions give:

| $r$ | $r/p$ | $b_r(d^+)$ | $b_r(d^-)$ | $b_r(q^{++})$ | $\operatorname{tr}A_r$ |
| ---: | ---: | ---: | ---: | ---: | ---: |
| 7 | 0.21875 | $-0.022832\pm0.000197$ | $0.007545\pm0.000037$ | $-0.0021875\pm0.0000154$ | $(3.4063\pm0.0618)10^{-4}$ |
| 16 | 0.5 | $-0.014725\pm0.000082$ | $0.015705\pm0.000114$ | $-0.0006038\pm0.0000039$ | $(2.9456\pm0.0342)10^{-4}$ |
| 25 | 0.78125 | $-0.006467\pm0.000112$ | $0.023618\pm0.000244$ | $-0.00005894\pm0.00000143$ | $(3.4723\pm0.0555)10^{-4}$ |

Division by the global time scale retains the position dependence. For fixed
horizons, the coefficient and binned-transition plateau defects remain nonzero
as $N$ increases:

| $p$ | statistic | $N=512$ | $N=1024$ | $N=2048$ | $N=4096$ | $N=8192$ |
| ---: | --- | ---: | ---: | ---: | ---: | ---: |
| 4 | drift plateau $D_b$ | 3.882 | 3.951 | 4.020 | 4.044 | 4.048 |
| 4 | covariance plateau $D_A$ | 0.222 | 0.211 | 0.213 | 0.212 | 0.210 |
| 4 | 32-bin transition plateau | 0.250 | 0.248 | 0.256 | 0.263 | 0.271 |
| 8 | drift plateau $D_b$ | 6.117 | 6.309 | 6.600 | 6.688 | 6.741 |
| 8 | covariance plateau $D_A$ | 0.305 | 0.282 | 0.283 | 0.279 | 0.278 |
| 8 | 32-bin transition plateau | 0.305 | 0.267 | 0.259 | 0.264 | 0.271 |
| 16 | drift plateau $D_b$ | 9.615 | 10.271 | 11.169 | 11.664 | 11.986 |
| 16 | covariance plateau $D_A$ | 0.418 | 0.340 | 0.333 | 0.325 | 0.320 |
| 16 | 32-bin transition plateau | 0.325 | 0.333 | 0.301 | 0.297 | 0.309 |

The displayed standard errors exclude zero. The fixed-$p$ data support a
nonautonomous finite route bridge whose coefficients depend on $r/p$, rather
than a route-position-independent bulk plateau under this normalization.

The controlled-coarsening closure defect behaves differently. The table
reports the maximal bulk corrected RMS defect for $32$ bins per coordinate.
Parenthesized values are the minimum assessable route mass over the bulk.

| $N$ | $p=4$ | $p=8$ | $p=16$ | $p=32$ |
| ---: | ---: | ---: | ---: | ---: |
| 512 | 0.2700 (0.9146) | 0.4078 (0.8985) | 0.6802 (0.7221) | -- |
| 1024 | 0.1947 (0.9761) | 0.2914 (0.9724) | 0.4899 (0.9530) | -- |
| 2048 | 0.1389 (0.9932) | 0.2087 (0.9921) | 0.3573 (0.9903) | 0.6105 (0.9711) |
| 4096 | 0.1004 (0.9970) | 0.1513 (0.9961) | 0.2636 (0.9949) | 0.4643 (0.9922) |
| 8192 | 0.07274 (0.9988) | 0.11135 (0.9987) | 0.21012 (0.9984) | 0.37882 (0.9968) |

At every fixed displayed horizon, this defect decreases with $N$, while nearly
all route mass remains assessable at the larger sizes. At $(8192,32)$ the
partition has $55.25\pm0.85$ occupied graph classes, singleton-class fraction
$0.0677\pm0.0079$, largest class size $445\pm12$, and route-weighted effective
sizes between approximately $178$ and $238$ across bulk positions. Its
corrected RMS defect is $0.37882\pm0.00121$, maximal corrected class defect
$0.8078\pm0.0240$, and transition-plateau defect
$0.37284\pm0.00600$. The decreasing defect therefore occurs in nondegenerate
classes.

At $(8192,4)$ the corrected RMS defects for $8$, $16$, and $32$ bins are
respectively

```math
0.17622\pm0.00061,
\qquad
0.08497\pm0.00088,
\qquad
0.07274\pm0.00130.
```

The present data support approximate graph-intrinsic lumpability at each fixed
position and fixed horizon as $N$ grows. A joint $N,p\to\infty$ closure claim
requires a joint regime and a partition-refinement argument. The defect remains
resolved at the largest size and increases with $p$ at fixed $N$.

# 9. Jump and third-moment diagnostics

At $N=8192$, the horizon dependence is:

| $p$ | $\alpha_{N,p}$ | maximal scaled jump | scaled raw third norm | scaled centered third norm | $L(0.1)$ | $L(0.2)$ |
| ---: | ---: | ---: | ---: | ---: | ---: | ---: |
| 4 | $1.2965\,10^{-2}$ | 6.423 | 0.5721 | 0.06152 | 2.5541 | 1.8692 |
| 8 | $5.0100\,10^{-3}$ | 10.045 | 0.2941 | 0.05010 | 1.8614 | 0.60888 |
| 16 | $1.6255\,10^{-3}$ | 16.433 | 0.1498 | 0.03264 | 0.80000 | 0.033118 |
| 32 | $4.9403\,10^{-4}$ | 25.584 | 0.07434 | 0.01845 | 0.071761 | $3.7963\,10^{-5}$ |

The uniform maximal-jump criterion fails on this grid. Rare large jumps may
nevertheless carry decreasing quadratic mass because the route-flow-weighted
tails at fixed displayed thresholds and both third-moment norms decrease with
$p$. Four horizons leave the Lindeberg condition for fixed $\varepsilon$ and
the limiting process unresolved.

# 10. Exact route-time scaling

The covariance in Section 3 combines the conditional transition variance with
variation of the position-dependent mean, so its trace is unsuitable as a
local time normalization. The original finite-sample correction estimates a
uniform-partition quantity while retaining graph discretization error. The
revised estimators separate route scaling from predictive closure and retain
the original quantity as `legacy_uniform_partition_closure`.

The reference route law fixes the relevant route-time scaling. Write the
ordered marks of a route with $p$ edges as

```math
0<X_0<X_1<\cdots<X_p<1,
```

and introduce the interval spacings

```math
G_0=X_0,\qquad
G_i=X_i-X_{i-1}\quad(1\leq i\leq p),\qquad
G_{p+1}=1-X_p.
```

The route weight is $\prod_{i=1}^pG_i$. Its simplex integral is

```math
\int_{\sum_iG_i=1,\ G_i>0}\prod_{i=1}^pG_i\,dG
=\frac1{(2p+1)!}.
```

Consequently, under the normalized continuum route law,

```math
(G_0,G_1,\ldots,G_p,G_{p+1})
\sim
\operatorname{Dirichlet}(1,2,\ldots,2,1).
```

This gives the position marginal

```math
X_r\sim
\operatorname{Beta}\bigl(2r+1,\,2(p-r)+1\bigr),
\qquad 0\leq r\leq p.
```

It also gives an exact conditional transition law. If

```math
U_r=\frac{X_{r+1}-X_r}{1-X_r},
```

then Dirichlet neutrality implies

```math
U_r\sim
\operatorname{Beta}\bigl(2,\,2(p-r)-1\bigr),
\qquad
U_r\ \text{is independent of }X_r.
```

The unconditional internal spacing $S=X_{r+1}-X_r$ has

```math
S\sim\operatorname{Beta}(2,2p),
```

with exact moments

```math
\mathbb E S=\frac1{p+1},
\qquad
\operatorname{Var}(S)
=
\frac{p}{(p+1)^2(2p+3)},
```

and

```math
\mathbb E[(S-\mathbb ES)^3]
=
\frac{p(p-1)}
{(p+1)^3(p+2)(2p+3)}.
```

Thus route time is $s=r/p$ with step $\Delta s=1/p$. The mean, variance, and
conditional centered third moment of a smooth coordinate increment have
leading orders $p^{-1}$, $p^{-2}$, and $p^{-3}$. These orders follow from the
route law rather than the measured mixed covariance. Over
$p=4,8,16,32$, the exact spacing factors have effective decay powers
$0.90849$, $1.68712$, and $2.31044$, instead of their limiting powers $1$,
$2$, and $3$. This finite-range distinction enters the subsequent comparisons.

For $r/p\to s\in(0,1)$,

```math
\mathbb E X_r=\frac{2r+1}{2p+2},
```

and

```math
\operatorname{Var}(X_r)
=
\frac{(2r+1)(2(p-r)+1)}
{(2p+2)^2(2p+3)}.
```

In particular,

```math
\sqrt{2p}\,(X_r-s)
```

has limiting variance $s(1-s)$ after removing the vanishing deterministic
centering error. The deterministic six-coordinate route profile is $\chi(s)$
from Section 1. If $m_{p,r}$ and $\Sigma_{p,r}$ denote the mean and covariance
of one $\chi$-increment at position $r$, the route law gives

```math
p\,m_{p,r}\longrightarrow\chi'(s),
\qquad
p^2\Sigma_{p,r}
\longrightarrow
\frac12\chi'(s)\chi'(s)^{\mathsf T}.
```

The corresponding conditional centered third tensor satisfies

```math
p^3K^{(3)}_{p,r}
\longrightarrow
\frac12\chi'(s)^{\otimes3}.
```

The mixed covariance of Section 3 now has the exact decomposition

```math
A^{\mathrm{mix}}_{N,p}
=
\frac1p\sum_{r=0}^{p-1}\Sigma_{N,p,r}
+
\operatorname{Cov}_{r}\!\left(m_{N,p,r}\right).
```

The first term is the mean within-position transition covariance. The second
is the between-position covariance of the local drift curve. The local
coefficient test treats them separately. Direct integration of $\chi'$ gives

```math
\int_0^1\lVert\chi'(s)\rVert_2^2\,ds
=\frac{179}{252},
\qquad
\lVert\chi(1)-\chi(0)\rVert_2^2
=\frac{77}{144}.
```

The leading averaged trace coefficients are therefore

```math
p^2\operatorname{tr}A^{\mathrm{within}}_p
\longrightarrow
\frac{179}{504},
```

and

```math
p^2\operatorname{tr}A^{\mathrm{between}}_p
\longrightarrow
\frac{59}{336}.
```

The leading averaged conditional third-tensor norm is

```math
p^3\left\lVert K^{(3),\mathrm{within}}_p\right\rVert_F
\longrightarrow
\sqrt{\frac{68\,989\,499}{1\,371\,686\,400}}
\approx0.2242663.
```

Exact rational arithmetic and an independent Dirichlet sampler reproduce these
identities.

# 11. Route-time-scaled estimators and matched experiment

The position-resolved estimator reports $p\,m_{N,p,r}$ and
$p^2\Sigma_{N,p,r}$ directly. Its bulk curve defects are the unnormalized
quantities

```math
\max_{r\in\mathcal B_{p,\eta}}
\left\lVert p\,m_{N,p,r}
-\overline{p\,m}_{N,p}\right\rVert_2,
```

and

```math
\max_{r\in\mathcal B_{p,\eta}}
\left\lVert p^2\Sigma_{N,p,r}
-\overline{p^2\Sigma}_{N,p}\right\rVert_F.
```

They test constancy of the route-time-scaled curves using their intrinsic
normalizations.

For the intrinsic route-position fluctuation, define

```math
\widehat x(u)=\frac12+X_N(u)_2-X_N(u)_1
```

in the coordinate order of Section 1. The jump diagnostics distinguish the
macroscopic increment $p\lvert\Delta\widehat x\rvert$ from the centered
fluctuation increment

```math
\sqrt{2p}
\left(
\Delta\widehat x
-\mathbb E_{N,p,r}\Delta\widehat x
\right).
```

For a threshold $\varepsilon$, the reported Lindeberg sum is the sum over route
positions of the second moment of this centered increment on the event that its
absolute value exceeds $\varepsilon$. Raw six-coordinate jump tails are
reported separately on their own scale.

The graph-intrinsic predictive comparison uses three source states:

```math
\widehat x,
```

```math
\left(
\widehat x,\,
\sqrt N\,[X_N-\chi(\widehat x)]
\right),
```

and the full six-coordinate state $X_N$. All predictor inputs are
graph-intrinsic. Each feature is standardized over the graph, and a
deterministic recursive median partition produces nested class counts
$8,16,32,64$. A permanent-identifier hash assigns source vertices to training
and holdout halves independently of the route outcomes.

The prediction target is the seven-component graph-intrinsic vector

```math
Y_N(w)
=
\left(
\widehat x(w),\,
\sqrt N\,[X_N(w)-\chi(\widehat x(w))]
\right).
```

For each source vertex $v$, the finite bridge supplies its exact conditional
mean

```math
\nu_{v,r}=\sum_wP_{N,p,r}(v,w)Y_N(w),
```

and exact histograms of $\widehat x(w)$ at nested target resolutions
$16,32,64$. The exact finite-partition defect is the route-mass-weighted
within-class variance of $\nu_{v,r}$, with no Bessel-like multiplier. The
predictive defect fits class means or histograms using only training source
vertices and scores the exact source-conditioned laws of held-out vertices.
It reports componentwise RMSE, an $R^2$ against the training global mean,
total variation at each target resolution, Wasserstein-$1$ distance in
intrinsic-mark units, holdout coverage, class occupancies, and singleton route
mass.

The matched continuation grid used master seed `20260803`, bulk fraction
$\eta=0.2$, and reference histograms with $256$ bins:

| $N$ | horizons $p$ | graph samples |
| ---: | --- | ---: |
| 512 | 4, 8, 16, 32 | 32 |
| 1024 | 4, 8, 16, 32 | 32 |
| 2048 | 4, 8, 16, 32 | 24 |
| 4096 | 4, 8, 16, 32 | 16 |
| 8192 | 4, 8, 16, 32 | 8 |

All $32$ samples at $(N,p)=(512,32)$ were route-free. Every other requested
pair had routes in every sample.

# 12. Route-law and coefficient results

Define the per-coordinate transverse residual by

```math
R_N=
\left[
\frac{1}{6N}
\sum_u
\left\lVert X_N(u)-\chi(\widehat x(u))\right\rVert_2^2
\right]^{1/2}.
```

The table reports $R_N$, its $\sqrt N$ rescaling, and the latent-validation
RMSE of $\widehat x$:

| $N$ | samples | $R_N$ | $\sqrt N R_N$ | $\operatorname{RMSE}(\widehat x,x)$ |
| ---: | ---: | ---: | ---: | ---: |
| 512 | 32 | $0.0045398\pm0.0000885$ | $0.10272\pm0.00200$ | $0.02204\pm0.00099$ |
| 1024 | 32 | $0.0032586\pm0.0000574$ | $0.10428\pm0.00184$ | $0.01636\pm0.00056$ |
| 2048 | 24 | $0.0022489\pm0.0000540$ | $0.10178\pm0.00244$ | $0.01142\pm0.00065$ |
| 4096 | 16 | $0.0015829\pm0.0000331$ | $0.10130\pm0.00212$ | $0.008081\pm0.000367$ |
| 8192 | 8 | $0.0011354\pm0.0000270$ | $0.10277\pm0.00244$ | $0.006010\pm0.000475$ |

This supports the $\sqrt N$ transverse scaling used in the predictive state.
After multiplication by the route fluctuation scale $\sqrt{2p}$, the
mark-reconstruction error is of order $\sqrt{p/N}$. The numerical evidence
therefore supplies a necessary indication that $p/N\to0$ before replacing the
latent route position by $\widehat x$ in a fluctuation limit. Sufficiency
requires a separate joint-limit argument.

At $N=8192$, the marginal and conditional Dirichlet audits give:

| $p$ | samples | maximal latent mean error | maximal latent Kolmogorov distance | maximal conditional-fraction mean error | maximal conditional-fraction Kolmogorov bound |
| ---: | ---: | ---: | ---: | ---: | ---: |
| 4 | 8 | $0.00343\pm0.00049$ | $0.02510\pm0.00126$ | $0.00384\pm0.00065$ | $0.02236\pm0.00125$ |
| 8 | 8 | $0.00370\pm0.00037$ | $0.03597\pm0.00181$ | $0.00558\pm0.00109$ | $0.03278\pm0.00107$ |
| 16 | 8 | $0.00378\pm0.00049$ | $0.04493\pm0.00421$ | $0.00692\pm0.00142$ | $0.06077\pm0.00183$ |
| 32 | 8 | $0.00462\pm0.00064$ | $0.06897\pm0.00462$ | $0.01003\pm0.00109$ | $0.12223\pm0.00350$ |

The conditional-fraction check uses the exact
$\operatorname{Beta}(2,2(p-r)-1)$ target and records its route-weighted
correlation with $X_r$. At $(8192,32)$ the maximum absolute correlation is
$0.0459\pm0.0036$. For fixed $p=16$, the maximal latent Kolmogorov distance
decreases from $0.3020\pm0.0124$ at $N=512$ to $0.0449\pm0.0042$ at
$N=8192$. The corresponding intrinsic-mark distance decreases from
$0.3956\pm0.0225$ to $0.1319\pm0.0144$. The finite graph approaches the exact
route law at fixed horizon, while increasing $p$ at fixed $N$ makes the audit
harder.

The separated covariance and third-moment coefficients at $N=8192$ are:

| $p$ | $p^2\operatorname{tr}A^{\mathrm{within}}_{N,p}$ | $p^2\operatorname{tr}A^{\mathrm{between}}_{N,p}$ | $p^3\lVert K^{(3),\mathrm{within}}_{N,p}\rVert_F$ |
| ---: | ---: | ---: | ---: |
| 4 | $0.15284\pm0.00027$ | $0.05516\pm0.00035$ | $0.03782\pm0.00024$ |
| 8 | $0.22565\pm0.00024$ | $0.09637\pm0.00061$ | $0.08548\pm0.00035$ |
| 16 | $0.28903\pm0.00035$ | $0.12926\pm0.00082$ | $0.13472\pm0.00032$ |
| 32 | $0.35783\pm0.00092$ | $0.15048\pm0.00104$ | $0.17098\pm0.00064$ |
| continuum reference | $0.35516$ | $0.17560$ | $0.22427$ |

At fixed $p=32$, the within-position trace decreases from
$0.5930\pm0.0107$ at $N=1024$ to $0.3578\pm0.0009$ at $N=8192$. Its
proximity at the final joint point to the reference constant may therefore be
a finite-grid coincidence. The between-position and third coefficients remain
respectively $0.02511\pm0.00104$ and $0.05329\pm0.00064$ below their targets
at that point.

Log-log fits over the matched horizons $4,8,16,32$ give:

| $N$ | decay power of $\lVert m\rVert$ | decay power of within covariance trace | decay power of within centered third norm | decay power of maximal six-coordinate jump |
| ---: | ---: | ---: | ---: | ---: |
| 2048 | $0.90997\pm0.00046$ | $1.46497\pm0.00378$ | $2.29874\pm0.00898$ | $0.28724\pm0.00383$ |
| 4096 | $0.90953\pm0.00036$ | $1.54639\pm0.00225$ | $2.28806\pm0.00484$ | $0.18341\pm0.00190$ |
| 8192 | $0.90916\pm0.00029$ | $1.59612\pm0.00155$ | $2.28136\pm0.00310$ | $0.12170\pm0.00182$ |

The measured mean power agrees with the exact $0.90922$ decay power of
$\lVert p^{-1}\mathbb E[\chi(X_p)-\chi(X_0)]\rVert_2$ over these four
horizons. The variance and third powers are closer to the exact spacing-factor
values $1.68712$ and $2.31044$ than to the limiting powers $2$ and $3$. The
maximal-jump power varies with $N$. These comparisons support route-time
scaling and place the measured horizon range in a preasymptotic regime.

The local scaled coefficients remain nonconstant in route position. At
$(N,p)=(8192,32)$:

| $r/p$ | $p\,m_r(d^+)$ | $p\,m_r(d^-)$ | $p\,m_r(q^{++})$ | $p^2\operatorname{tr}\Sigma_r$ |
| ---: | ---: | ---: | ---: | ---: |
| 0.25 | $-0.70185\pm0.00435$ | $0.26726\pm0.00146$ | $-0.06252\pm0.00051$ | $0.33540\pm0.00314$ |
| 0.50 | $-0.47369\pm0.00412$ | $0.50189\pm0.00324$ | $-0.019459\pm0.000201$ | $0.30313\pm0.00331$ |
| 0.75 | $-0.23749\pm0.00188$ | $0.72988\pm0.00323$ | $-0.002773\pm0.000028$ | $0.34763\pm0.00187$ |

The limiting values depend on $s$ and equal the corresponding entries of
$\chi'(s)$ and $\frac12\chi'(s)\chi'(s)^{\mathsf T}$. The direct bulk
deviations at $N=8192$ are:

| $p$ | maximal drift-curve deviation | maximal covariance-curve deviation |
| ---: | ---: | ---: |
| 4 | $0.21145\pm0.00100$ | $0.04396\pm0.00032$ |
| 8 | $0.27164\pm0.00112$ | $0.08992\pm0.00072$ |
| 16 | $0.31216\pm0.00131$ | $0.13447\pm0.00104$ |
| 32 | $0.38080\pm0.00256$ | $0.20191\pm0.00233$ |

The nonconstant curve is the expected nonautonomous profile of the finite route
bridge. A scalar normalization preserves this position dependence.

# 13. Predictive graph-intrinsic closure

At $p=16$, with $32$ source classes and $32$ target bins, the $\widehat x$
predictor behaves as follows:

| $N$ | held-out mark RMSE | held-out transverse RMSE | held-out Wasserstein-$1$ | held-out $R^2$ | holdout coverage |
| ---: | ---: | ---: | ---: | ---: | ---: |
| 512 | $0.03596\pm0.00066$ | $0.08262\pm0.00182$ | $0.03478\pm0.00049$ | $-0.1152\pm0.0274$ | $0.9812$ |
| 1024 | $0.02428\pm0.00019$ | $0.05956\pm0.00075$ | $0.02402\pm0.00016$ | $0.1445\pm0.0119$ | $0.9990$ |
| 2048 | $0.01734\pm0.00012$ | $0.04193\pm0.00035$ | $0.01682\pm0.00010$ | $0.3176\pm0.0058$ | $0.99998$ |
| 4096 | $0.01317\pm0.00007$ | $0.02942\pm0.00021$ | $0.01248\pm0.00005$ | $0.5014\pm0.0056$ | $>0.999999$ |
| 8192 | $0.010708\pm0.000033$ | $0.02064\pm0.00015$ | $0.009788\pm0.000026$ | $0.6758\pm0.0045$ | $>0.9999999$ |

The predictive errors decrease at fixed horizon. At the largest row, the exact
finite-partition and held-out mark RMSEs are $0.010653\pm0.000043$ and
$0.010708\pm0.000033$. The corresponding Wasserstein-$1$ values are
$0.009752\pm0.000034$ and $0.009788\pm0.000026$. Their agreement shows that
training-source estimation error is small at this resolution.

At $(N,p)=(8192,16)$ and the same $32$ classes and target bins, the state
comparison is:

| source state | held-out mark RMSE | held-out transverse RMSE | held-out total variation | held-out Wasserstein-$1$ | held-out $R^2$ |
| :--- | ---: | ---: | ---: | ---: | ---: |
| $\widehat x$ | $0.010708\pm0.000033$ | $0.02064\pm0.00015$ | $0.15816\pm0.00027$ | $0.009788\pm0.000026$ | $0.6758\pm0.0045$ |
| full $X_N$ | $0.011459\pm0.000056$ | $0.02066\pm0.00015$ | $0.16389\pm0.00028$ | $0.010334\pm0.000037$ | $0.6732\pm0.0042$ |
| $\widehat x$ plus transverse residual | $0.05920\pm0.00046$ | $0.02286\pm0.00033$ | $0.47369\pm0.00198$ | $0.05479\pm0.00045$ | $0.1882\pm0.0063$ |

The matched full-state minus $\widehat x$ mark-RMSE difference is
$0.000751\pm0.000052$, and the Wasserstein-$1$ difference is
$0.000546\pm0.000032$. At this class budget the intrinsic-mark state predicts
more accurately than either higher-dimensional partition.

The balanced unsupervised partition in six effective dimensions spends splits
on transverse directions, while the one-dimensional partition resolves
$\widehat x$. Its finite-class comparison therefore tests signal after this
partition cost rather than conditional information without approximation. The
data support $\widehat x$ together with normalized route position $s$ as the
smallest tested graph-intrinsic state. The full six-coordinate state remains
compatible with closure because it determines $\widehat x$, but this partition
provides no additional predictive resolution.

The $\widehat x$ refinements at $(8192,16)$ are:

| source classes | held-out mark RMSE | held-out Wasserstein-$1$ | held-out $R^2$ |
| ---: | ---: | ---: | ---: |
| 8 | $0.02937\pm0.00015$ | $0.02675\pm0.00013$ | $0.5705\pm0.0032$ |
| 16 | $0.01693\pm0.00006$ | $0.01528\pm0.00006$ | $0.6508\pm0.0043$ |
| 32 | $0.010708\pm0.000033$ | $0.009788\pm0.000026$ | $0.6758\pm0.0045$ |
| 64 | $0.008359\pm0.000040$ | $0.007917\pm0.000033$ | $0.6807\pm0.0045$ |

At $32$ source classes, target-bin refinement from $16$ through $32$ to $64$
gives Wasserstein-$1$ values

```math
0.009809\pm0.000022,\qquad
0.009788\pm0.000026,\qquad
0.009766\pm0.000027.
```

The corresponding total-variation values are $0.11690\pm0.00030$,
$0.15816\pm0.00027$, and $0.20960\pm0.00040$. Wasserstein-$1$ is stable under
this refinement, while total variation resolves progressively finer
discrepancies. A Euclidean norm with a changing target dimension would not
detect this distinction.

# 14. Jump diagnostics and the joint limit

At $N=8192$, the centered fluctuation diagnostics are:

| $p$ | maximal $\sqrt{2p}$ centered intrinsic jump | Lindeberg sum at $0.2$ | at $0.5$ | at $1$ |
| ---: | ---: | ---: | ---: | ---: |
| 4 | $2.2569\pm0.0034$ | $0.44519\pm0.00134$ | $0.22417\pm0.00119$ | $0.04653\pm0.00051$ |
| 8 | $3.4281\pm0.0091$ | $0.61817\pm0.00113$ | $0.27569\pm0.00091$ | $0.05813\pm0.00055$ |
| 16 | $4.7586\pm0.0164$ | $0.69858\pm0.00100$ | $0.26844\pm0.00070$ | $0.03435\pm0.00025$ |
| 32 | $5.8022\pm0.0230$ | $0.68457\pm0.00219$ | $0.18960\pm0.00080$ | $0.009679\pm0.000102$ |

The uniform maximal-jump condition fails on this grid. The tail at threshold
one decreases by $p=32$, whereas the tails at $0.2$ and $0.5$ have not entered
an unambiguous asymptotic regime. The route law predicts typical centered
fluctuation increments of order $p^{-1/2}$, but the maximum over all
positive-flow graph edges continues to detect rare transitions. The Lindeberg
condition along an admissible joint sequence $p=p(N)$ remains unresolved.

Route-count support already constrains that sequence. At $p=32$, the
expected-count ratio error is $-0.358\pm0.046$ at $N=1024$,
$-0.0109\pm0.0044$ at $N=4096$, and $-0.00424\pm0.00216$ at $N=8192$.
No $p=32$ route exists at $N=512$. At $N=8192$, the ratio errors for
$p=4,8,16,32$ are all within approximately $0.43\%$ of zero in absolute
value. Thus fixed-$p$ graph convergence is well resolved at the largest size,
while finite route support limits the available $p$.

# 15. Exact implementation audits

Across the $416$ horizon records with routes, the largest
covariance-decomposition reconstruction error was
$8.67\times10^{-19}$. The largest route-flow, conditional-row, and
forward-backward log-count errors were respectively

```math
6.67\times10^{-15},\qquad
5.25\times10^{-17},\qquad
2.78\times10^{-17}.
```

The C++ brute-force suite reports $4949$ checks. The schema and
deterministic-output verifier reports $8632$ checks, and the independent exact
and sampled Dirichlet verifier reports $430$ checks.
