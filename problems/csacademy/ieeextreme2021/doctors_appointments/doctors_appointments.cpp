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
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    for (int test_no = 0; test_no < t; ++test_no) {
        int n;
        cin >> n;
        vector<array<int, 3>> apps(n);
        for (int i = 0; i < n; ++i) {
            cin >> apps[i][1] >> apps[i][0];
            apps[i][2] = i + 1;
        }
        sort(all(apps));
        for (auto & [r, l, i]: apps) swap(r, l);
        set<int> taken;
        for (int i = 1; i <= n + 1; ++i) {
            taken.insert(i);
        }
        bool poss = true;
        vi sched(n + 1);
        for (auto [l, r, i] : apps) {
            int next = *taken.lower_bound(l);
            if (next > r) {
                poss = false;
                break;
            }
            sched[next] = i;
            taken.erase(next);
        }

        if (poss) {
            for (int i = 1; i <= n; ++i) {
                cout << sched[i] << ' ';
            }
            cout << '\n';
        } else {
            cout << "impossible\n";
        }
    }
}