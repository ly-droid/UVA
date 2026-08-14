#include <iostream>
using namespace std;

int main() {
    int n;

    while (cin >> n && n) {
        int m = 1;

        while (true) {
            int survivor = 0;

            for (int size = 2; size <= n - 1; size++) {
                survivor = (survivor + m) % size;
            }

            if (survivor == 11) {
                cout << m << '\n';
                break;
            }

            m++;
        }
    }

    return 0;
}
