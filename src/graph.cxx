#include "graph.hxx"

#include <algorithm>
#include <bit>
#include <stdexcept>

Graph::Graph(int vertexCount)
    : m_vertexCount(vertexCount),
      m_outgoing(static_cast<size_t>(vertexCount), 0) {
    if (m_vertexCount < 1 || m_vertexCount > 63) {
        throw std::invalid_argument("vertexCount must be in 1..63");
    }
}

int Graph::vertexCount() const { return m_vertexCount; }

int Graph::edgeCount() const {
    return std::ranges::fold_left(m_outgoing, 0, [](int count, uint64_t row) {
        return count + std::popcount(row);
    });
}

bool Graph::hasEdge(int source, int target) const {
    if (source < 0 || source >= m_vertexCount || target < 0 ||
        target >= m_vertexCount) {
        throw std::out_of_range("graph vertex index out of range");
    }

    return ((m_outgoing[source] >> target) & 1U) != 0;
}

void Graph::addEdge(int source, int target) {
    if (source < 0 || source >= m_vertexCount || target < 0 ||
        target >= m_vertexCount) {
        throw std::out_of_range("graph vertex index out of range");
    }

    m_outgoing[source] |= uint64_t{1} << target;
}

std::span<const uint64_t> Graph::outgoing() const { return m_outgoing; }
