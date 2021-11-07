#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template <typename K> using hset = gp_hash_table<K, null_type>;
template <typename K, typename V> using hmap = gp_hash_table<K, V>;


using namespace std;

#define all(x) (x).begin(), (x).end()
#define pb push_back
#define eb push_back
#define smax(x, y) (x = max(x, y))
#define smin(x, y) (x = min(x, y))

using ll = long long;

template <typename T>
using vv = vector<vector<T>>;

using vi = vector<int>;
using ii = array<int, 2>;
using vii = vector<ii>;
using vvi = vv<int>;

using vll = vector<ll>;
using l2 = array<int, 2>;
using vl2 = vector<l2>;
using vvl2 = vv<l2>;

template <typename T>
using minq = priority_queue<T, vector<T>, greater<T>>;
template <typename T>
using maxq = priority_queue<T>;

const ll M = 1000000007;

int k;
vi a;


int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> k;
    a.assign(k, 0);
    for (int i = 0; i < k; ++i) {
        cin >> a[i];
    }
    sort(all(a));
    reverse(all(a));
    vvi dp(1 << 20, vi(8, M));
    for (int i = 0; i < k; ++i) {
        dp[1 << i][a[i]] = a[i];
    }
    for (int i = 1; i < (1 << 20); ++i) {
        for (int s = 1; s <= 7; ++s) {
            if (dp[i][s] == M) {
                continue;
            }
            for (int j = 0; j < k; ++j) {
                if ((i >> j) & 1) {
                    continue;
                }
                int new_stub = a[j] >= s ? a[j] - s + 1 : 1;
                smin(dp[i | (1 << j)][new_stub], dp[i][s] + new_stub);
            }
        }
    }

    cout << (*min_element(all(dp[(1 << k) - 1]))) << '\n';


}