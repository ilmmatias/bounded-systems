# 1. A finite regular forcing system

The preceding two findings combine into a finite direct selector for the
standalone gap kernel on the regular degree-coordinate stratum.

For an acyclic directed kernel $W$, define

```math
s_W=d_W^--d_W^+,
```

the antisymmetric residual is

```math
R_W(x,y)
=
W(x,y)-W(y,x)-s_W(y)+s_W(x),
```

and

```math
P_W^-(x)
=
\int W(y,x)d_W^-(y)\,d\mu(y).
```

The incoming rooted composition defect is

```math
C_W^-(x)
=
6P_W^-(x)-\bigl(d_W^-(x)\bigr)^2.
```

Define the outgoing quantities dually by

```math
P_W^+(x)
=
\int W(x,y)d_W^+(y)\,d\mu(y),
```

and

```math
C_W^+(x)
=
6P_W^+(x)-\bigl(d_W^+(x)\bigr)^2.
```

# 2. The forcing constraints

The four forcing conditions are

```math
\begin{aligned}
\mathcal G_{\mathrm{gap}}(W)&=0,\\
\int \bigl(C_W^-(x)\bigr)^2\,d\mu(x)&=0,\\
\int \bigl(C_W^+(x)\bigr)^2\,d\mu(x)&=0,\\
\int W(x,y)\,d\mu(x)d\mu(y)&=\frac16.
\end{aligned}
```

The first is the cyclic Gram constraint of `findings-94.md`. The middle two
are squares of rooted quantum-DAG expressions. The last fixes the overall
scale.

## Theorem 1. Regular finite forcing

Suppose $W$ is an acyclic directed kernel satisfying the four constraints
above, and suppose the distribution of $s_W$ has connected essential support.
Equivalently, after monotone rearrangement, the coordinate quantile is
continuous and nondecreasing.

Then $W$ is weakly isomorphic to

```math
A(x,y)=(y-x)_+.
```

The connected-support hypothesis is used only against jump discontinuities of
the monotone quantile: no regularity assumption is needed for the cyclic
reconstruction $W=(s(y)-s(x))_+$, and the two-sided composition identities
already eliminate flat quantile intervals and singular continuous growth.
Whether the four identities themselves exclude signed-degree distributions
with disconnected essential support is open.

## Proof

The Gram constraint and acyclicity imply

```math
W(x,y)=\bigl(s_W(y)-s_W(x)\bigr)_+.
```

Rearrange the probability space so that $s_W=q(u)$ with $q$ continuous and
nondecreasing. The two rooted defects become

```math
6G(u)=F(u)^2,
\qquad
6\overline G(u)=\overline F(u)^2.
```

Theorem 2 of `findings-95.md` implies that $q$ is affine. Since $q=s_W$ has
mean zero and the edge density is $1/6$, the affine map is $q(u)=u-1/2$.
Substitution gives $W(u,v)=(v-u)_+$.

# 3. Realization by ordinary finite DAG densities

Each constraint is a finite linear combination of ordinary simple-DAG
homomorphism densities.

The function $d_W^-$ is represented by one incoming rooted edge. The
function $P_W^-$ is represented by a rooted two-edge path ending at the root.
Products such as $(d_W^-)^2$ and $(C_W^-)^2$ are formed by gluing
independent rooted copies at the root. Distinct copies use distinct sampled
leaves, so no parallel edge probe is required.

The gap Gram defect is realized by the simple-pattern expansion described in
`findings-94.md` and `findings-93.md`.

Consequently, the regular selector is finite in the ordinary central-DAG
pattern algebra.

# 4. Terminal selection consequence

Let $\mathcal E_{\mathrm{reg}}$ be the sum of the four nonnegative forcing
defects, with the edge-density term squared. A terminal Gibbs weight

```math
w_N(K)
=
\exp\left[-\beta_N\mathcal E_{\mathrm{reg}}(K)\right]
```

selects the gap sector among endpoint sequences whose limiting signed degree
coordinate remains in the regular stratum, provided the inverse temperature
dominates the endpoint entropy as in `findings-68.md`.

The resulting harmonic up law is then reconstructed from the selected
boundary profile; it is not appended as an independent transition rule.

Exact symbolic calculations reproduce the target identities, exclude the
finite atomic competitors, and confirm the full forcing chain on affine and
non-affine polynomial quantile families.
