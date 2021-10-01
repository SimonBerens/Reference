#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template <typename K> using hset = gp_hash_table<K, null_type>;
template <typename K, typename V> using hmap = gp_hash_table<K, V>;


using namespace std;

using ll = long long;

using vi = vector<int>;
using vvi = vector<vector<int>>;

template <typename T>
using minq = priority_queue<T, vector<T>, greater<T>>;
template <typename T>
using maxq = priority_queue<T>;

ll M = 1000000007;

int N, K;
vi a;
int dp(int i, int k) {
    if (i == 0) {
        return k <= a[0];
    }

    int res = 0;
    for (int j = 0; j <= a[i] && j <= k; ++j) {
        res += dp(i - 1, k - j);
        res %= M;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> K;
    a.assign(N, 0);
    for (int i = 0; i < N; ++i) {
        cin >> a[i];
    }
    cout << dp(N, K) << '\n';
}