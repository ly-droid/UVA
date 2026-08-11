#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

int main() {
    int n, k, m;

    while (cin >> n >> k >> m) {
        if (n == 0 && k == 0 && m == 0) break;

        vector<int> alive(n + 1, 1);
        int left = n;
        int p1 = 0;
        int p2 = n + 1;
        bool first = true;

        while (left > 0) {
            int cnt = 0;
            while (cnt < k) {
                p1++;
                if (p1 > n) p1 = 1;
                if (alive[p1]) cnt++;
            }

            cnt = 0;
            while (cnt < m) {
                p2--;
                if (p2 < 1) p2 = n;
                if (alive[p2]) cnt++;
            }

            if (!first) cout << ",";
            first = false;

            if (p1 == p2) {
                cout << setw(3) << p1;
                alive[p1] = 0;
                left--;
            } else {
                cout << setw(3) << p1 << setw(3) << p2;
                alive[p1] = 0;
                alive[p2] = 0;
                left -= 2;
            }
        }

        cout << '\n';
    }

    return 0;
}
