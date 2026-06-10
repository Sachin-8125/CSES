#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int INF = 1e9;

struct SegmentTree {
    int n;
    vector<int> tree;

    SegmentTree(int n) : n(n), tree(2 * n, INF) {}

    void update(int idx, int val) {
        idx += n - 1;
        tree[idx] = val;
        for (idx /= 2; idx >= 1; idx /= 2) {
            tree[idx] = min(tree[2 * idx], tree[2 * idx + 1]);
        }
    }

    int query(int l, int r) {
        int res = INF;
        for (l += n - 1, r += n; l < r; l /= 2, r /= 2) {
            if (l & 1) res = min(res, tree[l++]);
            if (r & 1) res = min(res, tree[--r]);
        }
        return res;
    }
};

vector<int> values;
int get_compressed_id(int x) {
    auto it = lower_bound(values.begin(), values.end(), x);
    if (it == values.end() || *it != x) return 0;
    return (it - values.begin()) + 1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    if (!(cin >> n >> q)) return 0;

    vector<int> a(n + 1);
    struct Query { int type, l, r; };
    vector<Query> queries(q);

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        values.push_back(a[i]);
    }
    for (int i = 0; i < q; i++) {
        cin >> queries[i].type >> queries[i].l >> queries[i].r;
        if (queries[i].type == 1) {
            values.push_back(queries[i].r);
        }
    }

    sort(values.begin(), values.end());
    values.erase(unique(values.begin(), values.end()), values.end());
    int num_unique = values.size();

    vector<int> head(num_unique + 1, 0);
    vector<int> nxt(n + 1, n + 1), prv(n + 1, 0);
    vector<int> last_pos(num_unique + 1, 0);

    for (int i = 1; i <= n; i++) {
        int id = get_compressed_id(a[i]);
        if (last_pos[id] != 0) {
            nxt[last_pos[id]] = i;
            prv[i] = last_pos[id];
        } else {
            head[id] = i;
        }
        last_pos[id] = i;
    }

    SegmentTree st(n + 1);
    for (int i = 1; i <= n; i++) {
        st.update(i, nxt[i]);
    }

    for (int i = 0; i < q; i++) {
        if (queries[i].type == 1) {
            int k = queries[i].l;
            int u = queries[i].r;
            if (a[k] == u) continue;

            int old_id = get_compressed_id(a[k]);
            int new_id = get_compressed_id(u);

            int p_k = prv[k], n_k = nxt[k];
            if (p_k != 0) {
                nxt[p_k] = n_k;
                st.update(p_k, n_k);
            } else {
                head[old_id] = (n_k == n + 1) ? 0 : n_k;
            }
            if (n_k != n + 1) {
                prv[n_k] = p_k;
            }

            a[k] = u;
            if (head[new_id] == 0 || k < head[new_id]) {
                int old_head = head[new_id];
                head[new_id] = k;
                prv[k] = 0;
                nxt[k] = (old_head == 0) ? n + 1 : old_head;
                if (old_head != 0) prv[old_head] = k;
                st.update(k, nxt[k]);
            } else {
                int curr = head[new_id];
                while (nxt[curr] != n + 1 && nxt[curr] < k) {
                    curr = nxt[curr];
                }
                int next_node = nxt[curr];
                nxt[curr] = k;
                st.update(curr, k);
                prv[k] = curr;
                nxt[k] = next_node;
                if (next_node != n + 1) prv[next_node] = k;
                st.update(k, nxt[k]);
            }
        } 
        else {
            int l = queries[i].l;
            int r = queries[i].r;
            if (st.query(l, r) > r) {
                cout << "YES\n";
            } else {
                cout << "NO\n";
            }
        }
    }

    return 0;
}