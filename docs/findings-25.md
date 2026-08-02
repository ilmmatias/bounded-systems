# 1. Canonical concatenation unitary

Let $p:u\to w$ and $q:w\to v$ have lengths $n$ and $m$, respectively.

Their concatenation is

```math
qp:u\to v,
\qquad |qp|=m+n.
```

Define the balanced Hilbert tensor product concretely by

```math
\mathcal H_m\overline\otimes_{\mathcal D}\mathcal H_n=
\bigoplus_{u,w,v}
\mathcal H_m(v,w)
\otimes
\mathcal H_n(w,u),
```

where $\mathcal D$ is the atomic node diagonal.

There is a canonical map

```math
C_{m,n}:
\mathcal H_m\overline\otimes_{\mathcal D}\mathcal H_n
\longrightarrow
\mathcal H_{m+n}
```

defined by

```math
C_{m,n}(\xi_q\otimes\xi_p)=\xi_{qp}.
```

Every length-$(m+n)$ path has a unique cut after its first $n$ edges. Therefore
$C_{m,n}$ is unitary.

Moreover,

```math
C_{\ell+m,n}
\bigl(C_{\ell,m}\otimes I\bigr)=
C_{\ell,m+n}
\bigl(I\otimes C_{m,n}\bigr).
```

The resolved route tower

```math
{\mathcal H_n,C_{m,n}}_{m,n\ge0}
```

is strictly associative.

The tensor is the primary multiplicative object and retains all route
information.

# 2. Cardinal convolution of route multiplicities

Recall

```math
N_n(v,u)=
|\mathsf P_n(u,v)|.
```

Cutting every length-$(m+n)$ path at depth $n$ gives a disjoint union

```math
\mathsf P_{m+n}(u,v)
\cong
\bigsqcup_{w\in V}
\mathsf P_m(w,v)\times\mathsf P_n(u,w).
```

For arbitrary cardinalities,

```math
N_{m+n}(v,u)=
\sum_{w\in V}
N_m(v,w)N_n(w,u),
```

where the right side is cardinal addition and multiplication.

Whenever these are ordinary finite numbers, this is matrix multiplication:

```math
N_{m+n}=N_mN_n.
```

Since $N_1=A$, the primitive-channel multiplicity kernel,

```math
N_n=A^n.
```

The multiplicity tower is determined by the direct-channel kernel, provided
ordinary scalar convolution is defined.

# 3. Endpoint collapse respects concatenation

Define $\mathcal K$ by

```math
\mathcal K=\ell^2(V\times V)
```

with basis $\eta_{v,u}$.

On finite-support route vectors, define

```math
\Sigma_n^0\xi_p=
\eta_{r(p),s(p)}.
```

Also define the algebraic endpoint-composition map

```math
W_{m,n}^0:
\mathcal K\otimes_{\mathcal D}\mathcal K
\longrightarrow
\mathcal K
```

by

```math
W_{m,n}^0
\left(
\eta_{v,w}\otimes\eta_{w,u}
\right)=
\eta_{v,u}.
```

Then the following diagram commutes exactly:

```math
\Sigma_{m+n}^0C_{m,n}=
W_{m,n}^0
\left(
\Sigma_m^0\otimes_{\mathcal D}\Sigma_n^0
\right).
```

On a path pair,

```math
\xi_q\otimes\xi_p
\longmapsto
\eta_{v,w}\otimes\eta_{w,u}
\longmapsto
\eta_{v,u},
```

which is the same result as first concatenating $qp$ and then forgetting its
internal route.

Thus endpoint collapse is compatible with composition algebraically.

In general, it is not an isometry.

# 4. Multiplicity operators under composition

Assume the relevant route fibers are finite, and recall

```math
D_n\eta_{v,u}=
N_n(v,u)\eta_{v,u}.
```

Define a weighted intermediate-node collapse by

```math
\Gamma_{m,n}
\left(
\eta_{v,w}\otimes\eta_{w,u}
\right)=
\sqrt{
N_m(v,w)N_n(w,u)
},\eta_{v,u}.
```

For fixed endpoints $(u,v)$, this is the row functional with coefficients

```math
\sqrt{
N_m(v,w)N_n(w,u)
}.
```

Thus the endpoint action is

```math
\Gamma_{m,n}\Gamma_{m,n}^\ast\eta_{v,u}=
\left(
\sum_wN_m(v,w)N_n(w,u)
\right)\eta_{v,u}.
```

Using the convolution identity,

```math
D_{m+n}=
\Gamma_{m,n}\Gamma_{m,n}^\ast.
```

The length-$(m+n)$ multiplicity is the Gram norm of all possible
intermediate-node factorizations.

# 5. Equal-route vectors do not tensor naively

Fix $u,v$, and suppose all relevant route counts are finite.

For an intermediate node $w$, define

