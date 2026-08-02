# 1. Finite-dimensional adaptive sector states

Fixed algebraic sector families admit finite coordinate systems. A
different question arises when the sector itself is initially uncertain.
A general nonextremal central law carries a boundary variable whose
posterior need not remain in any finite-dimensional family.

For ordered stochastic block DAGs, Dirichlet and beta mixing laws give
an exact exception. Their posterior family is closed under every finite
extension. The resulting nonextremal central law therefore has a
finite-dimensional adaptive sector state.

# 2. The hierarchical ordered-DAG law

Fix $q\geq2$ and positive hyperparameters

```math
\alpha_1,\ldots,\alpha_q>0,
```

and, for each $i<j$,

```math
a_{ij},b_{ij}>0.
```

First sample

```math
p\sim\operatorname{Dirichlet}(\alpha_1,\ldots,\alpha_q),
```

and independently sample

```math
w_{ij}\sim\operatorname{Beta}(a_{ij},b_{ij}).
```

Conditional on $(p,W)$, sample the stochastic ordered-block DAG of
`findings-50.md`: the vertex layers are independent with law $p$, and
each possible edge from layer $i$ to layer $j$, where $i<j$, is included
independently with probability $w_{ij}$.

The unconditional infinite law is exchangeable and hence defines a
central measure. Its extremal decomposition is

```math
\mathbb P
=
\int \mathbb P_{p,W}\,\Pi(dp,dW),
```

where $\Pi$ is the product Dirichlet-beta prior. The boundary variable is

```math
\Theta=(p,W).
```

# 3. Sufficient relational counts

Suppose first that the ordered layer marks are observed. At level $n$, let

```math
C_{n,i}
=
\#\{v\leq n:A_v=i\},
```

and, for $i<j$, let

```math
M_{ij,n}=C_{n,i}C_{n,j}
```

be the number of possible cross-layer pairs and

```math
E_{ij,n}
```

be the number of present edges in that block. The number of absent
block edges is

```math
M_{ij,n}-E_{ij,n}.
```

The finite statistic

```math
S_n
=
\left(
(C_{n,i})_{i=1}^q,
(E_{ij,n})_{i<j}
\right)
```

contains all likelihood information about $(p,W)$.

## Theorem 1. Exact conjugate posterior

Conditional on the marked DAG through level $n$, the posterior
distribution factorizes as

```math
p\mid\mathcal F_n
\sim
\operatorname{Dirichlet}
(\alpha_1+C_{n,1},\ldots,\alpha_q+C_{n,q}),
```

and independently

```math
w_{ij}\mid\mathcal F_n
\sim
\operatorname{Beta}
\left(
 a_{ij}+E_{ij,n},
 b_{ij}+M_{ij,n}-E_{ij,n}
\right).
```

Thus $S_n$ is a finite-dimensional sufficient sector state.

## Proof

The marked likelihood is

```math
\prod_{i=1}^q p_i^{C_{n,i}}
\prod_{i<j}
 w_{ij}^{E_{ij,n}}
 (1-w_{ij})^{M_{ij,n}-E_{ij,n}}.
```

Multiplication by the product Dirichlet-beta prior updates the exponents
by the displayed counts and preserves factorization.

# 4. Exact predictive extension law

Write

```math
\alpha_0=\sum_i\alpha_i,
```

and define the posterior block parameters

```math
A_{ij,n}=a_{ij}+E_{ij,n},
```

and

```math
B_{ij,n}=b_{ij}+M_{ij,n}-E_{ij,n}.
```

The next layer has predictive law

```math
\mathbb P
(A_{n+1}=k\mid\mathcal F_n)
=
\frac{\alpha_k+C_{n,k}}{\alpha_0+n}.
```

Fix the event $A_{n+1}=k$. For every old layer $i\neq k$, let
$y_i\in\{0,1\}^{C_{n,i}}$ specify the edges between the new vertex and
the vertices of layer $i$, and let

```math
s_i=\sum y_i.
```

For $i<k$, these are edges from layer $i$ to the new vertex; for $i>k$,
they are edges from the new vertex to layer $i$. The probability of the
specific attachment vectors is

```math
\prod_{i<k}
\frac{
 B(A_{ik,n}+s_i,B_{ik,n}+C_{n,i}-s_i)
}{
 B(A_{ik,n},B_{ik,n})
}
```

multiplied by

