#include "reference_dag.hxx"

#include <algorithm>
#include <cmath>
#include <limits>
#include <numeric>
#include <stdexcept>

namespace {

constexpr uint64_t kMarkDomain = 0x243f6a8885a308d3ULL;
constexpr uint64_t kEdgeDomain = 0x13198a2e03707344ULL;
constexpr uint64_t kSampleDomain = 0xa4093822299f31d0ULL;

uint64_t splitMix64(uint64_t value) {
    value += 0x9e3779b97f4a7c15ULL;
    value = (value ^ (value >> 30)) * 0xbf58476d1ce4e5b9ULL;
    value = (value ^ (value >> 27)) * 0x94d049bb133111ebULL;
    return value ^ (value >> 31);
}

double uniform01(uint64_t value) {
    constexpr double scale = 0x1.0p-53;
    return static_cast<double>(splitMix64(value) >> 11) * scale;
}

uint64_t pairCounter(uint32_t first, uint32_t second) {
    const uint32_t low = std::min(first, second);
    const uint32_t high = std::max(first, second);
    return (static_cast<uint64_t>(low) << 32) | high;
}

} // namespace
GapCoordinate gapContinuumCoordinate(double x) {
    const double oneMinusX = 1.0 - x;
    const double x2 = x * x;
    const double x4 = x2 * x2;
    const double oneMinusX2 = oneMinusX * oneMinusX;
    const double oneMinusX4 = oneMinusX2 * oneMinusX2;

    return {
        oneMinusX2 / 2.0,
        x2 / 2.0,
        oneMinusX4 / 24.0,
        x4 / 24.0,
        1.0 / 8.0 - x / 6.0 + x4 / 24.0,
        1.0 / 8.0 - oneMinusX / 6.0 + oneMinusX4 / 24.0,
    };
}

uint64_t deriveGapSampleSeed(uint64_t masterSeed, uint64_t sampleIndex) {
    return splitMix64(masterSeed ^ kSampleDomain ^ splitMix64(sampleIndex));
}

ReferenceDag ReferenceDag::generate(size_t vertexCount, uint64_t sampleSeed) {
    if (vertexCount < 2) {
        throw std::invalid_argument("vertex count must be at least two");
    }
    if (vertexCount > std::numeric_limits<uint32_t>::max()) {
        throw std::invalid_argument(
            "vertex count exceeds the 32-bit DAG index");
    }

    struct MarkedVertex {
        double mark;
        uint32_t originalId;
    };

    std::vector<MarkedVertex> vertices(vertexCount);
    for (size_t index = 0; index < vertexCount; ++index) {
        vertices[index] = {
            .mark = uniform01(sampleSeed ^ kMarkDomain ^ splitMix64(index)),
            .originalId = static_cast<uint32_t>(index),
        };
    }

    std::ranges::sort(vertices,
                      [](const MarkedVertex& left, const MarkedVertex& right) {
                          if (left.mark != right.mark) {
                              return left.mark < right.mark;
                          }
                          return left.originalId < right.originalId;
                      });

    ReferenceDag graph;
    graph.m_vertexCount = vertexCount;
    graph.m_outgoingOffsets.resize(vertexCount + 1);
    graph.m_latentMarks.resize(vertexCount);
    graph.m_originalVertexIds.resize(vertexCount);

    const size_t pairCount = vertexCount * (vertexCount - 1) / 2;
    const size_t expectedEdgeCount = pairCount / 3;
    // Keep a modest margin above the mean to avoid a full capacity doubling.
    graph.m_outgoingTargets.reserve(expectedEdgeCount + pairCount / 24 + 1);

    for (size_t source = 0; source < vertexCount; ++source) {
        graph.m_outgoingOffsets[source] = graph.m_outgoingTargets.size();
        graph.m_latentMarks[source] = vertices[source].mark;
        graph.m_originalVertexIds[source] = vertices[source].originalId;

        for (size_t target = source + 1; target < vertexCount; ++target) {
            const double separation =
                vertices[target].mark - vertices[source].mark;
            const uint64_t counter = pairCounter(vertices[source].originalId,
                                                 vertices[target].originalId);
            const double draw =
                uniform01(sampleSeed ^ kEdgeDomain ^ splitMix64(counter));
            if (draw < separation) {
                graph.m_outgoingTargets.push_back(
                    static_cast<uint32_t>(target));
            }
        }
    }
    graph.m_outgoingOffsets[vertexCount] = graph.m_outgoingTargets.size();

    return graph;
}

