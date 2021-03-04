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
#define EPS 1e-9


int main() {
    while (true) {
        int C;
        cin >> C;
        if (C == 0) {
            break;
        }
        map<string, int> m;
        int t = 0;
        for (int i = 0; i < C; ++i) {
            string cc;
            cin >> cc;
            m[cc] = t++;
        }
        vector<vector<double>> g(C, vector<double>(C, numeric_limits<double>::max()));
        int R;
        cin >> R;
        for (int i = 0; i < R; ++i) {
            string a, b;
            char c;
            int x, y;
            cin >> a >> b >> x >> c >> y;
            g[m[a]][m[b]] = -log((double) y / x);
        }

        for (int k = 0; k < C; ++k) {
            for (int i = 0; i < C; ++i) {
                for (int j = 0; j < C; ++j) {
                    g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
                }
            }
        }
        bool neg_cycle = false;
        for (int k = 0; k < C; ++k) {
            for (int i = 0; i < C; ++i) {
                for (int j = 0; j < C; ++j) {
                    if (g[i][j] - (g[i][k] + g[k][j]) > EPS) {
                        neg_cycle = true;
                    }
                }
            }
        }
        cout << (neg_cycle ? "Arbitrage" : "Ok") << "\n";
    }
}