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

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    vi atks, defs;
    for (int i = 0; i < n; ++i) {
        string pos;
        int strength;
        cin >> pos >> strength;
        if (pos == "ATK") {
            atks.push_back(strength);
        } else {
            defs.push_back(strength);
        }
    }
    vi cards(m);
    for (int i = 0; i < m; ++i) {
        cin >> cards[i];
    }
    sort(cards.begin(), cards.end());
    sort(atks.begin(), atks.end());
    sort(defs.begin(), defs.end());
    // pure attack
    int res1 = 0;
    int ci = m - 1, ai = 0;
    for (; ci >= 0 && ai < atks.size() && cards[ci] > atks[ai]; --ci, ++ai) res1 += cards[ci] - atks[ai];

    // try to get through attack and defense
    multiset<int> cardsms(cards.begin(), cards.end());
    // get through defense overshooting as little as possible
    for (int i = 0; i < defs.size(); ++i) {
        auto it = cardsms.upper_bound(defs[i]);
        if (it != cardsms.end()) {
            cardsms.erase(it);
        } else {
            cout << res1 << '\n';
            exit(0);
        }
    }
    // check that you can get through attack with biggest remaining cards
    int s = accumulate(cardsms.begin(), cardsms.end(), 0);
    for (int i = 0; i < atks.size(); ++i) {
        auto it = cardsms.lower_bound(atks[i]);
        if (it != cardsms.end()) {
            cardsms.erase(it);
        } else {
            cout << res1 << '\n';
            exit(0);
        }
    }
    // if so, print sum(remaining) - sum(atks)
    cout << max(res1, s - accumulate(atks.begin(), atks.end(), 0)) << '\n';
}