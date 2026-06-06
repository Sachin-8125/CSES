#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct Point {
    ll x, y;
    Point(ll x = 0, ll y = 0) : x(x), y(y) {}
};

ll cross(const Point &a, const Point &b, const Point &c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

int orientation(const Point &a, const Point &b, const Point &c) {
    ll val = cross(a, b, c);
    if (val == 0) return 0;
    return (val > 0) ? 1 : 2;
}

bool onSegment(const Point &a, const Point &b, const Point &p) {
    return min(a.x, b.x) <= p.x && p.x <= max(a.x, b.x) &&
           min(a.y, b.y) <= p.y && p.y <= max(a.y, b.y);
}

bool segmentsIntersect(const Point &a1, const Point &a2, 
                       const Point &b1, const Point &b2) {
    int o1 = orientation(a1, a2, b1);
    int o2 = orientation(a1, a2, b2);
    int o3 = orientation(b1, b2, a1);
    int o4 = orientation(b1, b2, a2);

    if (o1 != o2 && o3 != o4) return true;

    if (o1 == 0 && onSegment(a1, a2, b1)) return true;
    if (o2 == 0 && onSegment(a1, a2, b2)) return true;
    if (o3 == 0 && onSegment(b1, b2, a1)) return true;
    if (o4 == 0 && onSegment(b1, b2, a2)) return true;

    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    cin >> t;
    while (t--) {
        Point a1, a2, b1, b2;
        cin >> a1.x >> a1.y >> a2.x >> a2.y;
        cin >> b1.x >> b1.y >> b2.x >> b2.y;
        
        cout << (segmentsIntersect(a1, a2, b1, b2) ? "YES" : "NO") << "\n";
    }
    return 0;
}
