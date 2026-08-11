#include <iostream>
#include <vector>
using namespace std;

int idAffine(int x, int y, int q) {
    return x * q + y + 1;
}

int idSlope(int m, int q) {
    return q * q + m + 1;
}

int idVertical(int q) {
    return q * q + q + 1;
}

int main() {
    int k;
    bool first = true;

    while (cin >> k) {
        if (!first) cout << '\n';
        first = false;

        if (k == 1) {
            cout << 1 << '\n';
            continue;
        }

        if (k == 2) {
            cout << "1 2\n";
            cout << "1 3\n";
            cout << "2 3\n";
            continue;
        }

        int q = k - 1;

        for (int m = 0; m < q; m++) {
            for (int b = 0; b < q; b++) {
                vector<int> line;

                for (int x = 0; x < q; x++) {
                    int y = (m * x + b) % q;
                    line.push_back(idAffine(x, y, q));
                }

                line.push_back(idSlope(m, q));

                for (int i = 0; i < (int)line.size(); i++) {
                    if (i) cout << " ";
                    cout << line[i];
                }
                cout << '\n';
            }
        }

        for (int x = 0; x < q; x++) {
            vector<int> line;

            for (int y = 0; y < q; y++) {
                line.push_back(idAffine(x, y, q));
            }

            line.push_back(idVertical(q));

            for (int i = 0; i < (int)line.size(); i++) {
                if (i) cout << " ";
                cout << line[i];
            }
            cout << '\n';
        }

        for (int m = 0; m < q; m++) {
            if (m) cout << " ";
            cout << idSlope(m, q);
        }

        cout << " " << idVertical(q) << '\n';
    }

    return 0;
}
