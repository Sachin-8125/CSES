#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 200005;
vector<int> adj[MAXN];
bool removed_node[MAXN];
int subtree_size[MAXN];
int n, k1, k2;
long long ans = 0;

int cnt[MAXN];
int pref[MAXN];
vector<int> current_depths;

int get_subtree_size(int u, int p = 0) {
    subtree_size[u] = 1;
    for (int v : adj[u]) {
        if (v != p && !removed_node[v]) {
            subtree_size[u] += get_subtree_size(v, u);
        }
    }
    return subtree_size[u];
}

int get_centroid(int u, int p, int total) {
    for (int v : adj[u]) {
        if (v != p && !removed_node[v] && subtree_size[v] > total / 2) {
            return get_centroid(v, u, total);
        }
    }
    return u;
}

int get_max_depth(int u, int p, int d) {
    if (d == k2) return d;
    int md = d;
    for (int v : adj[u]) {
        if (v != p && !removed_node[v]) {
            md = max(md, get_max_depth(v, u, d + 1));
        }
    }
    return md;
}

void get_depths(int u, int p, int d) {
    if (d > k2) return;
    current_depths.push_back(d);
    for (int v : adj[u]) {
        if (v != p && !removed_node[v]) {
            get_depths(v, u, d + 1);
        }
    }
}

void solve_centroid(int u) {
    int total = get_subtree_size(u);
    int centroid = get_centroid(u, 0, total);

    removed_node[centroid] = true;

    vector<pair<int, int>> children;
    for (int v : adj[centroid]) {
        if (!removed_node[v]) {
            children.push_back({get_max_depth(v, centroid, 1), v});
        }
    }

    sort(children.begin(), children.end());

    cnt[0] = 1;
    int max_depth_so_far = 0;

    for (auto& child : children) {
        int md = child.first;
        int v = child.second;

        pref[0] = cnt[0];
        for (int i = 1; i <= max_depth_so_far; i++) {
            pref[i] = pref[i - 1] + cnt[i];
        }

        current_depths.clear();
        get_depths(v, centroid, 1);

        for (int d : current_depths) {
            int L = max(0, k1 - d);
            int R = min(max_depth_so_far, k2 - d);
            if (L <= R) {
                ans += pref[R] - (L > 0 ? pref[L - 1] : 0);
            }
        }

        for (int d : current_depths) {
            cnt[d]++;
        }
        max_depth_so_far = max(max_depth_so_far, md);
    }

    for (int i = 0; i <= max_depth_so_far; i++) {
        cnt[i] = 0;
    }

    for (int v : adj[centroid]) {
        if (!removed_node[v]) {
            solve_centroid(v);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    if (!(cin >> n >> k1 >> k2)) return 0;
    
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    solve_centroid(1);
    
    cout << ans << "\n";
    
    return 0;
}