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

template<typename T, int H, int W>
struct matrix {

    T M[H][W];
    matrix(const T k = 0) { ident(k); }
    matrix(initializer_list<initializer_list<T>> v) : matrix() {
        for (int i = 0; i < v.size(); i++)
            copy(v.begin()[i].begin(), v.begin()[i].end(), M[i]);
    }

    T* operator[](const int i) { return M[i]; }
    const T* operator[](const int i) const { return M[i]; }

    void clear() { fill(&M[0][0], &M[0][0]+sizeof(M)/sizeof(T), 0); }
    void ident(const T k = 1) {
        clear(); for (int i = 0; i < min(H, W); i++) M[i][i] = k;
    }

    friend string to_string(const matrix& a) {
        string s = "";
        for (int i = 0; i < H; i++) {
            s += (i == 0 ? "[" : ", ");
            for (int j = 0; j < W; j++)
                s += (j == 0 ? "[" : ", ")+to_string(a.M[i][j]);
            s += "]";
        } return s+"]";
    }
    friend ostream& operator<<(ostream& o, const matrix<T, H, W>& a) {
        return o << to_string(a);
    }

    matrix& operator*=(const T& r) {
        for (int i = 0; i < H; i++) for (int j = 0; j < W; j++)
                M[i][j] *= r;
        return *this;
    }
    matrix& operator/=(const T& r) {
        for (int i = 0; i < H; i++) for (int j = 0; j < W; j++)
                M[i][j] /= r;
        return *this;
    }
    matrix operator*(const T& r) const { return matrix(*this) *= r; }
    matrix operator/(const T& r) const { return matrix(*this) /= r; }
    friend matrix operator*(const T& r, const matrix& a) {
        return matrix(a) *= r;
    }

    matrix& operator+=(const matrix& a) {
        for (int i = 0; i < H; i++) for (int j = 0; j < W; j++)
                M[i][j] += a.M[i][j];
        return *this;
    }
    template<int C> matrix<T, H, C> operator*(const matrix<T, W, C>& b) {
        matrix<T, H, C> r(0);
        for (int i = 0; i < H; i++) for (int j = 0; j < C; j++)
                for (int k = 0; k < W; k++) r.M[i][j] += M[i][k]*b.M[k][j];
        return r;
    }

    matrix& operator*=(const matrix& b) { return *this = *this*b; }
    matrix operator+(const matrix& b) { return matrix(*this) += b; }
    matrix operator-(const matrix& b) { return matrix(*this) += -b; }
    matrix operator+() { return matrix(*this); }
    matrix operator-() { return matrix(*this) *= -1; }

    matrix transpose() const {
        matrix r(0);
        for (int i = 0; i < H; i++) for (int j = 0; j < W; j++)
                r.M[i][j] = M[j][i];
        return r;
    }

    // O(n^3logk) matrix exponentiation
    matrix pow(long long k) {
        matrix a(1), r(*this);
        for (long long i = 1; i <= k; i <<= 1) {
            if (i&k) a *= r;
            r *= r;
        }
        return a;
    }

    // O(n^3) matrix determinant, uses operator/
    T det() const {
        matrix r(*this); T d = 1;
        for (int i = 0; i < H; i++) {
            if (r.M[i][i] == 0) for (int j = i+1; j < H; j++) if (r.M[j][i] != 0)
                    { swap(r.M[i], r.M[j]); d = 0-d; break; }
            d *= r.M[i][i]; if (r.M[i][i] == 0) return 0;
            for (int j = i+1; j < H; j++) { T c = r.M[j][i]/r.M[i][i];
                for (int k = i; k < H; k++) r.M[j][k] -= r.M[i][k]*c;
            } } return d;
    }

    // O(n^3) matrix inversion, uses operator/, undefined behavior if det(*this) == 0
    matrix inv() const {
        matrix b(1), r(*this);
        for (int i = 0; i < H; i++) {
            if (r.M[i][i] == 0) for (int j = i+1; j < H; j++) if (r.M[j][i] != 0)
                    { swap(b.M[i], b.M[j]), swap(r.M[i], r.M[j]); break; }
            for (int j = i+1; j < H; j++) { T c = r.M[j][i]/r.M[i][i];
                for (int k = 0; k < H; k++)
                    b.M[j][k] -= b.M[i][k]*c, r.M[j][k] -= r.M[i][k]*c;
            } }
        for (int i = H-1; i >= 0; i--) { T c = 1/r.M[i][i];
            for (int j = 0; j < H; j++) b.M[i][j] *= c, r.M[i][j] *= c;
            for (int j = 0; j < i; j++) { c = r.M[j][i];
                for (int k = 0; k < H; k++) b.M[j][k] -= b.M[i][k]*c;
            } } return b;
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    string s;
    cin >> s;
    int q;
    cin >> q;
    vii queries(q);
    for (int i = 0; i < q; ++i) {
        cin >> queries[i][0] >> queries[i][1];
    }
    const int dim = 10;
    using mat = matrix<modint<M>, dim, dim>;
    vector<mat> pmat{mat(1)}, pimat{mat(1)};

    for (int i = 0; i < s.size(); ++i) {
        mat trans(1);
        int e = s[i] - 'a';
        for (int j = 0; j < dim; ++j) {
            trans[e][j] = 1;
        }
        pmat.pb(trans * pmat.back());
        pimat.pb(pmat.back().inv());
    }

    for (auto [l, r] : queries) {

        auto start = matrix<modint<M>, dim, 1>{};
        start[dim-1][0] = 1;

        auto end = pmat[r] * pimat[l - 1] * start;
        modint<M> ans;
        for (int i = 0; i < dim - 1; ++i) {
            ans += end[i][0];
        }
        cout << ans << '\n';
    }
}