## 1. The full noncommutative resolvent

In the formal path completion,

$$
R_G(z)=
\sum_{p\in\mathsf P(G)}z^{|p|}p.
$$

Its inverse is simply

$$
R_G(z)^{-1}=1-z\mathbf E.
$$

Therefore the complete set of all finite routes has an extremely simple inverse: identity minus the primitive-channel element.

All composite paths disappear under inversion, leaving precisely the primitive channels.

This formal identity is independent of:

* finite cardinality;
* bounded degree;
* local finiteness;
* topology;
* operator norm.

---

# 2. Endpoint route counting

For nodes $u,v$, define

$$
N_n(v,u)=
\#\{p:u\to v,\ |p|=n\}.
$$

The cardinal-valued path-counting series

$$
\mathcal P^\#_G(v,u;z)=
\delta_{uv}
+
\sum_{n\ge1}N_n(v,u)z^n
$$

exists for every set-sized system, with coefficients interpreted as cardinals.

It retains:

* endpoints;
* route length;
* route multiplicity.

But it forgets:

* the identity of each route;
* its internal node sequence;
* orthogonality among routes;
* how two particular routes overlap.

When all $N_n(v,u)$ are finite and the relevant convolutions are coefficientwise finite, we may regard

$$
\mathcal P_G(z)
$$

as a matrix—or reachability-category kernel—with coefficients in $\mathbb Z[[z]]$.

It is the endpoint aggregation of the full resolvent:

$$
\mathcal P_G(z)=Q_\Sigma(R_G(z)).
$$

---

# 3. The direct-edge kernel

Let

$$
A_G(v,u)=
\#\{e:u\to v\}.
$$

This is the primitive-channel multiplicity kernel.

Since concatenating $n$ primitive channels produces exactly a length-$n$ path,

$$
\mathcal P_G(z)=
I+zA_G+z^2A_G^2+\cdots.
$$

Hence

$$
\mathcal P_G(z)=
(I-zA_G)^{-1}.
$$

Therefore:

$$
\mathcal P_G(z)^{-1}=I-zA_G.
$$

Endpoint route summation preserves the local inversion property.

We now have:

$$
\begin{aligned}
R_G(z)^{-1}&=1-z\mathbf E,
&&\text{individual channels},[1mm]
\mathcal P_G(z)^{-1}&=I-zA_G,
&&\text{channel multiplicities}.
\end{aligned}
$$

The coefficient of $z$ in $\mathcal P_G$ already recovers $A_G$, so the complete path-count kernel determines the underlying directed multigraph up to isomorphism when the node diagonal remains marked.

It does not canonically distinguish two parallel edges inside their multiplicity space.

---

# 4. The analytic obstruction to route summation

Fix $u,v,n$, and suppose there are $m$ length-$n$ paths

$$
p_1,\ldots,p_m:u\to v.
$$

In the Fock representation, their operators are orthogonal:

$$
L_{p_i}^\ast L_{p_j}=
\delta_{ij}P_u.
$$

Therefore

$$
\left|
\sum_{j=1}^{m}c_jL_{p_j}
\right|=
\left(
\sum_{j=1}^{m}|c_j|^2
\right)^{1/2}.
$$

Endpoint aggregation applies the all-ones functional

$$
(c_1,\ldots,c_m)
\longmapsto
\sum_{j=1}^{m}c_j.
$$

Its norm is

$$
\sqrt m.
$$

If infinitely many routes share the endpoint pair, this functional has no bounded extension to the corresponding $\ell^2$ route corner.

Thus:

$$
\text{route summation changes the natural geometry from }\ell^2
\text{ to }\ell^1.
$$

Consequently, route collapse is algebraically meaningful on finite-support expressions but may fail as a bounded operation on the Fock completion.

---

# 5. Support and attainable lengths

Before reducing to shortest paths, retain only which lengths occur:

$$
\mathcal S_G(v,u;z)=
\sum_{\substack{n\ge0\\N_n(v,u)>0}}z^n.
$$

This forgets route multiplicities but preserves the complete set

$$
L(u,v)=
\{n:N_n(v,u)>0\}.
$$

For a reachable pair, define

$$
d(u,v)=\min L(u,v).
$$

This minimum always exists because path lengths are natural numbers.

So even when route counts are infinite and scalar endpoint summation is unavailable, shortest compositional distance remains unconditionally defined.

The reduction is:

$$
\mathcal P^\#
\longrightarrow
\mathcal S
\longrightarrow
d.
$$

