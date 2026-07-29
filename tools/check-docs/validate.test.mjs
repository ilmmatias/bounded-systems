import assert from "node:assert/strict";
import path from "node:path";
import test from "node:test";
import { repositoryRoot } from "./config.mjs";
import { Diagnostics } from "./diagnostics.mjs";
import {
  checkCodeFences,
  checkTableShapes,
  parseDocuments,
} from "./markdown-checks.mjs";
import { createVsCodeParser } from "./markdown-parser.mjs";

const fixtureFile = path.join(repositoryRoot, "docs", "validation-fixture.md");

test("reports an unclosed code fence", () => {
  const diagnostics = new Diagnostics(repositoryRoot);
  const sources = new Map([[fixtureFile, "# Fixture\n\n```text\nunclosed\n"]]);
  checkCodeFences(sources, diagnostics);
  assert.equal(diagnostics.count, 1);
});

test("reports an unmatched math delimiter", () => {
  const diagnostics = new Diagnostics(repositoryRoot);
  const sources = new Map([
    [fixtureFile, "# Fixture\n\nInvalid $x expression.\n"],
  ]);

  parseDocuments(createVsCodeParser(), sources, diagnostics);
  assert.equal(diagnostics.count, 1);
});

test("reports inconsistent table widths", () => {
  const diagnostics = new Diagnostics(repositoryRoot);
  const documents = new Map([
    [
      fixtureFile,
      {
        file: fixtureFile,
        tokens: [
          { type: "table_open", map: [2, 5] },
          { type: "tr_open" },
          { type: "th_open" },
          { type: "th_open" },
          { type: "tr_close" },
          { type: "tr_open" },
          { type: "td_open" },
          { type: "tr_close" },
          { type: "table_close" },
        ],
      },
    ],
  ]);

  checkTableShapes(documents, diagnostics);
  assert.equal(diagnostics.count, 1);
});

test("accepts balanced fences and math", () => {
  const diagnostics = new Diagnostics(repositoryRoot);
  const source = "# Fixture\n\n```math\nx^2\n```\n\nInline $y$.\n";
  const sources = new Map([[fixtureFile, source]]);
  checkCodeFences(sources, diagnostics);
  parseDocuments(createVsCodeParser(), sources, diagnostics);
  assert.equal(diagnostics.count, 0);
});
