# 1. Rank-layer projections

Recall the past-rank layers

$$
L^-_\alpha=
\{v:\rho_-(v)=\alpha\}
$$

and their projections

$$
\Delta^-_\alpha=
\sum_{v\in L^-_\alpha}e_v.
$$

Similarly, the future-rank layers are

$$
L^+_\alpha=
\{v:\rho_+(v)=\alpha\},
$$

with projections

$$
\Delta^+_\alpha=
\sum_{v\in L^+_\alpha}e_v.
$$

The sums exist in the completed node diagonal

$$
\widehat{\mathcal D}=
\prod_{v\in V}\mathbb C e_v.
$$

Define cumulative projections

$$
F^-_\alpha=
\sum_{\beta<\alpha}\Delta^-_\beta,
\qquad
F^+_\alpha=
\sum_{\beta<\alpha}\Delta^+_\beta.
$$

The families

$$
{F^-_\alpha}_\alpha,
\qquad
{F^+_\alpha}_\alpha
$$

are linearly ordered projection nests. In an operator realization, they give the usual triangular block structure associated with a nest of invariant or coinvariant subspaces.

---

# 2. Paths obey exact ordinal support constraints

Let

$$
p:u\to v
$$

be a path of length $n$.

Whenever the relevant past ranks exist,

$$
\rho_-(u)+n\le \rho_-(v).
$$

Similarly, whenever future ranks exist,

$$
\rho_+(v)+n\le \rho_+(u).
$$

These use ordinal addition.

For finite ranks, they reduce to the familiar inequalities

$$
n\le \rho_-(v)-\rho_-(u)
$$

and

$$
n\le \rho_+(u)-\rho_+(v).
$$

For transfinite ranks, ordinary subtraction is not canonical, so the ordinal inequalities are the correct formulation.

A path therefore moves:

$$
\text{strictly upward in past rank},
$$

and

$$
\text{strictly downward in future rank}.
$$

---

# 3. The past-rank resolvent matrix

Recall the universal formal channel element

$$
\mathbf E=\sum_{e\in E}e
$$

and its formal resolvent

$$
R_G(z)=
(1-z\mathbf E)^{-1}=
\sum_{n=0}^{\infty}z^n\mathbf E^n.
$$

Define its past-rank blocks by

$$
R^-_{\beta,\alpha}(z)=
\Delta^-_\beta
R_G(z)
\Delta^-_\alpha.
$$

The right projection selects the source rank and the left projection selects the target rank.

Expanding,

$$
R^-_{\beta,\alpha}(z)=
\delta_{\alpha\beta}\Delta^-_\alpha
+
\sum_{n\ge1}
z^n
\Delta^-_\beta
\mathbf E^n
\Delta^-_\alpha.
$$

The coefficient

$$
\Delta^-_\beta
\mathbf E^n
\Delta^-_\alpha
$$

is exactly the formal sum of all length-$n$ paths whose:

* source has past rank $\alpha$;
* target has past rank $\beta$.

Consequently,

$$
\Delta^-_\beta
\mathbf E^n
\Delta^-_\alpha=0
\quad\text{unless}\quad
\alpha+n\le\beta.
$$

In particular,

$$
R^-_{\beta,\alpha}(z)=0
\qquad(\beta<\alpha),
$$

and

$$
R^-_{\alpha,\alpha}(z)=\Delta^-_\alpha.
$$

No positive path begins and ends in the same past-rank layer because every layer is an antichain.

Thus $R_G(z)$ is a transfinite lower-triangular matrix relative to the past-rank ordering:

$$
R_G(z)
\sim
\begin{pmatrix}
\Delta^-*0&0&0&0&\cdots\\
R^-_{1,0}&\Delta^-*1&0&0&\cdots\\
R^-_{2,0}&R^-_{2,1}&\Delta^-_2&0&\cdots\\
\vdots&\vdots&\vdots&\ddots&
\end{pmatrix}.
$$

Edges may skip arbitrarily many layers, so the matrix need not be banded.

---

# 4. The future-rank resolvent matrix

Define

$$
R^+_{\beta,\alpha}(z)=
\Delta^+_\beta
R_G(z)
\Delta^+_\alpha.
$$

Again, $\alpha$ is the source rank and $\beta$ is the target rank.

Now

$$
\Delta^+_\beta
\mathbf E^n
\Delta^+_\alpha=0
$$

unless

