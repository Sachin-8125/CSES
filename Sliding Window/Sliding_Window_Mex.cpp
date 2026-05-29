
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
using namespace std;

vector<int> slidingWindowMex(const vector<int>& nums, int n, int k) {
    vector<int> result;
    if (k <= 0 || k > n) {
        return result;
    }

    map<int, int> freqMap;
    set<int> missingNumbers;
    for (int i = 0; i <= k; ++i) {
        missingNumbers.insert(i);
    }

    for (int i = 0; i < k; ++i) {
        int num = nums[i];
        freqMap[num]++;
        if (missingNumbers.count(num)) {
            missingNumbers.erase(num);
        }
    }
    result.push_back(*missingNumbers.begin());

    for (int i = k; i < n; ++i) {
        int oldNum = nums[i - k];
        freqMap[oldNum]--;
        if (freqMap[oldNum] == 0 && oldNum >= 0 && oldNum <= k) {
            missingNumbers.insert(oldNum);
        }

        int newNum = nums[i];
        freqMap[newNum]++;
        if (missingNumbers.count(newNum)) {
            missingNumbers.erase(newNum);
        }

        result.push_back(*missingNumbers.begin());
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

    vector<int> mexValues = slidingWindowMex(nums, n, k);

    for (int i = 0; i < mexValues.size(); ++i) {
        if (i > 0) cout << " ";
        cout << mexValues[i];
    }
    cout << "\n";

    return 0;
}
