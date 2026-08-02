# 1. The positive-path ideal is intrinsically recoverable

Let

```math
\mathcal A=\mathbb C[G]=
\mathcal D\oplus J,
```

where $\mathcal D$ is the node diagonal and $J$ is the span of all
positive-length paths.

Write

```math
[\mathcal A,\mathcal A]
```

for the linear span of all commutators

```math
xy-yx.
```

## Theorem 1. Commutator ideal

For every acyclic system,

```math
J=[\mathcal A,\mathcal A].
```

## Proof

Since

```math
\mathcal A/J\cong\mathcal D
```

and $\mathcal D$ is commutative, every commutator lies in $J$:

```math
[\mathcal A,\mathcal A]\subseteq J.
```

Conversely, let $p:u\to v$ be any positive-length path. Acyclicity implies

```math
u\ne v.
```

Using the terminal node projection,

```math
e_vp=p,
\qquad
pe_v=0.
```

Therefore,

```math
p=[e_v,p].
```

Every positive path is a commutator, so

```math
J\subseteq[\mathcal A,\mathcal A].
```

This proves the reverse inclusion and hence the equality.

The abelianization is therefore

```math
\mathcal A/[\mathcal A,\mathcal A]\cong\mathcal D.
```

Thus abelianization removes every positive-length communication process and
retains only the mutually orthogonal node algebra. In this precise sense, the
communication structure is the noncommutative part of $\mathcal A$.

# 2. Reconstruction from the marked diagonal

A reconstruction argument may initially be formulated for isomorphisms
preserving both the diagonal and the path-length grading. In the acyclic case,
preservation of the grading follows intrinsically from preservation of the
diagonal.

Suppose

```math
\Phi:\mathcal A(G)\to\mathcal A(H)
```

is an algebra isomorphism satisfying only

```math
\Phi(\mathcal D(G))=\mathcal D(H).
```

Because commutators are intrinsic,

```math
\Phi(J(G))=
\Phi([\mathcal A(G),\mathcal A(G)])=
[\mathcal A(H),\mathcal A(H)]=
J(H).
```

It also preserves

```math
J^2,J^3,\ldots
```

and induces an isomorphism

```math
J(G)/J(G)^2
\cong
J(H)/J(H)^2.
```

The corner

```math
e_v(J/J^2)e_u
```

is precisely the vector space of primitive channels from $u$ to $v$. Composite
paths vanish modulo $J^2$, and hence

```math
\dim e_v(J/J^2)e_u=
\left|\{e:u\to v\}\right|.
```

## Theorem 2. Reconstruction from the diagonal

For arbitrary-cardinality acyclic systems,

```math
(\mathcal A(G),\mathcal D(G))
\cong
(\mathcal A(H),\mathcal D(H))
\implies
G\cong H
```

as directed multigraphs.

The grading can be reconstructed from the intrinsic filtration:

```math
J\supseteq J^2\supseteq J^3\supseteq\cdots.
```

Exact length-$n$ paths appear in

```math
J^n/J^{n+1}.
```

Consequently, the marked pair $(\mathcal A,\mathcal D)$ retains the complete
finite communication structure.

# 3. Algebraic spectrum

Take any algebraic element

```math
a=d+x,
```

where

```math
d=\sum_{v\in V}\lambda_ve_v\in\mathcal D
```

has finite support and

```math
x\in J.
```

Assign $\lambda_v=0$ at every node not explicitly present in $d$.

## Theorem 3. Algebraic spectrum

In the natural unitization,

```math
\sigma_{\mathrm{alg}}(a)=
\{\lambda_v:v\in V\}.
```

In particular,

```math
x\in J
\implies
\sigma_{\mathrm{alg}}(x)=\{0\}.
```

## Proof

If

```math
\lambda=\lambda_v
```

for some node $v$, evaluation at that diagonal coordinate shows that

```math
\lambda1-a
```

cannot be invertible.

Now suppose

```math
\lambda\notin\{\lambda_v:v\in V\}.
```

Then the diagonal element

