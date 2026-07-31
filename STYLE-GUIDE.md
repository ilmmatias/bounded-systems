# Style Guide for Mathematical Physics Manuscripts

## Scope

This guide governs the research notebook's mathematical prose, section structure, notation, theorem presentation, and preservation of Markdown, LaTeX, bibliographic, and computational content. It is based off manuscripts in causal-set theory, discrete spacetime, graph operator algebras, noncommutative geometry, quantum foundations, and quantum gravity.

The governing principles are restraint, mathematical specificity, continuous narrative, explicit logical status, and exact preservation of technical content. Definitions are introduced when the argument requires them; operator data are stated before interpretive claims depend on them; physical motivation supplements rather than replaces formal construction; and lists are reserved for material that is intrinsically list-like.

The cited corpus includes research articles, reviews, and lecture notes with different rhetorical permissions. The stricter rule governs when those genres differ, unless the manuscript has explicitly been designated as expository or pedagogical.

## Research basis

The guide was created against the following representative corpus:

- Rafael D. Sorkin, `Causal Sets: Discrete Gravity`, arXiv:gr-qc/0309009.
- Fay Dowker, `Causal sets and the deep structure of spacetime`, arXiv:gr-qc/0508109.
- Joe Henson, `The causal set approach to quantum gravity`, arXiv:gr-qc/0601121.
- David W. Kribs and Baruch Solel, `A class of limit algebras associated with directed graphs`, arXiv:math/0411379.
- David W. Kribs and Stephen C. Power, `Free Semigroupoid Algebras`, arXiv:math/0309394.
- Mark Tomforde, `A unified approach to Exel-Laca algebras and $C^*$-algebras associated to graphs`, arXiv:math/0106161.
- Alain Connes, `Gravity coupled with matter and the foundation of non-commutative geometry`, arXiv:hep-th/9603053.
- Markus P. Müller, `Probabilistic Theories and Reconstructions of Quantum Theory`, arXiv:2011.01286.
- Lee Smolin, `The case for background independence`, arXiv:hep-th/0507235.
- Christopher J. Isham, `Canonical Quantum Gravity and the Problem of Time`, arXiv:gr-qc/9210011.
- Dmitry Kobak, Rita González-Márquez, Emőke-Ágnes Horvát, and Jan Lause, `Delving into LLM-assisted writing in biomedical publications through excess vocabulary`, arXiv:2406.07016; Science Advances 11 (2025).
- Mingmeng Geng and Roberto Trotta, `Is ChatGPT Transforming Academics' Writing Style?`, arXiv:2404.08627.

The corpus supports the following editorial conclusions.

First, theorem-driven operator-algebra papers generally use compact descriptive headings, short roadmap paragraphs, numbered formal statements, and definitions that fix spaces, generators, relations, and conventions before interpretation. Secondly, causal-set reviews and quantum-gravity lectures may use genuine disciplinary questions as headings, but the question is answered directly and followed by exact definitions or physical argument. Thirdly, equations are normally part of sentences: the preceding prose states what is being defined or derived, and the following prose identifies a consequence, hypothesis, or interpretation. Fourthly, lists occur naturally for axioms, operator relations, cases, research programmes, and propositions with separately referenced clauses; they are not used as a default substitute for exposition.

The studies of LLM-associated prose are population-level linguistic studies, not reliable authorship tests for individual passages. Their marker words therefore justify an editorial watchlist, not accusations of machine authorship. Words with legitimate technical meanings remain permissible in those meanings. The ban applies to generic rhetorical use, especially when several markers cluster in the same paragraph.

# 1. Structural conventions and section headers

## 1.1 Governing principle

A section title shall identify the mathematical object, task, result, comparison, or interpretive issue treated in that section. It shall not advertise the importance of the section, promise revelation, imitate a presentation slide, or attempt to create suspense.

The logical dependency of the argument, rather than a fixed content template, determines the section order. A standard research-article hierarchy is:

```text
1 Introduction
2 Preliminaries and notation
3 The causal or graph-theoretic construction
4 Main results
5 Examples or applications
6 Discussion
Appendix A Technical lemmas
```

This is a template rather than a compulsory sequence. A short paper may omit preliminaries, discussion, or conclusion. A paper should not contain a section solely because a generic template expects one.

## 1.2 Genre-specific permissions

Use the following hierarchy of permissions.

1. A theorem-driven research article should default to descriptive noun phrases and result-oriented headings.
2. A conceptual or foundational article may use a declarative claim as a heading when the section defends that precise claim.
3. A review or set of lecture notes may use a specialist question as a heading when the section answers it directly.
4. A computational notebook may use procedural headings when they identify a genuine stage of the calculation, such as `Discretization`, `Convergence test`, or `Error estimate`.

Do not import the conversational freedoms of lecture notes into a formal research article without a clear reason.

## 1.3 Preferred heading forms

Use compact descriptive headings such as:

- `Causal-set preliminaries`
- `Faithful embeddings`
- `Continuum approximation`
- `The discrete retarded propagator`
- `Graph correspondences`
- `The left-regular representation`
- `Toeplitz-Cuntz-Krieger families`
- `Gauge-invariant uniqueness`
- `Spectral triples and distance`
- `Existence of the representation`
- `Proof of Theorem 4.2`
- `Numerical implementation`
- `Convergence of the estimator`
- `Discussion and open problems`

A heading may contain notation only when that notation is already defined or is standard enough to be immediately intelligible. Do not introduce a new symbol in a heading.

## 1.4 Acceptable question headings

A question may be used as a section title only when all of the following hold:

1. The manuscript is substantially expository, conceptual, or review-oriented.
2. The question is meaningful to a specialist independently of the manuscript.
3. The section gives a determinate answer, a precise obstruction, or a documented state of knowledge.
4. The wording does not contain promotional adjectives or second-person address.

Acceptable examples include `What kind of discreteness?`, `Why is the qubit state space three-dimensional?`, and `How is locality recovered?`.

Do not use semantically vague or promotional questions such as `Why this changes everything`, `What is really going on here?`, `Can this powerful idea unlock quantum gravity?`, or `Why should the reader care?`.

## 1.5 Forbidden dramatic or presentation-style headers

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
- `The Secret Ingredient`
- `The Missing Piece`
- `A New Lens`
- `The Roadmap to Discovery`

`The Road Ahead` is permitted only for an actual research outlook when the publication style permits it. A memorable article title is permissible; a sequence of theatrical internal headings is not.

Do not put emojis, decorative symbols, or marketing punctuation in headings. Avoid repeated colon templates such as `Local Finiteness: Why It Matters` or `Spectral Distance: The Big Picture`.

