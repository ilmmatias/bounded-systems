# 1. The full noncommutative resolvent

In the formal path completion,

```math
R_G(z)=
\sum_{p\in\mathsf P(G)}z^{|p|}p.
```

Its inverse is simply

```math
R_G(z)^{-1}=1-z\mathbf E.
```

The complete set of finite routes has inverse identity minus the primitive-channel element.

All composite paths disappear under inversion, leaving precisely the primitive channels.

This formal identity requires neither finite cardinality nor bounded degree, local finiteness, a topology, or an operator norm.

---

# 2. Endpoint route counting

For nodes $u,v$, define

```math
N_n(v,u)=
\left|\{p:u\to v,\ |p|=n\}\right|.
```

The cardinal-valued path-counting series

```math
\mathcal P^\mathrm{\#}_G(v,u;z)=
\delta_{uv}
+
\sum_{n\ge1}N_n(v,u)z^n
```

exists for every set-sized system, with coefficients interpreted as cardinals.

It retains endpoints, route length, and route multiplicity, but forgets the identity and internal node sequence of each route, the orthogonality among distinct routes, and the manner in which particular routes overlap.

When all $N_n(v,u)$ are finite and the relevant convolutions are coefficientwise finite, one may regard

```math
\mathcal P_G(z)
```

as a matrix, or reachability-category kernel, with coefficients in $\mathbb Z[[z]]$.

It is the endpoint aggregation of the full resolvent:

```math
\mathcal P_G(z)=Q_\Sigma(R_G(z)).
```

---

# 3. The direct-edge kernel

Define the direct-edge kernel by

```math
A_G(v,u)=
\left|\{e:u\to v\}\right|.
```

$C_1$ is the primitive-channel multiplicity kernel.

Since concatenating $n$ primitive channels produces exactly a length-$n$ path,

```math
\mathcal P_G(z)=
I+zA_G+z^2A_G^2+\cdots
=(I-zA_G)^{-1},
```

and hence

```math
\mathcal P_G(z)^{-1}=I-zA_G.
```

Endpoint route summation preserves the local inversion property.

```math
\begin{aligned}
R_G(z)^{-1}&=1-z\mathbf E,
&&\text{individual channels},\\[1mm]
\mathcal P_G(z)^{-1}&=I-zA_G,
&&\text{channel multiplicities}.
\end{aligned}
```

The coefficient of $z$ in $\mathcal P_G$ recovers $A_G$, so the complete path-count kernel determines the underlying directed multigraph up to isomorphism when the node diagonal remains marked.

It does not canonically distinguish two parallel edges inside their multiplicity space.

---

# 4. The analytic obstruction to route summation

Fix $u,v,n$, and suppose there are $m$ length-$n$ paths

```math
p_1,\ldots,p_m:u\to v.
```

In the Fock representation, their operators are orthogonal:

```math
L_{p_i}^\ast L_{p_j}=
\delta_{ij}P_u.
```

Consequently,

```math
\left|
\sum_{j=1}^{m}c_jL_{p_j}
\right|=
\left(
\sum_{j=1}^{m}|c_j|^2
\right)^{1/2}.
```

Endpoint aggregation applies the all-ones functional

```math
(c_1,\ldots,c_m)
\longmapsto
\sum_{j=1}^{m}c_j.
```

Its norm is

```math
\sqrt m.
```

If infinitely many routes share the endpoint pair, this functional has no bounded extension to the corresponding $\ell^2$ route corner.

```math
\text{route summation changes the natural geometry from }\ell^2
\text{ to }\ell^1.
```

Route collapse is algebraically meaningful on finite-support expressions but may fail to be bounded on the Fock completion.

---

# 5. Support and attainable lengths

Before reducing to shortest paths, retain only which lengths occur:

```math
\mathcal S_G(v,u;z)=
\sum_{\substack{n\ge0\\N_n(v,u)>0}}z^n.
```

The support series forgets route multiplicities but preserves the set

```math
L(u,v)=
\{n:N_n(v,u)>0\}.
```

For a reachable pair, define

```math
d(u,v)=\min L(u,v).
```

The minimum exists because path lengths are natural numbers.

Shortest compositional distance remains unconditionally defined even when route counts are infinite and scalar endpoint summation is unavailable.

The reduction is:

```math
\mathcal P^\mathcal{\#}
\longrightarrow
\mathcal S
\longrightarrow
d.
```

It loses, respectively:

1. route identity;
2. route multiplicity;
3. every nonminimal path length.

