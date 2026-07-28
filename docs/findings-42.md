# 1. Microscopic data for a continuum limit

Take a directed refinement family

```math
G_\delta=(V_\delta,E_\delta),
\qquad
\delta\downarrow0.
```

We need the following derived data.

### Profile embedding

A map into a finite-dimensional smooth profile stratum,

```math
x_\delta:V_\delta\longrightarrow M,
```

where $M$ is locally represented by coordinates

```math
x=(x^1,\ldots,x^d).
```

For infinite-dimensional profile spaces, the same construction is performed first on cylindrical observables.

### Positive critical profile

Let the transfer operator be

```math
(T_\delta f)(v)=
\sum_{e:s(e)=v}
w_\delta(e)f(r(e)),
```

where $w_\delta(e)=1$ in the unweighted channel-counting case.

Choose

```math
T_\delta h_\delta=
\lambda_\delta h_\delta,
\qquad
h_\delta>0.
```

The derived channel law is

```math
p_\delta^h(e\mid v)=
\frac{
w_\delta(e)h_\delta(r(e))
}{
\lambda_\delta h_\delta(v)
}.
```

Indeed,

```math
\sum_{e:s(e)=v}p_\delta^h(e\mid v)=1.
```

### Continuum time scale

Let one microscopic edge step represent

```math
a_\delta\downarrow0
```

units of continuum compositional time.

The rescaled path process is

```math
X_\delta(\tau)=
x_\delta\!\left(
V_{\lfloor\tau/a_\delta\rfloor}
\right).
```

Everything follows from the tuple

```math
\left(
G_\delta,x_\delta,h_\delta,
\lambda_\delta,a_\delta
\right).
```

# 2. The exact discrete generator

For a test function $f$ on $M$, define

```math
\begin{aligned}
\mathcal L_\delta^hf(x_\delta(v))=
\frac1{a_\delta}
\sum_{e:s(e)=v}
p_\delta^h(e\mid v)
\Big[
f(x_\delta(r(e)))
-f(x_\delta(v))
\Big].
\end{aligned}
```

Let the edge displacement be

```math
Y_\delta(e)=
x_\delta(r(e))-x_\delta(v).
```

Then

```math
\mathcal L_\delta^hf(x)=
\frac1{a_\delta}
\mathbb E_{\delta,h}
\left[
f(x+Y_\delta)-f(x)
\mid x
\right].
```

This generator determines the drift, diffusion, and stable exponents.

# 3. Local drift and quadratic tensor

In a local coordinate chart, define

```math
b_\delta^i(x)=
\frac1{a_\delta}
\sum_e
p_\delta^h(e\mid x)
Y_\delta^i(e),
```

and

```math
A_\delta^{ij}(x)=
\frac1{a_\delta}
\sum_e
p_\delta^h(e\mid x)
Y_\delta^i(e)Y_\delta^j(e).
```

If

```math
b_\delta(x)\longrightarrow b_h(x)
```

and

```math
A_\delta(x)\longrightarrow a_h(x),
```

then the candidate local generator is

```math
\mathcal L^hf=
b_h^i\partial_i f
+
\frac12a_h^{ij}\partial_i\partial_jf.
```

The tensor $a_h$ is positive semidefinite because each $A_\delta$ is a weighted sum of rank-one positive tensors.

For a tangent field $\phi$,

```math
\begin{aligned}
a_h^{ij}\partial_i\phi,\partial_j\phi
&=
\lim_{\delta\to0}
\frac1{a_\delta}
\sum_e
p_\delta^h(e\mid x)
\bigl[
\phi(x+Y_\delta(e))-\phi(x)
\bigr]^2.
\end{aligned}
```

Thus the continuum diffusion tensor is exactly the scaled limit of the discrete quadratic variation already derived.

# 4. A direct diffusion-limit theorem

Assume on every compact $K\Subset M$:

```math
\sup_{x_\delta(v)\in K}
\max_{e:s(e)=v}
|Y_\delta(e)|
\longrightarrow0,
```

```math
b_\delta\longrightarrow b_h
```

uniformly on $K$,

```math
A_\delta\longrightarrow a_h
```

uniformly on $K$, and

```math
\sup_{x_\delta(v)\in K}
\frac1{a_\delta}
\sum_e
p_\delta^h(e\mid v)
|Y_\delta(e)|^3
\longrightarrow0.
```

Then for every $f\in C_c^3(M)$,

```math
\mathcal L_\delta^hf
\longrightarrow
\mathcal L^hf
```

