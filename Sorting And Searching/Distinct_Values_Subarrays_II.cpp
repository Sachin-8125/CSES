#include <iostream>
#include <vector>
#include <map>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    long long k; 
    if (!(cin >> n >> k)) return 0;

    vector<long long> x(n);
    for (int i = 0; i < n; ++i) {
        cin >> x[i];
    }

    map<long long, int> freq;
    long long count = 0, left = 0, ans = 0;
   
    for (int right = 0; right < n; ++right) {
        if (freq[x[right]] == 0) count++;
        freq[x[right]]++;

        while (count > k) {
            freq[x[left]]--;
            if (freq[x[left]] == 0) count--;
            left++;
        }

        ans += (right - left + 1);
    }

    cout << ans << endl;
    return 0;
}
