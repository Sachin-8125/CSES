#include <iostream>
#include <vector>
#include <map>

using namespace std;

const int MAXN = 100005;
const int MAXK = 100005;

int parent_[MAXN], rank_[MAXN];
int n, m, k, num_components;
vector<pair<int,int>> tree[4 * MAXK];
vector<int> results;

int find_root(int x) {
    while (parent_[x] != x) x = parent_[x];
    return x;
}

struct Rollback { int y, old_parent_y, x, old_rank_x; bool merged; };
vector<Rollback> rollback_stack;

void unite(int a, int b) {
    int x = find_root(a), y = find_root(b);
    Rollback r;
    if (x == y) { r.merged = false; rollback_stack.push_back(r); return; }
    if (rank_[x] < rank_[y]) swap(x, y);
    r = {y, parent_[y], x, rank_[x], true};
    parent_[y] = x;
    if (rank_[x] == rank_[y]) rank_[x]++;
    num_components--;
    rollback_stack.push_back(r);
}

void undo() {
    Rollback r = rollback_stack.back(); rollback_stack.pop_back();
    if (r.merged) { parent_[r.y] = r.old_parent_y; rank_[r.x] = r.old_rank_x; num_components++; }
}

void add_edge(int node, int tl, int tr, int l, int r, pair<int,int> edge) {
    if (r < tl || tr < l) return;
    if (l <= tl && tr <= r) { tree[node].push_back(edge); return; }
    int mid = (tl + tr) / 2;
    add_edge(2*node, tl, mid, l, r, edge);
    add_edge(2*node+1, mid+1, tr, l, r, edge);
}

void dfs(int node, int tl, int tr) {
    int ops = 0;
    for (auto& e : tree[node]) { unite(e.first, e.second); ops++; }
    if (tl == tr) results.push_back(num_components);
    else { int mid = (tl + tr) / 2; dfs(2*node, tl, mid); dfs(2*node+1, mid+1, tr); }
    while (ops--) undo();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++) { parent_[i] = i; rank_[i] = 0; }
    num_components = n;
    
    map<pair<int,int>, int> edge_start;
    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        if (a > b) swap(a, b);
        edge_start[{a, b}] = 0;
    }
    
    vector<tuple<int,int,int>> events(k);
    for (int i = 0; i < k; i++) {
        int t, a, b; cin >> t >> a >> b;
        if (a > b) swap(a, b);
        events[i] = {t, a, b};
    }
    
    vector<tuple<int,int,int,int>> intervals;
    for (int i = 0; i < k; i++) {
        auto [t, a, b] = events[i];
        if (t == 1) edge_start[{a, b}] = i + 1;
        else { intervals.push_back({a, b, edge_start[{a,b}], i}); edge_start.erase({a, b}); }
    }
    for (auto& [edge, start] : edge_start)
        intervals.push_back({edge.first, edge.second, start, k});
    
    for (auto& [a, b, l, r] : intervals)
        add_edge(1, 0, k, l, r, {a, b});
    
    dfs(1, 0, k);
    
    for (int i = 0; i <= k; i++) cout << results[i] << " \n"[i == k];
    return 0;
}