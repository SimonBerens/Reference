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
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    const int BITS = 30;
    vi basis(BITS);
    int bs = 0;
    for (int q = 0; q < n; ++q) {
        int t, k;
        cin >> t >> k;
        if (t == 1) {
            for (int i = BITS - 1; i >= 0; --i) {
                if ((k & 1 << i) == 0) continue;
                if (!basis[i]) {
                    basis[i] = k;
                    ++bs;
                    break;
                }
                k ^= basis[i];
            }
        } else {
            int res = 0;
            int tot = 1 << bs;
            for (int i = BITS - 1; i >= 0; --i) {
                if (!basis[i]) continue;
                int low = tot / 2;
                if ((low < k && (res & 1 << i) == 0) || (low >= k && (res & 1 << i) > 0)) {
                    res ^= basis[i];
                }

                if (low < k) k -= low;

                tot /= 2;

            }
            cout << res << '\n';
        }
    }
}