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
    int n, m, q;
    cin >> n >> m >> q;
    vi a(n), b(m);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    for (int i = 0; i < m; ++i) {
        cin >> b[i];
    }
    set<ll> vals;
    // populate vals
        // compute even/odd sums of a
        // compute f(j) without abs
            // get even/odd sums up to n of b
            // when you increment j, subtract left value from even sum and swap sums
    vll ps{0};
    for (int i = 0; i < n; ++i) {
        ps.pb(ps.back() + (1 - 2 * (i % 2)) * a[i]);
    }
    ll as = ps.back();
    ps.clear();
    ps = {0};
    for (int i = 0; i < m; ++i) {
        ps.pb(ps.back() + (1 - 2 * (i % 2)) * b[i]);
    }
    for (int j = 0; j <= m - n; ++j) {
        vals.insert(as + (ps[j + n] - ps[j]) * (1 - 2 * (1 - (j % 2))));
    }
    ll zero = 0;
    vector<array<ll, 3>> queries(q + 1);
    for (int i = 1; i <= q; ++i) {
        for (int j = 0; j < 3; ++j) {
            cin >> queries[i][j];
        }
    }
    for (auto [l, r, x] : queries) {
        // each query increments f(j) by +x/-x/0
        // shift zero accordingly
        // find element to the left/right of zero in vals
        if (l % 2 == 1 && r % 2 == 1) {
            zero -= x;
        } else if (l % 2 == 0 && r % 2 == 0) {
            zero += x;
        }
        auto it = vals.upper_bound(zero);
        ll b = M * M, t = M * M;
        if (it != vals.end()) t = *it;
        if (it != vals.begin()) b = *(--it);
        cout << min(abs(t - zero), abs(b - zero)) << '\n';
    }
}