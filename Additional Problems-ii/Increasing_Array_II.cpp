#include <iostream>
#include <queue>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    priority_queue<int> pq;
    long long moves = 0;

    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        
        pq.push(x);
        
        if (pq.top() > x) {
            moves += pq.top() - x;
            pq.pop();
            pq.push(x);
        }
    }

    cout << moves << "\n";

    return 0;
}