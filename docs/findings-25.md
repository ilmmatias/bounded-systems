# 1. Canonical concatenation unitary

Let

$$
p:u\to w,\qquad |p|=n,
$$

and

$$
q:w\to v,\qquad |q|=m.
$$

Their concatenation is

$$
qp:u\to v,
\qquad |qp|=m+n.
$$

Define the balanced Hilbert tensor product concretely by

$$
\mathcal H_m\overline\otimes_{\mathcal D}\mathcal H_n=
\bigoplus_{u,w,v}
\mathcal H_m(v,w)
\otimes
\mathcal H_n(w,u),
$$

where $\mathcal D$ is the atomic node diagonal.

There is a canonical map

$$
C_{m,n}:
\mathcal H_m\overline\otimes_{\mathcal D}\mathcal H_n
\longrightarrow
\mathcal H_{m+n}
$$

defined by

$$
C_{m,n}(\xi_q\otimes\xi_p)=\xi_{qp}.
$$

Every length-$(m+n)$ path has a unique cut after its first $n$ edges. Therefore $C_{m,n}$ is unitary.

Moreover,

$$
C_{\ell+m,n}
\bigl(C_{\ell,m}\otimes I\bigr)=
C_{\ell,m+n}
\bigl(I\otimes C_{m,n}\bigr).
$$

Thus the resolved route tower

$$
{\mathcal H_n,C_{m,n}}_{m,n\ge0}
$$

is strictly associative.

This is the fundamental multiplicative object. No route information has yet been discarded.

---

# 2. Cardinal convolution of route multiplicities

Recall

$$
N_n(v,u)=
|\mathsf P_n(u,v)|.
$$

Cutting every length-$(m+n)$ path at depth $n$ gives a disjoint union

$$
\mathsf P_{m+n}(u,v)
\cong
\bigsqcup_{w\in V}
\mathsf P_m(w,v)\times\mathsf P_n(u,w).
$$

Hence, for arbitrary cardinalities,

$$
N_{m+n}(v,u)=
\sum_{w\in V}
N_m(v,w)N_n(w,u),
$$

where the right side is cardinal addition and multiplication.

Whenever these are ordinary finite numbers, this is simply matrix multiplication:

$$
N_{m+n}=N_mN_n.
$$

Since $N_1=A$, the primitive-channel multiplicity kernel,

$$
N_n=A^n.
$$

So the whole multiplicity tower is already determined by the direct-channel kernel, provided ordinary scalar convolution is defined.

---

# 3. Endpoint collapse respects concatenation

Let

$$
\mathcal K=\ell^2(V\times V)
$$

with basis $\eta_{v,u}$.

On finite-support route vectors, define

$$
\Sigma_n^0\xi_p=
\eta_{r(p),s(p)}.
$$

Also define the algebraic endpoint-composition map

$$
W_{m,n}^0:
\mathcal K\otimes_{\mathcal D}\mathcal K
\longrightarrow
\mathcal K
$$

by

$$
W_{m,n}^0
\left(
\eta_{v,w}\otimes\eta_{w,u}
\right)=
\eta_{v,u}.
$$

Then the following diagram commutes exactly:

$$
\Sigma_{m+n}^0C_{m,n}=
W_{m,n}^0
\left(
\Sigma_m^0\otimes_{\mathcal D}\Sigma_n^0
\right).
$$

On a path pair,

$$
\xi_q\otimes\xi_p
\longmapsto
\eta_{v,w}\otimes\eta_{w,u}
\longmapsto
\eta_{v,u},
$$

which is the same result as first concatenating $qp$ and then forgetting its internal route.

Thus endpoint collapse is compatible with composition algebraically.

In general, it is not an isometry.

---

# 4. Multiplicity operators under composition

Assume the relevant route fibers are finite, and recall

$$
D_n\eta_{v,u}=
N_n(v,u)\eta_{v,u}.
$$

Define a weighted intermediate-node collapse by

