#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<pair<int, int>> events;
    for (int i = 0; i < n; ++i) {
        int a, b; 
        cin >> a >> b;
        events.push_back({a, 1});  
        events.push_back({b, -1});
    }
    sort(events.begin(), events.end());
    int current = 0, max_customers = 0;
    for (auto it : events) {
        current += it.second;
        max_customers = max(max_customers, current);
    }
    cout << max_customers << endl;
    return 0;
}
