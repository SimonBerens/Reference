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
    int w, h, n;
    cin >> w >> h >> n;
    vvi dp(w + 1, vi(h + 1));
    for (int r = 0; r < dp.size(); ++r) {
        for (int c = 0; c < dp[r].size(); ++c) {
            dp[r][c] = r * c;
        }
    }
    for (int i = 0; i < n; ++i) {
        int wi, hi;
        cin >> wi >> hi;
        dp[wi][hi] = 0;
    }
    for (int ww = 1; ww <= w; ++ww) {
        for (int hh = 1; hh <= h; ++hh) {
            for (int lw = 1; lw < ww; ++lw) {
                smin(dp[ww][hh], dp[lw][hh] + dp[ww - lw][hh]);
            }
            for (int bh = 1; bh < hh; ++bh) {
                smin(dp[ww][hh], dp[ww][bh] + dp[ww][hh - bh]);
            }
        }
    }
    cout << dp[w][h] << '\n';
}