import fs from "node:fs/promises";
import path from "node:path";
import GithubSlugger from "github-slugger";
import { lint as lintMarkdown } from "markdownlint/sync";
import { markdownLintConfig, repositoryRoot } from "./config.mjs";

const displayMathTokenTypes = new Set([
  "math_block",
  "math_inline_block",
  "math_inline_bare_block",
]);

function walkTokens(tokens, visit, inheritedLine = 1) {
  for (const token of tokens) {
    const line =
      token.map?.[0] === undefined ? inheritedLine : token.map[0] + 1;

    visit(token, line);

    if (token.children) {
      walkTokens(token.children, visit, line);
    }
  }
}

function tokenAttributes(token) {
  return Object.fromEntries(token.attrs ?? []);
}

function mathExpression(token, line) {
  const hasBacktickWrapper =
    token.content.startsWith("`") && token.content.endsWith("`");
  const tex = hasBacktickWrapper ? token.content.slice(1, -1) : token.content;
  return { tex, display: false, line };
}

function analyzeTokens(file, source, tokens, diagnostics) {
  const math = [];
  let ordinaryCodeBlocks = 0;

  walkTokens(tokens, (token, line) => {
    if (token.type === "fence") {
      if (token.info.trim().toLowerCase() === "math") {
        math.push({ tex: token.content.trim(), display: true, line });
      } else {
        ordinaryCodeBlocks += 1;
      }

      return;
    }

    if (token.type === "code_block") {
      ordinaryCodeBlocks += 1;
      return;
    }

    if (displayMathTokenTypes.has(token.type)) {
      math.push({ tex: token.content.trim(), display: true, line });
      return;
    }

    if (token.type === "math_inline") {
      math.push(mathExpression(token, line));
      return;
    }

    if (token.type === "text" && /(^|[^\\])\$/.test(token.content)) {
      diagnostics.add(
        file,
        "math-delimiters",
        `unbalanced or unsupported delimiter near ${JSON.stringify(token.content.slice(0, 80))}`,
        line,
      );
    }
  });

  for (const expression of math) {
    if (!expression.tex) {
      diagnostics.add(
        file,
        "math-delimiters",
        "empty mathematical expression",
        expression.line,
      );
    }
  }

  return { file, source, tokens, math, ordinaryCodeBlocks };
}

export function parseDocuments(parser, sources, diagnostics) {
  const documents = new Map();

  for (const [file, source] of sources) {
    const tokens = parser.parse(source, {});
    const document = analyzeTokens(file, source, tokens, diagnostics);
    documents.set(file, document);
  }

  return documents;
}

export function checkMarkdownLint(sources, diagnostics) {
  const strings = Object.fromEntries(
    [...sources].map(([file, source]) => [
      path.relative(repositoryRoot, file),
      source,
    ]),
  );

  const results = lintMarkdown({ strings, config: markdownLintConfig });

  for (const [relativeFile, errors] of Object.entries(results)) {
    for (const error of errors) {
      const column = error.errorRange?.[0] ?? 1;
      const message = `${error.ruleDescription} (column ${column})`;
      diagnostics.add(
        path.join(repositoryRoot, relativeFile),
        `markdownlint/${error.ruleNames[0]}`,
        message,
        error.lineNumber,
      );
    }
  }
}

