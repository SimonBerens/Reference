#include <bits/stdc++.h>

using namespace std;

#ifndef REFERENCE_DISCRETE_BINARY_SEARCH_H
#define REFERENCE_DISCRETE_BINARY_SEARCH_H


#include <iostream>
#include <functional>


template<typename IN>
IN discrete_binary_search(function<bool(IN)> predicate, IN low = 0, IN high = numeric_limits<IN>::max()) {
    while (low < high) {
        IN middle = low + (high - low) / 2; // todo std::midpoint in cpp 2020
        if (predicate(middle))
            high = middle;
        else low = middle + 1;
    }
    return low;
}

#endif //REFERENCE_DISCRETE_BINARY_SEARCH_H


typedef long long ll;

int main() {

    freopen("race.in","r",stdin);
    freopen("race.out","w",stdout);

    int k, n;
    cin >> k >> n;
    for (int i = 0; i < n; ++i) {
        ll x;
        cin >> x;

        int h = discrete_binary_search<ll>([k](ll c) -> bool {
            return c * (c + 1) > 2 * k;
        }, 0, k) - 1;
        if (h <= x) {
            ll d = k - h * (h + 1) / 2;
            cout << h + (d != 0) << "\n";
        } else {
            h = discrete_binary_search<ll>([x, k](ll c) -> bool {
                return c * (c + 1) - (x - 1) * x / 2 > k;
            }, 0, k) - 1;
            ll d = k - (h * (h + 1) - (x - 1) * x / 2);
            if (d == 0) {
                cout << 2 * h - (x - 1) << "\n";
            } else if (d > h) {
                cout << 2 * h - (x - 1) + 2 << "\n";
            } else {
                cout << 2 * h - (x - 1) + 1 << "\n";
            }
        }

    }
}