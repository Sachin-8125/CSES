#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 100005;

struct State {
    int len, link;
    int next[26];
    int count;
    int first_pos;
};

State st[MAXN * 2];
int sz, last;

void sam_init() {
    st[0].len = 0;
    st[0].link = -1;
    st[0].count = 0;
    st[0].first_pos = -1;
    for (int i = 0; i < 26; i++) st[0].next[i] = -1;
    sz = 1;
    last = 0;
}

void sam_extend(char c, int pos) {
    int cur = sz++;
    int v = c - 'a';
    st[cur].len = st[last].len + 1;
    st[cur].count = 1;
    st[cur].first_pos = pos;
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
            st[clone].count = 0;
            st[clone].first_pos = st[q].first_pos;
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
    for (int i = 0; i < (int)s.length(); i++) {
        sam_extend(s[i], i);
    }

    vector<int> states_by_len(sz);
    for (int i = 0; i < sz; i++) states_by_len[i] = i;
    sort(states_by_len.begin(), states_by_len.end(), [](int a, int b) {
        return st[a].len > st[b].len;
    });

    for (int i : states_by_len) {
        if (st[i].link != -1) {
            st[st[i].link].count += st[i].count;
        }
    }

    int max_len = 0;
    int best_end_pos = -1;

    for (int i = 1; i < sz; i++) {
        if (st[i].count >= 2) {
            if (st[i].len > max_len) {
                max_len = st[i].len;
                best_end_pos = st[i].first_pos;
            }
        }
    }

    if (max_len == 0) {
        cout << -1 << endl;
    } else {
        cout << s.substr(best_end_pos - max_len + 1, max_len) << endl;
    }

    return 0;
}