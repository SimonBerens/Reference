
#pragma GCC optimize ("fast-math")

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

using ld = double;
using ll = long long;

template <typename T>
using vv = vector<vector<T>>;

using vi = vector<int>;
using ii = array<int, 2>;
using vii = vector<ii>;
using vvi = vv<int>;

using vll = vector<ll>;
using l2 = array<int, 2>;
using vl2 = vector<l2>;
using vvll = vv<ll>;

template <typename T>
using minq = priority_queue<T, vector<T>, greater<T>>;
template <typename T>
using maxq = priority_queue<T>;

const ll M = 1000000007;

#ifndef REFERENCE_DISCRETE_BINARY_SEARCH_H
#define REFERENCE_DISCRETE_BINARY_SEARCH_H


#include <iostream>
#include <functional>


template<typename IN>
IN discrete_binary_search(function<bool(IN)> predicate, IN low = 0, IN high = numeric_limits<IN>::max()) {
    while (fabs(high - low) > 1e-4) {
        IN middle = low + (high - low) / 2; // todo std::midpoint in cpp 2020
        if (predicate(middle))
            high = middle;
        else low = middle;
    }
    return low;
}

#endif //REFERENCE_DISCRETE_BINARY_SEARCH_H

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, l;
    cin >> n >> l;
    vll x(n), y(n);
    for (int i = 0; i < n; ++i) {
        cin >> x[i] >> y[i];
    }

    cout << fixed << setprecision(4) <<  discrete_binary_search<ld>([&](ld d) -> bool {
        // is there a point with min distance > d
        // equivalently, is every point within distance d

        vector<array<ld, 2>> intervals;
        intervals.reserve(n);
        // add to intervals
        for (int i = 0; i < n; ++i) {
            if (abs(y[i]) > d) continue;
            ld dx = sqrt(d * d - y[i] * y[i]);
            ld s1 = x[i] - dx, e1 = x[i] + dx;
            // can merge in place
            while (!intervals.empty()) {
                auto & [s2, e2] = intervals.back();
                if (max(s1, s2) <= min(e1, e2)) {
                    smin(s1, s2);
                    smax(e1, e2);
                    intervals.pop_back();
                } else break;
            }
            intervals.pb({s1, e1});
        }

        // check interval spans whole highway
        for (auto [s, e] : intervals) {
            if (s <= 0 && l <= e) return true;
        }
        return false;

    }, 0, 4e9) << '\n';

}