#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

long long power(long long base, long long exp, long long mod) {
    long long result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) result = result * base % mod;
        base = base * base % mod;
        exp >>= 1;
    }
    return result;
}

long long modInverse(long long n, long long mod) {
    return power(n, mod - 2, mod);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    if (n % 2 != 0) {
        cout << 0 << "\n";
        return 0;
    }
    
    n /= 2; 
    
    vector<long long> fact(2 * n + 1);
    fact[0] = 1;
    for (int i = 1; i <= 2 * n; i++) {
        fact[i] = fact[i - 1] * i % MOD;
    }

    long long catalan = fact[2 * n] * modInverse(fact[n + 1], MOD) % MOD;
    catalan = catalan * modInverse(fact[n], MOD) % MOD;
    
    cout << catalan << "\n";
    
    return 0;
}