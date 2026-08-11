#include <iostream>
#include <queue>
#include <vector>
#include <iomanip>
using namespace std;

int main() {
    int N, k;

    while (cin >> N >> k) {
        if (N == 0 && k == 0) break;

        queue<int> q;
        vector<int> paid(N + 1, 0);

        for (int i = 1; i <= N; i++) {
            q.push(i);
        }

        int store = 0;
        int nextCoins = 1;

        while (!q.empty()) {
            if (store == 0) {
                store = nextCoins;
                nextCoins++;
                if (nextCoins > k) nextCoins = 1;
            }

            int student = q.front();
            q.pop();

            int need = 40 - paid[student];

            if (store >= need) {
                store -= need;
                paid[student] = 40;
                cout << setw(3) << student;
            } else {
                paid[student] += store;
                store = 0;
                q.push(student);
            }
        }

        cout << '\n';
    }

    return 0;
}
