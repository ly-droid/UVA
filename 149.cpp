#include <bits/stdc++.h>
using namespace std;

const double PI = acos(-1.0);
const double TWO_PI = 2.0 * PI;
const double LIM = PI / 18000.0;
const double EPS = 1e-10;

struct Node {
    double d2;
    int x, y, dir;

    bool operator<(const Node& other) const {
        return d2 > other.d2;
    }
};

map<double, double> seg;
double covered;

bool hitOne(double l, double r) {
    auto it = seg.upper_bound(l);

    if (it != seg.begin()) {
        auto p = it;
        --p;
        if (p->second >= l - EPS) return true;
    }

    if (it != seg.end() && it->first <= r + EPS) return true;

    return false;
}

bool hit(double l, double r) {
    while (l < 0) {
        l += TWO_PI;
        r += TWO_PI;
    }
    while (l >= TWO_PI) {
        l -= TWO_PI;
        r -= TWO_PI;
    }

    if (r <= TWO_PI) {
        return hitOne(l, r);
    } else {
        return hitOne(l, TWO_PI) || hitOne(0, r - TWO_PI);
    }
}

void addOne(double l, double r) {
    l = max(l, 0.0);
    r = min(r, TWO_PI);

    auto it = seg.lower_bound(l);

    if (it != seg.begin()) {
        auto p = it;
        --p;

        if (p->second >= l - EPS) {
            l = min(l, p->first);
            r = max(r, p->second);
            covered -= p->second - p->first;
            seg.erase(p);
        }
    }

    it = seg.lower_bound(l);

    while (it != seg.end() && it->first <= r + EPS) {
        l = min(l, it->first);
        r = max(r, it->second);
        covered -= it->second - it->first;
        it = seg.erase(it);
    }

    seg[l] = r;
    covered += r - l;
}

void addSeg(double l, double r) {
    if (r - l >= TWO_PI - EPS) {
        seg.clear();
        seg[0] = TWO_PI;
        covered = TWO_PI;
        return;
    }

    while (l < 0) {
        l += TWO_PI;
        r += TWO_PI;
    }
    while (l >= TWO_PI) {
        l -= TWO_PI;
        r -= TWO_PI;
    }

    if (r <= TWO_PI) {
        addOne(l, r);
    } else {
        addOne(l, TWO_PI);
        addOne(0, r - TWO_PI);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    double d, ox, oy;

    while (cin >> d >> ox >> oy) {
        if (d == 0 && ox == 0 && oy == 0) break;

        double rad = d / 2.0;
        double maxDist = rad / sin(LIM / 2.0);
        double maxD2 = maxDist * maxDist;
        double rad2 = rad * rad;

        priority_queue<Node> pq;

        int xmin = (int)ceil(ox - maxDist);
        int xmax = (int)floor(ox + maxDist);

        for (int x = xmin; x <= xmax; x++) {
            int y1 = (int)ceil(oy);
            int y2 = (int)floor(oy);

            double dx = x - ox;

            double dy = y1 - oy;
            double d2 = dx * dx + dy * dy;
            if (d2 <= maxD2 + EPS) pq.push({d2, x, y1, 1});

            if (y2 != y1) {
                dy = y2 - oy;
                d2 = dx * dx + dy * dy;
                if (d2 <= maxD2 + EPS) pq.push({d2, x, y2, -1});
            }
        }

        seg.clear();
        covered = 0.0;
        int ans = 0;

        while (!pq.empty() && covered < TWO_PI - EPS) {
            double curD2 = pq.top().d2;
            vector<Node> group;

            while (!pq.empty() && fabs(pq.top().d2 - curD2) < EPS) {
                Node now = pq.top();
                pq.pop();

                if (now.d2 > rad2 + EPS) {
                    group.push_back(now);
                }

                int ny = now.y + now.dir;
                double dx = now.x - ox;
                double dy = ny - oy;
                double nd2 = dx * dx + dy * dy;

                if (nd2 <= maxD2 + EPS) {
                    pq.push({nd2, now.x, ny, now.dir});
                }
            }

            vector<pair<double, double>> addList;

            for (auto &t : group) {
                double dist = sqrt(t.d2);
                double half = asin(rad / dist);

                if (2.0 * half <= LIM + EPS) continue;

                double ang = atan2(t.y - oy, t.x - ox);
                if (ang < 0) ang += TWO_PI;

                double l = ang - half;
                double r = ang + half;

                if (!hit(l, r)) ans++;

                addList.push_back({l - LIM, r + LIM});
            }

            for (auto &p : addList) {
                addSeg(p.first, p.second);
            }
        }

        cout << ans << '\n';
    }

    return 0;
}
