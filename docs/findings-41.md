# 1. Operational visible–hidden system

Let $\mathscr H_{\mathrm{vis}}$ be the visible profile-fluctuation space and $\mathscr H_{\mathrm{hid}}$ the hidden route sector discarded by profile compression.

Write the linearized operational dynamics as

```math
\begin{aligned}
\partial_s\Psi(s)
&=
-\mathbb H_h\Psi(s)+C^\ast Y(s),\\
\partial_sY(s)
&=
-D_hY(s)-C\Psi(s).
\end{aligned}
```

Here:

* $\mathbb H_h\ge0$ contains the directly visible profile dynamics;
* $D_h\ge0$ contains hidden route relaxation;
* $C$ couples the two sectors.

Depending on the regime,

```math
\mathbb H_h=
\begin{cases}
d\Gamma(B_h),&\text{Gaussian profile regime},\\[1mm]
d\Gamma(B_{\alpha,h}),&\alpha\text{-stable regime},\\[1mm]
\text{a general Lévy fluctuation generator},&\text{mixed jump regime}.
\end{cases}
```

The variable $s$ counts operational profile evolution before applying an anomalous clock.

---

# 2. Eliminate the hidden route sector

Take a Laplace transform in $s$. Ignoring a nonzero hidden initial condition for the moment,

```math
(s+D_h)\widetilde Y(s)=
-C\widetilde\Psi(s),
```

so

```math
\widetilde Y(s)=
-(s+D_h)^{-1}C\widetilde\Psi(s).
```

Substitution gives

```math
\left[
s+\mathbb H_h+
C^\ast(s+D_h)^{-1}C
\right]
\widetilde\Psi(s)=
\Psi_0.
```

Define the hidden-route self-energy

```math
\Sigma_h(s)=
C^\ast(s+D_h)^{-1}C.
```

The operational visible resolvent is therefore

```math
R_{\mathrm{op}}(s)=
\left[
s+\mathbb H_h+\Sigma_h(s)
\right]^{-1}.
```

This is the Schur complement of the full visible–hidden operator.

The corresponding time-domain equation is

```math
\partial_s\Psi(s)=
-\mathbb H_h\Psi(s)-
\int_0^sK_h(s-r)\Psi(r)\,dr,
```

with

```math
K_h(s)=C^\ast e^{-sD_h}C
```

and

```math
\widetilde K_h(z)=\Sigma_h(z).
```

Eliminating unresolved variables yields an operator-valued memory kernel, as standard in generalized Langevin/Mori–Zwanzig reductions.

---

# 3. Spectral representation of the self-energy

When $D_h$ is nonnegative self-adjoint,

```math
D_h=\int_0^\infty\omega\,dE_h(\omega).
```

Therefore

```math
\Sigma_h(s)=
\int_0^\infty
\frac{dM_h(\omega)}{s+\omega},
```

where

```math
dM_h(\omega)=
C^\ast dE_h(\omega)C.
```

So $\Sigma_h$ is an operator-valued Stieltjes function.

If the hidden-route spectral measure has low-frequency behavior

```math
dM_h(\omega)
\sim
A_h\omega^{\eta-1}\,d\omega,
\qquad
0<\eta<1,
```

then

```math
\begin{aligned}
\Sigma_h(s)
&\sim
A_h
\int_0^\infty
\frac{\omega^{\eta-1}}{s+\omega}\,d\omega\\
&=
\frac{\pi A_h}{\sin(\pi\eta)}
s^{\eta-1}.
\end{aligned}
```

Thus the power-law memory self-energy is

```math
\Sigma_h(s)\sim\kappa_hs^{\eta-1}.
```

This is the precise sense in which a gapless hidden route spectrum produces long memory.

---

# 4. The general intrinsic clock

Let the accumulated hidden block-length process converge to a subordinator with Laplace exponent

```math
\mathbb E[e^{-qD_s}]=
e^{-s\Phi(q)}.
```

The function $\Phi$ is a Bernstein function.

Examples include

```math
\Phi(q)=q
```

for an ordinary clock,

```math
\Phi(q)=q^\gamma,
\qquad
0<\gamma<1,
```

for a stable anomalous clock, and

```math
\Phi(q)=
(q+\vartheta)^\gamma-\vartheta^\gamma
```

for a tempered stable clock.

If $R_{\mathrm{op}}(s)$ is the operational resolvent, inverse subordination gives the observed-time resolvent

```math
\widetilde R_\Phi(q)=
\frac{\Phi(q)}q
R_{\mathrm{op}}(\Phi(q)).
```

The factor

```math
\frac{\Phi(q)}q
```

