#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    long long x;
    if (!(cin >> n >> x)) return 0;

    vector<long long> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];

    // Store one pair (i, j) for each sum seen so far with j < current i
    unordered_map<long long, pair<int, int>> seen;
    seen.reserve(1ull * n * n / 2);
    seen.max_load_factor(0.7f);

    for (int i = 0; i < n; ++i) {
        // Try to pair (i, j) with any previously seen pair summing to x
        for (int j = i + 1; j < n; ++j) {
            long long need = x - a[i] - a[j];
            auto it = seen.find(need);
            if (it != seen.end()) {
                auto [p, q] = it->second; // p < q < i
                cout << (p + 1) << ' ' << (q + 1) << ' ' << (i + 1) << ' ' << (j + 1) << '\n';
                return 0;
            }
        }
        // Add sums involving index i with all previous indices j < i
        for (int j = 0; j < i; ++j) {
            seen[a[i] + a[j]] = {j, i};
        }
    }

    cout << "IMPOSSIBLE\n";
    return 0;
}
