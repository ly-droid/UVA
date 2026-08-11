#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
using namespace std;

const double EPS = 1e-9;

struct Point {
    double x, y;
};

double cross(Point a, Point b, Point c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

double areaSigned(const vector<Point>& p) {
    double s = 0;
    int n = p.size();

    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        s += p[i].x * p[j].y - p[j].x * p[i].y;
    }

    return s / 2.0;
}

double areaAbs(const vector<Point>& p) {
    return fabs(areaSigned(p));
}

Point intersection(Point s, Point e, Point a, Point b) {
    double A1 = e.y - s.y;
    double B1 = s.x - e.x;
    double C1 = A1 * s.x + B1 * s.y;

    double A2 = b.y - a.y;
    double B2 = a.x - b.x;
    double C2 = A2 * a.x + B2 * a.y;

    double det = A1 * B2 - A2 * B1;

    return {
        (B2 * C1 - B1 * C2) / det,
        (A1 * C2 - A2 * C1) / det
    };
}

bool inside(Point p, Point a, Point b, int orient) {
    return orient * cross(a, b, p) >= -EPS;
}

vector<Point> clipPolygon(vector<Point> subject, const vector<Point>& clipper) {
    int orient = areaSigned(clipper) >= 0 ? 1 : -1;

    for (int i = 0; i < (int)clipper.size(); i++) {
        Point a = clipper[i];
        Point b = clipper[(i + 1) % clipper.size()];

        vector<Point> output;

        if (subject.empty()) return output;

        Point s = subject.back();

        for (Point e : subject) {
            bool ein = inside(e, a, b, orient);
            bool sin = inside(s, a, b, orient);

            if (ein) {
                if (!sin) output.push_back(intersection(s, e, a, b));
                output.push_back(e);
            } else if (sin) {
                output.push_back(intersection(s, e, a, b));
            }

            s = e;
        }

        subject = output;
    }

    return subject;
}

int main() {
    int n;
    bool first = true;

    while (cin >> n) {
        if (n == 0) break;

        vector<Point> p1(n);

        for (int i = 0; i < n; i++) {
            cin >> p1[i].x >> p1[i].y;
        }

        int m;
        cin >> m;

        vector<Point> p2(m);

        for (int i = 0; i < m; i++) {
            cin >> p2[i].x >> p2[i].y;
        }

        vector<Point> inter = clipPolygon(p1, p2);

        double ans = areaAbs(p1) + areaAbs(p2) - 2.0 * areaAbs(inter);

        if (fabs(ans) < 0.005) ans = 0.0;

        cout << fixed << setprecision(2) << setw(8) << ans;
    }

    cout << '\n';

    return 0;
}
