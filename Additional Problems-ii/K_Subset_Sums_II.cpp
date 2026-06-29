#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct State {
    long long sum;
    int f, val, limit;
    
    bool operator>(const State& other) const {
        if (sum != other.sum) return sum > other.sum;
        if (f != other.f) return f > other.f;
        if (val != other.val) return val > other.val;
        return limit > other.limit;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, k;
    if (!(cin >> n >> m >> k)) return 0;

    vector<long long> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    sort(a.begin(), a.end());

    long long base_sum = 0;
    for (int i = 0; i < m; ++i) {
        base_sum += a[i];
    }

    cout << base_sum << (k == 1 ? "" : " ");
    if (k == 1) {
        cout << "\n";
        return 0;
    }

    priority_queue<State, vector<State>, greater<State>> pq;
    pq.push({base_sum - a[m - 1] + a[m], m - 1, m, n});

    for (int i = 1; i < k; ++i) {
        State current = pq.top();
        pq.pop();

        cout << current.sum << (i == k - 1 ? "" : " ");

        if (current.f > 0) {
            pq.push({
                current.sum - a[current.f - 1] + a[current.f],
                current.f - 1,
                current.f,
                current.val
            });
        }

        if (current.val + 1 < current.limit) {
            pq.push({
                current.sum - a[current.val] + a[current.val + 1],
                current.f,
                current.val + 1,
                current.limit
            });
        }
    }

    cout << "\n";
    return 0;
}