# 1. The original bridge question

The first bridge proposal was direct:

```math
\text{estimate a route-side local generator and compare it with }J_{\mathrm{config}}.
```

The route sampler generated exact uniform labeled DAGs and resolved routes at relative horizons

```math
\rho=\frac18,\frac14,\frac38.
```

Initial samples at

```math
N=64,128,256
```

produced all required records, but the first bridge analysis returned

```text
route_gate=UNRESOLVED
primary=NOT_EVALUATED_OR_FAIL
secondary=NOT_EVALUATED_OR_FAIL
```

The failure was not a runtime or normalization error. It indicated that the proposed projected route state did not satisfy the assumptions needed for a direct generator comparison.

# 2. Per-position route closure looked deceptively strong

A first closure probe regressed local route transitions separately at each route position.

At $N=64$, the augmented local dictionary achieved high within-position fit:

| horizon | base $R^2$ | degree-two $R^2$ | augmented $R^2$ |
|---:|---:|---:|---:|
| 8 | 0.878 | 0.946 | 0.980 |
| 16 | 0.836 | 0.944 | 0.976 |
| 24 | 0.826 | 0.968 | 0.989 |

This initially suggested that a finite local closure might exist.

However, a strong fit conditional on route position is not the same as an autonomous state law.

# 3. Autonomy test

The decisive test pooled route positions and then left one position out.

For $N=64$, the augmented pooled fit remained high:

```math
0.950,
0.911,
0.886
```

at horizons 8, 16, and 24.

But the leave-one-position-out values collapsed:

```math
0.781,
0.120,
-1.820.
```

The same behavior strengthened with size and horizon. At $N=256$, the leave-one-position-out augmented values were approximately

```math
0.064,
-1.018,
-4.196.
```

The corresponding route-time target became even worse.

Therefore

```math
\text{position-conditioned predictability does not transfer across route position.}
```

The local profile was not an autonomous route state.

# 4. State-overlap analysis

A node-overlap sampler emitted multiple nodes from each graph and route position to determine whether failure came merely from poor support overlap.

The route-position class was almost perfectly recoverable:

```math
\text{classification accuracy}\approx0.999-1.000.
```

Thus route position was strongly encoded in the local coordinates.

But overlap coverage decreased rapidly. Representative coverage values were:

| $N$ | short horizon | middle horizon | long horizon |
|---:|---:|---:|---:|
| 64 | 0.662 | 0.450 | 0.313 |
| 128 | 0.081 | 0.027 | 0.019 |
| 256 | 0.014 | 0.009 | 0.001 |

The finite local states occupied increasingly disjoint position-dependent regions.

Adding the explicit route-time coordinate produced negligible gain, typically of order

```math
10^{-4}
```

and sometimes negative.

# 5. Graph-context test

The next possibility was that a local node profile required a small graph-global context variable.

The analysis compared:

* local state only;
* local state plus graph horizon summaries;
* local state plus graph profile;
* both global additions.

The global additions improved fit only slightly, generally by a few thousandths to a few hundredths. Permuting the graph-profile context across graphs produced essentially no positive gain.

The between-graph variance was small compared with the unresolved within-route variation.

Therefore no simple graph-global scalar or low-dimensional graph profile repaired closure.

# 6. Route jets

A route jet records present and nearby route-position features. Depths up to four were tested.

For every horizon and position in the pilot, the best predictive depth was

```math
k=0,
```

meaning the present local profile outperformed deeper deterministic jets.

The deepest-jet fits often deteriorated severely. For example, at horizon 24 and position zero, the fit fell from about

```math
0.545
```

to

```math
0.095.
```

Thus deterministic finite route history did not provide the missing autonomous coordinate.

# 7. Covariance and cross-covariance jets

The next probes added:

* local covariance tensors;
* covariance jets across nearby positions;
* deterministic cross-covariances between route positions.

These features gave small, inconsistent gains. Some short-horizon positions improved by a few hundredths, while others worsened. The best depth remained zero throughout the pilot summaries.

The cross-covariance gain reached about $0.071$ in one horizon-position cell, but did not form a stable monotone pattern and did not repair long-horizon closure.

# 8. Singular bridge discovery

Although full closure failed, the cross-moment operators exhibited a sharp singular structure.

At each relative horizon, the fourth singular value was much smaller than the third. Representative ratios were

```math
0.00227,
0.000257,
0.00453.
```

The right singular geometry was stable:

* right-subspace angles below roughly three degrees;
* right-null residuals below one percent in point estimates.

The left geometry was not stable under the original exact-pair bootstrap. Its upper confidence angles reached roughly 12-16 degrees, and left-null residual intervals exceeded the preregistered limit.

Thus the original two-sided bridge failed because the left observable was not shared, even though the right state geometry was much cleaner.

# 9. Sector-adapted left tests

A second singular-sector analysis replaced the exact left vector by a fitted left sector. Point estimates improved dramatically, with sector angles often below one degree.

Nevertheless the confirmatory bootstrap still returned

```text
sector=FAIL_OR_UNRESOLVED
exact_pair=FAIL_OR_UNRESOLVED
```

because the left sector remained too weakly conditioned at the available sizes.

This was the decisive conceptual change:

```math
\text{the route/configuration bridge should be tested one-sidedly first.}
```

# 10. What the failed closure tests ruled out

The combined diagnostics disfavor the following simple model:

> A route endpoint carries a finite six- or low-order-jet profile whose conditional next-step law is autonomous and can be identified directly with the configuration hydrodynamic Jacobian.

The reason is structural rather than statistical:

* route position is strongly encoded;
* state supports separate with size;
* leaving out one position destroys prediction;
* deeper deterministic and covariance jets do not restore transfer;
* a common left observable is unstable.

# 11. What survived

The failures did not erase the entire bridge. They exposed three robust remnants:

1. a low-rank route cross-moment operator;
2. a stable right singular subspace;
3. a candidate one-dimensional graph-profile direction inside that subspace.

This suggested that the route process may select the same **state sector** as configuration dynamics without sharing the same complete local generator or left observable.

# 12. Methodological conclusion

Negative results were essential here. Had only the high within-position $R^2$ been reported, the route process would have appeared closed. The leave-one-position-out and overlap tests showed that this was an interpolation artifact on position-separated support.

The correct lesson is

```math
\text{high local predictability is not evidence of autonomous continuum closure.}
```
