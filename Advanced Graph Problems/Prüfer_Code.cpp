#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> code(max(0, n - 2));
    for (int i = 0; i < n - 2; i++) cin >> code[i];

    vector<int> deg(n + 1, 1);
    for (int x : code) deg[x]++;

    priority_queue<int, vector<int>, greater<int>> pq;
    for (int i = 1; i <= n; i++) {
        if (deg[i] == 1) pq.push(i);
    }

    vector<pair<int,int>> edges;
    edges.reserve(n - 1);

    for (int x : code) {
        int leaf = pq.top(); pq.pop();
        edges.push_back({leaf, x});
        deg[leaf]--;
        deg[x]--;
        if (deg[x] == 1) pq.push(x);
    }

    int a = pq.top(); pq.pop();
    int b = pq.top(); pq.pop();
    edges.push_back({a, b});

    for (auto &e : edges) {
        cout << e.first << " " << e.second << "\n";
    }
    return 0;
}