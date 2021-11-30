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

template <typename T, typename C>
vector<pair<T, C>> groupby(const vector<T> & a) {
    vector<pair<T, C>> groups;
    for (const T & v : a) {
        if (groups.empty() || groups.back().first != v) {
            groups.pb({v, C{}});
        }
        ++groups.back().second;
    }
    return groups;
}

vi cnt(1e6 + 1, 0);

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        cnt[x]++;
    }
    for (int g = cnt.size() - 1; g >= 1; --g) {
        int dcnt = 0;
        for (int m = 1; g * m < cnt.size(); ++m) {
            dcnt += cnt[g * m];
        }
        if (dcnt >= 2) {
            cout << g << '\n';
            break;
        }
    }
}