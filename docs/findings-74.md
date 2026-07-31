# 1. Endpoint multiplicativity

The terminal-selection theorem of `findings-68.md` uses finite endpoints whose empirical profiles converge to the selected sector. This is valid for extremal sectors, but it cannot hold for a genuinely nonextremal target.

For finite DAGs, homomorphism densities satisfy the exact identity

```math
t(F\sqcup G,K)
=
t(F,K)t(G,K).
```

The maps from the two components are sampled independently, so the identity holds at every finite order, not only asymptotically.

## Proposition 1. Endpoint limits are extremal

Every coordinatewise limit of finite endpoint homomorphism profiles is multiplicative on disjoint unions. The associated central law is therefore dissociated and extremal.

## Proof

Pass the finite multiplicativity identity to the limit. Multiplicativity of all finite homomorphism coordinates is equivalent to dissociation of restrictions on disjoint vertex sets, hence to extremality of the exchangeable central law.

For a central mixture with ergodic law $\nu$,

```math
\begin{aligned}
t(F\sqcup G,\mu)
-
t(F,\mu)t(G,\mu)
=
\operatorname{Cov}_{\nu}
\left(
 t(F,\xi),t(G,\xi)
\right).
\end{aligned}
```

Distinct phases make this covariance nonzero for some pair of finite patterns. Such a mixture cannot be the projective limit of individual endpoints.

# 2. Correction to terminal selection

The concentration theorem of `findings-68.md` must be read with an extremality or endpoint-approximability hypothesis on the uniquely forced target. Its proof explicitly uses a deterministic sequence $K_N^\star$ whose forcing energy tends to zero. Such sequences exist for extremal sectors by the sampling theorem, but not for genuinely nonextremal profiles.

Finite forcing does not imply approximation by a single sequence of endpoints.

# 3. Phase-specific terminal ensembles

Let

```math
\mu
=
\sum_{a=1}^r\lambda_a\mu^a
```

be a finite mixture of absolutely forced extremal sectors. For each phase choose a finite endpoint energy $\mathcal E_{a,N}(K)$, an inverse temperature $\beta_N$, and define

```math
Z_{a,N}
=
\sum_{K\in\mathfrak D_N}
\dim(K)
\exp\left(-\beta_N\mathcal E_{a,N}(K)\right).
```

The normalized phase endpoint law is

```math
\pi_{a,N}(K)
=
\frac{
 \dim(K)e^{-\beta_N\mathcal E_{a,N}(K)}
}{Z_{a,N}}.
```

Assume the hypotheses of `findings-68.md` hold for each extremal phase, so its finite-horizon coherent marginals converge to $\mu^a$.

# 4. Calibrated multiwell weight

Define one terminal weight by

```math
w_N^{\mathrm{mix}}(K)
=
\sum_{a=1}^r
\frac{\lambda_a}{Z_{a,N}}
\exp\left(-\beta_N\mathcal E_{a,N}(K)\right).
```

Its total path-counting partition function is exactly one:

```math
\sum_K\dim(K)w_N^{\mathrm{mix}}(K)
=
\sum_a\lambda_a
=1.
```

Hence the endpoint law is the exact mixture

```math
\pi_N^{\mathrm{mix}}
=
\sum_{a=1}^r\lambda_a\pi_{a,N}.
```

## Theorem 2. Terminal selection of a finite phase mixture

For every fixed level $n$,

```math
\mu_n^{N,\mathrm{mix}}
\longrightarrow
\sum_{a=1}^r\lambda_a\mu_n^a.
```

The normalized backward route counts converge to

```math
h_n^\mu
=
\sum_a\lambda_ah_n^a,
```

and every positive-mass up transition converges to

```math
U_n^\mu(G,H)
=
\sum_a
\pi_n(a\mid G)U_n^a(G,H).
```

## Proof

The finite-horizon marginal is linear in the endpoint law:

```math
\mu_n^{N,\mathrm{mix}}
=
\sum_a\lambda_a\mu_n^{N,a}.
```

Each term converges to $\mu_n^a$. Harmonic and transition convergence then follows from the profile reconstruction formulas, exactly as in `findings-68.md`.

# 5. Entropic phase weights

The factors $Z_{a,N}^{-1}$ calibrate the desired phase probabilities. Without them, an unnormalized multiwell weight

```math
\sum_a c_a e^{-\beta_N\mathcal E_{a,N}}
```

selects phase proportions proportional to the asymptotic well partition functions as well as the coefficients $c_a$. The resulting weights contain an entropic contribution from the number and path multiplicity of low-energy endpoints in each phase.

This is not a defect. It identifies a second possible selection principle: phase weights can be imposed externally by calibration, or allowed to emerge from relative endpoint entropy.

# 6. Finite phase closure

The multiwell construction gives a route-counting realization of the finite adaptive state in `findings-73.md`. At finite level, the endpoint updates both the graph state and the posterior phase weights. In the limit, the posterior selects one extremal phase almost surely, while the annealed law retains the finite degree-zero mixture.

Exact finite-model calculations confirm endpoint multiplicativity, calibrated multiwell normalization, convergence of the mixed lower marginals, and the adaptive up-transition identity.
