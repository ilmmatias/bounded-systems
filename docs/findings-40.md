# 1. The nonstationary correlation object

Because the graph is acyclic, we cannot automatically assume stationarity along compositional depth.

Let

[
\xi_k\in T_h\mathcal M
]

be a centered profile increment associated with the (k)-th route block. The primary covariance is therefore the two-index kernel

[
\boxed{
C_{jk}
======

\mathbb E_h[\xi_j\otimes\xi_k],
}
]

not necessarily a lag-only function.

For

[
S_n=\sum_{k=1}^n\xi_k,
]

we have

[
\boxed{
\operatorname{Cov}(S_{\lfloor nt\rfloor},S_{\lfloor ns\rfloor})
===============================================================

\sum_{j\le nt}
\sum_{k\le ns}
C_{jk}.
}
]

A continuum candidate is determined by a normalization (a_n) satisfying

[
\boxed{
a_n^{-2}
\operatorname{Cov}
\left(
S_{\lfloor nt\rfloor},
S_{\lfloor ns\rfloor}
\right)
\longrightarrow
\mathcal R(t,s).
}
]

Covariance convergence alone does not prove a Gaussian functional limit; tightness, Lindeberg/projective conditions or corresponding chaos assumptions are also required. Functional limit theorems for nonstationary dependent triangular arrays require precisely such additional dependence controls.

---

# 2. Why harmonic score increments have no long memory

Let (\phi) be a tangent score:

[
P_h\phi=\phi.
]

Then

[
M_n^\phi=\phi(X_n)
]

is a martingale, and

[
\Delta M_n^\phi
===============

\phi(X_{n+1})-\phi(X_n)
]

is a martingale difference.

For (j<k),

[
\begin{aligned}
\mathbb E[
\Delta M_j^\phi
\Delta M_k^\psi
]
&=
\mathbb E
\left[
\Delta M_j^\phi
\mathbb E[
\Delta M_k^\psi\mid\mathcal F_k
]
\right]\
&=0.
\end{aligned}
]

Therefore

[
\boxed{
\operatorname{Cov}
(
\Delta M_j^\phi,
\Delta M_k^\psi
)
=0
\qquad(j\ne k).
}
]

So the linear harmonic fluctuation sector is already whitened by the Doob-transformed dynamics.

This means long-range dependence can appear only through something that the harmonic martingale description has omitted:

[
\boxed{
\begin{aligned}
&\text{coarse profile compression},\
&\text{nonlinear functions of route fluctuations},\
&\text{a hidden boundary/environment variable},\
&\text{or a state description that is not Markov-complete}.
\end{aligned}
}
]

That is a significant structural result. Long memory is itself evidence of unresolved route information.

---

# 3. Asymptotically homogeneous special case

Suppose that sufficiently deep in the graph, the block correlations become approximately translation invariant:

[
C_{jk}\sim C(|j-k|).
]

Then

[
\operatorname{Var}(S_n)
=======================

nC(0)
+
\sum_{m=1}^{n-1}
(n-m)
\left[
C(m)+C(m)^\ast
\right].
]

## Summable correlations

If

[
\sum_{m\ge1}|C(m)|<\infty,
]

then

[
\operatorname{Var}(S_n)
\sim
n\Sigma_{\mathrm{eff}},
]

where

[
\boxed{
\Sigma_{\mathrm{eff}}
=====================

C(0)
+
\sum_{m\ge1}
\left[
C(m)+C(m)^\ast
\right].
}
]

Under appropriate mixing or martingale-approximation hypotheses, the normalization remains

[
a_n=\sqrt n
]

and the limit is Brownian with renormalized covariance (\Sigma_{\mathrm{eff}}). Functional central limit theorems for additive functionals of stationary reversible Markov processes give a rigorous version of this phenomenon under operator-domain conditions.

Thus summable route correlation does **not** create a new continuum regime. It renormalizes the quadratic tensor.

---

# 4. Power-law correlation and the Hurst exponent

Suppose instead

[
\boxed{
C(m)
\sim
Q,m^{-\eta}L(m),
\qquad
0<\eta<1,
}
]

where (L) is slowly varying and (Q) is a positive semidefinite covariance tensor.

Then

