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
    int s, n;
    cin >> s >> n;
    // weight -> sorted(val, amt)
    vv<ii> ws(s + 1);
    for (int i = 0; i < n; ++i) {
        int v, w, k;
        cin >> v >> w >> k;
        ws[w].pb({v, k});
    }
    for (auto & vec : ws) {
        sort(all(vec), greater<>());
    }
    vi dp(s + 1); // s, k
    for (int w = 1; w <= s; ++w) {
        if (ws[w].empty()) continue;
        auto ndp = dp;
        for (int ss = 0; ss <= s; ++ss) { // space left
            int tv = 0, tw = w;
            for (int i = 0; i < ws[w].size() && tw <= ss; ++i) {
                auto [v, k] = ws[w][i];
                for (int kk = 1; kk <= k && tw<= ss; ++kk) { // amount used
                    tv += v;
                    smax(ndp[ss], dp[ss - tw] + tv);
                    tw += w;
                }
            }

        }
        dp = ndp;
    }
    cout << *max_element(all(dp)) << '\n';

}