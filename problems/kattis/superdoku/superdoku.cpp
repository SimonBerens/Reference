//#include <bits/stdc++.h>
//
//#include <ext/pb_ds/assoc_container.hpp>
//using namespace __gnu_pbds;
//template <typename K> using hset = gp_hash_table<K, null_type>;
//template <typename K, typename V> using hmap = gp_hash_table<K, V>;

#include "vector"
#include "iostream"
#include "algorithm"
#include "queue"
#include "set"
#include "map"


using namespace std;

#define all(x) (x).begin(), (x).end()
#define pb push_back
#define eb emplace_back
#define smax(x, y) (x = max(x, y))
#define smin(x, y) (x = min(x, y))

using ll = long long;
using ld = long double;

template <typename T>
using vv = vector<vector<T>>;

using vi = vector<int>;
using ii = array<int, 2>;
using vii = vector<ii>;
using vvi = vv<int>;

using vll = vector<ll>;
using l2 = array<ll, 2>;
using vl2 = vector<l2>;
using vvll = vv<ll>;

template <typename T>
using minq = priority_queue<T, vector<T>, greater<T>>;
template <typename T>
using maxq = priority_queue<T>;

const ll M = 1000000007;


// N vertices, flow and cost are measured with type T
template<int N, typename T>
struct mincostflow {

    const T inf_T = numeric_limits<T>::max(), eps = 0; // set epsilon for non-integral types
    const bool CYCLIC = false; // false will usually make it run faster, but requires a DAG

    struct flow_edge { int v, u; T f, w, c; };
    vector<flow_edge> adj[N];
    T l[N], pot[N];
    int p[N], vis[N], s, t;
    priority_queue<pair<T, int>, vector<pair<T, int>>, greater<>> pq;

    // add an edge from i to j with capacity w and cost per unit flow c
    void edge(int i, int j, T w, T c, bool directed = true) {
        adj[i].push_back({j, int(adj[j].size()), 0, w, c});
        adj[j].push_back({i, int(adj[i].size())-1, 0, 0, -c});
        if (!directed) edge(j, i, w, c);
    }

    T dp(int v) {
        if (vis[v] || v == s) return pot[v];
        for (auto& e : adj[v])
            if (adj[e.v][e.u].w != 0)
                pot[v] = min(pot[v], dp(e.v)-e.c);
        return vis[v] = 1, pot[v];
    }

    bool dij() {
        fill(l, l+N, inf_T), pq.push({l[s] = 0, s});
        fill(vis, vis+N, 0);
        while (!pq.empty()) {
            auto [c, v] = pq.top(); pq.pop();
            if (vis[v]) continue; vis[v] = 1;
            for (auto& e : adj[v]) {
                T d = e.c+pot[v]-pot[e.v];
                if (l[v] != inf_T && e.f < e.w-eps && c+d < l[e.v]-eps)
                    p[e.v] = e.u, pq.push({l[e.v] = c+d, e.v});
            }
        }
        for (int i = 0; i < N; i++)
            if (l[i] != inf_T) pot[i] += l[i];
        return l[t] != inf_T;
    }

    bool spfa() {
        fill(l, l+N, inf_T), l[s] = 0;
        fill(vis, vis+N, 0);
        queue<int> q({s});
        while (!q.empty()) {
            int v = q.front(); q.pop();
            vis[v] = 0;
            for (auto& e : adj[v])
                if (l[v] != inf_T && e.f < e.w-eps && l[v]+e.c < l[e.v]-eps) {
                    l[e.v] = l[v]+e.c, p[e.v] = e.u;
                    if (!vis[e.v]) q.push(e.v), vis[e.v] = 1;
                }
        }
        return l[t] != inf_T;
    }

