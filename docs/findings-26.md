# 1. Three depthwise multiplicity quantities

For length $n$, define

```math
B_n^+=\sup_u\sum_vN_n(v,u),
\qquad
B_n^-=\sup_v\sum_uN_n(v,u),
\qquad
M_n=\sup_{u,v}N_n(v,u).
```

These quantities control three operators:

```math
|S_+^n|^2=B_n^+,
\qquad
|S_-^n|^2=B_n^-,
\qquad
|\Sigma_n|^2=M_n.
```

Their meanings differ: $B_n^+$ measures all length-$n$ branching from one source, $B_n^-$ measures all length-$n$ reconvergence into one target, and $M_n$ measures reconvergence for one fixed endpoint pair.

Always,

```math
M_n\le B_n^+,
\qquad
M_n\le B_n^-.
```

Bounded total forward or backward path growth implies bounded endpoint collapse at that depth.

The converse fails sharply.

---

# 2. Three singular depths

Define the three singular depths by

```math
\delta_{\mathrm{br}}=
\inf{n\ge1:B_n^+=\infty},
\qquad
\delta_{\mathrm{ub}}=
\inf{n\ge1:M_n=\infty},
```

and

```math
\delta_{\mathrm{nc}}=
\inf
\left\lbrace n\ge1: N_n(v,u)\text{ is infinite for some }u,v \right\rbrace.
```

Here $M_n=\infty$ includes the case of unbounded finite fiber sizes.

It follows that

```math
\delta_{\mathrm{br}}
\le
\delta_{\mathrm{ub}}
\le
\delta_{\mathrm{nc}}.
```

The third failure requires an infinite route fiber; the first two concern source branching and lack of a uniform endpoint-fiber bound.

Use $+\infty$ if the corresponding failure never occurs.

## An asymmetry

Because

```math
B_{m+n}^+\le B_m^+B_n^+,
```

The resulting bound is

```math
B_1^+<\infty
\quad\Longrightarrow\quad
B_n^+\le(B_1^+)^n<\infty
```

for every $n$.

```math
\delta_{\mathrm{br}}\in\{1,\infty\}.
```

Global forward branching is either already unbounded at the primitive-channel level or remains bounded at every finite depth.

Endpoint collapse is different. Even when

```math
M_1=1,
```

Equivalently,

```math
M_2=\infty
```

because arbitrarily many or infinitely many intermediate sectors reconverge.

Thus $\delta_{\mathrm{ub}}$ and $\delta_{\mathrm{nc}}$ can occur at genuinely higher depths.

---

# 3. Exact closability criterion under composition

Recall

```math
N_{m+n}(v,u)=
\sum_wN_m(v,w)N_n(w,u).
```

$\Sigma_{m+n}$ is closable exactly when

```math
\sum_wN_m(v,w)N_n(w,u)<\infty
\qquad
\text{for every }u,v.
```

Since these are nonnegative cardinal sums, this means precisely:

1. every contributing product $N_m(v,w)N_n(w,u)$ is finite; and
2. only finitely many intermediate nodes $w$ contribute positively for each endpoint pair.

Hence nonclosability at depth $m+n$ has two distinct causes. An inherited singularity occurs when, for some $w$,

```math
N_m(v,w)N_n(w,u)
```

is infinite; an already-infinite route family has then been prefixed or suffixed by another path family. A fresh factorization singularity occurs when every such product is finite but

```math
\left| \left\lbrace w: N_m(v,w)N_n(w,u)>0 \right\rbrace \right|
```

is infinite, so infinitely many finite intermediate sectors reconverge onto one endpoint pair.

```math
N_{m+n}(v,u)\text{ is infinite}
```

if and only if either

```math
\exists w:
N_m(v,w)N_n(w,u)\text{ is infinite}
```

or

```math
\text{infinitely many }w
\text{ give positive finite products}.
```

The formula decomposes higher-depth nonclosability by cardinality.

