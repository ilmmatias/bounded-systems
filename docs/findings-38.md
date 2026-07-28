# 1. Where the stable exponent comes from

A stable limit cannot arise from one fixed finite graph by merely renaming its edges. We require either:

* a refinement family $G_\delta$;
* increasingly fine profile coordinates;
* or block increments built from increasingly long finite path segments.

Let $Z_{\delta,x}$ be the unscaled profile displacement associated with one coarse block beginning near profile point $x$, and let

```math
Y_{\delta,x}=\delta Z_{\delta,x}.
```

Assume the block displacement has a regularly varying tail:

```math
\Pr_h\bigl(|Z_{\delta,x}|>r\bigr)
\sim
r^{-\alpha}L_x(r),
\qquad
0<\alpha<2,
```

where $L_x$ is slowly varying.

A displacement of macroscopic order occurs when

```math
|Z_{\delta,x}|\gtrsim\delta^{-1}.
```

Its probability is therefore

```math
a_\delta(x)=
\Pr_h\bigl(
|Z_{\delta,x}|>\delta^{-1}
\bigr)
\sim
\delta^\alpha L_x(\delta^{-1}).
```

Hence the intrinsic stable time scale is

```math
\tau=n,a_\delta
\sim
n\delta^\alpha L(\delta^{-1}).
```

For a pure power law,

```math
\tau=n\delta^\alpha.
```

Thus the dynamical exponent is not chosen independently:

```math
z=\alpha.
```

The Gaussian regime is the boundary case $z=2$. For $0<\alpha<2$, macroscopic motion is dominated by heavy-tailed route blocks rather than finite quadratic variation.

---

# 2. Vague convergence of the channel-increment law

Let

```math
K_{\delta,h}(x,dy)
```

be the derived one-block profile-increment law.

The stable candidate is determined by the vague convergence

```math
\frac1{a_\delta}
K_{\delta,h}(x,dy)
;\xrightarrow[\delta\to0]{v};
\nu_h(x,dy)
```

on

```math
\mathbb R^d\setminus\{0\}.
```

For a stable-like limit, the Lévy kernel has radial-angular decomposition

```math
\nu_h(x,dy)=
\frac{dr}{r^{1+\alpha}}
\Lambda_h(x,d\theta),
\qquad
y=r\theta,
```

up to a normalization absorbed into the finite angular measure $\Lambda_h$.

Equivalently, when the angular measure has a density,

```math
\nu_h(x,dy)=
\frac{q_h(x,\widehat y)}
{|y|^{d+\alpha}},dy.
```

Stable-like operators of this form are standard pure-jump Lévy-type generators; existence and uniqueness of their martingale problems require regularity and nondegeneracy assumptions on the state-dependent angular coefficient.

The parameters already separate naturally:

```math
\alpha=
\text{radial route-tail exponent},
```

while

```math
\Lambda_h(x,d\theta)=
\text{directional profile-jump structure}.
```

So $\alpha$ is one scalar, but the full stable regime also carries an angular spectral measure.

# 3. The general stable-like profile generator

Using the fixed truncation

```math
\chi(y)=y\mathbf1_{\{|y|<1\}},
```

define

```math
\begin{aligned}
\mathcal L_{\alpha,0}f(x)
={}&
b(x)\cdot\nabla f(x)\\
&+
\int_{\mathbb R^d\setminus\{0\}}
\left[
f(x+y)-f(x)-\chi(y)\cdot\nabla f(x)
\right]
\nu_0(x,dy)\\
&-c(x)f(x).
\end{aligned}
```

For $\alpha<1$, the compensation term may be omitted when the integral is absolutely convergent; retaining one fixed truncation convention simply transfers the difference into the drift. The standard stable-like generator has precisely this nonlocal form.

Let the critical positive profile satisfy

```math
\mathcal L_{\alpha,0}h=
\kappa h,
\qquad
h>0.
```

Write

```math
u=\log h.
```

Then the derived Markov generator is the exact Doob transform

