#include <iostream>
#include <vector>
#include <set>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, k;
    cin >> n >> k;
    vector<long long> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    multiset<long long> left, right;
    long long leftSum = 0, rightSum = 0;

    auto add = [&](long long x) {
        if (left.empty() || x <= *left.rbegin()) {
            left.insert(x);
            leftSum += x;
        } else {
            right.insert(x);
            rightSum += x;
        }
        
        // Balance sizes: left should have (k+1)/2 elements
        int needLeft = (k + 1) / 2;
        while ((int)left.size() > needLeft) {
            auto it = prev(left.end());
            long long val = *it;
            left.erase(it);
            leftSum -= val;
            right.insert(val);
            rightSum += val;
        }
        while ((int)left.size() < needLeft && !right.empty()) {
            auto it = right.begin();
            long long val = *it;
            right.erase(it);
            rightSum -= val;
            left.insert(val);
            leftSum += val;
        }
    };

    auto remove = [&](long long x) {
        auto it = left.find(x);
        if (it != left.end()) {
            left.erase(it);
            leftSum -= x;
        } else {
            auto it2 = right.find(x);
            if (it2 != right.end()) {
                right.erase(it2);
                rightSum -= x;
            }
        }
        
        // Rebalance after removal
        int needLeft = (k + 1) / 2;
        while ((int)left.size() > needLeft && !left.empty()) {
            auto it = prev(left.end());
            long long val = *it;
            left.erase(it);
            leftSum -= val;
            right.insert(val);
            rightSum += val;
        }
        while ((int)left.size() < needLeft && !right.empty()) {
            auto it = right.begin();
            long long val = *it;
            right.erase(it);
            rightSum -= val;
            left.insert(val);
            leftSum += val;
        }
    };

    auto getCost = [&]() -> long long {
        if (left.empty()) return 0LL;
        long long median = *left.rbegin();
        long long leftSize = left.size();
        long long rightSize = right.size();
        return median * leftSize - leftSum + rightSum - median * rightSize;
    };

    vector<long long> res;
    for (int i = 0; i < n; ++i) {
        add(a[i]);
        if (i >= k - 1) {
            res.push_back(getCost());
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