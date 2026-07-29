# 1. Bounded systems and finite adjacency data

A bounded system is an isomorphism class of acyclic directed multigraphs:

```math
B=\big[(N,E,s,t)\big]_{\cong}.
```

The representative data consist of a set $N$ of nodes with no primitive labels or attributes, a set $E$ of directed channels, and source and target maps $s,t:E\to N$. The graph $(N,E,s,t)$ is acyclic, while distinct channels $e,f\in E$ may have the same source and target. All changes of the system are therefore represented internally by its channels.

For the finite calculations below, fix a representative

```math
G=(N,E,s,t)
```

of $B$. If $n=|N|$, temporarily label the nodes by $(1,\dots,n)$. Relabeling by a permutation matrix $P$ sends the adjacency matrix to

```math
A\longmapsto P^{-1}AP.
```

Consequently, only quantities invariant under permutation similarity define properties of $B$. The adjacency matrix is given by

```math
A_{ij}=
\text{number of realized directed channels }i\to j.
```

## Nilpotence of the adjacency matrix

Because $G$ is a finite DAG, its nodes can be topologically ordered. In that ordering,

```math
A=
\begin{pmatrix}
0&\ast&\ast&\cdots&\ast\\
0&0&\ast&\cdots&\ast\\
0&0&0&\cdots&\ast\\
\vdots&\vdots&\vdots&\ddots&\ast\\
0&0&0&\cdots&0
\end{pmatrix}.
```

Thus $A$ is strictly upper triangular and satisfies

```math
A^n=0.
```

It follows that every finite configuration has

```math
\mathrm{spec}(A)=\{0\}.
```

## Path counts and finite spectral data

With this convention, the matrix entry $(A^k)_{ij}$ counts directed paths of length $k$ from $i$ to $j$, including channel multiplicities. Hence the least integer $\nu$ for which

```math
A^\nu=0
```

is the nilpotency index, and the longest directed path has length $\nu-1$.

For later comparisons, define the rank profile

```math
\rho(A)=
\left(
\mathrm{rank}A,
\mathrm{rank}A^2,\ldots
\right)
```

and truncate the sequence after it first reaches zero. We also record the singular-value multiset

```math
\sigma(A)=
\sqrt{\mathrm{spec}(A^\mathsf TA)}.
```

# 2. Simple-channel configurations

We first restrict to the $0/1$ sector, in which at most one channel is present in a fixed direction between any ordered pair of nodes. This is the smallest finite sector of the theory.

Let

```math
\varphi=\frac{1+\sqrt5}{2}.
```

The symbols $d^+$ and $d^-$ denote the multisets of out-degrees and in-degrees, respectively. We write $L_u$ for the Laplacian of the underlying undirected graph obtained by forgetting edge orientation.

## Classification through three nodes

| Nodes | Configuration            | $\rho(A)$ | $\sigma(A)$                | $d^+$       | $d^-$       | $\mathrm{spec}(L_u)$ |
| ----: | ------------------------ | --------- | -------------------------- | ----------- | ----------- | -------------------------- |
|     1 | isolated node            | $(0)$     | $(0)$                      | $\{0\}$     | $\{0\}$     | $\{0\}$                    |
|     2 | two isolated nodes       | $(0)$     | $(0,0)$                    | $\{0,0\}$   | $\{0,0\}$   | $\{0,0\}$                  |
|     2 | $1\to2$                  | $(1,0)$   | $(1,0)$                    | $\{1,0\}$   | $\{1,0\}$   | $\{0,2\}$                  |
|     3 | three isolated nodes     | $(0)$     | $(0,0,0)$                  | $\{0,0,0\}$ | $\{0,0,0\}$ | $\{0,0,0\}$                |
|     3 | one edge + isolated node | $(1,0)$   | $(1,0,0)$                  | $\{1,0,0\}$ | $\{1,0,0\}$ | $\{0,0,2\}$                |
|     3 | outgoing fork            | $(1,0)$   | $(\sqrt2,0,0)$             | $\{2,0,0\}$ | $\{1,1,0\}$ | $\{0,1,3\}$                |
|     3 | incoming fork            | $(1,0)$   | $(\sqrt2,0,0)$             | $\{1,1,0\}$ | $\{2,0,0\}$ | $\{0,1,3\}$                |
|     3 | chain                    | $(2,1,0)$ | $(1,1,0)$                  | $\{1,1,0\}$ | $\{1,1,0\}$ | $\{0,1,3\}$                |
|     3 | transitive triangle      | $(2,1,0)$ | $(\varphi,\varphi^{-1},0)$ | $\{2,1,0\}$ | $\{2,1,0\}$ | $\{0,3,3\}$                |

