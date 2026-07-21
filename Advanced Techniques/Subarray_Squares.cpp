#include <iostream>
#include <vector>
#include <deque>

using namespace std;

typedef long long ll;

struct Line {
    ll m, c;
    ll eval(ll x) {
        return m * x + c;
    }
};

bool bad(Line l1, Line l2, Line l3) {
    return (__int128)(l3.c - l1.c) * (l1.m - l2.m) <= (__int128)(l2.c - l1.c) * (l1.m - l3.m);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    cin >> n >> k;

    vector<ll> prefix(n + 1);
    prefix[0] = 0;
    for (int i = 1; i <= n; i++) {
        ll x;
        cin >> x;
        prefix[i] = prefix[i - 1] + x;
    }

    const ll INF = 1e18;
    vector<ll> prev_dp(n + 1, INF), curr_dp(n + 1, INF);
    prev_dp[0] = 0;
    
    for (int j = 1; j <= k; j++) {
        fill(curr_dp.begin(), curr_dp.end(), INF);
        deque<Line> hull;
        
        for (int i = j; i <= n; i++) {
            int l = i - 1;
            if (prev_dp[l] < INF) {
                Line newLine = {-2 * prefix[l], prev_dp[l] + prefix[l] * prefix[l]};
                while (hull.size() >= 2 && bad(hull[hull.size() - 2], hull.back(), newLine)) {
                    hull.pop_back();
                }
                hull.push_back(newLine);
            }
            
            while (hull.size() >= 2 && hull[0].eval(prefix[i]) >= hull[1].eval(prefix[i])) {
                hull.pop_front();
            }
            if (!hull.empty()) {
                curr_dp[i] = prefix[i] * prefix[i] + hull.front().eval(prefix[i]);
            }
        }
        
        swap(prev_dp, curr_dp);
    }

    cout << prev_dp[n] << "\n";

    return 0;
}