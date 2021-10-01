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

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    for (int test_no = 0; test_no < t; ++test_no) {
        int a, b, c, m;
        cin >> a >> b >> c >> m;
        vi vs{a, b, c};
        sort(vs.begin(), vs.end());
        if (m < max(vs[2] - 1 - (vs[0] + vs[1]), 0) || m > max(a - 1, 0) + max(b - 1, 0) + max(c - 1, 0)) {
            cout << "NO\n";
        } else {
            cout << "YES\n";
        }

    }
}