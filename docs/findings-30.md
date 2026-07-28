# 1. Rays and their node shadows

Let

```math
\xi=(e_1,e_2,\ldots)
```

be an infinite path beginning at $o$. Write

```math
p_n^\xi=e_n\cdots e_1
```

for its length-$n$ prefix and

```math
x_n^\xi=r(p_n^\xi)
```

for its current node.

The sequence of normalized Green columns is

```math
K_t(\cdot,x_n^\xi).
```

It need not converge. Its canonical cluster set is

```math
\mathrm{Cl}_t(\xi)=
\bigcap_{N\ge1}
\overline{\left\{
K_t(\cdot,x_n^\xi):n\ge N
\right\}}.
```

The closure is taken in the product topology of pointwise convergence.

Because every coordinate is bounded by prefixing estimates, the ambient product is compact, so this cluster set is nonempty whenever all columns are defined.

### Martin-regular ray

Call $\xi$ $t$-Martin regular when

```math
\mathrm{Cl}_t(\xi)={h_\xi}
```

is a singleton.

Equivalently,

```math
h_\xi(v)=
\lim_{n\to\infty}
\frac{G_t(v,x_n^\xi)}
{G_t(o,x_n^\xi)}
```

exists for every fixed node $v$.

The function $h_\xi$ is the node shadow of the complete history $\xi$.

---

# 2. Exact node-equivalence relation

On the Martin-regular rays, define

```math
\xi\sim_t^M\eta
\iff
h_\xi=h_\eta.
```

Equivalently,

```math
\xi\sim_t^M\eta
\iff
\lim_{n\to\infty}
\left[
K_t(v,x_n^\xi)-
K_t(v,x_n^\eta)
\right]
=0
\quad
\text{for every }v.
```

The synchronization by the same $n$ is not essential; both sequences simply converge to the same product-space point.

This relation has a direct observational interpretation:

```math
\xi\sim_t^M\eta
```

exactly when every fixed node $v$, using normalized weighted route counts toward the distant endpoints, sees the two histories asymptotically identically.

The quotient forgets route history precisely to the extent that those normalized Green observations fail to separate rays.

---

# 3. Three levels of route identification

There are three progressively weaker ways for two rays to become indistinguishable.

## Eventual common tail

Write

```math
\xi\sim_{\mathrm{tail}}\eta
```

when, after possibly different finite prefixes, the two paths follow exactly the same infinite edge sequence.

This is the standard tail relation used for path spaces of Bratteli diagrams and related graded graphs. Tail-equivalence classes and tail-invariant measures are fundamental objects in that setting.

If two rays have an eventual common tail, their node sequences are eventually identical up to a finite shift. Hence

```math
\xi\sim_{\mathrm{tail}}\eta
\Longrightarrow
\mathrm{Cl}_t(\xi)=
\mathrm{Cl}_t(\eta).
```

In particular, for regular rays,

```math
\xi\sim_{\mathrm{tail}}\eta
\Longrightarrow
\xi\sim_t^M\eta.
```

## Cofinal reconvergence

Say that $\xi$ and $\eta$ reconverge cofinally when there are sequences

```math
n_k,m_k\to\infty
```

such that

```math
x_{n_k}^\xi=x_{m_k}^\eta
```

for every $k$.

If both rays are Martin regular, their Green-column sequences contain the same cofinal subsequence. Therefore

```math
\text{cofinal reconvergence}
\Longrightarrow
\xi\sim_t^M\eta.
```

The rays may split again after every common node. They need not possess an eventual common tail.

## Asymptotic Green equivalence

Two rays can satisfy

```math
\xi\sim_t^M\eta
```

without ever meeting after the root.

Their distant nodes can simply become indistinguishable under all normalized Green ratios.

Thus, on regular rays,

```math
\sim_{\mathrm{tail}}
\ \subseteq
\sim_{\mathrm{cofinal}}
\ \subseteq
\sim_t^M.
```

