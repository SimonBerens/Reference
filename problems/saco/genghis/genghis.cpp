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
    vi horses(k);
    for (int i = 0; i < k; ++i) {
        cin >> horses[i];
    }
    horses.pb(0);
    horses.pb(n + 1);
    k += 2;
    sort(all(horses));
    vvi dp(k, vi(k, M));
    for (int i = 0; i < k - 1; ++i) {
        dp[i + 1][i] = 0;
    }
    for (int l = k - 2; l >= 1; --l) {
        for (int r = l; r < k - 1; ++r) {
            int a = horses[r + 1] - horses[l - 1] - 1;
            for (int i = l; i <= r; ++i) {
                smin(dp[l][r], a + dp[l][i - 1] + dp[i + 1][r]);
            }
        }
    }
    cout << dp[1][k - 2] << '\n';
}