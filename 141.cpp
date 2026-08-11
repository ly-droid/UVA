#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <algorithm>
using namespace std;

string encode(const vector<vector<int>>& b) {
    int n = b.size();
    string s;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            s += char('0' + b[i][j]);
        }
    }

    return s;
}

vector<vector<int>> rotate90(const vector<vector<int>>& b) {
    int n = b.size();
    vector<vector<int>> r(n, vector<int>(n));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            r[j][n - 1 - i] = b[i][j];
        }
    }

    return r;
}

string canonical(vector<vector<int>> b) {
    vector<string> forms;

    for (int i = 0; i < 4; i++) {
        forms.push_back(encode(b));
        b = rotate90(b);
    }

    return *min_element(forms.begin(), forms.end());
}

int main() {
    int n;

    while (cin >> n) {
        if (n == 0) break;

        vector<vector<int>> board(n, vector<int>(n, 0));
        set<string> seen;

        bool ended = false;
        int winner = 0;
        int moveNo = 0;

        for (int move = 1; move <= 2 * n; move++) {
            int x, y;
            char op;
            cin >> x >> y >> op;

            if (op == '+') board[x - 1][y - 1] = 1;
            else board[x - 1][y - 1] = 0;

            if (!ended) {
                string state = canonical(board);

                if (seen.count(state)) {
                    int loser = (move % 2 == 1 ? 1 : 2);
                    winner = 3 - loser;
                    moveNo = move;
                    ended = true;
                } else {
                    seen.insert(state);
                }
            }
        }

        if (ended) {
            cout << "Player " << winner << " wins on move " << moveNo << '\n';
        } else {
            cout << "Draw\n";
        }
    }

    return 0;
}
