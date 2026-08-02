# 1. Bipartite payload kernels

The forcing results through `findings-74.md` treat finite ordered step
kernels. A non-step sector requires a mechanism that inserts an arbitrary
bipartite kernel into an acyclic digraphon without losing graph-intrinsic
identification of the ambient parts.

Let

```math
U:X\times Y\longrightarrow[0,1]
```

be a bigraphon on atomless probability spaces $(X,\mu)$ and $(Y,\nu)$. The
row-degree function is

```math
r_U(x)=\int_YU(x,y)\,d\nu(y),
```

the column-degree function is

```math
c_U(y)=\int_XU(x,y)\,d\mu(x),
```

and

```math
e_U=\int_{X\times Y}U(x,y)\,d\mu(x)d\nu(y).
```

Two bigraphons are weakly isomorphic when they agree after independent
measure-preserving changes of variables on their left and right probability
spaces. We call $U$ finitely forcible when finitely many bipartite pattern
densities determine its weak-isomorphism class.

# 2. Balanced acyclic completion

Assume

```math
0<e_U<1.
```

Form four disjoint parts

```math
D,\quad A,\quad B,\quad C,
```

each of mass $1/4$. Identify $A$ with $X$, $B$ with $Y$, and let $D$ and $C$
be auxiliary copies of atomless probability spaces. Define the directed
kernel $\Gamma_U$ by

```math
\Gamma_U(a,b)=U(a,b)
\qquad(a\in A,\ b\in B),
```

the first compensator block is

```math
\Gamma_U(a,c)=1-r_U(a)
\qquad(a\in A,\ c\in C),
```

and

```math
\Gamma_U(d,b)=1-c_U(b)
\qquad(d\in D,\ b\in B).
```

All remaining blocks are zero.

Every edge starts in $D\cup A$ and ends in $B\cup C$. The kernel is therefore
acyclic and contains no directed path of length two.

The compensator blocks make the degree pairs constant on each part. With the
convention

```math
\delta(x)=(\delta^-(x),\delta^+(x)),
```

we obtain

```math
\delta(D)
=
\left(0,\frac{1-e_U}{4}\right),
```

whereas the first payload class has

```math
\delta(A)
=
\left(0,\frac14\right),
```

and the second payload class has

```math
\delta(B)
=
\left(\frac14,0\right),
```

and

```math
\delta(C)
=
\left(\frac{1-e_U}{4},0\right).
```

These four points are distinct because $0<e_U<1$. The parts are therefore
recoverable from the unmarked directed kernel by the polynomial interpolation
method used in `findings-66.md` and `findings-70.md`.

# 3. One-sided rigidity

The auxiliary blocks must be forced to contain exactly the row and column
complements of the payload. Constant total degrees alone do not remove
fluctuations in the auxiliary coordinate. The following defect does.

Let $K:X\times Z\to[0,1]$ be a bigraphon and let

```math
f(x)=\int_ZK(x,z)\,d\zeta(z).
```

Define

```math
\mathcal R(K)
=
\int_{X^2}
\left[
 \int_ZK(x,z)K(x',z)\,d\zeta(z)
 -f(x)f(x')
\right]^2
\,d\mu(x)d\mu(x').
```

## Proposition 1. One-sided rank-one criterion

The defect $\mathcal R(K)$ vanishes if and only if

```math
K(x,z)=f(x)
```

for almost every $(x,z)$.

## Proof

Set

```math
R(x,z)=K(x,z)-f(x).
```

The kernel inside the square is

```math
\int_ZR(x,z)R(x',z)\,d\zeta(z),
```

which is the integral kernel of the positive operator $RR^*$. If
$\mathcal R(K)=0$, then $RR^*=0$ as a Hilbert-Schmidt operator, hence $R=0$.
The converse is immediate.

