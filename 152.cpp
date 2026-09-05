#include <iostream>
#include <vector>
#include <iomanip>
#include <climits>
#include <cmath>
using namespace std;

struct Point {
    int x, y, z;
};

int main() {
    vector<Point> points;
    int x, y, z;

    while (cin >> x >> y >> z) {
        if (x == 0 && y == 0 && z == 0) break;
        points.push_back({x, y, z});
    }

    int histogram[10] = {0};
    int n = points.size();

    for (int i = 0; i < n; i++) {
        int nearest = INT_MAX;

        for (int j = 0; j < n; j++) {
            if (i == j) continue;

            int dx = points[i].x - points[j].x;
            int dy = points[i].y - points[j].y;
            int dz = points[i].z - points[j].z;

            int distanceSquared = dx * dx + dy * dy + dz * dz;
            nearest = min(nearest, distanceSquared);
        }

        int bin = static_cast<int>(sqrt(nearest));

        if (bin < 10) {
            histogram[bin]++;
        }
    }

    for (int i = 0; i < 10; i++) {
        cout << setw(4) << histogram[i];
    }

    cout << '\n';

    return 0;
}
