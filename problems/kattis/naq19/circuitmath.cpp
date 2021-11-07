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
    int n;
    cin >> n;
    vi v(n);
    for (int i = 0; i < n; ++i) {
        char c;
        cin >> c;
        v[i] = c == 'T';
    }
    stack<int> s;
    char c;
    while (cin >> c) {
        if ('A' <= c && c <= 'Z') {
            s.push(v[c - 'A']);
        } else if (c == '-') {
            int a = s.top(); s.pop();
            s.push(1 - a);
        } else {
            int a = s.top();
            s.pop();
            int b = s.top();
            s.pop();
            if (c == '*') {
                s.push(a & b);
            } else if (c == '+') {
                s.push(a | b);
            }
        }
    }
    cout << (s.top() == 1 ? 'T' : 'F') << '\n';
}