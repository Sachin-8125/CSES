#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

const long long INF = 1e15;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<long long> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    sort(a.begin(), a.end());

    vector<long long> V(n + 1, 0);
    vector<int> L(n + 1, 0);
    vector<int> R(n + 1, 0);
    vector<bool> dead(n + 1, false);

    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;

    V[0] = INF;
    V[n] = INF;

    for (int i = 1; i < n; i++) {
        V[i] = a[i] - a[i - 1];
        L[i] = i - 1;
        R[i] = i + 1;
        pq.push({V[i], i});
    }
    
    L[0] = 0; R[0] = 1;
    L[n] = n - 1; R[n] = n;

    long long current_cost = 0;
    int max_k = n / 2;

    for (int k = 1; k <= max_k; k++) {
        while (!pq.empty() && dead[pq.top().second]) {
            pq.pop();
        }

        auto [val, id] = pq.top();
        pq.pop();

        current_cost += val;
        cout << current_cost << (k == max_k ? "" : " ");

        int left_id = L[id];
        int right_id = R[id];

        long long new_val = V[left_id] + V[right_id] - V[id];
        V[id] = min(INF, new_val);

        dead[left_id] = true;
        dead[right_id] = true;

        L[id] = L[left_id];
        R[id] = R[right_id];
        
        R[L[id]] = id;
        L[R[id]] = id;

        pq.push({V[id], id});
    }
    cout << "\n";

    return 0;
}