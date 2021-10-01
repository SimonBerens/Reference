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
//    freopen("paintbarn.in", "r", stdin);
//    freopen("paintbarn.out", "w", stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, k;
    cin >> n >> k;
    vvi g(1002, vi(1002));
    for (int i = 0; i < n; ++i) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        g[y1][x1] += 1;
        g[y2][x2] += 1;
        g[y2][x1] -= 1;
        g[y1][x2] -= 1;
    }
    int res = 0;
    vvi p(1002, vi(1002));
    for (int r = 1; r < 1002; ++r) {
        for (int c = 1; c < 1002; ++c) {
            p[r][c] = p[r-1][c] + p[r][c-1] - p[r-1][c-1] + g[r-1][c-1];
            if (p[r][c] == k) {
                res++;
            }
        }
    }
    cout << res << '\n';

}