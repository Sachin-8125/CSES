#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <chrono>

using namespace std;

int n;
vector<long long> x;
vector<long long> rem_sum;
long long ans_maskA = 0;
long long ans_maskB = 0;

int dfs_nodes = 0;
bool dfs_aborted = false;

bool dfs(int idx, long long sumA, long long sumB, long long maskA, long long maskB) {
    if (dfs_aborted) return false;
    
    if (++dfs_nodes > 2000000) {
        dfs_aborted = true;
        return false;
    }

    if (sumA == sumB && sumA > 0) {
        ans_maskA = maskA;
        ans_maskB = maskB;
        return true;
    }
    
    if (idx == n) return false;

    if (sumA < sumB) {
        swap(sumA, sumB);
        swap(maskA, maskB);
    }

    if (sumA - sumB > rem_sum[idx]) return false;

    if (dfs(idx + 1, sumA, sumB + x[idx], maskA, maskB | (1LL << idx))) return true;
    if (dfs(idx + 1, sumA + x[idx], sumB, maskA | (1LL << idx), maskB)) return true;
    if (dfs(idx + 1, sumA, sumB, maskA, maskB)) return true;

    return false;
}

void print_solution(long long mask1, long long mask2) {
    vector<long long> A, B;
    for (int i = 0; i < n; ++i) {
        if ((mask1 >> i) & 1) A.push_back(x[i]);
        if ((mask2 >> i) & 1) B.push_back(x[i]);
    }
    
    cout << A.size() << "\n";
    for (size_t i = 0; i < A.size(); ++i) cout << A[i] << (i + 1 == A.size() ? "" : " ");
    cout << "\n";
    
    cout << B.size() << "\n";
    for (size_t i = 0; i < B.size(); ++i) cout << B[i] << (i + 1 == B.size() ? "" : " ");
    cout << "\n";
    exit(0);
}

uint64_t state = 123456789123456789ULL;
inline uint64_t next_rnd() {
    state ^= state << 13;
    state ^= state >> 7;
    state ^= state << 17;
    return state;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (!(cin >> n)) return 0;
    
    x.resize(n);
    for (int i = 0; i < n; ++i) cin >> x[i];

    sort(x.begin(), x.end(), greater<long long>());

    rem_sum.resize(n + 1, 0);
    for (int i = n - 1; i >= 0; --i) rem_sum[i] = rem_sum[i + 1] + x[i];

    if (dfs(0, 0, 0, 0, 0)) {
        print_solution(ans_maskA, ans_maskB);
    }

    vector<long long> X(40, 0);
    for (int i = 0; i < n; ++i) X[i] = x[i];

    static long long block_sum[5][256];
    for (int b = 0; b < 5; ++b) {
        for (int m = 0; m < 256; ++m) {
            long long s = 0;
            for (int i = 0; i < 8; ++i) {
                if ((m >> i) & 1) {
                    s += X[b * 8 + i];
                }
            }
            block_sum[b][m] = s;
        }
    }

    if (n <= 21) {
        int limit = (1 << n) - 1;
        vector<pair<long long, uint64_t>> exact_subsets(limit);
        
        for (int m = 1; m <= limit; ++m) {
            long long s = block_sum[0][m & 0xFF] +
                          block_sum[1][(m >> 8) & 0xFF] +
                          block_sum[2][(m >> 16) & 0xFF];
            exact_subsets[m - 1] = {s, m};
        }
        
        sort(exact_subsets.begin(), exact_subsets.end());
        
        for (int i = 1; i < limit; ++i) {
            if (exact_subsets[i].first == exact_subsets[i - 1].first) {
                uint64_t m1 = exact_subsets[i].second;
                uint64_t m2 = exact_subsets[i - 1].second;
                uint64_t common = m1 & m2;
                print_solution(m1 ^ common, m2 ^ common);
            }
        }
    } else {
        int K = 2000000;
        vector<pair<long long, uint64_t>> subsets(K);
        long long max_mask = (1ULL << n) - 1;
        
        state = chrono::steady_clock::now().time_since_epoch().count() | 1;

        while (true) {
            for (int i = 0; i < K; ++i) {
                uint64_t mask = next_rnd() & max_mask;
                if (mask == 0) mask = 1;
                
                long long s = block_sum[0][mask & 0xFF] +
                              block_sum[1][(mask >> 8) & 0xFF] +
                              block_sum[2][(mask >> 16) & 0xFF] +
                              block_sum[3][(mask >> 24) & 0xFF] +
                              block_sum[4][(mask >> 32) & 0xFF];
                subsets[i] = {s, mask};
            }

            sort(subsets.begin(), subsets.end());

            for (int i = 1; i < K; ++i) {
                if (subsets[i].first == subsets[i - 1].first && subsets[i].second != subsets[i - 1].second) {
                    uint64_t m1 = subsets[i].second;
                    uint64_t m2 = subsets[i - 1].second;
                    uint64_t common = m1 & m2;
                    
                    m1 ^= common;
                    m2 ^= common;
                    
                    if (m1 > 0 && m2 > 0) {
                        print_solution(m1, m2);
                    }
                }
            }
        }
    }

    cout << "IMPOSSIBLE\n";
    return 0;
}