Both inclusions can be strict.

---

# 4. One reconvergence is not sufficient

Suppose two rays meet at a node $w$, but then choose different outgoing branches and never meet again.

The common finite prefix after reconvergence says nothing by itself about the asymptotic Green columns of the later endpoints.

Therefore:

```math
\text{one finite reconvergence}
\not\Longrightarrow
\text{one Martin boundary point}.
```

The sufficient conditions are instead:

* a permanently common tail;
* an unbounded sequence of common later nodes, assuming regularity;
* or direct equality of all limiting Green ratios.

---

# 5. Unique-route systems: no boundary collapse

Suppose every node reachable from $o$ is reached by exactly one route.

Then the graph rooted at $o$ is identified with its prefix tree.

Let $v$ have unique rooted path $p_v$, of length $k$. For a ray $\xi$,

```math
K_t(v,x_n^\xi)=
\begin{cases}
t^{-k},&p_v\preceq \xi\text{ and }n\ge k,\\
0,&p_v\npreceq \xi.
\end{cases}
```

Therefore

```math
h_\xi(v)=
t^{-|p_v|}
\mathbf1_{\{p_v\preceq\xi\}}.
```

If $\xi\ne\eta$, there is a first prefix belonging to one ray and not the other. The corresponding coordinate separates their node kernels.

Hence:

```math
\text{unique rooted routes}
\Longrightarrow
\xi\sim_t^M\eta
\iff
\xi=\eta.
```

The node Martin boundary retains the entire infinite route history.

This is the boundary analogue of

```math
X_G=0
```

at the finite-path level.

---

# 6. Eventual reconvergence: the diamond-tail fiber

Consider

```math
o\to a\to v_0\to v_1\to v_2\to\cdots
```

and

```math
o\to b\to v_0.
```

There are two infinite histories,

```math
\xi_a,\qquad \xi_b,
```

but after reaching $v_0$ they have the same tail. Thus

```math
\xi_a\sim_t^M\xi_b.
```

The prefix boundary has two points, while the node Martin boundary has one corresponding direction.

The node bridge weights average the two equal-length histories:

```math
\mu_h=
\frac12\delta_{\xi_a}
+
\frac12\delta_{\xi_b}.
```

The difference

```math
\delta_{\xi_a}-\delta_{\xi_b}
```

is invisible after node compression.

It is the asymptotic counterpart of a finite diamond route defect.

---

# 7. Complete layered mixing: collapse without reconvergence

Fix an integer $b\ge2$.

Let:

* $V_0={o}$;
* every level $V_n$, $n\ge1$, contain $b$ nodes;
* $o$ connect to every node of $V_1$;
* every node of $V_n$ connect to every node of $V_{n+1}$.

An infinite route is an arbitrary sequence

```math
(i_1,i_2,\ldots)\in\{1,\ldots,b\}^{\mathbb N}.
```

So the prefix boundary is the full $b$-symbol product space.

Take $v\in V_k$ and $x\in V_n$, with $n>k$. Then

```math
\left|\mathsf P(v,x)\right|=b^{n-k-1}
```

and

```math
\left|\mathsf P(o,x)\right|=b^{n-1}.
```

All such paths have their level-determined lengths, so

```math
G_t(v,x)=b^{n-k-1}t^{n-k},
```

```math
G_t(o,x)=b^{n-1}t^n.
```

Therefore

```math
K_t(v,x)=(bt)^{-k},
```

independent of:

* the terminal node $x$;
* the route used to reach $x$;
* every future symbol choice.

Consequently every infinite ray has exactly the same node shadow:

```math
h(v)=(bt)^{-k}
\qquad(v\in V_k).
```

Thus

```math
\partial_{\mathrm{pre}}G
\cong
\{1,\ldots,b\}^{\mathbb N},
```

while

```math
\partial_t^M V
\text{ consists of one point}.
```

Two rays can choose different nodes at every positive level and never reconverge, yet still be Martin-equivalent.

So:

