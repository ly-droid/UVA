#include <iostream>
#include <cmath>
using namespace std;

typedef unsigned long long ull;

ull ipow(ull base, int exp, ull limit) {
    ull result = 1;
    for (int i = 0; i < exp; ++i) {
        if (result > limit / base) return limit + 1; 
        result *= base;
    }
    return result;
}

int main() {
    ull H, W;

    while (cin >> H >> W) {
        if (H == 0 && W == 0) break;

        if (H == 1 && W == 1) {
            cout << 0 << " " << 1 << "\n";
            continue;
        }

        ull N = 0;
        int k = 0;

        if (W == 1) {
            N = 1;
            ull temp = H;
            while (temp > 1) {
                temp /= 2;
                ++k;
            }
        } else {
            for (int candK = 1; candK <= 64; ++candK) {
                double approx = pow((double)W, 1.0 / candK);
                ull candN = (ull)(approx + 0.5);

                if (candN < 1) continue;

                if (ipow(candN, candK, W) == W &&
                    ipow(candN + 1, candK, H) == H) {
                    N = candN;
                    k = candK;
                    break;
                }
            }
        }

        ull nonWorking = 0;
        ull totalHeight = 0;

        if (N == 1) {
            nonWorking = k;
            totalHeight = 2 * H - 1;
        } else {
            ull cnt = 1;
            for (int i = 0; i < k; ++i) {
                nonWorking += cnt;
                cnt *= N;
            }

            ull nPow = 1;
            ull np1Pow = H; 
            for (int i = 0; i <= k; ++i) {
                totalHeight += nPow * np1Pow;
                nPow *= N;
                if (i != k) np1Pow /= (N + 1);
            }
        }

        cout << nonWorking << " " << totalHeight << "\n";
    }

    return 0;
}
