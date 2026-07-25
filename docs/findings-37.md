# 1. Stop assuming diffusive time in advance

Let $\delta\to0$ index a refinement of the profile geometry, and let

$$
a_\delta\to0
$$

be the compositional time represented by one microscopic channel step.

Write the derived profile-increment kernel as

$$
K_{\delta,h}(x,dy),
$$

where $y$ is the local profile displacement caused by one edge.

The rescaled generator is

$$
\mathcal L_{\delta}^{h}f(x)=
\frac1{a_\delta}
\int
\bigl[f(x+y)-f(x)\bigr]
K_{\delta,h}(x,dy).
$$

Previously we selected

$$
a_\delta=\delta^2
$$

and assumed $y=O(\delta)$. That singled out Gaussian diffusion.

The general question is instead:

$$
\text{For which }a_\delta
\text{ does }\mathcal L_\delta^h
\text{ have a finite nontrivial limit?}
$$

---

# 2. The universal Markovian continuum generator

Under the usual tightness and convergence conditions on the triangular array of increment kernels, the canonical local-in-time Markov limit is a Lévy-type operator

$$
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
$$

where

$$
\chi(y)=y,\mathbf1_{\{|y|<1\}}
$$

is a conventional truncation.

The three coefficients have distinct origins:

$$
b_h=
\text{finite first-order transport},
$$

$$
a_h=
\text{accumulated vanishing-jump quadratic variation},
$$

$$
\nu_h(x,dy)=
\text{limiting rate of nonvanishing jumps}.
$$

Existence and uniqueness of a process with such a nonlocal generator is naturally formulated through its martingale problem; well-posedness is known under various regularity and nondegeneracy assumptions but is not automatic for arbitrary coefficients.

The density equation is simply

$$
\partial_\tau\rho=
(\mathcal L^h)^\ast\rho.
$$

This is the general Markovian replacement for the Fokker–Planck equation.

---

# 3. The exact nonlocal (h)-transform

The harmonic profile still determines the effective dynamics.

Let the untransformed continuum generator be

$$
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
$$

Suppose the critical profile satisfies

$$
\mathcal L_0h=\kappa h,
\qquad h>0.
$$

The transformed generator is

$$
\mathcal L^hf=
h^{-1}\mathcal L_0(hf)-\kappa f.
$$

This formula is valid for both local and nonlocal generators.

Set

$$
r_h(x,y)=\frac{h(x+y)}{h(x)}.
$$

Then the transformed jump measure is

$$
\nu_h(x,dy)=
r_h(x,y)\nu(x,dy).
$$

The transformed drift is

$$
b_h=
b+a\nabla\log h
+
\int
\chi(y)\bigl[r_h(x,y)-1\bigr]\nu(x,dy).
$$

Therefore

$$
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
$$

So the earlier relation

$$
b_h=b+a\nabla\log h
$$

was only the diffusion part of a more general result.

In the jump regime, the profile also reweights every finite displacement:

$$
\nu_h(x,dy)=
\frac{h(x+y)}{h(x)}
\nu(x,dy).
$$

This is the continuum analogue of

$$
P_h(e\mid v)=
\frac{h(r(e))}{\lambda h(v)}.
$$

---

# 4. The nonlocal critical-profile equation

Write

$$
u=\log h.
$$

Dividing

$$
\mathcal L_0h=\kappa h
$$

by $h$ gives

$$
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
$$

This is the exact nonlocal extension of the logarithmic critical-profile equation.

The previous viscous Hamilton–Jacobi equation is recovered when

$$
\nu=0.
$$

Therefore the master profile equation of the full Markovian continuum family is

$$
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
$$

The exponential jump term is not a perturbative correction. It is the exact survival of finite profile displacements.

---

# 5. Regime I: ballistic transport

Suppose

$$
\Delta_\delta x=O(\delta),
$$

but the conditional mean is also $O(\delta)$, rather than $O(\delta^2)$.

