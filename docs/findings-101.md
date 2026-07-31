# 1. Edge density of the endpoint-atomic family

Let

```math
\nu
=
p\,\delta_\alpha
+
\mathcal L^1\vert_{(\alpha,\beta)}
+
q\,\delta_\beta
```

be a probability measure of the form obtained in `findings-100.md`. Write

```math
D=\beta-\alpha,
\qquad
p+q=1-D.
```

The directed edge density of the associated gap kernel is

```math
e(\nu)
=
\iint (y-x)_+\,d\nu(x)d\nu(y).
```

Translation does not affect this quantity. Setting the interval to $[0,D]$ gives

```math
e(\nu)
=
\frac{D^3}{6}
+
\frac{(p+q)D^2}{2}
+
pqD.
```

The three terms are respectively the continuous--continuous, endpoint--continuous, and lower-endpoint--upper-endpoint contributions.

# 2. The maximal density at fixed interval length

Since

```math
pq\leq\frac{(p+q)^2}{4}
=
\frac{(1-D)^2}{4},
```

one obtains

```math
e(\nu)
\leq
\frac{D^3}{6}
+
\frac{(1-D)D^2}{2}
+
\frac{D(1-D)^2}{4}
=
\frac{3D-D^3}{12}.
```

The difference from the target density is

```math
\frac16-\frac{3D-D^3}{12}
=
\frac{(1-D)^2(D+2)}{12}.
```

For $0\leq D\leq1$, equality is possible only when $D=1$.

## Proposition 1. Endpoint atoms are excluded

If the cubic composition identity holds and

```math
e(\nu)=\frac16,
```

then

```math
D=1,
\qquad
p=q=0.
```

Hence $\nu$ is Lebesgue measure on an interval of length one.

The singleton solution has edge density zero and is excluded simultaneously.

# 3. Fixing translation intrinsically

For every directed kernel,

```math
\int s_W\,d\mu
=
\int d_W^-\,d\mu
-
\int d_W^+\,d\mu
=0.
```

Thus the intrinsic coordinate distribution has mean zero. The unique length-one interval with mean zero is

```math
\left[-\frac12,\frac12\right].
```

Therefore

```math
\nu
=
\mathcal L^1\vert_{[-1/2,1/2]}.
```

# 4. The standalone gap kernel

Let

```math
u(x)=s_W(x)+\frac12.
```

The map $u$ pushes $\mu$ forward to uniform measure on $[0,1]$. The intrinsic gap reconstruction gives

```math
W(x,y)
=
\bigl(u(y)-u(x)\bigr)_+.
```

Consequently, $W$ is weakly isomorphic to

```math
A(r,s)=(s-r)_+.
```

The scale, translation, coordinate distribution, and edge law have all been reconstructed from graph-intrinsic finite constraints.

Exact symbolic calculation gives the edge-density decomposition and the factorization

```math
\frac16-e_{\max}(D)
=
\frac{(1-D)^2(D+2)}{12}.
```
