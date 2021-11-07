#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template <typename K> using hset = gp_hash_table<K, null_type>;
template <typename K, typename V> using hmap = gp_hash_table<K, V>;


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

using edge = tuple<int, long double>;
vv<edge> g;
vi isend;

int start_node, start_dist;

void solve() {
    maxq<tuple<long double, int>> q; // space, node
    q.push({start_dist, start_node});
    vi vis(g.size());
    while (!q.empty()) {
        auto [space, u] = q.top(); q.pop();
        if (vis[u]) continue;
        vis[u] = true;
        if (isend[u]) {
            cout << fixed << setprecision(10) << space << '\n';
            return;
        }
        for (auto [v, w]: g[u]) {
            if (!vis[v]) {
                q.push({min(space, w), v});
            }
        }
    }
    cout << "Impossible\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, m, r;
    cin >> n >> m >> r;
    vv<ii> cars(n), gaps(n);
    int acmlen, acmback;
    cin >> acmlen >> acmlen >> acmback;
    for (int i = 0; i < m - 1; ++i) {
        int lane, len, back;
        cin >> lane >> len >> back;
        cars[lane].pb({back + len, back});
    }
    int gapcnt = 0;
    map<array<int, 3>, int> gapmap;
    for (int lane = 0; lane < n; ++lane) {
        cars[lane].pb({0, -1});
        cars[lane].pb({r + 1, r});
        sort(all(cars[lane]));
        for (int i = 0; i < cars[lane].size() - 1; ++i) {
            auto[f1, b1] = cars[lane][i];
            auto[f2, b2] = cars[lane][i+1];
            gapmap[{b2, f1, lane}] = gapcnt++;
            gaps[lane].pb({b2, f1});
        }
    }
    g.assign(gapcnt, vector<edge>{});
    isend.assign(gapcnt, false);
    for (auto[f, b]: gaps[0]){
        if (b <= acmback && acmback + acmlen <= f) {
            start_node = gapmap[{f, b, 0}];
            start_dist = min(acmback - b, f - (acmback + acmlen));
            break;
        }
    }
    for (auto[f, b]: gaps.back()) {
        isend[gapmap[{f, b, n - 1}]] = true;
    }
    for (int lane = 0; lane + 1 < n; ++lane) {
        // add edges to g
        for (auto[f1, b1]: gaps[lane]) {
            for (auto[f2, b2]: gaps[lane + 1]) {
                int insctsz = min(f1, f2) - max(b1, b2);
                if (insctsz >= acmlen) {
                    long double space = (insctsz - acmlen) / 2.l;
                    int g1 = gapmap[{f1, b1, lane}], g2 = gapmap[{f2, b2, lane + 1}];
                    g[g1].pb({g2, space});
                    g[g2].pb({g1, space});
                }
            }
        }
    }
    solve();
}