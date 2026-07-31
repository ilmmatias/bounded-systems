# 1. Connected canonical support statistics

The support-pattern expansion gives exact finite-level covariance identities for every joint vertex-edge support pattern. The remaining question is whether those covariance limits arise from genuine process limits.

Connected support patterns admit a complete answer. Their canonical sums have Gaussian sequential limits in linear size, and the logarithmic-size transform is an Ornstein-Uhlenbeck process whose relaxation rate is half the number of supporting vertices.

Retain the independent vertex variables $(X_i)$ and pair variables $(Y_{ij})$. Let $P$ be a looped support pattern on $r$ vertices, with no isolated vertices. A single loop on one vertex is regarded as connected. For $r\geq2$, connectedness means that the ordinary edges of $P$ connect all supporting vertices; loops do not connect distinct vertices.

Let

```math
g_P\in L^2(\mathscr F_P)
```

be canonical in the sense that

```math
\mathbb E[g_P\mid\mathscr F_Q]=0
```

for every proper subpattern $Q\subsetneq P$, and assume that $g_P$ is invariant under $\operatorname{Aut}(P)$. Define the ordered embedding sum

```math
S_{n,P}(g_P)
=
\sum_{\psi:V(P)\hookrightarrow[n]}
(g_P)_\psi.
```

The normalized support average is

```math
U_{n,P}(g_P)
=
\frac{S_{n,P}(g_P)}{(n)_r}.
```

# 2. Martingale structure

Let $\mathcal F_n$ contain all vertex variables $X_i$ with $i\leq n$ and all pair variables $Y_{ij}$ with $i,j\leq n$.

## Proposition 1. Canonical embedding sums are martingales

The sequence

```math
\left(S_{n,P}(g_P),\mathcal F_n\right)_{n\geq r}
```

is a square-integrable martingale.

## Proof

The increment from level $n-1$ to level $n$ is the sum of the embedded copies whose support contains the new vertex $n$. In every such copy, at least one primitive coordinate is new: either the vertex variable $X_n$, when the corresponding support vertex carries a loop, or a pair variable $Y_{in}$ attached to an incident ordinary edge.

Conditioning on $\mathcal F_{n-1}$ integrates all new primitive coordinates. The old coordinates form a proper subpattern of $P$, so canonicality gives zero conditional expectation for every new copy. Summing proves the martingale identity.

The exact support-pattern covariance formula gives

```math
\mathbb E
\left[
S_{n,P}(g_P)S_{m,P}(h_P)
\right]
=
(n)_r|\operatorname{Aut}(P)|
\mathbb E[g_Ph_P],
\qquad n\leq m.
```

In particular,

```math
\operatorname{Var}(S_{n,P}(g_P))
=
(n)_r|\operatorname{Aut}(P)|\|g_P\|_2^2.
```

# 3. Linear-size functional limit

For $t\geq0$, define

```math
M_{N,P}(t)
=
N^{-r/2}
S_{\lfloor Nt\rfloor,P}(g_P).
```

## Theorem 2. Connected-support invariance principle

If $P$ is connected, then

```math
M_{N,P}
\Longrightarrow
\sqrt{|\operatorname{Aut}(P)|}\,
\|g_P\|_2
B(t^r)
```

in the Skorohod topology on every compact time interval, where $B$ is a standard Brownian motion.

More generally, let $g_P^{(1)},\ldots,g_P^{(d)}$ be canonical kernels on the same connected pattern. Their joint limit is a centered Gaussian process with covariance

```math
\mathbb E
\left[
M_P^{(a)}(s)M_P^{(b)}(t)
\right]
=
|\operatorname{Aut}(P)|
\mathbb E
\left[
g_P^{(a)}g_P^{(b)}
\right]
\min(s,t)^r.
```

Canonical sums belonging to nonisomorphic connected support patterns converge jointly to independent Gaussian processes.

## Proof

Assume first that the kernels are bounded. Expand a mixed moment of finitely many process coordinates. Every summand is indexed by a family of embedded copies of connected support patterns.

Canonicality implies that the expectation of such a product vanishes whenever a primitive vertex or pair coordinate occurs in exactly one copy. Suppose no coordinate is unique. The connected-support counting lemma gives two possibilities:

1. the embedded support patterns coincide in pairs;
2. some supporting vertex belongs to at least three copies.

In the second case, the union of the embedded supports has strictly fewer than half the total number of listed support vertices. After multiplication by $N^{-r/2}$ for every factor, the number of such configurations is of lower order and their total contribution vanishes.

