# 1. Serial diamonds: ambiguity without syzygies

Consider $k$ binary ambiguity gadgets arranged consecutively:

```math
v_0
\overset{p_1^0,p_1^1}{\longrightarrow}
v_1
\overset{p_2^0,p_2^1}{\longrightarrow}
\cdots
\overset{p_k^0,p_k^1}{\longrightarrow}
v_k,
```

with no cross-links between gadgets.

A complete route is determined by a bit string

```math
\epsilon=(\epsilon_1,\ldots,\epsilon_k)\in\{0,1\}^k,
```

so there are $2^k$ routes from $v_0$ to $v_k$.

Put

```math
d_i=p_i^1-p_i^0.
```

For $S\subseteq\{1,\ldots,k\}$, replacing each factor at position $i\in S$ by
$d_i$ yields an $|S|$-fold alternating route box; modulo one higher power of
$I$, ordinary route choices outside $S$ do not matter. The resulting corner has
dimension

```math
\dim e_{v_k}\left(I^m/I^{m+1}\right)e_{v_0}=
\binom{k}{m}.
```

The whole route corner decomposes as

```math
2^k=
\sum_{m=0}^{k}\binom{k}{m},
```

where $m=0$ is the one-dimensional reachability direction; $m=1$ consists of
individual diamond effects; $m=2$ consists of pairwise alternating rectangles;
$m=3$ consists of alternating cubes; and so on.

The orthogonal route space has a Boolean, or Walsh, decomposition.

For this family, there are no higher dependencies among these boxes: each
product corresponds uniquely to its selected ambiguity positions. Hence

```math
\mathrm{gr}_I A
\cong
T_B(I/I^2)
```

on the relevant corners, so

```math
H_{n,m}^{\mathrm{rt}}=0
\qquad(n\ge2).
```

There is higher-order ambiguity, but no higher syzygy.

# 2. The $2\times2$ directed grid

Take the Hasse-directed square grid from $(0,0)$ to $(2,2)$, with horizontal
and vertical edges increasing coordinates.

There are

```math
\binom{4}{2}=6
```

monotone routes between the two extreme nodes.

The full endpoint route corner has dimension six. Its route ideal has
dimension five:

```math
\dim e_{(2,2)}Ie_{(0,0)}=5.
```

Direct calculation gives

```math
\dim e_{(2,2)}I^2e_{(0,0)}=1,
\qquad
I^3=0
```

in that corner. The graded dimensions are therefore

```math
\begin{aligned}
\dim C_0&=1,\\
\dim C_1&=4,\\
\dim C_2&=1.
\end{aligned}
```

Composing two compatible square ambiguities yields the unique second-order
direction, an alternating four-route rectangle.

Moreover, the relevant multiplication map

```math
C_1\otimes_B C_1\longrightarrow C_2
```

is an isomorphism. Hence

```math
H_{2,2}^{\mathrm{rt}}=0.
```

The second-order box is the product of two first-order ambiguities, not a
syzygy.

# 3. The Boolean rank-three interval and the hexagonal syzygy

Now consider the Boolean lattice $B_3$, directed by adding one element at a
time.

Between

```math
\varnothing
\quad\text{and}\quad
\{1,2,3\},
```

the six saturated paths are the six permutations:

```math
123,\ 132,\ 312,\ 321,\ 231,\ 213.
```

Adjacent paths exchange the order of adding two elements; the six local
diamond moves form a hexagon:

```math
123\to132\to312\to321\to231\to213\to123.
```

Let the following notation be fixed:

```math
\begin{aligned}
r_1&=132-123,\\
r_2&=312-132,\\
r_3&=321-312,\\
r_4&=231-321,\\
r_5&=213-231,\\
r_6&=123-213.
\end{aligned}
```

Summing these differences gives

```math
r_1+r_2+r_3+r_4+r_5+r_6=0.
```

The hexagonal sum is a relation among six contextualized local diamond
relations.

But in $B_3$,

```math
I^2=0.
```

There is not enough rank to concatenate two nontrivial ambiguous intervals:
each ambiguity requires at least two rank steps, while the whole interval has
only three.

Therefore the previous bar construction has

```math
C_2=0
```

and hence no degree-two chains capable of recording the hexagonal dependency.

The hexagon is a syzygy among local relation generators, but it is not a
product relation in the $I$-adic associated graded.

This disproves the stronger interpretation of $H^{\mathrm{rt}}_{n,m}$.

