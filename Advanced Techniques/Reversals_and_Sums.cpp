#include <iostream>
#include <random>

using namespace std;

const int MAXN = 200005;

struct Node {
    int left, right;
    int priority;
    int size;
    long long val;
    long long sum;
    bool rev;
};

Node tree[MAXN];
int nodeCount = 0;
int root = 0;

mt19937 rng(12345);

int getSize(int t) {
    return t ? tree[t].size : 0;
}

long long getSum(int t) {
    return t ? tree[t].sum : 0;
}

void push(int t) {
    if (t && tree[t].rev) {
        swap(tree[t].left, tree[t].right);
        if (tree[t].left) tree[tree[t].left].rev ^= 1;
        if (tree[t].right) tree[tree[t].right].rev ^= 1;
        tree[t].rev = false;
    }
}

void update(int t) {
    if (t) {
        tree[t].size = 1 + getSize(tree[t].left) + getSize(tree[t].right);
        tree[t].sum = tree[t].val + getSum(tree[t].left) + getSum(tree[t].right);
    }
}

int newNode(long long v) {
    nodeCount++;
    tree[nodeCount].left = 0;
    tree[nodeCount].right = 0;
    tree[nodeCount].priority = rng();
    tree[nodeCount].size = 1;
    tree[nodeCount].val = v;
    tree[nodeCount].sum = v;
    tree[nodeCount].rev = false;
    return nodeCount;
}

void split(int t, int k, int &l, int &r) {
    if (!t) {
        l = r = 0;
        return;
    }
    push(t);
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
        push(l);
        tree[l].right = merge(tree[l].right, r);
        update(l);
        return l;
    } else {
        push(r);
        tree[r].left = merge(l, tree[r].left);
        update(r);
        return r;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    for (int i = 0; i < n; ++i) {
        long long x;
        cin >> x;
        root = merge(root, newNode(x));
    }

    while (m--) {
        int t, a, b;
        cin >> t >> a >> b;
        
        int l1, mid, r1;
        split(root, a - 1, l1, mid);
        split(mid, b - a + 1, mid, r1);
        
        if (t == 1) {
            if (mid) tree[mid].rev ^= 1;
        } else {
            cout << getSum(mid) << "\n";
        }
        
        root = merge(merge(l1, mid), r1);
    }

    return 0;
}