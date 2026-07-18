#include <bits/stdc++.h>
using namespace std;

vector<char> vars;
vector<string> out;

void emit(const string& s, int depth) {
    out.push_back(string(depth * 2, ' ') + s);
}

void gen(const vector<char>& sortedVars, int nextIdx, int depth) {
    if (nextIdx == (int)vars.size()) {
        string line = "writeln(";
        for (int i = 0; i < (int)sortedVars.size(); ++i) {
            if (i) line += ",";
            line += sortedVars[i];
        }
        line += ")";
        emit(line, depth);
        return;
    }

    char x = vars[nextIdx];

    function<void(int, int)> insertRec = [&](int pos, int d) {
        if (pos == 0) {
            vector<char> ns = sortedVars;
            ns.insert(ns.begin(), x);
            gen(ns, nextIdx + 1, d);
            return;
        }
        emit(string("if ") + sortedVars[pos - 1] + " < " + x + " then", d);
        if (pos == (int)sortedVars.size()) {
            vector<char> ns = sortedVars;
            ns.push_back(x);
            gen(ns, nextIdx + 1, d + 1);
            emit("else", d);
            insertRec(pos - 1, d + 1);
        } else {
            vector<char> ns = sortedVars;
            ns.insert(ns.begin() + pos, x);
            gen(ns, nextIdx + 1, d + 1);
            emit("else", d);
            insertRec(pos - 1, d + 1);
        }
    };

    insertRec((int)sortedVars.size(), depth);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;

        vars.clear();
        for (int i = 0; i < n; ++i) vars.push_back('a' + i);

        out.clear();
        out.push_back("program sort(input,output);");
        out.push_back("var");
        string decl;
        for (int i = 0; i < n; ++i) {
            if (i) decl += ",";
            decl += vars[i];
        }
        decl += " : integer;";
        out.push_back(decl);
        out.push_back("begin");

        string read = "readln(";
        for (int i = 0; i < n; ++i) {
            if (i) read += ",";
            read += vars[i];
        }
        read += ");";
        out.push_back(read);

        if (n == 1) {
            out.push_back("writeln(a)");
        } else {
            emit(string("if ") + vars[0] + " < " + vars[1] + " then", 0);
            gen({vars[0], vars[1]}, 2, 1);
            emit("else", 0);
            gen({vars[1], vars[0]}, 2, 1);
        }

        out.push_back("end.");

        for (string& s : out) cout << s << '\n';
        if (T) cout << '\n';
    }

    return 0;
}
