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

using mi = modint<M - 7>;

int R, C, k;
using nodet = array<int, 3>;



#ifndef REFERENCE_UNION_FIND_H
#define REFERENCE_UNION_FIND_H

#include <vector>
#include <algorithm>
#include <unordered_map>

template<typename T>
class UnionFind {
public:

    UnionFind() : groups(0) {};

    bool add(const T &a) {
        if (to_elem.count(a) > 0) {
            return false;
        } else {
            to_elem[a] = elements.size();
            elements.push_back(elements.size());
            sizes.push_back(1);
            groups += 1;
            return true;
        }
    }

    template<typename Container>
    explicit UnionFind(const Container &l) : groups(0) {
        for (const auto &item : l)
            add(item);
    }

    UnionFind(const std::initializer_list<T>& l) : UnionFind<std::initializer_list<T>>(l) {}

    bool disjoint(const T &a, const T &b)  {
        return find_root(a) != find_root(b);
    }

    std::size_t group_size(const T &a)  {
        return sizes[find_root(a)];
    }

    void unify(const T &a, const T &b) {
        auto root_a = find_root(a), root_b = find_root(b);
        if (root_a != root_b) {
            --groups;
            if (sizes[root_b] > sizes[root_a])
                std::swap(root_a, root_b);
            elements[root_b] = elements[root_a];
            sizes[root_a] += sizes[root_b];
        }
    }
    std::map<T, std::size_t> to_elem;
    std::vector<std::size_t> elements;
    std::vector<std::size_t> sizes;
    size_t groups{};

    std::size_t find_root(const T &val) {
        std::size_t start = to_elem[val], cur;
        for (cur = start; cur != elements[cur]; cur = elements[cur]);
        std::size_t ret = cur;
        for (cur = start; cur != ret; cur = elements[cur])
            elements[cur] = ret;
        return ret;
    }
};

#endif //REFERENCE_UNION_FIND_H

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> R >> C >> k;
    UnionFind<nodet> dsu;
    for (int r = 1; r <= R; ++r) {
        dsu.add({r, 0, 0});
        dsu.add({r, 0, 1});
    }
    for (int c = 1; c <= C; ++c) {
        dsu.add({0, c, 0});
        dsu.add({0, c, 1});
    }
    for (int i = 0; i < k; ++i) {
        int r, c, color;
        cin >> r >> c >> color;
        if (color ^ ((r * c) % 2)) {
            dsu.unify({r, 0, 0}, {0, c, 1});
            dsu.unify({r, 0, 1}, {0, c, 0});
        } else {
            dsu.unify({r, 0, 0}, {0, c, 0});
            dsu.unify({r, 0, 1}, {0, c, 1});
        }
    }
    int cc = 0;
    bool poss = true;
    for (int r = 1; r <= R; ++r) {
        if (dsu.find_root({r, 0, 0}) == dsu.to_elem[{r, 0, 0}]) {
            ++cc;
        }
        if (!dsu.disjoint({r, 0, 0}, {r, 0, 1})) poss =false;
    }
    for (int c = 1; c <= C; ++c) {
        if (dsu.find_root({0, c, 0}) == dsu.to_elem[{0, c, 0}]) ++cc;
        if (!dsu.disjoint({0, c, 0}, {0, c, 1})) poss = false;
    }
    cout << (poss ? mi(2).pow(cc - 1) : 0) << '\n';
}