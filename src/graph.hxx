#pragma once

#include <cstdint>
#include <span>
#include <vector>

class Graph {
  public:
    explicit Graph(int vertexCount);

    int vertexCount() const;
    int edgeCount() const;

    bool hasEdge(int source, int target) const;
    void addEdge(int source, int target);

    std::span<const uint64_t> outgoing() const;

  private:
    int m_vertexCount;
    std::vector<uint64_t> m_outgoing;
};
