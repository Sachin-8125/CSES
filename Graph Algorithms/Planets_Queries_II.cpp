#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int MAXN = 200005;
int up[MAXN][20];
int t[MAXN];
int indegree[MAXN];
int depth[MAXN];
int cycle_id[MAXN];
int pos[MAXN];
int cycle_len[MAXN];
vector<int> adj_rev[MAXN];

int advance(int x, int k) {
    for (int j = 0; j < 20; j++) {
        if ((k >> j) & 1) {
            x = up[x][j];
        }
    }
    return x;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    if (!(cin >> n >> q)) return 0;

    for (int i = 1; i <= n; i++) {
        cin >> t[i];
        up[i][0] = t[i];
        indegree[t[i]]++;
        adj_rev[t[i]].push_back(i);
    }

    for (int j = 1; j < 20; j++) {
        for (int i = 1; i <= n; i++) {
            up[i][j] = up[up[i][j - 1]][j - 1];
        }
    }

    queue<int> Q;
    for (int i = 1; i <= n; i++) {
        if (indegree[i] == 0) {
            Q.push(i);
        }
    }

    while (!Q.empty()) {
        int u = Q.front();
        Q.pop();
        int v = t[u];
        indegree[v]--;
        if (indegree[v] == 0) {
            Q.push(v);
        }
    }

    int c_id = 1;
    for (int i = 1; i <= n; i++) {
        if (indegree[i] > 0 && cycle_id[i] == 0) {
            int curr = i;
            int idx = 0;
            while (cycle_id[curr] == 0) {
                cycle_id[curr] = c_id;
                pos[curr] = idx++;
                curr = t[curr];
            }
            cycle_len[c_id] = idx;
            c_id++;
        }
    }

    for (int i = 1; i <= n; i++) {
        if (indegree[i] > 0) {
            depth[i] = 0;
            Q.push(i);
        }
    }

    while (!Q.empty()) {
        int u = Q.front();
        Q.pop();
        for (int v : adj_rev[u]) {
            if (indegree[v] == 0) {
                depth[v] = depth[u] + 1;
                cycle_id[v] = cycle_id[u];
                Q.push(v);
            }
        }
    }

    while (q--) {
        int a, b;
        cin >> a >> b;

        if (depth[a] < depth[b]) {
            cout << -1 << "\n";
            continue;
        }

        int a_prime = advance(a, depth[a] - depth[b]);
        if (a_prime == b) {
            cout << depth[a] - depth[b] << "\n";
        } else if (depth[b] == 0 && cycle_id[a_prime] == cycle_id[b]) {
            int dist = (pos[b] - pos[a_prime] + cycle_len[cycle_id[b]]) % cycle_len[cycle_id[b]];
            cout << depth[a] + dist << "\n";
        } else {
            cout << -1 << "\n";
        }
    }

    return 0;
}