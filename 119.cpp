#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;

int main() {
    int n;
    bool firstGroup = true;

    while (cin >> n) {
        vector<string> names(n);
        map<string, int> net;

        for (int i = 0; i < n; i++) {
            cin >> names[i];
            net[names[i]] = 0;
        }

        for (int i = 0; i < n; i++) {
            string giver;
            int money, cnt;
            cin >> giver >> money >> cnt;

            if (cnt == 0) {
                continue;
            }

            int gift = money / cnt;
            int totalGiven = gift * cnt;

            net[giver] -= totalGiven;

            for (int j = 0; j < cnt; j++) {
                string receiver;
                cin >> receiver;
                net[receiver] += gift;
            }
        }

        if (!firstGroup) {
            cout << '\n';
        }
        firstGroup = false;

        for (int i = 0; i < n; i++) {
            cout << names[i] << " " << net[names[i]] << '\n';
        }
    }

    return 0;
}
