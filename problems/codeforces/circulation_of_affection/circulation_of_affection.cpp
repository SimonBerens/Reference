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
    int n;
    cin >> n;
    string s;
    cin >> s;
    vvi res(26, vi(1501));
    for (int c = 0; c < 26; ++c) {
        for (int i = 0; i < n; ++i) {
            int non_c = 0;
            for (int j = i; j < n; ++j) {
                if (s[j] - 'a' != c) {
                    non_c += 1;
                }
                res[c][non_c] = max(res[c][non_c], j - i + 1);
            }
        }
    }
    for (int c = 0; c < 26; ++c) {
        for (int i = 1; i < 1501; ++i) {
            res[c][i] = max(res[c][i], res[c][i - 1]);
        }
    }
    int q;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        int m;
        char c;
        cin >> m >> c;
        cout << res[c - 'a'][m] << '\n';
    }
}