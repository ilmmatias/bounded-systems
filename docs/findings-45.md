# 1. Minimal first-pass cylinder dictionary

Let $A$ be the adjacency matrix of a DAG, including channel multiplicities,
and let

```math
\mathbf 1=(1,\ldots,1)^\mathsf T.
```

The out- and in-degree vectors are

```math
d^+=A\mathbf1,
\qquad
d^-=A^\mathsf T\mathbf1.
```

The four second-order aggregate vectors are

```math
\begin{aligned}
q^{++}&=A^2\mathbf1=A d^+, &
q^{--}&=(A^\mathsf T)^2\mathbf1=A^\mathsf T d^-,\\
q^{+-}&=AA^\mathsf T\mathbf1=A d^-, &
q^{-+}&=A^\mathsf TA\mathbf1=A^\mathsf T d^+.
\end{aligned}
```

At a node $u$, $q^{++}(u)$ and $q^{--}(u)$ count the directed length-two routes
starting and ending at $u$, respectively, while

```math
q^{+-}(u)=
\sum_v
\left|N^+(u)\cap N^+(v)\right|,
\qquad
q^{-+}(u)=
\sum_v
\left|N^-(u)\cap N^-(v)\right|.
```

Define the normalized node coordinate

```math
X_G(u)=
\begin{pmatrix}
d^+(u)/n\\
d^-(u)/n\\
q^{++}(u)/n^2\\
q^{--}(u)/n^2\\
q^{+-}(u)/n^2\\
q^{-+}(u)/n^2
\end{pmatrix}
\in\mathbb R^6.
```

The six-coordinate dictionary is the first-moment projection of the
second-order pair profile.

It is label invariant, comparable across system sizes, computable by
sparse-matrix methods, bounded in a fixed compact subset of $\mathbb R^6$,
and sensitive to direction, two-step flow, divergence, and reconvergence.

No manually selected graph statistic has been added.

## Sufficiency of the six-coordinate profile

The direct-relation frequencies are already determined by the first two
coordinates:

```math
\frac{\left|\{v:u\to v\}\right|}n=\frac{d^+(u)}n,
\qquad
\frac{\left|\{v:v\to u\}\right|}n=\frac{d^-(u)}n.
```

Equality contributes $1/n$; incomparability is the remainder, so these
relation-count cylinders add no independent first-order information.

Partner-degree averages that do not depend on $u$ are also graph-global
constants and do not contribute to node motion.

The three families just eliminated are the redundant ones among the linear node
cylinders available from the current communication record; these six coordinates
are the survivors.

# 2. Integer node signatures

Before normalization, define the exact integer signature

```math
S_G(u)=
\left(
d^+(u),
d^-(u),
q^{++}(u),
q^{--}(u),
q^{+-}(u),
q^{-+}(u)
\right).
```

Group nodes into classes

```math
C_a=\{u:S_G(u)=s_a\},
\qquad
a=1,\ldots,m.
```

Each class has one normalized coordinate

```math
\xi_a=X_G(u),
\qquad u\in C_a.
```

The first-pass state space has at most $n$ states and usually fewer.

The exact profile-refinement hierarchy will later replace $S_G(u)$ by
increasingly refined node colors.

# 3. Route counting

For a selected route horizon $p$, compute

```math
r_0=\mathbf1,
\qquad
r_{k+1}=Ar_k,
```

and

```math
\ell_0=\mathbf1,
\qquad
\ell_{k+1}=A^\mathsf T\ell_k.
```

Thus $r_k(v)$ counts the length-$k$ routes starting at $v$, and $\ell_k(v)$
counts the length-$k$ routes ending at $v$.

The total number of length-$p$ routes is

```math
T_p=\sum_v r_p(v).
```

For an edge $e:v\to w$ of multiplicity $m_e$, define its route-flow numerator

```math
W_e^{(p)}=
m_e
\sum_{j=0}^{p-1}
\ell_j(v),
r_{p-j-1}(w).
```

The count sums the occurrences of $e$ over all positions in all length-$p$
routes.

The normalized route-averaged edge flow is

```math
f_e^{(p)}=
\frac{W_e^{(p)}}{pT_p}.
```

