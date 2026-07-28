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
#include <print>
#include <ranges>
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

struct OneRoundKeyLess {
    bool operator()(const OneRoundKey& left, const OneRoundKey& right) const {
        return std::ranges::lexicographical_compare(left, right);
    }
};

struct RefinementDescriptor {
    int oldColor = 0;
    std::vector<std::pair<int, int>> transitions;

    auto operator<=>(const RefinementDescriptor&) const = default;
};

struct RefinementItem {
    RefinementDescriptor descriptor;
    size_t graph = 0;
    int position = 0;
};

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
        for (int word = 0; word < 4; ++word) {
            hash.words[word] ^=
                static_cast<uint64_t>(byte) + (position << ((word + 1) & 7)) +
                0x9e3779b97f4a7c15ULL * static_cast<uint64_t>(word + 1);
            hash.words[word] *= multipliers[word];
            hash.words[word] = std::rotl(hash.words[word], rotations[word]);
            hash.words[word] ^= hash.words[word] >> 31;
        }

        ++position;
    }

    for (int word = 0; word < 4; ++word) {
        hash.words[word] ^=
            static_cast<uint64_t>(key.size()) * multipliers[3 - word];
        hash.words[word] ^= hash.words[word] >> 30;
        hash.words[word] *= 0xbf58476d1ce4e5b9ULL;
        hash.words[word] ^= hash.words[word] >> 27;
        hash.words[word] *= 0x94d049bb133111ebULL;
        hash.words[word] ^= hash.words[word] >> 31;
    }

    return hash;
}

std::string hashText(const Hash256& hash) {
    std::string result;
    result.reserve(hash.words.size() * 16);

    for (const uint64_t word : hash.words) {
        result += std::format("{:016x}", word);
    }

    return result;
}

std::string escapeJson(std::string_view value) {
    std::string result;
    result.reserve(value.size());

    for (const uint8_t character : value) {
        switch (character) {
        case '"':
            result += "\\\"";
            break;
        case '\\':
            result += "\\\\";
            break;
        case '\n':
            result += "\\n";
            break;
        case '\r':
            result += "\\r";
            break;
        case '\t':
            result += "\\t";
            break;
        default:
            result += static_cast<char>(character);
            break;
        }
    }

    return result;
}

std::string edgesJson(const Graph& graph) {
    std::string result{"["};
    bool first = true;

    for (int source = 0; source < graph.vertexCount(); ++source) {
        for (int target = 0; target < graph.vertexCount(); ++target) {
            if (!graph.hasEdge(source, target)) {
                continue;
            }

            if (!first) {
                result += ',';
            }

            first = false;
            result += std::format("[{},{}]", source, target);
        }
    }

    result += ']';
    return result;
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

} // namespace

