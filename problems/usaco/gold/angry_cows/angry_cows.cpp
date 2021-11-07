#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template <typename K> using hset = gp_hash_table<K, null_type>;
template <typename K, typename V> using hmap = gp_hash_table<K, V>;


using namespace std;

#define all(x) (x).begin(), (x).end()
#define pb push_back
#define eb push_back
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
using vvl2 = vv<l2>;

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


bool can_blow_up_all_right(ll r, ll loc, const vi & v) {
    auto it = upper_bound(all(v), loc);
    if (it == v.end()) return true;
    int i = it - v.begin();
    for (; i < v.size(); ++i) {
        if (loc + r < v[i]) {
            if (i == 0) return false;
            r -= 2;
            loc = v[i-1];
            if (loc + r < v[i]) return false;
        }
    }
    return true;
}

bool cant_blow_up_all_left(ll r, ll loc, const vi & v) {
    auto it = upper_bound(all(v), loc);
    int i = it == v.end() ? v.size() - 1 : it - v.begin();
    for (; i >= 0; --i) {
        if (v[i] + r < loc) {
            if (i == v.size() - 1) return true;
            r -= 2;
            loc = v[i+1];
            if (v[i] + r < loc) return true;
        }
    }
    return false;
}

int main() {
    freopen("angry.in", "r", stdin);
    freopen("angry.out", "w", stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    vi bales(n);
    for (int i = 0; i < n; ++i) {
        cin >> bales[i];
        bales[i] *= 2;
    }
    sort(all(bales));

    cout << fixed << setprecision(1) << discrete_binary_search<ll>([&](ll r) -> bool {
        ll min_to_right = discrete_binary_search<ll>([&](ll loc) -> bool {return can_blow_up_all_right(r, loc, bales);}, 0, 1e10),
        max_to_left = discrete_binary_search<ll>([&](ll loc) -> bool {return cant_blow_up_all_left(r, loc, bales);}, 0, 1e10) - 1;
        return max_to_left >= min_to_right;
    }, 0, 1e10) / 2. << '\n';


}