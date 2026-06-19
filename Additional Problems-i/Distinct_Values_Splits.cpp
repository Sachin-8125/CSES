#include <iostream>
#include <vector>
#include <map>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<int> x(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> x[i];
    }

    const int MOD = 1e9 + 7;

    vector<long long> dp(n + 1, 0);
    vector<long long> pref(n + 1, 0);

    dp[0] = 1;
    pref[0] = 1;

    map<int, int> last_pos;
    
    int left_bound = 1;

    for (int i = 1; i <= n; i++) {
        if (last_pos.count(x[i])) {
            left_bound = max(left_bound, last_pos[x[i]] + 1);
        }
        last_pos[x[i]] = i;

        int R = i - 1;
        int L = left_bound - 1;

        long long current_sum = pref[R];
        if (L > 0) {
            current_sum = (current_sum - pref[L - 1] + MOD) % MOD;
        }

        dp[i] = current_sum;
        pref[i] = (pref[i - 1] + dp[i]) % MOD;
    }

    cout << dp[n] << "\n";

    return 0;
}