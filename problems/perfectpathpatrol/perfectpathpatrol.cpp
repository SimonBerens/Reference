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
using vvii = vector<vector<pair<int, int>>>;

#define all(x) (x).begin(), (x).end()

int main() {
    int N;
    cin >> N;
    vvi g(N), ps(N);
    for (int i = 0; i < N - 1; ++i) {
        int u, v, p;
        cin >> u >> v >> p;
        g[u].emplace_back(v);
        ps[u].emplace_back(p);
        g[v].emplace_back(u);
        ps[v].emplace_back(p);
    }
    ll patrols = 0;
    for (int i = 0; i < N; ++i) {
        ll s = accumulate(all(ps[i]), 0LL);
        ll m = *max_element(all(ps[i]));
        patrols += 2 * max(0LL, m - ((ll) ceil(s / 2.))) + s % 2;
    }
    cout << patrols / 2 << "\n";
}