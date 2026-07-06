#include <iostream>
#include <vector>
#include <numeric>
#include <bitset>
#include <set>
#include <cmath>

using namespace std;

const int MAX_SUM = 500005;
bitset<MAX_SUM> dp[1005];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<int> a(n);
    long long sum = 0;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        sum += a[i];
    }

    if (sum % 2 != 0) {
        cout << -1 << "\n";
        return 0;
    }

    int target = sum / 2;
    dp[0][0] = 1;

    for (int i = 1; i <= n; ++i) {
        dp[i] = dp[i - 1] | (dp[i - 1] << a[i - 1]);
    }

    if (!dp[n][target]) {
        cout << -1 << "\n";
        return 0;
    }

    multiset<int> A, B;
    int curr = target;
    for (int i = n; i >= 1; --i) {
        if (curr >= a[i - 1] && dp[i - 1][curr - a[i - 1]]) {
            A.insert(a[i - 1]);
            curr -= a[i - 1];
        } else {
            B.insert(a[i - 1]);
        }
    }

    for (int i = 0; i < n - 1; ++i) {
        if (A.empty()) {
            auto it1 = B.begin(); int v1 = *it1; B.erase(it1);
            auto it2 = B.begin(); int v2 = *it2; B.erase(it2);
            cout << v1 << " " << v2 << "\n";
            B.insert(abs(v1 - v2));
        } else if (B.empty()) {
            auto it1 = A.begin(); int v1 = *it1; A.erase(it1);
            auto it2 = A.begin(); int v2 = *it2; A.erase(it2);
            cout << v1 << " " << v2 << "\n";
            A.insert(abs(v1 - v2));
        } else {
            int maxA = *A.rbegin();
            int maxB = *B.rbegin();
            
            if (maxA > maxB) {
                auto itA = prev(A.end());
                auto itB = B.begin();
                int valA = *itA, valB = *itB;
                cout << valA << " " << valB << "\n";
                A.erase(itA);
                B.erase(itB);
                A.insert(valA - valB);
            } else {
                auto itB = prev(B.end());
                auto itA = A.begin();
                int valB = *itB, valA = *itA;
                cout << valB << " " << valA << "\n";
                B.erase(itB);
                A.erase(itA);
                B.insert(valB - valA);
            }
        }
    }

    return 0;
}