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

    freopen("reststops.in", "r", stdin);
    freopen("reststops.out", "w", stdout);

    int L, N, rf, rb;
    cin >> L >> N >> rf >> rb;
    vector<pair<int, int>> stops;
    for (int i = 0; i < N; ++i) {
        int x, c;
        cin >> x >> c;
        stops.emplace_back(x, c);
    }
    sort(stops.begin(), stops.end());
    vector<pair<int, int>> good_stops;
    for (auto [x, c] : stops) {
        while (!good_stops.empty() && good_stops.back().second <= c)
            good_stops.pop_back();
        good_stops.emplace_back(x, c);
    }
    ll last_x = 0, res = 0;
    for (auto [x, c] : good_stops) {
        res += (rf - rb) * (x - last_x) * c;
        last_x = x;
    }
    cout << res << "\n";

}