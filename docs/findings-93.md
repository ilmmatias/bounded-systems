# 1. Correction to the shortcut forcing observable

The compositional sector of `findings-83.md` used the formal defect

```math
\int
\left(
\Gamma_{02}-cP_{02}
\right)^2.
```

Analytically, this vanishes exactly at the desired shortcut. However, its
expansion contains the square of one direct edge value. In the simple-DAG
density algebra, duplicating the same labelled edge does not create a second
independent factor. The formal $L^2$ defect is therefore not directly an
ordinary simple-DAG observable.

It would be valid in a directed multigraph observable algebra with parallel edge
probes, but the central branching theory from `findings-46.md` onward uses
simple DAGs. The proof requires a simple-pattern replacement.

# 2. One-sided Gram correction

Let

```math
R(x,z)=\Gamma_{02}(x,z)-cP_{02}(x,z),
```

where $c=3$ in the decorated sector and $c=36$ in its tagged completion. Define

```math
G_R(x,x')
=
\int R(x,z)R(x',z)\,d\mu(z)
```

and

```math
\mathcal G(R)
=
\int G_R(x,x')^2
\,d\mu(x)d\mu(x').
```

The kernel $G_R$ represents the positive operator $RR^*$. Hence

```math
\mathcal G(R)
=
\|RR^*\|_{\mathrm{HS}}^2
\geq0,
```

and

```math
\mathcal G(R)=0
\quad\Longleftrightarrow\quad
R=0.
```

The corrected defect therefore forces exactly the same compositional identity.

# 3. Realization by simple DAG patterns

The Gram defect has a finite simple-pattern expansion.

The kernel $G_R(x,x')$ is a linear combination of terms in which:

- two direct shortcut edges share a terminal endpoint;
- one shortcut edge and one two-step path share a terminal endpoint;
- two two-step paths share a terminal endpoint.

Squaring $G_R$ introduces a second independently sampled terminal endpoint.
Every edge occurrence then belongs to a distinct pair of sampled vertices. No
parallel copy of a single labelled edge is needed.

Consequently, after expanding the path integrals and forgetting the labels,
$\mathcal G(R)$ is a finite linear combination of decorated simple-DAG
homomorphism densities. The tagged-compensated transfer of `findings-84.md`
then converts it into an uncolored finite constraint.

# 4. Corrected theorem status

With the Gram defect substituted for the direct $L^2$ defect:

1. the relative compositional forcing theorem of `findings-83.md` remains valid;
2. the tagged-compensated absolute completion of `findings-85.md` remains valid;
3. the graph-intrinsic route geometry and terminal selection statements of
   `findings-86.md` remain valid.

The correction changes only the observable used to prove shortcut equality; the
selected kernel and the compositional identity are unchanged.

# 5. Finite-dimensional consistency identities

For the zero shortcut, $R=-A$. The corrected defect is

```math
\mathcal G(-A)
=
\|AA^*\|_{\mathrm{HS}}^2
=
\frac{11}{1680}.
```

For a shortcut equal to half of the target,

```math
R=-\frac12A,
```

and therefore

```math
\mathcal G(R)
=
\frac1{16}\mathcal G(-A)
=
\frac{11}{26880}.
```

Both are strictly positive, while the target defect vanishes.

The corrected finite calculation uses the Gram defect in place of the formal
direct-edge square and reproduces the compositional and completion identities.
