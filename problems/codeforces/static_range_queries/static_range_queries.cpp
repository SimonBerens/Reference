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
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, q;
    cin >> n >> q;
    map<int, int> upd;
    for (int i = 0; i < n; ++i) {
        int l, r, v;
        cin >> l >> r >> v;
        upd[l] += v;
        upd[r] -= v;
    }
    upd[M] = 0;
    upd[0] += 0;
    // create disjoint intervals of updates
    // map each interval to an element in an array
    // compute prefix sums on array
    // when answering a query, find interval i that query maps to
    // get sum from previous elements of array
    // multiply the update of interval i by the distance from the start of i
    // add that to the prefix sum
    vl2 vupd;
    ll rt = 0;
    for (auto [x, d]: upd) {
        rt += d;
        vupd.pb({x, rt});
//        cout <<x << ' ' << rt << '\n';
    }
//    cout << '\n';
    vll ps(1);
    map<l2, l2> cc; // map (upper, lower) -> array index, d
    for (int i = 0; i < vupd.size() - 1; ++i) {
        auto [x1, d] = vupd[i];
        auto [x2, _] = vupd[i+1];
        cc[{x2 - 1, x1}] = {i + 1, d};
        ps.pb(ps.back() + (x2 - x1) * d);
//        cout << ps.back() << '\n';
    }

    auto answer_prefix_query = [&](ll r) -> ll {
        auto [interval, psidx_d] = *cc.lower_bound({r, 0});
        auto [r1, l1] = interval;
        auto [psidx, d] = psidx_d;
//        if (r < l1) return 0;
//        cout << "query for r=" << r << '\n'
//            << "ps: " << ps[psidx - 1] << '\n'
//            << "l1: " << l1 << '\n'
//            << "r1: " << r1 << '\n'
//            << "dist: " << (r - l1 + 1) << '\n'
//            << "delta: " << d << "\n\n";
        return ps[psidx - 1] + (r - l1 + 1) * d;
    };

    for (int i = 0; i < q; ++i) {
        int l, r;
        cin >> l >> r;
        cout << answer_prefix_query(r-1) - answer_prefix_query(l - 1) << '\n';
    }
    // use ll for prefix sums

}