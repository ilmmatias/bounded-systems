# 1. Formal setup

Take one realized configuration of the system.

Let

```math
G=(N,E)
```

be its directed acyclic graph.

For $n=|N|$, temporarily label the nodes $(1,\dots,n)$. A relabeling by a permutation matrix $P$ changes the adjacency matrix by

```math
A\longmapsto P^{-1}AP.
```

Therefore, only quantities invariant under permutation similarity count as properties of the system.

Define

```math
A_{ij}=
\text{number of realized directed channels }i\to j.
```

## Adjacency nilpotence

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

Thus $A$ is strictly upper triangular and

```math
A^n=0.
```

Consequently,

```math
\mathrm{spec}(A) = \{0\}
```

for every finite configuration.

## Powers count paths

With our convention,

```math
(A^k)_{ij}
```

counts the number of directed paths of length $k$ from $i$ to $j$, counting channel multiplicities.

Thus the smallest number $\nu$ such that

```math
A^\nu=0
```

is the nilpotency index, and

```math
\text{longest directed-path length}=\nu-1.
```

We will record the rank profile

```math
\rho(A)=
\left(
\mathrm{rank}A,
\mathrm{rank}A^2,\ldots
\right)
```

until it reaches zero.

We will also record the singular values

```math
\sigma(A)=
\sqrt{\mathrm{spec}(A^\mathsf TA)}.
```

# 2. Simple-channel atlas

We first examine the $0/1$ sector: at most one realized channel in each direction between a given pair, which is the smallest finite sector of the full theory.

Let

```math
\varphi=\frac{1+\sqrt5}{2}.
```

The notation $d^+$ and $d^-$ denotes the multisets of out-degrees and in-degrees. The notation $L_u$ denotes the Laplacian of the underlying undirected graph, obtained by temporarily forgetting edge direction.

## Complete table through three nodes

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

# 3. The nontrivial three-node cases

## Outgoing fork

```math
1\to2,\qquad1\to3.
```

Its adjacency matrix is

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

whose eigenvalues are

```math
2,0,0.
```

Therefore,

```math
\sigma(A_{\mathrm{out}})=
(\sqrt2,0,0).
```

## Incoming fork

```math
1\to3,\qquad2\to3.
```

Its matrix is

```math
A_{\mathrm{in}}=
\begin{pmatrix}
0&0&1\\
0&0&1\\
0&0&0
\end{pmatrix}.
```

It has the same rank profile and singular values as the outgoing fork:

```math
\rho(A_{\mathrm{in}})=(1,0),
```

```math
\sigma(A_{\mathrm{in}})=
(\sqrt2,0,0).
```

So singular values alone cannot tell whether two channels converge or diverge.

The in- and out-degree multisets do distinguish them:

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

```math
1\to2\to3.
```

Its matrix is

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

Therefore,

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

```math
1\to2,\qquad2\to3,\qquad1\to3.
```

Its matrix is

```math
A_{\triangle}=
\begin{pmatrix}
0&1&1\\
0&0&1\\
0&0&0
\end{pmatrix}.
```

We again have

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

Thus the chain and transitive triangle have the same rank profile:

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

# 4. Reachability

Define the binary reachability matrix

```math
R_{ij}=
\begin{cases}
1,&\text{if a nonempty directed path exists from }i\text{ to }j,\\
0,&\text{otherwise}.
\end{cases}
```

For the chain,

```math
1\to2\to3,
```

we obtain

```math
R_{\mathrm{chain}}=
\begin{pmatrix}
0&1&1\\
0&0&1\\
0&0&0
\end{pmatrix}.
```

But this is exactly the adjacency matrix of the transitive triangle:

```math
R_{\mathrm{chain}}=A_{\triangle}.
```

Therefore,

```math
R_{\mathrm{chain}}=
R_{\triangle}.
```

The chain and transitive triangle have different immediate communication structures but identical eventual communication possibilities.

Both profiles must therefore be retained:

```math
A=\text{immediate channels}
```

and

```math
R=\text{eventual reachability}.
```

# 5. Parallel-channel sector

Now we avoid assuming that parallel edges are forbidden.

Let $a,b,c$ be positive integer channel multiplicities.

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

For

```math
1\xrightarrow{a}2\xrightarrow{b}3,
```

we have

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

# 6. First genuine collision

Consider these two weighted chains:

```math
G_1:
\quad
1\xrightarrow{a}2\xrightarrow{b}3,
```

```math
G_2:
\quad
1\xrightarrow{b}2\xrightarrow{a}3,
```

with $a\neq b$.

The directed weighted graphs are nonisomorphic. The source, middle, and target are structurally fixed, so an isomorphism cannot exchange the upstream and downstream multiplicities. Nevertheless, they share identical adjacency eigenvalues, singular values, degree multisets, and underlying weighted-Laplacian spectra, as well as the same path multiplicity $ab$.

Therefore, our initial spectral package cannot determine whether the larger channel multiplicity comes first or second.

---

# 7. A new operator forced by the collision

To recover directional placement, define for some fixed

```math
\tau>0,\qquad \tau\neq1,
```

the positive-semidefinite matrix

```math
Q_\tau(A)=
A^\mathsf TA+\tau AA^\mathsf T.
```

Here:

* $A^\mathsf TA$ compares incoming-channel profiles;
* $AA^\mathsf T$ compares outgoing-channel profiles;
* $\tau\neq1$ prevents the two roles from being weighted symmetrically.

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

Therefore, when

```math
a\neq b
\quad\text{and}\quad
\tau\neq1,
```

the determinants differ, and hence their spectra differ.

So:

```math
\mathrm{spec}(Q_\tau)
\text{ distinguishes the two weighted-chain orientations.}
```
