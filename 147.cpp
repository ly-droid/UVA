#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

int main() {
    int coin[] = {5, 10, 20, 50, 100, 200, 500, 1000, 2000, 5000, 10000};
    long long dp[30001] = {0};

    dp[0] = 1;

    for (int i = 0; i < 11; i++) {
        for (int j = coin[i]; j <= 30000; j++) {
            dp[j] += dp[j - coin[i]];
        }
    }

    double x;

    while (cin >> x) {
        if (fabs(x) < 1e-9) break;

        int amount = (int)(x * 100 + 0.5);

        cout << fixed << setprecision(2)
             << setw(6) << x
             << setw(17) << dp[amount]
             << '\n';
    }

    return 0;
}