$$
\Gamma_{m,n}
\left(
\eta_{v,w}\otimes\eta_{w,u}
\right)=
\sqrt{
N_m(v,w)N_n(w,u)
},\eta_{v,u}.
$$

For fixed endpoints $(u,v)$, this is the row functional with coefficients

$$
\sqrt{
N_m(v,w)N_n(w,u)
}.
$$

Therefore

$$
\Gamma_{m,n}\Gamma_{m,n}^\ast\eta_{v,u}=
\left(
\sum_wN_m(v,w)N_n(w,u)
\right)\eta_{v,u}.
$$

Using the convolution identity,

$$
D_{m+n}=
\Gamma_{m,n}\Gamma_{m,n}^\ast.
$$

So the length-$(m+n)$ multiplicity is the Gram norm of all possible intermediate-node factorizations.

---

# 5. Equal-route vectors do not tensor naively

Fix $u,v$, and suppose all relevant route counts are finite.

For an intermediate node $w$, define

$$
a_w=
N_m(v,w)N_n(w,u).
$$

This is the number of length-$(m+n)$ routes from $u$ to $v$ whose depth-$n$ node is $w$.

Let

$$
N=\sum_wa_w=N_{m+n}(v,u).
$$

Inside

$$
\mathcal H_m(v,w)\otimes\mathcal H_n(w,u),
$$

the normalized equal-route vector is

$$
e_w=
\omega_{v,w}^{(m)}
\otimes
\omega_{w,u}^{(n)}.
$$

Under path concatenation, the global equal-route vector is

$$
\omega_{v,u}^{(m+n)}=
C_{m,n}
\left(
\frac1{\sqrt N}
\sum_w
\sqrt{a_w},e_w
\right).
$$

So the equal-route direction at total depth is a weighted superposition over every admissible intermediate node.

It is a simple tensor only when exactly one $w$ contributes.

Therefore:

$$
\text{resolved path spaces multiply strictly,}
$$

but

$$
\text{normalized equal-route sectors generally do not.}
$$

Reconvergence mixes the intermediate sectors.

---

# 6. Exact decomposition of route defects

Let

$$
B_w=
\mathcal H_m(v,w)\otimes\mathcal H_n(w,u).
$$

Decompose it as

$$
B_w=
\mathbb Ce_w\oplus F_w,
$$

where $F_w$ contains all route defects internal to that fixed intermediate node.

More explicitly,

$$
\begin{aligned}
F_w
={}&
\left(
\mathbb C\omega_{v,w}^{(m)}
\otimes
\mathcal D_n(w,u)
\right)
\\
&\oplus
\left(
\mathcal D_m(v,w)
\otimes
\mathbb C\omega_{w,u}^{(n)}
\right)
\\
&\oplus
\left(
\mathcal D_m(v,w)
\otimes
\mathcal D_n(w,u)
\right).
\end{aligned}
$$

Here $\mathcal D_j$ denotes the zero-sum route-defect subspace at length $j$, not the node diagonal.

The full defect space at length $m+n$ decomposes as

$$
\mathcal D_{m+n}(v,u)=
C_{m,n}
\left[
\left(
\bigoplus_wF_w
\right)
\oplus
\mathcal F_{m,n}(v,u)
\right],
$$

where

$$
\mathcal F_{m,n}(v,u)=
\left\{
\sum_wc_we_w:
\sum_wc_w\sqrt{a_w}=0
\right\}.
$$

The two parts have different meanings.

### Internal route defects

$$
\bigoplus_wF_w
$$

contains ambiguities already present within the two route segments.

### Intermediate-factorization defects

$$
\mathcal F_{m,n}(v,u)
$$

compares different possible cut nodes $w$.

These are new defects created by composition.

---

# 7. Finite-dimensional count

Let

$$
k_{m,n}(v,u)=
\#\{w:a_w>0\}.
$$

Then:

$$
\dim\mathcal D_{m+n}(v,u)=N-1.
$$

The internal part has dimension

$$
\sum_w(a_w-1)=N-k_{m,n}(v,u),
$$

while the factorization-defect part has dimension

