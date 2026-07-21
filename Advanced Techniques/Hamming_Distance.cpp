#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> nums(n);
    for(int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        for(char c : s) {
            nums[i] <<= 1;
            if(c == '1') nums[i] |= 1;
        }
    }
    int minDist = INT_MAX;
    for(int i = 0; i < n; ++i) {
        for(int j = i+1; j < n; ++j) {
            int dist = __builtin_popcount(nums[i] ^ nums[j]);
            minDist = min(minDist, dist);
        }
    }
    cout << minDist << endl;
}