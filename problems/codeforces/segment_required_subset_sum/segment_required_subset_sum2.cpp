#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template <typename K> using hset = gp_hash_table<K, null_type>;
template <typename K, typename V> using hmap = gp_hash_table<K, V>;


using namespace std;

#define all(x) (x).begin(), (x).end()
#define pb push_back
#define smax(x, y) (x = max(x, y))
#define smin(x, y) (x = min(x, y))

using ll = long long;

using vi = vector<int>;
using vvi = vector<vector<int>>;

template <typename T>
using minq = priority_queue<T, vector<T>, greater<T>>;
template <typename T>
using maxq = priority_queue<T>;

const ll M = 1000000007;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, s;
    cin >> n >> s;
    vi a(n);
    for (int i = 0; i < n; ++i)
        cin >> a[i];

    int res = M;
    vi dp(s + 1, -1);
    for (int i = 0; i < n; ++i) {
        dp[0] = i;
        for (int j = dp.size() - 1; j -a[i] >= 0; --j)
            smax(dp[j], dp[j - a[i]]);
        if (dp[s] != -1)
            smin(res,  i - dp[s] + 1);
    }
    cout << (res == M ? -1 : res) << '\n';

}