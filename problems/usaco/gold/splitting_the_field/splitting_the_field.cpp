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

int main() {
    freopen("split.in", "r", stdin);
    freopen("split.out", "w", stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    vl2 cows(n);
    for (int i = 0; i < n; ++i) {
        cin >> cows[i][0] >> cows[i][1];
    }
    ll minarea = numeric_limits<ll>::max();
    ll totarea;
    for (int j = 0; j < 2; ++j) {
        for (auto &[x, y]: cows) {
            x *= -1;
            swap(x, y);
        }
        sort(all(cows));
        vll p;
        ll l = M, r = -M, t = -M, b = M;
        for (int i = 0; i < n; ++i) {
            ll X = cows[i][0];
            for (; i < n && cows[i][0] == X; ++i) {
                auto[x, y] = cows[i];
                smin(l, x);
                smax(r, x);
                smin(b, y);
                smax(t, y);
            }
            --i;
            p.pb((r - l) * (t - b));
        }
        vll s;
        l = M, r = -M, t = -M, b = M;
        for (int i = n - 1; i >= 0; --i) {
            ll X = cows[i][0];
            for (; i >= 0 && cows[i][0] == X; --i) {
                auto[x, y] = cows[i];
                smin(l, x);
                smax(r, x);
                smin(b, y);
                smax(t, y);
            }
            ++i;
            s.pb((r - l) * (t - b));
        }
        reverse(all(s));
        for (int i = 0; i < p.size() - 1; ++i) {
            smin(minarea, p[i] + s[i+1]);
        }
        totarea = s[0];
    }
    cout << totarea - minarea << '\n';
}