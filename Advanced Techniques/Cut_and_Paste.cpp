#include <iostream>
#include <string>
#include <random>

using namespace std;

const int MAXN = 200005;

struct Node {
    int left, right;
    int priority;
    int size;
    char val;
};

Node tree[MAXN];
int nodeCount = 0;
int root = 0;

mt19937 rng(12345);

int getSize(int t) {
    return t ? tree[t].size : 0;
}

void update(int t) {
    if (t) {
        tree[t].size = 1 + getSize(tree[t].left) + getSize(tree[t].right);
    }
}

int newNode(char c) {
    nodeCount++;
    tree[nodeCount].left = 0;
    tree[nodeCount].right = 0;
    tree[nodeCount].priority = rng();
    tree[nodeCount].size = 1;
    tree[nodeCount].val = c;
    return nodeCount;
}

void split(int t, int k, int &l, int &r) {
    if (!t) {
        l = r = 0;
        return;
    }
    int leftSize = getSize(tree[t].left);
    if (leftSize < k) {
        split(tree[t].right, k - leftSize - 1, tree[t].right, r);
        l = t;
    } else {
        split(tree[t].left, k, l, tree[t].left);
        r = t;
    }
    update(t);
}

int merge(int l, int r) {
    if (!l || !r) return l ? l : r;
    if (tree[l].priority > tree[r].priority) {
        tree[l].right = merge(tree[l].right, r);
        update(l);
        return l;
    } else {
        tree[r].left = merge(l, tree[r].left);
        update(r);
        return r;
    }
}

void output(int t, string &res) {
    if (!t) return;
    output(tree[t].left, res);
    res += tree[t].val;
    output(tree[t].right, res);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    string s;
    cin >> s;

    for (int i = 0; i < n; ++i) {
        root = merge(root, newNode(s[i]));
    }

    while (m--) {
        int a, b;
        cin >> a >> b;
        int l1, mid, r1;
        split(root, a - 1, l1, mid);
        split(mid, b - a + 1, mid, r1);
        root = merge(merge(l1, r1), mid);
    }

    string res;
    res.reserve(n);
    output(root, res);
    cout << res << "\n";

    return 0;
}