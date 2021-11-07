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

template <typename T>
using vv = vector<vector<T>>;

using vi = vector<int>;
using ii = array<int, 2>;
using vii = vector<ii>;
using vvi = vv<int>;

using vll = vector<ll>;
using l2 = array<int, 2>;
using vl2 = vector<l2>;
using vvll = vv<ll>;

template <typename T>
using minq = priority_queue<T, vector<T>, greater<T>>;
template <typename T>
using maxq = priority_queue<T>;

const ll M = 1000000007;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    for (int test_no = 0; test_no < t; ++test_no) {
        int n, x, y;
        cin >> n >> x >> y;
        vi b(n);
        int C = n + 2;
        vi c(C);
        for (int i = 0; i < n; ++i) {
            cin >> b[i];
            ++c[b[i]];
        }
        vii c_e;
        for (int i = 1; i < C; ++i) {
            if (!c[i]) continue;
            c_e.pb({c[i], i});
        }
        sort(all(c_e));
        int xx = x;
        for (int i = (int) c_e.size() - 1; i >= 0; --i) {
            int m = min(c_e[i][0], xx);
            c_e[i][0] -= m;
            xx -= m;
        }
        sort(all(c_e));
        if (c_e.back()[0] + )
    }
}