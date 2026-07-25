# 1. The outgoing adjacency operator

Define the positive outgoing adjacency operator pointwise by

$$
(\mathcal A_+f)(v)=
\sum_{e:s(e)=v}f(r(e)).
$$

Parallel channels appear separately in the sum.

With the earlier convention

$$
A(w,v)=\#\{e:v\to w\},
$$

this is

$$
(\mathcal A_+f)(v)=
\sum_w A(w,v)f(w).
$$

It need not define a bounded operator on any fixed Banach space. The pointwise formula remains meaningful whenever the indicated sum is finite or otherwise convergent.

---

# 2. The rooted partition resolvent

For a node $v$, define

$$
Z_v(r)=
\sum_{p:s(p)=v}r^{2|p|}.
$$

This is the squared norm of the unnormalized rooted radial vector

$$
\sum_{p:s(p)=v}r^{|p|}\xi_p.
$$

Every path beginning at $v$ is either:

* the identity path $1_v$; or
* an edge $e:v\to w$, followed by a path beginning at $w$.

Therefore

$$
Z_v(r)=
1+r^2\sum_{e:s(e)=v}Z_{r(e)}(r).
$$

Equivalently,

$$
Z(r)=\mathbf 1+r^2\mathcal A_+Z(r).
$$

Formally,

$$
Z(r)=
\left(I-r^2\mathcal A_+\right)^{-1}\mathbf 1=
\sum_{n\ge0}r^{2n}\mathcal A_+^n\mathbf 1.
$$

This is the node-compressed positive resolvent associated with the full path resolvent.

---

# 3. Critical normalization

Fix a root $u$, and suppose

$$
Z_u(r)<\infty
\qquad(0\le r<R)
$$

but

$$
Z_u(r)\longrightarrow\infty
\qquad(r\uparrow R).
$$

Define the normalized ratio function

$$
h_r(v)=
\frac{Z_v(r)}{Z_u(r)}.
$$

Then

$$
h_r(u)=1,
$$

and the resolvent equation becomes

$$
h_r(v)=
\frac1{Z_u(r)}
+
r^2
\sum_{e:s(e)=v}h_r(r(e)).
$$

Thus $h_r$ is not yet harmonic. It has a uniform defect

$$
\varepsilon_r=\frac1{Z_u(r)}.
$$

As $r\uparrow R$,

$$
\varepsilon_r\longrightarrow0.
$$

Suppose, along a subnet or sequence, that

$$
h_r(v)\longrightarrow h(v)
$$

for the relevant nodes.

At a node with finitely many outgoing edges, we may pass directly to the limit:

$$
h(v)=
R^2
\sum_{e:s(e)=v}h(r(e)).
$$

Equivalently,

$$
\mathcal A_+h=R^{-2}h.
$$

If we write

$$
\lambda=R^{-2},
$$

then

$$
\mathcal A_+h=\lambda h.
$$

The critical growth scale has become a positive adjacency eigenvalue.

Positive vectors satisfying adjacency inequalities, with equality at regular vertices and possible defects at sinks or infinite emitters, also arise naturally in graph-operator-algebra treatments of harmonic and boundary weights.

---

## 4. Why ratio limits are locally bounded

Suppose $q:u\to v$ is a fixed path.

Every path beginning at $v$ gives, after prefixing by $q$, a path beginning at $u$. Therefore

$$
Z_u(r)\ge r^{2|q|}Z_v(r).
$$

Hence

$$
h_r(v)\le r^{-2|q|}.
$$

So for each node reachable from $u$, the normalized ratios are bounded on every interval bounded away from $r=0$.

This is why pointwise cluster functions can exist even while the unnormalized partition functions diverge.

---

# 5. The unrestricted infinite-emitter inequality

If $v$ emits infinitely many edges, passing an infinite sum through the limit is not automatic.

For every finite subset

$$
F\subseteq\{e:s(e)=v\},
$$

we have

$$
h_r(v)
\ge
r^2\sum_{e\in F}h_r(r(e)).
$$

Therefore every cluster function satisfies

$$
h(v)
\ge
R^2\sum_{e\in F}h(r(e))
\qquad
\text{for every finite }F.
$$

This is the correct cardinality-independent formulation.

