# 1. Refinement-stability result

Across two terminal sizes, six checkpoint pairs per size, four singular-value cutoffs, and retained ranks from 12 through 18, all audits reported

```text
slower_modes=0
status=PASS
```

relative to the threshold

```math
J>-1.8.
```

The $J\approx-2$ slow sector therefore survives the first dictionary refinement.

No evidence appeared for a hidden mode that would close the relaxation gap.

# 2. Scope of the result

The nested-dictionary test goes beyond repeating the original fit with more samples: it shows that the slow spectral boundary remains stable when degree-two moments are added.

It does not prove the same gap for every higher refinement; in particular, the following remain untested:

* full one-round node-profile histograms;
* sparse Hellinger embeddings of refined pair colors;
* stabilized WL profile coordinates;
* non-polynomial cylinder observables.

# 3. Need for refinement robustness

The initial configuration spectrum used six graph-profile coordinates, so its stable projected gap could still be artificial if an omitted coordinate relaxed more slowly.

The refinement test therefore enlarged the emitted trajectory dictionary to 27 features containing:

* the original first moments;
* degree-two products and second moments;
* duality-related partners;
* exact redundant combinations retained initially and removed numerically by rank truncation.

The analysis specifically sought a mode with Jacobian rate closer to zero than the established $J\approx-2$ slow sector.

# 4. Trajectory generation

The refined sampler emitted exact uniform labeled-DAG trajectories at:

```math
N=128,
\qquad
N=256.
```

For each terminal size, 100,000 independent samples were generated.

The checkpoint sets were

```math
64,80,96,112
```

for terminal 128 and

```math
128,160,192,224
```

for terminal 256.

The full $N=128$ run took about 5.6 seconds wall time; the $N=256$ run took about 58 seconds on 32 hardware threads.

# 5. Two nested dictionaries

The audit compared the original first-moment dictionary, `r0_first_moments`, whose effective numerical rank was four after exact symmetry reduction, with the refined degree-two dictionary, `r1_degree2`, whose numerical rank varied between approximately 12 and 18 according to the interval and singular-value cutoff.

The rank variation was expected: several new coordinates become nearly linearly dependent as the profile concentrates near its fixed point.

# 6. Singular-value cutoff sweep

The pseudoinverse threshold was varied over

```math
10^{-7},
3\times10^{-8},
10^{-8},
3\times10^{-9}.
```

The cutoff sweep changed the retained refined rank substantially: approximately 13--18 at terminal size 128 and 12--18 at terminal size 256.

A genuine slow mode should persist over a stable threshold range; one appearing only when near-null covariance directions are inverted is not reliable.

# 7. Terminal-128 results

At the reference cutoff

```math
\mathrm{rcond}=10^{-8},
```

the original dictionary produced slowest rates between approximately

```math
-2.034
\quad\text{and}\quad
-2.010.
```

The refined dictionary produced slowest rates between approximately

```math
-2.013
\quad\text{and}\quad
-1.984.
```

The shortest late interval

```math
96\to112
```

had refined rank 16 and slowest rate

```math
-1.98385.
```

Across the full cutoff sweep, no refined mode crossed the preregistered slow threshold

```math
-1.8.
```

# 8. Terminal-256 results

At

```math
\mathrm{rcond}=10^{-8},
```

The original dictionary again gave slowest rates close to $-2$, while the refined dictionary ranged from approximately

```math
-2.006
```

to

```math
-1.935.
```

The least negative estimate occurred for the earliest interval

```math
128\to160,
```

where finite-size effects and covariance conditioning are strongest.

Later and longer intervals moved closer to $-2$, including

```math
-2.00037
```

for

```math
192\to224.
```

No interval produced a mode slower than $-1.8$.

# 9. Predictive fit did not materially improve

The refined dictionary changed multistep $R^2$ only in the third or fourth decimal place; for example, representative pairs gave:

```math
R^2\approx0.64,
0.44,
0.32,
0.69,
0.50,
0.73
```

for both the original and refined dictionaries.

The extra features did not uncover a large missing deterministic component; their scientific value was spectral, testing whether a hidden slow direction existed.

# 10. Practical stopping rule

The refinement hierarchy should be continued only when one of the following occurs:

1. the projected Markov-closure defect remains non-vanishing;
2. a new retained singular direction is statistically stable;
3. the slow spectral boundary changes beyond its bootstrap error;
4. an independently motivated observable is absent from the current dictionary.

Blindly increasing the feature dimension would amplify pseudoinverse noise without necessarily adding physical information.
