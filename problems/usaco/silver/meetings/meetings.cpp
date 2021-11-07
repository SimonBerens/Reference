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

int main() {
    freopen("meetings.in", "r", stdin);
    freopen("meetings.out", "w", stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, l;
    cin >> n >> l;
    vector<array<int, 3>> cows(n);
    int lcnt = 0;
    int tw = 0;
    for (int i = 0; i < n; ++i) {
        int w, x, d;
        cin >> w >> x >> d;
        cows[i] = {x, w, d};
        lcnt += d == -1;
        tw += w;
    }
    sort(all(cows));
    vvi ts(2);
    for (auto [x, w, d]: cows) {
        ts[(d + 1) / 2].pb(d == -1? x : l -x);
    }
    minq<ii> tq;
    for (int i = 0; i < n; ++i) {
        auto [x, w, _d] = cows[i];
        tq.push({ts[i >= lcnt][i < lcnt ? i : i - lcnt], w});
    }
    int sw = 0;
    int T;
    while (!tq.empty()) {
        auto [t, w] = tq.top(); tq.pop();
        sw += w;
        if (2 * sw >= tw) {
            T = t;
            break;
        }
    }
    ll res = 0;
    queue<ll> pos;
    for (auto [x, w, d] : cows) {
        while (!pos.empty() && pos.front() + 2 * T < x) {
            pos.pop();
        }
        if (d == 1) {
            pos.push(x);
        } else {
            res += pos.size();
        }
    }
    cout << res << '\n';
}