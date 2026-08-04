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
    const size_t rowIndex = static_cast<size_t>(row);
    const size_t columnIndex = static_cast<size_t>(column);
    const size_t width = static_cast<size_t>(size);
    return rowIndex * width + columnIndex;
}

IntegerMatrix transpose(const IntegerMatrix& matrix, int size) {
    const size_t width = static_cast<size_t>(size);
    IntegerMatrix out(width * width, 0);

    for (int row = 0; row < size; ++row) {
        for (int column = 0; column < size; ++column) {
            out[indexOf(column, row, size)] =
                matrix[indexOf(row, column, size)];
        }
    }

    return out;
}

IntegerMatrix multiply(const IntegerMatrix& left, const IntegerMatrix& right,
                       int size) {
    const size_t width = static_cast<size_t>(size);
    IntegerMatrix out(width * width, 0);

    for (int row = 0; row < size; ++row) {
        for (int middle = 0; middle < size; ++middle) {
            const int64_t value = left[indexOf(row, middle, size)];
            if (value == 0) {
                continue;
            }

            for (int column = 0; column < size; ++column) {
                out[indexOf(row, column, size)] +=
                    value * right[indexOf(middle, column, size)];
            }
        }
    }

    return out;
}

BigMatrix multiply(const BigMatrix& left, const BigMatrix& right, int size) {
    const size_t width = static_cast<size_t>(size);
    BigMatrix out(width * width, 0);

    for (int row = 0; row < size; ++row) {
        for (int middle = 0; middle < size; ++middle) {
            const BigInt& value = left[indexOf(row, middle, size)];
            if (value == 0) {
                continue;
            }

            for (int column = 0; column < size; ++column) {
                out[indexOf(row, column, size)] +=
                    value * right[indexOf(middle, column, size)];
            }
        }
    }

    return out;
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
    const size_t order = static_cast<size_t>(size);
    std::vector<BigInt> traces(order + 1, 0);

    for (size_t exponent = 1; exponent <= order; ++exponent) {
        BigInt trace = 0;

        for (int diagonal = 0; diagonal < size; ++diagonal) {
            trace += power[indexOf(diagonal, diagonal, size)];
        }

        traces[exponent] = trace;
        if (exponent < order) {
            power = multiply(power, base, size);
        }
    }

    std::vector<BigInt> coefficients(order + 1, 0);
    coefficients[0] = 1;

    for (size_t degree = 1; degree <= order; ++degree) {
        BigInt sum = 0;

        for (size_t exponent = 1; exponent <= degree; ++exponent) {
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
    std::string out = std::format("{}:", values.size());

    for (const int value : values) {
        out += std::format("{},", value);
    }

    return out;
}

std::string serializePolynomial(const IntegerMatrix& matrix, int size) {
    const auto coefficients = characteristicPolynomial(matrix, size);
    std::string out = std::format("{}:", size);

    for (const BigInt& coefficient : coefficients) {
        out += coefficient.str();
        out += ',';
    }

    return out;
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
    const size_t vertexSize = static_cast<size_t>(vertexCount);
    const size_t matrixSize = vertexSize * vertexSize;
    BuiltMatrices built;
    built.vertexCount = vertexCount;

    IntegerMatrix adjacency(matrixSize, 0);
    for (int source = 0; source < vertexCount; ++source) {
        for (int target = 0; target < vertexCount; ++target) {
            adjacency[indexOf(source, target, vertexCount)] =
                graph.hasEdge(source, target) ? 1 : 0;
        }
    }

    const IntegerMatrix adjTranspose = transpose(adjacency, vertexCount);
    built.adjacencyGram = multiply(adjTranspose, adjacency, vertexCount);
    const IntegerMatrix outGram =
        multiply(adjacency, adjTranspose, vertexCount);

    built.asymmetricGram.assign(matrixSize, 0);
    for (size_t i = 0; i < matrixSize; ++i) {
        built.asymmetricGram[i] = built.adjacencyGram[i] + 2 * outGram[i];
    }

    built.outLaplacian.assign(matrixSize, 0);
    built.inLaplacian.assign(matrixSize, 0);
    built.undirectedLaplacian.assign(matrixSize, 0);

    for (int row = 0; row < vertexCount; ++row) {
        int64_t outDeg = 0;
        int64_t inDeg = 0;
        int64_t undirectedDeg = 0;

        for (int column = 0; column < vertexCount; ++column) {
            outDeg += adjacency[indexOf(row, column, vertexCount)];
            inDeg += adjacency[indexOf(column, row, vertexCount)];
            if (graph.hasEdge(row, column) || graph.hasEdge(column, row)) {
                ++undirectedDeg;
            }
        }

        for (int column = 0; column < vertexCount; ++column) {
            const size_t pos = indexOf(row, column, vertexCount);
            built.outLaplacian[pos] = -adjacency[pos];
            built.inLaplacian[pos] = -adjacency[pos];
            built.undirectedLaplacian[pos] =
                -(graph.hasEdge(row, column) || graph.hasEdge(column, row) ? 1
                                                                           : 0);
        }

        built.outLaplacian[indexOf(row, row, vertexCount)] += outDeg;
        built.inLaplacian[indexOf(row, row, vertexCount)] += inDeg;
        built.undirectedLaplacian[indexOf(row, row, vertexCount)] +=
            undirectedDeg;
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
    const size_t edgeSize = static_cast<size_t>(edgeCount);
    IntegerMatrix lineAdj(edgeSize * edgeSize, 0);

    for (int first = 0; first < edgeCount; ++first) {
        for (int second = 0; second < edgeCount; ++second) {
            const size_t firstIndex = static_cast<size_t>(first);
            const size_t secondIndex = static_cast<size_t>(second);

            if (edges[firstIndex].second == edges[secondIndex].first) {
                lineAdj[indexOf(first, second, edgeCount)] = 1;
            }
        }
    }

    const IntegerMatrix lineTranspose = transpose(lineAdj, edgeCount);
    const IntegerMatrix lineInGram =
        multiply(lineTranspose, lineAdj, edgeCount);
    const IntegerMatrix lineOutGram =
        multiply(lineAdj, lineTranspose, edgeCount);

    built.edgeAsymmetricGram.assign(edgeSize * edgeSize, 0);

    for (size_t i = 0; i < built.edgeAsymmetricGram.size(); ++i) {
        built.edgeAsymmetricGram[i] = lineInGram[i] + 2 * lineOutGram[i];
    }

    return built;
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

using CollisionGroups = std::vector<std::vector<std::string>>;

CollisionGroups collectCollisions(const std::vector<GraphRecord>& records,
                                  const std::vector<SpectralKeys>& keys,
                                  size_t level) {
    std::map<std::string, std::vector<std::string>> groups;
    for (size_t i = 0; i < records.size(); ++i) {
        groups[keys[i].cumulative[level]].push_back(records[i].digraph6);
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

    for (size_t i = 0; i < collisions.size(); ++i) {
        std::print(output, "{{\"class\":{},\"size\":{},\"graphs\":[", i,
                   collisions[i].size());

        for (size_t graph = 0; graph < collisions[i].size(); ++graph) {
            if (graph != 0) {
                std::print(output, ",");
            }

            std::print(output, "\"{}\"", escapeJson(collisions[i][graph]));
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

SpectralKeys spectralKeys(const Graph& graph) {
    const BuiltMatrices built = buildMatrices(graph);
    SpectralKeys out;
    std::string key;

    appendComponent(key, "edges", std::format("{}", graph.edgeCount()));
    out.cumulative[0] = key;

    appendComponent(key, "ranks", serializeIntegers(built.rankProfile));
    out.cumulative[1] = key;

    appendComponent(
        key, "ata",
        serializePolynomial(built.adjacencyGram, built.vertexCount));
    out.cumulative[2] = key;

    appendComponent(key, "lout",
                    serializePolynomial(built.outLaplacian, built.vertexCount));
    appendComponent(key, "lin",
                    serializePolynomial(built.inLaplacian, built.vertexCount));
    out.cumulative[3] = key;

    appendComponent(
        key, "lu",
        serializePolynomial(built.undirectedLaplacian, built.vertexCount));
    out.cumulative[4] = key;

    appendComponent(
        key, "orientation",
        serializePolynomial(built.orientationSkew, built.vertexCount));
    out.cumulative[5] = key;

    appendComponent(
        key, "reachability",
        serializePolynomial(built.reachabilityGram, built.vertexCount));
    out.cumulative[6] = key;

    appendComponent(
        key, "q2",
        serializePolynomial(built.asymmetricGram, built.vertexCount));
    out.cumulative[7] = key;

    appendComponent(
        key, "edge-q2",
        serializePolynomial(built.edgeAsymmetricGram, built.edgeCount));
    out.cumulative[8] = key;

    return out;
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

    std::vector<SpectralKeys> keys;
    keys.reserve(records.size());

    for (size_t i = 0; i < records.size(); ++i) {
        const GraphRecord& record = records[i];
        keys.push_back(spectralKeys(record.graph));

        const size_t completed = i + 1;
        if (completed % 1000 == 0 || completed == records.size()) {
            std::print(stderr, "\rprofiled {} / {}", completed, records.size());
        }
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
