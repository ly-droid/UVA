#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

int main() {
    double rate[5][3] = {
        {0.10, 0.06, 0.02},
        {0.25, 0.15, 0.05},
        {0.53, 0.33, 0.13},
        {0.87, 0.47, 0.17},
        {1.44, 0.80, 0.30}
    };

    char step;

    while (cin >> step) {
        if (step == '#') break;

        string number;
        int sh, sm, eh, em;
        cin >> number >> sh >> sm >> eh >> em;

        int start = sh * 60 + sm;
        int end = eh * 60 + em;

        if (end <= start) end += 24 * 60;

        int cnt[3] = {0, 0, 0};

        for (int t = start; t < end; t++) {
            int cur = t % (24 * 60);

            if (cur >= 8 * 60 && cur < 18 * 60) {
                cnt[0]++;
            } else if (cur >= 18 * 60 && cur < 22 * 60) {
                cnt[1]++;
            } else {
                cnt[2]++;
            }
        }

        int idx = step - 'A';
        double cost = cnt[0] * rate[idx][0] +
                      cnt[1] * rate[idx][1] +
                      cnt[2] * rate[idx][2];

        cout << setw(10) << number
             << setw(6) << cnt[0]
             << setw(6) << cnt[1]
             << setw(6) << cnt[2]
             << setw(3) << step
             << setw(8) << fixed << setprecision(2) << cost
             << '\n';
    }

    return 0;
}
