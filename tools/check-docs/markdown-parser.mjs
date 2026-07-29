import MarkdownIt from "markdown-it";
import vscodeKatexPackage from "@vscode/markdown-it-katex";
import katex from "katex";
import { markdownItOptions } from "./config.mjs";

export function createVsCodeParser() {
  const parser = new MarkdownIt(markdownItOptions);
  const vscodeKatex = vscodeKatexPackage.default ?? vscodeKatexPackage;

  parser.use(vscodeKatex, {
    katex,
    throwOnError: false,
    strict: "error",
    enableFencedBlocks: true,
  });

  return parser;
}
