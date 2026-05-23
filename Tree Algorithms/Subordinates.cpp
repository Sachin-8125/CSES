#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 200005;
vector<int> adj[MAXN];
int subordinates[MAXN];

void dfs(int u) {
    subordinates[u] = 0;
    for (int v : adj[u]) {
        dfs(v);
        subordinates[u] += subordinates[v] + 1;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    for (int i = 2; i <= n; i++) {
        int boss;
        cin >> boss;
        adj[boss].push_back(i);
    }

    dfs(1);

    for (int i = 1; i <= n; i++) {
        cout << subordinates[i] << (i == n ? "" : " ");
    }
    cout << endl;

    return 0;
}