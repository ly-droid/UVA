#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    vector<int> height(10001, 0);
    int L, H, R;
    int maxR = 0;

    while (cin >> L >> H >> R) {
        for (int x = L; x < R; ++x) {
            height[x] = max(height[x], H);
        }
        maxR = max(maxR, R);
    }

    bool first = true;
    int prev = 0;

    for (int x = 0; x <= maxR; ++x) {
        if (height[x] != prev) {
            if (!first) cout << " ";
            cout << x << " " << height[x];
            first = false;
            prev = height[x];
        }
    }

    cout << "\n";
    return 0;
}
