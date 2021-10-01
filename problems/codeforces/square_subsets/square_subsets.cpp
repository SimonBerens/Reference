#include <functional>
#include <tuple>
#include <optional>
#include <variant>
#include <string>
#include <string_view>
#include <array>
#include <vector>
#include <deque>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <algorithm>
#include <valarray>
#include <random>
#include <numeric>
#include <iostream>
#include <cassert>
#include <sstream>

#include <ext/pb_ds/assoc_container.hpp>
#include <cstring>

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

vi ps{2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67}, ms(71), c(71);
ll M = 1000000007LL;

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
    int n;
    cin >> n;
    vi v(n);
    for (int i = 0; i < n; ++i) {
        cin >> v[i];
        c[v[i]]++;
    }

    for (int i = 2; i < 71; ++i) {
        int x = i;
        for (int j = 0; j < ps.size(); ++j) {
            while (x > 1 && x % ps[j] == 0) {
                x /= ps[j];
                ms[i] ^= 1 << j;
            }
        }
    }

    vector<ll> prev(1 << 20), dp(1 << 20);
    prev[0] = 1;
    ll ans = 1;

    for (int i = 0; i <= 70; ++i) {
        if (c[i] != 0) {
            ans *= powmod<ll>(2, c[i] - 1, M);
            ans %= M;
            for (int j = 0; j < 1 << 20; ++j) {
                dp[j] = (prev[j] % M + prev[j ^ ms[i]] % M) % M;
            }
            swap(prev, dp);
        }
    }

    cout << (ans * prev[0] - 1) % M << '\n';


}