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

template<typename IN>
IN discrete_binary_search(function<bool(IN)> predicate, IN low = 0, IN high = numeric_limits<IN>::max()) {
    while (low < high) {
        IN middle = low + (high - low) / 2; // todo std::midpoint in cpp 2020
        if (predicate(middle))
            high = middle;
        else low = middle + 1;
    }
    return low;
}

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
    int n, s;
    cin >> n >> s;
    vv<char> g(n, vector<char>(n));
    int mr, mc, dr, dc;
    vii hives;
    F0R(i, n) {
        F0R(j, n) {
            char x;
            cin >> x;
            g[i][j] = x;
            if (x == 'M') {
                mr = i;
                mc = j;
            } else if (x == 'H') {
                hives.pb({i, j});
            } else if (x == 'D') {
                dr = i;
                dc = j;
            }
        }
    }
    vvi beetime(n, vi(n, M));
    queue<ii> bees;
    for (auto [r, c] : hives) {
        bees.push({r, c});
        beetime[r][c] = 0;
    }

    F0R(t, n * n) {
        queue<ii> nextbees;
        while (!bees.empty()) {
            assert(bees.size() < n * n);
            auto [r, c] = bees.front(); bees.pop();
            for (auto [nr, nc] : adjc(r, c)) {
                if (0 <= nr && nr < n && 0 <= nc && nc < n && beetime[nr][nc] == M && (g[nr][nc] == 'G' || g[nr][nc] == 'M')) {
                    nextbees.push({nr, nc});
                    beetime[nr][nc] = t + 1;
                }
            }
        }
        swap(bees, nextbees);
    }

    cout << discrete_binary_search<int>([&](int startt) -> bool {
        vvi seen(n, vi(n));
        queue<ii> bear;
        bear.push({mr, mc});
        seen[mr][mc] = 1;
        if (beetime[mr][mc] <= startt) return true;
        FOR(t, startt, n * n) {
            F0R(_, s) {
                queue<ii> nextbear;
                while (!bear.empty()) {
                    auto [r, c] = bear.front(); bear.pop();
                    if (r == dr && c == dc) return false;
                    if (beetime[r][c] == t) continue;
                    for (auto [nr, nc] : adjc(r, c)) {
                        if (0 <= nr && nr < n && 0 <= nc && nc < n && (g[nr][nc] == 'G' || g[nr][nc] == 'D') && seen[nr][nc] == 0 && beetime[nr][nc] > t) {
                            nextbear.push({nr, nc});
                            seen[nr][nc] = 1;
                        }
                    }
                }
                swap(bear, nextbear);
                if (bear.empty()) return true;
            }
        }
        return true;

    }, 0, n * n) - 1 << '\n';
}