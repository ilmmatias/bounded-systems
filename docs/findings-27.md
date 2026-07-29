# 1. Rooted path growth versus endpoint-fiber growth

Fix a source node $u$.

Define the total rooted path count

```math
T_n(u)=
\sum_vN_n(v,u).
```

Its rooted partition series is

```math
Z_u(r)=
\sum_{p:s(p)=u}r^{2|p|}=
\sum_{n\ge0}T_n(u)r^{2n}.
```

When this is finite, define the normalized rooted path vector

```math
\Omega_{u,r}=
\frac1{\sqrt{Z_u(r)}}
\sum_{p:s(p)=u}r^{|p|}\xi_p.
```

By contrast, for one fixed endpoint pair $u,v$, define

```math
H_{v,u}(r)=
\sum_{p:u\to v}r^{2|p|}=
\sum_{n\ge0}N_n(v,u)r^{2n},
```

with normalized route-fiber vector

```math
\Omega_{v,u,r}=
\frac1{\sqrt{H_{v,u}(r)}}
\sum_{p:u\to v}r^{|p|}\xi_p.
```

The two generating functions have different roles: $Z_u$ measures all paths escaping forward from $u$, whereas $H_{v,u}$ measures the alternative finite routes reconverging at $v$.

Since

```math
N_n(v,u)\le T_n(u),
```

The fixed-endpoint series can remain finite beyond the rooted one.

---

# 2. Two local critical radii

The forward path-growth rate is

```math
\gamma_u^+=
\limsup_{n\to\infty}
T_n(u)^{1/(2n)},
```

and

```math
\gamma_{v,u}^{\mathrm{fib}}=
\limsup_{n\to\infty}
N_n(v,u)^{1/(2n)}.
```

Then the respective radii are

```math
R_u^+=
\frac1{\gamma_u^+},
\qquad
R_{v,u}^{\mathrm{fib}}=
\frac1{\gamma_{v,u}^{\mathrm{fib}}}.
```

Because $N_n(v,u)\le T_n(u)$,

```math
R_{v,u}^{\mathrm{fib}}\ge R_u^+.
```

Forward depth escape can occur while every individual endpoint fiber is still analytically harmless.

Globally,

```math
R_{\mathrm{Fock}}=
\frac1{r(S_+)},
```

while

```math
R_{\mathrm{col}}=
\frac1{\rho_{\mathrm{col}}}.
```

Since

```math
\rho_{\mathrm{col}}\le r(S_+),
```

The resulting bound is

```math
R_{\mathrm{col}}\ge R_{\mathrm{Fock}}.
```

Endpoint collapse can remain bounded after the global rooted Fock sum ceases to exist.

---

# 3. Rooted boundary-escape theorem

Assume:

1. $Z_u(r)<\infty$ for $0\le r<R_u^+$;
2. $Z_u(r)\to\infty$ as $r\uparrow R_u^+$.

It follows that

```math
\Omega_{u,r}\rightharpoonup0
\quad\text{weakly in Fock space}.
```

Indeed, for any fixed finite path $p$,

```math
\left\langle\xi_p,\Omega_{u,r}\right\rangle=
\frac{r^{|p|}}{\sqrt{Z_u(r)}}
\longrightarrow0.
```

Finite-support vectors are dense, while every $\Omega_{u,r}$ has norm one, so coordinatewise convergence implies weak convergence to zero.

There is therefore no nonzero critical Fock vector.

But the associated vector functionals

```math
\varphi_{u,r}(T)=
\left\langle T\Omega_{u,r},\Omega_{u,r}\right\rangle
```

remain states. Weak-* compactness gives cluster states

```math
\varphi_{u,\partial}=
\operatorname*{w^\ast\!-\!lim}_{r\uparrow R_u^+}
\varphi_{u,r},
```

using a subnet when necessary.

The vectors disappear weakly, while their states can survive.

Toeplitz-Cuntz-type state spaces naturally include such non-vector-normal or “essential” states, although precise terminology and the quotient depend on the operator-algebraic setting.

