#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXA = 1000005;
const int LOGN = 20;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    if (!(cin >> n >> q)) return 0;

    vector<int> min_end(MAXA, MAXA);

    for (int i = 0; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        if (b < min_end[a]) {
            min_end[a] = b;
        }
    }

    for (int i = MAXA - 2; i >= 1; --i) {
        if (min_end[i + 1] < min_end[i]) {
            min_end[i] = min_end[i + 1];
        }
    }

    vector<vector<int>> nxt(MAXA, vector<int>(LOGN, MAXA));

    for (int i = 1; i < MAXA; ++i) {
        nxt[i][0] = min_end[i];
    }

    for (int j = 1; j < LOGN; ++j) {
        for (int i = 1; i < MAXA; ++i) {
            if (nxt[i][j - 1] < MAXA) {
                nxt[i][j] = nxt[nxt[i][j - 1]][j - 1];
            } else {
                nxt[i][j] = MAXA;
            }
        }
    }

    for (int i = 0; i < q; ++i) {
        int a, b;
        cin >> a >> b;

        int ans = 0;
        int curr = a;

        for (int j = LOGN - 1; j >= 0; --j) {
            if (nxt[curr][j] <= b) {
                ans += (1 << j);
                curr = nxt[curr][j];
            }
        }

        cout << ans << "\n";
    }

    return 0;
}