# 1. A compositional three-layer sector

The standalone kernel $(y-x)_+$ can be placed in a sector where it is forced
to arise from composition rather than assigned as an unrelated block.

Take three equal-mass decorated parts

```math
L_0,
\qquad
L_1,
\qquad
L_2,
```

each carrying a coordinate in $[0,1]$. Define the nonzero blocks by

```math
\Gamma_{01}(x,y)=\mathbf 1_{\{x<y\}},
```

the second adjacent block is

```math
\Gamma_{12}(y,z)=\mathbf 1_{\{y<z\}},
```

and

```math
\Gamma_{02}(x,z)=(z-x)_+.
```

All within-layer and backward blocks vanish. The sector is acyclic and
contains genuine two-step routes through $L_1$.

# 2. Alignment of the order coordinates

Each adjacent block is a bipartite half-kernel and is finitely forcible
relative to its two decorated parts. For the first block, the normalized
column degree of $y\in L_1$ is

```math
c_{01}(y)=y.
```

For the second block, the normalized row degree is

```math
r_{12}(y)=1-y.
```

The rooted identity

```math
c_{01}(y)+r_{12}(y)=1
```

aligns the two a priori independent half-kernel coordinates on the shared
middle part.

Indeed, after forcing the first block one may write its middle coordinate
as $y$. The second forced half-kernel may use another measure-preserving
coordinate $\phi(y)$, in which case its row degree is $1-\phi(y)$. The
displayed identity gives $\phi(y)=y$ almost everywhere.

# 3. The shortcut as a route-density function

Because the middle part has ambient mass $1/3$, the two-labelled path
density through $L_1$ is

```math
P_{02}(x,z)
=
\int_{L_1}
\Gamma_{01}(x,y)
\Gamma_{12}(y,z)\,d\mu(y)
=
\frac13(z-x)_+.
```

Set

```math
R(x,z)=\Gamma_{02}(x,z)-3P_{02}(x,z).
```

A direct integral of $R(x,z)^2$ would involve a repeated copy of the same
continuum edge and is not, by itself, an ordinary simple-DAG density. The
correct simple-pattern defect is the one-sided Gram defect

```math
\mathcal G(R)
=
\int_{L_0^2}
\left[
 \int_{L_2}
 R(x,z)R(x',z)\,d\mu(z)
\right]^2
\,d\mu(x)d\mu(x').
```

This quantity is nonnegative and vanishes if and only if $R=0$ almost
everywhere. Indeed, the inner kernel is the integral kernel of the positive
operator $RR^*$, so $\mathcal G(R)=0$ implies $RR^*=0$ and hence $R=0$.
Therefore

```math
\mathcal G(R)=0
\quad\Longleftrightarrow\quad
\Gamma_{02}(x,z)=(z-x)_+
```

almost everywhere.

After expanding $R$, the Gram defect is a finite quantum-DAG expression
involving direct edges and two-step paths with shared labelled endpoints.
The outer square introduces independent copies of the terminal endpoint, so
no parallel copy of one simple edge is required. After label forgetting, the
defect becomes a finite linear combination of ordinary decorated simple-DAG
densities.

# 4. Relative finite forcing theorem

Collecting the alignment identity and the Gram defect with the two adjacent
half-kernel families gives the following relative forcing statement.

## Theorem 1. Decorated compositional forcing

Within the class of digraphons equipped with the three parts $L_0,L_1,L_2$,
the preceding sector is finitely forcible by:

1. the three part masses and the zero-block constraints;
2. finite forcing families for the two adjacent half-kernel blocks;
3. the middle-coordinate alignment identity;
4. the shortcut Gram defect.

## Proof

The adjacent forcing families identify both half-kernels up to independent
measure-preserving coordinate changes. The alignment identity makes the two
coordinates on $L_1$ agree. The outer coordinates are then fixed by the row
degree of $\Gamma_{01}$ and the column degree of $\Gamma_{12}$. The shortcut
defect forces the remaining forward block to equal the normalized composition
of the adjacent blocks. Every nonzero block is therefore weakly isomorphic to
the displayed target.

The forcing is relative to the prescribed parts $L_0,L_1,L_2$. Two questions
remain open: whether the parts can be eliminated without an auxiliary
graph-intrinsic tagging completion, and whether the standalone one-part kernel
of `findings-58.md` is absolutely finitely forcible.

# 5. Foundational interpretation

In this sector, the stochastic shortcut law

```math
(z-x)_+
```

is not independently postulated. It is the measure of all primitive two-step
factorizations

```math
x\longrightarrow y\longrightarrow z.
```

The derived block simultaneously supplies an operational transition
probability, interval length on comparable endpoints, the second power of the
primitive order operator, and the base of the higher path-volume hierarchy.

# 6. Scope of absolute forcing

Known necessary conditions do not decide whether the standalone one-part
kernel of `findings-58.md` is absolutely finitely forcible. The kernel has
infinite operator rank, so it is not excluded by the theorem that a finitely
forcible non-step graphon must have infinite rank. It is piecewise polynomial
rather than a single nonconstant polynomial, so the nonforcibility result for
polynomial graphons does not apply directly.

Exact calculations give the following results for the compositional sector:

- the adjacent half-kernel degree coordinates;
- exact coordinate alignment and positivity of a misalignment defect;
- the normalized two-step path integral;
- vanishing of the shortcut defect at the target;
- positivity for explicit incorrect shortcut blocks.

# 7. Literature relation

The adjacent threshold blocks use the finite forcing of monotone polynomial
support kernels developed by Lovasz and Szegedy. Their necessary-condition
results also show that finitely forcible graphons are either stepfunctions or
have infinite rank, and that nonconstant polynomial graphons are not finitely
forcible. These results delimit but do not settle the standalone
piecewise-polynomial kernel considered here.

Reference:

- L. Lovasz and B. Szegedy, *Finitely forcible graphons*, Journal of
  Combinatorial Theory, Series B 101 (2011), 269-301, arXiv:0901.0929.