There is a column version $\mathcal C(K)$, obtained by interchanging the two
probability spaces. Both defects are finite quantum-bigraph densities: after
expanding the square, every term is a finite bipartite pattern density. Once
the four parts are represented by rooted polynomial indicators, the same
expressions are finite quantum-DAG observables by Proposition 1 of
`findings-70.md`.

# 4. Forcing the completion

Suppose the four degree classes and their masses have been forced. The
zero-block constraints remove every edge except

```math
D\longrightarrow B,
\qquad
A\longrightarrow B,
\qquad
A\longrightarrow C.
```

The $A\times B$ block is then constrained by a finite forcing family for $U$.

For $a\in A$, the fixed total outdegree gives

```math
\int_B\Gamma(a,b)\,d\nu(b)
+
\int_C\Gamma(a,c)\,d\zeta(c)
=1.
```

Thus the normalized row degree of the $A\times C$ block is $1-r_U(a)$.
Imposing the one-sided defect $\mathcal R=0$ forces

```math
\Gamma(a,c)=1-r_U(a).
```

The analogous column defect on $D\times B$ forces

```math
\Gamma(d,b)=1-c_U(b).
```

Every displayed condition is a polynomial identity in finitely many rooted
pattern densities. Squaring the identities gives a nonnegative extremal-sector
energy, and the boundary polynomial lift of `findings-70.md` turns its ergodic
average into finitely many ordinary induced-DAG coordinates.

## Theorem 2. Balanced-completion transfer

Let $U$ be a finitely forcible bigraphon satisfying $0<e_U<1$. Its balanced
acyclic completion $\Gamma_U$ is absolutely finitely forcible in the full
central DAG boundary.

## Proof

Let a central law have zero lifted forcing energy. Nonnegativity makes every
term vanish in almost every extremal component.

The degree-pair polynomial and mass constraints recover the four parts
$D,A,B,C$. The zero-block constraints give the source-sink architecture. The
finite payload constraints identify the $A\times B$ block with $U$ up to
independent measure-preserving transformations. Fixed total degrees determine
the row and column sums of the two auxiliary blocks. Proposition 1 and its
column analogue force those blocks to be the required complements. Hence
almost every extremal component is weakly isomorphic to $\Gamma_U$, and the
original central law is the corresponding extremal sector.

# 5. Structural consequences

The transfer theorem separates two tasks that were previously combined in the
ordered step construction.

The bigraphon forcing family controls the internal payload. The balanced
completion controls acyclicity, part recovery, and compatibility of the
payload with the unmarked DAG endpoint. The payload can therefore be
non-step, have continuum range, or have infinite operator rank without
changing the finite nature of the final relational selector.

Once $\Gamma_U$ is selected, all results of `findings-56.md` apply to its
finite DAG observables. The complete projective profile, harmonic function, up
transition, support-order coefficients, and logarithmic process limits exist
exactly as in the previously studied sectors.

Exact rational calculations confirm that:

- arbitrary finite rational payload matrices have the four claimed degree pairs;
- the two compensator blocks reconstruct the row and column complements;
- the one-sided Gram defects vanish on the balanced completion;
- row-sum-preserving perturbations of a compensator produce a strictly
  positive defect;
- the completed directed matrix has no directed path of length two.

# 6. Literature relation

The proof uses the same general principle as decorated graphon forcing: a
finitely forcible payload is inserted into an intrinsically identifiable
finite partition, and decorated constraints are then converted into ordinary
density constraints, as in L. Lovasz and B. Szegedy,
*Finitely forcible graphons*, Journal of Combinatorial Theory, Series B 101
(2011), 269-301, arXiv:0901.0929, and J. W. Cooper, D. Kral, and T. L.
Martins, *Finitely forcible graph limits are universal*, Advances in
Mathematics 340 (2018), 819-854, arXiv:1701.03846. The new point is the
acyclic balancing operation. It makes every ambient part have a constant and
distinct directed degree pair while allowing the payload itself to be
arbitrary.
