#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    long long x = 3, y = 2;
    int count = 0;

    while (count < 10) {
        long long nx = 3 * x + 4 * y;
        long long ny = 2 * x + 3 * y;

        x = nx;
        y = ny;

        long long house = y / 2;
        long long last = (x - 1) / 2;

        cout << setw(10) << house << setw(10) << last << '\n';
        count++;
    }

    return 0;
}
