#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <span>
#include <utility>
#include <vector>

constexpr size_t kGapCoordinateCount = 6;
using GapCoordinate = std::array<double, kGapCoordinateCount>;
using GapSignature = std::array<uint64_t, kGapCoordinateCount>;

class ReferenceDag {
  public:
    static ReferenceDag generate(size_t vertexCount, uint64_t sampleSeed);
    static ReferenceDag
    fromTopologicalEdges(size_t vertexCount,
                         std::span<const std::pair<uint32_t, uint32_t>> edges);

    size_t vertexCount() const;
    size_t edgeCount() const;
    std::span<const size_t> outgoingOffsets() const;
    std::span<const uint32_t> outgoingTargets() const;

    bool hasLatentMarks() const;
    std::span<const double> latentMarks() const;
    std::span<const uint32_t> originalVertexIds() const;

    size_t estimatedBytes() const;

  private:
    size_t m_vertexCount = 0;
    std::vector<size_t> m_outgoingOffsets;
    std::vector<uint32_t> m_outgoingTargets;
    std::vector<double> m_latentMarks;
    std::vector<uint32_t> m_originalVertexIds;
};

struct GapNodeState {
    std::vector<GapSignature> signatures;
    std::vector<GapCoordinate> coordinates;
    size_t estimatedBytes() const;
};

struct LatentStateValidation {
    GapCoordinate coordinateRmse{};
    double totalCoordinateRmse = 0.0;
    double reconstructedMarkRmse = 0.0;
    double reconstructedMarkMaxError = 0.0;
};

uint64_t deriveGapSampleSeed(uint64_t masterSeed, uint64_t sampleIndex);
GapCoordinate gapContinuumCoordinate(double x);
GapNodeState computeGapNodeState(const ReferenceDag& graph);
LatentStateValidation validateGapNodeState(const ReferenceDag& graph,
                                           const GapNodeState& state);
