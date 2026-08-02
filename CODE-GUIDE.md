# Code Guide for Computational Research

## Scope

This guide governs source-code style, local naming, control-flow layout,
comments, file organization, error handling, command-line interfaces,
computational reproducibility, and edits to existing C++, Python, and Bash
code in this repository.

The guide is intentionally more specific than a formatter configuration.
`clang-format`, Ruff, and `shfmt` can normalize indentation and line wrapping,
but they cannot decide whether a function reads as a sequence of mathematical
operations, whether a local name is needlessly verbose, whether a blank line is
required between two independent checks, or whether an abstraction exists only
because generated code tends to over-structure simple programs.

The governing principles are directness, visible logical structure, short local
names, exact correspondence with the mathematics, repository-local idiom,
minimal abstraction, and auditable numerical behavior. Code should read as a
clear implementation of one calculation. It should not read as framework code
unless the repository actually contains a framework.

This guide is normative. Existing code may predate some rules. New code and
substantive rewrites shall follow them unless a local constraint is documented.

## Repository basis

The preferred style is represented by the existing compact C++ drivers and
artifact writers in `src/`, the exact verification scripts in `scripts/`, and
the linear experiment launchers already used by the repository.

The following characteristics are intentional:

- one-purpose drivers may remain in one translation unit;
- long calculations may remain in one function when their stages are linear and
  locally readable;
- blank lines separate logical stages even when a formatter would not require
  them;
- local names are shorter than public API names;
- formatted file output uses RAII streams and `std::print`;
- mathematical operations are visible in the source rather than hidden behind
  generic utility layers;
- exact checks use assertions or explicit failures close to the formula being
  checked;
- scripts preserve parameters, seeds, and output locations.

The project does not use file count, function length, class count, or
abstraction count as proxies for quality.

# 1. General source structure

## 1.1 Governing principle

A source file shall make the computational path visible. A reader should be able
to identify the inputs, preprocessing, main calculation, diagnostics, and output
without reconstructing them from generic wrappers or tracing several one-use
helpers.

Use structure to expose the calculation, not to satisfy arbitrary size rules.

## 1.2 One-purpose files

A file may contain one complete command-line calculation. Do not split a driver
into several files merely because the implementation is long.

A new file is justified when at least one of the following holds:

1. the code defines a reusable domain object used by multiple translation units;
2. the code implements an independently testable algorithm with a stable
   interface;
3. the code is generated or platform-specific and should be isolated;
4. the existing file would otherwise mix unrelated programs or mathematical
   constructions;
5. separate compilation materially improves build behavior.

A new file is not justified merely because a function exceeds a preferred line
count.

Do not create structures such as:

```text
route_scaling_manager.cxx
route_scaling_processor.cxx
route_scaling_context.cxx
route_scaling_result_builder.cxx
route_scaling_utils.cxx
```

when the code implements one route-scaling executable.

## 1.3 Linear drivers

A linear driver is acceptable when it follows a genuine calculation:

```text
parse options
load or generate samples
construct the reference law
accumulate conditional moments
fit scaling exponents
score closure candidates
write artifacts
```

Keep these stages in their mathematical order. Separate them with blank lines
and, when useful, one short comment naming the operation.

Do not fragment every stage into a helper solely to make the main function look
short. Extract a helper when it does one of the following:

- names a mathematical operation that is reused or independently checked;
- removes substantial duplicated logic;
- isolates a stable parsing or serialization contract;
- reduces nesting or makes an invariant explicit;
- permits a focused unit test.

A helper that is called once, takes twelve parameters, mutates several outputs,
and has no independent meaning usually makes the code harder to read.

## 1.4 Logical paragraphs

Code has paragraphs. A paragraph is a consecutive group of statements that
performs one local task.

Separate independent tasks with one blank line. Examples include:

- validation of different option families;
- completion of allocation before accumulation begins;
- completion of one estimator before another estimator is computed;
- construction of data before diagnostics consume it;
- opening a file before output formatting begins;
- a loop followed by a separate aggregate check;
- a conditional early exit followed by the normal path.

Do not write a wall of consecutive checks merely because all checks concern the
same options object.

Bad:

```cpp
for (int n : opt.predClasses) {
    if (n < 2 || std::cmp_greater(n, opt.vertices)) {
        throw std::invalid_argument("invalid predictive class count");
    }
}
if (opt.targetBins.empty()) {
    throw std::invalid_argument("missing target bins");
}
const int maxBins = opt.targetBins.back();
for (int n : opt.targetBins) {
    if (n < 2 || maxBins % n != 0) {
        throw std::invalid_argument("target bins are not nested");
    }
}
if (opt.refBins < 16) {
    throw std::invalid_argument("reference bin count is too small");
}
```

Preferred:

```cpp
for (int n : opt.predClasses) {
    if (n < 2 || std::cmp_greater(n, opt.vertices)) {
        throw std::invalid_argument(
            "--predictive-classes values must lie in 2..vertices");
    }
}

if (opt.targetBins.empty()) {
    throw std::invalid_argument("--target-bins must not be empty");
}

const int maxBins = opt.targetBins.back();

for (int n : opt.targetBins) {
    if (n < 2 || maxBins % n != 0) {
        throw std::invalid_argument(
            "--target-bins must be nested divisors of the maximum");
    }
}

if (opt.refBins < 16) {
    throw std::invalid_argument(
        "--reference-bins must be at least 16");
}
```

## 1.5 Vertical density

Do not optimize for the fewest lines. Compact code is not code with all blank
lines removed.

A source region requires revision when several of the following occur together:

1. more than four independent checks appear without a blank line;
2. setup, accumulation, and reporting appear in one uninterrupted block;
3. a loop begins immediately after an unrelated declaration;
4. a declaration is visually detached from the statements that use it;
5. comments divide stages that blank lines should already divide;
6. a reader must inspect variable names to discover where one task ends;
7. a long initializer, loop, or lambda is followed immediately by another major
   operation.

Do not insert a blank line between every statement. The unit is the logical
paragraph, not the individual line.

## 1.6 Horizontal density

The configured line limit is a maximum, not a target. Prefer lines that expose
one operation.

Do not compress multiple conditions, transformations, or output fields into one
line merely because the formatter permits it.

