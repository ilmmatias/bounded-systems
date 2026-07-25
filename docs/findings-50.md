# 1. Why refinement robustness was necessary

The first configuration spectrum was extracted from six graph-profile coordinates. A stable gap in that projection could still be artificial if an omitted profile coordinate relaxed more slowly.

The next test therefore enlarged the emitted trajectory dictionary to 27 features containing:

* the original first moments;
* degree-two products and second moments;
* duality-related partners;
* exact redundant combinations retained initially and removed numerically by rank truncation.

The analysis searched specifically for a mode with Jacobian rate closer to zero than the established $J\approx-2$ slow sector.

# 2. Exact trajectory generation

The refined sampler emitted exact uniform labeled-DAG trajectories at:

$$
N=128,
\qquad
N=256.
$$

For each terminal size, 100,000 independent samples were generated.

The checkpoint sets were

$$
64,80,96,112
$$

for terminal 128 and

$$
128,160,192,224
$$

for terminal 256.

The full $N=128$ run completed in about 5.6 seconds wall time, while the $N=256$ run completed in about 58 seconds on 32 hardware threads.

# 3. Two nested dictionaries

The audit compared:

## Original first-moment dictionary

$$
r0\_\mathrm{first\_moments}
$$

with effective numerical rank four after exact symmetry reduction.

## Refined degree-two dictionary

$$
r1\_\mathrm{degree2}
$$

with numerical rank varying between approximately 12 and 18, depending on interval and singular-value cutoff.

The rank variation was expected: several new coordinates become nearly linearly dependent as the profile concentrates near its fixed point.

# 4. Singular-value cutoff sweep

The pseudoinverse threshold was varied over

$$
10^{-7},
3\times10^{-8},
10^{-8},
3\times10^{-9}.
$$

This moved the retained refined rank substantially, for example:

* terminal 128: roughly 13-18;
* terminal 256: roughly 12-18.

A genuine slow mode should remain visible over a stable range of thresholds. A mode that appears only when near-null covariance directions are inverted is not reliable.

# 5. Terminal-128 results

At the reference cutoff

$$
\mathrm{rcond}=10^{-8},
$$

the original dictionary produced slowest rates between approximately

$$
-2.034
\quad\text{and}\quad
-2.010.
$$

The refined dictionary produced slowest rates between approximately

$$
-2.013
\quad\text{and}\quad
-1.984.
$$

The shortest late interval

$$
96\to112
$$

had refined rank 16 and slowest rate

$$
-1.98385.
$$

Across the full cutoff sweep, no refined mode crossed the preregistered slow threshold

$$
-1.8.
$$

# 6. Terminal-256 results

At

$$
\mathrm{rcond}=10^{-8},
$$

the original dictionary again gave slowest rates close to $-2$, while the refined dictionary ranged from approximately

$$
-2.006
$$

to

$$
-1.935.
$$

The least negative estimate occurred for the earliest interval

$$
128\to160,
$$

where finite-size effects and covariance conditioning are strongest.

Later and longer intervals moved closer to $-2$, including

$$
-2.00037
$$

for

$$
192\to224.
$$

No interval produced a mode slower than $-1.8$.

# 7. Predictive fit did not materially improve

The refined dictionary changed the multistep $R^2$ only in the third or fourth decimal place. For example, representative pairs gave:

$$
R^2\approx0.64,
0.44,
0.32,
0.69,
0.50,
0.73
$$

for both the original and refined dictionaries.

This means the extra features did not uncover a large missing deterministic component. Their scientific value was instead spectral: they tested whether a hidden slow direction existed.

# 8. Robust conclusion

Across:

* two terminal sizes;
* six checkpoint pairs per terminal size;
* four singular-value cutoffs;
* retained ranks from 12 through 18;

all audits reported

```text
slower_modes=0
status=PASS
```

relative to the threshold

$$
J>-1.8.
$$

Therefore

$$
\text{the }J\approx-2\text{ slow sector survives the first dictionary refinement.}
$$

No evidence appeared for a hidden mode that would close the relaxation gap.

# 9. What this does and does not establish

This result is stronger than repeating the original fit with more samples. It tests a nested observable space and shows that the slow spectral boundary is stable when degree-two moments are added.

It does not prove that every higher refinement has the same gap. In particular, the following remain untested:

* full one-round node-profile histograms;
* sparse Hellinger embeddings of refined pair colors;
* stabilized WL profile coordinates;
* non-polynomial cylinder observables.

# 10. Practical stopping rule

The refinement hierarchy should be continued only when one of the following occurs:

1. the projected Markov-closure defect remains non-vanishing;
2. a new retained singular direction is statistically stable;
3. the slow spectral boundary changes beyond its bootstrap error;
4. an independently motivated observable is absent from the current dictionary.

Blindly increasing the feature dimension would amplify pseudoinverse noise without necessarily adding physical information.
