#!/usr/bin/env python3

from __future__ import annotations

import argparse
import json
import shlex
import subprocess
from pathlib import Path
from typing import TypedDict


class CompileCommand(TypedDict):
    directory: str
    file: str
    output: str
    arguments: list[str]


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Write compile_commands.json from a dry-run build."
    )
    parser.add_argument("--output", required=True, type=Path)
    parser.add_argument("command", nargs=argparse.REMAINDER)
    return parser.parse_args()


def logical_lines(output: str) -> list[str]:
    lines: list[str] = []
    pending = ""

    for line in output.splitlines():
        stripped = line.rstrip()
        if stripped.endswith("\\"):
            pending += stripped[:-1] + " "
            continue

        lines.append(pending + stripped.lstrip())
        pending = ""

    if pending:
        lines.append(pending.rstrip())

    return lines


def extract_commands(output: str, directory: Path) -> list[CompileCommand]:
    commands: dict[str, CompileCommand] = {}

    for line in logical_lines(output):
        arguments = shlex.split(line)
        if "-c" not in arguments or "-o" not in arguments:
            continue

        source_index = arguments.index("-c") + 1
        output_index = arguments.index("-o") + 1
        if source_index == len(arguments) or output_index == len(arguments):
            continue

        source = arguments[source_index]
        object_path = arguments[output_index]
        command: CompileCommand = {
            "directory": str(directory),
            "file": source,
            "output": object_path,
            "arguments": arguments,
        }

        previous = commands.get(source)
        if previous is not None and previous != command:
            raise ValueError(f"multiple compile commands for {source}")

        commands[source] = command

    return [commands[source] for source in sorted(commands)]


def main() -> int:
    args = parse_args()
    command = args.command
    if command and command[0] == "--":
        command = command[1:]

    if not command:
        raise SystemExit("missing dry-run build command")

    directory = Path.cwd().resolve()
    completed = subprocess.run(
        command,
        cwd=directory,
        check=True,
        capture_output=True,
        text=True,
    )
    commands = extract_commands(completed.stdout, directory)
    if not commands:
        raise SystemExit("dry-run build produced no compilation commands")

    args.output.write_text(json.dumps(commands, indent=2) + "\n")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
