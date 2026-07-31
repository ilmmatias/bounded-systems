# 1. Stop assuming diffusive time in advance

Let $\delta\to0$ index a refinement of the profile geometry, and let

```math
a_\delta\to0
```

be the compositional time represented by one microscopic channel step.

Write the derived profile-increment kernel as

```math
K_{\delta,h}(x,dy),
```

where $y$ is the local profile displacement caused by one edge.

The rescaled generator is

```math
\mathcal L_{\delta}^{h}f(x)=
\frac1{a_\delta}
\int
\bigl[f(x+y)-f(x)\bigr]
K_{\delta,h}(x,dy).
```

The previous analysis selected

```math
a_\delta=\delta^2
```

and assumed $y=O(\delta)$. That singled out Gaussian diffusion.

The general question is instead:

```math
\text{For which }a_\delta
\text{ does }\mathcal L_\delta^h
\text{ have a finite nontrivial limit?}
```

# 2. The universal Markovian continuum generator

Under the usual tightness and convergence conditions on the triangular array of increment kernels, the canonical local-in-time Markov limit is a Lévy-type operator

```math
\begin{aligned}
\mathcal L^hf(x)
={}&
b_h(x)\cdot\nabla f(x)
+
\frac12a_h^{ij}(x)\partial_i\partial_jf(x)\\
&+
\int_{\mathbb R^d\setminus\{0\}}
\left[
f(x+y)-f(x)-\chi(y)\cdot\nabla f(x)
\right]
\nu_h(x,dy),
\end{aligned}
```

where

```math
\chi(y)=y\,\mathbf1_{\{|y|<1\}}
```

is a conventional truncation.

The three coefficients have distinct origins: $b_h$ is the finite first-order transport, $a_h$ is the accumulated quadratic variation of vanishing jumps, and $\nu_h(x,dy)$ is the limiting rate of nonvanishing jumps.

Existence and uniqueness of a process with such a nonlocal generator are formulated through its martingale problem; well-posedness holds under various regularity and nondegeneracy assumptions but is not automatic for arbitrary coefficients.

The density equation is simply

```math
\partial_\tau\rho=
(\mathcal L^h)^\ast\rho.
```

The Lévy-type equation is the general Markovian replacement for Fokker-Planck diffusion.

# 3. The nonlocal $h$-transform

The harmonic profile still determines the effective dynamics.

Let the untransformed continuum generator be

```math
\begin{aligned}
\mathcal L_0f
={}&
b\cdot\nabla f
+
\frac12a^{ij}\partial_i\partial_jf\\
&+
\int
\left[
f(x+y)-f(x)-\chi(y)\cdot\nabla f(x)
\right]\nu(x,dy)
-c(x)f.
\end{aligned}
```

Suppose the critical profile satisfies

```math
\mathcal L_0h=\kappa h,
\qquad h>0.
```

The transformed generator is

```math
\mathcal L^hf=
h^{-1}\mathcal L_0(hf)-\kappa f.
```

The formula applies to both local and nonlocal generators.

Set $r_h(x,y)=\frac{h(x+y)}{h(x)}$.

Then the transformed jump measure is

```math
\nu_h(x,dy)=
r_h(x,y)\nu(x,dy).
```

The transformed drift is

```math
b_h=
b+a\nabla\log h
+
\int
\chi(y)\bigl[r_h(x,y)-1\bigr]\nu(x,dy).
```

This gives

```math
\begin{aligned}
\mathcal L^hf
={}&
b_h\cdot\nabla f
+
\frac12a:\nabla^2f\\
&+
\int
\left[
f(x+y)-f(x)-\chi(y)\cdot\nabla f
\right]
\nu_h(x,dy).
\end{aligned}
```

The earlier relation

```math
b_h=b+a\nabla\log h
```

was only the diffusion part of a more general result.

In the jump regime, the profile also reweights every finite displacement:

```math
\nu_h(x,dy)=
\frac{h(x+y)}{h(x)}
\nu(x,dy).
```

The identity is the continuum analogue of

```math
P_h(e\mid v)=
\frac{h(r(e))}{\lambda h(v)}.
```

# 4. The nonlocal critical-profile equation

Write $u=\log h$.

Dividing

```math
\mathcal L_0h=\kappa h
```

by $h$ gives

