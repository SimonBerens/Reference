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
    freopen("diamond.in", "r", stdin);
    freopen("diamond.out", "w", stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, k;
    cin >> n >> k;
    vi ds(n);
    for (int i = 0; i < n; ++i) {
        cin >> ds[i];
    }
    if (n <= 2) {
        cout << accumulate(ds.begin(), ds.end(), 0) << '\n';
        return 0;
    }
    sort(ds.begin(), ds.end());
    int l = 0;
    int cur_case = 0, res = 0;
    vi cache(n + 1);
    for (int i = 0; i < n; ++i) {
        while (ds[i] - ds[l] > k) {
            cur_case -= 1;
            l++;
        }
        if (ds[i] - ds[l] <= k) {
            cur_case += 1;
        }
        cache[i + 1] = max(cache[i], cur_case);
        res = max(res, cur_case + cache[l]);
    }
    cout << res << '\n';
}