[
\begin{aligned}
\operatorname{Var}(S_n)
&\sim
2Q
\sum_{m=1}^{n-1}
(n-m)m^{-\eta}L(m)\
&\sim
\frac{2Q}
{(1-\eta)(2-\eta)}
n^{2-\eta}L(n).
\end{aligned}
]

Therefore the correct normalization is

[
\boxed{
a_n
===

n^HL(n)^{1/2},
\qquad
H=1-\frac{\eta}{2}.
}
]

Because (0<\eta<1),

[
\boxed{
\frac12<H<1.
}
]

If the correlation field is asymptotically Gaussian or linear enough, the limiting covariance is

[
\boxed{
\mathcal R_H(t,s)
=================

\frac{Q}{2}
\left(
t^{2H}
+s^{2H}
-|t-s|^{2H}
\right).
}
]

That is the covariance of a vector or operator-valued fractional Brownian field.

Fractional Brownian limits under long-range dependence, and the possibility of non-Gaussian Rosenblatt-type limits, go back to the noncentral limit theory of Taqqu and Dobrushin–Major.

So the correlation exponent and Hurst exponent are related by

[
\boxed{
\eta=2-2H.
}
]

---

# 5. Nonlinear route observables and Hermite rank

Long memory becomes richer when the coarse profile increment is a nonlinear function of a correlated Gaussian route field.

Suppose (G_k) is centered Gaussian with

[
\mathbb E[G_0G_m]
\sim
c,m^{-\eta}L(m),
]

and the observed route quantity is

[
\xi_k=F(G_k),
\qquad
\mathbb E[F(G_k)]=0.
]

Expand (F) in Hermite polynomials:

[
F(x)
====

\sum_{q=m}^{\infty}
c_qH_q(x),
\qquad
c_m\ne0.
]

The integer (m) is the Hermite rank.

The leading covariance behaves as

[
\boxed{
\operatorname{Cov}(\xi_0,\xi_k)
\sim
m!c_m^2
\left[
\operatorname{Cov}(G_0,G_k)
\right]^m
\sim
\widetilde c,k^{-m\eta}L(k)^m.
}
]

Three cases follow.

## (m\eta>1)

The transformed correlation is summable. The ordinary Brownian central-limit regime is restored.

## (m\eta<1)

The correlation remains nonsummable. The normalization is

[
\boxed{
n^{H_m},
\qquad
H_m=1-\frac{m\eta}{2},
}
]

and the limit is generally the (m)-th Hermite process.

* (m=1): fractional Brownian motion;
* (m=2): Rosenblatt process;
* (m\ge3): higher non-Gaussian Hermite process.

## (m\eta=1)

This is the borderline case, typically involving a logarithmic normalization.

The fact that nonlinear functionals of slowly decaying Gaussian fields can require faster-than-(\sqrt n) normalization and converge to non-Gaussian limits is exactly the Dobrushin–Major–Taqqu noncentral-limit mechanism.

Thus the route-correlation regime has a new discrete invariant:

[
\boxed{
m=\text{first nonlinear chaos degree visible after profile compression}.
}
]

---

# 6. Exact elimination of hidden route variables

There is a more structural derivation of memory that does not start by guessing a correlation law.

Linearize the full resolved dynamics into visible profile variables (x) and hidden route variables (y):

[
\boxed{
\begin{aligned}
\dot x(\tau)
&=
-B_hx(\tau)
+
C^\ast y(\tau),\
\dot y(\tau)
&=
-Cx(\tau)
---------

D_hy(\tau).
\end{aligned}
}
]

Here:

* (B_h) is the direct visible profile relaxation;
* (D_h) is the hidden-route relaxation operator;
* (C) couples visible and hidden sectors.

Solve the hidden equation:

[
y(\tau)
=======

## e^{-\tau D_h}y_0

\int_0^\tau
e^{-(\tau-s)D_h}
Cx(s),ds.
]

Substitution gives the exact visible equation

[
\boxed{
\dot x(\tau)
============

## -B_hx(\tau)

\int_0^\tau
K_h(\tau-s)x(s),ds
+
\eta_h(\tau),
}
]

where

[
\boxed{
K_h(\tau)
=========

C^\ast e^{-\tau D_h}C
}
]

and

[
\boxed{
\eta_h(\tau)
============

C^\ast e^{-\tau D_h}y_0.
}
]

This is a generalized Langevin/Volterra equation, but here it has been obtained directly by eliminating the hidden route sector.

