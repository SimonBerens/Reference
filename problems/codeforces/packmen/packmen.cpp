#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template <typename K> using hset = gp_hash_table<K, null_type>;
template <typename K, typename V> using hmap = gp_hash_table<K, V>;

#pragma GCC optimize ("Ofast")
#pragma GCC target ("avx2")
using namespace std;

#define all(x) (x).begin(), (x).end()
#define pb push_back
#define eb emplace_back
#define smax(x, y) (x = max(x, y))
#define smin(x, y) (x = min(x, y))

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
    while (low < high) {
        IN middle = low + (high - low) / 2; // todo std::midpoint in cpp 2020
        if (predicate(middle))
            high = middle;
        else low = middle + 1;
    }
    return low;
}

#endif //REFERENCE_DISCRETE_BINARY_SEARCH_H

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    set<int> packmen, stars;
    for (int i = 0; i < n; ++i) {
        char c;
        cin >> c;
        if (c == '*') {
            stars.insert(i);
        } else if (c == 'P') {
            packmen.insert(i);
        }
    }
    cout << discrete_binary_search<int>([&](int t) -> bool {
        int covered = -1;
        int last_packman = -1;
        while (true) {
            // find rightmost star
            auto it_star = stars.lower_bound(covered + 1);
            if (it_star == stars.end()) return true;
            int rightmost_star = *it_star;
            // find packman
            auto it_pack = packmen.lower_bound(last_packman + 1);
            if (it_pack == packmen.end()) break;
            int packman = *it_pack;
            last_packman = packman;
            // doable?
            smax(covered, packman); // fine because if we don't cover it we return false
            if (rightmost_star < packman) {
                int diff = packman - rightmost_star;
                if (t < diff) return false;
                smax(covered, max(rightmost_star + t - diff, packman + (t - diff) / 2));
            } else {
                smax(covered, packman + t);
            }
            smax(last_packman, covered - t );
        }
        return stars.lower_bound(covered + 1) == stars.end();

    }, 0, 2 * n) << '\n';

}