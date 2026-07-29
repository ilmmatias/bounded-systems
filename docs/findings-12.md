# 1. Endpoint decomposition

For $u\le v$, let

```math
\mathscr P(u,v)
```

be the set of all finite paths from $u$ to $v$. Its path-space corner is

```math
A_{v,u}=
e_vAe_u=
\mathbb K^{(\mathscr P(u,v))}.
```

Define the endpoint summation map

```math
\varepsilon_{v,u}:A_{v,u}\to\mathbb K
```

by

```math
\varepsilon_{v,u}
\left(
\sum_{p:u\to v}c_pp
\right)=
\sum_{p:u\to v}c_p.
```

Then

```math
I_{v,u}=
e_vIe_u=
\ker\varepsilon_{v,u}.
```

Therefore

```math
I=
\bigoplus_{u<v}I_{v,u}.
```

Every element of $I_{v,u}$ is a finite linear combination of routes from $u$ to $v$ whose coefficients sum to zero.

In particular, it is spanned by differences

```math
p-q
```

of paths with the same endpoints.

---

# 2. Same-length versus cross-length ambiguity

Let

```math
\mathscr P_n(u,v)=
\{p:u\to v,\ |p|=n\}
```

and

```math
A^n_{v,u}=
\mathbb K^{(\mathscr P_n(u,v))}.
```

Then

```math
A_{v,u}=
\bigoplus_{n\ge0}A^n_{v,u}.
```

For each attained length $n$, define

```math
\varepsilon^n_{v,u}:A^n_{v,u}\to\mathbb K
```

by coefficient summation.

The same-length defect space is

```math
I^{\mathrm{same}}_{v,u}=
\bigoplus_n
\ker\varepsilon^n_{v,u}.
```

It contains differences

```math
p-q
```

where $p$ and $q$ have the same endpoints and the same length.

Let

```math
L(u,v)=
\{n:\mathscr P_n(u,v)\ne\varnothing\}
```

be the set of attained route lengths. Define its reduced finite-support coefficient space

```math
\widetilde{\mathbb K}^{(L(u,v))}=
\left\lbrace (a_n)_{n\in L(u,v)}: a_n=0\text{ except finitely often}, \quad \sum_na_n=0 \right\rbrace.
```

There is a canonical exact sequence

```math
0
\longrightarrow
I^{\mathrm{same}}_{v,u}
\longrightarrow
I_{v,u}
\longrightarrow
\widetilde{\mathbb K}^{(L(u,v))}
\longrightarrow
0.
```

The last map sends a route combination to the total coefficient contributed by each length.

Thus the endpoint defect has two distinct parts.

## Same-length ambiguity

Several routes have equal compositional depth:

```math
p,q:u\to v,
\qquad
|p|=|q|.
```

Parallel primitive channels occur here at length one.

Branching followed by reconvergence occurs here at greater lengths.

### Length disagreement

Routes with the same endpoints have different compositional depths:

```math
|p|\ne |q|.
```

The most basic example is a shortcut:

```math
u\to v
```

alongside

```math
u\to w\to v.
```

Their difference belongs to the cross-length part.

Generally, the exact sequence has no canonical splitting: choosing a representative path for each length would be arbitrary.

---

# 3. The orthogonal meaning of the route kernel

The Fock representation makes the route kernel geometrically explicit.

For a fixed endpoint pair, the path creators

```math
{L_p:p\in\mathscr P(u,v)}
```

have mutually orthogonal ranges.

Indeed, for distinct paths $p,q$ with the same source and target,

```math
L_p^\ast L_q=0.
```

Distinct same-endpoint paths cannot be prefix extensions of one another, because that would leave a positive path from $v$ back to $v$, contradicting A5.

Therefore, for

```math
x=\sum_{p:u\to v}c_pL_p,
```

we obtain

```math
x^\ast x=
\left(
\sum_p|c_p|^2
\right)P_u
```

and hence

```math
\left|
\sum_pc_pL_p
\right|=
\left(\sum_p|c_p|^2\right)^{1/2}.
```

So each route corner carries the canonical coefficient Hilbert space

