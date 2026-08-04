#include "wl_profile.hxx"

#include "digraph6.hxx"

#include <algorithm>
#include <array>
#include <bit>
#include <cstddef>
#include <cstdint>
#include <filesystem>
#include <format>
#include <fstream>
#include <iostream>
#include <map>
#include <ostream>
#include <print>
#include <set>
#include <stdexcept>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

namespace {

using PairDescriptor = std::array<uint8_t, 17>;

struct Hash256 {
    std::array<uint64_t, 4> words{};
};

struct WlRecord {
    std::string digraph6;
    Graph graph;
};

struct RefinementDescriptor {
    int oldColor = 0;
    std::vector<std::pair<int, int>> transitions;

    auto operator<=>(const RefinementDescriptor&) const = default;
};

struct RefinementItem {
    RefinementDescriptor descriptor;
    size_t graph = 0;
    size_t position = 0;
};

size_t pairIndex(int source, int target, int width) {
    return static_cast<size_t>(source) * static_cast<size_t>(width) +
           static_cast<size_t>(target);
}

Hash256 hashKey(std::span<const uint8_t> key) {
    Hash256 hash{{
        0x243f6a8885a308d3ULL,
        0x13198a2e03707344ULL,
        0xa4093822299f31d0ULL,
        0x082efa98ec4e6c89ULL,
    }};

    constexpr std::array<uint64_t, 4> multipliers{{
        0x9e3779b185ebca87ULL,
        0xc2b2ae3d27d4eb4fULL,
        0x165667b19e3779f9ULL,
        0xd6e8feb86659fd93ULL,
    }};

    constexpr std::array<int, 4> rotations{{17, 29, 41, 53}};

    uint64_t position = 0;

    for (const uint8_t byte : key) {
        for (size_t word = 0; word < hash.words.size(); ++word) {
            hash.words[word] ^=
                static_cast<uint64_t>(byte) + (position << ((word + 1) & 7)) +
                0x9e3779b97f4a7c15ULL * static_cast<uint64_t>(word + 1);
            hash.words[word] *= multipliers[word];
            hash.words[word] = std::rotl(hash.words[word], rotations[word]);
            hash.words[word] ^= hash.words[word] >> 31;
        }

        ++position;
    }

    for (size_t word = 0; word < hash.words.size(); ++word) {
        const size_t reverse = multipliers.size() - 1 - word;
        hash.words[word] ^=
            static_cast<uint64_t>(key.size()) * multipliers[reverse];
        hash.words[word] ^= hash.words[word] >> 30;
        hash.words[word] *= 0xbf58476d1ce4e5b9ULL;
        hash.words[word] ^= hash.words[word] >> 27;
        hash.words[word] *= 0x94d049bb133111ebULL;
        hash.words[word] ^= hash.words[word] >> 31;
    }

    return hash;
}

std::string hashText(const Hash256& hash) {
    std::string out;
    out.reserve(hash.words.size() * 16);

    for (const uint64_t word : hash.words) {
        out += std::format("{:016x}", word);
    }

    return out;
}

std::string escapeJson(std::string_view value) {
    std::string out;
    out.reserve(value.size());

    for (const char ch : value) {
        switch (ch) {
        case '"':
            out += "\\\"";
            break;
        case '\\':
            out += "\\\\";
            break;
        case '\n':
            out += "\\n";
            break;
        case '\r':
            out += "\\r";
            break;
        case '\t':
            out += "\\t";
            break;
        default:
            out += static_cast<char>(ch);
            break;
        }
    }

    return out;
}

std::string edgesJson(const Graph& graph) {
    std::string out{"["};
    bool first = true;

    for (int source = 0; source < graph.vertexCount(); ++source) {
        for (int target = 0; target < graph.vertexCount(); ++target) {
            if (!graph.hasEdge(source, target)) {
                continue;
            }

            if (!first) {
                out += ',';
            }

            first = false;
            out += std::format("[{},{}]", source, target);
        }
    }

    out += ']';
    return out;
}

size_t uniqueGraphKeyCount(const std::vector<std::vector<int>>& keys) {
    return std::set<std::vector<int>>(keys.begin(), keys.end()).size();
}

std::pair<size_t, size_t>
unresolvedGraphKeys(const std::vector<std::vector<int>>& keys) {
    std::map<std::vector<int>, size_t> groups;
    for (const std::vector<int>& key : keys) {
        ++groups[key];
    }

    size_t classCount = 0;
    size_t graphCount = 0;

    for (const auto& entry : groups) {
        const size_t count = entry.second;
        if (count > 1) {
            ++classCount;
            graphCount += count;
        }
    }

    return {classCount, graphCount};
}

int initialColor(const Graph& graph, int source, int target) {
    if (source == target) {
        return 0;
    }

    if (graph.hasEdge(source, target)) {
        return 1;
    }

    if (graph.hasEdge(target, source)) {
        return 2;
    }

    return 3;
}

struct WlReductionState {
    std::string currentHash;
    std::vector<std::string> bucket;
    size_t totalRecords = 0;
    size_t hashBuckets = 0;
    size_t collisionClasses = 0;
    size_t collisionGraphs = 0;
    size_t unresolvedClasses = 0;
    size_t unresolvedGraphs = 0;
    size_t classId = 0;
};

void flushWlBucket(WlReductionState& state, int vertexCount,
                   std::ostream& collisionOutput,
                   std::ostream& separationOutput) {
    if (state.bucket.size() < 2) {
        state.bucket.clear();
        return;
    }

    ++state.hashBuckets;
    std::map<OneRoundKey, std::vector<WlRecord>> exactGroups;

    for (const std::string& record : state.bucket) {
        Graph graph = parseDigraph6(record);
        if (graph.vertexCount() != vertexCount) {
            throw std::runtime_error(
                "digraph6 record has unexpected vertex count");
        }

        OneRoundKey key = oneRoundWlKey(graph);
        exactGroups[std::move(key)].push_back({
            .digraph6 = record,
            .graph = std::move(graph),
        });
    }

    for (auto& entry : exactGroups) {
        auto& records = entry.second;
        if (records.size() < 2) {
            continue;
        }

        std::ranges::sort(records, {}, &WlRecord::digraph6);

        ++state.collisionClasses;
        state.collisionGraphs += records.size();

        std::vector<Graph> graphs;
        graphs.reserve(records.size());

        for (const WlRecord& record : records) {
            graphs.push_back(record.graph);
        }

        const StableWlResult out = stabilizeWl(graphs);
        const auto [remainingClasses, remainingGraphs] =
            unresolvedGraphKeys(out.graphKeys);
        state.unresolvedClasses += remainingClasses;
        state.unresolvedGraphs += remainingGraphs;

        const size_t stableClasses = uniqueGraphKeyCount(out.graphKeys);
        const std::string sepText =
            out.separationRound == 0 ? "unresolved"
                                     : std::format("{}", out.separationRound);
        const std::string sepJson =
            out.separationRound == 0 ? "null"
                                     : std::format("{}", out.separationRound);

        std::println(separationOutput, "{}\t{}\t{}\t{}", state.classId,
                     records.size(), sepText, stableClasses);

        std::print(collisionOutput,
                   "{{\"class\":{},"
                   "\"one_round_hash\":\"{}\","
                   "\"size\":{},"
                   "\"separation_round\":{},"
                   "\"stable_class_count\":{},"
                   "\"graphs\":[",
                   state.classId, escapeJson(state.currentHash), records.size(),
                   sepJson, stableClasses);

        for (size_t i = 0; i < records.size(); ++i) {
            if (i != 0) {
                std::print(collisionOutput, ",");
            }

            const WlRecord& record = records[i];
            std::print(collisionOutput, "{{\"d6\":\"{}\",\"edges\":{}}}",
                       escapeJson(record.digraph6), edgesJson(record.graph));
        }

        std::println(collisionOutput, "]}}");
        ++state.classId;
    }

    state.bucket.clear();
}

} // namespace