```math
\mathcal L_{\alpha}^{h}f=
h^{-1}\mathcal L_{\alpha,0}(hf)-\kappa f.
```

Ground-state and Doob transforms of nonlocal Lévy generators produce state-dependent drift and jump intensities of this kind. 

# 4. Exact transformation of the stable jump kernel

Define

```math
r_h(x,y)=
\frac{h(x+y)}{h(x)}=
e^{u(x+y)-u(x)}.
```

Direct substitution gives

```math
\nu_h(x,dy)=
r_h(x,y)\nu_0(x,dy).
```

The transformed drift is

```math
b_h(x)=
b(x)
+
\int
\chi(y)
\bigl[r_h(x,y)-1\bigr]
\nu_0(x,dy).
```

Therefore

```math
\begin{aligned}
\mathcal L_{\alpha}^{h}f(x)
={}&
b_h(x)\cdot\nabla f(x)\\
&+
\int
\left[
f(x+y)-f(x)-\chi(y)\cdot\nabla f(x)
\right]
\nu_h(x,dy).
\end{aligned}
```

This is the exact stable analogue of the discrete transformation

```math
P_h(e\mid v)=
\frac{h(r(e))}
{\lambda h(v)}.
```

The discrete profile reweights channels by a successor-to-current ratio. The stable continuum profile reweights every displacement by

```math
\frac{h(x+y)}{h(x)}.
```

# 5. Can the $h$-transform change $\alpha$?

The $h$-transform can change $\alpha$.

Suppose the untransformed radial kernel is

```math
\nu_0(dr,d\theta)=
r^{-1-\alpha}dr,\Lambda_0(d\theta).
```

If

```math
\frac{h(x+r\theta)}{h(x)}
\longrightarrow
q_h(x,\theta)
```

as $r\to\infty$, with a finite nonzero limit, then

```math
\alpha_h=\alpha
```

and only the angular measure changes:

```math
\Lambda_h(x,d\theta)=
q_h(x,\theta)\Lambda_0(x,d\theta).
```

More generally, suppose

```math
\frac{h(x+r\theta)}{h(x)}
\sim
r^\gamma q_h(x,\theta).
```

Then

```math
r^{-1-\alpha}r^\gamma=
r^{-1-(\alpha-\gamma)}.
```

So, when the transformed measure remains admissible,

```math
\alpha_h=\alpha-\gamma.
```

Thus the positive profile can do more than bias the directions of anomalous propagation: sufficiently strong asymptotic profile growth can change the stable universality class itself.

The stable exponent is preserved only when the profile is asymptotically neutral at the radial power-law scale.

# 6. The nonlocal critical-profile equation

Divide

```math
\mathcal L_{\alpha,0}h=\kappa h
```

by $h=e^u$. We obtain

```math
\begin{aligned}
\kappa+c(x)
={}&
b(x)\cdot\nabla u(x)\\
&+
\int
\left[
e^{u(x+y)-u(x)}
-1
-\chi(y)\cdot\nabla u(x)
\right]
\nu_0(x,dy).
\end{aligned}
```

This is the stable/nonlocal Hamilton–Jacobi profile equation.

For the stable-like kernel

```math
\nu_0(x,dy)=
\frac{q_0(x,\widehat y)}
{|y|^{d+\alpha}},dy,
```

it becomes

```math
\begin{aligned}
\kappa+c(x)
={}&
b(x)\cdot\nabla u(x)\\
&+
\int_{\mathbb R^d\setminus\{0\}}
\frac{
e^{u(x+y)-u(x)}
-1
-\chi(y)\cdot\nabla u(x)
}{
|y|^{d+\alpha}
}
q_0(x,\widehat y),dy.
\end{aligned}
```

This is the exact profile equation of the stable regime.

It reduces to the quadratic viscous Hamilton–Jacobi equation only when the jump kernel concentrates into vanishing finite-variance increments.

# 7. First variation: stable harmonic tangent fields

Take a smooth family of critical profiles

