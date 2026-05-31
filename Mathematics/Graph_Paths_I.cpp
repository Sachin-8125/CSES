#include <iostream>
#include <vector>
using namespace std;

const long long MOD = 1000000007;

struct Matrix {
    int size;
    vector<vector<long long>> mat;
    
    Matrix(int n) : size(n), mat(n, vector<long long>(n, 0)) {}
    
    static Matrix identity(int n) {
        Matrix res(n);
        for (int i = 0; i < n; i++) res.mat[i][i] = 1;
        return res;
    }
};

Matrix multiply(const Matrix& A, const Matrix& B) {
    int n = A.size;
    Matrix C(n);
    for (int i = 0; i < n; i++) {
        for (int k = 0; k < n; k++) {
            if (A.mat[i][k] == 0) continue;
            for (int j = 0; j < n; j++) {
                C.mat[i][j] = (C.mat[i][j] + A.mat[i][k] * B.mat[k][j]) % MOD;
            }
        }
    }
    return C;
}

Matrix power(Matrix A, long long p) {
    Matrix res = Matrix::identity(A.size);
    while (p > 0) {
        if (p & 1) res = multiply(res, A);
        A = multiply(A, A);
        p >>= 1;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    long long k;
    if (!(cin >> n >> m >> k)) return 0;

    Matrix adj(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj.mat[u - 1][v - 1]++;
    }

    Matrix result = power(adj, k);

    cout << result.mat[0][n - 1] << endl;

    return 0;
}