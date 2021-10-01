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
    int n;
    cin >> n;
    string s;
    cin >> s;
    vi a(n + 1);
    for (int i = 0; i < n + 1; ++i) {
        cin >> a[i];
    }

    int k = 100000000;
    for (int i = 0; i < n; ++i) {
        k = min(k, abs(a[i] - a[i + 1]));
    }

    vvi res(k);
    for (int i = 0; i < n + 1; ++i) {
        for (int j = 0; j < k; ++j) {
            res[j].push_back((a[i] + j) / k);
        }
    }

    cout << k << '\n';
    for (int i = 0; i < k; ++i) {
        for (int j = 0; j < n + 1; ++j) {
            cout << res[i][j] << ' ';
        }
        cout << '\n';
    }

}