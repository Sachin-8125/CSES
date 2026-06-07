#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, q;
    if (!(cin >> n >> q)) return 0;

    int max_log = 0;
    while ((1 << (max_log + 1)) <= n) {
        max_log++;
    }
    
    vector<vector<int>> st(max_log + 1, vector<int>(n + 1));

    for (int i = 1; i <= n; ++i) {
        cin >> st[0][i];
    }

    for (int i = 1; i <= max_log; ++i) {
        for (int j = 1; j + (1 << i) - 1 <= n; ++j) {
            st[i][j] = min(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
        }
    }

    while (q--) {
        int a, b;
        if (!(cin >> a >> b)) break;
        int len = b - a + 1;
        int k = __lg(len);
        cout << min(st[k][a], st[k][b - (1 << k) + 1]) << "\n";
    }

    return 0;
}