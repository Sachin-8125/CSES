#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const long long INF = 4e18;
const int MAXV = 1000005;

struct Line {
    long long m, c;
    long long eval(long long x) const {
        return m * x + c;
    }
};

struct Node {
    Line line;
    Node *left, *right;
    Node(Line l) : line(l), left(nullptr), right(nullptr) {}
};

void insert(Node*& node, int l, int r, Line newline) {
    if (!node) {
        node = new Node(newline);
        return;
    }
    int mid = (l + r) >> 1;
    bool lef = newline.eval(l) < node->line.eval(l);
    bool midf = newline.eval(mid) < node->line.eval(mid);
    if (midf) {
        swap(node->line, newline);
    }
    if (l == r) return;
    if (lef != midf) {
        insert(node->left, l, mid, newline);
    } else {
        insert(node->right, mid + 1, r, newline);
    }
}

long long query(Node* node, int l, int r, long long x) {
    if (!node) return INF;
    long long res = node->line.eval(x);
    if (l == r) return res;
    int mid = (l + r) >> 1;
    if (x <= mid) return min(res, query(node->left, l, mid, x));
    return min(res, query(node->right, mid + 1, r, x));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    long long x;
    if (!(cin >> n >> x)) return 0;

    vector<long long> s(n + 1), f(n + 1);
    for (int i = 1; i <= n; i++) cin >> s[i];
    for (int i = 1; i <= n; i++) cin >> f[i];

    Node* root = nullptr;
    insert(root, 1, MAXV - 1, {x, 0});

    long long ans = 0;
    for (int i = 1; i <= n; i++) {
        long long dp = query(root, 1, MAXV - 1, s[i]);
        if (i == n) {
            ans = dp;
            break;
        }
        insert(root, 1, MAXV - 1, {f[i], dp});
    }

    cout << ans << "\n";

    return 0;
}