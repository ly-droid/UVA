#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    vector<long long> ugly(1500);
    ugly[0] = 1;

    int i2 = 0, i3 = 0, i5 = 0;

    for (int i = 1; i < 1500; i++) {
        long long nextUgly = min({ugly[i2] * 2, ugly[i3] * 3, ugly[i5] * 5});
        ugly[i] = nextUgly;

        if (nextUgly == ugly[i2] * 2) i2++;
        if (nextUgly == ugly[i3] * 3) i3++;
        if (nextUgly == ugly[i5] * 5) i5++;
    }

    cout << "The 1500'th ugly number is " << ugly[1499] << ".\n";

    return 0;
}