The exact audit identity is

```math
\sum_eW_e^{(p)}=pT_p,
```

hence

```math
\sum_ef_e^{(p)}=1.
```

A failure of this identity means the route-flow implementation is wrong.

# 4. Compression of the route flow to node-profile classes

Define the integer class-flow matrix

```math
W_{ab}^{(p)}=
\sum_{\substack{e:v\to w\\v\in C_a,\ w\in C_b}}
W_e^{(p)}.
```

It follows that

```math
\sum_{a,b}W_{ab}^{(p)}=pT_p.
```

Its normalized version is

```math
F_{ab}^{(p)}=
\frac{W_{ab}^{(p)}}{pT_p}.
```

Define the source mass

```math
\pi_a^{\mathrm{out}}=
\sum_bF_{ab}^{(p)}
```

and target mass

```math
\pi_b^{\mathrm{in}}=
\sum_aF_{ab}^{(p)}.
```

Whenever $\pi_a^{\mathrm{out}}>0$, the empirical route transition matrix is

```math
K_{ab}^{(p)}=
\frac{F_{ab}^{(p)}}{\pi_a^{\mathrm{out}}}.
```

By construction,

```math
\sum_bK_{ab}^{(p)}=1.
```

The corresponding finite generator is

```math
L_{ab}^{(p)}=
\frac{
K_{ab}^{(p)}-\delta_{ab}
}{
a_{G,p}
},
```

where $a_{G,p}$ is the continuum-time scale extracted below.

The matrix is a directly computable approximation to the continuum profile
operator.

# 5. Local coefficient fields

At class $a$, define

```math
\Delta\xi_{ab}=\xi_b-\xi_a.
```

The local drift is

```math
b_a^{(p)}=
\frac1{a_{G,p}}
\sum_bK_{ab}^{(p)}\Delta\xi_{ab}.
```

The local raw quadratic tensor is

```math
A_a^{(p)}=
\frac1{a_{G,p}}
\sum_b
K_{ab}^{(p)}
\Delta\xi_{ab}
\Delta\xi_{ab}^\mathsf T.
```

The local covariance is

```math
\Sigma_a^{(p)}=
A_a^{(p)}-
a_{G,p},
b_a^{(p)}
b_a^{(p)\mathsf T}.
```

The final factor appears because the unscaled conditional mean is

```math
a_{G,p}b_a^{(p)}.
```

The local third tensor is

```math
C_a^{(3,p)}=
\frac1{a_{G,p}}
\sum_b
K_{ab}^{(p)}
\Delta\xi_{ab}^{\otimes3}.
```

These classwise tensors determine whether different profile regions have
different continuum regimes.

# 6. Exact global tensors

The route-averaged mean increment is

```math
m_{G,p}=
\sum_{a,b}
F_{ab}^{(p)}
\Delta\xi_{ab}.
```

The raw quadratic tensor is

```math
Q_{G,p}=
\sum_{a,b}
F_{ab}^{(p)}
\Delta\xi_{ab}
\Delta\xi_{ab}^\mathsf T.
```

The centered covariance is

```math
C_{G,p}=
Q_{G,p}-
m_{G,p}m_{G,p}^\mathsf T.
```

The third moment is

```math
M_{G,p}^{(3)}=
\sum_{a,b}
F_{ab}^{(p)}
\Delta\xi_{ab}^{\otimes3}.
```

The canonical first-pass time scale is

```math
a_{G,p}=
\mathrm{tr}C_{G,p}.
```

When

```math
a_{G_n,p_n}\to0,
```

one primitive edge represents $a_{G_n,p_n}$ units of continuum time.

# 7. An exact telescoping identity for the drift

Under the uniform length-$p$ route ensemble,

```math
\sum_{j=0}^{p-1}
\left[
X(V_{j+1})-X(V_j)
\right]=
X(V_p)-X(V_0).
```

After expectation and division by $p$,

```math
m_{G,p}=
\frac{
\mathbb E_p[X(V_p)]-
\mathbb E_p[X(V_0)]
}{
p
}.
```

Equivalently,

