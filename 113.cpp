#include <bits/stdc++.h>
#include <boost/multiprecision/cpp_int.hpp>

using namespace std;
using boost::multiprecision::cpp_int;

int comparePower(long long base, int n, const cpp_int& target) {
    cpp_int result = 1;

    for (int i = 0; i < n; i++) {
        result *= base;

        if (result > target) {
            return 1;   // base^n is too large
        }
    }

    if (result == target) return 0;
    return -1;          // base^n is too small
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    string pStr;

    while (cin >> n >> pStr) {
        cpp_int p = 0;

        for (char c : pStr) {
            p = p * 10 + (c - '0');
        }

        long long low = 1;
        long long high = 1000000000LL;
        long long answer = 1;

        while (low <= high) {
            long long mid = low + (high - low) / 2;

            int cmp = comparePower(mid, n, p);

            if (cmp == 0) {
                answer = mid;
                break;
            } else if (cmp < 0) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }

        cout << answer << '\n';
    }

    return 0;
}
