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

mt19937 randint(chrono::steady_clock::now().time_since_epoch().count());

// returns a vector of length n, containing 1 if a number is prime, else 0.
// runs in O(nloglogn) time.
vector<bool> primesieve(int n) {
    vector<bool> sieve(n, 1);
    for (int i = 2; i < n; i++)
        if (sieve[i])
            for (int j = 2*i; j < n; j += i)
                sieve[j] = 0;
    sieve[1] = 0;
    return sieve;
}

// returns a sorted list of all primes less than or equal to n.
// runs in O(nloglogn) time.
vector<ll> primesupto(int n) {
    vector<bool> sieve = primesieve(n+1);
    vector<ll> out;
    for (int i = 2; i <= n; i++)
        if (sieve[i]) out.push_back(i);
    return out;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int d;
    cin >> d;
    vi qs(d);
    for (int i = 0; i < d; ++i) {
        cin >> qs[i];
    }
    int mx = *max_element(all(qs));
    auto primes = primesupto(mx);
    vector<ld> dp(mx + 1, -1);
    dp[0] = 0;
//    auto ndp = dp;

    vector<bitset<10001>> re;
    for (int p : primes) {
        re.eb();
        for (int s = p; s <= mx; ++s) {
            if (dp[s-p] == -1) continue;
            auto cand = dp[s - p] + log(p);
            if (dp[s] < cand) {
                dp[s] = cand;
                re.back()[s] = true;
            }
        }
    }

    for (int n : qs) {
        cout << exp(*max_element(dp.begin(), dp.begin() + n + 1)) << '\n';
    }

}