$$
k_{m,n}(v,u)-1.
$$

Therefore

$$
N-1=
\bigl(N-k_{m,n}\bigr)
+
\bigl(k_{m,n}-1\bigr).
$$

In words:

$$
\text{total route ambiguity}=
\text{ambiguity within intermediate sectors}
+
\text{ambiguity between intermediate sectors}.
$$

For a diamond, there are two intermediate nodes, each supporting one route pair:

$$
N=2,\qquad k=2.
$$

The internal defect dimension is zero, while the factorization defect dimension is one.

This is the diamond relation.

---

# 8. Kernel propagation and its strict failure

The commutative composition diagram implies

$$
C_{m,n}
\left(
\ker\Sigma_m\otimes\mathcal H_n
+
\mathcal H_m\otimes\ker\Sigma_n
\right)
\subseteq
\ker\Sigma_{m+n}.
$$

So route defects propagate under prefixing and suffixing.

But the inclusion may be strict.

The additional quotient consists exactly of factorization defects arising from multiple intermediate nodes.

Schematically,

$$
\frac{
\ker\Sigma_{m+n}
}{
\text{defects inherited from lengths }m\text{ and }n
}
\cong
\text{intermediate-node defect space}.
$$

This is the operator version of the distinction between:

* route ambiguity internal to factors;
* coherence ambiguity among different factorizations.

---

# 9. Connection to interval topology

For fixed $m,n,u,v$, define

$$
W_{m,n}(v,u)=
\left\{
w:
N_n(w,u)>0,;
N_m(v,w)>0
\right\}.
$$

This is the set of nodes through which a length-$(m+n)$ path can pass at the prescribed cut.

The factorization defect is the weighted reduced space on this set:

$$
\mathcal F_{m,n}(v,u)=
\left\{
(c_w):
\sum_wc_w\sqrt{a_w}=0
\right\}.
$$

When the set is finite and nonempty,

$$
\dim\mathcal F_{m,n}(v,u)=
|W_{m,n}(v,u)|-1.
$$

This is the same dimension as

$$
\widetilde H_0
\left(
W_{m,n}(v,u)
\right)
$$

when the admissible intermediate nodes are viewed as a discrete complex.

Thus the first factorization-defect layer is exactly the degree-zero shadow of the interval complexes derived earlier.

Iterating cuts produces chains of intermediate nodes, and those chains assemble into the full order complex

$$
\Delta(u,v).
$$

So the operator decomposition and the interval-topology construction meet naturally:

$$
\text{one cut}
\longrightarrow
\widetilde H_0,
$$

$$
\text{many compatible cuts}
\longrightarrow
\widetilde H_*(\Delta(u,v)).
$$

---

# 10. A new infinite singularity created by composition

Suppose every lower-level endpoint fiber is finite but infinitely many intermediate nodes contribute.

Consider

$$
u\to w_i\to v
\qquad(i\in I),
$$

with $I$ infinite and exactly one edge in each segment.

At length one,

$$
N_1(w_i,u)=1,
\qquad
N_1(v,w_i)=1.
$$

Therefore every length-one endpoint fiber has size at most one:

$$
|\Sigma_1|=1.
$$

But at length two,

$$
N_2(v,u)=|I|,
$$

which is infinite.

Hence

$$
\Sigma_2^0
$$

is nonclosable.

So:

$$
\text{bounded endpoint collapse at lengths }m\text{ and }n
$$

does not imply

$$
\text{closable endpoint collapse at length }m+n.
$$

The singularity can arise entirely from infinitely many distinct intermediate factorizations.

There are therefore two independent causes of analytic collapse failure:

1. infinitely many routes inside one fixed intermediate sector;
2. infinitely many intermediate sectors reconverging onto the same endpoint pair.

The second cannot be detected from $\Sigma_m$ and $\Sigma_n$ separately.

---

# 11. Support tower and Boolean composition

Define

$$
Z_n(v,u)=
\begin{cases}
1,&N_n(v,u)>0,\\
0,&N_n(v,u)=0.
\end{cases}
$$

