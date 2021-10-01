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
    freopen("art.in", "r", stdin);
    freopen("art.out", "w", stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    vvi g(n, vi(n));
    vi l(n * n + 1, M), r(n * n + 1, -1), b(n * n + 1, M), t(n * n + 1, -1);
    vi seen_colors(n * n + 1);
    for (int row = 0; row < n; ++row) {
        for (int col = 0; col < n; ++col) {
            cin >> g[row][col];
            l[g[row][col]] = min(l[g[row][col]], col);
            r[g[row][col]] = max(r[g[row][col]], col);
            b[g[row][col]] = min(b[g[row][col]], row);
            t[g[row][col]] = max(t[g[row][col]], row);
            if (g[row][col] != 0) {
                seen_colors[g[row][col]] = 1;
            }
        }
    }
    if (accumulate(seen_colors.begin(), seen_colors.end(), 0) == 1) {
        cout << n * n - 1 << '\n';
        return 0;
    }
    vvi pre_p(n+1, vi(n+1));
    for (int i = 1; i <= n * n; ++i) {
        if (l[i] == M) continue;
        pre_p[b[i]][l[i]] += 1;
        pre_p[t[i]+1][r[i]+1] += 1;
        pre_p[b[i]][r[i]+1] -= 1;
        pre_p[t[i]+1][l[i]] -= 1;
    }
    vvi p(n+1, vi(n+1));
    for (int row = 1; row <= n; ++row) {
        for (int col = 1; col <= n; ++col) {
            p[row][col] = p[row - 1][col] + p[row][col - 1] - p[row - 1][col - 1] + pre_p[row - 1][col - 1];
        }
    }
    vi poss(n * n + 1, 1);
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < n; ++c) {
            if (p[r + 1][c + 1] > 1) {
                poss[g[r][c]] = 0;
            }
        }
    }
    cout << accumulate(poss.begin(), poss.end(), 0) - 1 << '\n';

}