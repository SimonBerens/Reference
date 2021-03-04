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

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template <typename K> using hset = gp_hash_table<K, null_type>;
template <typename K, typename V> using hmap = gp_hash_table<K, V>;


using namespace std;

using ll = long long;

using vi = vector<int>;
using vvi = vector<vector<int>>;

vi seen;
hset<int> cur_seen;
vi topo;

int dfs(int cur, const vvi &graph) {
    int res = 1;
    seen[cur] = 1;
    cur_seen.insert(cur);
    for (int nbr: graph[cur]) {
        if (!seen[nbr]) {
            res &= dfs(nbr, graph);
        } else if (cur_seen.find(nbr) == cur_seen.end()) {
            res = 0;
        }
    }
    topo.push_back(cur);
    return res;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        vvi g(n + 1);
        vvi gt(n + 1);
        for (int i = 0; i < m; ++i) {
            int x, y;
            cin >> x >> y;
            g[x].push_back(y);
            gt[y].push_back(x);
        }

        seen.assign(n + 1, 0);
        cur_seen.clear();
        topo.clear();

        for (int dom = 1; dom <= n; ++dom) {
            if (!seen[dom]) {
                dfs(dom, g);
            }
        }
        seen.assign(n + 1, 0);
        cur_seen.clear();
        int res = 0;
        for (int i = n - 1; i >= 0; --i) {
            int dom = topo[i];
            if (!seen[dom]) {
                res += dfs(dom, gt);
                cur_seen.clear();
            }
        }
        cout << res << "\n";
    }
}