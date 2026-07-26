# 1. Exact observation classes

Let $X$ be the set of $t$-Martin-regular tail ends after eventual-tail collapse, and let

$$
\Phi_t:X\longrightarrow \mathcal M_t,
\qquad
\Phi_t(\tau)=h_\tau
$$

be the node-profile map.

For a finite node set $F\Subset V_o$, define

$$
\tau\equiv_F\sigma
\iff
h_\tau(v)=h_\sigma(v)
\quad\forall v\in F.
$$

Let

$$
C_F=X/!\equiv_F.
$$

If $F\subseteq F'$, then $F'$ distinguishes at least as much as $F$, giving a surjection

$$
\rho_{F',F}:C_{F'}\longrightarrow C_F.
$$

Thus

$$
{C_F,\rho_{F',F}}_{F\Subset V_o}
$$

is the exact observation-refinement diagram.

For a locally finite rooted component, the balls

$$
B_n(o)=\{v:d(o,v)\le n\}
$$

are finite and exhaust $V_o$. We may then use the sequence

$$
C_n=C_{B_n(o)}
$$

with bonding maps

$$
\rho_n:C_{n+1}\to C_n.
$$

For arbitrary branching, the directed system over all finite $F$ remains primary; there may be no canonical one-parameter sequence of finite observations.

---

# 2. Local splitting and the associated graded defect

For $c\in C_n$, define its splitting multiplicity

$$
b_n(c)=|\rho_n^{-1}(c)|.
$$

This is the number of distinct depth-$(n+1)$ profiles hidden inside one depth-$n$ profile.

If the class sets are finite, then

$$
|C_{n+1}|=
\sum_{c\in C_n}b_n(c).
$$

Let

$$
\mathfrak D_n^{\mathrm{obs}}=
\mathrm{span}
\{
\delta_\tau-\delta_\sigma:
\tau\equiv_{B_n(o)}\sigma
\}.
$$

The defect filtration is decreasing:

$$
\mathfrak D_0^{\mathrm{obs}}
\supseteq
\mathfrak D_1^{\mathrm{obs}}
\supseteq
\cdots
\supseteq
\mathfrak D_M,
$$

where

$$
\mathfrak D_M=
\bigcap_n\mathfrak D_n^{\mathrm{obs}}
$$

is the permanent Martin-collapse defect.

At every level,

$$
0\to
\mathfrak D_{n+1}^{\mathrm{obs}}
\to
\mathfrak D_n^{\mathrm{obs}}
\to
\bigoplus_{c\in C_n}
\widetilde{k}^{(\rho_n^{-1}(c))}
\to0.
$$

Consequently,

$$
\mathrm{gr}_{\mathrm{obs}}\mathfrak D=
\bigoplus_{n\ge0}
\mathfrak D_n^{\mathrm{obs}}/
\mathfrak D_{n+1}^{\mathrm{obs}}
$$

records distinctions according to the first observation layer at which they become visible.

When $C_n$ and $C_{n+1}$ are finite,

$$
\dim
\frac{\mathfrak D_n^{\mathrm{obs}}}
{\mathfrak D_{n+1}^{\mathrm{obs}}}=
|C_{n+1}|-|C_n|.
$$

No canonical splitting of these exact sequences is implied. The filtration is canonical; a direct-sum decomposition into layers generally is not.

---

# 3. Exact splitting growth

When every $C_n$ is finite, define

$$
c_n=|C_n|.
$$

A simple growth invariant is

$$
\Lambda_{\mathrm{split}}=
\limsup_{n\to\infty}c_n^{1/n}.
$$

Equivalently, one may retain the complete sequence

$$
(c_0,c_1,c_2,\ldots)
$$

and the local branching data

$$
{b_n(c):c\in C_n}.
$$

The scalar $\Lambda_{\mathrm{split}}$ is only a compression. Different diagrams can have the same exponential rate but radically different splitting patterns.

Three extremal cases are already visible:

### No node-level separation

$$
c_n=1
\qquad\forall n.
$$

Every tail end has the same node Martin profile.

### Eventual finite determination

For each full profile, there is some $n$ after which its class never splits further.

Such a profile is isolated in the exact refinement structure.

### Persistent refinement

A compatible branch passes through classes that split infinitely often.

Its full profile cannot be determined by any finite observation depth.

---

# 4. Why exact separation depth is not a topology

Previously we defined the first exact separating depth

$$
s_t(\tau,\sigma)=
\min{n:h_\tau|_{B_n}\ne h_\sigma|_{B_n}}.
$$

It satisfies

$$
s_t(\tau,\zeta)
\ge
\min{s_t(\tau,\sigma),s_t(\sigma,\zeta)}.
$$

So, after quotienting permanent Martin-equivalent ends, one may formally construct an ultrametric such as

$$
d_\theta(\tau,\sigma)=\theta^{s_t(\tau,\sigma)},
\qquad 0<\theta<1.
$$

But this topology can be much finer than the actual Martin topology.

If two profiles differ by $10^{-100}$ at a shallow node, the exact ultrametric treats them as immediately separated. The Martin product topology treats them as extremely close.

Therefore:

$$
s_t
\text{ measures logical distinguishability, not quantitative proximity.}
$$

---

# 5. Canonical finite-coordinate profile geometry

Normalize every Martin profile by

$$
\widehat h(v)=
t^{d(o,v)}h(v).
$$

The prefix bound gives

$$
0\le\widehat h(v)\le1.
$$

For a finite observation set $F$, define the pseudometric

$$
d_F(h,g)=
\max_{v\in F}
|\widehat h(v)-\widehat g(v)|.
$$

This is the finite-coordinate geometry of the real-valued Martin profiles.

Let

$$
\mathcal N_F(\varepsilon)
$$

be the minimum number of $d_F$-balls of radius $\varepsilon$ required to cover the profile image $\Phi_t(X)$.

For a locally finite rooted component, define

$$
\mathcal N_n(\varepsilon)=
\mathcal N_{B_n(o)}(\varepsilon).
$$

Then

$$
\Lambda_{\mathrm{obs}}(\varepsilon)=
\limsup_{n\to\infty}
\mathcal N_n(\varepsilon)^{1/n}
$$

is the observation-growth spectrum at precision $\varepsilon$.

The full family

$$
\varepsilon\longmapsto
\Lambda_{\mathrm{obs}}(\varepsilon)
$$

is more informative than one exact class-growth scalar.

If the finite profile set at depth $n$ is discrete with minimum pairwise separation $\delta_n>0$, then for

$$
\varepsilon<\frac{\delta_n}{2}
$$

we recover the exact count:

$$
\mathcal N_n(\varepsilon)=c_n.
$$

In continuous-profile situations, the covering numbers remain meaningful even when $c_n$ is infinite.

---

# 6. How much route history is needed to determine a profile?

Let

$$
\mathrm{pref}_m(\xi)
$$

denote the length-$m$ prefix of an infinite history.

Define the approximate observation lag

$$
\ell_t(n,\varepsilon)=
\min
\left\lbrace m: \begin{array}{l} \mathrm{pref}_m(\xi)= \mathrm{pref}*m(\eta)[1mm] \Longrightarrow d_{B_n(o)}(h_\xi,h_\eta <\varepsilon \end{array} \right\rbrace.
$$

Set it to $\infty$ when no finite $m$ works.

Interpretation:

$$
\ell_t(n,\varepsilon)=
\text{how much route history is needed to predict}
$$

$$
\text{all node observations through depth }n
\text{ to precision }\varepsilon.
$$

This separates three regimes.

### Route-local profiles

$$
\ell_t(n,\varepsilon)\approx n.
$$

Shallow node profiles are determined by comparably shallow route history.

### Strong asymptotic mixing

$$
\ell_t(n,\varepsilon)\ll n.
$$

Very little route history is needed because many histories have nearly identical node profiles.

### Long-range dependence

$$
\ell_t(n,\varepsilon)\gg n
\quad\text{or}\quad
\ell_t(n,\varepsilon)=\infty.
$$

Even shallow node asymptotics depend on very long—or complete—infinite history.

If the prefix boundary is compact, finitely branching, and the profile map is continuous, then

$$
\ell_t(n,\varepsilon)<\infty
$$

for every finite $n$ and every $\varepsilon>0$. This is simply uniform continuity expressed in the intrinsic cylinder structure.

If $P_m(o)$ is the number of length-$m$ prefixes from $o$, then

$$
\mathcal N_n(\varepsilon)
\le
P_{\ell_t(n,\varepsilon)}(o)
$$

whenever the right side is finite.

So the profile geometry is bounded by resolved route growth only after accounting for the observation lag.

---

# 7. Coherent branches and generalized branches

Let

$$
C_\infty=
\varprojlim_n C_n.
$$

An element

$$
\mathbf c=(c_0,c_1,c_2,\ldots)
$$

is a coherent sequence of progressively refined exact profile classes.

Every actual tail end produces one such branch:

$$
\beta:X\longrightarrow C_\infty,
\qquad
\beta(\tau)=([\tau]_0,[\tau]_1,\ldots).
$$

Its kernel is exactly full Martin equivalence:

$$
\beta(\tau)=\beta(\sigma)
\iff
h_\tau=h_\sigma.
$$

Define the generalized branch set

$$
\mathcal G_t=
C_\infty\setminus\beta(X).
$$

These are coherent finite-observation profiles not realized by any actual tail end.

There is then an exact algebraic sequence

$$
0
\to
\mathfrak D_M
\to
k^{(X)}
\xrightarrow{\beta_*}
k^{(C_\infty)}
\to
k^{(\mathcal G_t)}
\to0.
$$

This is the clean separation between:

* **collapse**, measured by the kernel $\mathfrak D_M$;
* **completion**, measured by the cokernel $k^{(\mathcal G_t)}$.

Several histories can collapse to one branch, while other branches can be added without being represented by any history.

---

# 8. Compact realization theorem

Suppose:

1. $X$ is compact;
2. every finite-coordinate profile map
$$
   \Phi_F:X\to\mathbb R^F
$$
   is continuous.

Let

$$
Y_F=\Phi_F(X).
$$

Because $X$ is compact, every $Y_F$ is compact and therefore closed.

Then

$$
\Phi_t(X)
\cong
\varprojlim_{F\Subset V_o}Y_F.
$$

In particular, every coherent family of **realized finite profiles** is realized by at least one point of $X$.

### Proof

Take a compatible family

$$
(y_F)_F.
$$

For every finite $F$, define

$$
A_F=\{\tau\in X:\Phi_F(\tau)=y_F\}.
$$

Each $A_F$ is nonempty and closed. Compatibility gives

$$
A_{F\cup F'}\subseteq A_F\cap A_{F'}.
$$

Thus the family has the finite-intersection property. Compactness of $X$ gives

$$
\bigcap_FA_F\ne\varnothing.
$$

Any point in the intersection realizes the whole compatible profile.

Therefore:

$$
\text{compact history space + continuous profile map}
\Longrightarrow
\mathcal G_t=\varnothing
$$

for the inverse system built from the realized ray-profile images.

Inverse-limit descriptions of path-space and boundary data are standard in the theory of Bratteli-type diagrams; the same compactness mechanism is operating here.

---

# 9. This does not yet realize the full Martin compactification

The compact realization theorem concerns

$$
\Phi_t(X),
$$

the image of actual regular ends.

The full node Martin compactification is

$$
\mathcal M_t=
\overline{
{K_t(,\cdot,,x):x\in V_o}
}.
$$

It can contain profiles not generated by any ray, even when every coherent branch of the ray-profile refinement diagram is realized.

If $X$ is compact and $\Phi_t$ is continuous, then $\Phi_t(X)$ is closed. Therefore

$$
\text{every Martin point is ray-generated}
\iff
\Phi_t(X)=\mathcal M_t^{\partial}.
$$

So there are two different possible completion defects:

$$
C_\infty\setminus\beta(X)
$$

for completion of the observation diagram of actual ends, and

$$
\mathcal M_t^{\partial}\setminus\Phi_t(X)
$$

for Martin points not generated by actual ends.

The first vanishes under compactness and continuity. The second may still survive.

---

# 10. A sufficient ray-realization condition

Assume:

1. the rooted infinite-path space $X$ is compact;
2. every sufficiently deep node lies on an infinite ray;
3. $\Phi_t:X\to\mathcal M_t$ is continuous;
4. Green columns approach ray profiles uniformly along deep prefixes:

for every finite $F\Subset V_o$ and every $\varepsilon>0$, there is $N$ such that

$$
d_F\bigl(K_t(,\cdot,,x),\Phi_t(\xi)\bigr)<\varepsilon
$$

whenever $x$ is the endpoint of a prefix of $\xi$ of length at least $N$.

Then every Martin boundary point is generated by a ray.

### Proof

Let

$$
K_t(,\cdot,,x_i)\longrightarrow h
$$

with $x_i$ escaping every finite-depth region.

Choose a ray $\xi_i$ passing through $x_i$. Compactness gives a subnet

$$
\xi_i\longrightarrow\xi.
$$

Continuity gives

$$
\Phi_t(\xi_i)\longrightarrow\Phi_t(\xi).
$$

Uniform prefix approximation gives

$$
K_t(,\cdot,,x_i)-\Phi_t(\xi_i)\longrightarrow0
$$

on every finite observation set. Hence

$$
h=\Phi_t(\xi).
$$

So

$$
\mathcal M_t^\partial=\Phi_t(X).
$$

The essential hypothesis is the uniform convergence of deep node columns toward the profile of the ray containing them.

---

# 11. Examples

### Unique-route (d)-ary tree

At depth $n$, a ray profile is determined by its length-$n$ prefix.

Thus

$$
c_n=d^n,
$$

$$
\Lambda_{\mathrm{split}}=d,
$$

and for sufficiently small $\varepsilon$,

$$
\mathcal N_n(\varepsilon)=d^n.
$$

Also,

$$
\ell_t(n,\varepsilon)=n
$$

for the natural separated profile scale.

The ray space is compact, every compatible prefix branch is an actual ray, and every Martin point is ray-generated.

Here the node boundary preserves the full route boundary.

---

### Diamond followed by one tail

There are two route histories but only one node Martin profile.

Hence

$$
c_n=1
\qquad\forall n,
$$

and

$$
\Lambda_{\mathrm{split}}=1.
$$

The permanent defect is nonzero:

$$
\mathfrak D_M=
k(\delta_{\xi_a}-\delta_{\xi_b}).
$$

But there is no generalized branch:

$$
\mathcal G_t=\varnothing.
$$

This is pure collapse without completion.

---

### Complete layered mixing

The prefix boundary can contain an uncountable family of histories, but every history has the same node profile.

Again,

$$
c_n=1,
\qquad
\mathcal N_n(\varepsilon)=1,
\qquad
\Lambda_{\mathrm{split}}=1.
$$

The permanent Martin defect is enormous, but the node-observation refinement diagram is trivial.

This demonstrates:

$$
\text{route-boundary size and node-profile growth are independent.}
$$

---

### Infinite emitter with disjoint infinite rays

Let $o$ emit one edge into each disjoint infinite chain

$$
\xi_1,\xi_2,\xi_3,\ldots.
$$

The literal ray space

$$
X=\{\xi_1,\xi_2,\ldots\}
$$

is noncompact.

Observe successively the first $n$ branch-entry nodes. Then $C_n$ has:

* one class for each $\xi_1,\ldots,\xi_n$;
* one residual class containing every $\xi_m$ with $m>n$.

Thus

$$
c_n=n+1.
$$

There is a coherent branch that remains in the residual class for every $n$, but no actual ray belongs to every residual class:

$$
\bigcap_{n\ge1}
{\xi_m:m>n}=
\varnothing.
$$

Therefore

$$
\mathcal G_t\ne\varnothing.
$$

The generalized profile has

$$
h(o)=1
$$

and

$$
h(v)=0
$$

at every node lying on a named outgoing branch.

It represents mass escaping through the infinite emitter without selecting any one actual ray.

This is completion without route collapse: every actual ray remains distinguishable, but the noncompact observation diagram adds one generalized exit.

---

# 12. The resulting invariant package

The observation-refinement geometry now has four distinct components.

## Exact splitting

$$
\mathrm{gr}_{\mathrm{obs}}\mathfrak D
$$

records which history distinctions first become exactly visible at each observation layer.

## Quantitative profile complexity

$$
\mathcal N_F(\varepsilon)
$$

or, in the locally finite rooted case,

$$
\Lambda_{\mathrm{obs}}(\varepsilon)
$$

records how many distinguishable profile regions exist at finite precision.

## History-to-profile locality

$$
\ell_t(n,\varepsilon)
$$

records how much route history is required to predict shallow node asymptotics.

## Realization defect

$$
\mathcal G_t=
C_\infty\setminus\beta(X)
$$

records coherent profile branches with no actual historical realization.

These answer different questions and cannot be reduced to one scalar.