encodes the initial condition for the generalized Caputo-type equation. Inverse subordinators generate these generalized time-nonlocal Cauchy problems.

Substituting the operational resolvent gives

```math
\widetilde R_\Phi(q)=
\frac{\Phi(q)}q
\left[
\Phi(q)
+
\mathbb H_h
+
\Sigma_h(\Phi(q))
\right]^{-1}.
```

Already, without gauge, this combines spatial propagation, renewal clock and hidden-route memory.

---

# 5. Restore the primitive path gauge

The original gauge counts primitive edge degree:

```math
N\xi_p=|p|\xi_p.
```

Set

```math
G=i\beta N,
\qquad
\beta=\log\lambda=-2\log R.
```

The gauge-covariant Laplace variable is

```math
Z_q=qI+G=qI+i\beta N.
```

This replacement is justified when the visible and hidden dynamics preserve gauge degree, meaning that the coupling intertwines the relevant number operators.

Equivalently, in the interaction picture

```math
\Phi_{\mathrm{int}}(\tau)=
e^{G\tau}\Psi(\tau),
```

the dissipative and hidden-route equations contain no explicit gauge phase.

The ordinary scalar clock variable $q$ is therefore replaced by the operator $Z_q$.

Under the degree-preserving hypothesis, $\Phi(Z_q)$ is defined by the holomorphic functional calculus. Bernstein and complete Bernstein functions are naturally compatible with sectorial-generator functional calculus and subordination.

---

# 6. The master resolvent

Combining all four structures gives

```math
\widetilde\Psi(q)=
\frac{\Phi(Z_q)}{Z_q}
\left[
\Phi(Z_q)
+
\mathbb H_h
+
\Sigma_h\!\left(\Phi(Z_q)\right)
\right]^{-1}
\Psi_0.
```

That is the master equation in resolvent form.

With

```math
Z_q=qI+i(\log\lambda)N,
```

it is

```math
\widetilde\Psi(q)=
\frac{
\Phi\!\left(qI+i(\log\lambda)N\right)
}{
qI+i(\log\lambda)N
}
\left[
\begin{aligned}
&
\Phi\!\left(qI+i(\log\lambda)N\right)
+\mathbb H_h\\
&\quad+
\Sigma_h\!\left(
\Phi\!\left(qI+i(\log\lambda)N\right)
\right)
\end{aligned}
\right]^{-1}
\Psi_0.
```

A nonzero hidden-sector initial condition or external forcing adds a numerator source but does not change the regime-controlling denominator.

---

# 7. Time-domain master equation

Define the gauge-covariant generalized derivative by

```math
\mathcal{L}_{\tau}
\left[\mathfrak{D}_{G}^{\Phi}\Psi\right](q)
=
\Phi(Z_q)\widetilde{\Psi}(q)
-
\frac{\Phi(Z_q)}{Z_q}\Psi_0.
```

Define the clock-renormalized memory kernel through

```math
\widetilde{\mathcal K}_{\Phi,G}(q)=
\Sigma_h\!\left(\Phi(Z_q)\right).
```

Then the time-domain equation is

```math
\mathfrak D_G^\Phi\Psi(\tau)
+
\mathbb H_h\Psi(\tau)
+
\int_0^\tau
\mathcal K_{\Phi,G}(\tau-s)
\Psi(s)\,ds=
0.
```

This operator equation contains every candidate regime derived so far.

It says:

```math
\text{generalized covariant time derivative}
+
\text{visible spatial generator}
+
\text{hidden-route self-energy}
=0.
```

---

# 8. Mode reduction

Assume the regime is homogeneous and degree preserving, so that $\mathbb H_h$, $N$, and the hidden self-energy can be simultaneously decomposed.

On the $n$-excitation sector, let

```math
N=n,
```

and define

```math
z_n=q+i\beta n.
```

Suppose

```math
\mathbb H_h\Psi_{n,\mathbf k}=
\omega_n(\mathbf k)\Psi_{n,\mathbf k},
```

and

```math
\Sigma_h(s)\Psi_{n,\mathbf k}=
\sigma_n(s,\mathbf k)\Psi_{n,\mathbf k}.
```

Then

```math
\widetilde\Psi_n(\mathbf k,q)=
\frac{\Phi(z_n)}{z_n}
\frac{
\Psi_n(\mathbf k,0)
}{
\Phi(z_n)
+
\omega_n(\mathbf k)
+
\sigma_n(\Phi(z_n),\mathbf k)
}.
```

This is the scalar sector equation.

The generalized complex dispersion denominator is

