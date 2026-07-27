// Cumulative invariant separation for all DAG isomorphism classes on n nodes.
//
// Floating-point eigenvalues cannot compare spectra for equality, and using
// exact bignum characteristic polynomials is far too slow. Instead each
// characteristic polynomial is computed exactly modulo two independent 62-bit
// primes and the residue pair is used as the spectral key.
//
// This is not really a proof of distinctness as-is: two different polynomials
// could collide mod both primes. For a k-class partition the failure
// probability is bounded by ~k^2 * d / p^2 with d the degree; at n = 7 (k
// < 2.5e5, d <= 21, p ~ 4.6e18) that is below 1e-25. Any suspected collision
// can be re-checked with GMP.

#include <algorithm>
#include <fstream>
#include <numeric>
#include <print>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#ifdef _OPENMP
#include <omp.h>
#endif

namespace {

constexpr int kMaxN = 8;
constexpr int kMaxE = kMaxN * (kMaxN - 1) / 2; // 28 at n = 8

// Two independent primes below 2^62.
constexpr uint64_t kP1 = 4611686018427387847ULL;
constexpr uint64_t kP2 = 4611686018427387817ULL;

inline uint64_t MulMod(uint64_t a, uint64_t b, uint64_t p) {
    return static_cast<uint64_t>((static_cast<__uint128_t>(a) * b) % p);
}

inline uint64_t AddMod(uint64_t a, uint64_t b, uint64_t p) {
    const uint64_t s = a + b;
    return s >= p ? s - p : s;
}

inline uint64_t SubMod(uint64_t a, uint64_t b, uint64_t p) {
    return a >= b ? a - b : a + p - b;
}

uint64_t PowMod(uint64_t a, uint64_t e, uint64_t p) {
    uint64_t r = 1;

    while (e) {
        if (e & 1) {
            r = MulMod(r, a, p);
        }

        a = MulMod(a, a, p);
        e >>= 1;
    }

    return r;
}

inline uint64_t InvMod(uint64_t a, uint64_t p) { return PowMod(a, p - 2, p); }

inline uint64_t Norm(long long v, uint64_t p) {
    long long m = v % static_cast<long long>(p);
    return static_cast<uint64_t>(m < 0 ? m + static_cast<long long>(p) : m);
}

// --- Linear algebra ---

// Determinant mod p by Gaussian elimination with partial pivoting.
uint64_t DetMod(std::vector<uint64_t> m, int n, uint64_t p) {
    uint64_t det = 1;

    for (int c = 0; c < n; ++c) {
        int piv = -1;

        for (int r = c; r < n; ++r) {
            if (m[r * n + c]) {
                piv = r;
                break;
            }
        }

        if (piv < 0) {
            return 0;
        }

        if (piv != c) {
            for (int k = 0; k < n; ++k) {
                std::swap(m[piv * n + k], m[c * n + k]);
            }

            det = SubMod(0, det, p);
        }

        const uint64_t d = m[c * n + c];
        const uint64_t di = InvMod(d, p);
        det = MulMod(det, d, p);

        for (int r = c + 1; r < n; ++r) {
            const uint64_t f = MulMod(m[r * n + c], di, p);
            if (!f) {
                continue;
            }

            for (int k = c; k < n; ++k) {
                m[r * n + k] =
                    SubMod(m[r * n + k], MulMod(f, m[c * n + k], p), p);
            }
        }
    }

    return det;
}

// Rank mod p. rank_p(M) <= rank_Q(M), with equality unless p divides every
// maximal minor; vanishingly unlikely for a fixed 62-bit prime and the small
// integer matrices here.
int RankMod(std::vector<uint64_t> m, int rows, int cols, uint64_t p) {
    int rank = 0;

    for (int c = 0; c < cols && rank < rows; ++c) {
        int piv = -1;

        for (int r = rank; r < rows; ++r) {
            if (m[r * cols + c]) {
                piv = r;
                break;
            }
        }

        if (piv < 0) {
            continue;
        }

        if (piv != rank) {
            for (int k = 0; k < cols; ++k) {
                std::swap(m[piv * cols + k], m[rank * cols + k]);
            }
        }

        const uint64_t di = InvMod(m[rank * cols + c], p);

        for (int r = rank + 1; r < rows; ++r) {
            const uint64_t f = MulMod(m[r * cols + c], di, p);
            if (!f) {
                continue;
            }

            for (int k = c; k < cols; ++k) {
                m[r * cols + k] = SubMod(m[r * cols + k],
                                         MulMod(f, m[rank * cols + k], p), p);
            }
        }

        ++rank;
    }

    return rank;
}

// Characteristic polynomial of M mod p, ascending powers, degree n.
//
// Evaluate det(xI - M) at x = 0..n, then interpolate. det is O(n^3) and there
// are n+1 points, so O(n^4), trivial for n <= 21 and free of the pivoting
// subtleties of a Hessenberg reduction over a finite field.
std::vector<uint64_t> CharPolyMod(const std::vector<uint64_t>& M, int n,
                                  uint64_t p) {
    std::vector<uint64_t> xs(n + 1), ys(n + 1);
    std::vector<uint64_t> work(static_cast<size_t>(n) * n);

    for (int t = 0; t <= n; ++t) {
        const uint64_t x = static_cast<uint64_t>(t);
        xs[t] = x;

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                work[i * n + j] = (i == j) ? SubMod(x, M[i * n + j], p)
                                           : SubMod(0, M[i * n + j], p);
            }
        }

