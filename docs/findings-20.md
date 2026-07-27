# 1. The rank-restricted order

Fix an ordinal stage $\alpha$. Let

```math
V_\alpha^-=\{x:\tau^-(x)\le \alpha\}
```

be the nodes admitted by the past-rank filtration.

For fixed endpoints $u<v$, define an endpoint-restricted order $P_\alpha^{u,v}$ on

```math
\bigl(V_\alpha^-\cap [u,v]\bigr)\cup\{u,v\}.
```

Write

```math
a\le_\alpha b
```

when an $a\to b$ path exists whose internal nodes lie in $V_\alpha^-$.

This is transitive: if two admissible paths meet at an admitted intermediate node, their concatenation remains admissible.

Define

```math
d_\alpha(a,b)
```

as the shortest length of such a path, with $d_\alpha(a,b)=\infty$ when none exists.

A strict factorization chain

```math
c:\quad
u=x_0<_\alpha x_1<_\alpha\cdots<_\alpha x_m=v
```

has cost

```math
\ell_\alpha(c)=
\sum_{i=1}^{m}d_\alpha(x_{i-1},x_i).
```

The filtered interval complex $\Delta^{N,\alpha}(u,v)$ contains precisely those chains with

```math
\ell_\alpha(c)\le N.
```

# 2. Filtered Euler–Möbius value

Assume for the moment that $\Delta^{N,\alpha}(u,v)$ has finite-dimensional homology, vanishing outside finitely many degrees.

Define

```math
\mu^{N,\alpha}_{\mathrm E}(u,v)=
\widetilde\chi\!\left(
\Delta^{N,\alpha}(u,v)
\right).
```

Using the coherence groups

```math
\mathcal K_n^{N,\alpha}(v,u;k)=
\widetilde H_{n-2}
\left(
\Delta^{N,\alpha}(u,v);k
\right),
```

this becomes

```math
\mu^{N,\alpha}_{\mathrm E}(u,v)=
\sum_{n\ge1}
(-1)^n
\dim_k
\mathcal K_n^{N,\alpha}(v,u;k).
```

The signs have the expected interpretation:

* a temporary cover class contributes $-1$;
* a diamond relation contributes $+1$;
* a third-level hexagonal coherence contributes $-1$;
* and so forth.

For finite poset intervals, the ordinary Möbius function is exactly the reduced Euler characteristic of the open-interval order complex.

## Chain-count formula

Let

```math
c_m^{N,\alpha}(u,v)
```

be the number of strict chains with $m$ reachability factors and cost at most $N$:

```math
u=x_0<_\alpha x_1<_\alpha\cdots<_\alpha x_m=v.
```

Then

```math
\mu^{N,\alpha}_{\mathrm E}(u,v)=
\sum_{m\ge1}
(-1)^m
c_m^{N,\alpha}(u,v).
```

This is the filtered inclusion–exclusion signature of all accessible factorizations.

# 3. Immediate vanishing bound

Every strict reachability factor has positive path length:

```math
d_\alpha(x_{i-1},x_i)\ge1.
```

Therefore an $m$-factor chain has

```math
\ell_\alpha(c)\ge m.
```

Consequently,

```math
\mathcal K_m^{N,\alpha}(v,u)=0
\qquad\text{whenever }m>N.
```

A compositional budget $N$ cannot support coherence order greater than $N$.

It also identifies the exact region in which filtered coherence can occur.

# 4. Length-weighted Möbius series

Instead of cumulatively counting all chains with cost at most $N$, retain their exact costs.

Define

```math
\mathfrak m_\alpha(u,v;z)=
\sum_{m\ge1}(-1)^m
\sum_{\substack{
u=x_0<_\alpha\cdots<_\alpha x_m=v
}}
z^{\ell_\alpha(x_0,\ldots,x_m)}.
```

The coefficient

```math
[z^L]\mathfrak m_\alpha(u,v;z)
```

is the signed number of factorization chains whose minimum realizable total path length is exactly $L$.

This series is an ordinary integer-valued formal series when, for every $L$, only finitely many chains have cost $L$.

Then

```math
\mu^{N,\alpha}_{\mathrm E}(u,v)=
\sum_{L\le N}
[z^L]\mathfrak m_\alpha(u,v;z).
```

Equivalently, the generating function of cumulative Euler values is

```math
\sum_{N\ge0}
\mu^{N,\alpha}_{\mathrm E}(u,v)t^N=
\frac{\mathfrak m_\alpha(u,v;t)}{1-t}.
```

So the filtered Euler profile and the exact-cost Möbius series determine one another.

# 5. Weighted zeta inversion

Under local or coefficientwise finiteness, define a weighted zeta kernel on $P_\alpha^{u,v}$:

```math
\zeta_\alpha(z)(a,b)=
\begin{cases}
1,&a=b,\\
z^{d_\alpha(a,b)},&a<_\alpha b,\\
0,&\text{otherwise}.
\end{cases}
```

Write

