#include <iostream>
#include <vector>
#include <string>

using namespace std;

int n, q;
vector<vector<int>> bit;
vector<string> grid;

void update(int r, int c, int val) {
    for (int i = r; i <= n; i += i & -i) {
        for (int j = c; j <= n; j += j & -j) {
            bit[i][j] += val;
        }
    }
}

int query(int r, int c) {
    int sum = 0;
    for (int i = r; i > 0; i -= i & -i) {
        for (int j = c; j > 0; j -= j & -j) {
            sum += bit[i][j];
        }
    }
    return sum;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (!(cin >> n >> q)) return 0;

    grid.resize(n);
    bit.assign(n + 1, vector<int>(n + 1, 0));

    for (int i = 0; i < n; ++i) {
        cin >> grid[i];
        for (int j = 0; j < n; ++j) {
            if (grid[i][j] == '*') {
                update(i + 1, j + 1, 1);
            }
        }
    }

    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            int y, x;
            cin >> y >> x;
            if (grid[y - 1][x - 1] == '.') {
                grid[y - 1][x - 1] = '*';
                update(y, x, 1);
            } else {
                grid[y - 1][x - 1] = '.';
                update(y, x, -1);
            }
        } else if (type == 2) {
            int y1, x1, y2, x2;
            cin >> y1 >> x1 >> y2 >> x2;
            int ans = query(y2, x2) - query(y1 - 1, x2) - query(y2, x1 - 1) + query(y1 - 1, x1 - 1);
            cout << ans << "\n";
        }
    }

    return 0;
}