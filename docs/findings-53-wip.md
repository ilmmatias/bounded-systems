# 1. Evolution of the clock question

The first state-line analyses at sizes through 288 produced route/configuration clock ratios near

$$
9.
$$

This suggested the provisional candidate

$$
\lambda_{\mathrm{route}}\approx-18
$$

relative to

$$
\lambda_{\mathrm{config}}=-2.
$$

The finite Schur decomposition supported a genuine slow scalar, but exact $-18$ remained unresolved. Larger exact-uniform samples at

$$
N=384,480,576,672,768
$$

moved the extrapolated rate downward.

# 2. High-size exact-uniform clock fits

The combined low- and high-size Schur fits gave

| $\rho$ | rate estimate | clock ratio |
|---:|---:|---:|
| 1/8 | -18.011 | 9.006 |
| 1/4 | -17.692 | 8.846 |
| 3/8 | -17.567 | 8.783 |

The high-size-only fits gave

| $\rho$ | rate estimate | clock ratio |
|---:|---:|---:|
| 1/8 | -17.612 | 8.806 |
| 1/4 | -17.472 | 8.736 |
| 3/8 | -17.416 | 8.708 |

Thus all three horizons moved below nine and toward one another.

# 3. Common-limit model

A paired high-size fit to

$$
\lambda_{N,\rho}
=
L+\frac{a_\rho}{N}
$$

gave

$$
L=-17.500109.
$$

The corresponding ratio was

$$
\kappa=8.7500545.
$$

The common-limit model predicted better than three independent limits and much better than fixed $-18$. However, the paired-bootstrap interval was broad:

$$
L\in[-18.0175,-16.9773]
$$

at 95%.

Therefore $-18$ was strongly disfavored as the finite-size model but only narrowly not rejected as an asymptotic limit.

The value

$$
8.75=\frac{35}{4}
$$

was recognized after inspecting the fit. This post-hoc pattern is not an exact result.

# 4. Why an analytic calculation became necessary

The high-size extrapolation could not distinguish nearby candidates such as

$$
-17.5
$$

and

$$
-\frac{120}{7}\approx-17.142857.
$$

The route latent geometry supplied a way to compute the scalar directly in the ordered-Bernoulli surrogate, without fitting an arbitrary rational number.

# 5. Leading latent covariance

For forward-edge probability $q$, define

$$
b=(-q,q,-q^2,0,0,q^2)^\mathsf T,
$$

$$
c=\frac{q^2}{2}(0,0,1,1,-1,-1)^\mathsf T.
$$

With asymptotically uniform latent route-source position,

$$
\Sigma
=
\mathrm{Cov}(t,t^2)
=
\begin{pmatrix}
1/12&1/12\\
1/12&4/45
\end{pmatrix}.
$$

The leading state covariance is

$$
G_0=[b\ c]\Sigma[b\ c]^\mathsf T.
$$

Its graph-profile intersection is exactly the line $Er_0$.

# 6. First-order edge-noise covariance

For a vertex at latent position $t$, the influence vectors of one outgoing edge to $y>t$ and one incoming edge from $x<t$ are

$$
g_+(t,y)
=
\begin{pmatrix}
1\\0\\q(1-y)\\0\\qy\\0
\end{pmatrix},
$$

and

$$
g_-(t,x)
=
\begin{pmatrix}
0\\1\\0\\qx\\0\\q(1-x)
\end{pmatrix}.
$$

The first-order local-noise covariance is

$$
\Omega
=
q(1-q)
\int_0^1
\left[
\int_t^1g_+g_+^\mathsf Tdy
+
\int_0^tg_-g_-^\mathsf Tdx
\right]dt.
$$

The route jump has two endpoint contributions, giving the intrinsic denominator

$$
\alpha(q)
=2\mathrm{tr}\Omega
=\frac{2q(1-q)(2q^2+3)}3.
$$

# 7. Singular solvability condition

Because $G_0$ has rank two, the equation

$$
G_0z=Er_0
$$

does not uniquely determine the dual vector.

The bounded limit selected by the full finite covariance must additionally satisfy

$$
K^\mathsf T\Omega z=0,
$$

where the columns of $K$ span $\ker G_0$.

The symbolic solution family is

$$
z=
\begin{pmatrix}
-qz_4-40\sqrt3/q^3\\
-qz_5-40\sqrt3/q^3\\
z_4+120\sqrt3/q^4\\
z_5+120\sqrt3/q^4\\
z_4\\z_5
\end{pmatrix}.
$$

Two free coordinates remain, but the scalar route action is independent of both.

# 8. Exact surrogate numerator and clock law

Let

$$
L=\frac1{\sqrt3}(0,0,1,0,-1,-1).
$$

The symbolic calculation gives

$$
L\Omega z
=\frac{10(1-q)}q.
$$

Therefore

$$
\lambda_{\mathrm{route}}(q)
=-\frac{L\Omega z}{\alpha(q)}
=-\frac{15}{q^2(2q^2+3)}.
$$

Relative to the configuration eigenvalue $-2$,

$$
\kappa(q)
=\frac{15}{2q^2(2q^2+3)}.
$$

At

$$
q=\frac12,
$$

this becomes

$$
\lambda_{\mathrm{route}}
=-\frac{120}{7},
\qquad
\kappa=\frac{60}{7}\approx8.57142857.
$$

# 9. Fresh multi-(q) predictions

The analytic law made two predictions not used in its derivation:

$$
q=\frac13:
\qquad
\lambda=-\frac{1215}{29}
\approx-41.89655,
$$

and

$$
q=\frac23:
\qquad
\lambda=-\frac{243}{28}
\approx-8.67857.
$$

