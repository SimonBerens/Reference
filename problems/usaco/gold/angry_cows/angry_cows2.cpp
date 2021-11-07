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
    freopen("angry.in", "r", stdin);
    freopen("angry.out", "w", stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    vll bales(n);
    for (int i = 0; i < n; ++i) {
        cin >> bales[i];
        bales[i] *= 2;
    }
    sort(all(bales));
    vll dpl(n);
    ll prev = bales[0];
    ll r = 0;
    for (int i = 1; i < n; ++i) {
        if (prev + r < bales[i]) {
            r = max(r + 2, bales[i] - bales[i-1]);
            prev = bales[i-1];
        }
        dpl[i] = r;
    }
    vll dpr(n);
    prev = bales.back();
    r = 0;
    for (int i = n - 2; i>=0; --i) {
        if (bales[i] + r < prev) {
            r = max(r + 2, bales[i+1] - bales[i]);
            prev = bales[i+1];
        }
        dpr[i] = r;
    }
    int i = 0, j = n - 1;
    ll res = 1e15;
    while (i < j) {
        smin(res, max({dpl[i] + 2, dpr[j] + 2, (bales[j] - bales[i])/2}));
        if (dpl[i + 1] > dpr[j - 1]) {
            --j;
        } else {
            ++i;
        }
    }
    cout << fixed << setprecision(1) << res / 2. << '\n';
}