## 1.6 Heading depth and granularity

Ordinarily, use no more than three numbered levels. A fourth level is appropriate only in a long monograph, review, or technical appendix.

Do not create a heading for a single short paragraph. A subsection should normally contain at least two substantive paragraphs, or one substantial formal result together with proof and discussion. When a short transition does not warrant a heading, write it as the opening sentence of the next paragraph.

Do not use multiple adjacent headings with no intervening prose.

## 1.7 Numbering and capitalization

Follow the target journal's capitalization and numbering conventions when they are known. Otherwise:

- use sentence case for Markdown headings;
- number major sections and substantive subsections;
- leave acknowledgements and references unnumbered unless the project template requires numbering;
- use letters for appendices;
- do not restart theorem numbering without a declared convention.

The manuscript shall use one heading-capitalization system consistently. Do not mix title case, sentence case, and all capitals merely for emphasis.

## 1.8 Theorem-style headings

When a theorem, proposition, lemma, corollary, definition, or remark is presented as a Markdown heading, use a period between the result number and its descriptive name:

```markdown
## Theorem 1. Algebraic universality
## Proposition 2. Faithfulness of the representation
## Lemma 3. Interval decomposition
## Corollary 4. Uniqueness of the extension
## Definition 5. Faithful embedding
```

Do not use parenthetical titles such as `Theorem 1 (algebraic universality)` in notebook Markdown. Preserve the target journal's theorem syntax in LaTeX source when it differs.

A proof heading may be `## Proof` when it is unambiguous, or `## Proof of Theorem 1` when separation from the theorem makes the reference useful.

The title of a result shall describe its conclusion, not praise it. Use `Faithfulness of the representation`, not `A powerful faithfulness theorem`.

## 1.9 Abstract structure

An abstract should state, in continuous prose:

1. the problem or class of objects;
2. the construction, method, or hypotheses;
3. the principal result;
4. a consequence, scope condition, or limitation when needed.

Do not include a roadmap, bullet list, literature survey, motivational anecdote, or undefined notation in the abstract. Avoid citations unless the journal or subject convention makes them necessary.

Do not claim novelty by adjective alone. Replace `We introduce a novel framework` by a statement of what object is introduced and how it differs from the nearest established construction.

## 1.10 Introduction structure

An introduction should normally perform the following work in continuous prose:

1. State the mathematical or physical problem.
2. Explain why the problem is nontrivial.
3. Identify the limitation in the existing framework or literature.
4. State the construction, hypotheses, or principal result of the manuscript.
5. Explain the significance by naming an exact consequence.
6. Delimit what is not proved or not treated.
7. Give a restrained roadmap when the document is long enough to require one.

The roadmap should be a single paragraph near the end of the introduction. It may name sections and results, but it shall not duplicate the table of contents sentence by sentence. Do not present the roadmap as a bullet list unless the manuscript is unusually long and the list materially improves navigation.

A research introduction should not begin with an unbounded claim such as `Since the dawn of time, humanity has sought to understand spacetime.` Begin at the scale of the problem actually addressed.

## 1.11 Section openings

The first paragraph of a section should establish its local purpose by continuing the argument, not by describing the act of writing. Prefer:

> To compare the discrete operator with the continuum retarded propagator, we first fix the normalization of the sprinkling density.

Avoid:

> In this section, we will explore the fascinating relationship between the discrete and continuum pictures.

A section may begin directly with a definition or theorem when the preceding section has already supplied the motivation.

## 1.12 Section endings

End a section when its local mathematical task is complete. A final sentence may state a consequence, limitation, or transition. Do not append a generic recap to every section.

A section-ending transition should identify the dependency that motivates the next section, for example:

> The construction is therefore covariant at fixed sprinkling density; the remaining issue is its continuum limit.

Do not write `Having established this powerful foundation, we are now ready to move on.`

## 1.13 Terminal sections

Use descriptive titles such as `Discussion`, `Discussion and outlook`, `Conclusion`, `Open problems`, or `Limitations and open questions`.

Do not automatically include both `Discussion` and `Conclusion`. Use both only when they serve different functions: discussion treats interpretation, comparison, limitations, and implications; conclusion gives a compact statement of established results.

A conclusion shall not reproduce the abstract sentence by sentence, introduce a new theorem, or convert open conjectures into established claims.

## 1.14 Appendices

Use appendices for technical lemmas, convention-dependent calculations, auxiliary data, long tables, implementation details, or proofs whose placement would interrupt the main argument.

An appendix title must state its content, for example `Appendix A. Poisson estimates` or `Appendix B. Domain of the discrete Dirac operator`. Do not use `Additional material` or `Technical details` when a more specific title is available.

# 2. Prose and narrative integration

## 2.1 The basic narrative unit

Each paragraph should perform one identifiable mathematical task: motivate a definition, fix notation, state a construction, derive a relation, interpret a result, delimit an assumption, compare with a known object, introduce a proposition, or explain the next proof step.

Do not combine broad motivation, several unrelated definitions, a literature review, a derivation, and a conclusion in one paragraph.

A paragraph should have a logical center. If two sentences cannot be connected by a clear mathematical relation, they probably belong in different paragraphs.

## 2.2 Dependency order

Present material in the order required to understand it. The default dependency order is:

1. problem or required property;
2. ambient objects and standing hypotheses;
3. notation and conventions;
4. definition or construction;
5. immediate consequence;
6. formal result or derivation;
7. interpretation, comparison, or next use.

This order may be compressed, but it shall not be reversed merely for dramatic effect. Do not announce an operator's physical significance several paragraphs before the reader knows its domain or action.

## 2.3 Required order for a new mathematical object

Unless there is a strong reason otherwise, introduce a new object in this order:

1. Identify what the object must encode or accomplish.
2. Specify the ambient spaces, algebras, graphs, domains, measures, or assumptions.
3. Give the definition and its formula.
4. State the first immediate consequence.
5. Explain its physical or structural interpretation.
6. State how it enters the next result.

A standard operator introduction has the form:

```latex
Let $E=(E^0,E^1,r,s)$ be a countable directed graph, and let
$\mathcal H_E=\ell^2(E^*)$ with canonical basis
$\{\xi_\mu:\mu\in E^*\}$. For $e\in E^1$, define
\[
L_e\xi_\mu =
\begin{cases}
\xi_{e\mu}, & s(e)=r(\mu),\\
0, & \text{otherwise}.
\end{cases}
\]
Thus $L_e$ acts by left concatenation on admissible paths. It is a
partial isometry whose initial projection is determined by the relevant
vertex projection.
```

