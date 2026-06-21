#include <iostream>
#include <vector>
#include <map>

using namespace std;

long long MOD = 1e9 + 7;

struct Matrix {
    long long mat[2][2];
    Matrix() {
        mat[0][0] = mat[0][1] = mat[1][0] = mat[1][1] = 0;
    }
};

Matrix multiply(Matrix A, Matrix B) {
    Matrix C;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                C.mat[i][j] = (C.mat[i][j] + A.mat[i][k] * B.mat[k][j]) % MOD;
            }
        }
    }
    return C;
}

Matrix power(Matrix A, long long p) {
    Matrix res;
    res.mat[0][0] = 1; res.mat[1][1] = 1;
    while (p > 0) {
        if (p & 1) res = multiply(res, A);
        A = multiply(A, A);
        p >>= 1;
    }
    return res;
}

long long solve_e(long long n, int e) {
    if (n == 0) return 1;
    Matrix T;
    T.mat[0][0] = 1; T.mat[0][1] = e;
    T.mat[1][0] = 1; T.mat[1][1] = 0;
    T = power(T, n);
    return (T.mat[0][0] + T.mat[0][1]) % MOD;
}

void solve() {
    long long n, k;
    cin >> n >> k;
    if (k == 1) {
        cout << 1 << endl;
        return;
    }
    map<int, int> factors;
    long long temp_k = k;
    for (long long i = 2; i * i <= temp_k; i++) {
        while (temp_k % i == 0) {
            factors[i]++;
            temp_k /= i;
        }
    }
    if (temp_k > 1) factors[temp_k]++;

    long long ans = 1;
    map<int, long long> cache;
    for (auto const& [p, e] : factors) {
        if (cache.find(e) == cache.end()) {
            cache[e] = solve_e(n, e);
        }
        ans = (ans * cache[e]) % MOD;
    }
    cout << ans << endl;
}

int main() {
    int t;
    if (!(cin >> t)) return 0;
    while (t--) {
        solve();
    }
    return 0;
}
