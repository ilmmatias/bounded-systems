# 1. Decorated acyclic sectors

The finite forcing result of `findings-83.md` is relative to a prescribed
partition. A general completion removes these decorations while preserving
acyclicity and every payload relation.

Let a decorated acyclic sector have parts

```math
L_1,\ldots,L_q
```

of masses $\alpha_1,\ldots,\alpha_q$, where $\alpha_i>0$ and
$\sum_i\alpha_i=1$. Assume the parts are ordered so that the payload kernel
has no block from $L_j$ to $L_i$ when $j\geq i$.

For $x\in L_i$, write

```math
r_i(x)
=
\sum_{j>i}\alpha_j
\int_{L_j}\Gamma_{ij}(x,y)\,d\mu_j(y)
```

for its normalized outgoing payload degree, and write

```math
c_i(x)
=
\sum_{j<i}\alpha_j
\int_{L_j}\Gamma_{ji}(y,x)\,d\mu_j(y)
```

for its normalized incoming payload degree. Both functions take values in
$[0,1]$. The normalized payload edge density is

```math
e
=
\sum_i\alpha_i\int_{L_i}r_i(x)\,d\mu_i(x)
=
\sum_i\alpha_i\int_{L_i}c_i(x)\,d\mu_i(x).
```

Assume that the decorated payload is finitely forcible relative to the parts
$L_i$.

# 2. Tagged and compensated completion

Choose positive numbers

```math
\beta,
\quad d,
\quad c,
\quad s_1,\ldots,s_q,
\quad t_1,\ldots,t_q
```

such that

```math
\beta+d+c+\sum_i(s_i+t_i)=1,
```

and

```math
d\geq2\beta,
\qquad
c\geq2\beta.
```

Scale the whole decorated payload to total mass $\beta$, so the completed
mass of $L_i$ is $\beta\alpha_i$. Add source-marker parts $S_i$ of mass
$s_i$, sink-marker parts $T_i$ of mass $t_i$, one global source compensator
$D$ of mass $d$, and one global sink compensator $C$ of mass $c$.

Retain the original payload blocks on the $L_i$. Add the deterministic
marker blocks

```math
S_i\longrightarrow L_i,
\qquad
S_i\longrightarrow T_i,
\qquad
L_i\longrightarrow T_i
```

with kernel value one. The two compensator blocks are defined by

```math
\Gamma_{D,L_i}(u,x)
=
\frac12+
\frac{\beta(1-c_i(x))}{d},
```

and

```math
\Gamma_{L_i,C}(x,v)
=
\frac12+
\frac{\beta(1-r_i(x))}{c}.
```

They are independent of the auxiliary coordinates $u\in D$ and $v\in C$. All
other blocks vanish.

The inequalities on $d$ and $c$ ensure that both compensator kernels lie in
$[0,1]$.

# 3. Constant and distinct degree pairs

The compensators cancel every payload-dependent variation in total directed
degree. Every point of $L_i$ has the constant degree pair

```math
\delta(L_i)
=
\left(
 s_i+\beta+\frac d2,
 t_i+\beta+\frac c2
\right).
```

Indeed, the incoming contribution of the payload is $\beta c_i(x)$, while
the contribution of $D$ is

```math
d
\left(
\frac12+
\frac{\beta(1-c_i(x))}{d}
\right)
=
\frac d2+\beta-\beta c_i(x).
```

The outgoing calculation is identical.

The auxiliary degree pairs are

```math
\delta(S_i)
=
\left(0,\beta\alpha_i+t_i\right),
```

whereas the target marker has

```math
\delta(T_i)
=
\left(s_i+\beta\alpha_i,0\right),
```

and the source compensator has

```math
\delta(D)
=
\left(
0,
\frac\beta2+
\frac{\beta^2(1-e)}d
\right),
```

and

```math
\delta(C)
=
\left(
\frac\beta2+
\frac{\beta^2(1-e)}c,
0
\right).
```

