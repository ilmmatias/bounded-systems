# 1. Orthogonal continuum coordinates

The route projections in `findings-80.md` are centered even polynomials in

```math
t=1-2x.
```

Their natural orthogonal coordinates are the even Legendre polynomials. Let $P_j$ denote the standard Legendre polynomial and define

```math
e_j(x)
=
\sqrt{4j+1}\,P_{2j}(1-2x),
\qquad j\geq1.
```

The functions $e_j$ form an orthonormal basis for the mean-zero even subspace of $L^2([0,1])$.

# 2. Triangular route expansion

For $1\leq j\leq\ell$, set

```math
a_{\ell j}
=
\frac{(4j+1)(2\ell)!}
{(2\ell-2j)!!(2\ell+2j+1)!!}.
```

The standard monomial-Legendre expansion gives

```math
(1-2x)^{2\ell}-\frac1{2\ell+1}
=
\sum_{j=1}^{\ell}
a_{\ell j}P_{2j}(1-2x).
```

Consequently,

```math
h_\ell(x)
=
\sum_{j=1}^{\ell}
\frac{A_\ell a_{\ell j}}{\sqrt{4j+1}}
e_j(x).
```

The coefficient matrix is triangular, and its diagonal entries

```math
a_{\ell\ell}
=
\frac{(4\ell+1)(2\ell)!}{(4\ell+1)!!}
```

are nonzero. The first $L$ route projections therefore span exactly the first $L$ even Legendre modes.

# 3. Independent Ornstein-Uhlenbeck modes

Define the empirical mode process

```math
Z_{j,N}(s)
=
\frac1{\sqrt{m_N(s)}}
\sum_{i=1}^{m_N(s)}e_j(U_i).
```

For every fixed $J$, the vector $(Z_{1,N},\ldots,Z_{J,N})$ converges to independent stationary processes satisfying

```math
dZ_j(s)
=
-\frac{1}{2}Z_j(s)\,ds+dB_j(s).
```

Each coordinate has stationary variance one and covariance

```math
\mathbb E[Z_j(s)Z_k(t)]
=
\delta_{jk}e^{-|s-t|/2}.
```

The leading route process is therefore

```math
X_\ell(s)
=
(\ell+1)
\sum_{j=1}^{\ell}
\frac{A_\ell a_{\ell j}}{\sqrt{4j+1}}
Z_j(s).
```

This representation diagonalizes every finite route covariance matrix and reproduces the closed coefficient formula of `findings-80.md`.

# 4. Rooted star hierarchy

The directed kernel is

```math
\Gamma(x,y)=(y-x)_+.
```

Its conditional incoming and outgoing degrees are

```math
d^-(x)=\frac{x^2}{2},
\qquad
d^+(x)=\frac{(1-x)^2}{2}.
```

The rooted density of an $r$-leaf incoming star is

```math
I_r(x)=\left(\frac{x^2}{2}\right)^r,
```

and the corresponding outgoing-star density is

```math
O_r(x)=\left(\frac{(1-x)^2}{2}\right)^r.
```

In the centered coordinate $t=2x-1$, the sums $I_r+O_r$ have even leading degree $2r$, while the differences $I_r-O_r$ have odd leading degree $2r-1$. The resulting triangular system implies that

```math
1,
I_1,O_1,
\ldots,
I_L,O_L
```

spans every polynomial of degree at most $2L$.

Since polynomials are dense in $L^2([0,1])$, the infinite rooted-star hierarchy recovers the complete latent empirical Gaussian field, not only its even route sector.

# 5. Graph-intrinsic latent coordinate

The degree difference gives

```math
d^-(x)-d^+(x)
=
x-\frac12.
```

Thus the latent coordinate is reconstructed directly from the rooted directed-degree profile:

```math
x
=
\frac12+d^-(x)-d^+(x).
```

If

```math
s(x)=d^-(x)-d^+(x),
```

then the kernel itself is

```math
\Gamma(x,y)
=
\left(s(y)-s(x)\right)_+.
```

Equivalently,

```math
\Gamma(x,y)\Gamma(y,x)=0
```

and

```math
\Gamma(x,y)-\Gamma(y,x)
=
s(y)-s(x).
```

The continuous latent order is therefore not an external hidden coordinate once the complete rooted profile is known. It is a graph-intrinsic function of the expected incoming and outgoing relations.

# 6. Closure and finite forcing

The preceding reconstruction is an exact continuum closure statement. The rooted degree functions determine the coordinate, the coordinate determines the kernel, and the kernel determines the coherent profile and harmonic growth law.

It does not by itself prove absolute finite forcing. A finite forcing family consists of finitely many scalar pattern densities, whereas the reconstruction above uses the full rooted degree functions. The distinction is essential:

```math
\text{functional reconstruction}
\quad\not\Rightarrow\quad
\text{finite scalar selection}.
```

The standalone finite forcibility of this kernel remains unresolved.

Exact symbolic calculations confirm:

- the exact monomial-Legendre coefficients;
- orthonormality of the normalized even modes;
- triangular invertibility of the route expansion;
- the covariance recovered from the independent mode representation;
- polynomial spanning by incoming and outgoing rooted stars;
- exact coordinate and kernel reconstruction from directed degrees.