At a finite nonzero emitter, equality holds.

At a sink, a purely harmonic vector must satisfy

$$
h(v)=0.
$$

At an infinite emitter, strict inequality can remain. It represents boundary mass that cannot be assigned to any finite collection of outgoing cylinders.

The same equality/inequality distinction is standard in graph-algebra formulations: equality is imposed at ordinary vertices, while sinks and infinite emitters may carry a positive defect.

---

# 6. Critical cylinder weights

For a finite path

$$
q:u\to v,
$$

the subcritical rooted vector gives the cylinder weight

$$
\mu_{u,r}[q]=
\frac{r^{2|q|}Z_v(r)}{Z_u(r)}.
$$

In terms of $h_r$,

$$
\mu_{u,r}[q]=
r^{2|q|}h_r(v).
$$

At a critical cluster limit,

$$
\mu_{u,\partial}[q]=
R^{2|q|}h(v).
$$

This is normalized because

$$
\mu_{u,\partial}[1_u]=h(u)=1.
$$

At a finite emitter $v=r(q)$,

$$
\begin{aligned}
\sum_{e:s(e)=v}\mu_{u,\partial}[qe]
&=
\sum_eR^{2(|q|+1)}h(r(e))\\
&=
R^{2|q|}
\left(
R^2\sum_eh(r(e))
\right)\\
&=
R^{2|q|}h(v)\\
&=
\mu_{u,\partial}[q].
\end{aligned}
$$

Thus the adjacency eigenvector equation is exactly the cylinder-conservation equation.

For arbitrary directed graphs, the boundary-path space is naturally realized as the spectrum of the graph diagonal, so these consistent cylinder values define boundary-state data.

---

# 7. Derived edge splitting

When $h(v)>0$, define

$$
\pi_h(e\mid v)=
\frac{R^2h(r(e))}{h(v)}.
$$

At a finite emitter satisfying the harmonic equation,

$$
\sum_{e:s(e)=v}\pi_h(e\mid v)=1.
$$

For a path

$$
q=e_n\cdots e_1,
\qquad
u=v_0\to v_1\to\cdots\to v_n,
$$

the factors telescope:

$$
\begin{aligned}
\prod_{i=1}^n
\pi_h(e_i\mid v_{i-1})
&=
\prod_{i=1}^n
\frac{R^2h(v_i)}{h(v_{i-1})}\\
&=
R^{2n}\frac{h(v_n)}{h(u)}.
\end{aligned}
$$

Since $h(u)=1$,

$$
\prod_{i=1}^n
\pi_h(e_i\mid v_{i-1})=
\mu_{u,\partial}[q].
$$

Here $\pi_h(e\mid v)$ is the conditional splitting of a boundary cylinder, derived from the graph, the critical path-length scale, and the boundary state.

---

# 8. The primary object is path-harmonic, not node-harmonic

The node function $h$ does not describe every possible boundary state.

For a general boundary state, define its prefix weight

$$
\Psi(q)=\mu([q]).
$$

At every finite regular emitter,

$$
\Psi(q)=
\sum_{e:s(e)=r(q)}
\Psi(qe).
$$

At an infinite emitter,

$$
\Psi(q)
\ge
\sum_{e\in F}\Psi(qe)
$$

for every finite edge set $F$.

This is a harmonic law on the **prefix tree of actual paths**.

The node eigenvector form occurs only when

$$
\Psi(q)=
R^{2|q|}h(r(q))
$$

for some node function $h$.

Equivalently:

$$
R^{-2|q|}\Psi(q)
\text{ depends only on the endpoint }r(q).
$$

This is a substantial symmetry condition.

---

## Consequences for alternative routes

Suppose

$$
p,q:u\to v.
$$

An endpoint-factorized state must satisfy

$$
\frac{\Psi(p)}{\Psi(q)}=
R^{2(|p|-|q|)}.
$$

Therefore:

### Parallel or equal-length routes

If

$$
|p|=|q|,
$$

then

$$
\Psi(p)=\Psi(q).
$$

The node compression assigns equal cylinder weight to every equal-length route with the same endpoints.

### Shortcut versus composite route

If

$$
|q|=|p|+k,
$$

then

