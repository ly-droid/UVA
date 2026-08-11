#include <iostream>
#include <vector>
using namespace std;

int survivor(int n, int k, int start) {
    vector<int> a;
    for (int i = 1; i <= n; i++) a.push_back(i);

    int pos = start - 1;

    while ((int)a.size() > 1) {
        int m = a.size();

        int victim = (pos + k - 1) % m;
        a.erase(a.begin() + victim);

        int afterVictimSize = a.size();
        int buryStart = victim % afterVictimSize;
        int burier = (buryStart + k - 1) % afterVictimSize;
        int val = a[burier];

        a.erase(a.begin() + burier);

        int insertPos = victim;
        if (burier < victim) insertPos--;
        if (insertPos > (int)a.size()) insertPos = a.size();

        a.insert(a.begin() + insertPos, val);

        pos = (insertPos + 1) % a.size();
    }

    return a[0];
}

int main() {
    int n, k;

    while (cin >> n >> k) {
        if (n == 0 && k == 0) break;

        for (int i = 1; i <= n; i++) {
            if (survivor(n, k, i) == 1) {
                cout << i << '\n';
                break;
            }
        }
    }

    return 0;
}
