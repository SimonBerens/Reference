#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template <typename K> using hset = gp_hash_table<K, null_type>;
template <typename K, typename V> using hmap = gp_hash_table<K, V>;


using namespace std;

using ll = long long;

using vi = vector<int>;
using vvi = vector<vector<int>>;

using pii =  pair<int, int>;

template <typename T>
using minq = priority_queue<T, vector<T>, greater<T>>;
template <typename T>
using maxq = priority_queue<T>;

ll M = 1000000007;
int n;
vector<pair<int, int>> segs;

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

int dpa[3005][3005] = {};
int test[3005][3005] = {};
int test_no = 1;

int dp(int i, int j) {
    if (i == -1 || j == -1) {
        return 0;
    }

    int & res = dpa[i][j];
    int t = test[i][j];
    if (t == test_no) {
        return res;
    }
    test[i][j] = test_no;


    if (i == j) {
        return res = 1 + dp(i, j- 1);
    }

    // don't take
    int no_take = dp(i, j - 1);
    // take
    if (!(segs[i].first <= segs[j].first && segs[j].second <= segs[i].second)) {
        return res = no_take;
    }
    int take = dp(j, j);
    // find next interval you can take
    return res = max(no_take, take + dp(i, discrete_binary_search<int>([&](int k) -> bool {
        return segs[k].second >= segs[j].first;
    }, 0, j) - 1));



}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    for (; test_no <= t; ++test_no) {
        cin >> n;
        segs.clear();
        segs.emplace_back(0, M);
        for (int i = 0; i < n; ++i) {
            int l, r;
            cin >> l >> r;
            segs.emplace_back(l, r);
        }
        sort(segs.begin(), segs.end(), [](pii s1, pii s2) -> bool {
            if (s1.second == s2.second) {
                return s1.first > s2.first;
            }
            return s1.second < s2.second;
        });
        cout << dp(n, n) - 1 << '\n';
    }
}