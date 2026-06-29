#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    if (!(cin >> n >> k)) return 0;

    long long neg_sum = 0;
    vector<long long> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        if (a[i] < 0) {
            neg_sum += a[i];
            a[i] = -a[i]; 
        }
    }

    sort(a.begin(), a.end());

    cout << neg_sum << (k == 1 ? "" : " ");
    if (k == 1) {
        cout << "\n";
        return 0;
    }

    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
    pq.push({a[0], 0});

    for (int i = 1; i < k; ++i) {
        auto [current_sum, idx] = pq.top();
        pq.pop();

        cout << neg_sum + current_sum << (i == k - 1 ? "" : " ");

        if (idx + 1 < n) {
            pq.push({current_sum + a[idx + 1], idx + 1});
            pq.push({current_sum - a[idx] + a[idx + 1], idx + 1});
        }
    }
    
    cout << "\n";
    return 0;
}