Then the correct time scale is

$$
a_\delta=\delta.
$$

The quadratic variation per unit rescaled time vanishes:

$$
\frac{\mathbb E[\Delta x\otimes\Delta x]}{\delta}=
O(\delta)\to0.
$$

The limit is first order:

$$
\mathcal L^hf=b_h\cdot\nabla f,
$$

and

$$
\partial_\tau\rho
+
\nabla\cdot(b_h\rho)=0.
$$

This is the deterministic transport regime.

It occurs when directed bias survives more strongly than route dispersion.

---

# 6. Regime II: Gaussian diffusion

Suppose:

$$
\Delta_\delta x=O(\delta),
$$

$$
\mathbb E[\Delta_\delta x]=O(\delta^2),
$$

$$
\mathbb E[\Delta_\delta x\otimes\Delta_\delta x]=
O(\delta^2),
$$

and the Lindeberg condition excludes significant large jumps.

Then

$$
a_\delta=\delta^2,
$$

$$
\nu_h=0,
$$

and

$$
\mathcal L^hf=
b_h\cdot\nabla f
+
\frac12a_h:\nabla^2f.
$$

This is the quadratic regime already closed.

Central-limit results for dependent or nonhomogeneous Markov triangular arrays require appropriate mixing or correlation control, which is one of the conditions that must eventually be checked for the graph-derived kernels.

---

# 7. Regime III: rare finite jumps

Suppose most increments vanish, but finite displacements $y=O(1)$ occur with probability

$$
a_\delta,\nu(x,dy)+o(a_\delta).
$$

Then

$$
\mathcal L^hf=
b_h\cdot\nabla f
+
\frac12a_h:\nabla^2f
+
\int
[f(x+y)-f(x)]
\nu_h(x,dy),
$$

when the jump measure has finite mass:

$$
\nu_h(x,\mathbb R^d)<\infty.
$$

This is a compound-Poisson or finite-activity jump-diffusion regime.

The point is that the third and higher Taylor coefficients do **not** vanish here, because $y$ is not small. They resum into the full nonlocal expression

$$
f(x+y)-f(x).
$$

Therefore the anomalous object is the jump integral, not an infinite higher-derivative PDE.

---

# 8. Regime IV: stable and fractional spatial dynamics

Suppose the increment distribution has heavy tails with index

$$
0<\alpha<2.
$$

The quadratic moment may not exist, and diffusive scaling is wrong. The natural scaling is typically

$$
a_\delta=\delta^\alpha.
$$

The limiting jump kernel has the form

$$
\nu(x,dy)
\sim
\frac{c(x,\widehat y)}
{|y|^{d+\alpha}},dy.
$$

For an isotropic symmetric kernel,

$$
\mathcal Lf=
-C_\alpha(-\Delta)^{\alpha/2}f.
$$

After the harmonic transform,

$$
\nu_h(x,dy)=
e^{u(x+y)-u(x)}
\frac{c(x,\widehat y)}
{|y|^{d+\alpha}},dy.
$$

The effective equation is

$$
\partial_\tau\rho=
(\mathcal L_\alpha^h)^\ast\rho,
$$

with a profile-biased fractional or stable-like operator.

Stable limits can arise for heavy-tailed additive functionals of Markov chains under suitable mixing and operator assumptions, while state-dependent stable-like generators require their own martingale-problem analysis.

The critical-profile equation becomes

$$
\kappa=
\int
\left[
e^{u(x+y)-u(x)}
-1
-\chi(y)\cdot\nabla u
\right]
\frac{c(x,\widehat y)}
{|y|^{d+\alpha}},dy
-c,
$$

plus any surviving local drift or diffusion terms.

---

# 9. Regime V: mixed Lévy dynamics

Nothing forces the limit to be purely Gaussian or purely stable.

The general limit can simultaneously contain:

* drift;
* Brownian quadratic variation;
* finite jumps;
* infinitely many small jumps;
* anisotropic stable components.

Its symbol is

$$
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
$$

When the coefficients are translation invariant,

$$
\mathcal L^he^{ik\cdot x}=
\Psi_h(k)e^{ik\cdot x}.
$$

This symbol replaces the quadratic dispersion relation of the Gaussian regime.

Thus the complete Markovian classification is encoded by the Lévy triplet

$$
(b_h,a_h,\nu_h).
$$

---

# 10. Regime VI: anomalous internal clock

There is another failure mode that does not alter spatial increments. Instead, the number of microscopic channel steps required for one coarse profile transition becomes heavy-tailed.

Let $\Pi$ be a coarse profile partition, and define the first exit length

$$
W
=
\min{n\ge1:\Pi(X_n)\ne\Pi(X_0)}.
$$

This is entirely intrinsic: $W$ counts primitive channel compositions before the coarse profile changes.

Suppose

$$
\Pr(W>n)\sim n^{-\gamma},
\qquad
0<\gamma<1.
$$

Then the coarse profile clock has no finite mean. In scaling limits it can be represented by an inverse stable subordinator, producing the time-fractional equation

$$
\partial_\tau^\gamma\rho=
(\mathcal L^h)^\ast\rho,
$$

where $\partial_\tau^\gamma$ is the Caputo-type fractional derivative.

Time changes by inverse stable subordinators are known to convert ordinary Kolmogorov or Fokker–Planck equations into time-fractional ones.

The distribution of microscopic path lengths between coarse profile events can therefore generate fractional time.

---

# 11. Regime VII: long-range history dependence

Acyclicity prevents exact recurrence, but it does not force successive profile increments to be independent or short-range correlated.

Reconvergence and common deep ancestry can produce correlations

$$
C(m)=
\mathbb E[
\Delta X_n\otimes\Delta X_{n+m}
].
$$

If

$$
\sum_{m\ge0}|C(m)|<\infty,
$$

those correlations can often be absorbed into an effective finite covariance.

If instead

$$
C(m)\sim m^{-\eta},
\qquad
0<\eta<1,
$$

the covariance sum diverges. The correct scaling may be

$$
n^{-H}\sum_{k=1}^n\Delta X_k,
\qquad
H\ne\frac12.
$$

Possible limits include:

* fractional Brownian motion;
* operator fractional Brownian motion;
* Rosenblatt or higher Hermite processes.

Long-range dependent systems can have Gaussian or non-Gaussian functional limits depending on their dependence structure and Hermite rank.

This regime is different from Lévy dynamics:

$$
\text{Lévy anomaly}=
\text{independent-increment nonlocality},
$$

$$
\text{long-memory anomaly}=
\text{history-dependent temporal correlations}.
$$

The profile state alone is then generally not Markovian.

One must either enlarge the state to include sufficient history or use a memory equation such as

$$
\partial_\tau\rho(\tau)=
\int_0^\tau
K(\tau-s)
(\mathcal L^h)^\ast\rho(s),ds.
$$

Unlike the Lévy case, there is no single universal memory kernel determined solely by a tail exponent. The detailed route-correlation structure matters.

---

# 12. The regime decision tree

The continuum classification can now be stated directly from microscopic characteristics.

## Step 1: determine the correct time scale

Find $a_\delta$ such that at least one rescaled characteristic remains finite and nonzero.

## Step 2: inspect large jumps

For every set $A$ bounded away from zero, examine

$$
\frac1{a_\delta}
K_{\delta,h}(x,A).
$$

If this converges to a nonzero measure, a jump term survives.

## Step 3: inspect vanishing-jump covariance

Examine

$$
\frac1{a_\delta}
\int_{|y|\le\varepsilon}
y\otimes y,
K_{\delta,h}(x,dy).
$$

Taking first $\delta\to0$ and then $\varepsilon\to0$ determines the Gaussian covariance $a_h$.

