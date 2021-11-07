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

using edge = array<int, 3>; // node, distance, color
vector<vector<edge>> g;

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

int n, k;

bool poss(ll C) {
    vvi visited(g.size(), vi(5));
    minq<array<ll, 3>> q; // t, u, cur_c
    q.push({0, 1, 0});
    while (!q.empty()) {
        auto [t, u, cur_c] = q.top();
        q.pop();
        if (t > k) return false;
        if (visited[u][cur_c]) continue;
        visited[u][cur_c] = true;
        if (u == n) return true;
        for (auto [v, d, c]: g[u]) {
            if (!visited[v][c]) q.push({t + d + (cur_c != c) * C, v, c});
        }
    }
    return false;
}

void solve() {
    ll ans = discrete_binary_search<ll>([&](ll C) -> bool {return !poss(C);}, 1, k + 1) - 1;
    if (ans == 0) {
        cout << "impossible\n";
    } else if (ans == k) {
        cout << "relaxing\n";
    } else {
        cout << ans << '\n';
    }

}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    for (int test_no = 0; test_no < t; ++test_no) {
        int m;
        cin >> n >> m >> k;
        g.assign(n + 1, vector<edge>{});
        for (int i = 0; i < m; ++i) {
            int x, y, d;
            char c;
            cin >> x >> y >> d >> c;
            g[x].pb({y, d, c - 'a'});
            g[y].pb({x, d, c - 'a'});
        }
        solve();
    }
}