```math
m_{G,p}=
\sum_a
\left(
\pi_a^{\mathrm{in}}-
\pi_a^{\mathrm{out}}
\right)\xi_a.
```

Because $X$ is bounded,

```math
|m_{G,p}|
\le
\frac{\mathrm{diam}(X_G)}p.
```

The globally route-averaged drift is therefore a horizon-boundary effect. It
normally vanishes as $p\to\infty$, so global mean drift alone cannot determine
whether the local continuum dynamics has drift.

The local quantities

```math
b_a^{(p)}
```

must be retained. They can remain nonzero even while the globally averaged
drift vanishes.

The identity also provides an audit:

```math
p,m_{G,p}=
\mathbb E_p[X(V_p)]-\mathbb E_p[X(V_0)].
```

# 8. Markov-closure or lumpability defect

A class transition matrix is exact only if nodes with the same profile class
have the same conditional transition law over classes.

For remaining horizon $k$, define

```math
P_k(v,w)=
\frac{
A_{vw}r_{k-1}(w)
}{
r_k(v)
}.
```

For $v\in C_a$, let

```math
P_k(v,C_b)=
\sum_{w\in C_b}P_k(v,w).
```

Exact lumpability requires

```math
P_k(v,C_b)=
P_k(v',C_b)
```

for every $v,v'\in C_a$.

Define a route-weighted mean class transition

```math
\overline P_{ab,k}=
\sum_{v\in C_a}
\omega_{a,k}(v)
P_k(v,C_b),
```

where $\omega_{a,k}$ is the route-occupancy distribution inside $C_a$.

The squared closure defect is

```math
\mathfrak E_{a,k}^2=
\sum_{v\in C_a}
\omega_{a,k}(v)
\sum_b
\left[
P_k(v,C_b)-
\overline P_{ab,k}
\right]^2.
```

Aggregate it as

```math
\mathfrak E_{G,p}=
\max_{\substack{k\text{ in bulk}\\a}}
\mathfrak E_{a,k}.
```

The condition

```math
\mathfrak E_{G,p}=0
```

means that the six-coordinate state is exactly Markov-complete at that horizon.
Along a sequence of systems, convergence

```math
\mathfrak E_{G_n,p_n}\to0
```

means that it becomes asymptotically Markov-complete.

If it does not vanish, increase the profile dictionary:

```math
6\text{-coordinate signature}
\longrightarrow
\text{full one-round pair-profile histogram}
\longrightarrow
\text{stabilized profile}.
```

The defect provides a data-driven stopping rule for refinement depth.

# 9. Bulk-plateau defect

The finite route law depends on the remaining horizon. The relevant test is
whether an autonomous bulk generator emerges.

At route position $j$, let

```math
k=p-j
```

be the remaining horizon, and compute the class transition matrix

```math
K^{(p,j)}.
```

Choose a bulk fraction $0<\varepsilon<1/2$, for example $\varepsilon=0.2$,
and define

```math
J_{\mathrm{bulk}}=
\{
j:
\varepsilon p\le j\le(1-\varepsilon)p
\}.
```

Define $\overline K_{\mathrm{bulk}}$ by

```math
\overline K_{\mathrm{bulk}}=
\frac1{|J_{\mathrm{bulk}}|}
\sum_{j\in J_{\mathrm{bulk}}}
K^{(p,j)}.
```

The plateau defect is

```math
\mathfrak P_{G,p}=
\max_{j\in J_{\mathrm{bulk}}}
\left|
K^{(p,j)}-
\overline K_{\mathrm{bulk}}
\right|_{\mathrm{row},\pi}.
```

A convenient route-weighted norm is

```math
|M|_{\mathrm{row},\pi}^2=
\sum_a\pi_a
\sum_bM_{ab}^2.
```

The autonomous continuum generator requires

```math
\mathfrak P_{G_n,p_n}\to0.
```

If it converges instead to a nonzero profile as a function of $j/p$, the
continuum limit is nonautonomous.

# 10. Small-jump and Gaussian-closure diagnostics

Define the maximal route-relevant jump

```math
J_{\max}=
\max_{e:f_e^{(p)}>0}
|\Delta X_e|.
```

The basic small-jump ratio is

