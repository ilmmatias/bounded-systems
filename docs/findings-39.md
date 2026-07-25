# 1. Coarse transition lengths

Choose a profile-resolution map or partition

[
\Pi_\delta:\Omega_G\longrightarrow \mathcal X_\delta.
]

Along the resolved derived history (X_n), define successive coarse-change epochs

[
T_0=0,
]

[
T_{m+1}
=======

\inf\left{
n>T_m:
\Pi_\delta(X_n)
\neq
\Pi_\delta(X_{T_m})
\right}.
]

The intrinsic block lengths are

[
\boxed{
W_m=T_{m+1}-T_m.
}
]

Each (W_m) is the number of primitive edge events that occur before the observable profile changes again.

The accumulated primitive length after (m) coarse transitions is

[
S_m=W_1+\cdots+W_m.
]

The number of completed coarse transitions by primitive depth (n) is

[
\boxed{
N(n)=\max{m:S_m\le n}.
}
]

Nothing temporal was added. Both (S_m) and (N(n)) are built from compositional length.

---

# 2. Finite-mean clock: no anomaly

If

[
\mathbb E[W]<\infty,
]

then typically

[
S_m\sim m\mathbb E[W],
]

and therefore

[
N(n)\sim \frac{n}{\mathbb E[W]}.
]

The two clocks differ only by a constant conversion factor.

If the operational profile process has generator (\mathcal L^h), then the coarse process still has an ordinary first-order evolution equation, with a rescaled generator.

Thus:

[
\boxed{
\mathbb E[W]<\infty
\Longrightarrow
\text{ordinary effective time}.
}
]

The anomalous regime begins when the mean block length diverges.

---

# 3. Heavy-tailed intrinsic clock

Assume

[
\boxed{
\Pr(W>n)
\sim
c,n^{-\gamma}L(n),
\qquad
0<\gamma<1,
}
]

where (L) is slowly varying.

Then

[
\mathbb E[W]=\infty.
]

The Laplace or generating-function behavior near its critical point is

[
\boxed{
1-\mathbb E[e^{-qW}]
\sim
c,\Gamma(1-\gamma)
q^\gamma L(q^{-1})
}
]

as (q\downarrow0).

After the corresponding normalization, the partial-sum clock converges to a (\gamma)-stable subordinator (D_s), while the rescaled renewal count converges to its inverse

[
\boxed{
E_\tau
======

\inf{s>0:D_s>\tau}.
}
]

Inverse stable subordinators are the standard scaling limits behind fractional Poisson and time-fractional Cauchy problems.

The number of effective profile changes grows sublinearly:

[
\boxed{
N(n)\asymp n^\gamma.
}
]

So long stretches of primitive compositional evolution can be invisible at the chosen profile resolution.

---

# 4. Operational and observed profile processes

Let

[
Y_s
]

be the profile process indexed by coarse-transition count (s). Its semigroup is

[
T_s=e^{s\mathcal L^h}
=====================

e^{-sB_h},
]

where

[
B_h=-\mathcal L^h.
]

The process seen in primitive compositional time is

[
\boxed{
Z_\tau=Y_{E_\tau}.
}
]

This is not Markovian on the profile coordinate alone, because the inverse clock (E_\tau) does not have independent increments.

Its evolution family is

[
\boxed{
S_\gamma(\tau)f
===============

\int_0^\infty
T_sf,
\ell_\gamma(\tau,s),ds,
}
]

where (\ell_\gamma(\tau,s)) is the density of the inverse stable clock.

This is inverse subordination, not ordinary semigroup subordination. The resulting families solve fractional Cauchy problems.

---

# 5. Laplace resolvent

Take the Laplace transform in primitive-scale time:

[
\widetilde u(q)
===============

\int_0^\infty e^{-q\tau}u(\tau),d\tau.
]

For the inverse (\gamma)-stable clock,

[
\boxed{
\widetilde u(q)
===============

q^{\gamma-1}
\left(
q^\gamma+B_h
\right)^{-1}
u_0.
}
]

Rearranging,

[
q^\gamma\widetilde u(q)
-----------------------

# q^{\gamma-1}u_0

-B_h\widetilde u(q).
]

The left side is the Laplace transform of the Caputo derivative. Therefore

[
\boxed{
{}^{C}D_\tau^\gamma u(\tau)
===========================

-B_hu(\tau),
\qquad
u(0)=u_0.
}
]

Equivalently, for observables,

[
\boxed{
{}^{C}D_\tau^\gamma u
=====================

\mathcal L^hu.
}
]

