# 1. Rank-layer projections

Recall the past-rank layers

```math
L^-_\alpha=
\{v:\rho_-(v)=\alpha\}
```

and their projections

```math
\Delta^-_\alpha=
\sum_{v\in L^-_\alpha}e_v.
```

Similarly, the future-rank layers are

```math
L^+_\alpha=
\{v:\rho_+(v)=\alpha\},
```

with projections

```math
\Delta^+_\alpha=
\sum_{v\in L^+_\alpha}e_v.
```

The sums exist in the completed node diagonal

```math
\widehat{\mathcal D}=
\prod_{v\in V}\mathbb C e_v.
```

Define cumulative projections

```math
F^-_\alpha=
\sum_{\beta<\alpha}\Delta^-_\beta,
\qquad
F^+_\alpha=
\sum_{\beta<\alpha}\Delta^+_\beta.
```

The families

```math
\{F^-_\alpha\}_\alpha,
\qquad
\{F^+_\alpha\}_\alpha
```

are linearly ordered projection nests. In an operator realization they produce
the triangular block structure associated with invariant or coinvariant
subspaces.

# 2. Ordinal support constraints

Let

```math
p:u\to v
```

be a path of length $n$.

Whenever the relevant past ranks exist,

```math
\rho_-(u)+n\le \rho_-(v).
```

Similarly, whenever future ranks exist,

```math
\rho_+(v)+n\le \rho_+(u).
```

Both inequalities use ordinal addition.

For finite ranks, they reduce to the familiar inequalities

```math
n\le \rho_-(v)-\rho_-(u)
```

and

```math
n\le \rho_+(u)-\rho_+(v).
```

For transfinite ranks, ordinal inequalities are the correct formulation
because ordinary subtraction is not canonical.

A path therefore moves strictly upward in past rank and strictly downward in
future rank.

# 3. The past-rank resolvent matrix

Recall the universal formal channel element

```math
\mathbf E=\sum_{e\in E}e
```

and its formal resolvent

```math
R_G(z)=
(1-z\mathbf E)^{-1}=
\sum_{n=0}^{\infty}z^n\mathbf E^n.
```

Define its past-rank blocks by

```math
R^-_{\beta,\alpha}(z)=
\Delta^-_\beta
R_G(z)
\Delta^-_\alpha.
```

The right projection selects the source rank and the left projection selects
the target rank.

Expanding,

```math
R^-_{\beta,\alpha}(z)=
\delta_{\alpha\beta}\Delta^-_\alpha
+
\sum_{n\ge1}
z^n
\Delta^-_\beta
\mathbf E^n
\Delta^-_\alpha.
```

The coefficient

```math
\Delta^-_\beta
\mathbf E^n
\Delta^-_\alpha
```

is the formal sum of all length-$n$ paths from a source of past rank $\alpha$
to a target of past rank $\beta$. The ordinal support condition gives

```math
\Delta^-_\beta
\mathbf E^n
\Delta^-_\alpha=0
\quad\text{unless}\quad
\alpha+n\le\beta.
```

In particular,

```math
R^-_{\beta,\alpha}(z)=0
\qquad(\beta<\alpha),
```

and

```math
R^-_{\alpha,\alpha}(z)=\Delta^-_\alpha.
```

No positive path begins and ends in the same past-rank layer because every
layer is an antichain.

Thus $R_G(z)$ is a transfinite lower-triangular matrix relative to the
past-rank ordering:

```math
R_G(z)
\sim
\begin{pmatrix}
\Delta^-_0&0&0&0&\cdots\\
R^-_{1,0}&\Delta^-_1&0&0&\cdots\\
R^-_{2,0}&R^-_{2,1}&\Delta^-_2&0&\cdots\\
\vdots&\vdots&\vdots&\ddots&
\end{pmatrix}.
```

Edges may skip arbitrarily many layers, so the matrix need not be banded.

# 4. The future-rank resolvent matrix

Define

```math
R^+_{\beta,\alpha}(z)=
\Delta^+_\beta
R_G(z)
\Delta^+_\alpha.
```

Again, $\alpha$ is the source rank and $\beta$ is the target rank.

Now

```math
\Delta^+_\beta
\mathbf E^n
\Delta^+_\alpha=0
```