ReferenceDag ReferenceDag::fromTopologicalEdges(
    size_t vertexCount, std::span<const std::pair<uint32_t, uint32_t>> edges) {
    if (vertexCount < 1 || vertexCount > std::numeric_limits<uint32_t>::max()) {
        throw std::invalid_argument("invalid scalable DAG vertex count");
    }

    ReferenceDag graph;
    graph.m_vertexCount = vertexCount;
    graph.m_outgoingOffsets.assign(vertexCount + 1, 0);

    for (const auto& [source, target] : edges) {
        if (source >= vertexCount || target >= vertexCount ||
            source >= target) {
            throw std::invalid_argument(
                "test DAG edges must follow the supplied topological order");
        }
        ++graph.m_outgoingOffsets[source + 1];
    }

    std::partial_sum(graph.m_outgoingOffsets.begin(),
                     graph.m_outgoingOffsets.end(),
                     graph.m_outgoingOffsets.begin());
    graph.m_outgoingTargets.resize(edges.size());
    std::vector<size_t> cursors = graph.m_outgoingOffsets;
    for (const auto& [source, target] : edges) {
        graph.m_outgoingTargets[cursors[source]++] = target;
    }

    for (size_t source = 0; source < vertexCount; ++source) {
        auto first =
            graph.m_outgoingTargets.begin() +
            static_cast<std::ptrdiff_t>(graph.m_outgoingOffsets[source]);
        auto last =
            graph.m_outgoingTargets.begin() +
            static_cast<std::ptrdiff_t>(graph.m_outgoingOffsets[source + 1]);
        std::ranges::sort(first, last);
        if (std::adjacent_find(first, last) != last) {
            throw std::invalid_argument("test DAG contains a duplicate edge");
        }
    }

    return graph;
}

size_t ReferenceDag::vertexCount() const { return m_vertexCount; }

size_t ReferenceDag::edgeCount() const { return m_outgoingTargets.size(); }

std::span<const size_t> ReferenceDag::outgoingOffsets() const {
    return m_outgoingOffsets;
}

std::span<const uint32_t> ReferenceDag::outgoingTargets() const {
    return m_outgoingTargets;
}

bool ReferenceDag::hasLatentMarks() const {
    return m_latentMarks.size() == m_vertexCount;
}

std::span<const double> ReferenceDag::latentMarks() const {
    return m_latentMarks;
}

std::span<const uint32_t> ReferenceDag::originalVertexIds() const {
    return m_originalVertexIds;
}

size_t ReferenceDag::estimatedBytes() const {
    return sizeof(*this) + m_outgoingOffsets.capacity() * sizeof(size_t) +
           m_outgoingTargets.capacity() * sizeof(uint32_t) +
           m_latentMarks.capacity() * sizeof(double) +
           m_originalVertexIds.capacity() * sizeof(uint32_t);
}

size_t GapNodeState::estimatedBytes() const {
    return sizeof(*this) + signatures.capacity() * sizeof(GapSignature) +
           coordinates.capacity() * sizeof(GapCoordinate);
}

