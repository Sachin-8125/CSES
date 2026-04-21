#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    const int LOG = 30; // enough for numbers up to 1e9
    long long basis[LOG + 1] = {};

    for (int i = 0; i < n; i++) {
        long long x;
        cin >> x;

        for (int b = LOG; b >= 0; b--) {
            if (((x >> b) & 1) == 0) continue;

            if (!basis[b]) {
                basis[b] = x;
                break;
            }

            x ^= basis[b];
        }
    }

    long long ans = 0;
    for (int b = LOG; b >= 0; b--) {
        ans = max(ans, ans ^ basis[b]);
    }

    cout << ans << '\n';
    return 0;
}