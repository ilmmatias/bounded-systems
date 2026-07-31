# 1. Positive critical-profile manifold

Fix the critical eigenvalue

```math
\lambda=R^{-2},
```

and consider normalized positive profiles

```math
\mathcal H_\lambda^+=
\left\lbrace h>0: \mathcal A_+h=\lambda h,\quad h(o)=1 \right\rbrace.
```

Write $u=\log h$.

The harmonic equation becomes the exact nonlinear profile equation

```math
\mathcal F_v(u)=
\log\left(
\sum_{e:s(e)=v}e^{u(r(e))}
\right)
-u(v)-\log\lambda
=0.
```

Define the derived edge kernel

```math
P_h(e\mid v)=
\frac{h(r(e))}{\lambda h(v)}=
\frac{e^{u(r(e))}}
{\sum_{f:s(f)=v}e^{u(r(f))}}.
```

The outgoing channel law is the softmax of the successor log-profiles, a generalized Doob $h$-transform of the channel-counting operator obtained from the positive eigenpair $(h,\lambda)$.

No probability was added here: normalization of the positive harmonic profile produced it.

# 2. First variation

Take a smooth profile curve through $h$:

```math
h_\varepsilon(v)=
h(v)
\exp\left(
\varepsilon\phi(v)
+\frac{\varepsilon^2}{2}\chi(v)
+o(\varepsilon^2)
\right).
```

Normalization gives

```math
\phi(o)=0,
\qquad
\chi(o)=0.
```

Here

```math
\phi=
\left.\frac{d}{d\varepsilon}\log h_\varepsilon\right|_0
```

is a tangent score.

Differentiate $\mathcal F_v(u_\varepsilon)=0$. Since

```math
D\mathcal F_v(u)[\phi]=
\sum_{e:s(e)=v}P_h(e\mid v)\phi(r(e))
-\phi(v),
```

The tangent equation is

```math
P_h\phi=\phi.
```

Explicitly,

```math
\phi(v)=
\sum_{e:s(e)=v}
P_h(e\mid v)\phi(r(e)).
```

Tangent vectors to the fixed-$\lambda$ profile manifold are harmonic observables of the derived dynamics.

The tangent equation is the first dynamical equation on the profile manifold.

# 3. Local quadratic variation

Differentiate a second time.

The Hessian of the log-sum-exp term is a covariance:

```math
D^2\mathcal F_v(u)[\phi,\psi]=
\sum_eP_h(e\mid v)\phi(r(e))\psi(r(e))-
(P_h\phi)(v)(P_h\psi)(v).
```

For tangent fields $P_h\phi=\phi$ and $P_h\psi=\psi$, this becomes

```math
\mathsf Q_v(\phi,\psi)=
\sum_{e:s(e)=v}
P_h(e\mid v)
\bigl[\phi(r(e))-\phi(v)\bigr]
\bigl[\psi(r(e))-\psi(v)\bigr].
```

In particular,

```math
\mathsf Q_v(\phi)=
\sum_{e:s(e)=v}
P_h(e\mid v)
\bigl[\phi(r(e))-\phi(v)\bigr]^2.
```

The quadratic form is the local carré du champ on the profile tangent space.

It is symmetric, nonnegative, and zero exactly in tangent directions locally constant over the supported outgoing channels.

After quotienting null directions, it is a genuine local metric.

# 4. The $\varepsilon\to0$ metric

Let $X,Y\in T_h\mathcal H_\lambda^+$, with score fields

```math
\phi_X=X\log h,
\qquad
\phi_Y=Y\log h.
```

The local metric is therefore

```math
g_v(X,Y)=
\mathsf Q_v(\phi_X,\phi_Y).
```

Now perturb the outgoing kernel:

```math
P_\varepsilon(e\mid v)=
P_{h_\varepsilon}(e\mid v).
```

Its score is

