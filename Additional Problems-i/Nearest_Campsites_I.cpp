#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int INF = 1e9;
const int MAX_C = 1000005;

int bit_arr[MAX_C];
vector<int> modified;

void update(int i, int val) {
    for (; i < MAX_C; i += i & -i) {
        if (bit_arr[i] == -INF) modified.push_back(i);
        bit_arr[i] = max(bit_arr[i], val);
    }
}

int query(int i) {
    int mx = -INF;
    for (; i > 0; i -= i & -i) {
        mx = max(mx, bit_arr[i]);
    }
    return mx;
}

void reset_bit() {
    for (int i : modified) {
        bit_arr[i] = -INF;
    }
    modified.clear();
}

struct Point {
    int x, y, id;
    bool is_res;
};

int min_dist[100005];

void solve_quadrant(vector<Point> p) {
    sort(p.begin(), p.end(), [](const Point& a, const Point& b) {
        if (a.x != b.x) return a.x < b.x;
        if (a.y != b.y) return a.y < b.y;
        return a.is_res > b.is_res;
    });
    
    reset_bit();
    
    for (auto& pt : p) {
        if (pt.is_res) {
            update(pt.y, pt.x + pt.y);
        } else {
            int val = query(pt.y);
            if (val != -INF) {
                min_dist[pt.id] = min(min_dist[pt.id], pt.x + pt.y - val);
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<Point> pts;
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        pts.push_back({x, y, -1, true});
    }
    
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        pts.push_back({x, y, i, false});
        min_dist[i] = INF;
    }

    fill(bit_arr, bit_arr + MAX_C, -INF);

    int MX = 1000005;
    int MY = 1000005;

    for (int dir = 0; dir < 4; dir++) {
        vector<Point> trans = pts;
        for (auto& p : trans) {
            if (dir == 1) p.y = MY - p.y;
            else if (dir == 2) p.x = MX - p.x;
            else if (dir == 3) {
                p.x = MX - p.x;
                p.y = MY - p.y;
            }
        }
        solve_quadrant(trans);
    }

    int ans = 0;
    for (int i = 0; i < m; i++) {
        ans = max(ans, min_dist[i]);
    }
    
    cout << ans << "\n";

    return 0;
}