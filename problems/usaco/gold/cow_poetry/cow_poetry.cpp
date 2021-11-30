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

template<ll M>
struct modint {

    static ll _reduce(ll n) {
        constexpr static ll b = -1ull/M;
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

using mi = modint<M>;

int main() {
    freopen("poetry.in", "r", stdin);
    freopen("poetry.out", "w", stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, m, k;
    cin >> n >> m >> k;
    vi s(n), c(n);
    vvi cti(n + 1);
    for (int i = 0; i < n; ++i) {
        cin >> s[i] >> c[i];
        cti[c[i]].pb(i);
    }
    map<char, int> chrcnt;
    for (int i = 0; i < m; ++i) {
        char e;
        cin >> e;
        chrcnt[e]++;
    }
    // first, calculate how many ways there are to make a line ending with class ci O(NK)
        // # of words of class ci * # of ways to make a line of length l - si
            // ldp(l) = sum(ldp(l - si) for i in range(n) if l - si >= 0)
            // ldp(0) = 1
    // now, for each letter we need to assign it to a rhyme class O(26Nlog(10**9))
        // choose a rhyme class
        // make cnt lines from that class
        // sum(ways[rc] ** cnt for rc in rcs)
    vector<mi> cnt_line_w_end_(n + 1);
    vector<mi> cnt_line_w_len_(k + 1);
    cnt_line_w_len_[0] = 1;

    for (int len = 0; len <= k; ++len) {
        for (int i = 0; i < n; ++i) {
            if (len - s[i] >= 0) cnt_line_w_len_[len] += cnt_line_w_len_[len - s[i]];
        }
    }
    for (int rc = 1; rc <= n; ++rc) {
        for (int i : cti[rc]) {
            cnt_line_w_end_[rc] += cnt_line_w_len_[k - s[i]];
        }
    }
    mi res(1);
    for (auto [chr, cnt] : chrcnt) {
        mi x;
        for (int rc = 1; rc <= n; ++rc) {
            x += cnt_line_w_end_[rc].pow(cnt);
        }
        res *= x;
    }
    cout << res << '\n';
}