```math
\mathcal D_n(q,\mathbf k)=
\Phi(q+i\beta n)
+
\omega_n(\mathbf k)
+
\sigma_n\!\left(
\Phi(q+i\beta n),\mathbf k
\right).
```

The asymptotic behavior is controlled by the poles, branch points and threshold singularities of

```math
\mathcal D_n(q,\mathbf k)^{-1}.
```

---

# 9. Gaussian regime

Take

```math
\Phi(z)=z,
\qquad
\sigma_n=0,
```

and

```math
\omega_n(\mathbf k)=
D_2\sum_{j=1}^n|k_j|^2.
```

Then

```math
\widetilde\Psi_n=
\frac{
\Psi_n(0)
}{
q+i\beta n
+
D_2\sum_j|k_j|^2
}.
```

Inverting gives

```math
\Psi_n(\mathbf k,\tau)=
e^{-i\beta n\tau}
e^{-D_2\tau\sum_j|k_j|^2}
\Psi_n(\mathbf k,0).
```

This is the ordinary diffusion-plus-gauge regime.

---

# 10. Stable spatial regime

Take

```math
\Phi(z)=z,
\qquad
\sigma_n=0,
```

and

```math
\omega_n(\mathbf k)=
D_\alpha\sum_j|k_j|^\alpha.
```

Then

```math
\widetilde\Psi_n=
\frac{
\Psi_n(0)
}{
q+i\beta n
+
D_\alpha\sum_j|k_j|^\alpha
}.
```

Therefore

```math
\Psi_n(\mathbf k,\tau)=
e^{-i\beta n\tau}
e^{-D_\alpha\tau\sum_j|k_j|^\alpha}
\Psi_n(\mathbf k,0).
```

---

# 11. Renewal-clock regime

Take

```math
\Phi(z)=z^\gamma,
\qquad
0<\gamma<1,
```

and

```math
\sigma_n=0.
```

Then

```math
\widetilde\Psi_n=
\frac{
z_n^{\gamma-1}
}{
z_n^\gamma+\omega_n(\mathbf k)
}
\Psi_n(0).
```

In time,

```math
\Psi_n(\mathbf k,\tau)=
e^{-i\beta n\tau}
E_\gamma
\left[
-\omega_n(\mathbf k)\tau^\gamma
\right]
\Psi_n(\mathbf k,0).
```

This reproduces the primitive-gauge anomalous-clock equation.

---

# 12. Hidden-route memory regime

Take an ordinary clock,

```math
\Phi(z)=z,
```

and a power-law self-energy,

```math
\sigma_n(z,\mathbf k)=
\kappa_n(\mathbf k)z^{\eta-1},
\qquad
0<\eta<1.
```

Then

```math
\widetilde\Psi_n=
\frac{
\Psi_n(0)
}{
z_n
+
\omega_n(\mathbf k)
+
\kappa_n(\mathbf k)z_n^{\eta-1}
}.
```

This recovers the previously derived long-memory response.

The gauge translates its branch point:

```math
z_n=0
\iff
q=-i\beta n.
```

Thus, the $n$-th degree sector has the zero-degree sector's memory envelope, modulated by the primitive gauge phase

```math
e^{-i\beta n\tau}.
```

---

# 13. Fully combined nested regime

Now take:

```math
\Phi(z)=z^\gamma,
```

```math
\omega_n(\mathbf k)=
D_\alpha
\sum_j|k_j|^\alpha,
```

and

```math
\sigma_n(s)=
\kappa_ns^{\eta-1}.
```

Then

```math
\sigma_n(\Phi(z_n))=
\kappa_nz_n^{\gamma(\eta-1)}.
```

The master mode resolvent becomes

```math
\widetilde\Psi_n(\mathbf k,q)=
\frac{
z_n^{\gamma-1}
}{
z_n^\gamma
+
D_\alpha\sum_j|k_j|^\alpha
+
\kappa_nz_n^{\gamma(\eta-1)}
}
\Psi_n(\mathbf k,0).
```

Equivalently,

```math
\mathcal D_n(q,\mathbf k)=
(q+i\beta n)^\gamma
+
D_\alpha\sum_j|k_j|^\alpha
+
\kappa_n
(q+i\beta n)^{\gamma(\eta-1)}.
```

This contains simultaneously:

* stable spatial propagation $\alpha$;
* anomalous clock exponent $\gamma$;
* hidden-route memory exponent $\eta$;
* primitive gauge rate $\beta$.

---

# 14. Nested versus parallel anomalies

There is one structural distinction that cannot be erased.

The preceding combined equation assumes the order

```math
\text{eliminate hidden route variables}
\quad\longrightarrow\quad
\text{apply anomalous clock}.
```

