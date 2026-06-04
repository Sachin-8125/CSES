#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

struct Point {
    long long x, y;
};

int orientation(Point p, Point q, Point r) {
    long long val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    if (val == 0) return 0; 
    return (val > 0) ? 1 : 2; 
}

bool onSegment(Point p, Point q, Point r) {
    if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) &&
        q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y))
        return true;
    return false;
}

bool doIntersect(Point p1, Point q1, Point p2, Point q2) {
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);

    if (o1 != o2 && o3 != o4)
        return true;

    if (o1 == 0 && onSegment(p1, p2, q1)) return true;
    if (o2 == 0 && onSegment(p1, q2, q1)) return true;
    if (o3 == 0 && onSegment(p2, p1, q2)) return true;
    if (o4 == 0 && onSegment(p2, q1, q2)) return true;

    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<Point> polygon(n);
    for (int i = 0; i < n; i++) {
        cin >> polygon[i].x >> polygon[i].y;
    }

    for (int i = 0; i < m; i++) {
        Point p;
        cin >> p.x >> p.y;

        bool boundary = false;
        for (int j = 0; j < n; j++) {
            Point p1 = polygon[j];
            Point p2 = polygon[(j + 1) % n];
            if (orientation(p1, p, p2) == 0 && onSegment(p1, p, p2)) {
                boundary = true;
                break;
            }
        }

        if (boundary) {
            cout << "BOUNDARY\n";
            continue;
        }

        Point extreme = {1000000009, p.y + 1};
        int count = 0;
        for (int j = 0; j < n; j++) {
            Point p1 = polygon[j];
            Point p2 = polygon[(j + 1) % n];
            if (doIntersect(p1, p2, p, extreme)) {
                count++;
            }
        }

        if (count % 2 == 1) {
            cout << "INSIDE\n";
        } else {
            cout << "OUTSIDE\n";
        }
    }

    return 0;
}