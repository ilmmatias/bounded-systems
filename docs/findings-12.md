## 1. Endpoint decomposition

For $u\le v$, let

$$
\mathscr P(u,v)
$$

be the set of all finite paths from $u$ to $v$. Its path-space corner is

$$
A_{v,u}=
e_vAe_u=
\mathbb K^{(\mathscr P(u,v))}.
$$

Define the endpoint summation map

$$
\varepsilon_{v,u}:A_{v,u}\to\mathbb K
$$

by

$$
\varepsilon_{v,u}
\left(
\sum_{p:u\to v}c_pp
\right)=
\sum_{p:u\to v}c_p.
$$

Then

$$
I_{v,u}=
e_vIe_u=
\ker\varepsilon_{v,u}.
$$

Therefore

$$
I=
\bigoplus_{u<v}I_{v,u}.
$$

Every element of $I_{v,u}$ is a finite linear combination of routes from $u$ to $v$ whose coefficients sum to zero.

In particular, it is spanned by differences

$$
p-q
$$

of paths with the same endpoints.

---

# 2. Same-length versus cross-length ambiguity

Let

$$
\mathscr P_n(u,v)=
\{p:u\to v,\ |p|=n\}
$$

and

$$
A^n_{v,u}=
\mathbb K^{(\mathscr P_n(u,v))}.
$$

Then

$$
A_{v,u}=
\bigoplus_{n\ge0}A^n_{v,u}.
$$

For each attained length $n$, define

$$
\varepsilon^n_{v,u}:A^n_{v,u}\to\mathbb K
$$

by coefficient summation.

The **same-length defect space** is

$$
I^{\mathrm{same}}_{v,u}=
\bigoplus_n
\ker\varepsilon^n_{v,u}.
$$

It contains differences

$$
p-q
$$

where $p$ and $q$ have the same endpoints and the same length.

Let

$$
L(u,v)=
\{n:\mathscr P_n(u,v)\ne\varnothing\}
$$

be the set of attained route lengths. Define its reduced finite-support coefficient space

$$
\widetilde{\mathbb K}^{(L(u,v))}=
\left\{
(a_n)_{n\in L(u,v)}:
a_n=0\text{ except finitely often},
\quad
\sum_na_n=0
\right\}.
$$

There is a canonical exact sequence

$$
0
\longrightarrow
I^{\mathrm{same}}_{v,u}
\longrightarrow
I_{v,u}
\longrightarrow
\widetilde{\mathbb K}^{(L(u,v))}
\longrightarrow
0.
$$

The last map sends a route combination to the total coefficient contributed by each length.

Thus the endpoint defect has two distinct parts.

### Same-length ambiguity

Several routes have equal compositional depth:

$$
p,q:u\to v,
\qquad
|p|=|q|.
$$

Parallel primitive channels occur here at length one.

Branching followed by reconvergence occurs here at greater lengths.

### Length disagreement

Routes with the same endpoints have different compositional depths:

$$
|p|\ne |q|.
$$

The most basic example is a shortcut:

$$
u\to v
$$

alongside

$$
u\to w\to v.
$$

Their difference belongs to the cross-length part.

There is generally no canonical splitting of the exact sequence: choosing one representative path for each length would be arbitrary.

---

# 3. The orthogonal meaning of the route kernel

The Fock representation makes the route kernel geometrically explicit.

For a fixed endpoint pair, the path creators

$$
{L_p:p\in\mathscr P(u,v)}
$$

have mutually orthogonal ranges.

Indeed, for distinct paths $p,q$ with the same source and target,

$$
L_p^\ast L_q=0.
$$

Distinct same-endpoint paths cannot be prefix extensions of one another, because that would leave a positive path from $v$ back to $v$, contradicting A5.

Therefore, for

$$
x=\sum_{p:u\to v}c_pL_p,
$$

we obtain

$$
x^\ast x=
\left(
\sum_p|c_p|^2
\right)P_u
$$

and hence

$$
\left|
\sum_pc_pL_p
\right|=
\left(\sum_p|c_p|^2\right)^{1/2}.
$$

So each route corner carries the canonical coefficient Hilbert space

$$
\ell^2(\mathscr P(u,v)).
$$

## Finitely many routes

Suppose there are exactly $m$ routes $p_1,\ldots,p_m$. Define

