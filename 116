#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m, n;

    while (cin >> m >> n) {
        vector<vector<int>> a(m, vector<int>(n));

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                cin >> a[i][j];
            }
        }

        vector<vector<int>> dp(m, vector<int>(n, 0));
        vector<vector<int>> nxt(m, vector<int>(n, -1));

        // last column
        for (int i = 0; i < m; i++) {
            dp[i][n - 1] = a[i][n - 1];
        }

        // DP from right to left
        for (int col = n - 2; col >= 0; col--) {
            for (int row = 0; row < m; row++) {
                vector<int> candidates;

                candidates.push_back((row - 1 + m) % m); 
                candidates.push_back(row);  
                candidates.push_back((row + 1) % m);    

                // Important for lexicographically smallest path
                sort(candidates.begin(), candidates.end());

                int bestRow = candidates[0];
                int bestCost = dp[bestRow][col + 1];

                for (int r : candidates) {
                    if (dp[r][col + 1] < bestCost) {
                        bestCost = dp[r][col + 1];
                        bestRow = r;
                    }
                }

                dp[row][col] = a[row][col] + bestCost;
                nxt[row][col] = bestRow;
            }
        }

        // choose best starting row
        int start = 0;
        for (int i = 1; i < m; i++) {
            if (dp[i][0] < dp[start][0]) {
                start = i;
            }
        }

        // reconstruct path
        int row = start;
        for (int col = 0; col < n; col++) {
            if (col > 0) cout << " ";
            cout << row + 1; 

            if (col < n - 1) {
                row = nxt[row][col];
            }
        }

        cout << "\n";
        cout << dp[start][0] << "\n";
    }

    return 0;
}
