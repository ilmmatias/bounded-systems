# 1. Transitive-triangle detector

The signed-lift expansion of `findings-90.md` shows that hidden pair modes are carried by Eulerian edge subsets. A directed graph can be acyclic while its underlying undirected graph contains cycles. Such motifs are the first possible detectors of the sheet interaction.

Let $T_3$ be the transitive triangle with edges

```math
1\to2,
\qquad
1\to3,
\qquad
2\to3.
```

Its underlying undirected graph is a three-cycle. The only Eulerian edge subsets are the empty set and the full triangle. Therefore

```math
t(T_3,\widetilde A_\varepsilon)
=
t(T_3,A)+\varepsilon^3I_3,
```

where

```math
I_3
=
\int_{0<x<y<z<1}
h(x,y)h(x,z)h(y,z)
\,dx\,dy\,dz.
```

For the polynomial perturbation of `findings-90.md`,

```math
I_3
=
\frac{311}{20532303792000}
>0.
```

Since

```math
t(T_3,A)=\frac1{180},
```

we obtain

```math
t(T_3,\widetilde A_\varepsilon)
=
\frac1{180}
+
\frac{311}{20532303792000}
\varepsilon^3.
```

Within this signed-lift family, the transitive-triangle density recovers the sign and magnitude of $\varepsilon$.

# 2. Directed four-cycle detector

Let $B_{2,2}$ be the directed complete bipartite pattern with two sources and two sinks. Its underlying undirected graph is a four-cycle. Again, the only Eulerian subsets are the empty set and the full cycle, so

```math
t(B_{2,2},\widetilde A_\varepsilon)
=
t(B_{2,2},A)+\varepsilon^4I_4.
```

The coefficient has the Gram form

```math
I_4
=
\int
\left(
\int h(x,y)h(x',y)\,dy
\right)^2
\,dx\,dx'
=
\|T_hT_h^*\|_{\mathrm{HS}}^2.
```

It is strictly positive for every nonzero $h$. For the explicit polynomial perturbation,

```math
I_4
=
\frac{13}{624153318768000}.
```

The base value is

```math
t(B_{2,2},A)=\frac{11}{1680},
```

so

```math
t(B_{2,2},\widetilde A_\varepsilon)
=
\frac{11}{1680}
+
\frac{13}{624153318768000}
\varepsilon^4.
```

Unlike the triangle coefficient, the four-cycle coefficient is a nonnegative norm and detects every nonzero perturbation of this signed-lift form, independently of its sign.

# 3. General cycle expansion

For an arbitrary directed pattern $F$, the first nonzero signed-lift correction is indexed by the smallest nonempty Eulerian subgraph contained in its underlying undirected graph.

Forest patterns have no signed-lift correction, whereas an underlying cycle of length $g$ can produce a correction of order $\varepsilon^g$.

The directed acyclicity condition removes directed recurrence but does not remove cyclic correlation structure in the undirected incidence pattern.

# 4. Information-theoretic interpretation

The sheet sign is a hidden vertex variable that enters each edge only through a pair product. A tree has a leaf, so at least one hidden sign appears to an odd power and averages to zero. Closing the incidence pattern around an undirected cycle pairs every hidden sign and makes the pair mode observable.

This is the finite-pattern counterpart of the support-order analysis developed in `findings-53.md` through `findings-56.md`: pair-supported information is not necessarily visible in linear or tree-like averages, but cyclic contractions produce nonzero invariant norms.

Exact rational evaluation gives the stated values of $t(T_3,A)$, $I_3$, $t(B_{2,2},A)$, and $I_4$, together with the Eulerian-subgraph expansion.
