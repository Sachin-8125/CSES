#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;
    int n = (int)s.size();

    vector<int> sa(n), ranks(n), tmp(n);
    for (int i = 0; i < n; ++i) {
        sa[i] = i;
        ranks[i] = s[i];
    }

    for (int step = 1; step < n; step <<= 1) {
        auto cmp = [step, &ranks, n](int i, int j) {
            if (ranks[i] != ranks[j]) return ranks[i] < ranks[j];
            int ri = (i + step < n) ? ranks[i + step] : -1;
            int rj = (j + step < n) ? ranks[j + step] : -1;
            return ri < rj;
        };
        sort(sa.begin(), sa.end(), cmp);
        tmp[sa[0]] = 0;
        for (int i = 1; i < n; ++i)
            tmp[sa[i]] = tmp[sa[i - 1]] + (cmp(sa[i - 1], sa[i]) ? 1 : 0);
        for (int i = 0; i < n; ++i) ranks[i] = tmp[i];
        if (ranks[sa[n - 1]] == n - 1) break;
    }

    vector<int> lcp(n, 0);
    for (int i = 0; i < n; ++i) ranks[sa[i]] = i;
    int h = 0;
    for (int i = 0; i < n; ++i) {
        int j = ranks[i];
        if (j < n - 1) {
            int p = sa[j + 1];
            while (i + h < n && p + h < n && s[i + h] == s[p + h]) ++h;
            lcp[j] = h;
            if (h > 0) --h;
        }
    }

    vector<long long> diff(n + 2, 0);
    int prev = 0;
    for (int i = 0; i < n; ++i) {
        diff[prev + 1]++;
        diff[n - sa[i] + 1]--;
        prev = lcp[i];
    }

    long long cur = 0;
    for (int i = 1; i <= n; ++i) {
        cur += diff[i];
        cout << cur << (i == n ? '\n' : ' ');
    }

    return 0;
}