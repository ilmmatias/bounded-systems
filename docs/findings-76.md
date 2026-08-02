# 1. The half-bigraphon

The transfer theorem of `findings-75.md` becomes explicit for the half-bigraphon

```math
H(x,y)=\mathbf 1_{\{x+y\leq1\}},
\qquad
(x,y)\in[0,1]^2.
```

Its row and column degree functions are

```math
r_H(x)=1-x,
```

and

```math
c_H(y)=1-y,
```

while its edge density is

```math
e_H=\frac12.
```

The rows are nested threshold sets. The kernel is not a finite step bigraphon
because the threshold location varies continuously.

# 2. Finite forcibility as a bigraphon

The polynomial-support argument of Lovasz and Szegedy extends from symmetric
graphons to bigraphons without modification. The left and right variables are
rearranged independently, and the complete bipartite moments are already
bipartite observables.

For a monotone polynomial $p(x,y)$, the signed four-cycle condition forces a
zero-one bigraphon with nested rows and columns. Finitely many
complete-bipartite densities then determine the boundary of its support. Taking

```math
p(x,y)=1-x-y
```

forces the positive support

```math
\{(x,y):x+y\leq1\}.
```

## Proposition 1. Half-bigraphon forcing

The half-bigraphon $H$ is finitely forcible up to independent
measure-preserving transformations of its two coordinate spaces.

Its complete-bipartite densities satisfy

```math
t(K_{a,b},H)
=
\frac{a!b!}{(a+b)!}
```

for positive integers $a,b$. The finite forcing proof needs only bounded
orders determined by the degree of $p$, not the entire moment sequence.

# 3. Explicit balanced completion

Apply the construction of `findings-75.md`. The completed DAGon has four
equal-mass parts $D,A,B,C$ and only three nonzero blocks:

```math
\Gamma(a_x,b_y)
=
\mathbf 1_{\{x+y\leq1\}},
```

the first compensator block is

```math
\Gamma(a_x,c_z)=x,
```

and

```math
\Gamma(d_z,b_y)=y.
```

All other blocks vanish.

The degree pairs are

```math
\delta(D)=\left(0,\frac18\right),
```

whereas

```math
\delta(A)=\left(0,\frac14\right),
```

and

```math
\delta(B)=\left(\frac14,0\right),
```

and

```math
\delta(C)=\left(\frac18,0\right).
```

The directed edge density of the complete kernel is

```math
t(\longrightarrow,\Gamma)
=
\frac{3}{32}.
```

There are no directed two-step paths.

## Theorem 2. An absolutely forced continuum-range DAG sector

The sector represented by $\Gamma$ is absolutely finitely forcible in the full
central DAG boundary.

Its essential range contains the full interval $[0,1]$, because the two
compensator blocks take the values $x$ and $y$. In particular, the selected
kernel is not weakly isomorphic to any finite ordered step kernel.

## Proof

Proposition 1 supplies a finite forcing family for the payload $H$. Theorem 2
of `findings-75.md` transfers that family to the balanced completion. The
formulas on $A\times C$ and $D\times B$ have essential range $[0,1]$, which
is invariant under weak isomorphism. A finite step kernel has finite
essential range, so the completed sector cannot be a finite ordered step
sector.

# 4. Relation to the continuous ordered example

The kernel in `findings-58.md` has the smooth pair probability

```math
w(x,y)=|x-y|.
```

Whether this particular sector is finitely forcible is open. The present
construction proves the logically prior statement that absolute finite
selection is compatible with a continuum of edge probabilities and with
non-step latent structure.

Thus the obstruction identified after `findings-74.md` is not a general
impossibility. The remaining question is kernel-specific: which continuous or
continuum-range acyclic kernels admit finite forcing identities?

# 5. Continuum and harmonic consequences

The sector is extremal and dissociated, so the following consequences hold:

- every finite induced-DAG density converges almost surely to a deterministic
  value;
- every finite family has the support-order fluctuation spectrum of
  `findings-56.md`;
- its complete projective profile reconstructs the harmonic function and up
  transition;
- the finite forcing energy can be used as a terminal potential in the
  extremal selection theorem of the corrected `findings-68.md`.

Exact calculations give the following properties:

- the exact complete-bipartite moment formula for the half-bigraphon;
- nested row supports on finite threshold discretizations;
- the three completed blocks and their exact degree pairs;
- the total edge density $3/32$;
- absence of directed paths of length two;
- growth of the finite discretized payload rank with the discretization order.

# 6. Literature relation

Lovasz and Szegedy prove that the half-graphon is finitely forcible and, more
generally, that positive supports of monotone two-variable polynomials are
finitely forcible. Their proof is bipartite in its operative variables and
yields Proposition 1 after allowing independent rearrangements of the two
sides.

Reference:

- L. Lovasz and B. Szegedy, *Finitely forcible graphons*, Journal of
  Combinatorial Theory, Series B 101 (2011), 269-301, arXiv:0901.0929,
  Theorem 5.1 and Corollary 5.2.
