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

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    vll g(n);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        g[u] |= 1ll << v;
        g[v] |= 1ll << u;
    }
    for (int u = 0; u < n; ++u) {
        g[u] |= 1ll << u;
    }
    vi dp1(1 << (n / 2));
    // dp(S) = max dp(S\{adj(u)}) + 1
    for (ll s = 0; s < dp1.size(); ++s) {
        for (int u = 0; u < n / 2; ++u) {
            if (s & (1ll << u)) smax(dp1[s], dp1[s ^ (s & g[u])] + 1);
        }
    }
    vi dp2(1ll << (n - n / 2));
    for (ll i = 0; i < dp2.size(); ++i) {
        ll s = i << (n / 2);
        for (int u = n / 2; u < n; ++u) {
            if (s & (1ll << u)) smax(dp2[s >> (n / 2)], dp2[(s ^ (s & g[u])) >> (n / 2)] + 1);
        }
    }
    ll r1 = 0, r2 = 0, res = 0;
    for (ll s = 0; s < dp1.size(); ++s) {
        ll x = 0;
        for (int u = 0; u < n / 2; ++u) {
            if (s & (1 << u)) x |= g[u];
        }
        ll c1 = s, c2 = (((1ll << n) - 1) ^ x) >> (n / 2);
        if (res < dp1[c1] + dp2[c2]) {
            res = dp1[c1] + dp2[c2];
            r1 = c1;
            r2 = c2;
        }
    }
    cout << res << '\n';
    for (ll s = r1; s >= 0; s = r1 & (s - 1)) {
        if (dp1[s] == dp1[r1] && __builtin_popcount(s) == dp1[r1]) {
            for (int u = 0; u < n / 2; ++u) {
                if (s & (1ll << u)) cout << u << ' ';
            }
            break;
        }
    }
    for (ll s = r2; s >= 0; s = r2 & (s - 1)) {
        if (dp2[s] == dp2[r2] && __builtin_popcount(s) == dp2[r2]) {
            for (int u = n / 2; u < n; ++u) {
                if (s & (1ll << (u - n / 2))) cout << u << ' ';
            }
            break;
        }
    }
}