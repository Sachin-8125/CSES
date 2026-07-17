#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 200005;
const int LOGK = 30;
int up[MAXN][LOGK];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    if (!(cin >> n >> q)) return 0;

    for (int i = 1; i <= n; i++) {
        cin >> up[i][0];
    }

    for (int j = 1; j < LOGK; j++) {
        for (int i = 1; i <= n; i++) {
            up[i][j] = up[up[i][j-1]][j-1];
        }
    }

    while (q--) {
        int x, k;
        cin >> x >> k;
        for (int j = 0; j < LOGK; j++) {
            if ((k >> j) & 1) {
                x = up[x][j];
            }
        }
        cout << x << "\n";
    }

    return 0;
}