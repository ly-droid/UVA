#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
using namespace std;

int value(char c) {
    if (c >= '2' && c <= '9') return c - '0';
    if (c == 'T') return 10;
    if (c == 'J') return 11;
    if (c == 'Q') return 12;
    if (c == 'K') return 13;
    return 14;
}

int rankHand(vector<string> hand) {
    vector<int> v;
    map<int, int> cnt;
    bool flush = true;

    for (int i = 0; i < 5; i++) {
        int x = value(hand[i][0]);
        v.push_back(x);
        cnt[x]++;
        if (hand[i][1] != hand[0][1]) flush = false;
    }

    sort(v.begin(), v.end());

    bool straight = false;

    if (v[0] + 1 == v[1] &&
        v[1] + 1 == v[2] &&
        v[2] + 1 == v[3] &&
        v[3] + 1 == v[4]) {
        straight = true;
    }

    if (v[0] == 2 && v[1] == 3 && v[2] == 4 && v[3] == 5 && v[4] == 14) {
        straight = true;
    }

    vector<int> counts;
    for (auto p : cnt) {
        counts.push_back(p.second);
    }

    sort(counts.rbegin(), counts.rend());

    if (straight && flush) return 8;
    if (counts[0] == 4) return 7;
    if (counts[0] == 3 && counts[1] == 2) return 6;
    if (flush) return 5;
    if (straight) return 4;
    if (counts[0] == 3) return 3;
    if (counts[0] == 2 && counts[1] == 2) return 2;
    if (counts[0] == 2) return 1;
    return 0;
}

int main() {
    vector<string> name = {
        "highest-card",
        "one-pair",
        "two-pairs",
        "three-of-a-kind",
        "straight",
        "flush",
        "full-house",
        "four-of-a-kind",
        "straight-flush"
    };

    vector<string> hand(5), deck(5);

    while (cin >> hand[0] >> hand[1] >> hand[2] >> hand[3] >> hand[4]
               >> deck[0] >> deck[1] >> deck[2] >> deck[3] >> deck[4]) {
        int best = 0;

        for (int mask = 0; mask < 32; mask++) {
            vector<string> cur;
            int need = 0;

            for (int i = 0; i < 5; i++) {
                if (mask & (1 << i)) {
                    need++;
                } else {
                    cur.push_back(hand[i]);
                }
            }

            for (int i = 0; i < need; i++) {
                cur.push_back(deck[i]);
            }

            best = max(best, rankHand(cur));
        }

        cout << "Hand:";
        for (int i = 0; i < 5; i++) {
            cout << " " << hand[i];
        }

        cout << " Deck:";
        for (int i = 0; i < 5; i++) {
            cout << " " << deck[i];
        }

        cout << " Best hand: " << name[best] << '\n';
    }

    return 0;
}