```math
D_\lambda=\lambda1-d
```

is invertible. Factor:

```math
\lambda1-a=
D_\lambda\bigl(1-D_\lambda^{-1}x\bigr).
```

The element

```math
D_\lambda^{-1}x
```

is still a finite positive-path expression. Since $J$ is locally nilpotent, it
is nilpotent. Therefore

```math
\bigl(1-D_\lambda^{-1}x\bigr)^{-1}=
\sum_{k=0}^{N-1}
(D_\lambda^{-1}x)^k
```

for some finite $N$.

Hence $\lambda1-a$ is invertible, which proves the stated spectral formula.

The ordinary algebraic spectrum therefore depends only on the diagonal node
coefficients, regardless of the finite positive-path component.

For example, adding a channel term does not alter the spectrum:

```math
\sigma_{\mathrm{alg}}(d+te)=
\sigma_{\mathrm{alg}}(d)
```

for every scalar $t$.

This extends the collapse of the adjacency spectrum for finite DAGs. A single
spectral set is too compressed to recover the channel structure, which instead
remains visible in multiplication, commutators, corners, and resolvents.

# 4. The canonical formal path completion

The Fock norm completion depends on a choice of Hilbert-space norm.

Before any norm is chosen, a formal completion can be defined for every
set-sized system.

Let

```math
\widehat{\mathcal A}(G)=
\mathbb C^{\mathsf P(G)}
```

be the space of all formal coefficient functions on finite paths.

An element has the form

```math
X=\sum_{p\in\mathsf P(G)}c_pp,
```

with no finite-support requirement.

Define multiplication by path convolution. For a fixed path $r$,

```math
(XY)(r)=
\sum_{r=qp}X(q)Y(p).
```

The sum is always finite because a path of length $n$ has only $n+1$ cuts into
initial and final segments.

The multiplication is therefore well-defined for arbitrary set-sized node and
edge sets, including systems with infinitely many paths of a fixed length or
unbounded degree.

The element

```math
\mathbf 1=\sum_{v\in V}e_v
```

is now a genuine identity.

No analytic convergence is involved.

# 5. Path-length topology

Define

```math
F^n\widehat{\mathcal A}=
\left\lbrace X:X(p)=0\text{ whenever }|p|<n \right\rbrace.
```

Then

```math
F^mF^n\subseteq F^{m+n}.
```

A sequence or net converges in the path-length topology when, for every fixed
depth $n$, its coefficients eventually stabilize on all paths of length below
$n$.

The positive-length part is $F^1\widehat{\mathcal A}$. For every
$X\in F^1\widehat{\mathcal A}$,

```math
X^n\in F^n\widehat{\mathcal A}
```

and hence

```math
X^n\longrightarrow0
```

in the path-length topology.

The completion is topologically nilpotent, not algebraically nilpotent.

Accordingly,

```math
(1-X)^{-1}=
\sum_{n=0}^{\infty}X^n
```

always exists formally.

At any fixed finite path, only finitely many terms contribute.

The resolvent construction is independent of cardinality.

# 6. The universal channel element

Inside the formal completion, define

```math
\mathbf E=
\sum_{e\in E}e.
```

Unlike the global Fock operator, this formal sum exists without finite-degree or
uniform branching assumptions and requires neither square summability nor
operator convergence.

Introduce a formal scalar variable $z$. Then

```math
R_G(z)=
(1-z\mathbf E)^{-1}=
\sum_{n=0}^{\infty}z^n\mathbf E^n.
```

The variable $z$ records compositional depth and carries no temporal
interpretation.

Because every composable sequence of $n$ primitive channels is exactly one path
of length $n$,

```math
\mathbf E^n=
\sum_{|p|=n}p.
```

Substitution into the resolvent series gives

```math
R_G(z)=
\sum_{p\in\mathsf P(G)}
z^{|p|}p.
```

Thus $R_G(z)$ records every finite communication path together with its length.

# 7. Relational information in cornered resolvents

For nodes $u,v$,

