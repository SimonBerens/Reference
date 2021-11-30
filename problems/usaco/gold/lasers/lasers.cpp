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

vii dirs{{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

int main() {
    freopen("lasers.in", "r", stdin);
    freopen("lasers.out", "w", stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, xl, yl, xb, yb;
    cin >> n >> xl >> yl >> xb >> yb;
    map<int, vi> xm, ym;
    set<array<int, 4>> seen;
    F0R(i, n) {
        int x,y;
        cin >> x >> y;
        xm[x].pb(y);
        ym[y].pb(x);
    }
    xm[xl].pb(yl);
    ym[yl].pb(xl);
    xm[xb].pb(yb);
    ym[yb].pb(xb);
    for (auto &[x, v] : xm) sort(all(v));
    for (auto &[y, v]: ym) sort(all(v));
    deque<array<int, 5>> q; // m, x, y, dx, dy
    q.push_back({-1, xl, yl, 0, 0}); // need to subtract 1 for the original "change in direction"
    while (!q.empty()) {
        auto [m, x, y, dx, dy] = q.front(); q.pop_front();
        if (seen.count({x, y, dx, dy}) == 1) continue;
        seen.insert({x, y, dx, dy});
        if (x == xb && y == yb) {
            cout << m << '\n';
            return 0;
        }
        for (auto [dx1, dy1] : dirs) {
            if (dx1 == -dx && dy1 == -dy) continue;
            int nx, ny;
            if (dx1 == 0) {
                auto cur = lower_bound(all(xm[x]),y);
                if (cur == xm[x].begin() && dy1 == -1) continue;
                if (cur + dy1 == xm[x].end()) continue;
                nx = x;
                ny = *(cur + dy1);
            } else {
                auto cur = lower_bound(all(ym[y]), x);
                if (cur == ym[y].begin() && dx1 == -1) continue;
                if (cur + dx1 == ym[y].end()) continue;
                nx = *(cur + dx1);
                ny = y;
            }
            if (seen.count({nx, ny, dx1, dy1}) == 1) continue;

            if (dx1 == dx && dy1 == dy) {
                q.push_front({m, nx, ny, dx1, dy1});
            } else {
                q.push_back({m + 1, nx, ny, dx1, dy1});
            }
        }
    }
    cout << -1 << '\n';
}