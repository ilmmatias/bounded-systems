# 1. The completed compositional distance sector

Apply the transfer theorem of `findings-84.md` to the decorated three-layer
sector of `findings-83.md`. The payload parts $L_0,L_1,L_2$ have equal
normalized masses and nonzero blocks

```math
\Gamma_{01}(x,y)=\mathbf 1_{\{x<y\}},
```

the second adjacent block is

```math
\Gamma_{12}(y,z)=\mathbf 1_{\{y<z\}},
```

and

```math
\Gamma_{02}(x,z)=(z-x)_+.
```

The payload edge density is

```math
e=\frac7{54}.
```

Choose

```math
\beta=\frac1{12},
\qquad
 d=c=\frac5{16},
```

together with

```math
(s_0,s_1,s_2)
=
\left(
\frac1{72},
\frac1{36},
\frac1{24}
\right),
```

and

```math
(t_0,t_1,t_2)
=
\left(
\frac1{18},
\frac5{72},
\frac1{12}
\right).
```

These masses sum to one after adding the scaled payload, the three source
markers, the three sink markers, and the two global compensators.

# 2. Exact graph-intrinsic part signatures

The global source and sink compensators have degree pairs

```math
\delta(D)
=
\left(0,\frac{593}{9720}\right),
```

and

```math
\delta(C)
=
\left(\frac{593}{9720},0\right).
```

The source markers have pairs

```math
\delta(S_0)=\left(0,\frac1{12}\right),
\qquad
\delta(S_1)=\left(0,\frac7{72}\right),
\qquad
\delta(S_2)=\left(0,\frac19\right).
```

The sink markers have pairs

```math
\delta(T_0)=\left(\frac1{24},0\right),
\qquad
\delta(T_1)=\left(\frac1{18},0\right),
\qquad
\delta(T_2)=\left(\frac5{72},0\right).
```

The payload parts have constant pairs

```math
\delta(L_0)
=
\left(\frac{73}{288},\frac{85}{288}\right),
```

the middle payload part has

```math
\delta(L_1)
=
\left(\frac{77}{288},\frac{89}{288}\right),
```

and

```math
\delta(L_2)
=
\left(\frac9{32},\frac{31}{96}\right).
```

All eleven degree pairs are distinct. The complete partition is therefore
recoverable from the unmarked directed kernel through one finite
rooted-degree polynomial.

# 3. Absolute compositional forcing

The distinct degree pairs of the preceding section identify all eleven
completed parts, which gives the following absolute forcing statement.

## Theorem 1. Uncolored compositional distance completion

The tagged-compensated completion of the three-layer distance sector is
absolutely finitely forcible in the full central DAG boundary.

## Proof

The part polynomial and mass constraints recover all eleven completed parts.
The relative forcing result of `findings-83.md` then forces the two adjacent
half-kernels, aligns their middle coordinate, and forces the shortcut block
to equal their normalized composition. The marker blocks are deterministic.
The one-sided Gram defects force the two compensator blocks. Theorem 2 of
`findings-84.md` completes the argument.

No external colors or latent layer labels remain in the final selector. Every
decorated expression used in the proof is converted into an ordinary finite
quantum-DAG expression through the graph-intrinsic part indicators.

# 4. The derived shortcut law

Inside the selected uncolored sector, the two-step path density through the
recovered middle part is

```math
P_{02}(x,z)
=
\frac{\beta}{3}(z-x)_+.
```

The shortcut block satisfies

```math
\Gamma_{02}(x,z)
=
\frac3\beta P_{02}(x,z)
=
36P_{02}(x,z).
```

The coefficient differs from `findings-83.md` because the complete payload
has been scaled to mass $\beta=1/12$. The relation itself is unchanged: the
shortcut probability is the normalized volume of admissible intermediate
states.

Set

```math
R(x,z)=\Gamma_{02}(x,z)-36P_{02}(x,z).
```

The valid simple-DAG forcing observable is the one-sided Gram defect

```math
\mathcal G(R)
=
\int_{L_0^2}
\left[
 \int_{L_2}R(x,z)R(x',z)\,d\mu(z)
\right]^2
\,d\mu(x)d\mu(x').
```

It vanishes exactly when the shortcut block equals the normalized path
composition. After substituting the graph-intrinsic part indicators, it is an
ordinary uncolored quantum-DAG observable assembled from simple DAG patterns.

# 5. Scope of the forcing result

Theorem 1 constrains the completed eleven-part architecture. For the
standalone one-population kernel

```math
(x,y)\longmapsto(y-x)_+
```

absolute finite forcibility without auxiliary parts remains open, and the
completion selects the compositional scaffold rather than identifying it with
a single undivided population.

Exact calculations reproduce the payload degree functions, the edge density
$7/54$, all eleven completed degree pairs, pointwise degree flattening,
normalized path composition, and separation of the graph-intrinsic parts.
