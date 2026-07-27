# 1. Green recursion

Every path from $v$ to $x$ is either:

* the identity path, when $v=x$; or
* an edge $e:v\to w$, followed by a path $w\to x$.

Therefore

```math
G_t(v,x)=
\delta_{v,x}
+
t\sum_{e:s(e)=v}G_t(r(e),x).
```

At a finite emitter, this is an ordinary finite sum.

At an infinite emitter, it is an equality in the extended nonnegative reals; to use scalar Martin kernels, we restrict to endpoint pairs for which the value is finite.

The standard Martin construction likewise begins with a Green kernel and normalizes its columns by a reference state. 

---

# 2. The node Martin kernel

For every node $x$ reachable from $o$, with

```math
0<G_t(o,x)<\infty,
```

define

```math
K_t(v,x)=
\frac{G_t(v,x)}{G_t(o,x)}.
```

Then

```math
K_t(o,x)=1.
```

If $q:o\to v$ is any fixed path, every path $v\to x$ can be prefixed by $q$. Hence

```math
G_t(o,x)
\ge
t^{|q|}G_t(v,x),
```

so

```math
0\le K_t(v,x)\le t^{-|q|}.
```

Thus each coordinate $K_t(v,x)$ is uniformly bounded as $x$ varies.

The map

```math
x\longmapsto K_t(\cdot,x)
```

places the reachable nodes inside the product

```math
\prod_{v\in V_o}[0,C_v],
```

where $C_v=t^{-|q_v|}$ for one chosen route $q_v:o\to v$.

Its closure is compact in the product topology.

We may therefore define the **weighted node Martin compactification**

```math
\overline V_t^{\,M}=
\overline{
{K_t(\cdot,x):x\in V_o}
}.
```

The added points constitute its node Martin boundary

```math
\partial_t^M V=
\overline V_t^{\,M}\setminus V_o.
```

For countable transient Markov kernels, this is the usual Martin compactification; the product-closure formulation above remains meaningful for arbitrary set-sized systems whenever the Green columns are finite. Standard Martin theory defines convergence exactly through coordinatewise convergence of the normalized kernels. 

---

# 3. Boundary limits are harmonic

For an ordinary node $x$,

```math
K_t(v,x)-
t\sum_{e:v\to w}K_t(w,x)=
\frac{\delta_{v,x}}{G_t(o,x)}.
```

The right side is the point defect at the terminal node $x$.

Now let $x_i$ escape through the graph and suppose

```math
K_t(v,x_i)\longrightarrow h(v)
```

for every fixed $v$.

At a finite emitter, eventually $x_i\ne v$, so the point defect vanishes and

```math
h(v)=
t\sum_{e:v\to w}h(w).
```

Equivalently,

```math
\mathcal A_+h=t^{-1}h.
```

At an infinite emitter, every finite edge subset $F$ gives

```math
h(v)
\ge
t\sum_{e\in F}h(r(e)).
```

Thus node Martin boundary points produce exactly the harmonic or superharmonic functions derived in the preceding section.

---

# 4. Minimal harmonic functions

Let

```math
\mathscr H_t(o)=
\left\lbrace h\ge0: h(o)=1,\quad h(v)=t\sum_{v\to w}h(w) \right\rbrace
```

in a setting where the sums are defined.

A nonzero positive harmonic function $h$ is **minimal** when

```math
0\le g\le h,\qquad g\text{ harmonic}
```

implies

```math
g=ch
```

for some scalar $0\le c\le1$.

Within the normalized convex set $\mathscr H_t(o)$,

```math
h\text{ is minimal}
\iff
h\text{ is an extreme point}.
```

Indeed, if

```math
h=ah_1+(1-a)h_2,
\qquad0<a<1,
```

then $ah_1\le h$; minimality forces $h_1=h$, and similarly $h_2=h$. The converse follows by normalizing any harmonic $0\le g\le h$.

The **minimal Martin boundary** consists of boundary kernels that are minimal harmonic. The full Martin boundary can be larger than its minimal part; full and minimal boundaries coincide only in special systems.

