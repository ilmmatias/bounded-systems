# 1. Computational conclusions

The finite construction established, without Monte Carlo approximation, that:

* the DAG Bratteli incidence operator is explicitly computable;
* both terminal sectors define exact coherent measures;
* conditional graph-profile drift and covariance can be streamed exactly.

It also exposed the exhaustive bottleneck:

```math
|\mathfrak D_8|=20{,}286{,}025
```

is manageable for a terminal profile table, but the next full incidence level would be too large for routine iteration.

# 2. From the abstract configuration graph to an executable pipeline

Let $\mathfrak D_n$ be the set of non-isomorphic simple DAGs with $n$ vertices. For

```math
G\in\mathfrak D_n,
\qquad
H\in\mathfrak D_{n+1},
```

define the deletion multiplicity

```math
d(G,H)
=
\left|\{v\in V(H):H-v\cong G\}\right|.
```

Write $a(G)=|\mathrm{Aut}(G)|$.

For a fixed labeled realization of $G$, the number of labeled one-vertex extensions belonging to the class $H$ is

```math
e(G,H)
=
d(G,H)
\frac{a(G)}{a(H)}.
```

The computation built the sparse incidence operator

```math
B_n(G,H)=e(G,H).
```

The two consistency audits were checked for every emitted successor class:

```math
\sum_G d(G,H)=n+1,
```

and

```math
\sum_G \dim(G)e(G,H)=\dim(H),
\qquad
\dim(G)=\frac{n!}{a(G)}.
```

The first verifies deletion accounting; the second independently verifies the automorphism ratio and labeled-history interpretation.

# 3. Exhaustive DAG catalogs through eight vertices

The class counts used by the pipeline were

```math
1,
2,
6,
31,
302,
5984,
243668,
20286025
```

for orders

```math
n=1,2,3,4,5,6,7,8.
```

The eight-vertex level therefore contains

```math
20{,}286{,}025
```

non-isomorphic DAG classes.

The catalogs and profiles were generated and validated at every level. The profile pass reported a fixed eight-coordinate graph dictionary and exactly the expected number of records:

| order | classes | profile dimension |
|---:|---:|---:|
| 1 | 1 | 8 |
| 2 | 2 | 8 |
| 3 | 6 | 8 |
| 4 | 31 | 8 |
| 5 | 302 | 8 |
| 6 | 5,984 | 8 |
| 7 | 243,668 | 8 |
| 8 | 20,286,025 | 8 |

In the exact eight-node 2-WL computation from the preceding stage, one refinement round left only 509 collision classes containing 1,020 graphs, whereas stabilized refinement separated all 20,286,025 classes. The finite catalog is exact, although the first continuum pass uses only the smaller graph-profile projection.

# 4. Incidence volume and streaming necessity

The coefficient pass streamed the following incidence-row counts:

| predecessor level | predecessor states | incidence rows |
|---:|---:|---:|
| 1 | 1 | 2 |
| 2 | 2 | 10 |
| 3 | 6 | 80 |
| 4 | 31 | 1,209 |
| 5 | 302 | 32,348 |
| 6 | 5,984 | 1,625,762 |
| 7 | 243,668 | 158,645,769 |

At approximately 3.96 GB, the level-seven incidence file made a streaming implementation mandatory: retaining the complete incidence operator, all profiles, and all conditional moments simultaneously in memory would have been wasteful and eventually impossible.

The executable order was therefore:

1. build canonical catalogs;
2. stream one-node deletion incidence;
3. compute finite-horizon harmonic masses backward;
4. stream incidence again to accumulate conditional coefficients;
5. reduce the result to levelwise summaries.

# 5. Two terminal sectors

For a terminal level $N=8$, the finite-horizon route counts were computed for two endpoint conventions.

## Labeled terminal sector

The terminal weight was constant:

```math
w_N(H)=1.
```

The resulting endpoint law is proportional to

```math
\dim(H)=\frac{N!}{|\mathrm{Aut}(H)|},
```

which is the law induced by uniform labeled DAG counting.

The exact backward computation reported

```math
Z_{8,\mathrm{labeled}}=783{,}702{,}329{,}343.
```

## Uniform-class terminal sector

The terminal weight was

```math
w_N(H)=\frac1{\dim(H)}.
```

so every terminal isomorphism class receives equal endpoint mass.

The corresponding exact normalizer was

