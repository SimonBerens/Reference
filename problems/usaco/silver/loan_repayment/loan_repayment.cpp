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
    freopen("loan.in", "r", stdin);
    freopen("loan.out", "w", stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll n, k, m;
    cin >> n >> k >> m;

    cout << discrete_binary_search<ll>([&](ll x) -> bool {
        ll rem = n;
        ll days = 0;
        while (m < rem / x) {
            ll s = ((rem % x) + (rem / x) - 1) / (rem / x);
            days += s;
            rem -= s * (rem / x);
            rem -= rem / x;
            ++days;
        }
        return !(k >= days + (rem + m - 1) / m);
    }, 0, n) - 1 << '\n';

}