#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    long long x;
    int n;
    if (!(cin >> x >> n)) return 0;

    priority_queue<long long, vector<long long>, greater<long long>> pq;

    for (int i = 0; i < n; ++i) {
        long long d;
        cin >> d;
        pq.push(d);
    }

    long long total_cost = 0;

    while (pq.size() > 1) {
        long long first = pq.top();
        pq.pop();
        long long second = pq.top();
        pq.pop();

        long long current_cost = first + second;
        total_cost += current_cost;

        pq.push(current_cost);
    }

    cout << total_cost << "\n";

    return 0;
}