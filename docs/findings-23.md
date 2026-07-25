## 1. The complete fixed-depth inequality chain

We have

$$
T\le Q\le MT\le T^2
$$

and also

$$
Q\ge\frac{T^2}{R}.
$$

### Proof

Since every nonzero $a_v$ is a positive integer,

$$
a_v^2\ge a_v,
$$

so $Q\ge T$.

Since $a_v\le M$,

$$
a_v^2\le Ma_v,
$$

so $Q\le MT$.

Since $M\le T$,

$$
MT\le T^2.
$$

Finally, Cauchy–Schwarz gives

$$
T^2=
\left(\sum_{a_v>0}a_v\right)^2
\le
R\sum_{a_v>0}a_v^2=
RQ.
$$

---

# 2. Exact equality criteria

Each equality identifies a precise structural regime.

## No reconvergence at depth (n)

$$
Q=T
\iff
a_v\in\{0,1\}\text{ for every }v.
$$

Equivalently, no two distinct length-$n$ paths from $u$ terminate at the same node.

Operatorially,

$$
|A^n\delta_u|_2=
|S_+^nP_u|.
$$

Endpoint collapse has caused no amplification because every route remains in its own endpoint sector.

This is **lengthwise thinness at $(u,n)$**. It does not yet imply a unique route overall: there might still be paths of different lengths connecting the same endpoints.

---

## Maximal endpoint funneling

$$
Q=T^2
\iff
R=1.
$$

All length-$n$ paths from $u$ terminate at one node.

Then

$$
|A^n\delta_u|_2=
|S_+^nP_u|^2.
$$

Every orthogonal route amplitude has been collapsed into one endpoint coordinate.

---

## Uniform reconvergence

$$
Q=\frac{T^2}{R}
\iff
a_v=\frac TR
\quad\text{for every reached endpoint }v.
$$

The path multiplicity is distributed equally among the $R$ endpoints.

This minimizes $Q$ when $T$ and $R$ are fixed.

---

## Saturation of the endpoint-collapse norm

$$
Q=MT
\iff
a_v\in\{0,M\}\text{ for every }v.
$$

Every reached endpoint receives exactly the maximum multiplicity $M$.

Recall that the endpoint-collapse operator satisfies

$$
|C_{n,u}|^2=M.
$$

Thus $Q=MT$ is exactly the condition under which the all-route vector attains the norm of $C_{n,u}$.

---

# 3. A parameter-free reconvergence profile

The ratio

$$
\kappa_n(u)=
\frac{Q}{T}=
\frac{\sum_vN_n(v,u)^2}
{\sum_vN_n(v,u)}
$$

lies in

$$
1\le\kappa_n(u)\le M.
$$

It is the route-weighted average endpoint multiplicity.

Equivalently,

$$
\kappa_n(u)=
\frac{|A^n\delta_u|*2^2}
{|S*+^nP_u|^2}.
$$

So:

* $\kappa_n(u)=1$ means no reconvergence;
* $\kappa_n(u)=T$ means complete funneling into one endpoint.

Another useful quantity is

$$
R_{\mathrm{eff},n}(u)=
\frac{T^2}{Q}.
$$

It satisfies

$$
1\le R_{\mathrm{eff},n}(u)\le R.
$$

It is the effective number of endpoint sectors occupied by the route family:

* $R_{\mathrm{eff}}=R$ under uniform multiplicity;
* $R_{\mathrm{eff}}=1$ under total funneling.

Neither introduces a probability law or dynamics. They are normalized expressions of finite route counts.

---

# 4. Global structural versions

## Lengthwise-thin systems

The following are equivalent:

1. For every $u,v,n$,
$$
   N_n(v,u)\le1.
$$
2. For every $u,n$,
$$
   \sum_vN_n(v,u)^2=
   \sum_vN_n(v,u).
$$
3. For every $u,n$,
$$
   |A^n\delta_u|_2=
   |S_+^nP_u|.
$$

Such a system has no equal-length reconvergence.

It can still contain a shortcut:

$$
u\to v,
\qquad
u\to w\to v,
$$

because these two routes have different lengths.

---

## Fully unique-route systems

The following are equivalent:

1. For every ordered pair $(u,v)$, there is at most one finite path $u\to v$.
2. The path category is thin.
3. For every $(u,v)$, at most one length $n$ has
$$
   N_n(v,u)=1,
$$
   and all other $N_m(v,u)$ vanish.
4. Every path is geodesic and no two paths have the same endpoints.
5. The route-excess kernel vanishes:
$$
   X_G(z)=0.
$$
6. The route-counting kernel equals the shortest monomial kernel:
$$
   \mathcal P_G(z)=\zeta_d(z).
$$
7. Whenever the scalar inverses exist,
$$
   M_d(z)=I-zA_G.
$$

Thus:

$$
\text{unique routes}
\iff
\text{weighted Möbius inversion remains completely local}.
$$

This is stronger than lengthwise thinness because it also forbids different-length alternatives.

---

## Maximal funnel systems

Suppose that, for every node $u$, all outgoing primitive channels have the same target, although parallel channels are allowed.

Then the underlying simple support relation is a partial function

$$
f:V\rightharpoonup V.
$$

Every length-$n$ path from $u$, when one exists, terminates at the single node

$$
f^n(u).
$$

Conversely, if every source has only one possible endpoint at every positive length, then the length-one case implies that all outgoing channels from each node share one target.

Therefore:

$$
\begin{aligned}
&\text{all paths from each source funnel to one endpoint at every depth}\\
&\iff
\text{the simple support graph has outdegree at most one}.
\end{aligned}
$$

If the number of parallel channels along the successive transitions is

$$
m_0,m_1,\ldots,
$$

then

$$
T_n(u)=m_0m_1\cdots m_{n-1},
$$

and

$$
Q_n(u)=T_n(u)^2.
$$

---

# 5. Spectral twins with opposite endpoint geometry

Consider two families with the same integer $d\ge2$.

## (d)-ary branching tree

Every node has $d$ distinct children and there is no reconvergence.

From a fixed root,

$$
T_n=d^n,
\qquad
R_n=d^n,
\qquad
M_n=1,
\qquad
Q_n=d^n.
$$

Hence

$$
|S_+^nP_u|=d^{n/2}
$$

and

$$
|A^n\delta_u|_2=d^{n/2}.
$$

## Parallel-channel funnel

Take a one-way chain, with $d$ parallel channels between consecutive nodes.

Then

$$
T_n=d^n,
\qquad
R_n=1,
\qquad
M_n=d^n,
\qquad
Q_n=d^{2n}.
$$

Again,

$$
|S_+^nP_u|=d^{n/2},
$$

but now

$$
|A^n\delta_u|_2=d^n.
$$

So the two systems have identical:

$$
\text{Fock route growth}
$$

and identical

$$
\ell^1\text{ path-count growth},
$$

yet occupy opposite reconvergence extremes:

$$
\begin{array}{c|c|c}
&d\text{-ary tree}&d\text{-parallel funnel}\\
\hline
R_n&d^n&1\\
M_n&1&d^n\\
Q_n&d^n&d^{2n}\\
\kappa_n&1&d^n
\end{array}
$$

Therefore:

$$
r(S_+)
\text{ alone cannot distinguish expansion from reconvergence}.
$$

This is a clean infinite obstruction to treating one spectral radius as a complete structural descriptor.

---

# 6. Refined bounds for weighted Möbius coefficients

Recall that

$$
m_L(v,u)=
[z^L]M_d(v,u;z)=
\sum_{r=1}^{L}(-1)^r c_{r,L}(v,u),
$$

where $c_{r,L}$ counts strict $r$-factor chains of total shortest-path cost $L$.

Define the geodesic multiplicity

$$
g(b,a)=N_{d(a,b)}(b,a).
$$

For each $r,L$, put

$$
G_{r,L}(v,u)=
\sum_{\substack{
u=x_0<\cdots<x_r=v\\
\sum_i d(x_{i-1},x_i)=L
}}
\prod_{i=1}^{r}g(x_i,x_{i-1}).
$$

This counts each factorization chain together with one selected geodesic realization of every factor.

Then:

$$
c_{r,L}(v,u)
\le
G_{r,L}(v,u)
\le
\binom{L-1}{r-1}N_L(v,u).
$$

### First equality

$$
c_{r,L}=G_{r,L}
$$

if and only if every factor occurring in every cost-$L$, $r$-step chain has a unique geodesic.

