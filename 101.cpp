#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<vector<int> > piles(n);
    vector<int> pos(n);  

    for (int i = 0; i < n; ++i) {
        piles[i].push_back(i);
        pos[i] = i;
    }

    string cmd1, cmd2;
    int a, b;

    auto clear_above = [&](int x) {
        int p = pos[x];
        while (!piles[p].empty() && piles[p].back() != x) {
            int topBlock = piles[p].back();
            piles[p].pop_back();
            piles[topBlock].push_back(topBlock);
            pos[topBlock] = topBlock;
        }
    };

    auto pile_over = [&](int a, int b) {
        int pa = pos[a];
        int pb = pos[b];

        vector<int> moving;
        bool start = false;

        for (int block : piles[pa]) {
            if (block == a) start = true;
            if (start) moving.push_back(block);
        }

        while (!piles[pa].empty()) {
            int topBlock = piles[pa].back();
            piles[pa].pop_back();
            if (topBlock == a) break;
        }

        for (int block : moving) {
            piles[pb].push_back(block);
            pos[block] = pb;
        }
    };

    while (cin >> cmd1) {
        if (cmd1 == "quit") break;

        cin >> a >> cmd2 >> b;

        if (a == b) continue;
        if (pos[a] == pos[b]) continue;  

        if (cmd1 == "move") {
            clear_above(a);
        }
        if (cmd2 == "onto") {
            clear_above(b);
        }

        pile_over(a, b);
    }

    for (int i = 0; i < n; ++i) {
        cout << i << ":";
        for (int block : piles[i]) {
            cout << " " << block;
        }
        cout << "\n";
    }

    return 0;
}
