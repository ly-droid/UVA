#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

long long C[31][31];

long long countPerm(int cnt[26]) {
    long long res = 1;
    int used = 0;

    for (int i = 0; i < 26; i++) {
        int c = cnt[i];
        if (c > 0) {
            res *= C[used + c][c];
            used += c;
        }
    }

    return res;
}

int main() {
    for (int i = 0; i <= 30; i++) {
        C[i][0] = C[i][i] = 1;
        for (int j = 1; j < i; j++) {
            C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
        }
    }

    string s;

    while (cin >> s) {
        if (s == "#") break;

        int cnt[26] = {0};

        for (char c : s) {
            cnt[c - 'a']++;
        }

        long long rank = 1;

        for (int i = 0; i < (int)s.size(); i++) {
            int cur = s[i] - 'a';

            for (int c = 0; c < cur; c++) {
                if (cnt[c] > 0) {
                    cnt[c]--;
                    rank += countPerm(cnt);
                    cnt[c]++;
                }
            }

            cnt[cur]--;
        }

        cout << setw(10) << rank << '\n';
    }

    return 0;
}