```math
a_w=
N_m(v,w)N_n(w,u).
```

The entry counts length-$(m+n)$ routes from $u$ to $v$ whose depth-$n$ node is
$w$.

Set $N$ by

```math
N=\sum_wa_w=N_{m+n}(v,u).
```

Inside

```math
\mathcal H_m(v,w)\otimes\mathcal H_n(w,u),
```

the normalized equal-route vector is

```math
e_w=
\omega_{v,w}^{(m)}
\otimes
\omega_{w,u}^{(n)}.
```

Under path concatenation, the global equal-route vector is

```math
\omega_{v,u}^{(m+n)}=
C_{m,n}
\left(
\frac1{\sqrt N}
\sum_w
\sqrt{a_w},e_w
\right).
```

The equal-route direction at total depth is a weighted superposition over every
admissible intermediate node.

It is a simple tensor only when exactly one $w$ contributes.

Resolved path spaces multiply strictly, but normalized equal-route sectors
generally do not.

Reconvergence mixes the intermediate sectors.

# 6. Exact decomposition of route defects

Define $B_w$ by

```math
B_w=
\mathcal H_m(v,w)\otimes\mathcal H_n(w,u).
```

Decompose it as

```math
B_w=
\mathbb Ce_w\oplus F_w,
```

where $F_w$ contains all route defects internal to that fixed intermediate node.

More explicitly,

```math
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
```

Here $\mathcal D_j$ denotes the zero-sum route-defect subspace at length $j$,
not the node diagonal.

The full defect space at length $m+n$ decomposes as

```math
\mathcal D_{m+n}(v,u)=
C_{m,n}
\left[
\left(
\bigoplus_wF_w
\right)
\oplus
\mathcal F_{m,n}(v,u)
\right],
```

where

```math
\mathcal F_{m,n}(v,u)=
\left\lbrace \sum_wc_we_w: \sum_wc_w\sqrt{a_w}=0 \right\rbrace.
```

The two parts have different meanings.

## Internal route defects

The internal route-defect space

```math
\bigoplus_wF_w
```

contains ambiguities already present within the two route segments.

## Intermediate-factorization defects

The intermediate-factorization defect space

```math
\mathcal F_{m,n}(v,u)
```

compares different possible cut nodes $w$.

These are new defects created by composition.

# 7. Finite-dimensional count

Define $k_{m,n}(v,u)$ by

```math
k_{m,n}(v,u)=
\left|\{w:a_w>0\}\right|.
```

It follows that

```math
\dim\mathcal D_{m+n}(v,u)=N-1.
```

The internal part has dimension

```math
\sum_w(a_w-1)=N-k_{m,n}(v,u),
```

while the factorization-defect part has dimension

```math
k_{m,n}(v,u)-1.
```

Equivalently,

```math
N-1=
\bigl(N-k_{m,n}\bigr)
+
\bigl(k_{m,n}-1\bigr).
```

Thus total route ambiguity splits into ambiguity within intermediate sectors
and ambiguity between intermediate sectors.

For a diamond, there are two intermediate nodes, each supporting one route pair:

```math
N=2,\qquad k=2.
```

The internal defect dimension is zero, while the factorization defect dimension
is one.

The kernel vector is the diamond relation.

# 8. Kernel propagation and its strict failure

The commutative composition diagram implies

```math
C_{m,n}
\left(
\ker\Sigma_m\otimes\mathcal H_n
+
\mathcal H_m\otimes\ker\Sigma_n
\right)
\subseteq
\ker\Sigma_{m+n}.
```

Route defects propagate under prefixing and suffixing.

But the inclusion may be strict.

The additional quotient consists exactly of factorization defects arising from
multiple intermediate nodes.

Schematically,

```math
\frac{
\ker\Sigma_{m+n}
}{
\text{defects inherited from lengths }m\text{ and }n
}
\cong
\text{intermediate-node defect space}.
```

The operator identity separates:

* route ambiguity internal to factors;
* coherence ambiguity among different factorizations.

# 9. Connection to interval topology

For fixed $m,n,u,v$, define

```math
W_{m,n}(v,u)=
\left\lbrace w: N_n(w,u)>0,\; N_m(v,w)>0 \right\rbrace.
```

The set contains the nodes through which a length-$(m+n)$ path can pass at the
prescribed cut.

The factorization defect is the weighted reduced space on this set:

```math
\mathcal F_{m,n}(v,u)=
\left\lbrace (c_w): \sum_wc_w\sqrt{a_w}=0 \right\rbrace.
```

When the set is finite and nonempty,

```math
\dim\mathcal F_{m,n}(v,u)=
|W_{m,n}(v,u)|-1.
```

The dimension equals

```math
\widetilde H_0
\left(
W_{m,n}(v,u)
\right)
```

when the admissible intermediate nodes are viewed as a discrete complex.

