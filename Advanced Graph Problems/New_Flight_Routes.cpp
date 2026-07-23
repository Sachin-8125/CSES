#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<vector<int>> adj(n + 1), radj(n + 1);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        radj[v].push_back(u);
    }

    vector<bool> vis(n + 1, false);
    vector<int> order;
    
    auto dfs1 = [&](auto& self, int u) -> void {
        vis[u] = true;
        for (int v : adj[u]) {
            if (!vis[v]) self(self, v);
        }
        order.push_back(u);
    };

    for (int i = 1; i <= n; ++i) {
        if (!vis[i]) dfs1(dfs1, i);
    }

    vector<int> scc(n + 1, -1);
    int num_scc = 0;
    
    auto dfs2 = [&](auto& self, int u) -> void {
        scc[u] = num_scc;
        for (int v : radj[u]) {
            if (scc[v] == -1) self(self, v);
        }
    };

    for (int i = n - 1; i >= 0; --i) {
        if (scc[order[i]] == -1) {
            dfs2(dfs2, order[i]);
            num_scc++;
        }
    }

    if (num_scc == 1) {
        cout << 0 << "\n";
        return 0;
    }

    vector<int> in_deg(num_scc, 0), out_deg(num_scc, 0);
    vector<vector<int>> dag(num_scc);
    vector<int> scc_rep(num_scc);

    for (int u = 1; u <= n; ++u) {
        scc_rep[scc[u]] = u;
        for (int v : adj[u]) {
            if (scc[u] != scc[v]) {
                dag[scc[u]].push_back(scc[v]);
                out_deg[scc[u]]++;
                in_deg[scc[v]]++;
            }
        }
    }

    vector<int> sources, sinks;
    vector<bool> is_sink(num_scc, false);

    for (int i = 0; i < num_scc; ++i) {
        if (in_deg[i] == 0) sources.push_back(i);
        if (out_deg[i] == 0) {
            sinks.push_back(i);
            is_sink[i] = true;
        }
    }

    vector<int> matched_T_of_S(num_scc, -1);
    vector<int> matched_S_of_T(num_scc, -1);
    vector<bool> dag_vis(num_scc, false);

    vector<int> matched_S_list;
    vector<int> matched_T_list;

    for (int s : sources) {
        auto dfs = [&](auto& self, int u) -> int {
            dag_vis[u] = true;
            if (is_sink[u] && matched_S_of_T[u] == -1) {
                return u;
            }
            for (int v : dag[u]) {
                if (!dag_vis[v]) {
                    int res = self(self, v);
                    if (res != -1) return res;
                }
            }
            return -1;
        };
        
        int t = dfs(dfs, s);
        if (t != -1) {
            matched_T_of_S[s] = t;
            matched_S_of_T[t] = s;
            matched_S_list.push_back(s);
            matched_T_list.push_back(t);
        }
    }

    vector<int> unmatched_S, unmatched_T;
    for (int s : sources) {
        if (matched_T_of_S[s] == -1) unmatched_S.push_back(s);
    }
    for (int t : sinks) {
        if (matched_S_of_T[t] == -1) unmatched_T.push_back(t);
    }

    vector<pair<int, int>> ans;
    int k = matched_S_list.size();

    for (int i = 0; i < k; ++i) {
        ans.push_back({matched_T_list[i], matched_S_list[(i + 1) % k]});
    }

    int m_unmatched = min(unmatched_S.size(), unmatched_T.size());
    for (int i = 0; i < m_unmatched; ++i) {
        ans.push_back({unmatched_T[i], unmatched_S[i]});
    }
    for (int i = m_unmatched; i < unmatched_S.size(); ++i) {
        ans.push_back({matched_T_list[0], unmatched_S[i]});
    }
    for (int i = m_unmatched; i < unmatched_T.size(); ++i) {
        ans.push_back({unmatched_T[i], matched_S_list[0]});
    }

    cout << ans.size() << "\n";
    for (const auto& p : ans) {
        cout << scc_rep[p.first] << " " << scc_rep[p.second] << "\n";
    }

    return 0;
}