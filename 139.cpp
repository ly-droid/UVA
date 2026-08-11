#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

struct Code {
    string code;
    string name;
    int price;
};

int main() {
    vector<Code> codes;
    string line;

    while (getline(cin, line)) {
        if (line == "000000") break;

        int sp = line.find(' ');
        int dollar = line.find('$');

        Code c;
        c.code = line.substr(0, sp);
        c.name = line.substr(sp + 1, dollar - sp - 1);
        c.price = stoi(line.substr(dollar + 1));

        codes.push_back(c);
    }

    string number;
    int duration;

    while (cin >> number) {
        if (number == "#") break;

        cin >> duration;

        string locality, subscriber;
        double rate = 0.0;
        double total = 0.0;
        bool ok = false;
        bool unknown = false;

        if (number[0] != '0') {
            locality = "Local";
            subscriber = number;
            ok = true;
        } else {
            for (int i = 0; i < (int)codes.size(); i++) {
                string code = codes[i].code;

                if (number.size() <= code.size()) continue;
                if (number.substr(0, code.size()) != code) continue;

                int subLen = number.size() - code.size();

                if (number.substr(0, 2) == "00") {
                    if (code.substr(0, 2) == "00" && subLen >= 4 && subLen <= 10) {
                        locality = codes[i].name;
                        subscriber = number.substr(code.size());
                        rate = codes[i].price / 100.0;
                        total = rate * duration;
                        ok = true;
                        break;
                    }
                } else {
                    if (code[0] == '0' && code.substr(0, 2) != "00" && subLen >= 4 && subLen <= 7) {
                        locality = codes[i].name;
                        subscriber = number.substr(code.size());
                        rate = codes[i].price / 100.0;
                        total = rate * duration;
                        ok = true;
                        break;
                    }
                }
            }

            if (!ok) {
                locality = "Unknown";
                subscriber = "";
                rate = 0.0;
                total = -1.0;
                unknown = true;
            }
        }

        cout << left << setw(16) << number
             << left << setw(25) << locality
             << right << setw(10) << subscriber
             << setw(5) << duration;

        if (unknown) {
            cout << setw(13) << fixed << setprecision(2) << total << '\n';
        } else {
            cout << setw(6) << fixed << setprecision(2) << rate
                 << setw(7) << fixed << setprecision(2) << total << '\n';
        }
    }

    return 0;
}
