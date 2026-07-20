#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;

int main() {
    string line;

    while (getline(cin, line)) {
        cout << line << '\n';

        stringstream ss(line);
        vector<int> a;
        int x;

        while (ss >> x) {
            a.push_back(x);
        }

        int n = a.size();
        vector<int> flips;

        for (int size = n; size >= 2; size--) {
            int maxPos = 0;

            for (int i = 1; i < size; i++) {
                if (a[i] > a[maxPos]) {
                    maxPos = i;
                }
            }

            if (maxPos == size - 1) {
                continue;
            }

            if (maxPos != 0) {
                reverse(a.begin(), a.begin() + maxPos + 1);
                flips.push_back(n - maxPos);
            }

            reverse(a.begin(), a.begin() + size);
            flips.push_back(n - size + 1);
        }

        for (int f : flips) {
            cout << f << " ";
        }

        cout << "0\n";
    }

    return 0;
}
