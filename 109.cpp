#include <bits/stdc++.h>
using namespace std;

struct Point {
    double x, y;
    bool operator<(const Point& other) const {
        if (x != other.x) return x < other.x;
        return y < other.y;
    }
    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
};

double cross(const Point& O, const Point& A, const Point& B) {
    return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}

vector<Point> convexHull(vector<Point> p) {
    sort(p.begin(), p.end());
    p.erase(unique(p.begin(), p.end()), p.end());
    int n = p.size(), k = 0;
    if (n <= 1) return p;
    vector<Point> h(2 * n);

    for (int i = 0; i < n; i++) {
        while (k >= 2 && cross(h[k - 2], h[k - 1], p[i]) <= 0) k--;
        h[k++] = p[i];
    }
    for (int i = n - 2, t = k + 1; i >= 0; i--) {
        while (k >= t && cross(h[k - 2], h[k - 1], p[i]) <= 0) k--;
        h[k++] = p[i];
    }
    h.resize(k - 1);
    return h;
}

double polygonArea(const vector<Point>& poly) {
    double area = 0;
    int n = poly.size();
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        area += poly[i].x * poly[j].y - poly[j].x * poly[i].y;
    }
    return fabs(area) / 2.0;
}

bool onSegment(const Point& a, const Point& b, const Point& p) {
    const double eps = 1e-9;
    if (fabs(cross(a, b, p)) > eps) return false;
    return min(a.x, b.x) - eps <= p.x && p.x <= max(a.x, b.x) + eps &&
           min(a.y, b.y) - eps <= p.y && p.y <= max(a.y, b.y) + eps;
}

bool pointInPolygon(const vector<Point>& poly, const Point& p) {
    int n = poly.size();
    bool in = false;
    for (int i = 0, j = n - 1; i < n; j = i++) {
        if (onSegment(poly[j], poly[i], p)) return true;
        bool intersect = ((poly[i].y > p.y) != (poly[j].y > p.y)) &&
                         (p.x < (poly[j].x - poly[i].x) * (p.y - poly[i].y) / (poly[j].y - poly[i].y) + poly[i].x);
        if (intersect) in = !in;
    }
    return in;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<vector<Point>> kingdoms;
    vector<double> areas;
    vector<bool> destroyed;

    int n;
    while (cin >> n && n != -1) {
        vector<Point> pts(n);
        for (int i = 0; i < n; i++) cin >> pts[i].x >> pts[i].y;
        vector<Point> hull = convexHull(pts);
        kingdoms.push_back(hull);
        areas.push_back(polygonArea(hull));
        destroyed.push_back(false);
    }

    Point missile;
    while (cin >> missile.x >> missile.y) {
        for (int i = 0; i < (int)kingdoms.size(); i++) {
            if (!destroyed[i] && pointInPolygon(kingdoms[i], missile)) {
                destroyed[i] = true;
            }
        }
    }

    double ans = 0;
    for (int i = 0; i < (int)areas.size(); i++) {
        if (destroyed[i]) ans += areas[i];
    }

    cout << fixed << setprecision(2) << ans << '\n';
    return 0;
}
