#include <iostream>
#include <vector>
#include <map>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    long long x;
    if (!(cin >> n >> x)) return 0;

    long long current_prefix_sum = 0;
    long long count = 0;
    
    map<long long, int> prefix_counts;

    prefix_counts[0] = 1;

    for (int i = 0; i < n; ++i) {
        long long a;
        cin >> a;
        current_prefix_sum += a;

        long long target = current_prefix_sum - x;

        if (prefix_counts.find(target) != prefix_counts.end()) {
            count += prefix_counts[target];
        }

        prefix_counts[current_prefix_sum]++;
    }

    cout << count << "\n";

    return 0;
}
