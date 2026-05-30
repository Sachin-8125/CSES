#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    int k = 1;
    while (k < n) {
        k <<= 1;
    }

    vector<long long> dp(k, 0);
    for (int i = 0; i < n; ++i) {
        cin >> dp[i];
    }

    for (int mask = 1; mask < k; mask <<= 1) {
        for (int i = 0; i < k; ++i) {
            if (i & mask) {
                dp[i] ^= dp[i ^ mask];
            }
        }
    }

    for (int r = 0; r < n; ++r) {
        cout << dp[r] << (r == n - 1 ? "" : " ");
    }
    cout << "\n";

    return 0;
}
