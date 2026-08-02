# 1. Gap-generated kernels and quantile coordinates

Let $q:[0,1]\to\mathbb R$ be nondecreasing and define

```math
W_q(u,v)=\bigl(q(v)-q(u)\bigr)_+.
```

We first treat the strictly increasing case and then remove that assumption
by imposing the incoming and outgoing identities together.

The incoming degree is

```math
F(u)
=
d_{W_q}^-(u)
=
\int_0^u\bigl(q(u)-q(v)\bigr)\,dv.
```

The rooted two-step incoming route density is

```math
G(u)
=
\int_0^u
\bigl(q(u)-q(v)\bigr)F(v)\,dv.
```

For the affine gap kernel $q(u)=Lu+c$,

```math
F(u)=\frac{L}{2}u^2,
\qquad
G(u)=\frac{L^2}{24}u^4,
```

so

```math
6G(u)=F(u)^2.
```

# 2. A quantile rigidity theorem

Theorem 1 shows that the affine gap kernel is the only continuous strictly
increasing solution of the quadratic route identity.

## Theorem 1. Quadratic route rigidity

Let $q$ be continuous and strictly increasing. If

```math
6G(u)=F(u)^2
```

for almost every $u\in[0,1]$, then $q$ is affine almost everywhere.

## Proof

Let $dq$ be the Stieltjes measure of $q$, and define

```math
J(u)=\int_0^uF(v)\,dv.
```

The identities

```math
F(u)=u q(u)-\int_0^u q(v)\,dv
```

and

```math
G(u)=q(u)J(u)-\int_0^u q(v)F(v)\,dv
```

give the Stieltjes differentials

```math
dF=u\,dq,
\qquad
dG=J\,dq.
```

Because $q$ is continuous, the ordinary chain rule for continuous functions
of bounded variation gives

```math
d\left(\frac{F^2}{6}\right)
=
\frac{F}{3}\,dF
=
\frac{uF}{3}\,dq.
```

The assumed identity therefore implies

```math
\left(J-\frac{uF}{3}\right)dq=0.
```

Strict increase means that the support of $dq$ is all of $[0,1]$. The
function in parentheses is continuous, so

```math
J(u)=\frac{uF(u)}{3}
```

for every $u$.

Taking Stieltjes differentials once more gives

```math
F\,du
=
\frac13F\,du+
\frac13u\,dF.
```

Hence

```math
u\,dF=2F\,du.
```

The measure $dF$ is therefore absolutely continuous on $(0,1]$, and the
differential equation

```math
u F'(u)=2F(u)
```

has the solution

```math
F(u)=C u^2.
```

Since $dF=u\,dq$, it follows that

```math
dq=2C\,du.
```

Thus $q(u)=2Cu+c$ almost everywhere.

# 3. Fixing translation and scale intrinsically

Suppose the coordinate is not externally supplied but is the signed degree
coordinate

```math
q(u)=s_W(u)=d_W^-(u)-d_W^+(u).
```

For every gap-generated kernel,

```math
s_W(u)=q(u)-\int_0^1q(v)\,dv.
```

Thus the intrinsic coordinate has mean zero. If $q(u)=Lu+c$, this fixes

```math
c=-\frac L2.
```

The total directed edge density is

```math
\int W_q
=
\frac L6.
```

Prescribing edge density $1/6$ therefore fixes $L=1$ and gives

```math
q(u)=u-\frac12,
```

so

```math
W_q(u,v)=(v-u)_+.
```

# 4. Continuous quantile rigidity

The symmetric outgoing quantities are

```math
\overline F(u)
=
\int_u^1\bigl(q(v)-q(u)\bigr)\,dv
```

and

```math
\overline G(u)
=
\int_u^1
\bigl(q(v)-q(u)\bigr)\overline F(v)\,dv.
```

The target also satisfies

```math
6\overline G(u)=\overline F(u)^2.
```

## Theorem 2. Continuous two-sided rigidity

Let $q$ be continuous, nondecreasing, and nonconstant. If both

```math
6G=F^2
```

and

```math
6\overline G=\overline F^2
```

hold almost everywhere, then $q$ is affine.

## Proof

Continuity makes all four functions continuous, so the identities hold
everywhere. Let

```math
D_-(u)=J(u)-\frac{uF(u)}3.
```

The Stieltjes calculation in Theorem 1 shows that $D_-=0$ on the support of
$dq$. On an interval where $q$ is constant, $F$ is constant and

```math
D_-'(u)=\frac{2F(u)}3.
```

A flat interval with increasing support on both sides would therefore force
$F=0$ at its left endpoint, which is possible only before any increase has
occurred. The measure equation $u\,dF=2F\,du$ then shows that a nonconstant
solution cannot begin with a flat interval. Thus the incoming identity allows
at most one terminal flat interval, and $q$ is affine before it.

Applying the same argument to the reversed coordinate $u\mapsto-q(1-u)$
shows that the outgoing identity allows at most one initial flat interval. A
nonconstant function satisfying both identities can have neither. Hence the
support of $dq$ is all of $[0,1]$, and Theorem 1 gives the affine conclusion.

The theorem permits singular continuous coordinates a priori; the Stieltjes
equation forces them to become absolutely continuous. It also rules out
positive-measure twin classes, because these appear as flat intervals of the
quantile.

# 5. Interpretation

The identity $6G=F^2$ is a compositional law. It compares the volume of
two-step incoming factorizations with the square of the one-step incoming
volume. On the regular stratum, that single relation forces the intrinsic
coordinate to have constant density.

A rooted route-composition identity therefore selects the uniform interval
geometry.

Exact symbolic calculations reproduce the affine formulas, the Stieltjes
identities on polynomial test families, and the failure of the quadratic
route relation for finite atomic gap sectors.
