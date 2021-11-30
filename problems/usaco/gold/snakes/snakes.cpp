#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>

using namespace __gnu_pbds;
template<typename K> using hset = gp_hash_table<K, null_type>;
template<typename K, typename V> using hmap = gp_hash_table<K, V>;


using namespace std;

#define all(x) (x).begin(), (x).end()
#define pb push_back
#define eb emplace_back
#define smax(x, y) (x = max(x, y))
#define smin(x, y) (x = min(x, y))

using ll = long long;
using ld = long double;

template<typename T>
using vv = vector<vector<T>>;

using vi = vector<int>;
using ii = array<int, 2>;
using vii = vector<ii>;
using vvi = vv<int>;

using vll = vector<ll>;
using l2 = array<ll, 2>;
using vl2 = vector<l2>;
using vvll = vv<ll>;

template<typename T>
using minq = priority_queue<T, vector<T>, greater<T>>;
template<typename T>
using maxq = priority_queue<T>;

const ll M = 1000000007;

int main() {
    freopen("snakes.in", "r", stdin);
    freopen("snakes.out", "w", stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, k;
    cin >> n >> k;
    vi a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    // split the array into k + 1 subarrays s.t. the sum of max_sub * len_sub - sum (elements of sub) is minimized
    // dp(i, kk) -> we are in subarrray kk
    vvi dp(n + 1, vi(k + 1, M));
    int mx = 0, sum = 0;
    for (int i = 0; i < n; ++i) {
        smax(mx, a[i]);
        sum += a[i];
        dp[i + 1][0] = mx * (i + 1) - sum;
    }
    for (int i = 0; i < n; ++i) {
        for (int kk = 1; kk <= k; ++kk) {
            mx = 0; sum = 0;
            for (int j = i; j >= kk; --j) {
                smax(mx, a[j]);
                sum += a[j];
                int len = i - j + 1;
                smin(dp[i + 1][kk], mx * len - sum + dp[j][kk -1]);
            }
        }
    }
    cout << dp.back().back() << '\n';
}