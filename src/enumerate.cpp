// Exhaustive DAG isomorphism-class enumeration.
//
// A DAG in topological order is a strictly upper-triangular 0/1 matrix, encoded
// as a bitmask over the n(n-1)/2 pairs (i, j), i < j, in row-major order. The
// canonical form is the lexicographically smallest n*n bit encoding over all n!
// relabelings. Output: one hex mask per line.

#include <algorithm>
#include <atomic>
#include <numeric>
#include <print>
#include <unordered_set>
#include <vector>

namespace {

constexpr int kMaxN = 8;

struct PermTable {
    // For permutation p and edge-slot b (a pair i<j), target[b] is the bit
    // position (p[i]*n + p[j]) in the n*n grid. Relabeling never reverses an
    // edge, it only moves it, so a single target per slot suffices.
    std::vector<std::array<uint8_t, kMaxN*(kMaxN - 1) / 2>> target;
    int npair = 0;
};

PermTable BuildPermTable(int n) {
    std::vector<std::pair<int, int>> pairs;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            pairs.emplace_back(i, j);
        }
    }

    PermTable t;
    t.npair = static_cast<int>(pairs.size());

    std::vector<int> p(n);
    std::iota(p.begin(), p.end(), 0);

    do {
        std::array<uint8_t, kMaxN*(kMaxN - 1) / 2> row{};

        for (int b = 0; b < t.npair; ++b) {
            const int i = pairs[b].first, j = pairs[b].second;
            row[b] = static_cast<uint8_t>(p[i] * n + p[j]);
        }

        t.target.push_back(row);
    } while (std::next_permutation(p.begin(), p.end()));

    return t;
}

// Smallest n*n-bit encoding of `mask` over all relabelings.
inline uint64_t Canonical(uint32_t mask, const PermTable& t) {
    uint64_t best = ~0ULL;

    for (const auto& row : t.target) {
        uint64_t e = 0;
        uint32_t k = mask;

        while (k) {
            const int b = __builtin_ctz(k);
            e |= 1ULL << row[b];
            k &= k - 1;
        }

        if (e < best) {
            best = e;
        }
    }

    return best;
}

} // namespace

int main(int argc, char** argv) {
    const int n = (argc > 1) ? std::atoi(argv[1]) : 7;
    if (n < 1 || n > 7) {
        std::println(stderr,
                     "n must be in 1..7 (n=8 needs 2^28 masks; out of scope)");
        return 1;
    }

    const PermTable table = BuildPermTable(n);
    const uint32_t total = 1u << table.npair;

    // Canonicalization dominates the runtime and each mask is independent.
    // Store the results by mask so the second pass can preserve the original
    // ascending-mask representative order.
    std::vector<uint64_t> canonical(total);
    std::atomic<uint32_t> completed = 0;

#ifdef _OPENMP
#pragma omp parallel for schedule(static)
#endif
    for (uint32_t mask = 0; mask < total; ++mask) {
        canonical[mask] = Canonical(mask, table);

        const uint32_t count =
            completed.fetch_add(1, std::memory_order_relaxed) + 1;

        if ((count & 0xFFFFu) == 0 || count == total) {
            std::print(stderr, "\r  canonicalized {} / {}", count, total);
        }
    }

    // One representative mask per canonical class. This pass remains serial
    // so the first mask encountered for each class is still the representative.
    std::unordered_set<uint64_t> seen;
    seen.reserve(1u << 20);
    std::vector<uint32_t> reps;

    for (uint32_t mask = 0; mask < total; ++mask) {
        if (seen.insert(canonical[mask]).second) {
            reps.push_back(mask);
        }
    }

    std::println(stderr, "\r  done: {} classes{:>30}", reps.size(), "");
    std::println("# n={}  classes={}  bit order: pairs (i,j) i<j row-major", n,
                 reps.size());

    for (const uint32_t m : reps) {
        std::println("{:x}", m);
    }

    return 0;
}