uniformly on compact sets.

### Proof

Taylor expansion gives

```math
\begin{aligned}
f(x+y)-f(x)
={}&
\partial_i f(x)y^i
+
\frac12
\partial_i\partial_jf(x)y^iy^j\\
&+
R_f(x,y),
\end{aligned}
```

with

```math
|R_f(x,y)|
\le
C_{f,K}|y|^3.
```

Substituting into $\mathcal L_\delta^h$,

```math
\begin{aligned}
\mathcal L_\delta^hf
={}&
b_\delta^i\partial_i f
+
\frac12A_\delta^{ij}
\partial_i\partial_j f\\
&+
\frac1{a_\delta}
\sum_ep_\delta^h(e\mid x)
R_f(x,Y_\delta(e)).
\end{aligned}
```

The final term vanishes by the scaled third-moment condition.

Therefore

```math
\mathcal L_\delta^hf
\to
b_h\cdot\nabla f
+
\frac12a_h:\nabla^2f.
```

That proves generator convergence.

# 5. From generator convergence to process convergence

Generator convergence alone is not enough. The full continuum-limit proof requires three pieces.

## Compact containment

For every $T>0$ and $\varepsilon>0$, there must be a compact $K\Subset M$ such that

```math
\inf_\delta
\Pr
\left[
X_\delta(\tau)\in K
\text{ for all }0\le\tau\le T
\right]
\ge1-\varepsilon.
```

This prevents probability from escaping through unrepresented parts of the profile space.

## Tightness

For every smooth compactly supported $f$,

```math
\begin{aligned}
M_\delta^f(\tau)=
f(X_\delta(\tau))
-f(X_\delta(0))
-\int_0^\tau
\mathcal L_\delta^hf(X_\delta(s)),ds
\end{aligned}
```

is a martingale.

Bounds on the drift and quadratic variation of these martingales establish tightness in the Skorokhod path space.

## Uniqueness of the limiting martingale problem

Every subsequential limit $X$ satisfies

```math
f(X_\tau)-f(X_0)
-\int_0^\tau
\mathcal L^hf(X_s),ds
```

is a martingale.

If the martingale problem for $\mathcal L^h$ is unique, all subsequences have the same limit, and therefore

```math
X_\delta\Rightarrow X.
```

For example, local Lipschitz regularity of $b_h$ and a sufficiently regular nondegenerate $a_h$ gives a standard uniqueness route. Degenerate profile metrics require a more careful argument.

# 6. General jump-coefficient extraction

For stable or mixed Lévy limits, Taylor expansion cannot be used globally.

Choose a bounded truncation function

```math
\chi(y)=y
\quad\text{near }y=0.
```

Define the scaled jump kernel

```math
\nu_\delta^h(x,dy)=
\frac1{a_\delta}
\sum_{e:s(e)=v}
p_\delta^h(e\mid v)
\delta_{Y_\delta(e)}(dy).
```

The limiting measure is generally infinite near $y=0$, so convergence is tested against continuous functions $g$ that vanish in a neighborhood of zero:

```math
\int g(y)\nu_\delta^h(x,dy)
\longrightarrow
\int g(y)\nu_h(x,dy).
```

The truncated drift is

```math
b_\delta^\chi(x)=
\int\chi(y)\nu_\delta^h(x,dy).
```

The residual Gaussian covariance is

```math
a_h(x)=
\lim_{\varepsilon\downarrow0}
\lim_{\delta\downarrow0}
\int_{|y|\le\varepsilon}
y\otimes y,
\nu_\delta^h(x,dy),
```

when this iterated limit exists.

The limiting generator is then

```math
\begin{aligned}
\mathcal L^hf(x)
={}&
b_h^\chi(x)\cdot\nabla f(x)
+
\frac12a_h(x):\nabla^2f(x)\\
&+
\int
\left[
f(x+y)-f(x)-\chi(y)\cdot\nabla f(x)
\right]
\nu_h(x,dy).
\end{aligned}
```

The three coefficient objects are therefore obtained directly as

```math
b_h^\chi,\qquad
a_h,\qquad
\nu_h.
```

# 7. Stable coefficient extraction

Suppose the limiting jump measure satisfies

```math
\nu_h(x,rA)=
r^{-\alpha}\nu_h(x,A)
```

for every $r>0$ and suitable sets $A$.

Then $\alpha$ is the stable exponent.

It can be extracted from the radial tail:

