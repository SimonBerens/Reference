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
    int n, k;
    cin >> n >> k;
    vll a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    vvi dp(k + 1, vi(k * 25 + 1, -1)); // res, 2^x, 5^y
    dp[0][0] = 0;
    auto ndp = dp;
    for (int i = 0; i < n; ++i) {
        int x = 0, y = 0;
        while (a[i] % 2 == 0) {
            a[i] /= 2;
            ++x;
        }
        while (a[i] % 5 == 0) {
            a[i] /= 5;
            ++y;
        }
        for (int kk = 0; kk < k; ++kk) {
            for (int f = 0; f + y < dp[kk].size(); ++f) {
                if (dp[kk][f] != -1) smax(ndp[kk + 1][f + y], dp[kk][f] + x);
            }
        }
        dp = ndp;
    }
    int res = 0;
    for (int f = 0; f < dp[0].size(); ++f) {
        smax(res, min(f, dp[k][f]));
    }
    cout << res << '\n';
}