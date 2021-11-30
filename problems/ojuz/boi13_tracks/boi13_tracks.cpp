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

vii adjc(int x, int y) {
    vii res;
    for (auto [dx, dy] : dirs)
        res.pb({x + dx, y + dy});
    return res;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int h, w;
    cin >> h >> w;
    vector<string> g(h);
    F0R(r, h) {
        cin >> g[r];
    }
    int res = 0;
    int p = '.';
    deque<ii> q; // r, c
    q.push_front({0, 0});
    vvi seen(h, vi(w));
    seen[0][0] = 1;
    while (!q.empty()) {
        assert(q.size() <= h * w);
        auto [r, c] = q.front(); q.pop_front();
        if (g[r][c] != p) res++;
        p = g[r][c];
        for (auto [nr, nc] : adjc(r, c)) {
            if (0 <= nr && nr < h && 0 <= nc && nc < w && seen[nr][nc] == 0 && g[nr][nc] != '.') {
                if (g[nr][nc] == p) q.push_front({nr, nc});
                else q.push_back({nr, nc});
                seen[nr][nc] = 1;
            }
        }
    }
    cout << res << '\n';

}