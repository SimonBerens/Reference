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

vvi t, g;
vll par, tsz, dd, ud;

void root(int u, int p) {
    t[p].pb(u);
    par[u] = p;
    for (int v: g[u]) {
        if (v != p) root(v, u);
    }
}

ll ctsz(int u) {
    ll res = 1;
    for (int v: t[u]) {
        res += ctsz(v);
    }
    return tsz[u] = res;
}

ll cdd(int u) {
    ll res = 0;
    for (int v: t[u]) {
        res += tsz[v] + cdd(v);
    }
    return dd[u] = res;
}

void cud(int u) {
    ud[u] = dd[par[u]] - (dd[u] + tsz[u]) + ud[par[u]] + t.size() - tsz[u];
    for (int v: t[u]) {
        cud(v);
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    t.assign(n, vi{});
    g.assign(n, vi{});
    par.assign(n, 0);
    tsz.assign(n, 0);
    dd.assign(n, 0);
    ud.assign(n, 0);
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        g[a].pb(b);
        g[b].pb(a);
    }
    for (int u: g[0]) {
        root(u, 0);
    }
    ctsz(0);
    cdd(0);
    for (int u: g[0]) {
        cud(u);
    }
    for (int i = 0; i < n; ++i) {
        cout << dd[i] + ud[i] << ' ';
    }
}