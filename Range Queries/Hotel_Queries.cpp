#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<long long> tree;
vector<long long> hotels;

void build(int node, int start, int end) {
    if (start == end) {
        tree[node] = hotels[start];
        return;
    }
    int mid = (start + end) / 2;
    build(2 * node, start, mid);
    build(2 * node + 1, mid + 1, end);
    tree[node] = max(tree[2 * node], tree[2 * node + 1]);
}

int query_and_update(int node, int start, int end, long long rooms) {
    if (tree[node] < rooms) {
        return 0;
    }
    
    if (start == end) {
        tree[node] -= rooms;
        return start;
    }
    
    int mid = (start + end) / 2;
    int assigned_hotel = 0;
    
    if (tree[2 * node] >= rooms) {
        assigned_hotel = query_and_update(2 * node, start, mid, rooms);
    } else {
        assigned_hotel = query_and_update(2 * node + 1, mid + 1, end, rooms);
    }
    
    tree[node] = max(tree[2 * node], tree[2 * node + 1]);
    return assigned_hotel;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    if (!(cin >> n >> m)) return 0;
    
    hotels.resize(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> hotels[i];
    }
    
    tree.resize(4 * n + 1);
    build(1, 1, n);
    
    for (int i = 0; i < m; ++i) {
        long long rooms;
        cin >> rooms;
        int result = query_and_update(1, 1, n, rooms);
        cout << result << (i == m - 1 ? "" : " ");
    }
    cout << "\n";
    
    return 0;
}
