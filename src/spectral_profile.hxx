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

SpectralKeys spectralKeys(const Graph& graph);

int generateSpectralArtifacts(int vertexCount,
                              const std::filesystem::path& outputDirectory);
