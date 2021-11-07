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

int h, b;
vi dogs, buns;

int dpha[100][100001];

int dph(int i, int v) {
    if (i == h) {
        return v == 0 ? 0 : M;
    }
    int & res = dpha[i][v];
    if (res != -1) {
        return res;
    }
    return res  = min(dph(i + 1, v), dph(i + 1, v - dogs[i]) + 1);
}

int dpba[100][100001];


int dpb(int i, int v) {
    if (i == b) {
        return v == 0 ? 0 : M;
    }
    int & res = dpba[i][v];
    if (res != -1) {
        return res;
    }
    return res = min(dpb(i + 1, v), dpb(i + 1, v- buns[i]) + 1);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> h;
    dogs.assign(h, 0);
    for (int i = 0; i < h; ++i) {
        cin >> dogs[i];
    }
    cin >> b;
    buns.assign(b, 0);
    for (int i = 0; i < b; ++i) {
        cin >> buns[i];
    }

    fill(dpha[0] + 0, dpha[99] + 100001, -1);
    fill(dpba[0] + 0, dpba[99] + 100001, -1);
    int res = M;
    for (int v = 1; v <= 100000; ++v) {
        res = min(res, dph(0, v) + dpb(0, v));
    }
    if (res == M) {
        cout << "impossible\n";
    } else {
        cout << res << '\n';
    }
    

}