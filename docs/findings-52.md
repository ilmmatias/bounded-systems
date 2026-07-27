# 1. From a failed full bridge to a one-sided bridge

The route closure studies showed that a common full local generator was too strong a demand. The stable object was the right state geometry.

The revised bridge question became:

```math
\text{Do route geometry and configuration dynamics select the same state direction?}
```

Only the candidate state direction is compared; the complete route state may remain nonautonomous. The comparison permits:

* different left observables;
* different full finite matrices;
* different time normalizations.

# 2. The candidate state line

The singular route analysis identified the four-coordinate graph-profile vector

```math
r_0=(0,1,-1,-1)^\mathsf T.
```

Its interpretation is a fluctuation that leaves the edge coordinate unchanged while increasing the directed two-path coordinate and decreasing both wedge coordinates in the corresponding ratio.

Using the normalized vector

```math
\widehat r_0=\frac1{\sqrt3}(0,1,-1,-1)^\mathsf T,
```

the route right singular vector converged toward this line.

# 3. Independent confirmatory design

A fresh state-line experiment used independent sizes and seeds:

```math
N=96,144,192,240,288,
```

with relative horizons

```math
\rho=\frac18,\frac14,\frac38.
```

The sample counts were

```math
6000,
4000,
3000,
2400,
2000.
```

The design was fixed before the confirmatory analysis.

# 4. Confirmatory state-line results

The results were:

| $\rho$ | rank-three defect | fast angle | fast null residual | largest-size angle | state line |
|---:|---:|---:|---:|---:|:---:|
| 1/8 | 0.0011908 | 1.97° | 0.00550 | 2.98° | PASS |
| 1/4 | 0.0005210 | 0.325° | 0.000781 | 0.775° | PASS |
| 3/8 | 0.0026613 | 0.0943° | 0.00102 | 0.370° | PASS |

The aggregate verdict was

```text
state_line=CONFIRMATORY_PASS
clock_band=CONFIRMATORY_PASS
combined=CONFIRMATORY_PASS
```

while exact clock ratio nine remained unresolved.

Thus the state line passed independently of the later scalar-clock interpretation.

# 5. Configuration dynamics on the same line

The configuration semigroup and constrained Jacobian analysis had already identified an odd/tangent mode with

```math
J_{\mathrm{config}}r_0=-2r_0.
```

Therefore the two calculations met on an exact state direction:

```math
\text{configuration dynamics selects }r_0,
```

and

```math
\text{route right singular geometry selects }r_0.
```

This is the first direct bridge between the two continuum constructions.

# 6. Regression geometry and singular scaling

A dedicated route-geometry sampler measured the cross-moment and covariance matrices through sizes 96 to 288.

Across all three relative horizons:

* the relevant operator retained rank six at numerical cutoffs from $10^{-6}$ through $10^{-12}$;
* the fourth-to-third singular ratio remained of order $10^{-3}$;
* the right-state angle decreased with horizon, reaching about $0.21^\circ$ at $\rho=3/8$;
* the coefficient and action exponents were close to one;
* the smallest covariance exponent was close to $-2$.

This established the singular hierarchy needed for a finite slow state embedded in otherwise fast route coordinates.

# 7. Corrected Kramers-Moyal reduction

The uncorrected Kramers-Moyal reduction mixed the first-order drift cancellation with the singular covariance scaling. After separating these terms, the corrected analysis found:

| $\rho$ | corrected angle | null residual | slow clock estimate |
|---:|---:|---:|---:|
| 1/8 | 3.20° | 0.0102 | 9.19 |
| 1/4 | 0.735° | 0.00287 | 8.97 |
| 3/8 | 0.392° | 0.00201 | 8.85 |

The diagnosis was

```text
FIRST_ORDER_DRIFT_CANCELLATION_SUPPORTED
```

The state-sector result therefore came from cancellation in a singular covariance geometry, not from an ordinary nonsingular local regression.

# 8. Ordered-Bernoulli surrogate transfer

An ordered-Bernoulli DAG surrogate with forward-edge probability one half reproduced the route singular structure.

Comparing the exact uniform-DAG and surrogate reductions gave:

| $\rho$ | subspace structure | matrix relative difference | intrinsic-scale relative difference | clock pair |
|---:|:---:|---:|---:|---:|
| 1/8 | PASS | 0.070 | 0.0021 | 9.190, 9.124 |
| 1/4 | PASS | 0.093 | 0.0024 | 8.968, 8.899 |
| 3/8 | PASS | 0.095 | 0.0090 | 8.852, 8.789 |

The aggregate result was

```text
structure=REPRODUCED
quantitative=MATCH
```

Thus the simple ordered latent-position model captured both the singular state geometry and most finite quantitative structure.

# 9. Planted versus quenched route conditioning

A planted-route ensemble was then compared with the quenched ordered-Bernoulli route law.

