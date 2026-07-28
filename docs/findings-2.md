# 1. Computation through six nodes

Testing our node-level spectral profile across all simple DAGs up to six nodes reveals where node-level data succeeds and where it fails.

## Information breakdown by invariant

| Cumulative information profile     | $n=4$ | $n=5$ | $n=6$ |
| :--------------------------------- | ----: | ----: | ----: |
| Total non-isomorphic DAGs          |    31 |   302 | 5,984 |
| Edge count                         |     7 |    11 |    16 |
| $+$ ranks of $A,A^2,\ldots$        |    15 |    36 |    90 |
| $+$ singular spectrum of $A$       |    20 |   108 | 1,077 |
| $+$ in/out Laplacian spectra       |    27 |   189 | 2,237 |
| $+$ underlying Laplacian spectrum  |    30 |   270 | 5,158 |
| $+$ Hermitian orientation spectrum |    30 |   272 | 5,385 |
| $+$ reachability singular spectrum |    30 |   276 | 5,505 |
| $+$ asymmetric Gram operator $Q_2$ |    31 |   302 | 5,980 |

Through five nodes, the full node-level profile completely distinguishes every simple DAG. At six nodes, exactly four non-isomorphic pairs remain collision-bound.

# 2. Node-level ambiguity at six nodes

The simplest surviving collision pair consists of a six-node chain with a single shortcut:

```math
G_A: \quad 1\to2\to3\to4\to5\to6,\qquad 3\to5,

```

```math
G_B: \quad 1\to2\to3\to4\to5\to6,\qquad 2\to4.

```

These graphs are order duals; one has an early shortcut, the other a late shortcut. They share identical edge counts, rank profiles, singular spectra, degree spectra, reachability spectra, and underlying/orientation Laplacians.

Furthermore, $Q_2(A) = A^\mathsf TA + 2AA^\mathsf T$ fails to separate them, yielding identical characteristic polynomials:

```math
\chi_{Q_2}(\lambda) = \lambda^6 - 18\lambda^5 + 125\lambda^4 - 429\lambda^3 + 768\lambda^2 - 681\lambda + 234.

```

All four surviving collisions at six nodes are non-self-dual pairs of this form. Node-level operators cannot determine where compositional shortcuts sit relative to the global orientation of the order.

# 3. Channel-level lift via line graphs

To recover positional structure, let $\mathcal{L}(G)$ be the directed line graph of $G$, where nodes represent edges of $G$, and directed edges $e \to f$ exist whenever $t(e) = s(f)$. Using target $T$ and source $S$ incidence matrices, the line-graph adjacency matrix is $C = T^\mathsf T S$.

We then apply the asymmetric Gram operator at the edge level:

```math
Q_2^{(E)} = C^\mathsf T C + 2 CC^\mathsf T.

```

For the late-shortcut graph $G_A$:

```math
\chi_{Q_2^{(E)}}(\lambda) = \lambda^6 - 18\lambda^5 + 127\lambda^4 - 446\lambda^3 + 816\lambda^2 - 728\lambda + 240.

```

For the early-shortcut graph $G_B$:

```math
\chi_{Q_2^{(E)}}(\lambda) = \lambda^6 - 18\lambda^5 + 127\lambda^4 - 442\lambda^3 + 780\lambda^2 - 640\lambda + 192.

```

The polynomials differ. Applying $Q_2^{(E)}$ separates all four remaining six-node pairs.

# 4. Communication spectral tower

Iterating the line graph construction creates a natural hierarchy:

```math
G^{(0)} = G, \qquad G^{(r+1)} = \mathcal{L}(G^{(r)}).

```

Here, nodes of $G^{(r)}$ represent composable directed paths of length $r$ in the original system. Because $G$ is a finite DAG, this sequence terminates at $r = \nu - 1$.

Defining the spectral tower as $\mathfrak{S}(G) = \left(\Phi(G^{(0)}), \Phi(G^{(1)}), \ldots\right)$, the two-level fingerprint

```math
\Phi_{\text{aug}}(G) = \left( \Phi_0(G^{(0)}), \, \mathrm{spec}\left(Q_2(A_{\mathcal{L}(G)})\right) \right)

```

completely distinguishes all 5,984 simple DAGs on six nodes.
