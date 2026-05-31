#include <bits/stdc++.h>
using namespace std;

static const long long MOD = 1000000007;

// Fast exponentiation to compute modular inverse
long long modpow(long long a, long long e) {
    long long r = 1;
    a %= MOD;
    while (e > 0) {
        if (e & 1) r = (r * a) % MOD;
        a = (a * a) % MOD;
        e >>= 1;
    }
    return r;
}

long long modinv(long long a) {
    return modpow(a, MOD - 2); // Fermat inverse since MOD is prime
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<long long>> a(n, vector<long long>(m + 1));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= m; j++) {
            cin >> a[i][j];
        }
    }

    int row = 0;
    vector<int> where(m, -1);

    for (int col = 0; col < m && row < n; col++) {
        int sel = -1;
        for (int i = row; i < n; i++) {
            if (a[i][col] != 0) {
                sel = i;
                break;
            }
        }
        if (sel == -1) continue;

        swap(a[sel], a[row]);
        where[col] = row;

        long long inv = modinv(a[row][col]);
        for (int j = col; j <= m; j++) {
            a[row][j] = (a[row][j] * inv) % MOD;
        }

        for (int i = 0; i < n; i++) {
            if (i != row && a[i][col] != 0) {
                long long factor = a[i][col];
                for (int j = col; j <= m; j++) {
                    a[i][j] = (a[i][j] - factor * a[row][j]) % MOD;
                    if (a[i][j] < 0) a[i][j] += MOD;
                }
            }
        }

        row++;
    }

    // Check for inconsistency
    for (int i = 0; i < n; i++) {
        bool all_zero = true;
        for (int j = 0; j < m; j++) {
            if (a[i][j] != 0) {
                all_zero = false;
                break;
            }
        }
        if (all_zero && a[i][m] != 0) {
            cout << -1 << "\n";
            return 0;
        }
    }

    vector<long long> ans(m, 0);
    for (int i = 0; i < m; i++) {
        if (where[i] != -1) {
            ans[i] = a[where[i]][m];
        } else {
            ans[i] = 0; // free variable
        }
    }

    for (int i = 0; i < m; i++) {
        cout << ans[i] << " ";
    }
    cout << "\n";

    return 0;
}