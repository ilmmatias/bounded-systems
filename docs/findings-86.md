# 1. Uncolored observables inherited from the payload

The absolute completion of `findings-85.md` makes every payload part an
intrinsic degree class. Let

```math
\chi_{L_i}(x)
```

be the polynomial indicator of the degree pair belonging to $L_i$. For any
decorated finite DAG $F$ whose vertex $a$ is assigned to a payload part
$L_{i_a}$, define

```math
\begin{aligned}
t_{\mathrm{pay}}(F)
={}&
\int
\prod_a\chi_{L_{i_a}}(x_a)\\
&\times
\prod_{a\to b\in E(F)}
\Gamma(x_a,x_b)
\prod_a d\mu(x_a).
\end{aligned}
```

This is a finite ordinary quantum-DAG density. Label forgetting and the
homomorphism-to-induced change of basis express it through finitely many
uncolored induced-DAG frequencies.

The primitive order blocks, their rooted degree coordinates, the two-step
path volume, and the shortcut Gram defect of `findings-83.md` are therefore
graph-intrinsic observables of one absolutely selected uncolored sector.

# 2. Recovery of the three continuum coordinates

Normalize each payload block by the mass of its target part. For $x\in L_0$,
the outgoing degree into $L_1$ is

```math
r_{01}(x)=1-x.
```

For $y\in L_1$, the incoming degree from $L_0$ and outgoing degree into
$L_2$ are

```math
c_{01}(y)=y,
\qquad
r_{12}(y)=1-y.
```

For $z\in L_2$, the incoming degree from $L_1$ is

```math
c_{12}(z)=z.
```

Hence all three coordinates are recovered from rooted relational data. The
middle identity

```math
c_{01}(y)+r_{12}(y)=1
```

aligns the two adjacent order kernels, so the coordinates are not
independently rearrangeable after the forcing constraints are imposed.

The auxiliary completion changes the total degrees used to identify the finite
parts, but it does not alter these normalized internal degree functions. Total
completed degrees identify the finite payload part, after which normalized
payload degrees recover the continuum coordinate.

# 3. Graph-intrinsic route geometry

Let $P_{02}(x,z)$ be the complete-space density of two-step paths from
$x\in L_0$ to $z\in L_2$ through the recovered middle part. Since
$\mu(L_1)=1/36$,

```math
P_{02}(x,z)
=
\frac1{36}(z-x)_+.
```

The selected shortcut block is therefore

```math
\Gamma_{02}(x,z)
=
36P_{02}(x,z).
```

The directed interval separation is obtained from a finite compositional
relation inside the uncolored sector. The function $(z-x)_+$ is not supplied
as an unrelated transition law after the two primitive order blocks and their
shared coordinate have been selected.

The operator identity is rectangular:

```math
K_{01}\circ K_{12}=A_{02}.
```

The standalone identity $K^2=A$ of `findings-82.md` acts on one probability
space, whereas the completion contains three coordinate copies linked by
forced block relations, so repeated powers $A^\ell$ are not directed paths of
the finite completed architecture.

Exact normalization converts complete-space path densities into
payload-normalized path densities and leaves the shortcut relation unchanged
after completion.

# 4. Stable finite-pattern coefficients

The completed sector is extremal and dissociated. The general support
decomposition of `findings-53.md` through `findings-56.md` therefore applies
to every uncolored finite pattern observable of the completion.

For each finite observable, the principal support order determines its
normalization and logarithmic relaxation rate. Connected principal supports
yield Gaussian OU fields, while disconnected supports yield the corresponding
Wick products. The coefficients are graph-intrinsic because the finite
completion is now selected without decorations.

The stable process laws therefore hold for every uncolored finite pattern
observable of the completion. Presence of the entire standalone route
hierarchy of `findings-80.md` as a literal path hierarchy of the completed
architecture is a separate question.

# 5. Harmonic law selected by the finite relational model

Let $\mathcal E_{\mathrm{comp}}$ be any nonnegative finite forcing energy
for the completed sector. At horizon $N$, assign terminal weight

```math
w_N(K)
=
\exp\left[-\lambda_N\mathcal E_{\mathrm{comp},N}(K)\right].
```

If

```math
\frac{\lambda_N}{N^2}\longrightarrow\infty,
```

then the endpoint law concentrates projectively on the completed extremal
sector by `findings-67.md` and the corrected extremal theorem of
`findings-68.md`. The normalized backward route counts converge to its
positive harmonic function, and the finite-horizon up transitions converge to
its coherent growth law.

The selected law contains the primitive order blocks, the route-derived
shortcut probability, the continuum coordinate recovered from rooted degrees,
and the stable finite-pattern fluctuation fields as intrinsic conditional
observables.

The finite relational selector determines the forward transition kernel
through the selected boundary profile.

The selector acts on the completed multi-part architecture, and finite
forcibility of the one-population kernel $(y-x)_+$ remains a separate
problem.
