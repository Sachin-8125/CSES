#include <bits/stdc++.h>
using namespace std;

struct TrieNode {
    TrieNode* next[2];
    TrieNode() {
        next[0] = next[1] = nullptr;
    }
};

void insert(TrieNode* root, int num) {
    TrieNode* node = root;
    for (int i = 31; i >= 0; i--) {
        int bit = (num >> i) & 1;
        if (!node->next[bit])
            node->next[bit] = new TrieNode();
        node = node->next[bit];
    }
}

int query(TrieNode* root, int num) {
    TrieNode* node = root;
    int maxXor = 0;
    for (int i = 31; i >= 0; i--) {
        int bit = (num >> i) & 1;
        if (node->next[1 - bit]) {
            maxXor |= (1 << i);
            node = node->next[1 - bit];
        } else {
            node = node->next[bit];
        }
    }
    return maxXor;
}

int main() {
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int &x : arr) cin >> x;
    TrieNode* root = new TrieNode();
    insert(root, 0); // Important: Insert zero for correct prefix
    int prefixXor = 0, answer = 0;
    for (int x : arr) {
        prefixXor ^= x;
        answer = max(answer, query(root, prefixXor));
        insert(root, prefixXor);
    }
    cout << answer << endl;
}