# 4. Scope of the previous complex

The corrected interpretation is:

```math
C_m=I^m/I^{m+1}
```

measures actual $m$-fold multiplicative route ambiguity.

Meanwhile,

```math
H_{n,m}^{\mathrm{rt}}
```

measures dependencies among factorizations of those multiplicative ambiguity
elements.

It does not necessarily measure dependencies among a minimal collection of
local route-identification laws.

The ordinary reduced bar construction is standard for an augmented algebra and
its derived tensor products, but finding a coherent presentation by generators,
relations, and relations among relations is a different question.

# 5. The local relation module

Let $J\subset A$ be the positive-path ideal, and let

```math
I=\ker(A\to B)
```

be the parallel-route ideal. The local relation module is

```math
R_2=
I/(JI+IJ).
```

The quotient removes relations obtained only by adding nonempty path context
before or after a smaller relation.

Thus $R_2$ records the locally irreducible route-identification laws.

For example, two parallel primitive channels give one element of $R_2$; an
elementary diamond gives one element; a shortcut versus a composite route
gives one element; and a larger diamond obtained by prefixing and suffixing a
smaller diamond gives no new element.

For $B_3$,

```math
\dim R_2=6,
```

one generator for each rank-two Boolean diamond. Their transported images
satisfy the one hexagonal syzygy above.

The presentation of an incidence algebra as a path algebra uses the ideal
identifying parallel paths, often called the parallel ideal.

# 6. Initial terms of the corrected resolution

Let $D=\bigoplus_{v\in V}\mathbb K e_v$ be the node diagonal, and let

```math
M=J/J^2
```

be the primitive-channel bimodule.

The reachability algebra is

```math
B=A/I.
```

The first terms of a route-presentation bimodule resolution are

```math
P_0=B\otimes_D B,
\qquad
P_1=B\otimes_D M\otimes_D B,
\qquad
P_2=B\otimes_D R_2\otimes_D B.
```

The multiplication differential $d_0:P_0\to B$ is defined by

```math
d_0(b_L\otimes b_R)=b_Lb_R.
```

## Channel differential

For a primitive edge $e$, let $\bar e$ denote its reachability image in $B$.
Define

```math
d_1(b_L\otimes e\otimes b_R)=
b_L\bar e\otimes b_R-
b_L\otimes\bar e b_R.
```

It follows that

```math
d_0d_1=0.
```

# 7. The noncommutative path derivative

For a path

```math
p=e_n\cdots e_1,
```

define its path derivative

```math
\partial p=
\sum_{j=1}^{n}
\overline{e_n\cdots e_{j+1}}
\otimes e_j\otimes
\overline{e_{j-1}\cdots e_1}.
```

Empty prefixes or suffixes are interpreted as their corresponding node
identities.

The formula marks every cut around one primitive channel.

It satisfies the Leibniz rule

```math
\partial(qp)=
\bar q\,\partial p
+
(\partial q)\,\bar p.
```

For a route relation

```math
r=\sum_pc_pp\in I,
```

define

```math
d_2(1\otimes[r]\otimes1)=
\sum_pc_p\,\partial p.
```

Extend $B$-bilinearly.

Because every path in $r$ has the same reachability image,

```math
d_1d_2=0.
```

The first part of the resulting complex is

```math
P_2\xrightarrow{d_2}P_1\xrightarrow{d_1}P_0\xrightarrow{d_0}B\to0.
```

It records local relations together with their left and right reachability
contexts.

# 8. Third-level generators

Set $Z_2$ by

```math
Z_2=\ker d_2.
```

Elements of $Z_2$ are identities among contextualized local route relations.

For $B_3$, the hexagonal sum gives an element of $Z_2$.

To remove identities obtained merely by surrounding a smaller identity with
ordinary reachability context, take the local third-generator module
schematically as

```math
R_3=
Z_2/
\left(
\mathrm{rad}(B)Z_2
+
Z_2\mathrm{rad}(B)
\right),
```

where $\mathrm{rad}(B)$ is the strict-reachability ideal.

It follows that

```math
P_3=B\otimes_D R_3\otimes_D B.
```

A differential

```math
d_3:P_3\to P_2
```

chooses representatives of the local syzygies.

The next relation module is defined by

```math
R_4=
\text{local generators of }\ker d_3.
```

Higher stages are obtained recursively from local generators of the preceding
kernel.

