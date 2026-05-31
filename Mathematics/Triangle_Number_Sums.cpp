#include <bits/stdc++.h>
using namespace std;

using int64 = long long;

bool isTriangular(int64 x) {
    if (x <= 0) return false;
    int64 v = 8 * x + 1;
    int64 s = sqrtl(v);
    return s * s == v;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        int64 n;
        cin >> n;

        if (isTriangular(n)) {
            cout << 1 << "\n";
            continue;
        }

        bool found = false;

        for (int64 k = 1;; k++) {
            int64 T = k * (k + 1) / 2;
            if (T > n) break;

            if (isTriangular(n - T)) {
                found = true;
                break;
            }
        }
        cout<< (found ? "2" : "3") << "\n";  
    }
    return 0;
}