## Step 4: inspect temporal correlations

Even if the one-step characteristics converge, check whether accumulated cross-covariances are summable.

## Step 5: inspect coarse exit lengths

Heavy-tailed block lengths indicate an anomalous clock rather than anomalous spatial noise.

The resulting classification is

$$
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
$$

---

# 13. The fluctuation representation also changes

The Gaussian regime uses Wiener chaos:

$$
\Gamma_s(\mathfrak t_h).
$$

A jump regime naturally introduces Poisson chaos associated with the Lévy measure:

$$
\Gamma_s\!\left(
L^2(\nu_h)
\right).
$$

For a mixed Gaussian–jump limit, the fluctuation space takes the schematic form

$$
\Gamma_s(\mathfrak t_h)
\otimes
\Gamma_s\!\left(L^2(\nu_h)\right).
$$

Square-integrable functionals of Poisson random measures admit a Wiener–Itô/Fock-space chaos representation, so this is the jump counterpart of the Gaussian fluctuation construction.

There remains a total chaos number operator

$$
N_{\mathrm{tot}}.
$$

The critical gauge phase acts as

$$
e^{-i\beta\tau N_{\mathrm{tot}}},
\qquad
\beta=\log\lambda.
$$

Let $\mathbb H_h$ denote the closed dissipative generator of the limiting fluctuation dynamics, once it exists.

Then the general complex equation becomes

$$
\partial_\tau\Psi=
*
\left[
\mathbb H_h
+
i\beta N_{\mathrm{tot}}
\right]\Psi.
$$

---

# 14. The new obstruction: chaos-degree mixing

In the Gaussian linear regime,

$$
\mathbb H_h=d\Gamma(B_h),
$$

so

$$
[\mathbb H_h,N_{\mathrm{tot}}]=0.
$$

The dissipative and gauge parts preserve the same homogeneous grading.

For a general nonlinear or state-dependent jump limit, this need not remain true.

Define

$$
\mathfrak C_h=
[\mathbb H_h,N_{\mathrm{tot}}].
$$

This is the exact obstruction to the complex evolution decomposing into independent chaos degrees.

## Degree-preserving anomalous regime

$$
\mathfrak C_h=0.
$$

Then

$$
\Psi_\tau=
e^{-\tau\mathbb H_h}
e^{-i\beta\tau N_{\mathrm{tot}}}
\Psi_0,
$$

and the modes can be resolved simultaneously by relaxation and compositional degree.

## Degree-mixing anomalous regime

$$
\mathfrak C_h\ne0.
$$

Then jump interactions create or destroy effective fluctuation degree. The gauge grading remains defined, but it is no longer conserved by the dissipative dynamics.

This commutator is therefore the first invariant beyond the free quadratic regime.

---

# 15. The completed anomalous equations

The full Markovian continuum regime is governed by

$$
\begin{aligned}
\mathcal L_0h&=\kappa h,[1mm]
\mathcal L^hf&=h^{-1}\mathcal L_0(hf)-\kappa f,[1mm]
\partial_\tau\rho&=(\mathcal L^h)^\ast\rho,[1mm]
\partial_\tau\Psi
&=-
\left[
\mathbb H_h+i(\log\lambda)N_{\mathrm{tot}}
\right]\Psi.
\end{aligned}
$$

The explicit spatial generator is

$$
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
$$

with

$$
\nu_h(x,dy)=
\frac{h(x+y)}{h(x)}\nu(x,dy),
$$

and

$$
b_h=
b+a\nabla\log h
+
\int\chi(y)
\left[
\frac{h(x+y)}{h(x)}-1
\right]\nu(x,dy).
$$

The Gaussian regime is the special case

$$
\nu=0.
$$

The anomalous spatial regimes are exactly the cases

$$
\nu\ne0.
$$

The anomalous-clock and long-memory regimes occur when no closed Markov generator on the instantaneous profile manifold suffices.