And for densities,

[
\boxed{
{}^{C}D_\tau^\gamma\rho
=======================

(\mathcal L^h)^\ast\rho.
}
]

The inverse-stable time change and the Caputo equation are two representations of the same limiting evolution.

---

# 6. Memory-integral form

The fractional equation can also be written without fractional-derivative notation:

[
\boxed{
u(\tau)
=======

u_0
+
\frac1{\Gamma(\gamma)}
\int_0^\tau
(\tau-s)^{\gamma-1}
\mathcal L^hu(s),ds.
}
]

Thus the current profile change depends on the complete earlier profile evolution.

The memory kernel is

[
\boxed{
M_\gamma(\tau)
==============

\frac{\tau^{\gamma-1}}{\Gamma(\gamma)}.
}
]

This is not a second dynamical law. It is what remains after:

1. evolving through primitive channels;
2. grouping them into profile-constant blocks;
3. forgetting the age inside the current block.

General semi-Markov processes obey Volterra-type evolution equations, with the fractional equation appearing for heavy-tailed renewal laws.

---

# 7. Markovianity is restored by adding the hidden age

Define the age of the current coarse block:

[
\boxed{
A_\tau
======

\tau-S_{N(\tau)}.
}
]

The profile coordinate (Z_\tau) alone is generally non-Markovian.

But the enlarged state

[
\boxed{
(Z_\tau,A_\tau)
}
]

is semi-Markov and can often be represented as a Markov process on the extended profile-age space.

So the temporal memory has a precise source:

[
\boxed{
\text{memory}
=============

\text{discarded position inside an unresolved route block}.
}
]

This is completely aligned with the earlier route-collapse results. A resolved history retains enough information for local evolution; compression to the current profile discards information and creates an effective memory kernel.

---

# 8. General intrinsic clock

The stable clock is one case of a general subordinator with Laplace exponent

[
\Phi(q).
]

Define the generalized time operator by

[
\boxed{
\mathcal L_\tau
\left[
\mathfrak D_\tau^\Phi u
\right](q)
==========

## \Phi(q)\widetilde u(q)

\frac{\Phi(q)}q u_0.
}
]

The general anomalous-clock equation is

[
\boxed{
\mathfrak D_\tau^\Phi u
=======================

\mathcal L^hu.
}
]

Its resolvent is

[
\boxed{
\widetilde u(q)
===============

\frac{\Phi(q)}q
\left(
\Phi(q)-\mathcal L^h
\right)^{-1}
u_0.
}
]

Equivalently,

[
\boxed{
u(\tau)
=======

u_0
+
\int_0^\tau
M_\Phi(\tau-s)
\mathcal L^hu(s),ds,
}
]

where

[
\boxed{
\widetilde M_\Phi(q)=\frac1{\Phi(q)}.
}
]

For the stable clock,

[
\Phi(q)=q^\gamma,
]

which gives

[
M_\Phi(\tau)
============

\frac{\tau^{\gamma-1}}{\Gamma(\gamma)}.
]

Mixtures of stable subordinators produce distributed-order fractional equations, while adding exponential truncation produces tempered memory.

---

# 9. Spectral relaxation

Suppose

[
B_h\varphi_j
============

\omega_j\varphi_j,
\qquad
\omega_j\ge0.
]

The scalar amplitude (a_j(\tau)) obeys

[
{}^CD_\tau^\gamma a_j
=====================

-\omega_ja_j.
]

Hence

[
\boxed{
a_j(\tau)
=========

E_\gamma(-\omega_j\tau^\gamma)
a_j(0),
}
]

where

[
E_\gamma(z)
===========

\sum_{m=0}^\infty
\frac{z^m}{\Gamma(1+\gamma m)}
]

is the Mittag–Leffler function.

For (0<\gamma<1) and (\omega_j>0),

[
\boxed{
E_\gamma(-\omega_j\tau^\gamma)
\sim
\frac1{
\omega_j\Gamma(1-\gamma)
}
\tau^{-\gamma}.
}
]

Thus exponential relaxation becomes algebraic:

[
\boxed{
e^{-\omega_j\tau}
\quad\longrightarrow\quad
E_\gamma(-\omega_j\tau^\gamma)
\sim\tau^{-\gamma}.
}
]

A positive operational spectral gap no longer gives exponential decay in the compressed primitive clock.

---

# 10. Combined space–time anomalous regime

Now combine the (\alpha)-stable spatial operator with the (\gamma)-stable clock:

[
\boxed{
{}^CD_\tau^\gamma\rho
=====================

(\mathcal L_{\alpha}^h)^\ast\rho.
}
]

For the homogeneous isotropic untransformed case,

[
\mathcal L_\alpha
=================

-D_\alpha(-\Delta)^{\alpha/2}.
]

Then

[
\boxed{
{}^CD_\tau^\gamma\rho
=====================

-D_\alpha(-\Delta)^{\alpha/2}\rho.
}
]

On the Fourier side,

[
\boxed{
{}^CD_\tau^\gamma
\widehat\rho(k,\tau)
====================

-D_\alpha|k|^\alpha
\widehat\rho(k,\tau).
}
]

Therefore

[
\boxed{
\widehat\rho(k,\tau)
====================

E_\gamma
\left(
-D_\alpha|k|^\alpha\tau^\gamma
\right)
\widehat\rho(k,0).
}
]

The scale-invariant combination is

[
|k|^\alpha\tau^\gamma.
]

Hence the characteristic profile displacement scales as

[
\boxed{
|x|\sim\tau^{\gamma/\alpha}.
}
]

Equivalently,

[
\boxed{
\tau\sim |x|^{\alpha/\gamma}.
}
]

So the combined dynamical exponent is

[
\boxed{
z=\frac{\alpha}{\gamma}.
}
]

For (\alpha=2),

[
|x|\sim\tau^{\gamma/2},
]

and, when a second moment exists,

[
\mathbb E|X_\tau|^2\sim\tau^\gamma.
]

---

# 11. The gauge-clock issue

There are two mathematically distinct ways the gauge phase can couple to the anomalous clock.

They must not be conflated.

## Coarse-event gauge

Suppose gauge degree advances once per **coarse profile transition**.

Then the operational generator is

[
\mathbb A_h
===========

\mathbb H_h+i\beta N,
\qquad
\beta=\log\lambda.
]

The entire complex evolution is inverse-time-changed:

[
\boxed{
{}^CD_\tau^\gamma\Psi
=====================

*

\left(
\mathbb H_h+i\beta N
\right)\Psi.
}
]

For a simultaneous mode

[
\mathbb H_h\Psi_{\omega,n}
==========================

\omega\Psi_{\omega,n},
\qquad
N\Psi_{\omega,n}
================

n\Psi_{\omega,n},
]

the solution is

[
\boxed{
\Psi_{\omega,n}(\tau)
=====================

E_\gamma
\left[
-(\omega+i\beta n)\tau^\gamma
\right]
\Psi_{\omega,n}(0).
}
]

Here random coarse-event counts affect both damping and phase.

---

## Primitive-channel gauge

But the gauge originally derived from the path algebra was

[
\alpha_t(L_p)
=============

e^{it|p|}L_p.
]

It counts **primitive edge length**, not coarse profile transitions.

If (W_m) counts primitive edges hidden inside one coarse event, then gauge phase continues to accumulate through the entire block, even while the coarse profile remains unchanged.

Therefore the original gauge is more faithfully represented by

[
\boxed{
\Psi(\tau)
==========

e^{-i\beta\tau N}
S_\gamma^{\mathbb H}(\tau)\Psi_0.
}
]

When

[
[\mathbb H_h,N]=0,
]

this becomes modewise

[
\boxed{
\Psi_{\omega,n}(\tau)
=====================

e^{-i\beta n\tau}
E_\gamma(-\omega\tau^\gamma)
\Psi_{\omega,n}(0).
}
]

The phase remains exponential in primitive compositional depth, while relaxation becomes fractional.

This distinction is decisive.

---

# 12. Gauge-covariant fractional derivative

Define

[
C=i\beta N.
]

Introduce the gauge-covariant Caputo operator

[
\boxed{
{}^CD_{\tau,C}^{\gamma}\Psi
===========================

e^{-C\tau}
{}^CD_\tau^\gamma
\left(
e^{C\tau}\Psi
\right).
}
]

Then the primitive-channel gauge equation is

[
\boxed{
{}^CD_{\tau,i\beta N}^{\gamma}\Psi
==================================

-\mathbb H_h\Psi.
}
]

Its Laplace transform is

[
\boxed{
\left[
(q+i\beta N)^\gamma
+
\mathbb H_h
\right]
\widetilde\Psi(q)
=================

(q+i\beta N)^{\gamma-1}\Psi_0.
}
]

Here the fractional power uses the principal branch. Since (q>0), the spectrum of (q+i\beta N) lies in the open right half-plane, so this functional calculus is well defined on the natural domain.