---

# 4. Compact operators disappear at the boundary

Define $\Theta_{p,q}$ by

```math
\Theta_{p,q}=
|\xi_p\rangle\langle\xi_q|
```

be a rank-one operator between two finite paths beginning at $u$.

It follows that

```math
\varphi_{u,r}(\Theta_{p,q})=
\frac{r^{|p|+|q|}}{Z_u(r)}.
```

The induced morphism is

```math
\varphi_{u,r}(\Theta_{p,q})\longrightarrow0.
```

It follows first for finite-rank operators and then, by norm approximation, for every compact operator $K$:

```math
\varphi_{u,\partial}(K)=0.
```

Every critical escape state factors through the represented Toeplitz algebra modulo its compact ideal.

Operator-theoretically, no finite path retains positive mass at the boundary.

---

# 5. Cylinder projections

Let $q:u\to w$ be a finite path.

Denote by $P[q]$ the projection onto the span of all finite paths beginning with $q$:

```math
\mathrm{Ran}P[q]=
\overline{\operatorname{span}\{\xi_{qt}:s(t)=w\}}.
```

It follows that

```math
\varphi_{u,r}(P[q])=
\frac{
r^{2|q|}Z_w(r)
}{
Z_u(r)
}.
```

The identity follows because every extension of $q$ is uniquely $qt$, with

```math
|qt|=|q|+|t|.
```

The cylinder weight of $q$ is

```math
\mu_{u,r}[q]=
\varphi_{u,r}(P[q]).
```

The cylinder weights satisfy

```math
\mu_{u,r}[q]=
\frac{r^{2|q|}}{Z_u(r)}
+
\sum_{e:s(e)=w}
\mu_{u,r}[qe],
```

whenever the sum is finite or otherwise meaningfully convergent.

The first term is the finite path $q$'s mass. At a divergent critical point,

```math
\frac{r^{2|q|}}{Z_u(r)}
\longrightarrow0.
```

The critical cylinder state becomes purely extendable:

```math
\mu_{u,\partial}[q]=
\sum_{e:s(e)=w}
\mu_{u,\partial}[qe].
```

A finitely branching rooted path tree yields an ordinary consistent cylinder system on the genuine infinite-path boundary.

---

# 6. When the limit is an actual infinite-path measure

Assume the forward prefix tree from $u$ is finitely branching.

Under this hypothesis:

* every cylinder has finitely many immediate subcylinders;
* the conservation equation passes directly to the limit;
* unbounded rooted depth guarantees an infinite ray by König’s lemma;
* the cylinder weights determine a countably additive Borel measure on the infinite-path space.

Thus, under finite branching,

```math
Z_u(r)\to\infty
\quad\Longrightarrow\quad
\text{critical mass escapes to genuine infinite paths}.
```

A measure on $\partial_u^+G$ then represents the boundary state's restriction to the commutative cylinder algebra.

In standard graph $C^*$-algebra constructions, the boundary-path space is precisely the spectrum of a distinguished commutative diagonal subalgebra and, depending on the graph, may include infinite paths and finite paths ending at singular vertices.

---

# 7. Infinite branching changes the conclusion

Without finite branching, a limit cylinder state need not be concentrated on actual infinite rays.

For an infinite emitter $w$, the relation

```math
P[q]=
Q_q+\sum_{e:s(e)=w}P[qe]
```

contains an infinite sum.

Although every finite partial sum satisfies

```math
\sum_{e\in F}\mu[q e]\le\mu[q],
```

it can happen that

```math
\sup_{F\subset E_w,\;F\text{ finite}}
\sum_{e\in F}\mu[q e]
<
\mu[q].
```

The missing mass has escaped through the infinitely many children without selecting any one child with positive limiting mass.

```math
\text{critical state}
\not\Rightarrow
\text{measure on actual infinite rays}
```

for arbitrary branching.

