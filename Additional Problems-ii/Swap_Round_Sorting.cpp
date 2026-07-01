#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<int> p(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> p[i];
    }

    vector<vector<int>> cycles;
    vector<bool> vis(n + 1, false);
    bool needs_two_rounds = false;

    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            vector<int> cycle;
            int curr = i;
            while (!vis[curr]) {
                vis[curr] = true;
                cycle.push_back(curr);
                curr = p[curr];
            }
            if (cycle.size() > 1) {
                cycles.push_back(cycle);
            }
            if (cycle.size() > 2) {
                needs_two_rounds = true;
            }
        }
    }

    if (cycles.empty()) {
        cout << 0 << "\n";
        return 0;
    }

    if (!needs_two_rounds) {
        cout << 1 << "\n";
        cout << cycles.size() << "\n";
        for (const auto& cycle : cycles) {
            cout << cycle[0] << " " << cycle[1] << "\n";
        }
        return 0;
    }

    vector<pair<int, int>> round1;
    
    for (auto& cycle : cycles) {
        int k = cycle.size();
        int l = 1;
        int r = k - 1;
        while (l < r) {
            round1.push_back({cycle[l], cycle[r]});
            swap(p[cycle[l]], p[cycle[r]]);
            l++;
            r--;
        }
    }

    vector<pair<int, int>> round2;
    fill(vis.begin(), vis.end(), false);
    
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            vector<int> cycle;
            int curr = i;
            while (!vis[curr]) {
                vis[curr] = true;
                cycle.push_back(curr);
                curr = p[curr];
            }
            if (cycle.size() > 1) {
                round2.push_back({cycle[0], cycle[1]});
            }
        }
    }

    cout << 2 << "\n";
    cout << round1.size() << "\n";
    for (const auto& pair : round1) {
        cout << pair.first << " " << pair.second << "\n";
    }
    cout << round2.size() << "\n";
    for (const auto& pair : round2) {
        cout << pair.first << " " << pair.second << "\n";
    }
}