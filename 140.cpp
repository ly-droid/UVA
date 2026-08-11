#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>
#include <cstring>
using namespace std;

int main() {
    string line;

    while (getline(cin, line)) {
        if (line == "#") break;

        bool adj[26][26];
        memset(adj, false, sizeof(adj));

        set<char> nodes;

        int i = 0;
        while (i < (int)line.size()) {
            char u = line[i];
            nodes.insert(u);
            i += 2;

            while (i < (int)line.size() && line[i] != ';') {
                char v = line[i];
                nodes.insert(v);
                adj[u - 'A'][v - 'A'] = true;
                adj[v - 'A'][u - 'A'] = true;
                i++;
            }

            if (i < (int)line.size() && line[i] == ';') i++;
        }

        vector<char> perm(nodes.begin(), nodes.end());
        vector<char> best = perm;
        int bestBw = 1000000;

        do {
            int pos[26];

            for (int i = 0; i < (int)perm.size(); i++) {
                pos[perm[i] - 'A'] = i;
            }

            int bw = 0;

            for (int a = 0; a < 26; a++) {
                for (int b = a + 1; b < 26; b++) {
                    if (adj[a][b]) {
                        bw = max(bw, abs(pos[a] - pos[b]));
                    }
                }
            }

            if (bw < bestBw) {
                bestBw = bw;
                best = perm;
            }

        } while (next_permutation(perm.begin(), perm.end()));

        for (char c : best) {
            cout << c << " ";
        }

        cout << "-> " << bestBw << '\n';
    }

    return 0;
}
