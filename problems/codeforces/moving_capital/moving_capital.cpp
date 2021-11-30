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

vi dist;
vvi g;
vi ress;

int dfs(int u) {
    if (ress[u] != -1) return ress[u];
    int res = dist[u];
    for (int v : g[u]) {
        if (dist[u] < dist[v]) {
            smin(res, dfs(v));
        } else {
            smin(res, dist[v]);
        }
    }
    return ress[u] = res;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    for (int test_no = 0; test_no < t; ++test_no) {
        int n, m;
        cin >> n >> m;
        g.assign(n + 1, vi{});
        for (int i = 0; i < m; ++i) {
            int u, v;
            cin >> u >> v;
            g[u].pb(v);
        }
        dist.assign(n + 1, 0);
        queue<ii> q;
        q.push({1, 0});
        vi vis(n + 1);
        while (!q.empty()) {
            auto[u, d] = q.front();
            q.pop();
            if (vis[u]) continue;
            vis[u] = true;
            dist[u] = d;
            for (int v: g[u]) {
                if (!vis[v]) q.push({v, d + 1});
            }
        }
        ress.assign(n + 1, -1);
        dfs(1);
        for (int i = 1; i <= n; ++i) {
            cout << ress[i] << ' ';
        }
        cout << '\n';
    }
}