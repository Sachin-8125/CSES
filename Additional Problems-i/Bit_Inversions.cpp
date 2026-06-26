#include <iostream>
#include <string>
#include <set>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    if (!(cin >> s)) return 0;

    int n = s.length();
    int m;
    cin >> m;

    set<int> diff;
    multiset<int> lengths;

    diff.insert(0);
    diff.insert(n);

    for (int i = 1; i < n; ++i) {
        if (s[i] != s[i - 1]) {
            diff.insert(i);
        }
    }

    auto it = diff.begin();
    int prev = *it;
    ++it;
    while (it != diff.end()) {
        lengths.insert(*it - prev);
        prev = *it;
        ++it;
    }

    auto toggle = [&](int p) {
        if (p <= 0 || p >= n) return;
        
        auto it = diff.find(p);
        if (it != diff.end()) {
            auto prev_it = std::prev(it);
            auto next_it = std::next(it);
            lengths.erase(lengths.find(p - *prev_it));
            lengths.erase(lengths.find(*next_it - p));
            lengths.insert(*next_it - *prev_it);
            diff.erase(it);
        } else {
            auto next_it = diff.upper_bound(p);
            auto prev_it = std::prev(next_it);
            lengths.erase(lengths.find(*next_it - *prev_it));
            lengths.insert(p - *prev_it);
            lengths.insert(*next_it - p);
            diff.insert(p);
        }
    };

    for (int i = 0; i < m; ++i) {
        int x;
        cin >> x;
        int idx = x - 1;
        
        toggle(idx);
        toggle(idx + 1);
        
        cout << *lengths.rbegin() << (i == m - 1 ? "" : " ");
    }
    cout << "\n";

    return 0;
}