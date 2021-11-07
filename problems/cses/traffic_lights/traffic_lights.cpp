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
    int x, n;
    cin >> x >> n;
    // intervals via start -> len
    // map of len -> starts (set)
    map<int, int> startlen;
    map<int, set<int>, greater<>> lenstarts;
    startlen[1] = x - 1;
    lenstarts[x -1].insert(1);
    for (int i = 0; i < n; ++i) {
        int p;
        cin >> p;
        auto [start, len] = *(--startlen.upper_bound(p));
        lenstarts[len].erase(start);
        if (lenstarts[len].empty()) lenstarts.erase(len);
        startlen.erase(start);
        if (p - start > 0) {
            startlen[start] = p - start;
            lenstarts[p - start].insert(start);
        } if (start + len -1 - p > 0) {
            startlen[p + 1] = start + len -1 - p;
            lenstarts[start + len - 1 - p].insert(p + 1);
        }

        cout << lenstarts.begin()->first + 1 << ' ';
    }
}