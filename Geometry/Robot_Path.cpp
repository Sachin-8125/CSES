#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Segment {
    long long x1, y1, x2, y2;
    long long min_x, max_x, min_y, max_y;
    int id;
    bool horizontal;

    Segment(long long _x1, long long _y1, long long _x2, long long _y2, int _id) 
        : x1(_x1), y1(_y1), x2(_x2), y2(_y2), id(_id) {
        min_x = min(x1, x2);
        max_x = max(x1, x2);
        min_y = min(y1, y2);
        max_y = max(y1, y2);
        horizontal = (y1 == y2);
    }
};

struct Fenwick {
    int n;
    vector<int> tree;
    Fenwick(int _n) : n(_n), tree(_n + 1, 0) {}
    void add(int i, int v) {
        for (; i <= n; i += i & -i) tree[i] += v;
    }
    int query(int i) {
        int res = 0;
        for (; i > 0; i -= i & -i) res += tree[i];
        return res;
    }
};

vector<long long> all_ys;
int get_y_idx(long long y) {
    return lower_bound(all_ys.begin(), all_ys.end(), y) - all_ys.begin() + 1;
}

struct Event {
    long long x;
    int type; // 0: H-start, 1: V, 2: H-end
    int y1, y2;
    bool operator<(const Event& other) const {
        if (x != other.x) return x < other.x;
        return type < other.type;
    }
};

bool check(int k, const vector<Segment>& segments) {
    //  Collinear check (H-H or V-V)
    auto check_collinear = [&](bool horiz) {
        vector<const Segment*> s;
        for (int i = 0; i <= k; ++i) if (segments[i].horizontal == horiz) s.push_back(&segments[i]);
        if (s.empty()) return false;
        sort(s.begin(), s.end(), [&](const Segment* a, const Segment* b) {
            if (horiz) {
                if (a->min_y != b->min_y) return a->min_y < b->min_y;
                return a->min_x < b->min_x;
            } else {
                if (a->min_x != b->min_x) return a->min_x < b->min_x;
                return a->min_y < b->min_y;
            }
        });
        for (size_t i = 1; i < s.size(); ++i) {
            if (horiz) {
                if (s[i]->min_y == s[i-1]->min_y) {
                    if (s[i]->min_x <= s[i-1]->max_x) {
                        if (abs(s[i]->id - s[i-1]->id) == 1) {
                            if (s[i]->min_x < s[i-1]->max_x) return true;
                        } else return true;
                    }
                }
            } else {
                if (s[i]->min_x == s[i-1]->min_x) {
                    if (s[i]->min_y <= s[i-1]->max_y) {
                        if (abs(s[i]->id - s[i-1]->id) == 1) {
                            if (s[i]->min_y < s[i-1]->max_y) return true;
                        } else return true;
                    }
                }
            }
        }
        return false;
    };
    if (check_collinear(true)) return true;
    if (check_collinear(false)) return true;

    //  Perpendicular check (H-V)
    vector<Event> events;
    for (int i = 0; i <= k; ++i) {
        if (segments[i].horizontal) {
            events.push_back({segments[i].min_x, 0, get_y_idx(segments[i].min_y), 0});
            events.push_back({segments[i].max_x, 2, get_y_idx(segments[i].min_y), 0});
        } else {
            events.push_back({segments[i].min_x, 1, get_y_idx(segments[i].min_y), get_y_idx(segments[i].max_y)});
        }
    }
    sort(events.begin(), events.end());

    Fenwick fw(all_ys.size());
    long long total_hv = 0;
    for (auto& e : events) {
        if (e.type == 0) fw.add(e.y1, 1);
        else if (e.type == 2) fw.add(e.y1, -1);
        else total_hv += fw.query(e.y2) - fw.query(e.y1 - 1);
    }

    long long consecutive_perp = 0;
    for (int i = 1; i <= k; ++i) {
        if (segments[i].horizontal != segments[i-1].horizontal) consecutive_perp++;
    }
    return total_hv > consecutive_perp;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<Segment> segments;
    long long cur_x = 0, cur_y = 0;
    all_ys.push_back(0);
    for (int i = 0; i < n; ++i) {
        char d;
        long long x;
        cin >> d >> x;
        long long next_x = cur_x, next_y = cur_y;
        if (d == 'U') next_y += x;
        else if (d == 'D') next_y -= x;
        else if (d == 'L') next_x -= x;
        else if (d == 'R') next_x += x;
        segments.emplace_back(cur_x, cur_y, next_x, next_y, i);
        cur_x = next_x;
        cur_y = next_y;
        all_ys.push_back(cur_y);
    }
    sort(all_ys.begin(), all_ys.end());
    all_ys.erase(unique(all_ys.begin(), all_ys.end()), all_ys.end());

    int low = 0, high = n - 1, ans_k = n;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (check(mid, segments)) {
            ans_k = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    long long total_dist = 0;
    for (int i = 0; i < ans_k; ++i) {
        total_dist += abs(segments[i].x1 - segments[i].x2) + abs(segments[i].y1 - segments[i].y2);
    }

    if (ans_k < n) {
        const Segment& sk = segments[ans_k];
        long long min_d = abs(sk.x1 - sk.x2) + abs(sk.y1 - sk.y2);
        
        for (int j = 0; j < ans_k; ++j) {
            const Segment& sj = segments[j];
            if (sk.horizontal && sj.horizontal) {
                if (sk.y1 == sj.y1) {
                    long long inter_x1 = max(sk.min_x, sj.min_x);
                    long long inter_x2 = min(sk.max_x, sj.max_x);
                    if (inter_x1 <= inter_x2) {
                        if (j == ans_k - 1) {
                            if (inter_x1 < inter_x2) {
                                if (sk.x1 < sk.x2) min_d = min(min_d, max(0LL, inter_x1 - sk.x1));
                                else min_d = min(min_d, max(0LL, sk.x1 - inter_x2));
                            }
                        } else {
                            if (sk.x1 < sk.x2) min_d = min(min_d, max(0LL, inter_x1 - sk.x1));
                            else min_d = min(min_d, max(0LL, sk.x1 - inter_x2));
                        }
                    }
                }
            } else if (!sk.horizontal && !sj.horizontal) {
                if (sk.x1 == sj.x1) {
                    long long inter_y1 = max(sk.min_y, sj.min_y);
                    long long inter_y2 = min(sk.max_y, sj.max_y);
                    if (inter_y1 <= inter_y2) {
                        if (j == ans_k - 1) {
                            if (inter_y1 < inter_y2) {
                                if (sk.y1 < sk.y2) min_d = min(min_d, max(0LL, inter_y1 - sk.y1));
                                else min_d = min(min_d, max(0LL, sk.y1 - inter_y2));
                            }
                        } else {
                            if (sk.y1 < sk.y2) min_d = min(min_d, max(0LL, inter_y1 - sk.y1));
                            else min_d = min(min_d, max(0LL, sk.y1 - inter_y2));
                        }
                    }
                }
            } else {
                const Segment& h = sk.horizontal ? sk : sj;
                const Segment& v = sk.horizontal ? sj : sk;
                if (v.min_x >= h.min_x && v.min_x <= h.max_x && h.min_y >= v.min_y && h.min_y <= v.max_y) {
                    if (j < ans_k - 1) {
                        if (sk.horizontal) min_d = min(min_d, abs(sk.x1 - v.x1));
                        else min_d = min(min_d, abs(sk.y1 - h.y1));
                    }
                }
            }
        }
        total_dist += min_d;
    }

    cout << total_dist << endl;

    return 0;
}