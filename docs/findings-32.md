# 1. Relative nerve of tail collapse inside Martin collapse

Fix a Martin fiber

```math
F_h=\{\text{histories with Martin shadow }h\}.
```

Partition it into eventual-tail classes:

```math
F_h=\coprod_{\tau\in\overline F_h}T_\tau,
```

where

```math
\overline F_h=F_h/\!\sim_{\mathrm{tail}}.
```

Define two simplicial sets:

```math
K_h=E(F_h)
```

and

```math
A_h=\coprod_{\tau\in\overline F_h}E(T_\tau).
```

Here $K_h$ coherently identifies every history having Martin shadow $h$ and
$A_h$ identifies only histories already related by finite-prefix replacement.

Thus the pair

```math
(K_h,A_h)
```

isolates the genuinely asymptotic part of Martin collapse.

# 2. Relative homology theorem

Every $E(T_\tau)$ is contractible, and $K_h$ is contractible. Hence

```math
H_j(A_h;k)=0
\qquad(j\ge1),
```

while

```math
H_0(A_h;k)
\cong
k^{(\overline F_h)}.
```

Also,

```math
H_0(K_h;k)\cong k.
```

The map

```math
H_0(A_h;k)\longrightarrow H_0(K_h;k)
```

is coefficient summation:

```math
(c_\tau)_\tau\longmapsto\sum_\tau c_\tau.
```

The long exact sequence of the pair therefore gives

```math
H_1(K_h,A_h;k)
\cong
\widetilde{k}^{(\overline F_h)}
```

and

```math
H_n(K_h,A_h;k)=0
\qquad(n\neq1).
```

The pure asymptotic defect module has an exact homological realization:

```math
H_1(K_h,A_h;k)=
\left\lbrace (c_\tau): \text{finite support},\\ \sum_\tau c_\tau=0 \right\rbrace.
```

Globally,

```math
\mathfrak D_M/\mathfrak D_{\mathrm{tail}}
\cong
\bigoplus_h H_1(K_h,A_h;k).
```

# 3. No hidden higher syzygies inside one fiber

The same computation gives the vanishing

```math
H_n(K_h,A_h)=0
\qquad(n\ge2).
```

A Martin fiber containing many tail ends does not by size alone possess
higher-dimensional mixing homology.

The following examples illustrate this point.

## Diamond followed by one common tail

There is only one tail class:

```math
|\overline F_h|=1.
```

Consequently,

```math
H_1(K_h,A_h)=0.
```

All collapse is inherited from a finite route defect.

### Two genuinely different tails with one Martin shadow

If $|\overline F_h|=2$, then

```math
H_1(K_h,A_h)\cong k.
```

There is one independent asymptotic end difference.

### Complete layered mixing

There may be infinitely many tail classes. Then

```math
H_1(K_h,A_h)
\cong
\widetilde{k}^{(\overline F_h)}
```

is infinite-dimensional, but still

```math
H_n(K_h,A_h)=0
\qquad(n\ge2).
```

Thus large asymptotic multiplicity does not imply higher homological
complexity. Similarly, many route ambiguities need not produce higher route
syzygies.

# 4. Where higher structure can reside

If higher structure is not in the indiscrete equivalence relation of one fiber,
it must come from one of two sources:

1. the topology of the tail-end space and the Martin quotient;
2. the way the fibers vary and twist over different Martin directions.

The relevant object is the complete quotient map

```math
\bar\pi_t:Z_t\longrightarrow Y_t,
```

where

```math
Z_t=X_{\mathrm{pre}}/\!\sim_{\mathrm{tail}}
```

is the tail-end space and

```math
Y_t=Z_t/\!\sim_t^M
```

is the node Martin quotient.

Set-theoretically,

```math
\bar\pi_t^{-1}(h)=\overline F_h.
```

The new information is the variation of the fibers with $h$, beyond their
individual cardinalities.

# 5. The global Čech nerve

Assume for now that $Z_t$ and $Y_t$ carry suitable topologies and that

```math
\bar\pi_t:Z_t\to Y_t
```

is continuous.

Define the iterated fiber products

