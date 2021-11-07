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


bool query(int a, int b, int c, int d) {
    cout << "? " << a + 1 << " " << b + 1 << " " << c + 1 << " " << d + 1 << endl;
    char ans;
    cin >> ans;
    return ans == '<';
}

void get_edges(vvi &g, vii &pairs, int i, int j) {
    auto[a, b] = pairs[i];
    auto[c, d] = pairs[j];
    if (query(a, c, b, d)) {
        g[a].push_back(d);
        if (query(a, d, b, c)) {
            g[a].push_back(c);
            g[a].push_back(b);
        } else {
            g[b].push_back(d);
            g[c].push_back(d);
        }
    } else {
        g[b].push_back(c);
        if (query(a, d, b, c)) {
            g[a].push_back(c);
            g[d].push_back(c);
        } else {
            g[b].push_back(a);
            g[b].push_back(d);
        }
    }

}

vector<int> toposort(vector<vector<int>> adj) {
    vector<int> out, stk, in(adj.size(), 0);
    for (int i = 0; i < adj.size(); i++)
        for (int j: adj[i]) in[j]++;
    for (int i = 0; i < adj.size(); i++)
        if (!in[i]) stk.push_back(i);
    while (!stk.empty()) {
        out.push_back(stk.back());
        stk.pop_back();
        for (int j: adj[out.back()])
            if (!--in[j]) stk.push_back(j);
    }
    return out;
}

int main() {
    int t, n;
    cin >> t >> n;
    for (int test_no = 0; test_no < t; ++test_no) {
        vii pairs;
        vvi g(n);
        for (int i = 0; i < n - 1; ++i) {
            for (int j = 1; j < n; ++j) {
                pairs.pb({i, j});
            }
        }
        sort(all(pairs), [&](ii pi, ii pj) -> bool {
            return set<int>{pi[0], pi[1], pj[0], pj[1]}.size() == 4 && query(pi[0], pi[1], pj[0], pj[1]);
        });
        vi ctpi(n);
        for (int i = 0; i < pairs.size(); ++i) {
            auto[a, b] = pairs[i];
            if(a == 0) ctpi[b]=i;
            if(b == 0) ctpi[a]=i;
        }
        vi is(n);
        iota(all(is), 0);
        sort(all(is), [&](int i, int j) -> bool {
            return ctpi[i] < ctpi[j];
        });
        cout << "! ";
        for (int i: is) {
            cout << i << ' ';
        }
        cout << endl;
    }
}