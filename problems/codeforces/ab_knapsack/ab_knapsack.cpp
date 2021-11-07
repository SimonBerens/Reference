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

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, m, s, A, B;
    cin >> n >> m >> s >> A >> B;
    vi c(n + m), w(n + m);
    for (int i = 0; i < n; ++i) {
        cin >> c[i];
        w[i] = A;
    }
    for (int i = n; i < n + m; ++i) {
        cin >> c[i];
        w[i] = B;
    }
    sort(c.begin(), c.begin() + n);
    sort(c.begin() + n, c.end());
    reverse(c.begin() + n, c.end());

    int l = 0;
    ll res = 0;
    ll tc = 0;
    ll tw = 0;
    for (int r = 0; r < n + m; ++r) {
        tw += w[r];
        tc += c[r];
        while (tw > s) {
            tw -= w[l];
            tc -= c[l];
            ++l;
        }
        res = max(res, tc);
    }

    cout << res << '\n';

}