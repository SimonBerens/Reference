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

int n, m, c;
vi r;
vii edges;

int main() {
    freopen("time.in", "r", stdin);
    freopen("time.out", "w", stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m >> c;
    r.assign(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        cin >> r[i];
    }
    edges.assign(m, {});
    for (int i = 0; i < m; ++i) {
        cin >> edges[i][0] >> edges[i][1];
    }
    vi dp(n + 1, -M);
    int res = 0;
    dp[1] = 0;
    for (int t = 1; t < 1000; ++t) {
        vi ndp(n + 1, -M);
        for (auto [a, b]: edges) {
            if (dp[a] == -M) continue;
            smax(ndp[b], dp[a] + r[b]);
        }
        dp = ndp;
        smax(res, dp[1] - c * t * t);
    }
    cout << res << '\n';
}