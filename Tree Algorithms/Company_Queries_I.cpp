#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 200005;
const int LOG = 19;

int up[MAXN][LOG];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    if (!(cin >> n >> q)) return 0;

    for (int i = 2; i <= n; i++) {
        cin >> up[i][0];
    }

    // Precompute binary lifting table
    for (int j = 1; j < LOG; j++) {
        for (int i = 1; i <= n; i++) {
            if (up[i][j - 1] != 0) {
                up[i][j] = up[up[i][j - 1]][j - 1];
            } else {
                up[i][j] = 0;
            }
        }
    }

    while (q--) {
        int x, k;
        cin >> x >> k;
        for (int j = 0; j < LOG; j++) {
            if ((k >> j) & 1) {
                x = up[x][j];
                if (x == 0) break;
            }
        }
        if (x == 0) cout << -1 << "\n";
        else cout << x << "\n";
    }

    return 0;
}