GapNodeState computeGapNodeState(const ReferenceDag& graph) {
    const size_t vertexCount = graph.vertexCount();
    const auto offsets = graph.outgoingOffsets();
    const auto targets = graph.outgoingTargets();

    std::vector<uint64_t> outDegree(vertexCount);
    std::vector<uint64_t> inDegree(vertexCount, 0);
    for (size_t source = 0; source < vertexCount; ++source) {
        outDegree[source] = offsets[source + 1] - offsets[source];
        for (size_t edge = offsets[source]; edge < offsets[source + 1];
             ++edge) {
            ++inDegree[targets[edge]];
        }
    }

    std::vector<uint64_t> qPlusPlus(vertexCount, 0);
    std::vector<uint64_t> qMinusMinus(vertexCount, 0);
    std::vector<uint64_t> qPlusMinus(vertexCount, 0);
    std::vector<uint64_t> qMinusPlus(vertexCount, 0);

    for (size_t source = 0; source < vertexCount; ++source) {
        for (size_t edge = offsets[source]; edge < offsets[source + 1];
             ++edge) {
            const size_t target = targets[edge];
            qPlusPlus[source] += outDegree[target];
            qPlusMinus[source] += inDegree[target];
            qMinusMinus[target] += inDegree[source];
            qMinusPlus[target] += outDegree[source];
        }
    }

    GapNodeState state;
    state.signatures.resize(vertexCount);
    state.coordinates.resize(vertexCount);
    const double inverseN = 1.0 / static_cast<double>(vertexCount);
    const double inverseN2 = inverseN * inverseN;

    for (size_t vertex = 0; vertex < vertexCount; ++vertex) {
        state.signatures[vertex] = {
            outDegree[vertex],   inDegree[vertex],   qPlusPlus[vertex],
            qMinusMinus[vertex], qPlusMinus[vertex], qMinusPlus[vertex],
        };
        state.coordinates[vertex] = {
            static_cast<double>(outDegree[vertex]) * inverseN,
            static_cast<double>(inDegree[vertex]) * inverseN,
            static_cast<double>(qPlusPlus[vertex]) * inverseN2,
            static_cast<double>(qMinusMinus[vertex]) * inverseN2,
            static_cast<double>(qPlusMinus[vertex]) * inverseN2,
            static_cast<double>(qMinusPlus[vertex]) * inverseN2,
        };
    }

    return state;
}

LatentStateValidation validateGapNodeState(const ReferenceDag& graph,
                                           const GapNodeState& state) {
    if (!graph.hasLatentMarks()) {
        throw std::invalid_argument(
            "latent validation requires a generated reference DAG");
    }
    if (state.coordinates.size() != graph.vertexCount()) {
        throw std::invalid_argument("node-state size does not match graph");
    }

    LatentStateValidation result;
    std::array<long double, kGapCoordinateCount> squaredErrors{};
    long double markSquaredError = 0.0L;

    for (size_t vertex = 0; vertex < graph.vertexCount(); ++vertex) {
        const double mark = graph.latentMarks()[vertex];
        const GapCoordinate expected = gapContinuumCoordinate(mark);
        for (size_t coordinate = 0; coordinate < kGapCoordinateCount;
             ++coordinate) {
            const long double error =
                state.coordinates[vertex][coordinate] - expected[coordinate];
            squaredErrors[coordinate] += error * error;
        }

        const double reconstructed =
            0.5 + state.coordinates[vertex][1] - state.coordinates[vertex][0];
        const double markError = reconstructed - mark;
        markSquaredError += static_cast<long double>(markError) * markError;
        result.reconstructedMarkMaxError =
            std::max(result.reconstructedMarkMaxError, std::abs(markError));
    }

    long double totalSquaredError = 0.0L;
    for (size_t coordinate = 0; coordinate < kGapCoordinateCount;
         ++coordinate) {
        const long double meanSquaredError =
            squaredErrors[coordinate] /
            static_cast<long double>(graph.vertexCount());
        result.coordinateRmse[coordinate] =
            std::sqrt(static_cast<double>(meanSquaredError));
        totalSquaredError += meanSquaredError;
    }

    result.totalCoordinateRmse =
        std::sqrt(static_cast<double>(totalSquaredError));
    result.reconstructedMarkRmse = std::sqrt(static_cast<double>(
        markSquaredError / static_cast<long double>(graph.vertexCount())));
    return result;
}
