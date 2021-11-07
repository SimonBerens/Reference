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
    freopen("convention2.in", "r", stdin);
    freopen("convention2.out", "w", stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    vector<array<int, 3>> cows(n);
    for (int i = 0; i < n; ++i) {
        cin >> cows[i][0] >> cows[i][1];
        cows[i][2] = i;
    }
    sort(all(cows));
    map<int, vi> arriving; // arrival time -> cowis
    minq<ii> waiting; // waiting -> seniority, cowi
    for (int i = 0; i < n; ++i) {
        arriving[cows[i][0]].pb(i);
    }
    int res = 0;
    int curt = 0;
    while (true) {
        // process waiting cows
        while (!waiting.empty()) {
            auto [sen, i] = waiting.top(); waiting.pop();
            smax(res, curt - cows[i][0]);
            curt += cows[i][1];
            while(!arriving.empty() && arriving.begin()->first <= curt) {
                auto & [at, v] = *arriving.begin();
                for (int ci : v) {
                    waiting.push({cows[ci][2], ci});
                }
                arriving.erase(at);
            }
        }

        if (arriving.empty()) {
            break;
        } else {
            auto & [at, v] = *arriving.begin();
            curt = at;
            for (int ci : v) {
                waiting.push({cows[ci][2], ci});
            }
            arriving.erase(at);
        }


        // if arrivals is empty we're done
        // process next set of arrivals
        // erase from map when done
    }
    cout << res << '\n';

}