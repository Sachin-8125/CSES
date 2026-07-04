#include <iostream>
#include <map>
#include <algorithm>

using namespace std;

map<pair<long long, int>, pair<long long, long long>> memo;

pair<long long, long long> solve(long long n, int max_d) {
    if (n < 10) {
        int m = max((int)n, max_d);
        if (m == 0) return {0, 0};
        return {1, n - m};
    }

    pair<long long, int> state = {n, max_d};
    if (memo.count(state)) return memo[state];

    long long p = 1;
    while (p <= n / 10) {
        p *= 10;
    }
    
    long long steps = 0;
    long long curr = n;
    
    while (curr >= p) {
        int first_digit = curr / p;
        
        auto res = solve(curr % p, max(max_d, first_digit));
        steps += res.first;
        
        curr = first_digit * p + res.second; 
    }
    
    auto res2 = solve(curr, max_d);
    
    return memo[state] = {steps + res2.first, res2.second};
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    long long n;
    if (cin >> n) {
        cout << solve(n, 0).first << "\n";
    }
    return 0;
}