#include <iostream>
#include <vector>
#include <numeric>
#include <random>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<int> a(n), b(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    for (int i = 0; i < n; ++i) cin >> b[i];

    if (n < 3) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }

    vector<int> c(n);
    iota(c.begin(), c.end(), 1);

    mt19937 rng(42); 

    while (true) {
        bool bad = false;
        for (int i = 0; i < n; ++i) {
            if (c[i] == a[i] || c[i] == b[i]) {
                int j = rng() % n;
                swap(c[i], c[j]);
                bad = true;
            }
        }
        if (!bad) {
            bool verified = true;
            for (int i = 0; i < n; ++i) {
                if (c[i] == a[i] || c[i] == b[i]) {
                    verified = false;
                    break;
                }
            }
            if (verified) break;
        }
    }

    for (int i = 0; i < n; ++i) {
        cout << c[i] << (i == n - 1 ? "" : " ");
    }
    cout << "\n";

    return 0;
}