```math
Z_{8,\mathrm{class}}=817{,}932{,}528{,}000.
```

The two sectors were retained separately because isomorphism invariance alone does not distinguish equal class weights from weights induced by labeled realizations.

# 6. Finite coherent measures

For either terminal weight, define

```math
R_{N,N}(H)=w_N(H),
```

and recursively

```math
R_{n,N}(G)
=
\sum_H e(G,H)R_{n+1,N}(H).
```

The finite up transition is

```math
U_n^{N,w}(G,H)
=
\frac{e(G,H)R_{n+1,N}(H)}{R_{n,N}(G)}.
```

The level measure is

```math
\mu_n^{N,w}(G)
=
\frac{\dim(G)R_{n,N}(G)}{Z_{N,w}}.
```

Together with the canonical down transition

```math
D_n(H,G)=\frac{d(G,H)}{n+1},
```

The pipeline checked the exact intertwining identity

```math
\mu_n^{N,w}(G)U_n^{N,w}(G,H)
=
\mu_{n+1}^{N,w}(H)D_n(H,G).
```

The identity was verified in exact arithmetic for both terminal sectors.

# 7. Harmonic masses and generated files

The backward mass pass completed with status `PASS` at every level in both sectors. State counts were

```math
1,
2,
6,
31,
302,
5984,
243668,
20286025.
```

The largest emitted files were the level-eight mass and weight tables: each mass table was about 1.06 GB and each weight table about 415 MB. Their size reflects the number of terminal classes, not an approximation or sampling step.

The pass was run with

```text
EMIT_UP=0
```

in both sectors. The emitted masses and incidence records fully determined the transition law; a complete up-transition table would only duplicate a very large sparse object.

# 8. Finite graph profiles

For the first configuration pass, the graph-level dictionary was the normalized eight-coordinate profile motivated in `findings-46.md`, providing a finite cylindrical projection

```math
x_n(G)\in\mathbb R^8
```

on which one-node extension increments can be measured.

The profile files reached approximately:

| level | profile-file size |
|---:|---:|
| 6 | 0.90 MB |
| 7 | 38.5 MB |
| 8 | 2.59 GB |

The eight-coordinate pass did not treat its dictionary as the final profile space; it supplied a fixed finite projection within the projective hierarchy.

# 9. Streaming conditional coefficients

For every incidence edge

```math
G\to H,
```

The scaled profile increment was

```math
F_n(G,H)
=
(n+1)\bigl(x_{n+1}(H)-x_n(G)\bigr).
```

With transition weight

```math
u(G,H)=U_n^{N,w}(G,H),
```

The pass accumulated, per predecessor class,

```math
b_n(G)=\sum_Hu(G,H)F_n(G,H),
```

and

```math
a_n(G)
=
\sum_Hu(G,H)F_n(G,H)F_n(G,H)^\mathsf T
-b_n(G)b_n(G)^\mathsf T.
```

The full third tensor was disabled in the large run:

```text
EMIT_THIRD=0
```

because the immediate target was the fixed profile and linearized fluctuation operator. The omission was computational, not conceptual; the third cumulant remains defined by the finite transition law.

Both labeled and class-sector coefficient passes completed through predecessor level seven with status `PASS`.

# 10. Levelwise hydrodynamic summaries

The summary pass computed:

* the coherent mean graph profile at levels one through eight;
* profile moments through predecessor level seven;
* levelwise mean scaled increments;
* levelwise covariance summaries;
* a compact machine-readable `moments.json` for each sector.

Every mean and moment pass reported `PASS`.

The calculation remained finite-horizon: the level-eight terminal law influences all earlier levels, so the output could not yet be interpreted as an established infinite harmonic boundary sector.

# 11. Horizon-convergence sweep

To distinguish terminal-boundary effects from bulk behavior, the same analysis was repeated with terminal horizons

```math
N=4,5,6,7,8.
```

The comparison yielded 25 rows per sector: five profile or coefficient summaries at each of five horizons, providing an explicit finite-horizon convergence diagnostic for the configuration process.

The sweep served three purposes:

1. verify that the finite calculations were mutually consistent;
2. identify which coordinates were still dominated by the terminal level;
3. determine whether extrapolation to much larger $N$ required exhaustive incidence or a sampler.

Growth from 243,668 classes at level seven to 20,286,025 at level eight showed that further exact incidence enumeration would be inefficient.
