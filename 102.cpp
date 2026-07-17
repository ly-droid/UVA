#include <iostream>
#include <vector>
#include <string>
#include <climits>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long b1, g1, c1, b2, g2, c2, b3, g3, c3;

    vector<string> orders = {"BCG", "BGC", "CBG", "CGB", "GBC", "GCB"};

    while (cin >> b1 >> g1 >> c1 >> b2 >> g2 >> c2 >> b3 >> g3 >> c3) {
        long long bins[3][3] = {
            {b1, g1, c1},
            {b2, g2, c2},
            {b3, g3, c3}
        };

        long long total = b1 + g1 + c1 + b2 + g2 + c2 + b3 + g3 + c3;

        string bestOrder;
        long long minMoves = LLONG_MAX;

        for (const string& order : orders) {
            int colorIdx[3];
            for (int i = 0; i < 3; i++) {
                if (order[i] == 'B') colorIdx[i] = 0;
                else if (order[i] == 'G') colorIdx[i] = 1;
                else colorIdx[i] = 2; // 'C'
            }

            long long stay = 0;
            for (int i = 0; i < 3; i++) {
                stay += bins[i][colorIdx[i]];
            }

            long long moves = total - stay;

            if (moves < minMoves) {
                minMoves = moves;
                bestOrder = order;
            }
        }

        cout << bestOrder << " " << minMoves << "\n";
    }

    return 0;
}