The memory kernel and fluctuating term have the same hidden propagator:

[
e^{-\tau D_h}.
]

Generalized Langevin reductions likewise arise by eliminating unresolved degrees of freedom, producing a memory term and colored forcing; under equilibrium assumptions these are connected by a fluctuation–dissipation relation.

A fluctuation–dissipation identity is **not** automatic under A1–A5. It additionally requires a suitable symmetric or equilibrium state.

---

# 7. Spectral origin of power-law memory

Assume, conditionally, that

[
D_h\ge0
]

is self-adjoint on the hidden sector.

Its spectral resolution gives

[
e^{-\tau D_h}
=============

\int_{[0,\infty)}
e^{-\omega\tau},dE_h(\omega).
]

Hence

[
\boxed{
K_h(\tau)
=========

\int_{[0,\infty)}
e^{-\omega\tau},
d\Sigma_h(\omega),
}
]

where the operator-valued coupling measure is

[
d\Sigma_h(\omega)
=================

C^\ast dE_h(\omega)C.
]

Suppose its low-frequency density behaves as

[
\boxed{
d\Sigma_h(\omega)
\sim
A_h\omega^{\eta-1},d\omega,
\qquad
\omega\downarrow0,
}
]

with (0<\eta<1).

Then, under the corresponding Tauberian regularity,

[
\begin{aligned}
K_h(\tau)
&\sim
A_h
\int_0^\infty
e^{-\omega\tau}
\omega^{\eta-1}d\omega\
&=
\boxed{
\Gamma(\eta)A_h\tau^{-\eta}.
}
\end{aligned}
]

Therefore:

[
\boxed{
\text{long-range memory}
\iff
\text{a gapless hidden-route spectrum with weight near }\omega=0.
}
]

This is the precise spectral bridge.

Acyclicity forbids exact cyclic recurrence, but it does not forbid arbitrarily slow hidden modes. Infinite depth and repeated route reconvergence can generate a continuum of relaxation scales accumulating at zero.

---

# 8. The power-law memory equation

Normalize the memory kernel as

[
\boxed{
K_h(\tau)
=========

\frac{\kappa_h}
{\Gamma(1-\eta)}
\tau^{-\eta},
\qquad
0<\eta<1.
}
]

Then

[
\widetilde K_h(q)
=================

\kappa_hq^{\eta-1}.
]

The visible equation becomes

[
\boxed{
\dot x(\tau)
============

## -B_hx(\tau)

\frac{\kappa_h}
{\Gamma(1-\eta)}
\int_0^\tau
(\tau-s)^{-\eta}x(s),ds
+
\eta_h(\tau).
}
]

Its Laplace-domain form is

[
\boxed{
\left[
q+B_h+\kappa_hq^{\eta-1}
\right]
\widetilde x(q)
===============

x_0+\widetilde\eta_h(q).
}
]

This is the closed linear equation of the power-law route-memory regime.

It is **not** the same as the inverse-stable-clock equation

[
(q^\gamma+B_h)\widetilde x
==========================

q^{\gamma-1}x_0.
]

The two anomalies have different resolvents:

[
\boxed{
\text{renewal clock: }
q^\gamma+B_h,
}
]

[
\boxed{
\text{route memory: }
q+B_h+\kappa_hq^{\eta-1}.
}
]

They can produce similar algebraic scaling while representing mathematically different mechanisms.

---

# 9. Fractional Brownian forcing versus memory friction

There are also two distinct long-correlation descriptions.

## Correlated forcing

One may obtain

[
\boxed{
dX_\tau
=======

-B_hX_\tau,d\tau
+
\sigma_h,dB_H(\tau),
}
]

where (B_H) is fractional Brownian motion with

[
H=1-\frac{\eta}{2}.
]

This is a fractional Ornstein–Uhlenbeck-type profile process.

## Memory friction

Alternatively, hidden-route elimination produces

[
\boxed{
\dot X_\tau
===========

## -B_hX_\tau

\int_0^\tau
K_h(\tau-s)X_s,ds
+
\eta_h(\tau).
}
]

These are not universally equivalent.

They become linked only when the memory kernel and colored forcing covariance satisfy an additional fluctuation–dissipation condition. Fractional Langevin equations use precisely such power-law memory and correlated forcing, but the relation depends on the assumed equilibrium structure.

---

