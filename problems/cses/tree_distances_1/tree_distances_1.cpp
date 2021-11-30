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

vvi g, t;
vi tp;

void root(int u, int p) {
    t[p].pb(u);
    tp[u] = p;
    for (int v: g[u]) {
        if (v != p)
            root(v, u);
    }
}

vi dd;
vector<map<int, int>> vvals;

int process_down(int u) {
    vi ds, ch;
    for (int v : t[u]) {
        ds.pb(1 + process_down(v));
        ch.pb(v);
    }
    vi pd{0};
    for (int i = 0; i < ds.size(); ++i) {
        pd.pb(max(pd.back(), ds[i]));
    }
    vi sd{0};
    for (int i = ds.size() - 1; i >= 0; --i) {
        sd.pb(max(sd.back(), ds[i]));
    }
    reverse(all(sd));
    for (int i = 0; i < ds.size(); ++i) {
        vvals[u][ch[i]] = max(pd[i], sd[i + 1]);
    }
    return dd[u] = pd.back();
}

vi du;

void process_up(int u) {
    du[u] = max(du[tp[u]], vvals[tp[u]][u]) + 1;
    for (int v : t[u]) {
        process_up(v);
    }
}


int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    g.assign(n, vi{});
    t.assign(n, vi{});
    tp.assign(n, 0);
    dd.assign(n, 0);
    du.assign(n, 0);
    vvals.assign(n, map<int, int>{});
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        g[--a].pb(--b);
        g[b].pb(a);
    }
    for (int u : g[0]) root(u, 0);
    process_down(0);
    for (int u: g[0]) process_up(u);
    for (int i = 0; i < n; ++i) {
        cout << max(dd[i], du[i]) << ' ';
    }
    cout << '\n';

}