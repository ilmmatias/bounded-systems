# 1. From the abstract configuration graph to an executable pipeline

Let

$$
\mathfrak D_n
$$

be the set of non-isomorphic simple DAGs with $n$ vertices. For

$$
G\in\mathfrak D_n,
\qquad
H\in\mathfrak D_{n+1},
$$

define the deletion multiplicity

$$
d(G,H)
=
\#\{v\in V(H):H-v\cong G\}.
$$

If

$$
a(G)=|\operatorname{Aut}(G)|,
$$

the number of labeled one-vertex extensions of a fixed labeled realization of $G$ that belong to the class $H$ is

$$
e(G,H)
=
d(G,H)
\frac{a(G)}{a(H)}.
$$

The computation built the sparse incidence operator

$$
B_n(G,H)=e(G,H).
$$

The two fundamental audits were checked for every emitted successor class:

$$
\sum_G d(G,H)=n+1,
$$

and

$$
\sum_G \dim(G)e(G,H)=\dim(H),
\qquad
\dim(G)=\frac{n!}{a(G)}.
$$

The first verifies deletion accounting. The second independently verifies the automorphism ratio and the labeled-history interpretation.

# 2. Exhaustive DAG catalogs through eight vertices

The canonical class counts used by the pipeline were

$$
1,
2,
6,
31,
302,
5984,
243668,
20286025
$$

for orders

$$
n=1,2,3,4,5,6,7,8.
$$

The eight-vertex level therefore contains

$$
20{,}286{,}025
$$

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

The exact eight-node 2-WL computation from the preceding stage remains relevant here: one refinement round left only 509 collision classes containing 1,020 graphs, while stabilized refinement separated all 20,286,025 classes. Thus the finite catalog is exact even though the first continuum pass uses only the smaller graph-profile projection.

# 3. Incidence volume and streaming necessity

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

The level-seven incidence file was approximately 3.96 GB. This made a streaming implementation mandatory: retaining the complete incidence operator, all profiles, and all conditional moments simultaneously in memory would have been wasteful and eventually impossible.

The executable order was therefore:

1. build canonical catalogs;
2. stream one-node deletion incidence;
3. compute finite-horizon harmonic masses backward;
4. stream incidence again to accumulate conditional coefficients;
5. reduce the result to levelwise summaries.

# 4. Two canonical terminal sectors

For a terminal level $N=8$, the finite-horizon route counts were computed for two endpoint conventions.

## Labeled terminal sector

The terminal weight was constant:

$$
w_N(H)=1.
$$

Consequently the endpoint law is proportional to

$$
\dim(H)=\frac{N!}{|\operatorname{Aut}(H)|},
$$

which is the law induced by uniform labeled DAG counting.

The exact backward computation reported

$$
Z_{8,\mathrm{labeled}}=783{,}702{,}329{,}343.
$$

## Uniform-class terminal sector

The terminal weight was

$$
w_N(H)=\frac1{\dim(H)}.
$$

so every terminal isomorphism class receives equal endpoint mass.

The corresponding exact normalizer was

$$
Z_{8,\mathrm{class}}=817{,}932{,}528{,}000.
$$

These two sectors were retained separately because neither weighting is selected directly by A1–A5.

# 5. Exact finite coherent measures

For either terminal weight, define

$$
R_{N,N}(H)=w_N(H),
$$

and recursively

$$
R_{n,N}(G)
=
\sum_H e(G,H)R_{n+1,N}(H).
$$

The finite up transition is

$$
U_n^{N,w}(G,H)
=
\frac{e(G,H)R_{n+1,N}(H)}{R_{n,N}(G)}.
$$

The level measure is

$$
\mu_n^{N,w}(G)
=
\frac{\dim(G)R_{n,N}(G)}{Z_{N,w}}.
$$

Together with the canonical down transition

$$
D_n(H,G)=\frac{d(G,H)}{n+1},
$$

the pipeline checked the exact intertwining identity