unless

```math
\beta+n\le\alpha.
```

Consequently,

```math
R^+_{\beta,\alpha}(z)=0
\qquad(\beta>\alpha).
```

Relative to increasing future rank, the same resolvent is upper triangular:

```math
R_G(z)
\sim
\begin{pmatrix}
\Delta^+_0&R^+_{0,1}&R^+_{0,2}&\cdots\\
0&\Delta^+_1&R^+_{1,2}&\cdots\\
0&0&\Delta^+_2&\cdots\\
\vdots&\vdots&\vdots&\ddots
\end{pmatrix}.
```

The two canonical rank systems reveal opposite triangular orientations:

```math
\begin{aligned}
\text{past rank:}&\quad \text{lower triangular},\\
\text{future rank:}&\quad \text{upper triangular}.
\end{aligned}
```

The opposite triangular orientations provide an intrinsic signature of directed
communication.

# 5. Exact factorization across a past-rank cut

Fix an ordinal $\gamma$, and let

```math
P=F^-_\gamma,
\qquad
Q=1-P.
```

Here $P$ contains all nodes of past rank below $\gamma$, while $Q$ contains
the nodes of rank at least $\gamma$ together with the backward-infinite core.

Because past rank cannot decrease along an edge,

```math
P\mathbf E Q=0.
```

There is no channel whose source is in $Q$ and whose target is in $P$.

Decompose

```math
\mathbf E=
P\mathbf EP
+
Q\mathbf EP
+
Q\mathbf EQ.
```

Define the corner resolvents

```math
R_P(z)=
(P-zP\mathbf EP)^{-1}
```

inside the corner with identity $P$, and

```math
R_Q(z)=
(Q-zQ\mathbf EQ)^{-1}
```

inside the corner with identity $Q$.

Then direct block inversion gives

```math
R_G(z)=
R_P(z)
+
R_Q(z)
+
zR_Q(z)\,Q\mathbf EP\,R_P(z).
```

The first two terms record paths that remain entirely in $P$ and $Q$,
respectively. The cross term

```math
zR_Q(z)\,Q\mathbf EP\,R_P(z)
```

records the paths that cross the cut. Each such path factors uniquely as a
path in $P$, followed by one primitive edge from $P$ to $Q$, followed by a
path in $Q$.

It cannot cross back because past rank cannot decrease.

Thus every path crosses a past-rank cut at most once.

# 6. Exact factorization across a future-rank cut

Now let

```math
P=F^+_\gamma,
\qquad
Q=1-P.
```

The projection $P$ contains nodes of future rank below $\gamma$, near the
system's terminating end.

Future-rank initial segments are successor-closed. Therefore

```math
Q\mathbf EP=0.
```

A channel cannot start in $P$ and leave for $Q$.

The decomposition is now upper triangular, and

```math
R_G(z)=
R_P(z)
+
R_Q(z)
+
zR_P(z)\,P\mathbf EQ\,R_Q(z).
```

A crossing path factors uniquely as a path in $Q$, one edge from $Q$ into
$P$, and a path remaining in $P$.

Once it enters the low-future-rank sector, it cannot leave.

# 7. Successor-stage recursion

The entire ranked resolvent can be constructed transfinally, one layer at a
time.

## Past recursion

Let

```math
R^-_{<\alpha}(z)=
F^-_\alpha R_G(z)F^-_\alpha.
```

At the next stage,

```math
F^-_{\alpha+1}=
F^-_\alpha+\Delta^-_\alpha.
```

There are no edges within $\Delta^-_\alpha$ and no edges from
$\Delta^-_\alpha$ into $F^-_\alpha$. Consequently,

```math
R^-_{<\alpha+1}(z)=
R^-_{<\alpha}(z)
+
\Delta^-_\alpha
+
z\Delta^-_\alpha
\mathbf E
F^-_\alpha
R^-_{<\alpha}(z).
```

Every nontrivial path ending at past rank $\alpha$ is obtained uniquely by
following a path through lower past ranks and then taking one final channel
into layer $\alpha$.

## Future recursion

Let

```math
R^+_{<\alpha}(z)=
F^+_\alpha R_G(z)F^+_\alpha.
```

Then

