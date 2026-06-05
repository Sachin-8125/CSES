#include <iostream>
#include <set>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    multiset<long long> sum_set;  
    multiset<long long> diff_set;

    for (int i = 0; i < n; ++i) {
        long long x, y;
        cin >> x >> y;
        sum_set.insert(x + y);
        diff_set.insert(x - y);

        long long max_sum_dist = *sum_set.rbegin() - *sum_set.begin();
        long long max_diff_dist = *diff_set.rbegin() - *diff_set.begin();

        cout << max(max_sum_dist, max_diff_dist) << "\n";
    }

    return 0;
}