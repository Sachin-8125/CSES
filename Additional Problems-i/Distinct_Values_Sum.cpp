#include <iostream>
#include <vector>
#include <map>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<long long> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    map<long long, int> last_pos;
    long long total_sum = 0;

    for (int i = 1; i <= n; ++i) {
        long long prev_idx = 0;
        if (last_pos.count(a[i])) {
            prev_idx = last_pos[a[i]];
        }
        
        long long left_choices = i - prev_idx;
        long long right_choices = n - i + 1;
        
        total_sum += left_choices * right_choices;
        last_pos[a[i]] = i;
    }

    cout << total_sum << "\n";

    return 0;
}