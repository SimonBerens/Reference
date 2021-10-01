#include <functional>
#include <tuple>
#include <optional>
#include <variant>
#include <string>
#include <string_view>
#include <array>
#include <vector>
#include <deque>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <algorithm>
#include <valarray>
#include <random>
#include <numeric>
#include <iostream>
#include <cassert>
#include <sstream>

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

int main() {
    freopen("hoofball.in", "r", stdin);
    freopen("hoofball.out", "w", stdout);

    int N;
    cin >> N;
    if (N <= 2) {
        cout << 1 << "\n";
        exit(0);
    }
    vi cows(N);
    for (int i = 0; i < N; ++i) {
        cin >> cows[i];
    }
    sort(cows.begin(), cows.end());
    vvi g(N), gt(N);
    g[0].push_back(1);
    gt[1].push_back(0);
    g[N-1].push_back(N-2);
    gt[N-2].push_back(N-1);
    for (int i = 1; i < N - 1; ++i) {
        if (cows[i] - cows[i - 1] <= cows[i + 1] - cows[i]) {
            g[i].push_back(i - 1);
            gt[i - 1].push_back(i);
        } else {
            g[i].push_back(i + 1);
            gt[i + 1].push_back(i);
        }
    }
    int cyc = 0;
    for (int i = 0; i < N - 1; ++i) {
        if (g[i] == vi{i + 1} && g[i + 1] == vi{i} && gt[i] == vi{i + 1} && gt[i + 1] == vi{i}) {
            cyc += 1;
        }
    }
    cout << accumulate(gt.begin(), gt.end(), 0, [](int acc, const vi &v) -> int { return acc + v.empty(); }) + cyc
         << "\n";
}