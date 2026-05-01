#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct SegmentTree {
    int n;
    vector<int> tree;

    SegmentTree(int n) : n(n), tree(2 * n, 0) {}

    void update(int pos, int value) {
        for (tree[pos += n] = value; pos > 1; pos >>= 1) {
            tree[pos >> 1] = max(tree[pos], tree[pos ^ 1]);
        }
    }

    int query(int l, int r) {
        int res = 0;
        for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
            if (l & 1) res = max(res, tree[l++]);
            if (r & 1) res = max(res, tree[--r]);
        }
        return res;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;

    vector<int> h(n);
    vector<pair<int, int>> mountains(n);
    for (int i = 0; i < n; i++) {
        cin >> h[i];
        mountains[i] = {h[i], i};
    }

    vector<int> L(n, -1), R(n, n);
    vector<int> st;

    for (int i = 0; i < n; i++) {
        while (!st.empty() && h[st.back()] < h[i]) {
            st.pop_back();
        }
        if (!st.empty()) L[i] = st.back();
        st.push_back(i);
    }

    st.clear();
    for (int i = n - 1; i >= 0; i--) {
        while (!st.empty() && h[st.back()] < h[i]) {
            st.pop_back();
        }
        if (!st.empty()) R[i] = st.back();
        st.push_back(i);
    }

    sort(mountains.begin(), mountains.end());

    SegmentTree segTree(n);
    vector<int> dp(n, 0);
    int max_path = 0;

    for (int i = 0; i < n; ) {
        int j = i;
        while (j < n && mountains[j].first == mountains[i].first) {
            j++;
        }

        for (int k = i; k < j; k++) {
            int idx = mountains[k].second;
            int left_bound = L[idx] + 1;
            int right_bound = R[idx] - 1;
            dp[idx] = 1 + segTree.query(left_bound, right_bound);
            max_path = max(max_path, dp[idx]);
        }

        for (int k = i; k < j; k++) {
            int idx = mountains[k].second;
            segTree.update(idx, dp[idx]);
        }

        i = j;
    }

    cout << max_path << "\n";
    return 0;
}