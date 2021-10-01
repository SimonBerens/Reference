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
namespace std {
    template<std::size_t N>
    bool operator<(const std::bitset<N>& x, const std::bitset<N>& y)
    {
        for (int i = N-1; i >= 0; i--) {
            if (x[i] ^ y[i]) return y[i];
        }
        return false;
    }
}
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

bitset<160> construct_bitset(string & s) {
    reverse(s.begin(), s.end());
    bitset<160> res;
    for (int i = 0; i < s.size(); ++i) {
        char c = s[i];
        if (c <= '9') {
            res ^= bitset<160>{static_cast<unsigned long long>(c - '0')} << (4 * i);
        } else {
            res ^= bitset<160>{static_cast<unsigned long long>(c - 'a' + 10)} << (4 * i);
        }
    }
    return res;
}




void add(bitset<160> x, vector<bitset<160>>& basis) {
    // make sure leading 1 of each "it" is unique
    for (auto &it: basis)
        if ((x ^ it) < x) // if this is true then
            x ^= it;
    if (x != bitset<160>{}) {
        // make sure leading 1 of "x" is unique
        for (auto &it: basis)
            if ((x ^ it) < it)
                it ^= x;
        basis.push_back(x);
        sort(basis.begin(), basis.end());
    }
}

bool representable(bitset<160> x, vector<bitset<160>> & basis) {
    // make sure leading 1 of each "it" is unique
    for (auto &it: basis)
        if ((x ^ it) < x) // if this is true then
            x ^= it;
    return x == 0;
}


int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<bitset<160>>> bs(n + 1);
    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        auto b = construct_bitset(s);
        bs[i+1] = bs[i];
        add(b, bs[i + 1]);
    }

    int first_lin_dep = -1;
    for (int i = 0; i < n; ++i) {
        if (bs[i].size() == bs[i + 1].size()) {
            first_lin_dep = i + 1;
            break;
        }
    }

    // construct basis

    // answer queries
    for (int i = 0; i < m; ++i) {
        string s;
        cin >> s;
        auto x = construct_bitset(s);
        if (x == bitset<160>{}) {
            cout << first_lin_dep << '\n';
            continue;
        }
        auto j = discrete_binary_search<int>([&](int m) -> bool {
            return representable(x, bs[m]) || m == n + 1;
        }, 0, n + 1);
        cout << (j == n + 1? -1 : j) << '\n';
    }

}