## 1. Three depthwise multiplicity quantities

For length $n$, define

$$
B_n^+=
\sup_u\sum_vN_n(v,u),
$$

$$
B_n^-=
\sup_v\sum_uN_n(v,u),
$$

and

$$
M_n=
\sup_{u,v}N_n(v,u).
$$

These control three operators:

$$
|S_+^n|^2=B_n^+,
$$

$$
|S_-^n|^2=B_n^-,
$$

and, when $M_n<\infty$,

$$
|\Sigma_n|^2=M_n.
$$

Their meanings differ:

* $B_n^+$ measures all length-$n$ branching from one source;
* $B_n^-$ measures all length-$n$ reconvergence into one target;
* $M_n$ measures reconvergence for one fixed endpoint pair.

Always,

$$
M_n\le B_n^+,
\qquad
M_n\le B_n^-.
$$

So bounded total forward or backward path growth implies bounded endpoint collapse at that depth.

The converse fails sharply.

---

# 2. Three singular depths

Define

$$
\delta_{\mathrm{br}}=
\inf{n\ge1:B_n^+=\infty},
$$

$$
\delta_{\mathrm{ub}}=
\inf{n\ge1:M_n=\infty},
$$

where $M_n=\infty$ includes unbounded finite fiber sizes, and

$$
\delta_{\mathrm{nc}}=
\inf
\left\{
n\ge1:
N_n(v,u)\text{ is infinite for some }u,v
\right\}.
$$

Then

$$
\delta_{\mathrm{br}}
\le
\delta_{\mathrm{ub}}
\le
\delta_{\mathrm{nc}}.
$$

The first failure concerns branching somewhere from a source. The second concerns lack of a uniform endpoint-fiber bound. The third requires an infinite route fiber.

Use $+\infty$ if the corresponding failure never occurs.

## An asymmetry

Because

$$
B_{m+n}^+\le B_m^+B_n^+,
$$

we have:

$$
B_1^+<\infty
\quad\Longrightarrow\quad
B_n^+\le(B_1^+)^n<\infty
$$

for every $n$.

Therefore

$$
\delta_{\mathrm{br}}\in\{1,\infty\}.
$$

Global forward branching is either already unbounded at the primitive-channel level or remains bounded at every finite depth.

Endpoint collapse is different. Even when

$$
M_1=1,
$$

we may have

$$
M_2=\infty
$$

because arbitrarily many or infinitely many intermediate sectors reconverge.

Thus $\delta_{\mathrm{ub}}$ and $\delta_{\mathrm{nc}}$ can occur at genuinely higher depths.

---

# 3. Exact closability criterion under composition

Recall

$$
N_{m+n}(v,u)=
\sum_wN_m(v,w)N_n(w,u).
$$

Therefore $\Sigma_{m+n}$ is closable exactly when

$$
\sum_wN_m(v,w)N_n(w,u)<\infty
\qquad
\text{for every }u,v.
$$

Since these are nonnegative cardinal sums, this means precisely:

1. every contributing product
$$
   N_m(v,w)N_n(w,u)
$$
   is finite; and
2. only finitely many intermediate nodes $w$ contribute positively for each endpoint pair.

Hence nonclosability at depth $m+n$ has two distinct causes.

## Inherited singularity

For some $w$,

$$
N_m(v,w)N_n(w,u)
$$

is infinite.

An already-infinite route family has been prefixed or suffixed by another path family.

## Fresh factorization singularity

Every product is finite, but

$$
\left|
\left\{
w:
N_m(v,w)N_n(w,u)>0
\right\}
\right|
$$

is infinite.

Infinitely many finite intermediate sectors reconverge onto one endpoint pair.

Thus:

$$
N_{m+n}(v,u)\text{ is infinite}
$$

if and only if either

$$
\exists w:
N_m(v,w)N_n(w,u)\text{ is infinite}
$$

or

$$
\text{infinitely many }w
\text{ give positive finite products}.
$$

