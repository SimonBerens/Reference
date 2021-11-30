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
    int n, m;
    cin >> n >> m;
    // given subset of notes, whats the largest prefix we can satisfy?
    // we're going to have a prefix with some leftover
    // consider removing a note to get some (i, l)
    // if
    vi a(n), b(m);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    for (int i = 0; i < m; ++i) {
        cin >> b[i];
    }
    // dp(s) = max dp(s\{b[i]}) + thing
    vii dp(1 << m, {-M, -M});
    dp[0] = {0, 0};
    for (int s = 1; s < (1 << m); ++s) {
        for (int i = 0; i < m; ++i) {
            if (s & (1 << i)) {
                auto [p, l] = dp[s ^ (1 << i)];
                int np = p, nl = l + b[i];
                if (nl == a[p]) {
                    np++;
                    nl = 0;
                }
                ii ndp = {np, nl};
                smax(dp[s], ndp);
            }
        }
        if (dp[s][0] == n) {
            cout << "YES\n";
            return 0;
        }
    }
    cout << "NO\n";
}