export function checkCodeFences(sources, diagnostics) {
  for (const [file, source] of sources) {
    let openFence = null;

    for (const [index, line] of source.split("\n").entries()) {
      const match = line.match(/^ {0,3}(`{3,}|~{3,})(.*)$/);
      if (!match) {
        continue;
      }

      const marker = match[1][0];
      const closesFence =
        openFence &&
        marker === openFence.marker &&
        match[1].length >= openFence.length &&
        match[2].trim() === "";

      if (closesFence) {
        openFence = null;
      } else if (!openFence) {
        openFence = {
          marker,
          length: match[1].length,
          line: index + 1,
        };
      }
    }

    if (openFence) {
      diagnostics.add(
        file,
        "code-fences",
        `close the ${openFence.marker.repeat(openFence.length)} fence opened here`,
        openFence.line,
      );
    }
  }
}

export function checkTableShapes(documents, diagnostics) {
  for (const document of documents.values()) {
    const { tokens } = document;

    for (let index = 0; index < tokens.length; index += 1) {
      if (tokens[index].type !== "table_open") {
        continue;
      }

      const tableLine = (tokens[index].map?.[0] ?? 0) + 1;
      const rowWidths = [];
      let rowWidth = 0;

      for (index += 1; index < tokens.length; index += 1) {
        const token = tokens[index];
        if (token.type === "table_close") {
          break;
        }

        if (token.type === "tr_open") {
          rowWidth = 0;
        } else if (token.type === "th_open" || token.type === "td_open") {
          rowWidth += 1;
        } else if (token.type === "tr_close") {
          rowWidths.push(rowWidth);
        }
      }

      const expectedWidth = rowWidths[0];
      const malformedRow = rowWidths.findIndex(
        (width) => width !== expectedWidth,
      );

      if (malformedRow !== -1) {
        diagnostics.add(
          document.file,
          "table-shape",
          `row ${malformedRow + 1} has ${rowWidths[malformedRow]} columns; expected ${expectedWidth}`,
          tableLine,
        );
      }
    }
  }
}

function headingAnchors(tokens) {
  const slugger = new GithubSlugger();
  const anchors = new Set();

  for (let index = 0; index < tokens.length; index += 1) {
    if (tokens[index].type !== "heading_open") {
      continue;
    }

    const headingText = tokens[index + 1]?.content ?? "";
    anchors.add(slugger.slug(headingText));
  }

  return anchors;
}

function linkDestinations(tokens) {
  const destinations = [];

  walkTokens(tokens, (token) => {
    const attributes = tokenAttributes(token);

    if (token.type === "link_open" && attributes.href) {
      destinations.push(attributes.href);
    }

    if (token.type === "image" && attributes.src) {
      destinations.push(attributes.src);
    }
  });

  return destinations;
}

function localLinkTarget(file, destination) {
  const [rawPath, rawFragment = ""] = destination.split("#", 2);
  const cleanPath = decodeURIComponent(rawPath.split("?", 1)[0]);
  const baseDirectory = cleanPath.startsWith("/")
    ? repositoryRoot
    : path.dirname(file);
  const target = cleanPath
    ? path.resolve(baseDirectory, cleanPath.replace(/^\//, ""))
    : file;
  return { target, rawFragment };
}

async function targetExists(target) {
  try {
    const stat = await fs.stat(target);
    return stat.isFile() || stat.isDirectory();
  } catch {
    return false;
  }
}

export async function checkLinks(parser, documents, diagnostics) {
  const headingCache = new Map(
    [...documents].map(([file, document]) => [
      file,
      headingAnchors(document.tokens),
    ]),
  );

  for (const document of documents.values()) {
    for (const destination of linkDestinations(document.tokens)) {
      if (/^(?:[a-z][a-z+.-]*:|\/\/)/i.test(destination)) {
        continue;
      }

      const { target, rawFragment } = localLinkTarget(
        document.file,
        destination,
      );

      const targetIsInsideRepository =
        target === repositoryRoot ||
        target.startsWith(`${repositoryRoot}${path.sep}`);

      if (!targetIsInsideRepository) {
        diagnostics.add(
          document.file,
          "internal-link",
          `link escapes the repository: ${destination}`,
        );
        continue;
      }

      if (!(await targetExists(target))) {
        diagnostics.add(
          document.file,
          "internal-link",
          `target does not exist: ${destination}`,
        );
        continue;
      }

      if (!rawFragment || !target.toLowerCase().endsWith(".md")) {
        continue;
      }

      if (!headingCache.has(target)) {
        const targetSource = await fs.readFile(target, "utf8");
        const targetTokens = parser.parse(targetSource, {});
        headingCache.set(target, headingAnchors(targetTokens));
      }

      const fragment = decodeURIComponent(rawFragment).toLowerCase();
      if (!headingCache.get(target).has(fragment)) {
        diagnostics.add(
          document.file,
          "heading-anchor",
          `#${rawFragment} does not exist in ${path.relative(repositoryRoot, target)}`,
        );
      }
    }
  }
}
