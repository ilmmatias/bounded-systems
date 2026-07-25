# 1. The positive-path ideal is intrinsically recoverable

Let

[
\mathcal A=\mathbb C[G]
=======================

\mathcal D\oplus J,
]

where (\mathcal D) is the node diagonal and (J) is the span of all positive-length paths.

Write

[
[\mathcal A,\mathcal A]
]

for the linear span of all commutators

[
xy-yx.
]

## Theorem

For every acyclic system,

[
\boxed{J=[\mathcal A,\mathcal A].}
]

### Proof

Since

[
\mathcal A/J\cong\mathcal D
]

and (\mathcal D) is commutative, every commutator lies in (J):

[
[\mathcal A,\mathcal A]\subseteq J.
]

Conversely, let (p:u\to v) be any positive-length path. Acyclicity implies

[
u\ne v.
]

Using the terminal node projection,

[
e_vp=p,
\qquad
pe_v=0.
]

Therefore

[
p=[e_v,p].
]

Every positive path is a commutator, so

[
J\subseteq[\mathcal A,\mathcal A].
]

Hence equality holds.

This has several consequences.

## Abelianization

[
\boxed{
\mathcal A/[\mathcal A,\mathcal A]\cong\mathcal D.
}
]

Removing noncommutativity removes every positive communication process and leaves only mutually orthogonal nodes.

That is an unusually direct relationship:

[
\boxed{
\text{communication is exactly the noncommutative part of the algebra.}
}
]

# 2. Reconstruction no longer requires the grading to be marked

Previously, we required an algebra isomorphism to preserve both the diagonal and the path-length grading.

For acyclic systems, that was stronger than necessary.

Suppose

[
\Phi:\mathcal A(G)\to\mathcal A(H)
]

is an algebra isomorphism satisfying only

[
\Phi(\mathcal D(G))=\mathcal D(H).
]

Because commutators are intrinsic,

[
\Phi(J(G))
==========

# \Phi([\mathcal A(G),\mathcal A(G)])

# [\mathcal A(H),\mathcal A(H)]

J(H).
]

Therefore it also preserves

[
J^2,J^3,\ldots
]

and induces an isomorphism

[
J(G)/J(G)^2
\cong
J(H)/J(H)^2.
]

But

[
e_v(J/J^2)e_u
]

is precisely the vector space of primitive channels from (u) to (v). Composite paths vanish modulo (J^2).

Thus:

[
\dim e_v(J/J^2)e_u
==================

#{e:u\to v}.
]

## Strengthened reconstruction theorem

For arbitrary-cardinality acyclic systems,

[
\boxed{
(\mathcal A(G),\mathcal D(G))
\cong
(\mathcal A(H),\mathcal D(H))
\implies
G\cong H
}
]

as directed multigraphs.

The grading can be reconstructed from the intrinsic filtration:

[
J\supseteq J^2\supseteq J^3\supseteq\cdots.
]

Exact length-(n) paths appear in

[
J^n/J^{n+1}.
]

So the marked pair

[
\boxed{(\mathcal A,\mathcal D)}
]

already retains the entire finite communication structure.

# 3. Algebraic spectra are almost completely blind to channels

Take any algebraic element

[
a=d+x,
]

where

[
d=\sum_{v\in V}\lambda_ve_v\in\mathcal D
]

has finite support and

[
x\in J.
]

Assign (\lambda_v=0) at every node not explicitly present in (d).

## Theorem — algebraic spectrum

In the natural unitization,

[
\boxed{
\sigma_{\mathrm{alg}}(a)
========================

{\lambda_v:v\in V}.
}
]

In particular,

[
\boxed{
x\in J
\implies
\sigma_{\mathrm{alg}}(x)={0}.
}
]

### Why

If

[
\lambda=\lambda_v
]

for some node (v), evaluation at that diagonal coordinate shows that

[
\lambda1-a
]

cannot be invertible.

Now suppose

[
\lambda\notin{\lambda_v:v\in V}.
]

Then the diagonal element

[
D_\lambda=\lambda1-d
]

is invertible. Factor:

