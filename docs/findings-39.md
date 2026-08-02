# 1. Coarse transition lengths

Choose a profile-resolution map or partition

```math
\Pi_\delta:\Omega_G\longrightarrow \mathcal X_\delta.
```

Along the resolved derived history $X_n$, set the initial coarse-change
epoch to

```math
T_0=0,
```

and define subsequent retained-change times recursively by

```math
T_{m+1}=
\inf\left\lbrace n>T_m: \Pi_\delta(X_n) \neq \Pi_\delta(X_{T_m}) \right\rbrace.
```

The intrinsic block lengths are

```math
W_m=T_{m+1}-T_m.
```

Each $W_m$ counts primitive edge events before the next observable profile
change.

The accumulated primitive length after $m$ coarse transitions is

```math
S_m=W_1+\cdots+W_m.
```

The number of completed coarse transitions by primitive depth $n$ is

```math
N(n)=\max{m:S_m\le n}.
```

Nothing temporal was added. Both $S_m$ and $N(n)$ are built from compositional
length.

# 2. Finite-mean clock: no anomaly

If

```math
\mathbb E[W]<\infty,
```

then typically

```math
S_m\sim m\mathbb E[W],
```

and therefore

```math
N(n)\sim \frac{n}{\mathbb E[W]}.
```

The two clocks differ only by a constant conversion factor.

If the operational profile process has generator $\mathcal L^h$, the coarse
process has an ordinary first-order evolution equation with a rescaled
generator.

```math
\mathbb E[W]<\infty
\Longrightarrow
\text{ordinary effective time}.
```

The anomalous regime begins when the mean block length diverges.

# 3. Heavy-tailed intrinsic clock

Assume that

```math
\Pr(W>n)
\sim
c,n^{-\gamma}L(n),
\qquad
0<\gamma<1,
```

where $L$ is slowly varying.

It follows that

```math
\mathbb E[W]=\infty.
```

The Laplace or generating-function behavior near its critical point is

```math
1-\mathbb E[e^{-qW}]
\sim
c,\Gamma(1-\gamma)
q^\gamma L(q^{-1})
```

as $q\downarrow0$.

Correspondingly normalized, the partial-sum clock converges to a $\gamma$-stable
subordinator $D_s$, and the rescaled renewal count to its inverse

```math
E_\tau=
\inf{s>0:D_s>\tau}.
```

Inverse stable subordinators are the standard scaling limits behind fractional
Poisson and time-fractional Cauchy problems.

The number of effective profile changes grows sublinearly:

```math
N(n)\asymp n^\gamma.
```

Long stretches of primitive compositional evolution can be invisible at the
chosen profile resolution.

# 4. Operational and observed profile processes

Let $Y_s$ be the profile process indexed by coarse-transition count $s$. Its
semigroup is

```math
T_s=e^{s\mathcal L^h}=
e^{-sB_h},
```

where

```math
B_h=-\mathcal L^h.
```

The process seen in primitive compositional time is

```math
Z_\tau=Y_{E_\tau}.
```

The profile coordinate alone is non-Markovian because the inverse clock
$E_\tau$ does not have independent increments.

Its evolution family is

```math
S_\gamma(\tau)f=
\int_0^\infty
T_s f\,
\ell_\gamma(\tau,s)\,ds,
```

where $\ell_\gamma(\tau,s)$ is the density of the inverse stable clock.

The construction is inverse subordination, not ordinary semigroup
subordination, and yields fractional Cauchy problems.

# 5. Laplace resolvent

Take the Laplace transform in primitive-scale time:

```math
\widetilde u(q)=
\int_0^\infty e^{-q\tau}u(\tau)\,d\tau.
```

For the inverse $\gamma$-stable clock,

```math
\widetilde u(q)=
q^{\gamma-1}
\left(
q^\gamma+B_h
\right)^{-1}
u_0.
```

Rearranging,

```math
q^\gamma\widetilde u(q)-
q^{\gamma-1}u_0=
-B_h\widetilde u(q).
```

The left side is the Laplace transform of the Caputo derivative. Therefore

```math
{}^{C}D_\tau^\gamma u(\tau)=
-B_hu(\tau),
\qquad
u(0)=u_0.
```

Equivalently, for observables,

```math
{}^{C}D_\tau^\gamma u=
\mathcal L^hu.
```

And for densities,

```math
{}^{C}D_\tau^\gamma\rho=
(\mathcal L^h)^\ast\rho.
```

The inverse-stable time change produces a solution of the Caputo equation. The
two descriptions agree as representations of the limiting evolution when that
equation has a unique solution for the given initial datum.

