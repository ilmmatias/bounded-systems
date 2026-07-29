import fs from "node:fs/promises";
import path from "node:path";
import process from "node:process";
import { load as loadHtml } from "cheerio";
import {
  artifactsDirectory,
  githubRepository,
  repositoryRoot,
} from "./config.mjs";

const githubMarkdownEndpoint = "https://api.github.com/markdown";
const maximumChunkBytes = 300_000;

export function renderVsCodeMarkdown(parser, markdown) {
  return parser.render(markdown);
}

export async function renderGithubMarkdown(markdown) {
  const headers = {
    Accept: "application/vnd.github+json",
    "Content-Type": "application/json",
    "X-GitHub-Api-Version": "2022-11-28",
    "User-Agent": "bounded-systems-check-docs",
  };

  if (process.env.GITHUB_TOKEN) {
    headers.Authorization = `Bearer ${process.env.GITHUB_TOKEN}`;
  }

  const response = await fetch(githubMarkdownEndpoint, {
    method: "POST",
    headers,
    body: JSON.stringify({
      text: markdown,
      mode: "gfm",
      context: githubRepository,
    }),
  });

  if (!response.ok) {
    const responseBody = await response.text();
    throw new Error(
      `GitHub Markdown API returned ${response.status}: ${responseBody}`,
    );
  }

  return response.text();
}

function sourceChunks(sources) {
  const chunks = [];
  let currentChunk = [];
  let currentBytes = 0;

  for (const entry of sources) {
    const entryBytes = Buffer.byteLength(entry[1], "utf8");

    if (currentChunk.length && currentBytes + entryBytes > maximumChunkBytes) {
      chunks.push(currentChunk);
      currentChunk = [];
      currentBytes = 0;
    }

    currentChunk.push(entry);
    currentBytes += entryBytes;
  }

  if (currentChunk.length) {
    chunks.push(currentChunk);
  }

  return chunks;
}

function chunkMarkdown(chunk) {
  return chunk
    .map(([file, source]) => {
      const relativeFile = path.relative(repositoryRoot, file);
      return `<!-- ${relativeFile} -->\n\n${source}`;
    })
    .join("\n\n---\n\n");
}

function renderedSemantics(html) {
  const $ = loadHtml(html);
  const counts = {};

  for (let level = 1; level <= 6; level += 1) {
    counts[`h${level}`] = $(`h${level}`).length;
  }

  counts.links = $("a[href]").length;
  counts.tables = $("table").length;
  counts.codeBlocks = $("pre").filter((_, element) => {
    const classesAndLanguage = `${$(element).attr("class") ?? ""} ${$(element).attr("lang") ?? ""}`;
    return !/\bmath\b/i.test(classesAndLanguage);
  }).length;

  const isVsCodeRender = $(".katex").length > 0;
  const mathNodes = isVsCodeRender
    ? $(".katex")
    : $("math-renderer, .js-inline-math, .js-display-math");

  // Both stacks support fenced and block math in the same contexts. GitHub's
  // REST renderer intentionally omits some inline contexts that VS Code accepts.
  const sharedMathNodes = isVsCodeRender
    ? $(".katex-block .katex")
    : $("math-renderer.js-display-math");

  counts.math = mathNodes.length;
  counts.sharedMath = sharedMathNodes.length;

  return counts;
}

function expectedCounts(chunk, documents) {
  return chunk.reduce(
    (counts, [file]) => {
      const document = documents.get(file);

      counts.math += document.math.length;
      counts.codeBlocks += document.ordinaryCodeBlocks;

      return counts;
    },
    { math: 0, codeBlocks: 0 },
  );
}

export function compareRenderedSemantics(
  githubHtml,
  vscodeHtml,
  expected,
  diagnostics,
  chunkLabel,
) {
  const github = renderedSemantics(githubHtml);
  const vscode = renderedSemantics(vscodeHtml);
  const sharedStructures = [
    "h1",
    "h2",
    "h3",
    "h4",
    "h5",
    "h6",
    "links",
    "tables",
    "codeBlocks",
  ];

  for (const structure of sharedStructures) {
    if (github[structure] !== vscode[structure]) {
      diagnostics.addGlobal(
        "render-semantics",
        `${chunkLabel}: ${structure} count differs (GitHub ${github[structure]}, VS Code ${vscode[structure]})`,
      );
    }
  }

  if (vscode.math !== expected.math) {
    diagnostics.addGlobal(
      "vscode-math",
      `${chunkLabel}: expected ${expected.math} math nodes, rendered ${vscode.math}`,
    );
  }

  if (github.sharedMath !== vscode.sharedMath) {
    diagnostics.addGlobal(
      "render-semantics",
      `${chunkLabel}: shared math-node count differs (GitHub ${github.sharedMath}, VS Code ${vscode.sharedMath})`,
    );
  }

  if (github.codeBlocks !== expected.codeBlocks) {
    diagnostics.addGlobal(
      "github-code-blocks",
      `${chunkLabel}: expected ${expected.codeBlocks} ordinary code blocks, rendered ${github.codeBlocks}`,
    );
  }
}

function completeHtml(title, body) {
  const katexStylesheet =
    "https://cdn.jsdelivr.net/npm/katex@0.16.22/dist/katex.min.css";

  return [
    "<!doctype html>",
    '<html lang="en">',
    "<head>",
    '  <meta charset="utf-8">',
    `  <title>${title}</title>`,
    `  <link rel="stylesheet" href="${katexStylesheet}">`,
    "</head>",
    '<body class="markdown-body">',
    body,
    "</body>",
    "</html>",
    "",
  ].join("\n");
}

export async function writeRenderArtifacts(githubBody, vscodeBody) {
  await fs.mkdir(artifactsDirectory, { recursive: true });

  const githubArtifact = completeHtml("GitHub GFM render", githubBody);
  const vscodeArtifact = completeHtml("VS Code Markdown preview", vscodeBody);

  await Promise.all([
    fs.writeFile(path.join(artifactsDirectory, "github.html"), githubArtifact),
    fs.writeFile(path.join(artifactsDirectory, "vscode.html"), vscodeArtifact),
  ]);
}

export async function renderAndValidate(
  parser,
  sources,
  documents,
  diagnostics,
) {
  const githubParts = [];
  const vscodeParts = [];
  const chunks = sourceChunks([...sources]);

  for (const [index, chunk] of chunks.entries()) {
    const markdown = chunkMarkdown(chunk);
    const vscodeHtml = renderVsCodeMarkdown(parser, markdown);
    const chunkLabel = `chunk ${index + 1}/${chunks.length}`;

    if (loadHtml(vscodeHtml)(".katex-error").length) {
      diagnostics.addGlobal(
        "vscode-math",
        `${chunkLabel}: KaTeX emitted an error node`,
      );
    }

    try {
      const githubHtml = await renderGithubMarkdown(markdown);
      const expected = expectedCounts(chunk, documents);

      compareRenderedSemantics(
        githubHtml,
        vscodeHtml,
        expected,
        diagnostics,
        chunkLabel,
      );

      githubParts.push(githubHtml);
    } catch (error) {
      diagnostics.addGlobal("github-render", `${chunkLabel}: ${error.message}`);
    }

    vscodeParts.push(vscodeHtml);
  }

  await writeRenderArtifacts(githubParts.join("\n"), vscodeParts.join("\n"));
}
