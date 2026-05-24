#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2e5 + 5;

int n, k;
vector<int> adj[MAXN];
int subtree_sz[MAXN];
bool removed[MAXN];
long long ans = 0;

// Global cnt array — only reset indices we actually touch
int cnt[MAXN];

int get_sz(int u, int p) {
    subtree_sz[u] = 1;
    for (int v : adj[u]) {
        if (v != p && !removed[v])
            subtree_sz[u] += get_sz(v, u);
    }
    return subtree_sz[u];
}

int get_centroid(int u, int p, int tree_sz) {
    for (int v : adj[u]) {
        if (v != p && !removed[v] && subtree_sz[v] > tree_sz / 2)
            return get_centroid(v, u, tree_sz);
    }
    return u;
}

void collect(int u, int p, int depth, vector<int>& depths) {
    if (depth > k) return;
    depths.push_back(depth);
    for (int v : adj[u]) {
        if (v != p && !removed[v])
            collect(v, u, depth + 1, depths);
    }
}

void solve(int u) {
    int sz = get_sz(u, -1);
    int c = get_centroid(u, -1, sz);
    removed[c] = true;

    // Track which indices of cnt we touched so we can reset them
    vector<int> touched;
    cnt[0] = 1;
    touched.push_back(0);

    for (int v : adj[c]) {
        if (removed[v]) continue;

        vector<int> depths;
        collect(v, c, 1, depths);

        // Count paths: pair depth d with depth (k - d)
        for (int d : depths) {
            int need = k - d;
            if (need >= 0 && need <= k)
                ans += cnt[need];
        }

        // Add to cnt, track touched indices
        for (int d : depths) {
            if (cnt[d] == 0) touched.push_back(d);
            cnt[d]++;
        }
    }

    // Reset only touched indices — O(subtree size) not O(k)
    for (int idx : touched) cnt[idx] = 0;

    for (int v : adj[c]) {
        if (!removed[v])
            solve(v);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    solve(1);
    cout << ans << "\n";
    return 0;
}