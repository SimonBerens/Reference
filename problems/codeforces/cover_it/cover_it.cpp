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

vi picked;
vvi g;

vi vis;

void dfs(int u, int c) {
    vis[u] = true;
    picked[u] = c;
    for (int v: g[u]) {
        if (!vis[v]) {
            dfs(v, !c);
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    for (int test_no = 0; test_no < t; ++test_no) {
        int n, m;
        cin >> n >> m;
        picked.assign(n + 1, 0);
        vis.assign(n + 1, 0);
        g.assign(n + 1, vi{});
        for (int i = 0; i < m; ++i) {
            int u, v;
            cin >> u >> v;
            g[u].pb(v);
            g[v].pb(u);
        }
        dfs(1, 0);
        int k = accumulate(all(picked), 0);
        int c = k <= n / 2;
        if (k > n / 2) k = n - k;
        cout << k << '\n';
        for (int i = 1; i <= n; ++i) {
            if (picked[i] == c) cout << i << ' ';
        }
        cout << '\n';
    }
}