# 6. Memory-integral form

The fractional equation can also be written without fractional-derivative
notation:

```math
u(\tau)=
u_0
+
\frac1{\Gamma(\gamma)}
\int_0^\tau
(\tau-s)^{\gamma-1}
\mathcal L^hu(s)\,ds.
```

The current profile change depends on the complete earlier profile evolution.

The memory kernel is

```math
M_\gamma(\tau)=
\frac{\tau^{\gamma-1}}{\Gamma(\gamma)}.
```

The memory kernel results from:

1. evolving through primitive channels;
2. grouping them into profile-constant blocks;
3. forgetting the age inside the current block.

General semi-Markov processes satisfy Volterra-type evolution equations; the
fractional equation arises for heavy-tailed renewal laws.

# 7. Markovianity is restored by adding the hidden age

Define the age of the current coarse block:

```math
A_\tau=
\tau-S_{N(\tau)}.
```

The profile coordinate $Z_\tau$ alone is generally non-Markovian.

But the enlarged state

```math
(Z_\tau,A_\tau)
```

is semi-Markov and often admits a Markov representation on the extended
profile-age space.

So the temporal memory has a precise source:

```math
\text{memory}=
\text{discarded position inside an unresolved route block}.
```

The result matches the route-collapse picture: resolved histories evolve
locally, while profile compression creates an effective memory kernel.

# 8. General intrinsic clock

The stable clock is one case of a general subordinator with Laplace exponent

```math
\Phi(q).
```

Define the generalized time operator by

```math
\mathcal L_\tau
\left[
\mathfrak D_\tau^\Phi u
\right](q)=
\Phi(q)\widetilde u(q)-
\frac{\Phi(q)}q u_0.
```

The general anomalous-clock equation is

```math
\mathfrak D_\tau^\Phi u=
\mathcal L^hu.
```

Its resolvent is

```math
\widetilde u(q)=
\frac{\Phi(q)}q
\left(
\Phi(q)-\mathcal L^h
\right)^{-1}
u_0.
```

Equivalently,

```math
u(\tau)=
u_0
+
\int_0^\tau
M_\Phi(\tau-s)
\mathcal L^hu(s)\,ds,
```

where

```math
\widetilde M_\Phi(q)=\frac1{\Phi(q)}.
```

For the stable clock,

```math
\Phi(q)=q^\gamma,
```

which gives

```math
M_\Phi(\tau)=
\frac{\tau^{\gamma-1}}{\Gamma(\gamma)}.
```

Mixtures of stable subordinators produce distributed-order fractional
equations, while adding exponential truncation produces tempered memory.

# 9. Spectral relaxation

Suppose that

```math
B_h\varphi_j=
\omega_j\varphi_j,
\qquad
\omega_j\ge0.
```

The scalar amplitude $a_j(\tau)$ obeys

```math
{}^CD_\tau^\gamma a_j=
-\omega_ja_j.
```

Equivalently,

```math
a_j(\tau)=
E_\gamma(-\omega_j\tau^\gamma)
a_j(0),
```

where

```math
E_\gamma(z)=
\sum_{m=0}^\infty
\frac{z^m}{\Gamma(1+\gamma m)}
```

is the Mittag-Leffler function.

For $0<\gamma<1$ and $\omega_j>0$,

```math
E_\gamma(-\omega_j\tau^\gamma)
\sim
\frac1{
\omega_j\Gamma(1-\gamma)
}
\tau^{-\gamma}.
```

Exponential relaxation becomes algebraic:

```math
e^{-\omega_j\tau}
\quad\longrightarrow\quad
E_\gamma(-\omega_j\tau^\gamma)
\sim\tau^{-\gamma}.
```

A positive operational spectral gap no longer gives exponential decay in the
compressed primitive clock.

# 10. Combined space-time anomalous regime

Now combine the $\alpha$-stable spatial operator with the $\gamma$-stable
clock:

```math
{}^CD_\tau^\gamma\rho=
(\mathcal L_{\alpha}^h)^\ast\rho.
```

For the homogeneous isotropic untransformed case,

```math
\mathcal L_\alpha=
-D_\alpha(-\Delta)^{\alpha/2}.
```

It follows that

```math
{}^CD_\tau^\gamma\rho=
-D_\alpha(-\Delta)^{\alpha/2}\rho.
```

On the Fourier side,

```math
{}^CD_\tau^\gamma
\widehat\rho(k,\tau)=
-D_\alpha|k|^\alpha
\widehat\rho(k,\tau).
```

This gives