```math
e_vR_G(z)e_u=
\delta_{uv}e_u
+
\sum_{p:u\to v}z^{|p|}p.
```

The coefficient of $z$ recovers the primitive channels from $u$ to $v$:

```math
e_v\mathbf Ee_u=
\sum_{e:u\to v}e.
```

More generally, the coefficient of $z^n$ is

```math
e_v\mathbf E^ne_u=
\sum_{\substack{p:u\to v\\|p|=n}}p.
```

Reachability is characterized by

```math
u\prec v
\iff
e_v(R_G(z)-1)e_u\ne0.
```

Acyclicity is equivalent to

```math
G\text{ is acyclic}
\iff
e_v(R_G(z)-1)e_v=0
\quad\text{for every }v.
```

A positive term in a diagonal corner would be a positive-length closed directed
path.

Finite height is detected by the degree of the resolvent:

```math
G\text{ has height at most }h
\iff
R_G(z)
\text{ is a polynomial of degree at most }h.
```

Unbounded finite compositional depth occurs precisely when $R_G(z)$ has nonzero
terms of arbitrarily high degree.

The same formal behavior can come from an infinite chain or from finite chains
of unbounded length. The infinite-path boundary distinguishes them.

# 8. Formal spectrum versus operator spectrum

For every $\lambda\ne0$, the formal channel element satisfies

```math
(\lambda\mathbf1-\mathbf E)^{-1}=
\lambda^{-1}
\sum_{n=0}^{\infty}
\lambda^{-n}\mathbf E^n.
```

In the completed formal algebra,

```math
\sigma_{\mathrm{formal}}(\mathbf E)=\{0\}.
```

In the Fock norm completion, however, the corresponding bounded operator may
have the closed unit disk as its spectrum for an infinite chain, or spectral
radius $\sqrt d$ for a regular $d$-branching system. The statements concern
different notions of convergence: for every nonzero $\lambda$, the inverse
series exists formally but may fail to converge in operator norm. Operator
spectrum therefore detects failure of analytic convergence rather than failure
of formal path composition.

There are three tiers:

| Tier                     | Positive-path spectrum | What it records                    |
| ------------------------ | ---------------------- | ---------------------------------- |
| Algebraic path algebra   | $\{0\}$                | finite expressions                 |
| Formal path completion   | $\{0\}$                | all finite paths and formal depth  |
| Fock/operator completion | potentially nonzero    | norm growth and infinite branching |

A nonzero operator spectrum is therefore a growth and convergence phenomenon;
nontrivial finite-path structure may still have zero positive-path spectrum.

# 9. Information carried by the marked resolvent

The spectral identity

```math
\sigma(\mathbf E)=\{0\}
```

does not distinguish the finite-path structure of acyclic systems.

But the full marked resolvent family

```math
\left\lbrace e_v(1-z\mathbf E)^{-1}e_u: u,v\in V \right\rbrace
```

contains every finite directed path.

The spectral set is coarser than the resolvent, and the uncornered resolvent is
coarser than the cornered marked family. The latter is equivalent to the full
finite-path structure. The earlier spectral collisions reflect the loss of the
node corners and the multiplication structure.

# 10. The algebraic and formal centers

The center changes under completion as well.

Let the weak components be the connected components obtained after forgetting
edge directions.

In the algebraic path algebra, a central element must be diagonal and constant
along every edge. Because algebraic elements have finite support, a nonzero
constant can occur only on a finite weak component. Consequently,

```math
Z(\mathcal A(G))=
\bigoplus_{\substack{C\text{ weak component}\\|C|<\infty}}
\mathbb C
\left(\sum_{v\in C}e_v\right).
```

In the formal completion, arbitrary diagonal coefficient functions are allowed,
and therefore

```math
Z(\widehat{\mathcal A}(G))
\cong
\prod_{C\in\pi_0(G)}\mathbb C.
```

The formal center assigns one scalar to every weak component, finite or
infinite.

The completion changes which infinite combinations are retained while preserving
the edge and interaction structure.