```math
\ell^2(\mathscr P(u,v)).
```

## Finitely many routes

Suppose there are exactly $m$ routes $p_1,\ldots,p_m$. Define

```math
\omega_{v,u}=
\frac1{\sqrt m}
\sum_{j=1}^mL_{p_j}.
```

Then

```math
\mathrm{span}\{L_{p_1},\ldots,L_{p_m}\}=
\mathbb K\omega_{v,u}
\oplus
\overline{I_{v,u}},
```

orthogonally, where

```math
\overline{I_{v,u}}=
\left\lbrace \sum_jc_jL_{p_j}: \sum_jc_j=0 \right\rbrace.
```

Thus:

```math
\text{reachability direction}
\perp
\text{route-defect directions}.
```

The reachability quotient retains the one-dimensional equal-route direction and discards the $m-1$ orthogonal distinctions.

This is a direct realization of the orthogonality constraint you emphasized.

---

# 4. A major infinite-route phenomenon

Now suppose that infinitely many distinct routes connect $u$ to $v$.

The algebraic summation map exists on finite-support combinations but has no bounded extension to

```math
\ell^2(\mathscr P(u,v)).
```

Select $N$ distinct routes with coefficients $1/\sqrt N$: their coefficient norm is one, but their sum is

```math
\sqrt N.
```

So the summation functional is unbounded.

There is an even stronger fact.

## Theorem: infinite route defects are norm dense

If $\mathscr P(u,v)$ is infinite, then

```math
\overline{I_{v,u}}^{\|\cdot\|}=
\overline{\operatorname{span}\{L_p:p\in\mathscr P(u,v)\}}.
```

### Proof

Fix one path $p$, and choose distinct alternative routes

```math
q_1,\ldots,q_N.
```

Define

```math
r_N=
L_p-\frac1N\sum_{j=1}^NL_{q_j}.
```

Its coefficients sum to zero, so

```math
r_N\in I_{v,u}.
```

But

```math
|r_N-L_p|=
\left|
\frac1N\sum_{j=1}^NL_{q_j}
\right|=
\frac1{\sqrt N}
\longrightarrow0.
```

Thus $L_p$ lies in the norm closure of the route-defect space; since $p$ was arbitrary, the entire route corner does.

## Consequence

With infinitely many routes, no one-dimensional “equal-route direction” survives in the Fock Hilbert geometry.

Instead,

```math
\text{the algebraic reachability quotient becomes analytically singular}.
```

If we quotient the norm-closed Fock algebra by the norm closure of $I$, the whole infinite-route corner is killed—not collapsed to one nonzero reachability arrow.

This gives a precise reason that the operations

```math
\text{collapse routes}
\qquad\text{and}\qquad
\text{take Fock norm closure}
```

do not commute.

It is one of the strongest genuinely infinite conclusions obtained so far.

---

# 5. Locally irreducible route defects

Some route relations are merely larger contexts surrounding a smaller ambiguity.

Suppose

```math
r=p-q\in I
```

is a route defect from $u$ to $v$; let $a,b$ be positive paths composable on the left and right. Then

```math
arb
```

is the same ambiguity with extra path context attached.

Such extended relations lie in

```math
JI+IJ,
```

where $J$ is the positive-path ideal.

Define the indecomposable route-relation module

```math
\mathcal R=
I/(JI+IJ).
```

Since positive paths act trivially on this quotient, $\mathcal R$ is naturally a bimodule over the node diagonal $\mathcal D=A/J$.

Its corner

```math
e_v\mathcal Re_u
```

records route ambiguity from $u$ to $v$ that cannot be expressed as a smaller ambiguity merely prefixed or suffixed by additional paths.

## Examples

### Parallel channels

For

```math
a,b:u\to v,
```

the difference

```math
a-b
```

survives in $\mathcal R$.

### Basic diamond

Suppose

```math
u\to x\to v
```

and

```math
u\to y\to v.
```

Let the two composite routes be $p$ and $q$. Then

```math
p-q
```

survives in $\mathcal R$, provided there is no smaller route ambiguity inside either branch.

