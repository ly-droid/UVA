#include <iostream>
#include <string>
using namespace std;

int n, L;
int cnt;
string ans;

bool isHard(const string& s) {
    int len = s.size();

    for (int k = 1; k * 2 <= len; k++) {
        bool same = true;

        for (int i = 0; i < k; i++) {
            if (s[len - 1 - i] != s[len - 1 - k - i]) {
                same = false;
                break;
            }
        }

        if (same) return false;
    }

    return true;
}

bool dfs(string s) {
    for (int i = 0; i < L; i++) {
        string t = s + char('A' + i);

        if (isHard(t)) {
            cnt++;

            if (cnt == n) {
                ans = t;
                return true;
            }

            if (dfs(t)) return true;
        }
    }

    return false;
}

int main() {
    while (cin >> n >> L) {
        if (n == 0 && L == 0) break;

        cnt = 0;
        ans = "";

        dfs("");

        for (int i = 0; i < (int)ans.size(); i++) {
            if (i > 0) {
                if (i % 64 == 0) cout << '\n';
                else if (i % 4 == 0) cout << ' ';
            }

            cout << ans[i];
        }

        cout << '\n' << ans.size() << '\n';
    }

    return 0;
}
