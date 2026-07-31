# 1. General stochastic ordered sectors

`findings-69.md` absolutely forces a stochastic source-sink sector. The rooted calculus of `findings-70.md` extends the result to any fixed finite number of ordered layers.

Fix $q\geq2$, positive masses $p_1,\ldots,p_q$, and block probabilities $w_{ij}$ for $i<j$, with

```math
w_{i,i+1}>0.
```

Write $\mu^{p,W}$ for the corresponding extremal stochastic ordered-DAG sector.

# 2. Intrinsic layer partition

For an extremal central sector $\xi$, choose a dissociated acyclic digraphon representation $\Gamma$, form the rooted path signature $S(x)$, and define

```math
q_0(\xi)
=
\int Q_{p,W}(S(x))\,dx.
```

If $q_0(\xi)=0$, the polynomials

```math
\ell_i(x)=L_i(S(x))
```

are almost-everywhere indicators of a measurable partition

```math
A_i=\{x:S(x)=s_i\}.
```

Define its class masses by

```math
m_i(\xi)=\int\ell_i(x)\,dx.
```

# 3. Orientation and block regularity

For all ordered pairs $(i,j)$, define the class-restricted edge density

```math
e_{ij}(\xi)
=
\int\!\!\int
\ell_i(x)\ell_j(y)\Gamma(x,y)
\,dx\,dy.
```

For $i<j$, define the row and column defects

```math
R_{ij}(\xi)
=
\int
\ell_i(x)
\left(
 \int\ell_j(y)\Gamma(x,y)\,dy
 -p_jw_{ij}
\right)^2dx,
```

and

```math
C_{ij}(\xi)
=
\int
\ell_j(y)
\left(
 \int\ell_i(x)\Gamma(x,y)\,dx
 -p_iw_{ij}
\right)^2dy.
```

Their vanishing makes the normalized row and column degrees in the $(i,j)$ block equal to $w_{ij}$.

Let $B_{ij}(\xi)$ be the raw directed $K_{2,2}$ density in that block:

```math
B_{ij}(\xi)
=
\int
\ell_i(x_1)\ell_i(x_2)
\ell_j(y_1)\ell_j(y_2)
\prod_{a,b=1}^2\Gamma(x_a,y_b)
\,dx_1dx_2dy_1dy_2.
```

The target value is

```math
p_i^2p_j^2w_{ij}^4.
```

# 4. Sector forcing energy

Define the nonnegative sector energy

```math
\begin{aligned}
\mathcal E_{p,W}(\xi)
={}&q_0(\xi)
+
\sum_i(m_i(\xi)-p_i)^2\\
&+
\sum_{i\geq j}e_{ij}(\xi)^2\\
&+
\sum_{i<j}
\left[
 R_{ij}(\xi)+C_{ij}(\xi)
 +
 \left(
  B_{ij}(\xi)-p_i^2p_j^2w_{ij}^4
 \right)^2
\right].
\end{aligned}
```

Every term is finite-pattern observable data. By the boundary polynomial lift of `findings-70.md`, the central functional

```math
\mathfrak E_{p,W}(\mu)
=
\int
\mathcal E_{p,W}(\xi)
\,d\nu_\mu(\xi)
```

is a finite linear combination of ordinary induced-DAG densities of $\mu$.

# 5. Block quasirandomness

## Proposition 1. Constant-block criterion

Suppose $A$ and $B$ have positive masses $a$ and $b$. Let

```math
K:A\times B\to[0,1]
```

have normalized row and column degree $r$. Then

```math
\int_{A^2\times B^2}
K(x_1,y_1)K(x_1,y_2)
K(x_2,y_1)K(x_2,y_2)
=
a^2b^2r^4
```

if and only if $K=r$ almost everywhere.

## Proof

Use normalized probability measures on $A$ and $B$. The constant functions form a singular pair of the Hilbert-Schmidt operator $T_K$ with singular value $r$. If $\sigma_1,\sigma_2,\ldots$ are its remaining singular values, the normalized four-edge density is

```math
r^4+
\sum_{k\geq1}\sigma_k^4.
```

Equality with $r^4$ is equivalent to the vanishing of every nonconstant singular mode.

# 6. Absolute forcing theorem

## Theorem 2. Absolute forcing of finite stochastic ordered sectors

Let $\mu$ be any central measure on the DAG branching graph. If

```math
\mathfrak E_{p,W}(\mu)=0,
```

then

```math
\mu=\mu^{p,W}.
```

Consequently, every stochastic ordered $q$-layer sector with positive layer masses and positive adjacent block probabilities is absolutely finitely forcible in the full central DAG boundary.

## Proof

The integrand $\mathcal E_{p,W}$ is nonnegative, so zero central energy makes it vanish in almost every extremal component $\xi$.

The path-signature term gives a measurable partition $A_1,\ldots,A_q$. The mass terms give $|A_i|=p_i$. The terms $e_{ij}=0$ for $i\geq j$ remove every within-layer and backward edge up to null sets.

For each forward block, $R_{ij}=C_{ij}=0$ gives constant normalized row and column degree $w_{ij}$. The four-edge term and Proposition 1 then force

```math
\Gamma(x,y)=w_{ij}
```

for almost every $(x,y)\in A_i\times A_j$. Thus the component is weakly isomorphic to the target ordered step digraphon. Almost every extremal component is the same, so the original central measure is $\mu^{p,W}$.

# 7. Pattern order

The proof is finite but not optimized for pattern size. A rooted path coordinate uses at most $q$ vertices. Each interpolation polynomial $L_i$ has degree $2(q-1)$ in those coordinates. Expanding all sector squares and replacing homomorphism densities by induced densities gives the crude bound

```math
16(q-1)^2+8
```

on the largest pattern order required by the displayed energy.

The two-layer construction of `findings-69.md` is much smaller because its partition is detected directly by in- and outdegrees. The present theorem prioritizes a uniform proof for arbitrary $q$, not minimal forcing complexity.

# 8. Structural interpretation

The selector has four independent tasks:

1. rooted path signatures create graph-intrinsic layer names;
2. mass constraints fix the size of each layer;
3. zero wrong-direction densities fix the ordered architecture;
4. block regularity and four-cycle equalities remove every nonconstant edge mode.

No transition kernel is postulated. Once the sector is selected, its coherent profile, harmonic function, and up transition follow from the projective reconstruction of `findings-59.md`.

For rational three- and four-layer targets, exact calculations give zero energy on arbitrary refinements of the target partition and positive four-cycle excess for nonconstant biregular perturbations.

# 9. Literature relation

The block equality is the bipartite quasirandomness mechanism used in graphon forcing. Lovasz and Szegedy describe finite forcing through quantum-graph identities and note the Lovasz-Sos theorem that every finite step graphon is finitely forcible. The present theorem is a direct directed-acyclic construction: rooted path signatures force the ordered partition, and blockwise singular-value equalities force its stochastic edge constants.

Reference:

- L. Lovasz and B. Szegedy, *Finitely forcible graphons*, Journal of Combinatorial Theory, Series B 101 (2011), 269-301, arXiv:0901.0929.