```math
\mathfrak J_{G,p}=
\frac{J_{\max}}{\sqrt{a_{G,p}}}.
```

For a conventional triangular-array diffusion limit, the stronger useful
condition is that the largest absolute jump tends to zero and the Lindeberg
contribution vanishes:

```math
\mathfrak L_{G,p}(\epsilon)=
\frac1{a_{G,p}}
\sum_e
f_e^{(p)}
|\Delta X_e|^2
\mathbf1_{
{
|\Delta X_e|>\epsilon
}
}.
```

The Gaussian closure requires

```math
\mathfrak L_{G_n,p_n}(\epsilon)\to0
```

for every $\epsilon>0$.

The scaled third-moment diagnostic is

```math
\mathfrak K_{3,G,p}=
\frac{
|M_{G,p}^{(3)}|
}{
a_{G,p}
}.
```

In an ordinary diffusive regime,

```math
\mathfrak K_{3,G_n,p_n}\to0.
```

If it remains finite or diverges, inspect the full jump measure rather than
forcing a diffusion approximation.

# 11. Route-growth and gauge diagnostics

Compute

```math
T_0,T_1,\ldots,T_h,
```

where $h$ is the graph height.

The finite route-growth sequence is

```math
\beta_p=
\log\frac{T_{p+1}}{T_p}.
```

For finite DAGs, it eventually collapses because $T_p=0$ beyond the maximum
path length. The relevant diagnostic is an interior plateau across graph
families of increasing height.

The mean bulk growth rate is

```math
\overline\beta_{\mathrm{bulk}}=
\frac1{|P_{\mathrm{bulk}}|}
\sum_{p\in P_{\mathrm{bulk}}}\beta_p
```

and

```math
\mathfrak B_G=
\max_{p\in P_{\mathrm{bulk}}}
|\beta_p-\overline\beta_{\mathrm{bulk}}|.
```

If

```math
\mathfrak B_{G_n}\to0,
```

it follows that

```math
\beta_0=
\lim\overline\beta_{\mathrm{bulk}}
```

is the carrier route-growth rate.

The finite residual gauge rate is

```math
\Omega=
\lim_n
\frac{
\overline\beta_{\mathrm{bulk}}(G_n)-\beta_0
}{
a_{G_n,p_n}
}.
```

The coefficient enters the continuum master resolvent.

# 12. A computable convergence criterion

For a graph sequence $G_n$, horizons $p_n$, and profile levels $r_n$, the
diffusion candidate is supported when

```math
a_n\to0,
\qquad
\mathfrak L_n(\epsilon)\to0
\quad\forall\epsilon>0,
\qquad
\mathfrak K_{3,n}\to0,
\qquad
\mathfrak E_n\to0,
\qquad
\mathfrak P_n\to0,
```

and the scaled local tensors

```math
b_{a,n},
\qquad
A_{a,n}
```

converge as functions of the profile coordinate.

If small jumps fail, retain the empirical class-jump measure

```math
\nu_n(\xi_a,dz)=
\frac1{a_n}
\sum_b
K_{ab}^{(p_n)}
\delta_{\xi_b-\xi_a}(dz)
```

and test it for Lévy convergence instead.

# 13. Streaming implementation

The first-pass implementation can be written as follows.

