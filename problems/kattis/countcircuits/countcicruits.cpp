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
int N;
vi xs;
vi ys;

ll dpa[41][850][850];

int offset(int z) {
    return z + 410;
}

ll dp(int i, int x, int y) {
    if (i == N) {
        return x == 0 && y == 0;
    }

    ll &res = dpa[i][offset(x)][offset(y)];

    if (res != -1) {
        return res;
    }

    return res = dp(i + 1, x + xs[i], y + ys[i]) + dp(i + 1, x, y);
}


int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    xs.assign(N, 0);
    ys.assign(N, 0);
    for (int i = 0; i < N; ++i) {
        cin >> xs[i] >> ys[i];
    }
    fill(dpa[0][0] + 0, dpa[40][849] + 850, -1);
    cout << dp(0, 0, 0) - 1 << '\n';
}