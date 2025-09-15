#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;
void solve() {
    int x, n;
    cin >> x >> n;
    set<int> light_positions;
    light_positions.insert(0);
    light_positions.insert(x);
    multiset<int> passage_lengths;
    passage_lengths.insert(x); 
    for (int i = 0; i < n; ++i) {
        int p;
        cin >> p;
        auto it_right = light_positions.upper_bound(p);
        auto it_left = prev(it_right);
        int right_pos = *it_right;
        int left_pos = *it_left;
        int old_length = right_pos - left_pos;
        passage_lengths.erase(passage_lengths.find(old_length));
        light_positions.insert(p);
        int new_length1 = p - left_pos;
        int new_length2 = right_pos - p;
        passage_lengths.insert(new_length1);
        passage_lengths.insert(new_length2);
        cout << *passage_lengths.rbegin() << (i == n - 1 ? "" : " ");
    }
    cout << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}