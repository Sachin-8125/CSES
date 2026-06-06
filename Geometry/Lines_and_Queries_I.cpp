#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Line {
    long long a, b;
    long long eval(long long x) const {
        return a * x + b;
    }
};

const int MAXX = 100000;
const long long INF = 4e18;

struct Node {
    Line line = {0, -INF};
    Node* left = nullptr;
    Node* right = nullptr;
};

void insert(Node* node, int l, int r, Line new_line) {
    int mid = l + (r - l) / 2;
    
    bool mid_better = (new_line.eval(mid) > node->line.eval(mid));
    bool left_better = (new_line.eval(l) > node->line.eval(l));
    
    if (mid_better) {
        swap(node->line, new_line);
    }
    
    if (l == r) return;
    
    if (left_better != mid_better) {
        if (!node->left) node->left = new Node();
        insert(node->left, l, mid, new_line);
    } else {
        if (!node->right) node->right = new Node();
        insert(node->right, mid + 1, r, new_line);
    }
}

long long query(Node* node, int l, int r, int x) {
    if (!node) return -INF;
    
    long long curr = node->line.eval(x);
    if (l == r) return curr;
    
    int mid = l + (r - l) / 2;
    if (x <= mid) {
        return max(curr, query(node->left, l, mid, x));
    } else {
        return max(curr, query(node->right, mid + 1, r, x));
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    if (!(cin >> n)) return 0;
    
    Node* root = new Node();
    
    for (int i = 0; i < n; ++i) {
        int type;
        cin >> type;
        if (type == 1) {
            long long a, b;
            cin >> a >> b;
            insert(root, 0, MAXX, {a, b});
        } else if (type == 2) {
            int x;
            cin >> x;
            cout << query(root, 0, MAXX, x) << "\n";
        }
    }
    
    return 0;
}