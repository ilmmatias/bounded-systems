#!/usr/bin/env bash

set -Eeuo pipefail

root=$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)
threads=${THREADS:-$(nproc)}
paths=${PATHS:-40000}
seed=${SEED:-273488412}
output=${OUTPUT:-$root/data/findings-104/control.json}

cmd=(
    "$root/bin/gap-clock-control"
    --horizons 16,32,64,128
    --scales 1,2,4
    --paths "$paths"
    --seed "$seed"
    --threads "$threads"
    --output "$output"
    --overwrite
)

"${cmd[@]}"
