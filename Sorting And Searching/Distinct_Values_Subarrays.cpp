#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    long long result = 0;
    unordered_map<int, int> freq;
    int left = 0;
    
    for (int right = 0; right < n; right++) {
        freq[arr[right]]++;
        while (freq[arr[right]] > 1) {
            freq[arr[left]]--;
            if (freq[arr[left]] == 0) {
                freq.erase(arr[left]);
            }
            left++;
        }
        result += (right - left + 1);
    }
    cout << result << endl;
    return 0;
}
