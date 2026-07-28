# 1. Fixed-length route spaces

Let

```math
\mathsf P_n(G)=
\{p:\lvert p\rvert=n\}
```

be the set of length-$n$ paths, and define the route Hilbert space

```math
\mathcal H_n=
\ell^2(\mathsf P_n(G)).
```

Its canonical orthonormal basis is

```math
{\xi_p:p\in\mathsf P_n(G)}.
```

For each ordered node pair $(u,v)$, let

```math
\mathsf P_n(u,v)=
\{p:u\to v,\ \lvert p\rvert=n\}
```

and

```math
N_n(v,u)=\lvert\mathsf P_n(u,v)\rvert.
```

Then

```math
\mathcal H_n=
\bigoplus_{(u,v)\in V\times V}
\ell^2\bigl(\mathsf P_n(u,v)\bigr).
```

This is the orthogonal decomposition of the route space into endpoint fibers.

Also define the endpoint-pair Hilbert space

```math
\mathcal K=
\ell^2(V\times V),
```

with basis vectors

```math
\eta_{v,u}.
```

The ordered pair remains marked: $\eta_{v,u}$ represents routes beginning at $u$ and terminating at $v$.

# 2. The algebraic endpoint-collapse map

On finitely supported route vectors, define

```math
\Sigma_n^0\xi_p=
\eta_{r(p),s(p)}.
```

Therefore

```math
\Sigma_n^0
\left(
\sum_pc_p\xi_p
\right)=
\sum_{u,v}
\left(
\sum_{p\in\mathsf P_n(u,v)}c_p
\right)\eta_{v,u}.
```

This is endpoint aggregation:

* individual routes are orthogonal in $\mathcal H_n$;
* routes with the same endpoints are added in $\mathcal K$.

The behavior of $\Sigma_n^0$ is controlled completely by the cardinalities $N_n(v,u)$.

# 3. The exact analytic trichotomy

There are three sharply different regimes.

## Regime I: uniformly finite route fibers

Suppose

```math
M_n=
\sup_{u,v}N_n(v,u)<\infty.
```

Then $\Sigma_n^0$ extends to a bounded operator

```math
\Sigma_n:\mathcal H_n\to\mathcal K
```

with

```math
|\Sigma_n|=
\sqrt{M_n}.
```

This is the largest fixed-length reconvergence multiplicity.

## Regime II: every fiber finite, but not uniformly bounded

Suppose

```math
N_n(v,u)<\infty
\quad\text{for every }(u,v),
```

but

```math
\sup_{u,v}N_n(v,u)=\infty.
```

Then $\Sigma_n^0$ is unbounded, but it is closable. Its closure has domain

```math
\mathrm{Dom}(\Sigma_n)=
\left\lbrace x\in\mathcal H_n: \sum_{u,v} \left| \sum_{p\in\mathsf P_n(u,v)}x_p \right|^2 <\infty \right\rbrace.
```

It is a densely defined closed operator.

## Regime III: one endpoint fiber is infinite

Suppose

```math
N_n(v,u)
```

is infinite for at least one pair.

Then the algebraic collapse map is not closable.

To see this, choose distinct paths

```math
p_1,p_2,\ldots\in\mathsf P_n(u,v)
```

and define

```math
x_N=
\frac1N\sum_{j=1}^N\xi_{p_j}.
```

Then

```math
|x_N|=
\frac1{\sqrt N}
\longrightarrow0,
```

while

```math
\Sigma_n^0x_N=
\eta_{v,u}
```

for every $N$.

Thus the graph of $\Sigma_n^0$ approaches

```math
(0,\eta_{v,u}),
```

which cannot belong to the graph of any operator.

Therefore:

```math
\begin{array}{c|c}
\text{Route multiplicities at length }n&
\text{Endpoint collapse}\\
\hline
\sup N_n<\infty&
\text{bounded}\\
N_n<\infty\text{ individually, but unbounded}&
\text{closed unbounded}\\
N_n=\infty\text{ for some endpoint pair}&
\text{nonclosable}
\end{array}
```