This is the exact cardinal decomposition of higher-depth nonclosability.

---

# 4. Exact boundedness criterion

When all route fibers are finite,

$$
|\Sigma_{m+n}|^2=
\sup_{u,v}
\sum_w
N_m(v,w)N_n(w,u).
$$

Therefore $\Sigma_{m+n}$ is bounded if and only if the weighted number of admissible cut sectors is uniformly bounded over all endpoint pairs.

This gives the sufficient estimates

$$
M_{m+n}\le M_mB_n^+,
$$

and

$$
M_{m+n}\le M_nB_m^-.
$$

Consequently,

$$
|\Sigma_{m+n}|
\le
\min
\left\{
|\Sigma_m|,|S_+^n|,
;
|\Sigma_n|,|S_-^m|
\right\}.
$$

But these inequalities can be strict because they replace the actual compatibility pattern of intermediate nodes by global suprema.

---

# 5. Regularity is not monotone in depth

A singularity at one length need not persist.

For example, take disjoint pairs $u_k,v_k$ with $k$ parallel edges

$$
u_k\to v_k,
$$

and make every $v_k$ a sink.

Then

$$
M_1=\infty
$$

as a supremum, so $\Sigma_1$ is unbounded but closable.

Yet

$$
M_n=0
\qquad(n\ge2),
$$

so every later collapse operator is bounded.

Likewise, an infinite route fiber may terminate at a sink and fail to propagate.

## Propagation with extensions

If

$$
N_n(v,u)
$$

is infinite and there is at least one length-$m$ path

$$
v\to x,
$$

then

$$
N_{n+m}(x,u)
\ge
N_m(x,v)N_n(v,u)
$$

is infinite.

Similarly, any path entering $u$ propagates the singularity backward in compositional depth.

Thus singularity propagates exactly along available extensions, not merely because the integer depth increases.

---

# 6. Strict examples for the three thresholds

## Infinite branching without reconvergence

Let one node $u$ have one edge to each of infinitely many sinks $v_i$.

Then

$$
B_1^+=\infty,
$$

but

$$
N_1(v_i,u)=1
$$

and every endpoint fiber has size at most one.

Therefore

$$
\delta_{\mathrm{br}}=1,
\qquad
\delta_{\mathrm{ub}}=\delta_{\mathrm{nc}}=\infty.
$$

The forward Fock creator is unbounded, but endpoint collapse remains bounded.

## Later unbounded but closable collapse

For each $k$, form a finite fan

$$
u_k\to w_{k,1},\ldots,w_{k,k}\to v_k
$$

with one edge per segment.

At length one,

$$
M_1=1.
$$

At length two,

$$
N_2(v_k,u_k)=k.
$$

Hence

$$
M_2=\infty
$$

as a supremum, but every individual fiber is finite.

Thus

$$
\delta_{\mathrm{br}}=1,
\qquad
\delta_{\mathrm{ub}}=2,
\qquad
\delta_{\mathrm{nc}}=\infty.
$$

The operator $\Sigma_2$ is closed and unbounded.

## Later nonclosable collapse

Take infinitely many disjoint length-$k$ paths from one node $u$ to one node $v$, with no reconvergence before the final node.

Then for

$$
j<k,
$$

every endpoint pair supports at most one length-$j$ path:

$$
M_j=1.
$$

But

$$
N_k(v,u)=\infty.
$$

Therefore

$$
\delta_{\mathrm{ub}}=
\delta_{\mathrm{nc}}=
k.
$$

The first nonclosable collapse can occur at any prescribed finite compositional depth.

---

# 7. Local finiteness and closability

Suppose every node has finitely many outgoing primitive channels, counting multiplicity.

Then, for each fixed source $u$ and each finite $n$, only finitely many length-$n$ paths begin at $u$.

Therefore

$$
N_n(v,u)<\infty
$$

for every $u,v,n$.

Hence:

$$
\text{finite outgoing degree at every node}
\Longrightarrow
\Sigma_n\text{ is closable for every }n.
$$

The degrees need not be uniformly bounded. Thus the operators can still be unbounded.

Dually, finite incoming degree at every node also guarantees finite endpoint fibers at every finite depth.

If there is a uniform outgoing-degree bound $D$, then

$$
B_n^+\le D^n,
$$

so

$$
M_n\le D^n
$$

and

$$
|\Sigma_n|\le D^{n/2}.
$$

A1–A5 imply none of these local-finiteness properties.

---

# 8. A collapse-growth exponent

When every $\Sigma_n$ is bounded, define

$$
\rho_{\mathrm{col}}=
\limsup_{n\to\infty}
|\Sigma_n|^{1/n}=
\limsup_{n\to\infty}
M_n^{1/(2n)}.
$$

This measures exponential endpoint reconvergence.

Since

$$
M_n\le B_n^+,
\qquad
M_n\le B_n^-,
$$

we obtain

$$
\rho_{\mathrm{col}}
\le
\min{r(S_+),r(S_-)}.
$$

Thus endpoint reconvergence cannot grow faster than either:

* total forward route growth;
* total backward route growth.

But it can be dramatically smaller.

## Branching tree

For a $d$-ary tree,

$$
M_n=1,
$$

so

$$
\rho_{\mathrm{col}}=1,
$$

while

$$
r(S_+)=\sqrt d.
$$

## Parallel funnel

For a $d$-parallel chain,

$$
M_n=d^n,
$$

so

$$
\rho_{\mathrm{col}}=\sqrt d=r(S_+)=r(S_-).
$$

The same total path-growth exponent can therefore split into very different collapse-growth exponents.

---

# 9. The all-length endpoint-collapse operator

The fixed-length operators can be assembled into one length-weighted map.

Let

$$
\mathcal H_{\mathrm{path}}=
\ell^2(\mathsf P(G))=
\bigoplus_{n\ge0}\mathcal H_n.
$$

For $z\in\mathbb C$, define algebraically

$$
\Sigma(z)^0\xi_p=
z^{|p|}\eta_{r(p),s(p)}.
$$

This map forgets both:

* the individual route;
* its exact length as a separate output coordinate.

But the length survives as the weight $z^{|p|}$.

For each endpoint pair, define the nonnegative path series

$$
H_{v,u}(r)=
\sum_{n\ge0}N_n(v,u)r^n.
$$

Then the squared norm of the endpoint block of $\Sigma(z)$ is

$$
H_{v,u}(|z|^2).
$$

---

# 10. Exact all-length trichotomy

The operator $\Sigma(z)^0$ is bounded if and only if

$$
\sup_{u,v}
H_{v,u}(|z|^2)<\infty.
$$

In that case,

$$
|\Sigma(z)|^2=
\sup_{u,v}
H_{v,u}(|z|^2).
$$

It is closable if and only if

$$
H_{v,u}(|z|^2)<\infty
\qquad
\text{for every }u,v.
$$

If this series diverges for even one endpoint pair, then $\Sigma(z)^0$ is nonclosable.

## Why divergence gives nonclosability

Fix an endpoint pair whose coefficient family is not square summable. For a finite route subset $F$, put

$$
a_p=z^{|p|}
$$

and define

$$
x_F=
\frac{1}{\sum_{p\in F}|a_p|^2}
\sum_{p\in F}\overline\{a_p\},\xi_p.
$$

Then

$$
\Sigma(z)^0x_F=\eta_{v,u},
$$

while

$$
|x_F|=
\frac{1}{
\sqrt{\sum_{p\in F}|a_p|^2}
}
\longrightarrow0
$$

as the finite subsets exhaust a family whose square sum diverges.

Thus the graph again approaches

$$
(0,\eta_{v,u}).
$$

---

# 11. Positive generating operator

When $\Sigma(z)$ is closed, define

$$
D(z)=\Sigma(z)\Sigma(z)^\ast.
$$

