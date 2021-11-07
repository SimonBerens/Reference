#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template <typename K> using hset = gp_hash_table<K, null_type>;
template <typename K, typename V> using hmap = gp_hash_table<K, V>;


using namespace std;

#define all(x) (x).begin(), (x).end()
#define pb push_back
#define eb push_back
#define smax(x, y) (x = max(x, y))
#define smin(x, y) (x = min(x, y))

using ll = long long;

template <typename T>
using vv = vector<vector<T>>;

using vi = vector<int>;
using ii = array<int, 2>;
using vii = vector<ii>;
using vvi = vv<int>;

using vll = vector<ll>;
using l2 = array<int, 2>;
using vl2 = vector<l2>;
using vvl2 = vv<l2>;

template <typename T>
using minq = priority_queue<T, vector<T>, greater<T>>;
template <typename T>
using maxq = priority_queue<T>;

const ll M = 1000000007;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int a;
    cin >> a;
    string s;
    cin >> s;
    vi delts;
    for (int i = 0; i < s.size(); ++i) {
        delts.push_back(s[i] == 'M' ? 1 : -1);
    }
    delts.push_back(M);
    int d = 0;
    for (int i = 0; i < delts.size() - 1; ++i) {
        if (abs(d + delts[i]) > abs(d + delts[i+1])) {
            swap(delts[i], delts[i+1]);
        }
        d += delts[i];
        if (abs(d) > a) {
            cout << i << '\n';
            return 0;
        }
    }
    cout << delts.size() - 1 << '\n';
}