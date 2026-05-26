#include <iostream>
#include <string>
#include <vector>
using namespace std;

const int MAXN = 100005;

struct State {
    int len, link;
    int next[26];
};

State st[MAXN * 2];
int sz, last;

void sam_init() {
    st[0].len = 0;
    st[0].link = -1;
    for (int i = 0; i < 26; i++) st[0].next[i] = -1;
    sz = 1;
    last = 0;
}

void sam_extend(char c) {
    int cur = sz++;
    int v = c - 'a';
    st[cur].len = st[last].len + 1;
    for (int i = 0; i < 26; i++) st[cur].next[i] = -1;
    
    int p = last;
    while (p != -1 && st[p].next[v] == -1) {
        st[p].next[v] = cur;
        p = st[p].link;
    }
    
    if (p == -1) {
        st[cur].link = 0;
    } else {
        int q = st[p].next[v];
        if (st[p].len + 1 == st[q].len) {
            st[cur].link = q;
        } else {
            int clone = sz++;
            st[clone].len = st[p].len + 1;
            for (int i = 0; i < 26; i++) st[clone].next[i] = st[q].next[i];
            st[clone].link = st[q].link;
            while (p != -1 && st[p].next[v] == q) {
                st[p].next[v] = clone;
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
    for (char c : s) {
        sam_extend(c);
    }

    long long distinct_substrings = 0;
    for (int i = 1; i < sz; i++) {
        // Each state i represents substrings of lengths in range (st[st[i].link].len, st[i].len]
        distinct_substrings += (st[i].len - st[st[i].link].len);
    }

    cout << distinct_substrings << endl;

    return 0;
}
