#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef pair<double, double> pdd;

int main() {
    ll n, l, w;
    while (cin >> n >> l >> w) {
        vector<pdd> intervals;
        intervals.reserve(n);
        for (int i = 0; i < n; ++i) {
            ll x, r;
            cin >> x >> r;
            if (2 * r > w) {
                double iw = sqrt(r * r - double(w) * w / 4.);
                intervals.emplace_back(x - iw, x + iw);
            }
        }
        sort(intervals.begin(), intervals.end());

        ll res = 0, i = 0;
        double end = 0;
        while (true) {
            double new_end = end;
            while (i < intervals.size() && intervals[i].first <= end) {
                new_end = max(new_end, intervals[i].second);
                i += 1;
            }
            res += 1;
            if (new_end == end) {
                cout << -1 << "\n";
                break;
            } else if (new_end >= l) {
                cout << res << "\n";
                break;
            }
            end = new_end;
        }
    }
}