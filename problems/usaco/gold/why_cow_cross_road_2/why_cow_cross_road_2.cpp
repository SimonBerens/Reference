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
    freopen("nocross.in", "r", stdin);
    freopen("nocross.out", "w", stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    vi a(n), b(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    vi m(n + 1); // val to idx
    for (int i = 0; i < n; ++i) {
        cin >> b[i];
        m[b[i]] = i;
    }
    // dp
    // for each element of a, you either take it or you dont
        // if you take it, you need to match it with its friends

    // dp(i, j) = max(dp(i - 1, j), max(dp(i -1, fj -1) + 1)

    vi dp(n + 1);
    for (int i = 0; i < n; ++i) {
        for (int j = n - 1; j >= 0; --j) {
            for (int fv = max(1, a[i] - 4); fv <= min(n, a[i] + 4); ++fv) {
                if (m[fv] <= j) smax(dp[j + 1], dp[m[fv]] + 1);
            }
        }
    }
    cout << dp.back() << '\n';
}