Do not manually create severe vertical formatting for an expression that is
clear on two or three lines. Let the formatter handle ordinary wrapping, then
revise the expression if the result remains difficult to read.

## 1.7 Ordering within a file

For a C++ translation unit, use the following order unless a stronger local
reason applies:

1. matching project header;
2. other project headers;
3. standard-library headers;
4. unnamed-namespace constants and local types;
5. parsing and small local support functions;
6. core calculation functions;
7. output functions;
8. public entry point or `main`.

For a Python script, use:

1. shebang when executable;
2. module docstring;
3. `from __future__` imports;
4. standard-library imports;
5. third-party imports;
6. constants and symbolic declarations;
7. pure mathematical helpers;
8. experiment or verification functions;
9. `main`;
10. the `__main__` guard.

For Bash, place option validation and path discovery before tool invocation.

# 2. Naming

## 2.1 Governing principle

A name shall be as short as its scope permits and as descriptive as its role
requires. Longer names are appropriate for public interfaces and persistent
state. Shorter names are appropriate for local values whose meaning is fixed by
a nearby calculation.

Do not encode the entire surrounding sentence in an identifier.

## 2.2 Local names

Preferred local names include:

```text
opt
out
path
root
graph
route
level
count
size
bins
maxBins
refBins
samples
weights
mean
cov
row
col
src
dst
pos
step
rate
scale
error
```

These names are acceptable because their scopes and types establish their
meaning.

Avoid generated prose names such as:

```text
maximumTargetBins
currentTransitionPositionIndex
numberOfPredictiveClasses
normalizedConditionalCovarianceAccumulator
intrinsicCoordinatePredictionResult
referenceDistributionDiagnosticsOutputPath
```

Preferred replacements depend on scope:

```text
maxBins
pos
classCount
condCov
pred
outPath
```

Do not shorten a name until it becomes cryptic. `condCov` is an acceptable
replacement for `conditionalCovariance` may be appropriate as a field in a
result type. `cc`, `cv2`, or `tmp3` is not an acceptable replacement.

## 2.3 Public names

Public types, functions, and fields may be more descriptive because their use is
not confined to one local paragraph.

Preferred:

```cpp
struct RouteScalingOptions;
struct ConditionalMoments;
RouteProfile buildReferenceRoute(...);
void writeScalingReport(...);
```

Do not add words that contribute no distinction:

```cpp
struct RouteScalingOptionsDataStructure;
class RouteScalingAnalysisManager;
RouteProfile calculateAndReturnReferenceRouteProfile(...);
```

## 2.4 Generic suffixes and nouns

Avoid generic architecture nouns unless they identify a real architectural
role:

- `Manager`
- `Processor`
- `Handler`
- `Controller`
- `Context`
- `Factory`
- `Builder`
- `Service`
- `Engine`
- `Provider`
- `Utility`
- `Helper`

`Parser`, `Sampler`, `Accumulator`, and `Writer` are acceptable when the type
actually owns that stable responsibility.

Do not name a namespace, file, or class `utils` when its members share a more
specific domain.

## 2.5 Booleans

Boolean names shall state the condition positively where possible:

```cpp
bool emitProfiles;
bool keepSamples;
bool isNested;
bool hasReference;
```

Avoid ambiguous names:

```cpp
bool flag;
bool enabled;
bool valid;
bool check;
```

Negated boolean names are permitted only when the negative condition is the
domain concept, such as `nonMarkovian`.

## 2.6 Units and scales

Include units or scaling in a name when omission could cause a real numerical
mistake:

```cpp
double seconds;
double stepVariance;
double scaledDrift;
double invSampleCount;
```

Do not append units to every dimensionless mathematical coordinate.

## 2.7 Index names

Use conventional short indices in small loops:

```cpp
for (size_t i = 0; i < rows.size(); ++i) {
    ...
}
```

Use a domain name when the index survives several statements or when multiple
indices coexist:

```cpp
for (size_t level = 0; level < counts.size(); ++level) {
    ...
}
```

Do not use `index` everywhere merely because it is more explicit than `i`.

## 2.8 Symmetry with mathematical notation

When code implements a displayed formula, align local names with the manuscript
notation where this does not reduce readability.

If the derivation uses `p`, `r`, and `u=r/p`, the implementation may use `p`,
`r`, and `u` inside a compact local calculation. Do not replace them with
`routeLengthParameter`, `currentRouteStepIndex`, and
`normalizedContinuumRoutePosition`.

Use descriptive fields at boundaries and conventional symbols inside the exact
formula.

# 3. C++23 style

## 3.1 Required language and toolchain

The repository uses C++23, Clang, libc++, and the repository's configured
ThinLTO mode.

Do not:

- invoke `g++`;
- configure GCC as the C++ compiler;
- add libstdc++ fallback logic;
- claim that a GCC build validates a change;
- replace a working Clang/libc++ idiom to support unsupported toolchains.

All documented build commands shall use the repository's Clang configuration.

## 3.2 Headers

Include what the file uses. Do not rely on transitive includes.

Prefer standard headers that directly provide the used facility. Keep project
headers above standard-library headers according to `.clang-format`.

Do not add broad convenience headers. Do not use non-standard aggregate headers
such as `<bits/stdc++.h>`.

A source file should include its matching header first when one exists.

## 3.3 Namespace use

Do not write `using namespace` at namespace scope.

An unnamed namespace is appropriate for translation-unit-local functions,
constants, and types.

Do not place project declarations in `std`.

Avoid nested namespaces that contain only one small one-purpose driver.

## 3.4 Types

Use domain types when they prevent invalid combinations or express a stable
contract. Do not wrap every integer or vector in a one-field type.

Prefer:

```cpp
struct ConditionalMoments {
    Vector mean;
    Matrix cov;
    size_t samples;
};
```

when the fields travel together through several functions.

Prefer local variables when the values exist only inside one calculation.

Use `struct` for simple records with public data. Use `class` when invariants
are maintained through an interface.

Do not generate getters and setters for passive records.

## 3.5 Const and mutation

Make local values `const` when they are not reassigned and the qualifier helps
show the data flow.

Do not add `const` mechanically to values whose role is an explicit accumulator
or loop state.

Prefer constructing a final value over declaring an empty object and assigning
it across several unrelated branches.

