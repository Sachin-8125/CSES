#include <bits/stdc++.h>
using namespace std;

static const int DY[4] = {1, 0, -1, 0};
static const int DX[4] = {0, 1, 0, -1};
static const char DIR[4] = {'D', 'R', 'U', 'L'};
int MP[256];

// ---------- Feasibility test ----------
bool is_solvable(int n, int m, int sy, int sx, int ty, int tx) {
    if (n == 1 && m == 1) return true;
    if (sy == ty && sx == tx) return false;

    if (n > m) {
        swap(n, m);
        swap(sy, sx);
        swap(ty, tx);
    }
    if (sx > tx) {
        swap(sx, tx);
        swap(sy, ty);
    }

    if (n == 1) {
        return (sx == 0 && tx == m - 1);
    } else if (n == 2) {
        if (sx == tx && (sx == 0 || sx == m - 1)) return true;
        if (sx == tx) return false;
        return ((sx + sy) % 2) != ((tx + ty) % 2);
    } else if ((n * m) % 2 == 1) {
        // odd number of cells -> both endpoints must be on majority color
        return ((sx + sy) % 2 == 0) && ((tx + ty) % 2 == 0);
    } else if (n == 3) {
        if (((sx + sy) % 2) == ((tx + ty) % 2)) return false;
        if (((sx + sy) % 2) == 1 && (sx < tx - 1 || (sy == 1 && sx < tx))) return false;
        if (((tx + ty) % 2) == 1 && (tx < sx - 1 || (ty == 1 && tx < sx))) return false;
        return true;
    } else {
        return ((sx + sy) % 2) != ((tx + ty) % 2);
    }
}

// ---------- Small board solver (n <= 4, m <= 5) ----------
struct SmallSolver {
    int n, m, N;
    int s, t;
    vector<vector<pair<int, char>>> adj;
    vector<int> vis;
    string ans, cur;

    int id(int y, int x) { return y * m + x; }

    bool unvisited_connected(int pos, int used_cnt) {
        int rem = N - used_cnt;
        if (rem == 0) return true;

        int first = -1;
        for (int v = 0; v < N; v++) {
            if (!vis[v]) {
                first = v;
                break;
            }
        }
        if (first == -1) return true;

        vector<int> q;
        vector<int> seen(N, 0);
        seen[first] = 1;
        q.push_back(first);
        int head = 0, cnt = 0;

        while (head < (int)q.size()) {
            int u = q[head++];
            cnt++;
            for (auto [v, _] : adj[u]) {
                if (!vis[v] && !seen[v]) {
                    seen[v] = 1;
                    q.push_back(v);
                }
            }
        }
        if (cnt != rem) return false;

        bool has_next = false;
        for (auto [v, _] : adj[pos]) {
            if (!vis[v]) {
                has_next = true;
                break;
            }
        }
        return has_next;
    }

    int onward_degree(int v) {
        int d = 0;
        for (auto [to, _] : adj[v]) d += (!vis[to]);
        return d;
    }

    bool dfs(int pos, int used_cnt) {
        if (used_cnt == N) {
            if (pos == t) {
                ans = cur;
                return true;
            }
            return false;
        }
        if (pos == t) return false;
        if (!unvisited_connected(pos, used_cnt)) return false;

        vector<tuple<int, int, char>> cand; // (degree, to, dir)
        for (auto [to, c] : adj[pos]) {
            if (!vis[to]) {
                cand.push_back({onward_degree(to), to, c});
            }
        }
        sort(cand.begin(), cand.end());

        for (auto [_, to, c] : cand) {
            vis[to] = 1;
            cur.push_back(c);
            if (dfs(to, used_cnt + 1)) return true;
            cur.pop_back();
            vis[to] = 0;
        }
        return false;
    }

    string solve(int n_, int m_, int sy, int sx, int ty, int tx) {
        n = n_;
        m = m_;
        N = n * m;
        s = id(sy, sx);
        t = id(ty, tx);

        adj.assign(N, {});
        for (int y = 0; y < n; y++) {
            for (int x = 0; x < m; x++) {
                int u = id(y, x);
                for (int d = 0; d < 4; d++) {
                    int ny = y + DY[d], nx = x + DX[d];
                    if (0 <= ny && ny < n && 0 <= nx && nx < m) {
                        adj[u].push_back({id(ny, nx), DIR[d]});
                    }
                }
            }
        }

        vis.assign(N, 0);
        vis[s] = 1;
        ans.clear();
        cur.clear();

        bool ok = dfs(s, 1);
        return ok ? ans : "";
    }
};

SmallSolver small_solver;

