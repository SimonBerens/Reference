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

template<typename IN>
IN discrete_binary_search(function<bool(IN)> predicate, IN low = 0, IN high = numeric_limits<IN>::max()) {
    while (fabs(high - low) > 1e-4) {
        IN middle = low + (high - low) / 2; // todo std::midpoint in cpp 2020
        if (predicate(middle))
            high = middle;
        else low = middle;
    }
    return low;
}

vector<array<int, 3>> mice;

ld dist(ld x1, ld y1, ld x2, ld y2) {
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

ld dist(int i, int j) {
    return dist(mice[i][0], mice[i][1], mice[j][0], mice[j][1]);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    mice.assign(n, {});
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < 3; ++j) {
            cin >> mice[i][j];
        }
    }
    ld m;
    cin >> m;
    cout << fixed << setprecision(10) << discrete_binary_search<ld>([&](ld v) -> bool {
        // subset reachability
        // dp(S, i) -> time to end at i after visiting S\{i}
        // dp(S, i) = min dp(S\{i}, j) + dist(j, i) / (v * m ^ (popcount(S) - 1))
        vv<ld> dp(1 << n, vector<ld>(n, M));
        for (int i = 0; i < n; ++i) {
            ld cand = dist(mice[i][0], mice[i][1], 0, 0) / v;
            int t = mice[i][2];
            dp[1 << i][i] = cand > t ? M : cand;
        }
        for (int s = 0; s < (1 << n); ++s) {
            ld cv = v * pow(m, __builtin_popcount(s) - 1);
            for (int i = 0; i < n; ++i) {
                if (!(s & (1 << i))) continue;
                ld t = mice[i][2];
                for (int j = 0; j < n; ++j) {
                    if (j == i || !(s & (1 << j))) continue;
                    ld cand = dp[s ^ (1 << i)][j] + dist(i, j) / cv;
                    if (cand > t) cand = M;
                    smin(dp[s][i], cand);
                }
            }
        }
        return any_of(all(dp.back()), [&](ld x) -> bool {return x < M;});
    }, 0.0001, M) << '\n';

}