Under the familiar countable, transient hypotheses, positive harmonic functions admit integral representations over the minimal Martin boundary. For the completely unrestricted A1–A5 setting, the kernel compactification and minimality definition are unconditional once the Green kernels are finite, while a full integral-representation theorem requires additional analytic assumptions. 

---

# 5. Weighted finite bridges to a node

The node kernel has a direct route interpretation.

For a terminal node $x$, place weight

```math
t^{|q|}
```

on every route

```math
q:o\to x.
```

After normalization, this gives the route distribution

```math
\nu_x^t(q)=
\frac{t^{|q|}}{G_t(o,x)}.
```

Indeed,

```math
\sum_{q:o\to x}\nu_x^t(q)=1.
```

This is a static normalized ensemble of paths ending at $x$, not an external temporal law.

Now let $p:o\to v$ be a finite path. The probability that the selected terminal route begins with $p$ is

```math
\begin{aligned}
\mu_x^t[p]
&=
\sum_{\substack{q:o\to x\\p\preceq q}}
\frac{t^{|q|}}{G_t(o,x)}\\
&=
\frac{t^{|p|}G_t(v,x)}{G_t(o,x)}.
\end{aligned}
```

Therefore

```math
\mu_x^t[p]=
t^{|p|}K_t(v,x).
```

The node Martin kernel is thus exactly the terminal-route bridge viewed through a fixed prefix.

---

# 6. Boundary lift to prefix cylinders

Suppose

```math
K_t(\cdot,x_i)\longrightarrow h.
```

Then for every finite route $p:o\to v$,

```math
\mu_{x_i}^t[p]
\longrightarrow
\mu_h[p]=
t^{|p|}h(v).
```

At a finite emitter,

```math
\begin{aligned}
\sum_{e:v\to w}\mu_h[pe]
&=
\sum_e t^{|p|+1}h(w)\\
&=
t^{|p|}
\left(t\sum_eh(w)\right)\\
&=
t^{|p|}h(v)\\
&=
\mu_h[p].
\end{aligned}
```

Thus every node Martin boundary point has a canonical route-sensitive lift:

```math
h
\longmapsto
\left(
p\longmapsto t^{|p|}h(r(p))
\right).
```

But this lift has a strong symmetry:

```math
t^{-|p|}\mu_h[p]
\text{ depends only on }r(p).
```

This is the endpoint-factorization condition derived earlier.

---

# 7. Same-endpoint route law

Let

```math
p,q:o\to v.
```

Their bridge-cylinder weights satisfy

```math
\frac{\mu_x^t[p]}{\mu_x^t[q]}=
t^{|p|-|q|}.
```

The terminal node $x$ has cancelled completely.

Therefore, conditional on the bridge passing through $v$,

```math
\Pr(p\mid\text{reach }v)=
\frac{t^{|p|}}{G_t(o,v)}.
```

This distribution is independent of the eventual destination $x$.

Consequences:

### Equal-length routes

If

```math
|p|=|q|,
```

then

```math
\mu_x^t[p]=\mu_x^t[q].
```

### Shortcut versus composite route

If

```math
|q|=|p|+k,
```

then

```math
\mu_x^t[q]=t^k\mu_x^t[p].
```

So the node Martin construction cannot favor one equal-length route over another having the same endpoint.

It is intrinsically endpoint-compressed.

---

# 8. Fock realization of the finite bridge

Define the normalized endpoint Fock vector

```math
\Omega_x^t=
\frac1{\sqrt{G_t(o,x)}}
\sum_{q:o\to x}
t^{|q|/2}\xi_q.
```

Then

```math
|\Omega_x^t|=1.
```

For the prefix-cylinder projection $P[p]$,

```math
\langle
P[p]\Omega_x^t,\Omega_x^t
\rangle=
\mu_x^t[p]=
t^{|p|}K_t(r(p),x).
```

Thus:

```math
\text{node Martin bridge}=
\text{diagonal state of a normalized orthogonal route vector}.
```