$$
\mu_n^{N,w}(G)U_n^{N,w}(G,H)
=
\mu_{n+1}^{N,w}(H)D_n(H,G).
$$

This was verified in exact arithmetic for both terminal sectors.

# 6. Harmonic masses and generated files

For both sectors, the backward mass pass completed with status `PASS` at every level. The state counts were

$$
1,
2,
6,
31,
302,
5984,
243668,
20286025.
$$

The largest emitted files were the level-eight mass and weight tables. Each level-eight mass table was about 1.06 GB, and each level-eight weight table was about 415 MB. This size reflects the number of terminal classes, not an approximation or sampling step.

The pass was run with

```text
EMIT_UP=0
```

for both sectors. The transition law remained fully determined by the emitted masses and incidence records; writing the complete up-transition table would only have duplicated a very large sparse object.

# 7. Finite graph profiles

The graph-level dictionary used for this first configuration pass was the normalized eight-coordinate profile already motivated in `findings-46.md`. Its role is to provide a finite cylindrical projection

$$
x_n(G)\in\mathbb R^8
$$

on which one-node extension increments can be measured.

The profile files reached approximately:

| level | profile-file size |
|---:|---:|
| 6 | 0.90 MB |
| 7 | 38.5 MB |
| 8 | 2.59 GB |

This pass did not claim that eight coordinates are the final profile space. It supplied the first fixed finite dictionary in the projective hierarchy.

# 8. Streaming conditional coefficients

For every incidence edge

$$
G\to H,
$$

the scaled profile increment was

$$
F_n(G,H)
=
(n+1)\bigl(x_{n+1}(H)-x_n(G)\bigr).
$$

With transition weight

$$
u(G,H)=U_n^{N,w}(G,H),
$$

the pass accumulated, per predecessor class,

$$
b_n(G)=\sum_Hu(G,H)F_n(G,H),
$$

and

$$
a_n(G)
=
\sum_Hu(G,H)F_n(G,H)F_n(G,H)^\mathsf T
-b_n(G)b_n(G)^\mathsf T.
$$

The full third tensor was disabled in the large run:

```text
EMIT_THIRD=0
```

because the immediate target was the fixed profile and linearized fluctuation operator. The omission was computational, not conceptual; the third cumulant remains defined by the finite transition law.

Both labeled and class-sector coefficient passes completed through predecessor level seven with status `PASS`.

# 9. Levelwise hydrodynamic summaries

The summary pass computed:

* the coherent mean graph profile at levels one through eight;
* profile moments through predecessor level seven;
* levelwise mean scaled increments;
* levelwise covariance summaries;
* a compact machine-readable `moments.json` for each sector.

Every mean and moment pass reported `PASS`.

At this stage the calculation was still finite-horizon. The level-eight terminal law influences all earlier levels, so the output could not yet be interpreted as an established infinite harmonic boundary sector.

# 10. Horizon-convergence sweep

To distinguish terminal-boundary effects from bulk behavior, the same analysis was repeated with terminal horizons

$$
N=4,5,6,7,8.
$$

The comparison produced 25 rows per sector: five profile or coefficient summaries at each of five horizons. This was the first explicit finite-horizon convergence diagnostic for the configuration process.

The sweep served three purposes:

1. verify that the finite calculations were mutually consistent;
2. identify which coordinates were still dominated by the terminal level;
3. determine whether extrapolation to much larger $N$ required exhaustive incidence or a sampler.

The growth from 243,668 classes at level seven to 20,286,025 at level eight showed that further exact incidence enumeration was not the efficient route.

# 11. Computational conclusions

The finite construction established the following without Monte Carlo approximation:

$$
\text{the DAG Bratteli incidence operator is explicitly computable,}
$$

$$
\text{both canonical terminal sectors define exact coherent measures,}
$$

and

$$
\text{conditional graph-profile drift and covariance can be streamed exactly.}
$$

It also exposed the exhaustive bottleneck:

$$
|\mathfrak D_8|=20{,}286{,}025
$$

is manageable for a terminal profile table, but the next full incidence level would be too large for routine iteration.
