#include <iostream>
using namespace std;
const int MOD = 1000000007;

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

int main() {
    long long n;
    if (!(cin >> n)) return 0;

    if (n == 0) {
        cout << 0 << endl;
        return 0;
    }

    long long mod = MOD;
    
    long long c0 = (n * n);
    
    long long c90;
    if (n % 2 == 0) {
        c90 = (n * n) / 4;
    } else {
        c90 = (n * n - 1) / 4 + 1;
    }
    
    long long c180;
    if (n % 2 == 0) {
        c180 = (n * n) / 2;
    } else {
        c180 = (n * n - 1) / 2 + 1;
    }

    long long f0 = power(2, c0);
    long long f90 = power(2, c90);
    long long f180 = power(2, c180);
    long long f270 = f90; // Same as 90 degrees

    long long total = (f0 + f90 + f180 + f270) % mod;
    long long ans = (total * modInverse(4)) % mod;

    cout << ans << endl;

    return 0;
}