#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;

struct Word {
    string s;
    int cnt[26];
};

vector<Word> dict;
vector<Word> cand;
vector<string> phraseWords;
vector<string> chosen;
string phrase;

bool leqCnt(int a[], int b[]) {
    for (int i = 0; i < 26; i++) {
        if (a[i] > b[i]) return false;
    }
    return true;
}

bool emptyCnt(int a[]) {
    for (int i = 0; i < 26; i++) {
        if (a[i] != 0) return false;
    }
    return true;
}

bool sameAsOriginal() {
    vector<string> a = chosen;
    vector<string> b = phraseWords;
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    return a == b;
}

void dfs(int start, int rem[]) {
    if (emptyCnt(rem)) {
        if (!sameAsOriginal()) {
            cout << phrase << " =";
            for (string s : chosen) {
                cout << " " << s;
            }
            cout << '\n';
        }
        return;
    }

    for (int i = start; i < (int)cand.size(); i++) {
        if (leqCnt(cand[i].cnt, rem)) {
            for (int j = 0; j < 26; j++) {
                rem[j] -= cand[i].cnt[j];
            }

            chosen.push_back(cand[i].s);
            dfs(i + 1, rem);
            chosen.pop_back();

            for (int j = 0; j < 26; j++) {
                rem[j] += cand[i].cnt[j];
            }
        }
    }
}

int main() {
    string s;

    while (getline(cin, s)) {
        if (s == "#") break;

        Word w;
        w.s = s;
        fill(w.cnt, w.cnt + 26, 0);

        for (char c : s) {
            w.cnt[c - 'A']++;
        }

        dict.push_back(w);
    }

    while (getline(cin, phrase)) {
        if (phrase == "#") break;

        int target[26] = {0};
        phraseWords.clear();
        cand.clear();
        chosen.clear();

        stringstream ss(phrase);
        string word;

        while (ss >> word) {
            phraseWords.push_back(word);
            for (char c : word) {
                target[c - 'A']++;
            }
        }

        for (Word w : dict) {
            if (leqCnt(w.cnt, target)) {
                cand.push_back(w);
            }
        }

        dfs(0, target);
    }

    return 0;
}
