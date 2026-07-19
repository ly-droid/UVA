#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;

    while (cin >> s) {
        vector<vector<int>> dist(26, vector<int>(26, INF));
        vector<int> degree(26, 0);

        for (int i = 0; i < 26; i++) {
            dist[i][i] = 0;
        }

        int total = 0;

        while (s != "deadend") {
            int u = s.front() - 'a';
            int v = s.back() - 'a';
            int w = (int)s.length();

            total += w;
            degree[u]++;
            degree[v]++;

            dist[u][v] = min(dist[u][v], w);
            dist[v][u] = min(dist[v][u], w);

            cin >> s;
        }

        vector<int> odd;
        for (int i = 0; i < 26; i++) {
            if (degree[i] % 2 == 1) {
                odd.push_back(i);
            }
        }

        // Floyd-Warshall
        for (int k = 0; k < 26; k++) {
            for (int i = 0; i < 26; i++) {
                for (int j = 0; j < 26; j++) {
                    if (dist[i][k] + dist[k][j] < dist[i][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                    }
                }
            }
        }

        int answer = total;

        if (odd.size() == 2) {
            answer += dist[odd[0]][odd[1]];
        }

        cout << answer << "\n";
    }

    return 0;
}