If $x_i$ escapes and the vectors converge weakly to zero, their cylinder states may still converge to the boundary lift $\mu_h$.

This unifies:

* the Fock route representation;
* endpoint Green kernels;
* node harmonic functions;
* boundary cylinder states.

---

# 9. The full prefix-tree Martin kernel

The node construction is not the full route-sensitive Martin construction.

Let

```math
\mathcal T_o
```

be the prefix tree whose vertices are actual finite paths beginning at $o$.

There is an edge

```math
p\longrightarrow pe
```

whenever $e$ continues $p$.

Even if two graph paths reconverge at the same graph node, they remain distinct vertices of $\mathcal T_o$.

For prefix-tree vertices $p,q$, the weighted Green kernel is

```math
G_t^{\mathrm{pre}}(p,q)=
\begin{cases}
t^{|q|-|p|},&p\preceq q,\\
0,&p\npreceq q.
\end{cases}
```

Since

```math
G_t^{\mathrm{pre}}(1_o,q)=t^{|q|},
```

the prefix Martin kernel is

```math
K_t^{\mathrm{pre}}(p,q)=
t^{-|p|}\mathbf1_{\{p\preceq q\}}.
```

This remembers the actual route history.

Along an infinite path $\xi$,

```math
K_t^{\mathrm{pre}}(p,\xi)=
t^{-|p|}
\mathbf1_{\{p\preceq\xi\}}.
```

Multiplying by $t^{|p|}$ gives its cylinder function:

```math
\Psi_\xi(p)=
\mathbf1_{\{p\preceq\xi\}}.
```

This is the Dirac state concentrated on the one infinite route $\xi$.

---

# 10. The node kernel is a barycenter of prefix kernels

For a node $x$, recall the terminal-route distribution

```math
\nu_x^t(q)=
\frac{t^{|q|}}{G_t(o,x)}.
```

Fix a path $p:o\to v$. Then

```math
\begin{aligned}
\sum_{q:o\to x}
\nu_x^t(q)
K_t^{\mathrm{pre}}(p,q)
&=
\sum_{\substack{q:o\to x\\p\preceq q}}
\frac{t^{|q|}}{G_t(o,x)}
t^{-|p|}\\
&=
\frac{G_t(v,x)}{G_t(o,x)}.
\end{aligned}
```

Therefore

```math
K_t(v,x)=
\sum_{q:o\to x}
\nu_x^t(q)
K_t^{\mathrm{pre}}(p,q),
```

for every $p:o\to v$.

This is the exact relationship between the two boundaries:

```math
\text{node Martin kernel}=
\text{weighted barycenter of route-prefix Martin kernels}.
```

The node kernel has already averaged over all routes to the terminal node.

---

# 11. Full route-sensitive versus endpoint-factorized cones

Let $\mathscr P_o$ denote the normalized prefix-harmonic cone:

```math
\Psi(1_o)=1,
```

and at finite emitters,

```math
\Psi(p)=
\sum_{e:r(p)\to w}\Psi(pe).
```

This contains all route-sensitive cylinder states.

The endpoint-factorized subcone consists of functions of the form

```math
\Psi_h(p)=
t^{|p|}h(r(p)),
```

where $h\in\mathscr H_t(o)$.

Hence

```math
\mathscr H_t(o)
\hookrightarrow
\mathscr P_o.
```

The inclusion is usually strict.

The full prefix cone can assign different weights to:

* parallel paths;
* equal-length reconvergent routes;
* histories that arrive at the same node.

The node cone cannot.

---

# 12. Unique-route criterion

If every node reachable from $o$ is reached by at most one path, then a node determines its unique prefix.

In that case, for any prefix-harmonic $\Psi$, define

```math
h(v)=
t^{-|p_v|}\Psi(p_v),
```

where $p_v$ is the unique path $o\to v$.

Then

```math
\Psi(p_v)=t^{|p_v|}h(v),
```

and prefix conservation becomes the node harmonic equation.

Therefore:

