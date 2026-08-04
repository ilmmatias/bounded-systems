#include "reference_dag.hxx"

#include <algorithm>
#include <cmath>
#include <cstddef>
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
    for (size_t i = 0; i < vertexCount; ++i) {
        vertices[i] = {
            .mark = uniform01(sampleSeed ^ kMarkDomain ^ splitMix64(i)),
            .originalId = static_cast<uint32_t>(i),
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
    const size_t expectedEdges = pairCount / 3;
    // Keep a modest margin above the mean to avoid a full capacity doubling.
    graph.m_outgoingTargets.reserve(expectedEdges + pairCount / 24 + 1);

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
        auto first = graph.m_outgoingTargets.begin() +
                     static_cast<ptrdiff_t>(graph.m_outgoingOffsets[source]);
        auto last = graph.m_outgoingTargets.begin() +
                    static_cast<ptrdiff_t>(graph.m_outgoingOffsets[source + 1]);
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
    const size_t n = graph.vertexCount();
    const auto offsets = graph.outgoingOffsets();
    const auto targets = graph.outgoingTargets();

    std::vector<uint64_t> outDeg(n);
    std::vector<uint64_t> inDeg(n, 0);
    for (size_t src = 0; src < n; ++src) {
        outDeg[src] = offsets[src + 1] - offsets[src];
        for (size_t edge = offsets[src]; edge < offsets[src + 1]; ++edge) {
            ++inDeg[targets[edge]];
        }
    }

    std::vector<uint64_t> qPlusPlus(n, 0);
    std::vector<uint64_t> qMinusMinus(n, 0);
    std::vector<uint64_t> qPlusMinus(n, 0);
    std::vector<uint64_t> qMinusPlus(n, 0);

    for (size_t src = 0; src < n; ++src) {
        for (size_t edge = offsets[src]; edge < offsets[src + 1]; ++edge) {
            const size_t dst = targets[edge];
            qPlusPlus[src] += outDeg[dst];
            qPlusMinus[src] += inDeg[dst];
            qMinusMinus[dst] += inDeg[src];
            qMinusPlus[dst] += outDeg[src];
        }
    }

    GapNodeState state;
    state.signatures.resize(n);
    state.coordinates.resize(n);
    const double invN = 1.0 / static_cast<double>(n);
    const double invN2 = invN * invN;

    for (size_t vertex = 0; vertex < n; ++vertex) {
        state.signatures[vertex] = {
            outDeg[vertex],      inDeg[vertex],      qPlusPlus[vertex],
            qMinusMinus[vertex], qPlusMinus[vertex], qMinusPlus[vertex],
        };
        state.coordinates[vertex] = {
            static_cast<double>(outDeg[vertex]) * invN,
            static_cast<double>(inDeg[vertex]) * invN,
            static_cast<double>(qPlusPlus[vertex]) * invN2,
            static_cast<double>(qMinusMinus[vertex]) * invN2,
            static_cast<double>(qPlusMinus[vertex]) * invN2,
            static_cast<double>(qMinusPlus[vertex]) * invN2,
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

    LatentStateValidation out;
    std::array<long double, kGapCoordinateCount> sqErrors{};
    long double markSqError = 0.0L;

    for (size_t vertex = 0; vertex < graph.vertexCount(); ++vertex) {
        const double mark = graph.latentMarks()[vertex];
        const GapCoordinate expected = gapContinuumCoordinate(mark);
        for (size_t coord = 0; coord < kGapCoordinateCount; ++coord) {
            const long double error =
                state.coordinates[vertex][coord] - expected[coord];
            sqErrors[coord] += error * error;
        }

        const double reconstructed =
            0.5 + state.coordinates[vertex][1] - state.coordinates[vertex][0];
        const double markError = reconstructed - mark;
        markSqError += static_cast<long double>(markError) * markError;
        out.reconstructedMarkMaxError =
            std::max(out.reconstructedMarkMaxError, std::abs(markError));
    }

    long double totalSqError = 0.0L;
    for (size_t coord = 0; coord < kGapCoordinateCount; ++coord) {
        const long double mse =
            sqErrors[coord] / static_cast<long double>(graph.vertexCount());
        out.coordinateRmse[coord] = std::sqrt(static_cast<double>(mse));
        totalSqError += mse;
    }

    out.totalCoordinateRmse = std::sqrt(static_cast<double>(totalSqError));
    out.reconstructedMarkRmse = std::sqrt(static_cast<double>(
        markSqError / static_cast<long double>(graph.vertexCount())));
    return out;
}