Mutation is acceptable for accumulators, buffers, samplers, and performance-
critical state. Keep the mutation local and visible.

## 3.6 `auto`

Use `auto` when:

- the type is obvious from the initializer;
- the type is a long iterator, range view, or template result;
- spelling the type would duplicate the function name;
- structured binding is clearer than the explicit pair or tuple type.

Prefer an explicit type when:

- the numeric representation matters;
- signedness matters;
- a conversion is being documented;
- the initializer does not reveal the semantic type;
- the code is part of a mathematical formula whose scalar type matters.

Preferred:

```cpp
const auto [end, error] = std::from_chars(...);
const int maxBins = opt.targetBins.back();
const double u = static_cast<double>(r) / p;
```

Avoid using `auto` to conceal a large or unexpected result type.

## 3.7 Numeric types and conversions

Use `size_t` for container sizes and indices that are compared directly with
container sizes. Use `int` for bounded domain counts when negative values are
meaningful during parsing or validation.

Use `std::cmp_less`, `std::cmp_greater`, and related functions when comparing
signed and unsigned values would otherwise require noisy casts.

Do not scatter `static_cast<size_t>` through control flow merely to silence a
warning. Normalize the types at an interface or use the comparison utilities.

Use explicit casts when a mathematical scaling intentionally changes type:

```cpp
const double u = static_cast<double>(r) / static_cast<double>(p);
```

Do not use C-style casts.

## 3.8 Functions

A function shall perform one coherent operation, but coherence is semantic, not
measured by line count.

Preferred function categories include:

- parse one command-line structure;
- compute one mathematical object;
- accumulate one family of statistics;
- write one artifact schema;
- run one complete one-purpose experiment.

Do not extract trivial wrappers:

```cpp
bool isTargetBinsEmpty(const Options& opt) {
    return opt.targetBins.empty();
}
```

Do not combine unrelated tasks merely because they share a few local variables.

Keep parameter lists small when practical. When several stable parameters always
travel together, introduce a record. Do not create a record for two locals used
by only one call.

## 3.9 Parameter passing

Pass small scalar values by value.

Pass read-only containers and large objects by `const&` or `std::span` as
appropriate.

Use `std::span` for borrowed contiguous sequences when ownership is irrelevant.

Use output parameters only when they are natural accumulators or when returning
a large tuple would obscure mutation. Prefer a returned record for ordinary
multi-result functions.

Do not pass a large options object into every helper when the helper needs two
fields.

## 3.10 Control flow

Prefer early validation and early exits over deep nesting.

Use braces for all control-flow bodies, including one-line bodies.

Keep conditions close to the operation they guard. Extract a predicate when it
has a domain name or is reused, not merely because it spans two lines.

Do not write chains of `else` after a branch that returns, throws, or continues.

Preferred:

```cpp
if (opt == "--vertices") {
    if (++i == args.size()) {
        throw std::invalid_argument("--vertices requires a value");
    }

    vertices = parseInt(args[i], opt);
    continue;
}
```

Do not compress parsing into nested ternaries or callback tables unless the
command set is large enough to justify them.

## 3.11 Loops and algorithms

Use a range-for loop when it states the operation directly.

Use an indexed loop when the index is part of the calculation, controls a
neighbor relation, or is required for output punctuation.

Use a standard algorithm when it makes the operation clearer than the loop.
Do not replace a clear loop with a dense chain of views, projections, lambdas,
and folds merely to appear modern.

Preferred:

```cpp
for (int bins : opt.targetBins) {
    if (bins < 2 || maxBins % bins != 0) {
        throw std::invalid_argument(
            "--target-bins must be nested divisors of the maximum");
    }
}
```

Avoid:

```cpp
if (!std::ranges::all_of(
        opt.targetBins,
        [maxBins](const auto currentTargetBinCountValue) {
            return currentTargetBinCountValue >= 2 &&
                   maxBins % currentTargetBinCountValue == 0;
        })) {
    ...
}
```

when the loop is shorter and easier to inspect.

## 3.12 Lambdas

Use a lambda for a short local operation whose meaning is clear at the call
site. Name a lambda when it is used more than once or spans several statements.

Do not place an entire stage of the calculation inside a large immediately
invoked lambda to avoid declaring locals in the surrounding scope.

Do not capture everything with `[&]` in long-lived or nontrivial lambdas. List
captures when ownership or lifetime matters.

## 3.13 Templates

Use templates for real type-generic code. Do not template a function merely
because two calls currently use `float` and `double`.

Constrain public templates when the required operations are not obvious.

Do not build a generic experiment framework around one calculation.

## 3.14 Ownership and lifetime

Use automatic storage and standard containers by default.

Do not use raw owning `new` or `delete`.

Use smart pointers only when dynamic ownership is required. Do not replace a
plain object with `std::unique_ptr` merely to delay construction.

Borrow with references, pointers, or spans according to nullability and
contiguity. A raw pointer is acceptable as a non-owning nullable pointer when
that role is clear.

## 3.15 File paths

Use `std::filesystem::path` for paths.

Do not construct paths by concatenating slash-containing strings.

Create parent directories deliberately. Do not silently redirect output to a
fallback directory.

Include the path in file-open and serialization errors.

## 3.16 File I/O

Use RAII streams for project file I/O.

Preferred:

```cpp
std::ofstream out(path);

if (!out) {
    throw std::runtime_error(
        std::format("cannot create artifact: {}", path.string()));
}

std::print(out,
           "{{\n"
           "  \"n\": {},\n"
           "  \"samples\": {}\n"
           "}}\n",
           n, samples);
```

Do not use:

- `FILE*`;
- `fopen`, `fdopen`, `fprintf`, or `fclose`;
- C stdio for project artifacts;
- long `operator<<` chains;
- manual buffer ownership for ordinary text output.

`std::print(out, ...)` is the repository idiom for formatted stream output.
Follow existing code rather than replacing it with a lower-level API.

Use binary streams only when the artifact format is actually binary.

## 3.17 Standard output and errors

Use `std::print` and `std::println`.

Write ordinary results to standard output and diagnostics to standard error.

Do not interleave progress output with machine-readable output on the same
stream.

A command that emits JSON or another machine format shall keep that stream free
of banners, timing chatter, and status prose.

## 3.18 Formatting strings

