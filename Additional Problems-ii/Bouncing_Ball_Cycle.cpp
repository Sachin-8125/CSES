#include <iostream>
#include <numeric>

using namespace std;

long long get_C(long long n, long long K, long long i) {
    return (n / K) + (i < (n % K) ? 1 : 0);
}

void solve() {
    long long n, m;
    cin >> n >> m;

    long long N = n - 1;
    long long M = m - 1;
    long long g = std::gcd(N, M);
    long long K = 2 * g;

    long long steps = 2LL * (N / g) * M;

    long long cells = get_C(n, K, 0) * get_C(m, K, 0) + get_C(n, K, g) * get_C(m, K, g);
    
    if (g > 1) {
        cells += (g - 1) * get_C(n, K, 1) * (get_C(m, K, 1) + get_C(m, K, K - 1));
        cells += (g - 1) * get_C(n, K, g + 1) * (get_C(m, K, g + 1) + get_C(m, K, K - (g + 1)));
    }

    cout << steps << " " << cells << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }
    
    return 0;
}