Together with $q=1/2$, these were tested in a fresh planted-route experiment at sizes

$$
N=192,288,384,480,576.
$$

# 10. Multi-(q) confirmatory results

The common-limit fits were:

| $q$ | analytic rate | fitted rate | relative error | 95% bootstrap interval |
|---:|---:|---:|---:|---:|
| 1/3 | -41.89655 | -42.13690 | 0.574% | [-42.8700, -41.3659] |
| 1/2 | -17.14286 | -17.55217 | 2.388% | [-18.0247, -17.0706] |
| 2/3 | -8.67857 | -8.92117 | 2.795% | [-9.4264, -8.4745] |

Every analytic prediction lay inside its bootstrap interval. The largest-size right-state angles were below one degree.

The frozen verdict was

```text
ANALYTIC_FORMULA_SUPPORTED
```

for the planted ordered-Bernoulli route ensemble.

# 11. Collapsed constant check

The formula is equivalent to

$$
-\lambda(q)q^2(2q^2+3)=15.
$$

Using the independently fitted limits gave approximately

$$
15.086,
15.358,
15.419.
$$

Thus three clock scales spanning nearly a factor of five collapsed onto the predicted constant 15 within about three percent.

# 12. Exact-uniform transfer problem

The surrogate result does not automatically imply

$$
\lambda_{\mathrm{uniform\ DAG}}
=-\frac{120}{7}.
$$

Define for the exact uniform-DAG route process

$$
\alpha_N=N\mathbb E[a],
$$

$$
G_N=\mathbb E[G],
\qquad
H_N=\mathbb E[aC],
$$

$$
z_N=G_N^+Er_0,
$$

and

$$
\eta_N=-N\,LH_Nz_N.
$$

Then the pooled moment clock is

$$
\lambda_N^{\mathrm{moment}}
=-\frac{\eta_N}{\alpha_N}.
$$

At $q=1/2$, the surrogate theorem predicts

$$
\alpha=\frac7{12},
\qquad
\eta=10,
\qquad
\lambda=-\frac{120}{7}.
$$

# 13. Existing numerator audits

## Exact uniform-DAG data through (N=288)

The direct extrapolation gave

$$
\alpha\approx0.603257,
\qquad
\eta\approx11.009646,
$$

and

$$
-\eta/\alpha\approx-18.2503.
$$

All three exact surrogate targets were disfavored under the simple linear correction model.

## Quenched ordered-Bernoulli control

The corresponding quenched control gave

$$
\alpha\approx0.598960,
\qquad
\eta\approx10.753079,
$$

and

$$
-\eta/\alpha\approx-17.9529.
$$

The bias had the same sign as the exact-uniform estimate, suggesting a substantial finite-size or estimator correction rather than an immediately isolated exact-ensemble effect.

## Fresh planted (q=1/2) control

Using the fresh planted data through $N=576$ gave

$$
\alpha\approx0.589206,
\qquad
\eta\approx10.255667,
$$

and

$$
-\eta/\alpha\approx-17.4059.
$$

The numerator target $10$ and clock target $-120/7$ were supported, while the denominator target $7/12$ was narrowly disfavored because the interval was precise enough to resolve a remaining one-percent finite-size offset.

This validates the numerator estimator in the ensemble for which the symbolic law was derived.

# 14. Why mean-of-fits is not the analytic scalar

The planted control also produced a mean-of-fits slow value near

$$
-18.88,
$$

which differs from the pooled moment ratio.

There is no contradiction. The analytic object is

$$
Q\,\mathbb E[aC]\,\mathbb E[G]^+E,
$$

whereas mean-of-fits uses

$$
\mathbb E[QCG^+E].
$$

Singular inversion does not commute with graph averaging. The common state line is robust, but the finite scalar estimator depends on the prescribed aggregation order.

# 15. Current high-size exact run

A new exact geometry run is currently generating the matrices required for the direct numerator audit at

$$
N=384,480,576,672,768.
$$

The intended outputs are:

1. a combined fit using sizes 96 through 768;
2. a high-size-only fit using sizes 384 through 768;
3. bootstrap intervals for $\alpha$, $\eta$, and $-\eta/\alpha$;
4. comparison with both the surrogate numerator $10$ and the descriptive post-hoc value
$$
   \frac{245}{24}\approx10.20833,
$$
   which would accompany a rate of $-17.5$ if $\alpha=7/12$.

The value $245/24$ is not a preregistered exact candidate.

# 16. Computational implementation note

The current exact sampler has two phases:

1. serial arbitrary-precision counting-table construction;
2. 32-thread graph sampling and route analysis.

The table builder stores all powers

$$
2^0,2^1,\ldots,2^{N^2},
$$

as separate GMP integers. Its raw limb storage scales as approximately

$$
O(N^4)\text{ bits}.
$$

This explains the single-core startup phase and memory use of roughly 14 GB at $N=672$, increasing into the low tens of gigabytes at $N=768$.

The sampled results remain valid, but future engineering should replace the global power table by shifts or a rolling recurrence and should use dynamic worker scheduling in the parallel phase.

# 17. Current decision tree

If the exact high-size audit finds

$$
\alpha_N\to\frac7{12},
\qquad
\eta_N\to10,
$$

then

$$
\lambda_{\mathrm{exact}}
=-\frac{120}{7}
$$

is strongly supported.

If

$$
\alpha_N\to\frac7{12},
\qquad
\eta_N\to\eta_\ast\ne10,
$$

then exact uniform-DAG weighting renormalizes the numerator while preserving the state line and intrinsic denominator.

If exact and planted estimates retain the same finite-size displacement, the remaining problem is the correction model rather than ensemble transfer.

### ... UNFINISHED/WIP, CURRENTLY HERE ... ###
