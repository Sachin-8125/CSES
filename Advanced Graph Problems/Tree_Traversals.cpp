#include <bits/stdc++.h>
using namespace std;

struct Frame {
    int preL, preR, inL, inR;
    bool outRoot;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> pre(n), in(n);
    for (int i = 0; i < n; i++) cin >> pre[i];
    for (int i = 0; i < n; i++) cin >> in[i];

    vector<int> pos(n + 1);
    for (int i = 0; i < n; i++) pos[in[i]] = i;

    vector<int> post;
    post.reserve(n);

    stack<Frame> st;
    st.push({0, n - 1, 0, n - 1, false});

    while (!st.empty()) {
        Frame f = st.top();
        st.pop();

        if (f.preL > f.preR) continue;

        if (f.outRoot) {
            post.push_back(pre[f.preL]);
            continue;
        }

        int root = pre[f.preL];
        int idx = pos[root];
        int leftSize = idx - f.inL;

        st.push({f.preL, f.preR, f.inL, f.inR, true}); // output root after subtrees

        int rightL = f.preL + 1 + leftSize;
        int rightR = f.preR;
        if (rightL <= rightR) {
            st.push({rightL, rightR, idx + 1, f.inR, false});
        }

        int leftL = f.preL + 1;
        int leftR = f.preL + leftSize;
        if (leftL <= leftR) {
            st.push({leftL, leftR, f.inL, idx - 1, false});
        }
    }

    for (int i = 0; i < n; i++) {
        if (i) cout << ' ';
        cout << post[i];
    }
    cout << "\n";
    return 0;
}