```math
\times
\prod_{j>k}
\frac{
 B(A_{kj,n}+s_j,B_{kj,n}+C_{n,j}-s_j)
}{
 B(A_{kj,n},B_{kj,n})
}.
```

There are no possible edges to vertices in the new vertex's own layer.

## Theorem 2. Finite-dimensional predictive closure

The current marked endpoint together with $S_n$ determines the complete
next-extension distribution. After the new layer and attachment vector
are observed, the sufficient state updates only by

```math
C_{n+1,k}=C_{n,k}+1,
```

and, for each incident block,

```math
E_{ik,n+1}=E_{ik,n}+s_i
```

or

```math
E_{kj,n+1}=E_{kj,n}+s_j.
```

All other coordinates remain unchanged. The family of posterior sector
states is therefore exactly invariant under one-node extension.

## Proof

Integrating each Bernoulli block likelihood against its independent beta
posterior gives the beta-function ratios above. Integrating the new
categorical mark against the Dirichlet posterior gives the layer factor.
The products normalize because each block factor is a beta-binomial
mixture over its attachment vectors. The posterior after the extension
is obtained by adding the new sufficient counts, so it remains in the
same finite-dimensional family.

# 5. Sequential Pólya form

The attachment law can also be generated one edge at a time. Within a
block having current posterior parameters $(A,B)$, after $u$ new
successes and $v$ new failures, the next possible edge is present with
probability

```math
\frac{A+u}{A+B+u+v}.
```

The integrated attachments in one block are exchangeable but not
independent. Their positive predictive correlation records the
unresolved common block parameter.

The categorical layer process has the analogous Pólya form:

```math
\mathbb P
(A_{n+1}=k\mid A_1,\ldots,A_n)
=
\frac{\alpha_k+C_{n,k}}{\alpha_0+n}.
```

Thus the central growth law is produced by a finite collection of coupled
reinforcement mechanisms whose state is exactly the posterior
hyperparameter vector.

# 6. Eventual graph-intrinsic closure

The preceding statements use the marked filtration. Under the prior,
almost surely

```math
p_i>0
```

for every layer and

```math
w_{i,i+1}>0
```

for every adjacent pair. Conditional on $(p,W)$, Theorem 3 of
`findings-51.md` therefore applies. With unconditional probability one,
there is a finite random level after which iterative source deletion
recovers the complete ordered layer partition from the DAG endpoint
itself.

## Corollary 3. Eventual unmarked finite-dimensional closure

Almost surely, after a finite random level, the unlabeled DAG endpoint
determines $S_n$. From that level onward, the exact predictive state is

```math
(G_n,S_n),
```

where $G_n$ is the relational microstate and $S_n$ is a fixed-dimensional
adaptive sector state.

Before recovery, the graph-intrinsic posterior must sum over compatible
latent partitions and need not reduce to the count vector alone. The
finite-dimensional closure is exact for the marked process at every level
and exact for the unmarked graph after the almost-sure recovery time.

# 7. Boundary learning

Conditional on the sampled boundary variable $(p,W)$, the strong laws give

```math
\frac{C_{n,i}}n\longrightarrow p_i
```

and

```math
\frac{E_{ij,n}}{C_{n,i}C_{n,j}}
\longrightarrow w_{ij}
```

almost surely. The posterior therefore concentrates on the selected
extremal sector.

This gives a finite-dimensional realization of the degree-zero mode of
`findings-57.md`. Initially, $(p,W)$ is unresolved boundary information.
The growing relational endpoint updates a finite posterior state, and
the selected sector is learned from the graph itself.

For integer hyperparameters, exact rational calculations confirm that:

- the one-step predictive law normalizes over every new layer and
  attachment vector in small two- and three-layer states;
- the marginal probability of an extended marked DAG equals the marginal
  probability of the current marked DAG times the stated predictive factor;
- posterior hyperparameter updates agree with direct recomputation from
  the extended sufficient counts.

# 8. Literature relation

Dirichlet-multinomial and beta-Bernoulli conjugacy are standard special
cases of conjugate analysis for exponential families. Their role here
is structural: they produce a nonextremal central DAG law whose boundary
posterior is an exactly invariant finite-dimensional state under
relational growth.

Reference:

- P. Diaconis and D. Ylvisaker, *Conjugate priors for exponential
  families*, Annals of Statistics 7 (1979), 269-281.
