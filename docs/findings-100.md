# 1. The coordinate measure equation

Let $\nu$ be a compactly supported probability measure on $\mathbb R$ satisfying

```math
6\int_{\mathbb R}
(t-a)_+(b-t)_+\,d\nu(t)
=
(b-a)_+^3
```

for every $a,b$ in the support of $\nu$.

This is the measure equation obtained in `findings-99.md` after the
intrinsic gap and cubic composition defects vanish.

# 2. Coordinate gaps are impossible

Applying the coordinate equation to a pair of support points separated by a
gap gives the following restriction.

## Proposition 1. Connected support

The support of $\nu$ is a compact interval or a singleton.

## Proof

Suppose the support has a gap $(a,b)$ with $a<b$ and both endpoints in the
support. The measure assigns no mass to $(a,b)$. The integrand

```math
(t-a)_+(b-t)_+
```

also vanishes at $t=a$ and $t=b$. Hence the left side of the coordinate
equation is zero, while the right side is $(b-a)^3>0$, a contradiction.

Thus no support gap exists.

# 3. Rigidity on the interior

Assume the support is the nondegenerate interval $[\alpha,\beta]$. Fix the
left endpoint $\alpha$. For every $y\in[\alpha,\beta]$,

```math
\int_{\mathbb R}
(t-\alpha)_+(y-t)_+\,d\nu(t)
=
\frac{(y-\alpha)^3}{6}.
```

Define the left side as $R(y)$. In the sense of distributions on
$(\alpha,\beta)$,

```math
R''(dy)
=
(y-\alpha)\,\nu(dy).
```

The second derivative of the right side is

```math
(y-\alpha)\,dy.
```

Since $y-\alpha>0$ in the open interval, it follows that

```math
\nu\vert_{(\alpha,\beta)}
=
\mathcal L^1\vert_{(\alpha,\beta)}.
```

## Theorem 2. Interior Lebesgue rigidity

Every nondegenerate solution has the form

```math
\nu
=
p\,\delta_\alpha
+
\mathcal L^1\vert_{(\alpha,\beta)}
+
q\,\delta_\beta,
```

where $p,q\geq0$ and

```math
p+q+(\beta-\alpha)=1.
```

No interior atom, singular continuous component, variable density, or
internal support gap is possible.

# 4. Endpoint-atomic ambiguity

The cubic composition identity does not see atoms at the endpoints. If
$a< b$ lie in $[\alpha,\beta]$, endpoint atoms outside the open interval
$(a,b)$ contribute nothing. If one endpoint of the sampled pair is $\alpha$
or $\beta$, the corresponding factor in the integrand vanishes at that atom.

Consequently, every measure of the form in Theorem 2 satisfies the pairwise
identity. A separate scalar constraint is required to remove the two
endpoint masses and the degenerate singleton solution.

# 5. Intrinsic meaning

The two-root path-volume law reconstructs the coordinate measure locally.
Between every two observed coordinate values, the weighted volume of
intermediates is exactly the Euclidean cubic volume. Distributional
differentiation then recovers unit Lebesgue density.

The only undetected information is mass concentrated at the extreme
coordinate values, where no lower or higher intermediate state exists.

On polynomial test functions, exact symbolic calculation confirms the
distributional kernel formula and shows that arbitrary endpoint masses leave
the two-root cubic identity unchanged.
