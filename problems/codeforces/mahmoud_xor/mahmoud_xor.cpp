#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template <typename K> using hset = gp_hash_table<K, null_type>;
template <typename K, typename V> using hmap = gp_hash_table<K, V>;


using namespace std;

using ll = long long;

using vi = vector<int>;
using vvi = vector<vector<int>>;

template <typename T>
using minq = priority_queue<T, vector<T>, greater<T>>;
template <typename T>
using maxq = priority_queue<T>;

ll M = 1000000007;

template<typename T>
T powmod(T b, T r, T m) {
    T out = 1;
    for (T t = 1; t <= r; t <<= 1) {
        if (r&t) out = (out*b)%m;
        b = (b*b)%m;
    }
    return out;
}


bool representable(int x, const vi & basis) {
    for (auto &it: basis)
        if ((x ^ it) < x) // if this is true then
            x ^= it;
    return x == 0;
}

void add(int x, vi & basis) {
    // make sure leading 1 of each "it" is unique
    for (auto &it: basis)
        if ((x ^ it) < x) // if this is true then
            x ^= it;
    if (x) {
        // make sure leading 1 of "x" is unique
        for (auto &it: basis)
            if ((x ^ it) < it)
                it ^= x;
        basis.push_back(x);
        sort(basis.begin(), basis.end());
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, q;
    cin >> n >> q;

    vi a(n);
    vi basis;
    vvi bases(n);

    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        add(a[i], basis);
        bases[i] = basis;
    }

    for (int i = 0; i < q; ++i) {
        int l, x;
        cin >> l >> x;
        if (representable(x, bases[l - 1])) {
            cout << powmod<ll>(2, l - bases[l - 1].size(), M) << '\n';
        } else {
            cout << 0 << '\n';
        }
    }

}