The first factorization-defect layer is exactly the degree-zero shadow of the
interval complexes derived earlier.

Iterated cuts produce chains of intermediate nodes that assemble into the full
order complex

```math
\Delta(u,v).
```

The operator decomposition and the interval-topology construction meet as
follows:

```math
\text{one cut}
\longrightarrow
\widetilde H_0,
```

and

```math
\text{many compatible cuts}
\longrightarrow
\widetilde H_*(\Delta(u,v)).
```

# 10. A new infinite singularity created by composition

Suppose every lower-level endpoint fiber is finite but infinitely many
intermediate nodes contribute.

Consider

```math
u\to w_i\to v
\qquad(i\in I),
```

with $I$ infinite and exactly one edge in each segment.

At length one,

```math
N_1(w_i,u)=1,
\qquad
N_1(v,w_i)=1.
```

Every length-one endpoint fiber has size at most one:

```math
|\Sigma_1|=1.
```

But at length two,

```math
N_2(v,u)=|I|,
```

which is infinite.

```math
\Sigma_2^0
```

is nonclosable.

```math
\text{bounded endpoint collapse at lengths }m\text{ and }n
```

does not imply

```math
\text{closable endpoint collapse at length }m+n.
```

The singularity can arise entirely from infinitely many distinct intermediate
factorizations.

There are therefore two independent causes of analytic collapse failure:

1. infinitely many routes inside one fixed intermediate sector;
2. infinitely many intermediate sectors reconverging onto the same endpoint
   pair.

The second cannot be detected from $\Sigma_m$ and $\Sigma_n$ separately.

# 11. Support tower and Boolean composition

Define the Boolean support kernel by

```math
Z_n(v,u)=
\begin{cases}
1,&N_n(v,u)>0,\\
0,&N_n(v,u)=0.
\end{cases}
```

It follows that

```math
Z_{m+n}(v,u)=
\bigvee_w
\left(
Z_m(v,w)\wedge Z_n(w,u)
\right).
```

The exact-length support tower multiplies over the Boolean semiring:

```math
Z_{m+n}=Z_m\odot Z_n.
```

The shortest compositional distance is

```math
d(u,v)=\min{n:Z_n(v,u)=1}.
```

The composition laws of the successive layers are:

```math
\begin{array}{c|c}
\text{Layer}&\text{Composition law}\\
\hline
\text{resolved routes}&\text{Hilbert tensor product and concatenation}\\
\text{multiplicities}&\text{ordinary/cardinal matrix multiplication}\\
\text{support}&\text{Boolean matrix multiplication}\\
\text{shortest distance}&\text{min-plus multiplication}
\end{array}
```

Each layer changes the meaning of addition while preserving compositional
multiplication.

# 12. Geodesic multiplicity under cutting

Set $d$ by

```math
d=d(u,v)
```

and let

```math
g(v,u)=N_d(v,u)
```

be the number of geodesic routes.

For every cut depth

```math
0\le n\le d,
```

every geodesic path has a unique node $w$ after $n$ edges. Its prefix and suffix
must themselves be geodesic; otherwise the full route could be shortened.

```math
g(v,u)=
\sum_{\substack{
w:\\
d(u,w)=n\\
d(w,v)=d-n
}}
g(w,u)g(v,w).
```

The leading-coefficient law complements the min-plus distance equation.

Tropicalization can therefore be refined from

```math
d(u,v)
```

to the pair

```math
\bigl(d(u,v),g(v,u)\bigr),
```

with min-plus composition for distances and ordinary addition and multiplication
for geodesic multiplicities along minimizing intermediates.

# 13. Propagation of total branching

Define $T_n(u)$ by

```math
T_n(u)=\sum_vN_n(v,u).
```

It follows that

```math
\begin{aligned}
T_{m+n}(u)
&=
\sum_v\sum_w
N_m(v,w)N_n(w,u)\\
&=
\sum_w
N_n(w,u)T_m(w).
\end{aligned}
```

Summing first over the terminal endpoint gives

```math
T_{m+n}(u)=
\sum_wN_n(w,u)T_m(w).
```

Taking suprema gives

```math
T_{m+n}^+
\le
T_m^+T_n^+.
```

Since

```math
T_n^+=|S_+^n|^2,
```

this recovers operator submultiplicativity:

```math
|S_+^{m+n}|
\le
|S_+^m||S_+^n|.
```

For maximum endpoint multiplicity,

```math
M_n=\sup_{u,v}N_n(v,u),
```

Thus,

```math
M_{m+n}
\le
M_mT_n^+,
```

and dually,

```math
M_{m+n}
\le
M_nT_m^-.
```

When the operators are bounded,

```math
|\Sigma_{m+n}|
\le
\min\left\lbrace |\Sigma_m|,|S_+^n|,|\Sigma_n|,|S_-^m| \right\rbrace.
```

The normalization separates forward branching from backward reconvergence.
