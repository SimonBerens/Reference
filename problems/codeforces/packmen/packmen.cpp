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

int n;
string s;

int main() {
    cin >> n;
    cin >> s;
    cout << discrete_binary_search<int>([](int t) -> bool {
        int x = s.find('*');
        int p = s.find('P');
        if (x < p) {
            x = p + t - 2 * (p - x)
        }
    }, 0, 200000);
}