```math
\zeta_\alpha(z)=\delta+W_\alpha(z).
```

Its convolution inverse is

```math
\zeta_\alpha(z)^{-1}=
\delta-W_\alpha+W_\alpha^{*2}-W_\alpha^{*3}+\cdots.
```

For $u<v$,

```math
\zeta_\alpha(z)^{-1}(u,v)=
\mathfrak m_\alpha(u,v;z).
```

Indeed, the $m$-fold convolution term sums over strict $m$-factor chains, and multiplication of their weights gives

```math
z^{d_\alpha(x_0,x_1)}
\cdots
z^{d_\alpha(x_{m-1},x_m)}=
z^{\ell_\alpha(c)}.
```

At the final rank stage and for a finite interval,

```math
\mathfrak m_\infty(u,v;1)=
\mu_P(u,v).
```

Thus the ordinary Möbius value is obtained by forgetting all compositional-cost distinctions:

```math
\text{weighted Möbius series}
\overset{z=1}{\longrightarrow}
\text{ordinary Möbius number}.
```

This specialization is defined when the series is a polynomial or otherwise converges; an arbitrary infinite interval need not satisfy this condition.

# 6. The leading term: geodesic factorization coherence

The triangle inequality gives

```math
d_\alpha(u,v)
\le
\sum_{i=1}^m
d_\alpha(x_{i-1},x_i).
```

Hence the smallest possible exponent in $\mathfrak m_\alpha$ is

```math
d_\alpha(u,v).
```

Define the geodesic factorization complex

```math
\Delta_{\mathrm{geo}}^\alpha(u,v)=
\Delta^{d_\alpha(u,v),\alpha}(u,v).
```

It consists of precisely those factorizations that do not increase the minimum path length.

Then

```math
[z^{d_\alpha(u,v)}]
\mathfrak m_\alpha(u,v;z)=
\widetilde\chi
\left(
\Delta_{\mathrm{geo}}^\alpha(u,v)
\right).
```

The leading coefficient therefore detects the topology of the shortest-factorization geometry.

Higher coefficients measure nongeodesic alternatives that become available only with additional compositional budget.

# 7. Examples

## Unique two-edge chain

Suppose

```math
u\to w\to v
```

with no shortcut.

The unfactored reachability arrow has cost two:

```math
-z^2.
```

The factorization through $w$ also has cost two:

```math
+z^2.
```

Therefore

```math
\mathfrak m(u,v;z)=0.
```

There is no independent coherence.

## Shortcut

Add

```math
u\to v.
```

Now

```math
d(u,v)=1,
```

while the factorization through $w$ costs two. Hence

```math
\mathfrak m(u,v;z)=
-z+z^2.
```

The cumulative Euler profile is

```math
\mu_{\mathrm E}^{N}(u,v)=
\begin{cases}
0,&N<1,\\
-1,&N=1,\\
0,&N\ge2.
\end{cases}
```

The shortcut creates a temporary primitive class that disappears when the longer factorization becomes visible.

## Symmetric diamond

Suppose

```math
u\to a\to v,
\qquad
u\to b\to v.
```

All relevant costs equal two:

```math
\mathfrak m(u,v;z)=
-z^2+z^2+z^2.
```

Therefore

```math
\mathfrak m(u,v;z)=z^2.
```

The degree-two relation appears at budget two.

## Asymmetric diamond

Suppose the $a$-branch costs two and the $b$-branch costs three.

Then

```math
\mathfrak m(u,v;z)=
-z^2+z^2+z^3=
z^3.
```

The geodesic direct/factorized contributions cancel. The genuine diamond coherence appears only when the longer branch becomes available.

## Boolean interval (B_3)

Every strict factorization chain from bottom to top has total cost three. The alternating chain count is the ordinary Möbius value $-1$. Thus

```math
\mathfrak m(\varnothing,[3];z)=
-z^3.
```

The third-level coherence is concentrated at exact compositional budget three.

## Parallel primitive channels

With several parallel channels $u\to v$ and no intermediate node,

```math
\mathfrak m(u,v;z)=-z.
```

The result is independent of channel multiplicity.

That multiplicity existed on the route-resolved page but disappeared under vertical collapse. This confirms that the weighted Möbius series is still a **thin** invariant.

# 8. Two-parameter persistence remains primary

For each coherence degree $n$, define

```math
M_n(N,\alpha)=
\mathcal K_n^{N,\alpha}(v,u;k).
```

For

```math
N\le M,\qquad \alpha\le\beta,
```

there is a canonical persistence map

```math
M_n(N,\alpha)
\longrightarrow
M_n(M,\beta).
```

The pointwise Betti function is

```math
\beta_n(N,\alpha)=
\dim_kM_n(N,\alpha).
```

A finer invariant is the two-parameter rank function

```math
\rho_n
\bigl(
(N,\alpha),(M,\beta)
\bigr)=
\mathrm{rank}
\left[
M_n(N,\alpha)
\to
M_n(M,\beta)
\right].
```

