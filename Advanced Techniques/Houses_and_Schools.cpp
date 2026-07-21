#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const long long INF = 4e18;

int n, k;
long long S[3005];
long long SX[3005];
long long prev_dp[3005];
long long curr_dp[3005];

inline long long sum_c(int L, int R) {
    if (L > R) return 0;
    return S[R] - S[L - 1];
}

inline long long sum_cx(int L, int R) {
    if (L > R) return 0;
    return SX[R] - SX[L - 1];
}

inline long long cost_before(int i) {
    if (i <= 1) return 0;
    return (long long)i * sum_c(1, i - 1) - sum_cx(1, i - 1);
}

inline long long cost_after(int i) {
    if (i >= n) return 0;
    return sum_cx(i + 1, n) - (long long)i * sum_c(i + 1, n);
}

inline long long cost(int p, int i) {
    if (p >= i - 1) return 0;
    int mid = p + (i - p) / 2;
    long long res = 0;
    res += sum_cx(p + 1, mid) - (long long)p * sum_c(p + 1, mid);
    res += (long long)i * sum_c(mid + 1, i - 1) - sum_cx(mid + 1, i - 1);
    return res;
}

void compute(int l, int r, int optl, int optr) {
    if (l > r) return;
    int mid = l + (r - l) / 2;
    long long best = INF;
    int opt = -1;
    
    int start = optl;
    int end = min(optr, mid - 1);
    
    for (int p = start; p <= end; p++) {
        if (prev_dp[p] == INF) continue;
        long long cur = prev_dp[p] + cost(p, mid);
        if (cur < best) {
            best = cur;
            opt = p;
        }
    }
    
    if (opt == -1) opt = start;
    
    curr_dp[mid] = best;
    compute(l, mid - 1, optl, opt);
    compute(mid + 1, r, opt, optr);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (!(cin >> n >> k)) return 0;

    for (int i = 1; i <= n; i++) {
        long long c;
        cin >> c;
        S[i] = S[i - 1] + c;
        SX[i] = SX[i - 1] + c * i;
    }

    for (int i = 1; i <= n; i++) {
        curr_dp[i] = cost_before(i);
    }

    for (int j = 2; j <= k; j++) {
        for (int i = 1; i <= n; i++) {
            prev_dp[i] = curr_dp[i];
            curr_dp[i] = INF;
        }
        compute(j, n, j - 1, n - 1);
    }

    long long ans = INF;
    for (int i = k; i <= n; i++) {
        ans = min(ans, curr_dp[i] + cost_after(i));
    }

    cout << ans << "\n";

    return 0;
}