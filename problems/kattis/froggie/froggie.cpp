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

int l, w;
vector<array<int, 3>> lanes;

bool good(int cl, int cx, ll t) {
    if (!(0 <= cx && cx < w)) return false;
    if (cl == -1) return true;
    auto [o, i, s] = lanes[cl];
    o = ((l - 1 - cl) %2 == 0) ? o : (w - 1 - o);
    s = ((l - 1 - cl) % 2 == 0) ? s : -s;
    ll k = floor((cx - t * s - o - 1) / (i + 0.));
    ll z = o + t * s + i * k;
    if ((cx - s) < z && z < cx) {
        return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> l >> w;
    lanes.assign(l, {});
    for (int i = 0; i < l; ++i) {
        for (int j = 0; j < 3; ++j) {
            cin >> lanes[i][j];
        }
    }
    reverse(all(lanes));
    int cx;
    string moves;
    cin >> cx >> moves;
    int cl = -1;
    int t = 0;
    for (char m : moves) {
        if (m == 'U') {
            cl += 1;
        } else if (m == 'D') {
            cl -= 1;
        } else if (m == 'L') {
            cx -= 1;
        } else if (m == 'R') {
            cx += 1;
        }
        if (cl == l) {
            cout << "safe\n";
            return 0;
        }
        if (!good(cl, cx, t)) {
            cout << "squish\n";
            return 0;
        }
        ++t;
    }
    cout << "squish\n";
}