#include <iostream>
#include <numeric>

using namespace std;

void solve() {
    long long n, m, k;
    cin >> n >> m >> k;

    long long n1 = n - 1;
    long long m1 = m - 1;

    long long rem_x = k % (2 * n1);
    long long x = (rem_x < n) ? (1 + rem_x) : (2 * n - 1 - rem_x);

    long long rem_y = k % (2 * m1);
    long long y = (rem_y < m) ? (1 + rem_y) : (2 * m - 1 - rem_y);

    unsigned long long g = std::gcd((unsigned long long)n1, (unsigned long long)m1);
    
    unsigned __int128 lcm = (unsigned __int128)n1 / g * m1;

    long long changes = (k / n1) + (k / m1) - (long long)((unsigned __int128)k / lcm);

    cout << x << " " << y << " " << changes << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    
    return 0;
}