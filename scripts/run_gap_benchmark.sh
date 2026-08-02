#!/usr/bin/env bash

set -Eeuo pipefail

root=$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)
program="$root/bin/gap-benchmark"
output="$root/data/findings-103"
threads=${THREADS:-$(nproc)}
seed=${SEED:-20260801}

run_size() {
    local vertices=$1
    local horizons=$2
    local samples=$3

    "$program" \
        --vertices "$vertices" \
        --horizons "$horizons" \
        --samples "$samples" \
        --seed "$seed" \
        --threads "$threads" \
        --output "$output/n$vertices" \
        --closure-bins 8,16,32 \
        --validation-length 4 \
        --legendre-modes 4 \
        --bulk-fraction 0.2 \
        --lindeberg-thresholds 0.01,0.025,0.05,0.1,0.2 \
        --overwrite
}

calibration_samples=${CALIBRATION_SAMPLES:-128}
calibration_threads=$threads
if ((calibration_threads > 16)); then
    calibration_threads=16
fi

run_calibration() {
    local vertices=$1

    "$program" \
        --vertices "$vertices" \
        --horizons 1 \
        --samples "$calibration_samples" \
        --seed "$seed" \
        --threads "$calibration_threads" \
        --output "$output/calibration-n$vertices" \
        --closure-bins 8 \
        --validation-length 4 \
        --legendre-modes 4 \
        --bulk-fraction 0.2 \
        --lindeberg-thresholds 0.01,0.025,0.05,0.1,0.2 \
        --overwrite
}

mkdir -p "$output"
run_size 512 4,8,12,16 "${SAMPLES_512:-32}"
run_size 1024 4,8,16,24 "${SAMPLES_1024:-16}"
run_size 2048 4,8,16,24,32 "${SAMPLES_2048:-8}"
run_size 4096 4,8,16,32,48 "${SAMPLES_4096:-8}"
run_size 8192 4,8,16,32 "${SAMPLES_8192:-4}"

run_calibration 512
run_calibration 1024
run_calibration 2048
run_calibration 4096
run_calibration 8192

perf_samples=${PERF_SAMPLES:-8}
perf_threads=$threads
if ((perf_threads > perf_samples)); then
    perf_threads=$perf_samples
fi

"$program" \
    --vertices 1024 \
    --horizons 16 \
    --samples "$perf_samples" \
    --seed 20260802 \
    --threads 1 \
    --output "$output/perf-serial" \
    --closure-bins 8,16,32 \
    --validation-length 4 \
    --legendre-modes 4 \
    --overwrite

"$program" \
    --vertices 1024 \
    --horizons 16 \
    --samples "$perf_samples" \
    --seed 20260802 \
    --threads "$perf_threads" \
    --output "$output/perf-parallel" \
    --closure-bins 8,16,32 \
    --validation-length 4 \
    --legendre-modes 4 \
    --overwrite

python3 "$root/scripts/analyze_gap_benchmark.py" \
    --inputs \
        "$output/n512" \
        "$output/n1024" \
        "$output/n2048" \
        "$output/n4096" \
        "$output/n8192" \
        "$output/calibration-n512" \
        "$output/calibration-n1024" \
        "$output/calibration-n2048" \
        "$output/calibration-n4096" \
        "$output/calibration-n8192" \
        "$output/perf-serial" \
        "$output/perf-parallel" \
    --output "$output/summary.json" \
    --markdown "$output/summary.md"