$$
\omega_{v,u}=
\frac1{\sqrt m}
\sum_{j=1}^mL_{p_j}.
$$

Then

$$
\operatorname{span}\{L_{p_1},\ldots,L_{p_m}\}=
\mathbb K\omega_{v,u}
\oplus
\overline{I_{v,u}},
$$

orthogonally, where

$$
\overline{I_{v,u}}=
\left\{
\sum_jc_jL_{p_j}:
\sum_jc_j=0
\right\}.
$$

Thus:

$$
\text{reachability direction}
\perp
\text{route-defect directions}.
$$

The reachability quotient retains the one-dimensional equal-route direction and discards the $m-1$ orthogonal distinctions.

This is a direct realization of the orthogonality constraint you emphasized.

---

# 4. A major infinite-route phenomenon

Now suppose that infinitely many distinct routes connect $u$ to $v$.

The algebraic summation map still exists on finite-support combinations. But it has no bounded extension to

$$
\ell^2(\mathscr P(u,v)).
$$

To see this, select $N$ distinct routes and take coefficients $1/\sqrt N$. Their coefficient norm is one, but their sum is

$$
\sqrt N.
$$

So the summation functional is unbounded.

There is an even stronger fact.

## Theorem: infinite route defects are norm dense

If $\mathscr P(u,v)$ is infinite, then

$$
\overline{I_{v,u}}^{|\cdot|}=
\overline\{\operatorname{span}\}
{L_p:p\in\mathscr P(u,v)}.
$$

### Proof

Fix one path $p$, and choose distinct alternative routes

$$
q_1,\ldots,q_N.
$$

Define

$$
r_N=
L_p-\frac1N\sum_{j=1}^NL_{q_j}.
$$

Its coefficients sum to zero, so

$$
r_N\in I_{v,u}.
$$

But

$$
|r_N-L_p|=
\left|
\frac1N\sum_{j=1}^NL_{q_j}
\right|=
\frac1{\sqrt N}
\longrightarrow0.
$$

Hence $L_p$ lies in the norm closure of the route-defect space. Since $p$ was arbitrary, the entire route corner lies in that closure.

## Consequence

For infinitely many routes, there is no surviving one-dimensional “equal-route direction” inside the Fock Hilbert geometry.

Instead,

$$
\text{the algebraic reachability quotient becomes analytically singular}.
$$

If we quotient the norm-closed Fock algebra by the norm closure of $I$, the whole infinite-route corner is killed—not collapsed to one nonzero reachability arrow.

This gives a precise reason that the operations

$$
\text{collapse routes}
\qquad\text{and}\qquad
\text{take Fock norm closure}
$$

do not commute.

It is one of the strongest genuinely infinite conclusions obtained so far.

---

# 5. Locally irreducible route defects

Some route relations are merely larger contexts surrounding a smaller ambiguity.

Suppose

$$
r=p-q\in I
$$

is a route defect from $u$ to $v$, and let $a,b$ be positive paths composable on the left and right. Then

$$
arb
$$

is the same ambiguity with extra path context attached.

Such extended relations lie in

$$
JI+IJ,
$$

where $J$ is the positive-path ideal.

Define the **indecomposable route-relation module**

$$
\mathcal R=
I/(JI+IJ).
$$

Since positive paths act trivially on this quotient, $\mathcal R$ is naturally a bimodule over the node diagonal $\mathcal D=A/J$.

Its corner

$$
e_v\mathcal Re_u
$$

records route ambiguity from $u$ to $v$ that cannot be expressed as a smaller ambiguity merely prefixed or suffixed by additional paths.

## Examples

### Parallel channels

For

$$
a,b:u\to v,
$$

the difference

$$
a-b
$$

survives in $\mathcal R$.

### Basic diamond

Suppose

$$
u\to x\to v
$$

and

$$
u\to y\to v.
$$

Let the two composite routes be $p$ and $q$. Then

$$
p-q
$$

survives in $\mathcal R$, provided there is no smaller route ambiguity inside either branch.

### Extended diamond

If $c$ precedes the diamond and $d$ follows it, then

$$
d(p-q)c
$$

vanishes in $\mathcal R$. It contains no new local route ambiguity; it is the original diamond transported into a longer context.

### Shortcut relation