# 3. Three-node calculations

## Outgoing fork

For the outgoing fork

```math
1\to2,\qquad1\to3,
```

the adjacency matrix is

```math
A_{\mathrm{out}}=
\begin{pmatrix}
0&1&1\\
0&0&0\\
0&0&0
\end{pmatrix}.
```

Then

```math
A_{\mathrm{out}}^2=0,
```

so the longest path has length $1$.

Also,

```math
A_{\mathrm{out}}^\mathsf T A_{\mathrm{out}}=
\begin{pmatrix}
0&0&0\\
0&1&1\\
0&1&1
\end{pmatrix},
```

whose eigenvalues are $2,0,0$. Therefore

```math
\sigma(A_{\mathrm{out}})=
(\sqrt2,0,0).
```

## Incoming fork

For the incoming fork

```math
1\to3,\qquad2\to3,
```

the adjacency matrix is

```math
A_{\mathrm{in}}=
\begin{pmatrix}
0&0&1\\
0&0&1\\
0&0&0
\end{pmatrix}.
```

The incoming and outgoing forks have the same rank profile and singular values:

```math
\rho(A_{\mathrm{in}})=(1,0),
\qquad
\sigma(A_{\mathrm{in}})=(\sqrt2,0,0).
```

The singular values therefore do not distinguish convergence from divergence. The in- and out-degree multisets do:

```math
d^+_{\mathrm{out}}=\{2,0,0\},
\qquad
d^-_{\mathrm{out}}=\{1,1,0\},
```

while

```math
d^+_{\mathrm{in}}=\{1,1,0\},
\qquad
d^-_{\mathrm{in}}=\{2,0,0\}.
```

## Chain

For the chain

```math
1\to2\to3,
```

the adjacency matrix is

```math
A_{\mathrm{chain}}=
\begin{pmatrix}
0&1&0\\
0&0&1\\
0&0&0
\end{pmatrix}.
```

Then

```math
A_{\mathrm{chain}}^2=
\begin{pmatrix}
0&0&1\\
0&0&0\\
0&0&0
\end{pmatrix},
\qquad
A_{\mathrm{chain}}^3=0.
```

Consequently, its rank profile is

```math
\rho(A_{\mathrm{chain}})=
(2,1,0).
```

Its longest path has length two.

Also,

```math
A_{\mathrm{chain}}^\mathsf T A_{\mathrm{chain}}=
\begin{pmatrix}
0&0&0\\
0&1&0\\
0&0&1
\end{pmatrix},
```

so

```math
\sigma(A_{\mathrm{chain}})=
(1,1,0).
```

## Transitive triangle

For the transitive triangle

```math
1\to2,\qquad2\to3,\qquad1\to3,
```

the adjacency matrix is

```math
A_{\triangle}=
\begin{pmatrix}
0&1&1\\
0&0&1\\
0&0&0
\end{pmatrix}.
```

Again,

```math
A_{\triangle}^2=
\begin{pmatrix}
0&0&1\\
0&0&0\\
0&0&0
\end{pmatrix},
\qquad
A_{\triangle}^3=0.
```

The chain and transitive triangle have the same rank profile:

```math
\rho(A_{\triangle})=
\rho(A_{\mathrm{chain}})=
(2,1,0).
```

But their singular spectra differ:

```math
\sigma(A_{\triangle})=
\left(\varphi,\varphi^{-1},0\right),
```

where

```math
\varphi=\frac{1+\sqrt5}{2}.
```

# 4. Immediate channels and reachability

To distinguish immediate communication from eventual communication, define the binary reachability matrix

```math
R_{ij}=
\begin{cases}
1,&\text{if a nonempty directed path exists from }i\text{ to }j,\\
0,&\text{otherwise}.
\end{cases}
```

For the chain

```math
1\to2\to3,
```

the reachability matrix is

```math
R_{\mathrm{chain}}=
\begin{pmatrix}
0&1&1\\
0&0&1\\
0&0&0
\end{pmatrix}.
```

