#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    cin >> n >> k;

    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    priority_queue<int, vector<int>, greater<int>> pq;

    int end = min(n - 1, k);
    for (int j = 0; j <= end; j++)
        pq.push(a[j]);

    for (int i = 0; i < n; i++) {
        cout << pq.top();
        if (i < n - 1) cout << " ";
        pq.pop();

        long long next_idx = (long long)i + k + 1;
        if (next_idx < n) pq.push(a[next_idx]);
    }
    cout << "\n";

    return 0;
}