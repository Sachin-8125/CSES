#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
using namespace std;

vector<int> slidingWindowMode(const vector<int>& nums, int k) {
    vector<int> result;
    if (nums.empty() || k <= 0 || k > nums.size()) {
        return result;
    }

    map<int, int> freqMap;
    set<pair<int, int>> mode;

    for (int i = 0; i < k; ++i) {
        int num = nums[i];
        if (freqMap.count(num)) {
            mode.erase({-freqMap[num], num});
        }
        freqMap[num]++;
        mode.insert({-freqMap[num], num});
    }
    result.push_back(mode.begin()->second);

    for (int i = k; i < nums.size(); ++i) {
        int oldNum = nums[i - k];
        mode.erase({-freqMap[oldNum], oldNum});
        freqMap[oldNum]--;
        if (freqMap[oldNum] > 0) {
            mode.insert({-freqMap[oldNum], oldNum});
        }

        int newNum = nums[i];
        if (freqMap.count(newNum)) {
            mode.erase({-freqMap[newNum], newNum});
        }
        freqMap[newNum]++;
        mode.insert({-freqMap[newNum], newNum});

        result.push_back(mode.begin()->second);
    }

    return result;
}

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> nums(n);
    for (int i = 0; i < n; ++i) {
        cin >> nums[i];
    }

    vector<int> modes = slidingWindowMode(nums, k);
    for (int i = 0; i < modes.size(); ++i) {
        if (i > 0) cout << " ";
        cout << modes[i];
    }
    cout << "\n";

    return 0;
}
