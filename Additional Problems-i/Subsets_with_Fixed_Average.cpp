#include <bits/stdc++.h>
using namespace std;

static const int MOD = 1000000007;
static const int MAXV = 500;

int addmod(int a, int b) {
    a += b;
    if (a >= MOD) a -= MOD;
    return a;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, a;
    cin >> n >> a;

    vector<int> cnt(MAXV + 1, 0);
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        cnt[x]++;
    }

    vector<vector<int>> C(n + 1, vector<int>(n + 1, 0));
    C[0][0] = 1;
    for (int i = 1; i <= n; ++i) {
        C[i][0] = C[i][i] = 1;
        for (int j = 1; j < i; ++j) {
            C[i][j] = addmod(C[i - 1][j - 1], C[i - 1][j]);
        }
    }

    int SHIFT = n * MAXV;                
    int S = 2 * SHIFT + 1;

    vector<int> dp(S, 0), ndp(S, 0);
    dp[SHIFT] = 1; 

    for (int v = 1; v <= MAXV; ++v) {
        if (cnt[v] == 0) continue;

        fill(ndp.begin(), ndp.end(), 0);
        int d = v - a;

        for (int s = 0; s < S; ++s) {
            if (dp[s] == 0) continue;

            for (int k = 0; k <= cnt[v]; ++k) {
                int ns = s + k * d;
                if (ns < 0 || ns >= S) continue;
                ndp[ns] = (ndp[ns] + 1LL * dp[s] * C[cnt[v]][k]) % MOD;
            }
        }

        dp.swap(ndp);
    }

    int ans = dp[SHIFT] - 1; // remove empty subset
    if (ans < 0) ans += MOD;

    cout << ans << '\n';
    return 0;
}