The canonical unrestricted object is the state on the commutative cylinder algebra, equivalently on its spectrum, not necessarily a measure supported only on the literal inverse-limit set of infinite paths.

This is the same logical distinction expressed by

```math
\text{unbounded finite depth}
\not\Rightarrow
\text{an actual infinite path}.
```

without a finite-branching or compactness assumption.

---

# 8. The fixed-endpoint fiber cannot produce a ray

Now consider the normalized fixed-endpoint vector

```math
\Omega_{v,u,r}=
H_{v,u}(r)^{-1/2}
\sum_{p:u\to v}r^{|p|}\xi_p.
```

Acyclicity gives a decisive lemma.

## Same-endpoint antichain lemma

If $p$ and $q$ are distinct paths from $u$ to $v$, neither can be a proper prefix of the other.

Indeed, if

```math
q=tp
```

with $t$ nonempty, then $t$ would be a nonempty path

```math
v\to v,
```

contradicting acyclicity.

```math
\mathscr P(u,v)
\text{ is an antichain under prefix order}.
```

Even when

```math
H_{v,u}(r)\to\infty,
```

The route-fiber vectors do not approach nested prefixes but spread across mutually incomparable finite routes.

fixed-endpoint critical escape is not an infinite-path boundary phenomenon.

It is a boundary of alternative finite route choices.

---

# 9. The route-choice corona

Define $S_{v,u}$ by

```math
S_{v,u}=\mathscr P(u,v)
```

with the discrete topology.

The normalized route weights define a state on bounded functions on this route set:

```math
\nu_{v,u,r}(f)=
\frac{
\sum_{p:u\to v}
r^{2|p|}f(p)
}{
H_{v,u}(r)
}.
```

Suppose $H_{v,u}(r)\to\infty$.

For every fixed finite subset $F\subset S_{v,u}$,

```math
\nu_{v,u,r}(1_F)=
\frac{
\sum_{p\in F}r^{2|p|}
}{
H_{v,u}(r)
}
\longrightarrow0.
```

Every cluster state $\nu_{v,u,\partial}$ satisfies

```math
\nu_{v,u,\partial}(f)=0
\qquad
\text{for every }f\in c_0(S_{v,u}).
```

It therefore factors through

```math
\ell^\infty(S_{v,u})/c_0(S_{v,u}).
```

Its spectrum is the remainder of the discrete route set after removing all individual finite routes.

Call this the route-choice corona:

```math
\partial_{\mathrm{route}}(v,u).
```

The name is descriptive.

Its points represent generalized ways of escaping through infinitely many mutually incomparable finite routes.

---

# 10. Three distinct escape mechanisms

Three analytically distinct phenomena occur.

## A. Rooted depth escape

The corresponding map is

```math
Z_u(r)\to\infty.
```

Mass moves through increasing path length from one source.

Under finite branching, this yields a state on

```math
\partial_u^+G.
```

## B. Fixed-endpoint fiber escape

The corresponding map is

```math
H_{v,u}(r)\to\infty.
```

Mass moves through infinitely many incomparable routes from $u$ to $v$.

The construction defines a state on

```math
\partial_{\mathrm{route}}(v,u),
```

not an infinite forward ray.

## C. Moving-endpoint unboundedness

The global endpoint-collapse norm may diverge because

```math
\sup_{u,v}H_{v,u}(r)=\infty
```

even though every fixed $H_{v,u}(r)$ is finite.

Consequently, no single endpoint pair carries the singularity; the maximizing pair moves farther through the graph.

The divergence comes from global depth drift, not a local fiber.

---

# 11. Example: one infinite chain

Consider the infinite chain $u_0\to u_1\to u_2\to\cdots$.

There is exactly one path of each length from $u_0$, so

```math
T_n(u_0)=1
```

and

```math
Z_{u_0}(r)=
\sum_{n\ge0}r^{2n}=
\frac1{1-r^2}.
```

The critical radius is

```math
R_{u_0}^+=1.
```

