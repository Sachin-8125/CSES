#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    long long sum_degrees = 0;
    set<pair<int, int>> st;

    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        sum_degrees += x;
        if (x > 0) {
            st.insert({x, i});
        }
    }

    vector<pair<int, int>> edges;
    bool possible = true;

    while (!st.empty()) {
        auto [deg, u] = *st.begin();
        st.erase(st.begin());

        if (deg > (int)st.size()) {
            possible = false;
            break;
        }

        vector<pair<int, int>> to_put_back;
        for (int i = 0; i < deg; i++) {
            auto it = prev(st.end());
            auto [v_deg, v] = *it;
            st.erase(it);

            edges.push_back({u, v});
            if (v_deg - 1 > 0) {
                to_put_back.push_back({v_deg - 1, v});
            }
        }

        for (auto &p : to_put_back) {
            st.insert(p);
        }
    }

    if (possible && (int)edges.size() * 2 == sum_degrees) {
        cout << edges.size() << "\n";
        for (auto &edge : edges) {
            cout << edge.first << " " << edge.second << "\n";
        }
    } else {
        cout << "IMPOSSIBLE\n";
    }

    return 0;
}