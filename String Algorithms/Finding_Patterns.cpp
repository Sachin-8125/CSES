#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

struct Node {
    int len, link;
    int next[26];
    
    Node() {
        len = 0;
        link = -1;
        for (int i = 0; i < 26; i++) next[i] = 0;
    }
};

const int MAXN = 100005;
Node st[MAXN * 2];
int sz = 1, last = 0;

void sam_extend(int c) {
    int cur = sz++;
    st[cur].len = st[last].len + 1;
    int p = last;
    while (p != -1 && !st[p].next[c]) {
        st[p].next[c] = cur;
        p = st[p].link;
    }
    if (p == -1) {
        st[cur].link = 0;
    } else {
        int q = st[p].next[c];
        if (st[p].len + 1 == st[q].len) {
            st[cur].link = q;
        } else {
            int clone = sz++;
            st[clone].len = st[p].len + 1;
            for (int i = 0; i < 26; i++) st[clone].next[i] = st[q].next[i];
            st[clone].link = st[q].link;
            while (p != -1 && st[p].next[c] == q) {
                st[p].next[c] = clone;
                p = st[p].link;
            }
            st[q].link = st[cur].link = clone;
        }
    }
    last = cur;
}

bool exists(const string& p) {
    int cur = 0;
    for (char c : p) {
        int v = c - 'a';
        if (!st[cur].next[v]) return false;
        cur = st[cur].next[v];
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    if (!(cin >> s)) return 0;

    for (char c : s) {
        sam_extend(c - 'a');
    }

    int k;
    cin >> k;
    while (k--) {
        string p;
        cin >> p;
        if (exists(p)) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }

    return 0;
}
