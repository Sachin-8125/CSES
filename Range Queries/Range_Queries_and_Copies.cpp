#include <iostream>
#include <vector>

using namespace std;

struct Node {
    long long sum;
    Node* left;
    Node* right;

    Node(long long val) : sum(val), left(nullptr), right(nullptr) {}
    Node(Node* l, Node* r) : left(l), right(r) {
        sum = 0;
        if (left) sum += left->sum;
        if (right) sum += right->sum;
    }
};

int n, q;
vector<long long> initial_arr;
vector<Node*> roots;

Node* build(int l, int r) {
    if (l == r) {
        return new Node(initial_arr[l]);
    }
    int mid = l + (r - l) / 2;
    return new Node(build(l, mid), build(mid + 1, r));
}

Node* update(Node* node, int l, int r, int idx, long long x) {
    if (l == r) {
        return new Node(x);
    }
    int mid = l + (r - l) / 2;
    if (idx <= mid) {
        return new Node(update(node->left, l, mid, idx, x), node->right);
    } else {
        return new Node(node->left, update(node->right, mid + 1, r, idx, x));
    }
}

long long query(Node* node, int l, int r, int ql, int qr) {
    if (ql > r || qr < l) {
        return 0;
    }
    if (ql <= l && r <= qr) {
        return node->sum;
    }
    int mid = l + (r - l) / 2;
    return query(node->left, l, mid, ql, qr) + query(node->right, mid + 1, r, ql, qr);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (!(cin >> n >> q)) return 0;

    initial_arr.resize(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> initial_arr[i];
    }

    roots.push_back(nullptr);
    roots.push_back(build(1, n));

    for (int i = 0; i < q; ++i) {
        int type;
        cin >> type;
        if (type == 1) {
            int k, a;
            long long x;
            cin >> k >> a >> x;
            roots[k] = update(roots[k], 1, n, a, x);
        } else if (type == 2) {
            int k, a, b;
            cin >> k >> a >> b;
            cout << query(roots[k], 1, n, a, b) << "\n";
        } else if (type == 3) {
            int k;
            cin >> k;
            roots.push_back(roots[k]);
        }
    }

    return 0;
}