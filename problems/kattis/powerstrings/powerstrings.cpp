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

#pragma GCC optimize ("Ofast")
#pragma GCC target ("avx2")

// call randint() for a random integer
mt19937 randint(chrono::steady_clock::now().time_since_epoch().count());

// returns a random integer over [a, b] inclusive
inline int uniform_randint(const int a, const int b) {
    return uniform_int_distribution<int>(a, b)(randint);
}

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

// checks if a number is prime in O(log^3(n)) time, randint comes from random.cpp.
// works for n <= 10^18
bool isprime(ll n) {
    static vector<bool> sieve = primesieve(1000000);
    if (n < sieve.size()) return sieve[n];
    if (n%2 == 0) return false;
    ll d = n-1, r = 0;
    while (d%2 == 0) r++, d >>= 1;
    for (int k = 0; k < 30; k++) {
        __int128_t x = 1, a = uniform_int_distribution<ll>(2, n-2)(randint);
        for (ll i = 1; i <= d; i <<= 1) {
            if (d&i) x = (x*a)%n;
            a = (a*a)%n;
        }
        bool f = 0;
        if (x == 1 || x == n-1) f = 1;
        for (int i = 1; i < r; i++)
            f = f || (x = (x*x)%n) == n-1;
        if (!f) return false;
    }
    return true;
}

// returns a sorted list of all prime factors of n in O(min(n^(1/2), n^(1/4)+log^3(n)+10^5)) time.
// works for n <= 10^18
vector<ll> primefactors(ll n) {
    static vector<ll> small = primesupto(1000000);
    if (isprime(n)) return {n};
    vector<ll> out;
    for (ll p : small) {
        if (p*p > n) break;
        while (n%p == 0)
            n /= p, out.push_back(p);
    }
    if (n == 1 || isprime(n)) {
        if (n != 1) out.push_back(n);
        return out;
    }
    __int128_t x = 2, y = 2;
    ll f = 0;
    for (ll z = 1; 1; z <<= 1) {
        y = x;
        for (ll i = 0; i < z; i++)
            if ((f = gcd(ll((x = (x*x+1)%n)-y), n)) > 1) {
                out.push_back(min(f, n/f)), out.push_back(max(f, n/f));
                return out;
            }
    }
    return out;
}

string s;

std::string repeat(const std::string& input, size_t num)
{
    std::ostringstream os;
    std::fill_n(std::ostream_iterator<std::string>(os), num, input);
    return os.str();
}

bool good(int p) {
    return (s.size() % p == 0) && (s == repeat(s.substr(0, s.size() / p), p));
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    while (true) {
        cin >> s;
        int szo = s.size();
        if (s == ".") break;
        auto pf = primefactors(s.size());
        for (int p : pf) {
            while (good(p)) {
                s = s.substr(0, s.size() / p);
            }
        }
        cout << szo / s.size() << '\n';
    }
}