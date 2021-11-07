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

int main() {
    freopen("snowboots.in", "r", stdin);
    freopen("snowboots.out", "w", stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, b;
    cin >> n >> b;
    minq<ii> depths;
    for (int i = 0; i < n; ++i) {
        int f;
        cin >> f;
        depths.push({f, i});
    }
    vector<array<int, 3>> qs(b);
    vi res(b);
    for (int i = 0; i < b; ++i) {
        cin >> qs[i][0] >> qs[i][1];
        qs[i][2] = i;
    }
    sort(all(qs));
    map<int, int> gaptlen; // start -> len
    map<int, set<int>, greater<>> lentgaps;
    gaptlen[0] = n;
    lentgaps[n].insert(0);

    auto longest_gap = [&]() -> int {
        return lentgaps.empty() ? 0 : lentgaps.begin()->first;
    };
    for (auto [s, d, ri]: qs) {
        // process depths <= s
        while (!depths.empty() && depths.top()[0] <= s) {
            auto [f, i] = depths.top();
            auto [start, len] = *(--gaptlen.upper_bound(i));
            gaptlen.erase(start);
            lentgaps[len].erase(start);
            if (lentgaps[len].empty()) lentgaps.erase(len);
            if (i != start) {
                gaptlen[start] = i - start;
                lentgaps[i - start].insert(start);
            }
            if (start + len - 1 != i) {
                gaptlen[i + 1] = start + len - 1 - i;
                lentgaps[start + len - 1 - i].insert(i + 1);
            }
            depths.pop();
        }
        // get longest gap, should be < d
        res[ri] = longest_gap() < d;
    }
    for (int x : res) {
        cout << x << '\n';
    }

}