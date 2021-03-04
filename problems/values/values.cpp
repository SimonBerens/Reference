#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<ll> vll;
typedef vector<vll> vvll;

ll dfs(int u, const vvll & g, vll &seen, const vll& extra) {
    seen[u] = 1;
    ll sum = extra[u];
    for (auto neighbor : g[u])
        if (seen[neighbor] == 0)
            sum += dfs(neighbor, g, seen, extra);
    return sum;
}


int main() {
    int n, m;
    cin >> n >> m;
    vll ais(n);
    vll bis(n);
    for (int i = 0; i < n; ++i) {
        cin >> ais[i];
    }
    for (int i = 0; i < n; ++i) {
        cin >> bis[i];
    }
    vvll g(n);
    for (int i = 0; i < m; ++i) {
        int c, d;
        cin >> c >> d;
        g[c - 1].push_back(d - 1);
        g[d - 1].push_back(c - 1);
    }
    vll seen1(n), seen2(n);
    for (int i = 0; i < n; ++i) {
        if (seen1[i] == 0) {
            if (dfs(i, g, seen1, ais) != dfs(i, g, seen2, bis)) {
                cout << "No\n";
                exit(0);
            }
        }
    }
    cout << "Yes\n";
}