This is the adjacency matrix of the transitive triangle:

```math
R_{\mathrm{chain}}=A_{\triangle}.
```

Since the transitive triangle is already transitively closed, $R_{\triangle}=A_{\triangle}$, and hence

```math
R_{\mathrm{chain}}=R_{\triangle}.
```

The chain and the transitive triangle thus have different immediate channel structures but the same reachability relation. The adjacency matrix $A$ records immediate channels, whereas $R$ records eventual reachability; both must be retained.

# 5. Parallel-channel configurations

Allow parallel channels, and let $a,b,c$ denote positive integer multiplicities.

## Two nodes

With $a$ channels from $1$ to $2$,

```math
A=
\begin{pmatrix}
0&a\\
0&0
\end{pmatrix}.
```

Then

```math
\sigma(A)=(a,0).
```

## Three-node outgoing or incoming fork

For the outgoing fork,

```math
A=
\begin{pmatrix}
0&a&b\\
0&0&0\\
0&0&0
\end{pmatrix}.
```

Its singular values are

```math
\sigma(A)=
\left(\sqrt{a^2+b^2},0,0\right).
```

## Weighted chain

For the weighted chain

```math
1\xrightarrow{a}2\xrightarrow{b}3,
```

the adjacency matrix is

```math
A=
\begin{pmatrix}
0&a&0\\
0&0&b\\
0&0&0
\end{pmatrix}.
```

Then

```math
A^2=
\begin{pmatrix}
0&0&ab\\
0&0&0\\
0&0&0
\end{pmatrix}.
```

The singular values are

```math
\sigma(A)=
\left(
\max(a,b),
\min(a,b),
0
\right).
```

## Weighted transitive triangle

Let

```math
1\xrightarrow{a}2,
\qquad
2\xrightarrow{b}3,
\qquad
1\xrightarrow{c}3.
```

Then

```math
A=
\begin{pmatrix}
0&a&c\\
0&0&b\\
0&0&0
\end{pmatrix}.
```

Set

```math
S=a^2+b^2+c^2.
```

The two nonzero squared singular values are

```math
\sigma_{\pm}^2=
\frac{
S\pm\sqrt{S^2-4a^2b^2}
}{2},
```

and the third singular value is zero.

# 6. A weighted-chain collision

Consider the weighted chains

```math
G_1:\quad 1\xrightarrow{a}2\xrightarrow{b}3,
\qquad
G_2:\quad 1\xrightarrow{b}2\xrightarrow{a}3,
```

with $a\neq b$.

The directed weighted graphs are nonisomorphic. The source, middle, and target are structurally fixed, so an isomorphism cannot exchange the upstream and downstream multiplicities. Nevertheless, they share identical adjacency eigenvalues, singular values, degree multisets, and underlying weighted-Laplacian spectra, as well as the same path multiplicity $ab$.

The initial spectral package therefore does not determine whether the larger multiplicity occurs upstream or downstream.

# 7. An asymmetric Gram operator

To retain the directional placement of channel multiplicities, fix

```math
\tau>0,\qquad \tau\neq1,
```

and define the positive-semidefinite matrix

```math
Q_\tau(A)=
A^\mathsf TA+\tau AA^\mathsf T.
```

The term $A^\mathsf TA$ compares incoming-channel profiles, whereas $AA^\mathsf T$ compares outgoing-channel profiles. The condition $\tau\neq1$ prevents these two roles from entering symmetrically.

For the weighted chain $a$ followed by $b$,

```math
Q_\tau(a,b)=
\begin{pmatrix}
\tau a^2&0&0\\
0&a^2+\tau b^2&0\\
0&0&b^2
\end{pmatrix}.
```

Its determinant is

```math
\det Q_\tau(a,b)=
\tau a^2b^2(a^2+\tau b^2).
```

After exchanging $a$ and $b$,

```math
\det Q_\tau(b,a)=
\tau a^2b^2(b^2+\tau a^2).
```

Their difference is

```math
\det Q_\tau(a,b)-\det Q_\tau(b,a)=
\tau a^2b^2(1-\tau)(a^2-b^2).
```

When

```math
a\neq b
\quad\text{and}\quad
\tau\neq1,
```

the determinants, and therefore the spectra, are distinct. Thus $\mathrm{spec}(Q_\tau)$ distinguishes the two weighted-chain orientations.