This is a stronger version of the earlier finite/infinite route distinction.

# 4. Equal-route and defect directions

Assume temporarily that

```math
m=N_n(v,u)
```

is finite and nonzero.

Inside the route fiber

```math
\mathcal H_n(v,u)=
\ell^2(\mathsf P_n(u,v)),
```

define the normalized equal-route vector

```math
\omega_{v,u}^{(n)}=
\frac1{\sqrt m}
\sum_{p\in\mathsf P_n(u,v)}\xi_p.
```

Also define the route-defect space

```math
\mathcal D_n(v,u)=
\left\lbrace \sum_pc_p\xi_p: \sum_pc_p=0 \right\rbrace.
```

These give an orthogonal decomposition

```math
\mathcal H_n(v,u)=
\mathbb C\omega_{v,u}^{(n)}
\oplus
\mathcal D_n(v,u).
```

The collapse map acts by

```math
\Sigma_n\omega_{v,u}^{(n)}=
\sqrt m,\eta_{v,u}
```

and

```math
\Sigma_n\mathcal D_n(v,u)=0.
```

Thus:

```math
\ker\Sigma_n=
\bigoplus_{u,v}\mathcal D_n(v,u).
```

For finite $m$,

```math
\dim\mathcal D_n(v,u)=m-1.
```

This is the length-$n$, endpoint-$(u,v)$ portion of the route-collapse ideal.

# 5. Why infinite fibers behave differently

If $\mathsf P_n(u,v)$ is infinite, the formal equal-route vector

```math
\sum_{p\in\mathsf P_n(u,v)}\xi_p
```

does not lie in $\ell^2$.

There is therefore no normalized equal-route direction orthogonal to the route defects.

Indeed, the finite-support zero-sum vectors are dense in the entire fiber. For any fixed route $p$, choose distinct alternatives $q_1,\ldots,q_N$ and define

```math
y_N=
\xi_p-
\frac1N\sum_{j=1}^N\xi_{q_j}.
```

Then

```math
y_N\in\mathcal D_n^{\mathrm{alg}}(v,u)
```

and

```math
|y_N-\xi_p|=\frac1{\sqrt N}\to0.
```

Hence

```math
\overline{\mathcal D_n^{\mathrm{alg}}(v,u)}=
\ell^2(\mathsf P_n(u,v))
```

when the route fiber is infinite.

So the finite case has

```math
\text{one equal-route direction}
\oplus
\text{route defects},
```

while the infinite case has only the closure of route-defect directions.

That is the precise Hilbert-space reason endpoint summation becomes nonclosable.

# 6. Polar decomposition of endpoint collapse

Assume every fixed endpoint fiber at length $n$ is finite, although their sizes may be unbounded.

Define the diagonal multiplicity operator on $\mathcal K$:

```math
D_n\eta_{v,u}=
N_n(v,u)\eta_{v,u}.
```

Its square root acts by

```math
D_n^{1/2}\eta_{v,u}=
\sqrt{N_n(v,u)}\,\eta_{v,u}.
```

Define the normalized collapse partial isometry

```math
U_n:\mathcal H_n\to\mathcal K
```

by

```math
U_n\omega_{v,u}^{(n)}=
\eta_{v,u}
```

and

```math
U_n\mathcal D_n(v,u)=0.
```

Then

```math
\Sigma_n=
D_n^{1/2}U_n.
```

Equivalently,

```math
\Sigma_n=
U_n|\Sigma_n|.
```

The general polar-decomposition theorem applies to closed densely defined Hilbert-space operators; here the decomposition is visible directly from the endpoint blocks.

The initial projection is

```math
U_n^\ast U_n=
P_n^{\mathrm{eq}},
```

the projection onto all equal-route directions, while

```math
U_nU_n^\ast
```

is the projection onto endpoint pairs admitting at least one length-$n$ route.

Therefore endpoint aggregation factors canonically into three operations:

