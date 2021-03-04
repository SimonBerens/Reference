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


struct scc {

    vector<vector<int>> adj, c_adj, r_adj;
    vector<int> c, v, ord;

    scc(vector<vector<int>> _adj) : adj(_adj) {}

    void dfs(int i) {
        v[i] = 1;
        for (int j : adj[i])
            if (!v[j]) dfs(j);
        ord.push_back(i);
    }

    void partition(int i, int t) {
        v[i] = 1, c[i] = t;
        for (int j : r_adj[i])
            if (!v[j]) partition(j, t);
    }

    // returns a component vector c s.t. c[i] == c[j] iff i and j
    // are in the same strongly connected component, runs in O(E).
    vector<int> components() {
        int n = adj.size(), t = 0;
        v.assign(n, 0), r_adj.resize(n);
        for (int i = 0; i < n; i++) {
            for (int j : adj[i]) r_adj[j].push_back(i);
            if (!v[i]) dfs(i);
        }
        v.assign(n, 0), c.assign(n, 0);
        for (int i = n - 1; i >= 0; i--)
            if (!v[ord[i]]) partition(ord[i], t++);
        return c;
    }

    // returns an adjacency list over the scc's where an edge u->v means there is
    // some edge i->j in the original graph s.t. c[i] = u && c[j] = v, runs in O(E).
    vector<vector<int>> dag() {
        if (c.empty()) components();
        c_adj.resize(*max_element(c.begin(), c.end()) + 1);
        for (int i = 0; i < adj.size(); i++)
            for (int j : adj[i])
                if (c[i] != c[j]) c_adj[c[i]].push_back(c[j]);
        return c_adj;
    }
};

int main() {
    int t;
    cin >> t;
    for (int test_no = 0; test_no < t; ++test_no) {
        int n, m;
        cin >> n >> m;
        vvi g(n);
        for (int i = 0; i < m; ++i) {
            int s1, s2;
            cin >> s1 >> s2;
            g[s1-1].push_back(s2-1);
        }
        scc s(g);
        s.dag();
        vvi c_adjt(s.c_adj.size());
        for (int i = 0; i < s.c_adj.size(); ++i) {
            for (int nbr : s.c_adj[i]) {
                c_adjt[nbr].push_back(i);
            }
        }
        int in0 = 0, out0 = 0;
        if (s.c_adj.size() > 1) {
            for (int i = 0; i < s.c_adj.size(); ++i) {
                if (s.c_adj[i].empty()) {
                    out0 += 1;
                }
                if (c_adjt[i].empty()) {
                    in0 += 1;
                }
            }
        }

        cout << max(in0, out0) << "\n";
    }
}