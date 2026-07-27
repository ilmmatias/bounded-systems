# 1. Common path-counting data

Let

```math
A(v,u)=\left|\{e:u\to v\}\right|
```

be the primitive-channel multiplicity kernel.

Define

```math
N_n(v,u)=
\left|\{\text{length-}n\text{ paths }u\to v\}\right|.
```

Whenever ordinary arithmetic is available,

```math
N_n(v,u)=(A^n)(v,u).
```

For a fixed source $u$, let

```math
T_n(u)=\sum_v N_n(v,u)
```

be the total number of length-$n$ routes beginning at $u$, and put

```math
T_n^+=\sup_u T_n(u).
```

Dually, define

```math
T_n^-=
\sup_v\sum_uN_n(v,u),
```

the largest number of length-$n$ routes terminating at one node.

These may be infinite. The operator conclusions below apply when the relevant quantities are finite and uniformly bounded.

---

# 2. Exact (\ell^2)-to-(\ell^1) growth identity

Let

```math
S_+=\sum_{e\in E}L_e
```

be the forward Fock creator.

Distinct length-$n$ paths are orthogonal, so on the source sector $P_u$,

```math
(S_+^n)^\ast S_+^nP_u=
T_n(u)P_u.
```

Therefore

```math
|S_+^nP_u|^2=T_n(u).
```

Globally,

```math
|S_+^n|^2=T_n^+.
```

Now regard $A$ as an operator on $\ell^1(V)$, using the convention

```math
(Af)(v)=\sum_uA(v,u)f(u).
```

Then

```math
|A^n\delta_u|_1=
\sum_vN_n(v,u)=
T_n(u),
```

and hence

```math
|A^n|_{\ell^1\to\ell^1}=
T_n^+=
|S_+^n|^2.
```

This is an equality, not merely a bound.

If $A$ is bounded on $\ell^1$, equivalently if outgoing degree is uniformly finite, the spectral-radius formula gives

```math
r(S_+)^2=
r_{\ell^1}(A).
```

Thus the Fock spectral radius is the square root of the endpoint-counting spectral radius.

Equivalently,

```math
r(S_+)=
\lim_{n\to\infty}
\left(
\sup_uT_n(u)
\right)^{1/(2n)}.
```

The square root appears because route counts are $\ell^1$ mass, whereas Fock routes are mutually orthogonal and therefore combine by Pythagoras.

---

# 3. Backward growth and node-space (\ell^2)

A backward Fock construction gives

```math
|S_-^n|^2=T_n^-.
```

For the ordinary node-space adjacency operator on $\ell^2(V)$, the Schur bound gives

```math
|A^n|_{\ell^2\to\ell^2}
\le
\sqrt{T_n^+T_n^-}.
```

Consequently,

```math
r_{\ell^2}(A)
\le
r(S_+)r(S_-).
```

This separates two directional sources of growth:

* forward branching;
* backward reconvergence.

A highly branching but nonreconverging tree can have large $S_+$ but small endpoint concentration. A system in which many routes repeatedly merge can make both directional quantities large.

---

# 4. Endpoint aggregation and reconvergence

Fix $u$ and $n$. Let

```math
\mathscr P_n(u)=
\{p:|p|=n,\ s(p)=u\}.
```

The Fock route space is

```math
\ell^2(\mathscr P_n(u)).
```

Define endpoint aggregation

```math
C_{n,u}:
\ell^2(\mathscr P_n(u))
\longrightarrow
\ell^2(V)
```

by

```math
C_{n,u}\xi_p=\eta_{r(p)},
```

where ${\eta_v}$ is the node basis.

Routes ending at the same node are added.

Let

```math
M_n(u)=\sup_vN_n(v,u)
```

be the largest endpoint route multiplicity. Then

```math
|C_{n,u}|=\sqrt{M_n(u)}.
```

So endpoint collapse is most singular precisely where many orthogonal routes reconverge onto one node.

Apply this to the all-route Fock vector

```math
\Psi_{n,u}=
\sum_{p\in\mathscr P_n(u)}\xi_p.
```

Its norm is

```math
|\Psi_{n,u}|^2=T_n(u).
```

After endpoint aggregation,

```math
C_{n,u}\Psi_{n,u}=
\sum_vN_n(v,u)\eta_v.
```

Therefore

```math
\left|
C_{n,u}\Psi_{n,u}
\right|_2^2=
\sum_vN_n(v,u)^2.
```