[
\lambda1-a
==========

D_\lambda\bigl(1-D_\lambda^{-1}x\bigr).
]

The element

[
D_\lambda^{-1}x
]

is still a finite positive-path expression. Since (J) is locally nilpotent, it is nilpotent. Therefore

[
\bigl(1-D_\lambda^{-1}x\bigr)^{-1}
==================================

\sum_{k=0}^{N-1}
(D_\lambda^{-1}x)^k
]

for some finite (N).

So (\lambda1-a) is invertible.

## Interpretation

No matter how complicated the finite path coefficients are, the ordinary algebraic spectrum sees only the diagonal node coefficients.

For example, adding a channel term does not alter the spectrum:

[
\sigma_{\mathrm{alg}}(d+te)
===========================

\sigma_{\mathrm{alg}}(d)
]

for every scalar (t).

This generalizes the earlier finite-DAG adjacency-spectrum collapse:

[
\boxed{
\text{bare single-operator spectra are structurally too compressed.}
}
]

The channel data are not absent from the algebra. They live in multiplication, commutators, corners, and resolvents—not in the set of spectral values alone.

# 4. The canonical formal path completion

The Fock norm completion is useful, but it depends on a Hilbert-space norm.

Before choosing any norm, there is a more primitive completion that works for every set-sized system.

Let

[
\widehat{\mathcal A}(G)
=======================

\mathbb C^{\mathsf P(G)}
]

be the space of **all** formal coefficient functions on finite paths.

An element has the form

[
X=\sum_{p\in\mathsf P(G)}c_pp,
]

with no finite-support requirement.

Define multiplication by path convolution. For a fixed path (r),

[
(XY)(r)
=======

\sum_{r=qp}X(q)Y(p).
]

This sum is always finite: a path of length (n) has only (n+1) possible cuts into an initial and final segment.

Therefore multiplication is well-defined even if:

* (V) is uncountable;
* (E) is uncountable;
* infinitely many paths have the same length;
* degrees are unbounded.

The element

[
\mathbf 1=\sum_{v\in V}e_v
]

is now a genuine identity.

No analytic convergence is involved.

# 5. Path-length topology

Define

[
F^n\widehat{\mathcal A}
=======================

\left{
X:X(p)=0\text{ whenever }|p|<n
\right}.
]

Then

[
F^mF^n\subseteq F^{m+n}.
]

A sequence or net converges in the path-length topology when, for every fixed depth (n), its coefficients eventually stabilize on all paths of length below (n).

The positive-length part is

[
F^1\widehat{\mathcal A}.
]

For every

[
X\in F^1\widehat{\mathcal A},
]

we have

[
X^n\in F^n\widehat{\mathcal A}.
]

Thus

[
X^n\longrightarrow0
]

in the path-length topology.

This is **topological nilpotence**, not algebraic nilpotence.

Accordingly,

[
\boxed{
(1-X)^{-1}
==========

\sum_{n=0}^{\infty}X^n
}
]

always exists formally.

At any fixed finite path, only finitely many terms contribute.

This is a completely cardinality-independent resolvent construction.

# 6. The universal channel element

Inside the formal completion, define

[
\mathbf E
=========

\sum_{e\in E}e.
]

Unlike the global Fock operator, this formal sum always exists. It does not require:

* finite degree;
* uniform branching bounds;
* square summability;
* operator convergence.

Introduce a formal scalar variable (z). Then

[
\boxed{
R_G(z)
======

# (1-z\mathbf E)^{-1}

\sum_{n=0}^{\infty}z^n\mathbf E^n.
}
]

The variable (z) records compositional depth. It is not time.

Because every composable sequence of (n) primitive channels is exactly one path of length (n),

[
\mathbf E^n
===========

\sum_{|p|=n}p.
]

Therefore

[
\boxed{
R_G(z)
======

\sum_{p\in\mathsf P(G)}
z^{|p|}p.
}
]

This is the complete finite-communication catalogue of the system.

# 7. Cornered resolvents recover the whole relational structure

For nodes (u,v),

