#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const long long INF = 2e18; 

struct Matrix {
    int size;
    vector<vector<long long>> mat;
    
    Matrix(int n) : size(n), mat(n, vector<long long>(n, INF)) {}
};

Matrix multiply(const Matrix& A, const Matrix& B) {
    int n = A.size;
    Matrix C(n);
    for (int i = 0; i < n; i++) {
        for (int p = 0; p < n; p++) {
            if (A.mat[i][p] == INF) continue;
            for (int j = 0; j < n; j++) {
                if (B.mat[p][j] == INF) continue;
                C.mat[i][j] = min(C.mat[i][j], A.mat[i][p] + B.mat[p][j]);
            }
        }
    }
    return C;
}

Matrix power(Matrix A, long long p) {
    int n = A.size;
    Matrix res(n);
    bool initialized = false;
    
    while (p > 0) {
        if (p & 1) {
            if (!initialized) {
                res = A;
                initialized = true;
            } else {
                res = multiply(res, A);
            }
        }
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
        long long w;
        cin >> u >> v >> w;
        adj.mat[u - 1][v - 1] = min(adj.mat[u - 1][v - 1], w);
    }

    Matrix result = power(adj, k);

    long long ans = result.mat[0][n - 1];
    if (ans >= INF) {
        cout << -1 << endl;
    } else {
        cout << ans << endl;
    }
    return 0;
}