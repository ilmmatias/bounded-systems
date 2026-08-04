# 1. Two-sided active-component equation

Let $q$ be a general nondecreasing quantile and retain the functions

```math
F(u)=\int_0^u\bigl(q(u)-q(v)\bigr)\,dv,
```

and

```math
G(u)=\int_0^u\bigl(q(u)-q(v)\bigr)F(v)\,dv,
```

with outgoing counterparts $\overline F$ and $\overline G$. Suppose both
rooted identities hold:

```math
6G=F^2,
\qquad
6\overline G=\overline F^2.
```

Define

```math
J(u)=\int_0^uF(v)\,dv,
\qquad
K(u)=\int_u^1\overline F(v)\,dv.
```

On any open interval on which $q$ is continuous and the support of $dq$ is
full, the Stieltjes calculations give

```math
J=\frac{uF}{3},
\qquad
K=\frac{(1-u)\overline F}{3}.
```

# 2. The centered linear differential equation

Set

```math
M=J+K.
```

Since

```math
M'(u)=F(u)-\overline F(u)=q(u)-\int_0^1q(v)\,dv,
```

we may center $q$ so that its mean is zero and write $M'=q$.

On an active interval,

```math
3M=uF+(1-u)\overline F.
```

Differentiating and using

```math
F'=u q',
\qquad
\overline F'=-(1-u)q'
```

gives

```math
3q
=
q+(2u-1)q'.
```

Hence

```math
(2u-1)q'(u)=2q(u).
```

## Proposition 1. Common-center affine pieces

On every diffuse continuity component,

```math
q(u)=c_I(2u-1)
```

for some constant $c_I\geq0$ depending a priori on the component.

Thus all active pieces pass through the same central zero $u=1/2$. The
identities do not permit independently translated affine components.

# 3. Jump conditions

Let $q$ have an upward jump $\Delta q$ at $u$. The incoming identity gives

```math
J(u)
=
\frac{uF(u-)}3+
\frac{u^2\Delta q}{6},
```

while the outgoing identity gives

```math
K(u)
=
\frac{(1-u)\overline F(u+)}3+
\frac{(1-u)^2\Delta q}{6}.
```

Equivalently, if

```math
D_-(u)=J(u)-\frac{uF(u)}3
```

and

```math
D_+(u)=K(u)-\frac{(1-u)\overline F(u)}3,
```

then the one-sided values at a jump satisfy exact sign-flip relations of
magnitude proportional to $\Delta q$.

If active support accumulates immediately to the left of the jump, then the
incoming relation has $D_-(u-)=0$, forcing $\Delta q=0$. If active support
accumulates immediately to the right, the outgoing relation similarly forces
$\Delta q=0$.

## Proposition 2. Flat buffers around every jump

Every nonzero jump of a solution must be preceded and followed by nontrivial
flat quantile intervals.

A gap in the coordinate support therefore requires positive-mass twin
classes on both sides of the gap.

# 4. Structure of a possible counterexample

The preceding results combine with `findings-97.md` as follows:

1. a finite atomic coordinate distribution is impossible;
2. a continuous coordinate is affine;
3. every diffuse active component is a centered affine piece;
4. every nonzero jump requires flat buffers on both sides.

Consequently, any non-affine solution of the two-sided composition equations
must be a hybrid object containing diffuse centered-affine pieces,
positive-length flat intervals, and jump discontinuities. It cannot be purely
continuous or purely finite atomic.

Two cases remain open under the present identities: a finite hybrid
arrangement with one or more buffered jumps, and an infinite accumulating
arrangement.

# 5. Buffered-jump conjecture

Proposition 2 restricts the unresolved case of `findings-97.md` to buffered
jumps.

## Conjecture 3. Exclusion of buffered jump structures

There is no nonconstant nondecreasing quantile with any nonzero buffered
jump that satisfies both rooted composition identities almost everywhere.

A proof of the conjecture would complete absolute finite forcing of the
standalone gap kernel by the four constraints of `findings-96.md`.

# 6. Exact restrictions on jump geometry

Exact symbolic calculations give the active-component differential equation,
the jump formulas, and the impossibility of an unbuffered jump between
affine active components.
