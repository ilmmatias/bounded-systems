#pragma once

#include "graph.hxx"

#include <cstdint>
#include <filesystem>
#include <span>
#include <vector>

using OneRoundKey = std::vector<uint8_t>;

struct StableWlResult {
    std::vector<std::vector<int>> graphKeys;
    int rounds = 0;
    int separationRound = 0;
};

OneRoundKey oneRoundWlKey(const Graph& graph);

StableWlResult stabilizeWl(std::span<const Graph> graphs);

int generateWlScan();
int generateWlReduction(int vertexCount,
                        const std::filesystem::path& outputDirectory);