# 10. Markovian reconstruction of the memory

A completely monotone memory kernel can be represented as a continuous mixture of exponentials:

[
K_h(\tau)
=========

\int_0^\infty
e^{-\omega\tau},
\mu_h(d\omega).
]

Introduce one auxiliary hidden mode (z_\omega) for every relaxation rate (\omega):

[
\boxed{
\dot z_\omega
=============

-\omega z_\omega
+
C_\omega x.
}
]

Then

[
\boxed{
\dot x
======

## -B_hx

\int C_\omega^\ast z_\omega,\mu_h(d\omega)
+
\text{forcing}
}
]

is Markovian on the enlarged state

[
\left(
x,{z_\omega}_{\omega>0}
\right).
]

For the power kernel,

[
\frac{\tau^{-\eta}}
{\Gamma(1-\eta)}
================

\frac{\sin(\pi\eta)}{\pi}
\int_0^\infty
e^{-\omega\tau}
\omega^{\eta-1},d\omega.
]

Thus the fractional memory is exactly a continuum of hidden exponential modes with density

[
\boxed{
\mu_h(d\omega)
==============

\kappa_h
\frac{\sin(\pi\eta)}{\pi}
\omega^{\eta-1}d\omega.
}
]

So the non-Markovian profile equation becomes Markovian again when the unresolved spectral continuum is restored.

---

# 11. Primitive gauge coupling

Let

[
G=i\beta N,
\qquad
\beta=\log\lambda.
]

As before, the original gauge counts primitive channel composition, so it should not be subordinated or erased by profile compression.

Move to the interaction-picture variable

[
\Phi(\tau)=e^{G\tau}\Psi(\tau).
]

Suppose (\Phi) obeys the memory equation

[
\dot\Phi
========

## -\mathbb B_h\Phi

\int_0^\tau
K_h(\tau-s)\Phi(s),ds
+
\eta_h.
]

Transforming back gives

[
\boxed{
\begin{aligned}
(\partial_\tau+G)\Psi(\tau)
={}&
-\mathbb B_h\Psi(\tau)\
&-
\int_0^\tau
K_h(\tau-s)
e^{-G(\tau-s)}
\Psi(s),ds\
&+
\eta_{h,G}(\tau),
\end{aligned}
}
]

assuming (G) commutes with (\mathbb B_h) and (K_h).

The memory of a past state therefore carries the gauge phase accumulated over the intervening primitive compositional depth.

---

# 12. Gauge-covariant memory resolvent

Taking the Laplace transform gives

[
\boxed{
\left[
q+G+\mathbb B_h
+
\widetilde K_h(q+G)
\right]
\widetilde\Psi(q)
=================

\Psi_0+\widetilde\eta_{h,G}(q).
}
]

For the power-law kernel,

[
\widetilde K_h(z)
=================

\kappa_hz^{\eta-1}.
]

Hence

[
\boxed{
\left[
q+i\beta N
+\mathbb B_h
+\kappa_h(q+i\beta N)^{\eta-1}
\right]
\widetilde\Psi(q)
=================

\Psi_0+\widetilde\eta(q).
}
]

This is the primitive-gauge long-memory equation.

Suppose

[
\mathbb B_h\Psi_{\omega,n}
==========================

\omega\Psi_{\omega,n},
\qquad
N\Psi_{\omega,n}
================

n\Psi_{\omega,n}.
]

Then the mode response is

[
\boxed{
\widetilde\Psi_{\omega,n}(q)
============================

\frac{
\Psi_{\omega,n}(0)
+
\widetilde\eta_{\omega,n}(q)
}{
q+i\beta n
+\omega
+\kappa_h(q+i\beta n)^{\eta-1}
}.
}
]

That denominator is the complete complex dispersion relation of the linear power-memory regime.

---

# 13. Gaussian long-memory fluctuation space

If the limiting correlation field is Gaussian, its one-particle space is not merely the local tangent space (\mathfrak t_h).

It is the covariance Hilbert space

[
\boxed{
\mathfrak H_H
\widehat\otimes
\mathfrak t_h,
}
]

where (\mathfrak H_H) is generated by the fractional covariance

[
R_H(t,s)
========

\frac12
\left(
t^{2H}+s^{2H}-|t-s|^{2H}
\right).
]

The Gaussian fluctuation representation is

