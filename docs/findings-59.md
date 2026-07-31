# 1. The projective boundary profile

The extremal central-sector analysis identifies each sector with a deterministic sequence of finite induced-DAG probabilities. This sequence is not merely a coordinate system for the continuum limit. It reconstructs the positive harmonic function on the DAG branching graph and therefore determines every upward growth transition exactly.

Let $\mathfrak D_n$ denote the isomorphism classes of simple DAGs on $n$ vertices. Retain the extension multiplicity $e(G,H)$, the path dimension

```math
\dim(G)=\frac{n!}{|\operatorname{Aut}(G)|},
```

and the canonical deletion cotransition

```math
D_n(H,G)
=
\frac{\dim(G)e(G,H)}{\dim(H)}
=
\frac{d(G,H)}{n+1}.
```

A coherent profile is a sequence $\mu=(\mu_n)_{n\geq0}$, where $\mu_n$ is a probability measure on $\mathfrak D_n$ and

```math
\mu_n(G)
=
\sum_{H\in\mathfrak D_{n+1}}
\mu_{n+1}(H)D_n(H,G).
```

The set of all coherent profiles is the inverse limit of the finite-dimensional simplices $\Delta(\mathfrak D_n)$. It is the central simplex of the multiplicity Bratteli diagram.

# 2. Harmonic coordinates

For a coherent profile $\mu$, define

```math
h_n(G)=\frac{\mu_n(G)}{\dim(G)}.
```

## Theorem 1. Coherent profiles and normalized harmonic functions

The functions $h_n$ satisfy

```math
h_n(G)
=
\sum_{H\in\mathfrak D_{n+1}}
e(G,H)h_{n+1}(H),
```

and $h_0(\varnothing)=1$. Conversely, every nonnegative family $h=(h_n)$ satisfying these relations and the root normalization determines a unique coherent profile through

```math
\mu_n(G)=\dim(G)h_n(G).
```

Thus the central simplex is affinely isomorphic to the normalized base of the positive harmonic cone of the DAG branching graph.

## Proof

Dividing the coherence relation by $\dim(G)$ gives

```math
\begin{aligned}
h_n(G)
&=
\sum_H
\frac{\mu_{n+1}(H)}{\dim(G)}
\frac{\dim(G)e(G,H)}{\dim(H)}\\
&=
\sum_H e(G,H)h_{n+1}(H).
\end{aligned}
```

Conversely, suppose that $h$ is nonnegative, harmonic, and normalized at the root. The dimension recursion

```math
\dim(H)
=
\sum_{G\in\mathfrak D_n}
\dim(G)e(G,H)
```

implies

```math
\begin{aligned}
\sum_{G\in\mathfrak D_n}\dim(G)h_n(G)
&=
\sum_G\dim(G)\sum_H e(G,H)h_{n+1}(H)\\
&=
\sum_H\dim(H)h_{n+1}(H).
\end{aligned}
```

The total mass is therefore independent of the level and equals one at the root. Hence $\mu_n(G)=\dim(G)h_n(G)$ is a probability distribution. Substitution into the harmonic relation gives coherence.

# 3. Exact upward transitions

A coherent profile supplies a forward growth law on every state in its support.

## Theorem 2. Boundary reconstruction of the up kernel

For $G\in\mathfrak D_n$ with $\mu_n(G)>0$, define

```math
U_n^{\mu}(G,H)
=
\frac{e(G,H)h_{n+1}(H)}{h_n(G)}.
```

Equivalently,

```math
U_n^{\mu}(G,H)
=
D_n(H,G)
\frac{\mu_{n+1}(H)}{\mu_n(G)}.
```

Then $U_n^{\mu}(G,\cdot)$ is a probability distribution, and the forward and backward transitions satisfy

```math
\mu_n(G)U_n^{\mu}(G,H)
=
\mu_{n+1}(H)D_n(H,G).
```

The central path measure is the Markov measure obtained from the initial root and these upward transitions.

## Proof

Harmonicity gives

```math
\sum_H U_n^{\mu}(G,H)
=
\frac1{h_n(G)}
\sum_H e(G,H)h_{n+1}(H)
=1.
```

Using $\mu_n(G)=\dim(G)h_n(G)$ and the definition of $D_n$, we obtain

```math
\begin{aligned}
\mu_n(G)U_n^{\mu}(G,H)
&=
\dim(G)e(G,H)h_{n+1}(H)\\
&=
\mu_{n+1}(H)D_n(H,G).
\end{aligned}
```

