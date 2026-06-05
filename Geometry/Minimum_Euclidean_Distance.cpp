#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

struct Point {
    long long x, y;
};

bool compareX(const Point& a, const Point& b) {
    return a.x < b.x;
}

bool compareY(const Point& a, const Point& b) {
    return a.y < b.y;
}

long long dist_sq(const Point& p1, const Point& p2) {
    return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}

long long closest_pair_rec(vector<Point>& points_x, int left, int right) {
    if (right - left <= 3) {
        long long min_d = 9e18;
        for (int i = left; i < right; ++i) {
            for (int j = i + 1; j < right; ++j) {
                min_d = min(min_d, dist_sq(points_x[i], points_x[j]));
            }
        }
        return min_d;
    }

    int mid = left + (right - left) / 2;
    Point mid_point = points_x[mid];

    long long dl = closest_pair_rec(points_x, left, mid);
    long long dr = closest_pair_rec(points_x, mid, right);
    long long d = min(dl, dr);

    vector<Point> strip;
    for (int i = left; i < right; ++i) {
        if ((points_x[i].x - mid_point.x) * (points_x[i].x - mid_point.x) < d) {
            strip.push_back(points_x[i]);
        }
    }

    sort(strip.begin(), strip.end(), compareY);

    for (size_t i = 0; i < strip.size(); ++i) {
        for (size_t j = i + 1; j < strip.size() && (strip[j].y - strip[i].y) * (strip[j].y - strip[i].y) < d; ++j) {
            d = min(d, dist_sq(strip[i], strip[j]));
        }
    }

    return d;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<Point> points(n);
    for (int i = 0; i < n; ++i) {
        cin >> points[i].x >> points[i].y;
    }

    sort(points.begin(), points.end(), compareX);

    cout << closest_pair_rec(points, 0, n) << "\n";

    return 0;
}