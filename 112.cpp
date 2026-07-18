#include <bits/stdc++.h>
using namespace std;

string s;
int pos;
int target;
bool ok;

bool parse(int sum, bool &isEmpty) {
    while (pos < (int)s.size() && isspace((unsigned char)s[pos])) pos++;
    pos++;
    while (pos < (int)s.size() && isspace((unsigned char)s[pos])) pos++;

    if (s[pos] == ')') {
        pos++;
        isEmpty = true;
        return false;
    }

    isEmpty = false;

    int sign = 1;
    if (s[pos] == '-') {
        sign = -1;
        pos++;
    }

    int num = 0;
    while (pos < (int)s.size() && isdigit((unsigned char)s[pos])) {
        num = num * 10 + (s[pos] - '0');
        pos++;
    }
    num *= sign;

    bool leftEmpty, rightEmpty;
    bool leftFound = parse(sum + num, leftEmpty);
    bool rightFound = parse(sum + num, rightEmpty);

    while (pos < (int)s.size() && isspace((unsigned char)s[pos])) pos++;
    pos++;

    if (leftEmpty && rightEmpty && sum + num == target) ok = true;

    return leftFound || rightFound || ok;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while (cin >> target) {
        s.clear();
        cin >> ws;

        int balance = 0;
        char c;
        do {
            if (!cin.get(c)) return 0;
        } while (isspace((unsigned char)c));

        s += c;
        if (c == '(') balance++;
        else if (c == ')') balance--;

        while (balance > 0 && cin.get(c)) {
            s += c;
            if (c == '(') balance++;
            else if (c == ')') balance--;
        }

        pos = 0;
        ok = false;
        bool isEmpty;
        parse(0, isEmpty);
        cout << (ok ? "yes" : "no") << '\n';
    }

    return 0;
}
