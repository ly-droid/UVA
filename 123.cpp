#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <sstream>
#include <algorithm>
using namespace std;

struct Entry {
    string keyword;
    int titleIndex;
    int wordIndex;
};

string lowerStr(string s) {
    for (char &c : s) c = tolower(c);
    return s;
}

string upperStr(string s) {
    for (char &c : s) c = toupper(c);
    return s;
}

int main() {
    set<string> ignore;
    string line;

    while (getline(cin, line)) {
        if (line == "::") break;
        ignore.insert(lowerStr(line));
    }

    vector<vector<string>> titles;
    vector<Entry> entries;

    int titleIndex = 0;

    while (getline(cin, line)) {
        stringstream ss(line);
        string word;
        vector<string> words;

        while (ss >> word) {
            words.push_back(lowerStr(word));
        }

        titles.push_back(words);

        for (int i = 0; i < (int)words.size(); i++) {
            if (!ignore.count(words[i])) {
                entries.push_back({words[i], titleIndex, i});
            }
        }

        titleIndex++;
    }

    stable_sort(entries.begin(), entries.end(), [](const Entry &a, const Entry &b) {
        return a.keyword < b.keyword;
    });

    for (const Entry &e : entries) {
        const vector<string> &words = titles[e.titleIndex];

        for (int i = 0; i < (int)words.size(); i++) {
            if (i) cout << " ";

            if (i == e.wordIndex) {
                cout << upperStr(words[i]);
            } else {
                cout << words[i];
            }
        }

        cout << '\n';
    }

    return 0;
}
