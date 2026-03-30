#include <iostream>
using namespace std;
const int mod = 1e9+7;

long long power(long long a, long long b) {
    long long res = 1;
    a %= mod;
    while (b > 0) {
        if (b % 2 == 1) res = (res * a) % mod;
        a = (a * a) % mod;
        b /= 2;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    while (n--) {
        long long a, b;
        cin >> a >> b;
        cout << power(a, b) << "\n";
    }
    return 0;
}