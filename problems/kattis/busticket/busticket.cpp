#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>

using namespace __gnu_pbds;
template<typename K> using hset = gp_hash_table<K, null_type>;
template<typename K, typename V> using hmap = gp_hash_table<K, V>;


using namespace std;

using ll = long long;

using vi = vector<int>;
using vvi = vector<vector<int>>;

template<typename T>
using minq = priority_queue<T, vector<T>, greater<T>>;
template<typename T>
using maxq = priority_queue<T>;

ll M = 1000000007;


int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int s, p, m, n;
    cin >> s >> p >> m >> n;
    vi ts(n);
    for (int i = 0; i < n; ++i) {
        cin >> ts[i];
    }

    vector<ll> dp(n+1);
    dp[0] = 0;
    for (int i = 1; i < n + 1; ++i) {
        int p_idx = min((int) distance(ts.begin(), upper_bound(ts.begin(), ts.end(), ts[i-1] - m)), i - 1);
        dp[i] = min(dp[i - 1] + s, dp[p_idx] + p);
    }
    cout << dp[n] << '\n';
}