---

# 6. Tropicalization

For a nonzero power series with nonnegative coefficients, define

```math
\nu(f)=\min{n:[z^n]f\ne0}.
```

Because no cancellation occurs,

```math
\nu(fg)=\nu(f)+\nu(g),
```

and

```math
\nu(f+g)=\min{\nu(f),\nu(g)}.
```

The passage

```math
\mathcal P_G(v,u;z)
\longmapsto
d(u,v)
```

is a min-plus, or tropical, compression of the path-counting kernel.

It remembers the earliest compositional depth at which communication is possible.

It forgets everything that occurs later or in parallel.

---

# 7. Re-embedding the distance matrix

From $d$, define the shortest-path zeta kernel

```math
\zeta_d(z)(v,u)=
\begin{cases}
1,&u=v,\\
z^{d(u,v)},&u<v,\\
0,&u\nleq v.
\end{cases}
```

The geodesic kernel differs from the original path-counting kernel.

In general,

```math
\zeta_d(z)\ne\mathcal P_G(z).
```

For $u<v$, let

```math
d=d(u,v).
```

It follows that

```math
\mathcal P_G(v,u;z)=
N_d(v,u)z^d
+
\sum_{n>d}N_n(v,u)z^n,
```

while

```math
\zeta_d(v,u;z)=z^d.
```

Define the route-excess kernel

```math
X_G(z)=\mathcal P_G(z)-\zeta_d(z).
```

Its endpoint corner is

```math
X_G(v,u;z)=
\bigl(N_d(v,u)-1\bigr)z^d
+
\sum_{n>d}N_n(v,u)z^n.
```

It separates two losses.

## Geodesic multiplicity

The geodesic multiplicity is

```math
N_d(v,u)-1.
```

The coefficient counts excess shortest routes.

### Detour content

The remaining detour contribution is

```math
\sum_{n>d}N_n(v,u)z^n.
```

The remainder records all nonshortest routes.

```math
X_G(z)=0
```

if and only if every comparable node pair is joined by exactly one directed path.

Equivalently,

```math
X_G=0
\iff
\mathsf P(G)\text{ is already thin}.
```

---

# 8. The weighted Möbius kernel

When the weighted incidence convolution is coefficientwise finite, define

```math
M_d(z)=\zeta_d(z)^{-1}.
```

Its endpoint coefficient is

```math
M_d(v,u;z)=
\sum_{m\ge1}(-1)^m
\sum_{u=x_0<\cdots<x_m=v}
z^{
d(x_0,x_1)+\cdots+d(x_{m-1},x_m)
}.
```

The expression is the weighted Möbius series.

Compare the two inverses:

```math
\begin{aligned}
\mathcal P_G(z)^{-1}
&=
I-zA_G,\\
\zeta_d(z)^{-1}
&=
M_d(z).
\end{aligned}
```

The first is local.

The second can contain arbitrarily long alternating factorization terms.

---

# 9. Exact Möbius-defect identity

Since

```math
\mathcal P_G=\zeta_d+X_G,
```

The inverse-difference identity gives

```math
M_d-(I-zA_G)=
M_dX_G(I-zA_G).
```

Equivalently,

```math
M_d-(I-zA_G)=
(I-zA_G)X_GM_d.
```

The product is noncommutative: factor order matters.

This identity states that every nonlocal Möbius correction is generated by the route excess discarded by shortest reduction.

There is also a formal geometric expansion:

```math
M_d=
(I-zA_G)
+
(I-zA_G)X_G(I-zA_G)
+\cdots
```

more precisely,

```math
M_d=
\sum_{k\ge0}
\bigl((I-zA_G)X_G\bigr)^k
(I-zA_G),
```

or equivalently,

```math
M_d=
(I-zA_G)
\sum_{k\ge0}
\bigl(X_G(I-zA_G)\bigr)^k.
```

Every occurrence of $X_G$ represents one insertion of information discarded by the shortest-path compression.

---

# 10. Unique-route theorem

Under the finiteness conditions needed for both inverses, the following are equivalent:

1. Every comparable pair $u\le v$ has exactly one directed path.
2. $\mathcal P_G(z)=\zeta_d(z)$.
3. $X_G(z)=0$.
4. $M_d(z)=I-zA_G$.
5. Weighted Möbius inversion contains no correction beyond primitive edges.

Möbius complexity measures failure of the path category to be thin.

