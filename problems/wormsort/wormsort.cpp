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


class UnionFind {
public:

    explicit UnionFind(int n) : groups(n), elements(n), sizes(n, 1) {
        iota(elements.begin(), elements.end(), 0);
    };


    bool disjoint(const int a, const int b)  {
        return find_root(a) != find_root(b);
    }

    int group_size(const int a)  {
        return sizes[find_root(a)];
    }

    void unify(const int a, const int b) {
        auto root_a = find_root(a), root_b = find_root(b);
        if (root_a != root_b) {
            --groups;
            if (sizes[root_b] > sizes[root_a])
                std::swap(root_a, root_b);
            elements[root_b] = elements[root_a];
            sizes[root_a] += sizes[root_b];
        }
    }
private:
    vi elements, sizes;
    int groups;

    int find_root(const int val) {
        int start = val, cur;
        for (cur = start; cur != elements[cur]; cur = elements[cur]);
        int ret = cur;
        for (cur = start; cur != ret; cur = elements[cur])
            elements[cur] = ret;
        return ret;
    }
};

int n, m;
vi p;
vector<tuple<int, int, int>> edges;

int main() {
    freopen("wormsort.in", "r", stdin);
    freopen("wormsort.out", "w", stdout);
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> n >> m;
    p.assign(n, 0);
    for (int i = 0; i < n; ++i) {
        cin >> p[i];
        p[i]--;
    }
    if (is_sorted(p.begin(), p.end())) {
        cout << "-1\n";
        return 0;
    }
    for (int i = 0; i < m; ++i) {
        int a, b, w;
        cin >> a >> b >> w;
        a--;
        b--;
        edges.emplace_back(w, a, b);
    }
    sort(edges.begin(), edges.end(), greater<>());
    UnionFind uf(n);
    int cur = 0;
    for (int i = 0; i < n; ++i) {
        while (uf.disjoint(i, p[i])) {
            auto[w, a, b] = edges[cur++];
            uf.unify(a, b);
        }
    }
    auto [w, a, b] = edges[cur - 1];
    cout << w << "\n";
}
