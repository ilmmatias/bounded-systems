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

class WlProfile {
  public:
    OneRoundKey oneRoundKey(const Graph& graph) const;

    StableWlResult stabilize(std::span<const Graph> graphs) const;

  private:
    int initialColor(const Graph& graph, int source, int target) const;
};

int generateWlScan();
int generateWlReduction(int vertexCount,
                        const std::filesystem::path& outputDirectory);
