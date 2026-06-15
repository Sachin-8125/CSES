#include <iostream>
#include <vector>

using namespace std;

const int MOD = 1000000007;
const int MAXN = 5005;

int euler[MAXN][MAXN];
long long fact[MAXN], invFact[MAXN];

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

long long inverse(long long n) {
    return power(n, MOD - 2);
}

void precompute() {
    fact[0] = 1;
    invFact[0] = 1;
    for (int i = 1; i < MAXN; i++) {
        fact[i] = (fact[i - 1] * i) % MOD;
        invFact[i] = inverse(fact[i]);
    }

    euler[0][0] = 1;
    for (int n = 1; n < MAXN; n++) {
        euler[n][0] = 1;
        for (int k = 1; k < n; k++) {
            euler[n][k] = (1LL * (k + 1) * euler[n - 1][k] + 1LL * (n - k) * euler[n - 1][k - 1]) % MOD;
        }
    }
}

long long nCr(int n, int r) {
    if (r < 0 || r > n) return 0;
    return (((fact[n] * invFact[r]) % MOD) * invFact[n - r]) % MOD;
}

void solve() {
    int n, a, b;
    if (!(cin >> n >> a >> b)) return;
    
    int c = n - a - b;
    if (c < 0) {
        cout << "0\n";
        return;
    }

    int m = n - c;
    int k = b;
    
    long long fm_k = 0;
    for (int j = 0; j <= m - k; j++) {
        long long term = (nCr(m, j) * euler[m - j][k]) % MOD;
        if (j % 2 == 1) {
            fm_k = (fm_k - term + MOD) % MOD;
        } else {
            fm_k = (fm_k + term) % MOD;
        }
    }

    long long ans = (fact[n] * nCr(n, c)) % MOD;
    ans = (ans * fm_k) % MOD;
    cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    precompute();
    
    int t;
    if (!(cin >> t)) return 0;
    while (t--) {
        solve();
    }
    
    return 0;
}
