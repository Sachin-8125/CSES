#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }

    vector<int> sorted(arr);
    sort(sorted.begin(), sorted.end());
    sorted.erase(unique(sorted.begin(), sorted.end()), sorted.end());

    vector<int> freq(sorted.size(), 0);
    int distinct = 0;

    for (int i = 0; i < k; ++i) {
        int idx = lower_bound(sorted.begin(), sorted.end(), arr[i]) - sorted.begin();
        if (freq[idx]++ == 0) distinct++;
    }
    cout << distinct;

    for (int i = k; i < n; ++i) {
        int l = lower_bound(sorted.begin(), sorted.end(), arr[i - k]) - sorted.begin();
        if (--freq[l] == 0) distinct--;

        int r = lower_bound(sorted.begin(), sorted.end(), arr[i]) - sorted.begin();
        if (freq[r]++ == 0) distinct++;

        cout << " " << distinct;
    }
    cout << "\n";

    return 0;
}