```math
\text{unique rooted routes}
\implies
\mathscr H_t(o)\cong\mathscr P_o.
```

In a genuinely reconvergent system,

```math
\mathscr H_t(o)\subsetneq\mathscr P_o
```

in general.

Thus reconvergence is exactly the obstruction to node harmonic data being complete boundary data.

---

# 13. Diamond followed by an infinite tail

Consider

```math
o\to a\to v_0\to v_1\to v_2\to\cdots
```

and

```math
o\to b\to v_0.
```

There are two infinite routes:

```math
\xi_a:
o\to a\to v_0\to v_1\to\cdots,
```

```math
\xi_b:
o\to b\to v_0\to v_1\to\cdots.
```

## Prefix boundary

The full prefix boundary has two minimal route states:

```math
\delta_{\xi_a},
\qquad
\delta_{\xi_b}.
```

Each selects one actual history.

## Node Martin boundary

For a distant tail node $v_n$,

```math
G_t(o,v_n)=2t^{n+2}.
```

The two terminal routes have equal length and therefore equal normalized weight:

```math
\nu_{v_n}^t(\xi_a|_{v_n})=
\nu_{v_n}^t(\xi_b|_{v_n})=
\frac12.
```

The node Martin limit lifts to

```math
\mu_h=
\frac12\delta_{\xi_a}
+
\frac12\delta_{\xi_b}.
```

So the same boundary object can be:

* extreme in the endpoint-factorized node cone;
* non-extreme in the full route-sensitive prefix cone.

This is a major structural point:

```math
\text{extremality depends on the level of compression}.
```

---

# 14. Shortcut followed by an infinite tail

Suppose there are two routes from $o$ to $v$:

* a direct edge $p$, with $|p|=1$;
* a composite route $q$, with $|q|=2$;

followed by a unique infinite tail from $v$.

The terminal-route weights are proportional to

```math
t
\quad\text{and}\quad
t^2.
```

Thus the node Martin lift is

```math
\mu_h=
\frac1{1+t}\delta_{\xi_p}
+
\frac{t}{1+t}\delta_{\xi_q}.
```

At the critical value $t=R^2$, the graph’s intrinsic path-growth scale determines the mixture.

The full prefix boundary still contains both Dirac route states separately.

---

# 15. Node memorylessness as a compression property

For a finite bridge to $x$, the conditional continuation after a prefix $p:o\to v$ is

```math
\frac{\mu_x^t[pe]}{\mu_x^t[p]}=
t\frac{G_t(r(e),x)}{G_t(v,x)}.
```

The right side depends on:

* the current endpoint $v$;
* the chosen next edge $e$;
* the terminal node $x$;

but not on the earlier route used to reach $v$.

At a boundary limit $h$,

```math
\frac{\mu_h[pe]}{\mu_h[p]}=
t\frac{h(r(e))}{h(v)}.
```

So endpoint-factorized Martin states are precisely those whose cylinder splitting forgets previous route history once the current node is known.

This memorylessness follows algebraically from collapsing all histories ending at the same node.

A general prefix-harmonic state can retain the full history:

```math
\frac{\Psi(pe)}{\Psi(p)}
```

may depend on the entire path $p$, even when two paths share the same endpoint.

---

# 16. Three boundary levels

The boundary hierarchy is now:

## Route-prefix boundary

```math
\partial_{\mathrm{pre}}G
```

Retains actual infinite histories and generalized prefix exits.

Its minimal points are individual route directions under suitable finite-branching assumptions.

## Node Martin boundary

```math
\partial_t^M V
```

Retains asymptotic endpoint Green-kernel ratios.

It merges or averages histories according to their weighted route multiplicities.

## Minimal node Martin boundary

```math
\partial_{t,\min}^M V
```

Retains only extreme endpoint-factorized harmonic functions.

The maps are conceptually

```math
\text{route histories}
\longrightarrow
\text{weighted endpoint averaging}
\longrightarrow
\text{minimal node-harmonic directions}.
```

Neither arrow is generally injective.
