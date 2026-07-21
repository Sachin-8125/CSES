#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("popcnt")

#include <iostream>

using namespace std;

const int MAXN = 3000;
unsigned long long grid[MAXN][47];
char buf[MAXN + 5];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    for (int i = 0; i < n; ++i) {
        cin >> buf;
        for (int j = 0; j < n; ++j) {
            if (buf[j] == '1') {
                grid[i][j >> 6] |= (1ULL << (j & 63));
            }
        }
    }

    long long ans = 0;
    
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            int cnt = 0;
            for (int k = 0; k < 47; ++k) {
                cnt += __builtin_popcountll(grid[i][k] & grid[j][k]);
            }
            ans += (long long)cnt * (cnt - 1) / 2;
        }
    }

    cout << ans << "\n";

    return 0;
}