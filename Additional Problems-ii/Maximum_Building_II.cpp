#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<string> grid(n);
    for (int i = 0; i < n; ++i) {
        cin >> grid[i];
    }

    vector<int> H(m, 0);
    vector<vector<long long>> D2(n + 2, vector<long long>(m + 2, 0));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (grid[i][j] == '*') {
                H[j] = 0;
            } else {
                H[j]++;
            }
        }

        vector<int> L(m), R(m);
        vector<int> st;

        for (int j = 0; j < m; ++j) {
            while (!st.empty() && H[st.back()] >= H[j]) {
                st.pop_back();
            }
            L[j] = st.empty() ? 0 : st.back() + 1;
            st.push_back(j);
        }

        st.clear();
        for (int j = m - 1; j >= 0; --j) {
            while (!st.empty() && H[st.back()] > H[j]) {
                st.pop_back();
            }
            R[j] = st.empty() ? m - 1 : st.back() - 1;
            st.push_back(j);
        }

        for (int j = 0; j < m; ++j) {
            if (H[j] == 0) continue;
            long long len1 = j - L[j] + 1;
            long long len2 = R[j] - j + 1;
            if (len1 > len2) swap(len1, len2);

            D2[H[j]][1] += 1;
            D2[H[j]][len1 + 1] -= 1;
            D2[H[j]][len2 + 1] -= 1;
            D2[H[j]][len1 + len2 + 1] += 1;
        }
    }

    vector<vector<long long>> ans(n + 2, vector<long long>(m + 2, 0));

    for (int h = 1; h <= n; ++h) {
        long long d = 0;
        long long val = 0;
        for (int w = 1; w <= m; ++w) {
            d += D2[h][w];
            val += d;
            ans[h][w] = val;
        }
    }

    for (int w = 1; w <= m; ++w) {
        long long suffix_sum = 0;
        for (int h = n; h >= 1; --h) {
            suffix_sum += ans[h][w];
            ans[h][w] = suffix_sum;
        }
    }

    for (int h = 1; h <= n; ++h) {
        for (int w = 1; w <= m; ++w) {
            cout << ans[h][w] << (w == m ? "" : " ");
        }
        cout << "\n";
    }

    return 0;
}