$$
\beta+n\le\alpha.
$$

Hence

$$
R^+_{\beta,\alpha}(z)=0
\qquad(\beta>\alpha).
$$

Relative to increasing future rank, the same resolvent is upper triangular:

$$
R_G(z)
\sim
\begin{pmatrix}
\Delta^+*0&R^+_{0,1}&R^+_{0,2}&\cdots\\
0&\Delta^+*1&R^+_{1,2}&\cdots\\
0&0&\Delta^+_2&\cdots\\
\vdots&\vdots&\vdots&\ddots
\end{pmatrix}.
$$

Thus the two canonical rank systems reveal opposite triangular orientations:

$$
\begin{aligned}
\text{past rank:}&\quad \text{lower triangular},\\
\text{future rank:}&\quad \text{upper triangular}.
\end{aligned}
$$

That opposition is an intrinsic signature of directed communication.

---

# 5. Exact factorization across a past-rank cut

Fix an ordinal $\gamma$, and let

$$
P=F^-_\gamma,
\qquad
Q=1-P.
$$

Here $P$ contains all nodes of past rank below $\gamma$, while $Q$ contains:

* nodes of rank at least $\gamma$;
* and nodes in the backward-infinite core.

Because past rank cannot decrease along an edge,

$$
P\mathbf E Q=0.
$$

There is no channel whose source is in $Q$ and whose target is in $P$.

Decompose

$$
\mathbf E=
P\mathbf EP
+
Q\mathbf EP
+
Q\mathbf EQ.
$$

Define the corner resolvents

$$
R_P(z)=
(P-zP\mathbf EP)^{-1}
$$

inside the corner with identity $P$, and

$$
R_Q(z)=
(Q-zQ\mathbf EQ)^{-1}
$$

inside the corner with identity $Q$.

Then direct block inversion gives

$$
R_G(z)=
R_P(z)
+
R_Q(z)
+
zR_Q(z),Q\mathbf EP,R_P(z).
$$

The three terms have exact interpretations.

### Paths remaining below the cut

$$
R_P(z).
$$

### Paths remaining above the cut

$$
R_Q(z).
$$

### Paths crossing the cut

$$
zR_Q(z),Q\mathbf EP,R_P(z).
$$

A crossing path consists uniquely of:

1. a path staying in $P$;
2. one primitive edge from $P$ into $Q$;
3. a path staying in $Q$.

It cannot cross back because past rank cannot decrease.

So every path crosses a past-rank cut **at most once**.

---

# 6. Exact factorization across a future-rank cut

Now let

$$
P=F^+_\gamma,
\qquad
Q=1-P.
$$

The projection $P$ contains nodes whose future rank is below $\gamma$, meaning nodes near the terminating end of the system.

Future-rank initial segments are successor-closed. Therefore

$$
Q\mathbf EP=0.
$$

A channel cannot start in $P$ and leave for $Q$.

The decomposition is now upper triangular, and

$$
R_G(z)=
R_P(z)
+
R_Q(z)
+
zR_P(z),P\mathbf EQ,R_Q(z).
$$

A crossing path consists of:

1. a path remaining in $Q$;
2. one edge from $Q$ into $P$;
3. a path remaining in $P$.

Once it enters the low-future-rank sector, it cannot leave.

---

# 7. Successor-stage recursion

The entire ranked resolvent can be constructed transfinally, one layer at a time.

## Past recursion

Let

$$
R^-_{<\alpha}(z)=
F^-_\alpha R_G(z)F^-_\alpha.
$$

At the next stage,

$$
F^-_{\alpha+1}=
F^-_\alpha+\Delta^-_\alpha.
$$

There are:

* no edges within $\Delta^-_\alpha$;
* no edges from $\Delta^-_\alpha$ into $F^-_\alpha$.

Therefore

$$
R^-_{<\alpha+1}(z)=
R^-_{<\alpha}(z)
+
\Delta^-_\alpha
+
z\Delta^-_\alpha
\mathbf E
F^-_\alpha
R^-_{<\alpha}(z).
$$

Every nontrivial path ending at past rank $\alpha$ is obtained uniquely by:

1. following a path entirely through lower past ranks;
2. taking one final channel into layer $\alpha$.

## Future recursion

Let

$$
R^+_{<\alpha}(z)=
F^+_\alpha R_G(z)F^+_\alpha.
$$

Then

