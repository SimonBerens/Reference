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

int n;

vvi g;
int numcc = 0;
map<ii, int> components;
map<int, int> sizes, colors;

vii dirs{{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

set<ii> vis;

bool in_bounds(int r, int c) {
    return 0 <= r && r < n && 0 <= c && c < n;
}

void dfs(int r, int c, int compid) {
    vis.insert({r, c});
    components[{r, c}] = compid;
    ++sizes[compid];
    colors[compid] = g[r][c];
    for (auto[dr, dc]: dirs) {
        int nr = r + dr, nc = c + dc;
        if (in_bounds(nr ,nc) && g[nr][nc] == g[r][c] && vis.count({nr, nc}) == 0) {
            dfs(nr, nc, compid);
        }
    }
}

vector<set<int>> cg;

set<array<int, 3>> vis2;

int dfs2(int u, int c1, int c2) {
    vis2.insert({u, c1, c2});
    int res = sizes[u];
//    cout << u << ' ' << c1 << ' ' << c2 << ' ' << sizes[u] << '\n';
    for (int v: cg[u]) {
        if ((colors[v] == c1 || colors[v] == c2) && (vis2.count({v, c1, c2}) == 0)) {
            res += dfs2(v, c1, c2);
        }
    }
    return res;
}


int main() {
    freopen("multimoo.in", "r", stdin);
    freopen("multimoo.out", "w", stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    g.assign(n, vi(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> g[i][j];
        }
    }
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < n; ++c) {
            if (vis.count({r, c}) == 0) dfs(r, c, numcc++);
        }
    }
    int res1 = 0;
    for (auto [comp, sz] : sizes) {
        smax(res1, sz);
    }
    cout << res1 << '\n';
    cg.assign(numcc++, set<int>{} );
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < n; ++c) {
            for (auto[dr, dc]: dirs) {
                int nr = r + dr, nc = c + dc;
                if (in_bounds(nr ,nc)) {
                    int c1 = components[{nr, nc}], c2 = components[{r, c}];
                    if (c1 != c2) {
                        cg[c1].insert(c2);
                    }
                }
            }
        }
    }
    int res2 = 0;
    for (int u = 0; u < cg.size(); ++u) {
        for (int v : cg[u]) {
            int c1 = min(colors[u], colors[v]);
            int c2 = max(colors[u], colors[v]);
            if (vis2.count({u, c1, c2}) == 0) smax(res2, dfs2(u, c1, c2));
        }
    }
    cout << res2 << '\n';
}