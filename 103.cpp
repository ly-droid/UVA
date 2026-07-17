#include <bits/stdc++.h>
using namespace std;

struct Box {
    vector<int> dim;
    int id;
};

bool canNest(const Box& a, const Box& b) {
    for (size_t i = 0; i < a.dim.size(); ++i) {
        if (a.dim[i] >= b.dim[i]) return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int k, n;
    while (cin >> k >> n) {
        vector<Box> boxes(k);

        for (int i = 0; i < k; ++i) {
            boxes[i].dim.resize(n);
            for (int j = 0; j < n; ++j) {
                cin >> boxes[i].dim[j];
            }
            sort(boxes[i].dim.begin(), boxes[i].dim.end());
            boxes[i].id = i + 1;
        }

        
        sort(boxes.begin(), boxes.end(), [](const Box& a, const Box& b) {
            return a.dim < b.dim;
        });

        vector<int> dp(k, 1), parent(k, -1);

        int bestLen = 1, bestEnd = 0;

        for (int i = 0; i < k; ++i) {
            for (int j = 0; j < i; ++j) {
                if (canNest(boxes[j], boxes[i])) {
                    if (dp[j] + 1 > dp[i]) {
                        dp[i] = dp[j] + 1;
                        parent[i] = j;
                    }
                }
            }
            if (dp[i] > bestLen) {
                bestLen = dp[i];
                bestEnd = i;
            }
        }

        vector<int> path;
        int cur = bestEnd;
        while (cur != -1) {
            path.push_back(boxes[cur].id);
            cur = parent[cur];
        }
        reverse(path.begin(), path.end());

        cout << bestLen << '\n';
        for (int i = 0; i < (int)path.size(); ++i) {
            if (i) cout << ' ';
            cout << path[i];
        }
        cout << '\n';
    }

    return 0;
}
