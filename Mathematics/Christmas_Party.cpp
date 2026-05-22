#include <iostream>
#include <vector>

using namespace std;

int main() {
    // Optimize standard I/O operations for performance
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    // Base cases
    if (n == 1) {
        cout << 0 << "\n";
        return 0;
    }
    if (n == 2) {
        cout << 1 << "\n";
        return 0;
    }

    const int MOD = 1e9 + 7;
    
    // Iterative DP approach using space optimization
    long long prev2 = 0; // !1
    long long prev1 = 1; // !2
    long long current = 0;

    for (int i = 3; i <= n; ++i) {
        current = (i - 1) * (prev1 + prev2) % MOD;
        prev2 = prev1;
        prev1 = current;
    }

    cout << current << "\n";

    return 0;
}
