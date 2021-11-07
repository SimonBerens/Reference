#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>

using namespace __gnu_pbds;
template<typename K> using hset = gp_hash_table<K, null_type>;
template<typename K, typename V> using hmap = gp_hash_table<K, V>;


using namespace std;

#define all(x) (x).begin(), (x).end()
#define pb push_back
#define eb emplace_back
#define smax(x, y) (x = max(x, y))
#define smin(x, y) (x = min(x, y))

using ll = long long;
using ld = long double;

template<typename T>
using vv = vector<vector<T>>;

using vi = vector<int>;
using ii = array<int, 2>;
using vii = vector<ii>;
using vvi = vv<int>;

using vll = vector<ll>;
using l2 = array<ll, 2>;
using vl2 = vector<l2>;
using vvll = vv<ll>;

template<typename T>
using minq = priority_queue<T, vector<T>, greater<T>>;
template<typename T>
using maxq = priority_queue<T>;

const ll M = 1000000007;


int n, m, t, d;

int school = 1, home;
vv<l2> g, grep;
vi isrep;

vl2 sps(vv<l2> &gr, int start, bool final) {
//    cout << '\n';
    vi vis(n + 1);
    minq<l2> q;
    q.push({0, start});
    vl2 out;
    while (!q.empty()) {
        auto [dis, u] = q.top(); q.pop();
        if (!final && dis > d) break;
        if (vis[u]) continue;
//        cout << u << ' ' << dis << '\n';
        vis[u] = true;
        out.pb({u, dis});
        if (!final && u != start && isrep[u]) continue;
        for (auto [v, k] : gr[u]) {
            if (!vis[v]) q.push({dis + k, v});
        }
    }
    return out;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m >> t >> d;
    home = n;
    g.assign(n + 1, vl2{});
    isrep.assign(n + 1, false);
    isrep[home] = isrep[school] = true;
    grep.assign(n + 1, vl2{});
    for (int i = 0; i < t; ++i) {
        int j;
        cin >> j;
        isrep[j] = true;
    }
    for (int i = 0; i < m; ++i) {
        int x, y, k;
        cin >> x >> y >> k;
        g[x].pb({y, k});
        g[y].pb({x, k});
    }
    for (int i = 0; i <= n; ++i) {
        if (isrep[i]) {
            for (auto [u, dis] : sps(g, i, false)) {
                if (isrep[u])
                    grep[i].pb({u, dis});
            }
        }
    }
    for (auto[u, dis]: sps(grep, school, true)) {
        if (u == home) {
            cout << dis << '\n';
            exit(0);
        }
    }
    cout << "stuck\n";
}