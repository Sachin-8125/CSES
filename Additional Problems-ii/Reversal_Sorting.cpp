#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 200010;

int ch[MAXN][2];
int p[MAXN];
int sz[MAXN];
int val[MAXN];
int rev[MAXN];
int node_of_val[MAXN];
int root;
int node_cnt = 0;
int A[MAXN];

void update(int x) {
    if (x) {
        sz[x] = 1;
        if (ch[x][0]) sz[x] += sz[ch[x][0]];
        if (ch[x][1]) sz[x] += sz[ch[x][1]];
    }
}

void pushdown(int x) {
    if (x && rev[x]) {
        swap(ch[x][0], ch[x][1]);
        if (ch[x][0]) rev[ch[x][0]] ^= 1;
        if (ch[x][1]) rev[ch[x][1]] ^= 1;
        rev[x] = 0;
    }
}

void push_all(int x) {
    static int st[MAXN];
    int top = 0;
    st[++top] = x;
    for (int i = x; p[i]; i = p[i]) st[++top] = p[i];
    while (top) pushdown(st[top--]);
}

void rotate(int x) {
    int y = p[x], z = p[y];
    int k = (ch[y][1] == x);
    ch[y][k] = ch[x][k ^ 1];
    if (ch[x][k ^ 1]) p[ch[x][k ^ 1]] = y;
    p[x] = z;
    if (z) ch[z][ch[z][1] == y] = x;
    ch[x][k ^ 1] = y;
    p[y] = x;
    update(y);
    update(x);
}

void splay(int x, int goal = 0) {
    push_all(x);
    while (p[x] != goal) {
        int y = p[x], z = p[y];
        if (z != goal) {
            if ((ch[y][0] == x) ^ (ch[z][0] == y)) rotate(x);
            else rotate(y);
        }
        rotate(x);
    }
    if (!goal) root = x;
}

int kth(int k) {
    int x = root;
    while (true) {
        pushdown(x);
        int left_sz = ch[x][0] ? sz[ch[x][0]] : 0;
        if (k <= left_sz) {
            x = ch[x][0];
        } else if (k == left_sz + 1) {
            return x;
        } else {
            k -= left_sz + 1;
            x = ch[x][1];
        }
    }
}

int build(int l, int r, int parent) {
    if (l > r) return 0;
    int mid = l + (r - l) / 2;
    int u = ++node_cnt;
    p[u] = parent;
    val[u] = A[mid];
    
    if (A[mid] > 0 && A[mid] < MAXN) {
        node_of_val[A[mid]] = u;
    }
    
    rev[u] = 0;
    ch[u][0] = build(l, mid - 1, u);
    ch[u][1] = build(mid + 1, r, u);
    update(u);
    return u;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    A[1] = 0; 
    for (int i = 1; i <= n; ++i) {
        cin >> A[i + 1];
    }
    A[n + 2] = 0; 

    root = build(1, n + 2, 0);

    vector<pair<int, int>> ans;
    ans.reserve(n);

    for (int i = 1; i <= n; ++i) {
        int u = node_of_val[i];
        splay(u);
        
        int curr_pos = (ch[root][0] ? sz[ch[root][0]] : 0);

        if (curr_pos > i) {
            ans.push_back({i, curr_pos});
            
            int L = kth(i);
            int R = kth(curr_pos + 2);
            
            splay(L);
            splay(R, L);
            
            rev[ch[R][0]] ^= 1;
        }
    }

    cout << ans.size() << "\n";
    for (const auto& p : ans) {
        cout << p.first << " " << p.second << "\n";
    }

    return 0;
}