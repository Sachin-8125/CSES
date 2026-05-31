#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    long double expected = 0.0L;

    long double k_pow_n = 1.0L;
    for (int i = 0; i < n; i++)
        k_pow_n *= k;

    for (int m = 1; m <= k; m++) {
        long double numerator = 1.0L;
        for (int i = 0; i < n; i++)
            numerator *= (m - 1);

        long double prob_le = numerator / k_pow_n;
        expected += (1.0L - prob_le);
    }

    cout << fixed << setprecision(6) << expected << "\n";

    return 0;
}