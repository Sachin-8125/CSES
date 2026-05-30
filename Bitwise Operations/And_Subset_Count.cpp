#include <iostream>
#include <vector>

using namespace std;

const int MOD = 1e9 + 7;
const int BITS = 18;
const int MAX_VAL = 1 << BITS;

int cnt[MAX_VAL];
long long g[MAX_VAL];
long long pow2[200005];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    pow2[0] = 1;
    for (int i = 1; i <= n; i++) {
        pow2[i] = (pow2[i - 1] * 2) % MOD;
    }

    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        cnt[a]++;
    }

    for (int i = 0; i < BITS; i++) {
        for (int mask = MAX_VAL - 1; mask >= 0; mask--) {
            if (!(mask & (1 << i))) {
                cnt[mask] += cnt[mask | (1 << i)];
            }
        }
    }

    for (int i = 0; i < MAX_VAL; i++) {
        g[i] = (pow2[cnt[i]] - 1 + MOD) % MOD;
    }

    for (int i = 0; i < BITS; i++) {
        for (int mask = MAX_VAL - 1; mask >= 0; mask--) {
            if (!(mask & (1 << i))) {
                g[mask] = (g[mask] - g[mask | (1 << i)] + MOD) % MOD;
            }
        }
    }

    for (int i = 0; i <= n; i++) {
        cout << g[i] << (i == n ? "" : " ");
    }
    cout << "\n";

    return 0;
}