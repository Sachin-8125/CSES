#include <iostream>
#include <vector>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    long long x;
    if (!(cin >> n >> x))
        return 0;
    vector<long long> w(n);
    for (int i = 0; i < n; ++i)
        cin >> w[i];
    vector<pair<int, long long>> dp(1 << n, {n + 1, 0});
    dp[0] = {1, 0};
    for (int mask = 0; mask < (1 << n); ++mask)
    {
        for (int i = 0; i < n; ++i)
        {
            if (!(mask & (1 << i)))
            {
                int r = dp[mask].first;
                long long wt = dp[mask].second;
                if (wt + w[i] <= x)
                    wt += w[i];
                else
                {
                    r++;
                    wt = w[i];
                }
                dp[mask | (1 << i)] = min(dp[mask | (1 << i)], {r, wt});
            }
        }
    }
    cout << dp[(1 << n) - 1].first << "\n";
    return 0;
}
