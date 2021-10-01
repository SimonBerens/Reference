#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>

using namespace __gnu_pbds;
template<typename K> using hset = gp_hash_table<K, null_type>;
template<typename K, typename V> using hmap = gp_hash_table<K, V>;


using namespace std;

using ll = long long;

using vi = vector<int>;
using vvi = vector<vector<int>>;

template<typename T>
using minq = priority_queue<T, vector<T>, greater<T>>;
template<typename T>
using maxq = priority_queue<T>;

ll M = 1000000007;

int tc, C;

vector<tuple<int, int, int>> things{{-8, 0,  0},
                                    {-3, -1, 0},
                                    {2,  0,  -1},
                                    {-3, 1,  -1},
                                    {2,  -2, 0}};

int dpa[151][151][51];

void init() {
    fill(dpa[0][0] + 0, dpa[150][150] + 51, -1);
}

int dp(int c, int n5, int n10) {
    if (c == 0) return 0;

    int &res = dpa[c][n5][n10];

    if (res != -1) {
        return res;
    }

    res = M;

    int n1 = tc - (C - c) * 8 - n5 * 5 - n10 * 10;
    for (const auto[x, y, z]: things) {
        if (n1 >= -x && n5 >= -y && n10 >= -z) {
            res = min(res, dp(c - 1, n5 + y, n10 + z) + max(0, -x) + max(0, -y) + max(0, -z));
        }
    }
    return res;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    for (int test_no = 0; test_no < t; ++test_no) {
        int n1, n5, n10;
        cin >> C >> n1 >> n5 >> n10;
        tc = n1 + n5 * 5 + n10 * 10;
        init();
        cout << dp(C, n5, n10) << '\n';
    }
}