```math
\begin{aligned}
\mathcal H_n
&\xrightarrow{P_n^{\mathrm{eq}}}
\text{equal-route sectors}\\
&\xrightarrow{U_n}
\text{endpoint-pair sectors}\\
&\xrightarrow{D_n^{1/2}}
\text{multiplicity-weighted endpoint data}.
\end{aligned}
```

In words:

1. discard the orthogonal route-defect directions;
2. identify each normalized equal-route sector with its endpoint pair;
3. amplify it by the square root of the number of routes.

This is the exact operator-level bridge from $\ell^2$ routes to endpoint counting.

# 7. The two Gram operators

The endpoint Gram operator is

```math
\Sigma_n\Sigma_n^\ast=D_n.
```

Thus

```math
\Sigma_n\Sigma_n^\ast\eta_{v,u}=
N_n(v,u)\eta_{v,u}.
```

It records the endpoint multiplicities exactly.

On the route side,

```math
\Sigma_n^\ast\Sigma_n
```

acts on each finite route fiber as the all-ones matrix:

```math
\Sigma_n^\ast\Sigma_n
\big|_{\mathcal H_n(v,u)}=
J_{N_n(v,u)}.
```

It has:

* eigenvalue $N_n(v,u)$ on the equal-route direction;
* eigenvalue zero on every route-defect direction.

Therefore the nonzero singular value associated with the endpoint pair $(u,v)$ is

```math
\sqrt{N_n(v,u)}.
```

The complete singular-value family of $\Sigma_n$ is exactly the square-root route-multiplicity profile.

# 8. Why the marked endpoint diagonal remains necessary

If we forget the basis projections

```math
E_{v,u}=
|\eta_{v,u}\rangle\langle\eta_{v,u}|,
```

the singular values retain only the multiset

```math
\left\lbrace \sqrt{N_n(v,u)} \right\rbrace_{u,v}.
```

They no longer say which multiplicity belongs to which endpoint pair.

With the marked pair diagonal,

```math
\mathcal D_{\mathrm{pair}}=
\mathrm{alg}{E_{v,u}},
```

we recover

```math
N_n(v,u)=
\langle
D_n\eta_{v,u},
\eta_{v,u}
\rangle.
```

Hence:

```math
\text{an operator without its distinguished orthogonal sectors loses relational identity}.
```

# 9. The positive multiplicity tower

The family

```math
{D_n}_{n\ge0}
```

is a canonical positive shadow of the resolved path system whenever the endpoint multiplicities are finite.

It contains all path counts:

```math
D_n(v,u)=N_n(v,u).
```

From it, we recover three progressively compressed structures.

## Exact-length reachability support

Define the support projection

```math
Z_n=
\mathbf1_{(0,\infty)}(D_n).
```

Then

```math
Z_n\eta_{v,u}=
\begin{cases}
\eta_{v,u},&N_n(v,u)>0,\\
0,&N_n(v,u)=0.
\end{cases}
```

## Shortest compositional distance

```math
d(u,v)=
\min
\left\lbrace n: Z_n\eta_{v,u}=\eta_{v,u} \right\rbrace.
```

## Geodesic multiplicity

At the first supported length,

```math
g(v,u)=
\left\langle
D_{d(u,v)}\eta_{v,u},
\eta_{v,u}
\right\rangle.
```

Thus the min-plus data arise from the positive tower by:

```math
{D_n}
\longrightarrow
{\mathrm{supp}D_n}
\longrightarrow
\text{first supported }n.
```

And the geodesic multiplicity is the first nonzero diagonal value.

# 10. The three geometries now factor exactly

We can state the relationship more sharply than before.

## Resolved $\ell^2$ geometry

Primary object:

```math
\mathcal H_n=
\bigoplus_{u,v}
\ell^2(\mathsf P_n(u,v)).
```

Retains:

* every individual route;
* orthogonality;
* route-defect directions;
* endpoint decomposition.

## Multiplicity geometry

Primary object:

```math
D_n=
\Sigma_n\Sigma_n^\ast.
```

Retains:

* exact path multiplicity for every endpoint pair;
* reconvergence magnitude;
* singular values of endpoint collapse.

Loses:

* identities of individual paths;
* internal overlap and branching structure;
* the route-defect basis.

