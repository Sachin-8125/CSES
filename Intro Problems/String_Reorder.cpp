#include <iostream>
#include <string>
#include <vector>
#include <queue>
using namespace std;

int main() {
    string s;
    cin >> s;
    int n = s.size();

    // Count frequency of each character
    vector<int> freq(26, 0);
    for(char c : s) freq[c - 'A']++;

    // Check if possible
    int maxFreq = 0;
    for (int f : freq) maxFreq = max(maxFreq, f);
    if (maxFreq > (n + 1) / 2) {
        cout << -1 << endl;
        return 0;
    }

    // Min-heap for lex minimality
    priority_queue<pair<char, int>, vector<pair<char,int>>, greater<>> pq;
    for (int i = 0; i < 26; ++i) {
        if (freq[i]) pq.push({(char)('A'+i), freq[i]});
    }

    string res = "";
    pair<char, int> prev = {'#', 0};

    while (!pq.empty()) {
        auto curr = pq.top(); pq.pop();

        if (!res.empty() && curr.first == res.back()) {
            if (pq.empty()) {
                cout << -1 << endl;
                return 0;
            }
            auto next = pq.top(); pq.pop();

            res += next.first;
            if (--next.second > 0) pq.push(next);
            pq.push(curr);
        } else {
            res += curr.first;
            if (--curr.second > 0) pq.push(curr);
        }
    }
    cout << res << endl;
    return 0;
}