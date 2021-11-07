#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template <typename K> using hset = gp_hash_table<K, null_type>;
template <typename K, typename V> using hmap = gp_hash_table<K, V>;


using namespace std;

#define all(x) (x).begin(), (x).end()
#define pb push_back
#define smax(x, y) (x = max(x, y))
#define smin(x, y) (x = min(x, y))

using ll = long long;

using vi = vector<int>;
using vvi = vector<vector<int>>;

template <typename T>
using minq = priority_queue<T, vector<T>, greater<T>>;
template <typename T>
using maxq = priority_queue<T>;

const ll M = 1000000007;

int n, s;
vi a;

vi lv, rv;
vector<bitset<1001>> ldp, rdp;

void push(int v) {
    rv.push_back(v);
    rdp.push_back(rdp.back() | (rdp.back() << v));
}

void pop() {
    if (lv.empty()) {
        while (!rv.empty()) {
            lv.push_back(rv.back());
            rv.pop_back();
            rdp.pop_back();
            ldp.push_back(ldp.back() | (ldp.back() >> lv.back()));
        }
    }
    lv.pop_back();
    ldp.pop_back();
}

bool good() {
    return (ldp.back() & rdp.back()) != 0;

}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> s;
    a.assign(n, 0);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    rdp.emplace_back();
    rdp.back()[0] = 1;
    ldp.emplace_back();
    ldp.back()[s] = 1;

    int res = M;
    int l = -1;
    for (int r = 0; r < n; ++r) {
        push(a[r]);
        while (good()) {
            res = min(res, r - l++);
            pop();
        }
    }

    cout << (res == M ? -1 : res) << '\n';


}