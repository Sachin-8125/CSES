#include <bits/stdc++.h>
using namespace std;

struct State {
    int link;
    int len;
    array<int, 26> next;
    long long cnt;
    State() : link(-1), len(0), cnt(0) { next.fill(-1); }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string text;
    if (!(cin >> text))
        return 0;

    int q;
    cin >> q;

    int n = text.size();
    vector<State> st;
    st.reserve(2 * max(1, n));
    st.emplace_back();

    int last = 0;
    for (char ch : text) {
        int c = ch - 'a';
        int cur = st.size();
        st.emplace_back();
        st[cur].len = st[last].len + 1;
        st[cur].cnt = 1;

        int p = last;
        while (p != -1 && st[p].next[c] == -1) {
            st[p].next[c] = cur;
            p = st[p].link;
        }

        if (p == -1) {
            st[cur].link = 0;
        } else {
            int qstate = st[p].next[c];
            if (st[p].len + 1 == st[qstate].len) {
                st[cur].link = qstate;
            } else {
                int clone = st.size();
                st.push_back(st[qstate]);
                st[clone].len = st[p].len + 1;
                st[clone].cnt = 0;

                while (p != -1 && st[p].next[c] == qstate) {
                    st[p].next[c] = clone;
                    p = st[p].link;
                }

                st[qstate].link = st[cur].link = clone;
            }
        }
        last = cur;
    }

    vector<int> lengthCount(n + 1);
    for (const State &state : st) {
        if (state.len <= n)
            lengthCount[state.len]++;
    }
    for (int i = 1; i <= n; i++)
        lengthCount[i] += lengthCount[i - 1];

    vector<int> order(st.size());
    for (int i = (int)st.size() - 1; i >= 0; i--) {
        order[--lengthCount[st[i].len]] = i;
    }

    for (int i = (int)st.size() - 1; i > 0; i--) {
        int state = order[i];
        int parent = st[state].link;
        if (parent != -1)
            st[parent].cnt += st[state].cnt;
    }

    string pattern;
    while (q--) {
        cin >> pattern;
        int v = 0;
        bool found = true;
        for (char ch : pattern) {
            int c = ch - 'a';
            if (c < 0 || c >= 26 || st[v].next[c] == -1) {
                found = false;
                break;
            }
            v = st[v].next[c];
        }
        cout << (found ? st[v].cnt : 0) << '\n';
    }

    return 0;
}