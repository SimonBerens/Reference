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
vi m;
vector<set<int>> g;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    while (true) {
        cin >> n;
        if (n == 0) break;
        m.assign(n, 0);
        g.assign(n, set<int>{});
        for (int i = 0; i < n; ++i) {
            int v, d;
            cin >> v >> m[i] >> d;
            for (int j = 0; j < d; ++j) {
                int u;
                cin >> u;
                u -= 1;
                g[i].insert(u);
                g[u].insert(i);
            }
        }
        queue<int> q; // node, unfilled,
        vi uf(n);
        for (int i = 0; i < n; ++i) {
            if (g[i].size() == 1) { q.push(i); }
        }
        int res = 0;
        while (!q.empty()) {
            auto node = q.front(); q.pop();
            uf[node] += 1 - m[node];
            for (int v : g[node]) {
                res += abs(uf[node]);
                uf[v] += uf[node];
                g[v].erase(node);
                if (g[v].size() == 1) q.push(v);
            }
        }
        cout << res << '\n';
    }
}