[
\boxed{
\Gamma_s(
\mathfrak H_H
\widehat\otimes
\mathfrak t_h
).
}
]

There remains a number operator (N), so the path-growth gauge grading survives.

But because the covariance is nonlocal in compositional depth, the dissipative dynamics is no longer generally generated by a time-local operator

[
d\Gamma(B_h)
]

on the instantaneous profile space. Its natural object is the memory resolvent above, or an enlarged Markovian hidden-mode representation.

---

# 14. Higher-Hermite route fields

For Hermite rank (m\ge2), the limit is non-Gaussian.

It lies in the (m)-th Wiener chaos of an underlying Gaussian correlation field, but that does **not** imply that its effective dynamics is the second quantization of a one-particle operator.

Therefore, in the higher-Hermite regime,

[
\boxed{
\mathbb H_h
\ne
d\Gamma(B_h)
}
]

in general.

One must retain nonlinear chaos couplings. The previous free-Fock closure fails.

The hierarchy is now:

[
\boxed{
\begin{array}{c|c}
\text{visible route structure}
&
\text{continuum fluctuation field}
\ \hline
\text{harmonic linear score}
&
\text{martingale/Brownian}
\
\text{linear long-memory score}
&
\text{fractional Gaussian}
\
\text{rank-2 nonlinear score}
&
\text{Rosenblatt}
\
\text{rank-}m\text{ score}
&
m\text{-th Hermite process}
\end{array}
}
]

Multivariate long-range systems can similarly produce operator fractional Brownian limits or matrix-valued Rosenblatt limits.

---

# 15. Three genuinely different sources of temporal anomaly

We can now separate the anomalies cleanly.

## Renewal anomaly

The number of primitive channels inside one coarse transition is heavy-tailed:

[
\Pr(W>n)\sim n^{-\gamma}.
]

Result:

[
{}^CD^\gamma_\tau u=\mathcal L^hu.
]

## Correlation anomaly

Distant route blocks remain correlated:

[
C(m)\sim m^{-\eta}.
]

Result:

[
\dot u
======

-B_hu-K_h*u+\eta_h,
\qquad
K_h(t)\sim t^{-\eta}.
]

## Nonlinear-chaos anomaly

A nonlinear profile observable has Hermite rank (m), causing long memory to survive in higher chaos.

Result:

[
n^{-H_m}
\sum_{k\le nt}F(G_k)
\Longrightarrow
Z_{m,H_m}(t).
]

These mechanisms can coexist, but they are not interchangeable.

---

# 16. Closure theorem for the long-memory branch

At the candidate-equation level, the long-range route-correlation regime is now closed by the following data:

[
\boxed{
(B_h,D_h,C)
}
]

for the resolved/hidden linearization,

[
\boxed{
K_h(\tau)=C^\ast e^{-\tau D_h}C,
}
]

and, in the power-law case,

[
\boxed{
d\Sigma_h(\omega)
\sim
A_h\omega^{\eta-1}d\omega
\iff
K_h(\tau)\sim
\Gamma(\eta)A_h\tau^{-\eta}.
}
]

The profile equation is

[
\boxed{
\dot x(\tau)
============

## -B_hx(\tau)

\int_0^\tau
K_h(\tau-s)x(s),ds
+
\eta_h(\tau).
}
]

Its primitive-gauge fluctuation lift is

[
\boxed{
(\partial_\tau+i\beta N)\Psi(\tau)
==================================

## -\mathbb B_h\Psi(\tau)

\int_0^\tau
K_h(\tau-s)
e^{-i\beta N(\tau-s)}
\Psi(s),ds
+
\eta_{h,\beta}(\tau).
}
]

And its spectral resolvent is

[
\boxed{
\widetilde\Psi(q)
=================

\left[
q+i\beta N
+\mathbb B_h
+\widetilde K_h(q+i\beta N)
\right]^{-1}
\left[
\Psi_0+\widetilde\eta(q)
\right].
}
]

For

[
K_h(t)
======

\frac{\kappa_h}{\Gamma(1-\eta)}t^{-\eta},
]

this becomes

[
\boxed{
\widetilde\Psi(q)
=================

\left[
q+i\beta N
+\mathbb B_h
+\kappa_h(q+i\beta N)^{\eta-1}
\right]^{-1}
\left[
\Psi_0+\widetilde\eta(q)
\right].
}
]