The defect detects parallel primitive channels, diamonds, shortcuts, longer detours, and repeated branching and reconvergence.

---

# 11. Examples

## Unique chain

Consider the chain $u\to w\to v$.

It follows that

```math
\mathcal P(v,u;z)=z^2,
```

and

```math
\zeta_d(v,u;z)=z^2.
```

Thus the route defect vanishes:

```math
X(v,u;z)=0.
```

The inverse satisfies

```math
M_d(v,u;z)=0,
```

because

```math
-z^2+z\cdot z=0.
```

The expression agrees with

```math
(I-zA_G)(v,u)=0,
```

since there is no direct edge $u\to v$.

## Parallel channels

Suppose there are $m$ parallel edges $u\to v$.

For this endpoint pair,

```math
\mathcal P(v,u;z)=mz,
\qquad
\zeta_d(v,u;z)=z,
```

and

```math
X(v,u;z)=(m-1)z.
```

The route-count inverse is

```math
\mathcal P^{-1}(v,u)=-mz,
```

while the weighted Möbius inverse is

```math
M_d(v,u)=-z.
```

The shortest thin signature has erased the parallel multiplicity.

## Diamond

Suppose that

```math
u\to a\to v,
\qquad
u\to b\to v.
```

For the diamond,

```math
\mathcal P(v,u;z)=2z^2,
\qquad
\zeta_d(v,u;z)=z^2,
```

and

```math
X(v,u;z)=z^2.
```

There is no direct edge, so

```math
(I-zA_G)(v,u)=0.
```

However,

```math
M_d(v,u;z)=z^2.
```

The nonzero Möbius coefficient is exactly the correction induced by the second shortest route.

## Shortcut

Suppose there is both a direct edge $u\to v$ and a two-step route

```math
u\to w\to v.
```

The corresponding endpoint series are

```math
\mathcal P(v,u;z)=z+z^2,
\qquad
\zeta_d(v,u;z)=z,
```

and

```math
X(v,u;z)=z^2.
```

The local inverse is

```math
(I-zA_G)(v,u)=-z.
```

The weighted Möbius inverse is

```math
M_d(v,u;z)=-z+z^2.
```

The $z^2$ correction is the longer factorization made invisible by shortest reduction.

---

# 12. Möbius complexity is compression compensation

The contrast can be stated at three levels. At the full path level,

```math
R_G^{-1}=1-z\mathbf E,
```

so inversion removes free compositions while retaining the primitive channels. At the endpoint-counting level,

```math
\mathcal P_G^{-1}=I-zA_G,
```

routes have been aggregated, but their multiplicities and lengths remain and primitive edge multiplicities are still recovered. At the shortest thin level,

```math
\zeta_d^{-1}=M_d,
```

alternative routes, multiplicities, and nonminimal lengths have been deleted; Möbius inversion must therefore recreate their net factorization effects through alternating global corrections.

Möbius nonlocality is the algebraic price of lossy route compression.

---

# 13. The compression sequence

Endpoint aggregation sends the route-resolved series $R_G(z)$ to the path-count kernel

```math
\mathcal P_G(v,u;z)=
\sum_nN_n(v,u)z^n.
```

Discarding multiplicity gives the support series

```math
\mathcal S_G(v,u;z)=
\sum_{n:N_n(v,u)>0}z^n.
```

Retaining only the least exponent yields the shortest-route distance $d(u,v)$, which is re-embedded as

```math
\zeta_d(v,u;z)=z^{d(u,v)}.
```

Incidence-convolution inversion then produces $M_d(v,u;z)$.

The operations have different mathematical types:

* endpoint aggregation is linear where defined;
* support reduction is semiring-valued;
* shortest reduction is tropical and nonlinear over a field;
* monomial re-embedding is lossy;
* Möbius inversion is convolutional and noncommutative.

They should not be treated as one algebra homomorphism.

---

# 14. Unconditional results for arbitrary systems

For any set-sized system, even with infinitely many routes:

* $R_G(z)$ exists formally;
* the cardinal path-count series $\mathcal P^\mathcal{\#}_G$ exists;
* the support series $\mathcal S_G$ exists;
* $d(u,v)$ exists for reachable pairs;
* the filtered interval complexes exist;
* their homology exists.

What may fail without finiteness is:

* scalar route summation into a field;
* convolution inverse of $\mathcal P_G$;
* scalar weighted Möbius inversion;
* evaluation at $z=1$.

In those cases, the path algebra, support, tropical distance, and chain complexes remain primary.