    // compute the maximum flow from s to t, and the minimum cost needed to do it, one-time use.
    // for cyclic graphs: SPFA + Edmonds-Karp, complexity is O(EV*min(EV, flow))
    // for DAGS: Dijkstra's w/ Johnson potentials + Edmonds-Karp, complexity is O(ElogE*min(EV, flow))
    // negative weight cycles will always break it
    pair<T, T> solve(int _s, int _t) {
        s = _s, t = _t; T f = 0, c = 0;
        fill(pot, pot+N, inf_T), pot[s] = 0;
        if (!CYCLIC) dp(t);
        while (CYCLIC ? spfa() : dij()) {
            T x = inf_T;
            for (int v = t; v != s; v = adj[v][p[v]].v) {
                auto& e = adj[v][p[v]];
                x = min(x, adj[e.v][e.u].w-adj[e.v][e.u].f);
            }
            for (int v = t; v != s; v = adj[v][p[v]].v) {
                auto& e = adj[v][p[v]];
                c -= e.c*x, e.f -= x, adj[e.v][e.u].f += x;
            }
            f += x;
        }
        return {f, c};
    }

    // after calling solve(), return a component vector C s.t. C[i] \in {0, 1}
    // and i is reachable from s iff C[i] = 1. any edge from a 1 to a 0 is in the min cut
    vector<bool> cut() {
        vector<bool> out(N, 0); out[s] = 1;
        queue<int> q({s});
        while (!q.empty()) {
            int v = q.front(); q.pop();
            for (auto& e : adj[v])
                if (e.f < e.w && !out[e.v])
                    out[e.v] = 1, q.push(e.v);
        }
        return out;
    }
};

int n, k;

int getvnode(int v) {
    return v - 1;
}

int getvrnode(int v, int r) {
    return 100 + 100 * (v-1) + r;
}

int getvrcnode(int v, int r, int c) {
    return 100 + 100 * 100 + 100 * 100 * (v-1) + 100 * r + c;
}

const int nodes = 1 + 1 + 100 + 100 * 100 + 100 * 100 * 100;

mincostflow<nodes, int> mcf;


int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> k;
    vvi g(k, vi(n));
    for (int i = 0; i < k; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> g[i][j];
        }
    }
    // s, t, vnodes (100), vrnodes (100 * 100), vrcnodes (100 * 100 * 100)
    int S = nodes - 2, T = nodes - 1;
    for (int r = 0; r < k; ++r) {
        set<int> vals;
        for (int c = 0; c < n; ++c) {
            if (vals.count(g[r][c]) == 1) {
                cout << "no\n";
                return 0;
            }
            vals.insert(g[r][c]);
        }
    }
    for (int v = 1; v <= n; ++v) {
        int vnode = getvnode(v);
        mcf.edge(S, vnode, n - k, 0);
        for (int r = k; r < n; ++r) {
            int vrnode = getvrnode(v, r);
            mcf.edge(vnode, vrnode, 1, 0);
        }
    }
    for (int c = 0; c < n; ++c) {
        set<int> vals;
        for (int i = 1; i <= n; ++i) {
            vals.insert(i);
        }
        for (int r = 0; r < k; ++r) {
            if (vals.count(g[r][c]) == 0) {
                cout << "no\n";
                return 0;
            }
            vals.erase(g[r][c]);
        }
        for (int v : vals) {
            for (int r = k; r < n; ++r) {
                //i, j, cap, cost
                int vrnode = getvrnode(v, r), vrcnode = getvrcnode(v, r, c);
                mcf.edge(vrnode, vrcnode, 1, 0);
                mcf.edge(vrcnode, T, 1, 0);
            }
        }
    }
    auto [f, c] = mcf.solve(S, T);
    if (f != n * (n - k)) {
        cout << "no\n";
        return 0;
    }
    cout << "yes\n";
    vvi out(n, vi(n));
    for (int r = 0; r < n - k; ++r) {
        for (int c = 0; c < n; ++c) {
            out[r][c] = g[r][c];
        }
    }
    for (auto & es : mcf.adj) {
        for (auto & e : es) {
            if (e.v == T && e.f == 1) {
                int u = e.u;
                u -=100 + 100 * 100;
                int v = u / (100 * 100) + 1;
                u /= 100 * 100;
                int r = u / 100;
                u /= 100;
                int c = u;
                out[r][c] = v;
            }
        }
    }
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < n; ++c) {
            cout << out[r][c] << ' ';
        }
        cout << '\n';
    }
}