```math
h_\varepsilon=
h\exp\left(
\varepsilon\phi
+\frac{\varepsilon^2}{2}\chi
+o(\varepsilon^2)
\right)
```

with the same eigenvalue $\kappa$.

Differentiating

```math
h_\varepsilon^{-1}
\mathcal L_{\alpha,0}h_\varepsilon=
\kappa
```

once gives

```math
\mathcal L_\alpha^h\phi=0.
```

So tangent vectors to the fixed-critical-value stable profile manifold are harmonic functions of the transformed stable process.

This exactly parallels the discrete equation

```math
(P_h-I)\phi=0.
```

# 8. Second variation: the nonlocal quadratic form survives

Differentiate again. The Hessian of the exponential jump term is

```math
\int
r_h(x,y)
\bigl[
\phi(x+y)-\phi(x)
\bigr]
\bigl[
\psi(x+y)-\psi(x)
\bigr]
\nu_0(x,dy).
```

Since

```math
r_h\nu_0=\nu_h,
```

define

```math
g_{\alpha,h,x}(\phi,\psi)=
\int
\Delta_y\phi(x),
\Delta_y\psi(x),
\nu_h(x,dy),
```

where

```math
\Delta_y\phi(x)=
\phi(x+y)-\phi(x).
```

The stable carré du champ is

```math
\Gamma_{\alpha,h}(\phi,\psi)=
\frac12g_{\alpha,h}(\phi,\psi).
```

The second-order profile equation is therefore

```math
-\mathcal L_\alpha^h\chi=
g_{\alpha,h}(\phi,\phi)=
2\Gamma_{\alpha,h}(\phi).
```

This is the exact nonlocal replacement for

```math
(I-P_h)\chi=
\mathsf Q_h(\phi).
```

The quadratic-profile structure becomes nonlocal in the stable regime:

```math
\text{local edge variance}
\quad\longrightarrow\quad
\text{integrated squared jump difference}.
```

Although an $\alpha$-stable coordinate process generally has no finite global second moment for $\alpha<2$, the Dirichlet/carré-du-champ form is finite on suitable bounded or sufficiently regular test functions because the small-jump singularity is controlled by the squared difference. Fractional and stable generators are naturally represented by such nonlocal quadratic forms.

# 9. Information geometry of stable jump intensities

Under the profile perturbation,

```math
\nu_{h_\varepsilon}(x,dy)=
e^{u_\varepsilon(x+y)-u_\varepsilon(x)}
\nu_0(x,dy).
```

Its infinitesimal log-intensity score is

```math
\left.
\partial_\varepsilon
\log\nu_{h_\varepsilon}(x,dy)
\right|_{\varepsilon=0}=
\Delta_y\phi(x).
```

Hence the local information-rate Hessian is

```math
\mathcal I_{\alpha,h,x}(\phi,\psi)=
\int
\Delta_y\phi,
\Delta_y\psi,
\nu_h(x,dy).
```

Therefore, whenever the relative-entropy-rate integral is finite,

```math
\mathcal I_{\alpha,h}=
g_{\alpha,h}=
2\Gamma_{\alpha,h}.
```

This is the stable continuation of the identity we found in the Gaussian regime:

```math
\text{profile Fisher tensor}=
\text{jump carré du champ}.
```

# 10. Symmetric anisotropic stable dispersion

Assume first that the stable kernel is translation invariant and symmetric:

```math
\nu_0(dy)=\nu_0(-dy).
```

Then

```math
\mathcal L_{\alpha,0}e^{ik\cdot x}=
-\psi_\alpha(k)e^{ik\cdot x},
```

where

```math
\psi_\alpha(k)=
\int_{\mathbb R^d}
\bigl[
1-\cos(k\cdot y)
\bigr]
\nu_0(dy).
```

For an anisotropic symmetric stable measure,

```math
\psi_{\alpha,\Lambda}(k)=
\int_{S^{d-1}}
|k\cdot\theta|^\alpha
\Lambda(d\theta),
```

with normalization absorbed into $\Lambda$.

