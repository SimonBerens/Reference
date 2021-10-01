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
    int n;
    cin >> n;
    vvi m100(n, vi(n)), m101(n, vi(n));
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < n; ++c) {
            int x;
            cin >> x;
            m100[r][c] = x >= 100;
            m101[r][c] = x > 100;
        }
    }
    vvi p100(n + 1, vi(n)), p101(n + 1, vi(n));
    for (int c = 0; c < n; ++c) {
        for (int r = 1; r <= n; ++r) {
            p100[r][c] = p100[r - 1][c] + m100[r - 1][c];
            p101[r][c] = p101[r - 1][c] + m101[r - 1][c];
        }
    }
    ll r100 = 0, r101 = 0;
    for (int rlo = 0; rlo < n; ++rlo) {
        for (int rhi = rlo; rhi < n; ++rhi) {
            ll l100 = -1, l101 = -1;
            int rd = rhi - rlo + 1;
            for (int c = 0; c < n; ++c) {
                if (p100[rhi + 1][c] - p100[rlo][c] == rd) {
                    r100 += c - l100;
                } else {
                    l100 = c;
                }
                if (p101[rhi + 1][c] - p101[rlo][c] == rd) {
                    r101 += c - l101;
                } else {
                    l101 = c;
                }
            }
        }
    }
    cout << r100 - r101 << '\n';
}