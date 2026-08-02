# 1. Finite selection and state complexity

`findings-60.md` proves that the entire central boundary has no universal
continuous finite-dimensional coordinate system. The absolutely forced kernel
of `findings-76.md` establishes a complementary point: even one sector
isolated by finitely many relational equations can have a genuinely
infinite-dimensional internal kernel structure.

Let $\Gamma$ denote the completed half-bigraphon sector. For $x\in[0,1]$,
write $a_x$ for the corresponding point in the part $A$.

# 2. Continuum of rooted profiles

The outgoing row of $a_x$ has two nonzero pieces:

```math
\Gamma(a_x,b_y)
=
\mathbf 1_{\{y\leq1-x\}},
```

and

```math
\Gamma(a_x,c_z)=x.
```

For $x,x'\in[0,1]$, their $L^1$ distance in the full probability space is

```math
\begin{aligned}
\|\Gamma(a_x,\cdot)-\Gamma(a_{x'},\cdot)\|_1
&=
\frac14
\int_0^1
\left|
 \mathbf 1_{\{y\leq1-x\}}
 -
 \mathbf 1_{\{y\leq1-x'\}}
\right|dy\\
&\quad+
\frac14\int_0^1|x-x'|\,dz\\
&=
\frac12|x-x'|.
\end{aligned}
```

The map

```math
x\longmapsto\Gamma(a_x,\cdot)
```

is therefore an isometric embedding of an interval up to the factor $1/2$.
The typical-vertex space contains a continuum and cannot collapse to finitely
many graph-intrinsic types.

# 3. Infinite operator rank

The half-bigraphon block already has infinite rank. For distinct thresholds

```math
0<t_1<\cdots<t_m<1,
```

the functions

```math
\mathbf 1_{[0,t_1]},\ldots,
\mathbf 1_{[0,t_m]}
```

are linearly independent. Since the rows of $H$ contain every threshold
indicator $\mathbf 1_{[0,1-x]}$, the associated Hilbert-Schmidt operator has
arbitrarily large finite-dimensional row spans and hence infinite rank.

The full completed DAG operator contains this block as a compression. It also
has infinite rank.

## Theorem 1. Finite relational forcing does not imply finite-dimensional state

There exists an extremal central DAG sector that is absolutely determined by
finitely many ordinary finite-DAG densities but whose kernel has:

- continuum essential range;
- a continuum of pairwise distinct rooted row profiles;
- infinite Hilbert-Schmidt operator rank.

The completed half-bigraphon sector is one such example.

# 4. Selector complexity and state complexity

The theorem separates two notions that can otherwise be conflated.

A finite selector means that one point of the central boundary is the unique
zero of finitely many relational functionals. It does not mean that the
selected point admits finitely many latent vertex types, a finite-rank kernel,
or a finite-dimensional complete predictive coordinate.

The exact projective profile remains the canonical state of `findings-59.md`.
Finite forcing supplies a finite address for one boundary point, not a finite
parametrization of all conditional structure inside that point.

This also explains why finite forcing is compatible with the noncompression
theorem of `findings-60.md`. A finite set of equations can isolate a point in
an infinite-dimensional compact space even when no finite coordinate map embeds
the whole space.

# 5. Process-level consequence

The internal kernel complexity does not obstruct finite-observable continuum
laws. Every fixed finite family of DAG densities has exact support coefficients
and stable logarithmic process limits.

The coefficients are integrals over the continuum rooted-profile space rather
than sums over finitely many layers. This is the same distinction already
visible in `findings-58.md`, now combined with absolute finite selection.

Increasing threshold discretizations give the following finite-dimensional
results:

- the payload matrix has full rank at every finite discretization order
  considered;
- the discrete rooted-row distance agrees with the
  threshold-plus-compensator formula;
- the number of distinct rooted profiles increases with the discretization
  order.