```math
\text{node Martin collapse can be caused by asymptotic mixing,}
```

not only by literal reconvergence.

---

# 8. The canonical quotient in the regular compact case

Assume now that:

1. the prefix boundary $X_{\mathrm{pre}}$ is compact;
2. every boundary path is $t$-Martin regular;
3. for every node $v$, the function $k_v(\xi)=h_\xi(v)$ is continuous on $X_{\mathrm{pre}}$.

Define

```math
\pi_t:
X_{\mathrm{pre}}\longrightarrow
\prod_{v\in V}[0,C_v]
```

by

```math
\pi_t(\xi)=\bigl(k_v(\xi)\bigr)_{v\in V}.
```

Let

```math
Y_t=\pi_t(X_{\mathrm{pre}}).
```

Then $Y_t$ is compact, and

```math
\xi\sim_t^M\eta
\iff
\pi_t(\xi)=\pi_t(\eta).
```

Therefore

```math
Y_t
\cong
X_{\mathrm{pre}}/\!\sim_t^M.
```

This is the precise boundary quotient:

```math
\text{actual infinite histories}
\longrightarrow
\text{normalized endpoint-asymptotic directions}.
```

---

# 9. The node-observable boundary algebra

Under the same compactness assumptions, define

```math
\mathcal N_t=
C^\ast\bigl(1,{k_v:v\in V}\bigr)
\subseteq
C(X_{\mathrm{pre}}).
```

This is the commutative algebra generated by all node Martin observables.

Its functions cannot distinguish two rays in the same fiber of $\pi_t$.

Conversely, because the coordinate functions separate points of $Y_t$,

```math
\mathcal N_t
\cong
C(Y_t).
```

Thus:

```math
\text{node Martin compression}=
\text{restriction from all prefix observables to }\mathcal N_t.
```

The full boundary algebra $C(X_{\mathrm{pre}})$ retains route history.

The subalgebra $\mathcal N_t$ retains only what can be detected through asymptotic node Green ratios.

This is the exact commutative boundary counterpart of the finite-level inclusion

```math
\text{endpoint data}
\subset
\text{route-resolved data}.
```

---

# 10. The Martin-collapse relation groupoid

Define

```math
\mathcal R_t^M=
\left\lbrace (\xi,\eta)\in X_{\mathrm{pre}}\times X_{\mathrm{pre}}: \pi_t(\xi)=\pi_t(\eta) \right\rbrace.
```

This equivalence relation contains the eventual-tail relation but can be much larger.

Its fiber over a node boundary point $h\in Y_t$ is

```math
F_h=\pi_t^{-1}(h).
```

The size and topology of $F_h$ measure how much actual route history is erased at the boundary.

Examples:

* unique-route tree:
  ```math
  |F_h|=1;
  ```
* diamond followed by a tail:
  ```math
  |F_h|=2;
  ```
* complete layered mixing:
  ```math
  F_h\cong\{1,\ldots,b\}^{\mathbb N}.
  ```

So a single node Martin direction can conceal anything from one history to an entire Cantor family of histories.

---

# 11. Boundary route-defect spaces

At finite depth, a route fiber $S$ had the defect space

```math
\left\lbrace (c_p): \sum_pc_p=0 \right\rbrace.
```

The exact boundary analogue is obtained from a fiber $F_h$.

Let $\mathcal M(F_h)$ be the finite signed measures on $F_h$. Define

```math
\mathfrak D_t(h)=
\left\lbrace \nu\in\mathcal M(F_h): \nu(F_h)=0 \right\rbrace.
```

Every difference

```math
\delta_\xi-\delta_\eta,
\qquad
\xi,\eta\in F_h,
```

belongs to $\mathfrak D_t(h)$.

It is killed by the node pushforward:

```math
(\pi_t)_*
(\delta_\xi-\delta_\eta)=0.
```

For a finite fiber of size $m$,

```math
\dim\mathfrak D_t(h)=m-1.
```