Keep a format string near its arguments. Use adjacent string literals for
multiline output.

Do not build formatted text through repeated concatenation when `std::format` or
`std::print` states the schema directly.

Do not hide a stable artifact schema behind a generic JSON-building abstraction
unless escaping, nested data, or schema evolution genuinely requires it.

## 3.19 Exceptions and failures

Throw `std::invalid_argument` for invalid command-line or API input.

Throw `std::runtime_error` for failed files, unavailable data, violated runtime
preconditions, and other execution failures.

Catch exceptions at the command boundary. Print one concise diagnostic and
return a nonzero status.

Do not catch an exception merely to continue with partial or silently degraded
results.

Do not catch `...` unless the program must perform a narrowly specified cleanup
that RAII cannot perform.

## 3.20 Assertions

Use `assert` for internal conditions that indicate a programming error and are
not required for input validation.

Use explicit exceptions or failed checks for conditions that must remain active
in release builds.

Verification programs may use assertions for exact identities when a failed
assertion is the intended experiment failure.

Do not use assertions as a replacement for checking user-provided paths or
arguments.

## 3.21 Comments

Comments shall identify mathematical meaning, invariants, non-obvious
algorithmic choices, or reasons for a constraint.

Preferred:

```cpp
// Separate within-position noise from drift variation across positions.
```

```cpp
// The Dirichlet aggregation law gives the exact marginal at route step r.
```

```cpp
// Keep the latent mark only for oracle diagnostics.
```

Avoid:

```cpp
// Loop over all thresholds.
for (double threshold : thresholds) {
```

```cpp
// Create a vector to store the results.
std::vector<Result> results;
```

```cpp
// Now calculate the covariance.
```

Do not write comments that announce activity rather than explain the operation.

Do not use promotional or vague comments such as `robust handling`, `powerful
analysis`, `comprehensive diagnostics`, or `important calculation`.

## 3.22 Section comments

A short section comment is acceptable in a long linear driver when it names a
real stage:

```cpp
// Exact reference law.
```

```cpp
// Position-conditioned moments.
```

```cpp
// Held-out closure diagnostics.
```

Do not use decorative banners:

```cpp
// ================================================================
//                  AMAZING ANALYSIS PHASE
// ================================================================
```

Do not number every local stage unless those numbers correspond to a documented
algorithm or output report.

## 3.23 Classes and object orientation

Do not introduce a class solely to group functions or avoid a long parameter
list.

Use a class when it maintains an invariant across operations, owns a resource,
or represents a domain object with meaningful behavior.

Do not generate interfaces, abstract base classes, factories, dependency
injection, or visitor hierarchies for a closed one-purpose calculation.

Prefer a free function and a record over a class with one public method.

## 3.24 Modern C++ restraint

C++23 facilities are welcome when they improve the source. They are not a goal
in themselves.

Use ranges, views, concepts, coroutines, expected-like types, and advanced
templates only when their semantics fit the task and the resulting code is
clearer than the direct alternative.

Do not replace a readable loop with a five-stage range pipeline. Do not replace
an ordinary result record with template metaprogramming. Do not use a coroutine
for a finite calculation that already fits naturally in a loop.

## 3.25 Performance

Do not optimize without evidence when the simpler implementation is adequate.

When performance matters, state the relevant cost in a comment or finding:
allocation count, asymptotic complexity, memory volume, cache behavior, or
measured runtime.

Prefer data-layout and algorithmic improvements over syntactic cleverness.

Do not obscure a formula for a micro-optimization without a benchmark and a
clear explanation.

## 3.26 Parallel code

Parallel code shall make ownership, reduction, and determinism explicit.

Use thread-local or partition-local accumulators followed by a visible reduction
when shared mutation would complicate correctness.

Document whether output depends on scheduling or floating-point reduction order.

Do not add parallelism before the serial calculation and verification path are
correct.

## 3.27 C++ anti-patterns associated with generated code

The following patterns require revision unless a local necessity is documented:

- sentence-length local identifiers;
- a function split into many one-use helpers with no mathematical names;
- a class with one method and no invariant;
- `Manager`, `Processor`, `Context`, or `Builder` types around a linear driver;
- large uninterrupted validation blocks;
- comments before every loop and declaration;
- repeated wrappers around standard-library calls;
- generic result containers whose fields are `data`, `values`, `metadata`, and
  `status`;
- deeply nested lambdas used as private functions;
- duplicated `try` and `catch` blocks around each operation;
- defensive null checks for values that cannot be null;
- converting every local operation into a range pipeline;
- logging at function entry and exit without a diagnostic need;
- `TODO` comments that restate unfinished work without an obligation;
- automatic fallback behavior that hides an invalid configuration;
- redundant temporaries introduced only to narrate each expression;
- huge functions with no blank lines between stages;
- huge functions split into helpers while each helper remains internally dense.

# 4. Python style

## 4.1 Governing principle

Python verification scripts shall expose the mathematical calculation directly.
They are executable derivations, not application frameworks.

A script may remain self-contained when it verifies one finding. Shared code
should be extracted only after several scripts implement the same mathematical
operation with the same contract.

## 4.2 Script structure

Executable scripts shall define `main` and end with:

```python
if __name__ == "__main__":
    raise SystemExit(main())
```

A verification-only script whose `main` cannot fail except through assertions
may return `None`; a command-line script should return an integer status.

Keep module-level executable work limited to constants and symbolic declarations
that are part of the derivation.

## 4.3 Names

Apply the same scope rule as C++.

Preferred local names:

```text
x
y
p
r
u
expr
poly
mat
rows
samples
mean
cov
scale
error
```

Avoid generated prose names:

```text
current_route_transition_position
maximum_number_of_target_partition_bins
normalized_conditional_covariance_matrix_result
```

Use longer names for public dataclasses, serialized fields, and functions whose
meaning must survive outside the local derivation.

## 4.4 Functions

A function should name one mathematical or computational operation.

Preferred:

```python
def triangle_integral(expr: sp.Expr) -> sp.Expr:
    ...
```

```python
def route_kernel(order: int) -> sp.Expr:
    ...
```

Avoid generic functions such as:

```python
def process_data(data, config):
    ...
```

Do not create a helper for a one-line expression unless the name contributes
mathematical meaning or the expression is reused.

