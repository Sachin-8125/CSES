#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct Customer {
    int a, b, id;
    
    bool operator<(const Customer& other) const {
        if (a == other.a) return b < other.b;
        return a < other.a;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<Customer> customers(n);
    for (int i = 0; i < n; ++i) {
        cin >> customers[i].a >> customers[i].b;
        customers[i].id = i;
    }

    sort(customers.begin(), customers.end());

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    vector<int> ans(n);
    int rooms = 0;

    for (int i = 0; i < n; ++i) {
        if (pq.empty() || pq.top().first >= customers[i].a) {
            rooms++;
            ans[customers[i].id] = rooms;
            pq.push({customers[i].b, rooms});
        } else {
            int room = pq.top().second;
            pq.pop();
            ans[customers[i].id] = room;
            pq.push({customers[i].b, room});
        }
    }

    cout << rooms << "\n";
    for (int i = 0; i < n; ++i) {
        cout << ans[i] << (i == n - 1 ? "" : " ");
    }
    cout << "\n";

    return 0;
}