At the shortest relative horizon, forcing a route produced large finite-size changes and failed the initial quantitative comparison. At the two longer horizons, the singular structure and clock remained compatible.

Pooling route records before inversion reduced the discrepancy and restored the rank-three cancellation, but a residual matrix mismatch remained.

This showed that:

* the state line is robust;
* mean-of-fits and pooled estimators need not agree as full matrices;
* route conditioning changes finite left geometry more strongly than the right state sector.

# 10. Failure of simple pathwise factorization

A direct attempt to factor the pooled null correction into a pathwise kernel failed.

The residual component had high cosine alignment with the expected sign direction but large kernel residuals, typically around

```math
0.83\text{ to }0.97.
```

Therefore the finite correction is not generated by a simple single-path observable. It is an ensemble-level singular perturbation.

# 11. Asymptotic matrix pencil

The covariance/cross-moment matrices displayed singular-value exponents approximately

```math
(-1,-1,-1,-2)
```

for the relevant reduced pencil.

Attempts to recover the slow line from a naive leading/subleading matrix expansion were numerically unstable because the leading covariance range itself has an internal weak direction. The correct treatment required identifying the latent geometry of the leading range.

# 12. Latent order-position basis

For forward-edge probability $q$, the leading six-coordinate local profile depends on latent position $t$ through two centered polynomial directions:

```math
b=(-q,q,-q^2,0,0,q^2)^\mathsf T,
```

and

```math
c=\frac{q^2}{2}(0,0,1,1,-1,-1)^\mathsf T.
```

The graph-profile embedding is

```math
E(e,p,w_+,w_-)
=
(e,e,p,p,w_+,w_-)^\mathsf T.
```

Any vector in $\mathrm{Range}E$ has equal first two components. A vector

```math
\alpha b+\beta c
```

has first two components

```math
-\alpha q,
\qquad
\alpha q.
```

For $q>0$, equality forces

```math
\alpha=0.
```

Therefore

```math
\mathrm{Range}E
\cap
\mathrm{span}\{b,c\}
=
\mathrm{span}\{c\}.
```

Since

```math
c=\frac{q^2}{2}Er_0,
```

we obtain the exact identity

```math
\mathrm{Range}E
\cap
\mathrm{Range}G_0
=
\mathrm{span}\{Er_0\}.
```

This is independent of $q$ and of the detailed nondegenerate covariance of $(t,t^2)$.

# 13. Empirical latent covariance

The fitted latent covariance was approximately

```math
\Sigma
\approx
\begin{pmatrix}
0.08333&0.08333\\
0.08333&0.08889
\end{pmatrix}
=
\begin{pmatrix}
1/12&1/12\\
1/12&4/45
\end{pmatrix}.
```

The matrix equals

```math
\mathrm{Cov}_{t\sim U[0,1]}(t,t^2).
```

The leading covariance fit errors were below one percent, usually below a few thousandths, and the empirical leading subspace angles were very small in the quenched ensemble.

The latent-geometry analysis therefore returned

```text
mechanism=SUPPORTED
```

# 14. Covariance eigenvalue hierarchy

The geometric decomposition of the six-dimensional covariance was

```math
2\text{ modes }O(1),
\qquad
2\text{ modes }O(N^{-1}),
\qquad
2\text{ modes }O(N^{-2}).
```

The two $O(1)$ modes are the latent linear and quadratic position directions. The graph-profile range intersects them in exactly one line, $Er_0$.

This explains why a finite state sector survives after inversion while generic graph-coordinate directions acquire an $O(N)$ fast action.

# 15. Schur-complement form of the slow sector

Choose a basis whose first vector is $r_0$ and whose remaining vectors span the fast graph-profile complement. Write the finite route operator as

```math
A_N=
\begin{pmatrix}
a_N&b_N\\
c_N&D_N
\end{pmatrix}.
```

The exact slow eigenvalue obeys

```math
\lambda_N
=
a_N-b_N(D_N-\lambda_NI)^{-1}c_N.
```

Because the fast block scales with $N$,

```math
\lambda_N
=
a_N-b_ND_N^{-1}c_N+O(N^{-1}).
```

The nonlinear Schur residual was at machine precision, and the static approximation differed from the directly extracted slow value by substantially less than one percent in the confirmatory analyses.

Thus the route scalar separates into:

```math
\text{direct action}
+
\text{fast-sector feedback}.
```

A common right state line does not imply a common left observable; the feedback term is precisely where left-geometry differences enter.

# 16. Central bridge conclusion

The bridge now has a mechanism-level form:

```math
\text{latent order covariance uniquely selects }r_0,
```

while

```math
J_{\mathrm{config}}r_0=-2r_0.
```

Therefore

```math
\text{configuration dynamics and route geometry independently select}
```

```math
\text{the same exact one-dimensional state sector.}
```

This is stronger than numerical alignment of two fitted eigenvectors. One side is a configuration semigroup direction; the other follows from an exact intersection of latent covariance and graph-profile ranges.
