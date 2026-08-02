# 1. Exact observation classes

Let $X$ be the set of $t$-Martin-regular tail ends after eventual-tail
collapse, and let

```math
\Phi_t:X\longrightarrow \mathcal M_t,
\qquad
\Phi_t(\tau)=h_\tau
```

be the node-profile map.

For a finite node set $F\Subset V_o$, define

```math
\tau\equiv_F\sigma
\iff
h_\tau(v)=h_\sigma(v)
\quad\forall v\in F.
```

Define $C_F$ by

```math
C_F=X/\!\equiv_F.
```

If $F\subseteq F'$, then $F'$ distinguishes at least as much as $F$, giving a
surjection

```math
\rho_{F',F}:C_{F'}\longrightarrow C_F.
```

The inverse system $\{C_F,\rho_{F',F}\}_{F\Subset V_o}$ is the exact
observation-refinement diagram.

For a locally finite rooted component, the balls

```math
B_n(o)=\{v:d(o,v)\le n\}
```

are finite and exhaust $V_o$. Use the sequence

```math
C_n=C_{B_n(o)}
```

with bonding maps

```math
\rho_n:C_{n+1}\to C_n.
```

For arbitrary branching, the directed system over all finite $F$ remains
primary; there may be no canonical one-parameter sequence of finite
observations.

# 2. Local splitting and the associated graded defect

For $c\in C_n$, define its splitting multiplicity

```math
b_n(c)=|\rho_n^{-1}(c)|.
```

The splitting multiplicity counts the depth-$(n+1)$ profiles hidden inside one
depth-$n$ profile.

If the class sets are finite, then

```math
|C_{n+1}|=
\sum_{c\in C_n}b_n(c).
```

Define $\mathfrak D_n^{\mathrm{obs}}$ by

```math
\mathfrak D_n^{\mathrm{obs}}=
\mathrm{span}
\{
\delta_\tau-\delta_\sigma:
\tau\equiv_{B_n(o)}\sigma
\}.
```

The defect filtration is decreasing:

```math
\mathfrak D_0^{\mathrm{obs}}
\supseteq
\mathfrak D_1^{\mathrm{obs}}
\supseteq
\cdots
\supseteq
\mathfrak D_M,
```

where

```math
\mathfrak D_M=
\bigcap_n\mathfrak D_n^{\mathrm{obs}}
```

is the permanent Martin-collapse defect.

At every level,

```math
0\to
\mathfrak D_{n+1}^{\mathrm{obs}}
\to
\mathfrak D_n^{\mathrm{obs}}
\to
\bigoplus_{c\in C_n}
\widetilde{k}^{(\rho_n^{-1}(c))}
\to0.
```

The associated graded module

```math
\mathrm{gr}_{\mathrm{obs}}\mathfrak D=
\bigoplus_{n\ge0}
\mathfrak D_n^{\mathrm{obs}}/
\mathfrak D_{n+1}^{\mathrm{obs}}
```

records distinctions according to the first observation layer at which they
become visible.

When $C_n$ and $C_{n+1}$ are finite,

```math
\dim
\frac{\mathfrak D_n^{\mathrm{obs}}}
{\mathfrak D_{n+1}^{\mathrm{obs}}}=
|C_{n+1}|-|C_n|.
```

No canonical splitting of these exact sequences is implied. The filtration is
canonical; a direct-sum decomposition into layers generally is not.

# 3. Exact splitting growth

When every $C_n$ is finite, define

```math
c_n=|C_n|.
```

A simple growth invariant is

```math
\Lambda_{\mathrm{split}}=
\limsup_{n\to\infty}c_n^{1/n}.
```

Alternatively, one may retain the complete sequence

```math
(c_0,c_1,c_2,\ldots)
```

and the local branching data

```math
{b_n(c):c\in C_n}.
```

The scalar $\Lambda_{\mathrm{split}}$ is only a compression. Different diagrams
can have the same exponential rate but different splitting patterns.

Three extremal cases occur. If $c_n=1$ for every $n$, there is no node-level
separation and every tail end has the same node Martin profile. A profile is
eventually finitely determined when its class ceases to split after some finite
level; such a profile is isolated in the exact refinement structure. Persistent
refinement occurs when a compatible branch passes through classes that split
infinitely often, so its full profile cannot be determined at any finite
observation depth.

# 4. Failure of exact separation depth to define a topology

The first exact separating depth was defined as

```math
s_t(\tau,\sigma)=
\min{n:h_\tau|_{B_n}\ne h_\sigma|_{B_n}}.
```

It satisfies

```math
s_t(\tau,\zeta)
\ge
\min{s_t(\tau,\sigma),s_t(\sigma,\zeta)}.
```

After quotienting permanent Martin-equivalent ends, one may formally construct
an ultrametric such as

```math
d_\theta(\tau,\sigma)=\theta^{s_t(\tau,\sigma)},
\qquad 0<\theta<1.
```

But this topology can be much finer than the actual Martin topology.

If two profiles differ by $10^{-100}$ at a shallow node, the exact ultrametric
treats them as immediately separated. The Martin product topology treats them as
extremely close.

```math
s_t
\text{ measures logical distinguishability, not quantitative proximity.}
```

# 5. Canonical finite-coordinate profile geometry

Normalize every Martin profile by

```math
\widehat h(v)=
t^{d(o,v)}h(v).
```

The prefix bound gives

```math
0\le\widehat h(v)\le1.
```

For a finite observation set $F$, define the pseudometric

```math
d_F(h,g)=
\max_{v\in F}
|\widehat h(v)-\widehat g(v)|.
```

The pseudometric gives the finite-coordinate geometry of the Martin profiles.

Let $\mathcal N_F(\varepsilon)$ be the minimum number of $d_F$-balls of radius
$\varepsilon$ required to cover the profile image $\Phi_t(X)$.

For a locally finite rooted component, define

```math
\mathcal N_n(\varepsilon)=
\mathcal N_{B_n(o)}(\varepsilon).
```

It follows that

```math
\Lambda_{\mathrm{obs}}(\varepsilon)=
\limsup_{n\to\infty}
\mathcal N_n(\varepsilon)^{1/n}
```

is the observation-growth spectrum at precision $\varepsilon$.

The full family

```math
\varepsilon\longmapsto
\Lambda_{\mathrm{obs}}(\varepsilon)
```

is more informative than one exact class-growth scalar.

If the finite profile set at depth $n$ is discrete with minimum pairwise
separation $\delta_n>0$, then for

```math
\varepsilon<\frac{\delta_n}{2}
```

the exact count is recovered:

```math
\mathcal N_n(\varepsilon)=c_n.
```

In continuous-profile situations, the covering numbers remain meaningful even
when $c_n$ is infinite.

# 6. Finite determination of route profiles

Let $\mathrm{pref}_m(\xi)$ denote the length-$m$ prefix of an infinite history.

Define the approximate observation lag

```math
\ell_t(n,\varepsilon)=
\min\left\lbrace m:
\begin{array}{l}
\mathrm{pref}_m(\xi)=\mathrm{pref}_m(\eta)\\[1mm]
\Longrightarrow d_{B_n(o)}(h_\xi,h_\eta)<\varepsilon
\end{array}
\right\rbrace.
```

Set it to $\infty$ when no finite $m$ works.

Thus $\ell_t(n,\varepsilon)$ measures how much route history is needed to
predict all node observations through depth $n$ to precision $\varepsilon$.

The comparison separates three regimes.

## Profile-locality regimes

When $\ell_t(n,\varepsilon)\approx n$, shallow node profiles are determined by
comparably shallow route history. Strong asymptotic mixing corresponds to
$\ell_t(n,\varepsilon)\ll n$, because little route history is needed when many
histories have nearly identical node profiles. Long-range dependence occurs when

```math
\ell_t(n,\varepsilon)\gg n
\quad\text{or}\quad
\ell_t(n,\varepsilon)=\infty,
```

so even shallow node asymptotics depend on very long, or complete, infinite
history.

If the prefix boundary is compact, finitely branching, and the profile map is
continuous, then

```math
\ell_t(n,\varepsilon)<\infty
```

for every finite $n$ and every $\varepsilon>0$; this is uniform continuity in
the intrinsic cylinder structure.

If $P_m(o)$ is the number of length-$m$ prefixes from $o$, then

```math
\mathcal N_n(\varepsilon)
\le
P_{\ell_t(n,\varepsilon)}(o)
```

whenever the right side is finite.

Thus profile geometry is bounded by resolved route growth only after accounting
for observation lag.

# 7. Coherent branches and generalized branches

Define $C_\infty$ by

```math
C_\infty=
\varprojlim_n C_n.
```

An element

```math
\mathbf c=(c_0,c_1,c_2,\ldots)
```

is a coherent sequence of progressively refined exact profile classes.

Every actual tail end produces one such branch:

```math
\beta:X\longrightarrow C_\infty,
\qquad
\beta(\tau)=([\tau]_0,[\tau]_1,\ldots).
```

Its kernel is exactly full Martin equivalence:

```math
\beta(\tau)=\beta(\sigma)
\iff
h_\tau=h_\sigma.
```

Define the generalized branch set

```math
\mathcal G_t=
C_\infty\setminus\beta(X).
```

These are coherent finite-observation profiles not realized by any actual tail
end.

There is then an exact algebraic sequence

```math
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
```

The distinction is between collapse, measured by the kernel $\mathfrak D_M$,
and completion, measured by the cokernel $k^{(\mathcal G_t)}$.

Several histories can collapse to one branch, whereas other branches can be
added without representing any history.

# 8. Compact realization theorem

Suppose the following hold:

1. $X$ is compact;
2. every finite-coordinate profile map $\Phi_F:X\to\mathbb R^F$ is continuous.

Define $Y_F$ by

```math
Y_F=\Phi_F(X).
```

Because $X$ is compact, every $Y_F$ is compact and therefore closed.

It follows that

```math
\Phi_t(X)
\cong
\varprojlim_{F\Subset V_o}Y_F.
```

In particular, every coherent family of realized finite profiles is realized by
at least one point of $X$.

## Proof

Take a compatible family

```math
(y_F)_F.
```

For every finite $F$, define

```math
A_F=\{\tau\in X:\Phi_F(\tau)=y_F\}.
```

Each $A_F$ is nonempty and closed. Compatibility gives

```math
A_{F\cup F'}\subseteq A_F\cap A_{F'}.
```

The family has the finite-intersection property. Compactness of $X$ gives

```math
\bigcap_FA_F\ne\varnothing.
```

Any point in the intersection realizes the whole compatible profile.

```math
\text{compact history space + continuous profile map}
\Longrightarrow
\mathcal G_t=\varnothing
```

for the inverse system built from the realized ray-profile images.

Inverse-limit descriptions of path-space and boundary data are standard for
Bratteli-type diagrams; the same compactness mechanism operates here.

# 9. Limits of compact realization

The compact realization theorem concerns the image of actual regular ends,

```math
\Phi_t(X).
```

The full node Martin compactification is

```math
\mathcal M_t=
\overline{
{K_t(\cdot,x):x\in V_o}
}.
```

It can contain profiles not generated by any ray, even when every coherent
branch of the ray-profile refinement diagram is realized.

If $X$ is compact and $\Phi_t$ is continuous, then $\Phi_t(X)$ is closed.
Therefore

```math
\text{every Martin point is ray-generated}
\iff
\Phi_t(X)=\mathcal M_t^{\partial}.
```

There are two different possible completion defects:

```math
C_\infty\setminus\beta(X)
```

for completion of the observation diagram of actual ends, and

```math
\mathcal M_t^{\partial}\setminus\Phi_t(X)
```

for Martin points not generated by actual ends.

The first vanishes under compactness and continuity. The second may still
survive.

# 10. A sufficient ray-realization condition

Assume the following:

1. the rooted infinite-path space $X$ is compact;
2. every sufficiently deep node lies on an infinite ray;
3. $\Phi_t:X\to\mathcal M_t$ is continuous;
4. Green columns approach ray profiles uniformly along deep prefixes:

for every finite $F\Subset V_o$ and every $\varepsilon>0$, there is $N$ such
that

```math
d_F\bigl(K_t(\cdot,x),\Phi_t(\xi)\bigr)<\varepsilon
```

whenever $x$ is the endpoint of a prefix of $\xi$ of length at least $N$.

Then every Martin boundary point is generated by a ray.

## Proof

Choose nodes $x_i$ escaping every finite-depth region such that

```math
K_t(\cdot,x_i)\longrightarrow h.
```

Choose a ray $\xi_i$ passing through $x_i$. Compactness gives a subnet

```math
\xi_i\longrightarrow\xi.
```

Continuity gives

```math
\Phi_t(\xi_i)\longrightarrow\Phi_t(\xi).
```

Uniform prefix approximation gives

```math
K_t(\cdot,x_i)-\Phi_t(\xi_i)\longrightarrow0
```

on every finite observation set. Hence

```math
h=\Phi_t(\xi).
```

Consequently,

```math
\mathcal M_t^\partial=\Phi_t(X).
```

The proof uses hypothesis 4, uniform convergence of deep node columns toward
the profile of the ray containing them.

# 11. Examples

## Unique-route $d$-ary tree

At depth $n$, a ray profile is determined by its length-$n$ prefix.

```math
c_n=d^n,
```

so

```math
\Lambda_{\mathrm{split}}=d,
```

and for sufficiently small $\varepsilon$,

```math
\mathcal N_n(\varepsilon)=d^n.
```

Also,

```math
\ell_t(n,\varepsilon)=n
```

for the natural separated profile scale.

The ray space is compact, every compatible prefix branch is an actual ray, and
every Martin point is ray-generated.

Here the node boundary preserves the full route boundary.

### Diamond followed by one tail

There are two route histories but only one node Martin profile.

```math
c_n=1
\qquad\forall n,
```

and

```math
\Lambda_{\mathrm{split}}=1.
```

The permanent defect is nonzero:

```math
\mathfrak D_M=
k(\delta_{\xi_a}-\delta_{\xi_b}).
```

But there is no generalized branch:

```math
\mathcal G_t=\varnothing.
```

The example exhibits collapse without completion.

### Complete layered mixing

The prefix boundary can contain an uncountable family of histories, but every
history has the same node profile.

Again,

```math
c_n=1,
\qquad
\mathcal N_n(\varepsilon)=1,
\qquad
\Lambda_{\mathrm{split}}=1.
```

The permanent Martin defect is infinite-dimensional, but the node-observation
refinement diagram is trivial.

The example shows that route-boundary size does not determine node-profile
growth.

### Infinite emitter with disjoint infinite rays

Let $o$ emit one edge into each disjoint infinite chain

```math
\xi_1,\xi_2,\xi_3,\ldots.
```

The literal ray space

```math
X=\{\xi_1,\xi_2,\ldots\}
```

is noncompact.

Observe successively the first $n$ branch-entry nodes. Then $C_n$ has:

* one class for each $\xi_1,\ldots,\xi_n$;
* one residual class containing every $\xi_m$ with $m>n$.

```math
c_n=n+1.
```

A coherent branch remains in the residual class for every $n$, but no actual
ray lies in every residual class:

```math
\bigcap_{n\ge1}
{\xi_m:m>n}=
\varnothing.
```

Thus the realization defect is nonempty:

```math
\mathcal G_t\ne\varnothing.
```

The generalized profile has

```math
h(o)=1
```

and

```math
h(v)=0
```

at every node lying on a named outgoing branch.

It represents mass escaping through the infinite emitter without selecting any
one actual ray.

Completion occurs without route collapse: every actual ray remains
distinguishable, but the noncompact observation diagram adds one generalized
exit.
