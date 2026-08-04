# 1. Degree balancing and observational order

The balanced completion of `findings-75.md` makes the ambient parts
graph-intrinsic by fixing their total directed degrees. This also creates a
separation between low-order observables and the internal payload.

Let $U$ be any payload bigraphon with edge density

```math
e=e_U,
```

and let $\Gamma_U$ be its balanced completion. Define the unoriented edge
indicator on a sampled pair by

```math
B_{12}
=
\Gamma_U(X_1,X_2)+\Gamma_U(X_2,X_1).
```

The two terms cannot both be nonzero because the completion is source-sink.

# 2. Edge mean

The three nonzero blocks contribute

```math
\frac{e}{16},
\qquad
\frac{1-e}{16},
\qquad
\frac{1-e}{16}
```

to the directed kernel integral. Hence the probability that an unordered
sampled pair carries an edge is

```math
\theta_E
=
\mathbb E[B_{12}]
=
\frac{2-e}{8}.
```

For a vertex in $D$ or $C$, the conditional incident-edge probability is

```math
q_-(x)=\frac{1-e}{4}.
```

For a vertex in $A$ or $B$, it is

```math
q_+(x)=\frac14.
```

The one-vertex projection therefore takes only the two values

```math
-\frac e8
\qquad\text{and}\qquad
\frac e8,
```

each on a set of mass $1/2$.

# 3. Exact stable edge coefficients

The one-vertex projection norm is

```math
\sigma_{E,1}^2
=
\frac{e^2}{64}.
```

Since the edge statistic has two vertex positions, the overlap-one coefficient
is

```math
C_1(E,E)
=
4\sigma_{E,1}^2
=
\frac{e^2}{16}.
```

The pair indicator is Bernoulli with mean $\theta_E$, so

```math
\operatorname{Var}(B_{12})
=
\theta_E(1-\theta_E).
```

Removing the two one-vertex projections gives

```math
\sigma_{E,2}^2
=
\theta_E(1-\theta_E)
-
\frac{e^2}{32}.
```

Thus

```math
C_2(E,E)
=
2\theta_E(1-\theta_E)
-
\frac{e^2}{16}.
```

For $n\leq m$, the exact nested covariance is

```math
\operatorname{Cov}(E_n,E_m)
=
\frac{e^2}{16m}
+
\frac{
 2\theta_E(1-\theta_E)-e^2/16
}{m(m-1)}.
```

The logarithmic edge process has the rate-one-half Ornstein-Uhlenbeck limit

```math
dX_E(s)
=
-\frac12X_E(s)\,ds
+
\frac e4\,dW(s),
```

with stationary variance $e^2/16$.

For the half-bigraphon completion, $e=1/2$, so

```math
\theta_E=\frac3{16},
```

the overlap-one coefficient is

```math
C_1(E,E)=\frac1{64},
```

and

```math
C_2(E,E)=\frac{37}{128}.
```

# 4. Universal low-order law

The displayed coefficients depend only on the payload edge density $e$, not
on the shape of $U$.

Consequently, two nonisomorphic payloads with the same edge density have
identical:

- completed edge means;
- one-vertex edge projections;
- exact edge variances and nested covariances;
- logarithmic edge Ornstein-Uhlenbeck limits.

Their difference first becomes visible through higher relational patterns
inside the payload block, such as complete bipartite densities, threshold
defects, or other members of a finite forcing family.

## Proposition 1. Selection can occur above hydrodynamic order

There are absolutely distinguishable balanced completions whose edge
hydrodynamics and edge fluctuation coefficients agree exactly.

## Proof

Choose two finitely forcible payloads with the same edge density but different
higher bipartite pattern profiles. The formulas above show equality of all
edge coefficients. The payload forcing coordinates distinguish the completed
sectors by Theorem 2 of `findings-75.md`.

# 5. Separation of coefficient and sector information

The result separates three levels of information:

```math
\text{edge density}
\quad\subsetneq\quad
\text{stable edge coefficient data}
\quad\subsetneq\quad
\text{finite forcing profile}.
```

In the balanced family, the first two levels collapse to the single scalar
$e$. The full selected sector can nevertheless contain a continuum of rooted
profiles and infinite operator rank.

Thus a macroscopic coefficient field may be stable and universal while
failing to identify the underlying boundary sector. Stable coefficients solve
the continuum problem for the chosen observables; they do not by themselves
solve the selection problem.

This is an explicit version of the distinction emphasized in
`findings-47.md`: continuum convergence and harmonic-sector selection are
logically separate.

Exact calculations confirm:

- the exact formulas for $\theta_E$, $C_1$, and $C_2$;
- agreement with direct finite-payload overlap calculations;
- equality of the completed edge coefficients for constant and checkerboard
  payloads of equal density;
- inequality of a class-restricted $K_{2,2}$ density for those same payloads.
