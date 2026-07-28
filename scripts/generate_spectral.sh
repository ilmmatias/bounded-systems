#!/usr/bin/env bash

set -euo pipefail

if [[ $# -lt 1 || $# -gt 2 ]]; then
    echo "usage: $0 N [OUTPUT_DIRECTORY]" >&2
    exit 1
fi

root=$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)
vertex_count=$1
output=${2:-"$root/data/findings-2/n${vertex_count}"}
geng=${GENG:-geng}
directg=${DIRECTG:-directg}

mkdir -p "$output"

"$geng" -q "$vertex_count" \
    | "$directg" -aq \
    | "$root/bin/artifact" spectral \
        --vertices "$vertex_count" \
        --output "$output"
