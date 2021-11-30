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

template <typename T, typename C>
vector<pair<T, C>> groupby(const vector<T> & a) {
    vector<pair<T, C>> groups;
    for (const T & v : a) {
        if (groups.empty() || groups.back().first != v) {
            groups.pb({v, C{}});
        }
        ++groups.back().second;
    }
    return groups;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    n += 2;
    vi a(n), p(n), s(n);
    for (int i = 1; i < n - 1; ++i) {
        cin >> a[i];
    }
    a[0] = a[n - 2];
    a[n - 1] = a[1];
    p[0] = a[0];
    p[1] = a[1];
    s.back() = a.back();
    s[n - 2] = a[n - 2];
    for (int i = 2; i < n; ++i) {
        p[i] = gcd(a[i], p[i - 1]);
    }
    for (int i = n - 3; i >= 0; --i) {
        s[i] = gcd(a[i], s[i + 1]);
    }
    int g = p.back();
    ll res = g;
    for (int i = 0; i + 2 < n; ++i) {
       res *= gcd(p[i], s[i + 2]) / g;
    }
    cout << res << '\n';


}