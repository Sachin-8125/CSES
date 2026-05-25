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
    string s;
    cin >> n >> s;

    if (n % 2 == 1) {
        cout << 0 << "\n";
        return 0;
    }
    
    int balance = 0;
    int open_needed = n / 2;  
    int close_needed = n / 2; 
    
    for (char c : s) {
        if (c == '(') {
            balance++;
            open_needed--;
        } else if (c == ')') {
            balance--;
            close_needed--;
            if (balance < 0) {
                cout << 0 << "\n";
                return 0;
            }
        }
    }
    int remaining = n - s.length();
    if (open_needed < 0 || close_needed < 0) {
        cout << 0 << "\n";
        return 0;
    }
    
    if (open_needed + close_needed != remaining) {
        cout << 0 << "\n";
        return 0;
    }

    int max_n = remaining;
    vector<long long> fact(max_n + 1), inv_fact(max_n + 1);
    fact[0] = 1;
    for (int i = 1; i <= max_n; i++) {
        fact[i] = fact[i - 1] * i % MOD;
    }
    inv_fact[max_n] = modInverse(fact[max_n], MOD);
    for (int i = max_n - 1; i >= 0; i--) {
        inv_fact[i] = inv_fact[i + 1] * (i + 1) % MOD;
    }
    
    auto nCr = [&](int n, int r) -> long long {
        if (r < 0 || r > n) return 0;
        return fact[n] * inv_fact[r] % MOD * inv_fact[n - r] % MOD;
    };

    if (close_needed != open_needed + balance) {
        cout << 0 << "\n";
        return 0;
    }
    
    long long total = nCr(remaining, open_needed);
    long long bad = nCr(remaining, open_needed + balance + 1);
    
    long long ans = (total - bad + MOD) % MOD;
    cout << ans << "\n";
    
    return 0;
}