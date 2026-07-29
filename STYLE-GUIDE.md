# Style Guide for Mathematical Physics Manuscripts

## Scope

This guide governs the research notebook's mathematical prose, section structure, notation, theorem presentation, and preservation of Markdown, LaTeX, and computational content. It is based on the conventions used in research papers and expository work in causal-set theory, graph operator algebras, noncommutative geometry, mathematical physics, and quantum gravity.

The governing principles are restraint, mathematical specificity, continuous narrative, and exact preservation of technical content. Definitions are introduced when the argument requires them, physical interpretation supplements rather than replaces formal construction, and lists are reserved for material that is intrinsically list-like.

## Research basis

The guide reflects representative work in causal-set theory, graph operator algebras, noncommutative geometry, quantum foundations, and quantum gravity, including papers and reviews by Rafael Sorkin, Fay Dowker, Joe Henson, David Kribs, Baruch Solel, Alain Connes, Mark Tomforde, Marcus Müller, Lee Smolin, and Christopher Isham. Across this corpus, technical papers ordinarily use restrained descriptive headings, introduce definitions when the argument requires them, state operator data before interpretation, and use lists primarily for axioms, equivalent conditions, classifications, or algorithms. Expository reviews may use genuine disciplinary questions as headings, but they do not rely on promotional or suspense-driven labels.

# 1. Structural conventions and section headers

## 1.1 Governing principle

A section title shall identify the mathematical object, task, result, or interpretive issue treated in that section. It shall not advertise the importance of the section or attempt to create suspense.

The default hierarchy is descriptive:

```text
1 Introduction
2 Preliminaries
3 The causal or graph-theoretic construction
4 Main results
5 Examples or applications
6 Discussion
7 Conclusion
Appendix A Technical lemmas
```

This is a template rather than a compulsory sequence. A short paper may omit preliminaries, discussion, or conclusion.

## 1.2 Preferred forms

Use compact descriptive noun phrases, for example:

- `Causal-set preliminaries`
- `Faithful embeddings`
- `The discrete retarded propagator`
- `Graph correspondences`
- `The left-regular representation`
- `Toeplitz--Cuntz--Krieger families`
- `Spectral triples and distance`
- `Existence of the representation`
- `Proof of Theorem 4.2`
- `Examples`
- `Continuum approximation`
- `Discussion and open problems`

## 1.3 Theorem-style headings

When a theorem, proposition, lemma, or corollary is presented as a Markdown heading, use a period between the result number and its descriptive name:

```markdown
## Theorem 1. Algebraic universality
## Proposition 2. Faithfulness of the representation
## Lemma 3. Interval decomposition
## Corollary 4. Uniqueness of the extension
```

Do not use parenthetical titles such as `Theorem 1 (algebraic universality)`.

A proof heading may be `## Proof` when it is unambiguous, or `## Proof of Theorem 1` when separation from the theorem makes the reference useful.

## 1.4 Acceptable question headings

A question may be used as a section title only when all of the following hold:

1. The section answers that precise question.
2. The question is meaningful to a specialist independently of the manuscript.
3. The manuscript is substantially expository, conceptual, or review-oriented.

Acceptable examples include `What kind of discreteness?`, `Why is the qubit state space three-dimensional?`, and `How is locality recovered?`.

Do not use promotional or semantically vague questions such as `Why this changes everything`, `What is really going on here?`, `Can this powerful idea unlock quantum gravity?`, or `Why should the reader care?`.

## 1.5 Forbidden dramatic headers

Do not use:

- `The Hidden Structure`
- `The Big Idea`
- `The Algebraic Heart of the Theory`
- `The Grand Synthesis`
- `Unlocking the Operator Framework`
- `A Radical New Perspective`
- `The Moment Everything Changes`
- `Bridging Two Worlds`
- `Beyond the Mathematics`
- `Putting It All Together`
- `Key Takeaways`
- `Why It Matters`
- `Deep Dive`
- `Conceptual Toolkit`
- `The Master Equation`

`The Road Ahead` is permitted only for an actual research outlook when the publication style permits it. A memorable paper title is permissible; a sequence of theatrical internal headings is not.