$$
R^+_{<\alpha+1}(z)=
R^+_{<\alpha}(z)
+
\Delta^+_\alpha
+
zR^+_{<\alpha}(z)
F^+_\alpha
\mathbf E
\Delta^+_\alpha.
$$

Every nontrivial path beginning at future rank $\alpha$ is obtained by:

1. taking one first channel into a lower future-rank layer;
2. continuing entirely through lower future ranks.

These two equations are exact transfinite analogues of recursive triangular-matrix inversion.

---

# 8. Limit stages

Let $\lambda$ be a limit ordinal.

Then

$$
F^-_\lambda=
\bigvee_{\alpha<\lambda}F^-_\alpha.
$$

Every finite path lying entirely below rank $\lambda$ already lies below some earlier rank $\alpha<\lambda$, because it contains only finitely many nodes.

Consequently,

$$
R^-_{<\lambda}(z)=
\operatorname*{coef\!-\!lim}_{\alpha<\lambda}
R^-_{<\alpha}(z).
$$

This is coefficientwise convergence in the formal path topology—not necessarily operator-norm convergence.

Dually,

$$
R^+_{<\lambda}(z)=
\operatorname*{coef\!-\!lim}_{\alpha<\lambda}
R^+_{<\alpha}(z).
$$

Thus the full well-founded resolvent is assembled by:

* successor-stage channel attachment;
* coefficientwise union at limit stages.

---

# 9. Ordinal bands

For ordinals $\alpha<\beta$, define the past-rank band

$$
B^-_{[\alpha,\beta)}=
F^-_\beta-F^-_\alpha.
$$

Any path whose source and target lie in this band must remain inside it.

Indeed, past rank strictly increases along the path, so every intermediate rank lies between the source and target ranks.

Therefore

$$
B^-_{[\alpha,\beta)}
R_G(z)
B^-_{[\alpha,\beta)}=
\left(
B^-_{[\alpha,\beta)}-
zB^-_{[\alpha,\beta)}
\mathbf E
B^-_{[\alpha,\beta)}
\right)^{-1}.
$$

The compression is the formal resolvent of the induced rank-band subsystem.

The same holds for future-rank bands.

This is stronger than arbitrary node compression. For a random node subset, a path can leave the subset and later reenter. A convex ordinal band forbids that.

---

# 10. Separating the ranked part from the infinite core

Define the total past-ranked projection

$$
W^-=
\bigvee_\alpha F^-_\alpha
$$

and backward-core projection

$$
K^-=1-W^-.
$$

The core consists of nodes admitting infinite backward chains.

It is forward-closed:

$$
u\in K^-,
\quad
u\to v
\quad\Longrightarrow\quad
v\in K^-.
$$

Therefore

$$
W^-\mathbf EK^-=0.
$$

The complete resolvent factorizes as

$$
R_G(z)=
R_{W^-}(z)
+
R_{K^-}(z)
+
zR_{K^-}(z)
K^-\mathbf EW^-
R_{W^-}(z).
$$

The cross term represents paths that begin in the past-well-founded region and eventually enter the backward-infinite core.

Once such a path enters $K^-$, it cannot leave.

Dually, define

$$
W^+=
\bigvee_\alpha F^+_\alpha,
\qquad
K^+=1-W^+.
$$

Here $K^+$ is predecessor-closed:

$$
v\in K^+,
\quad
u\to v
\quad\Longrightarrow\quad
u\in K^+.
$$

Thus

$$
K^+\mathbf EW^+=0
$$

and

$$
R_G(z)=
R_{W^+}(z)
+
R_{K^+}(z)
+
zR_{W^+}(z)
W^+\mathbf EK^+
R_{K^+}(z).
$$

This cross term represents paths that begin in the forward-infinite core but eventually branch into a future-well-founded terminating region.

---

# 11. The two-rank matrix

When both ranks exist, define the cell projection

$$
\Pi_{\alpha,\eta}=
\sum_{\substack{
\rho_-(v)=\alpha\\
\rho_+(v)=\eta
}}
e_v.
$$

A path of length $n$ from a source cell

$$
(\alpha,\eta)
$$

to a target cell

$$
(\beta,\theta)
$$

must satisfy

$$
\alpha+n\le\beta
$$

and

$$
\theta+n\le\eta.
$$

Hence communication moves through the ordinal plane according to

$$
(\alpha,\eta)
\longrightarrow
(\beta,\theta)
$$

only if