// ---------- Main constructive solver ----------
string solve_path(int n, int m, int sy, int sx, int ty, int tx) {
    if (n > m) {
        // Rotate transformation
        int n0 = n, m0 = m;
        int nsy = m0 - sx - 1, nsx = sy;
        int nty = m0 - tx - 1, ntx = ty;
        swap(n0, m0);
        string res = solve_path(n0, m0, nsy, nsx, nty, ntx);

        for (char &c : res) c = DIR[(MP[(int)c] + 3) % 4];
        return res;
    }

    if (sx > tx) {
        // Mirror left-right
        int nsx = m - sx - 1, ntx = m - tx - 1;
        string res = solve_path(n, m, sy, nsx, ty, ntx);
        for (char &c : res) {
            if (c == 'L') c = 'R';
            else if (c == 'R') c = 'L';
        }
        return res;
    }

    if (sy > ty) {
        // Mirror up-down
        int nsy = n - sy - 1, nty = n - ty - 1;
        string res = solve_path(n, m, nsy, sx, nty, tx);
        for (char &c : res) {
            if (c == 'U') c = 'D';
            else if (c == 'D') c = 'U';
        }
        return res;
    }

    if (n == 1) {
        return string(m - 1, 'R');
    }

    // Special shape in 2 x m
    if (n == 2 && sy == ty && sx + 1 == tx) {
        string res;
        for (int i = 0; i < sx; i++) res += 'L';
        if (sy == 0) {
            res += 'D';
            for (int i = 0; i < m - 1; i++) res += 'R';
            res += 'U';
        } else {
            res += 'U';
            for (int i = 0; i < m - 1; i++) res += 'R';
            res += 'D';
        }
        for (int i = m - 1; i > tx; i--) res += 'L';
        return res;
    }

    // Small base by exact DFS
    if (n <= 4 && m <= 5) {
        string res = small_solver.solve(n, m, sy, sx, ty, tx);
        return res;
    }

    // Peel 2 columns on the left
    if (sx >= 2 && is_solvable(n, m - 2, sy, sx - 2, ty, tx - 2)) {
        string res = solve_path(n, m - 2, sy, sx - 2, ty, tx - 2);
        int cy = sy, cx = sx - 2;
        for (int i = 0; i < (int)res.size(); i++) {
            int d = MP[(int)res[i]];
            int ny = cy + DY[d], nx = cx + DX[d];
            if (cx == 0 && nx == 0) {
                return res.substr(0, i) + "L" +
                       solve_path(n, 2, cy, 1, ny, 1) + "R" +
                       res.substr(i + 1);
            }
            cy = ny;
            cx = nx;
        }
    }

    // Peel 2 columns on the right
    if (tx <= m - 3 && is_solvable(n, m - 2, sy, sx, ty, tx)) {
        string res = solve_path(n, m - 2, sy, sx, ty, tx);
        int cy = sy, cx = sx;
        for (int i = 0; i < (int)res.size(); i++) {
            int d = MP[(int)res[i]];
            int ny = cy + DY[d], nx = cx + DX[d];
            if (cx == m - 3 && nx == m - 3) {
                return res.substr(0, i) + "R" +
                       solve_path(n, 2, cy, 0, ny, 0) + "L" +
                       res.substr(i + 1);
            }
            cy = ny;
            cx = nx;
        }
    }

    // Horizontal split
    for (int i = sy; i < ty; i++) {
        for (int j = 0; j < m; j++) {
            if (is_solvable(i + 1, m, sy, sx, i, j) &&
                is_solvable(n - i - 1, m, 0, j, ty - (i + 1), tx)) {
                string a = solve_path(i + 1, m, sy, sx, i, j);
                string b = solve_path(n - i - 1, m, 0, j, ty - (i + 1), tx);
                return a + "D" + b;
            }
        }
    }

    // Vertical split
    for (int j = sx; j < tx; j++) {
        for (int i = 0; i < n; i++) {
            if (is_solvable(n, j + 1, sy, sx, i, j) &&
                is_solvable(n, m - j - 1, i, 0, ty, tx - (j + 1))) {
                string a = solve_path(n, j + 1, sy, sx, i, j);
                string b = solve_path(n, m - j - 1, i, 0, ty, tx - (j + 1));
                return a + "R" + b;
            }
        }
    }

    return "";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    MP['D'] = 0;
    MP['R'] = 1;
    MP['U'] = 2;
    MP['L'] = 3;

    int t;
    cin >> t;
    while (t--) {
        int n, m, y1, x1, y2, x2;
        cin >> n >> m >> y1 >> x1 >> y2 >> x2;
        --y1; --x1; --y2; --x2;

        if (!is_solvable(n, m, y1, x1, y2, x2)) {
            cout << "NO\n";
            continue;
        }

        string ans = solve_path(n, m, y1, x1, y2, x2);
        if ((int)ans.size() != n * m - 1) {
            // Safety fallback (should not happen when solvable)
            cout << "NO\n";
            continue;
        }

        cout << "YES\n" << ans << '\n';
    }

    return 0;
}