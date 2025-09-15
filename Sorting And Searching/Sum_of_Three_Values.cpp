#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    long long x;
    cin >> n >> x;
    vector<pair<long long, int>> vec(n);
    for(int i = 0; i < n; ++i) {
        cin >> vec[i].first;
        vec[i].second = i+1; // Store original index (1-based)
    }
    sort(vec.begin(), vec.end()); // Sort by value

    for(int i = 0; i < n-2; ++i) {
        int l = i+1, r = n-1;
        while(l < r) {
            long long sum = vec[i].first + vec[l].first + vec[r].first;
            if(sum == x) {
                cout << vec[i].second << " " << vec[l].second << " " << vec[r].second << "\n";
                return 0;
            }
            else if(sum < x) l++;
            else r--;
        }
    }
    cout << "IMPOSSIBLE\n";
    return 0;
}