Then

$$
Z_{m+n}(v,u)=
\bigvee_w
\left(
Z_m(v,w)\wedge Z_n(w,u)
\right).
$$

Thus the exact-length support tower multiplies over the Boolean semiring:

$$
Z_{m+n}=Z_m\odot Z_n.
$$

The shortest compositional distance is

$$
d(u,v)=\min{n:Z_n(v,u)=1}.
$$

This demonstrates the three multiplicative laws directly:

$$
\begin{array}{c|c}
\text{Layer}&\text{Composition law}\\
\hline
\text{resolved routes}&\text{Hilbert tensor product and concatenation}\\
\text{multiplicities}&\text{ordinary/cardinal matrix multiplication}\\
\text{support}&\text{Boolean matrix multiplication}\\
\text{shortest distance}&\text{min-plus multiplication}
\end{array}
$$

Each layer changes the meaning of addition while preserving compositional multiplication.

---

# 12. Geodesic multiplicity under cutting

Let

$$
d=d(u,v)
$$

and let

$$
g(v,u)=N_d(v,u)
$$

be the number of geodesic routes.

For every cut depth

$$
0\le n\le d,
$$

every geodesic path has a unique node $w$ after $n$ edges. Its prefix and suffix must themselves be geodesic; otherwise the full route could be shortened.

Therefore

$$
g(v,u)=
\sum_{\substack{
w:\\
d(u,w)=n\\
d(w,v)=d-n
}}
g(w,u)g(v,w).
$$

This is the leading-coefficient companion to the min-plus distance equation.

So tropicalization can be refined from merely

$$
d(u,v)
$$

to the pair

$$
\bigl(d(u,v),g(v,u)\bigr),
$$

with:

* min-plus composition for distances;
* ordinary addition and multiplication for geodesic multiplicities along minimizing intermediates.

---

# 13. Propagation of total branching

Let

$$
T_n(u)=\sum_vN_n(v,u).
$$

Then

$$
\begin{aligned}
T_{m+n}(u)
&=
\sum_v\sum_w
N_m(v,w)N_n(w,u)\\
&=
\sum_w
N_n(w,u)T_m(w).
\end{aligned}
$$

Hence

$$
T_{m+n}(u)=
\sum_wN_n(w,u)T_m(w).
$$

Taking suprema gives

$$
T_{m+n}^+
\le
T_m^+T_n^+.
$$

Since

$$
T_n^+=|S_+^n|^2,
$$

this recovers operator submultiplicativity:

$$
|S_+^{m+n}|
\le
|S_+^m||S_+^n|.
$$

For maximum endpoint multiplicity,

$$
M_n=\sup_{u,v}N_n(v,u),
$$

we have

$$
M_{m+n}
\le
M_mT_n^+,
$$

and dually,

$$
M_{m+n}
\le
M_nT_m^-.
$$

Thus, when the operators are bounded,

$$
|\Sigma_{m+n}|
\le
\min\left\{
|\Sigma_m|,|S_+^n|,
;
|\Sigma_n|,|S_-^m|
\right\}.
$$

This separates propagation caused by forward branching from propagation caused by backward reconvergence.

---

# 14. The tower is multiplicative only before normalization

The two towers differ after normalization.

## Resolved tower

$$
\mathcal H_m\overline\otimes_{\mathcal D}\mathcal H_n
\cong
\mathcal H_{m+n}
$$

unitarily and associatively.

## Multiplicity tower

$$
N_{m+n}=N_mN_n
$$

by convolution.

## Support tower

$$
Z_{m+n}=Z_m\odot Z_n
$$

over the Boolean semiring.

## Equal-route sectors

The normalized equal-route direction at depth $m+n$ is a weighted sum over intermediate nodes. It is not generally the tensor product of the normalized lower-depth equal-route directions.

The obstruction is exactly reconvergence through multiple intermediate sectors.

So:

$$
\text{path composition is strictly multiplicative;}
$$

$$
\text{normalized thin collapse is only multiplicative after weighted summation over factorizations.}
$$