If there is a primitive edge $e:u\to v$ and a composite path $p:u\to v$, then

$$
e-p
$$

is an indecomposable cross-length relation unless it is generated by smaller route defects.

Thus

$$
\mathcal R
$$

locates the elementary branching/reconvergence or shortcut structures from which larger route discrepancies are built.

---

# 6. The route-ambiguity filtration

The ideal powers

$$
I\supseteq I^2\supseteq I^3\supseteq\cdots
$$

give another canonical hierarchy.

An element of $I^m$ is a sum of products of $m$ composable route defects.

Since

$$
I\subseteq J,
$$

we have

$$
I^m\subseteq J^m.
$$

Consequently:

* $I$ is locally nilpotent;
* every algebraic route defect is nilpotent;
* and
$$
  \bigcap_{m\ge1}I^m=0.
$$

The last assertion follows because a nonzero path polynomial has bounded path lengths, while every element of $I^m$ is supported on paths of length at least $m$.

Define the associated graded route algebra

$$
\operatorname{gr}_I(A)=
B
\oplus
I/I^2
\oplus
I^2/I^3
\oplus\cdots.
$$

This measures route sensitivity by the number of independent ambiguity factors.

---

# 7. First-order route ambiguity

Set

$$
\mathcal N=I/I^2.
$$

Unlike $\mathcal R$, this is naturally a bimodule over

$$
B=A/I.
$$

It retains route defects to first order, while setting products of two defects to zero.

The two quotients differ:

$$
\mathcal R=I/(JI+IJ)
$$

removes ordinary path context, while

$$
\mathcal N=I/I^2
$$

removes products of independent route ambiguities.

An extended diamond relation may vanish in $\mathcal R$ but remain nonzero in $\mathcal N$, because attaching ordinary paths is not the same as multiplying by another route defect.

Thus:

$$
\begin{aligned}
\mathcal R &: \text{local generators of ambiguity},\\
\mathcal N &: \text{first-order ambiguity relative to reachability}.
\end{aligned}
$$

---

# 8. Higher ambiguity and the syzygy algebra

Multiplication gives, for every $m\ge1$, a canonical surjection

$$
\mu_m:
\mathcal N^{\otimes_Bm}
\longrightarrow
I^m/I^{m+1}
$$

defined by

$$
[r_m]\otimes\cdots\otimes[r_1]
\longmapsto
[r_m\cdots r_1].
$$

For infinite node sets, this can be understood corner by corner using finite sums of node idempotents; no global algebraic identity is required.

The maps combine into a graded surjection

$$
\Psi:
T_B(\mathcal N)
\longrightarrow
\operatorname{gr}_I(A),
$$

where

$$
T_B(\mathcal N)=
B
\oplus\mathcal N
\oplus
\mathcal N^{\otimes_B2}
\oplus\cdots.
$$

Define the **route-syzygy ideal**

$$
\mathfrak S=\ker\Psi.
$$

Its degree-$m$ part

$$
\mathfrak S_m
$$

consists of identities among formal products of $m$ first-order route defects.

So we obtain three layers:

$$
\begin{aligned}
\mathcal N
&=I/I^2
&&\text{first-order route ambiguity},\\
I^m/I^{m+1}
&&&\text{actual }m\text{-fold ambiguity},\\
\mathfrak S_m
&&&\text{relations among }m\text{-fold ambiguity factorizations}.
\end{aligned}
$$

This is the systematic route-syzygy structure we were seeking.

---

# 9. Two consecutive diamonds

Consider two composable ambiguous sectors.

The first has routes

$$
p_0,p_1:u\to w,
$$

giving

$$
r_1=p_1-p_0.
$$

The second has routes

$$
q_0,q_1:w\to v,
$$

giving

$$
r_2=q_1-q_0.
$$

Their product is

$$
r_2r_1=
q_1p_1-q_1p_0-q_0p_1+q_0p_0.
$$

This is a second-order route defect:

$$
r_2r_1\in I^2.
$$

It compares the four routes obtained by independently choosing one branch in each diamond.

The alternating signs arise from multiplying the two differences.

If these are the only two composable ambiguity sectors, then

$$
I^3=0,
$$

and the class

$$
[r_2r_1]\in I^2/I^3
$$

is nonzero.

Thus higher powers of $I$ encode interaction among branching decisions:

$$
\text{one diamond}
\to I/I^2,
\qquad
\text{two composable diamonds}
\to I^2/I^3,
\quad\ldots
$$

A degree-two syzygy appears when two different tensors in

$$
\mathcal N\otimes_B\mathcal N
$$

produce the same second-order defect. Their difference lies in

$$
\mathfrak S_2.
$$

---

# 10. Joint path-depth and ambiguity filtration

The positive-path filtration and route-defect filtration measure different things:

* $J^n$: minimum compositional depth;
* $I^m$: minimum number of route-ambiguity factors.

Combine them through

$$
F^{m,n}=
I^m\cap J^n.
$$

The corresponding joint leading piece is

$$
\operatorname{gr}^{m,n}_{I,J}(A)=
\frac{I^m\cap J^n}
{
(I^{m+1}\cap J^n)
+
(I^m\cap J^{n+1})
}.
$$

This separates:

$$
\text{how long the routes are}
\quad\text{from}\quad
\text{how many independent route defects they contain}.
$$

For example:

* parallel-edge differences occur at $(m,n)=(1,1)$;
* an elementary length-two diamond occurs at $(1,2)$;
* a shortcut/composite disagreement begins at ambiguity order $1$, but is inhomogeneous in path length;
* two consecutive diamonds contribute at least $(2,4)$ when each branch has length two.

This bifiltration is intrinsic to the resolved path structure and requires no scalar weights.

---

# 11. Ordinal rank filtering of route ambiguity

The route ideal also respects the transfinite rank structure.

For past-rank layers,

$$
\Delta^-_\beta I^m\Delta^-_\alpha=0
$$

unless

$$
\alpha+m\le\beta.
$$

Every factor from $I$ contains positive paths, so a product of $m$ route defects advances past rank by at least $m$.

Dually,

$$
\Delta^+_\beta I^m\Delta^+_\alpha=0
$$

unless

$$
\beta+m\le\alpha.
$$

Hence each ambiguity order has its own transfinite triangular matrix:

$$
\left[
\Delta^-_\beta
(I^m/I^{m+1})
\Delta^-_\alpha
\right]_{\alpha,\beta}.
$$

This records where first-order, second-order, and higher route ambiguities occur among the ordinal layers.

Natural cardinal-valued invariants include

$$
r_m(\beta,\alpha)=
\dim
\Delta^-_\beta
(I^m/I^{m+1})
\Delta^-_\alpha
$$

and

$$
s_m(\beta,\alpha)=
\dim
\Delta^-_\beta
\mathfrak S_m
\Delta^-_\alpha.
$$

They retain information that any single aggregate spectrum discards.

---

# 12. Why ordinary spectra remain blind

Since

$$
I\subseteq J
$$

and $J$ is locally nilpotent, every algebraic element

$$
x\in I
$$

is nilpotent.

Therefore

$$
\sigma(x)=\{0\}.
$$

The same is true for elements representing:

* one parallel-edge difference;
* one diamond;
* a shortcut discrepancy;
* or any finite product of route defects.

So ordinary spectral values cannot distinguish their structures.

The information instead lies in:

$$
I/I^2,
\qquad
I^2/I^3,
\qquad
\mathfrak S_m,
\qquad
\text{endpoint corners},
\qquad
\text{rank-filtered blocks}.
$$

The finite experiments therefore give:

$$
\text{spectra alone are too compressed, while orthogonal noncommutative structure retains the distinctions}.
$$

---

# 13. Relation to existing path homology

There are established homology theories built from allowed directed paths, beginning with the path-homology construction of Grigor’yan, Lin, Muranov, and Yau. More recent work extends such ideas to quivers, marked categories, and marked algebras.

Those theories are not automatically identical to the route-syzygy structure above.

Their starting point is typically a chain complex with a boundary operation on directed paths. Our starting point is instead the exact quotient

$$
A\to B
$$

and its kernel $I$.

So our construction asks:

$$
\text{what is lost when route-sensitive composition is made thin?}
$$

rather than directly asking:

$$
\text{which directed path chains are cycles or boundaries?}
$$

The language of path algebras modulo relation ideals and higher relations is standard in quiver theory, including approaches based on reduction systems and diamond conditions, but the particular relation ideal here is canonically fixed by the reachability collapse rather than selected as external data.