### Second equality

$$
G_{r,L}=
\binom{L-1}{r-1}N_L
$$

if and only if every length-$L$ path, cut at any chosen $r-1$ positions, is geodesic on every resulting segment.

Thus the earlier bound

$$
|m_L(v,u)|
\le
2^{L-1}N_L(v,u)
$$

factorizes more precisely as

$$
|m_L|
\le
\sum_r c_{r,L}
\le
\sum_rG_{r,L}
\le
2^{L-1}N_L.
$$

---

# 7. Exact Möbius cancellation criteria

Separate the factorization chains by parity:

$$
E_L=
\sum_{\substack{r\ge1\\r\text{ even}}}
c_{r,L},
$$

$$
O_L=
\sum_{\substack{r\ge1\\r\text{ odd}}}
c_{r,L}.
$$

Then

$$
m_L=E_L-O_L.
$$

Consequently:

## No cancellation

$$
|m_L|=E_L+O_L
\iff
E_L=0\text{ or }O_L=0.
$$

All cost-$L$ factorizations have the same parity.

## Complete cancellation

$$
m_L=0
\iff
E_L=O_L.
$$

Equal numbers of even- and odd-factor chains cancel exactly.

This is purely an Euler-type cancellation. It does not imply that the filtered interval complex is contractible; nontrivial homology may cancel between even and odd degrees.

---

# 8. Unique routes produce maximal combinatorial cancellation

Suppose there is exactly one path from $u$ to $v$, of length $L$.

Its $L-1$ internal vertices are the only possible intermediate nodes in $(u,v)$. Every factorization is obtained by choosing a subset of those internal vertices.

Therefore the number of $r$-factor chains is

$$
c_{r,L}=
\binom{L-1}{r-1}.
$$

The total unsigned number of factorizations is

$$
\sum_{r=1}^{L}c_{r,L}=
2^{L-1}.
$$

This saturates the unsigned cut-count bound.

But the signed coefficient is

$$
m_L=
\sum_{r=1}^{L}
(-1)^r
\binom{L-1}{r-1}.
$$

Hence

$$
m_L=
\begin{cases}
-1,&L=1,\\
0,&L\ge2.
\end{cases}
$$

So a unique path of length $L\ge2$ simultaneously has:

* the largest possible number $2^{L-1}$ of cut factorizations for one route;
* complete alternating Möbius cancellation.

In the extremal case:

$$
\text{maximal factorization abundance can coexist with zero Möbius complexity}.
$$

The reason is that every factorization is merely a different placement of cuts along the same route. There is no genuine route ambiguity.

---

# 9. Diamonds break the cancellation

For a symmetric diamond of total cost two,

$$
c_{1,2}=1
$$

for the unfactored arrow, while

$$
c_{2,2}=2
$$

for the two intermediate nodes.

Therefore

$$
m_2=-1+2=1.
$$

The cancellation that would occur for a single route fails because there is one additional independent factorization branch.

For an asymmetric diamond whose second branch appears only at cost three, the cost-two terms cancel, while

$$
m_3=1.
$$

Thus the first nonzero Möbius coefficient identifies the first budget at which route-independent factorization multiplicity survives cancellation.

---

# 10. Equality structure of the spectral growth bound

Recall

$$
|S_+^n|^2=
\sup_uT_n(u).
$$

Thus two systems have the same forward Fock spectral radius whenever their maximal total route counts have the same exponential growth:

$$
r(S_+)=
\lim_{n\to\infty}
\left(\sup_uT_n(u)\right)^{1/(2n)}.
$$

Equality of this spectral radius does **not** require equality of:

* endpoint counts $R_n$;
* reconvergence maxima $M_n$;
* quadratic concentrations $Q_n$;
* shortest distances;
* interval topology;
* Möbius coefficients.

The extremal tree/funnel pair demonstrates that every one of those can differ exponentially while $r(S_+)$ remains identical.

So the correct hierarchy is now:

$$
\begin{aligned}
T_n
&:\text{total route growth},\\
(R_n,M_n,Q_n)
&:\text{endpoint-distribution geometry},\\
d
&:\text{earliest compositional access},\\
m_L
&:\text{signed thin-factorization complexity}.
\end{aligned}
$$

No single one determines all the others.
