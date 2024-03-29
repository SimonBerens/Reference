#include <functional>
#include <tuple>
#include <optional>
#include <variant>
#include <string>
#include <string_view>
#include <array>
#include <vector>
#include <deque>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <algorithm>
#include <valarray>
#include <random>
#include <numeric>
#include <iostream>
#include <cassert>
#include <sstream>

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

int main() {
    int N;
    cin >> N;
    vvi g(N, vi(N)), gt(N, vi(N));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> g[i][j];
            gt[j][i] = g[i][j];
        }
    }
    ll res = 0;
    for (auto &grid : {g, gt}) {
        ll temp_res = 0;
        for (int i = 0; i < N; ++i) {
            vi b1, b2;
            bool toggle = false;
            partition_copy(grid[i].begin(), grid[i].end(), back_inserter(b1), back_inserter(b2), [&toggle](int) { return toggle = !toggle; });
            temp_res += max(accumulate(b1.begin(), b1.end(), 0L), accumulate(b2.begin(), b2.end(), 0L));
        }
        res = max(res, temp_res);
    }
    cout << res << "\n";
}