```math
\begin{aligned}
\kappa
={}&
b\cdot\nabla u
+
\frac12a:
\left(
\nabla^2u+\nabla u\otimes\nabla u
\right)
-c\\
&+
\int
\left[
e^{u(x+y)-u(x)}
-1
-\chi(y)\cdot\nabla u(x)
\right]
\nu(x,dy).
\end{aligned}
```

The equation is the nonlocal extension of the logarithmic critical-profile equation.

The previous viscous Hamilton-Jacobi equation is recovered when

```math
\nu=0.
```

The master profile equation of the full Markovian continuum family is

```math
\begin{aligned}
\kappa+c
={}&
b\cdot\nabla u
+
\frac12a:
\left(
\nabla^2u+\nabla u\otimes\nabla u
\right)\\
&+
\int
\left[
e^{\Delta_yu}
-1-\chi(y)\cdot\nabla u
\right]\nu(x,dy).
\end{aligned}
```

The exponential jump term is not a perturbative correction. It is the exact survival of finite profile displacements.

# 5. Regime I: ballistic transport

Suppose $\Delta_\delta x=O(\delta)$, but the conditional mean is also $O(\delta)$, rather than $O(\delta^2)$.

Then the correct time scale is

```math
a_\delta=\delta.
```

The quadratic variation per unit rescaled time vanishes:

```math
\frac{\mathbb E[\Delta x\otimes\Delta x]}{\delta}=
O(\delta)\to0.
```

The limit is first order:

```math
\mathcal L^hf=b_h\cdot\nabla f,
```

and

```math
\partial_\tau\rho
+
\nabla\cdot(b_h\rho)=0.
```

It occurs when directed bias survives more strongly than route dispersion.

# 6. Regime II: Gaussian diffusion

Suppose the increments satisfy

```math
\Delta_\delta x=O(\delta),
\qquad
\mathbb E[\Delta_\delta x]=O(\delta^2),
\qquad
\mathbb E[\Delta_\delta x\otimes\Delta_\delta x]=O(\delta^2),
```

and assume that the Lindeberg condition excludes significant large jumps.

It follows that

```math
a_\delta=\delta^2,
```

This gives

```math
\nu_h=0,
```

and

```math
\mathcal L^hf=
b_h\cdot\nabla f
+
\frac12a_h:\nabla^2f.
```

Central-limit results for dependent or nonhomogeneous Markov triangular arrays require appropriate mixing or correlation control, which must eventually be checked for the graph-derived kernels.

# 7. Regime III: rare finite jumps

Suppose most increments vanish, but finite displacements $y=O(1)$ occur with probability

```math
a_\delta\,\nu(x,dy)+o(a_\delta).
```

It follows that

```math
\mathcal L^hf=
b_h\cdot\nabla f
+
\frac12a_h:\nabla^2f
+
\int
[f(x+y)-f(x)]
\nu_h(x,dy),
```

when the jump measure has finite mass:

```math
\nu_h(x,\mathbb R^d)<\infty.
```

The limit is a compound-Poisson or finite-activity jump-diffusion.

Because $y$ is not small, the third and higher Taylor coefficients do not vanish but resum into the full nonlocal expression

```math
f(x+y)-f(x).
```

The anomalous object is the jump integral, not an infinite higher-derivative PDE.

# 8. Regime IV: stable and fractional spatial dynamics

Suppose the increment distribution has heavy tails with index

```math
0<\alpha<2.
```

The quadratic moment may not exist, making diffusive scaling wrong; the natural scaling is typically

```math
a_\delta=\delta^\alpha.
```

The limiting jump kernel has the form

```math
\nu(x,dy)
\sim
\frac{c(x,\widehat y)}
{|y|^{d+\alpha}}\,dy.
```

For an isotropic symmetric kernel,

```math
\mathcal Lf=
-C_\alpha(-\Delta)^{\alpha/2}f.
```

After the harmonic transform,

```math
\nu_h(x,dy)=
e^{u(x+y)-u(x)}
\frac{c(x,\widehat y)}
{|y|^{d+\alpha}}\,dy.
```

The effective equation is

```math
\partial_\tau\rho=
(\mathcal L_\alpha^h)^\ast\rho,
```

with a profile-biased fractional or stable-like operator.

Stable limits can arise for heavy-tailed additive functionals of Markov chains under suitable mixing and operator assumptions, whereas state-dependent stable-like generators require separate martingale-problem analysis.

The critical-profile equation becomes

```math
\kappa=
\int
\left[
e^{u(x+y)-u(x)}
-1
-\chi(y)\cdot\nabla u
\right]
\frac{c(x,\widehat y)}
{|y|^{d+\alpha}}\,dy
-c,
```