```math
\widehat\rho(k,\tau)=
E_\gamma
\left(
-D_\alpha|k|^\alpha\tau^\gamma
\right)
\widehat\rho(k,0).
```

The scale-invariant combination is

```math
|k|^\alpha\tau^\gamma.
```

The characteristic profile displacement scales as

```math
|x|\sim\tau^{\gamma/\alpha}.
```

Equivalently,

```math
\tau\sim |x|^{\alpha/\gamma}.
```

The combined dynamical exponent is

```math
z=\frac{\alpha}{\gamma}.
```

For $\alpha=2$,

```math
|x|\sim\tau^{\gamma/2},
```

and, when a second moment exists,

```math
\mathbb E|X_\tau|^2\sim\tau^\gamma.
```

# 11. The gauge-clock issue

There are two mathematically distinct ways the gauge phase can couple to the
anomalous clock.

## Coarse-event gauge

Suppose gauge degree advances once per coarse profile transition.

Then the operational generator is

```math
\mathbb A_h=
\mathbb H_h+i\beta N,
\qquad
\beta=\log\lambda.
```

The entire complex evolution is inverse-time-changed:

```math
{}^CD_\tau^\gamma\Psi=
-\left(
\mathbb H_h+i\beta N
\right)\Psi.
```

For a simultaneous mode

```math
\mathbb H_h\Psi_{\omega,n}=
\omega\Psi_{\omega,n},
\qquad
N\Psi_{\omega,n}=
n\Psi_{\omega,n},
```

the solution is

```math
\Psi_{\omega,n}(\tau)=
E_\gamma
\left[
-(\omega+i\beta n)\tau^\gamma
\right]
\Psi_{\omega,n}(0).
```

Here random coarse-event counts affect both damping and phase.

## Primitive-channel gauge

But the gauge originally derived from the path algebra was

```math
\alpha_t(L_p)=
e^{it|p|}L_p.
```

It counts primitive edge length, not coarse profile transitions.

If $W_m$ counts primitive edges hidden within one coarse event, gauge phase
accumulates throughout the block while the coarse profile remains unchanged.

Therefore the original gauge is more faithfully represented by

```math
\Psi(\tau)=
e^{-i\beta\tau N}
S_\gamma^{\mathbb H}(\tau)\Psi_0.
```

When

```math
[\mathbb H_h,N]=0,
```

this becomes modewise

```math
\Psi_{\omega,n}(\tau)=
e^{-i\beta n\tau}
E_\gamma(-\omega\tau^\gamma)
\Psi_{\omega,n}(0).
```

The phase remains exponential in primitive compositional depth, while
relaxation becomes fractional.

The distinction determines the appropriate clock equation.

# 12. Gauge-covariant fractional derivative

Set the gauge generator to

```math
C=i\beta N.
```

Introduce the gauge-covariant Caputo operator

```math
{}^CD_{\tau,C}^{\gamma}\Psi=
e^{-C\tau}
{}^CD_\tau^\gamma
\left(
e^{C\tau}\Psi
\right).
```

Then the primitive-channel gauge equation is

```math
{}^CD_{\tau,i\beta N}^{\gamma}\Psi=
-\mathbb H_h\Psi.
```

Its Laplace transform is

```math
\left[
(q+i\beta N)^\gamma
+
\mathbb H_h
\right]
\widetilde\Psi(q)=
(q+i\beta N)^{\gamma-1}\Psi_0.
```

The fractional power uses the principal branch. Since $q>0$, the spectrum of
$q+i\beta N$ lies in the open right half-plane, making this functional
calculus well defined on the natural domain.

The operator has the form of a fractional substantial derivative, with the
scalar shift replaced by the gauge generator $i\beta N$.

# 13. Stable spatial mode with intrinsic gauge clock

Take

```math
\mathbb H_{\alpha,h}=
d\Gamma(B_{\alpha,h}).
```

The full primitive-gauge anomalous-clock equation is

```math
{}^CD_{\tau,i(\log\lambda)N}^{\gamma}
\Psi=
-d\Gamma(B_{\alpha,h})\Psi.
```

In the homogeneous isotropic case,

```math
B_\alpha=
D_\alpha(-\Delta)^{\alpha/2}.
```

On the $n$-particle Fourier sector,

```math
\omega_{\alpha,n}(\mathbf k)=
D_\alpha
\sum_{j=1}^n|k_j|^\alpha.
```

Combining the spatial and temporal factors gives