The sharp elementary bounds are

```math
T_n(u)
\le
\sum_vN_n(v,u)^2
\le
M_n(u)T_n(u)
\le
T_n(u)^2.
```

Interpretation:

* the lower bound is attained when no two routes end at the same node;
* the upper bound is attained when every route ends at one node;
* the middle quantity measures reconvergence concentration.

Thus the endpoint-summation map destroys orthogonality with norm amplification $\sqrt{M_n(u)}$.

---

# 5. From route counting to min-plus geometry

Define the endpoint path series

```math
\mathcal P(v,u;z)=
\delta_{uv}
+
\sum_{n\ge1}N_n(v,u)z^n.
```

For a reachable pair $u<v$, the shortest compositional distance is exactly the $z$-adic valuation:

```math
d(u,v)=
\nu_z\bigl(\mathcal P(v,u;z)\bigr)=
\min{n:N_n(v,u)>0}.
```

Let

```math
g(v,u)=N_{d(u,v)}(v,u)
```

be the number of geodesic routes. Then

```math
\mathcal P(v,u;z)=
g(v,u)z^{d(u,v)}
+
O\!\left(z^{d(u,v)+1}\right).
```

So the first two pieces of the scalar path series are:

```math
\begin{aligned}
\text{valuation}&=d(u,v),\\
\text{leading coefficient}&=g(v,u).
\end{aligned}
```

The min-plus reduction keeps only the valuation. It discards the leading coefficient and every higher coefficient.

## Fock meaning of geodesic multiplicity

Define the geodesic Fock vector

```math
\Gamma_{v,u}=
\sum_{\substack{
p:u\to v\\
|p|=d(u,v)
}}
\xi_p.
```

Orthogonality gives

```math
|\Gamma_{v,u}|^2=g(v,u).
```

Hence the first scalar correction discarded by tropicalization is itself the square of a canonical Fock norm.

The three geometries meet in the exact formula

```math
\mathcal P(v,u;z)=
|\Gamma_{v,u}|^2
z^{d(u,v)}
+\text{higher-length terms}.
```

---

# 6. Endpoint growth versus route growth

Let

```math
R_n(u)=
\left|\{v:d(u,v)=n\}\right|
```

be the number of nodes whose shortest distance from $u$ is exactly $n$.

Every such node has at least one length-$n$ path, so

```math
R_n(u)\le T_n(u).
```

Therefore

```math
\sup_uR_n(u)
\le
|S_+^n|^2.
```

At the exponential-growth level,

```math
\limsup_{n\to\infty}
\left(\sup_uR_n(u)\right)^{1/n}
\le
r(S_+)^2.
```

The inequality can be either an equality or extremely strict.

## Regular branching tree

If every node has $d$ children and routes never reconverge,

```math
T_n(u)=d^n,
\qquad
R_n(u)=d^n.
```

Thus

```math
r(S_+)=\sqrt d.
```

Here min-plus endpoint growth retains all route growth because every route reaches a distinct endpoint.

## Complete reconvergence

Suppose there is one node at every layer and $d$ parallel channels between consecutive layers.

Then

```math
T_n(u)=d^n,
```

but

```math
R_n(u)=1.
```

Again,

```math
r(S_+)=\sqrt d,
```

while shortest-path endpoint growth is trivial.

So tropical geometry can discard an arbitrarily large exponential amount of route information.

---

# 7. Weighted Möbius coefficients

Let

```math
M_d(z)=\zeta_d(z)^{-1}
```

be the weighted thin Möbius kernel.

For fixed $u<v$, write

```math
M_d(v,u;z)=
\sum_{L\ge1}m_L(v,u)z^L.
```

Let

```math
c_{r,L}(v,u)
```

be the number of strict factorization chains

```math
u=x_0<x_1<\cdots<x_r=v
```

whose total shortest-distance cost is

```math
\sum_{i=1}^r d(x_{i-1},x_i)=L.
```

Then

```math
m_L(v,u)=
\sum_{r=1}^L(-1)^r c_{r,L}(v,u).
```

Therefore the first exact bound is

```math
|m_L(v,u)|
\le
\sum_{r=1}^L c_{r,L}(v,u).
```

Equality occurs when there is no cancellation between even- and odd-length factorizations.

---

# 8. Bounding Möbius coefficients by actual routes

For each comparable pair, select one shortest path. This selection is needed only for the counting proof; the resulting inequality is independent of the selection.