The leading configurations are therefore pairings of identical embedded primitive-coordinate sets. A pair whose process times are $s$ and $t$ can be embedded in

```math
\left(\lfloor N\min(s,t)\rfloor\right)_r
```

ways, with $|\operatorname{Aut}(P)|$ equivalent ordered identifications. Its contribution tends to

```math
|\operatorname{Aut}(P)|
\mathbb E[g_Ph_P]
\min(s,t)^r.
```

Summing over pairings gives Wick's formula for the stated Gaussian vector. Nonisomorphic support patterns cannot have identical primitive-coordinate sets, so their leading cross pairings are absent and their Gaussian limits are independent.

For tightness, the same support-union count applied to four increment factors gives, for bounded kernels and $0\leq s\leq t\leq T$,

```math
\mathbb E
\left[
|M_{N,P}(t)-M_{N,P}(s)|^4
\right]
\leq
C_T
\left(
|t-s|^2+N^{-1}
\right).
```

The corresponding fourth-moment estimate for one-level martingale jumps shows that their maximal normalized size converges to zero in probability. The standard tightness criterion for càdlàg processes then applies, and the Gaussian finite-dimensional limit is continuous.

For a general square-integrable kernel, approximate $g_P$ in $L^2$ by bounded canonical kernels. The exact variance formula and Doob's maximal inequality give uniform process-level control of the approximation error:

```math
\mathbb E
\left[
\sup_{0\leq t\leq T}
\left|
M_{N,P}^{g}(t)-M_{N,P}^{g^{(L)}}(t)
\right|^2
\right]
\leq
C_T\|g_P-g_P^{(L)}\|_2^2.
```

Letting the truncation level tend to infinity completes the proof.

The moment argument is the sequential version of the connected-support proof for generalized $U$-statistics. The nested time restrictions alter only the number of admissible pair embeddings and replace the fixed-time covariance by $\min(s,t)^r$.

# 4. Logarithmic-size Ornstein-Uhlenbeck limit

Set

```math
m_N(s)=\lfloor Ne^s\rfloor
```

and define the stationary normalization

```math
X_{N,P}(s)
=
m_N(s)^{r/2}
U_{m_N(s),P}(g_P).
```

## Corollary 3. Connected support gives an OU process

The processes $X_{N,P}$ converge on compact logarithmic-time intervals to

```math
X_P(s)
=
\sqrt{|\operatorname{Aut}(P)|}\,
\|g_P\|_2
 e^{-rs/2}B(e^{rs}).
```

This is a stationary Ornstein-Uhlenbeck process satisfying

```math
dX_P(s)
=
-\frac r2X_P(s)\,ds
+
\sqrt{r|\operatorname{Aut}(P)|}\,
\|g_P\|_2\,dW_s.
```

Its covariance is

```math
\mathbb E[X_P(s)X_P(t)]
=
|\operatorname{Aut}(P)|
\|g_P\|_2^2
 e^{-r|s-t|/2}.
```

## Proof

The relation between the two normalizations is

```math
X_{N,P}(s)
=
\frac{m_N(s)^{r/2}}{(m_N(s))_r}
S_{m_N(s),P}(g_P)
=
 e^{-rs/2}M_{N,P}(e^s)+o_P(1)
```

uniformly on compact intervals. Theorem 2 and the continuous-mapping theorem give the Lamperti form.

The process $e^{-rs/2}B(e^{rs})$ is stationary Gaussian with exponential covariance. Applying the Brownian time-change formula gives the displayed stochastic differential equation.

This proves the process law anticipated by the finite-level covariance expansion. A connected support pattern on $r$ vertices does not merely have covariance decay rate $r/2$; its complete logarithmic-size limit is the rate-$r/2$ Ornstein-Uhlenbeck process.

# 5. Full observables with connected principal support

Let $f$ be a symmetric $k$-vertex joint vertex-edge kernel, and let $d=d(f)$ be its principal vertex-support degree. Assume that every support pattern $P$ with

```math
v(P)=d,
\qquad
f_P\neq0,
```

is connected.

Recall the stable principal coefficient

```math
C_d(f,g)
=
\sum_{\substack{P\\v(P)=d}}
\frac{(k)_d(\ell)_d}{|\operatorname{Aut}(P)|}
\mathbb E[f_Pg_P].
```

## Theorem 4. Connected-principal observable limit

For

```math
Z_{f,N}(s)
=
m_N(s)^{d/2}
\left(
T_{m_N(s)}(f)-\theta_f
\right),
```

we have

```math
Z_{f,N}\Longrightarrow Z_f,
```

where $Z_f$ is the stationary Ornstein-Uhlenbeck process