---

# 4. Exact boundedness criterion

When all route fibers are finite,

```math
|\Sigma_{m+n}|^2=
\sup_{u,v}
\sum_w
N_m(v,w)N_n(w,u).
```

$\Sigma_{m+n}$ is bounded if and only if admissible cut-sector weight is uniformly bounded over all endpoint pairs.

The decomposition gives the estimates

```math
M_{m+n}\le M_mB_n^+,
```

and

```math
M_{m+n}\le M_nB_m^-.
```

The corresponding inequality is

```math
|\Sigma_{m+n}|
\le
\min
\left\lbrace |\Sigma_m|,|S_+^n|,|\Sigma_n|,|S_-^m| \right\rbrace.
```

These inequalities can be strict because global suprema replace the actual compatibility pattern of intermediate nodes.

---

# 5. Regularity is not monotone in depth

A singularity at one length need not persist.

For example, take disjoint pairs $u_k,v_k$ with $k$ parallel edges

```math
u_k\to v_k,
```

and make every $v_k$ a sink.

It follows that

```math
M_1=\infty
```

as a supremum, so $\Sigma_1$ is unbounded but closable.

Yet

```math
M_n=0
\qquad(n\ge2),
```

so every later collapse operator is bounded.

Likewise, an infinite route fiber may terminate at a sink and fail to propagate.

## Propagation with extensions

If

```math
N_n(v,u)
```

is infinite and there is at least one length-$m$ path

```math
v\to x,
```

it follows that

```math
N_{n+m}(x,u)
\ge
N_m(x,v)N_n(v,u)
```

is infinite.

Similarly, any path entering $u$ propagates the singularity backward in compositional depth.

Singularity propagates exactly along available extensions, not merely with increasing integer depth.

---

# 6. Strict examples for the three thresholds

## Infinite branching without reconvergence

Let one node $u$ have one edge to each of infinitely many sinks $v_i$.

It follows that

```math
B_1^+=\infty,
```

but

```math
N_1(v_i,u)=1
```

and every endpoint fiber has size at most one.

```math
\delta_{\mathrm{br}}=1,
\qquad
\delta_{\mathrm{ub}}=\delta_{\mathrm{nc}}=\infty.
```

The forward Fock creator is unbounded, but endpoint collapse remains bounded.

## Later unbounded but closable collapse

For each $k$, form a finite fan

```math
u_k\to w_{k,1},\ldots,w_{k,k}\to v_k
```

with one edge per segment.

At length one,

```math
M_1=1.
```

At length two,

```math
N_2(v_k,u_k)=k.
```

Consequently,

```math
M_2=\infty
```

as a supremum, but every individual fiber is finite.

```math
\delta_{\mathrm{br}}=1,
\qquad
\delta_{\mathrm{ub}}=2,
\qquad
\delta_{\mathrm{nc}}=\infty.
```

The operator $\Sigma_2$ is closed and unbounded.

## Later nonclosable collapse

Take infinitely many disjoint length-$k$ paths from one node $u$ to one node $v$, with no reconvergence before the final node.

Then for

```math
j<k,
```

every endpoint pair supports at most one length-$j$ path:

```math
M_j=1.
```

At length $k$, however,

```math
N_k(v,u)=\infty.
```

Equivalently,

```math
\delta_{\mathrm{ub}}=
\delta_{\mathrm{nc}}=
k.
```

The first nonclosable collapse can occur at any prescribed finite compositional depth.

---

# 7. Local finiteness and closability

Suppose every node has finitely many outgoing primitive channels, counting multiplicity.

For each fixed source $u$ and finite $n$, only finitely many length-$n$ paths begin at $u$.

```math
N_n(v,u)<\infty
```

for every $u,v,n$.

```math
\text{finite outgoing degree at every node}
\Longrightarrow
\Sigma_n\text{ is closable for every }n.
```

The degrees need not be uniformly bounded. Thus the operators can still be unbounded.

