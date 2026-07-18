#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 200005;
int t[MAXN];
int ans[MAXN];
int visited[MAXN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    for (int i = 1; i <= n; i++) {
        cin >> t[i];
    }

    for (int i = 1; i <= n; i++) {
        if (ans[i] == 0) {
            vector<int> path;
            int curr = i;
            
            while (ans[curr] == 0 && visited[curr] == 0) {
                visited[curr] = path.size() + 1;
                path.push_back(curr);
                curr = t[curr];
            }

            if (ans[curr] > 0) {
                int add = ans[curr];
                for (int j = (int)path.size() - 1; j >= 0; j--) {
                    ans[path[j]] = ++add;
                }
            } else {
                int cycle_start_idx = visited[curr] - 1;
                int cycle_len = path.size() - cycle_start_idx;
                for (int j = cycle_start_idx; j < path.size(); j++) {
                    ans[path[j]] = cycle_len;
                }
                int add = cycle_len;
                for (int j = cycle_start_idx - 1; j >= 0; j--) {
                    ans[path[j]] = ++add;
                }
            }
            
            for (int p : path) {
                visited[p] = 0;
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        cout << ans[i] << (i == n ? "" : " ");
    }
    cout << "\n";

    return 0;
}