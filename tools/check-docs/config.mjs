import fs from "node:fs";
import path from "node:path";
import { fileURLToPath } from "node:url";

const toolDirectory = path.dirname(fileURLToPath(import.meta.url));

export const repositoryRoot = path.resolve(toolDirectory, "../..");
export const artifactsDirectory = path.join(
  repositoryRoot,
  "data",
  "check-docs",
);

const docsDirectory = path.join(repositoryRoot, "docs");

export const findingsFiles = fs
  .readdirSync(docsDirectory)
  .filter((file) => /^findings-.*\.md$/.test(file))
  .map((file) => path.join(docsDirectory, file));

export const githubRepository =
  process.env.GITHUB_REPOSITORY ?? "ilmmatias/bounded-systems";

export const markdownItOptions = {
  html: true,
  breaks: false,
  linkify: true,
  typographer: false,
};

export const markdownLintConfig = {
  default: true,
  MD013: false,
  MD024: { siblings_only: true },
  MD025: false,
  MD026: false,
  MD033: false,
  MD034: false,
  MD036: false,
  MD040: false,
  MD041: true,
  MD051: false,
  MD059: false,
  MD060: false,
};
