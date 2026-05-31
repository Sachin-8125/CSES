#include <iostream>
#include <vector>

using namespace std;

const long long MOD = 1000000007;

struct Matrix {
    long long mat[6][6];
    Matrix() {
        for (int i = 0; i < 6; i++)
            for (int j = 0; j < 6; j++)
                mat[i][j] = 0;
    }
};

Matrix multiply(Matrix A, Matrix B) {
    Matrix C;
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            for (int k = 0; k < 6; k++) {
                C.mat[i][j] = (C.mat[i][j] + A.mat[i][k] * B.mat[k][j]) % MOD;
            }
        }
    }
    return C;
}

Matrix power(Matrix A, long long p) {
    Matrix res;
    for (int i = 0; i < 6; i++) res.mat[i][i] = 1;
    while (p > 0) {
        if (p & 1) res = multiply(res, A);
        A = multiply(A, A);
        p >>= 1;
    }
    return res;
}

int main() {
    long long n;
    if (!(cin >> n)) return 0;

    if (n == 0) {
        cout << 1 << endl;
        return 0;
    }

    Matrix T;

    for (int j = 0; j < 6; j++) T.mat[0][j] = 1;

    for (int i = 1; i < 6; i++) T.mat[i][i - 1] = 1;

    Matrix result = power(T, n);

    cout << result.mat[0][0] << endl;

    return 0;
}