int WlProfile::initialColor(const Graph& graph, int source, int target) const {
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

OneRoundKey WlProfile::oneRoundKey(const Graph& graph) const {
    const int vertexCount = graph.vertexCount();
    std::vector<PairDescriptor> descriptors;
    descriptors.reserve(static_cast<size_t>(vertexCount) * vertexCount);

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

StableWlResult WlProfile::stabilize(std::span<const Graph> graphs) const {
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
    std::vector<std::vector<int>> colors(graphs.size(),
                                         std::vector<int>(pairCount, 0));

    for (size_t graph = 0; graph < graphs.size(); ++graph) {
        for (int source = 0; source < vertexCount; ++source) {
            for (int target = 0; target < vertexCount; ++target) {
                colors[graph][source * vertexCount + target] =
                    initialColor(graphs[graph], source, target);
            }
        }
    }

    int distinctColorCount = 4;
    StableWlResult result;

    for (int round = 1; round <= pairCount + 2; ++round) {
        std::vector<RefinementItem> items;
        items.reserve(graphs.size() * static_cast<size_t>(pairCount));

        for (size_t graph = 0; graph < graphs.size(); ++graph) {
            for (int source = 0; source < vertexCount; ++source) {
                for (int target = 0; target < vertexCount; ++target) {
                    const int position = source * vertexCount + target;
                    RefinementDescriptor descriptor;
                    descriptor.oldColor = colors[graph][position];
                    descriptor.transitions.reserve(vertexCount);

                    for (int middle = 0; middle < vertexCount; ++middle) {
                        descriptor.transitions.emplace_back(
                            colors[graph][source * vertexCount + middle],
                            colors[graph][middle * vertexCount + target]);
                    }

                    std::ranges::sort(descriptor.transitions);
                    items.push_back({std::move(descriptor), graph, position});
                }
            }
        }

        std::ranges::sort(items, {}, &RefinementItem::descriptor);

        std::vector<std::vector<int>> next(graphs.size(),
                                           std::vector<int>(pairCount, 0));
        int color = -1;
        RefinementDescriptor previous;
        bool hasPrevious = false;

        for (const RefinementItem& item : items) {
            if (!hasPrevious || item.descriptor != previous) {
                ++color;
                previous = item.descriptor;
                hasPrevious = true;
            }

            next[item.graph][item.position] = color;
        }

        result.graphKeys.clear();
        result.graphKeys.reserve(graphs.size());

        for (const std::vector<int>& graphColors : next) {
            std::vector<int> graphKey = graphColors;
            std::ranges::sort(graphKey);
            result.graphKeys.push_back(std::move(graphKey));
        }

        result.rounds = round;

        if (uniqueGraphKeyCount(result.graphKeys) == graphs.size()) {
            result.separationRound = round;
            return result;
        }

        const int newDistinctColorCount = color + 1;
        if (newDistinctColorCount == distinctColorCount) {
            return result;
        }

        distinctColorCount = newDistinctColorCount;
        colors.swap(next);
    }

    return result;
}

int generateWlScan() {
    WlProfile profile;
    std::string line;
    size_t count = 0;

    while (std::getline(std::cin, line)) {
        const std::string record = trimDigraph6(line);
        if (record.empty()) {
            continue;
        }

        const Graph graph = parseDigraph6(record);
        const OneRoundKey key = profile.oneRoundKey(graph);
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
    std::ofstream collisionOutput(outputDirectory / "collisions.jsonl");
    std::ofstream separationOutput(outputDirectory / "separation-rounds.tsv");
    if (!collisionOutput || !separationOutput) {
        throw std::runtime_error("cannot create WL output artifacts");
    }

    std::println(separationOutput,
                 "class\tsize\tseparation_round\tstable_class_count");

    WlProfile profile;
    std::string currentHash;
    std::vector<std::string> bucket;
    size_t totalRecords = 0;
    size_t hashCollisionBuckets = 0;
    size_t collisionClasses = 0;
    size_t collisionGraphs = 0;
    size_t unresolvedClasses = 0;
    size_t unresolvedGraphs = 0;
    size_t classId = 0;

    auto flush = [&]() {
        if (bucket.size() < 2) {
            bucket.clear();
            return;
        }

        ++hashCollisionBuckets;
        std::map<OneRoundKey, std::vector<WlRecord>, OneRoundKeyLess>
            exactGroups;

        for (const std::string& record : bucket) {
            Graph graph = parseDigraph6(record);
            if (graph.vertexCount() != vertexCount) {
                throw std::runtime_error(
                    "digraph6 record has unexpected vertex count");
            }

            OneRoundKey key = profile.oneRoundKey(graph);
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

            ++collisionClasses;
            collisionGraphs += records.size();

            const auto graphs =
                records | std::views::transform([](const WlRecord& record) {
                    return record.graph;
                }) |
                std::ranges::to<std::vector<Graph>>();

            const StableWlResult result = profile.stabilize(graphs);
            const auto [remainingClasses, remainingGraphs] =
                unresolvedGraphKeys(result.graphKeys);
            unresolvedClasses += remainingClasses;
            unresolvedGraphs += remainingGraphs;

            const size_t stableClassCount =
                uniqueGraphKeyCount(result.graphKeys);
            const std::string separationText =
                result.separationRound == 0
                    ? "unresolved"
                    : std::format("{}", result.separationRound);
            const std::string separationJson =
                result.separationRound == 0
                    ? "null"
                    : std::format("{}", result.separationRound);

            std::println(separationOutput, "{}\t{}\t{}\t{}", classId,
                         records.size(), separationText, stableClassCount);

            std::print(collisionOutput,
                       "{{\"class\":{},"
                       "\"one_round_hash\":\"{}\","
                       "\"size\":{},"
                       "\"separation_round\":{},"
                       "\"stable_class_count\":{},"
                       "\"graphs\":[",
                       classId, escapeJson(currentHash), records.size(),
                       separationJson, stableClassCount);

            for (size_t index = 0; const auto& record : records) {
                if (index != 0) {
                    std::print(collisionOutput, ",");
                }

                std::print(collisionOutput, "{{\"d6\":\"{}\",\"edges\":{}}}",
                           escapeJson(record.digraph6),
                           edgesJson(record.graph));

                ++index;
            }

            std::println(collisionOutput, "]}}");
            ++classId;
        }

        bucket.clear();
    };

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
        if (!currentHash.empty() && hash != currentHash) {
            flush();
        }

        if (bucket.empty()) {
            currentHash = hash;
        }

        bucket.push_back(record);
        ++totalRecords;
    }

    flush();

    std::ofstream summaryOutput(outputDirectory / "summary.txt");

    if (!summaryOutput) {
        throw std::runtime_error("cannot create WL summary artifact");
    }

    std::print(summaryOutput,
               "total_records={}\n"
               "hash_buckets_gt1={}\n"
               "exact_one_round_collision_classes={}\n"
               "exact_one_round_collision_graphs={}\n"
               "stable_2wl_unresolved_classes={}\n"
               "stable_2wl_unresolved_graphs={}\n",
               totalRecords, hashCollisionBuckets, collisionClasses,
               collisionGraphs, unresolvedClasses, unresolvedGraphs);

    std::println(stderr,
                 "total_records={} exact_collision_classes={} "
                 "stable_unresolved_classes={}",
                 totalRecords, collisionClasses, unresolvedClasses);

    return 0;
}