```c
for each graph G {
    n = number_of_vertices(G);

    // Minimal six-coordinate dictionary.
    d_out = A * ones;
    d_in  = transpose(A) * ones;

    q_pp = A * d_out;             // A^2 1
    q_mm = transpose(A) * d_in;   // (A^T)^2 1
    q_pm = A * d_in;              // A A^T 1
    q_mp = transpose(A) * d_out;  // A^T A 1

    for (v = 0; v < n; ++v) {
        signature[v] = {
            d_out[v], d_in[v],
            q_pp[v], q_mm[v],
            q_pm[v], q_mp[v]
        };

        X[v] = {
            d_out[v] / (double)n,
            d_in[v]  / (double)n,
            q_pp[v]  / (double)(n*n),
            q_mm[v]  / (double)(n*n),
            q_pm[v]  / (double)(n*n),
            q_mp[v]  / (double)(n*n)
        };
    }

    class_id = canonical_group_equal_signatures(signature);

    // Route-count dynamic programming.
    R[0] = ones;
    L[0] = ones;

    for (k = 1; k <= height; ++k) {
        R[k] = A * R[k-1];
        L[k] = transpose(A) * L[k-1];
        T[k] = sum(R[k]);
    }

    for each selected horizon p {
        clear W_class;
        clear mean;
        clear second;
        clear third;
        flow_total = 0;

        for each directed edge e = (v, w, multiplicity) {
            wide_integer W = 0;

            for (j = 0; j < p; ++j) {
                W += multiplicity
                   * L[j][v]
                   * R[p-j-1][w];
            }

            flow_total += W;
            W_class[class_id[v]][class_id[w]] += W;

            delta = X[w] - X[v];

            mean  += W * delta;
            second += W * outer(delta, delta);
            third += W * tensor3(delta);
        }

        assert(flow_total == p * T[p]);

        denominator = (wide_real)(p * T[p]);

        mean   /= denominator;
        second /= denominator;
        third  /= denominator;

        covariance = second - outer(mean, mean);
        a = trace(covariance);

        emit_coefficients(
            graph_id, n, p,
            T[p], T[p+1],
            a, mean, covariance, third,
            W_class
        );
    }
}
```

The identity

```math
\sum_eW_e=pT_p
```

makes overflow or normalization errors easy to detect.

# 14. Suggested output record

A compact binary output record for each $(G,p)$ should contain:

```text
graph_id
n
edge_count
height
p
num_node_classes

T_p
T_p_plus_1
log_growth_ratio

time_scale_a
mean_increment[6]
covariance_upper_triangle[21]
third_tensor_symmetric[56]

max_jump
lindeberg_bins[]
bulk_plateau_defect
lumpability_defect

class_sizes[]
class_coordinates[][6]
class_flow_sparse[(source_class, target_class, weight)]
```

The symmetric tensor sizes are:

```math
\frac{6(6+1)}2=21
```

for the quadratic tensor and

```math
\binom{6+3-1}{3}=56
```

for the symmetric cubic tensor.

# 15. Hierarchy beyond the six-coordinate pass

The refinement hierarchy begins with the level-zero dictionary

```math
X^{[0]}=
(d^+,d^-,A^2\mathbf1,(A^\mathsf T)^2\mathbf1,
AA^\mathsf T\mathbf1,A^\mathsf TA\mathbf1).
```

The calculation reuses the existing communication counts.

## Profile-histogram refinement

At the first level, let $c_1(u,v)$ be the canonical one-round ordered-pair
profile key. Define

```math
x_u(c,d)=
\frac1n
\left|\{
v:
(c_1(u,v),c_1(v,u))=(c,d)
\}\right|.
```

Use sparse histograms and a square-root embedding

```math
Y_u(c,d)=\sqrt{x_u(c,d)}.
```

It follows that

```math
|Y_u-Y_w|_2^2
```

is twice the squared Hellinger distance between their exact one-round node
profiles.

The construction supplies an information-geometric metric without arbitrary
weights among profile fields.

At refinement level $r$, replace $c_1$ by $c_r$ and stop when
$\mathfrak E_{G,p,r}$ is below tolerance or reaches zero exactly.

Thus the Markov-closure defect, rather than graph-isomorphism separation,
selects the required refinement depth.

# 16. Literature relation

The vanishing-jump ratio $\mathfrak J_{G,p}$ and the Lindeberg quantity
$\mathfrak L_{G,p}(\epsilon)$ of section 10, assembled into the criterion of
section 12, are finite-graph versions of two conditions in the generator
convergence scheme for triangular arrays. That scheme requires in addition
compact containment of the approximating family and uniqueness of the limiting
martingale problem, and its conditions are asymptotic along the sequence
$(G_n,p_n,r_n)$ rather than properties of a single pair $(G,p)$. Neither
additional requirement is a function of the quantities computed in section 13,
so the diagnostics can fall below tolerance on a finite sample without the
convergence conclusion following.

Reference:

- S. N. Ethier and T. G. Kurtz, *Markov Processes: Characterization and
  Convergence*, Wiley, 1986, Chapter 4.
