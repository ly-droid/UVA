#include <iostream>
#include <string>
#include <queue>
using namespace std;

struct Node {
    int value;
    bool hasValue;
    Node* left;
    Node* right;

    Node() {
        value = 0;
        hasValue = false;
        left = nullptr;
        right = nullptr;
    }
};

void clear(Node* root) {
    if (!root) return;
    clear(root->left);
    clear(root->right);
    delete root;
}

int main() {
    string token;
    Node* root = new Node();
    bool bad = false;

    while (cin >> token) {
        if (token == "()") {
            vector<int> ans;
            queue<Node*> q;
            q.push(root);

            while (!q.empty()) {
                Node* cur = q.front();
                q.pop();

                if (!cur->hasValue) {
                    bad = true;
                    break;
                }

                ans.push_back(cur->value);

                if (cur->left) q.push(cur->left);
                if (cur->right) q.push(cur->right);
            }

            if (bad) {
                cout << "not complete\n";
            } else {
                for (int i = 0; i < (int)ans.size(); i++) {
                    if (i) cout << " ";
                    cout << ans[i];
                }
                cout << "\n";
            }

            clear(root);
            root = new Node();
            bad = false;
            continue;
        }

        int comma = token.find(',');
        int value = stoi(token.substr(1, comma - 1));
        string path = token.substr(comma + 1, token.size() - comma - 2);

        Node* cur = root;

        for (char c : path) {
            if (c == 'L') {
                if (!cur->left) cur->left = new Node();
                cur = cur->left;
            } else {
                if (!cur->right) cur->right = new Node();
                cur = cur->right;
            }
        }

        if (cur->hasValue) {
            bad = true;
        } else {
            cur->value = value;
            cur->hasValue = true;
        }
    }

    clear(root);
    return 0;
}
