#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template <typename K> using hset = gp_hash_table<K, null_type>;
template <typename K, typename V> using hmap = gp_hash_table<K, V>;


using namespace std;

using ll = long long;

using vi = vector<ll>;
using vvi = vector<vector<ll>>;

template <typename T>
using minq = priority_queue<T, vector<T>, greater<T>>;
template <typename T>
using maxq = priority_queue<T>;

ll M = 1000000007;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll n;
    cin >> n;
    vector<ll> strengths(n);
    for (ll i = 0; i < n; ++i) {
        cin >> strengths[i];
    }
    sort(strengths.begin(), strengths.end());
    ll total_strength = accumulate(strengths.begin(), strengths.end(), 0ll);
    ll m;
    cin >> m;
    vector<ll> defences(m), attacks(m);
    for (ll i = 0; i < m; ++i) {
        cin >> defences[i] >> attacks[i];
    }

    for (ll i = 0; i < m; ++i) {
        ll j = distance(strengths.begin(), upper_bound(strengths.begin(), strengths.end(), defences[i]));
        ll weaker_cost = numeric_limits<ll>::max(), stronger_cost = numeric_limits<ll>::max();
        if (j != 0) {
            weaker_cost = defences[i] - strengths[j - 1] + max(attacks[i] - (total_strength - strengths[j - 1]), 0ll);
        }
        if (j != n) {
            stronger_cost = max(attacks[i] - (total_strength - strengths[j]), 0ll);
        }
        cout << min(weaker_cost, stronger_cost) << '\n';
    }
}