This is the correct dispersion relation in the general symmetric stable regime.

It is homogeneous:

```math
\psi_{\alpha,\Lambda}(ck)=
|c|^\alpha
\psi_{\alpha,\Lambda}(k).
```

Therefore the spatial and compositional scales obey

```math
x\sim\tau^{1/\alpha}.
```

# 11. Isotropic stable regime

For rotationally invariant $\Lambda$,

```math
\psi_\alpha(k)=
D_\alpha|k|^\alpha.
```

The generator is

```math
\mathcal L_{\alpha,0}=
-D_\alpha(-\Delta)^{\alpha/2}.
```

The isotropic fractional Laplacian is the generator of the isotropic $\alpha$-stable Lévy process and has Fourier multiplier $|k|^\alpha$.

The profile equation becomes

```math
-D_\alpha
\frac{(-\Delta)^{\alpha/2}h}{h}
-c=
\kappa.
```

In logarithmic form,

```math
\kappa+c=
C_{d,\alpha}D_\alpha
\int
\frac{
e^{u(x+y)-u(x)}
-1
-\chi(y)\cdot\nabla u(x)
}{
|y|^{d+\alpha}
},dy.
```

The transformed density equation is

```math
\partial_\tau\rho=
(\mathcal L_\alpha^h)^\ast\rho.
```

For constant $h$, this reduces to the fractional heat equation

```math
\partial_\tau\rho=
-D_\alpha(-\Delta)^{\alpha/2}\rho.
```

# 12. Ground-state form and the one-particle operator

Assume the untransformed stable kernel is symmetric. Then the $h$-transformed process is naturally represented on

```math
L^2(h^2dx).
```

Define

```math
B_{\alpha,h}=
-\mathcal L_\alpha^h.
```

Its quadratic form is

```math
\begin{aligned}
\mathcal E_{\alpha,h}(f,g)=
\frac12
\int dx\int
&
\bigl[f(x+y)-f(x)\bigr]\\
&\times
\bigl[g(x+y)-g(x)\bigr]\\
&\times
h(x)h(x+y),
\nu_0(dy).
\end{aligned}
```

Subject to the usual domain and integrability conditions,

```math
B_{\alpha,h}\ge0
```

and is the nonlocal one-particle relaxation operator. Ground-state transformation maps a nonlocal Schrödinger operator shifted by its ground-state eigenvalue into the negative of a Markov generator on the weighted $L^2$ space.

This is the operator whose continuum existence and spectral data can be investigated later.

# 13. Stable fluctuation lift

Let

```math
\mathfrak k_{\alpha,h}
```

be the one-particle fluctuation space on which $B_{\alpha,h}$ acts.

In the degree-preserving linearized regime, pass to

```math
\Gamma_s(\mathfrak k_{\alpha,h}).
```

The dissipative fluctuation generator is

```math
H_{\alpha,\mathrm{diss}}=
d\Gamma(B_{\alpha,h}).
```

The path-growth gauge contributes

```math
H_{\mathrm{gauge}}=
\beta N,
\qquad
\beta=\log\lambda=-2\log R.
```

Because $d\Gamma(B_{\alpha,h})$ preserves particle number,

```math
[d\Gamma(B_{\alpha,h}),N]=0.
```

Therefore the stable critical fluctuation equation closes as

```math
\partial_\tau\Psi=
-\left[
d\Gamma(B_{\alpha,h})
+i\beta N
\right]\Psi.
```

Equivalently,

```math
\Psi_\tau=
e^{-\tau d\Gamma(B_{\alpha,h})}
e^{-i\beta\tau N}
\Psi_0.
```

This is the stable counterpart of the Gaussian quadratic equation.

# 14. Explicit homogeneous mode equation

For the homogeneous isotropic case,

```math
B_\alpha=
D_\alpha(-\Delta)^{\alpha/2}.
```

On the one-particle Fourier side,

```math
\widehat{B_\alpha f}(k)=
D_\alpha|k|^\alpha\widehat f(k).
```