### Extended diamond

If $c$ precedes the diamond and $d$ follows it, then

```math
d(p-q)c
```

vanishes in $\mathcal R$. It contains no new local route ambiguity; it is the original diamond transported into a longer context.

### Shortcut relation

If there is a primitive edge $e:u\to v$ and a composite path $p:u\to v$, then

```math
e-p
```

is an indecomposable cross-length relation unless it is generated by smaller route defects.

Thus

```math
\mathcal R
```

locates the elementary branching/reconvergence or shortcut structures from which larger route discrepancies are built.

---

# 6. The route-ambiguity filtration

The ideal powers

```math
I\supseteq I^2\supseteq I^3\supseteq\cdots
```

give another canonical hierarchy.

An element of $I^m$ is a sum of products of $m$ composable route defects.

Since

```math
I\subseteq J,
```

we have

```math
I^m\subseteq J^m.
```

Consequently:

* $I$ is locally nilpotent;
* every algebraic route defect is nilpotent;
* $\bigcap_{m\ge1}I^m=0$.

The last assertion follows because a nonzero path polynomial has bounded path lengths, while every element of $I^m$ is supported on paths of length at least $m$.

Define the associated graded route algebra

```math
\mathrm{gr}_I(A)=
B
\oplus
I/I^2
\oplus
I^2/I^3
\oplus\cdots.
```

This measures route sensitivity by the number of independent ambiguity factors.

---

# 7. First-order route ambiguity

Set

```math
\mathcal N=I/I^2.
```

Unlike $\mathcal R$, this is naturally a bimodule over

```math
B=A/I.
```

It retains route defects to first order, while setting products of two defects to zero.

The two quotients differ:

```math
\mathcal R=I/(JI+IJ)
```

removes ordinary path context, while

```math
\mathcal N=I/I^2
```

removes products of independent route ambiguities.

An extended diamond relation may vanish in $\mathcal R$ but remain nonzero in $\mathcal N$, because attaching ordinary paths is not the same as multiplying by another route defect.

Thus:

```math
\begin{aligned}
\mathcal R &: \text{local generators of ambiguity},\\
\mathcal N &: \text{first-order ambiguity relative to reachability}.
\end{aligned}
```

---

# 8. Higher ambiguity and the syzygy algebra

Multiplication gives, for every $m\ge1$, a canonical surjection

```math
\mu_m:
\mathcal N^{\otimes_Bm}
\longrightarrow
I^m/I^{m+1}
```

defined by

```math
[r_m]\otimes\cdots\otimes[r_1]
\longmapsto
[r_m\cdots r_1].
```

For infinite node sets, this can be understood corner by corner using finite sums of node idempotents; no global algebraic identity is required.

The maps combine into a graded surjection

```math
\Psi:
T_B(\mathcal N)
\longrightarrow
\mathrm{gr}_I(A),
```

where

```math
T_B(\mathcal N)=
B
\oplus\mathcal N
\oplus
\mathcal N^{\otimes_B2}
\oplus\cdots.
```

Define the route-syzygy ideal

```math
\mathfrak S=\ker\Psi.
```

Its degree-$m$ part

```math
\mathfrak S_m
```

consists of identities among formal products of $m$ first-order route defects.

So we obtain three layers:

```math
\begin{aligned}
\mathcal N
&=I/I^2
&&\text{first-order route ambiguity},\\
I^m/I^{m+1}
&&&\text{actual }m\text{-fold ambiguity},\\
\mathfrak S_m
&&&\text{relations among }m\text{-fold ambiguity factorizations}.
\end{aligned}
```

This is the systematic route-syzygy structure we were seeking.

---

# 9. Two consecutive diamonds

Consider two composable ambiguous sectors.

The first has routes

```math
p_0,p_1:u\to w,
```

giving

```math
r_1=p_1-p_0.
```

The second has routes

```math
q_0,q_1:w\to v,
```

giving

```math
r_2=q_1-q_0.
```

Their product is

```math
r_2r_1=
q_1p_1-q_1p_0-q_0p_1+q_0p_0.
```

