# 1. Information contraction and support order

The fluctuation results of `findings-48.md` through `findings-58.md` associate a support on $r$ vertices with normalization $n^{r/2}$ and logarithmic relaxation rate $r/2$. The conjugate central family of `findings-64.md` gives an independent information-theoretic derivation of the same exponents.

Parameters attached to one-vertex frequencies receive $O(n)$ observations. Parameters attached to pair relations receive $O(n^2)$ observations. Their posterior standard deviations therefore contract respectively as $n^{-1/2}$ and $n^{-1}$.

# 2. Exact Dirichlet uncertainty

Let

```math
\bar p_{n,i}
=
\frac{\alpha_i+C_{n,i}}{\alpha_0+n}
```

be the posterior mean of the layer probability. The Dirichlet covariance is

```math
\operatorname{Cov}
(p\mid\mathcal F_n)
=
\frac{
\operatorname{diag}(\bar p_n)
-
\bar p_n\bar p_n^{\mathsf T}
}{
\alpha_0+n+1
}.
```

## Theorem 1. One-vertex information rate

Conditional on the selected sector $p$, almost surely,

```math
n\,
\operatorname{Cov}
(p\mid\mathcal F_n)
\longrightarrow
\Sigma_p
=
\operatorname{diag}(p)-pp^{\mathsf T}.
```

The posterior standard deviation of every nonconstant linear functional of $p$ is therefore of order $n^{-1/2}$. In logarithmic size $s=\log n$, this is contraction at rate $1/2$.

## Proof

The exact covariance formula is the standard Dirichlet moment identity. The strong law gives $\bar p_n\to p$, while

```math
\frac n{\alpha_0+n+1}\longrightarrow1.
```

Substitution gives the limit.

The matrix $\Sigma_p$ is exactly the stationary covariance of the rate-$1/2$ empirical-proportion Ornstein-Uhlenbeck field derived in `findings-48.md` and `findings-51.md`.

# 3. Exact beta uncertainty

For a block $i<j$, define

```math
\bar w_{ij,n}
=
\frac{
 a_{ij}+E_{ij,n}
}{
 a_{ij}+b_{ij}+M_{ij,n}
}.
```

Its posterior variance is

```math
\operatorname{Var}
(w_{ij}\mid\mathcal F_n)
=
\frac{
\bar w_{ij,n}(1-\bar w_{ij,n})
}{
 a_{ij}+b_{ij}+M_{ij,n}+1
}.
```

## Theorem 2. Pair-information rate

Conditional on the selected ordered-block sector $(p,W)$, almost surely,

```math
n^2
\operatorname{Var}
(w_{ij}\mid\mathcal F_n)
\longrightarrow
\frac{
 w_{ij}(1-w_{ij})
}{
 p_ip_j
}.
```

The posterior standard deviation is therefore of order $n^{-1}$, corresponding to logarithmic contraction rate $1$.

## Proof

The strong laws give

```math
\bar w_{ij,n}\longrightarrow w_{ij}
```

and

```math
\frac{M_{ij,n}}{n^2}
=
\frac{C_{n,i}C_{n,j}}{n^2}
\longrightarrow p_ip_j.
```

Multiplying the exact beta variance by $n^2$ gives the displayed limit.

The limiting coefficient is the stationary variance of the rate-one edge-parameter Ornstein-Uhlenbeck process of `findings-51.md`:

```math
\operatorname{Var}(\Xi_{ij})
=
\frac{w_{ij}(1-w_{ij})}{p_ip_j}.
```

Thus posterior uncertainty and quenched estimator fluctuations have the same support-order coefficient.

# 4. Predictive correlations from boundary uncertainty

Let $X$ and $Y$ be two distinct future possible edges in the same ordered block. Conditional on the current data, they are independent given $w_{ij}$, but not after $w_{ij}$ is integrated out.

## Proposition 3. Exact future-edge correlation

The predictive covariance is

```math
\operatorname{Cov}
(X,Y\mid\mathcal F_n)
=
\operatorname{Var}
(w_{ij}\mid\mathcal F_n).
```

Consequently,

```math
n^2
\operatorname{Cov}
(X,Y\mid\mathcal F_n)
\longrightarrow
\frac{w_{ij}(1-w_{ij})}{p_ip_j}.
```

## Proof

Conditional independence gives

```math
\mathbb E[XY\mid w_{ij},\mathcal F_n]
=w_{ij}^2.
```

The law of total covariance therefore reduces the predictive covariance to the posterior variance of $w_{ij}$.

The unresolved boundary variable creates an order-two correlation between otherwise independent future relational events. That correlation vanishes at the same rate as the pair-supported continuum mode.

# 5. General support-order information law

The preceding calculations are instances of a general counting principle. Suppose a scalar Bernoulli parameter $\lambda$ controls independent relation variables attached to admissible $r$-vertex supports. Give $\lambda$ a beta prior and let $M_n$ be the number of observed admissible supports by level $n$. Assume

```math
\frac{M_n}{n^r}\longrightarrow c>0
```

almost surely.

## Theorem 4. Conjugate support-order contraction

Let $\bar\lambda_n$ be the beta posterior mean. Conditional on the selected value $\lambda$,

```math
n^r
\operatorname{Var}
(\lambda\mid\mathcal F_n)
\longrightarrow
\frac{\lambda(1-\lambda)}c
```

almost surely. Hence the posterior standard deviation contracts as

```math
n^{-r/2}
```

and therefore as

```math
e^{-rs/2}
```

in logarithmic size.

## Proof

The beta posterior variance has the exact form

```math
\frac{
\bar\lambda_n(1-\bar\lambda_n)
}{
 a+b+M_n+1
}.
```

The conditional strong law gives $\bar\lambda_n\to\lambda$. Multiplication by $n^r$ and the assumed opportunity asymptotic give the result.

The same statement holds componentwise for a finite categorical relation with a Dirichlet prior.

# 6. The dual meaning of the half-integer spectrum

The support-order spectrum has two independent derivations. For quenched finite-pattern fluctuations, $r$ supporting vertices give normalization $n^{r/2}$ and relaxation rate $r/2$. For posterior sector uncertainty, $O(n^r)$ relational observations give standard deviation $n^{-r/2}$ and contraction rate $r/2$.

The same exponent therefore governs both random fluctuations around a selected sector and information gained about an unresolved sector parameter.

# 7. Martingale distinction

The posterior means

```math
\bar p_n
=
\mathbb E[p\mid\mathcal F_n]
```

and

```math
\bar w_{ij,n}
=
\mathbb E[w_{ij}\mid\mathcal F_n]
```

are bounded martingales under the nonextremal mixture law. They converge to the boundary variable. This learning process should not be confused with the stationary Ornstein-Uhlenbeck fluctuations obtained after conditioning on a fixed extremal sector.

The two descriptions are complementary. Under the annealed law, the posterior martingale learns $\Theta$; under the quenched law, the empirical field fluctuates around a fixed value of $\Theta$.

The degree-zero mode is the unresolved limiting boundary value, while the positive half-integer modes describe the finite-size information and fluctuation scales around it.

Exact rational calculations confirm:

- the Dirichlet covariance matrix against direct first and second moments;
- the beta posterior variance against direct moments;
- the equality between future-edge predictive covariance and posterior beta variance;
- convergence of the rescaled one-vertex and pair-information coefficients in representative rational sectors;
- the general beta support-order formula for several support orders.
