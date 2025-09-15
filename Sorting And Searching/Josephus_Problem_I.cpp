#include <iostream>
#include <queue>

using namespace std;

int main() {
    int n;
    cin >> n;
    queue<int> q;
    for (int i = 1; i <= n; ++i) {
        q.push(i);
    }
    bool remove = false;
    while (!q.empty()) {
        int curr = q.front();
        q.pop();
        if (remove) {
            cout << curr << " ";
        } else {
            q.push(curr);
        }
        remove = !remove;
    }
    return 0;
}
