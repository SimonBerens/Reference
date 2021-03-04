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

vvi g;
vi seen;
int n, m;
vector<tuple<int, int, int>> tours;

bool dfs(int u, int p) {
    seen[u] = 1;
    vi new_tours;
    for (int nbr : g[u])
        if (nbr != p && (seen[nbr] == 1 || (seen[nbr] == 0 && !dfs(nbr, u))))
            new_tours.push_back(nbr);
    seen[u] = 2;
    bool used_p_edge = false;
    if (new_tours.size() % 2 == 1) {
        used_p_edge = true;
        new_tours.push_back(p);
    }
    for (int i = 0; i + 1 < new_tours.size(); i += 2)
        tours.emplace_back(new_tours[i], u, new_tours[i+1]);
    return used_p_edge;
}

int main() {
    cin >> n >> m;
    g.assign(n, vi());
    seen.assign(n, 0);
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        g[a - 1].push_back(b - 1);
        g[b - 1].push_back(a - 1);
    }
    for (int i = 0; i < n; ++i)
        if (seen[i] == 0 && dfs(i, -1))
            tours.pop_back();
    cout << tours.size() << "\n";
    for (auto[u, v, w] : tours)
        cout << u + 1 << " " << v + 1 << " " << w + 1 << "\n";
}