```math
R^+_{<\alpha+1}(z)=
R^+_{<\alpha}(z)
+
\Delta^+_\alpha
+
zR^+_{<\alpha}(z)
F^+_\alpha
\mathbf E
\Delta^+_\alpha.
```

Every nontrivial path beginning at future rank $\alpha$ is obtained by taking
one first channel into a lower future-rank layer and then continuing through
lower future ranks.

These two equations are exact transfinite analogues of recursive
triangular-matrix inversion.

# 8. Limit stages

Let $\lambda$ be a limit ordinal.

Then

```math
F^-_\lambda=
\bigvee_{\alpha<\lambda}F^-_\alpha.
```

Every finite path entirely below rank $\lambda$ lies below some earlier rank
$\alpha<\lambda$, since it has only finitely many nodes. It follows
coefficientwise that

```math
R^-_{<\lambda}(z)=
\operatorname*{coef\!-\!lim}_{\alpha<\lambda}
R^-_{<\alpha}(z).
```

The convergence is coefficientwise in the formal path topology, not
necessarily in operator norm.

Dually,

```math
R^+_{<\lambda}(z)=
\operatorname*{coef\!-\!lim}_{\alpha<\lambda}
R^+_{<\alpha}(z).
```

The full well-founded resolvent is assembled by successor-stage channel
attachment and coefficientwise union at limit stages.

# 9. Ordinal bands

For ordinals $\alpha<\beta$, define the past-rank band

```math
B^-_{[\alpha,\beta)}=
F^-_\beta-F^-_\alpha.
```

Any path whose source and target lie in this band must remain inside it.

Past rank strictly increases along the path, so every intermediate rank lies
between the source and target ranks.

```math
B^-_{[\alpha,\beta)}
R_G(z)
B^-_{[\alpha,\beta)}=
\left(
B^-_{[\alpha,\beta)}-
zB^-_{[\alpha,\beta)}
\mathbf E
B^-_{[\alpha,\beta)}
\right)^{-1}.
```

The compression is the formal resolvent of the induced rank-band subsystem.

The same holds for future-rank bands.

Convex ordinal bands are stronger than arbitrary node subsets because a path
cannot leave an ordinal band and later reenter it.

# 10. Separating the ranked part from the infinite core

Define the total past-ranked projection

```math
W^-=
\bigvee_\alpha F^-_\alpha
```

and backward-core projection

```math
K^-=1-W^-.
```

The core consists of nodes admitting infinite backward chains.

It is forward-closed:

```math
u\in K^-,
\quad
u\to v
\quad\Longrightarrow\quad
v\in K^-.
```

Equivalently,

```math
W^-\mathbf EK^-=0.
```

The complete resolvent factorizes as

```math
R_G(z)=
R_{W^-}(z)
+
R_{K^-}(z)
+
zR_{K^-}(z)
K^-\mathbf EW^-
R_{W^-}(z).
```

The cross term represents paths beginning in the past-well-founded region and
eventually entering the backward-infinite core.

Once such a path enters $K^-$, it cannot leave.

Dually, define

```math
W^+=
\bigvee_\alpha F^+_\alpha,
\qquad
K^+=1-W^+.
```

Here $K^+$ is predecessor-closed:

```math
v\in K^+,
\quad
u\to v
\quad\Longrightarrow\quad
u\in K^+.
```

Equivalently,

```math
K^+\mathbf EW^+=0,
```

and

```math
R_G(z)=
R_{W^+}(z)
+
R_{K^+}(z)
+
zR_{W^+}(z)
W^+\mathbf EK^+
R_{K^+}(z).
```

The cross term represents paths beginning in the forward-infinite core but
eventually branching into a future-well-founded terminating region.

# 11. The two-rank matrix

When both ranks exist, define the cell projection

```math
\Pi_{\alpha,\eta}=
\sum_{\substack{
\rho_-(v)=\alpha\\
\rho_+(v)=\eta
}}
e_v.
```

A path of length $n$ from a source cell $(\alpha,\eta)$ to a target cell
$(\beta,\theta)$ must satisfy

```math
\alpha+n\le\beta
```

and

```math
\theta+n\le\eta.
```

Communication moves through the ordinal plane according to

