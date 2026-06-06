#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Event {
    int x;
    int y1, y2;
    int type;

    bool operator<(const Event& other) const {
        return x < other.x;
    }
};

const int MAX_VAL = 2000005;
const int OFFSET = 1000000;

int tree_count[4 * MAX_VAL];
int tree_len[4 * MAX_VAL];

void update(int node, int start, int end, int l, int r, int val) {
    if (l <= start && end <= r) {
        tree_count[node] += val;
    } else {
        int mid = start + (end - start) / 2;
        if (l <= mid) {
            update(2 * node, start, mid, l, r, val);
        }
        if (r > mid) {
            update(2 * node + 1, mid + 1, end, l, r, val);
        }
    }

    if (tree_count[node] > 0) {
        tree_len[node] = end - start + 1;
    } else {
        if (start == end) {
            tree_len[node] = 0;
        } else {
            tree_len[node] = tree_len[2 * node] + tree_len[2 * node + 1];
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<Event> events;
    events.reserve(2 * n);

    for (int i = 0; i < n; ++i) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        
        y1 += OFFSET;
        y2 += OFFSET;

        events.push_back({x1, y1, y2 - 1, 1});
        events.push_back({x2, y1, y2 - 1, -1});
    }

    sort(events.begin(), events.end());

    long long total_area = 0;
    int last_x = events[0].x;

    for (const auto& event : events) {
        long long delta_x = event.x - last_x;
        
        total_area += delta_x * tree_len[1];

        update(1, 0, MAX_VAL - 1, event.y1, event.y2, event.type);
        
        last_x = event.x;
    }

    cout << total_area << "\n";

    return 0;
}