OneRoundKey oneRoundWlKey(const Graph& graph) {
    const int vertexCount = graph.vertexCount();
    std::vector<PairDescriptor> descriptors;
    const size_t vertexSize = static_cast<size_t>(vertexCount);
    descriptors.reserve(vertexSize * vertexSize);

    for (int source = 0; source < vertexCount; ++source) {
        for (int target = 0; target < vertexCount; ++target) {
            PairDescriptor descriptor{};
            descriptor[0] =
                static_cast<uint8_t>(initialColor(graph, source, target));

            for (int middle = 0; middle < vertexCount; ++middle) {
                const int left = initialColor(graph, source, middle);
                const int right = initialColor(graph, middle, target);
                const size_t position =
                    1 + static_cast<size_t>(4 * left + right);
                ++descriptor[position];
            }

            descriptors.push_back(descriptor);
        }
    }

    std::ranges::sort(descriptors);
    OneRoundKey key;
    key.reserve(3 + descriptors.size() * 17);
    key.push_back(static_cast<uint8_t>(vertexCount));

    const int edgeCount = graph.edgeCount();
    key.push_back(static_cast<uint8_t>(edgeCount >> 8));
    key.push_back(static_cast<uint8_t>(edgeCount));

    for (const PairDescriptor& descriptor : descriptors) {
        key.insert(key.end(), descriptor.begin(), descriptor.end());
    }

    return key;
}

