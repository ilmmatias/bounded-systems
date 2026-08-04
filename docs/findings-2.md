# 1. Enumeration through six nodes

An exhaustive computation over simple DAGs with at most six nodes determines
how far the node-level spectral profile separates isomorphism classes.

## Cumulative separation by invariant

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

The full node-level profile distinguishes every simple DAG through five nodes.
At six nodes, exactly four pairs of non-isomorphic DAGs remain
indistinguishable.

# 2. Six-node collisions among node-level invariants

The simplest surviving collision consists of two six-node chains, each with
one shortcut:

```math
\begin{aligned}
G_A &: \quad 1\to2\to3\to4\to5\to6,\qquad 3\to5,\\
G_B &: \quad 1\to2\to3\to4\to5\to6,\qquad 2\to4.
\end{aligned}
```

The two graphs are order duals: one shortcut occurs earlier along the chain
and the other later. They have the same edge count, rank profile, singular
spectrum, degree spectra, reachability spectrum, and underlying and
orientation Laplacian spectra.

The node-level asymmetric Gram operator $Q_2(A)=A^\mathsf TA+2AA^\mathsf T$
also fails to separate them, since both matrices have characteristic polynomial

```math
\chi_{Q_2}(\lambda) = \lambda^6 - 18\lambda^5 + 125\lambda^4 - 429\lambda^3 + 768\lambda^2 - 681\lambda + 234.
```

All four surviving collisions at six nodes are non-self-dual pairs of this
type. The node-level operators therefore do not determine the position of a
compositional shortcut relative to the global orientation.

# 3. Line-graph lift to the channel level

To recover this positional information, let $\mathcal{L}(G)$ denote the
directed line graph of $G$. Its vertices are the edges of $G$, and it contains
an edge $e\to f$ precisely when $t(e)=s(f)$. If $T$ and $S$ are the target and
source incidence matrices, respectively, then the adjacency matrix of
$\mathcal{L}(G)$ is $C=T^\mathsf TS$.

Applying the asymmetric Gram construction to this channel-level adjacency
matrix gives

```math
Q_2^{(E)} = C^\mathsf T C + 2 CC^\mathsf T.
```

For the late-shortcut graph $G_A$, the resulting characteristic polynomial is

```math
\chi_{Q_2^{(E)}}(\lambda) = \lambda^6 - 18\lambda^5 + 127\lambda^4 - 446\lambda^3 + 816\lambda^2 - 728\lambda + 240.
```

For the early-shortcut graph $G_B$, it is

```math
\chi_{Q_2^{(E)}}(\lambda) = \lambda^6 - 18\lambda^5 + 127\lambda^4 - 442\lambda^3 + 780\lambda^2 - 640\lambda + 192.
```

The two polynomials are distinct. The channel-level operator $Q_2^{(E)}$
likewise separates each of the four remaining six-node pairs.

# 4. Iterated line graphs and the spectral tower

Iteration of the line-graph construction defines the sequence

```math
G^{(0)} = G, \qquad G^{(r+1)} = \mathcal{L}(G^{(r)}).
```

A vertex of $G^{(r)}$ represents a composable directed path of length $r$ in
the original graph. If $G$ is a finite DAG with nilpotency index $\nu$, the
sequence terminates at $r=\nu-1$.

Define the spectral tower by
$\mathfrak{S}(G)=\left(\Phi(G^{(0)}),\Phi(G^{(1)}),\ldots\right)$. In the
six-node computation, the two-level fingerprint is

```math
\Phi_{\text{aug}}(G) = \left( \Phi_0(G^{(0)}), \, \mathrm{spec}\left(Q_2(A_{\mathcal{L}(G)})\right) \right).
```

It distinguishes all $5{,}984$ isomorphism classes of simple DAGs on six nodes.

# 5. Literature relation

The totals 31, 302 and 5,984 in the first row of the table in Section 1
are the numbers of acyclic digraphs on four, five and six unlabeled nodes
listed as Sequence A003087, On-Line Encyclopedia of Integer Sequences. The
computation reproduces these values as an audit of the generation
procedure.

R. W. Robinson established the counts in *Counting unlabeled acyclic
digraphs*, in Combinatorial Mathematics V, Lecture Notes in Mathematics
622, Springer, 1977, 28-43. His argument counts isomorphism classes without
producing representatives, whereas the invariant profiles in Sections 1
and 2 are evaluated on explicit representatives of every class.

The directed line graph of section 3 is the line digraph studied in F. Harary
and R. Z. Norman, *Some properties of line digraphs*, Rendiconti del Circolo
Matematico di Palermo 9 (1960), 161-168, for digraphs in general and with no
acyclicity hypothesis. Acyclicity enters only in section 4, where the nilpotency
index $\nu$ of a finite DAG makes the iteration
$G^{(r+1)}=\mathcal{L}(G^{(r)})$ terminate at $r=\nu-1$, so that the spectral
tower is a finite family; their general setting provides no such termination.

The invariant recorded in section 1 as the Hermitian orientation spectrum is the
spectrum of the skew matrix $A-A^\mathsf T$. For a digraph without digons, which
every simple DAG is, the Hermitian adjacency matrix equals
$i(A-A^\mathsf T)$ under the convention that an arc contributes the entry $i$ in
its own direction, so the two matrices have the same eigenvectors and their
eigenvalues differ by the factor $i$. That matrix is studied for mixed graphs,
in which a digon is read as an undirected edge, in K. Guo and B. Mohar,
*Hermitian adjacency matrix of digraphs and mixed graphs*, Journal of Graph
Theory 85 (2017), 217-248, arXiv:1505.01321, and in J. Liu and X. Li,
*Hermitian-adjacency matrices and Hermitian energies of mixed graphs*, Linear
Algebra and its Applications 466 (2015), 182-207. Their cospectrality statements
concern that matrix by itself, while the corresponding row of the table records
how many additional isomorphism classes it separates once the preceding
invariants of the profile have been applied.