This is the correct fractional substantial derivative associated with the original path-length gauge.

---

# 13. Stable spatial mode with intrinsic gauge clock

Take

[
\mathbb H_{\alpha,h}
====================

d\Gamma(B_{\alpha,h}).
]

The full primitive-gauge anomalous-clock equation is

[
\boxed{
{}^CD_{\tau,i(\log\lambda)N}^{\gamma}
\Psi
====

*

d\Gamma(B_{\alpha,h})\Psi.
}
]

In the homogeneous isotropic case,

[
B_\alpha
========

D_\alpha(-\Delta)^{\alpha/2}.
]

On the (n)-particle Fourier sector,

[
\omega_{\alpha,n}(\mathbf k)
============================

D_\alpha
\sum_{j=1}^n|k_j|^\alpha.
]

Therefore

[
\boxed{
\begin{aligned}
\widehat\Psi_n(\mathbf k,\tau)
={}&
e^{-i(\log\lambda)n\tau}\
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
}
]

This is the explicit mode equation of the combined stable-space, anomalous-clock, primitive-gauge regime.

---

# 14. Why the primitive-gauge equation is the canonical one here

The coarse-event equation

[
{}^CD^\gamma\Psi
================

-(\mathbb H+i\beta N)\Psi
]

would be appropriate after redefining the gauge so that one gauge unit corresponds to one coarse profile transition.

But our original gauge was already fixed by

[
|p|
===

\text{number of primitive channels}.
]

Therefore, when the clock anomaly comes from random numbers of primitive edges per coarse transition, the canonical equation is

[
\boxed{
{}^CD_{\tau,i\beta N}^{\gamma}\Psi
==================================

-\mathbb H_h\Psi.
}
]

The gauge does not get subordinated because it measures the very microscopic count from which the anomalous coarse clock was constructed.

That also gives a useful physical distinction:

* a neutral mode (\omega=0) retains pure gauge oscillation,
  [
  e^{-i\beta n\tau};
  ]
* a stable mode (\omega>0) has algebraic relaxation multiplied by that phase.

Under coarse-event subordination, even a neutral gauge mode would undergo renewal-induced dephasing through

[
E_\gamma(-i\beta n\tau^\gamma).
]

The original path-length construction selects the first behavior.

---

# 15. When scalar fractional time is insufficient

The Caputo equation requires more than a heavy-tailed (W).

It also requires the clock to decouple sufficiently from the profile displacement.

Let

[
J_m
]

be the coarse profile jump and (W_m) its hidden primitive length.

If asymptotically

[
J_m
\quad\text{and}\quad
W_m
]

separate, then the limiting clock can be represented by one scalar inverse subordinator independent of the operational profile process.

If long blocks preferentially produce particular directions or jump sizes, then the joint kernel

[
\boxed{
Q_h(x,dy,dw)
}
]

must be retained.

The resulting equation has an operator-valued memory kernel and is generally semi-Markov rather than a scalar Caputo equation. General semi-Markov processes lead to abstract Volterra equations, with ordinary fractional derivatives only as special cases.

Similarly:

* state-dependent tail exponent
  [
  \gamma=\gamma(x)
  ]
  suggests variable-order memory;
* mixtures of tail exponents suggest distributed-order equations;
* directional waiting laws couple temporal and spatial symbols.

Thus

[
\boxed{
\Pr(W>n)\sim n^{-\gamma}
}
]

identifies the fractional order only after the necessary decoupling or joint-limit condition is checked.

---

# 16. Closure conditions

The anomalous-clock candidate is now fully specified. A later convergence proof must establish:

1. **Coarse-block definition:** specify (\Pi_\delta) and the renewal epochs (T_m).

2. **Regular variation:**
   [
   \Pr(W>n)\sim c n^{-\gamma}L(n).
   ]

3. **Operational-process convergence:** prove the profile process indexed by coarse transitions converges to the generator (\mathcal L^h) or (\mathcal L_\alpha^h).

4. **Clock convergence:** prove the accumulated block lengths converge to a subordinator with exponent (\Phi).

5. **Joint convergence:** determine whether the spatial/profile process and clock are asymptotically independent or coupled.

6. **Inverse-map convergence:** pass from the accumulated clock to its inverse renewal count.

7. **Age control:** identify initial-age effects and whether the process begins at a renewal epoch.

8. **Gauge bookkeeping:** verify whether phase accrues per primitive edge or per coarse transition.

These are later proof obligations, not unresolved ambiguity in the candidate equation.
