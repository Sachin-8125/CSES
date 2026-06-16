#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

string s;
long long dp[505][505];
long long C[255][255];
bool computed[505][505];

void precompute_binom() {
    C[0][0] = 1;
    for (int i = 1; i <= 250; i++) {
        C[i][0] = 1;
        for (int j = 1; j <= i; j++)
            C[i][j] = (C[i-1][j-1] + C[i-1][j]) % MOD;
    }
}

long long solve(int i, int j) {
    if (i > j) return 1LL;                    
    if ((j - i + 1) % 2 == 1) return 0LL;    
    if (computed[i][j]) return dp[i][j];
    computed[i][j] = true;
    dp[i][j] = 0;

    int total_ops = (j - i + 1) / 2;

    for (int k = i + 1; k <= j; k += 2) {
        if (s[k] == s[i]) {
            int b = (j - k) / 2;            
            long long ways = C[total_ops][b]; 
            ways = ways * solve(i + 1, k - 1) % MOD;
            ways = ways * solve(k + 1, j)     % MOD;
            dp[i][j] = (dp[i][j] + ways) % MOD;
        }
    }
    return dp[i][j];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> s;
    precompute_binom();
    memset(computed, false, sizeof(computed));
    cout << solve(0, (int)s.size() - 1) << "\n";
    return 0;
}