#pragma once

#include "gap_benchmark.hxx"

#include <cstddef>
#include <span>

long peakRssKib();
void writeGapOutput(const GapOptions& opt, std::span<const GapSample> samples,
                    size_t threads, double wallSeconds);