```math
\left.
\frac{d}{d\varepsilon}
\log P_\varepsilon(e\mid v)
\right|_0=
\phi_X(r(e))-\phi_X(v).
```

Taking the second-order limit yields

```math
\lim_{\varepsilon\to0}
\frac{2}{\varepsilon^2}
D_{\mathrm{KL}}
\left(
P_{h_\varepsilon}(\cdot\mid v)
\middle|
P_h(\cdot\mid v)
\right)=
g_v(X,X).
```

In this regime, the quadratic variation and Fisher metric are the same tensor:

```math
\text{local quadratic variation}=
\text{local Fisher information}.
```

KL divergence standardly has Fisher information as its second-order local term; here, the harmonic profile equation forces the explicit tensor.

# 5. The forced second-order profile equation

Expanding

```math
\mathcal F_v(u_\varepsilon)=0
```

to second order gives

```math
D\mathcal F_v[\chi]
+
D^2\mathcal F_v[\phi,\phi]
=0.
```

Equivalently,

```math
(P_h-I)\chi+\mathsf Q(\phi)=0,
```

or

```math
(I-P_h)\chi=
\mathsf Q(\phi).
```

Equivalently, defining

```math
\Gamma_h(\phi)=
\frac12\mathsf Q(\phi),
```

Hence the correction satisfies

```math
(I-P_h)\chi=
2\Gamma_h(\phi).
```

The first-order deformation is harmonic:

```math
(I-P_h)\phi=0,
```

while its second-order logarithmic correction is sourced by its own quadratic variation:

```math
\text{profile curvature}=
\text{Green response to local fluctuation energy}.
```

Formally, after choosing a boundary condition or complementary harmonic gauge,

```math
\chi=
(I-P_h)^{-1}\mathsf Q(\phi).
```

The inverse is the derived Green operator of the effective dynamics.

## A consistency check

Because the original eigenprofile equation is linear in $h$, a mixture-affine deformation

```math
h_\varepsilon=h+\varepsilon\dot h=
h(1+\varepsilon\phi)
```

remains harmonic whenever

```math
\mathcal A_+\dot h=\lambda\dot h.
```

However,

```math
\log(1+\varepsilon\phi)=
\varepsilon\phi-\frac{\varepsilon^2}{2}\phi^2+O(\varepsilon^3),
```

so in exponential coordinates

```math
\chi=-\phi^2.
```

It follows that

```math
(I-P_h)(-\phi^2)=
P_h(\phi^2)-\phi^2=
\mathsf Q(\phi),
```

exactly as required.

The quadratic equation gives the exact conversion between:

```math
\text{affine harmonic coordinates }h
```

and

```math
\text{exponential/information coordinates }u=\log h.
```

# 6. Quadratic variation along the actual derived dynamics

Let $X_n$ be the node process generated by $P_h$:

```math
\Pr(X_{n+1}=r(e)\mid X_n=v)=P_h(e\mid v).
```

For every tangent score $\phi$,

```math
P_h\phi=\phi,
```

so

```math
M_n^\phi=\phi(X_n)
```

is a martingale.

Its one-step conditional quadratic variation is

```math
\mathbb E_h
\left[
(M_{n+1}^\phi-M_n^\phi)^2
\mid X_n=v
\right]=
\mathsf Q_v(\phi).
```

For two tangent fields,

```math
\mathbb E_h
\left[
\Delta M_n^\phi\Delta M_n^\psi
\mid X_n=v
\right]=
\mathsf Q_v(\phi,\psi).
```

The predictable quadratic covariation is

```math
\left\langle
M^\phi,M^\psi
\right\rangle_N=
\sum_{n=0}^{N-1}
\mathsf Q_{X_n}(\phi,\psi).
```

The metric is the pathwise fluctuation tensor of the dynamics encoded by the harmonic profile.

# 7. The finite-horizon profile metric

For a length-$N$ route

```math
p=e_N\cdots e_1,
```

The derived path probability telescopes:

