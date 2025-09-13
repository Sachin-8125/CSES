#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<long long> coins(n);
    for (int i = 0; i < n; ++i)
        cin >> coins[i];
    sort(coins.begin(), coins.end());
    long long res = 1;
    for (int i = 0; i < n && coins[i] <= res; ++i)
        res += coins[i];
    cout << res << endl;
    return 0;
}