## 4.5 Type annotations

Use annotations for function boundaries, dataclasses, stable records, and
serialized schemas.

Do not annotate every obvious local variable.

Do not introduce complicated protocol or generic type machinery into a small
verification script unless it catches a real class of error.

## 4.6 Data records

Use a dataclass or named tuple when a fixed schema travels through several
functions.

Do not use a dictionary as an anonymous struct when the keys are fixed and
required.

A dictionary is appropriate for genuinely dynamic keyed data, JSON-like output,
or accumulators indexed by a domain value.

## 4.7 Numerical code

Keep array shapes, normalizations, and scaling conventions visible.

Name centered, scaled, and conditional quantities distinctly.

Do not reuse one variable name for raw, centered, and normalized versions of the
same data.

When a formula is delicate, write the direct formula before optimizing it.

Distinguish exact arithmetic, symbolic arithmetic, and floating-point estimates.
Do not silently convert exact values to floats.

## 4.8 NumPy and vectorization

Use vectorization when it improves performance and remains readable.

Do not replace a short exact loop with dense broadcasting whose axes require a
paragraph to reconstruct.

Document non-obvious axis order and shapes. Prefer intermediate names for
meaningful tensors over long nested indexing expressions.

## 4.9 SymPy

Use `expand`, `factor`, `simplify`, and related operations deliberately. Do not
apply global simplification repeatedly without evidence that it is needed.

State the exact identity being checked near the assertion.

Avoid testing only numerical samples when an exact symbolic identity is
available at the processed size.

## 4.10 Pandas

Do not use pandas for small fixed tables, simple CSV output, or arrays already
represented naturally by NumPy or the standard library.

Use pandas when labeled tabular operations materially simplify grouping,
joining, or reporting.

Do not let dataframe column names replace domain types and documented schemas.

## 4.11 Paths and files

Use `pathlib.Path`.

Open text files with an explicit encoding when the file may leave the local
process.

Write machine-readable artifacts through a stable schema. Do not mix progress
messages into the artifact.

Use temporary files and atomic replacement when an interrupted write would leave
a misleading valid-looking result.

## 4.12 Errors

Raise a specific exception with context. Do not catch `Exception` merely to
print and continue.

At a command boundary, convert expected user errors into a concise diagnostic
and nonzero status.

Assertions are appropriate for exact verification identities and internal
invariants. They are not user-input validation.

## 4.13 Comments and docstrings

A module docstring may state the finding or calculation verified:

```python
"""Exact checks for findings-88.md."""
```

Function docstrings are not required for short private mathematical helpers
whose type signature and body are immediate.

Do not generate parameter-by-parameter docstrings that repeat the names and
types.

Comments shall explain the formula, scaling, estimator, or exceptional choice.
Do not narrate ordinary Python syntax.

## 4.14 Output

Use `print` for concise human-readable verification summaries.

Use JSON, CSV, or another declared schema for data consumed by later tools.

Do not print decorative banners, emoji, or repeated status lines.

A verification script should normally end with one summary line containing the
number or class of checks performed.

## 4.15 Python anti-patterns associated with generated code

Revise code containing clusters of the following:

- a class used only as a namespace;
- a configuration dataclass with dozens of fields for one script invocation;
- generic `process`, `handle`, `execute`, and `run_analysis` helpers;
- sentence-length snake-case locals;
- a helper for every three-line loop;
- `try` and `except Exception` around each stage;
- repeated conversion between lists, arrays, dataframes, and dictionaries;
- a plugin or registry system for a fixed list of calculations;
- nested comprehensions that conceal a mathematical sum;
- comments that begin with `Now`, `Next`, or `This step` before every block;
- logging infrastructure in a script that emits one final result;
- a command-line parser with options that the script never varies;
- silent fallback values for missing scientific parameters;
- duplicated scripts that differ only in constants when a small explicit driver
  table would suffice;
- a universal analysis framework built before the common operations are known.

# 5. Bash style

## 5.1 Governing principle

Bash scripts shall remain short, linear, explicit launchers. They shall not
contain scientific logic that belongs in C++ or Python.

## 5.2 Header and strict mode

Executable Bash scripts shall begin with:

```bash
#!/usr/bin/env bash

set -Eeuo pipefail
```

Use `-E` when traps or functions need error propagation. A simple existing
script may retain `set -euo pipefail`, but new scripts should use the declared
repository convention consistently.

## 5.3 Variables

Use lower-case snake-case names for local script variables:

```bash
root
vertex_count
output
sample_count
```

Reserve upper-case names for exported environment variables and established
external tool overrides.

Quote expansions unless word splitting is explicitly required.

Use arrays for command arguments that may contain optional elements.

## 5.4 Paths

Resolve the repository root relative to `BASH_SOURCE[0]`:

```bash
root=$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)
```

Do not assume the current working directory.

Use quoted paths. Do not concatenate command fragments into one shell string.

## 5.5 Conditions

Use `[[ ... ]]` for Bash conditions.

Use arithmetic contexts for integer arithmetic.

Do not parse `ls`. Do not use unquoted glob results as data.

## 5.6 Commands and pipelines

Place one logical pipeline on a visible sequence of lines:

```bash
"$geng" -q "$vertex_count" \
    | "$directg" -aq \
    | "$root/bin/driver" spectral \
        --vertices "$vertex_count" \
        --output "$output"
```

Do not store a complete command in a string and execute it with `eval`.

Do not invoke `g++`. Build through the repository command or Clang toolchain.

## 5.7 Functions

Use a function when it is called more than once, requires a trap, or names a
substantial reusable shell operation.

Do not split a twelve-line linear launcher into six one-use functions.

Use `local` for function-local variables.

## 5.8 Output

Use `printf` for formatted or potentially ambiguous output.

A simple fixed usage line may use `printf` directly rather than `echo`.

Write diagnostics to standard error.

Do not print every command manually when `set -x` or a targeted diagnostic is
the correct tool.

## 5.9 Temporary files

Use `mktemp` and `trap` for temporary files or directories.

Do not create predictable temporary names in `/tmp`.

Clean temporary state on normal exit and failure.

## 5.10 Bash anti-patterns associated with generated code

Do not use:

- `eval`;
- unquoted variable expansions;
- string-built command lines;
- repeated `cd` calls without restoring or isolating the directory;
- scientific calculations in shell arithmetic;
- large case trees generated for a small fixed command set;
- generic logging wrappers;
- colorized banners in machine-oriented scripts;
- automatic retries that hide deterministic failures;
- fallback to GCC or another unsupported compiler;
- shell functions that wrap one command without adding semantics;
- duplicated launch scripts that differ only by constants when an explicit loop
  or parameter file is clearer.

# 6. Comments, documentation, and code prose

## 6.1 Governing principle

Comments are technical prose. They shall follow the same restraint and
specificity expected in the mathematical documents.

A comment should answer one of these questions:

1. What mathematical operation is this block implementing?
2. What invariant must remain true?
3. Why is the direct-looking alternative incorrect?
4. What scaling, normalization, or estimator is being used?
5. Why is this implementation choice required for correctness or performance?
6. Which finding or artifact contract does this code implement?

If the comment answers none of these, remove it.

## 6.2 Forbidden comment styles

Do not write:

- `Now we ...`
- `Next, we ...`
- `This is important because ...` without the exact consequence;
- `robustly handles ...`;
- `comprehensive analysis ...`;
- `perform the calculation`;
- `initialize variables`;
- `loop through the data`;
- `store the result`;
- `return the final output`;
- `helper function for ...`;
- `main processing logic`;
- `core analysis engine`;
- `TODO: improve this` without a precise obligation.

Do not place a comment above code that already states the same operation.

## 6.3 Mathematical comments

Preferred:

```cpp
// Remove drift variation across route position before estimating local noise.
```

```python
# Dirichlet aggregation gives the exact marginal Beta law.
```

```bash
# Preserve independent sample directories for the matched-size sweep.
```

A formula may appear in a comment when it prevents a normalization error, but a
long derivation belongs in the corresponding finding or a dedicated note.

## 6.4 TODO comments

A TODO shall state a specific unresolved obligation and, when known, the finding
or issue that motivates it.

Preferred:

```cpp
// TODO(findings-103): replace the fixed exponent grid after the analytic
// fluctuation normalization is proved.
```

Avoid:

```cpp
// TODO: clean up.
```

Do not leave a TODO for work completed by the same patch.

## 6.5 Generated-code narration

Do not retain planning prose in source comments. Sentences such as `Implementing
readable scaling analysis`, `Planning covariance diagnostics`, or `This section
will compute` belong neither in code nor in committed output.

# 7. Ban list of LLM coding artifacts

## 7.1 Scope

The forms below are forbidden unless the code's domain genuinely requires them.
No individual name or pattern proves generated authorship. The rule targets
habits that make small scientific programs verbose, generic, or difficult to
audit.

## 7.2 Overlong local identifiers

Do not use local names that encode type, ownership, scope, and prose meaning at
once.

Forbidden examples:

```text
maximumNumberOfReferenceHistogramBins
currentPredictivePartitionClassIndex
normalizedWithinPositionConditionalCovarianceMatrix
allAvailableIntrinsicCoordinateCandidateResults
```

Use:

```text
maxRefBins
classIndex
withinCov
candidates
```

## 7.3 Generic architecture vocabulary

Do not introduce `manager`, `processor`, `handler`, `controller`, `factory`,
`builder`, `service`, `engine`, or `context` to describe a one-purpose
calculation.

Name the mathematical object or operation instead.

## 7.4 Fake modularity

Do not create many files, classes, or helpers solely to make each unit small.

Signs of fake modularity include:

- every function is called once;
- helpers pass the same large options and result objects through unchanged;
- a reader must open several files to follow one loop;
- types exist only to wrap one function call;
- names describe software architecture rather than the calculation;
- the abstraction has no second implementation or stable contract.

## 7.5 Dense monoliths

Avoid the opposite failure. A one-file driver still requires blank lines,
locally meaningful names, and visible stages.

Keeping one file does not justify one uninterrupted 900-line function.

## 7.6 Redundant narration

Do not introduce a temporary for every syntactic operation:

```cpp
const auto targetBinsVector = options.targetBins;
const auto maximumTargetBinsValue = targetBinsVector.back();
const auto isReferenceBinCountValid = options.referenceBins >= 16;
```

Prefer:

```cpp
const int maxBins = opt.targetBins.back();

if (opt.refBins < 16) {
    ...
}
```

## 7.7 Defensive code without a threat model

Do not add checks for impossible states merely because defensive programming is
generally praised.

Validate external input, file state, numerical preconditions, and invariants.
Do not repeatedly check values already guaranteed by construction.

Do not catch and suppress errors to make the program appear resilient.

## 7.8 Generic result wrappers

Avoid types such as:

```cpp
struct AnalysisResult {
    std::vector<double> data;
    std::map<std::string, std::string> metadata;
    bool success;
    std::string message;
};
```

Use a domain record with exact fields or throw on failure.

## 7.9 Repetitive validation messages

Validation messages shall name the option and required condition. Do not add a
second sentence explaining ordinary command-line behavior.

Preferred:

```text
--target-bins must be nested divisors of the maximum
```

Avoid:

```text
Invalid target bins were provided. Please ensure that all target bin values are
valid nested divisors of the maximum target bin value and try again.
```

## 7.10 Excessive abstraction around output

Do not create a serializer framework for one stable JSON artifact.

A direct writer is preferred when the schema is small and exact. Extract common
escaping or atomic-write support when several artifacts need it.

## 7.11 Unnecessary configuration

Do not turn constants fixed by the derivation into command-line options merely
to make the program flexible.

An option is justified when users or matched experiments vary it. A parameter
fixed by the theorem should remain fixed and be named in code.

## 7.12 Premature generalization

Do not generalize from one implementation before the common contract is known.

When several scripts duplicate a pattern, first determine whether the formulas,
normalizations, data contracts, and failure conditions are actually the same.
Similar loop shapes do not prove one abstraction.

## 7.13 Activity-oriented comments and names

Avoid names and comments such as:

```text
performAnalysis
processResults
executeComputation
handleOutput
runAllDiagnostics
```

Use the domain operation:

```text
fitScaling
accumulateMoments
scoreClosure
writeReport
```

## 7.14 Artificial completeness

Do not add every conceivable check, output column, or extension point to make a
script look comprehensive.

