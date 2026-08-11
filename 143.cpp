#include <iostream>
#include <iomanip>
#include <cmath>
#include <algorithm>
using namespace std;

const double EPS = 1e-7;

struct Point {
    double x, y;
};

double cross(Point a, Point b, Point c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

bool inside(Point p, Point a, Point b, Point c) {
    double c1 = cross(a, b, p);
    double c2 = cross(b, c, p);
    double c3 = cross(c, a, p);

    return (c1 >= -EPS && c2 >= -EPS && c3 >= -EPS) ||
           (c1 <= EPS && c2 <= EPS && c3 <= EPS);
}

int main() {
    Point a, b, c;

    while (cin >> a.x >> a.y >> b.x >> b.y >> c.x >> c.y) {
        if (fabs(a.x) < EPS && fabs(a.y) < EPS &&
            fabs(b.x) < EPS && fabs(b.y) < EPS &&
            fabs(c.x) < EPS && fabs(c.y) < EPS) {
            break;
        }

        int ans = 0;

        int minX = max(1, (int)ceil(min({a.x, b.x, c.x}) - EPS));
        int maxX = min(99, (int)floor(max({a.x, b.x, c.x}) + EPS));
        int minY = max(1, (int)ceil(min({a.y, b.y, c.y}) - EPS));
        int maxY = min(99, (int)floor(max({a.y, b.y, c.y}) + EPS));

        for (int x = minX; x <= maxX; x++) {
            for (int y = minY; y <= maxY; y++) {
                Point p;
                p.x = x;
                p.y = y;

                if (inside(p, a, b, c)) {
                    ans++;
                }
            }
        }

        cout << setw(4) << ans << '\n';
    }

    return 0;
}
