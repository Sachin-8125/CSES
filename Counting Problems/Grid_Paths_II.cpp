#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

long long power(long long base, long long exp) {
    long long result = 1;
    base %= MOD;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % MOD;
        }
        base = (base * base) % MOD;
        exp /= 2;
    }
    return result;
}

long long modInverse(long long n) {
    return power(n, MOD - 2);
}

vector<long long> fact, invFact;

void precomputeFactorials(int n) {
    fact.resize(n + 1);
    invFact.resize(n + 1);
    fact[0] = 1;
    for (int i = 1; i <= n; i++) {
        fact[i] = (fact[i - 1] * i) % MOD;
    }
    invFact[n] = modInverse(fact[n]);
    for (int i = n - 1; i >= 0; i--) {
        invFact[i] = (invFact[i + 1] * (i + 1)) % MOD;
    }
}

long long nCr(int n, int r) {
    if (r < 0 || r > n) return 0;
    return fact[n] * invFact[r] % MOD * invFact[n - r] % MOD;
}

long long paths(int y1, int x1, int y2, int x2) {
    if (y1 > y2 || x1 > x2) return 0;
    int dy = y2 - y1;
    int dx = x2 - x1;
    return nCr(dy + dx, dy);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    
    vector<pair<int, int>> traps(m);
    for (int i = 0; i < m; i++) {
        cin >> traps[i].first >> traps[i].second;
    }
    
    sort(traps.begin(), traps.end());
    
    traps.push_back({n, n});
    m++;
    
    precomputeFactorials(2 * n);
    
    vector<long long> dp(m, 0);
    
    for (int i = 0; i < m; i++) {
        int y = traps[i].first;
        int x = traps[i].second;
        
        dp[i] = paths(1, 1, y, x);
        
        for (int j = 0; j < i; j++) {
            int yj = traps[j].first;
            int xj = traps[j].second;
            
            long long through_j = dp[j] * paths(yj, xj, y, x) % MOD;
            dp[i] = (dp[i] - through_j + MOD) % MOD;
        }
    }
    
    cout << dp[m - 1] << endl;
    
    return 0;
}