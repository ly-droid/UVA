#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

int skewCount(double w, double h) {
    const double H = sqrt(3.0) / 2.0;
    const double EPS = 1e-9;

    if (w + EPS < 1.0 || h + EPS < 1.0) return 0;

    int rows = 1 + (int)floor((h - 1.0) / H + EPS);
    int full = (int)floor(w + EPS);
    int shifted = (int)floor(w - 0.5 + EPS);

    if (shifted < 0) shifted = 0;

    int oddRows = (rows + 1) / 2;
    int evenRows = rows / 2;

    return oddRows * full + evenRows * shifted;
}

int main() {
    double a, b;

    while (cin >> a >> b) {
        int grid = (int)floor(a) * (int)floor(b);

        int skew = max(skewCount(a, b), skewCount(b, a));

        if (grid >= skew) {
            cout << grid << " grid\n";
        } else {
            cout << skew << " skew\n";
        }
    }

    return 0;
}
