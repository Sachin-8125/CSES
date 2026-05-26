#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int MAXLEN = 100005;

struct State {
    int len, link;
    int next[26];
    int first_pos;
};

State st[MAXLEN * 2];
int sz, last;

void sam_init() {
    st[0].len = 0;
    st[0].link = -1;
    st[0].first_pos = 0;
    for (int i = 0; i < 26; i++) st[0].next[i] = -1;
    sz = 1;
    last = 0;
}

void sam_extend(char c, int pos) {
    int cur = sz++;
    st[cur].len = st[last].len + 1;
    st[cur].first_pos = pos;
    for (int i = 0; i < 26; i++) st[cur].next[i] = -1;

    int p = last;
    while (p != -1 && st[p].next[c - 'a'] == -1) {
        st[p].next[c - 'a'] = cur;
        p = st[p].link;
    }

    if (p == -1) {
        st[cur].link = 0;
    } else {
        int q = st[p].next[c - 'a'];
        if (st[p].len + 1 == st[q].len) {
            st[cur].link = q;
        } else {
            int clone = sz++;
            st[clone].len = st[p].len + 1;
            for (int i = 0; i < 26; i++) st[clone].next[i] = st[q].next[i];
            st[clone].link = st[q].link;
            st[clone].first_pos = st[q].first_pos; // Clone gets the same first_pos as q

            while (p != -1 && st[p].next[c - 'a'] == q) {
                st[p].next[c - 'a'] = clone;
                p = st[p].link;
            }
            st[q].link = st[cur].link = clone;
        }
    }
    last = cur;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    if (!(cin >> s)) return 0;

    sam_init();
    for (int i = 0; i < (int)s.length(); i++) {
        sam_extend(s[i], i);
    }

    int k;
    if (!(cin >> k)) return 0;

    while (k--) {
        string p;
        cin >> p;
        int cur = 0;
        bool found = true;
        for (char c : p) {
            if (st[cur].next[c - 'a'] == -1) {
                found = false;
                break;
            }
            cur = st[cur].next[c - 'a'];
        }

        if (!found) {
            cout << -1 << "\n";
        } else {
            cout << st[cur].first_pos - (int)p.length() + 2 << "\n";
        }
    }

    return 0;
}