The formula is neither preceded nor followed by an isolated label such as `Definition:` unless a formal definition environment is warranted.

## 2.4 Definitions in prose and formal environments

Use a numbered definition when at least one of the following applies:

- the term is used throughout the manuscript;
- later statements refer to the definition by number;
- the definition has several hypotheses;
- variants of the definition must be distinguished;
- the object is original to the manuscript;
- the precise logical form is central to a theorem.

Use ordinary prose for local notation, for example:

> We write $I(x,y)=\{z\in C:x\prec z\prec y\}$ for the open order interval.

Do not create a formal definition for every symbol. Do not hide a central definition in a parenthetical aside.

## 2.5 Syntactic integration of definitions

Preferred:

> A causal set is a pair $(C,\prec)$ in which $\prec$ is an irreflexive, transitive, and locally finite relation.

A list is appropriate when the axioms themselves require individual emphasis or later reference. Do not replace an exact definition by a detached list of informal `ingredients`, `building blocks`, or `pillars`.

When a definition follows motivation, the transition should state the logical need:

> The embedding condition alone does not fix the discreteness scale. We therefore require the image to arise with Poisson density $\rho$.

## 2.6 Operator definitions

An operator definition is incomplete unless the reader can recover, as relevant:

1. the ambient Hilbert, Banach, Fock, module, or representation space;
2. the domain when it is not the whole space;
3. the action on a general vector, basis, core, or generating set;
4. the parameter dependence;
5. linearity or conjugate-linearity conventions;
6. boundedness, closability, symmetry, self-adjointness, or affiliation status;
7. the topology in which a sum or limit converges;
8. the notation for adjoints, closures, extensions, or resolvents if later used.

Preferred:

```latex
On the dense subspace
$\mathcal D_0=\operatorname{span}\{\xi_\mu:\mu\in E^*\}\subset\mathcal H_E$,
define
\[
D_0\xi_\mu=\lambda_\mu\xi_\mu .
\]
Since $\lambda_\mu\in\mathbb R$, the operator $D_0$ is symmetric.
Its closure will be denoted by $D$.
```

Do not write a formal-looking series for an operator without specifying its domain, convergence, basis assumptions, and operator class. Do not infer self-adjointness from a real diagonal formula unless the domain and closure justify it.

## 2.7 Families of generators and relations

When an algebra is defined by generators and relations, state the types of the generators before displaying the relations. Identify whether the construction is universal, concrete, norm closed, weak-operator closed, or represented on a specified space.

Preferred order:

1. declare the graph or correspondence;
2. declare projections, partial isometries, or creation operators;
3. display the relations;
4. state the universal property or concrete realization;
5. identify the generated algebra and topology.

A grouped display or numbered list is appropriate for relations that will be cited separately. It is not `shopping-list mathematics` when the list is the mathematical object.

## 2.8 Displayed equations

Every displayed equation must have a grammatical function.

The preceding sentence must tell the reader what the display does, using formulations such as `The left action is therefore given by`, `The expected number of sprinkled elements is`, `The operator takes the form`, or `Using the decomposition above, we obtain`.

Avoid repeated empty introductions such as `We have:`, `The equation is:`, `Mathematically:`, and `This can be written as follows:`.

The sentence following a display should do at least one of the following when needed:

- define remaining symbols;
- identify an immediate consequence;
- explain the relevant limiting case;
- relate the expression to the preceding construction;
- state the topology or sense of convergence;
- state how the equation will be used.

Do not restate the display in words unless the restatement adds interpretation or isolates a non-obvious consequence.

## 2.9 Equation punctuation

A displayed equation is part of the surrounding sentence. Use commas, semicolons, or periods according to the grammar of that sentence. Do not strip punctuation merely because an expression is displayed.

When several displays form one derivation, use prose between them to mark the reason for each step. Do not present a page of equalities with no indication of which hypothesis, identity, or estimate is being used.

## 2.10 Inline and displayed mathematics

In Markdown research files, delimit inline mathematics with `$...$` unless the project already uses a different convention. Do not introduce `\(...\)` into a file standardized on dollar delimiters.

Use inline mathematics for short memberships, simple conditions, compact maps, and symbols being named or compared.

Use display mathematics for central definitions, multi-case operators, chains of equalities used in an argument, relations with several quantifiers or indices, equations that will be referenced, and identities whose structure must be visually inspected.

Do not display a one-symbol statement merely to make it appear important. Do not put a long derivation inline merely to avoid a display.

## 2.11 Notation discipline

Every nonstandard symbol must be defined at first use. A notation table does not repair undefined notation in the prose.

Use one symbol for one object within an argument. Do not use the same letter for a graph and a conditional expectation, a projection and a probability measure, or dimension and distance.

Decorations must be systematic. If $A$, $\widehat A$, $\mathcal A$, $\overline A$, and $A^*$ occur, their distinctions must be explicit.

For a map $f:X\to Y$, state the domain and codomain at its first formal introduction. When several maps appear, state what structure they preserve.

For graphs, declare the orientation and path-composition convention once. In particular, say whether $e\mu$ means that $e$ is traversed before or after $\mu$. Do not silently reverse the convention later.

For causal sets, declare whether the order is reflexive or irreflexive and whether intervals include endpoints. Do not alternate between $\prec$ and $\preceq$ without defining both.

For $C^*$-algebras, distinguish algebraic span, norm closure, strong or weak operator closure, multiplier algebra, and bicommutant. Do not use `generated by` without identifying the closure when ambiguity matters.

## 2.12 Quantifiers and hypotheses

Place standing assumptions before the first statement that uses them. Do not let a crucial finiteness, separability, row-finiteness, no-source, covariance, or regularity hypothesis appear only in a proof.

Use quantifiers when they remove ambiguity, but do not overload prose with symbolic quantifiers when a sentence is clearer. A definition may state `for every $x,y\in C$`; a theorem may use `for all` or a formal quantifier according to local style.

When weakening or strengthening a hypothesis, state the change explicitly. Do not use `more generally` without naming what is generalized.

## 2.13 Operational motivation and formal rigor

The manuscript should operate on two connected levels.

At the operational or physical level, explain what can be prepared, observed, counted, reconstructed, or approximated; which continuum quantity a discrete object represents; why an operator is physically natural; and what covariance or symmetry requirement is imposed.

At the formal level, state the mathematical object, assumptions, map or operator, exact claim, topology, norm, measure, probability law, or convergence notion, and the proof or citation.

Do not blur these levels. The verbs `represents`, `corresponds to`, `approximates`, `recovers`, and `emerges as` must distinguish among:

- equality;
- isomorphism or unitary equivalence;
- faithful representation;
- asymptotic convergence;
- convergence in probability or distribution;
- expectation-value agreement;
- coarse-grained correspondence;
- heuristic interpretation.

A physical analogy may motivate a definition, but it cannot serve as its proof.

## 2.14 Logical status markers

Mark the status of a statement accurately.

- Use `Theorem`, `Proposition`, `Lemma`, or `Corollary` only for proved statements.
- Use `Conjecture` for a precise unproved claim.
- Use `Hypothesis` or `Assumption` for an adopted premise.
- Use `Heuristic` or `heuristically` for an argument not claimed as proof.
- Use `numerical evidence suggests` when the support is computational.
- Use `we expect` only when the basis for the expectation is stated or cited.
- Use `analogy` only when the correspondence is not asserted to be exact.

Do not let `suggests`, `indicates`, or `is consistent with` drift into `shows` in the next paragraph.

## 2.15 Permitted narrative transitions

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
- `The embedding condition does not determine the density; we therefore impose ...`
- `To pass from the algebraic action to a bounded representation, it suffices to show ...`

These transitions state logical relations. Avoid transitions that merely announce activity, such as `Next, we dive into`, `We now explore`, `Let us unpack`, `With this foundation in place`, `Armed with these insights`, `This brings us to`, and `Now comes the exciting part`.

## 2.16 Paragraph conclusions

End a technical paragraph with a consequence, limitation, or forward connection. Do not repeatedly end with generic emphasis such as `This is important`, `This observation is crucial`, `This provides a powerful framework`, or `This will be useful later`.

Replace generic emphasis by the exact consequence. For example:

> Consequently, $L_e^*L_e=P_{r(e)}$, so the initial projection depends only on the range vertex.

When no interpretive sentence is needed, end with the formula or formal conclusion without adding praise.

## 2.17 Proof style

A proof should begin with its mathematical strategy rather than ceremonial language.

Preferred:

> It suffices to prove that the representation is faithful on the fixed-point algebra, since gauge covariance then gives the result.

Avoid:

> We now embark on the proof of this important theorem. The proof consists of several key steps.

Within a proof:

- identify the reduction or strategy at the start when it is not immediate;
- cite equations by label when labels are available;
- identify where hypotheses are used;
- distinguish equality from isomorphism, unitary equivalence, approximation, and containment;
- state the topology of convergence;
- do not say `it is easy to see` when a one-line reason can be given;
- close with the result rather than a recap of the entire proof.

A proof may be divided into claims or cases when the division reflects actual logical structure. Do not manufacture `Step 1`, `Step 2`, and `Step 3` merely to make a short proof look organized.

## 2.18 Citations and attribution in prose

A factual historical claim, priority claim, known theorem, or borrowed construction requires an exact citation. Do not write `It is well known that` when the result is specialized, convention-dependent, or central to the argument.

Prefer:

> By the gauge-invariant uniqueness theorem for row-finite graphs [citation], the representation is faithful.

Avoid:

> Many studies have shown that the representation is robust.

When a result exists in several forms, cite the form whose hypotheses match the manuscript. Do not cite a review for a delicate theorem when the primary source is available and usable.

## 2.19 Voice, tense, and person

First-person plural is acceptable for authorial actions: `we define`, `we prove`, `we assume`, and `we compare`. Do not use `we` to coerce agreement, as in `we can clearly see`.

Use present tense for definitions and established relations, past tense for actions performed in a computation or experiment, and future tense sparingly for local signposting.

Second-person address is normally inappropriate in a research article. It may appear in lecture notes when pedagogically justified, but it is not the notebook default.

# 3. Ban list of LLM artifacts

## 3.1 Scope and evidentiary rule

The forms below are forbidden in manuscript prose unless they occur in a quotation, a bibliographic title, or necessary technical terminology.

The purpose of this section is editorial, not forensic. No single word, punctuation mark, sentence rhythm, or formatting habit proves LLM use. The rule targets generic, inflated, repetitive prose that weakens mathematical writing regardless of its origin.

Words in the context-sensitive watchlist are forbidden as generic evaluative decoration. They remain permissible when they have an exact technical meaning, such as `statistically significant`, `robust optimization`, `string landscape`, or `pivotal operator` in an established technical usage.

## 3.2 Promotional or inflated phrases

Do not use:

- `at its core`
- `in the grand scheme of things`
- `in today's rapidly evolving landscape`
- `a powerful lens`
- `a powerful framework`
- `a powerful toolkit`
- `a rich tapestry`
- `a fascinating interplay`
- `an intricate interplay`
- `a profound connection`
- `a deep and subtle relationship`
- `a groundbreaking perspective`
- `a game-changing result`
- `a remarkable journey`
- `an elegant dance`
- `serves as a testament to`
- `stands as a testament to`
- `unlocking the potential of`
- `unpacking the complexities of`
- `delving into`
- `taking a deep dive into`
- `navigating the complexities of`
- `bridging the gap between`
- `paving the way for`
- `ushering in a new era`
- `a paradigm shift`
- `a holistic approach`
- `seamlessly integrates`
- `seamlessly bridges`
- `offers valuable insights into`
- `sheds light on` when no concrete clarification is named
- `highlights the importance of` when the consequence can be stated directly
- `underscores the need for` when no argument is supplied
- `plays a pivotal role`
- `plays a crucial role`
- `holds immense promise`
- `opens exciting avenues`
- `marks a significant step forward`

Replace evaluative language with mathematical content.

Instead of:

> This powerful construction reveals a profound connection between the graph and its operator algebra.

write the exact conclusion, for example:

> The isometric isomorphism class of the algebra determines the multiplicity $C_{ij}$ of the arrows from $j$ to $i$.

## 3.3 Context-sensitive LLM-associated watchlist

The following words have been reported as unusually frequent in corpora of LLM-assisted scientific prose or are strongly associated with generic generated exposition. Do not use them as automatic praise, transition, or intensification:

- `delve`, `delves`, `delving`, `delved`
- `intricate`, `intricacies`, `intricately`
- `pivotal`
- `showcase`, `showcases`, `showcasing`
- `underscore`, `underscores`, `underscoring`
- `garner`, `garnered`, `garnering`
- `realm` or `realms`
- `multifaceted`
- `nuanced` when no specific distinction follows
- `notably` when the sentence itself does not establish noteworthiness
- `comprehensive` when the scope is not demonstrably comprehensive
- `valuable` when no criterion of value is given
- `compelling` when no argument is supplied
- `remarkable` when no comparison or estimate justifies it
- `innovative` or `novel` without an explicit novelty statement
- `transformative`
- `holistic`
- `seamless`
- `robust` when the intended meaning is merely useful, stable-looking, or well-defined
- `fundamental` when the claim is only locally useful
- `crucial`, `essential`, or `key` used repeatedly as emphasis rather than logically
- `significant` when neither statistical significance nor a specified mathematical consequence is intended
- `insight` or `insights` used as a substitute for a stated result
- `landscape` used as a generic synonym for field, area, or collection
- `leverage` used as an inflated synonym for use
- `enhance` used without identifying the improved quantity or criterion
- `facilitate` used without identifying what operation becomes possible

A cluster of these words in one paragraph requires revision even when each word might be defensible in isolation.

## 3.4 Conversational filler

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
- `Think of it as ...` when an exact definition is available
- `Imagine that ...` in place of specifying a model or assumption
- `The beauty of this is ...`
- `What makes this exciting is ...`

## 3.5 Meta-writing and activity announcements

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
- `We now turn our attention to ...` when the mathematical dependency can be named
- `It is important to note that ...`
- `It should be emphasized that ...`
- `One should keep in mind that ...` when the point can be stated directly

State the mathematical action directly, for example:

> We first prove boundedness on finite-path subspaces.

## 3.6 Generic summaries and takeaway blocks

Do not use recurring blocks or paragraphs headed:

- `Key takeaway`
- `Main insight`
- `What we learned`
- `Why this matters`
- `In a nutshell`
- `Quick recap`
- `Summary of the section`
- `Putting it all together`
- `The big picture`
- `Take-home message`
- `Bottom line`

A formal article may contain a proposition collecting equivalent conditions or a conclusion summarizing results. It should not contain pedagogical takeaway boxes after each subsection.

Do not end every section with `In summary` followed by a restatement of the opening paragraph.

## 3.7 Shopping-list mathematics

Do not replace a mathematical dependency by a list of informal ingredients.

Avoid:

> We need the following ingredients:
> - a graph;
> - a Hilbert space;
> - some operators;
> - a causal interpretation.

Write instead:

> Let $E$ be a directed graph. Its finite paths index the canonical basis of the Hilbert space $\mathcal H_E$, on which the edge operators act by left concatenation.

Forbidden list labels include `building blocks`, `pillars`, `ingredients`, `components of success`, and `pieces of the puzzle` when the entries are ordinary dependencies in a definition.

## 3.8 Arbitrary numbered promises

Do not write `There are three key reasons for introducing this operator` unless there are exactly three mathematically independent reasons and the enumeration improves later reference.

Do not manufacture the numbers three, four, or five for rhetorical symmetry. Do not force a paragraph into a triad of adjectives or claims when the argument has a different structure.

## 3.9 Repetitive internal templates

Do not repeat a fixed schema such as:

```text
Motivation
Core idea
Formal definition
Intuition
Why it matters
Key takeaway
```

The section structure must follow the argument rather than an invariant content template.

Do not begin every subsection with a question, follow every equation with `This means`, or close every proof with a general statement about importance.

## 3.10 Bold-label bullet patterns

Avoid strings of bullets whose entries begin with bold conversational labels such as:

- `**Intuition:** ...`
- `**Key idea:** ...`
- `**Why it matters:** ...`
- `**Takeaway:** ...`
- `**Result:** ...`

Use prose, a formal definition, or a theorem environment unless the entries are genuinely parallel and independently referable.

Do not use boldface as a substitute for logical structure.

## 3.11 Artificial contrasts and balanced slogans

Avoid formulaic constructions when they do not express a real logical distinction:

- `not merely X, but Y`
- `not only X; it also Y`
- `rather than simply X, it fundamentally Y`
- `from X to Y`
- `where intuition meets rigor`
- `both elegant and powerful`
- `simple yet profound`
- `local in form, global in meaning`

Use contrast only when both sides are mathematically relevant and the contrast advances the argument.

A related form states what a result does not claim instead of stating the limitation itself. Replace the disclaimer by the fact.

Avoid:

> The theorem gives a qualitative stability modulus. It does not claim that the function $\delta(\varepsilon)$ is computationally efficient.

Write:

> The argument is a compactness argument and produces no bound on $\delta(\varepsilon)$.

The revision is shorter, states the limitation positively, and is more accurate: the proof takes a minimum over a compact set, so no modulus is produced at all, efficient or otherwise. A disclaimer of this kind also tends to misdescribe the gap it is disclaiming.

A negative statement is justified only when it forecloses a specific misreading that the positive form would leave open, as in separating a global impossibility from the corresponding individual one, or in distinguishing a result forced by the primitive assumptions from one forced only after a selector is specified. Even then, state the positive content in the same passage.

## 3.12 Excessive signposting

Use no more than one roadmap paragraph in an introduction. Do not give a second roadmap at the start of every section and a recap at its end.

Avoid chains such as `First`, `Next`, `Then`, `Finally` when the relations are causal, logical, or inferential rather than merely chronological. Prefer `Because`, `Hence`, `By contrast`, `Under this hypothesis`, or a direct statement of the dependency.

## 3.13 Empty intensifiers and certainty claims

Avoid `clearly`, `obviously`, `evidently`, `trivially`, `undeniably`, `certainly`, `manifestly`, and `without question` unless the assertion genuinely follows immediately and the wording would not discourage scrutiny.

Prefer exact reasons: `By transitivity`, `Equation (3.4) gives`, or `The claim follows from Lemma 2.3.`

Do not use `straightforward` to conceal a nontrivial calculation. Either give the calculation, cite it, or state precisely what is omitted.

## 3.14 Unsupported claims of completeness, equivalence, and novelty

Do not write `This completely characterizes`, `This resolves the issue`, `This proves consistency`, `This establishes equivalence`, `This unifies`, or `This is the first` unless the theorem or documented literature search supports exactly that conclusion under specified hypotheses.

Use `if and only if` only for a proved biconditional. Do not replace a one-way implication by `equivalent` in explanatory prose.

Novelty claims must identify the comparison class and the new feature. `To our knowledge` does not excuse an inadequate literature search.

## 3.15 Vague authority and citation artifacts

Do not use:

- `research shows`
- `studies have demonstrated`
- `experts agree`
- `it is widely believed`
- `the literature suggests`
- `recent advances have shown`

unless an exact citation and a precise claim follow.

Never invent a citation, theorem name, equation number, page number, DOI, arXiv identifier, or author attribution. A plausible-looking reference is not an acceptable placeholder.

