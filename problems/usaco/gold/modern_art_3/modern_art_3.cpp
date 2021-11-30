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
    vi a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    vvi dp(n, vi(n, M));
    for (int i = 0; i < n; ++i) {
        dp[i][i] = 1;
    }
    for (int l = n - 1; l >= 0; --l) {
        for (int r = l + 1; r < n; ++r) {
            int x = a[l] == a[r];
            for (int i = l; i + 1 <= r; ++i) {
                smin(dp[l][r], dp[l][i] + dp[i + 1][r] - x);
            }
        }
    }
    cout << dp.front().back() << '\n';
}