```math
\begin{aligned}
\mathbb P_h(p)
&=
\prod_{k=1}^N
\frac{h(v_k)}{\lambda h(v_{k-1})}\\
&=
\lambda^{-N}
\frac{h(v_N)}{h(o)}.
\end{aligned}
```

All equal-length routes with the same endpoint have equal weight.

For a parameter coordinate $\theta^a$, define

```math
\phi_a(v)=\partial_a\log h_\theta(v).
```

Since $h(o)=1$,

```math
\partial_a\log\mathbb P_h(p)=
\phi_a(v_N).
```

The Fisher metric of the complete length-$N$ path law is therefore

```math
G^{(N)}_{ab}=
\mathbb E_h
\left[
\phi_a(X_N)\phi_b(X_N)
\right].
```

But the martingale isometry gives

```math
G^{(N)}_{ab}=
\mathbb E_h
\left[
\sum_{n=0}^{N-1}
\mathsf Q_{X_n}(\phi_a,\phi_b)
\right].
```

The endpoint Fisher information satisfies

```math
\text{endpoint Fisher information}=
\text{accumulated local quadratic variation}.
```

The identity holds without stationarity or cycles.

If the limit exists,

```math
\overline G_{ab}=
\lim_{N\to\infty}
\frac1N G^{(N)}_{ab}
```

is the asymptotic information-rate metric of the regime.

# 8. Diffusive continuum limit

Introduce a graph/profile refinement scale $\delta$, distinct from the profile displacement $\varepsilon$ just taken to zero.

Suppose outgoing edges produce local profile-coordinate increments

```math
\Delta_e x^i=
x^i(r(e))-x^i(v)=
O(\delta),
```

and set the continuum compositional time

```math
\tau=n\delta^2.
```

Define the first and second local moments

```math
b_h^i(x)=
\lim_{\delta\to0}
\frac1{\delta^2}
\sum_eP_h(e\mid x)\Delta_e x^i,
```

Thus the diffusion tensor is

```math
a_h^{ij}(x)=
\lim_{\delta\to0}
\frac1{\delta^2}
\sum_eP_h(e\mid x)
\Delta_e x^i\Delta_e x^j.
```

The tensor $a_h^{ij}$ is the continuum local quadratic variation.

For harmonic profile coordinates,

```math
P_hx^i=x^i,
```

so

```math
b_h^i=0
```

at leading order.

Under the usual vanishing-jump, tightness and martingale-limit conditions, the rescaled profile-coordinate process converges to a continuous local martingale with covariance $a_h$; quadratic variation exactly fixes the Brownian time change.

The limiting generator in harmonic coordinates is

```math
\mathcal L_hf=
\frac12a_h^{ij}(x)
\partial_i\partial_j f.
```

More generally, with nonzero drift,

```math
\mathcal L_hf=
b_h^i\partial_i f
+
\frac12a_h^{ij}\partial_i\partial_jf.
```

The corresponding density equation is

```math
\partial_\tau\rho=
-\partial_i(b_h^i\rho)
+
\frac12
\partial_i\partial_j(a_h^{ij}\rho).
```

# 9. Computing the drift from the profile

Let the continuum limit of the normalized untransformed channel operator be

```math
\mathcal L_0=
b^i\nabla_i
+
\frac12a^{ij}\nabla_i\nabla_j
-c.
```

Suppose the critical profile satisfies

```math
\mathcal L_0h=\kappa h.
```

The continuum Doob transform is

```math
\mathcal L^hf=
h^{-1}\mathcal L_0(hf)-\kappa f.
```

Write again

```math
u=\log h.
```

Using the product rule,

```math
\mathcal L^hf=
\frac12a^{ij}\nabla_i\nabla_jf
+
\left(
b^i+a^{ij}\nabla_j u
\right)\nabla_i f.
```

The profile-induced drift is

```math
b_h^i=
b^i+a^{ij}\nabla_j\log h.
```

The continuum equation is the limit of the discrete edge splitting

