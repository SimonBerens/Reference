#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template <typename K> using hset = gp_hash_table<K, null_type>;
template <typename K, typename V> using hmap = gp_hash_table<K, V>;


using namespace std;

#define all(x) (x).begin(), (x).end()
#define pb push_back
#define eb emplace_back
#define smax(x, y) (x = max(x, y))
#define smin(x, y) (x = min(x, y))

using ll = long long;
using ld = long double;

template <typename T>
using vv = vector<vector<T>>;

using vi = vector<int>;
using ii = array<int, 2>;
using vii = vector<ii>;
using vvi = vv<int>;

using vll = vector<ll>;
using l2 = array<ll, 2>;
using vl2 = vector<l2>;
using vvll = vv<ll>;

template <typename T>
using minq = priority_queue<T, vector<T>, greater<T>>;
template <typename T>
using maxq = priority_queue<T>;

const ll M = 1000000007;

template<typename T>
struct fenwick {

    int length;
    vector<T> tree;

    fenwick(int size) {
        length = size+1;
        tree.assign(length+1, 0);
    }

    fenwick(vector<T>& v) {
        length = v.size()+1;
        tree.assign(length+1, 0);
        for (int i = 0; i < v.size(); i++)
            update(i, v[i]);
    }

    // insert val at index i
    void update(int i, T val) {
        i++;
        while (i < length) {
            tree[i] += val;
            i += i & -i;
        }
    }

    // inclusive of i
    T prefix(int i) {
        i++;
        T out = 0;
        while (i > 0) {
            out += tree[i];
            i -= i & -i;
        }
        return out;
    }

    // sum over a..b, inclusive
    T query(int a, int b) {
        return prefix(b)-prefix(a-1);
    }
};

#ifndef REFERENCE_DISCRETE_BINARY_SEARCH_H
#define REFERENCE_DISCRETE_BINARY_SEARCH_H


#include <iostream>
#include <functional>


template<typename IN>
IN discrete_binary_search(function<bool(IN)> predicate, IN low = 0, IN high = numeric_limits<IN>::max()) {
    while (low < high) {
        IN middle = low + (high - low) / 2; // todo std::midpoint in cpp 2020
        if (predicate(middle))
            high = middle;
        else low = middle + 1;
    }
    return low;
}

#endif //REFERENCE_DISCRETE_BINARY_SEARCH_H


vii cows;
map<int, int> xc, yc;
vi xs, ys;

int xoffset = 2;

void solve() {
    int res = cows.size();
    // cows sorted by ys to transition down
    sort(all(cows));
    int i = 0;
    fenwick<int> t(xc.size() + 2 * xoffset + 10), b(xc.size() + 2 * xoffset + 10);
    int qmax = xs.size() + xoffset + 5;

    auto lrmax = [&](int x) -> ii {
        int lmax = max(b.query(1, x), t.query(1, x));
        int rmax = max(b.query(x + 1, qmax), t.query(x + 1, qmax));
        return {lmax, rmax};
    };
    auto allmax = [&](int x) -> int {
        auto [l, r] = lrmax(x);
        return max(l, r);
    };
    // process top
    int totalb = 0, totalt = 0;
    for (auto [y, x] : cows) {
        t.update(xc[x], 1);
        ++totalt;
    }
    for (int y = 0; y < ys.size(); ++y) {
//        cout << '\n';
        for (; i < cows.size() && yc[cows[i][0]] == y; ++i) {
            // add to bottom, remove from top
            b.update(xc[cows[i][1]], 1);
            ++totalb;
            t.update(xc[cows[i][1]], -1);
            --totalt;
        }
//        cout << "total b: " << totalb << '\n';
//        cout << "total t: " << totalt << '\n';
//        for (int x = xoffset; x <= xoffset + xs.size(); ++x) {
//            int lmax = max(b.query(1, x), t.query(1, x));
//            int rmax = max(b.query(x + 1, qmax), t.query(x + 1, qmax));
//            cout << x << "    lmax: " << lmax << "    rmax: " << rmax << '\n';
//        }
        int best = discrete_binary_search<int>([&](int x) -> bool {
            auto [lmax, rmax] = lrmax(x);
            return lmax >= rmax;
        }, 1 + xoffset, qmax - 2);
//        cout << "best: " << best << '\n';
        smin(res, min(allmax(best), allmax(best)));
    }
    cout << res << '\n';
}


int main() {
    freopen("balancing.in", "r", stdin);
    freopen("balancing.out", "w", stdout);

    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    cows.assign(n, {});
    for (int i = 0; i < n; ++i) {
        cin >> cows[i][0] >> cows[i][1];
        ys.pb(cows[i][0]);
        xs.pb(cows[i][1]);
    }
    sort(all(ys));
    ys.erase(unique(all(ys)), ys.end());
    for (int i = 0; i < ys.size(); ++i) {
        yc[ys[i]] = i;
    }
    sort(all(xs));
    xs.erase(unique(all(xs)), xs.end());
    for (int i = 0; i < xs.size(); ++i) {
        xc[xs[i]] = i + xoffset;
    }
    solve();
}