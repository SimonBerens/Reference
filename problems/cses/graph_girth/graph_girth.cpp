#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>

using namespace __gnu_pbds;
template<typename K> using hset = gp_hash_table<K, null_type>;
template<typename K, typename V> using hmap = gp_hash_table<K, V>;


using namespace std;

#define all(x) (x).begin(), (x).end()
#define pb push_back
#define eb emplace_back
#define smax(x, y) (x = max(x, y))
#define smin(x, y) (x = min(x, y))

#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define F0R(i, a) FOR(i,0,a)
#define ROF(i, a, b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i, a) ROF(i,0,a)


using ll = long long;
using ld = long double;

template<typename T>
using vv = vector<vector<T>>;

using vi = vector<int>;
using ii = array<int, 2>;
using vii = vector<ii>;
using vvi = vv<int>;

using vll = vector<ll>;
using l2 = array<ll, 2>;
using vl2 = vector<l2>;
using vvll = vv<ll>;

template<typename T>
using minq = priority_queue<T, vector<T>, greater<T>>;
template<typename T>
using maxq = priority_queue<T>;

const ll M = 1000000007;
const ll infll = M * M;
int n, m;
vvi g;

int solve_from(int init) {
    int res = M;
    queue<ii> q;
    vi seen(n + 1), ds(n + 1, -1);
    q.push({0, init});
    seen[init] = true;
    while (!q.empty()) {
        auto[d, u] = q.front();
        q.pop();
        for (int v: g[u]) {
            if (seen[v]) {
                if (ds[v] >= d) smin(res, d + ds[v] + 1);
                continue;
            }
            q.push({d + 1, v});
            ds[v] = d + 1;
            seen[v] = true;
        }
    }
    return res;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    g.assign(n + 1, vi{});
    F0R(i, m) {
        int a, b;
        cin >> a >> b;
        g[a].pb(b);
        g[b].pb(a);
    }
    int res = M;
    FOR(i, 1, n + 1) {
        smin(res, solve_from(i));
    }
    cout << (res == M ? -1 : res) << '\n';
}