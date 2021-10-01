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
int s;
vvi s1, s2;

bool good() {
    if (s1.empty() && s2.empty()) {
        return false;
    }
    if (s1.empty()) {
        return s2.back()[s] == 1;
    }
    if (s2.empty()) {
        return s1.back()[s] == 1;
    }
    for (int i = 0; i < 1001; ++i) {
        if (s2.back()[i] == 1 && s1.back()[s-i] == 1) {
            return true;
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n >> s;
    vi a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    int res = M;
    int l = 0;
    for (int r = 0; r < n; ++r) {
        if (s1.empty()) {
            s1.emplace_back(1001);
            s1.back()[0] = 1;
            s1.back()[a[r]] = 1;
        } else {
            s1.emplace_back(s1.back());
            for (int i = 1000 - a[r]; i >= 0; --i) {
                if (s1.back()[i] == 1) {
                    s1.back()[i + a[r]] = 1;
                }
            }
        }
        while (l <= r && good()) {
            res = min(res, r - l + 1);
            if (s2.empty()) {
                s2.emplace_back(1001);
                s2.back()[0] = 1;
                s2.back()[a[r]] = 1;
                for (int i = r - 1; i >= l; --i) {
                    s2.emplace_back(s2.back());
                    for (int j = 1000 - a[i]; j >= 0; --j) {
                        if (s2.back()[j] == 1) {
                            s2.back()[j + a[i]] = 1;
                        }
                    }
                }
                s1 = {};
            }
            s2.pop_back();
            ++l;
        }
    }

    cout << (res == M ? -1 : res)<< '\n';

}