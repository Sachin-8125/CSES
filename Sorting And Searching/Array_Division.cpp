#include <bits/stdc++.h>
using namespace std;
using ll = long long;

bool is_possible(const vector<ll>& arr, int k, ll max_sum) {
    int parts = 1;
    ll cur_sum = 0;
    for (ll x : arr) {
        if (cur_sum + x > max_sum) {
            parts++;
            cur_sum = x;
            if (parts > k) return false;
        } else {
            cur_sum += x;
        }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, k;
    cin >> n >> k;
    vector<ll> arr(n);
    ll total = 0, max_val = 0;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        total += arr[i];
        max_val = max(max_val, arr[i]);
    }
    
    ll low = max_val, high = total, ans = total;
    while (low <= high) {
        ll mid = low + (high - low) / 2;
        if (is_possible(arr, k, mid)) {
            ans = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    cout << ans << '\n';
}
