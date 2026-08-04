# 1. Finite constraints and ergodic support

Individual extremal sectors can be selected by finitely many relational
frequencies. The converse question is whether a central law with a continuous
or infinite boundary mixture can also be uniquely selected by finitely many
such frequencies.

The answer is negative. Finite relational forcing permits only finitely many
unresolved extremal phases.

Let $\mathcal C$ be the central simplex and let

```math
\mu
=
\int_{\operatorname{ex}\mathcal C}
\xi\,d\nu_\mu(\xi)
```

be the unique ergodic decomposition of $\mu$.

# 2. Richter-Tchakaloff reduction

The Richter-Tchakaloff theorem states that if $V$ is a finite-dimensional
subspace of $L^1(\Omega,\nu)$, then integration against $\nu$ on $V$ is
represented by a positive atomic measure with at most $\dim V$ atoms.

Apply it on the extremal boundary to

```math
V
=
\operatorname{span}
\{1,f_1,\ldots,f_m\},
```

where the $f_j$ are finite pattern coordinates or finite linear combinations
of them. There are extremal sectors $\xi_1,\ldots,\xi_r$, with

```math
r\leq m+1,
```

and positive weights $\lambda_a$ such that

```math
\int f_j(\xi)\,d\nu_\mu(\xi)
=
\sum_{a=1}^r
\lambda_af_j(\xi_a)
```

for every prescribed coordinate.

# 3. Finite-phase necessity

## Theorem 1. Finite forcing implies finite ergodic support

Suppose $\mu\in\mathcal C$ is uniquely determined among all central measures
by the values of $m$ finite affine pattern coordinates. Then its ergodic
decomposition has at most $m+1$ atoms.

The same conclusion holds when the forcing conditions are arbitrary equations
or inequalities that depend only on those $m$ coordinates.

## Proof

Use the Richter-Tchakaloff reduction to construct

```math
\mu'
=
\sum_{a=1}^r\lambda_a\xi_a
```

with the same $m$ forcing coordinates as $\mu$. The measure $\mu'$ therefore
satisfies every forcing condition. Uniqueness gives $\mu'=\mu$. Uniqueness of
the ergodic decomposition in the central simplex then gives

```math
\nu_\mu
=
\sum_{a=1}^r\lambda_a\delta_{\xi_a}.
```

# 4. Restrictions on diffuse and infinite mixtures

## Corollary 2. Diffuse mixtures are not finitely forcible

A central law whose extremal decomposition is non-atomic cannot be absolutely
selected by finitely many ordinary pattern densities.

## Corollary 3. Infinite atomic mixtures are not finitely forcible

A central law with infinitely many positive-weight extremal components
likewise cannot be absolutely selected by a finite relational profile.

## Corollary 4. Conjugate boundary priors remain infinite constraints

The Dirichlet-beta central laws of `findings-64.md` have finite-dimensional
adaptive posterior states, but their boundary distributions are diffuse.
Unless the prior degenerates to finitely many atoms, no finite set of ordinary
DAG pattern densities absolutely determines the complete annealed central law.

Finite-dimensional predictive updating does not imply absolute finite forcing
of the prior law.

The degree-zero boundary mode of `findings-57.md` is the unresolved extremal
variable. Theorem 1 shows that finite absolute forcing can leave at most a
finite-valued degree-zero variable. A continuously distributed phase requires
an infinite family of relational constraints, even when its posterior is
described by finitely many sufficient statistics.

# 5. Constraint-count bound

If a finitely forced central measure has $r$ extremal phases, every forcing
family of affine coordinates must contain at least

```math
r-1
```

independent coordinates that distinguish their weights. The bound $r\leq m+1$
is sharp at the level of finite-dimensional moment geometry.

Exact quadrature provides a diffuse parameter law and a finite atomic law with
the same prescribed finite moment data. The same calculations recover the
weights of finite mixtures of absolutely forced stochastic two-layer sectors.

# 6. Literature relation

The finite-atomic replacement is the Richter-Tchakaloff theorem for
finite-dimensional spaces of integrable functions. In moment language,
finitely many observations cannot distinguish an arbitrary probability measure
from a finite quadrature rule with the same moments.

Reference:

- K. Schmudgen, *The Moment Problem*, Graduate Texts in Mathematics 277,
  Springer, 2017, Theorem 1.24.
