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
    vi xs(n), ys(n);
    for (int i = 0; i < n; ++i) {
        cin >> xs[i] >> ys[i];
    }

    vi sxs = xs;
    sort(sxs.begin(), sxs.end());
    sxs.erase(unique(sxs.begin(), sxs.end()), sxs.end());
    vi sys = ys;
    sort(sys.begin(), sys.end());
    sys.erase(unique(sys.begin(), sys.end()), sys.end());

    vi r_to_c(n);

    vvi g(n, vi(n));
    for (int i = 0; i < n; ++i) {
        int xi = distance(sxs.begin(), lower_bound(sxs.begin(), sxs.end(), xs[i]));
        int yi = distance(sys.begin(), lower_bound(sys.begin(), sys.end(), ys[i]));
        g[yi][xi] = 1;
        r_to_c[yi] = xi;
    }
    vvi p(n + 1, vi(n + 1));
    for (int r = 1; r <= n; ++r) {
        for (int c = 1; c <= n; ++c) {
            p[r][c] = p[r][c - 1] + p[r-1][c] - p[r-1][c-1] + g[r-1][c-1];
        }
    }
    ll res = 0;
    for (int lo = 0; lo < n; ++lo) {
        for (int hi = lo; hi < n; ++hi) {
            int x1 = r_to_c[lo], x2 = r_to_c[hi];
            if (x1 > x2) swap(x1, x2);
            res += (p[hi + 1][x1 + 1] - p[lo][x1 + 1]) *
                    (p[hi + 1][n] - p[hi + 1][x2] - p[lo][n] + p[lo][x2]);

        }
    }

    cout << res + 1 << '\n';


}