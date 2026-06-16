#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

long long power(long long base, long long exp) {
    long long result = 1;
    base %= MOD;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % MOD;
        }
        base = (base * base) % MOD;
        exp /= 2;
    }
    return result;
}

long long modInverse(long long n) {
    return power(n, MOD - 2);
}

vector<long long> fact, invFact;

void precomputeFactorials(int n) {
    fact.resize(n + 1);
    invFact.resize(n + 1);
    fact[0] = 1;
    for (int i = 1; i <= n; i++) {
        fact[i] = (fact[i - 1] * i) % MOD;
    }
    invFact[n] = modInverse(fact[n]);
    for (int i = n - 1; i >= 0; i--) {
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
    
    int n, k;
    cin >> n >> k;
    
    precomputeFactorials(k);
    
    long long result = 0;
    
    for (int i = 0; i <= k; i++) {
        long long term = nCr(k, i) * power(k - i, n) % MOD;
        
        if (i % 2 == 1) {
            result = (result - term + MOD) % MOD;
        } else {
            result = (result + term) % MOD;
        }
    }
    
    cout << result << endl;
    
    return 0;
}