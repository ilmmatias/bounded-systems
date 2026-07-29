import fs from "node:fs/promises";
import path from "node:path";
import {
  artifactsDirectory,
  findingsFiles,
  repositoryRoot,
} from "./config.mjs";
import { Diagnostics } from "./diagnostics.mjs";
import {
  checkCodeFences,
  checkLinks,
  checkMarkdownLint,
  checkTableShapes,
  parseDocuments,
} from "./markdown-checks.mjs";
import { createVsCodeParser } from "./markdown-parser.mjs";
import {
  checkKatexTypesetting,
  checkMathJaxTypesetting,
} from "./math-validation.mjs";
import { renderAndValidate } from "./rendering.mjs";

async function loadSources() {
  const entries = await Promise.all(
    findingsFiles.map(async (file) => [file, await fs.readFile(file, "utf8")]),
  );

  return new Map(entries);
}

async function validateDocuments(diagnostics) {
  const sources = await loadSources();
  const parser = createVsCodeParser();

  checkMarkdownLint(sources, diagnostics);
  checkCodeFences(sources, diagnostics);

  const documents = parseDocuments(parser, sources, diagnostics);

  checkTableShapes(documents, diagnostics);
  await checkLinks(parser, documents, diagnostics);

  checkKatexTypesetting(documents, diagnostics);
  await checkMathJaxTypesetting(documents, diagnostics);

  await renderAndValidate(parser, sources, documents, diagnostics);
}

async function main() {
  const diagnostics = new Diagnostics(repositoryRoot);

  try {
    await validateDocuments(diagnostics);
  } catch (error) {
    diagnostics.addGlobal("validator", error.message);
  }

  if (diagnostics.count) {
    diagnostics.print();
    console.error(
      `\nDocumentation validation failed with ${diagnostics.count} issue(s).`,
    );
    process.exitCode = 1;
    return;
  }

  const relativeArtifacts = path.relative(repositoryRoot, artifactsDirectory);
  console.log(
    `Validated ${findingsFiles.length} Markdown files; artifacts saved in ${relativeArtifacts}/.`,
  );
}

await main();
