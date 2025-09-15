#include <bits/stdc++.h>
#define ll long long
using namespace std;

// Function to count the number of subarrays with sum = X
ll solve(ll N, ll X, vector<ll>& arr) {
    ll start = 0, end = -1;
    ll sum = 0;
    ll cnt = 0;

    while (end < N) {
        // Expand window to the right
        while (end < N && sum < X) {
            sum += arr[++end];
        }
        // Shrink window from the left if sum exceeds X
        while (start <= end && sum > X) {
            sum -= arr[start++];
        }
        // If the window sum is exactly X
        if (sum == X) {
            cnt += 1;
            sum -= arr[start++];
        }
    }
    return cnt;
}

int main() {
    ll N, X;
    cin >> N >> X;
    vector<ll> arr(N);
    for (ll i = 0; i < N; ++i) cin >> arr[i];
    cout << solve(N, X, arr) << endl;
}