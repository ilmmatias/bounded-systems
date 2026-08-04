#include "graph.hxx"

#include <algorithm>
#include <bit>
#include <stdexcept>

Graph::Graph(int vertexCount) : m_vertexCount(vertexCount) {
    if (m_vertexCount < 1 || m_vertexCount > 63) {
        throw std::invalid_argument("vertex count must be in 1..63");
    }

    m_outgoing.resize(static_cast<size_t>(m_vertexCount));
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

    const size_t sourceIndex = static_cast<size_t>(source);
    return ((m_outgoing[sourceIndex] >> target) & 1U) != 0;
}

void Graph::addEdge(int source, int target) {
    if (source < 0 || source >= m_vertexCount || target < 0 ||
        target >= m_vertexCount) {
        throw std::out_of_range("graph vertex index out of range");
    }

    const size_t sourceIndex = static_cast<size_t>(source);
    m_outgoing[sourceIndex] |= uint64_t{1} << target;
}

std::span<const uint64_t> Graph::outgoing() const { return m_outgoing; }
