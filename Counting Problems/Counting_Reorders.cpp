#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int MOD = 1e9 + 7;

long long fact[5005], invFact[5005];

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
    
    string s;
    if (!(cin >> s)) return 0;
    
    vector<int> f(26, 0);
    for (char c : s) {
        f[c - 'a']++;
    }
    
    vector<long long> P = {1};
    
    for (int c = 0; c < 26; ++c) {
        if (f[c] == 0) continue;
        
        vector<long long> Q(f[c] + 1, 0);
        for (int k = 1; k <= f[c]; ++k) {
            long long val = nCr(f[c] - 1, k - 1) * invFact[k] % MOD;
            if ((f[c] - k) % 2 == 1) {
                val = (MOD - val) % MOD;
            }
            Q[k] = val;
        }
        
        vector<long long> R(P.size() + Q.size() - 1, 0);
        for (int i = 0; i < P.size(); ++i) {
            if (P[i] == 0) continue;
            for (int j = 0; j < Q.size(); ++j) {
                if (Q[j] == 0) continue;
                R[i + j] = (R[i + j] + P[i] * Q[j]) % MOD;
            }
        }
        P = move(R);
    }
    
    long long ans = 0;
    for (int K = 0; K < P.size(); ++K) {
        long long term = P[K] * fact[K] % MOD;
        ans = (ans + term) % MOD;
    }
    
    cout << ans << "\n";
    
    return 0;
}