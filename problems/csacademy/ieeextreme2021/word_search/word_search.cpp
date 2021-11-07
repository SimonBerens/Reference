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

// Knuth-Morris-Pratt algorithm. Returns a list of all indices at which W appears in S.
// Runs in O(|S|+|W|) time.
template<typename it>
vector<int> kmp(it S_first, it S_last, it W_first, it W_last) {
    int n = S_last-S_first, m = W_last-W_first;
    vector<int> out, ptr(m+1);
    ptr[0] = -1;
    for (int i = 1, j = 0; i < m; i++, j++) {
        if (W_first[i] == W_first[j])
            ptr[i] = ptr[j];
        else {
            ptr[i] = j;
            do
                j = ptr[j];
            while (j >= 0 && W_first[i] != W_first[j]);
        }
        if (i == m-1) ptr[m] = j+1;
    }
    for (int i = 0, j = 0; i < n;) {
        if (W_first[j] == S_first[i]) {
            i++, j++;
            if (j == m) {
                out.push_back(i-j);
                j = ptr[j];
            }
        } else {
            j = ptr[j];
            if (j < 0) i++, j++;
        }
    }
    return out;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int R, C, Q;
    cin >> R >> C >> Q;
    vector<string> g(R);
    for (int r = 0; r < R; ++r) {
        cin >> g[r];
    }
    vector<string> words(2 * Q);
    for (int i = 0; i < Q; ++i) {
        cin >> words[i];
        words[Q + i] = words[i];
        reverse(all(words[Q + i]));
    }
    // dp(r, cstate) = sum dp(r, cstate)
    // dp(r, c, cstate) = sum(

}