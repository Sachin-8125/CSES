#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    long long n;
    if (!(cin >> n)) return 0;

    long long ans = 0;
    long long MOD = 1000000007;
    long long INV2 = 500000004;

    for (long long L = 1, R; L <= n; L = R + 1) {
        long long q = n / L;
        R = n / q;

        long long count = (R - L + 1) % MOD;
        long long sum_LR = (L + R) % MOD;
        long long range_sum = (count * sum_LR) % MOD * INV2 % MOD;

        ans = (ans + (q % MOD) * range_sum) % MOD;
    }

    cout << ans << "\n";

    return 0;
}