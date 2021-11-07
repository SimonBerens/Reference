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

string s;
map<char, int> m;

bool good() {

}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> s;
    ll res = 0;
    for (char c = 'a'; c <= 'z'; ++c) {
        int i = s.find(c);
        if (i == string::npos) continue;
        set<char> seen;
        for (; i < s.size(); ++i) {
            if (s[i] == c) {
                seen.clear();
                continue;
            }
            if (seen.count(s[i]) == 0) {
                ++res;
                seen.insert(s[i]);
            }
        }
    }
    cout << res << '\n';

}