This is a second-order route defect:

```math
r_2r_1\in I^2.
```

It compares the four routes obtained by independently choosing one branch in each diamond.

The alternating signs arise from multiplying the two differences.

If these are the only two composable ambiguity sectors, then

```math
I^3=0,
```

and the class

```math
[r_2r_1]\in I^2/I^3
```

is nonzero.

Thus higher powers of $I$ encode interaction among branching decisions:

```math
\text{one diamond}
\to I/I^2,
\qquad
\text{two composable diamonds}
\to I^2/I^3,
\quad\ldots
```

A degree-two syzygy appears when two different tensors in

```math
\mathcal N\otimes_B\mathcal N
```

produce the same second-order defect. Their difference lies in

```math
\mathfrak S_2.
```

---

# 10. Joint path-depth and ambiguity filtration

The positive-path filtration and route-defect filtration measure different things:

* $J^n$: minimum compositional depth;
* $I^m$: minimum number of route-ambiguity factors.

Combine them through

```math
F^{m,n}=
I^m\cap J^n.
```

The corresponding joint leading piece is

```math
\mathrm{gr}^{m,n}_{I,J}(A)=
\frac{I^m\cap J^n}
{
(I^{m+1}\cap J^n)
+
(I^m\cap J^{n+1})
}.
```

This separates:

```math
\text{how long the routes are}
\quad\text{from}\quad
\text{how many independent route defects they contain}.
```

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

```math
\Delta^-_\beta I^m\Delta^-_\alpha=0
```

unless

```math
\alpha+m\le\beta.
```

Every factor from $I$ contains positive paths, so a product of $m$ route defects advances past rank by at least $m$.

Dually,

```math
\Delta^+_\beta I^m\Delta^+_\alpha=0
```

unless

```math
\beta+m\le\alpha.
```

Hence each ambiguity order has its own transfinite triangular matrix:

```math
\left[
\Delta^-_\beta
(I^m/I^{m+1})
\Delta^-_\alpha
\right]_{\alpha,\beta}.
```

This records where first-order, second-order, and higher route ambiguities occur among the ordinal layers.

Natural cardinal-valued invariants include

```math
r_m(\beta,\alpha)=
\dim
\Delta^-_\beta
(I^m/I^{m+1})
\Delta^-_\alpha
```

and

```math
s_m(\beta,\alpha)=
\dim
\Delta^-_\beta
\mathfrak S_m
\Delta^-_\alpha.
```

They retain information that any single aggregate spectrum discards.

---

# 12. Why ordinary spectra remain blind

Since

```math
I\subseteq J
```

and $J$ is locally nilpotent, every algebraic element

```math
x\in I
```

is nilpotent.

Therefore

```math
\sigma(x)=\{0\}.
```

The same is true for elements representing:

* one parallel-edge difference;
* one diamond;
* a shortcut discrepancy;
* or any finite product of route defects.

So ordinary spectral values cannot distinguish their structures.

The information instead lies in:

```math
I/I^2,
\qquad
I^2/I^3,
\qquad
\mathfrak S_m,
\qquad
\text{endpoint corners},
\qquad
\text{rank-filtered blocks}.
```

The finite experiments therefore give:

```math
\text{spectra alone are too compressed, while orthogonal noncommutative structure retains the distinctions}.
```

---

# 13. Relation to existing path homology

Established homology theories for allowed directed paths begin with the path-homology construction of Grigor’yan, Lin, Muranov, and Yau; recent work extends these ideas to quivers, marked categories, and marked algebras.

Those theories are not automatically identical to the route-syzygy structure above.

They typically start from a chain complex with a boundary operation on directed paths; we start instead from the exact quotient

```math
A\to B
```

and its kernel $I$.

So our construction asks:

```math
\text{what is lost when route-sensitive composition is made thin?}
```

rather than directly asking:

```math
\text{which directed path chains are cycles or boundaries?}
```

Path algebras modulo relation ideals and higher relations are standard in quiver theory, including reduction-system and diamond-condition approaches, but here the reachability collapse canonically fixes the relation ideal rather than supplying it as external data.
