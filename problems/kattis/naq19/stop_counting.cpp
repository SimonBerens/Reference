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
    int n;
    cin >> n;
    vi cards(n);
    for (int i = 0; i < n; ++i) {
        cin >> cards[i];
    }
    vector<long double> p(n + 1), s(n + 1);
    ll sm = 0;
    for (int i = 0; i < n; ++i) {
        sm += cards[i];
        p[i+1] = max(p[i], sm / (i + 1.l));
    }
    sm = 0;
    for (int i = n - 1; i >= 0; --i) {
        sm += cards[i];
        s[i] = max(s[i + 1], sm / (n - i + 0.l));
    }
    long double res = 0;
    for (int i = 0; i < n + 1; ++i) {
        smax(res, max(p[i], s[i]));
    }
    cout << fixed << setprecision(10) << res << '\n';
}