$$
\alpha<\beta,
\qquad
\theta<\eta.
$$

The source’s past rank increases, while its future rank decreases.

Define the two-rank block

$$
R_{(\beta,\theta),(\alpha,\eta)}(z)=
\Pi_{\beta,\theta}
R_G(z)
\Pi_{\alpha,\eta}.
$$

Its $z^n$-coefficient is exactly the sum of all length-$n$ paths between those two cells.

Thus the system possesses a canonical transfinite “causal matrix”:

$$
\mathscr R_G(z)=
\left[
\Pi_{\beta,\theta}
R_G(z)
\Pi_{\alpha,\eta}
\right].
$$

It is supported only on the partial order

$$
(\alpha,\eta)
\triangleleft
(\beta,\theta)
\iff
\alpha<\beta
\text{ and }
\eta>\theta.
$$

Nodes in the same cell remain distinguishable only through finer channel structure; rank coordinates do not artificially label them.

---

# 12. Analytic specialization

Everything above exists formally for arbitrary cardinality and arbitrary degree.

Suppose now that the unweighted Fock aggregate

$$
S=\sum_{e\in E}L_e
$$

is bounded. This occurs, for example, when outgoing degree is uniformly finite.

For

$$
|z|<\frac1{|S|},
$$

the analytic resolvent exists:

$$
(I-zS)^{-1}=
\sum_{n=0}^{\infty}z^nS^n.
$$

The formal rank-block identities become bounded-operator identities:

$$
\Delta^-_\beta
(I-zS)^{-1}
\Delta^-_\alpha=
\delta_{\alpha\beta}\Delta^-_\alpha
+
\sum_{n\ge1}
z^n
\Delta^-_\beta S^n\Delta^-_\alpha.
$$

Let

$$
N_{n,\beta}(v)
$$

be the number of length-$n$ paths beginning at $v$ and ending in past-rank layer $\beta$.

Orthogonality of distinct Fock paths gives

$$
\left|
\Delta^-_\beta
S^n
\Delta^-_\alpha
\right|^2=
\sup_{\rho_-(v)=\alpha}
N_{n,\beta}(v).
$$

Thus each resolvent block records not merely whether layers communicate, but the norm growth of paths between particular transfinite layers.

The full spectral radius

$$
r(S)
$$

collapses all this into one global exponential growth number. The filtered family retains **where** the growth occurs.

---

# 13. Spectra versus cross-layer transfer

For a past-rank cut $P+Q=1$, the bounded operator has triangular form

$$
S=
\begin{pmatrix}
S_P&0\\
C&S_Q
\end{pmatrix}.
$$

Whenever both diagonal resolvents exist,

$$
(I-zS)^{-1}=
\begin{pmatrix}
(I-zS_P)^{-1}&0[1mm]
z(I-zS_Q)^{-1}C(I-zS_P)^{-1}
&
(I-zS_Q)^{-1}
\end{pmatrix}.
$$

The lower-left term

$$
z(I-zS_Q)^{-1}C(I-zS_P)^{-1}
$$

is the complete cross-rank transfer function.

The spectral set of $S$ is contained in the union of the spectra of its diagonal blocks:

$$
\sigma(S)
\subseteq
\sigma(S_P)\cup\sigma(S_Q).
$$

In infinite-dimensional triangular operator matrices, equality need not hold.

Even when the spectral set changes little, the cross term can make resolvent norms very large. It therefore contributes to:

* transient amplification;
* pseudospectral behavior;
* sensitivity to perturbation;
* long cross-layer path accumulation.

Hence:

$$
\text{spectrum}
<
\text{resolvent}
<
\text{rank-filtered resolvent}
<
\text{full marked path algebra}.
$$

---

# 14. What is forced and what is conditional

## Forced directly by A1–A5

The following exist without analytic assumptions:

$$
\Delta^\pm_\alpha,
\qquad
F^\pm_\alpha,
\qquad
K^\pm,
$$

$$
R_G(z),
$$

$$
\Delta^\pm_\beta
R_G(z)
\Delta^\pm_\alpha,
$$

and all transfinite cut factorizations.

They live in the formal path completion.

## Conditional analytic specialization

The following require the relevant bounded operator to exist:

$$
S=\sum_eL_e,
$$

$$
(I-zS)^{-1},
$$

operator norms, spectra, and pseudospectra.

These are analytic images of the formal path data under a particular faithful realization.