```math
Z_t^{[q]}=
\underbrace{
Z_t\times_{Y_t}\cdots\times_{Y_t}Z_t
}_{q+1\text{ factors}}.
```

In the first three degrees,

```math
Z_t^{[0]}=Z_t,
\qquad
Z_t^{[1]}=
\{(\tau_0,\tau_1):
\bar\pi_t(\tau_0)=\bar\pi_t(\tau_1)\},
```

and

```math
Z_t^{[2]}=
\{(\tau_0,\tau_1,\tau_2):
\bar\pi_t(\tau_0)=\bar\pi_t(\tau_1)=\bar\pi_t(\tau_2)\}.
```

Deleting one coordinate gives the face maps.

The resulting simplicial space

```math
Z_t^{[\bullet]}
```

is the Čech, or kernel-pair, nerve of the quotient map, built from these
iterated fiber products and their alternating face maps.

It remains fiberwise contractible, but globally its topology records how
collapse fibers fit together over $Y_t$.

# 6. The hidden-end sheaf

Let $\underline{k}_{Z_t}$ and $\underline{k}_{Y_t}$ denote constant sheaves.

Pulling a locally constant function back along $\bar\pi_t$ gives a natural map

```math
\underline{k}_{Y_t}
\longrightarrow
\bar\pi_{t*}\underline{k}_{Z_t}.
```

Define the quotient sheaf

```math
\mathscr Q_t=
\mathrm{coker}
\left(
\underline{k}_{Y_t}
\longrightarrow
\bar\pi_{t*}\underline{k}_{Z_t}
\right).
```

The resulting sheaf records hidden tail-end distinctions.

For a finite discrete fiber

```math
\overline F_h=\{\tau_1,\ldots,\tau_r\}
```

that varies locally immediately, the stalk is

```math
(\mathscr Q_t)_h
\cong
k^r/k(1,\ldots,1).
```

Its dimension is

```math
r-1.
```

The sheaf is dual to the zero-total defect module

```math
\widetilde{k}^{(\overline F_h)}.
```

The two descriptions differ as follows:

* the defect module uses signed end combinations with total zero;
* the quotient sheaf uses functions on hidden ends modulo functions constant
  across the fiber.

# 7. Monodromy: global structure with trivial individual fibers

Suppose every Martin fiber contains exactly $r$ tail ends locally.

Even though every fiber has the same simple defect space

```math
k^{r-1},
```

the hidden ends can be permuted when one moves around $Y_t$.

Then $\mathscr Q_t$ is not necessarily a trivial product sheaf. It can be a
nontrivial local system.

For $r=2$, exchanging the two hidden ends acts on

```math
k^2/k(1,1)
```

by multiplication by $-1$.

Thus two quotient systems can have:

* identical fiber cardinalities;
* identical fiberwise relative homology;
* different global twisting.

The first higher-level information absent from the isolated modules is

```math
\widetilde{k}^{(\overline F_h)}.
```

The topology lies in the variation of fibers, not within an individual fiber.

# 8. Derived pushforwards

More generally, retain the derived sheaves

```math
R^q\bar\pi_{t*}\underline{k}_{Z_t}.
```

Informally, the derived sheaves record the following data:

* $R^0\bar\pi_{t*}\underline{k}$ records locally constant data along inverse
  images;
* higher $R^q$ record higher cohomological information that survives within
  those inverse images.

Under standard sheaf-theoretic hypotheses, the quotient map has a Leray
spectral sequence

```math
E_2^{p,q}=
H^p
\left(
Y_t;
R^q\bar\pi_{t*}\underline{k}
\right)
\Longrightarrow
H^{p+q}(Z_t;k).
```

The index $q$ records cohomology inside collapse fibers, while $p$ records the
global organization over Martin directions.

# 9. The common zero-dimensional case

Graph prefix boundaries and spectra of cylinder Boolean algebras are frequently
zero-dimensional.

If the relevant fibers are zero-dimensional compact spaces and the chosen
cohomology theory has no positive-degree fiber cohomology, then

```math
R^q\bar\pi_{t*}\underline{k}=0
\qquad(q>0).
```

