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

double angle(double t) {
    return atan2(sin(t),cos(t));
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    vector<ll> xs(n), ys(n), rs(n);
    for (int i = 0; i < n; ++i) {
        cin >> xs[i] >> ys[i] >> rs[i];
    }

    auto dist = [&](int i, int j) -> double {
        return sqrt(pow(xs[j] - xs[i], 2) + pow(ys[j] - ys[i], 2));
    };

    auto is_disjoint = [&](int i, int j) -> bool {
        return dist(i, j) >= rs[i] + rs[j];
    };

    auto is_consumed = [&](int i, int j) -> bool {
        return dist(i, j) + rs[i] <= rs[j];
    };

    auto non_intersected_rads = [&](int i) -> double {
        map<double, int> cntr;
        for (int j = i + 1; j < n; ++j) {
            if (is_disjoint(i, j)) {
                continue;
            }
            if (is_consumed(i, j)) {
                return 0;
            }
            if (is_consumed(j, i)) {
                continue;
            }
            double a= rs[i], b = dist(i, j), c = rs[j];
            double gamma = acos((a * a + b * b - c * c) / (2 * a * b));
            double mid_angle = atan2(ys[j] - ys[i], xs[j] - xs[i]);
            double t1 = angle(mid_angle - gamma), t2 = angle(mid_angle + gamma);
            if (t1 < t2) {
                ++cntr[t1];
                --cntr[t2];
            } else {
                ++cntr[-M_PI];
                --cntr[t2];
                ++cntr[t1];
                --cntr[M_PI];
            }
        }
        double res = 0;
        cntr[-M_PI];
        cntr[M_PI];
        int acc = 0;
        double prev_rads = -M_PI;
        for (auto [rads, cnt] : cntr) {
            if (acc == 0) {
                res += rads - prev_rads;
            }
            prev_rads = rads;

            acc += cnt;
        }
        return res;
    };

    double res = 0;
    for (int i = 0; i < n; ++i) {
        res += rs[i] * non_intersected_rads(i);
    }
    cout << setprecision(10) << res << '\n';
}