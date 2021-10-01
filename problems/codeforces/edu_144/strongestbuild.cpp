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

vi kthSmallest(vector<vector<int>>& mat, int k) {

    using vv = pair<int, vector<int>>;
    priority_queue<vv, vector<vv>, greater<vv>> q;
    vector<int> vec;

    set<vector<int>> visited;

    vector<int> num(mat.size(), 0);
    int sumVal = 0;
    for (int i = 0; i < num.size(); ++i) sumVal += mat[i][num[i]];
    visited.insert(num);
    q.push({sumVal, num});

    while (vec.size() < k) {


        vector<int> curr = q.top().second;
         vec.push_back(q.top().first);
        q.pop();

        for (int i = 0; i < curr.size(); ++i) {
            if (curr[i] + 1 < mat[0].size()) {
                ++curr[i];
                if (visited.find(curr) == visited.end()) {
                    int val = vec.back() + mat[i][curr[i]] - mat[i][curr[i] - 1];
                    q.push({val, curr});
                    visited.insert(curr);
                }
                --curr[i];
            }
        }
    }

    return vec;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    vvi mat(n);
    for (int i = 0; i < n; ++i) {
        int c;
        cin >> c;
        mat[i].assign(c, 0);
        for (int j = 0; j < c; ++j) {
            cin >> mat[i][j];
        }
    }
    auto builds = kthSmallest(mat, m + 1);
    for (const auto &build: builds) {
        if (build) {}
    }
}