In that regime the Leray system has only the $q=0$ row.

There is still potentially nontrivial information, but it lies in

```math
H^p(Y_t;\mathscr Q_t),
```

not in higher homology of one Martin fiber.

Even when every fiber is totally disconnected, the following remain possible:

* the fibers can vary nontrivially;
* their hidden-end spaces can have monodromy;
* the quotient $Y_t$ can have nontrivial global topology;
* the sheaf $\mathscr Q_t$ can possess nonzero cohomology.

# 10. A completely unconditional observable system

The preceding topological construction requires the Martin quotient to be
sufficiently well behaved.

The bounded system definition alone does not guarantee Hausdorff quotient
spaces, local compactness, local triviality, properness, or the existence of
applicable sheaf base-change theorems.

There is, however, a canonical set-theoretic replacement.

For every finite node set

```math
F\subseteq V,
```

define the finite-observation map

```math
\pi_{t,F}(\tau)=
\bigl(h_\tau(v)\bigr)_{v\in F}.
```

Two tail ends are $F$-equivalent when

```math
\tau\sim_F\sigma
\iff
h_\tau(v)=h_\sigma(v)
\quad\forall v\in F.
```

If

```math
F\subseteq F',
```

it follows that

```math
\sim_{F'}
\subseteq
\sim_F.
```

More node observables produce a finer partition.

The complete Martin relation is

```math
\sim_t^M=
\bigcap_{F\subseteq V,\;F\text{ finite}}
\sim_F.
```

Two functions on $V$ agree exactly when they agree on every finite subset,
indeed on every singleton.

# 11. The inverse system of finite observations

Define $Y_{t,F}$ by

```math
Y_{t,F}=Z_t/\!\sim_F.
```

Whenever

```math
F\subseteq F',
```

there is a natural forgetting map

```math
Y_{t,F'}
\longrightarrow
Y_{t,F}.
```

The finite-observation quotients form an inverse system:

```math
{Y_{t,F}}_{F\Subset V}.
```

The full Martin quotient maps into its inverse limit:

```math
Y_t
\longrightarrow
\varprojlim_{F\Subset V}Y_{t,F}.
```

It is injective because the node coordinates separate distinct Martin functions.

The pro-object remains meaningful even when the quotient topology is ill
behaved.

It records exactly how much node information is needed to distinguish
asymptotic ends.

# 12. Observable defect filtration

Define $\mathfrak D_F$ by

```math
\mathfrak D_F=
\mathrm{span}
\{
\delta_\tau-\delta_\sigma:
\tau\sim_F\sigma
\}.
```

For

```math
F\subseteq F',
```

the relation becomes finer, so

```math
\mathfrak D_{F'}
\subseteq
\mathfrak D_F.
```

The quotient

```math
\mathfrak D_F/\mathfrak D_{F'}
```

consists of distinctions that are invisible to every observation in $F$ and
become visible after the additional coordinates in $F'\setminus F$ are included.

The kernels form a decreasing finite-observable filtration:

```math
\mathfrak D_\varnothing
\supseteq
\mathfrak D_F
\supseteq
\mathfrak D_{F'}
\supseteq
\mathfrak D_M.
```

At $F=\varnothing$, all tail ends are identified.

At the full Martin level, only ends with identical complete Green-ratio profiles
remain identified.

No arbitrary metric or external resolution scale is introduced; the index is
the directed set of finite subsets of the existing node set.

# 13. Relative-homology interpretation at finite observation

For a finite observation set $F$, partition the tail ends according to their
$F$-profiles.

For one $F$-fiber $B$, subdivide it into the finer $F'$-fibers

```math
B=\coprod_{\lambda\in\Lambda}B_\lambda.
```

Exactly the same relative-nerve calculation gives

```math
H_1
\left(
E(B),
\coprod_{\lambda\in\Lambda}E(B_\lambda);
k
\right)
\cong
\widetilde{k}^{(\Lambda)},
```

and all other relative homology vanishes.

Thus each refinement step creates only first-order distinctions.

Higher complexity arises through the organization of many refinement steps, not
through one equivalence-relation fiber.
