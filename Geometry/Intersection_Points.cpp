#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX_Y = 2000005;
const int OFFSET = 1000001;

struct FenwickTree {
    vector<int> tree;
    FenwickTree(int n) {
        tree.assign(n + 1, 0);
    }
    void update(int idx, int val) {
        for (; idx < tree.size(); idx += idx & -idx)
            tree[idx] += val;
    }
    int query(int l, int r) {
        if (l > r) return 0;
        int sum_r = 0, sum_l = 0;
        for (int i = r; i > 0; i -= i & -i) sum_r += tree[i];
        for (int i = l - 1; i > 0; i -= i & -i) sum_l += tree[i];
        return sum_r - sum_l;
    }
};

struct Event {
    int x;
    int type;
    int y1, y2;
    
    bool operator<(const Event& other) const {
        if (x != other.x) return x < other.x;
        return type < other.type;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    if (!(cin >> n)) return 0;
    
    vector<Event> events;
    
    for (int i = 0; i < n; i++) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        
        y1 += OFFSET;
        y2 += OFFSET;
        
        if (y1 == y2) {
            if (x1 > x2) swap(x1, x2);
            events.push_back({x1, 0, y1, y2});
            events.push_back({x2, 2, y1, y2});
        } else {
            if (y1 > y2) swap(y1, y2);
            events.push_back({x1, 1, y1, y2});
        }
    }
    
    sort(events.begin(), events.end());
    
    FenwickTree bit(MAX_Y);
    long long intersections = 0;
    
    for (const auto& ev : events) {
        if (ev.type == 0) {
            bit.update(ev.y1, 1);
        } else if (ev.type == 2) {
            bit.update(ev.y1, -1);
        } else if (ev.type == 1) {
            intersections += bit.query(ev.y1, ev.y2);
        }
    }
    
    cout << intersections << "\n";
    
    return 0;
}