```math
(\alpha,\eta)
\longrightarrow
(\beta,\theta)
```

only if

```math
\alpha<\beta,
\qquad
\theta<\eta.
```

Along such a path, past rank increases while future rank decreases.

Define the two-rank block

```math
R_{(\beta,\theta),(\alpha,\eta)}(z)=
\Pi_{\beta,\theta}
R_G(z)
\Pi_{\alpha,\eta}.
```

Its $z^n$-coefficient is exactly the sum of all length-$n$ paths between
those two cells.

The resulting canonical transfinite causal matrix is

```math
\mathscr R_G(z)=
\left[
\Pi_{\beta,\theta}
R_G(z)
\Pi_{\alpha,\eta}
\right].
```

It is supported only on the partial order

```math
(\alpha,\eta)
\triangleleft
(\beta,\theta)
\iff
\alpha<\beta
\text{ and }
\eta>\theta.
```

Within a cell, nodes remain distinguishable only through finer channel
structure; the rank coordinates introduce no artificial node labels.

# 12. Analytic specialization

The layer projections $\Delta^\pm_\alpha$, cumulative projections
$F^\pm_\alpha$, core projections $K^\pm$, formal resolvent $R_G(z)$,
rank-filtered blocks $\Delta^\pm_\beta R_G(z)\Delta^\pm_\alpha$, and
transfinite cut factorizations constructed above live in the formal path
completion. They require no analytic assumptions and exist for arbitrary
cardinality and arbitrary degree.

Suppose now that the unweighted Fock aggregate

```math
S=\sum_{e\in E}L_e
```

is bounded. This occurs, for example, when outgoing degree is uniformly
finite. The aggregate $S$, its resolvent $(I-zS)^{-1}$, and the associated
operator norms, spectra, and pseudospectra require this bounded operator
realization, and are analytic images of the formal path data under a
particular faithful realization.

For

```math
|z|<\frac1{|S|},
```

the analytic resolvent exists:

```math
(I-zS)^{-1}=
\sum_{n=0}^{\infty}z^nS^n.
```

The formal rank-block identities become bounded-operator identities:

```math
\Delta^-_\beta
(I-zS)^{-1}
\Delta^-_\alpha=
\delta_{\alpha\beta}\Delta^-_\alpha
+
\sum_{n\ge1}
z^n
\Delta^-_\beta S^n\Delta^-_\alpha.
```

Let

```math
N_{n,\beta}(v)
```

be the number of length-$n$ paths beginning at $v$ and ending in past-rank
layer $\beta$.

Orthogonality of distinct Fock paths gives

```math
\left|
\Delta^-_\beta
S^n
\Delta^-_\alpha
\right|^2=
\sup_{\rho_-(v)=\alpha}
N_{n,\beta}(v).
```

Each resolvent block records both the existence of communication between
layers and the norm growth of the corresponding path family.

The full spectral radius $r(S)$ collapses this information into one global
exponential growth number; the filtered family retains where growth occurs.

# 13. Spectra versus cross-layer transfer

For a past-rank cut $P+Q=1$, the bounded operator has triangular form

```math
S=
\begin{pmatrix}
S_P&0\\
C&S_Q
\end{pmatrix}.
```

Whenever both diagonal resolvents exist,

```math
(I-zS)^{-1}=
\begin{pmatrix}
(I-zS_P)^{-1}&0\\[1mm]
z(I-zS_Q)^{-1}C(I-zS_P)^{-1}
&
(I-zS_Q)^{-1}
\end{pmatrix}.
```

The lower-left block

```math
z(I-zS_Q)^{-1}C(I-zS_P)^{-1}
```

is the complete cross-rank transfer function.

The spectral set of $S$ lies in the union of its diagonal blocks' spectra:

```math
\sigma(S)
\subseteq
\sigma(S_P)\cup\sigma(S_Q).
```

In infinite-dimensional triangular operator matrices, equality need not hold.

Even when the spectral set changes little, the cross term can produce large
resolvent norms through transient amplification, pseudospectral effects,
perturbation sensitivity, or the accumulation of long cross-layer paths.

The spectral set is coarser than the resolvent, the unfiltered resolvent is
coarser than the rank-filtered family, and the full marked path algebra
retains the finest information among these objects.
