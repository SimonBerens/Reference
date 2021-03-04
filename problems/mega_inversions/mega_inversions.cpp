#include <bits/stdc++.h>

using namespace std;

#ifndef REFERENCE_FENWICK_TREE_H
#define REFERENCE_FENWICK_TREE_H

#define LSOne(S) ((S) & -(S))

#include <vector>

template<typename T = int>
class FenwickTree {
public:
    explicit FenwickTree(int n) : ft(n) {};

    explicit FenwickTree(std::vector<T> &v) : ft(v.size()) {
        for (int i = 1; i < v.size(); ++i) {
            ft[i] += v[i];
            if (i + LSOne(i) < v.size())
                ft[i + LSOne(i)] += ft[i];
        }
    };

    T prefix_rsq(int i) {
        int res = 0;
        while (i != 0) {
            res += ft[i];
            i -= LSOne(i);
        }
        return res;
    }

    T rsq(int i, int j) {
        return prefix_rsq(j) - prefix_rsq(i - 1);
    }

    void point_increment(int i, T amt) {
        for (; i < ft.size(); i += LSOne(i))
            ft[i] += amt;
    }

    void point_set(int i, T amt) {
        point_increment(i, amt - ft[i]);
    }


private:
    std::vector<T> ft;
};

#endif //REFERENCE_FENWICK_TREE_H

int main() {
    int n;
    cin >> n;
    vector<long long> v(n), freq(n + 2);
    for (int i = 0; i < n; ++i) {
        cin >> v[i];
        freq[v[i]] += 1;
    }
    FenwickTree<long long> f1(n + 2), f2(freq);
    long long res = 0;
    for (int j = 0; j < (int) v.size() - 1; ++j) {
        f2.point_increment(v[j], -1);
        res += f1.rsq(v[j] + 1, n) * f2.rsq(1, v[j] - 1);
        f1.point_increment(v[j], 1);
    }
    cout << res << endl;
}
