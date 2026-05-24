#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 200005;
vector<int> adj[MAXN];
long long val[MAXN];
int st[MAXN], en[MAXN], timer;
long long bit[MAXN];
int n, q;

void update(int i, long long delta) {
    for (; i <= n; i += i & -i)
        bit[i] += delta;
}

long long query(int i) {
    long long res = 0;
    for (; i > 0; i -= i & -i)
        res += bit[i];
    return res;
}

void dfs(int u, int p) {
    st[u] = ++timer;
    for (int v : adj[u]) {
        if (v != p) {
            dfs(v, u);
        }
    }
    en[u] = timer;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (!(cin >> n >> q)) return 0;

    for (int i = 1; i <= n; i++) {
        cin >> val[i];
    }

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs(1, 0);

    for (int i = 1; i <= n; i++) {
        update(st[i], val[i]);
    }

    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            int s;
            long long x;
            cin >> s >> x;
            update(st[s], x - val[s]);
            val[s] = x;
        } else {
            int s;
            cin >> s;
            cout << query(en[s]) - query(st[s] - 1) << "\n";
        }
    }

    return 0;
}