Use an explicit unresolved marker such as `[[citation needed]]` if the project permits it; otherwise report the gap outside the manuscript.

## 3.16 Formulaic conclusions

Do not close a manuscript with phrases such as:

- `In conclusion, we have explored ...`
- `The future is bright ...`
- `Only time will tell ...`
- `This opens the door to countless possibilities ...`
- `The journey does not end here ...`
- `These findings pave the way for future research ...`

State the proved result, its limitation, and a specific open problem.

## 3.17 Punctuation and rhythm

To prevent structural ambiguity and maintain mathematical precision, enforce strict limits on complex punctuation. Do not use humanities-style rhetorical prose elements.

1. Dashes: Ban em dashes (—) and en dashes (–) entirely. They visually conflict with minus signs and mathematical operators. Use standard precise conjunctions instead.
2. Semicolons: Restrict semicolons to separating distinct mathematical conditions, coordinate clauses with mathematical equivalence, or parameter arguments in functions. Do not use them for stylistic variation.
3. Parentheses: Reserve parenthetical remarks strictly for technical specifications, alternative units, or grouping operators. If a remark can be deleted without changing the logical proof of the sentence, remove it.
4. Rhetorical Lists: Eliminate decorative three-part lists. Information must be presented as binary logical progressions, chronological steps, or explicit bulleted items.

## 3.18 Permitted lists

Lists are appropriate for:

- axioms;
- standing assumptions;
- mutually exclusive cases;
- equivalent conditions in a theorem;
- clauses of a proposition that are referenced later;
- steps of an actual algorithm;
- input and output specifications;
- classifications;
- research programmes being explicitly compared;
- finite collections that are individually discussed.

Lists must have parallel grammatical form. Use numbering when order or later reference matters. Introduce the list with a complete sentence that states what the entries are.

## 3.19 Editorial test for suspected LLM-style prose

Revise a paragraph when two or more of the following are present:

1. evaluative adjectives without mathematical criteria;
2. a promotional transition followed by an elementary definition;
3. repeated `This` sentences that restate rather than advance the argument;
4. arbitrary bullets or numbered claims;
5. a cluster of watchlist words;
6. a heading that promises importance rather than naming content;
7. a conclusion that repeats the introduction without adding scope or limitations;
8. vague citations or unverified priority claims;
9. mathematical symbols introduced without spaces, domains, or conventions;
10. smooth prose that conceals a missing hypothesis or unsupported implication.

The correction is not to make the prose awkward. The correction is to replace generic fluency with exact mathematical relations.

# 4. Concrete transformations

## 4.1 Causal-set definition

### Before [AI style]

> ### The Core Building Blocks of Causal Structure
>
> The causal-set framework rests on three powerful pillars:
>
> - **Events:** the basic building blocks of spacetime.
> - **Causal order:** a relation that tells us which events influence others.
> - **Local finiteness:** a crucial discreteness condition.
>
> Together, these ingredients provide a robust and elegant framework for replacing the continuum.

### After [arXiv style]

> Let $C$ be a set equipped with a relation $\prec$. We interpret $x\prec y$ as saying that $x$ lies to the causal past of $y$. The relation is required to be irreflexive and transitive. Discreteness is imposed by local finiteness: for every $x,y\in C$, the interval
> \[
> I(x,y)=\{z\in C:x\prec z\prec y\}
> \]
> is finite. A pair $(C,\prec)$ satisfying these conditions is called a causal set.

The revision motivates the relation, states the exact axioms, introduces interval notation where it is needed, and names the resulting object without making an unsupported claim about replacing the continuum.

## 4.2 Graph creation operators

### Before [AI style]

> ### Unlocking the Operator Construction
>
> We now introduce the key operator that brings the graph to life. For every edge, we create a shift operator. Intuitively, it adds the edge to a path:
>
> \[
> L_e|\mu\rangle=|e\mu\rangle.
> \]
>
> This elegant construction forms the heart of the graph algebra and shows the deep connection between paths and quantum creation operators.

### After [arXiv style]

> Let $E=(E^0,E^1,r,s)$ be a directed graph, and let $\mathcal H_E=\ell^2(E^*)$ with canonical basis $\{\xi_\mu:\mu\in E^*\}$. We use the convention that $e\mu$ is defined when $s(e)=r(\mu)$. For $e\in E^1$, define
> \[
> L_e\xi_\mu=
> \begin{cases}
> \xi_{e\mu}, & s(e)=r(\mu),\\
> 0, & s(e)\neq r(\mu).
> \end{cases}
> \]
> Thus $L_e$ acts by left concatenation on admissible paths. It is a partial isometry and may be regarded as a creation operator on the graph Fock space.

The revision supplies the Hilbert space, basis, path convention, action on inadmissible paths, and operator class before giving the interpretation.

## 4.3 Spectral distance

### Before [AI style]

> ### A Powerful New Notion of Distance
>
> The Dirac operator does much more than encode geometry. In fact, it unlocks an entirely new way of measuring distance:
>
> \[
> d(\varphi,\psi)=\sup |\varphi(a)-\psi(a)|.
> \]
>
> The key takeaway is that noncommutative geometry replaces ordinary paths with operator-algebraic information.

### After [arXiv style]

> Let $(\mathcal A,\mathcal H,D)$ be a spectral triple. For states $\varphi$ and $\psi$ on the norm closure of $\mathcal A$, define
> \[
> d_D(\varphi,\psi)
> =
> \sup\left\{
> |\varphi(a)-\psi(a)|:
> a\in\mathcal A,\ \lVert[D,a]\rVert\leq 1
> \right\}.
> \]
> The commutator bound is the noncommutative analogue of a Lipschitz condition. In the commutative spin-manifold case, the restriction of $d_D$ to pure states corresponding to points agrees with the geodesic distance.

The revision specifies the spectral triple, restores the constraint in the supremum, identifies the functionals, and states the geometric interpretation in a precise case.

## 4.4 Operational motivation and formal state space

### Before [AI style]

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

### After [arXiv style]

