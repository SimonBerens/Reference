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

inline bool isInteger(const std::string & s)
{
    if(s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false;

    char * p;
    strtol(s.c_str(), &p, 10);

    return (*p == 0);
}

int S;
vvi g;
vi is_f;

ll dpa[410];

ll dp(int p) {
    if (is_f[p]) {
        return 1;
    }

    ll & res = dpa[p];

    if (res != -1) {
        return res;
    }
    ll s = 0;
    for (const auto nbr: g[p]) {
        s += dp(nbr);
    }
    return res = s;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    for (int test_no = 0; test_no < t; ++test_no) {
        cin >> S;
        g.assign(410, vi{});
        is_f.assign(410, 0);
        for (int i = 0; i < S; ++i) {
            int page, x, y, z;
            string ending;
            cin >> page >> ending;
            if (isInteger(ending)) {
                x = stoi(ending);
                cin >> y >> z;
                g[page].insert(g[page].end(), {x, y, z});
            } else if (ending == "favourably") {
                is_f[page] = true;
            }
        }
        fill(&dpa[0], dpa + 411, -1LL);
        cout << dp(1) << '\n';
    }
}