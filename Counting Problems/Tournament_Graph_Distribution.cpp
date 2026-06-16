#include <iostream>
#include <vector>

using namespace std;

const int MOD = 1e9 + 7;

long long fact[505], invFact[505];

long long power(long long base, long long exp) {
    long long res = 1;
    base %= MOD;
    while (exp > 0) {
        if (exp % 2 == 1) res = (res * base) % MOD;
        base = (base * base) % MOD;
        exp /= 2;
    }
    return res;
}

long long modInverse(long long n) {
    return power(n, MOD - 2);
}

void precompute() {
    fact[0] = 1;
    invFact[0] = 1;
    for (int i = 1; i <= 500; i++) {
        fact[i] = (fact[i - 1] * i) % MOD;
    }
    invFact[500] = modInverse(fact[500]);
    for (int i = 499; i >= 1; i--) {
        invFact[i] = (invFact[i + 1] * (i + 1)) % MOD;
    }
}

long long nCr(int n, int r) {
    if (r < 0 || r > n) return 0;
    return fact[n] * invFact[r] % MOD * invFact[n - r] % MOD;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    precompute();

    int n;
    if (!(cin >> n)) return 0;

    vector<long long> T(n + 1);
    for (int i = 0; i <= n; i++) {
        long long edges = 1LL * i * (i - 1) / 2;
        T[i] = power(2, edges);
    }

    vector<long long> S(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        S[i] = T[i];
        for (int y = 1; y < i; y++) {
            long long sub = nCr(i, y) * S[y] % MOD * T[i - y] % MOD;
            S[i] = (S[i] - sub + MOD) % MOD;
        }
    }

    vector<vector<long long>> dp(n + 1, vector<long long>(n + 1, 0));
    dp[0][0] = 1;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            for (int x = 1; x <= i - j + 1; x++) {
                long long ways = nCr(i, x) * S[x] % MOD * dp[i - x][j - 1] % MOD;
                dp[i][j] = (dp[i][j] + ways) % MOD;
            }
        }
    }

    for (int k = 1; k <= n; k++) {
        cout << dp[n][k] << "\n";
    }

    return 0;
}