#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int INF = 1e9;
const int MAX_C = 1000005;

struct Point {
    int x, y, type, id;
    bool operator<(const Point& other) const {
        if (x != other.x) return x < other.x;
        if (y != other.y) return y < other.y;
        return type < other.type;
    }
};

int bit[MAX_C];

void update(int i, int val) {
    for (; i < MAX_C; i += i & -i) bit[i] = max(bit[i], val);
}

int query(int i) {
    int res = -INF;
    for (; i > 0; i -= i & -i) res = max(res, bit[i]);
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<Point> pts(n + m);
    for (int i = 0; i < n; ++i) {
        cin >> pts[i].x >> pts[i].y;
        pts[i].type = 0;
        pts[i].id = -1;
    }
    for (int i = 0; i < m; ++i) {
        cin >> pts[n + i].x >> pts[n + i].y;
        pts[n + i].type = 1;
        pts[n + i].id = i;
    }

    vector<int> ans(m, INF);

    auto solve = [&]() {
        fill(bit, bit + MAX_C, -INF);
        sort(pts.begin(), pts.end());
        for (const auto& p : pts) {
            if (p.type == 0) {
                update(p.y, p.x + p.y);
            } else {
                int mx = query(p.y);
                if (mx != -INF) ans[p.id] = min(ans[p.id], p.x + p.y - mx);
            }
        }
    };

    solve();
    for (auto& p : pts) p.x = MAX_C - p.x;
    solve();
    for (auto& p : pts) p.y = MAX_C - p.y;
    solve();
    for (auto& p : pts) p.x = MAX_C - p.x;
    solve();

    for (int i = 0; i < m; ++i) {
        cout << ans[i] << (i == m - 1 ? "" : " ");
    }
    cout << "\n";

    return 0;
}