$$
\Psi(q)=R^{2k}\Psi(p).
$$

The longer route receives the fixed length-scaling factor.

A general prefix-harmonic boundary state need not obey either condition.

Hence:

$$
\text{node-harmonic vectors classify only endpoint-factorized boundary states.}
$$

They do not classify arbitrary route-sensitive boundary states.

---

# 9. When node compression loses nothing

If every node reachable from $u$ is reached by at most one path, then the endpoint uniquely determines the prefix.

In that case, given any prefix-harmonic weight $\Psi$ and any fixed $R>0$, we may define

$$
h(v)=
R^{-2|q_v|}\Psi(q_v),
$$

where $q_v$ is the unique path $u\to v$.

Then

$$
\Psi(q_v)=R^{2|q_v|}h(v).
$$

Thus on a rooted tree or any unique-route forward system:

$$
\text{prefix harmonicity}
\quad\text{and}\quad
\text{node harmonicity}
$$

contain equivalent information.

When routes reconverge, this equivalence fails. The node function identifies cylinders that remain distinct in the full path boundary.

This is yet another precise point at which thin compression destroys route information.

---

# 10. Potential–harmonic decomposition

Assume now that outgoing sums are finite, for example in a row-finite graph.

Set

$$
T_R=R^2\mathcal A_+.
$$

Let $h\ge0$ be superharmonic:

$$
h\ge T_Rh.
$$

Define its defect

$$
\varepsilon=h-T_Rh\ge0.
$$

Then

$$
h=\varepsilon+T_Rh.
$$

Iterating $N$ times gives

$$
h
=
\sum_{k=0}^{N-1}T_R^k\varepsilon
+
T_R^Nh.
$$

At a node $v$,

$$
h(v)=
\sum_{k=0}^{N-1}
R^{2k}
\sum_{\substack{p:s(p)=v\\|p|=k}}
\varepsilon(r(p))
+
R^{2N}
\sum_{\substack{p:s(p)=v\\|p|=N}}
h(r(p)).
$$

The two terms have different meanings.

## Potential part

$$
\sum_{k\ge0}T_R^k\varepsilon.
$$

This propagates finite-node defects backward along all paths.

It represents mass terminating at finite or singular boundary points.

## Harmonic remainder

$$
h_\infty=
\lim_{N\to\infty}T_R^Nh,
$$

when the pointwise limit exists.

Because

$$
h\ge T_Rh\ge T_R^2h\ge\cdots,
$$

the limit exists pointwise. Under finite outgoing sums,

$$
T_Rh_\infty=h_\infty.
$$

Therefore

$$
h
=
\sum_{k\ge0}T_R^k\varepsilon
+
h_\infty.
$$

This is the natural potential–boundary decomposition.

---

# 11. The resolvent is the pure potential case

The subcritical partition function satisfies

$$
Z(r)=\mathbf1+T_rZ(r),
\qquad
T_r=r^2\mathcal A_+.
$$

Its defect is exactly

$$
\varepsilon=\mathbf1.
$$

Thus

$$
Z(r)=
\sum_{k\ge0}T_r^k\mathbf1.
$$

It is a pure Green potential generated by the finite identity paths.

After normalization,

$$
h_r=\frac{Z(r)}{Z_u(r)}
$$

has defect

$$
\varepsilon_r=
\frac{\mathbf1}{Z_u(r)}.
$$

At critical divergence,

$$
\varepsilon_r\longrightarrow0.
$$

Therefore the finite-path source disappears and any nonzero limit becomes harmonic:

$$
\text{normalizing a diverging path resolvent removes its potential source and leaves boundary harmonic mass.}
$$

This is the precise resolvent-to-boundary transition.

---

# 12. Harmonic mass and the infinite-future core

Assume the graph is row-finite and $h\ge0$ satisfies

$$
h(v)=
R^2\sum_{e:s(e)=v}h(r(e)).
$$

Suppose $v$ lies in the future-well-founded part of the graph.

At a sink,

$$
h(v)=0.
$$

Now use transfinite induction on the future rank.

If every successor $w$ of $v$ has

$$
h(w)=0,
$$

then

$$
h(v)=
R^2\sum_{v\to w}h(w)=
0.
$$

Therefore:

