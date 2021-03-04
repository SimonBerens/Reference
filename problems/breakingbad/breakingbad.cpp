#include <bits/stdc++.h>

using namespace std;


bool dfs(const string &item, bool p, unordered_map<string, bool> &coloring, const unordered_map<string, vector<string>> & g) {
    coloring[item] = !p;
    for (const string &neighbor : g.at(item)) {
        if (coloring.count(neighbor) == 0) {
            if (!dfs(neighbor, !p, coloring, g)) {
                return false;
            }
        } else if (coloring[neighbor] != p) {
            return false;
        }
    }
    return true;
}

int main() {
    int n;
    cin >> n >> ws;
    unordered_map<string, vector<string>> g;
    for (int i = 0; i < n; ++i) {
        string line;
        getline(cin, line);
        g[line];
    }
    int m;
    cin >> m >> ws;
    for (int i = 0; i < m; ++i) {
        string line;
        getline(cin, line);
        int space = line.find(' ');
        string a = line.substr(0, space), b = line.substr(space + 1);
        g[a].push_back(b);
        g[b].push_back(a);
    }
    unordered_map<string, bool> coloring;
    for (const auto & [item, _] : g) {
        if (coloring.count(item) == 0) {
            if (!dfs(item, true, coloring, g)) {
                cout << "impossible\n";
                exit(0);
            }
        }
    }
    for (const auto &[item, b] : coloring) {
        if (b) {
            cout << item << ' ';
        }
    }
    cout << "\n";
    for (const auto &[item, b] : coloring) {
        if (!b) {
            cout << item << ' ';
        }
    }
    cout << "\n";
}