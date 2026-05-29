#include <iostream>
#include <vector>
#include <set>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    multiset<int> left, right;

    auto add = [&](int x) {
        if (left.empty() || x <= *left.rbegin()) {
            left.insert(x);
        } else {
            right.insert(x);
        }
        
        // Balance sizes: left should have (k+1)/2 elements
        int needLeft = (k + 1) / 2;
        while ((int)left.size() > needLeft) {
            auto it = prev(left.end());
            int val = *it;
            left.erase(it);
            right.insert(val);
        }
        while ((int)left.size() < needLeft && !right.empty()) {
            auto it = right.begin();
            int val = *it;
            right.erase(it);
            left.insert(val);
        }
    };

    auto remove = [&](int x) {
        auto it = left.find(x);
        if (it != left.end()) {
            left.erase(it);
        } else {
            auto it2 = right.find(x);
            if (it2 != right.end()) {
                right.erase(it2);
            }
        }
        
        // Rebalance after removal
        int needLeft = (k + 1) / 2;
        while ((int)left.size() > needLeft && !left.empty()) {
            auto it = prev(left.end());
            int val = *it;
            left.erase(it);
            right.insert(val);
        }
        while ((int)left.size() < needLeft && !right.empty()) {
            auto it = right.begin();
            int val = *it;
            right.erase(it);
            left.insert(val);
        }
    };

    vector<int> res;
    for (int i = 0; i < n; ++i) {
        add(a[i]);
        if (i >= k - 1) {
            res.push_back(*left.rbegin());
            remove(a[i - k + 1]);
        }
    }

    for (int i = 0; i < (int)res.size(); ++i) {
        if (i) cout << " ";
        cout << res[i];
    }
    cout << "\n";
    return 0;
}