        ys[t] = DetMod(work, n, p);
    }

    // Newton divided differences.
    std::vector<uint64_t> c = ys;
    for (int j = 1; j <= n; ++j) {
        for (int i = n; i >= j; --i) {
            const uint64_t num = SubMod(c[i], c[i - 1], p);
            const uint64_t den = SubMod(xs[i], xs[i - j], p);
            c[i] = MulMod(num, InvMod(den, p), p);
        }
    }

    // Horner in Newton form: poly <- poly * (x - xs[k]) + c[k], descending k.
    std::vector<uint64_t> poly(n + 1, 0), tmp(n + 1, 0);
    poly[0] = c[n];

    for (int k = n - 1; k >= 0; --k) {
        std::fill(tmp.begin(), tmp.end(), 0);

        for (int i = 0; i < n; ++i) {
            if (poly[i]) {
                tmp[i + 1] = AddMod(tmp[i + 1], poly[i], p); // x * poly
                tmp[i] = SubMod(tmp[i], MulMod(xs[k], poly[i], p), p);
            }
        }

        tmp[0] = AddMod(tmp[0], c[k], p);
        poly.swap(tmp);
    }

    return poly;
}

// --- Hashing ---

struct Hash128 {
    uint64_t a = 1469598103934665603ULL;
    uint64_t b = 1099511628211ULL;

    inline void Mix(uint64_t v) {
        a ^= v + 0x9e3779b97f4a7c15ULL + (a << 6) + (a >> 2);
        b = b * 0x100000001b3ULL ^ v;
        b ^= b >> 29;
    }

    inline uint64_t Fold() const {
        uint64_t h = a ^ (b * 0xff51afd7ed558ccdULL);
        h ^= h >> 33;
        h *= 0xc4ceb9fe1a85ec53ULL;
        h ^= h >> 33;
        return h;
    }
};

// --- Graph handling ---

struct Graph {
    int n = 0;
    std::array<int8_t, kMaxN * kMaxN> A{};
    inline int8_t at(int i, int j) const { return A[i * n + j]; }
};

std::vector<std::pair<int, int>> UpperPairs(int n) {
    std::vector<std::pair<int, int>> v;

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            v.emplace_back(i, j);
        }
    }

    return v;
}

Graph FromMask(uint32_t mask, int n,
               const std::vector<std::pair<int, int>>& pairs) {
    Graph g;
    g.n = n;

    for (size_t b = 0; b < pairs.size(); ++b) {
        if (mask >> b & 1) {
            g.A[pairs[b].first * n + pairs[b].second] = 1;
        }
    }

    return g;
}

// Canonical form: smallest n*n bit encoding over all relabelings.
struct Canonizer {
    int n;
    std::vector<std::array<uint8_t, kMaxE>> target;
    int npair;

    explicit Canonizer(int n_) : n(n_) {
        const auto pairs = UpperPairs(n);
        npair = static_cast<int>(pairs.size());

        std::vector<int> p(n);
        std::iota(p.begin(), p.end(), 0);

        do {
            std::array<uint8_t, kMaxE> row{};

            for (int b = 0; b < npair; ++b) {
                row[b] = static_cast<uint8_t>(p[pairs[b].first] * n +
                                              p[pairs[b].second]);
            }

            target.push_back(row);
        } while (std::next_permutation(p.begin(), p.end()));
    }