```math
\begin{aligned}
\widehat\Psi_n(\mathbf k,\tau)
={}&
e^{-i(\log\lambda)n\tau}\\
&\times
E_\gamma
\left[
-D_\alpha
\left(
\sum_{j=1}^n|k_j|^\alpha
\right)
\tau^\gamma
\right]
\widehat\Psi_n(\mathbf k,0).
\end{aligned}
```

# 14. Canonical form of the primitive-gauge equation

The coarse-event equation

```math
{}^CD^\gamma\Psi=
-(\mathbb H+i\beta N)\Psi
```

would apply after redefining the gauge so that one gauge unit corresponds to
one coarse profile transition.

But the original gauge was already fixed by

```math
|p|=
\text{number of primitive channels}.
```

When random numbers of primitive edges per coarse transition cause the clock
anomaly, the canonical equation is

```math
{}^CD_{\tau,i\beta N}^{\gamma}\Psi=
-\mathbb H_h\Psi.
```

The gauge is not subordinated because it measures the microscopic count from
which the anomalous coarse clock was constructed.

The two gauges also differ operationally:

* a neutral mode $\omega=0$ retains the pure gauge oscillation
  $e^{-i\beta n\tau}$;
* a stable mode $\omega>0$ has algebraic relaxation multiplied by that phase.

Under coarse-event subordination, even a neutral gauge mode would undergo
renewal-induced dephasing through

```math
E_\gamma(-i\beta n\tau^\gamma).
```

The original path-length construction selects the first behavior.

# 15. When scalar fractional time is insufficient

The Caputo equation requires more than a heavy-tailed $W$.

It also requires the clock to decouple sufficiently from the profile
displacement.

Let $J_m$ be the coarse profile jump and $W_m$ its hidden primitive length.

If asymptotically

```math
J_m
\quad\text{and}\quad
W_m
```

separate, the limiting clock can be represented by a scalar inverse
subordinator independent of the operational profile process.

If long blocks preferentially produce particular directions or jump sizes,
then the joint kernel

```math
Q_h(x,dy,dw)
```

must be retained.

The resulting equation has an operator-valued memory kernel and is generally
semi-Markov, satisfying an abstract Volterra equation; ordinary fractional
derivatives are only special cases.

Similarly:

* a state-dependent tail exponent $\gamma=\gamma(x)$ suggests variable-order
  memory;
* mixtures of tail exponents suggest distributed-order equations;
* directional waiting laws couple temporal and spatial symbols.

```math
\Pr(W>n)\sim n^{-\gamma}
```

identifies the fractional order only after the necessary decoupling or
joint-limit condition is checked.

# 16. Literature relation

The convergence of the rescaled clock to a $\gamma$-stable subordinator and of
the rescaled renewal count to its inverse, used in sections 3 to 5 to produce
the Caputo equation, is the limit theorem of M. M. Meerschaert and
H.-P. Scheffler, *Limit theorems for continuous-time random walks with infinite
mean waiting times*, Journal of Applied Probability 41 (2004), 623-638. The
waiting times there are independent, identically distributed, and independent of
the jumps. Section 3 assumes only the tail law of the single block length $W$,
and section 15 isolates the coupling between $J_m$ and $W_m$ that the
independence hypothesis excludes, so that hypothesis is imposed rather than
derived from the route structure.

The general clock of section 8, with Bernstein exponent $\Phi$, the prefactor
$\Phi(q)/q$ in the resolvent, and the representation of the time-changed family
as an inverse subordination rather than a semigroup subordination noted in
section 4, follows B. Toaldo, *Convolution-type derivatives, hitting-times of
subordinators and time-changed $C_0$-semigroups*, Potential Analysis 42 (2015),
115-140, arXiv:1308.1327, where the time-changed family is shown not to be a
semigroup, and A. N. Kochubei, *General fractional calculus, evolution
equations, and renewal processes*, Integral Equations and Operator Theory 71
(2011), 583-600, arXiv:1105.1239, whose kernels are complete Bernstein
functions. Both are stated for a scalar Laplace variable $q$. Section 12
replaces $q$ by the operator $q+i\beta N$ inside $\Phi$ and inside the
resolvent, which is not covered by either statement.

The enlarged state $(Z_\tau,A_\tau)$ of section 7, and the joint kernel
$Q_h(x,dy,dw)$ retained in section 15 when block length and displacement do not
decouple, correspond to M. M. Meerschaert and P. Straka, *Semi-Markov approach
to continuous time random walk limit processes*, Annals of Probability 42
(2014), 1699-1723, arXiv:1206.1960, where jumps and waiting times may be
coupled and may vary with space and time, and where the Markov property is
restored by augmenting the state with the age of the current block.
