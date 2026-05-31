#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    vector<int> queries(t);
    int maxN = 0;
    for (int i = 0; i < t; i++) {
        cin >> queries[i];
        maxN = max(maxN, queries[i]);
    }

    int maxRoot = sqrt(maxN);

    vector<int> twoSquares(maxN + 1, -1);

    for (int a = 0; a <= maxRoot; a++) {
        for (int b = 0; b <= maxRoot; b++) {
            int s = a * a + b * b;
            if (s > maxN) break;
            if (twoSquares[s] == -1) {
                twoSquares[s] = (a << 12) | b;
            }
        }
    }

    for (int n : queries) {
        bool found = false;

        for (int c = 0; c * c <= n && !found; c++) {
            for (int d = 0; c * c + d * d <= n; d++) {
                int s2 = c * c + d * d;
                int rem = n - s2;
                if (twoSquares[rem] != -1) {
                    int encoded = twoSquares[rem];
                    int a = encoded >> 12;
                    int b = encoded & ((1 << 12) - 1);
                    cout << a << " " << b << " " << c << " " << d << "\n";
                    found = true;
                    break;
                }
            }
        }

        // For completeness (the theorem guarantees existence)
        if (!found) {
            cout << "0 0 0 0\n";
        }
    }

    return 0;
}