On the $n$-particle sector,

```math
d\Gamma(B_\alpha)
```

acts by

```math
D_\alpha
\sum_{j=1}^n|k_j|^\alpha.
```

Meanwhile,

```math
N=n.
```

Hence the exact mode evolution is

```math
\widehat\Psi_n(
k_1,\ldots,k_n;\tau
)
=
\exp
\left[
-\tau D_\alpha
\sum_{j=1}^n|k_j|^\alpha
-i\beta n\tau
\right]
\widehat\Psi_n(
k_1,\ldots,k_n;0
).
```

Thus the complex spectral rate is

```math
\Omega_{\alpha,n}
(k_1,\ldots,k_n)=
D_\alpha\sum_{j=1}^n|k_j|^\alpha
+i\beta n.
```

For one excitation,

```math
\Omega_\alpha(k)=
D_\alpha|k|^\alpha+i\log\lambda.
```

In position space, the one-particle equation is

```math
\partial_\tau\psi=
-D_\alpha(-\Delta)^{\alpha/2}\psi
-i(\log\lambda)\psi.
```

This is the explicit equation of the homogeneous isotropic stable regime.

# 15. Stable diffusion and fractional unitary evolution

Because

```math
B_{\alpha,h}\ge0
```

in the symmetric ground-state case, the holomorphic family

```math
e^{-zB_{\alpha,h}},
\qquad
\Re z\ge0,
```

contains two boundary evolutions.

For real $z=\tau>0$,

```math
\partial_\tau\psi=
-B_{\alpha,h}\psi,
```

the stable diffusion.

For imaginary $z=it$,

```math
i\partial_t\psi=
B_{\alpha,h}\psi,
```

the associated fractional unitary evolution.

In the homogeneous isotropic case,

```math
i\partial_t\psi=
D_\alpha(-\Delta)^{\alpha/2}\psi.
```

Thus the fractional diffusion and fractional Schrödinger-type evolutions are analytic continuations of the same stable operator. The original path-length gauge supplies the additional commuting phase $\beta N$.

# 16. $\alpha$ and $\beta$ are different invariants

We now have two exponents:

```math
\alpha=
\text{profile-displacement tail/scaling exponent},
```

and

```math
\beta=\log\lambda=
\text{route-multiplicity growth/gauge parameter}.
```

Nothing derived so far forces a universal relation

```math
\alpha=f(\beta).
```

They encode different structural sectors:

* $\alpha$ comes from the radial tail of coarse profile increments;
* $\beta$ comes from critical route growth.

A relation between them would be additional structure to discover in a particular family, not something that should be inserted universally.

The homogeneous stable mode exposes both independently:

```math
\Omega_\alpha(k)=
D_\alpha|k|^\alpha+i\beta.
```

Its real part is anomalous profile relaxation.

Its imaginary part is compositional gauge phase.

# 17. The exact later convergence tests

To prove that a particular graph/profile family actually converges to this regime, the required checks are now concrete.

### Radial regular variation

Show

```math
\Pr_h(|Z_\delta|>r)
\sim
r^{-\alpha}L(r).
```

### Angular convergence

Show the directions of large profile displacements converge to

```math
\Lambda_0(x,d\theta).
```

### $h$-tilt stability

Determine the asymptotics of

```math
\frac{h(x+r\theta)}{h(x)}.
```

This decides whether $\alpha$ survives or changes.

### Anti-clustering

Show that one large route block does not force an uncontrolled cluster of equally large blocks, unless the cluster is explicitly incorporated into the limiting Lévy measure.

### Small-jump centering

For $\alpha>1$, control the truncated first moment needed to determine the drift.

### Generator convergence

Show

```math
\mathcal L_{\delta}^h f
\longrightarrow
\mathcal L_\alpha^h f
```

on a core of test functions.

### Martingale-problem uniqueness

Prove that the candidate stable-like operator determines a unique limiting process. Stable-like martingale problems are known to be well posed under suitable conditions, but those conditions must be verified for the operator produced by the graph family.
