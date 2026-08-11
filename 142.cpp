#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <climits>
using namespace std;

struct Icon {
    int x, y;
};

struct Region {
    int x1, y1, x2, y2;
};

bool insideRegion(int x, int y, const Region& r) {
    return x >= r.x1 && x <= r.x2 && y >= r.y1 && y <= r.y2;
}

int dist2(int x1, int y1, int x2, int y2) {
    int dx = x1 - x2;
    int dy = y1 - y2;
    return dx * dx + dy * dy;
}

int main() {
    vector<Icon> icons;
    vector<Region> regions;
    vector<bool> visible;

    char type;

    while (cin >> type) {
        if (type == '#') break;

        if (type == 'I') {
            int x, y;
            cin >> x >> y;
            icons.push_back({x, y});
        } else if (type == 'R') {
            int x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            regions.push_back({x1, y1, x2, y2});
        } else if (type == 'M') {
            int x, y;
            cin >> x >> y;

            if (visible.empty()) {
                visible.assign(icons.size(), true);

                for (int i = 0; i < (int)icons.size(); i++) {
                    for (int j = 0; j < (int)regions.size(); j++) {
                        if (insideRegion(icons[i].x, icons[i].y, regions[j])) {
                            visible[i] = false;
                            break;
                        }
                    }
                }
            }

            int chosenRegion = -1;

            for (int i = (int)regions.size() - 1; i >= 0; i--) {
                if (insideRegion(x, y, regions[i])) {
                    chosenRegion = i;
                    break;
                }
            }

            if (chosenRegion != -1) {
                cout << char('A' + chosenRegion) << '\n';
            } else {
                int best = INT_MAX;

                for (int i = 0; i < (int)icons.size(); i++) {
                    if (visible[i]) {
                        best = min(best, dist2(x, y, icons[i].x, icons[i].y));
                    }
                }

                for (int i = 0; i < (int)icons.size(); i++) {
                    if (visible[i] && dist2(x, y, icons[i].x, icons[i].y) == best) {
                        cout << setw(3) << i + 1;
                    }
                }

                cout << '\n';
            }
        }
    }

    return 0;
}
