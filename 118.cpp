#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int maxX, maxY;
    cin >> maxX >> maxY;

    bool scent[55][55] = {};

    string dirs = "NESW";

    int dx[4] = {0, 1, 0, -1};
    int dy[4] = {1, 0, -1, 0};

    int x, y;
    char face;
    string commands;

    while (cin >> x >> y >> face) {
        cin >> commands;

        int dir = dirs.find(face);
        bool lost = false;

        for (char c : commands) {
            if (lost) break;

            if (c == 'L') {
                dir = (dir + 3) % 4;
            } 
            else if (c == 'R') {
                dir = (dir + 1) % 4;
            } 
            else if (c == 'F') {
                int nx = x + dx[dir];
                int ny = y + dy[dir];

                if (nx < 0 || nx > maxX || ny < 0 || ny > maxY) {
                    if (scent[x][y]) {
                        continue;
                    } else {
                        scent[x][y] = true;
                        lost = true;
                    }
                } else {
                    x = nx;
                    y = ny;
                }
            }
        }

        cout << x << " " << y << " " << dirs[dir];

        if (lost) {
            cout << " LOST";
        }

        cout << "\n";
    }

    return 0;
}
