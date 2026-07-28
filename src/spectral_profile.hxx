#pragma once

#include "graph.hxx"

#include <array>
#include <cstddef>
#include <filesystem>
#include <string>

constexpr size_t kSpectralLevelCount = 9;

struct SpectralKeys {
    std::array<std::string, kSpectralLevelCount> cumulative;
};

class SpectralProfile {
  public:
    SpectralKeys keys(const Graph& graph) const;
};

int generateSpectralArtifacts(int vertexCount,
                              const std::filesystem::path& outputDirectory);
