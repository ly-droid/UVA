#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    while (cin >> n) {
        vector<vector<vector<double>>> best(
            n + 1, vector<vector<double>>(n, vector<double>(n, 0.0))
        );

        vector<vector<vector<int>>> parent(
            n + 1, vector<vector<int>>(n, vector<int>(n, -1))
        );

        // Read input
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i == j) {
                    best[1][i][j] = 1.0;
                } else {
                    cin >> best[1][i][j];
                    parent[1][i][j] = i;
                }
            }
        }

        bool found = false;
        int start = -1, steps = -1;

        for (int s = 2; s <= n && !found; ++s) {
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    best[s][i][j] = 0.0;
                    parent[s][i][j] = -1;

                    for (int k = 0; k < n; ++k) {
                        double candidate = best[s - 1][i][k] * best[1][k][j];
                        if (candidate > best[s][i][j]) {
                            best[s][i][j] = candidate;
                            parent[s][i][j] = k;
                        }
                    }
                }
            }

            for (int i = 0; i < n; ++i) {
                if (best[s][i][i] > 1.01) {
                    found = true;
                    start = i;
                    steps = s;
                    break;
                }
            }
        }

        if (!found) {
            cout << "no arbitrage sequence exists\n";
            continue;
        }

        vector<int> path(steps + 1);
        path[steps] = start;

        int curr = start;
        for (int s = steps; s >= 1; --s) {
            path[s - 1] = parent[s][start][curr];
            curr = path[s - 1];
        }

        for (int i = 0; i <= steps; ++i) {
            if (i) cout << ' ';
            cout << path[i] + 1;  
        }
        cout << '\n';
    }

    return 0;
}