Dually, finite incoming degree at every node also guarantees finite endpoint fibers at every finite depth.

If there is a uniform outgoing-degree bound $D$, then

```math
B_n^+\le D^n,
```

so

```math
M_n\le D^n
```

and

```math
|\Sigma_n|\le D^{n/2}.
```

The bounded system definition implies none of these local-finiteness properties.

---

# 8. A collapse-growth exponent

When every $\Sigma_n$ is bounded, define

```math
\rho_{\mathrm{col}}=
\limsup_{n\to\infty}
|\Sigma_n|^{1/n}=
\limsup_{n\to\infty}
M_n^{1/(2n)}.
```

The radius measures exponential endpoint reconvergence.

Since

```math
M_n\le B_n^+,
\qquad
M_n\le B_n^-,
```

The corresponding inequality is

```math
\rho_{\mathrm{col}}
\le
\min{r(S_+),r(S_-)}.
```

Endpoint reconvergence cannot grow faster than either:

* total forward route growth;
* total backward route growth.

But it can be dramatically smaller.

## Branching tree

For a $d$-ary tree,

```math
M_n=1,
```

so

```math
\rho_{\mathrm{col}}=1,
```

while

```math
r(S_+)=\sqrt d.
```

## Parallel funnel

For a $d$-parallel chain,

```math
M_n=d^n,
```

so

```math
\rho_{\mathrm{col}}=\sqrt d=r(S_+)=r(S_-).
```

The same total path-growth exponent can therefore split into very different collapse-growth exponents.

---

# 9. The all-length endpoint-collapse operator

The fixed-length operators can be assembled into one length-weighted map.

Define $\mathcal H_{\mathrm{path}}$ by

```math
\mathcal H_{\mathrm{path}}=
\ell^2(\mathsf P(G))=
\bigoplus_{n\ge0}\mathcal H_n.
```

For $z\in\mathbb C$, define algebraically

```math
\Sigma(z)^0\xi_p=
z^{|p|}\eta_{r(p),s(p)}.
```

The map forgets:

* the individual route;
* its exact length as a separate output coordinate.

But the length survives as the weight $z^{|p|}$.

For each endpoint pair, define the nonnegative path series

```math
H_{v,u}(r)=
\sum_{n\ge0}N_n(v,u)r^n.
```

Then the squared norm of the endpoint block of $\Sigma(z)$ is

```math
H_{v,u}(|z|^2).
```

---

# 10. Exact all-length trichotomy

The operator $\Sigma(z)^0$ is bounded if and only if

```math
\sup_{u,v}
H_{v,u}(|z|^2)<\infty.
```

In that case,

```math
|\Sigma(z)|^2=
\sup_{u,v}
H_{v,u}(|z|^2).
```

It is closable if and only if

```math
H_{v,u}(|z|^2)<\infty
\qquad
\text{for every }u,v.
```

If this series diverges for even one endpoint pair, then $\Sigma(z)^0$ is nonclosable.

## Divergence and nonclosability

Fix an endpoint pair whose coefficient family is not square summable. For a finite route subset $F$, put

```math
a_p=z^{|p|}
```

and define

```math
x_F=
\frac{1}{\sum_{p\in F}|a_p|^2}
\sum_{p\in F}\overline{a_p}\,\xi_p.
```

It follows that

```math
\Sigma(z)^0x_F=\eta_{v,u},
```

while

```math
|x_F|=
\frac{1}{
\sqrt{\sum_{p\in F}|a_p|^2}
}
\longrightarrow0
```

as the finite subsets exhaust a family whose square sum diverges.

Thus the graph again approaches

```math
(0,\eta_{v,u}).
```

---

# 11. Positive generating operator

When $\Sigma(z)$ is closed, define

```math
D(z)=\Sigma(z)\Sigma(z)^\ast.
```

It acts diagonally:

