#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>

using namespace std;

struct Point {
    long long x, y;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<Point> vertices(n);
    for (int i = 0; i < n; ++i) {
        cin >> vertices[i].x >> vertices[i].y;
    }

    long long double_area = 0;
    long long boundary_points = 0;

    for (int i = 0; i < n; ++i) {
        Point current = vertices[i];
        Point next = vertices[(i + 1) % n];

        double_area += (current.x * next.y) - (next.x * current.y);

        long long dx = abs(current.x - next.x);
        long long dy = abs(current.y - next.y);
        boundary_points += std::gcd(dx, dy);
    }

    double_area = abs(double_area);

    long long interior_points = (double_area - boundary_points + 2) / 2;

    cout << interior_points << " " << boundary_points << "\n";

    return 0;
}