#include <iostream>
#include <vector>

using namespace std;

const int MOD = 1e9 + 7;

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

long long fact[5005], invFact[5005];

void precompute() {
    fact[0] = 1;
    invFact[0] = 1;
    for (int i = 1; i <= 5000; i++) {
        fact[i] = (fact[i - 1] * i) % MOD;
    }
    invFact[5000] = modInverse(fact[5000]);
    for (int i = 4999; i >= 1; i--) {
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

    vector<long long> S(n + 1, 0);
    vector<long long> ans(n + 1, 0);

    S[0] = 1;

    for (int m = 1; m <= n; ++m) {
        for (int k = m; k >= 1; --k) {
            S[k] = (S[k - 1] + 1LL * (m - 1) * S[k]) % MOD;
        }
        S[0] = 0;

        long long trees = (m == n) ? 1 : (1LL * m * power(n, n - m - 1)) % MOD;
        long long T = nCr(n, m) * trees % MOD;

        for (int k = 1; k <= m; ++k) {
            ans[k] = (ans[k] + S[k] * T) % MOD;
        }
    }

    for (int k = 1; k <= n; ++k) {
        cout << ans[k] << "\n";
    }

    return 0;
}