```math
D(z)\eta_{v,u}=
H_{v,u}(|z|^2)\eta_{v,u}.
```

Therefore the weighted endpoint operator is

```math
D(z)=
\sum_{n\ge0}|z|^{2n}D_n
```

in the appropriate diagonal operator sense.

The positive operator packages the full multiplicity tower.

The Hilbert-space series uses squared modulus because route amplitudes combine quadratically.

---

# 12. Weighted equal-route directions

Assume $0<H_{v,u}(|z|^2)<\infty$.

Define the normalized endpoint vector by

```math
\omega_{v,u}(z)=
\frac{1}{
\sqrt{H_{v,u}(|z|^2)}
}
\sum_{p:u\to v}
\overline{z}^{\,|p|}\xi_p.
```

It follows that

```math
|\omega_{v,u}(z)|=1
```

and

```math
\Sigma(z)\omega_{v,u}(z)=
\sqrt{H_{v,u}(|z|^2)}\,\eta_{v,u}.
```

The weighted route-defect space is

```math
\mathcal D_{v,u}(z)=
\left\lbrace x: \sum_{p:u\to v}z^{|p|}x_p=0 \right\rbrace.
```

Equivalently,

```math
\ell^2(\mathsf P(u,v))=
\mathbb C\omega_{v,u}(z)
\oplus
\mathcal D_{v,u}(z).
```

The all-length polar decomposition is

```math
\Sigma(z)=D(z)^{1/2}U(z),
```

where $U(z)$ sends each weighted equal-route direction to its endpoint-pair basis vector and kills the weighted defect space.

The variable $z$ weights the path algebra’s intrinsic path-length grading; it does not represent time.

---

# 13. Collapse radius

Define $\rho_{\mathrm{col}}$ by

```math
\rho_{\mathrm{col}}=
\limsup_{n\to\infty}
M_n^{1/(2n)}.
```

It follows that

```math
|z|<\rho_{\mathrm{col}}^{-1}
\quad\Longrightarrow\quad
\Sigma(z)\text{ is bounded},
```

and

```math
|z|>\rho_{\mathrm{col}}^{-1}
\quad\Longrightarrow\quad
\Sigma(z)\text{ is unbounded}.
```

Behavior on the boundary may depend on finer growth.

```math
R_{\mathrm{col}}=
\rho_{\mathrm{col}}^{-1}
```

is the global endpoint-collapse radius.

For one endpoint pair, define

```math
\rho_{v,u}=
\limsup_{n\to\infty}
N_n(v,u)^{1/(2n)}.
```

Its weighted equal-route vector exists for

```math
|z|<\rho_{v,u}^{-1}
```

and fails to exist for

```math
|z|>\rho_{v,u}^{-1}.
```

The formula gives a local collapse radius for each ordered pair.

---

# 14. Comparison with the Fock resolvent radius

Since

```math
M_n\le B_n^+,
```

The corresponding inequality is

```math
\rho_{\mathrm{col}}\le r(S_+).
```

Likewise,

```math
\rho_{\mathrm{col}}\le r(S_-).
```

The resulting bound is

```math
R_{\mathrm{col}}
\ge
\max
\left\lbrace \frac1{r(S_+)}, \frac1{r(S_-)} \right\rbrace.
```

The endpoint-collapse generating operator can remain bounded beyond the global Fock route sum’s convergence radius.

## $d$-ary tree

Here

```math
M_n=1,
```

so

```math
R_{\mathrm{col}}=1.
```

In contrast,

```math
r(S_+)=\sqrt d,
```

so the global Fock resolvent has radius

```math
\frac1{\sqrt d}.
```

Branching destroys global route summability long before endpoint reconvergence becomes singular.

## $d$-parallel funnel

Here

```math
M_n=d^n,
```

so

```math
R_{\mathrm{col}}=
\frac1{\sqrt d}.
```

The local radius equals the Fock radius because all route growth is concentrated in one endpoint fiber.
