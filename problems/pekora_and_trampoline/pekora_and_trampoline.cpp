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
    int t;
    cin >> t;
    for (int test_no = 0; test_no < t; ++test_no) {
        ll res = 0, ps = 0, n, s;
        cin >> n;
        vi p(n + 2);
        for (int i = 0; i < n; ++i) {
            cin >> s;
            ps += p[i];
            res += max(0LL, s - ps - 1);
            int rem = max(0LL, ps - s + 1);
            p[i + 1] += rem;
            p[i + 2] += 1 - rem;
            --p[min(i + s + 1, n)];
        }
        cout << res << "\n";
    }
}