```math
\alpha=
-\lim_{r\to\infty}
\frac{
\log\nu_h(x,{|y|>r})
}{
\log r
},
```

when the limit exists and is independent of $x$.

The angular measure is

```math
\Lambda_h(x,B)=
\nu_h
\left(
x,
\left\lbrace y:|y|>1,\ \widehat y\in B \right\rbrace \right).
```

For a symmetric stable kernel, the characteristic symbol is

```math
\psi_{\alpha,h}(x,k)=
\int
\bigl[
1-\cos(k\cdot y)
\bigr]
\nu_h(x,dy).
```

In the homogeneous isotropic case,

```math
\psi_{\alpha,h}(k)=
D_\alpha|k|^\alpha.
```

A convention-independent extraction of $D_\alpha$ is

```math
D_\alpha=
\psi_{\alpha,h}(e)
```

for any unit vector $e$, when isotropy holds.

# 8. Convergence theorem for the Lévy regime

Suppose on every compact profile region:

1. for every continuous $g$ vanishing near zero, $\int g,d\nu_\delta^h \to \int g,d\nu_h$;
2. the truncated drifts converge, $b_\delta^\chi\to b_h^\chi$;
3. the residual small-jump covariance converges to $a_h$;
4. the family satisfies compact containment;
5. the martingale problem for the limiting Lévy-type operator is unique.

Then

```math
X_\delta\Rightarrow X,
```

where $X$ has generator $\mathcal L^h$.

This is the exact proof program for Gaussian, stable and mixed jump regimes. They differ only in which parts of the characteristic triplet survive.

# 9. Convergence of the $h$-transform itself

The transformed transition law contains the ratio

```math
\frac{h_\delta(r(e))}{h_\delta(v)}.
```

Therefore coefficient convergence also requires control of $h_\delta$.

Suppose, after interpolation to $M$,

```math
h_\delta\longrightarrow h>0
```

locally uniformly, and preferably

```math
\log h_\delta\longrightarrow \log h
```

in the regularity class required by the candidate operator.

For a local diffusion limit, one generally needs enough control that

```math
\nabla\log h_\delta
\longrightarrow
\nabla\log h.
```

For a nonlocal limit, one needs convergence of the ratios

```math
\frac{h_\delta(x+y)}{h_\delta(x)}
\longrightarrow
\frac{h(x+y)}{h(x)}
```

in a form integrable against the limiting jump kernels.

If an untransformed generator $\mathcal L_{0,\delta}$ exists with

```math
\mathcal L_{0,\delta}h_\delta=
\kappa_\delta h_\delta,
```

and

```math
\mathcal L_{0,\delta}\to\mathcal L_0,
\qquad
h_\delta\to h,
\qquad
\kappa_\delta\to\kappa,
```

then

```math
\begin{aligned}
\mathcal L_\delta^hf
&=
h_\delta^{-1}
\mathcal L_{0,\delta}(h_\delta f)
-\kappa_\delta f\\
&\longrightarrow
h^{-1}\mathcal L_0(hf)-\kappa f.
\end{aligned}
```

Hence

```math
\mathcal L^hf=
h^{-1}\mathcal L_0(hf)-\kappa f.
```

This is the rigorous continuum passage of the discrete harmonic normalization.

# 10. Bulk-growth renormalization

There is a subtle issue here.

The transfer eigenvalue $\lambda_\delta$ need not approach $1$. If

```math
\lambda_\delta\to\lambda_0>1,
```

then

```math
\frac{\lambda_\delta-1}{a_\delta}
\to\infty.
```

So the raw transfer operator cannot converge directly to a finite differential generator.

One must separate:

```math
\text{bulk route multiplication}
```

from

```math
\text{finite continuum evolution}.
```

Write

```math
\lambda_\delta=
\Lambda_\delta
e^{a_\delta\kappa_\delta},
```

where $\Lambda_\delta$ is the dominant combinatorial growth factor that is removed before taking the local generator limit.

Define the renormalized transfer

```math
\widehat T_\delta=
\Lambda_\delta^{-1}T_\delta.
```

Then

```math
\widehat T_\delta h_\delta=
e^{a_\delta\kappa_\delta}h_\delta=
\left(
1+a_\delta\kappa_\delta+o(a_\delta)
\right)h_\delta.
```

Now

```math
\frac{\widehat T_\delta-I}{a_\delta}
```

can have a finite continuum limit.

Thus $\Lambda_\delta$ is not an ignorable normalization. It is one of the principal coefficients that must be extracted from path growth.

