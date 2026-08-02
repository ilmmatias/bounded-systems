#!/usr/bin/env bash

set -Eeuo pipefail

root=$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)
program="$root/bin/gap-benchmark"
output=${OUTPUT:-"$root/data/findings-103/scaling"}
threads=${THREADS:-$(nproc)}
seed=${SEED:-20260803}
horizons=${HORIZONS:-4,8,16,32}

run_size() {
    local vertices=$1
    local samples=$2
    local workers=$threads

    if ((workers > samples)); then
        workers=$samples
    fi

    "$program" \
        --vertices "$vertices" \
        --horizons "$horizons" \
        --samples "$samples" \
        --seed "$seed" \
        --threads "$workers" \
        --output "$output/n$vertices" \
        --closure-bins 16,32 \
        --predictive-classes 8,16,32,64 \
        --target-bins 16,32,64 \
        --reference-bins 256 \
        --lindeberg-thresholds 0.05,0.1,0.2,0.5,1 \
        --validation-length 4 \
        --legendre-modes 4 \
        --bulk-fraction 0.2 \
        --overwrite
}

mkdir -p "$output"

# Every graph size uses the same horizons and master seed. Sample counts are
# kept substantial at the large coefficient runs rather than spent on a single
# extreme graph.
run_size 512 "${SAMPLES_512:-32}"
run_size 1024 "${SAMPLES_1024:-32}"
run_size 2048 "${SAMPLES_2048:-24}"
run_size 4096 "${SAMPLES_4096:-16}"
run_size 8192 "${SAMPLES_8192:-8}"

if [[ ${RUN_PERF:-1} != 0 ]]; then
    perf_samples=${PERF_SAMPLES:-8}
    perf_threads=$threads
    if ((perf_threads > perf_samples)); then
        perf_threads=$perf_samples
    fi

    for workers in 1 "$perf_threads"; do
        label=parallel
        if ((workers == 1)); then
            label=serial
        fi

        "$program" \
            --vertices 1024 \
            --horizons 16 \
            --samples "$perf_samples" \
            --seed 20260804 \
            --threads "$workers" \
            --output "$output/perf-$label" \
            --closure-bins 16,32 \
            --predictive-classes 8,16,32,64 \
            --target-bins 16,32,64 \
            --reference-bins 256 \
            --lindeberg-thresholds 0.05,0.1,0.2,0.5,1 \
            --validation-length 4 \
            --legendre-modes 4 \
            --bulk-fraction 0.2 \
            --overwrite
    done
fi

python3 "$root/scripts/analyze_gap_scaling.py" \
    "$output/n512" \
    "$output/n1024" \
    "$output/n2048" \
    "$output/n4096" \
    "$output/n8192" \
    --json "$output/summary.json" \
    --markdown "$output/summary.md"
