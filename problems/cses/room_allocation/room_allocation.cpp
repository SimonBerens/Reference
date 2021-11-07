#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>

using namespace __gnu_pbds;
template<typename K> using hset = gp_hash_table<K, null_type>;
template<typename K, typename V> using hmap = gp_hash_table<K, V>;


using namespace std;

#define all(x) (x).begin(), (x).end()
#define pb push_back
#define eb emplace_back
#define smax(x, y) (x = max(x, y))
#define smin(x, y) (x = min(x, y))

using ll = long long;
using ld = long double;

template<typename T>
using vv = vector<vector<T>>;

using vi = vector<int>;
using ii = array<int, 2>;
using vii = vector<ii>;
using vvi = vv<int>;

using vll = vector<ll>;
using l2 = array<ll, 2>;
using vl2 = vector<l2>;
using vvll = vv<ll>;

template<typename T>
using minq = priority_queue<T, vector<T>, greater<T>>;
template<typename T>
using maxq = priority_queue<T>;

const ll M = 1000000007;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    vector<array<int, 3>> intervals(n); // start, end, customer num
    for (int i = 0; i < n; ++i) {
        cin >> intervals[i][0] >> intervals[i][1];
        intervals[i][2] = i;
    }
    sort(all(intervals));
    int res = 0;
    minq<ii> rooms; // end, roomnum
    vi roomnums(n);
    for (auto[s, e, i]: intervals) {
        int num = rooms.size();
        if (!rooms.empty()) {
            auto[re, rn] = rooms.top();
            if (re < s) {
                num = rn;
                rooms.pop();
            }
        }
        rooms.push({e, num});
        smax(res, (int) rooms.size());
        roomnums[i] = num;
    }
    cout << res << '\n';
    for (int rn: roomnums) {
        cout << rn + 1 << ' ';
    }
    cout << '\n';
}