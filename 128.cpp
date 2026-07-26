#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

int main() {
    const int G = 34943;
    string s;

    while (getline(cin, s)) {
        if (!s.empty() && s[0] == '#') break;

        int rem = 0;

        for (char c : s) {
            rem = (rem * 256 + (unsigned char)c) % G;
        }

        rem = (rem * 256) % G;
        rem = (rem * 256) % G;

        int crc = (G - rem) % G;

        cout << uppercase << hex << setw(2) << setfill('0') << (crc >> 8);
        cout << " ";
        cout << uppercase << hex << setw(2) << setfill('0') << (crc & 255);
        cout << dec << '\n';
    }

    return 0;
}