    inline uint64_t operator()(uint32_t mask) const {
        uint64_t best = ~0ULL;

        for (const auto& row : target) {
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
};

// --- Invariants ---

using Mat = std::vector<uint64_t>;

Mat ToMod(const std::vector<long long>& src, uint64_t p) {
    Mat out(src.size());
    for (size_t i = 0; i < src.size(); ++i) {
        out[i] = Norm(src[i], p);
    }

    return out;
}

// Integer matrices we need, built once per graph.
struct Built {
    int n;
    std::vector<long long> AtA;
    std::vector<long long> Lout;
    std::vector<long long> Lin;
    std::vector<long long> Lu;
    std::vector<long long> Skew;
    std::vector<long long> RtR;
    std::vector<long long> Q2;
    std::vector<long long> Q2edge;
    int nedge = 0;
    std::vector<int> rankprofile;
};

Built Build(const Graph& g, uint64_t rank_prime) {
    const int n = g.n;
    Built b;
    b.n = n;

    const auto idx = [n](int i, int j) { return i * n + j; };

    std::vector<long long> A(n * n, 0);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            A[idx(i, j)] = g.at(i, j);
        }
    }

    const auto matmul = [n](const std::vector<long long>& X,
                            const std::vector<long long>& Y) {
        std::vector<long long> Z(n * n, 0);

        for (int i = 0; i < n; ++i) {
            for (int k = 0; k < n; ++k) {
                const long long xv = X[i * n + k];
                if (!xv) {
                    continue;
                }

                for (int j = 0; j < n; ++j) {
                    Z[i * n + j] += xv * Y[k * n + j];
                }
            }
        }

        return Z;
    };

    const auto transpose = [n](const std::vector<long long>& X) {
        std::vector<long long> Z(n * n);

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                Z[j * n + i] = X[i * n + j];
            }
        }

        return Z;
    };

    const auto At = transpose(A);
    b.AtA = matmul(At, A);
    const auto AAt = matmul(A, At);

    b.Q2.assign(n * n, 0);
    for (int i = 0; i < n * n; ++i) {
        b.Q2[i] = b.AtA[i] + 2 * AAt[i];
    }

    b.Lout.assign(n * n, 0);
    b.Lin.assign(n * n, 0);
    b.Lu.assign(n * n, 0);

    for (int i = 0; i < n; ++i) {
        long long ro = 0;
        long long ci = 0;
        long long ru = 0;

        for (int j = 0; j < n; ++j) {
            ro += A[idx(i, j)];
            ci += A[idx(j, i)];
            ru += (A[idx(i, j)] || A[idx(j, i)]) ? 1 : 0;
        }

        for (int j = 0; j < n; ++j) {
            b.Lout[idx(i, j)] = -A[idx(i, j)];
            b.Lin[idx(i, j)] = -A[idx(i, j)];
            b.Lu[idx(i, j)] = -((A[idx(i, j)] || A[idx(j, i)]) ? 1 : 0);
        }

        b.Lout[idx(i, i)] += ro;
        b.Lin[idx(i, i)] += ci;
        b.Lu[idx(i, i)] += ru;
    }

    b.Skew.assign(n * n, 0);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            b.Skew[idx(i, j)] = A[idx(i, j)] - A[idx(j, i)];
        }
    }

    // Reachability: transitive closure excluding zero-length paths.
    std::vector<long long> R(n * n, 0);
    {
        std::vector<char> reach(n * n, 0);

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                reach[idx(i, j)] = A[idx(i, j)] ? 1 : 0;
            }
        }

        for (int k = 0; k < n; ++k) {
            for (int i = 0; i < n; ++i) {
                if (!reach[idx(i, k)]) {
                    continue;
                }

                for (int j = 0; j < n; ++j) {
                    if (reach[idx(k, j)]) {
                        reach[idx(i, j)] = 1;
                    }
                }
            }
        }

        for (int i = 0; i < n * n; ++i) {
            R[i] = reach[i];
        }
    }
    b.RtR = matmul(transpose(R), R);

    // Rank profile of A, A^2, ... down to zero.
    {
        std::vector<long long> M = A;

        for (int step = 0; step < n; ++step) {
            const Mat mm = ToMod(M, rank_prime);
            const int rank = RankMod(mm, n, n, rank_prime);
            b.rankprofile.push_back(rank);

            if (rank == 0) {
                break;
            }

            M = matmul(M, A);
        }
    }

    // Directed line graph, then Q_2 on it.
    {
        std::vector<std::pair<int, int>> edges;

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                for (int edge = 0; edge < g.at(i, j); ++edge) {
                    edges.emplace_back(i, j);
                }
            }
        }

        const int edge_count = static_cast<int>(edges.size());
        b.nedge = edge_count;

        if (edge_count > 0) {
            std::vector<long long> C(
                static_cast<size_t>(edge_count) * edge_count, 0);

            for (int a = 0; a < edge_count; ++a) {
                for (int c = 0; c < edge_count; ++c) {
                    if (edges[a].second == edges[c].first) {
                        C[a * edge_count + c] = 1;
                    }
                }
            }

            std::vector<long long> Ct(static_cast<size_t>(edge_count) *
                                      edge_count);
            for (int i = 0; i < edge_count; ++i) {
                for (int j = 0; j < edge_count; ++j) {
                    Ct[j * edge_count + i] = C[i * edge_count + j];
                }
            }

            const auto multiply_edges = [edge_count](
                                            const std::vector<long long>& X,
                                            const std::vector<long long>& Y) {
                std::vector<long long> Z(
                    static_cast<size_t>(edge_count) * edge_count, 0);

                for (int i = 0; i < edge_count; ++i) {
                    for (int k = 0; k < edge_count; ++k) {
                        const long long xv = X[i * edge_count + k];
                        if (!xv) {
                            continue;
                        }

                        for (int j = 0; j < edge_count; ++j) {
                            Z[i * edge_count + j] += xv * Y[k * edge_count + j];
                        }
                    }
                }

                return Z;
            };

            const auto CtC = multiply_edges(Ct, C);
            const auto CCt = multiply_edges(C, Ct);
            b.Q2edge.assign(static_cast<size_t>(edge_count) * edge_count, 0);

            for (int i = 0; i < edge_count * edge_count; ++i) {
                b.Q2edge[i] = CtC[i] + 2 * CCt[i];
            }
        }
    }

    return b;
}

