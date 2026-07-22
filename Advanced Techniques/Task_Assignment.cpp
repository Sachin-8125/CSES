#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;

    vector<vector<long long>> a(n + 1, vector<long long>(n + 1));
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            cin >> a[i][j];

    const long long INF = (1LL<<60);

    vector<long long> u(n + 1), v(n + 1);
    vector<int> p(n + 1), way(n + 1);

    for (int i = 1; i <= n; i++) {
        p[0] = i;
        int j0 = 0;
        vector<long long> minv(n + 1, INF);
        vector<char> used(n + 1, false);

        do {
            used[j0] = true;
            int i0 = p[j0];
            long long delta = INF;
            int j1 = 0;

            for (int j = 1; j <= n; j++) {
                if (used[j]) continue;
                long long cur = a[i0][j] - u[i0] - v[j];
                if (cur < minv[j]) {
                    minv[j] = cur;
                    way[j] = j0;
                }
                if (minv[j] < delta) {
                    delta = minv[j];
                    j1 = j;
                }
            }

            for (int j = 0; j <= n; j++) {
                if (used[j]) {
                    u[p[j]] += delta;
                    v[j] -= delta;
                } else {
                    minv[j] -= delta;
                }
            }

            j0 = j1;
        } while (p[j0] != 0);

        do {
            int j1 = way[j0];
            p[j0] = p[j1];
            j0 = j1;
        } while (j0 != 0);
    }

    vector<int> assignment(n + 1, 0);
    for (int j = 1; j <= n; j++) assignment[p[j]] = j;

    long long cost = -v[0];
    cout << cost << "\n";
    for (int i = 1; i <= n; i++) {
        cout << i << " " << assignment[i] << "\n";
    }

    return 0;
}