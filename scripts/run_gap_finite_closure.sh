#!/usr/bin/env bash

set -Eeuo pipefail

root=$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)
program="$root/bin/gap-finite-closure"
output=${OUTPUT:-"$root/data/findings-105"}
threads=${THREADS:-$(nproc)}
seed=${SEED:-20260817}

run_size() {
    local family=$1
    local vertices=$2
    local horizons=$3
    local samples=$4
    local paths=$5
    local run_seed=${6:-$seed}
    local worker_limit=${7:-$threads}
    local workers=$threads

    if ((workers > samples)); then
        workers=$samples
    fi
    if ((workers > worker_limit)); then
        workers=$worker_limit
    fi

    "$program" \
        --vertices "$vertices" \
        --horizons "$horizons" \
        --samples "$samples" \
        --paths "$paths" \
        --seed "$run_seed" \
        --threads "$workers" \
        --output "$output/$family/n$vertices" \
        --base-bins 8,16,16,32 \
        --aux-leaves 2,2,4,2 \
        --target-bins 32,64,64,128 \
        --reference-bins 256 \
        --pseudocount 0.5 \
        --overwrite
}

mkdir -p "$output"

# The fixed family uses the same two horizons at every N. The joint family
# keeps p/sqrt(N) in [0.35,0.375] and includes a half-horizon control.
large_workers=${WORKERS_32768:-$threads}
run_size fixed 512 8,16 "${SAMPLES_512:-32}" "${PATHS_512:-3000}"
run_size fixed 1024 8,16 "${SAMPLES_1024:-32}" "${PATHS_1024:-3000}"
run_size fixed 2048 8,16 "${SAMPLES_2048:-32}" "${PATHS_2048:-3000}"
run_size fixed 4096 8,16 "${SAMPLES_4096:-32}" "${PATHS_4096:-2500}"
run_size fixed 8192 8,16 "${SAMPLES_8192:-32}" "${PATHS_8192:-2000}"
run_size fixed 16384 8,16 "${SAMPLES_16384:-32}" "${PATHS_16384:-2000}"

run_size fixed 32768 8,16 "${SAMPLES_32768:-32}" "${PATHS_32768:-2000}" \
    "$seed" "$large_workers"
run_size joint 512 4,8 "${SAMPLES_512:-32}" "${PATHS_512:-3000}"
run_size joint 1024 6,12 "${SAMPLES_1024:-32}" "${PATHS_1024:-3000}"
run_size joint 2048 8,16 "${SAMPLES_2048:-32}" "${PATHS_2048:-3000}"
run_size joint 4096 12,24 "${SAMPLES_4096:-32}" "${PATHS_4096:-2500}"
run_size joint 8192 16,32 "${SAMPLES_8192:-32}" "${PATHS_8192:-2000}"
run_size joint 16384 23,46 "${SAMPLES_16384:-32}" "${PATHS_16384:-2000}"

run_size joint 32768 32,64 "${SAMPLES_32768:-32}" "${PATHS_32768:-2000}" \
    "$seed" "$large_workers"
if [[ ${RUN_FOCUSED:-1} != 0 ]]; then
    focused_samples=${FOCUSED_SAMPLES:-32}
    focused_paths=${FOCUSED_PATHS:-10000}
    focused_seed=${FOCUSED_SEED:-20260819}
    run_size focused 4096 16 "$focused_samples" "$focused_paths" "$focused_seed"
    run_size focused 8192 16 "$focused_samples" "$focused_paths" "$focused_seed"
    run_size focused 16384 16 "$focused_samples" "$focused_paths" "$focused_seed"
    run_size focused 32768 16 "$focused_samples" "$focused_paths" \
        "$focused_seed" "$large_workers"
fi

if [[ ${RUN_PERF:-1} != 0 ]]; then
    perf_samples=${PERF_SAMPLES:-32}
    perf_paths=${PERF_PATHS:-1000}
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
            --paths "$perf_paths" \
            --seed 20260818 \
            --threads "$workers" \
            --output "$output/perf-$label" \
            --base-bins 8,16,16,32 \
            --aux-leaves 2,2,4,2 \
            --target-bins 32,64,64,128 \
            --reference-bins 256 \
            --pseudocount 0.5 \
            --overwrite
    done
fi

python3 "$root/scripts/analyze_gap_finite_closure.py" \
    "$output/fixed/n512" \
    "$output/fixed/n1024" \
    "$output/fixed/n2048" \
    "$output/fixed/n4096" \
    "$output/fixed/n8192" \
    "$output/fixed/n16384" \
    "$output/fixed/n32768" \
    --output "$output/fixed/summary.json"

python3 "$root/scripts/analyze_gap_finite_closure.py" \
    "$output/joint/n512" \
    "$output/joint/n1024" \
    "$output/joint/n2048" \
    "$output/joint/n4096" \
    "$output/joint/n8192" \
    "$output/joint/n16384" \
    "$output/joint/n32768" \
    --output "$output/joint/summary.json"

if [[ ${RUN_FOCUSED:-1} != 0 ]]; then
    python3 "$root/scripts/analyze_gap_finite_closure.py" \
        "$output/focused/n4096" \
        "$output/focused/n8192" \
        "$output/focused/n16384" \
        "$output/focused/n32768" \
        --output "$output/focused/summary.json"
fi
