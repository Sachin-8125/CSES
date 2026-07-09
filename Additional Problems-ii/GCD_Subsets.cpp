#include <iostream>
#include <vector>

using namespace std;

const int MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<int> cnt(n + 1, 0);
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        cnt[x]++;
    }

    vector<long long> pow2(n + 1);
    pow2[0] = 1;
    for (int i = 1; i <= n; i++) {
        pow2[i] = (pow2[i - 1] * 2) % MOD;
    }

    vector<long long> dp(n + 1, 0);

    for (int k = n; k >= 1; k--) {
        int multiples_count = 0;
        
        for (int i = k; i <= n; i += k) {
            multiples_count += cnt[i];
        }

        long long subsets = (pow2[multiples_count] - 1 + MOD) % MOD;

        for (int i = 2 * k; i <= n; i += k) {
            subsets = (subsets - dp[i] + MOD) % MOD;
        }

        dp[k] = subsets;
    }

    for (int k = 1; k <= n; k++) {
        cout << dp[k] << (k == n ? "" : " ");
    }
    cout << "\n";

    return 0;
}