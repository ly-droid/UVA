#include <bits/stdc++.h>
using namespace std;

struct Bumper {
    bool exists = false;
    long long value = 0;
    long long cost = 0;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m, n;
    cin >> m >> n;

    long long wallCost;
    cin >> wallCost;

    int p;
    cin >> p;

    vector<vector<Bumper>> grid(m + 1, vector<Bumper>(n + 1));

    for (int i = 0; i < p; i++) {
        int x, y;
        long long value, cost;
        cin >> x >> y >> value >> cost;

        grid[x][y].exists = true;
        grid[x][y].value = value;
        grid[x][y].cost = cost;
    }

    // Directions: 0 = right, 1 = up, 2 = left, 3 = down
    int dx[4] = {1, 0, -1, 0};
    int dy[4] = {0, 1, 0, -1};

    long long totalScore = 0;

    int x, y, dir;
    long long life;

    while (cin >> x >> y >> dir >> life) {
        long long score = 0;

        while (life > 1) {
            life--; 

            int nx = x + dx[dir];
            int ny = y + dy[dir];

            bool hitWall = (nx == 1 || nx == m || ny == 1 || ny == n);

            if (hitWall) {
                life -= wallCost;
                dir = (dir + 3) % 4; 
            } 
            else if (grid[nx][ny].exists) {
                score += grid[nx][ny].value;
                life -= grid[nx][ny].cost;
                dir = (dir + 3) % 4; 
            } 
            else {
                x = nx;
                y = ny;
            }
        }

        cout << score << '\n';
        totalScore += score;
    }

    cout << totalScore << '\n';

    return 0;
}
