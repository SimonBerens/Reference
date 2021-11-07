#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template <typename K> using hset = gp_hash_table<K, null_type>;
template <typename K, typename V> using hmap = gp_hash_table<K, V>;


using namespace std;

#define all(x) (x).begin(), (x).end()
#define pb push_back
#define eb push_back
#define smax(x, y) (x = max(x, y))
#define smin(x, y) (x = min(x, y))

using ll = long long;

template <typename T>
using vv = vector<vector<T>>;

using vi = vector<int>;
using ii = array<int, 2>;
using vii = vector<ii>;
using vvi = vv<int>;

using vll = vector<ll>;
using l2 = array<int, 2>;
using vl2 = vector<l2>;
using vvl2 = vv<l2>;

template <typename T>
using minq = priority_queue<T, vector<T>, greater<T>>;
template <typename T>
using maxq = priority_queue<T>;

const ll M = 1000000007;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n;
    double l, w;
    while (cin >> n >> l >> w) {
        vector<array<double, 2>> intervals;
        for (int i = 0; i < n; ++i) {
            double x, r;
            cin >> x >> r;
            double xi = sqrt(r * r - w * w / 4);
            if (r <= w / 2 || x + xi <= 0) continue;
            intervals.pb({x - xi, x + xi});
        }
        sort(all(intervals));
        double e1 = -M, e2 = 0;
        int res = 0;
        for (auto [s, e] : intervals) {
            if (s > e1) {
                if (s > e2) break;
                res += 1;
                e1 = e2;
            }
            smax(e2, e);
            if (e2 >= l) break;
        }
        cout << (e2 < l ? -1 : res) << '\n';
    }
}