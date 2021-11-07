#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template <typename K> using hset = gp_hash_table<K, null_type>;
template <typename K, typename V> using hmap = gp_hash_table<K, V>;


using namespace std;

#define all(x) (x).begin(), (x).end()
#define pb push_back
#define eb emplace_back
#define smax(x, y) (x = max(x, y))
#define smin(x, y) (x = min(x, y))

using ll = long long;
using ld = long double;

template <typename T>
using vv = vector<vector<T>>;

using vi = vector<int>;
using ii = array<int, 2>;
using vii = vector<ii>;
using vvi = vv<int>;

using vll = vector<ll>;
using l2 = array<ll, 2>;
using vl2 = vector<l2>;
using vvll = vv<ll>;

template <typename T>
using minq = priority_queue<T, vector<T>, greater<T>>;
template <typename T>
using maxq = priority_queue<T>;

const ll M = 1000000007;

ii furthest_node(vector<set<int>> &g, int u, int p) {
    ii res{0, u};
    for (int v : g[u]) {
        if (v != p) {
            auto [dist, node] = furthest_node(g, v, u);
            int new_dist = dist + 1;
            if (new_dist > res[0]) {
                res = {new_dist, node};
            }
        }
    }
    return res;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    for (int test_no = 0; test_no < t; ++test_no) {
        vector<vector<set<int>>> gs(2);
        vi c(2), d(2), dw(2);
        for (int i = 0; i < 2; ++i) {
            int n;
            cin >> n;
            vector<set<int>> &g = gs[i];
            g.assign(n + 1, set<int>{});
            for (int j = 0; j < n - 1; ++j) {
                int a, b;
                cin >> a >> b;
                g[a].insert(b);
                g[b].insert(a);
            }
            queue<int> q;
            for (int j = 1; j <= n; ++j) {
                if (g[j].size() == 1) q.push(j);
            }
            vector<set<int>> gc = g;
            int u;
            while (!q.empty()) {
                u = q.front(); q.pop();
                for (int v : g[u]) {
                    g[v].erase(u);
                    if (g[v].size() == 1) q.push(v);
                }
                g[u].clear();
            }
            c[i] = u;
            auto [dist, fnodec] = furthest_node(gc, u, 0);
            d[i] = dist;
            dw[i] = furthest_node(gc, fnodec, 0)[0];
        }
        cout << max({dw[0], dw[1], d[0] + d[1] + 1}) << '\n';
        cout << c[0] << ' ' << c[1] << '\n';
    }
}