This records which classes survive from one length/rank scale to another.

Rank invariants and their generalizations are central tools in multiparameter persistence, but unlike the one-parameter finite-type case, a simple complete barcode classification does not generally exist.

# 9. Persistent Euler rank

The pointwise Euler value knows only what exists at one scale. We can retain some survival information by defining

```math
\Xi
\bigl(
(N,\alpha),(M,\beta)
\bigr)=
\sum_{n\ge1}
(-1)^n
\rho_n
\bigl(
(N,\alpha),(M,\beta)
\bigr),
```

whenever the sum is finite.

At equal parameter values,

```math
\Xi((N,\alpha),(N,\alpha))=
\mu_{\mathrm E}^{N,\alpha}(u,v).
```

For distinct parameter values, $\Xi$ is the signed number of coherence classes that persist across the specified rectangle in parameter space.

It is finer than the pointwise Euler profile but still much coarser than the full graded rank invariant:

```math
{\rho_n}_n
\longrightarrow
\Xi
```

forgets which homological degree each surviving class occupied.

A surviving degree-two class and a surviving degree-three class can cancel in $\Xi$.

# 10. Why ordinal rank should remain an index

Length is naturally indexed by

```math
N\in\mathbb N,
```

so the variable $z$ is canonical.

Transfinite rank is different. There is no canonical real or complex scalar corresponding to an arbitrary ordinal, and ordinal addition is not a commutative grading law suitable for an ordinary power series.

Therefore we should retain

```math
\alpha\longmapsto
\mathfrak m_\alpha(u,v;z)
```

as an ordinal-indexed family.

At a successor stage, define the jump

```math
J_\alpha(u,v;z)=
\mathfrak m_{\alpha+1}(u,v;z)-
\mathfrak m_\alpha(u,v;z).
```

It records the signed exact-cost factorizations becoming available when the new rank layer enters.

At a limit ordinal $\lambda$, no finite chain first appears only at $\lambda$. Every finite chain uses finitely many nodes and therefore already occurs at some earlier stage:

```math
\Delta^{N,\lambda}(u,v)=
\bigcup_{\alpha<\lambda}
\Delta^{N,\alpha}(u,v).
```

Homology commutes with this filtered union at the algebraic chain level. Scalar Euler characteristics, however, need not commute with it unless suitable finite-type assumptions hold.

If all ranks happen to be natural numbers, one may introduce a second formal variable $y$. That is a valid specialization, but not the unrestricted cardinality-independent construction.

# 11. Exact information-loss hierarchy

We can now state precisely what each level retains.

## Full bifiltered route–factorization complex

```math
F_{N,\alpha}C_{\bullet,\bullet}^{\mathrm{RF}}.
```

Retains:

* every actual path;
* parallel channels;
* exact lengths;
* internal rank profiles;
* route-identification chains;
* factorization topology;
* all persistence maps.

## Coherence persistence modules

```math
\mathcal K_n^{N,\alpha}.
```

Retain:

* homological degree;
* birth, survival, and death through $(N,\alpha)$;
* field-dependent Betti and torsion information if integral coefficients are retained.

Lose:

* individual route bases;
* orthogonality;
* chain-level attaching information.

## Rank invariant

```math
\rho_n((N,\alpha),(M,\beta)).
```

Retains:

* dimensions of images across scales.

Loses:

* extension data and much of the full multiparameter module structure.

## Filtered Euler profile

```math
\mu_{\mathrm E}^{N,\alpha}.
```

Retains:

* one signed total at each parameter value.

Loses:

* homological degrees;
* persistence maps;
* torsion;
* cancellations between even and odd coherence.

Euler-characteristic profiles are computationally economical precisely because they compress a filtered complex to one alternating scalar per scale.

## Weighted Möbius series

```math
\mathfrak m_\alpha(u,v;z).
```

Retains:

* exact compositional costs of net Euler contributions;
* shortcut delays;
* asymmetric-factorization thresholds;
* the final Möbius value when specialization is valid.

Loses:

* individual Betti degrees;
* persistence lifespans;
* route multiplicity and orthogonality.

## Ordinary Möbius number

```math
\mu(u,v)=
\mathfrak m_\infty(u,v;1).
```

Retains only the final alternating total.

# 12. The finiteness boundary

The filtered complexes and their simplicial homology are always defined.

The integer

```math
\widetilde\chi(\Delta^{N,\alpha})
```

is canonical when, for example:

* the sublevel complex has finitely many simplices; or
* its homology is finite-dimensional and nonzero in only finitely many degrees; or
* its chain complex is perfect, allowing an Euler class in $K_0$.

Similarly,

```math
\mathfrak m_\alpha(u,v;z)
```

has ordinary integer coefficients when there are finitely many factorization chains of every exact cost.

If infinitely many positive and negative terms occur at one cost, A1–A5 provide no canonical subtraction of infinite cardinals. In that case:

```math
\text{retain the chain complex or persistence module;}
\quad
\text{do not force a scalar Möbius value}.
```
