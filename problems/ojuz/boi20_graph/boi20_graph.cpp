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

int n, m;
vv<ii> g;
using valt = ii;
vector<set<valt>> coefs;
vi vis;

tuple<bool, vvi> solve() {
    vvi comps;
    for (int i = 1; i <= n; ++i) {
        if (vis[i]) continue;
        comps.pb({});
        queue<tuple<int, valt>> q; // node, val
        q.push({i, {1, 0}});
        while (!q.empty()) {
            auto [u, val] = q.front(); q.pop();
            coefs[u].insert(val);
            if (vis[u]) {
                if (coefs[u].size() > 2) return {false, {}};
                continue;
            }
            vis[u] = true;
            comps.back().pb(u);
            auto [a, b] = val;
            for (auto [v, c]: g[u]) {
                q.push({v, {-a, c-b}});
            }
        }

    }
    return {true, comps};
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    g.assign(n + 1, vii{});
    coefs.assign(n + 1, set<valt>{});
    vis.assign(n + 1, false);

    for (int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        g[a].pb({b, c});
        g[b].pb({a, c});
    }
    auto [poss, comps] = solve();
    if (poss) {
        vector<long double> vals(n + 1);
        for (const auto & comp : comps) {
            vi pts;
            long double x;
            bool fixed = false;
            for (int u : comp) {
                auto [a, b] = *coefs[u].begin();
                pts.pb(-a * b);
                if (coefs[u].size() == 2) {
                    auto [a1, b1] = *coefs[u].begin();
                    auto [a2, b2] = *(++coefs[u].begin());
                    long double tmp = (b2 - b1) / (0.l + a1 - a2);
                    if (b1 == b2) tmp = 0;
                    if ((a1 == a2) || (fixed && fabs(tmp - x) > DBL_EPSILON)) {
                        cout << "NO\n";
                        exit(0);
                    }
                    x = tmp;
                    fixed = true;
                }
            }
            if (!fixed) {
                sort(all(pts));
                if (pts.size() % 2 == 1) x = pts[pts.size() / 2];
                else x = (pts[pts.size() / 2 - 1] + pts[pts.size() / 2]) / 2.l;
            }
            for (int u : comp) {
                auto [a, b] = *coefs[u].begin();
                vals[u] = a * x + b;
            }
        }
        cout << "YES\n";
        for (int i = 1; i <= n; ++i) {
            cout << vals[i] << ' ';
        }
        cout << '\n';
    } else {
        cout << "NO\n";
    }

}