For the unique length-$k$ prefix $q_k$,

```math
\mu_{u_0,r}[q_k]=
r^{2k}.
```

This gives

```math
\lim_{r\uparrow1}\mu_{u_0,r}[q_k]=1.
```

The boundary state is concentrated on the unique infinite ray.

The normalized vectors themselves satisfy

```math
\sqrt{1-r^2}
\sum_{n\ge0}r^n\xi_{q_n}
\rightharpoonup0,
```

but their cylinder states converge nontrivially.

---

# 12. Example: the $d$-ary tree

Suppose each node has $d$ outgoing edges to distinct children.

It follows that

```math
T_n(u)=d^n,
```

so

```math
Z_u(r)=\frac1{1-dr^2}
```

and

```math
R_u^+=\frac1{\sqrt d}.
```

For a prefix $q$ of length $k$, every descendant subtree is isomorphic to the original rooted tree. Hence

```math
\mu_{u,r}[q]=r^{2k}.
```

At the critical point,

```math
\mu_{u,\partial}[q]=d^{-k}.
```

There are $d^k$ cylinders at depth $k$, and their masses sum to one.

The measure is the equal-weight state on the $d$-ary infinite-path boundary.

Yet each fixed endpoint pair has at most one path, so every local route-fiber series is a monomial with infinite radius.

The infinite-path boundary appears even though no endpoint fiber is singular.

---

# 13. Example: infinitely many finite routes but no ray

Construct, for every $n\ge1$, one separate length-$n$ chain from $u$ to $v$:

```math
u\to x_{n,1}\to\cdots\to x_{n,n-1}\to v.
```

The chains are internally disjoint.

It follows that

```math
N_n(v,u)=1
\qquad(n\ge1),
```

and therefore

```math
H_{v,u}(r)=
\sum_{n\ge1}r^{2n}=
\frac{r^2}{1-r^2}.
```

The fixed-endpoint critical radius is one.

As $r\uparrow1$, the vectors

```math
\Omega_{v,u,r}
```

escape through longer and longer mutually incomparable finite routes.

But this subgraph has no infinite path: every branch terminates at $v$, and acyclicity prevents continuation into the branch.

Therefore the limiting state lies on the route-choice corona, not on an infinite-path boundary.

Meanwhile, $Z_u(r)$ is infinite for every $r>0$ because $u$ emits infinitely many first edges.

Thus no rooted radial Fock vector exists at all.

The example separates endpoint-collapse criticality from infinite-ray emergence.

---

# 14. Critical regularity versus critical escape

For a rooted source $u$, there are three regimes. In the subcritical regime $0\le r<R_u^+$, the vector $\Omega_{u,r}$ lies in Fock space. At a critical regular point,

```math
Z_u(R_u^+)<\infty,
```

so $\Omega_{u,R_u^+}$ still exists as an ordinary Fock vector and no boundary escape is forced. At a critical divergent point,

```math
Z_u(R_u^+)=\infty,
```

normalized vectors tend weakly to zero while cluster states may survive outside the normal Fock sector.

Thus the radius alone is insufficient. The behavior of the series at the boundary matters.

---

# 15. Noncommutative versus diagonal boundary data

Cylinder weights retain only the critical state's restriction to the commutative prefix diagonal.

The full cluster state

```math
\varphi_{u,\partial}
```

is defined on the noncommutative Toeplitz algebra generated by the path creators and node projections.

So the complete hierarchy is:

```math
\begin{aligned}
\varphi_{u,\partial}
&:\text{noncommutative boundary state},\\
\varphi_{u,\partial}|_{\mathcal D_{\mathrm{cyl}}}
&:\text{cylinder-boundary state},\\
\mu_{u,\partial}
&:\text{boundary measure when countable additivity holds}.
\end{aligned}
```

The first retains interference between prefix operators and their adjoints.

The second retains only nested-cylinder incidence.

The third is a classical representation of the second under appropriate topological and finiteness conditions.
