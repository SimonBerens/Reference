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

int n, k;

bool in_bounds(int l, int r, int j) {
    if (l <= r) {
        return l <= j && j <= r;
    } else {
        return j <= r || l <= j;
    }
}

struct modint {
    static ll M;
    static ll _reduce(ll n) {
        static ll b = -1ull/M;
        ll r = n-(ll)(__uint128_t(b)*n>>64)*M; return r >= M ? r-M : r;
    }

    static ll _pow(ll n, ll k) {
        ll r = 1;
        for (; k > 0; k >>= 1, n = _reduce(n*n))
            if (k&1) r = _reduce(r*n);
        return r;
    }

    ll v; modint(ll n = 0) : v(_reduce(n)) { v += (M&(0-(v<0))); }

    friend string to_string(const modint n) { return to_string(n.v); }
    friend istream& operator>>(istream& i, modint& n) { return i >> n.v; }
    friend ostream& operator<<(ostream& o, const modint n) { return o << n.v; }
    template<typename T> explicit operator T() { return T(v); }

    friend bool operator==(const modint n, const modint m) { return n.v == m.v; }
    friend bool operator!=(const modint n, const modint m) { return n.v != m.v; }
    friend bool operator<(const modint n, const modint m) { return n.v < m.v; }
    friend bool operator<=(const modint n, const modint m) { return n.v <= m.v; }
    friend bool operator>(const modint n, const modint m) { return n.v > m.v; }
    friend bool operator>=(const modint n, const modint m) { return n.v >= m.v; }

    modint& operator+=(const modint n) { v += n.v; v -= (M&(0-(v>=M))); return *this; }
    modint& operator-=(const modint n) { v -= n.v; v += (M&(0-(v<0))); return *this; }
    modint& operator*=(const modint n) { v = _reduce(v*n.v); return *this; }
    modint& operator/=(const modint n) { v = _reduce(v*_pow(n.v, M-2)); return *this; }
    friend modint operator+(const modint n, const modint m) { return modint(n) += m; }
    friend modint operator-(const modint n, const modint m) { return modint(n) -= m; }
    friend modint operator*(const modint n, const modint m) { return modint(n) *= m; }
    friend modint operator/(const modint n, const modint m) { return modint(n) /= m; }
    modint& operator++() { return *this += 1; }
    modint& operator--() { return *this -= 1; }
    modint operator++(int) { modint t = *this; return *this += 1, t; }
    modint operator--(int) { modint t = *this; return *this -= 1, t; }
    modint operator+() { return *this; }
    modint operator-() { return modint(0) -= *this; }

    // O(logk) modular exponentiation
    modint pow(const ll k) const {
        return k < 0 ? _pow(v, M-1-(-k%(M-1))) : _pow(v, k);
    }
    modint inv() const { return _pow(v, M-2); }
};

ll modint::M = 0;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> k;
    modint::M = n;
    vvi g(n);
    for (int i = 0; i < n; ++i) {
        while (true) {
            int x;
            cin >> x;
            if (x == 0) break;
            g[i].pb(x - 1);
        }
    }
    vv<vi> dp(n, vvi(n, vi(2)));
    for (int len = 1; len < n; ++len) {
        for (int l = 0; l < n; ++l) {
            int r = modint(l + len - 1).v;
            for (int i : g[l])
                if (in_bounds(l, r, i))
                    smax(dp[l][r][0], max(dp[modint(l + 1).v][i][1], dp[i][r][0]) + 1);
            for (int i : g[r])
                if (in_bounds(l, r, i))
                    smax(dp[l][r][1], max(dp[l][i][1], dp[i][modint(r - 1).v][0]) + 1);

        }
    }
    ii res{0, 0};
    for (int i = 0; i < n; ++i) {
        int l = i;
        for (int j : g[i]) {
            if (k) {
                int r = j;
                vi dp1(n);
                // we have intervals [l, r] and [r, l]
                for (int u = min(l, r); u <= max(l, r); ++u) {
                    for (int v : g[u]) {

                    }
                }
            } else {
                int r = modint(i - 1).v;
                ii cand{max(dp[modint(l  +1).v][j][1], dp[j][r][0]) + 1, i};
                smax(res, cand);
            }
        }
    }
    cout << res[0] << '\n' << res[1] + 1 << '\n';
}