## Proposition 1. Separation parameters

For every finite decorated payload, the parameters can be chosen so that all
$3q+2$ displayed degree pairs are distinct.

## Proof

Choose $\beta>0$ sufficiently small and then choose $d,c>2\beta$ with
$d+c<1-\beta$. The remaining parameters $(s_i,t_i)$ vary in a nonempty open
simplex. Every unwanted equality between two displayed degree pairs is a
proper affine or algebraic hypersurface in this simplex. There are only
finitely many such equalities. Their union has empty interior, so parameters
outside it exist. Rational points are dense, and the parameters may therefore
be chosen rational.

# 4. Acyclicity

Place the parts in the topological order

```math
D,S_1,\ldots,S_q,
L_1,\ldots,L_q,
T_1,\ldots,T_q,C.
```

Every nonzero block points forward in this order. The completion is therefore
acyclic whenever the decorated payload is acyclic.

# 5. Absolute forcing theorem

Distinct degree pairs and the forward block order make each completed part
recoverable from rooted degree data, which gives the following transfer
statement.

## Theorem 2. Tagged-compensated transfer

Let a finite decorated acyclic sector be finitely forcible relative to its
parts. A separated tagged-compensated completion is absolutely finitely
forcible in the full central DAG boundary.

## Proof

The finite set of constant degree pairs is forced by the nonnegative rooted
polynomial

```math
Q(z_-,z_+)
=
\prod_P
\left(
(z_--\delta^-_P)^2
+
(z_+-\delta^+_P)^2
\right),
```

where $P$ ranges over all completed parts. Lagrange interpolation on this
finite zero set gives polynomial indicators for every part. Their integrals
force the target part masses.

The zero-block constraints force the stated acyclic architecture.
Variance-zero constraints force the marker blocks to have the constant values
zero or one. Once the $L_i$ are represented by graph-intrinsic polynomial
indicators, the original decorated forcing family becomes a finite family of
ordinary quantum-DAG constraints by the realization lemma of
`findings-70.md`.

The total-degree identities determine the required column function of every
block $D\to L_i$ and the required row function of every block $L_i\to C$. The
one-sided Gram defects of `findings-75.md` force those blocks to be
independent of the auxiliary coordinate. They are therefore exactly the
displayed compensator kernels.

All constraints are polynomial expressions in finitely many rooted densities.
Squaring and integrating produces a nonnegative sector energy, and the
boundary polynomial lift turns it into finitely many ordinary induced-DAG
coordinates. Zero energy forces almost every extremal component to equal the
completed target. The central law is therefore the selected extremal sector.

# 6. Consequences

The theorem removes finite decorations without requiring the payload itself
to have constant degrees, finite rank, finite range, or finitely many rooted
types. The auxiliary parts perform only two tasks:

- marker blocks distinguish the payload classes;
- compensator blocks make the finite partition recoverable through constant
  degree pairs.

Every relation proved inside the payload remains valid after completion and
can be written as an ordinary uncolored quantum-DAG identity using the
polynomial part indicators.

For rational three-part acyclic payload matrices, exact calculations give
degree flattening at every payload atom, separation of all completed degree
pairs, vanishing one-sided Gram defects, positivity under compensator
perturbations, and absence of directed cycles.

# 7. Literature relation

Decorated graphon constraints are commonly eliminated by forcing a finite
partition and then translating decorated expressions into ordinary
subgraph-density constraints, as in L. Lovasz and B. Szegedy,
*Finitely forcible graphons*, Journal of Combinatorial Theory, Series B 101
(2011), 269-301, arXiv:0901.0929, and D. Kral, L. M. Lovasz, J. A. Noel, and
J. Sosnovec, *Finitely forcible graphons with an almost arbitrary structure*,
Discrete Analysis 2020:9, arXiv:1809.05973. The construction above is an
acyclic directed version with explicit marker and compensator blocks. The
compensators are needed because the payload parts may have continuously
varying directed degrees.