```math
dZ_f(s)
=
-\frac d2 Z_f(s)\,ds
+
\sqrt{dC_d(f,f)}\,dW_s.
```

For a finite collection $f_1,\ldots,f_q$ with the same principal degree $d$ and connected principal supports, the joint limit is the multivariate OU process

```math
dZ(s)
=
-\frac d2 Z(s)\,ds
+
\sqrt{dC_d}\,dW_s,
```

where

```math
(C_d)_{ab}=C_d(f_a,f_b).
```

## Proof

The exact support decomposition separates the order-$d$ principal component from all higher orders. The higher support terms vanish in $L^2$ under the normalization $m_N^{d/2}$.

Each connected principal support pattern converges by Corollary 3. Nonisomorphic support patterns have independent Gaussian limits, while kernels on the same support pattern have covariance given by their $L^2$ inner product. Multiplication by the exact orbit coefficient

```math
\frac{(k)_d}{|\operatorname{Aut}(P)|}
```

and summation gives stationary covariance $C_d(f,g)$. Since every component has the same relaxation rate $d/2$, their Gaussian sum is the displayed OU process.

# 6. Examples across support orders

The theorem contains the previously derived Gaussian modes as special cases.

For a one-loop pattern, $r=1$. The limit is the empirical-mark OU process

```math
dX_s=-\frac12X_s\,ds+\sigma\,dW_s.
```

For a single centered pair variable, the support pattern is one ordinary edge on two vertices. Hence $r=2$, and the limit is the rate-one pair-noise process.

A centered product on the two edges of a three-vertex path has connected support order three. Its logarithmic limit is Gaussian despite being a product of two primitive pair variables:

```math
dX_s=-\frac32X_s\,ds+\sqrt{6}\,\sigma\,dW_s
```

when the support kernel has unit variance and the path automorphism group has order two.

Likewise, a canonical centered triangle of pair variables has support order three and a Gaussian rate-$3/2$ limit. The Gaussianity follows from connected support topology, not from linearity in the primitive variables.

# 7. Connected and disconnected modes at one rate

The symmetric two-layer edge density has principal degree two, but its principal support contains both connected and disconnected patterns. The disconnected two-loop component gives a quadratic Gaussian-chaos limit, while the connected edge components give a Gaussian rate-one OU process.

Theorem 4 does not apply to the full statistic because not every principal pattern is connected. It does apply separately to its connected projection, proving that the process denoted previously by $Z$ is the universal connected-support OU component.

The same separation holds for the symmetric three-layer route density. Its connected order-two edge residuals are OU processes, while its disconnected order-two mark projection is non-Gaussian. Both have covariance decay $e^{-|s-t|}$ because both use two supporting vertices.

At process level, connected principal support gives a Gaussian Ornstein-Uhlenbeck mode, whereas disconnected principal support gives a composite or chaos mode.

Support size fixes the relaxation rate; connected-component structure fixes whether that rate is carried by a primitive Gaussian mode or by a nonlinear composite field.

# 8. Consequences for stable laws

The finite ordered-kernel sectors now have a complete process theorem whenever the principal support is connected. Its finite primitive-coordinate projection determines the normalization $n^{d/2}$, stationary covariance $C_d$, relaxation rate $d/2$, and diffusion coefficient $\sqrt{dC_d}$.

No continuum coefficient is fitted independently. The OU generator is fixed by the combinatorial support degree and the exact finite projection norm.

The remaining functional problem is confined to disconnected principal supports. Their covariance is already known exactly, but their process laws may involve products, contractions, and sums of connected OU fields. A complete theorem should classify those limits by the connected-component decomposition of each principal support pattern.

# 9. Literature relation

S. Janson and K. Nowicki, *The asymptotic distributions of generalized U-statistics with applications to random graphs*, Probability Theory and Related Fields 90 (1991), 341-375, proved the fixed-level Gaussian limit for generalized $U$-statistics whose principal support graphs are connected. Their proof uses the same canonical-support pairing lemma that appears here.

The present result adds the nested-level process structure. Pair embeddings restricted to two levels contribute according to the smaller level, producing the covariance $\min(s,t)^r$ in linear size. The Lamperti transform then turns that self-similar Gaussian process into a stationary Ornstein-Uhlenbeck process with rate $r/2$.

Thus the generalized $U$-statistic topology and the logarithmic relaxation spectrum are two forms of one statement:

```math
\text{connected support on }r\text{ vertices}
\Longrightarrow
B(t^r)
\Longrightarrow
 e^{-rs/2}B(e^{rs}).
```