## 1.6 Heading depth

Ordinarily, use no more than three numbered levels. A fourth level is appropriate only in a long monograph or review. Do not create a heading for a single short paragraph.

A subsection should normally contain at least two substantive paragraphs, or one substantial formal result together with proof and discussion.

## 1.7 Introduction structure

An introduction should normally perform the following work in continuous prose:

1. State the mathematical or physical problem.
2. Explain why the problem is nontrivial.
3. Identify the limitation in the existing framework.
4. State the construction or result of the manuscript.
5. Explain its significance with specific mathematical content.
6. Give a restrained roadmap when the document is long enough to require one.

The roadmap should be a single paragraph near the end of the introduction. Do not present it as a bullet list unless the manuscript is unusually long.

## 1.8 Terminal sections

Use descriptive titles such as `Discussion`, `Discussion and outlook`, `Conclusion`, `Open problems`, or `Limitations and open questions`.

Do not automatically include both `Discussion` and `Conclusion`. Use both only when they serve different functions: discussion treats interpretation, comparison, limitations, and implications; conclusion gives a compact statement of established results. A conclusion shall not reproduce the abstract sentence by sentence.

# 2. Prose and narrative integration

## 2.1 The basic narrative unit

Each paragraph should perform one identifiable mathematical task: motivate a definition, fix notation, state a construction, derive a relation, interpret a result, delimit an assumption, compare with a known object, introduce a proposition, or explain the next proof step.

Do not combine motivation, several unrelated definitions, a literature review, and a conclusion in one paragraph.

## 2.2 Required order for new mathematical objects

Unless there is a strong reason otherwise, introduce an object in this order:

1. Identify what the object must encode or accomplish.
2. Specify the ambient spaces, algebras, graphs, domains, or assumptions.
3. Give the definition and its formula.
4. State the first immediate consequence.
5. Explain its physical or structural interpretation.
6. State how it enters the next result.

A standard operator introduction has the form:

```latex
Let \(E=(E^0,E^1,r,s)\) be a countable directed graph, and let
\(\mathcal H_E=\ell^2(E^*)\) with canonical basis
\(\{\xi_\mu:\mu\in E^*\}\). For \(e\in E^1\), define
\[
L_e\xi_\mu =
\begin{cases}
\xi_{e\mu}, & s(e)=r(\mu),\\
0, & \text{otherwise}.
\end{cases}
\]
The operators \(L_e\) are partial isometries whose initial projections are
determined by the range vertices of the corresponding edges. They may
therefore be viewed as left-creation operators on the graph Fock space.
```

The formula is neither preceded nor followed by an isolated label such as `Definition:` unless a formal definition environment is warranted.

## 2.3 Formal definitions

Use a numbered definition when at least one of the following applies:

- the term is used throughout the manuscript;
- later statements refer to the definition by number;
- the definition has several hypotheses;
- variants of the definition must be distinguished;
- the object is original to the manuscript.

Use ordinary prose for local notation, for example: `We write \(I(x,y)=\{z\in C:x\prec z\prec y\}\) for the open order interval.`

Do not create a formal definition for every symbol.

## 2.4 Syntactic integration of definitions

Preferred:

> A causal set is a pair \((C,\prec)\) in which \(\prec\) is an irreflexive, transitive, and locally finite relation.

A list is appropriate when the axioms themselves require individual emphasis. Do not replace an exact definition by a detached list of informal “ingredients.”

## 2.5 Displayed equations

Every displayed equation must have a grammatical function.

The preceding sentence must tell the reader what the display does, using formulations such as `The left action is therefore given by`, `The expected number of sprinkled elements is`, `The operator takes the form`, or `Using the decomposition above, we obtain`.

Avoid repeated empty introductions such as `We have:`, `The equation is:`, `Mathematically:`, and `This can be written as follows:`.

The sentence following a display should define remaining symbols, identify a consequence, explain the relevant limiting case, relate the expression to the preceding construction, or state how it will be used.

## 2.6 Inline and displayed mathematics

Use inline mathematics for short memberships, simple conditions, compact maps, and symbols being named or compared.

