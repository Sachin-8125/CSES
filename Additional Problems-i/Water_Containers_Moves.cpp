#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int a, b, x;
    if (!(cin >> a >> b >> x)) return 0;
    
    if (x > a) {
        cout << -1 << "\n";
        return 0;
    }
    
    int n_states = (a + 1) * (b + 1);
    vector<long long> dist(n_states, -1);
    vector<int> parent(n_states, -1);
    vector<int> move_type(n_states, -1);
    
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
    
    dist[0] = 0;
    pq.push({0, 0});
    
    int target_u = -1;
    
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        
        if (d > dist[u]) continue;
        
        int i = u / (b + 1);
        int j = u % (b + 1);

        if (i == x) {
            target_u = u;
            break;
        }
        
        // 0: FILL A
        if (i < a) {
            int v = a * (b + 1) + j;
            long long w = a - i;
            if (dist[v] == -1 || dist[v] > d + w) {
                dist[v] = d + w;
                parent[v] = u;
                move_type[v] = 0;
                pq.push({dist[v], v});
            }
        }
        
        // 1: FILL B
        if (j < b) {
            int v = i * (b + 1) + b;
            long long w = b - j;
            if (dist[v] == -1 || dist[v] > d + w) {
                dist[v] = d + w;
                parent[v] = u;
                move_type[v] = 1;
                pq.push({dist[v], v});
            }
        }
        
        // 2: EMPTY A
        if (i > 0) {
            int v = 0 * (b + 1) + j;
            long long w = i;
            if (dist[v] == -1 || dist[v] > d + w) {
                dist[v] = d + w;
                parent[v] = u;
                move_type[v] = 2;
                pq.push({dist[v], v});
            }
        }
        
        // 3: EMPTY B
        if (j > 0) {
            int v = i * (b + 1) + 0;
            long long w = j;
            if (dist[v] == -1 || dist[v] > d + w) {
                dist[v] = d + w;
                parent[v] = u;
                move_type[v] = 3;
                pq.push({dist[v], v});
            }
        }
        
        // 4: MOVE A B
        if (i > 0 && j < b) {
            long long w = min(i, b - j);
            int v = (i - w) * (b + 1) + (j + w);
            if (dist[v] == -1 || dist[v] > d + w) {
                dist[v] = d + w;
                parent[v] = u;
                move_type[v] = 4;
                pq.push({dist[v], v});
            }
        }
        
        // 5: MOVE B A
        if (j > 0 && i < a) {
            long long w = min(j, a - i);
            int v = (i + w) * (b + 1) + (j - w);
            if (dist[v] == -1 || dist[v] > d + w) {
                dist[v] = d + w;
                parent[v] = u;
                move_type[v] = 5;
                pq.push({dist[v], v});
            }
        }
    }
    
    if (target_u == -1) {
        cout << -1 << "\n";
    } else {
        vector<int> path;
        int curr = target_u;
        while (curr != 0) {
            path.push_back(move_type[curr]);
            curr = parent[curr];
        }
        reverse(path.begin(), path.end());
        
        cout << path.size() << " " << dist[target_u] << "\n";
        
        string moves_str[] = {
            "FILL A", "FILL B", 
            "EMPTY A", "EMPTY B", 
            "MOVE A B", "MOVE B A"
        };
        for (int m : path) {
            cout << moves_str[m] << "\n";
        }
    }
    
    return 0;
}