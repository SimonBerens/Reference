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

vvi t;
vi tsz, tmarb, m;

int ctsz(int u) {
    int res = 1;
    for (int v : t[u]) {
        res += ctsz(v);
    }
    return tsz[u] = res;
}

int ctmarb(int u) {
    int res = m[u];
    for (int v: t[u]) {
        res += ctmarb(v);
    }
    return tmarb[u] = res;
}

int solve(int u) {
    int res = 0;
    for (int v : t[u]) {
        res += abs(tsz[v] - tmarb[v]) + solve(v);
    }
    return res;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    while (true) {
        int n;
        cin >> n;
        if (n == 0) break;
        t.assign(n, vi{});
        tsz.assign(n, 0);
        tmarb.assign(n, 0);
        m.assign(n, 0);
        set<int> roots;
        for (int i = 0; i < n; ++i) {
            roots.insert(i);
        }
        for (int i = 0; i < n; ++i) {
            int v, d;
            cin >> v >> m[i] >> d;
            for (int j = 0; j < d; ++j) {
                int u;
                cin >> u;
                --u;
                t[i].pb(u);
                roots.erase(u);
            }
        }
        int root = *roots.begin();
        ctsz(root);
        ctmarb(root);
        cout << solve(root) << '\n';
    }
}