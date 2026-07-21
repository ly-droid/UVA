#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

vector<char> vars;
int n;
bool adj[26][26];
int indeg[26];
bool used[26];
string cur;

void dfs() {
    if ((int)cur.size() == n) {
        cout << cur << '\n';
        return;
    }

    for (char c : vars) {
        int u = c - 'a';

        if (!used[u] && indeg[u] == 0) {
            used[u] = true;
            cur.push_back(c);

            for (int v = 0; v < 26; v++) {
                if (adj[u][v]) indeg[v]--;
            }

            dfs();

            for (int v = 0; v < 26; v++) {
                if (adj[u][v]) indeg[v]++;
            }

            cur.pop_back();
            used[u] = false;
        }
    }
}

int main() {
    string line1, line2;
    bool firstCase = true;

    while (getline(cin, line1)) {
        if (!getline(cin, line2)) break;

        vars.clear();
        cur.clear();

        for (int i = 0; i < 26; i++) {
            indeg[i] = 0;
            used[i] = false;
            for (int j = 0; j < 26; j++) {
                adj[i][j] = false;
            }
        }

        stringstream ss1(line1);
        char c;

        while (ss1 >> c) {
            vars.push_back(c);
        }

        sort(vars.begin(), vars.end());
        n = vars.size();

        stringstream ss2(line2);
        char a, b;

        while (ss2 >> a >> b) {
            int u = a - 'a';
            int v = b - 'a';

            if (!adj[u][v]) {
                adj[u][v] = true;
                indeg[v]++;
            }
        }

        if (!firstCase) cout << '\n';
        firstCase = false;

        dfs();
    }

    return 0;
}
