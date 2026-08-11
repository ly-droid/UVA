#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <cmath>
#include <algorithm>
using namespace std;

const double EPS = 1e-9;

struct Point {
    double x, y;
};

double cross(Point a, Point b, Point c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

double proj(Point a, Point b, Point c) {
    return (c.x - a.x) * (b.x - a.x) + (c.y - a.y) * (b.y - a.y);
}

int main() {
    string id;

    while (cin >> id) {
        if (id == "#") break;

        Point cm;
        cin >> cm.x >> cm.y;

        vector<Point> p;
        double x, y;

        while (cin >> x >> y) {
            if (fabs(x) < EPS && fabs(y) < EPS) break;
            p.push_back({x, y});
        }

        int n = p.size();
        int ans = n + 1;

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                Point a = p[i], b = p[j];

                int pos = 0, neg = 0;
                vector<int> touch;

                for (int k = 0; k < n; k++) {
                    double c = cross(a, b, p[k]);

                    if (c > EPS) pos = 1;
                    else if (c < -EPS) neg = 1;
                    else touch.push_back(k);
                }

                if (pos && neg) continue;

                double cmSide = cross(a, b, cm);
                if (pos && cmSide <= EPS) continue;
                if (neg && cmSide >= -EPS) continue;
                if (!pos && !neg) continue;

                double mn = 1e100, mx = -1e100;
                int base = 0;

                for (int k : touch) {
                    double t = proj(a, b, p[k]);
                    mn = min(mn, t);
                    mx = max(mx, t);
                    base = max(base, k + 1);
                }

                double cmt = proj(a, b, cm);

                if (cmt > mn + EPS && cmt < mx - EPS) {
                    ans = min(ans, base);
                }
            }
        }

        cout << left << setw(20) << id << ans << '\n';
    }

    return 0;
}
