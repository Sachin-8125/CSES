#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    vector<int> b(m);
    for (int i = 0; i < m; i++) cin >> b[i];

    vector<int> posA(n + 1, -1);
    for (int i = 0; i < n; i++) {
        posA[a[i]] = i;
    }

    vector<int> seq;
    vector<int> seqVal;
    seq.reserve(m);
    seqVal.reserve(m);

    for (int i = 0; i < m; i++) {
        int v = b[i];
        if (v >= 1 && v <= n && posA[v] != -1) {
            seq.push_back(posA[v]);
            seqVal.push_back(v);
        }
    }

    int k = (int)seq.size();
    if (k == 0) {
        cout << 0 << '\n';
        return 0;
    }

    vector<int> lisEnd;
    lisEnd.reserve(k);

    vector<int> parent(k, -1);

    for (int i = 0; i < k; i++) {
        int x = seq[i];
        int l = lower_bound(
            lisEnd.begin(), lisEnd.end(), x,
            [&](int idx, int val) { return seq[idx] < val; }
        ) - lisEnd.begin();

        if (l == (int)lisEnd.size()) {
            lisEnd.push_back(i);
        } else {
            lisEnd[l] = i;
        }

        if (l > 0) parent[i] = lisEnd[l - 1];
    }

    int lisLen = (int)lisEnd.size();
    vector<int> lisIdx;
    lisIdx.reserve(lisLen);
    int cur = lisEnd.back();
    while (cur != -1) {
        lisIdx.push_back(cur);
        cur = parent[cur];
    }
    reverse(lisIdx.begin(), lisIdx.end());

    cout << lisLen << '\n';
    for (int i = 0; i < lisLen; i++) {
        if (i) cout << ' ';
        cout << seqVal[lisIdx[i]];
    }
    cout << '\n';

    return 0;
}