#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<vector<int>> a(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> a[i][j];
        }
    }

    int ans = INT_MIN;

    for (int top = 0; top < n; ++top) {
        vector<int> col(n, 0);
        for (int bottom = top; bottom < n; ++bottom) {
            for (int j = 0; j < n; ++j) {
                col[j] += a[bottom][j];
            }

            int cur = col[0], best = col[0];
            for (int j = 1; j < n; ++j) {
                cur = max(col[j], cur + col[j]);
                best = max(best, cur);
            }
            ans = max(ans, best);
        }
    }

    cout << ans << '\n';
    return 0;
}




发件人: LU, Yan <1155233173@link.cuhk.edu.hk>
日期: 星期二, 民国115年4月21日 下午5:35
收件人: Prof. Chiou-Shann Fuh 傅楸善 <fuh@csie.ntu.edu.tw>
主题: UVA 108

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<vector<int>> a(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> a[i][j];
        }
    }

    int ans = INT_MIN;

    for (int top = 0; top < n; ++top) {
        vector<int> col(n, 0);
        for (int bottom = top; bottom < n; ++bottom) {
            for (int j = 0; j < n; ++j) {
                col[j] += a[bottom][j];
            }

            int cur = col[0], best = col[0];
            for (int j = 1; j < n; ++j) {
                cur = max(col[j], cur + col[j]);
                best = max(best, cur);
            }
            ans = max(ans, best);
        }
    }

    cout << ans << '\n';
    return 0;
}
