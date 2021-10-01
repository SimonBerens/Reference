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

void add(int x, vi & basis) {
    for (auto &it: basis)
        if ((x ^ it) < x)
            x ^= it;
    if (x) {
        for (auto &it: basis)
            if ((x ^ it) < it)
                it ^= x;
        basis.push_back(x);
        sort(basis.begin(), basis.end());
    }
}


int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    vi basis;
    int tx = 0;
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        add(x, basis);
        tx ^= x;
    }

    if (tx == 0) {
        cout << -1 << '\n';
    } else {
        cout << basis.size() << '\n';
    }

}