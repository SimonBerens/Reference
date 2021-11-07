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

void del(map<int, int, greater<>> &a, int x) {
    if (--a[x] == 0) a.erase(x);

}

bool solve(map<int, int, greater<>> &a, int removed) {
    int x = a.begin()->first + removed;
    int start = x;
    vii moves;
    while (!a.empty()) {
        int p = a.begin()->first;
        if (a.count(x - p) == 0) {
            return false;
        }
        del(a, p);
        del(a, x - p);
        moves.pb({p, x - p});
        x = p;
    }
    cout << "YES\n" << start << '\n';
    for (auto [p, q] : moves) {
        cout << p << ' ' << q << '\n';
    }
    return true;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    for (int test_no = 0; test_no < t; ++test_no) {
        int n;
        cin >> n;
        map<int, int, greater<>> ao;
        for (int i = 0; i < 2 * n; ++i) {
            int x;
            cin >> x;
            ++ao[x];
        }
        bool poss = false;
        for (auto[x, cnt]: ao) {
            auto a = ao;
            if (solve(a, x)) {
                poss = true;
                break;
            }
        }
        if (!poss) cout << "NO\n";
    }
}