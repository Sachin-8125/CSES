#include <iostream>
#include <vector>
#include <deque>

using namespace std;

struct Line {
    long long m, c;
};

bool check(Line a, Line b, Line c) {
    return (__int128_t)(b.c - a.c) * (b.m - c.m) >= (__int128_t)(c.c - b.c) * (a.m - b.m);
}

long long eval(Line l, long long x) {
    return l.m * x + l.c;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    long long x;
    if (!(cin >> n >> x)) return 0;

    vector<long long> s(n), f(n);
    for (int i = 0; i < n; ++i) cin >> s[i];
    for (int i = 0; i < n; ++i) cin >> f[i];

    deque<Line> dq;
    dq.push_back({x, 0});

    for (int i = 0; i < n; ++i) {
        while (dq.size() >= 2 && eval(dq[0], s[i]) >= eval(dq[1], s[i])) {
            dq.pop_front();
        }
        long long ans = eval(dq[0], s[i]);
        if (i == n - 1) {
            cout << ans << "\n";
            return 0;
        }
        Line L = {f[i], ans};
        
        if (!dq.empty() && dq.back().m == L.m) {
            if (L.c >= dq.back().c) {
                continue;
            }
            dq.pop_back();
        }
        
        while (dq.size() >= 2 && check(dq[dq.size() - 2], dq.back(), L)) {
            dq.pop_back();
        }
        dq.push_back(L);
    }

    return 0;
}