StableWlResult stabilizeWl(std::span<const Graph> graphs) {
    if (graphs.empty()) {
        return {};
    }

    const int vertexCount = graphs.front().vertexCount();
    if (!std::ranges::all_of(graphs, [vertexCount](const Graph& graph) {
            return graph.vertexCount() == vertexCount;
        })) {
        throw std::invalid_argument("joint 2-WL requires equal graph orders");
    }

    const int pairCount = vertexCount * vertexCount;
    const size_t pairSize = static_cast<size_t>(pairCount);
    std::vector<std::vector<int>> colors(graphs.size(),
                                         std::vector<int>(pairSize, 0));

    for (size_t g = 0; g < graphs.size(); ++g) {
        for (int source = 0; source < vertexCount; ++source) {
            for (int target = 0; target < vertexCount; ++target) {
                colors[g][pairIndex(source, target, vertexCount)] =
                    initialColor(graphs[g], source, target);
            }
        }
    }

    int colorCount = 4;
    StableWlResult out;

    for (int round = 1; round <= pairCount + 2; ++round) {
        std::vector<RefinementItem> items;
        items.reserve(graphs.size() * pairSize);

        for (size_t g = 0; g < graphs.size(); ++g) {
            for (int source = 0; source < vertexCount; ++source) {
                for (int target = 0; target < vertexCount; ++target) {
                    const size_t position =
                        pairIndex(source, target, vertexCount);
                    RefinementDescriptor descriptor;
                    descriptor.oldColor = colors[g][position];
                    descriptor.transitions.reserve(
                        static_cast<size_t>(vertexCount));

                    for (int middle = 0; middle < vertexCount; ++middle) {
                        descriptor.transitions.emplace_back(
                            colors[g][pairIndex(source, middle, vertexCount)],
                            colors[g][pairIndex(middle, target, vertexCount)]);
                    }

                    std::ranges::sort(descriptor.transitions);
                    items.push_back({std::move(descriptor), g, position});
                }
            }
        }

        std::ranges::sort(items, {}, &RefinementItem::descriptor);

        std::vector<std::vector<int>> next(graphs.size(),
                                           std::vector<int>(pairSize, 0));
        int color = -1;
        RefinementDescriptor prev;
        bool hasPrev = false;

        for (const RefinementItem& item : items) {
            if (!hasPrev || item.descriptor != prev) {
                ++color;
                prev = item.descriptor;
                hasPrev = true;
            }

            next[item.graph][item.position] = color;
        }

        out.graphKeys.clear();
        out.graphKeys.reserve(graphs.size());

        for (const std::vector<int>& graphColors : next) {
            std::vector<int> graphKey = graphColors;
            std::ranges::sort(graphKey);
            out.graphKeys.push_back(std::move(graphKey));
        }

        out.rounds = round;

        if (uniqueGraphKeyCount(out.graphKeys) == graphs.size()) {
            out.separationRound = round;
            return out;
        }

        const int nextColorCount = color + 1;

        if (nextColorCount == colorCount) {
            return out;
        }

        colorCount = nextColorCount;
        colors.swap(next);
    }

    return out;
}

