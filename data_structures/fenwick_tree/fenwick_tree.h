#ifndef REFERENCE_FENWICK_TREE_H
#define REFERENCE_FENWICK_TREE_H

#define LSOne(S) ((S) & -(S))

#include <vector>

template<typename T = int>
class FenwickTree {
public:
    explicit FenwickTree(int n) : ft(n + 1) {};

    explicit FenwickTree(const std::vector<T> &v) : FenwickTree(v.size()) {
        for (int i = 1; i < v.size(); ++i) {
            ft[i] += v[i];
            if (i + LSOne(i) < v.size())
                ft[i + LSOne(i)] += ft[i];
        }
    };

    explicit FenwickTree(const std::vector<T> &&v) : FenwickTree(v) {}

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
        point_increment(i, amt - rsq(i, i));
    }


private:
    std::vector<T> ft;
};

#endif //REFERENCE_FENWICK_TREE_H
