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
    int n, x;
    cin >> n >> x;
    vi w(n);
    for (int i = 0; i < n; ++i) {
        cin >> w[i];
    }
    // consider some subset of people S
    // for each person, if we add him last, then we increase the capacity used
    // if the capacity overflows, then we need to start a new ride
    vii dp(1 << n, {M, M}); // rides, cap
    dp[0] = {1, 0};
    for (int s = 0; s < (1 << n); ++s) {
        for (int i = 0; i < n; ++i) {
            if (s & (1 << i)) {
                auto [r, c] = dp[s ^ (1 << i)];
                int nr = r, nc = c + w[i];
                if (nc > x) {
                    nr = r + 1;
                    nc = w[i];
                }
                ii ndp{nr, nc};
                smin(dp[s], ndp);
            }
        }
    }
    cout << dp.back()[0] << '\n';
}