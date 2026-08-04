#include "digraph6.hxx"
#include "graph.hxx"

#include <cctype>
#include <cstddef>
#include <cstdint>
#include <stdexcept>
#include <string>
#include <string_view>

namespace {

constexpr std::string_view kHeader = ">>digraph6<<";

uint8_t readByte(std::string_view rec, size_t& pos) {
    if (pos >= rec.size()) {
        throw std::runtime_error("truncated digraph6 record");
    }

    return static_cast<uint8_t>(rec[pos++]);
}

uint32_t decodeValue(uint8_t byte) {
    if (byte < 63 || byte > 126) {
        throw std::runtime_error("invalid digraph6 byte");
    }

    return byte - 63;
}

uint64_t decodeOrder(std::string_view rec, size_t& pos) {
    const auto first = readByte(rec, pos);
    if (first != 126) {
        return decodeValue(first);
    }

    const auto second = readByte(rec, pos);
    if (second != 126) {
        auto order = static_cast<uint64_t>(decodeValue(second)) << 12;
        order |= static_cast<uint64_t>(decodeValue(readByte(rec, pos))) << 6;
        order |= decodeValue(readByte(rec, pos));
        return order;
    }

    uint64_t order = 0;
    for (int i = 0; i < 6; ++i) {
        order = (order << 6) | decodeValue(readByte(rec, pos));
    }

    return order;
}

} // namespace

std::string trimDigraph6(std::string_view rec) {
    while (!rec.empty() && isspace(static_cast<unsigned char>(rec.front()))) {
        rec.remove_prefix(1);
    }

    while (!rec.empty() && isspace(static_cast<unsigned char>(rec.back()))) {
        rec.remove_suffix(1);
    }

    if (rec.starts_with(kHeader)) {
        rec.remove_prefix(kHeader.size());
    }

    return std::string(rec);
}

Graph parseDigraph6(std::string_view rawRecord) {
    const auto rec = trimDigraph6(rawRecord);
    if (rec.empty() || rec.front() != '&') {
        throw std::runtime_error("digraph6 record must begin with '&'");
    }

    size_t pos = 1;
    const auto order = decodeOrder(rec, pos);
    if (order < 1 || order > 63) {
        throw std::runtime_error("this build supports digraph6 order 1..63");
    }

    const size_t vertexCount = static_cast<size_t>(order);
    Graph graph(static_cast<int>(vertexCount));
    const size_t bitCount = vertexCount * vertexCount;
    size_t bit = 0;

    while (pos < rec.size() && bit < bitCount) {
        const auto block = decodeValue(readByte(rec, pos));

        for (int shift = 5; shift >= 0 && bit < bitCount; --shift, ++bit) {
            if (((block >> shift) & 1U) == 0) {
                continue;
            }

            const auto src = static_cast<int>(bit / vertexCount);
            const auto dst = static_cast<int>(bit % vertexCount);
            graph.addEdge(src, dst);
        }
    }

    if (bit < bitCount) {
        throw std::runtime_error("truncated digraph6 adjacency data");
    }

    return graph;
}
