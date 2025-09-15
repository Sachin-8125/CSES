#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

int main() {
    int n;
    cin >> n;
    vector<int> v(n);
    for(int i = 0; i < n; i++) {
        cin >> v[i];
    }
    unordered_map<int, int> freq;
    for(int i = 0; i < n; i++) {
        freq[v[i]]++;
    }
    long long ans = 1;
    for(auto& p : freq) {
        ans = (ans * (p.second + 1)) % MOD;
    }
    ans = (ans - 1 + MOD) % MOD;
    cout << ans << endl;
    return 0;
}