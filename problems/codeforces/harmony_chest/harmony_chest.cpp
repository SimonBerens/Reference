#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>

using namespace __gnu_pbds;
template<typename K> using hset = gp_hash_table<K, null_type>;
template<typename K, typename V> using hmap = gp_hash_table<K, V>;


using namespace std;

using ll = long long;

using vi = vector<int>;
using vvi = vector<vector<int>>;

template<typename T>
using minq = priority_queue<T, vector<T>, greater<T>>;
template<typename T>
using maxq = priority_queue<T>;

ll M = 1000000007;

vi primes{2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53};
vi prime_masks(59); // map i -> x s.t. for all j, (x >> j) & 1 iff i % primes[j] == 0

void compute_masks() {
    for (int i = 2; i < prime_masks.size(); ++i) {
        for (int j = 0; j < primes.size(); ++j) {
            prime_masks[i] ^= (1 << j) * (i % primes[j] == 0);
        }
    }
}

int n;
vi a;

int dpa[100][1 << 16];

int dp(int i, int pm) {
    if (i == n) {
        return 0;
    }
    int &res = dpa[i][pm];
    if (res != -1) {
        return res;
    }
    res = M;
    for (int j = 1; j < prime_masks.size(); ++j) {
        if (prime_masks[j] & pm) {
            continue;
        }
        res = min(res, dp(i + 1, pm ^ prime_masks[j]) + abs(a[i] - j));
    }
    return res;
}

vi resv;
void dpt(int i, int pm) {
    if (i == n) {
        return;
    }
    int res = dp(i, pm);
    for (int j = 1; j < prime_masks.size(); ++j) {
        if (prime_masks[j] & pm) {
            continue;
        }
        if (res == dp(i + 1, pm ^ prime_masks[j]) + abs(a[i] - j)) {
            resv.push_back(j);
            dpt(i + 1, pm ^ prime_masks[j]);
            return;
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    a.assign(n, 0);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    fill(dpa[0] + 0, dpa[99] + (1 << 16), -1);
    compute_masks();
    dpt(0, 0);
    for (int i: resv) {
        cout << i << ' ';
    }
    cout << endl;
}