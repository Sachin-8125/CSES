#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 2e5 + 5;
vector<int> adj[MAXN];
bool visited[MAXN];
int count = 0;

void dfs(int u, int p) {
    for (int v : adj[u]) {
        if (v != p) {
            dfs(v, u);
            if (!visited[v] && !visited[u]) {
                visited[v] = true;
                visited[u] = true;
                count++;
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs(1, 0);

    cout << count << endl;

    return 0;
}