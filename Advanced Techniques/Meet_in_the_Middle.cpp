#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


vector<long long> generate_sums(const vector<int>& v) {
    int n = v.size();
    vector<long long> sums;
    for (int i = 0; i < (1 << n); ++i) {
        long long current_sum = 0;
        for (int j = 0; j < n; ++j) {
            if ((i >> j) & 1) {
                current_sum += v[j];
            }
        }
        sums.push_back(current_sum);
    }
    return sums;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    long long x;
    if (!(cin >> n >> x)) return 0;

    vector<int> a, b;
    for (int i = 0; i < n; ++i) {
        int t;
        cin >> t;
        if (i < n / 2) a.push_back(t);
        else b.push_back(t);
    }

    vector<long long> sums_a = generate_sums(a);
    vector<long long> sums_b = generate_sums(b);

    sort(sums_a.begin(), sums_a.end());

    long long total_ways = 0;
    for (long long s : sums_b) {
        long long target = x - s;
        auto range = equal_range(sums_a.begin(), sums_a.end(), target);
        total_ways += distance(range.first, range.second);
    }

    cout << total_ways << endl;

    return 0;
}
