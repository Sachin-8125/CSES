#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to;
    int rev;
    int cap;
    int cost;
};

struct MinCostMaxFlow {
    int N;
    vector<vector<Edge>> g;

    MinCostMaxFlow(int n) : N(n), g(n + 1) {}

    void addEdge(int u, int v, int cap, int cost) {
        Edge a{v, (int)g[v].size(), cap, cost};
        Edge b{u, (int)g[u].size(), 0, -cost};
        g[u].push_back(a);
        g[v].push_back(b);
    }

    pair<int, long long> minCostFlow(int s, int t, int maxf) {
        const long long INF = (1LL<<60);
        vector<long long> pot(N + 1, 0), dist(N + 1);
        vector<int> pv(N + 1), pe(N + 1);

        int flow = 0;
        long long cost = 0;

        while (flow < maxf) {
            fill(dist.begin(), dist.end(), INF);
            dist[s] = 0;
            priority_queue<pair<long long,int>, vector<pair<long long,int>>, greater<pair<long long,int>>> pq;
            pq.push({0, s});

            while (!pq.empty()) {
                auto [d, v] = pq.top();
                pq.pop();
                if (d != dist[v]) continue;
                for (int i = 0; i < (int)g[v].size(); i++) {
                    const Edge &e = g[v][i];
                    if (e.cap <= 0) continue;
                    long long nd = d + e.cost + pot[v] - pot[e.to];
                    if (nd < dist[e.to]) {
                        dist[e.to] = nd;
                        pv[e.to] = v;
                        pe[e.to] = i;
                        pq.push({nd, e.to});
                    }
                }
            }

            if (dist[t] == INF) break;

            for (int v = 1; v <= N; v++) {
                if (dist[v] < INF) pot[v] += dist[v];
            }

            int add = maxf - flow;
            for (int v = t; v != s; v = pv[v]) {
                add = min(add, g[pv[v]][pe[v]].cap);
            }

            for (int v = t; v != s; v = pv[v]) {
                Edge &e = g[pv[v]][pe[v]];
                Edge &r = g[v][e.rev];
                e.cap -= add;
                r.cap += add;
            }

            flow += add;
            cost += 1LL * add * (pot[t] - pot[s]);
        }

        return {flow, cost};
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;

    MinCostMaxFlow mcmf(n);

    vector<int> U(m), V(m), idxInAdj(m);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        U[i] = a; V[i] = b;
        int pos = (int)mcmf.g[a].size();
        mcmf.addEdge(a, b, 1, 1);
        idxInAdj[i] = pos;
    }

    auto [flow, cost] = mcmf.minCostFlow(1, n, k);
    if (flow < k) {
        cout << -1 << "\n";
        return 0;
    }

    vector<int> remFlow(m, 0);
    for (int i = 0; i < m; i++) {
        int a = U[i], b = V[i];
        int idx = idxInAdj[i];
        int revIdx = mcmf.g[a][idx].rev;
        remFlow[i] = mcmf.g[b][revIdx].cap;
    }

    vector<vector<pair<int,int>>> out(n + 1);
    for (int i = 0; i < m; i++) {
        if (remFlow[i] > 0) out[U[i]].push_back({V[i], i});
        else out[U[i]].push_back({V[i], i});
    }

    for (int i = 1; i <= n; i++) {
        sort(out[i].begin(), out[i].end());
    }

    cout << cost << "\n";

    vector<int> prevNode(n + 1), prevEdge(n + 1);
    vector<int> usedPathEdges;
    vector<int> q;
    q.reserve(n);

    for (int day = 0; day < k; day++) {
        fill(prevNode.begin(), prevNode.end(), -1);
        fill(prevEdge.begin(), prevEdge.end(), -1);

        deque<int> dq;
        dq.push_back(1);
        prevNode[1] = 1;

        while (!dq.empty() && prevNode[n] == -1) {
            int u = dq.front();
            dq.pop_front();
            for (auto [v, id] : out[u]) {
                if (remFlow[id] <= 0) continue;
                if (prevNode[v] != -1) continue;
                prevNode[v] = u;
                prevEdge[v] = id;
                dq.push_back(v);
                if (v == n) break;
            }
        }

        if (prevNode[n] == -1) {
            cout << "0\n\n";
            return 0;
        }

        vector<int> pathNodes;
        int cur = n;
        while (cur != 1) {
            pathNodes.push_back(cur);
            int e = prevEdge[cur];
            usedPathEdges.push_back(e);
            cur = prevNode[cur];
        }
        pathNodes.push_back(1);
        reverse(pathNodes.begin(), pathNodes.end());

        for (int eId : usedPathEdges) remFlow[eId]--;
        usedPathEdges.clear();

        cout << pathNodes.size() << "\n";
        for (int i = 0; i < (int)pathNodes.size(); i++) {
            if (i) cout << ' ';
            cout << pathNodes[i];
        }
        cout << "\n";
    }

    return 0;
}