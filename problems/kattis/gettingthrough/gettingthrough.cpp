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


struct dsu {

    vector<int> p, sz;

    dsu(int n) : p(n), sz(n, 1) {
        iota(p.begin(), p.end(), 0);
    }

    int rep(int x) {
        while (x != p[x]) x = p[x] = p[p[x]];
        return x;
    }

    // returns true if a and b are in the same set, and then unites them.
    bool unite(int a, int b) {
        a = rep(a), b = rep(b);
        if (sz[a] < sz[b]) swap(a, b);
        if (a != b) p[b] = a, sz[a] += sz[b];
        return a == b;
    }

    // returns true if a and b are in the same set.
    bool query(int a, int b) {
        return rep(a) == rep(b);
    }

    // returns the size of the set containing x
    int size(int x) {
        return sz[rep(x)];
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    cout << setprecision(7);
    for (int test_no = 0; test_no < t; ++test_no) {
        int cw, n;
        cin >> cw >> n;
        vector<ll> xs(n), ys(n), rs(n);
        for (int i = 0; i < n; ++i) {
            cin >> xs[i] >> ys[i] >> rs[i];
        }

        auto dist = [&](int i, int j) -> double {
            return sqrt((ys[j] - ys[i]) * (ys[j] - ys[i]) + (xs[j] - xs[i]) * (xs[j] - xs[i])) -
                    (rs[i] + rs[j]);
        };

        int V = n + 2, L = n, R = n + 1;

        minq<tuple<double, int, int>> edges;
        for (int i = 0; i < n; ++i) {
            // left wall
            edges.emplace(xs[i] - rs[i], i, L);
            // right wall
            edges.emplace(cw - (xs[i] + rs[i]), i, R);

        }
        for (int i = 0; i < n - 1; ++i) {
            for (int j = i + 1; j < n; ++j) {
                edges.emplace(dist(i, j), i, j);
            }
        }

        dsu uf(V);
        double res = cw;
        while (!edges.empty() && !uf.query(L, R)) {
            auto [d, i, j] = edges.top();
            edges.pop();
            if (uf.query(i, j)) continue;
            uf.unite(i, j);
            res = max(0., d);
        }
        cout << res / 2 << '\n';
    }
}