# 11. Correct continuum gauge coefficient

The graph gauge action itself is

```math
\alpha_\theta(L_p)=
e^{i\theta|p|}L_p.
```

Its parameter is $\theta$, while

```math
\beta_\delta=\log\lambda_\delta
```

is the KMS/critical growth parameter.

These are related but not automatically the same as continuum time.

Suppose one microscopic edge contributes phase

```math
\vartheta_\delta.
```

Since one edge represents $a_\delta$ continuum-time units, the continuum gauge frequency is

```math
\Omega_\delta=
\frac{\vartheta_\delta}{a_\delta}.
```

Under the KMS-locked choice

```math
\vartheta_\delta=\beta_\delta=\log\lambda_\delta,
```

we get

```math
\Omega_\delta=
\frac{\log\lambda_\delta}{a_\delta}.
```

Therefore a finite continuum gauge rate requires

```math
\log\lambda_\delta=
a_\delta\Omega+o(a_\delta).
```

If instead

```math
\log\lambda_\delta=
\beta_0+a_\delta\Omega+o(a_\delta),
\qquad
\beta_0\ne0,
```

then the phase contains a rapidly oscillating carrier

```math
e^{-i\beta_0\tau N/a_\delta}.
```

One must pass to the interaction picture by removing this carrier. The finite residual rate is then

```math
\Omega=
\lim_{\delta\to0}
\frac{
\log\lambda_\delta-\beta_0
}{
a_\delta
}.
```

Consequently, the continuum master resolvent should contain

```math
Z_q=qI+i\Omega N,
```

not automatically

```math
qI+i(\log\lambda)N.
```

The latter is correct only when the continuum clock is literally primitive step count, $a_\delta=1$, or when a separate gauge parametrization $\theta=\beta\tau$ has been explicitly chosen.

This coefficient stage therefore separates:

```math
\beta_\delta=\log\lambda_\delta=
\text{critical/KMS parameter per edge},
```

from

```math
\Omega=
\text{finite gauge frequency per continuum-time unit}.
```

# 12. Extracting the anomalous clock coefficient

Let $W_\delta$ be the number of primitive edges in one coarse profile block.

Its continuum duration is

```math
J_\delta=a_\delta W_\delta.
```

Let one operational coarse transition represent $c_\delta\downarrow0$ units of operational time. Define

```math
\widehat\psi_\delta(q)=
\mathbb E[e^{-qJ_\delta}].
```

The subordinator exponent is extracted as

```math
\Phi(q)=
\lim_{\delta\to0}
\frac{
1-\widehat\psi_\delta(q)
}{
c_\delta
},
```

locally uniformly for $q\ge0$.

Indeed, after $s/c_\delta$ coarse blocks,

```math
\begin{aligned}
\mathbb E
\exp\left(
-q\sum_{j=1}^{s/c_\delta}J_{\delta,j}
\right)
&=
\widehat\psi_\delta(q)^{s/c_\delta}\\
&\longrightarrow
e^{-s\Phi(q)}.
\end{aligned}
```

For a stable clock,

```math
\Phi(q)=c_\gamma q^\gamma.
```

Both the order $\gamma$ and the coefficient $c_\gamma$ come from the small-$q$ asymptotics of the block-length transform.

# 13. Extracting the hidden-route self-energy

Let $\mathscr H_\delta$ be the resolved route fluctuation space.

Choose the visible projection

```math
P_\delta:
\mathscr H_\delta\to\mathscr H_{\delta,\mathrm{vis}}
```

generated by profile observables, and let

```math
Q_\delta=I-P_\delta
```

be the hidden route sector.

Write the rescaled generator in block form

```math
\mathbb A_\delta=
\begin{pmatrix}
H_\delta&-C_\delta^\ast\\
C_\delta&D_\delta
\end{pmatrix}.
```

The opposite off-diagonal signs make the coupling conservative between visible and hidden sectors while $H_\delta,D_\delta$ provide dissipation.

Eliminating the hidden block gives

```math
\Sigma_\delta(z)=
C_\delta^\ast
(z+D_\delta)^{-1}
C_\delta.
```

Thus the hidden coefficients are matrix elements of the hidden resolvent.

If

```math
H_\delta\to H,
\qquad
D_\delta\to D
```

in strong-resolvent or form sense, and

```math
C_\delta\to C
```

strongly with suitable uniform bounds, then for $\Re z>0$,

