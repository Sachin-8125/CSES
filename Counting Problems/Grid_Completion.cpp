#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

const int MOD = 1e9 + 7;

long long fact[1005], invFact[1005];

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
    for (int i = 1; i <= 1000; i++) {
        fact[i] = (fact[i - 1] * i) % MOD;
    }
    invFact[1000] = modInverse(fact[1000]);
    for (int i = 999; i >= 1; i--) {
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
    
    vector<string> grid(n);
    for (int i = 0; i < n; i++) {
        cin >> grid[i];
    }
    
    vector<int> p(n, -1), q(n, -1);
    vector<bool> in_p(n, false), in_q(n, false);
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == 'A') {
                p[i] = j;
                in_p[j] = true;
            } else if (grid[i][j] == 'B') {
                q[i] = j;
                in_q[j] = true;
            }
        }
    }
    
    int c0 = 0, c1 = 0, c2 = 0, c3 = 0;
    int pn = 0, qn = 0;
    
    for (int i = 0; i < n; i++) {
        if (p[i] == -1 && q[i] == -1) c0++;
        if (p[i] == -1 && q[i] != -1 && !in_p[q[i]]) c1++;
        if (p[i] != -1 && q[i] == -1 && !in_q[p[i]]) c2++;
        if (p[i] == -1) pn++;
        if (q[i] == -1) qn++;
    }
    
    for (int j = 0; j < n; j++) {
        if (!in_p[j] && !in_q[j]) c3++;
    }
    
    long long ans = 0;
    int limit = min(c0, c3);
    
    for (int i = 0; i <= limit; i++) {
        long long ways_i = nCr(c0, i) * nCr(c3, i) % MOD * fact[i] % MOD;
        
        long long s1 = 0;
        for (int j = 0; j <= c1; j++) {
            if (pn - i - j < 0) continue;
            long long term = nCr(c1, j) * fact[pn - i - j] % MOD;
            if (j % 2 == 1) {
                s1 = (s1 - term + MOD) % MOD;
            } else {
                s1 = (s1 + term) % MOD;
            }
        }
        
        long long s2 = 0;
        for (int k = 0; k <= c2; k++) {
            if (qn - i - k < 0) continue;
            long long term = nCr(c2, k) * fact[qn - i - k] % MOD;
            if (k % 2 == 1) {
                s2 = (s2 - term + MOD) % MOD;
            } else {
                s2 = (s2 + term) % MOD;
            }
        }
        
        long long current_term = ways_i * s1 % MOD * s2 % MOD;
        
        if (i % 2 == 1) {
            ans = (ans - current_term + MOD) % MOD;
        } else {
            ans = (ans + current_term) % MOD;
        }
    }
    
    cout << ans << "\n";
    
    return 0;
}