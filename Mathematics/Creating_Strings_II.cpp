#include <iostream>
#include <string>
#include <vector>

using namespace std;

const int MOD = 1e9 + 7;
const int MAX = 1e6 + 5;

long long fact[MAX];
long long invFact[MAX];

// Function to calculate (base^exp) % MOD in O(log exp) time
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

// Function to calculate modular inverse
long long modInverse(long long n) {
    return power(n, MOD - 2);
}

// Precompute factorials and inverse factorials up to MAX
void precompute() {
    fact[0] = 1;
    invFact[0] = 1;
    for (int i = 1; i < MAX; i++) {
        fact[i] = (fact[i - 1] * i) % MOD;
    }
    
    // Compute the inverse factorial for the largest value
    invFact[MAX - 1] = modInverse(fact[MAX - 1]);
    
    // Compute remaining inverse factorials backwards
    for (int i = MAX - 2; i >= 1; i--) {
        invFact[i] = (invFact[i + 1] * (i + 1)) % MOD;
    }
}

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    precompute();

    string s;
    if (!(cin >> s)) return 0;

    int n = s.length();
    vector<int> counts(26, 0);

    // Count occurrences of each character
    for (char c : s) {
        counts[c - 'a']++;
    }

    // Calculate total permutations: n! / (c1! * c2! * ... * ck!)
    long long ans = fact[n];
    for (int i = 0; i < 26; i++) {
        if (counts[i] > 0) {
            ans = (ans * invFact[counts[i]]) % MOD;
        }
    }

    cout << ans << "\n";

    return 0;
}
