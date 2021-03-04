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
    freopen("evolution.in", "r", stdin);
    freopen("evolution.out", "w", stdout);

    int N;
    cin >> N;
    hmap<string, set<int>> trait_to_pops;
    for (int i = 0; i < N; ++i) {
        int k;
        cin >> k;
        for (int j = 0; j < k; ++j) {
            string s;
            cin >> s;
            trait_to_pops[s].insert(i);
        }
    }
    for (auto & [k, v] : trait_to_pops) {
        for (auto & [k2, v2] : trait_to_pops) {
            vi out;
            set_intersection(v.begin(), v.end(), v2.begin(), v2.end(), back_inserter(out));
            ll s = out.size();
            if (s != 0 && s != v.size() && s != v2.size()) {
                cout << "no\n";
                exit(0);
            }
        }
    }
    cout << "yes\n";
}