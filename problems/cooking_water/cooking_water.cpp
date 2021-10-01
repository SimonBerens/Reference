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
    vector<pair<int, int>> v(N);
    for (int i = 0; i < N; ++i) {
        int a, b;
        cin >> a >> b;
        v[i] = {a, b};
    }
    auto [a, b] = v[0];
    for (int i = 1; i < N; ++i) {
        auto[c, d] = v[i];
        a = max(a, c);
        b = min(b, d);
        if (a > b) {
            cout << "edward is right\n";
            exit(0);
        }
    }
    cout << "gunilla has a point\n";
}