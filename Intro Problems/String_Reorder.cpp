#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>
#include <cassert>
using namespace std;
void solve() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string s;
    cin >> s;
    int n = s.length();
    vector<int> counts(26, 0);
    for (char ch : s) {
        counts[ch - 'A']++;
    }
    int max_freq_initial = 0;
    for (int count : counts) {
        max_freq_initial = max(max_freq_initial, count);
    }
    if (max_freq_initial > (n + 1) / 2) {
        cout << -1 << endl;
        return;
    }
    string result = "";
    int last_char_idx = -1; 
    int rem = n; 
    for (int i = 0; i < n; ++i) {
        vector<pair<int, int>> freqs;
        for (int j = 0; j < 26; ++j) {
            if (counts[j] > 0) {
                freqs.push_back({-counts[j], j});
            }
        }
        sort(freqs.begin(), freqs.end());
        int max_freq = 0;
        int M_idx = -1; 
        int second_max_freq = 0;
        if (!freqs.empty()) {
            max_freq = -freqs[0].first;
            M_idx = freqs[0].second;
        }
        if (freqs.size() > 1) {
            second_max_freq = -freqs[1].first;
        }
        int to_place_idx = -1;
        if ((2 * max_freq > rem) && (M_idx != last_char_idx)) {
            to_place_idx = M_idx;
        } else {
            for (int c = 0; c < 26; ++c) {
                if (counts[c] > 0 && c != last_char_idx) {
                    int max_freq_after_c;
                    if (c == M_idx) {
                        max_freq_after_c = max(counts[c] - 1, second_max_freq);
                    } else {
                        max_freq_after_c = max_freq;
                    }

                    if (max_freq_after_c <= rem / 2) {
                        to_place_idx = c;
                        break; 
                    }
                }
            }
        }
        assert(to_place_idx != -1);
        result += (char)('A' + to_place_idx);
        counts[to_place_idx]--;
        last_char_idx = to_place_idx;
        rem--;
    }
    cout << result << endl;
}
int main() {
    solve();
    return 0;
}