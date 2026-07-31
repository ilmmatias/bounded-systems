# 1. Primitive order kernel

Let

```math
K(x,y)=\mathbf 1_{\{x<y\}}
```

be the strict order kernel on $[0,1]$. As an integral operator,

```math
(Kf)(x)=\int_x^1f(y)\,dy.
```

The stochastic distance kernel of `findings-58.md` is

```math
A(x,y)=(y-x)_+.
```

It is not introduced independently: it is the second operator power of the primitive order relation.

## Proposition 1. Two-step route volume

The two-step route operator is the second compositional power of the order kernel:

```math
A=K^{\circ2}.
```

## Proof

For fixed $x,y$,

```math
K^{\circ2}(x,y)
=
\int_0^1
\mathbf 1_{\{x<z\}}
\mathbf 1_{\{z<y\}}\,dz
=
\lambda\{z:x<z<y\}
=
(y-x)_+.
```

The transition amplitude is therefore the measure of admissible intermediate relational states.

# 2. Complete path-volume algebra

## Theorem 2. Volterra powers

For every integer $m\geq1$,

```math
K^{\circ m}(x,y)
=
\mathbf 1_{\{x<y\}}
\frac{(y-x)^{m-1}}{(m-1)!}.
```

## Proof

The statement is immediate for $m=1$. If it holds at $m$, then

```math
\begin{aligned}
K^{\circ(m+1)}(x,y)
&=
\int_x^y
\frac{(z-x)^{m-1}}{(m-1)!}\,dz\\
&=
\frac{(y-x)^m}{m!}
\end{aligned}
```

when $x<y$, and both sides vanish otherwise.

The kernels close under composition:

```math
K^{\circ m}\circ K^{\circ n}
=
K^{\circ(m+n)}.
```

The factorial is the simplex volume of the ordered intermediate points.

# 3. Route kernels in the distance sector

Since $A=K^{\circ2}$,

```math
A^{\circ\ell}
=
K^{\circ2\ell},
```

and hence

```math
A^{\circ\ell}(x,y)
=
\mathbf 1_{\{x<y\}}
\frac{(y-x)^{2\ell-1}}{(2\ell-1)!}.
```

Integrating the endpoint kernel gives the labeled $\ell$-edge path density

```math
\left\langle1,A^{\circ\ell}1\right\rangle
=
\frac1{(2\ell+1)!}.
```

This is exactly the path density used in `findings-80.md`.

# 4. Emergent interval geometry

Define the symmetrized operational separation

```math
\delta(x,y)
=
A(x,y)+A(y,x).
```

Then

```math
\delta(x,y)=|x-y|.
```

It follows directly that $\delta$ is a metric on the latent quotient. For ordered triples $x<y<z$,

```math
A(x,z)=A(x,y)+A(y,z).
```

Thus interval length is reconstructed from the volume of two-step factorizations of the primitive order relation. The higher route kernels satisfy

```math
K^{\circ m}(x,y)
=
\frac{\delta(x,y)^{m-1}}{(m-1)!}
```

on comparable pairs.

Together with `findings-81.md`, this geometry is graph-intrinsic: the coordinate difference is recoverable from directed degree profiles, so $\delta$ does not require an externally supplied embedding of the vertices into an interval.

# 5. All-path resolvents

The complete primitive-route generating kernel is

```math
\sum_{m=1}^{\infty}
t^mK^{\circ m}(x,y)
=
\mathbf 1_{\{x<y\}}
 t e^{t(y-x)}.
```

For the distance kernel,

```math
\sum_{\ell=1}^{\infty}
z^\ell A^{\circ\ell}(x,y)
=
\mathbf 1_{\{x<y\}}
\sqrt z\,
\sinh\!\left(\sqrt z\,(y-x)\right).
```

The scalar path-generating function is

```math
\left\langle
1,(I-zA)^{-1}1
\right\rangle
=
\sum_{\ell=0}^{\infty}
\frac{z^\ell}{(2\ell+1)!}
=
\frac{\sinh\sqrt z}{\sqrt z}.
```

The apparent singularity at $z=0$ is removable.

# 6. Quasinilpotence and entire closure

The Hilbert-Schmidt norm satisfies

```math
\left\|K^{\circ m}\right\|_{\mathrm{HS}}^2
=
\frac1{((m-1)!)^2(2m-1)(2m)}.
```

Its factorial decay implies

```math
\lim_{m\to\infty}
\left\|K^{\circ m}\right\|^{1/m}=0.
```

The Volterra operator therefore has spectral radius zero. The same holds for $A=K^{\circ2}$. Their path resolvents are entire operator-valued functions.

This supplies an exact example in which an infinite route algebra closes without introducing a separate local evolution equation. The order relation, its compositional volumes, the induced metric, and the all-path resolvent belong to one operator structure.

Exact symbolic calculations confirm:

- the convolution formula for the Volterra powers;
- composition closure for independent route lengths;
- the path-density factorials;
- the degree-coordinate and metric identities;
- the coefficients of both all-path generating kernels;
- the Hilbert-Schmidt norm formula.
