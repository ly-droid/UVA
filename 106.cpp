#include <bits/stdc++.h>
using namespace std;

int gcd_int(int a, int b) {
    while (b != 0) {
        int t = a % b;
        a = b;
        b = t;
    }
    return a;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<int> queries;
    int N, maxN = 0;
    while (cin >> N) {
        queries.push_back(N);
        if (N > maxN) maxN = N;
    }

    if (queries.empty()) return 0;

    vector<int> primitiveCount(maxN + 1, 0);

    const int INF = 1e9;
    vector<int> minAppear(maxN + 1, INF);

    for (int m = 2; 1LL * m * m <= maxN; ++m) {
        for (int n = 1; n < m; ++n) {
            if (((m - n) & 1) == 0) continue;   
            if (gcd_int(m, n) != 1) continue;   

            int a = m * m - n * n;
            int b = 2 * m * n;
            int c = m * m + n * n;

            if (c > maxN) break;
            if (a > b) swap(a, b);

            primitiveCount[c]++;

            for (int k = 1; 1LL * k * c <= maxN; ++k) {
                int x = k * a;
                int y = k * b;
                int z = k * c;

                if (minAppear[x] > z) minAppear[x] = z;
                if (minAppear[y] > z) minAppear[y] = z;
                if (minAppear[z] > z) minAppear[z] = z;
            }
        }
    }

    vector<int> appearCount(maxN + 1, 0);
    for (int i = 1; i <= maxN; ++i) {
        if (minAppear[i] <= maxN) {
            appearCount[minAppear[i]]++;
        }
    }

    vector<int> primitivePrefix(maxN + 1, 0);
    vector<int> usedPrefix(maxN + 1, 0);

    for (int i = 1; i <= maxN; ++i) {
        primitivePrefix[i] = primitivePrefix[i - 1] + primitiveCount[i];
        usedPrefix[i] = usedPrefix[i - 1] + appearCount[i];
    }

    for (int q : queries) {
        int primitiveTriples = primitivePrefix[q];
        int notInAnyTriple = q - usedPrefix[q];
        cout << primitiveTriples << ' ' << notInAnyTriple << '\n';
    }

    return 0;
}