Implement the diagnostics required by the current finding. Record unresolved
work explicitly rather than producing placeholder infrastructure.

# 8. Concrete transformations

## 8.1 C++ option validation

### Before [generated dense style]

```cpp
for (const int classes : options.predictiveClasses) {
    if (classes < 2 ||
        static_cast<size_t>(classes) > options.vertexCount) {
        throw std::invalid_argument(
            "--predictive-classes values must lie in 2..vertices");
    }
}
if (options.targetBins.empty()) {
    throw std::invalid_argument("--target-bins must not be empty");
}
const int maximumTargetBins = options.targetBins.back();
for (const int bins : options.targetBins) {
    if (bins < 2 || maximumTargetBins % bins != 0) {
        throw std::invalid_argument(
            "--target-bins must be nested divisors of the maximum");
    }
}
if (options.referenceBins < 16) {
    throw std::invalid_argument("--reference-bins must be at least 16");
}
```

### After [repository style]

```cpp
for (int n : opt.predClasses) {
    if (n < 2 || std::cmp_greater(n, opt.vertices)) {
        throw std::invalid_argument(
            "--predictive-classes values must lie in 2..vertices");
    }
}

if (opt.targetBins.empty()) {
    throw std::invalid_argument("--target-bins must not be empty");
}

const int maxBins = opt.targetBins.back();

for (int n : opt.targetBins) {
    if (n < 2 || maxBins % n != 0) {
        throw std::invalid_argument(
            "--target-bins must be nested divisors of the maximum");
    }
}

if (opt.refBins < 16) {
    throw std::invalid_argument(
        "--reference-bins must be at least 16");
}
```

The revision does not add abstractions. It shortens local names, removes a noisy
cast, and restores visible logical paragraphs.

## 8.2 C++ artifact output

### Before [unnecessary C API]

```cpp
FILE* file = std::fopen(path.c_str(), "w");
if (file == nullptr) {
    throw std::runtime_error("failed to open output file");
}

std::print(file, "{}\n", value);
std::fclose(file);
```

### After [repository style]

```cpp
std::ofstream out(path);

if (!out) {
    throw std::runtime_error(
        std::format("cannot create artifact: {}", path.string()));
}

std::println(out, "{}", value);
```

The stream owns the file, failure contains the path, and output follows the
existing C++23 idiom.

## 8.3 C++ unnecessary helper extraction

### Before [fake modularity]

```cpp
bool validateReferenceBins(const Options& opt) {
    return opt.refBins >= 16;
}

void throwReferenceBinsError() {
    throw std::invalid_argument(
        "--reference-bins must be at least 16");
}

void validateOptions(const Options& opt) {
    if (!validateReferenceBins(opt)) {
        throwReferenceBinsError();
    }
}
```

### After [direct validation]

```cpp
if (opt.refBins < 16) {
    throw std::invalid_argument(
        "--reference-bins must be at least 16");
}
```

## 8.4 C++ mathematical stage

### Before [generic names]

```cpp
for (const auto& currentDataPoint : allDataPoints) {
    const auto currentPositionValue =
        calculateNormalizedPosition(currentDataPoint);
    updateAccumulatorUsingCurrentDataPoint(
        globalAccumulator, currentDataPoint, currentPositionValue);
}
```

### After [domain names]

```cpp
for (const RouteStep& step : route) {
    const double u = routePosition(step, p);
    moments.add(u, step.delta);
}
```

## 8.5 Python exact verification

### Before [framework style]

```python
class RouteFormulaVerificationManager:
    def __init__(self, maximum_order: int) -> None:
        self.maximum_order = maximum_order
        self.verification_results: list[bool] = []

    def execute_all_verification_checks(self) -> None:
        for current_order in range(1, self.maximum_order + 1):
            current_result = self._verify_single_order(current_order)
            self.verification_results.append(current_result)
```

### After [verification script style]

```python
def verify_route_formula(max_order: int) -> int:
    checks = 0

    for m in range(1, max_order + 1):
        assert sp.expand(route_kernel(m) - route_formula(m)) == 0
        checks += 1

    return checks
```

## 8.6 Python visual structure

### Before [dense script]

```python
samples = load_samples(path)
mean = samples.mean(axis=0)
cov = np.cov(samples, rowvar=False)
fit = fit_scaling(mean, cov, sizes)
score = score_closure(samples, fit)
write_report(output, fit, score)
```

### After [logical paragraphs]

```python
samples = load_samples(path)

mean = samples.mean(axis=0)
cov = np.cov(samples, rowvar=False)

fit = fit_scaling(mean, cov, sizes)
score = score_closure(samples, fit)

write_report(output, fit, score)
```

Blank lines identify loading, moment construction, inference, and output.

## 8.7 Bash launcher

### Before [string command]

```bash
command="$compiler $flags $source -o $output"
eval "$command"
```

### After [argument array]

```bash
cmd=(
    clang++
    -std=c++23
    -stdlib=libc++
    "$source"
    -o "$output"
)

"${cmd[@]}"
```

# 9. Editing existing code

## 9.1 Local precedent

Before writing new code, inspect nearby source that performs a similar task.
Match its naming, output, error handling, include order, and control-flow style
unless this guide explicitly supersedes it.

Do not replace a working repository idiom with a generic style learned from
another codebase.

## 9.2 Minimal-diff principle

A focused change shall not trigger unrelated renaming, reformatting, file moves,
or abstraction changes.

Do not clean an entire file while implementing one diagnostic unless the user
has requested a cleanup pass.

When a touched block violates this guide and a local correction is safe, repair
the block without expanding the patch beyond the surrounding operation.

## 9.3 Preserve scientific behavior

A style-only patch shall preserve:

- formulas;
- scaling powers;
- estimator definitions;
- random seeds;
- sample partitions;
- output field names;
- command-line semantics;
- file locations;
- floating-point order when reproducibility depends on it;
- exact versus approximate arithmetic choices.

Do not silently repair a suspected mathematical error during a style pass.
Report it separately.

## 9.4 Refactoring threshold

Refactor only after identifying the stable contract.

A duplicated operation is ready for extraction when:

1. the mathematical formula is the same;
2. the normalization is the same;
3. the input and output meaning is the same;
4. the failure conditions are the same;
5. at least two current callers benefit from one implementation;
6. the extracted name is more specific than `helper` or `utility`.