$$
h(v)=0
\quad
\text{on every future-well-founded node}.
$$

Consequently,

$$
\operatorname{supp}h\subseteq K^+,
$$

where $K^+$ is the infinite-future core obtained by transfinite sink pruning.

This ties the boundary eigenvector directly to the earlier ordinal decomposition.

A nonzero pure harmonic state cannot live on a finite DAG or on a row-finite region whose forward paths all terminate.

---

## Constructive version

If $h(v)>0$ and $v$ has finitely many outgoing edges, then the equality

$$
h(v)=R^2\sum_{v\to w}h(w)
$$

implies that at least one successor $w$ satisfies

$$
h(w)>0.
$$

Repeating this choice produces an infinite path of positive harmonic support, under the usual dependent-choice principle.

Thus in the row-finite case:

$$
h(v)>0
\Longrightarrow
\text{an infinite forward path begins at }v.
$$

At an infinite emitter this implication can fail because positive superharmonic defect may remain at the emitter itself.

---

# 13. Examples

## Infinite chain

Let

$$
v_0\to v_1\to v_2\to\cdots.
$$

The rooted partition function is

$$
Z_{v_n}(r)=\frac1{1-r^2}.
$$

Hence

$$
R=1
$$

and

$$
h(v_n)=1.
$$

The harmonic equation is

$$
h(v_n)=h(v_{n+1}).
$$

The derived cylinder split assigns weight one to the unique continuation.

---

## (d)-ary tree

Every node has $d$ distinct children.

Then

$$
Z_v(r)=\frac1{1-dr^2},
\qquad
R=d^{-1/2}.
$$

Again,

$$
h(v)=1.
$$

The equation becomes

$$
1
=
\frac1d
\sum_{i=1}^d1.
$$

Thus

$$
\pi_h(e\mid v)=\frac1d.
$$

The equal cylinder splitting is derived from the symmetry and path growth; it was not externally assigned.

---

## Spherically varying branching

Suppose every node at depth $n$ has $b_n$ children.

Let $h_n$ be the common value of $h$ at depth $n$. Then

$$
h_n=R^2b_nh_{n+1}.
$$

With $h_0=1$,

$$
h_n=
\frac{R^{-2n}}{b_0b_1\cdots b_{n-1}}.
$$

The cylinder weight of any depth-$n$ path is therefore

$$
R^{2n}h_n=
\frac1{b_0b_1\cdots b_{n-1}}.
$$

The critical scale cancels after normalization, leaving the equal split forced by the branching profile.

---

## A reconvergent diamond followed by an infinite tail

Consider

$$
u\to a\to v\to v_1\to v_2\to\cdots
$$

and

$$
u\to b\to v.
$$

The exponential growth rate is one, so $R=1$.

Normalize $h(u)=1$. Harmonicity gives

$$
h(a)=h(v),
\qquad
h(b)=h(v),
$$

and

$$
h(u)=h(a)+h(b)=2h(v).
$$

Hence

$$
h(v)=h(a)=h(b)=\frac12.
$$

The two route cylinders receive equal weight

$$
\frac12.
$$

But a general route-sensitive prefix state could favor one branch over the other. That asymmetry is precisely what the node eigenvector compression cannot retain.

---

# 14. The convex boundary cone

For fixed $R$, define the endpoint-factorized harmonic cone

$$
\mathscr H_R=
\left\{
h\ge0:
h(v)=R^2\sum_{e:s(e)=v}h(r(e))
\text{ at regular vertices}
\right\},
$$

with finite-subset inequalities at infinite emitters.

After choosing a root $u$, normalize by

$$
h(u)=1.
$$

This gives a convex set of endpoint-factorized boundary states.

Its extreme points represent indecomposable states within this compressed class.

But the full boundary cone is larger:

$$
\mathscr P=
\left\{
\Psi\ge0:
\Psi(q)=\sum_e\Psi(qe)
\text{ on the prefix tree}
\right\}.
$$

The endpoint-factorized cone is the subcone satisfying

$$
\Psi(q)=R^{2|q|}h(r(q)).
$$

Thus:

$$
\mathscr H_R
\subseteq
\mathscr P.
$$

Equality holds in unique-route systems, but generally not in reconvergent systems.
