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
    int n, p , k;
    cin >> n >> p >> k;
    vll a(n);
    vvll s(n, vll(p));
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < p; ++j) {
            cin >> s[i][j];
        }
    }
    vi is(n);
    iota(all(is), 0);
    sort(all(is), [&](int i, int j) -> bool { return a[i] > a[j];});

    vll dp(1 << p, -1);
    dp[0] = 0;
    for (int z = 0; z < n; ++z) {
        int i = is[z];
        for (int S = (1 << p) - 1; S >= 0; --S) {
            int c = z - __builtin_popcount(S);
            if (dp[S] != -1 && c < k) {
                dp[S] += a[i];
            }
            for (int j = 0; j < p; ++j) {
                if (S & (1 << j) && dp[S ^ (1 << j)] != -1) {
                    smax(dp[S], dp[S ^ (1 << j)] + s[i][j]);
                } 
            }
        }
    }
    cout << dp.back() << '\n';
}