It loses, respectively:

1. route identity;
2. route multiplicity;
3. every nonminimal path length.

---

# 6. Tropicalization

For a nonzero power series with nonnegative coefficients, define

$$
\nu(f)=\min{n:[z^n]f\ne0}.
$$

Because no cancellation occurs,

$$
\nu(fg)=\nu(f)+\nu(g),
$$

and

$$
\nu(f+g)=\min{\nu(f),\nu(g)}.
$$

Thus the passage

$$
\mathcal P_G(v,u;z)
\longmapsto
d(u,v)
$$

is a min-plus, or tropical, compression of the path-counting kernel.

It remembers the earliest compositional depth at which communication is possible.

It forgets everything that occurs later or in parallel.

---

# 7. Re-embedding the distance matrix

From $d$, define the shortest-path zeta kernel

$$
\zeta_d(z)(v,u)=
\begin{cases}
1,&u=v,\\
z^{d(u,v)},&u<v,\\
0,&u\nleq v.
\end{cases}
$$

This differs from the original path-counting kernel.

In general,

$$
\zeta_d(z)\ne\mathcal P_G(z).
$$

For $u<v$, let

$$
d=d(u,v).
$$

Then

$$
\mathcal P_G(v,u;z)=
N_d(v,u)z^d
+
\sum_{n>d}N_n(v,u)z^n,
$$

while

$$
\zeta_d(v,u;z)=z^d.
$$

Define the **route-excess kernel**

$$
X_G(z)=\mathcal P_G(z)-\zeta_d(z).
$$

Its endpoint corner is

$$
X_G(v,u;z)=
\bigl(N_d(v,u)-1\bigr)z^d
+
\sum_{n>d}N_n(v,u)z^n.
$$

It separates two losses.

### Geodesic multiplicity

$$
N_d(v,u)-1.
$$

This counts the excess shortest routes.

### Detour content

$$
\sum_{n>d}N_n(v,u)z^n.
$$

This records all nonshortest routes.

Therefore:

$$
X_G(z)=0
$$

if and only if every comparable node pair is joined by exactly one directed path.

Equivalently:

$$
X_G=0
\iff
\mathsf P(G)\text{ is already thin}.
$$

---

# 8. The weighted Möbius kernel

When the weighted incidence convolution is coefficientwise finite, define

$$
M_d(z)=\zeta_d(z)^{-1}.
$$

Its endpoint coefficient is

$$
M_d(v,u;z)=
\sum_{m\ge1}(-1)^m
\sum_{u=x_0<\cdots<x_m=v}
z^{
d(x_0,x_1)+\cdots+d(x_{m-1},x_m)
}.
$$

This is the weighted Möbius series derived previously.

Compare the two inverses:

$$
\begin{aligned}
\mathcal P_G(z)^{-1}
&=
I-zA_G,\\
\zeta_d(z)^{-1}
&=
M_d(z).
\end{aligned}
$$

The first is local.

The second can contain arbitrarily long alternating factorization terms.

---

# 9. Exact Möbius-defect identity

Since

$$
\mathcal P_G=\zeta_d+X_G,
$$

the inverse-difference identity gives

$$
M_d-(I-zA_G)=
M_dX_G(I-zA_G).
$$

Equivalently,

$$
M_d-(I-zA_G)=
(I-zA_G)X_GM_d.
$$

This is noncommutative: the order of factors matters.

It says:

$$
\text{every nonlocal Möbius correction is generated by the route excess discarded by shortest reduction.}
$$

There is also a formal geometric expansion:

$$
M_d=
(I-zA_G)
+
(I-zA_G)X_G(I-zA_G)
+\cdots
$$

more precisely,

$$
M_d=
\sum_{k\ge0}
\bigl((I-zA_G)X_G\bigr)^k
(I-zA_G),
$$

or equivalently,

$$
M_d=
(I-zA_G)
\sum_{k\ge0}
\bigl(X_G(I-zA_G)\bigr)^k.
$$

Every occurrence of $X_G$ represents one insertion of information discarded by the shortest-path compression.

---

# 10. Unique-route theorem

Under the finiteness conditions needed for both inverses, the following are equivalent:

1. Every comparable pair $u\le v$ has exactly one directed path.
2. $\mathcal P_G(z)=\zeta_d(z)$.
3. $X_G(z)=0$.
4. $M_d(z)=I-zA_G$.
5. Weighted Möbius inversion contains no correction beyond primitive edges.

