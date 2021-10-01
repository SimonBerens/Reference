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

vi primes{2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67};

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

template<typename T>
T powmod(T b, T r, T m) {
    T out = 1;
    for (T t = 1; t <= r; t <<= 1) {
        if (r&t) out = (out*b)%m;
        b = (b*b)%m;
    }
    return out;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    vi a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    vi ma(n);
    for (int i = 0; i < n; ++i) {
        int num = a[i];
        for (int j = 0; j < primes.size(); ++j) {
            while (num > 1 && num % primes[j] == 0) {
                num /= primes[j];
                ma[i] ^= 1 << j;
            }
        }
    }

    vi basis;

    for (const auto &prime_mask: ma) {
        add(prime_mask, basis);
    }

    cout << powmod<ll>(2, n - basis.size(), M) -1 << '\n';

}