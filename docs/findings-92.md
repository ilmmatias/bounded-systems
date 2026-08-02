# 1. A necessary structural condition for standalone forcing

The preceding results give two distinct nonuniqueness mechanisms for the
standalone gap kernel:

1. every finite route family has exact smooth degree-preserving matching
   manifolds;
2. the complete directed-forest homomorphism hierarchy is preserved by
   nontrivial signed two-sheet lifts.

The second mechanism yields the following necessary condition.

## Theorem 1. Cycle necessity

No family consisting only of homomorphism densities of directed forests can
force the standalone gap kernel $A(x,y)=(y-x)_+$ in the full central DAG
boundary.

In particular, every absolute finite forcing family for $A$, if one exists,
must contain at least one directed acyclic pattern whose underlying undirected
graph contains a cycle.

## Proof

For every sufficiently small nonzero $\varepsilon$, the kernel
$\widetilde A_\varepsilon$ of `findings-90.md` is acyclic and has the same
density as $A$ for every directed forest. The directed $B_{2,2}$ density
differs by the strictly positive amount

```math
\varepsilon^4
\|T_hT_h^*\|_{\mathrm{HS}}^2,
```

so the two kernels are not weakly isomorphic.

# 2. Consequence for terminal selection

Consider a terminal energy built from finitely or countably many forest
homomorphism densities:

```math
\mathcal E(W)
=
\sum_j c_j
\left(
 t(F_j,W)-t(F_j,A)
\right)^2,
```

where every $F_j$ is a directed forest and the series is well defined. Then

```math
\mathcal E(\widetilde A_\varepsilon)=0
```

for all sufficiently small signed lifts.

Such an energy cannot select the gap sector uniquely. A terminal Gibbs
construction based only on route, star, broom, or branching-tree densities
necessarily retains unresolved boundary sectors.

A cyclic motif such as the transitive triangle or directed $B_{2,2}$ is
required to remove the explicit sheet ambiguity.

# 3. Scope of the theorem

Theorem 1 states a necessary condition on any forcing family for the standalone
gap kernel and leaves open whether that kernel is finitely forcible.

A finite family containing suitable undirected-cycle motifs may still be
nonlinearly rigid. The compositional completion of `findings-85.md` succeeds
precisely because it introduces Gram-type and square constraints whose pattern
expansions contain cyclic incidence structure.

The remaining direct problem can now be stated more narrowly:

> Can finitely many graph-intrinsic degree, compositional, and cyclic Gram
  constraints force $A(x,y)=(y-x)_+$ without an auxiliary tagged completion?

# 4. Revised selection hierarchy

The current hierarchy is:

```math
\begin{aligned}
&\text{finite route data}
&&\Longrightarrow
\text{exact local nonuniqueness},\\
&\text{complete forest data}
&&\Longrightarrow
\text{global signed-lift nonuniqueness},\\
&\text{cycle data}
&&\Longrightarrow
\text{detection of hidden pair modes},\\
&\text{tagged compositional completion}
&&\Longrightarrow
\text{absolute finite selection}.
\end{aligned}
```

The hierarchy separates three detection roles: path composition detects
sequential structure, branching probes orientation-asymmetric local structure,
and undirected cycles detect hidden pair correlations. Any direct standalone
forcing theorem must control all three.

# 5. Literature relation

For undirected graphons, equality of all tree homomorphism densities
characterizes fractional isomorphism rather than weak isomorphism. The
signed-lift theorem provides an explicit directed acyclic realization of the
same general principle: tree-like relational observations can determine a
branching quotient while leaving cyclic pair information unresolved.

Relevant references include:

- M. Grebik and I. Rocha, *Fractional isomorphism of graphons*, Combinatorica 42
  (2022), 365-404.
- J. Hladky, E. K. Hng, and A. M. Limbach, *Graphon branching processes and
  fractional isomorphism*, arXiv:2408.02528.
- L. Lovasz and B. Szegedy, *Finitely forcible graphons*, Journal of
  Combinatorial Theory, Series B 101 (2011), 269-301.
