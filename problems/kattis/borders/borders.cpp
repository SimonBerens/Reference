#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>

using namespace __gnu_pbds;
template<typename K> using hset = gp_hash_table<K, null_type>;
template<typename K, typename V> using hmap = gp_hash_table<K, V>;


using namespace std;

using ll = long long;

using vi = vector<int>;
using vvi = vector<vector<int>>;

template<typename T>
using minq = priority_queue<T, vector<T>, greater<T>>;
template<typename T>
using maxq = priority_queue<T>;

ll M = 1000000007;

struct BipartiteMatcher {
    vector<vector<int>> G;
    vector<int> L, R, Viz;

    BipartiteMatcher(int n, int m) :
            G(n), L(n, -1), R(m, -1), Viz(n) {}

    void AddEdge(int a, int b) {
        G[a].push_back(b);
    }

    bool Match(int node) {
        if (Viz[node])
            return false;
        Viz[node] = true;

        for (auto vec : G[node]) {
            if (R[vec] == -1) {
                L[node] = vec;
                R[vec] = node;
                return true;
            }
        }

        for (auto vec : G[node]) {
            if (Match(R[vec])) {
                L[node] = vec;
                R[vec] = node;
                return true;
            }
        }

        return false;
    }

    int Solve() {
        int ok = true;
        while (ok--) {
            fill(Viz.begin(), Viz.end(), 0);
            for (int i = 0; i < (int)L.size(); ++i)
                if (L[i] == -1)
                    ok |= Match(i);
        }

        int ret = 0;
        for (int i = 0; i < L.size(); ++i)
            ret += (L[i] != -1);
        return ret;
    }
};

vector<vector<char>> g;
vvi regions;
vi is_region_border;
vi region_type;

int n, m;

vvi seen;

void dfs(int r, int c, int region) {
    seen[r][c] = 1;
    regions[r][c] = region;
    for (auto[dr, dc]: vector<pair<int, int>>{{0,  1},
                                              {0,  -1},
                                              {1,  0},
                                              {-1, 0}}) {
        int nr = r + dr, nc = c + dc;
        if (!(nr >= 0 && nr < n && nc >= 0 && nc < m)) {
            is_region_border[region] = true;
        } else if (g[nr][nc] == g[r][c] && !seen[nr][nc]) {
            dfs(nr, nc, region);
        }
    }
}

int get_region_id(int r, int c) {
    return m * r + c;
}
//matching<100 * 100, 100 * 100> match;
BipartiteMatcher match(100 * 200, 100 * 200);



int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;
    g.assign(n, vector<char>(m));
    seen.assign(n, vi(m));
    regions.assign(n, vi(m));
    is_region_border.assign(n * m, false);
    region_type.assign(n * m, -1);

    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < m; ++c) {
            cin >> g[r][c];
        }
    }
    // paint regions + calculate cost + check if border
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < m; ++c) {
            if (!seen[r][c]) {
                region_type[get_region_id(r, c)] = g[r][c] - '0';
                dfs(r, c, get_region_id(r, c));
            }
        }
    }
    // add edges, don't care about border regions
    set<pair<int, int>> edges;
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < m - 1; ++c) {
            int r1 = regions[r][c], r2 = regions[r][c + 1];
            if (!is_region_border[r1] && !is_region_border[r2] && r1 != r2) {
                edges.emplace(min(r1, r2), max(r1, r2));
            }
        }
    }
    for (int c = 0; c < m; ++c) {
        for (int r = 0; r < n - 1; ++r) {
            int r1 = regions[r][c], r2 = regions[r + 1][c];
            if (!is_region_border[r1] && !is_region_border[r2] && r1 != r2) {
                edges.emplace(min(r1, r2), max(r1, r2));
            }
        }
    }
    for (auto [r1, r2] : edges) {
        if (region_type[r1] == 0) {
            match.AddEdge(r1, r2);
        } else {
            match.AddEdge(r2, r1);
        }
    }

    cout << match.Solve() + accumulate(is_region_border.begin(), is_region_border.end(), 0) << '\n';
}