> Consider a prepare-and-measure experiment with conditional probabilities $P(k\mid p,m)$, where $p$ labels a preparation, $m$ a measurement, and $k$ an outcome. Two preparations $p$ and $p'$ define the same operational state when
> \[
> P(k\mid p,m)=P(k\mid p',m)
> \]
> for every $m$ and $k$. Measurement outcomes are identified analogously whenever they induce the same probabilities for all preparations. The resulting equivalence classes may then be represented by states and effects in dual real vector spaces, with their pairing equal to the observed probability.

The revision begins with observable data, defines states through an explicit equivalence relation, and introduces the vector-space representation only after the operational quotient has been specified.

# 5. File-format preservation

These rules are mandatory unless a separate instruction explicitly authorizes mathematical or structural refactoring.

## 5.1 Minimal-diff principle

Make the smallest edit that achieves the requested stylistic correction.

Do not reorder equations for stylistic symmetry, rename symbols while editing prose, replace theorem environments with ordinary paragraphs, convert citation systems, normalize all formatting across a file without approval, or repair unrelated mathematical issues silently.

Substantive mathematical corrections must be reported separately from prose edits. When possible, place them in a separate commit or patch.

## 5.2 Content-zone classification

Before editing, classify each span as one of the following:

1. ordinary prose;
2. inline mathematics;
3. displayed mathematics;
4. theorem-like environment;
5. citation or cross-reference command;
6. Markdown table;
7. fenced code or pseudocode;
8. generated output;
9. YAML or other front matter;
10. HTML, template, or renderer-specific markup;
11. comment or revision marker.

Only ordinary prose is freely editable during a prose-only pass. Every other zone is protected unless the request explicitly includes it.

## 5.3 Protected mathematical spans

Treat the contents of inline and displayed mathematical delimiters and environments as protected unless mathematical editing is explicitly requested:

```latex
$...$
$$...$$
\[...\]
\begin{equation}...\end{equation}
\begin{equation*}...\end{equation*}
\begin{align}...\end{align}
\begin{align*}...\end{align*}
\begin{gather}...\end{gather}
\begin{multline}...\end{multline}
\begin{cases}...\end{cases}
```

Prose surrounding a block may be revised without rewriting the block.

Do not automatically convert delimiter conventions or replace Unicode symbols by LaTeX commands. Such normalization may affect compilation, line numbering, renderer behavior, or repository diffs and requires explicit approval.

## 5.4 Raw LaTeX block integrity

Within a protected LaTeX block, preserve exactly unless instructed otherwise:

- alignment markers `&`;
- line breaks `\\`;
- equation tags and suppression commands such as `\tag`, `\notag`, and `\nonumber`;
- `\intertext` placement;
- delimiter sizing commands;
- spacing commands;
- nested environments;
- comments following `%`;
- macro names and arguments;
- labels and anchors.

Do not wrap, reindent, or reorder an `align` environment solely for appearance. A harmless-looking change can alter alignment, numbering, or macro expansion.

## 5.5 Labels and references

Preserve exactly:

```latex
\label{...}
\ref{...}
\eqref{...}
\pageref{...}
\autoref{...}
\cref{...}
\Cref{...}
```

Never invent a reference key to conceal a missing reference. When moving a paragraph, verify that the referenced object remains correctly placed and that positional words such as `above` and `below` remain accurate.

Prefer explicit references such as `Equation \eqref{eq:propagator}` over positional phrases when editing makes the latter unstable.

## 5.6 Macros and notation commands

Preserve user-defined macros and their argument structure. Do not expand, rename, or replace a macro unless asked. A macro may encode typography, semantic markup, indexing behavior, accessibility, or compatibility with another file.

Before editing notation, inspect the preamble or macro file. Never infer a macro's meaning solely from its name.

Do not replace `\mathcal H_E` by `H_E`, `\Cstar` by `$C^*$`, or a semantic macro by its visual expansion without project approval.

## 5.7 Theorem-like environments

Preserve definitions, theorems, lemmas, propositions, corollaries, assumptions, conjectures, remarks, examples, and proofs.

Do not remove optional theorem titles, move hypotheses out of a theorem without checking scope, merge a theorem and its proof, change proof endings, or turn numbered results into unnumbered prose.

When improving a theorem statement, maintain the logical order: ambient objects, hypotheses, quantified variables, conclusion, and exceptional or equality cases.

Preserve `\qed`, `\qedhere`, and custom proof-ending conventions.

## 5.8 Equation punctuation and surrounding prose

Preserve or repair punctuation according to the prose sentence containing the equation. The punctuation following a display is part of the sentence and should not be stripped by automated formatting.

When changing the sentence before a display, verify that introductory words such as `where`, `with`, `such that`, and `namely` still govern the display grammatically.

Do not separate an equation from the sentence that introduces it by inserting an unrelated paragraph or heading.

## 5.9 Markdown mathematics

In Markdown manuscripts:

- preserve the existing delimiter convention;
- do not mix delimiter systems without need;
- do not indent display mathematics unless it is intentionally part of a list or quotation;
- preserve blank lines required by the renderer;
- keep fenced code distinct from mathematical blocks;
- do not place block mathematics inside inline code marks;
- do not convert raw LaTeX into rendered Unicode during a prose edit.

Do not place a display equation inside a Markdown table cell unless the renderer is known to support it reliably.

## 5.10 Markdown tables

Treat a table's column count, alignment row, and pipe structure as fixed. Preserve escaped pipes, inline code, citation markers, HTML breaks, and renderer-specific syntax.

Do not reflow a table if it contains multiline code, LaTeX environments, manually aligned data, HTML tags, citation markers, or long operator definitions.

A derivation does not belong in a table. Move it into prose only with explicit structural permission.

When editing a cell, verify that no unescaped `|` has been introduced and that every row retains the same number of columns.

## 5.11 Lists in Markdown and LaTeX

Do not convert prose into bullets merely to shorten sentences.

When a formal list is retained:

- keep entries grammatically parallel;
- preserve numbering when entries are referenced later;
- do not change `enumerate` to `itemize` when order matters;
- preserve custom labels and counters;
- check nested indentation;
- do not insert blank lines that alter Markdown numbering;
- do not change a theorem's numbered clauses into bullets.

Do not wrap a mathematical list in conversational labels such as `Key points` or `Main takeaways`.

## 5.12 Code and computational sections

Treat fenced code, scripts, notebooks, pseudocode, command lines, and configuration blocks as protected technical content. Preserve:

- indentation;
- language identifiers;
- variable and function names;
- comments when they are semantically significant;
- line continuations;
- string literals;
- regular expressions;
- shell quoting;
- random seeds;
- file paths;
- units;
- numerical precision;
- dependency versions;
- command-line flags;
- expected output formatting.

Do not improve prose inside executable strings or comments when doing so might change a test, parser, output comparison, command, doctest, or generated documentation.

Do not run a general Markdown formatter across code-heavy files without a verified exclusion mechanism.

## 5.13 Computational narrative

A computational subsection should distinguish:

1. the mathematical algorithm or estimator;
2. the discretization or data representation;
3. the implementation and dependency versions;
4. parameter choices and random seeds;
5. validation, error, or convergence checks;
6. reported output and interpretation.

A suitable structure is:

```text
4.1 Discrete estimator
4.2 Numerical implementation
4.3 Convergence test
4.4 Results
```

Do not interleave raw code with every algebraic step unless the document is explicitly a literate notebook.

Do not claim agreement with theory without naming the error metric, tolerance, sample size, or limiting procedure.

## 5.14 Output blocks and generated evidence

Preserve generated outputs verbatim when they constitute evidence. Do not silently round values, remove warnings, reorder output, delete failed runs, or replace actual output by a cleaned illustrative version.

A cleaned, truncated, or reformatted output must be labeled as such. Record the command or cell that produced it when reproducibility matters.

Do not edit timestamps, hashes, environment summaries, or version reports to make an output block look cleaner.

## 5.15 Citations and bibliography keys

Preserve citation commands and keys exactly. Do not change citation command types without checking grammar, merge commands in a way that changes prenotes or postnotes, invent page numbers, replace a citation by an author name from memory, or reorder keys unless the project convention requires it.

Protected forms include:

```latex
\cite{...}
\citep{...}
\citet{...}
\parencite{...}
\textcite{...}
\footcite{...}
```

In Markdown, preserve citation syntax such as `[@key]`, `[-@key]`, and project-specific reference links.

## 5.16 Front matter, HTML, and renderer directives

Preserve YAML front matter, Pandoc attributes, Quarto options, Jupyter cell metadata, MyST directives, HTML tags, and static-site shortcodes unless the request explicitly includes them.

Do not alphabetize or rewrap YAML keys without checking whether order, indentation, or scalar style is significant.

Do not treat HTML comments or hidden directives as disposable prose.

## 5.17 Comments and revision markers

Preserve comments and revision macros. Do not remove commented-out equations, alternate passages, TODO markers, or author notes unless instructed; they may record unresolved mathematical choices.

Protected examples include `% ...`, `<!-- ... -->`, `\todo{...}`, `\comment{...}`, `\rev{...}`, and custom change-tracking commands.

When resolving a comment, remove it only after the requested resolution has been implemented and verified.

## 5.18 Encoding and typography

Preserve the project's policy for UTF-8 characters, TeX accents, quotation marks, dashes, nonbreaking spaces, thin spaces in units, and spelling conventions.

Do not normalize variants such as `C*-algebra`, `C^{*}`-algebra, and `$C^*$-algebra` without checking the project convention.

Preserve the distinction among hyphen `-`, en dash `--` in TeX, and em dash `---` in TeX where the source convention relies on it.

Do not replace mathematical minus signs with prose hyphens or vice versa.

## 5.19 Compilation and rendering safety

After an edit, check for:

- balanced mathematical delimiters;
- balanced environments;
- undefined or multiply defined labels;
- malformed citation commands;
- broken Markdown fences;
- damaged table rows;
- accidental code-indentation changes;
- unescaped special characters;
- equations separated from their introductory sentences;
- altered theorem numbering;
- broken list numbering;
- changed notebook metadata;
- invalid YAML or directive indentation.

A successful compile is necessary but not sufficient. Inspect the rendered output around every edited display, theorem, figure, table, citation, code block, and page break when a renderer is available.

## 5.20 Patch reporting

For every editorial patch, report separately:

1. prose-only changes;
2. structural changes;
3. notation or mathematical changes;
4. file-format or tooling changes;
5. unresolved questions.

A prose-edit request does not authorize silent mathematical correction. If an equation appears wrong, preserve it in the prose patch and report the suspected error with its location.

# Mandatory house rules

1. Use descriptive academic headings rather than promotional headings.
2. Match heading style to genre; reserve genuine question headings for expository or conceptual work.
3. Format notebook result headings as `Theorem <number>. <Name>`, `Proposition <number>. <Name>`, `Lemma <number>. <Name>`, `Corollary <number>. <Name>`, or `Definition <number>. <Name>`.
4. Introduce definitions through the problem that requires them.
5. Define operators with their space, domain, action, parameter dependence, and relevant analytic status.
6. State graph orientation, path composition, causal-order, and interval conventions explicitly.
7. Place physical interpretation after or alongside the formal construction, never in place of it.
8. Distinguish equality, representation, approximation, convergence, and heuristic correspondence.
9. Use lists only for genuinely list-like mathematical material.
10. Introduce every display with a grammatical sentence and interpret it afterward when interpretation is needed.
11. Treat display punctuation as part of the surrounding sentence.
12. Replace generic emphasis with an exact consequence.
13. Do not use takeaway boxes, repetitive recaps, or templated motivation-intuition-key-insight scaffolding.
14. Remove promotional, conversational, and LLM-associated filler, while preserving words used in exact technical senses.
15. Never infer or allege LLM authorship from stylistic markers alone.
16. Preserve notation, macros, labels, citations, code, mathematical blocks, tables, outputs, metadata, and theorem structure during prose editing.
17. Keep prose edits minimal and disclose substantive mathematical changes separately.
18. Verify compilation and rendering after any edit that touches technical structure.
19. State a limitation as a fact rather than as a disclaimer about what a result does not claim.

# Editorial preflight checklist

Before producing a patch, verify each edited file against the following questions:

1. Are all section and result headings descriptive, genre-appropriate, and consistently formatted?
2. Does every paragraph perform a recognizable mathematical task?
3. Are definitions and operators introduced with their ambient objects, assumptions, conventions, and domains?
4. Does each displayed equation have a grammatical introduction, correct punctuation, and an appropriate continuation?
5. Are lists confined to axioms, relations, equivalent conditions, algorithms, classifications, or other intrinsically list-like material?
6. Have promotional, conversational, generic-summary, meta-writing, and clustered LLM-watchlist phrases been removed?
7. Are claims of equivalence, completeness, universality, reconstruction, novelty, and physical emergence supported by stated hypotheses or citations?
8. Are operational interpretations explicitly connected to formal objects and convergence notions?
9. Have graph path conventions, causal-order conventions, and closure topologies been stated where needed?
10. Have notation, formulas, fenced math, tables, code, labels, references, macros, outputs, front matter, and comments been preserved?
11. Does the patch contain only the intended files and the smallest changes needed to satisfy the guide?
12. Have suspected mathematical errors been reported separately rather than silently repaired?
13. Does the patch apply cleanly to the stated baseline?
14. Does the applied result match the reviewed working copy?
15. Does the file compile or render without new warnings attributable to the edit?
16. Has the rendered output been inspected around every edited technical block?
17. Is every limitation stated positively, rather than as a disclaimer about what is not claimed?
