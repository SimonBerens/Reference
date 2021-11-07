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
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    vi p(n);
    for (int i = 0; i < n; ++i) {
        cin >> p[i];
    }
    sort(all(p));
    reverse(all(p));
    long double res = 0;
    vector<long double> dp(n+1);
    dp[0] = 1;
    for (int s = 1; s <= n; ++s) {
        long double cp = p[s-1] / 100.l;
        long double erpi = 0;
        auto ndp = dp;
        ndp[0] = (1 - cp) * dp[0];
        for (int a = 1; a <= s; ++a) {
            // dp(i, k) = p * dp(i - 1, k - 1) + (1 - p) * dp(i - 1, k)
            ndp[a] = cp * dp[a-1] + (1 - cp) * dp[a];
            erpi += ndp[a] * pow(a, a / (s + 0.l));
        }
        dp = ndp;
        smax(res, erpi);
    }
    cout << fixed << setprecision(7) << res << '\n';

}