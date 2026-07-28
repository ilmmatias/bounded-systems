#include "spectral_profile.hxx"

#include "digraph6.hxx"

#include <algorithm>
#include <array>
#include <boost/multiprecision/cpp_int.hpp>
#include <cstdint>
#include <filesystem>
#include <format>
#include <fstream>
#include <iostream>
#include <map>
#include <print>
#include <stdexcept>
#include <string>
#include <string_view>
#include <unordered_set>
#include <utility>
#include <vector>

namespace {

using BigInt = boost::multiprecision::cpp_int;
using IntegerMatrix = std::vector<int64_t>;
using BigMatrix = std::vector<BigInt>;

struct GraphRecord {
    std::string digraph6;
    Graph graph;
};

struct BuiltMatrices {
    int vertexCount = 0;
    int edgeCount = 0;

    IntegerMatrix adjacencyGram;
    IntegerMatrix outLaplacian;
    IntegerMatrix inLaplacian;
    IntegerMatrix undirectedLaplacian;
    IntegerMatrix orientationSkew;
    IntegerMatrix reachabilityGram;
    IntegerMatrix asymmetricGram;
    IntegerMatrix edgeAsymmetricGram;

    std::vector<int> rankProfile;
};

size_t indexOf(int row, int column, int size) {
    return static_cast<size_t>(row) * size + column;
}

IntegerMatrix transpose(const IntegerMatrix& matrix, int size) {
    IntegerMatrix result(static_cast<size_t>(size) * size, 0);

    for (int row = 0; row < size; ++row) {
        for (int column = 0; column < size; ++column) {
            result[indexOf(column, row, size)] =
                matrix[indexOf(row, column, size)];
        }
    }

    return result;
}

IntegerMatrix multiply(const IntegerMatrix& left, const IntegerMatrix& right,
                       int size) {
    IntegerMatrix result(static_cast<size_t>(size) * size, 0);

    for (int row = 0; row < size; ++row) {
        for (int middle = 0; middle < size; ++middle) {
            const int64_t value = left[indexOf(row, middle, size)];
            if (value == 0) {
                continue;
            }

            for (int column = 0; column < size; ++column) {
                result[indexOf(row, column, size)] +=
                    value * right[indexOf(middle, column, size)];
            }
        }
    }

    return result;
}

BigMatrix multiply(const BigMatrix& left, const BigMatrix& right, int size) {
    BigMatrix result(static_cast<size_t>(size) * size, 0);

    for (int row = 0; row < size; ++row) {
        for (int middle = 0; middle < size; ++middle) {
            const BigInt& value = left[indexOf(row, middle, size)];
            if (value == 0) {
                continue;
            }

            for (int column = 0; column < size; ++column) {
                result[indexOf(row, column, size)] +=
                    value * right[indexOf(middle, column, size)];
            }
        }
    }

    return result;
}

int exactRank(const IntegerMatrix& matrix, int rows, int columns) {
    std::vector<BigInt> work(matrix.begin(), matrix.end());
    int rank = 0;

    for (int column = 0; column < columns && rank < rows; ++column) {
        int pivot = -1;

        for (int row = rank; row < rows; ++row) {
            if (work[indexOf(row, column, columns)] != 0) {
                pivot = row;
                break;
            }
        }

        if (pivot < 0) {
            continue;
        }

        if (pivot != rank) {
            for (int current = 0; current < columns; ++current) {
                std::swap(work[indexOf(pivot, current, columns)],
                          work[indexOf(rank, current, columns)]);
            }
        }

        const BigInt pivotValue = work[indexOf(rank, column, columns)];

        for (int row = rank + 1; row < rows; ++row) {
            const BigInt factor = work[indexOf(row, column, columns)];
            if (factor == 0) {
                continue;
            }

            for (int current = column; current < columns; ++current) {
                work[indexOf(row, current, columns)] =
                    pivotValue * work[indexOf(row, current, columns)] -
                    factor * work[indexOf(rank, current, columns)];
            }
        }

        ++rank;
    }

    return rank;
}

std::vector<BigInt> characteristicPolynomial(const IntegerMatrix& matrix,
                                             int size) {
    if (size == 0) {
        return {BigInt{1}};
    }

    BigMatrix base(matrix.begin(), matrix.end());
    BigMatrix power = base;
    std::vector<BigInt> traces(static_cast<size_t>(size) + 1, 0);

    for (int exponent = 1; exponent <= size; ++exponent) {
        BigInt trace = 0;
        for (int diagonal = 0; diagonal < size; ++diagonal) {
            trace += power[indexOf(diagonal, diagonal, size)];
        }

        traces[exponent] = trace;
        if (exponent < size) {
            power = multiply(power, base, size);
        }
    }

    std::vector<BigInt> coefficients(static_cast<size_t>(size) + 1, 0);
    coefficients[0] = 1;

    for (int degree = 1; degree <= size; ++degree) {
        BigInt sum = 0;
        for (int exponent = 1; exponent <= degree; ++exponent) {
            sum += coefficients[degree - exponent] * traces[exponent];
        }

        const BigInt divisor = degree;
        if (sum % divisor != 0) {
            throw std::runtime_error("non-integral characteristic coefficient");
        }

        coefficients[degree] = -sum / divisor;
    }

    return coefficients;
}

std::string serializeIntegers(const std::vector<int>& values) {
    std::string result = std::format("{}:", values.size());

    for (const int value : values) {
        result += std::format("{},", value);
    }

    return result;
}

std::string serializePolynomial(const IntegerMatrix& matrix, int size) {
    const auto coefficients = characteristicPolynomial(matrix, size);
    std::string result = std::format("{}:", size);

    for (const BigInt& coefficient : coefficients) {
        result += coefficient.str();
        result += ',';
    }

    return result;
}

void appendComponent(std::string& key, std::string_view name,
                     std::string_view value) {
    key += '|';
    key += name;
    key += '=';
    key += std::format("{}:", value.size());
    key += value;
}

BuiltMatrices buildMatrices(const Graph& graph) {
    const int vertexCount = graph.vertexCount();
    const size_t matrixSize = static_cast<size_t>(vertexCount) * vertexCount;
    BuiltMatrices built;
    built.vertexCount = vertexCount;

    IntegerMatrix adjacency(matrixSize, 0);
    for (int source = 0; source < vertexCount; ++source) {
        for (int target = 0; target < vertexCount; ++target) {
            adjacency[indexOf(source, target, vertexCount)] =
                graph.hasEdge(source, target) ? 1 : 0;
        }
    }

    const IntegerMatrix adjacencyTranspose = transpose(adjacency, vertexCount);
    built.adjacencyGram = multiply(adjacencyTranspose, adjacency, vertexCount);
    const IntegerMatrix outgoingGram =
        multiply(adjacency, adjacencyTranspose, vertexCount);

    built.asymmetricGram.assign(matrixSize, 0);
    for (size_t current = 0; current < matrixSize; ++current) {
        built.asymmetricGram[current] =
            built.adjacencyGram[current] + 2 * outgoingGram[current];
    }

    built.outLaplacian.assign(matrixSize, 0);
    built.inLaplacian.assign(matrixSize, 0);
    built.undirectedLaplacian.assign(matrixSize, 0);

    for (int row = 0; row < vertexCount; ++row) {
        int64_t outDegree = 0;
        int64_t inDegree = 0;
        int64_t undirectedDegree = 0;

        for (int column = 0; column < vertexCount; ++column) {
            outDegree += adjacency[indexOf(row, column, vertexCount)];
            inDegree += adjacency[indexOf(column, row, vertexCount)];
            if (graph.hasEdge(row, column) || graph.hasEdge(column, row)) {
                ++undirectedDegree;
            }
        }

        for (int column = 0; column < vertexCount; ++column) {
            const size_t current = indexOf(row, column, vertexCount);
            built.outLaplacian[current] = -adjacency[current];
            built.inLaplacian[current] = -adjacency[current];
            built.undirectedLaplacian[current] =
                -(graph.hasEdge(row, column) || graph.hasEdge(column, row) ? 1
                                                                           : 0);
        }

        built.outLaplacian[indexOf(row, row, vertexCount)] += outDegree;
        built.inLaplacian[indexOf(row, row, vertexCount)] += inDegree;
        built.undirectedLaplacian[indexOf(row, row, vertexCount)] +=
            undirectedDegree;
    }

    built.orientationSkew.assign(matrixSize, 0);
    for (int row = 0; row < vertexCount; ++row) {
        for (int column = 0; column < vertexCount; ++column) {
            built.orientationSkew[indexOf(row, column, vertexCount)] =
                adjacency[indexOf(row, column, vertexCount)] -
                adjacency[indexOf(column, row, vertexCount)];
        }
    }

    IntegerMatrix reachability(matrixSize, 0);
    for (int row = 0; row < vertexCount; ++row) {
        for (int column = 0; column < vertexCount; ++column) {
            reachability[indexOf(row, column, vertexCount)] =
                adjacency[indexOf(row, column, vertexCount)];
        }
    }

    for (int middle = 0; middle < vertexCount; ++middle) {
        for (int source = 0; source < vertexCount; ++source) {
            if (reachability[indexOf(source, middle, vertexCount)] == 0) {
                continue;
            }

            for (int target = 0; target < vertexCount; ++target) {
                if (reachability[indexOf(middle, target, vertexCount)] != 0) {
                    reachability[indexOf(source, target, vertexCount)] = 1;
                }
            }
        }
    }

    built.reachabilityGram = multiply(transpose(reachability, vertexCount),
                                      reachability, vertexCount);

    IntegerMatrix power = adjacency;

    for (int exponent = 1; exponent <= vertexCount; ++exponent) {
        const int rank = exactRank(power, vertexCount, vertexCount);
        built.rankProfile.push_back(rank);

        if (rank == 0) {
            break;
        }

        power = multiply(power, adjacency, vertexCount);
    }

    std::vector<std::pair<int, int>> edges;

    for (int source = 0; source < vertexCount; ++source) {
        for (int target = 0; target < vertexCount; ++target) {
            if (graph.hasEdge(source, target)) {
                edges.emplace_back(source, target);
            }
        }
    }

    built.edgeCount = static_cast<int>(edges.size());

    if (built.edgeCount == 0) {
        return built;
    }

    const int edgeCount = built.edgeCount;
    IntegerMatrix lineAdjacency(static_cast<size_t>(edgeCount) * edgeCount, 0);

    for (int first = 0; first < edgeCount; ++first) {
        for (int second = 0; second < edgeCount; ++second) {
            if (edges[first].second == edges[second].first) {
                lineAdjacency[indexOf(first, second, edgeCount)] = 1;
            }
        }
    }

    const IntegerMatrix lineTranspose = transpose(lineAdjacency, edgeCount);
    const IntegerMatrix lineIncomingGram =
        multiply(lineTranspose, lineAdjacency, edgeCount);
    const IntegerMatrix lineOutgoingGram =
        multiply(lineAdjacency, lineTranspose, edgeCount);

    built.edgeAsymmetricGram.assign(static_cast<size_t>(edgeCount) * edgeCount,
                                    0);

    for (size_t current = 0; current < built.edgeAsymmetricGram.size();
         ++current) {
        built.edgeAsymmetricGram[current] =
            lineIncomingGram[current] + 2 * lineOutgoingGram[current];
    }

    return built;
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

using CollisionGroups = std::vector<std::vector<std::string>>;

CollisionGroups collectCollisions(const std::vector<GraphRecord>& records,
                                  const std::vector<SpectralKeys>& keys,
                                  size_t level) {
    std::map<std::string, std::vector<std::string>> groups;
    for (size_t index = 0; index < records.size(); ++index) {
        groups[keys[index].cumulative[level]].push_back(
            records[index].digraph6);
    }

    CollisionGroups collisions;

    for (auto& entry : groups) {
        auto& group = entry.second;
        if (group.size() < 2) {
            continue;
        }

        std::ranges::sort(group);
        collisions.push_back(std::move(group));
    }

    std::ranges::sort(collisions);
    return collisions;
}

void writeCollisionFile(const std::filesystem::path& path,
                        const CollisionGroups& collisions) {
    std::ofstream output(path);
    if (!output) {
        throw std::runtime_error(
            std::format("cannot create collision artifact: {}", path.string()));
    }

    for (size_t index = 0; index < collisions.size(); ++index) {
        std::print(output, "{{\"class\":{},\"size\":{},\"graphs\":[", index,
                   collisions[index].size());

        for (size_t graph = 0; graph < collisions[index].size(); ++graph) {
            if (graph != 0) {
                std::print(output, ",");
            }

            std::print(output, "\"{}\"", escapeJson(collisions[index][graph]));
        }

        std::println(output, "]}}");
    }
}

constexpr std::array<std::string_view, kSpectralLevelCount> kLevelLabels = {
    "edge count",
    "(+) ranks of A, A^2, ...",
    "(+) singular spectrum of A",
    "(+) in/out Laplacian spectra",
    "(+) underlying Laplacian spectrum",
    "(+) Hermitian orientation spectrum",
    "(+) reachability singular spectrum",
    "(+) asymmetric Gram spectrum Q_2",
    "(+) edge-level lift Q_2(L(G))",
};

void writeSummary(const std::filesystem::path& path, int vertexCount,
                  size_t graphCount,
                  const std::array<size_t, kSpectralLevelCount>& counts,
                  const CollisionGroups& nodeCollisions,
                  const CollisionGroups& fullCollisions) {
    std::ofstream output(path);
    if (!output) {
        throw std::runtime_error(
            std::format("cannot create summary artifact: {}", path.string()));
    }

    std::print(output,
               "n = {}:  {} non-isomorphic DAGs\n\n"
               "  cumulative invariant                  classes\n"
               "  ----------------------------------------------\n",
               vertexCount, graphCount);

    for (size_t level = 0; level < kSpectralLevelCount; ++level) {
        std::println(output, "  {:<36}{}", kLevelLabels[level], counts[level]);
    }

    std::print(output,
               "\nnode-level collision classes: {}\n"
               "augmented collision classes: {}\n",
               nodeCollisions.size(), fullCollisions.size());
}

void writeTableJson(const std::filesystem::path& path, int vertexCount,
                    size_t graphCount,
                    const std::array<size_t, kSpectralLevelCount>& counts,
                    const CollisionGroups& nodeCollisions,
                    const CollisionGroups& fullCollisions) {
    std::ofstream output(path);
    if (!output) {
        throw std::runtime_error(
            std::format("cannot create JSON artifact: {}", path.string()));
    }

    std::print(output,
               "{{\n"
               "  \"n\": {},\n"
               "  \"classes\": {},\n"
               "  \"levels\": [\n",
               vertexCount, graphCount);

    for (size_t level = 0; level < kSpectralLevelCount; ++level) {
        std::print(output, "    {{\"label\": \"{}\", \"classes\": {}}}{}\n",
                   escapeJson(kLevelLabels[level]), counts[level],
                   level + 1 == kSpectralLevelCount ? "" : ",");
    }

    std::print(output,
               "  ],\n"
               "  \"node_collision_classes\": {},\n"
               "  \"augmented_collision_classes\": {}\n"
               "}}\n",
               nodeCollisions.size(), fullCollisions.size());
}

} // namespace

SpectralKeys SpectralProfile::keys(const Graph& graph) const {
    const BuiltMatrices built = buildMatrices(graph);
    SpectralKeys result;
    std::string key;

    appendComponent(key, "edges", std::format("{}", graph.edgeCount()));
    result.cumulative[0] = key;

    appendComponent(key, "ranks", serializeIntegers(built.rankProfile));
    result.cumulative[1] = key;

    appendComponent(
        key, "ata",
        serializePolynomial(built.adjacencyGram, built.vertexCount));
    result.cumulative[2] = key;

    appendComponent(key, "lout",
                    serializePolynomial(built.outLaplacian, built.vertexCount));
    appendComponent(key, "lin",
                    serializePolynomial(built.inLaplacian, built.vertexCount));
    result.cumulative[3] = key;

    appendComponent(
        key, "lu",
        serializePolynomial(built.undirectedLaplacian, built.vertexCount));
    result.cumulative[4] = key;

    appendComponent(
        key, "orientation",
        serializePolynomial(built.orientationSkew, built.vertexCount));
    result.cumulative[5] = key;

    appendComponent(
        key, "reachability",
        serializePolynomial(built.reachabilityGram, built.vertexCount));
    result.cumulative[6] = key;

    appendComponent(
        key, "q2",
        serializePolynomial(built.asymmetricGram, built.vertexCount));
    result.cumulative[7] = key;

    appendComponent(
        key, "edge-q2",
        serializePolynomial(built.edgeAsymmetricGram, built.edgeCount));
    result.cumulative[8] = key;

    return result;
}

int generateSpectralArtifacts(int vertexCount,
                              const std::filesystem::path& outputDirectory) {
    if (vertexCount < 1 || vertexCount > 6) {
        throw std::invalid_argument(
            "spectral generation supports vertex count 1..6");
    }

    std::filesystem::create_directories(outputDirectory);
    std::vector<GraphRecord> records;
    std::string line;

    while (std::getline(std::cin, line)) {
        const std::string record = trimDigraph6(line);
        if (record.empty()) {
            continue;
        }

        Graph graph = parseDigraph6(record);
        if (graph.vertexCount() != vertexCount) {
            throw std::runtime_error(
                "digraph6 record has unexpected vertex count");
        }

        records.push_back({
            .digraph6 = record,
            .graph = std::move(graph),
        });
    }

    std::println(stderr, "loaded {} DAG records", records.size());

    SpectralProfile profile;
    std::vector<SpectralKeys> keys;
    keys.reserve(records.size());

    for (size_t index = 0; const auto& record : records) {
        keys.push_back(profile.keys(record.graph));

        const auto completed = static_cast<size_t>(index + 1);
        if (completed % 1000 == 0 || completed == records.size()) {
            std::print(stderr, "\rprofiled {} / {}", completed, records.size());
        }

        ++index;
    }

    std::println(stderr);

    std::array<size_t, kSpectralLevelCount> counts{};

    for (size_t level = 0; level < kSpectralLevelCount; ++level) {
        std::unordered_set<std::string> unique;
        unique.reserve(records.size());
        for (const SpectralKeys& graphKeys : keys) {
            unique.insert(graphKeys.cumulative[level]);
        }

        counts[level] = unique.size();
    }

    const CollisionGroups nodeCollisions = collectCollisions(records, keys, 7);
    const CollisionGroups fullCollisions = collectCollisions(records, keys, 8);

    writeSummary(outputDirectory / "summary.txt", vertexCount, records.size(),
                 counts, nodeCollisions, fullCollisions);
    writeTableJson(outputDirectory / "table.json", vertexCount, records.size(),
                   counts, nodeCollisions, fullCollisions);
    writeCollisionFile(outputDirectory / "node-collisions.jsonl",
                       nodeCollisions);
    writeCollisionFile(outputDirectory / "full-collisions.jsonl",
                       fullCollisions);

    return 0;
}
