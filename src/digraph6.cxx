#include "digraph6.hxx"

#include <cctype>
#include <cstddef>
#include <cstdint>
#include <stdexcept>
#include <string_view>

namespace {

constexpr std::string_view kHeader = ">>digraph6<<";

unsigned int decodeSixBit(uint8_t byte) {
    if (byte < 63 || byte > 126) {
        throw std::runtime_error("invalid digraph6 byte");
    }

    return byte - 63;
}

uint64_t decodeOrder(std::string_view rec, size_t& pos) {
    if (pos == rec.size()) {
        throw std::runtime_error("truncated digraph6 order");
    }

    const auto first = static_cast<uint8_t>(rec[pos++]);
    if (first != 126) {
        return decodeSixBit(first);
    }

    if (pos == rec.size()) {
        throw std::runtime_error("truncated digraph6 order");
    }

    const auto second = static_cast<uint8_t>(rec[pos++]);
    if (second != 126) {
        if (pos + 2 > rec.size()) {
            throw std::runtime_error("truncated 18-bit digraph6 order");
        }

        uint64_t order = static_cast<uint64_t>(decodeSixBit(second)) << 12;
        order |= static_cast<uint64_t>(
                     decodeSixBit(static_cast<uint8_t>(rec[pos++])))
                 << 6;
        order |= decodeSixBit(static_cast<uint8_t>(rec[pos++]));
        return order;
    }

    if (pos + 6 > rec.size()) {
        throw std::runtime_error("truncated 36-bit digraph6 order");
    }

    uint64_t order = 0;
    for (int index = 0; index < 6; ++index) {
        order = (order << 6) |
                decodeSixBit(static_cast<uint8_t>(rec[pos++]));
    }

    return order;
}

} // namespace

std::string trimDigraph6(std::string_view rec) {
    while (!rec.empty() &&
           std::isspace(static_cast<uint8_t>(rec.front()))) {
        rec.remove_prefix(1);
    }

    while (!rec.empty() &&
           std::isspace(static_cast<uint8_t>(rec.back()))) {
        rec.remove_suffix(1);
    }

    if (rec.starts_with(kHeader)) {
        rec.remove_prefix(kHeader.size());
    }

    return std::string(rec);
}

Graph parseDigraph6(std::string_view rawRecord) {
    const std::string rec = trimDigraph6(rawRecord);
    if (rec.empty() || rec.front() != '&') {
        throw std::runtime_error("digraph6 rec must begin with '&'");
    }

    size_t pos = 1;
    const uint64_t order = decodeOrder(rec, pos);
    if (order < 1 || order > 63) {
        throw std::runtime_error("this build supports digraph6 order 1..63");
    }

    Graph graph(static_cast<int>(order));
    const size_t bitCount = static_cast<size_t>(order) * order;
    size_t bitIndex = 0;

    while (pos < rec.size() && bitIndex < bitCount) {
        const unsigned int block =
            decodeSixBit(static_cast<uint8_t>(rec[pos++]));

        for (int shift = 5; shift >= 0 && bitIndex < bitCount;
             --shift, ++bitIndex) {
            if (((block >> shift) & 1U) == 0) {
                continue;
            }

            const int source = static_cast<int>(bitIndex / order);
            const int target = static_cast<int>(bitIndex % order);
            graph.addEdge(source, target);
        }
    }

    if (bitIndex < bitCount) {
        throw std::runtime_error("truncated digraph6 adjacency data");
    }

    return graph;
}
