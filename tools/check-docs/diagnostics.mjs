import path from "node:path";

export class Diagnostics {
  #entries = [];
  #repositoryRoot;

  constructor(repositoryRoot) {
    this.#repositoryRoot = repositoryRoot;
  }

  add(file, rule, message, line = null) {
    const relativeFile = path.relative(this.#repositoryRoot, file);
    this.#entries.push({ file: relativeFile, line, rule, message });
  }

  addGlobal(rule, message) {
    this.#entries.push({ file: "validation", line: null, rule, message });
  }

  get count() {
    return this.#entries.length;
  }

  print() {
    const orderedEntries = [...this.#entries].sort((left, right) => {
      return (
        left.file.localeCompare(right.file) ||
        (left.line ?? 0) - (right.line ?? 0) ||
        left.rule.localeCompare(right.rule) ||
        left.message.localeCompare(right.message)
      );
    });

    for (const entry of orderedEntries) {
      const location =
        entry.line === null ? entry.file : `${entry.file}:${entry.line}`;
      console.error(`${location}: ${entry.rule}: ${entry.message}`);
    }
  }
}
