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

vector<set<int>> g;
set<int> unvis;

int dfs(int u) {
    unvis.erase(u);
    int res = 1;
    int v = 0;
    while (true) {
        auto vit = unvis.upper_bound(v);
        if (vit == unvis.end()) break;
        v = *vit;
        if (g[u].count(v) == 0) res += dfs(v);
    }
    return res;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    g.assign(n + 1, set<int>{});
    for (int i = 0; i < m; ++i) {
        int x, y;
        cin >> x >> y;
        g[x].insert(y);
        g[y].insert(x);
    }
    for (int i = 1; i <= n; ++i) {
        unvis.insert(i);
    }
    vi c;
    for (int i = 1; i <= n; ++i) {
        if (unvis.count(i) == 1) c.pb(dfs(i));
    }
    sort(all(c));
    cout << c.size() << '\n';
    for (int i : c) {
        cout << i << ' ';
    }
    cout << '\n';
}