Use display mathematics for central definitions, multi-case operators, chains of equalities used in an argument, relations with several quantifiers or indices, equations that will be referenced, and identities whose structure must be visually inspected.

Do not display a one-symbol statement merely to make it appear important.

## 2.7 Operator definitions

An operator definition is incomplete unless the reader can recover:

1. the ambient space;
2. the domain when it is not the whole space;
3. the action on a general vector or a specified core or basis;
4. parameter dependence;
5. boundedness, closability, or self-adjointness status when relevant;
6. the notation for adjoints or closures if later used.

Preferred:

```latex
On the dense subspace
\(\mathcal D_0=\operatorname{span}\{\xi_\mu:\mu\in E^*\}\subset\mathcal H_E\),
define
\[
D_0\xi_\mu=\lambda_\mu\xi_\mu .
\]
Since \(\lambda_\mu\in\mathbb R\), the operator \(D_0\) is symmetric.
Its closure will be denoted by \(D\).
```

Do not write a formal-looking series for an operator without specifying its domain, convergence, basis assumptions, and operator class.

## 2.8 Notation discipline

Every nonstandard symbol must be defined at first use. A notation table does not repair undefined notation in the prose.

Use one symbol for one object within an argument. Do not use the same letter for a graph and a conditional expectation, a projection and a probability measure, or dimension and distance.

Decorations must be systematic. If \(A\), \(\widehat A\), \(\mathcal A\), and \(A^*\) occur, their distinctions must be explicit.

For a map \(f:X\to Y\), state the domain and codomain at its first formal introduction. When several maps appear, state what structure they preserve.

For graphs, declare the orientation and path-composition convention once. Do not silently reverse the convention later.

## 2.9 Motivation and rigor

The manuscript should operate on two connected levels.

At the operational or physical level, explain what can be prepared, observed, counted, or reconstructed; which continuum quantity a discrete object approximates; why an operator is physically natural; and what symmetry or covariance requirement is imposed.

At the formal level, state the mathematical object, assumptions, map or operator, exact claim, topology, norm, measure, or convergence notion, and the proof or citation.

Do not blur these levels. The verbs `represents`, `corresponds to`, `approximates`, and `emerges as` must be precise enough to distinguish equality, representation, asymptotic convergence, probabilistic concentration, and heuristic interpretation.

## 2.10 Permitted narrative transitions

Preferred transitions include:

- `To make this precise, let ...`
- `We now fix the notation used in the construction.`
- `The preceding observation suggests the following definition.`
- `This representation has two consequences.`
- `Under the standing hypothesis that ...`
- `It remains to verify ...`
- `The converse follows from ...`
- `We next compare this operator with ...`
- `In the continuum approximation, the corresponding quantity is ...`
- `The role of local finiteness is now apparent.`
- `The following lemma isolates the required estimate.`

These transitions state logical relations. Avoid transitions that merely announce activity, such as `Next, we dive into`, `We now explore`, `Let us unpack`, `With this foundation in place`, `Armed with these insights`, `This brings us to`, and `Now comes the exciting part`.

## 2.11 Paragraph conclusions

End a technical paragraph with a consequence, limitation, or forward connection. Do not repeatedly end with generic emphasis such as `This is important`, `This observation is crucial`, `This provides a powerful framework`, or `This will be useful later`.

Replace generic emphasis by the exact consequence. For example: `Consequently, \(L_e^*L_e=P_{r(e)}\), so the initial projection depends only on the range vertex.`

## 2.12 Proof style

A proof should begin with its mathematical strategy rather than ceremonial language.

Preferred:

> It suffices to prove that the representation is faithful on the fixed-point algebra, since gauge covariance then gives the result.

Avoid:

> We now embark on the proof of this important theorem. The proof consists of several key steps.

Within a proof, cite equations by label when labels are available, identify where hypotheses are used, distinguish equality from unitary equivalence or isomorphism, and close with the result rather than a recap of the entire proof.

# 3. Ban list of LLM artifacts

The following forms are forbidden in manuscript prose unless they occur in a quotation or are necessary technical terminology.

## 3.1 Promotional or inflated phrases

Do not use:

