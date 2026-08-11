#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <set>
#include <cctype>
using namespace std;

enum Type {
    T_A, T_MOD, T_BA, T_DA, T_LA, T_NAM, T_PREDA, T_OTHER
};

vector<string> w;
vector<Type> tp;
int n;

bool isVowel(char c) {
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
}

bool isPreda(const string& s) {
    if (s.size() != 5) return false;

    bool p1 = !isVowel(s[0]) && !isVowel(s[1]) && isVowel(s[2]) && !isVowel(s[3]) && isVowel(s[4]);
    bool p2 = !isVowel(s[0]) && isVowel(s[1]) && !isVowel(s[2]) && !isVowel(s[3]) && isVowel(s[4]);

    return p1 || p2;
}

Type getType(const string& s) {
    if (s == "a" || s == "e" || s == "i" || s == "o" || s == "u") return T_A;

    if (s == "ga" || s == "ge" || s == "gi" || s == "go" || s == "gu") return T_MOD;
    if (s == "ba" || s == "be" || s == "bi" || s == "bo" || s == "bu") return T_BA;
    if (s == "da" || s == "de" || s == "di" || s == "do" || s == "du") return T_DA;
    if (s == "la" || s == "le" || s == "li" || s == "lo" || s == "lu") return T_LA;

    if (isPreda(s)) return T_PREDA;

    if (!s.empty() && !isVowel(s.back())) return T_NAM;

    return T_OTHER;
}

vector<int> predstring(int pos) {
    vector<int> res;

    while (pos < n && tp[pos] == T_PREDA) {
        pos++;
        res.push_back(pos);
    }

    return res;
}

vector<int> predname(int pos) {
    vector<int> res;

    if (pos < n && tp[pos] == T_NAM) {
        res.push_back(pos + 1);
    }

    if (pos < n && tp[pos] == T_LA) {
        vector<int> v = predstring(pos + 1);
        for (int x : v) res.push_back(x);
    }

    return res;
}

vector<int> verbpred(int pos) {
    vector<int> res;

    if (pos < n && tp[pos] == T_MOD) {
        vector<int> v = predstring(pos + 1);
        for (int x : v) res.push_back(x);
    }

    return res;
}

vector<int> preds(int pos) {
    set<int> res;
    vector<int> starts = predstring(pos);

    for (int x : starts) {
        res.insert(x);

        vector<int> q;
        q.push_back(x);

        while (!q.empty()) {
            int cur = q.back();
            q.pop_back();

            if (cur < n && tp[cur] == T_A) {
                vector<int> nxt = predstring(cur + 1);

                for (int y : nxt) {
                    if (!res.count(y)) {
                        res.insert(y);
                        q.push_back(y);
                    }
                }
            }
        }
    }

    return vector<int>(res.begin(), res.end());
}

bool statement() {
    vector<int> a = predname(0);

    for (int x : a) {
        vector<int> b = verbpred(x);

        for (int y : b) {
            if (y == n) return true;

            vector<int> c = predname(y);

            for (int z : c) {
                if (z == n) return true;
            }
        }
    }

    return false;
}

bool predclaim() {
    if (n > 0 && tp[0] == T_DA) {
        vector<int> v = preds(1);

        for (int x : v) {
            if (x == n) return true;
        }
    }

    vector<int> a = predname(0);

    for (int x : a) {
        if (x < n && tp[x] == T_BA) {
            vector<int> b = preds(x + 1);

            for (int y : b) {
                if (y == n) return true;
            }
        }
    }

    return false;
}

bool goodSentence() {
    return statement() || predclaim();
}

int main() {
    string line, all = "";

    while (getline(cin, line)) {
        if (line == "#") break;

        if (!all.empty()) all += " ";
        all += line;

        if (!line.empty() && line.find('.') != string::npos) {
            for (char& c : all) {
                if (c == '.') c = ' ';
            }

            stringstream ss(all);
            string s;

            w.clear();
            tp.clear();

            while (ss >> s) {
                w.push_back(s);
                tp.push_back(getType(s));
            }

            n = w.size();

            if (goodSentence()) cout << "Good\n";
            else cout << "Bad!\n";

            all = "";
        }
    }

    return 0;
}
