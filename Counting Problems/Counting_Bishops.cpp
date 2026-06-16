#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

int squares(int i) {
    if (i & 1) {
        return i / 4 * 2 + 1;
    } else {
        return (i - 1) / 4 * 2 + 2;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, k;
    cin >> n >> k;
    
    if (k > 2 * n - 1) {
        cout << 0 << endl;
        return 0;
    }

    vector<vector<long long>> D(n * 2, vector<long long>(k + 1, 0));
    
    for (int i = 0; i < n * 2; i++) {
        D[i][0] = 1;
    }
    
    D[1][1] = 1;
    
    for (int i = 2; i < n * 2; i++) {
        for (int j = 1; j <= k; j++) {
            long long term1 = D[i - 2][j];
            long long term2 = D[i - 2][j - 1] * (squares(i) - j + 1) % MOD;
            D[i][j] = (term1 + term2) % MOD;
        }
    }
    
    long long ans = 0;
    for (int i = 0; i <= k; i++) {
        long long ways = D[n * 2 - 1][i] * D[n * 2 - 2][k - i] % MOD;
        ans = (ans + ways) % MOD;
    }
    
    cout << ans << endl;
    
    return 0;
}