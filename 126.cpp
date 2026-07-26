#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <cctype>
#include <cmath>
using namespace std;

struct Term {
    int coef;
    int xpow;
    int ypow;
};

vector<Term> parsePoly(const string& s) {
    vector<Term> terms;
    int i = 0, n = s.size();

    while (i < n) {
        int sign = 1;

        if (s[i] == '+') {
            sign = 1;
            i++;
        } else if (s[i] == '-') {
            sign = -1;
            i++;
        }

        int coef = 1;
        bool hasCoef = false;

        if (i < n && isdigit(s[i])) {
            coef = 0;
            hasCoef = true;
            while (i < n && isdigit(s[i])) {
                coef = coef * 10 + (s[i] - '0');
                i++;
            }
        }

        int xp = 0, yp = 0;

        while (i < n && s[i] != '+' && s[i] != '-') {
            char var = s[i++];
            int exp = 0;
            bool hasExp = false;

            while (i < n && isdigit(s[i])) {
                exp = exp * 10 + (s[i] - '0');
                hasExp = true;
                i++;
            }

            if (!hasExp) exp = 1;

            if (var == 'x') xp = exp;
            else if (var == 'y') yp = exp;
        }

        terms.push_back({sign * coef, xp, yp});
    }

    return terms;
}

void appendSpaces(string& s, int cnt) {
    for (int i = 0; i < cnt; i++) s += ' ';
}

void appendText(string& upper, string& lower, const string& text) {
    lower += text;
    appendSpaces(upper, text.size());
}

void appendVariable(string& upper, string& lower, char var, int exp) {
    lower += var;
    upper += ' ';

    if (exp > 1) {
        string e = to_string(exp);
        appendSpaces(lower, e.size());
        upper += e;
    }
}

int main() {
    string p1, p2;

    while (getline(cin, p1)) {
        if (!p1.empty() && p1[0] == '#') break;
        getline(cin, p2);

        vector<Term> a = parsePoly(p1);
        vector<Term> b = parsePoly(p2);

        map<pair<int, int>, int> mp;

        for (auto t1 : a) {
            for (auto t2 : b) {
                int c = t1.coef * t2.coef;
                int xp = t1.xpow + t2.xpow;
                int yp = t1.ypow + t2.ypow;
                mp[{xp, yp}] += c;
            }
        }

        vector<Term> res;

        for (auto it : mp) {
            if (it.second != 0) {
                res.push_back({it.second, it.first.first, it.first.second});
            }
        }

        sort(res.begin(), res.end(), [](const Term& a, const Term& b) {
            if (a.xpow != b.xpow) return a.xpow > b.xpow;
            return a.ypow < b.ypow;
        });

        string upper, lower;

        if (res.empty()) {
            upper = " ";
            lower = "0";
        } else {
            for (int i = 0; i < (int)res.size(); i++) {
                int c = res[i].coef;
                int absC = abs(c);
                bool hasVar = res[i].xpow > 0 || res[i].ypow > 0;

                if (i == 0) {
                    if (c < 0) appendText(upper, lower, "-");
                } else {
                    if (c < 0) appendText(upper, lower, " - ");
                    else appendText(upper, lower, " + ");
                }

                if (absC != 1 || !hasVar) {
                    appendText(upper, lower, to_string(absC));
                }

                if (res[i].xpow > 0) {
                    appendVariable(upper, lower, 'x', res[i].xpow);
                }

                if (res[i].ypow > 0) {
                    appendVariable(upper, lower, 'y', res[i].ypow);
                }
            }
        }

        while (upper.size() < lower.size()) upper += ' ';
        while (lower.size() < upper.size()) lower += ' ';

        cout << upper << '\n';
        cout << lower << '\n';
    }

    return 0;
}