void MixPoly(Hash128& h, const std::vector<long long>& M, int dim) {
    if (dim == 0) {
        h.Mix(0xdeadbeefULL);
        return;
    }

    for (const uint64_t p : {kP1, kP2}) {
        const auto poly = CharPolyMod(ToMod(M, p), dim, p);
        for (const uint64_t c : poly) {
            h.Mix(c);
        }
    }
}

} // namespace

int main(int argc, char** argv) {
    const int n = (argc > 1) ? std::atoi(argv[1]) : 6;
    const char* catalog = (argc > 2) ? argv[2] : nullptr;

    if (n < 1 || n > kMaxN) {
        std::println(stderr, "n out of range");
        return 1;
    }

    const auto pairs = UpperPairs(n);
    std::vector<uint32_t> masks;

    if (catalog) {
        std::ifstream in(catalog);
        if (!in) {
            std::println(stderr, "cannot open {}", catalog);
            return 1;
        }

        std::string line;
        while (std::getline(in, line)) {
            if (line.empty() || line[0] == '#') {
                continue;
            }

            masks.push_back(
                static_cast<uint32_t>(std::stoul(line, nullptr, 16)));
        }

        std::println(stderr, "loaded {} classes from {}", masks.size(),
                     catalog);
    } else {
        const Canonizer canon(n);
        const uint32_t total = 1u << pairs.size();
        std::unordered_set<uint64_t> seen;
        seen.reserve(1u << 20);

        for (uint32_t mask = 0; mask < total; ++mask) {
            const uint64_t canonical_mask = canon(mask);
            if (seen.insert(canonical_mask).second) {
                masks.push_back(mask);
            }
        }

        std::println(stderr, "enumerated {} classes", masks.size());
    }

    const size_t class_count = masks.size();

    // Six cumulative levels, matching findings-2's table rows.
    constexpr int kLevels = 6;
    std::vector<std::vector<uint64_t>> keys(kLevels);
    for (auto& level_keys : keys) {
        level_keys.resize(class_count);
    }

#ifdef _OPENMP
    std::println(stderr, "threads: {}", omp_get_max_threads());
#endif

#ifdef _OPENMP
#pragma omp parallel for schedule(dynamic, 256)
#endif
    for (size_t i = 0; i < class_count; ++i) {
        const Graph g = FromMask(masks[i], n, pairs);
        const Built b = Build(g, kP1);

        int edge_count = 0;
        for (int source = 0; source < n; ++source) {
            for (int target = 0; target < n; ++target) {
                edge_count += g.at(source, target);
            }
        }

        Hash128 h;
        h.Mix(static_cast<uint64_t>(edge_count));
        keys[0][i] = h.Fold();

        for (const int rank : b.rankprofile) {
            h.Mix(static_cast<uint64_t>(rank) + 1);
        }

        h.Mix(0xAAAA);
        keys[1][i] = h.Fold();

        MixPoly(h, b.AtA, n);
        keys[2][i] = h.Fold();

        MixPoly(h, b.Lout, n);
        MixPoly(h, b.Lin, n);
        keys[3][i] = h.Fold();

        MixPoly(h, b.Lu, n);
        MixPoly(h, b.Skew, n);
        MixPoly(h, b.RtR, n);
        MixPoly(h, b.Q2, n);
        keys[4][i] = h.Fold();

        h.Mix(static_cast<uint64_t>(b.nedge) + 1);
        MixPoly(h, b.Q2edge, b.nedge);
        keys[5][i] = h.Fold();
    }

    static const char* kLabels[kLevels] = {
        "edge count",
        "(+) rank profile of A^k",
        "(+) singular spectrum of A",
        "(+) in/out Laplacian spectra",
        "(+) full node profile Phi_0",
        "(+) edge-level lift Q_2(L(G))",
    };

    std::println("n = {}:  {} non-isomorphic DAGs", n, class_count);
    std::println();
    std::println("  {:<32} {:>12}", "cumulative invariant", "classes");
    std::println("  {}", std::string(46, '-'));

    size_t node_level = 0;
    size_t full_level = 0;

    for (int level = 0; level < kLevels; ++level) {
        const std::unordered_set<uint64_t> unique_keys(keys[level].begin(),
                                                       keys[level].end());
        std::println("  {:<32} {:>12}", kLabels[level], unique_keys.size());

        if (level == 4) {
            node_level = unique_keys.size();
        }
        if (level == 5) {
            full_level = unique_keys.size();
        }
    }

    // Dump surviving collision groups so the second pass can re-check them in
    // exact arithmetic instead of re-enumerating. DUMP_LEVEL selects which
    // cumulative stage to report: 4 = node profile Phi_0, 5 = augmented
    // (default).
    if (const char* dump = std::getenv("DUMP_COLLISIONS")) {
        const char* dump_level = std::getenv("DUMP_LEVEL");
        const int level = dump_level ? std::atoi(dump_level) : 5;
        std::unordered_map<uint64_t, std::vector<uint32_t>> groups;

        for (size_t i = 0; i < class_count; ++i) {
            groups[keys[level][i]].push_back(masks[i]);
        }

        std::vector<std::vector<uint32_t>> collisions;
        for (const auto& entry : groups) {
            const auto& group = entry.second;
            if (group.size() > 1) {
                collisions.push_back(group);
            }
        }

        // Deterministic order, so the file is reproducible byte-for-byte.
        for (auto& group : collisions) {
            std::sort(group.begin(), group.end());
        }

        std::sort(collisions.begin(), collisions.end());

        FILE* file = std::fopen(dump, "w");
        std::println(file, "# n={} level={} collision groups (hex masks)", n,
                     level);

        for (const auto& group : collisions) {
            for (size_t i = 0; i < group.size(); ++i) {
                std::print(file, "{}{:x}", i ? " " : "", group[i]);
            }

            std::println(file);
        }

        std::fclose(file);
        std::println(stderr, "{} collision groups (level {}) written to {}",
                     collisions.size(), level, dump);
    }

    std::println();
    if (node_level == class_count) {
        std::println("  node-level profile separates all {} classes",
                     class_count);
    } else {
        std::println("  node-level profile leaves {} collision(s)",
                     class_count - node_level);
    }

    if (full_level == class_count) {
        std::println("  augmented profile separates all {} classes  -- PASS",
                     class_count);
    } else {
        std::println("  augmented profile STILL leaves {} collision(s)",
                     class_count - full_level);
    }

    // Machine-readable form.
    if (const char* json_path = std::getenv("EMIT_JSON")) {
        FILE* file = std::fopen(json_path, "w");
        std::print(file,
                   "{{\n  \"n\": {},\n  \"classes\": {},\n  \"levels\": [\n", n,
                   class_count);

        for (int level = 0; level < kLevels; ++level) {
            const std::unordered_set<uint64_t> unique_keys(keys[level].begin(),
                                                           keys[level].end());
            std::println(file, "    {{\"label\": \"{}\", \"classes\": {}}}{}",
                         kLabels[level], unique_keys.size(),
                         level + 1 < kLevels ? "," : "");
        }

        std::println(file,
                     "  ],\n  \"node_level_classes\": {},\n"
                     "  \"augmented_classes\": {}\n}}",
                     node_level, full_level);
        std::fclose(file);
        std::println(stderr, "json written to {}", json_path);
    }

    return 0;
}