```math
P_h(e\mid v)=
\frac{h(r(e))}{\lambda h(v)}.
```

The logarithmic gradient of the positive profile is the additional effective drift.

# 10. The equation of the critical profile regime

Divide the eigenprofile equation

```math
\mathcal L_0h=\kappa h
```

by $h=e^u$. Since

```math
\frac{\nabla_i\nabla_jh}{h}=
\nabla_i\nabla_j u
+
\nabla_i u\nabla_j u,
```

Equivalently,

```math
\kappa=
b^i\nabla_i u
+
\frac12a^{ij}
\left(
\nabla_i\nabla_j u
+
\nabla_i u\nabla_j u
\right)
-c.
```

The stationary logarithmic profile satisfies a viscous Hamilton-Jacobi equation.

Equivalently, the linear form is

```math
\mathcal L_0h=\kappa h.
```

The nonlinear and linear equations are related by the intrinsic exponential transformation

```math
h=e^u.
```

For a time-dependent profile satisfying

```math
\partial_\tau h=\mathcal L_0h,
```

The logarithmic field satisfies

```math
\partial_\tau u=
b^i\nabla_i u
+
\frac12a^{ij}
\left(
\nabla_i\nabla_j u
+
\nabla_i u\nabla_j u
\right)
-c.
```

Local quadratic variation produces the second-order term, while positivity/exponential normalization produces the quadratic gradient term.

# 11. The corresponding effective transport equation

Substituting

```math
b_h^i=b^i+a^{ij}\nabla_j u
```

into the Fokker-Planck equation gives

```math
\partial_\tau\rho=
-\nabla_i
\left[
\left(
b^i+a^{ij}\nabla_j\log h
\right)\rho
\right]
+
\frac12
\nabla_i\nabla_j
\left(
a^{ij}\rho
\right).
```

The two coupled equations are

```math
\begin{aligned}
\kappa
&=
b\cdot\nabla u
+
\frac12a:
\left(
\nabla^2u+\nabla u\otimes\nabla u
\right)
-c,\\[1mm]
\partial_\tau\rho
&=
-\nabla\cdot
\left[
(b+a\nabla u)\rho
\right]
+
\frac12\nabla\nabla:(a\rho).
\end{aligned}
```

The first determines the profile potential.

The second transports the resulting effective state.

## Centered geometric form

If the base drift vanishes and the quadratic-variation tensor is the inverse of a smooth metric,

```math
a^{ij}=g^{ij},
```

it follows that

```math
\kappa=
\frac12
\left(
\Delta_g u
+
|\nabla u|_g^2
\right)-c,
```

and

```math
\partial_\tau\rho=
-\mathrm{div}_g
\left(
\rho\nabla_g u
\right)
+
\frac12\Delta_g\rho.
```

The effective motion is diffusion on the profile manifold with drift generated by the critical Martin/harmonic profile.

# 12. Deterministic equation on the profile manifold

The same local Fisher tensor gives a deterministic continuum equation when one asks for the least-distinguishable slowly varying profile curve.

For a curve $\theta(\tau)$ in profile space, the accumulated infinitesimal KL cost is

```math
\mathcal S[\theta]=
\frac12
\int
G_{ab}(\theta)
\dot\theta^a\dot\theta^b\,d\tau.
```

The stationary curves satisfy

```math
\ddot\theta^a
+
\Gamma^a{}_{bc}(\theta)
\dot\theta^b\dot\theta^c
=0,
```

where

```math
\Gamma^a{}_{bc}=
\frac12G^{ad}
\left(
\partial_bG_{dc}
+\partial_cG_{db}
-\partial_dG_{bc}
\right).
```

The same quadratic variation yields two complementary equations:

```math
\text{fluctuating regime}
\longrightarrow
\text{Fokker-Planck/diffusion equation},
```

and

```math
\text{least-information regime}
\longrightarrow
\text{geodesic equation}.
```
