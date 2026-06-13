#include <iostream>
#include <vector>
#include <string>
#include <cstdint>

using namespace std;

static uint32_t col_masks[500][500];
static uint32_t current_masks[500];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    if (!(cin >> n >> k)) return 0;

    for (int i = 0; i < n; ++i) {
        string row;
        cin >> row;
        for (int j = 0; j < n; ++j) {
            int c = row[j] - 'A';
            if (c < k) {
                col_masks[j][i] = (1U << c);
            }
        }
    }

    uint32_t target = (1U << k) - 1;
    long long ans = 0;

    for (int r1 = 0; r1 < n; ++r1) {
        for (int j = 0; j < n; ++j) current_masks[j] = 0;
        for (int r2 = r1; r2 < n; ++r2) {
            uint32_t total_mask = 0;
            for (int j = 0; j < n; ++j) {
                current_masks[j] |= col_masks[j][r2];
                total_mask |= current_masks[j];
            }

            if (total_mask != target) continue;

            int left = 0;
            uint32_t s1[500], s2[500], p1[501], p2[501];
            int top1 = 0, top2 = 0;
            p1[0] = 0; p2[0] = 0;

            for (int right = 0; right < n; ++right) {
                s2[top2++] = current_masks[right];
                p2[top2] = p2[top2 - 1] | current_masks[right];

                while (true) {
                    uint32_t current_window_mask = p1[top1] | p2[top2];
                    if (current_window_mask != target) break;

                    ans += (n - right);

                    if (top1 == 0) {
                        while (top2 > 0) {
                            uint32_t val = s2[--top2];
                            s1[top1++] = val;
                            p1[top1] = p1[top1 - 1] | val;
                        }
                        p2[0] = 0; // reset prefix OR for s2
                    }
                    top1--;
                    left++;
                }
            }
        }
    }

    cout << ans << endl;
    return 0;
}