Hence the self-energy is evaluated at

```math
\Sigma_h(\Phi(z)).
```

Thus the clock and memory operations are nested.

If route memory is generated directly in primitive time after compressing the operational clock, the denominator becomes

```math
\Phi(z)
+
\mathbb H_h
+
\Sigma_h(z).
```

For power laws, that gives

```math
z^\gamma
+
D_\alpha|k|^\alpha
+
\kappa z^{\eta-1},
```

not

```math
z^\gamma
+
D_\alpha|k|^\alpha
+
\kappa z^{\gamma(\eta-1)}.
```

These two equations represent different causal organizations:

```math
\Sigma(\Phi(z))=
\text{memory inside operational dynamics, then clocked},
```

```math
\Sigma(z)=
\text{memory acting directly in primitive time}.
```

The microscopic block construction decides which one applies.

---

# 15. Stability of the master denominator

Assume:

```math
\mathbb H_h\ge0,
\qquad
D_h\ge0.
```

For $\Re s>0$,

```math
\begin{aligned}
\Re\langle f,\Sigma_h(s)f\rangle
&=
\Re
\left\langle
Cf,(s+D_h)^{-1}Cf
\right\rangle\\
&=
\int_0^\infty
\frac{
\Re s+\omega
}{
|s+\omega|^2
}
\,d\mu_f(\omega)\\
&\ge0.
\end{aligned}
```

Thus the hidden-route self-energy is accretive in the right half-plane.

If $\Phi$ maps the right half-plane into an appropriate positive sector, then

```math
\Phi(Z_q)+\mathbb H_h+\Sigma_h(\Phi(Z_q))
```

is likewise accretive for $\Re q>0$, subject to the standard domain conditions.

Therefore the master resolvent has no exponentially growing pole in the open right half-plane.

The stability criterion is:

```math
\text{positive visible relaxation}
+
\text{positive hidden relaxation}
+
\text{admissible intrinsic clock}
\Longrightarrow
\text{no right-half-plane instability}.
```

Instability would require:

* a nonaccretive transformed spatial generator;
* an active rather than dissipative hidden sector;
* a nonadmissible clock law;
* or a sign-changing coupling not represented by the positive Schur complement above.

---

# 16. Gauge-translated spectral structure

Because every appearance of $q$ is through

```math
z_n=q+i\beta n,
```

the $n$-th gauge sector is a vertical translation of the zero-degree spectral structure.

If the ungauged amplitude has inverse Laplace transform $A_n(\tau)$, then

```math
\Psi_n(\tau)=
e^{-i\beta n\tau}A_n(\tau).
```

This remains true whether $A_n$ is:

* exponential;
* Mittag–Leffler;
* fractional-stable;
* power-law-memory;
* or a general Volterra relaxation profile.

So the primitive gauge phase is universal across all the regimes:

```math
\text{gauge changes spectral location, not the dissipative envelope}.
```

This requires degree preservation: if the dissipative generator changes path degree, the sectors couple and the simple translation law fails.

---

# 17. The degree-mixing obstruction

Define

```math
\mathfrak C_H=[\mathbb H_h,N],
```

```math
\mathfrak C_D=[D_h,N_{\mathrm{hid}}],
```

and the coupling defect

```math
\mathfrak C_C=
N_{\mathrm{hid}}C-CN.
```

The scalar sector equation exists exactly in the gauge-compatible case

```math
\mathfrak C_H=
\mathfrak C_D=
\mathfrak C_C=0.
```

If any of these fail, the path grading is not preserved by the effective dynamics.

The master equation still exists on the full block space, but the substitution

```math
q\mapsto q+i\beta n
```

cannot be performed separately in each sector. One must retain the full operator resolvent.

Thus degree mixing is the precise obstruction to diagonal gauge closure.

---

# 18. The universality data

The candidate continuum regime is now classified by

```math
\mathfrak U=
\left(
\alpha,\gamma,\eta,\beta;
\Lambda_h,
\Phi,
M_h,
\mathfrak C_H,
\mathfrak C_D,
\mathfrak C_C
\right).
```

Here:

```math
\alpha=
\text{spatial/profile jump exponent},
```

```math
\gamma=
\text{renewal-clock exponent},
```

```math
\eta=
\text{hidden spectral/memory exponent},
```

```math
\beta=\log\lambda=
\text{primitive gauge rate},
```

```math
\Lambda_h=
\text{angular stable-jump measure},
```

```math
M_h=
\text{hidden-route spectral measure}.
```

The exponents alone do not determine the theory: the angular jump measure, hidden spectral measure and degree-mixing defects retain information beyond four scalar parameters.