plus any surviving local drift or diffusion terms.

# 9. Regime V: mixed Lévy dynamics

Nothing forces the limit to be purely Gaussian or purely stable.

The general limit can simultaneously contain:

* drift;
* Brownian quadratic variation;
* finite jumps;
* infinitely many small jumps;
* anisotropic stable components.

Its symbol is

```math
\begin{aligned}
\Psi_h(x,k)
={}&
i,b_h(x)\cdot k
-\frac12k^\top a_h(x)k\\
&+
\int
\left[
e^{ik\cdot y}
-1
-i,k\cdot\chi(y)
\right]
\nu_h(x,dy).
\end{aligned}
```

When the coefficients are translation invariant,

```math
\mathcal L^he^{ik\cdot x}=
\Psi_h(k)e^{ik\cdot x}.
```

The Lévy symbol replaces the quadratic Gaussian dispersion relation.

Thus the complete Markovian classification is encoded by the Lévy triplet

```math
(b_h,a_h,\nu_h).
```

# 10. Regime VI: anomalous internal clock

There is another failure mode that does not alter spatial increments. Instead, the number of microscopic channel steps required for one coarse profile transition becomes heavy-tailed.

Let $\Pi$ be a coarse profile partition, and define the first exit length

```math
W
=
\min{n\ge1:\Pi(X_n)\ne\Pi(X_0)}.
```

The clock is intrinsic: $W$ counts primitive channel compositions before the coarse profile changes.

Suppose that

```math
\Pr(W>n)\sim n^{-\gamma},
\qquad
0<\gamma<1.
```

Then the coarse profile clock has no finite mean. In scaling limits it can be represented by an inverse stable subordinator, producing the time-fractional equation

```math
\partial_\tau^\gamma\rho=
(\mathcal L^h)^\ast\rho,
```

where $\partial_\tau^\gamma$ is the Caputo-type fractional derivative.

Inverse-stable-subordinator time changes convert ordinary Kolmogorov or Fokker-Planck equations into time-fractional equations.

The distribution of microscopic path lengths between coarse profile events can therefore generate fractional time.

# 11. Regime VII: long-range history dependence

Acyclicity prevents exact recurrence but does not imply independent or short-range-correlated successive profile increments.

Reconvergence and common deep ancestry can produce correlations

```math
C(m)=
\mathbb E[
\Delta X_n\otimes\Delta X_{n+m}
].
```

If

```math
\sum_{m\ge0}|C(m)|<\infty,
```

those correlations can often be absorbed into an effective finite covariance.

If instead

```math
C(m)\sim m^{-\eta},
\qquad
0<\eta<1,
```

The covariance sum diverges. The correct scaling may be

```math
n^{-H}\sum_{k=1}^n\Delta X_k,
\qquad
H\ne\frac12.
```

Possible limits include:

* fractional Brownian motion;
* operator fractional Brownian motion;
* Rosenblatt or higher Hermite processes.

Long-range-dependent systems can have Gaussian or non-Gaussian functional limits according to their dependence structure and Hermite rank.

The anomalous-clock regime differs from Lévy dynamics: a Lévy anomaly is nonlocality with independent increments, whereas a long-memory anomaly is produced by history-dependent temporal correlations.

The profile state alone is then generally not Markovian.

One must enlarge the state to include sufficient history or use a memory equation such as

```math
\partial_\tau\rho(\tau)=
\int_0^\tau
K(\tau-s)
(\mathcal L^h)^\ast\rho(s)\,ds.
```

Unlike the Lévy case, no single universal memory kernel is determined solely by a tail exponent; the detailed route-correlation structure matters.

# 12. Regime classification procedure

The continuum regime is determined from the microscopic characteristics by the following procedure:

1. Choose $a_\delta$ so that at least one rescaled characteristic remains finite and nonzero.
2. For every set $A$ bounded away from zero, examine $a_\delta^{-1}K_{\delta,h}(x,A)$. A nonzero limiting measure produces a jump term.
3. Examine the vanishing-jump covariance $a_\delta^{-1}\int_{|y|\le\varepsilon} y\otimes y\,K_{\delta,h}(x,dy)$. Taking first $\delta\to0$ and then $\varepsilon\to0$ determines the Gaussian covariance $a_h$.
4. Check whether the accumulated temporal cross-covariances are summable, even when the one-step characteristics converge.
5. Inspect the coarse exit lengths; heavy-tailed block lengths indicate an anomalous clock rather than anomalous spatial noise.

