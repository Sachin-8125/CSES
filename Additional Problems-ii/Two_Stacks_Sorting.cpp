#include <iostream>
#include <vector>
#include <stack>
#include <set>
#include <algorithm>

using namespace std;

const int INF = 1e9 + 7;

int n;
vector<int> A, parent_dsu;
vector<set<pair<int, int>>> active_elements;
pair<int, int> tree[800005];

void update(int node, int start, int end, int idx, int val) {
    if (start == end) {
        tree[node] = {val, start};
        return;
    }
    int mid = (start + end) / 2;
    if (idx <= mid) update(2 * node, start, mid, idx, val);
    else update(2 * node + 1, mid + 1, end, idx, val);
    tree[node] = min(tree[2 * node], tree[2 * node + 1]);
}

pair<int, int> query(int node, int start, int end, int l, int r) {
    if (r < start || end < l) return {INF, -1};
    if (l <= start && end <= r) return tree[node];
    int mid = (start + end) / 2;
    return min(query(2 * node, start, mid, l, r), query(2 * node + 1, mid + 1, end, l, r));
}

int find_set(int v) {
    if (v == parent_dsu[v]) return v;
    return parent_dsu[v] = find_set(parent_dsu[v]);
}

void merge_roots(int u, int v) {
    int root_u = find_set(u);
    int root_v = find_set(v);
    if (root_u == root_v) return;
    
    if (!active_elements[root_u].empty()) {
        auto rep_u = *active_elements[root_u].begin();
        update(1, 1, n, rep_u.second, INF);
    }
    if (!active_elements[root_v].empty()) {
        auto rep_v = *active_elements[root_v].begin();
        update(1, 1, n, rep_v.second, INF);
    }
    
    if (active_elements[root_u].size() < active_elements[root_v].size()) {
        swap(root_u, root_v);
    }
    
    parent_dsu[root_v] = root_u;
    for (auto& eq : active_elements[root_v]) {
        active_elements[root_u].insert(eq);
    }
    active_elements[root_v].clear();
    
    if (!active_elements[root_u].empty()) {
        auto rep_new = *active_elements[root_u].begin();
        update(1, 1, n, rep_new.second, rep_new.first);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (!(cin >> n)) return 0;

    A.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> A[i];
    }

    vector<int> min_after(n + 2, INF);
    for (int i = n; i >= 1; i--) {
        min_after[i] = min(min_after[i + 1], A[i]);
    }

    vector<int> R_idx(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        int left = i + 1, right = n, best = i;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (min_after[mid] < A[i]) {
                best = mid;
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        R_idx[i] = best;
    }

    vector<vector<int>> expires_at(n + 2);
    for (int i = 1; i <= n; i++) {
        expires_at[R_idx[i] + 1].push_back(i);
    }

    parent_dsu.resize(2 * n + 1);
    for (int i = 1; i <= 2 * n; i++) parent_dsu[i] = i;

    active_elements.resize(2 * n + 1);
    for (int i = 1; i <= 4 * n; i++) tree[i] = {INF, -1};

    for (int j = 1; j <= n; j++) {
        for (int i : expires_at[j]) {
            int r = find_set(i);
            if (!active_elements[r].empty()) {
                auto rep = *active_elements[r].begin();
                update(1, 1, n, rep.second, INF);
            }
            active_elements[r].erase({A[i], i});
            if (!active_elements[r].empty()) {
                auto rep = *active_elements[r].begin();
                update(1, 1, n, rep.second, rep.first);
            }
        }

        vector<int> conflicts;
        while (true) {
            pair<int, int> res = query(1, 1, n, 1, j - 1);
            if (res.first >= A[j]) break;
            conflicts.push_back(res.second);
            update(1, 1, n, res.second, INF);
        }

        active_elements[j].insert({A[j], j});
        update(1, 1, n, j, A[j]);

        for (int i : conflicts) {
            merge_roots(j + n, i);
            merge_roots(j, i + n);
        }
    }

    for (int i = 1; i <= n; i++) {
        if (find_set(i) == find_set(i + n)) {
            cout << "IMPOSSIBLE\n";
            return 0;
        }
    }

    vector<int> color(n + 1, 0);
    vector<int> comp_color(2 * n + 1, 0);
    for (int i = 1; i <= n; i++) {
        int root = find_set(i);
        int root_opp = find_set(i + n);
        if (comp_color[root] == 0) {
            comp_color[root] = 1;
            comp_color[root_opp] = 2;
        }
        color[i] = comp_color[root];
    }

    stack<int> s1, s2;
    int next_out = 1;
    for (int i = 1; i <= n; i++) {
        if (color[i] == 1) s1.push(A[i]);
        else s2.push(A[i]);

        while (!s1.empty() || !s2.empty()) {
            if (!s1.empty() && s1.top() == next_out) { s1.pop(); next_out++; }
            else if (!s2.empty() && s2.top() == next_out) { s2.pop(); next_out++; }
            else break;
        }
    }

    if (next_out <= n) {
        cout << "IMPOSSIBLE\n";
    } else {
        for (int i = 1; i <= n; i++) {
            cout << color[i] << (i == n ? "" : " ");
        }
        cout << "\n";
    }

    return 0;
}