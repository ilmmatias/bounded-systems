#!/usr/bin/env bash
set -euo pipefail

if [[ $# -lt 1 || $# -gt 2 ]]; then
    echo "usage: $0 N [OUTPUT_DIRECTORY]" >&2
    exit 1
fi

root=$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)
vertex_count=$1
output=${2:-"$root/data/findings-43/n${vertex_count}"}
threads=${THREADS:-$(nproc)}
shards=${SHARDS:-$threads}
sort_memory=${SORT_MEM:-1G}
geng=${GENG:-geng}
directg=${DIRECTG:-directg}

mkdir -p "$output/shards" "$output/tmp"
export TMPDIR="$output/tmp"

undirected="$output/undirected.g6"
if [[ ! -s "$undirected" ]]; then
    echo "generating undirected graphs on $vertex_count vertices"
    "$geng" -q "$vertex_count" > "$undirected.tmp"
    mv "$undirected.tmp" "$undirected"
fi

run_shard() {
    local shard=$1
    local name
    name=$(printf '%04d' "$shard")
    local records="$output/shards/$name.tsv"
    local log="$output/shards/$name.log"

    if [[ -s "$records" ]]; then
        return
    fi

    "$directg" -aq "-s${shard}/${shards}" "$undirected" \
        | "$root/bin/artifact" wl-scan 2> "$log.tmp" \
        | LC_ALL=C sort --parallel=1 \
            -S "$sort_memory" -k1,1 \
        > "$records.tmp"

    mv "$records.tmp" "$records"
    mv "$log.tmp" "$log"
}

active=0
for ((shard = 0; shard < shards; ++shard)); do
    run_shard "$shard" &
    active=$((active + 1))
    if ((active >= threads)); then
        wait -n
        active=$((active - 1))
    fi
done

wait

echo "merging exact one-round profile buckets"
LC_ALL=C sort -m -k1,1 "$output"/shards/*.tsv \
    | "$root/bin/artifact" wl-reduce \
        --vertices "$vertex_count" \
        --output "$output"
