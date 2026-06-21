#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    if (!(cin >> s)) return 0;

    int n = s.length();
    vector<bool> present(26, false);
    int unique_chars = 0;
    for (char c : s) {
        if (!present[c - 'a']) {
            present[c - 'a'] = true;
            unique_chars++;
        }
    }

    vector<int> current_counts(26, 0);
    map<vector<int>, int> fingerprint_counts;

    vector<int> initial_fingerprint(26, 0);
    fingerprint_counts[initial_fingerprint] = 1;

    long long special_substrings = 0;

    for (int i = 0; i < n; i++) {
        current_counts[s[i] - 'a']++;

        int reference_count = -1;
        for (int j = 0; j < 26; j++) {
            if (present[j]) {
                reference_count = current_counts[j];
                break;
            }
        }

        vector<int> fingerprint(26, 0);
        for (int j = 0; j < 26; j++) {
            if (present[j]) {
                fingerprint[j] = current_counts[j] - reference_count;
            }
        }

        if (fingerprint_counts.count(fingerprint)) {
            special_substrings += fingerprint_counts[fingerprint];
        }
        fingerprint_counts[fingerprint]++;
    }

    cout << special_substrings << "\n";

    return 0;
}
