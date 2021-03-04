#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

array<array<ll, 101>, 30001> cnt;

void dp(vector<ll> &prices, ll pi, ll c) {
    if (cnt[c][pi] == -1) {
        cnt[c][pi] = 0;
        if (pi == prices.size()) {
            cnt[c][pi] = c == 0 ? 1 : 0;
        } else {
            dp(prices, pi + 1, c);
            cnt[c][pi] = cnt[c][pi + 1];
            if (c - prices[pi] >= 0) {
                dp(prices, pi, c - prices[pi]);
                cnt[c][pi] += cnt[c - prices[pi]][pi];
            }
            cnt[c][pi] = min(2LL, cnt[c][pi]);
        }
    }
}


int main() {
    for (auto &x : cnt) {
        fill(begin(x), end(x), -1);
    }
    ll n;
    cin >> n;
    vector<ll> prices(n);
    for (ll i = 0; i < n; ++i) {
        cin >> prices[i];
    }
    ll m;
    cin >> m;
    for (ll i = 0; i < m; ++i) {
        ll order;
        cin >> order;
        dp(prices, 0, order);
        ll nsols = cnt[order][0];
        if (nsols == 0) {
            cout << "Impossible" << "\n";
        } else if (nsols == 1) {
            ll c = order;
            for (ll j = 0; j < n; ++j) {
                while (c - prices[j] >= 0 && cnt[c - prices[j]][j] == 1) {
                    cout << j + 1 << " ";
                    c -= prices[j];
                }
            }
            cout << "\n";
        } else {
            cout << "Ambiguous" << "\n";
        }
    }

}
