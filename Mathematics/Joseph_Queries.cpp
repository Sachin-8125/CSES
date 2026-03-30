#include <iostream>

using namespace std;

int solve(int n, int k) {
    if (n == 1) return 1;
    if (k <= n / 2) return 2 * k;
    
    int res = solve(n - n / 2, k - n / 2);
    
    if (n % 2 == 0) {
        return 2 * res - 1;
    } else {
        return res == 1 ? n : 2 * res - 3;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int q;
    if (cin >> q) {
        while (q--) {
            int n, k;
            cin >> n >> k;
            cout << solve(n, k) << "\n";
        }
    }

    return 0;
}