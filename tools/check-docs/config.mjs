import path from "node:path";
import { fileURLToPath } from "node:url";

const toolDirectory = path.dirname(fileURLToPath(import.meta.url));

export const repositoryRoot = path.resolve(toolDirectory, "../..");
export const artifactsDirectory = path.join(
  repositoryRoot,
  "data",
  "check-docs",
);

const findingsNames = [
  ...Array.from({ length: 50 }, (_, index) => `findings-${index + 3}.md`),
  "findings-53-wip.md",
];

export const findingsFiles = findingsNames.map((name) =>
  path.join(repositoryRoot, "docs", name),
);

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
