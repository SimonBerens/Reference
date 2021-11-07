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
    freopen("rental.in", "r", stdin);
    freopen("rental.out", "w", stdout);

    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, m, r;
    cin >> n >> m >> r;
    vi cows(n);
    for (int i = 0; i < n; ++i) {
        cin >> cows[i];
    }
    maxq<l2> stores; // pi, qi
    for (int i = 0; i < m; ++i) {
        int q, p;
        cin >> q >> p;
        stores.push({p, q});
    }
    maxq<ll> renters;
    for (int i = 0; i < r; ++i) {
        int ri;
        cin >> ri;
        renters.push(ri);
    }
    sort(all(cows));
    reverse(all(cows));
    vll vals;
    for (ll c : cows) {
        ll val = 0;
        while (c > 0 && !stores.empty()) {
            auto [p, q] = stores.top();stores.pop();
            val += min(c, q) * p;
            if (q > c)
                stores.push({p, q - c});
            c -= min(c, q);
        }
        vals.pb(val);
    }
    ll res = accumulate(all(vals), 0LL);
    for (int i = vals.size() - 1; i >= 0; --i) {
        if (renters.empty()) break;
        int ri = renters.top(); renters.pop();
        res += max(0ll, ri - vals[i]);
    }
    cout << res << '\n';
}