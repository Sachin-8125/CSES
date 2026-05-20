#include <iostream>
#include <vector>

using namespace std;

const int MOD = 1e9 + 7;
const int MAX = 1e6;

vector<long long> fact(MAX + 1);
vector<long long> invFact(MAX + 1);

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

// Function to find modular inverse using Fermat's Little Theorem
long long modInverse(long long n) {
    return power(n, MOD - 2);
}

// Precompute factorials and their modular inverses
void precompute() {
    fact[0] = 1;
    invFact[0] = 1;
    
    for (int i = 1; i <= MAX; i++) {
        fact[i] = (fact[i - 1] * i) % MOD;
    }
    
    // Compute the inverse of the largest factorial
    invFact[MAX] = modInverse(fact[MAX]);
    
    // Compute remaining inverse factorials backwards in O(MAX) total time
    for (int i = MAX - 1; i >= 1; i--) {
        invFact[i] = (invFact[i + 1] * (i + 1)) % MOD;
    }
}

// Function to calculate nCr in O(1) time
long long nCr(int n, int r) {
    if (r < 0 || r > n) return 0;
    return fact[n] * invFact[r] % MOD * invFact[n - r] % MOD;
}

int main() {
    // Optimize standard I/O operations for performance
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    precompute();

    int n;
    if (cin >> n) {
        while (n--) {
            int a, b;
            cin >> a >> b;
            cout << nCr(a, b) << "\n";
        }
    }

    return 0;
}