## 9.5 Generated patches

Review generated patches for:

- overlong local names;
- removed blank lines;
- new C APIs;
- unsupported compiler commands;
- one-use abstractions;
- comments that narrate syntax;
- silent fallbacks;
- altered output schemas;
- opportunistic dependency additions.

# 10. Computational reproducibility

## 10.1 Exact and sampled calculations

State whether a result is exact, symbolic, exhaustive, deterministic numerical,
or Monte Carlo.

Do not describe a sampled estimate as exact because the sampler itself is exact.
An exact sampler still produces finite-sample uncertainty.

## 10.2 Seeds and independence

Record explicit seeds for reproducible pseudo-random runs.

When a result depends on independent graph samples, do not reuse one large
sample and label partitions as independent unless the estimand permits it.

Preserve sample identifiers or manifests when uncertainty is estimated across
independent runs.

## 10.3 Parameters

Record all parameters that affect the result, including sizes, route lengths,
bin counts, thresholds, tolerances, scaling exponents, and held-out partitions.

Do not rely on undocumented source defaults for a published calculation.

## 10.4 Artifacts

Machine-readable artifacts shall include enough metadata to identify the
calculation and schema.

Do not manually edit generated evidence.

Write artifacts atomically when a partial file could be mistaken for a complete
run.

## 10.5 Diagnostics

A diagnostic shall have a stated estimand. Do not add a correction factor,
normalization, or score merely because it is conventional in a different
statistical setting.

Distinguish:

- exact finite-object defects;
- uncertainty across independent samples;
- held-out predictive error;
- discretization error;
- finite-size drift;
- numerical solver error.

Do not combine these into one number without a derivation.

# 11. Tooling and enforcement

## 11.1 Formatters

Use the repository formatter configurations.

A formatter does not authorize dense code. Preserve or add semantic blank lines
after formatting.

Do not fight the formatter through manual alignment or repeated disable markers.
Change the expression or update the repository configuration when the style rule
is general.

## 11.2 Static analysis

New warnings introduced by the patch shall be resolved or narrowly justified.

Do not silence a diagnostic globally to permit one local pattern.

A static analyzer supplements code review. Passing it does not establish that
naming, spacing, abstraction, or mathematical correspondence satisfies this
guide.

## 11.3 Forbidden toolchain fallbacks

Build scripts and documentation shall not invoke `g++`, select GCC, or link
libstdc++.

A toolchain audit may reject:

- `g++` in committed scripts and build commands;
- `-stdlib=libstdc++`;
- an unexpected `libstdc++.so` dependency;
- a compiler other than Clang for repository targets.

## 11.4 Style checks

Mechanical checks may enforce:

- formatter compliance;
- line length;
- forbidden C stdio calls;
- forbidden compiler commands;
- missing strict mode in Bash;
- Python lint and format rules;
- shell quoting and ShellCheck diagnostics.

Mechanical checks should not enforce arbitrary function-length, file-length, or
class-count limits.

Blank-line and naming rules require review or a narrowly designed local checker.
Do not replace judgment with a brittle metric that encourages worse code.

# Mandatory house rules

1. Use short local names whose meaning is clear from scope and type.
2. Use descriptive public names without architecture filler.
3. Separate independent logical stages with one blank line.
4. Do not remove semantic blank lines merely because a formatter permits a dense
   block.
5. Keep one-purpose drivers cohesive; do not split code solely to reduce file or
   function length.
6. Extract helpers only when they name a mathematical operation, remove real
   duplication, isolate a stable contract, or permit a focused test.
7. Do not introduce manager, processor, handler, controller, factory, builder,
   service, engine, context, utility, or helper abstractions without a concrete
   domain role.
8. Follow existing repository idioms before generic language-community habits.
9. Use C++23 with Clang and libc++; do not invoke `g++` or link libstdc++.
10. Use RAII streams and `std::print` for C++ file output.
11. Do not use `FILE*`, C stdio, or long stream-insertion chains for project
    artifacts.
12. Use modern C++ facilities only when they make the calculation clearer.
13. Prefer a clear loop over a dense range pipeline.
14. Use comments for mathematics, invariants, normalization, and non-obvious
    implementation reasons; do not narrate syntax.
15. Keep exact, symbolic, deterministic numerical, and sampled results distinct.
16. Preserve formulas, parameters, seeds, schemas, and output semantics during
    style-only edits.
17. Do not add silent fallbacks or continue after incomplete scientific output.
18. Use `pathlib.Path` in Python and `std::filesystem::path` in C++.
19. Keep Bash as a strict, quoted, linear launcher; do not place scientific
    logic in shell scripts.
20. Do not build a reusable framework before the common mathematical contract is
    known.

# Code preflight checklist

Before completing a code patch, verify the following.

1. Does each file implement one recognizable program, domain object, or stable
   algorithm?
2. Are setup, calculation, diagnostics, and output visually separated?
3. Are independent validation groups separated by blank lines?
4. Are local names shorter than public names and free of sentence-like wording?
5. Does every helper have a mathematical, reused, or independently testable
   purpose?
6. Has the patch avoided generic manager, processor, context, builder, and
   utility abstractions?
7. Does the C++ code use the repository's Clang/libc++ C++23 toolchain?
8. Have all new `g++`, GCC, libstdc++, `FILE*`, C stdio, and long
   insertion-chain uses been removed?
9. Does formatted output follow the existing RAII stream and `std::print` idiom?
10. Are signed and unsigned comparisons handled without noisy cast scattering?
11. Are loops, algorithms, ranges, and lambdas chosen for clarity rather than
    novelty?
12. Do comments explain formulas, invariants, scales, or non-obvious choices
    rather than syntax?
13. Does Python expose the derivation directly without an unnecessary framework?
14. Does Bash use strict mode, quoted expansions, arrays where needed, and no
    `eval`?
15. Are exact and sampled results labeled correctly?
16. Are seeds, parameters, sample partitions, and output schemas preserved?
17. Does the patch avoid unrelated formatting and renaming?
18. Do formatter, static-analysis, build, test, and verification commands pass?
19. Has machine-readable output remained free of progress prose?
20. Can a reader map each major code block to the corresponding mathematical or
    computational stage without opening several one-use wrappers?