The resulting classification is

```math
\begin{array}{c|c}
\text{surviving structure}&\text{limit}\\
\hline
\text{mean only}&\text{transport}\\
\text{finite quadratic variation}&\text{diffusion}\\
\text{finite-rate macroscopic jumps}&\text{compound Poisson}\\
\text{heavy-tailed jumps}&\text{stable/fractional space}\\
\text{heavy-tailed exit lengths}&\text{fractional time}\\
\text{nonsummable correlations}&\text{memory/fractional-history}\\
\text{several of these}&\text{mixed anomalous regime}
\end{array}
```

# 13. The fluctuation representation also changes

The Gaussian regime uses Wiener chaos:

```math
\Gamma_s(\mathfrak t_h).
```

A jump regime naturally introduces Poisson chaos associated with the Lévy measure:

```math
\Gamma_s\!\left(
L^2(\nu_h)
\right).
```

For a mixed Gaussian-jump limit, the fluctuation space takes the schematic form

```math
\Gamma_s(\mathfrak t_h)
\otimes
\Gamma_s\!\left(L^2(\nu_h)\right).
```

Square-integrable functionals of Poisson random measures admit a Wiener-Itô/Fock-space chaos representation, the jump counterpart of the Gaussian fluctuation construction.

There remains a total chaos number operator

```math
N_{\mathrm{tot}}.
```

The critical gauge phase acts as

```math
e^{-i\beta\tau N_{\mathrm{tot}}},
\qquad
\beta=\log\lambda.
```

Let $\mathbb H_h$ denote the closed dissipative generator of the limiting fluctuation dynamics, once it exists.

Then the general complex equation becomes

```math
\partial_\tau\Psi=
-\left[
\mathbb H_h
+
i\beta N_{\mathrm{tot}}
\right]\Psi.
```

# 14. The new obstruction: chaos-degree mixing

In the Gaussian linear regime,

```math
\mathbb H_h=d\Gamma(B_h),
```

so

```math
[\mathbb H_h,N_{\mathrm{tot}}]=0.
```

The dissipative and gauge parts preserve the same homogeneous grading.

For a general nonlinear or state-dependent jump limit, this need not remain true.

The degree-mixing commutator is

```math
\mathfrak C_h=
[\mathbb H_h,N_{\mathrm{tot}}].
```

The commutator obstructs decomposition into independent chaos degrees.

If $\mathfrak C_h=0$, then

```math
\Psi_\tau=
e^{-\tau\mathbb H_h}
e^{-i\beta\tau N_{\mathrm{tot}}}
\Psi_0,
```

and the modes can be resolved simultaneously by relaxation and compositional degree. If $\mathfrak C_h\ne0$, jump interactions create or destroy effective fluctuation degree. The gauge grading remains defined, but it is no longer conserved by the dissipative dynamics.

The commutator is the first invariant beyond the free quadratic regime.

# 15. The completed anomalous equations

The full Markovian continuum regime is governed by

```math
\begin{aligned}
\mathcal L_0h&=\kappa h,\\[1mm]
\mathcal L^hf&=h^{-1}\mathcal L_0(hf)-\kappa f,\\[1mm]
\partial_\tau\rho&=(\mathcal L^h)^\ast\rho,\\[1mm]
\partial_\tau\Psi
&=-
\left[
\mathbb H_h+i(\log\lambda)N_{\mathrm{tot}}
\right]\Psi.
\end{aligned}
```

The explicit spatial generator is

```math
\begin{aligned}
\mathcal L^hf
={}&
b_h\cdot\nabla f
+\frac12a_h:\nabla^2f\\
&+
\int
\left[
f(x+y)-f(x)-\chi(y)\cdot\nabla f
\right]
\nu_h(x,dy),
\end{aligned}
```

with

```math
\nu_h(x,dy)=
\frac{h(x+y)}{h(x)}\nu(x,dy),
```

and

```math
b_h=
b+a\nabla\log h
+
\int\chi(y)
\left[
\frac{h(x+y)}{h(x)}-1
\right]\nu(x,dy).
```

The Gaussian regime is the special case

```math
\nu=0.
```

The anomalous spatial regimes are exactly the cases

```math
\nu\ne0.
```

Anomalous-clock and long-memory regimes arise when no closed Markov generator on the instantaneous profile manifold suffices.
