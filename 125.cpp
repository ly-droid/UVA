#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int m;
    int city = 0;

    while (cin >> m) {
        vector<pair<int, int>> edges;
        int maxNode = 0;

        for (int i = 0; i < m; i++) {
            int a, b;
            cin >> a >> b;
            edges.push_back({a, b});
            maxNode = max(maxNode, max(a, b));
        }

        int n = maxNode + 1;

        vector<vector<long long>> ways(n, vector<long long>(n, 0));
        vector<vector<int>> reach(n, vector<int>(n, 0));

        for (auto &e : edges) {
            int a = e.first;
            int b = e.second;
            ways[a][b]++;
            reach[a][b] = 1;
        }

        for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (ways[i][k] && ways[k][j]) {
                        ways[i][j] += ways[i][k] * ways[k][j];
                    }
                }
            }
        }

        for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (reach[i][k] && reach[k][j]) {
                        reach[i][j] = 1;
                    }
                }
            }
        }

        for (int c = 0; c < n; c++) {
            if (reach[c][c]) {
                for (int i = 0; i < n; i++) {
                    for (int j = 0; j < n; j++) {
                        if (reach[i][c] && reach[c][j]) {
                            ways[i][j] = -1;
                        }
                    }
                }
            }
        }

        cout << "matrix for city " << city++ << '\n';

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (j) cout << " ";
                cout << ways[i][j];
            }
            cout << '\n';
        }
    }

    return 0;
}
