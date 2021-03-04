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


#include <bits/stdc++.h>
using namespace std;

int main () {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    for (int j = 0; j < t; ++j) {

        int m, r;
        cin >> m >> r;

        FenwickTree ft(m + r);
        vector<int> q_to_pos(m + 1);

        for (int i = 1; i <= m; ++i) {
            q_to_pos[i] = m - i + 1;
            ft.point_increment(i, 1);
        }
        for (int i = 1; i <= r; ++i) {
            int q;
            cin >> q;
            cout << ft.rsq(q_to_pos[q], m + r) - 1 << " ";
            ft.point_increment(q_to_pos[q], -1);
            q_to_pos[q] = m + i;
            ft.point_increment(q_to_pos[q], 1);
        }
        cout << "\n";
    }

}