Every finite path ending at $G$ has central cylinder probability $h_n(G)$. Multiplying the displayed upward transition probabilities along a path telescopes to that cylinder probability, proving the last statement.

# 4. Induced-pattern coordinates are complete

Let $X$ be the exchangeable infinite DAG associated with $\mu$. For $F\in\mathfrak D_k$, define

```math
p_F
=
\mathbb P(X|_{[k]}\cong F).
```

The central-exchangeable correspondence gives

```math
p_F=\mu_k(F).
```

## Theorem 3. Completeness of the full pattern profile

Two coherent profiles $\mu$ and $\nu$ are equal if and only if

```math
p_F^{\mu}=p_F^{\nu}
```

for every finite DAG $F$. In particular, the full induced-pattern profile determines:

1. every finite labeled distribution of the exchangeable DAG;
2. the coherent system on the Bratteli diagram;
3. the normalized harmonic function;
4. every upward transition $U_n$ on states of positive mass;
5. the weak-isomorphism class of any representing digraphon.

## Proof

The coordinate indexed by $F\in\mathfrak D_k$ is exactly $\mu_k(F)$. Equality of all coordinates is therefore equality of the coherent profiles. The labeled law on $[k]$ is uniform inside each isomorphism class and assigns probability

```math
\frac{\mu_k(F)}{\dim(F)}
```

to every labeled realization of $F$. The finite labeled distributions determine the infinite exchangeable law by projective extension. Theorems 1 and 2 then reconstruct the harmonic function and upward transitions. Standard digraphon representation theory identifies two representing digraphons precisely when they induce the same exchangeable directed-graph law.

# 5. Exact finite-horizon closure

For $N\geq1$, write

```math
\Pi_N(\mu)
=
(\mu_0,\mu_1,\ldots,\mu_N).
```

This is a finite-dimensional vector because every level $\mathfrak D_n$ is finite.

## Corollary 4. Finite truncation determines finite growth

The truncation $\Pi_N(\mu)$ determines exactly:

```math
U_0^{\mu},U_1^{\mu},\ldots,U_{N-1}^{\mu}.
```

More specifically, $(\mu_n,\mu_{n+1})$ determines $U_n^{\mu}$ through

```math
U_n^{\mu}(G,H)
=
D_n(H,G)
\frac{\mu_{n+1}(H)}{\mu_n(G)}.
```

No latent ordering, block partition, graphon representative, external time parameter, or separately postulated transition probability is required.

The required state has two parts. The finite endpoint $G$ is the current relational microstate, while $\mu$ is the selected boundary or sector state. Once the sector is fixed, the endpoint process is Markov with the displayed transition law.

# 6. Consequences for closure and selection

The infinite pattern profile is therefore an exact graph-intrinsic predictive state for the central growth problem. The remaining compression question is not whether a closed state exists. It is whether the projective state can be represented by fewer coordinates in a specified class of sectors.

Selection and closure are now separate:

```math
\text{selection chooses }\mu,
\qquad
\text{harmonic reconstruction gives }U^{\mu}.
```

A nonextremal central law makes $\mu$ random through its boundary variable, as described in `findings-57.md`. Conditional on that variable, the same reconstruction is exact.

Exhaustive construction of the DAG branching graph through four vertices gives the following exact rational results for several positive terminal profiles:

- the harmonic recursion;
- normalization of every level measure;
- coherence under deletion;
- normalization of every upward transition;
- the forward-backward balance identity;
- reconstruction of the terminally weighted central path law.

# 7. Literature relation

The equivalence between coherent systems, positive harmonic functions, and Markov central measures is standard in the theory of equipped graded graphs and Bratteli diagrams, for which see A. M. Vershik, *Equipped graded graphs, projective limits of simplices, and their boundaries*, Journal of Mathematical Sciences 209 (2015), 860-873, arXiv:1503.04447. The identification of complete finite-pattern probabilities with an exchangeable graph law is the graph-limit form of the Aldous-Hoover correspondence, developed in P. Diaconis and S. Janson, *Graph limits and exchangeable random graphs*, Rendiconti di Matematica 28 (2008), 33-61, arXiv:0712.2749. Directed graph laws are represented by digraphons, with uniqueness understood up to weak isomorphism, as in D. Cai, N. Ackerman, and C. Freer, *Priors on exchangeable directed graphs*, Electronic Journal of Statistics 10 (2016), 3490-3515, arXiv:1510.08440.