It acts diagonally:

$$
D(z)\eta_{v,u}=
H_{v,u}(|z|^2)\eta_{v,u}.
$$

Therefore

$$
D(z)=
\sum_{n\ge0}|z|^{2n}D_n
$$

in the appropriate diagonal operator sense.

This packages the entire multiplicity tower into one positive object.

It is the Hilbert-space form of the endpoint path-count series, evaluated at the squared modulus because route amplitudes combine quadratically.

---

# 12. Weighted equal-route directions

Assume

$$
0<H_{v,u}(|z|^2)<\infty.
$$

Define

$$
\omega_{v,u}(z)=
\frac{1}{
\sqrt{H_{v,u}(|z|^2)}
}
\sum_{p:u\to v}
\overline z^{,|p|}\xi_p.
$$

Then

$$
|\omega_{v,u}(z)|=1
$$

and

$$
\Sigma(z)\omega_{v,u}(z)=
\sqrt{H_{v,u}(|z|^2)},\eta_{v,u}.
$$

The weighted route-defect space is

$$
\mathcal D_{v,u}(z)=
\left\{
x:
\sum_{p:u\to v}z^{|p|}x_p=0
\right\}.
$$

Hence

$$
\ell^2(\mathsf P(u,v))=
\mathbb C\omega_{v,u}(z)
\oplus
\mathcal D_{v,u}(z).
$$

The all-length polar decomposition is

$$
\Sigma(z)=D(z)^{1/2}U(z),
$$

where $U(z)$ sends each weighted equal-route direction to its endpoint-pair basis vector and kills the weighted defect space.

The variable $z$ does not represent time. It weights the intrinsic path-length grading already present in the path algebra.

---

# 13. Collapse radius

Let

$$
\rho_{\mathrm{col}}=
\limsup_{n\to\infty}
M_n^{1/(2n)}.
$$

Then:

$$
|z|<\rho_{\mathrm{col}}^{-1}
\quad\Longrightarrow\quad
\Sigma(z)\text{ is bounded},
$$

and

$$
|z|>\rho_{\mathrm{col}}^{-1}
\quad\Longrightarrow\quad
\Sigma(z)\text{ is unbounded}.
$$

Behavior on the boundary may depend on finer growth.

Thus

$$
R_{\mathrm{col}}=
\rho_{\mathrm{col}}^{-1}
$$

is the global endpoint-collapse radius.

For one endpoint pair, define

$$
\rho_{v,u}=
\limsup_{n\to\infty}
N_n(v,u)^{1/(2n)}.
$$

Its weighted equal-route vector exists for

$$
|z|<\rho_{v,u}^{-1}
$$

and fails to exist for

$$
|z|>\rho_{v,u}^{-1}.
$$

This gives a local collapse radius for every ordered pair.

---

# 14. Comparison with the Fock resolvent radius

Since

$$
M_n\le B_n^+,
$$

we have

$$
\rho_{\mathrm{col}}\le r(S_+).
$$

Likewise,

$$
\rho_{\mathrm{col}}\le r(S_-).
$$

Therefore

$$
R_{\mathrm{col}}
\ge
\max
\left\{
\frac1{r(S_+)},
\frac1{r(S_-)}
\right\}.
$$

The endpoint-collapse generating operator can remain bounded beyond the radius at which the global Fock route sum ceases to converge.

## (d)-ary tree

Here

$$
M_n=1,
$$

so

$$
R_{\mathrm{col}}=1.
$$

But

$$
r(S_+)=\sqrt d,
$$

so the global Fock resolvent has radius

$$
\frac1{\sqrt d}.
$$

Branching destroys global route summability long before endpoint reconvergence becomes singular.

## (d)-parallel funnel

Here

$$
M_n=d^n,
$$

so

$$
R_{\mathrm{col}}=
\frac1{\sqrt d}.
$$

This agrees with the Fock radius. All route growth is concentrated into one endpoint fiber.