```math
\Sigma_\delta(z)
\longrightarrow
C^\ast(z+D)^{-1}C=
\Sigma(z).
```

The hidden memory kernel is

```math
K(\tau)=
C^\ast e^{-\tau D}C.
```

# 14. Extracting the memory exponent

For a visible vector $f$, define the hidden coupling spectral measure

```math
\mu_f(B)=
\left\langle
Cf,E_D(B)Cf
\right\rangle.
```

Suppose

```math
\mu_f([0,\omega])
\sim
\frac{A_f}{\eta}\omega^\eta,
\qquad
\omega\downarrow0,
```

with $0<\eta<1$.

Then

```math
d\mu_f(\omega)
\sim
A_f\omega^{\eta-1}d\omega.
```

Consequently,

```math
\begin{aligned}
\langle f,\Sigma(z)f\rangle
&=
\int_0^\infty
\frac{d\mu_f(\omega)}{z+\omega}\\
&\sim
\frac{\pi A_f}{\sin(\pi\eta)}
z^{\eta-1}
\end{aligned}
```

as $z\to0$ in the appropriate sector.

Thus

```math
\eta=
\text{low-frequency hidden spectral exponent},
```

and

```math
\kappa_f=
\frac{\pi A_f}{\sin(\pi\eta)}
```

is the corresponding memory strength.

# 15. Joint convergence with an anomalous clock

Let $Y_\delta$ be the operational profile process and $D_\delta$ the accumulated block-length process.

The correct proof target is joint convergence:

```math
(Y_\delta,D_\delta)
\Rightarrow
(Y,D).
```

Define the inverse clocks

```math
E_\delta(\tau)=
\inf{s:D_\delta(s)>\tau},
```

```math
E(\tau)=
\inf{s:D(s)>\tau}.
```

Under the continuity conditions for the inverse-map operation, in particular when $D$ is strictly increasing,

```math
E_\delta\Rightarrow E.
```

Then

```math
Y_\delta(E_\delta(\tau))
\Rightarrow
Y(E_\tau).
```

Independence of $Y$ and $D$ gives the scalar inverse-subordination equation. If they remain coupled, one obtains a joint semi-Markov kernel rather than a scalar $\Phi$.

# 16. The corrected continuum master resolvent

After extracting the limits

```math
\mathbb H_h,\qquad
D_h,\qquad
C,\qquad
\Phi,\qquad
\Omega,
```

the continuum gauge variable is

```math
Z_q=qI+i\Omega N.
```

The corrected master resolvent is

```math
\widetilde\Psi(q)=
\frac{\Phi(Z_q)}{Z_q}
\left[
\Phi(Z_q)
+
\mathbb H_h
+
C^\ast
\left(
\Phi(Z_q)+D_h
\right)^{-1}
C
\right]^{-1}
\Psi_0.
```

The old form with

```math
\Omega=\log\lambda
```

is recovered only when the gauge parameter has already been expressed per unit of the chosen continuum clock.

# 17. Complete proof obligations

For a concrete refinement family, the continuum theorem is reduced to proving:

```math
\begin{aligned}
&x_\delta(V_\delta)
\text{ has compactly controlled profile geometry},\\
&h_\delta\to h,\\
&\mathcal L_\delta^h\to\mathcal L^h
\text{ on a core},\\
&\text{the limiting martingale problem is unique},\\
&\Phi_\delta\to\Phi,\\
&H_\delta\to H,\quad D_\delta\to D,\quad C_\delta\to C,\\
&\Omega_\delta\to\Omega
\text{ after carrier renormalization if needed}.
\end{aligned}
```

The coefficients are then:

```math
\begin{aligned}
b_h
&=
\lim
\frac{\mathbb E[\Delta X_\delta]}{a_\delta},\\[1mm]
a_h
&=
\lim
\frac{\mathbb E[\Delta X_\delta\otimes\Delta X_\delta]}{a_\delta},\\[1mm]
\nu_h
&=
\lim
\frac{\text{profile-jump law}}{a_\delta},\\[1mm]
\Phi(q)
&=
\lim
\frac{1-\mathbb E[e^{-qJ_\delta}]}{c_\delta},\\[1mm]
\Sigma(z)
&=
\lim
C_\delta^\ast(z+D_\delta)^{-1}C_\delta,\\[1mm]
\Omega
&=
\lim
\frac{\vartheta_\delta-\vartheta_\delta^{(0)}}{a_\delta}.
\end{aligned}
```
