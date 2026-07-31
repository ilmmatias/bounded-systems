# 1. Finite-type competitors are excluded

The unresolved part of `findings-96.md` concerns singular distributions of the intrinsic coordinate. The first possible competitors are finite atomic distributions, corresponding to finite ordered layers with edge probability equal to the difference of their coordinate values.

Let

```math
q_1<q_2<\cdots<q_m
```

have positive masses $p_1,\ldots,p_m$. The induced gap kernel is

```math
W(i,j)=(q_j-q_i)_+.
```

At the second coordinate value $q_2$, the incoming degree is

```math
d^-(q_2)=p_1(q_2-q_1)>0.
```

However, there is no intermediate coordinate strictly between $q_1$ and $q_2$. The rooted incoming two-step route density is therefore

```math
P^-(q_2)=0.
```

Hence

```math
6P^-(q_2)-d^-(q_2)^2
=
-p_1^2(q_2-q_1)^2
<0.
```

## Proposition 1. No nontrivial finite atomic solution

No nonzero finite atomic gap-generated sector satisfies the rooted composition identity

```math
6P^-=\left(d^-\right)^2
```

almost everywhere.

Thus every nontrivial finite ordered-layer competitor is excluded before any cyclic higher-pattern constraint is used.

# 2. The singular problem is narrower than finite-step ambiguity

A remaining counterexample, if one exists, must have coordinate values accumulating immediately above the essential minimum. The same conclusion holds after restricting to any positive-mass component: there can be no second isolated coordinate level.

The continuous case is settled by Theorem 2 of `findings-95.md`: singular continuous growth and flat quantile intervals are both forced away. The unresolved possibilities therefore require genuine gaps in the essential coordinate support, represented by jump discontinuities of the monotone quantile. They may be accompanied by diffuse or atomic mass on the remaining components.

This is substantially narrower than the full graphon forcing problem.

# 3. Quantile form of the singular equation

For a general nondecreasing quantile $q$, define

```math
F(u)=\int_0^u\bigl(q(u)-q(v)\bigr)\,dv
```

and

```math
G(u)=\int_0^u
\bigl(q(u)-q(v)\bigr)F(v)\,dv.
```

The exact remaining equation is

```math
6G(u)=F(u)^2
```

for almost every $u$. Its outgoing dual is obtained by reversing the interval.

On every continuity component, the two-sided Stieltjes argument of `findings-95.md` forces $q$ to be affine and excludes flat intervals. Any remaining solution must therefore join affine components across jump discontinuities while preserving both rooted identities.

# 4. A sharpened conjecture

The calculations suggest the following precise statement.

## Conjecture 2. Absolute quantile rigidity

Let $q$ be nondecreasing and nonconstant. If both the incoming and outgoing rooted composition identities hold almost everywhere, then $q$ is affine almost everywhere.

If this conjecture is proved, the four finite constraints of `findings-96.md` absolutely force the standalone gap kernel in the full acyclic central boundary.

The conjecture is now a one-dimensional Stieltjes rigidity problem rather than an unrestricted two-variable graphon problem.

# 5. Relation to finite forcibility

Lovász and Szegedy showed that finite forcibility can be expressed through vanishing quantum-graph identities and that finitely forcible graphons are exceptional. The present reduction identifies a concrete candidate identity rather than appealing only to general rarity.

The gap kernel has infinite rank, so the finite-rank obstruction does not apply. The new result instead isolates the exact singular mechanism that must be controlled to complete a direct forcing theorem.

Enumeration of finite rational atomic sectors gives the exact second-level obstruction, the affine solution, and the incoming and outgoing defects for non-affine monotone polynomial quantiles.