- `at its core`
- `in the grand scheme of things`
- `a powerful lens`
- `a powerful framework`
- `a rich tapestry`
- `a fascinating interplay`
- `a profound connection`
- `a deep and subtle relationship`
- `a groundbreaking perspective`
- `a game-changing result`
- `a remarkable journey`
- `an elegant dance`
- `unlocking`
- `unpacking`
- `delving into`
- `navigating the complexities of`
- `bridging the gap`
- `paving the way`
- `a paradigm shift`
- `holistic`
- `seamless`
- `transformative`
- `robust` when the intended meaning is merely useful or well-defined
- `novel` without an explicit statement of what is new
- `fundamental` when the claim is only locally useful
- `crucial`, `essential`, or `key` used repeatedly as emphasis rather than logically

Replace evaluative adjectives with mathematical content.

Instead of `This powerful construction reveals a profound connection between the graph and its operator algebra`, write the precise conclusion, such as `The isometric isomorphism class of the algebra determines the multiplicity \(C_{ij}\) of the arrows from \(j\) to \(i\).`

## 3.2 Conversational filler

Do not use:

- `Let's dive in.`
- `Let's take a closer look.`
- `Let's break this down.`
- `So, what does this mean?`
- `You might be wondering ...`
- `It is worth pausing here.`
- `Here is the interesting part.`
- `The answer is surprisingly simple.`
- `As we can clearly see ...`
- `Needless to say ...`
- `Of course` when the point is not genuinely immediate to the target reader
- `Basically`
- `Simply put`
- `In simple terms`
- `In other words` when it merely repeats the preceding sentence

## 3.3 Meta-writing

Do not use:

- `This section will explore ...`
- `This section aims to provide ...`
- `In this subsection, we will delve into ...`
- `The goal of this section is to unpack ...`
- `The reader will learn ...`
- `We have now covered ...`
- `Before moving on ...`
- `As mentioned earlier` without an exact section, theorem, or equation reference
- `As discussed above` when the antecedent is not immediate
- `The following discussion provides a comprehensive overview ...`

State the mathematical action directly, for example: `We first prove boundedness on finite path subspaces.`

## 3.4 Generic summaries

Do not use recurring blocks or paragraphs headed:

- `Key takeaway`
- `Main insight`
- `What we learned`
- `Why this matters`
- `In a nutshell`
- `Quick recap`
- `Summary of the section`
- `Putting it all together`

A formal article may contain a proposition collecting equivalent conditions or a conclusion summarizing results. It should not contain pedagogical takeaway boxes after each subsection.

## 3.5 Shopping-list mathematics

Do not replace a mathematical dependency by a list of informal ingredients.

Avoid:

> We need the following ingredients:
> - a graph;
> - a Hilbert space;
> - some operators;
> - a causal interpretation.

Write instead:

> Let \(E\) be a directed graph. Its finite paths index the canonical basis of the Hilbert space \(\mathcal H_E\), on which the edge operators act by left concatenation.

## 3.6 Arbitrary numbered promises

Do not write `There are three key reasons for introducing this operator` unless there are exactly three mathematically independent reasons and the enumeration improves later reference. Do not manufacture the numbers three, four, or five for rhetorical symmetry.

## 3.7 Repetitive heading templates

Do not repeat a fixed internal schema such as:

```text
Motivation
Core idea
Formal definition
Why it matters
Key takeaway
```

The section structure must follow the argument rather than an invariant content template.

## 3.8 Artificial contrasts

Avoid formulaic constructions when they do not express a real logical distinction:

- `not merely X, but Y`
- `not only X; it also Y`
- `rather than simply X, it fundamentally Y`
- `from X to Y`
- `where intuition meets rigor`

Use contrast only when both sides are mathematically relevant.

## 3.9 Excessive signposting

Use no more than one roadmap paragraph in an introduction. Do not give a second roadmap at the start of every section and a recap at its end.

## 3.10 Empty intensifiers and certainty claims

Avoid `clearly`, `obviously`, `evidently`, `trivially`, `undeniably`, `certainly`, and `without question` unless the assertion genuinely follows immediately and the wording would not discourage scrutiny.

Prefer exact reasons: `By transitivity`, `Equation (3.4) gives`, or `The claim follows from Lemma 2.3.`

