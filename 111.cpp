#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string line;
    int n = 0;
    vector<int> correctRank, correctOrder;
    bool readCorrect = false;

    while (getline(cin, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        vector<int> a;
        int x;
        while (ss >> x) a.push_back(x);
        if (a.empty()) continue;

        if (a.size() == 1) {
            n = a[0];
            correctRank.assign(n + 1, 0);
            correctOrder.assign(n + 1, 0);
            readCorrect = true;
            continue;
        }

        if (readCorrect) {
            for (int i = 1; i <= n; ++i) correctRank[i] = a[i - 1];
            for (int event = 1; event <= n; ++event) correctOrder[correctRank[event]] = event;
            readCorrect = false;
            continue;
        }

        vector<int> studentRank(n + 1), studentOrder(n + 1);
        for (int i = 1; i <= n; ++i) studentRank[i] = a[i - 1];
        for (int event = 1; event <= n; ++event) studentOrder[studentRank[event]] = event;

        vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (correctOrder[i] == studentOrder[j]) dp[i][j] = dp[i - 1][j - 1] + 1;
                else dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }

        cout << dp[n][n] << '\n';
    }

    return 0;
}