Thus:

```math
\begin{array}{c|c}
\text{Finite route fiber}&\text{Boundary Martin fiber}\\
\hline
{p:u\to v}&F_h\\
\sum c_p=0&\nu(F_h)=0\\
p-q&\delta_\xi-\delta_\eta\\
m-1&m-1
\end{array}
```

The finite route-collapse ideal has become an asymptotic history-collapse space.

---

# 12. A boundary route-resolution nerve

For each node boundary point $h$, form the chaotic simplicial set

```math
E(F_h)_n=F_h^{n+1}.
```

Its:

* vertices are infinite histories mapping to $h$;
* edges identify pairs of such histories;
* triangles enforce coherence among three identifications;
* higher simplices provide all higher collapse coherence.

Its normalized degree-one boundary is

```math
d_1(\xi,\eta)=\eta-\xi.
```

Therefore its first image spans the atomic boundary defects

```math
\delta_\eta-\delta_\xi.
```

If $F_h\ne\varnothing$, the unmarked simplicial set $E(F_h)$ is contractible. But its marked zero-skeleton remembers every actual history.

This parallels the finite route-resolution construction:

```math
E(\mathscr P(u,v))
\quad\longrightarrow\quad
E(F_h).
```

The first resolves collapse of finite paths to one reachability arrow.

The second resolves collapse of infinite histories to one node Martin direction.

---

# 13. Minimality after compression

Suppose $h$ is a minimal node harmonic function.

Its lifted endpoint-factorized boundary measure can still be non-extreme among all route-sensitive measures.

The diamond-tail example already shows this:

```math
h
\quad\longleftrightarrow\quad
\frac12\delta_{\xi_a}
+
\frac12\delta_{\xi_b}.
```

The node function is extreme because the compressed node cone has only one direction. But the lifted route measure decomposes into two distinct route-extreme states.

More generally, under an integral representation in which Martin-regular rays project through $\pi_t$, minimality of $h$ forces its representing node-shadow measure to be concentrated at $h$. Its route-sensitive representing measure may nevertheless spread arbitrarily inside

```math
F_h.
```

Hence:

```math
\text{node minimality}
\not\Longrightarrow
\text{route-history purity}.
```

It implies only that all histories in the decomposition have the same compressed node shadow.

---

# 14. Nonregular rays

For a general A1–A5 system, a ray need not have a unique node Martin limit.

Then the correct primary object is not a function

```math
\pi_t(\xi),
```

but the compact cluster set

```math
\mathrm{Cl}_t(\xi).
```

Several distinctions arise:

### Singleton cluster set

```math
\mathrm{Cl}_t(\xi)={h}.
```

The ray has a well-defined node shadow.

### Multiple cluster points

The same route history presents different node asymptotic profiles along different subsequences.

### Equal cluster sets

Two nonregular rays may have

```math
\mathrm{Cl}_t(\xi)=
\mathrm{Cl}_t(\eta)
```

even though neither has a unique limit.

### Intersecting cluster sets

Two rays may share some asymptotic node profiles but not all.

Therefore, without regularity, there is no canonical point-valued quotient of the literal ray space.

The unconditional object is the relation between:

```math
\text{prefix histories}
\quad\text{and}\quad
\text{their sets of Martin cluster points}.
```

A genuine quotient map appears only after imposing or proving appropriate convergence.

---

# 15. Arbitrary branching

When the literal infinite-ray space is not compact—for example because of infinite emitters—the same construction should be made on the spectrum of the prefix-cylinder algebra rather than only on actual rays.

That spectrum includes generalized exits through infinite branching, exactly as encountered in the earlier boundary-state analysis.

The node observables $k_v$, whenever defined, still generate a subalgebra. Its spectrum is again the endpoint-asymptotic quotient.

Thus the algebraic formulation

```math
\mathcal N_t
\subseteq
\mathcal D_{\mathrm{prefix}}
```

is more general than the literal topological map between infinite-ray spaces.
