#include <iostream>
#include <vector>

using namespace std;

const long long MOD = 1e9 + 7;

struct Matrix {
    long long a, b, c, d;
    Matrix(long long a, long long b, long long c, long long d) : a(a), b(b), c(c), d(d) {}
};

Matrix multiply(const Matrix& m1, const Matrix& m2) {
    return Matrix(
        (m1.a * m2.a + m1.b * m2.c) % MOD,
        (m1.a * m2.b + m1.b * m2.d) % MOD,
        (m1.c * m2.a + m1.d * m2.c) % MOD,
        (m1.c * m2.b + m1.d * m2.d) % MOD
    );
}

Matrix power(Matrix base, long long exp) {
    Matrix result(1, 0, 0, 1);
    while (exp > 0) {
        if (exp % 2 == 1) result = multiply(result, base);
        base = multiply(base, base);
        exp /= 2;
    }
    return result;
}

long long fib(long long n) {
    if (n == 0) return 0;
    if (n == 1) return 1;
    Matrix base(1, 1, 1, 0);
    Matrix result = power(base, n - 1);
    return result.a;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    long long n;
    cin >> n;
    cout << fib(n) << "\n";
    
    return 0;
}