## Support/min-plus geometry

Primary objects:

```math
Z_n=\mathrm{supp}D_n
```

and

```math
d(u,v)=\min{n:Z_n(v,u)=1}.
```

Retain:

* which lengths are possible;
* which length occurs first.

Lose:

* multiplicity;
* orthogonality;
* every later route length after taking the minimum.

The exact compression chain is therefore

```math
\mathcal H_n
\xrightarrow{\Sigma_n}
D_n
\xrightarrow{\mathrm{supp}}
Z_n
\xrightarrow{\min n}
d.
```

# 11. A stronger finite/infinite boundary

The endpoint-collapse tower exposes three notions that had previously been mixed:

```math
\begin{aligned}
\text{finite multiplicity}&:
N_n(v,u)<\infty,\\
\text{uniform finite multiplicity}&:
\sup_{u,v}N_n(v,u)<\infty,\\
\text{finite total branching}&:
\sup_u\sum_vN_n(v,u)<\infty.
\end{aligned}
```

They control different operators.

### Endpoint collapse

```math
\Sigma_n
```

is bounded exactly under uniform finite endpoint multiplicity.

### Forward Fock creator

```math
S_+^n
```

is bounded exactly when total length-$n$ branching is uniformly finite:

```math
\sup_u\sum_vN_n(v,u)<\infty.
```

Since

```math
\sup_{u,v}N_n(v,u)
\le
\sup_u\sum_vN_n(v,u),
```

bounded forward Fock growth implies bounded fixed-length endpoint collapse.

The converse fails.

A source may reach infinitely many distinct endpoints by one route each:

```math
N_n(v,u)\le1
```

for every endpoint, so $\Sigma_n$ is bounded with norm one, while

```math
\sum_vN_n(v,u)=\infty,
```

so the global forward creator is not bounded.

Thus:

```math
\text{reconvergence boundedness}
\neq
\text{branching boundedness}.
```

# 12. Tree and funnel revisited

## $d$-ary tree

At depth $n$, every reached endpoint has one route:

```math
N_n(v,u)\in\{0,1\}.
```

Therefore

```math
D_n=Z_n
```

on the reachable endpoint pairs and

```math
|\Sigma_n|=1.
```

But there are $d^n$ such endpoints, so

```math
|S_+^nP_u|=d^{n/2}.
```

Route growth comes entirely from branching.

## $d$-parallel funnel

At depth $n$, one endpoint receives

```math
d^n
```

routes.

Therefore

```math
|\Sigma_n|=d^{n/2}
```

and

```math
|S_+^nP_u|=d^{n/2}.
```

Route growth appears entirely as endpoint-collapse amplification.

The two systems have the same total Fock growth but radically different collapse operators:

```math
\begin{array}{c|c|c}
&d\text{-ary tree}&d\text{-parallel funnel}\\
\hline
|\Sigma_n|&1&d^{n/2}\\
\mathrm{rank}D_n&d^n&1\\
|D_n|&1&d^n
\end{array}
```

This operator tower distinguishes them immediately.

# 13. What remains for infinite route multiplicities

When some $N_n(v,u)$ is infinite, the cardinal profile

```math
(u,v)\longmapsto N_n(v,u)
```

still exists.

The support projection $Z_n$ and shortest distance $d$ still exist.

What fails is precisely the Hilbert-space endpoint-summation operator:

```math
\Sigma_n^0
```

is nonclosable, and no positive Hilbert operator $D_n=\Sigma_n\Sigma_n^\ast$ represents an infinite cardinal as an ordinary scalar eigenvalue.

Thus the unrestricted hierarchy is:

```math
\begin{aligned}
\text{all cardinalities:}&\quad
N_n^\mathcal{\#},\ Z_n,\ d,\\
\text{finite route fibers:}&\quad
\Sigma_n,\ D_n,\\
\text{uniformly finite fibers:}&\quad
\Sigma_n\text{ bounded}.
\end{aligned}
```

The analytic failure marks the boundary of the Hilbert representation without changing the underlying relational data.