## 3.11 Unsupported claims of completeness

Do not write `This completely characterizes`, `This resolves the issue`, `This proves consistency`, or `This establishes equivalence` unless the theorem states exactly that conclusion under specified hypotheses.

## 3.12 Permitted lists

Lists are appropriate for axioms, standing assumptions, mutually exclusive cases, equivalent conditions in a theorem, steps of an actual algorithm, input and output specifications, classifications, categories being explicitly compared, and finite collections that will be referenced individually.

Lists must have parallel grammatical form and should be numbered when order or later reference matters.

# 4. Concrete transformations

## 4.1 Causal-set definition

### Before: AI style

> ### The Core Building Blocks of Causal Structure
>
> The causal-set framework rests on three powerful pillars:
>
> - **Events:** the basic building blocks of spacetime.
> - **Causal order:** a relation that tells us which events influence others.
> - **Local finiteness:** a crucial discreteness condition.
>
> Together, these ingredients provide a robust and elegant framework for replacing the continuum.

### After: research style

> Let \(C\) be a set equipped with a relation \(\prec\). We interpret \(x\prec y\) as saying that \(x\) lies to the causal past of \(y\). The relation is required to be irreflexive and transitive. Discreteness is imposed by local finiteness: for every \(x,y\in C\), the interval
> \[
> I(x,y)=\{z\in C:x\prec z\prec y\}
> \]
> is finite. A pair \((C,\prec)\) satisfying these conditions is called a causal set.

The revision motivates the relation, states the exact axioms, introduces interval notation where it is needed, and names the resulting object without making an unsupported claim about replacing the continuum.

## 4.2 Graph creation operators

### Before: AI style

> ### Unlocking the Operator Construction
>
> We now introduce the key operator that brings the graph to life. For every edge, we create a shift operator. Intuitively, it adds the edge to a path:
>
> \[
> L_e|\mu\rangle=|e\mu\rangle.
> \]
>
> This elegant construction forms the heart of the graph algebra and shows the deep connection between paths and quantum creation operators.

### After: research style

> Let \(E=(E^0,E^1,r,s)\) be a directed graph, and let \(\mathcal H_E=\ell^2(E^*)\) with canonical basis \(\{\xi_\mu:\mu\in E^*\}\). For \(e\in E^1\), define
> \[
> L_e\xi_\mu=
> \begin{cases}
> \xi_{e\mu}, & s(e)=r(\mu),\\
> 0, & s(e)\neq r(\mu).
> \end{cases}
> \]
> Thus \(L_e\) acts by left concatenation on admissible paths. It is a partial isometry and may be regarded as a creation operator on the graph Fock space.

The revision supplies the Hilbert space, basis, composition convention, action on inadmissible paths, and operator class before giving the interpretation.

## 4.3 Spectral distance

### Before: AI style

> ### A Powerful New Notion of Distance
>
> The Dirac operator does much more than encode geometry. In fact, it unlocks an entirely new way of measuring distance:
>
> \[
> d(\varphi,\psi)=\sup |\varphi(a)-\psi(a)|.
> \]
>
> The key takeaway is that noncommutative geometry replaces ordinary paths with operator algebraic information.

### After: research style

> Let \((\mathcal A,\mathcal H,D)\) be a spectral triple. For states \(\varphi,\psi\) on the norm closure of \(\mathcal A\), define
> \[
> d_D(\varphi,\psi)
> =
> \sup\left\{
> |\varphi(a)-\psi(a)|:
> a\in\mathcal A,\ \lVert[D,a]\rVert\leq 1
> \right\}.
> \]
> The commutator bound plays the role of a Lipschitz condition. In the commutative spin-manifold case, \(d_D\) restricts to the geodesic distance on pure states corresponding to points.

The revision specifies the spectral triple, restores the constraint in the supremum, identifies the functionals, and states the geometric interpretation in a precise case.

## 4.4 Operational motivation and formal state space

### Before: AI style

> ### From Experiments to Abstract Mathematics
>
> The framework contains several key ingredients:
>
> 1. Preparations.
> 2. Measurements.
> 3. Outcomes.
> 4. States.
> 5. Effects.
>
> We can seamlessly translate these operational notions into a powerful convex-geometric framework.

