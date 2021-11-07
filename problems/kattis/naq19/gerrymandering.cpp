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
    int P, D;
    cin >> P >> D;
    vvi dtp(D);
    vii pab(P);
    ll v = 0;
    for (int i = 0; i < P; ++i) {
        int d;
        cin >> d >> pab[i][0] >> pab[i][1];
        dtp[d - 1].pb(i);
    }
    ll twa = 0, twb = 0;
    for (int d = 0; d < D; ++d) {
        ll ta = 0, tb = 0;
        for (int p: dtp[d]) {
            ta += pab[p][0];
            tb += pab[p][1];
        }
        v += ta + tb;
        ll wa, wb;
        if (ta > tb) {
            wa = ta - ((ta + tb) / 2 + 1);
            wb = tb;
            cout << "A " << wa << ' ' << wb << '\n';
        } else {
            wa = ta;
            wb = tb - ((ta + tb) / 2 + 1);
            cout << "B " << wa << ' ' << wb << '\n';
        }
        twa += wa;
        twb += wb;
    }
    cout << fabs(twa - twb) / v << '\n';
}