int generateWlScan() {
    std::string line;
    size_t count = 0;

    while (std::getline(std::cin, line)) {
        const std::string record = trimDigraph6(line);
        if (record.empty()) {
            continue;
        }

        const Graph graph = parseDigraph6(record);
        const OneRoundKey key = oneRoundWlKey(graph);
        std::println("{}\t{}", hashText(hashKey(key)), record);
        ++count;
    }

    std::println(stderr, "processed_graphs={}", count);
    return 0;
}

int generateWlReduction(int vertexCount,
                        const std::filesystem::path& outputDirectory) {
    if (vertexCount < 1 || vertexCount > 63) {
        throw std::invalid_argument(
            "WL generation supports vertex count 1..63");
    }

    std::filesystem::create_directories(outputDirectory);

    const std::filesystem::path collisionPath =
        outputDirectory / "collisions.jsonl";
    const std::filesystem::path separationPath =
        outputDirectory / "separation-rounds.tsv";
    std::ofstream collisionOutput(collisionPath);
    std::ofstream separationOutput(separationPath);

    if (!collisionOutput) {
        throw std::runtime_error(std::format("cannot create WL artifact: {}",
                                             collisionPath.string()));
    }

    if (!separationOutput) {
        throw std::runtime_error(std::format("cannot create WL artifact: {}",
                                             separationPath.string()));
    }

    std::println(separationOutput,
                 "class\tsize\tseparation_round\tstable_class_count");

    WlReductionState state;

    std::string line;

    while (std::getline(std::cin, line)) {
        if (line.empty()) {
            continue;
        }

        const size_t tab = line.find('\t');
        if (tab == std::string::npos) {
            throw std::runtime_error(
                "WL reduction input must be HASH<TAB>DIGRAPH6");
        }

        const std::string hash = line.substr(0, tab);
        const std::string record = line.substr(tab + 1);
        if (!state.currentHash.empty() && hash != state.currentHash) {
            flushWlBucket(state, vertexCount, collisionOutput,
                          separationOutput);
        }

        if (state.bucket.empty()) {
            state.currentHash = hash;
        }

        state.bucket.push_back(record);
        ++state.totalRecords;
    }

    flushWlBucket(state, vertexCount, collisionOutput, separationOutput);

    const std::filesystem::path summaryPath = outputDirectory / "summary.txt";
    std::ofstream summaryOutput(summaryPath);

    if (!summaryOutput) {
        throw std::runtime_error(
            std::format("cannot create WL artifact: {}", summaryPath.string()));
    }

    std::print(summaryOutput,
               "total_records={}\n"
               "hash_buckets_gt1={}\n"
               "exact_one_round_collision_classes={}\n"
               "exact_one_round_collision_graphs={}\n"
               "stable_2wl_unresolved_classes={}\n"
               "stable_2wl_unresolved_graphs={}\n",
               state.totalRecords, state.hashBuckets, state.collisionClasses,
               state.collisionGraphs, state.unresolvedClasses,
               state.unresolvedGraphs);

    std::println(stderr,
                 "total_records={} exact_collision_classes={} "
                 "stable_unresolved_classes={}",
                 state.totalRecords, state.collisionClasses,
                 state.unresolvedClasses);

    return 0;
}