### After: research style

> Consider a prepare-and-measure experiment with conditional probabilities \(P(k\mid p,m)\), where \(p\) labels a preparation, \(m\) a measurement, and \(k\) an outcome. Two preparations \(p\) and \(p'\) define the same operational state when
> \[
> P(k\mid p,m)=P(k\mid p',m)
> \]
> for every \(m\) and \(k\). Measurement outcomes are identified analogously whenever they induce the same probabilities for all preparations. The resulting equivalence classes are represented by states and effects in dual real vector spaces, with their pairing equal to the observed probability.

The revision begins with observable data, defines states through an explicit equivalence relation, and introduces the vector-space representation only after the operational quotient has been specified.

# 5. File-format preservation

These rules are mandatory unless a separate instruction explicitly authorizes mathematical or structural refactoring.

## 5.1 Minimal-diff principle

Make the smallest edit that achieves the requested stylistic correction.

Do not reorder equations for stylistic symmetry, rename symbols while editing prose, replace theorem environments with ordinary paragraphs, convert citation systems, normalize all formatting across a file without approval, or repair unrelated mathematical issues silently.

Substantive mathematical corrections must be reported separately from prose edits.

## 5.2 Protected mathematical spans

Treat the contents of inline and displayed mathematical delimiters and environments as protected unless mathematical editing is explicitly requested:

```latex
$...$
\(...\)
\[...\]
\begin{equation}...\end{equation}
\begin{align}...\end{align}
\begin{gather}...\end{gather}
\begin{multline}...\end{multline}
\begin{cases}...\end{cases}
```

Prose surrounding a block may be revised without rewriting the block.

Do not automatically convert delimiter conventions or replace Unicode symbols by LaTeX commands. Such normalization may affect compilation, line numbering, or repository diffs and requires explicit approval.

## 5.3 Labels and references

Preserve exactly:

```latex
\label{...}
\ref{...}
\eqref{...}
\autoref{...}
\cref{...}
\Cref{...}
```

Never invent a reference key to conceal a missing reference. When moving a paragraph, verify that the referenced object remains correctly placed and that positional words such as `above` and `below` remain accurate.

Prefer explicit references such as `Equation \eqref{eq:propagator}` over positional phrases when editing makes the latter unstable.

## 5.4 Macros

Preserve user-defined macros and their argument structure. Do not expand or replace a macro unless asked. A macro may encode typography, semantic markup, indexing behavior, or compatibility with another file.

Before editing notation, inspect the preamble or macro file. Never infer a macro's meaning solely from its name.

## 5.5 Theorem-like environments

Preserve definitions, theorems, lemmas, propositions, corollaries, remarks, examples, and proofs.

Do not remove optional theorem titles, move hypotheses out of a theorem without checking scope, merge a theorem and its proof, change proof endings, or turn numbered results into unnumbered prose.

When improving a theorem statement, maintain the logical order: ambient objects, hypotheses, quantified variables, conclusion, and exceptional or equality cases.

## 5.6 Equation punctuation

Preserve or repair punctuation according to the prose sentence containing the equation. The punctuation following a display is part of the sentence and should not be stripped by automated formatting.

## 5.7 Markdown mathematics

In Markdown manuscripts, preserve the existing delimiter convention, do not mix delimiter systems without need, do not indent display mathematics unless it is intentionally part of a list, ensure blank lines do not terminate adjacent blocks unexpectedly, and keep fenced code distinct from mathematical blocks.

Do not place a display equation inside a Markdown table cell unless the renderer is known to support it reliably.

## 5.8 Markdown tables

Treat a table's column count and alignment row as fixed. Preserve escaped pipes and renderer-specific syntax.

Do not reflow a table if it contains multiline code, LaTeX environments, manually aligned data, HTML tags, citation markers, or long operator definitions. A derivation does not belong in a table and should be moved into prose only with explicit structural permission.

## 5.9 Lists in Markdown and LaTeX

Do not convert prose into bullets merely to shorten sentences.

When a formal list is retained, keep entries grammatically parallel, preserve numbering when entries are referenced later, do not change `enumerate` to `itemize` when order matters, preserve custom labels, check nested indentation, and do not insert blank lines that alter Markdown numbering.

## 5.10 Code and computational sections

Treat fenced code, scripts, notebooks, and pseudocode as protected technical content. Preserve indentation, language identifiers, variable names, comments, line continuations, string literals, regular expressions, shell quoting, random seeds, file paths, units, and numerical precision.

Do not improve prose inside executable strings or comments when doing so might change a test, parser, output comparison, command, or generated documentation.

## 5.11 Computational narrative

A computational subsection should distinguish the mathematical algorithm, implementation, parameter choices, validation or convergence checks, and reported output.

A suitable structure is:

```text
4.1 Discrete estimator
4.2 Numerical implementation
4.3 Convergence test
4.4 Results
```

Do not interleave raw code with every algebraic step unless the document is explicitly a literate notebook.

## 5.12 Output blocks

Preserve generated outputs verbatim when they constitute evidence. Do not silently round values, remove warnings, reorder output, delete failed runs, or replace actual output by a cleaned illustrative version. A cleaned or abbreviated output must be labeled as such.

## 5.13 Citations and bibliography keys

Preserve citation commands and keys exactly. Do not change citation command types without checking grammar, merge commands in a way that changes prenotes or postnotes, invent page numbers, replace a citation by an author name from memory, or reorder keys unless the project convention requires it.

## 5.14 Comments and revision markers

Preserve comments and revision macros. Do not remove commented-out equations or alternate passages unless instructed; they may record unresolved mathematical choices.

## 5.15 Encoding and typography

Preserve the project's policy for UTF-8 characters, TeX accents, quotation marks, dashes, nonbreaking spaces, thin spaces in units, and spelling conventions.

Do not normalize variants such as `C*-algebra`, `C^{*}`-algebra, and \(C^*\)-algebra without checking the project convention.

## 5.16 Compilation and rendering safety

After an edit, check for balanced delimiters and environments, undefined references, multiply defined labels, malformed citation commands, broken Markdown fences, damaged table rows, accidental code-indentation changes, unescaped special characters, and equations separated from their introductory sentences.

A successful compile is necessary but not sufficient. The rendered output should also be inspected around every edited display, theorem, figure, table, and page break when a renderer is available.

# Mandatory house rules

1. Use descriptive academic headings rather than promotional headings.
2. Format result headings as `Theorem <number>. <Name>`, `Proposition <number>. <Name>`, `Lemma <number>. <Name>`, or `Corollary <number>. <Name>`.
3. Introduce definitions through the problem that requires them.
4. Define operators with their space, domain, action, and relevant analytic status.
5. Place physical interpretation after or alongside the formal construction, never in place of it.
6. Use lists only for genuinely list-like mathematical material.
7. Introduce every display with a grammatical sentence and interpret it afterward when interpretation is needed.
8. Replace generic emphasis with an exact consequence.
9. Do not use takeaway boxes, repetitive recaps, or templated motivation--intuition--key-insight scaffolding.
10. Preserve notation, macros, labels, code, mathematical blocks, and theorem structure during prose editing.
11. Keep prose edits minimal and disclose substantive mathematical changes separately.

# Editorial preflight checklist

Before producing a patch, verify each edited file against the following questions:

1. Are all section and result headings descriptive and consistently formatted?
2. Does every paragraph perform a recognizable mathematical task?
3. Are definitions and operators introduced with their ambient objects and assumptions?
4. Does each displayed equation have a grammatical introduction and an appropriate continuation?
5. Are lists confined to axioms, equivalent conditions, algorithms, classifications, or other intrinsically list-like material?
6. Have promotional, conversational, generic-summary, and meta-writing phrases been removed?
7. Are claims of equivalence, completeness, universality, and reconstruction supported by the stated hypotheses?
8. Have notation, formulas, fenced math, tables, code, labels, and references been preserved?
9. Does the patch contain only the intended files and the smallest changes needed to satisfy the guide?
10. Does the patch apply cleanly to the stated baseline, and does the applied result match the reviewed working copy?