Given a factorization chain

```math
u=x_0<\cdots<x_r=v
```

of total cost $L$, concatenate the selected geodesic for each factor. This produces:

1. an actual length-$L$ path from $u$ to $v$;
2. a choice of $r-1$ cut positions among the $L-1$ internal edge positions.

The full path and its cut positions determine the factorization chain. Hence

```math
c_{r,L}(v,u)
\le
\binom{L-1}{r-1}N_L(v,u).
```

Summing over $r$,

```math
\sum_{r=1}^Lc_{r,L}(v,u)
\le
2^{L-1}N_L(v,u).
```

Thus:

```math
|m_L(v,u)|
\le
2^{L-1}N_L(v,u).
```

And since

```math
N_L(v,u)\le T_L(u),
```

we obtain

```math
|m_L(v,u)|
\le
2^{L-1}T_L(u)=
2^{L-1}|S_+^LP_u|^2.
```

Finally,

```math
|m_L(v,u)|
\le
2^{L-1}|S_+^L|^2.
```

This is the requested direct inequality linking:

* weighted Möbius coefficients;
* route multiplicity;
* orthogonal Fock growth.

The factor $2^{L-1}$ cannot be improved for the **unsigned number of factorization chains**: one unique path of length $L$ has $2^{L-1}$ possible cut subsets. But its signed Möbius coefficient may cancel all the way to zero.

---

# 9. Spectral-radius consequence

Assume $S_+$ is bounded and the scalar Möbius coefficients are finite.

From the previous inequality,

```math
\limsup_{L\to\infty}
|m_L(v,u)|^{1/L}
\le
2r(S_+)^2.
```

Using

```math
r(S_+)^2=r_{\ell^1}(A),
```

we obtain

```math
\limsup_{L\to\infty}
|m_L(v,u)|^{1/L}
\le
2r_{\ell^1}(A).
```

Therefore every scalar endpoint series satisfies the coarse convergence bound

```math
\mathrm{rad}
M_d(v,u;\cdot)
\ge
\frac{1}{2r(S_+)^2}=
\frac{1}{2r_{\ell^1}(A)},
```

with the usual interpretation when the denominator is zero.

This gives only a lower bound for the convergence radius. Alternating cancellation can make the true radius much larger.

For finite-height systems, all relevant series are polynomials.

---

# 10. A uniform operator-norm bound

Suppose $A$ is bounded on $\ell^1$, and put

```math
a=|z||A|_1.
```

For $a<1$,

```math
|\mathcal P(|z|)-I|_1
\le
\frac{a}{1-a}.
```

Because the shortest-path strict kernel $W_d=\zeta_d-I$ is coefficientwise bounded by $\mathcal P-I$,

```math
|W_d(|z|)|_1
\le
\frac{a}{1-a}.
```

If

```math
a<\frac12,
```

this is less than one, so the weighted Möbius inverse converges and

```math
|M_d(z)|_1
\le
\frac{1-a}{1-2a}.
```

Thus the elementary region

```math
|z|<\frac{1}{2|A|_1}
```

is always contained in the $\ell^1$-operator convergence domain whenever the scalar weighted kernel is defined.

Again, this is a universal safe region, not usually the optimal one.

---

# 11. The three geometries as successive algebraic operations

The same path family undergoes three changes of addition.

## Orthogonal path geometry

Routes are basis vectors:

```math
p\perp q\qquad(p\ne q).
```

Aggregation obeys

```math
\left|\sum_pc_p\xi_p\right|_2^2=
\sum_p|c_p|^2.
```

This retains individual route identity.

## Counting geometry

Routes with the same endpoint are added:

```math
N_n(v,u)=
\sum_{\substack{p:u\to v\\|p|=n}}1.
```

Addition is ordinary nonnegative arithmetic.

This retains multiplicity but loses route identity.

## Min-plus geometry

Only the first nonzero degree remains:

```math
d(u,v)=
\min{n:N_n(v,u)>0}.
```

Ordinary addition of alternatives is replaced by minimum, while path concatenation becomes addition of lengths.

This retains only earliest compositional possibility.

The exact endpoint-level bridge is

```math
\mathcal P(v,u;z)
\longmapsto
\left(
\nu_z\mathcal P(v,u;z),
\mathrm{lc}_z\mathcal P(v,u;z)
\right)=
\left(
d(u,v),
|\Gamma_{v,u}|^2
\right).
```
