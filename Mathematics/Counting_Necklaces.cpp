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

// Function to calculate Euler's Totient Function phi(x)
long long phi(long long x) {
    long long result = x;
    for (long long i = 2; i * i <= x; i++) {
        if (x % i == 0) {
            while (x % i == 0) {
                x /= i;
            }
            result -= result / i;
        }
    }
    if (x > 1) {
        result -= result / x;
    }
    return result;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    long long n, m;
    if (!(cin >> n >> m)) return 0;

    long long total_sum = 0;

    for (long long g = 1; g * g <= n; g++) {
        if (n % g == 0) {
            long long count1 = phi(n / g) % MOD;
            long long ways1 = power(m, g);
            total_sum = (total_sum + count1 * ways1) % MOD;

            if (g * g != n) {
                long long g2 = n / g;
                long long count2 = phi(n / g2) % MOD;
                long long ways2 = power(m, g2);
                total_sum = (total_sum + count2 * ways2) % MOD;
            }
        }
    }

    long long ans = (total_sum * modInverse(n)) % MOD;

    cout << ans << "\n";

    return 0;
}
