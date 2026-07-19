#include <bits/stdc++.h>
using namespace std;

unordered_map<string, string> parentOf;

unordered_map<string, int> getAncestors(string x) {
    unordered_map<string, int> dist;
    int d = 0;

    dist[x] = 0;

    while (parentOf.count(x)) {
        x = parentOf[x];
        d++;
        dist[x] = d;
    }

    return dist;
}

string makeChildRelation(int edges) {
    if (edges == 1) return "child";
    if (edges == 2) return "grand child";

    string res = "";
    for (int i = 0; i < edges - 2; i++) {
        res += "great ";
    }
    res += "grand child";
    return res;
}

string makeParentRelation(int edges) {
    if (edges == 1) return "parent";
    if (edges == 2) return "grand parent";

    string res = "";
    for (int i = 0; i < edges - 2; i++) {
        res += "great ";
    }
    res += "grand parent";
    return res;
}

string relationship(string p, string q) {
    if (p == q) {
        return "no relation";
    }

    auto ancP = getAncestors(p);
    auto ancQ = getAncestors(q);

    if (ancQ.count(p)) {
        int edges = ancQ[p];
        return makeParentRelation(edges);
    }

    if (ancP.count(q)) {
        int edges = ancP[q];
        return makeChildRelation(edges);
    }

    int bestDist = INT_MAX;
    string lca = "";

    for (auto &item : ancP) {
        string ancestor = item.first;
        int distP = item.second;

        if (ancQ.count(ancestor)) {
            int distQ = ancQ[ancestor];
            int total = distP + distQ;

            if (total < bestDist) {
                bestDist = total;
                lca = ancestor;
            }
        }
    }

    if (lca == "") {
        return "no relation";
    }

    int distP = ancP[lca];
    int distQ = ancQ[lca];

    if (distP == 1 && distQ == 1) {
        return "sibling";
    }

    int cousin = min(distP, distQ) - 1;
    int removed = abs(distP - distQ);

    string res = to_string(cousin) + " cousin";

    if (removed > 0) {
        res += " removed " + to_string(removed);
    }

    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string child, parent;

    while (cin >> child >> parent) {
        if (child == "no.child") {
            break;
        }

        parentOf[child] = parent;
    }

    string p, q;

    while (cin >> p >> q) {
        cout << relationship(p, q) << "\n";
    }

    return 0;
}
