# 1. Absolute finite forcing of the standalone distance sector

Combine the intrinsic gap Gram defect of `findings-94.md` with the cubic composition defect of `findings-99.md`.

## Theorem 1. Absolute finite forcing

Let $W$ be an acyclic directed kernel. Suppose

```math
\mathcal G_{\mathrm{gap}}(W)=0,
```

the compositional Gram defect satisfies

```math
\mathcal G_{\mathrm{comp}}(W)=0,
```

and

```math
\iint W(x,y)\,d\mu(x)d\mu(y)=\frac16.
```

Then $W$ is weakly isomorphic to

```math
A(x,y)=(y-x)_+
```

on $[0,1]$.

## Proof

The first Gram constraint and acyclicity give

```math
W(x,y)=\bigl(s_W(y)-s_W(x)\bigr)_+.
```

The second Gram constraint gives the coordinate measure equation of `findings-99.md`. By `findings-100.md`, the signed degree distribution is unit Lebesgue measure on the interior of a compact interval, with possible atoms only at its endpoints. By `findings-101.md`, edge density $1/6$ forces the interval length to be one and both endpoint masses to vanish. The signed coordinate has mean zero, so its distribution is uniform on $[-1/2,1/2]$. The resulting kernel is the standalone gap kernel up to a measure-preserving representation.

# 2. Finiteness in the ordinary pattern algebra

The theorem uses three scalar constraints:

1. the intrinsic antisymmetric gap Gram defect;
2. the intrinsic cubic composition Gram defect;
3. the one-edge density.

Both Gram defects expand into finite linear combinations of ordinary simple-DAG homomorphism densities. The forcing theorem therefore requires neither decorated parts nor an auxiliary completion.

This is absolute finite selection in the full acyclic central boundary, rather than selection relative to a regularity stratum or a prescribed parametric family.

# 3. Relation to the earlier rooted selector

The regular forcing system of `findings-96.md` used incoming and outgoing rooted quadratic identities. Those identities remain valid and retain their interpretation as local composition laws, but their unresolved buffered-jump analysis is no longer needed for finite selection.

The stronger two-root cubic law directly observes a missing interval of intermediate coordinate values. It reduces the possible coordinate measures to a one-parameter endpoint-atomic family, and the edge density then removes that final ambiguity.

The original Conjecture 3 of `findings-98.md` remains a separate one-dimensional rigidity question about the weaker rooted system. The absolute forcing theorem does not assume its resolution.

# 4. Harmonic and continuum consequences

The finite terminal-selection construction of `findings-68.md` now applies directly to the standalone distance sector. A terminal energy formed from the three forcing defects selects its extremal central boundary point, harmonic function, and coherent up-transition law.

All continuum results previously proved for this sector therefore belong to an absolutely selected law. The finite relational constraints determine the central sector and its harmonic growth law, which in turn determine the route hierarchy and the Legendre-mode Ornstein-Uhlenbeck field.

The derived geometry also remains intrinsic:

```math
A(x,y)+A(y,x)=|x-y|,
```

and

```math
A(x,y)
=
\int \mathbf 1_{\{x<z\}}\mathbf 1_{\{z<y\}}\,dz.
```

Thus the same finitely selected sector carries an exact interval geometry, a complete path-volume hierarchy, stable continuum coefficients, and an explicit fluctuation spectrum.

# 5. Robustness

Because the central-profile space is compact and the three forcing coordinates are continuous, the robustness theorem of `findings-67.md` applies. Small total forcing energy implies projective proximity to the gap sector and convergence of every fixed finite-horizon reconstructed transition law.

The result is therefore stable under approximate finite constraints, not only exact at their common zero.

# 6. Status of the forcing result

The standalone kernel

```math
A(x,y)=(y-x)_+
```

is now absolutely finitely forcible in the full acyclic central DAG boundary.

The earlier obstruction results remain essential: paths and forests alone cannot select it. The successful selector necessarily includes cyclic Gram information and a two-root compositional constraint. The new theorem identifies exactly how those two kinds of information cooperate:

```math
\text{cyclic antisymmetric rigidity}
+
\text{two-root intermediate-volume rigidity}
+
\text{one scalar normalization}.
```

Exact symbolic calculations reproduce the path-volume identity, the coordinate-measure classification, the endpoint-atomic edge formula, and the final normalization argument.