[
e_vR_G(z)e_u
============

\delta_{uv}e_u
+
\sum_{p:u\to v}z^{|p|}p.
]

This one formula recovers several structures.

## Primitive channels

The coefficient of (z) is

[
e_v\mathbf Ee_u
===============

\sum_{e:u\to v}e.
]

## Length-(n) paths

The coefficient of (z^n) is

[
e_v\mathbf E^ne_u
=================

\sum_{\substack{p:u\to v\|p|=n}}p.
]

## Reachability

[
u\prec v
\iff
e_v(R_G(z)-1)e_u\ne0.
]

## Acyclicity

[
\boxed{
G\text{ is acyclic}
\iff
e_v(R_G(z)-1)e_v=0
\quad\text{for every }v.
}
]

A positive term in a diagonal corner would be a positive-length closed directed path.

## Finite height

[
G\text{ has height at most }h
\iff
R_G(z)
\text{ is a polynomial of degree at most }h.
]

## Unbounded finite compositional depth

[
R_G(z)
]

has nonzero terms of arbitrarily high degree.

This may arise either from an actual infinite chain or from finite chains of unbounded lengths. That distinction requires the infinite-path boundary, which is the next layer.

# 8. Formal spectrum versus operator spectrum

The formal channel element satisfies

[
(\lambda\mathbf1-\mathbf E)^{-1}
================================

\lambda^{-1}
\sum_{n=0}^{\infty}
\lambda^{-n}\mathbf E^n
]

for every

[
\lambda\ne0.
]

Thus, in the completed formal algebra,

[
\boxed{
\sigma_{\mathrm{formal}}(\mathbf E)={0}.
}
]

Yet in the Fock norm completion, the corresponding bounded operator may have spectrum:

[
{z:|z|\le1}
]

for an infinite chain, or radius

[
\sqrt d
]

for a regular (d)-branching system.

There is no contradiction.

The inverse series exists formally for every nonzero (\lambda), but it may fail to converge in operator norm. Operator spectrum detects failure of analytic convergence, not failure of formal path composition.

This gives three distinct tiers:

| Tier                     | Positive-path spectrum | What it records                    |
| ------------------------ | ---------------------- | ---------------------------------- |
| Algebraic path algebra   | ({0})                  | finite expressions                 |
| Formal path completion   | ({0})                  | all finite paths and formal depth  |
| Fock/operator completion | potentially nonzero    | norm growth and infinite branching |

So:

[
\boxed{
\text{nonzero operator spectrum is a growth/convergence phenomenon.}
}
]

It is not required for the underlying finite-path structure to be nontrivial.

# 9. The resolvent is richer than the spectrum

The spectral set

[
\sigma(\mathbf E)={0}
]

contains almost no information.

But the full marked resolvent family

[
\boxed{
\left{
e_v(1-z\mathbf E)^{-1}e_u:
u,v\in V
\right}
}
]

contains every finite directed path.

This suggests the correct hierarchy:

[
\boxed{
\text{spectrum}
;<;
\text{resolvent}
;<;
\text{cornered marked resolvent}
;\cong;
\text{full finite-path structure}.
}
]

The earlier spectral collisions were therefore not accidental. They were manifestations of discarding the node corners and the multiplication structure.

# 10. The algebraic and formal centers

There is another clean completion effect.

Let the **weak components** be the connected components obtained after forgetting edge directions.

In the algebraic path algebra, a central element must be diagonal and constant along every edge. Because algebraic elements have finite support, a nonzero constant can occur only on a finite weak component.

Thus

[
\boxed{
Z(\mathcal A(G))
================

\bigoplus_{\substack{C\text{ weak component}\|C|<\infty}}
\mathbb C
\left(\sum_{v\in C}e_v\right).
}
]

In the formal completion, arbitrary diagonal coefficient functions are allowed. Therefore

[
\boxed{
Z(\widehat{\mathcal A}(G))
\cong
\prod_{C\in\pi_0(G)}\mathbb C.
}
]

The formal center assigns one scalar to every weak component, finite or infinite.

Again, the completion adds no new edges or interactions. It changes which infinite combinations are retained.
