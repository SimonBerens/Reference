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


int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    vvi g(n, vi(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            char c;
            cin >> c;
            g[i][j] = c == 'W';
        }
    }
    vvi goal(n, vi(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            char c;
            cin >> c;
            goal[i][j] = c == 'W';
        }
    }

    int res = 0;
    for (int i = 0; i < pow(3, n); ++i) {
        for (int j = 0; j < pow(3, m); ++j) {
            int cur = 0;
            for (int r = 0; r < n; ++r) {
                for (int c = 0; c < m; ++c) {
                    int x = ((i / (int) pow(3, r)) % 3);
                    int y = ((j / (int) pow(3, c)) % 3);
                    if (y == 0) {
                        if (x == 0) {
                            cur += g[r][c] == goal[r][c];
                        } else {
                            cur += (x-1) == goal[r][c];
                        }
                    } else {
                        cur += (y-1) == goal[r][c];
                    }
                }
            }
            res = max(res, cur);
        }
    }

    cout << res << '\n';
}