Therefore:

$$
\text{Möbius complexity measures failure of the path category to be thin.}
$$

This includes failures caused by:

* parallel primitive channels;
* diamonds;
* shortcuts;
* longer detours;
* repeated branching and reconvergence.

---

# 11. Examples

## Unique chain

Let

$$
u\to w\to v.
$$

Then

$$
\mathcal P(v,u;z)=z^2,
$$

and

$$
\zeta_d(v,u;z)=z^2.
$$

Hence

$$
X(v,u;z)=0.
$$

The inverse satisfies

$$
M_d(v,u;z)=0,
$$

because

$$
-z^2+z\cdot z=0.
$$

This agrees with

$$
(I-zA_G)(v,u)=0,
$$

since there is no direct edge $u\to v$.

## Parallel channels

Suppose there are $m$ parallel edges $u\to v$.

Then

$$
\mathcal P(v,u;z)=mz,
$$

$$
\zeta_d(v,u;z)=z,
$$

and

$$
X(v,u;z)=(m-1)z.
$$

The route-count inverse is

$$
\mathcal P^{-1}(v,u)=-mz,
$$

while the weighted Möbius inverse is

$$
M_d(v,u)=-z.
$$

The shortest thin signature has erased the parallel multiplicity.

## Diamond

Suppose

$$
u\to a\to v,
\qquad
u\to b\to v.
$$

Then

$$
\mathcal P(v,u;z)=2z^2,
$$

$$
\zeta_d(v,u;z)=z^2,
$$

and

$$
X(v,u;z)=z^2.
$$

There is no direct edge, so

$$
(I-zA_G)(v,u)=0.
$$

But

$$
M_d(v,u;z)=z^2.
$$

The nonzero Möbius coefficient is exactly the correction induced by the second shortest route.

## Shortcut

Suppose

$$
u\to v
$$

and

$$
u\to w\to v.
$$

Then

$$
\mathcal P(v,u;z)=z+z^2,
$$

$$
\zeta_d(v,u;z)=z,
$$

and

$$
X(v,u;z)=z^2.
$$

The local inverse is

$$
(I-zA_G)(v,u)=-z.
$$

The weighted Möbius inverse is

$$
M_d(v,u;z)=-z+z^2.
$$

The $z^2$ correction is the longer factorization made invisible by shortest reduction.

---

# 12. Möbius complexity is compression compensation

The contrast can now be stated sharply.

## Full path level

$$
R_G^{-1}=1-z\mathbf E.
$$

All routes are retained individually, so inversion merely removes their free compositions and recovers primitive channels.

## Endpoint-counting level

$$
\mathcal P_G^{-1}=I-zA_G.
$$

Routes are aggregated, but all multiplicities and lengths remain, so inversion still recovers primitive edge multiplicities.

## Shortest thin level

$$
\zeta_d^{-1}=M_d.
$$

Alternative routes, multiplicities, and nonminimal lengths have been deleted. Möbius inversion must recreate their net factorization effects through alternating global corrections.

Thus:

$$
\text{Möbius nonlocality is the algebraic price of lossy route compression.}
$$

---

# 13. The complete compression diagram

The sequence is now:

$$
R_G(z)
$$

$$
\downarrow\quad
\text{aggregate paths by endpoints}
$$

$$
\mathcal P_G(v,u;z)=
\sum_nN_n(v,u)z^n
$$

$$
\downarrow\quad
\text{discard multiplicity}
$$

$$
\mathcal S_G(v,u;z)=
\sum_{n:N_n>0}z^n
$$

$$
\downarrow\quad
\text{retain the minimum exponent}
$$

$$
d(u,v)
$$

$$
\downarrow\quad
\text{monomial re-embedding}
$$

$$
\zeta_d(v,u;z)=z^{d(u,v)}
$$

$$
\downarrow\quad
\text{incidence-convolution inversion}
$$

$$
M_d(v,u;z).
$$

The operations have different mathematical types:

* endpoint aggregation is linear where defined;
* support reduction is semiring-valued;
* shortest reduction is tropical and nonlinear over a field;
* monomial re-embedding is lossy;
* Möbius inversion is convolutional and noncommutative.

They should not be treated as one algebra homomorphism.

---

# 14. What remains unconditional for arbitrary systems

For any set-sized system, even with infinitely many routes:

* $R_G(z)$ exists formally;
* the cardinal path-count series $\mathcal P^\#_G$ exists;
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