For finite systems, or finite ordinal-rank bands, this can be implemented
through ordinary linear algebra and projective covers. Recent work gives
practical algorithms for minimal projective resolutions of finite-dimensional
incidence algebras.

# 9. Boolean lattices and permutohedral coherence

For the Boolean interval of rank $d$:

* complete routes are permutations of $d$ elements;
* elementary diamond relations are adjacent exchanges;
* independent exchanges produce square coherence diagrams;
* overlapping exchanges produce hexagonal braid diagrams.

Independent and overlapping exchanges therefore contribute square and
hexagonal two-dimensional coherence cells, and the $B_3$ hexagon is the first
permutohedral coherence cell.

For larger $d$, one obtains:

```math
\begin{array}{c|l}
\text{dimension}&\text{meaning}\\
\hline
0&\text{complete routes/permutations}\\
1&\text{elementary diamond replacements}\\
2&\text{square and hexagonal coherences}\\
3&\text{coherences among those coherences}\\
\vdots&\vdots
\end{array}
```

The full permutohedron is a convex polytope with a contractible cellular
complex, so its hierarchy of coherence cells can be rich even though its final
reduced homology vanishes.

The distinction is that vanishing homology does not imply the absence of
higher coherence.

It can mean that every ambiguity loop is coherently filled at a higher
dimension.

Higher-dimensional rewriting and polygraphic resolutions were developed to
encode generators, relations, and higher syzygies in this way.

# 10. Canonical versus minimal

A completely canonical construction can take:

* every pair of parallel paths as a relation;
* every compatible diagram among them as a higher relation;
* every higher coherence after that.

But this “all relations” resolution is enormous and largely contractible by
construction.

A small or minimal resolution selects:

* elementary diamonds;
* independent shortcut relations;
* a basis of hexagonal or cubical coherences;
* higher critical branchings.

That selection is generally not unique.

Different convergent presentations can yield different cell bases while
resolving the same quotient; the meaningful invariant is therefore the
resulting chain-homotopy or derived object, not the selected generators'
names. Squier and polygraphic constructions formalize this distinction between
a presentation and its coherent higher completion.

# 11. Literature relation

The presentation used in section 5, an incidence algebra as a path algebra
modulo the differences of parallel paths, is that of C. Cibils, *Cohomology of
incidence algebras and simplicial complexes*, Journal of Pure and Applied
Algebra 56 (1989), 221-232, established there for a finite poset. The module
$R_2=I/(JI+IJ)$ of section 5 has the form of the module whose dual is identified
with the degree-two Ext group between simple modules in B. Keller, *A-infinity
algebras in representation theory*, in Representations of Algebras, Volume I,
Beijing Normal University Press, 2002, 74-86, where the quiver is finite, the
ground ring is a field, and the relation ideal is admissible; sections 6 to 8
use $R_2$ and the successive modules $R_3,R_4,\ldots$ as generator modules of a
bimodule resolution over the node diagonal, with no field and no finiteness of
the node set. The practical algorithms referred to in section 8 are those of
V. Bekkert, J. W. MacQuarrie, and J. Marques, *Projective resolutions of simple
modules and Hochschild cohomology for incidence algebras*, Linear Algebra and
its Applications 740 (2026), 139-150, arXiv:2411.07910, which assume a
finite-dimensional incidence algebra over a field and therefore apply to the
finite systems and finite ordinal-rank bands named there.

The distinction drawn in section 10 between a presentation and its coherent
higher completion is the one formalized in C. C. Squier, F. Otto, and
Y. Kobayashi, *A finiteness condition for rewriting systems*, Theoretical
Computer Science 131 (1994), 271-294, for monoids, where finite derivation type
is a property of a finite presentation, and in Y. Guiraud and P. Malbos,
*Higher-dimensional normalisation strategies for acyclicity*, Advances in
Mathematics 231 (2012), 2294-2351, arXiv:1011.0558, for small categories
equipped with a convergent presentation, whose acyclic polygraphs carry
generators, relations, and higher syzygies. Both require the presentation to be
supplied, and the polygraphic resolutions of the second are built from a chosen
convergent rewriting system, while the route relations of section 5 are indexed
by all pairs of parallel paths and section 10 records that the selection of a
small basis among them is not unique. The permutohedral cells of section 9 occur
in Guiraud and Malbos as cells of such a polygraph, the order-three cell being
the braid or Yang-Baxter cell; section 3 obtains its hexagon from the six
adjacent exchanges among the saturated chains of $B_3$.
